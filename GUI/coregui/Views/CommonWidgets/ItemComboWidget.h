// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/ItemComboWidget.h
//! @brief     Defines class ItemComboWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef ITEMCOMBOWIDGET_H
#define ITEMCOMBOWIDGET_H

#include "IFactory.h"
#include "WinDllMacros.h"
#include <QMap>
#include <QString>
#include <QWidget>

class SessionItem;
class SessionItemWidget;
class ItemComboToolBar;
class QStackedWidget;

//! The ItemComboWidget class combines stack of widgets with QComboBox controller to switch between
//! widgets. It is used in the case when one SessionItem can be presented with different widgets.

//! For example, in JobOutputDataWidget the results of the job can be presented with either
//! IntensityDataWidget or FitDataWidget, depending from the JobView's activity type.

class BA_CORE_API_ ItemComboWidget : public QWidget
{
    Q_OBJECT

public:
    using factory_function_t = std::function<SessionItemWidget*()>;

    explicit ItemComboWidget(QWidget* parent = 0);

    virtual void setItem(SessionItem* item);

    void registerWidget(const QString& presentationType, factory_function_t);

    void setPresentation(const QString& presentationType);

protected:
    virtual QStringList activePresentationList(SessionItem* item);
    virtual QStringList validPresentationList(SessionItem* item);

private slots:
    void onComboChanged(const QString& name);

private:
    QString currentPresentation() const;

    ItemComboToolBar* m_toolBar;
    QStackedWidget* m_stackedWidget;
    SessionItem* m_currentItem;
    IFactory<QString, SessionItemWidget> m_widgetFactory;
    QMap<QString, SessionItemWidget*> m_presentationTypeToWidget;
};

#endif // ITEMCOMBOWIDGET_H
