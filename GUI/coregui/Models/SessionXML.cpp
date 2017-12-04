// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionXML.cpp
//! @brief     Implements reader and writer classes for SessionModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ColorProperty.h"
#include "ComboProperty.h"
#include "GUIHelpers.h"
#include "GroupItem.h"
#include "ItemFactory.h"
#include "ExternalProperty.h"
#include "SessionModel.h"
#include "WarningMessageService.h"
#include <QtCore/QXmlStreamWriter>

namespace
{
const QString SET_ITEM_PROPERTY_ERROR = "SET_ITEM_PROPERTY_ERROR";
const QString ITEM_IS_NOT_INITIALIZED = "ITEM_IS_NOT_INITIALIZED";
const QString NON_EXISTING_SUBITEM = "NON_EXISTING_SUBITEM";

const QString bool_type_name = "bool";
const QString double_type_name = "double";
const QString int_type_name = "int";
const QString qstring_type_name = "QString";
}

void SessionWriter::writeTo(QXmlStreamWriter *writer, SessionItem *parent)
{
    writer->writeStartElement(parent->model()->getModelTag());
    writer->writeAttribute(SessionXML::ModelNameAttribute, parent->model()->getModelName());

    writeItemAndChildItems(writer, parent);

    writer->writeEndElement(); // m_model_tag
}

void SessionWriter::writeItemAndChildItems(QXmlStreamWriter *writer, const SessionItem *item)
{
    Q_ASSERT(item);
    if (item->parent()) {
        writer->writeStartElement(SessionXML::ItemTag);
        writer->writeAttribute(SessionXML::ModelTypeAttribute, item->modelType());
        QString tag = item->parent()->tagFromItem(item);
        if (tag == item->parent()->defaultTag())
            tag = "";
        writer->writeAttribute(SessionXML::TagAttribute, tag);
        writer->writeAttribute(SessionXML::DisplayNameAttribute, item->data(SessionFlags::DisplayNameRole).toString());
        QVector<int> roles = item->getRoles();
        foreach(int role, roles) {
            if (role == Qt::DisplayRole || role == Qt::EditRole)
                writeVariant(writer, item->value(), role);
        }

    }
    foreach (SessionItem *child_item, item->children()) {
        writeItemAndChildItems(writer, child_item);
    }
    if (item->parent()) {
        writer->writeEndElement(); // ItemTag
    }
}

void SessionWriter::writeVariant(QXmlStreamWriter *writer, QVariant variant, int role)
{
    if (variant.isValid()) {
        writer->writeStartElement(SessionXML::ParameterTag);
        QString type_name = variant.typeName();
        writer->writeAttribute(SessionXML::ParameterTypeAttribute, type_name);
        writer->writeAttribute(SessionXML::ParameterRoleAttribute, QString::number(role));

        if (type_name == double_type_name) {
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                   QString::number(variant.toDouble(), 'e', 12));
        }

        else if (type_name == int_type_name) {
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                   QString::number(variant.toInt()));
        }

        else if (type_name == bool_type_name) {
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                   QString::number(variant.toBool()));
        }

        else if (type_name == qstring_type_name) {
            writer->writeAttribute(SessionXML::ParameterValueAttribute, variant.toString());
        }

        else if (type_name == Constants::ExternalPropertyType) {
            ExternalProperty prop = variant.value<ExternalProperty>();
            writer->writeAttribute(SessionXML::ExternalPropertyTextAtt, prop.text());

            QString tcol = prop.color().isValid() ? prop.color().name(QColor::HexArgb) : "";
            writer->writeAttribute(SessionXML::ExternalPropertyColorAtt, tcol);
            writer->writeAttribute(SessionXML::ExternalPropertyIdentifierAtt, prop.identifier());
        }

        else if (type_name == Constants::ComboPropertyType) {
            int currentIndex = variant.value<ComboProperty>().currentIndex();
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                   QString::number(currentIndex));
            writer->writeAttribute(SessionXML::ParameterExtAttribute,
                                   variant.value<ComboProperty>().stringOfValues());

        }

        else if (type_name == Constants::GroupPropertyType) {
            QString ff_name = variant.value<GroupProperty_t>()->currentType();
            writer->writeAttribute(SessionXML::ParameterValueAttribute, ff_name);
        }

        else if (type_name == Constants::ColorPropertyType) {
            int r, g, b, a;
            QColor material_color = variant.value<ColorProperty>().getColor();
            material_color.getRgb(&r, &g, &b, &a);
            writer->writeAttribute(SessionXML::ColorRedAttribute, QString::number(r));
            writer->writeAttribute(SessionXML::ColorGreenAttribute, QString::number(g));
            writer->writeAttribute(SessionXML::ColorBlueAttribute, QString::number(b));
            writer->writeAttribute(SessionXML::ColorAlphaAttribute, QString::number(a));

        } else {
            throw GUIHelpers::Error("SessionModel::writeProperty: Parameter type not supported " + type_name);
        }

        writer->writeEndElement(); // end ParameterTag
    }
}

