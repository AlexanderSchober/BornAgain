// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionModel.cpp
//! @brief     Implements class SessionModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SessionModel.h"
#include "GUIHelpers.h"
#include "ItemFactory.h"
#include "SessionItemUtils.h"
#include <QFile>
#include <QMimeData>

using SessionItemUtils::ParentRow;

namespace
{
const int MaxCompression = 9;
}

SessionModel::SessionModel(QString model_tag, QObject* parent)
    : QAbstractItemModel(parent)
    , m_root_item(0)
    , m_name("DefaultName")
    , m_model_tag(model_tag)
{
    createRootItem();
}

void SessionModel::createRootItem()
{
    m_root_item = ItemFactory::createEmptyItem();
    m_root_item->setModel(this);
    m_root_item->registerTag("rootTag");
    m_root_item->setDefaultTag("rootTag");
}

SessionModel::~SessionModel()
{
    delete m_root_item;
}

Qt::ItemFlags SessionModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags result_flags = QAbstractItemModel::flags(index);
    if (index.isValid()) {
        result_flags |= Qt::ItemIsSelectable | Qt::ItemIsEnabled
                        | Qt::ItemIsDragEnabled;
        SessionItem* item = itemForIndex(index);
        if (index.column() == ITEM_VALUE && item->value().isValid())
            result_flags |= Qt::ItemIsEditable;
        QVector<QString> acceptable_child_items = getAcceptableDefaultItemTypes(index);
        if (acceptable_child_items.contains(m_dragged_item_type)) {
            result_flags |= Qt::ItemIsDropEnabled;
        }
    } else {
        result_flags |= Qt::ItemIsDropEnabled;
    }
    return result_flags;
}

QVariant SessionModel::data(const QModelIndex& index, int role) const
{
    if (!m_root_item || !index.isValid() || index.column() < 0 || index.column() >= columnCount(QModelIndex())) {
        return QVariant();
    }
    if (SessionItem* item = itemForIndex(index)) {
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            if (index.column() == ITEM_VALUE)
                return item->data(Qt::DisplayRole);
            if (index.column() == ITEM_NAME)
                return item->itemName();
        } else if(role == Qt::ToolTipRole) {
            return item->displayName();
        } else {
            return item->data(role);
        }
    }
    return QVariant();
}

QVariant SessionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case ITEM_NAME:
            return "Name";
        case ITEM_VALUE:
            return "Value";
        }
    }
    return QVariant();
}

int SessionModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return 0;
    SessionItem* parent_item = itemForIndex(parent);
    return parent_item ? parent_item->numberOfChildren() : 0;
}

int SessionModel::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return 0;
    return MAX_COLUMNS;
}

QModelIndex SessionModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!m_root_item || row < 0 || column < 0 || column >= columnCount(QModelIndex())
        || (parent.isValid() && parent.column() != 0))
        return QModelIndex();
    SessionItem* parent_item = itemForIndex(parent);
    if (SessionItem* item = parent_item->childAt(row)) {
        return createIndex(row, column, item);
    }
    return QModelIndex();
}

QModelIndex SessionModel::parent(const QModelIndex& child) const
{
    if (!child.isValid())
        return QModelIndex();
    if (SessionItem* child_item = itemForIndex(child)) {
        if (SessionItem* parent_item = child_item->parent()) {
            if (parent_item == m_root_item)
                return QModelIndex();

            return createIndex(ParentRow(*parent_item), 0, parent_item);
        }
    }
    return QModelIndex();
}

bool SessionModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid())
        return false;
    QModelIndex dataIndex = index;
    if (SessionItem* item = itemForIndex(dataIndex)) {
        if (item->setData(role, value)) {
            return true;
        }
    }
    return false;
}

bool SessionModel::removeRows(int row, int count, const QModelIndex& parent)
{
    if (!m_root_item)
        return false;
    SessionItem* item = parent.isValid() ? itemForIndex(parent) : m_root_item;
    for (int i = 0; i < count; ++i) {
        delete item->takeRow(row);
    }
    return true;
}

QStringList SessionModel::mimeTypes() const
{
    return QStringList() << SessionXML::ItemMimeType;
}

QMimeData *SessionModel::mimeData(const QModelIndexList& indices) const
{
    if (indices.count() != 2)
        return 0;
    if (SessionItem* item = itemForIndex(indices.at(0))) {
        QMimeData *mime_data = new QMimeData;
        QByteArray xml_data;
        QXmlStreamWriter writer(&xml_data);
        SessionWriter::writeItemAndChildItems(&writer, item);
        mime_data->setData(SessionXML::ItemMimeType, qCompress(xml_data, MaxCompression));
        return mime_data;
    }
    return 0;
}

