// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FitProxyModel.h
//! @brief     Defines class FitProxyModel
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITPROXYMODEL_H
#define FITPROXYMODEL_H


#include <QAbstractItemModel>

class FitModel;
class ParameterizedItem;

class BA_CORE_API_ FitProxyModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit FitProxyModel(QObject *parent = 0);
    ~FitProxyModel(){}

    // overriden methods
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parentIndex) const;
    int columnCount(const QModelIndex &parentIndex) const;
    QModelIndex index(int row, int column, const QModelIndex &parentIndex) const;
    QModelIndex parent(const QModelIndex &child) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    //end if overriden methods

    void setFitModel(FitModel *fitModel);
    FitModel *getFitModel()
        { return m_fitModel; }

    ParameterizedItem *itemForIndex(const QModelIndex &index) const;


private:
    FitModel *m_fitModel;

};




#endif