void SessionReader::readItems(QXmlStreamReader *reader, SessionItem *item, const QString &topTag,
                              WarningMessageService *messageService)
{
    bool isTopItem = true;
    const QString start_type = item->model()->getModelTag();
    while (!reader->atEnd()) {
        reader->readNext();
        if (reader->isStartElement()) {
            if (reader->name() == SessionXML::ItemTag) {
                const QString model_type
                    = reader->attributes().value(SessionXML::ModelTypeAttribute).toString();
                QString tag = reader->attributes().value(SessionXML::TagAttribute).toString();
                if (isTopItem) {
                    tag = topTag;
                }
                if (tag == SessionItem::P_NAME)
                    item->setItemName("");
                if (model_type == Constants::PropertyType || model_type == Constants::GroupItemType) {
                    SessionItem *newItem = item->getItem(tag);
                    if (!newItem) {
                        QString message = QString("Unrecoverable read error for model '%1', "
                            "Can't get item for tag '%2'").arg(item->model()->getModelTag()).arg(tag);
                        throw GUIHelpers::Error(message);
                    }
                    item = newItem;

                } else if (item->modelType() == Constants::GroupItemType) {
                    // get item corresponding to model_type and create if it doesn't exist
                    SessionItem *newItem = item->parent()->item<GroupItem>(
                                               item->parent()->tagFromItem(item))
                                           .groupProperty()->getItemOfType(model_type);
                    if (!newItem) {
                        QString message = QString("Unrecoverable read error for model '%1', "
                            "Can't get group item").arg(item->model()->getModelTag());
                        throw GUIHelpers::Error(message);
                    }
                    item = newItem;

                } else {
                    if (tag == "")
                        tag = item->defaultTag();

                    SessionItem *newItem(0);
                    SessionTagInfo info = item->getTagInfo(tag);
                    if (info.min == 1 && info.max == 1 && info.childCount == 1) {
                        newItem = item->getItem(tag);
                    } else {
                        newItem = ItemFactory::createItem(model_type);
                        if (!item->insertItem(-1, newItem, tag)) {
                            QString message = QString("Attempt to create item '%1' for tag '%2' failed")
                                              .arg(model_type).arg(tag);
                            report_error(messageService, item, ITEM_IS_NOT_INITIALIZED, message);
                            return;
                        }

                    }

                    if (!newItem) {
                        QString message = QString("Unrecoverable read error for model '%1', "
                            "Can't add item for tag").arg(item->model()->getModelTag()).arg(tag);
                        throw GUIHelpers::Error(message);
                    }

                    if (reader->attributes().hasAttribute(SessionXML::DisplayNameAttribute)) {
                        newItem->setDisplayName(reader->attributes().value(SessionXML::DisplayNameAttribute).toString());
                    }
                    item = newItem;
                }
                if (!item) {
//                    tag = -1;
                }

//                tag = -1; // all but the first item should be appended
                isTopItem = false;

            } else if (reader->name() == SessionXML::ParameterTag) {
                readProperty(reader, item, messageService);
            }
        } else if (reader->isEndElement()) {
            if (reader->name() == SessionXML::ItemTag) {
                if(item) {
                    item = item->parent();
                } else {
                    // handling the case when reading obsolete project file, when SubItem doesn't exist anymore
                    Q_ASSERT(0);
                }
            }
            if (reader->name() == start_type) {
                break;
            }
            if (reader->name() == SessionXML::ParameterTag) {
            }
        }
    }
}

