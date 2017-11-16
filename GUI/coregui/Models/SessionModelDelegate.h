// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionModelDelegate.h
//! @brief     Defines class SessionModelDelegate
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SESSIONMODELDELEGATE_H
#define SESSIONMODELDELEGATE_H

#include "WinDllMacros.h"
#include "GroupProperty.h"
#include <QStyledItemDelegate>

class ComboProperty;
class MaterialProperty;
class ColorProperty;
class ScientificDoubleProperty;

//! The SessionModelDelegate class presents the content of SessionModel items in
//! standard QTreeView. Extents base QItemDelegate with possibility to show/edit
//! our custom QVariant's.

class BA_CORE_API_ SessionModelDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    SessionModelDelegate(QWidget* parent);

    void paint(QPainter* painter, const QStyleOptionViewItem& option,
               const QModelIndex& index) const;

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                          const QModelIndex& index) const;

    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;

    void setEditorData(QWidget* editor, const QModelIndex& index) const;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
                              const QModelIndex& index) const;

private slots:
    void onComboPropertyChanged(const ComboProperty&);
    void onGroupPropertyChanged(const GroupProperty_t&);
    void onMaterialPropertyChanged(const MaterialProperty&);
    void onColorPropertyChanged(const ColorProperty&);
    void onScientificDoublePropertyChanged(const ScientificDoubleProperty&);

private:
    void paintCustomLabel(QPainter* painter, const QStyleOptionViewItem& option,
                          const QModelIndex& index, const QString& text) const;

    void paintCustomDouble(QPainter* painter, const QStyleOptionViewItem& option,
                          const QModelIndex& index) const;

};

#endif // SESSIONMODELDELEGATE_H
