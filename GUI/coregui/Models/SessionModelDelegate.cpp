// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionModelDelegate.cpp
//! @brief     Implements class SessionModelDelegate
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SessionModelDelegate.h"
#include "PropertyBrowserUtils.h"
#include "SessionItem.h"
#include <QApplication>

namespace {

bool isComboProperty(const QModelIndex& index)
{
    return index.data().canConvert<ComboProperty>();
}

bool isGroupProperty(const QModelIndex& index)
{
    return index.data().canConvert<GroupProperty_t>();
}

bool isMaterialProperty(const QModelIndex& index)
{
    return index.data().canConvert<MaterialProperty>();
}

bool isColorProperty(const QModelIndex& index)
{
    return index.data().canConvert<ColorProperty>();
}

bool isScientificDoubleProperty(const QModelIndex& index)
{
    return index.data().canConvert<ScientificDoubleProperty>();
}

}

bool isDoubleProperty(const QModelIndex& index)
{
    return index.data().type() == QVariant::Double;
}

SessionModelDelegate::SessionModelDelegate(QWidget* parent)
    : QStyledItemDelegate(parent)
{

}

void SessionModelDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,
                                 const QModelIndex& index) const
{
    QVariant prop_value = index.model()->data(index, Qt::EditRole);

    if (isComboProperty(index)) {
        ComboProperty property = prop_value.value<ComboProperty>();
        paintCustomLabel(painter, option, index, property.getValue());

    } else if (isGroupProperty(index)) {
        GroupProperty_t property = prop_value.value<GroupProperty_t>();
        paintCustomLabel(painter, option, index, property->currentType());

    } else if (isMaterialProperty(index)) {
        MaterialProperty property = prop_value.value<MaterialProperty>();
        paintCustomLabel(painter, option, index, property.getName());

    } else if (isColorProperty(index)) {
        ColorProperty property = prop_value.value<ColorProperty>();
        paintCustomLabel(painter, option, index, property.getText());

    } else if (isScientificDoubleProperty(index)) {
        ScientificDoubleProperty property = prop_value.value<ScientificDoubleProperty>();
        paintCustomLabel(painter, option, index, property.getText());

    } else if (isDoubleProperty(index)) {
        paintCustomDouble(painter, option, index);

    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QWidget* SessionModelDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                                            const QModelIndex& index) const
{
    if (isComboProperty(index)) {
        ComboPropertyEdit* editor = new ComboPropertyEdit(parent);
        ComboProperty combo = index.data().value<ComboProperty>();
        editor->setComboProperty(combo);
        connect(editor, &ComboPropertyEdit::comboPropertyChanged,
                this, &SessionModelDelegate::onComboPropertyChanged);
        return editor;

    } else if (isGroupProperty(index)) {
        GroupPropertyEdit* editor = new GroupPropertyEdit(parent);
        editor->setGroupProperty(index.data().value<GroupProperty_t>());
        connect(editor, &GroupPropertyEdit::groupPropertyChanged,
                this, &SessionModelDelegate::onGroupPropertyChanged);
        return editor;

    } else if (isMaterialProperty(index)) {
        MaterialPropertyEdit* editor = new MaterialPropertyEdit(parent);
        editor->setMaterialProperty(index.data().value<MaterialProperty>());
        connect(editor, &MaterialPropertyEdit::materialPropertyChanged,
                this, &SessionModelDelegate::onMaterialPropertyChanged);
        return editor;

    } else if (isColorProperty(index)) {
        ColorPropertyEdit* editor = new ColorPropertyEdit(parent);
        editor->setColorProperty(index.data().value<ColorProperty>());
        connect(editor, &ColorPropertyEdit::colorPropertyChanged,
                this, &SessionModelDelegate::onColorPropertyChanged);
        return editor;

    } else if (isScientificDoubleProperty(index)) {
        ScientificDoublePropertyEdit* editor = new ScientificDoublePropertyEdit(parent);
        editor->setScientificDoubleProperty(index.data().value<ScientificDoubleProperty>());
        connect(editor, &ScientificDoublePropertyEdit::scientificDoublePropertyChanged,
                this, &SessionModelDelegate::onScientificDoublePropertyChanged);
        return editor;

    } else {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}

void SessionModelDelegate::setModelData(QWidget* editor, QAbstractItemModel* model,
                                        const QModelIndex& index) const
{
    if (isComboProperty(index)) {
        ComboPropertyEdit* comboEditor = qobject_cast<ComboPropertyEdit*>(editor);
        model->setData(index, comboEditor->getComboProperty().getVariant());

    } else if (isGroupProperty(index)) {
        GroupPropertyEdit* groupEditor = qobject_cast<GroupPropertyEdit*>(editor);
        model->setData(index,
                       QVariant::fromValue<GroupProperty_t>(groupEditor->getGroupProperty()));

    } else if (isMaterialProperty(index)) {
        MaterialPropertyEdit* matEditor = qobject_cast<MaterialPropertyEdit*>(editor);
        model->setData(index,
                       QVariant::fromValue<MaterialProperty>(matEditor->getMaterialProperty()));

    } else if (isColorProperty(index)) {
        ColorPropertyEdit* colorEditor = qobject_cast<ColorPropertyEdit*>(editor);
        model->setData(index,
                       QVariant::fromValue<ColorProperty>(colorEditor->getColorProperty()));

    } else if (isScientificDoubleProperty(index)) {
        ScientificDoublePropertyEdit* doubleEditor
                = qobject_cast<ScientificDoublePropertyEdit*>(editor);
        model->setData(index, QVariant::fromValue<
                ScientificDoubleProperty>(doubleEditor->getScientificDoubleProperty()));

    } else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void SessionModelDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    if (isComboProperty(index) || isGroupProperty(index) || isMaterialProperty(index)
        || isScientificDoubleProperty(index) || isColorProperty(index)) {
        // as using custom widget(s), doing nothing here
    } else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

QSize SessionModelDelegate::sizeHint(const QStyleOptionViewItem& option,
                                     const QModelIndex& index) const
{
    QSize result = QStyledItemDelegate::sizeHint(option, index);
    result.setHeight(static_cast<int>(result.height() * 1.2));
    return result;
}

//! Makes an editor occupying whole available space in a cell. If cell contains an icon
//! as a decoration (i.e. icon of material property), it will be hidden as soon as editor
//! up and running.

void SessionModelDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
                                                const QModelIndex& index) const
{
    QStyledItemDelegate::updateEditorGeometry(editor, option, index);
    editor->setGeometry(option.rect);
}

void SessionModelDelegate::onComboPropertyChanged(const ComboProperty& /*property*/)
{
    ComboPropertyEdit* editor = qobject_cast<ComboPropertyEdit*>(sender());
    Q_ASSERT(editor);
    emit commitData(editor);
    // emit closeEditor(editor); // Qt by default leaves editor alive after editing finished
}

void SessionModelDelegate::onGroupPropertyChanged(const GroupProperty_t& /*property*/)
{
    GroupPropertyEdit* editor = qobject_cast<GroupPropertyEdit*>(sender());
    Q_ASSERT(editor);
    emit commitData(editor);
}

void SessionModelDelegate::onMaterialPropertyChanged(const MaterialProperty& /*property*/)
{
    MaterialPropertyEdit* editor = qobject_cast<MaterialPropertyEdit*>(sender());
    Q_ASSERT(editor);
    emit commitData(editor);
}

void SessionModelDelegate::onColorPropertyChanged(const ColorProperty& /*property*/)
{
    ColorPropertyEdit* editor = qobject_cast<ColorPropertyEdit*>(sender());
    Q_ASSERT(editor);
    emit commitData(editor);
}

void SessionModelDelegate::onScientificDoublePropertyChanged(const ScientificDoubleProperty&)
{
    ScientificDoublePropertyEdit* editor = qobject_cast<ScientificDoublePropertyEdit*>(sender());
    Q_ASSERT(editor);
    emit commitData(editor);

}

//! Paints custom text in a a place corresponding given index.

void SessionModelDelegate::paintCustomLabel(QPainter* painter, const QStyleOptionViewItem& option,
                                            const QModelIndex& index, const QString& text) const
{
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index); // calling original method to take into accounts colors etc
    opt.text = displayText(text, option.locale); // by overriding text with ours
    const QWidget* widget = opt.widget;
    QStyle* style = widget ? widget->style() : QApplication::style();
    style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, widget);
}

void SessionModelDelegate::paintCustomDouble(QPainter* painter,
                                             const QStyleOptionViewItem& option,
                                             const QModelIndex& index) const
{
    SessionItem* item = static_cast<SessionItem*>(index.internalPointer());

    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);
    opt.text = opt.locale.toString(item->value().toDouble(), 'f', item->decimals());
    const QWidget* widget = opt.widget;
    QStyle* style = widget ? widget->style() : QApplication::style();
    style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, widget);
}