QString SessionReader::readProperty(QXmlStreamReader *reader,
        SessionItem *item, WarningMessageService *messageService)
{
    const QString parameter_name
        = reader->attributes().value(SessionXML::ParameterNameAttribute).toString();
    const QString parameter_type
        = reader->attributes().value(SessionXML::ParameterTypeAttribute).toString();
    const int role
            = reader->attributes().value(SessionXML::ParameterRoleAttribute).toInt();

    if(!item) {
        QString message = QString("Attempt to set property '%1' for non existing item")
                          .arg(parameter_name);
        report_error(messageService, item, ITEM_IS_NOT_INITIALIZED, message);
        return parameter_name;
    }

    QVariant variant;
    if (parameter_type == double_type_name) {
        double parameter_value
            = reader->attributes().value(SessionXML::ParameterValueAttribute).toDouble();
        variant = parameter_value;
    }

    else if (parameter_type == int_type_name) {
        int parameter_value
            = reader->attributes().value(SessionXML::ParameterValueAttribute).toInt();
        variant = parameter_value;
    }

    else if (parameter_type == bool_type_name) {
        bool parameter_value
            = reader->attributes().value(SessionXML::ParameterValueAttribute).toInt();
        variant = parameter_value;
    }

    else if (parameter_type == qstring_type_name) {
        QString parameter_value
            = reader->attributes().value(SessionXML::ParameterValueAttribute).toString();
        variant = parameter_value;
    }

    else if (parameter_type == Constants::ExternalPropertyType) {
        QString text = reader->attributes().value(SessionXML::ExternalPropertyTextAtt).toString();
        QString colorName = reader->attributes().value(SessionXML::ExternalPropertyColorAtt).toString();
        QString identifier = reader->attributes().value(SessionXML::ExternalPropertyIdentifierAtt).toString();

        ExternalProperty property;
        property.setText(text);
        property.setColor(QColor(colorName));
        property.setIdentifier(identifier);
        variant = property.variant();
    }

    else if (parameter_type == Constants::ComboPropertyType) {
        int parameter_value
            = reader->attributes().value(SessionXML::ParameterValueAttribute).toInt();
        QString parameterExt
            = reader->attributes().value(SessionXML::ParameterExtAttribute).toString();

        ComboProperty combo_property;
        combo_property.setStringOfValues(parameterExt);
        combo_property.setCurrentIndex(parameter_value);

        variant = combo_property.getVariant();
    }

    else if (parameter_type == Constants::GroupPropertyType) {
        QString parameter_value
            = reader->attributes().value(SessionXML::ParameterValueAttribute).toString();

        QVariant v = item->value();
        if(!v.canConvert<GroupProperty_t>()) {
            report_error(messageService, item, SET_ITEM_PROPERTY_ERROR,
                         QStringLiteral("GroupProperty conversion failed"));
        } else {
            GroupProperty_t group_property = v.value<GroupProperty_t>();
            group_property->setCurrentTypeName(parameter_value);
            variant = QVariant::fromValue<GroupProperty_t>(group_property);
        }
    }

    else if (parameter_type == Constants::ColorPropertyType) {
        int r = reader->attributes().value(SessionXML::ColorRedAttribute).toInt();
        int g = reader->attributes().value(SessionXML::ColorGreenAttribute).toInt();
        int b = reader->attributes().value(SessionXML::ColorBlueAttribute).toInt();
        int a = reader->attributes().value(SessionXML::ColorAlphaAttribute).toInt();
        ColorProperty color(QColor(r, g, b, a));
        variant = color.getVariant();
    }

    else {
        throw GUIHelpers::Error("SessionModel::readProperty: "
                                "Parameter type not supported" + parameter_type);
    }

    if (variant.isValid()) {
        item->setData(role, variant);
    }

    return parameter_name;
}

void SessionReader::report_error(WarningMessageService *messageService,
                                 SessionItem *item, const QString &error_type,
                                 const QString &message)
{
    if(messageService) {
        messageService->send_message(item->model(), error_type, message);
    } else {
        throw GUIHelpers::Error(error_type + QString(" ") + message);
    }
}