bool SessionModel::canDropMimeData(const QMimeData* data, Qt::DropAction action, int row,
                                   int column, const QModelIndex& parent) const
{
    (void)row;
    if (action == Qt::IgnoreAction)
        return true;
    if (action != Qt::MoveAction || column > 0 || !data
        || !data->hasFormat(SessionXML::ItemMimeType))
        return false;
    if (!parent.isValid())
        return true;
    QVector<QString> acceptable_child_items = getAcceptableDefaultItemTypes(parent);
    QByteArray xml_data = qUncompress(data->data(SessionXML::ItemMimeType));
    QXmlStreamReader reader(xml_data);
    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            if (reader.name() == SessionXML::ItemTag) {
                const QString model_type
                    = reader.attributes().value(SessionXML::ModelTypeAttribute).toString();
                return acceptable_child_items.contains(model_type);
            }
        }
    }
    return false;
}

bool SessionModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                                const QModelIndex& parent)
{
    if (action == Qt::IgnoreAction)
        return true;
    if (action != Qt::MoveAction || column > 0 || !data
        || !data->hasFormat(SessionXML::ItemMimeType))
        return false;
    if (!canDropMimeData(data, action, row, column, parent))
        return false;
    if (SessionItem* item = itemForIndex(parent)) {
        QByteArray xml_data = qUncompress(data->data(SessionXML::ItemMimeType));
        QXmlStreamReader reader(xml_data);
        if (row == -1)
            row = item->numberOfChildren();
        beginInsertRows(parent, row, row);
        // this code block is currently not in use. The row parameter of the reader is removed
        //SessionReader::readItems(&reader, item, row);
        endInsertRows();
        return true;
    }
    return false;
}

QModelIndex SessionModel::indexOfItem(SessionItem* item) const
{
    if (!item || item == m_root_item || !item->parent())
        return QModelIndex();
    SessionItem* parent_item = item->parent();
    int row = parent_item->rowOfChild(item);
    return createIndex(row, 0, item);
}

SessionItem* SessionModel::insertNewItem(QString model_type, const QModelIndex& parent,
                                         int row, QString tag)
{
    SessionItem* parent_item = itemForIndex(parent);
    if (!parent_item)
        parent_item = m_root_item;
    if (row > parent_item->numberOfChildren())
        return nullptr;
    if (parent_item != m_root_item) {
        if (tag.isEmpty())
            tag = parent_item->defaultTag();
        SessionTagInfo tagInfo = parent_item->getTagInfo(tag);

        if (!tagInfo.modelTypes.contains(model_type))
            return nullptr;
    }
    SessionItem* new_item = ItemFactory::createItem(model_type);

    if (!new_item)
        throw GUIHelpers::Error("SessionModel::insertNewItem() -> Wrong model type " + model_type);
    if(!parent_item->insertItem(row, new_item, tag)) {
        throw GUIHelpers::Error("SessionModel::insertNewItem -> Error. Can't insert item");
    }
    return new_item;
}

QVector<QString> SessionModel::getAcceptableDefaultItemTypes(const QModelIndex& parent) const
{
    QVector<QString> result;
    if (SessionItem* parent_item = itemForIndex(parent)) {
        result = parent_item->acceptableDefaultItemTypes();
    }
    return result;
}

void SessionModel::clear()
{
    beginResetModel();
    delete m_root_item;
    createRootItem();
    endResetModel();
}

void SessionModel::load(const QString& filename)
{
    beginResetModel();
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        throw GUIHelpers::Error(file.errorString());
    clear();
    m_root_item = ItemFactory::createEmptyItem();
    QXmlStreamReader reader(&file);
    SessionReader::readItems(&reader, m_root_item);
    if (reader.hasError())
        throw GUIHelpers::Error(reader.errorString());
    endResetModel();
}

void SessionModel::save(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        throw GUIHelpers::Error(file.errorString());

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("BornAgain");
    writer.writeAttribute("Version", GUIHelpers::getBornAgainVersionString());
    SessionWriter::writeItemAndChildItems(&writer, m_root_item);
    writer.writeEndElement(); // BornAgain
    writer.writeEndDocument();
}

SessionItem* SessionModel::itemForIndex(const QModelIndex& index) const
{
    if (index.isValid()) {
        if (SessionItem* item = static_cast<SessionItem*>(index.internalPointer()))
            return item;
    }
    return m_root_item;
}

