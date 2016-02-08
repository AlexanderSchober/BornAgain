// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/NJobModel.h
//! @brief     Defines class NJobModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#ifndef FITMODEL_H
#define FITMODEL_H

#include "SessionModel.h"
#include <QVector>

class QModelIndex;


class BA_CORE_API_ FitModel : public SessionModel
{
    Q_OBJECT

public:
    explicit FitModel(QObject *parent = 0);

public slots:
    void dataChangedProxy(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                          const QVector<int> &roles = QVector<int> ());
};

#endif
