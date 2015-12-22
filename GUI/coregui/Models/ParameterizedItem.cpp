// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParameterizedItem.cpp
//! @brief     Implements class ParameterizedItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParameterizedItem.h"
#include "Exceptions.h"
#include "MaterialEditor.h"
#include "GUIHelpers.h"
#include "PropertyVariantManager.h"
#include "GroupPropertyRegistry.h"
#include "GroupProperty.h"

#include <sstream>
#include <QEvent>
#include <QDynamicPropertyChangeEvent>
#include <QDebug>
#include <QMetaEnum>

const QString ParameterizedItem::P_NAME = "Name";
const QString ParameterizedItem::P_PORT = "Port";

ParameterizedItem::ParameterizedItem(QString model_type, ParameterizedItem *parent)
    : m_model_type(std::move(model_type)), mp_parent(parent)
{
    setDisplayName(m_model_type);
    if (mp_parent) {
        mp_parent->insertChildItem(-1, this);
    }

    registerProperty(P_NAME, QString(), PropertyAttribute(PropertyAttribute::HIDDEN));
    registerProperty(P_PORT, -1, PropertyAttribute(PropertyAttribute::HIDDEN));
    setItemName(m_model_type);
}

ParameterizedItem::~ParameterizedItem()
{
    qDeleteAll(m_children);
    qDeleteAll(m_sub_items);
}

QString ParameterizedItem::modelType() const
{
    return m_model_type;
}

QString ParameterizedItem::itemName() const
{
    return getRegisteredProperty(P_NAME).toString();
}

void ParameterizedItem::setItemName(const QString &item_name)
{
    setRegisteredProperty(P_NAME, item_name);
}

QString ParameterizedItem::displayName() const
{
    if (mp_parent) {
        int index = mp_parent->getCopyNumberOfChild(this);
        if (index >= 0) {
            return m_display_name + QString::number(index);
        }
    }
    return m_display_name;
}

void ParameterizedItem::setDisplayName(QString display_name)
{
    m_display_name = std::move(display_name);
}

QString ParameterizedItem::getItemLabel() const
{
    return QString("");
}

ParameterizedItem *ParameterizedItem::parent() const
{
    return mp_parent;
}

ParameterizedItem *ParameterizedItem::childAt(int row) const
{
    return m_children.value(row);
}

int ParameterizedItem::rowOfChild(ParameterizedItem *child) const
{
    return m_children.indexOf(child);
}

int ParameterizedItem::childItemCount() const
{
    return m_children.count();
}

bool ParameterizedItem::hasChildItems() const
{
    return !m_children.isEmpty();
}

QList<ParameterizedItem *> ParameterizedItem::childItems() const
{
    return m_children;
}

void ParameterizedItem::insertChildItem(int row, ParameterizedItem *item)
{
    if (row == -1)
        row = m_children.size();
    item->mp_parent = this;
    m_children.insert(row, item);
    onChildPropertyChange();
}

ParameterizedItem *ParameterizedItem::takeChildItem(int row)
{
    ParameterizedItem *item = m_children.takeAt(row);
    item->mp_parent = 0;
    onChildPropertyChange();
    return item;
}

ParameterizedItem *ParameterizedItem::getChildOfType(QString type) const
{
    for (QList<ParameterizedItem *>::const_iterator it = m_children.begin();
         it != m_children.end(); ++it) {
        if ((*it)->modelType() == type) return *it;
    }
    return 0;
}

bool ParameterizedItem::acceptsAsChild(const QString &child_name) const
{
    return m_valid_children.contains(child_name);
}

QList<QString> ParameterizedItem::acceptableChildItems() const
{
    return m_valid_children;
}

// emits signal on property change
bool ParameterizedItem::event(QEvent *e)
{
    if (e->type() == QEvent::DynamicPropertyChange) {
        QDynamicPropertyChangeEvent *propertyEvent = dynamic_cast<QDynamicPropertyChangeEvent *>(e);
        Q_ASSERT(e);
        QByteArray byte_array = propertyEvent->propertyName();
        QString name(byte_array.constData());
        onPropertyChange(name);
    }
    return QObject::event(e);
}

QMap<QString, ParameterizedItem *> ParameterizedItem::getSubItems() const
{
    return m_sub_items;
}

void ParameterizedItem::addPropertyItem(QString name, ParameterizedItem *item)
{
    // if (!item) return;
    Q_ASSERT(item);
    qDebug() << "ParameterizedItem::addPropertyItem()" << name;

    if (m_sub_items.contains(name)) {
        qDebug() << "       ParameterizedItem::addPropertyItem() -> item is already there" << name
                 << "replacing with " << item->modelType();
        delete m_sub_items[name];
        m_sub_items.remove(name);
    }
    m_sub_items[name] = item;
    item->mp_parent = this;
    onSubItemChanged(name);
    onChildPropertyChange();
    qDebug() << "ParameterizedItem::addPropertyItem() -> about to leave" << name;
}

