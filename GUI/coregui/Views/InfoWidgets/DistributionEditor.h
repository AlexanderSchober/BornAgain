// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/DistributionEditor.h
//! @brief     Defines class DistributionEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DISTRIBUTIONEDITOR_H
#define DISTRIBUTIONEDITOR_H

#include <QWidget>

class QGroupBox;
class DistributionWidget;
class ParameterizedItem;
class AwesomePropertyEditor;

//! The DistributionEditor class, being a child of DistributionDialog, contains a widget
//! to show Distribution1D and awesome property editor to change distribution parameters
class DistributionEditor : public QWidget
{
    Q_OBJECT
public:
    DistributionEditor(QWidget *parent = 0);
    virtual ~DistributionEditor() {}
    void setItem(ParameterizedItem *item);
    void plotItem(ParameterizedItem *item);
    void setNameOfEditor(QString name);

private slots:
    void onSubItemChanged(const QString &property_name);

private:
    AwesomePropertyEditor *m_propertyEditor;
    ParameterizedItem *m_item;
    DistributionWidget *m_plotwidget;
    QString m_nameOfEditor;
    QGroupBox *m_box;
};

#endif