void SessionModel::readFrom(QXmlStreamReader* reader, WarningMessageService* messageService)
{
    Q_ASSERT(reader);

    if (reader->name() != m_model_tag)
        throw GUIHelpers::Error("SessionModel::readFrom() -> Format error in p1");

    beginResetModel();
    clear();

    m_name = reader->attributes().value(SessionXML::ModelNameAttribute).toString();

    SessionReader::readItems(reader, m_root_item, QString(), messageService);
    if (reader->hasError())
        throw GUIHelpers::Error(reader->errorString());
    endResetModel();
}

void SessionModel::writeTo(QXmlStreamWriter* writer, SessionItem* parent)
{
    if (!parent)
        parent = m_root_item;
    SessionWriter::writeTo(writer, parent);
}

//! Move given parameterized item to the new_parent at given row. If new_parent is not defined,
//! use root_item as a new parent.
SessionItem* SessionModel::moveParameterizedItem(SessionItem* item, SessionItem* new_parent,
                                                 int row, const QString &tag)
{
    if (!new_parent)
        new_parent = m_root_item;
    const QString tagName = tag.isEmpty() ? new_parent->defaultTag() : tag;

    if (new_parent) {
        if (!new_parent->getTagInfo(tagName).modelTypes.empty() &&
                !new_parent->getTagInfo(tagName).modelTypes.contains(item->modelType()))
            return 0;
    }
    if (item->parent() == new_parent) {
        // take care of indexes when moving item within same parent
        int previousIndex = item->parent()->getItems(tagName).indexOf(item);
        if (row==previousIndex) {
            return item;
        } else if (previousIndex >= 0 && row>previousIndex) {
            row--;
        }
    }
    SessionItem* stuff = item->parent()->takeRow(item->parent()->rowOfChild(item));
    if(!new_parent->insertItem(row, stuff, tagName)) {
        SessionTagInfo info = new_parent->getTagInfo(tagName);
        if (info.max == info.childCount && info.childCount == 1) {
            SessionItem* old = new_parent->takeItem(0, tagName);
            new_parent->insertItem(row, stuff, tagName);
            m_root_item->insertItem(-1, old);
        }
        m_root_item->insertItem(-1, stuff);
    }
    return stuff;
}

//! Copy given item to the new_parent at given row. Item indended for copying can belong to
//! another model and it will remains intact. Returns pointer to the new child.
SessionItem* SessionModel::copyParameterizedItem(const SessionItem* item_to_copy,
                                                 SessionItem* new_parent, const QString &tag)
{
    if (!new_parent) {
        new_parent = m_root_item;
    }
    const QString tagName = tag.isEmpty() ? new_parent->defaultTag() : tag;

    QByteArray xml_data;
    QXmlStreamWriter writer(&xml_data);
    SessionWriter::writeItemAndChildItems(&writer, item_to_copy);

    QXmlStreamReader reader(xml_data);

    SessionReader::readItems(&reader, new_parent, tagName);

    return new_parent->getItems(tagName).back();
}

SessionModel* SessionModel::createCopy(SessionItem* parent)
{
    (void)parent;
    throw GUIHelpers::Error("SessionModel::createCopy() -> Error. Not implemented.");
}

//! returns top level item with given name and model type
SessionItem* SessionModel::topItem(const QString& model_type, const QString& item_name) const
{
    QList<SessionItem*> items = topItems(model_type);

    if(item_name.isEmpty() && items.size())
        return items.front();

    foreach(SessionItem* item, items) {
        if(item_name == item->itemName())
            return item;
    }
    return nullptr;
}

//! Returns top items which are children of parentIndex and have given model_type
QList<SessionItem*> SessionModel::topItems(const QString& model_type,
                                           const QModelIndex& parentIndex) const
{
    QList<SessionItem*> result;
    for (int i_row = 0; i_row < rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = index(i_row, 0, parentIndex);
        if (SessionItem* item = itemForIndex(itemIndex)) {
            if (model_type.isEmpty()) {
                result.append(item);
            } else {
                if (item->modelType() == model_type) {
                    result.append(item);
                }
            }
        }
    }
    return result;
}

QStringList SessionModel::topItemNames(const QString& model_type,
                                       const QModelIndex& parentIndex) const
{
    QList<SessionItem*> items = topItems(model_type, parentIndex);
    QStringList result;
    foreach(SessionItem* item, items) {
        result.append(item->itemName());
    }
    return result;
}

void SessionModel::initFrom(SessionModel* model, SessionItem*)
{
    QByteArray byte_array;
    QXmlStreamWriter writer(&byte_array);
    writer.setAutoFormatting(true);

    model->writeTo(&writer);

    QXmlStreamReader reader(byte_array);

    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            readFrom(&reader);
        }
    }
}

SessionItem* SessionModel::rootItem() const{
    return m_root_item;
}

QVector<SessionItem*> SessionModel::nonXMLData() const
{
    return QVector<SessionItem*>();
}