bool ParameterizedItem::isRegisteredProperty(const QString &name) const
{
    return m_registered_properties.contains(name);
}

ParameterizedItem *ParameterizedItem::registerGroupProperty(const QString &group_name,
                                                            const Constants::ModelType &group_model)
{
    qDebug() << "ParameterizedItem::registerGroupProperty() ->"
             << "this->modelType" << modelType() << "group_name" << group_name << " group_model"
             << group_model;

    GroupProperty_t group_property
        = GroupPropertyRegistry::createGroupProperty(group_name, group_model);
    QVariant variant;
    variant.setValue(group_property);
    registerProperty(group_name, variant);
    group_property->setParent(this);
    ParameterizedItem *p_result = m_sub_items[group_name];
    if (group_property->type() == GroupProperty::FIXED) {
        p_result->setDisplayName(group_name);
    }
    return p_result;
}

ParameterizedItem *ParameterizedItem::setGroupProperty(const QString &name, const QString &value)
{
    qDebug() << "ParameterizedItem::setGroupProperty()" << name << value;
    GroupProperty_t group_property = getRegisteredProperty(name).value<GroupProperty_t>();
    group_property->setCurrentType(value);
    return m_sub_items[name];
}

void ParameterizedItem::registerProperty(const QString &name, const QVariant &variant,
                                         const PropertyAttribute &attribute)
{
    if (m_registered_properties.contains(name))
        throw GUIHelpers::Error(
            "ParameterizedItem::registerProperty() -> Error. Already existing property " + name);

    if (m_property_attribute.contains(name))
        throw GUIHelpers::Error(
            "ParameterizedItem::registerProperty() -> Error. Already existing attribute " + name);

    m_registered_properties << name;
    m_property_attribute[name] = attribute;

    setProperty(name.toUtf8().constData(), variant);
}

void ParameterizedItem::setRegisteredProperty(const QString &name, const QVariant &variant)
{
    // check if variant of previous property coincides with new one
    QVariant previous_variant = getRegisteredProperty(name);
    if (GUIHelpers::getVariantType(previous_variant) != GUIHelpers::getVariantType(variant)) {
        qDebug() << "ParameterizedItem::setRegisteredProperty() -> Error. Type of previous and new "
                    "variant does not coincide.";
        qDebug() << "New variant" << variant << ", previous " << previous_variant;
        throw GUIHelpers::Error("ParameterizedItem::setRegisteredProperty() -> Error. Type of "
                                "previous and new variant does not coincide.");
    }

    setProperty(name.toUtf8().constData(), variant);
}

QVariant ParameterizedItem::getRegisteredProperty(const QString &name) const
{
    if (!m_registered_properties.contains(name))
        throw GUIHelpers::Error(
            "ParameterizedItem::getRegisteredProperty() -> Error. Unknown property '" + name
            + "', item '" + modelType() + "'");


    // for debugging purpose
//    PropertyAttribute attribute = getPropertyAttribute(name);
//    if(attribute.getAppearance() == PropertyAttribute::DISABLED) {
//        throw GUIHelpers::Error("ParameterizedItem::getRegisteredProperty() -> Logic Error? "
//            "You are trying to get DISABLED property with name '" +name +"', model " + modelType());
//    }

    return property(name.toUtf8().constData());
}

void ParameterizedItem::removeRegisteredProperty(const QString &name)
{
    if(isRegisteredProperty(name)) {
        qDebug() << "ParameterizedItem::removeRegisteredProperty()" << name;
        if (m_sub_items.contains(name)) {
            qDebug()
                << "       ParameterizedItem::removeRegisteredProperty() -> Removing property iteme";
            delete m_sub_items[name];
            m_sub_items.remove(name);
        }
        m_registered_properties.removeOne(name);
        m_property_attribute.remove(name);
        setProperty(name.toUtf8().constData(), QVariant());
    }
}

PropertyAttribute ParameterizedItem::getPropertyAttribute(const QString &name) const
{
    if (!m_registered_properties.contains(name))
        throw GUIHelpers::Error(
            "ParameterizedItem::getPropertyAttribute() -> Error. Unknown property " + name + " "
            + modelType());

    if (!m_property_attribute.contains(name))
        throw GUIHelpers::Error(
            "ParameterizedItem::getPropertyAttribute() -> Error. Unknown property attribute "
            + name);

    return m_property_attribute[name];
}

void ParameterizedItem::setPropertyAttribute(const QString &name,
                                             const PropertyAttribute &attribute)
{
    if (!m_registered_properties.contains(name))
        throw GUIHelpers::Error(
            "ParameterizedItem::setPropertyAttribute() -> Error. Unknown property " + name);

    if (!m_property_attribute.contains(name))
        throw GUIHelpers::Error(
            "ParameterizedItem::setPropertyAttribute() -> Error. Unknown property attribute "
            + name);

    m_property_attribute[name] = attribute;
}

void ParameterizedItem::setPropertyAppearance(const QString &name,
                                              const PropertyAttribute::EAppearance &appearance)
{
    if (!m_registered_properties.contains(name))
        throw GUIHelpers::Error(
            "ParameterizedItem::setPropertyAppearance() -> Error. Unknown property " + name);

    if (!m_property_attribute.contains(name))
        throw GUIHelpers::Error(
            "ParameterizedItem::setPropertyAppearance() -> Error. Unknown property attribute "
            + name);

    m_property_attribute[name].setAppearance(appearance);
}

void ParameterizedItem::onPropertyChange(const QString &name)
{
    if (mp_parent)
        mp_parent->onChildPropertyChange();
    emit propertyChanged(name);
}

void ParameterizedItem::onChildPropertyChange()
{
    qDebug() << "ParameterizedItem::onChildPropertyChange()";
    if (mp_parent)
        mp_parent->onChildPropertyChange();
}

void ParameterizedItem::print() const
{
    qDebug() << "--- ParameterizedItem::print() ------------------------------------";
    qDebug() << modelType() << displayName();
    qDebug() << "--- SubItems ---";
    for (QMap<QString, ParameterizedItem *>::const_iterator it = m_sub_items.begin();
         it != m_sub_items.end(); ++it) {
        qDebug() << "   key:" << it.key() << " value->modelType:" << it.value()->modelType();
    }
    qDebug() << "--- Properties ---";
    QList<QByteArray> property_names = dynamicPropertyNames();
    for (int i = 0; i < property_names.length(); ++i) {
        QString name(property_names[i]);
        qDebug() << name << property(name.toUtf8().constData());
    }
    qDebug() << " ";
}

// returns child which should be removed by the model due to over population of children of given
// type
ParameterizedItem *ParameterizedItem::getCandidateForRemoval(ParameterizedItem *new_comer)
{
    if (!new_comer)
        return 0;

    QMap<int, QVector<ParameterizedItem *> > nport_to_nitems;
    foreach (ParameterizedItem *child, m_children) {
        int nport = child->getRegisteredProperty(P_PORT).toInt();
        nport_to_nitems[nport].push_back(child);
    }

    QMap<int, QVector<ParameterizedItem *> >::iterator it = nport_to_nitems.begin();
    while (it != nport_to_nitems.end()) {
        int nport = it.key();
        if (m_port_info.contains(nport)) {
            if (m_port_info[nport].m_item_max_number != 0
                && it.value().size() > m_port_info[nport].m_item_max_number) {
                foreach (ParameterizedItem *item, it.value()) {
                    if (item != new_comer)
                        return item;
                }
            }
        }
        ++it;
    }

    return 0;
}

void ParameterizedItem::setItemPort(ParameterizedItem::PortInfo::EPorts nport)
{
    setRegisteredProperty(P_PORT, nport);
}

void ParameterizedItem::addToValidChildren(const QString &name, PortInfo::EPorts nport,
                                           int nmax_items)
{
    m_valid_children.append(name);

    if (m_port_info.contains(nport)) {
        m_port_info[nport].m_item_names << name;
        m_port_info[nport].m_item_max_number = nmax_items;
    } else {
        m_port_info[nport] = PortInfo(name, nmax_items);
    }
}

void ParameterizedItem::swapChildren(int first, int second)
{
    m_children.swap(first, second);
}

QStringList ParameterizedItem::getParameterTreeList(QString prefix) const
{
    QStringList result;
    // add child parameters:
    if (hasChildItems()) {
        for (auto p_child : m_children) {
            QString child_name = p_child->displayName();
            QString child_prefix = prefix + child_name + QString("/");
            result << p_child->getParameterTreeList(child_prefix);
        }
    }
    // add subitem parameters:
    if (m_sub_items.size() > 0) {
        for (QMap<QString, ParameterizedItem *>::const_iterator it = m_sub_items.begin();
             it != m_sub_items.end(); ++it) {
            PropertyAttribute prop_attribute = getPropertyAttribute(it.key());
            if (prop_attribute.getAppearance() & (PropertyAttribute::HIDDEN |
                                                  PropertyAttribute::DISABLED) ) {
                continue;
            }
            ParameterizedItem *p_subitem = it.value();
            QString subitem_name = p_subitem->displayName();
            QString subitem_prefix = prefix + subitem_name + QString("/");
            result << p_subitem->getParameterTreeList(subitem_prefix);
        }
    }
    // add own parameters:
    result << getParameterList(prefix);
    return result;
}

std::string ParameterizedItem::translateParameterName(const QString &par_name) const
{
    std::ostringstream result;
    auto first_field = getFirstField(par_name);
    result << "/" << translateSingleName(first_field);
    auto remainder = stripFirstField(par_name);
    if (remainder != "") {
        auto p_child = getChildByDisplayName(first_field);
        result << p_child->translateParameterName(remainder);
    }
    return result.str();
}

//! called when new SubItem appeared
void ParameterizedItem::onSubItemChanged(const QString &propertyName)
{
    connect(m_sub_items[propertyName], SIGNAL(propertyChanged(QString)), this,
            SLOT(processSubItemPropertyChanged(QString)), Qt::UniqueConnection);
    emit subItemChanged(propertyName);
}

void ParameterizedItem::onSubItemPropertyChanged(const QString &property_group,
                                                 const QString &property_name)
{
    emit subItemPropertyChanged(property_group, property_name);
    if (mp_parent)
        mp_parent->onChildPropertyChange();
}

//! called when SubItem change one of its properties
void ParameterizedItem::processSubItemPropertyChanged(const QString &propertyName)
{
    Q_UNUSED(propertyName);
    ParameterizedItem *propertyItem = qobject_cast<ParameterizedItem *>(sender());
    for (QMap<QString, ParameterizedItem *>::iterator it = m_sub_items.begin();
         it != m_sub_items.end(); ++it) {
        if (it.value() == propertyItem) {
            GroupProperty_t group_property
                = getRegisteredProperty(it.key()).value<GroupProperty_t>();
            group_property->setCurrentLabel(propertyItem->getItemLabel());
            onSubItemPropertyChanged(it.key(), propertyName);
            return;
        }
    }
    throw GUIHelpers::Error("ParameterizedItem::onSubItemPropertyChanged() ->"
                            " Error. No such propertyItem found");
}

QString ParameterizedItem::getFirstField(const QString &par_name) const
{
    QStringList par_list = par_name.split("/");
    if (par_list.size()==0) return QString();
    return par_list.front();
}

QString ParameterizedItem::stripFirstField(const QString &par_name) const
{
    QStringList par_list = par_name.split("/");
    if (par_list.size()<2) return QString();
    par_list.removeFirst();
    return par_list.join("/");
}

std::string ParameterizedItem::translateSingleName(const QString &name) const
{
    return name.toStdString();
}

ParameterizedItem *ParameterizedItem::getChildByDisplayName(const QString &name) const
{
    // look through child items:
    if (hasChildItems()) {
        for (auto p_child : m_children) {
            QString child_name = p_child->displayName();
            if (child_name == name) {
                return p_child;
            }
        }
    }
    // look through subitems:
    if (m_sub_items.size() > 0) {
        for (QMap<QString, ParameterizedItem *>::const_iterator it = m_sub_items.begin();
             it != m_sub_items.end(); ++it) {
            ParameterizedItem *p_subitem = it.value();
            QString subitem_name = p_subitem->displayName();
            if (subitem_name == name) {
                return p_subitem;
            }
        }
    }
    // nothing found...
    return nullptr;
}

QStringList ParameterizedItem::getParameterList(QString prefix) const
{
    QStringList result;
    QList<QByteArray> property_names = dynamicPropertyNames();
    for (int i = 0; i < property_names.length(); ++i) {
        QString prop_name = QString(property_names[i]);
        PropertyAttribute prop_attribute = getPropertyAttribute(prop_name);
        if (prop_attribute.getAppearance() & (PropertyAttribute::HIDDEN |
                                              PropertyAttribute::DISABLED) ) {
            continue;
        }
        QVariant variant = property(prop_name.toUtf8().constData());
        int type = GUIHelpers::getVariantType(variant);
        if (type == QVariant::Double) {
            result << prefix + prop_name;
        }
    }
    return result;
}

int ParameterizedItem::getCopyNumberOfChild(const ParameterizedItem *p_item) const
{
    if (!p_item) return -1;
    int result = -1;
    int count = 0;
    QString model_type = p_item->modelType();
    // check child items:
    if (hasChildItems()) {
        for (auto p_child_item : m_children) {
            QString child_type = p_child_item->modelType();
            if (p_child_item == p_item) {
                result = count;
            }
            if (child_type == model_type) {
                ++count;
            }
        }
    }
    // check subitems:
    if (m_sub_items.size() > 0) {
        for (QMap<QString, ParameterizedItem *>::const_iterator it = m_sub_items.begin();
             it != m_sub_items.end(); ++it) {
            ParameterizedItem *p_sub_item = it.value();
            QString subitem_type = p_sub_item->modelType();
            if (p_sub_item == p_item) {
                result = count;
            }
            if (subitem_type == model_type) {
                ++count;
            }
        }
    }
    if (count > 1) return result;
    return -1;
}
