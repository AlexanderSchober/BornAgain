// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/TestItem.cpp
//! @brief     Implements class TestItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ModelMapper.h"
#include "SessionModel.h"
#include "SessionItem.h"

#include <QModelIndex>

ModelMapper::ModelMapper(QObject *parent)
    : QObject(parent)
    , m_active {true}
    , m_model(0)
    , m_item(0)
{
}

void ModelMapper::setItem(SessionItem *item)
{
    if (item) {
        m_item = item;
        setModel(item->model());
    }
}

void ModelMapper::setOnValueChange(std::function<void ()> f)
{
    m_onValueChange.push_back(f);
}

void ModelMapper::setOnPropertyChange(std::function<void (QString)> f)
{
    m_onPropertyChange.push_back(f);
}

void ModelMapper::setOnChildPropertyChange(std::function<void (SessionItem *, QString)> f)
{
    m_onChildPropertyChange.push_back(f);
}

void ModelMapper::setOnParentChange(std::function<void (SessionItem *)> f)
{
    m_onParentChange.push_back(f);
}

void ModelMapper::setOnChildrenChange(std::function<void ()> f)
{
    m_onChildrenChange.push_back(f);
}

void ModelMapper::setOnSiblingsChange(std::function<void ()> f)
{
    m_onSiblingsChange.push_back(f);
}

void ModelMapper::setOnAnyChildChange(std::function<void (SessionItem *)> f)
{
    m_onAnyChildChange.push_back(f);
}

void ModelMapper::setModel(SessionModel *model)
{
    if (m_model) {
        disconnect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
                   this, SLOT(onDataChanged(QModelIndex,QModelIndex,QVector<int>)));
        disconnect(m_model, SIGNAL(rowsInserted(QModelIndex,int,int)),
                   this, SLOT(onRowsInserted(QModelIndex,int,int)));
        disconnect(m_model, SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)),
                this, SLOT(onBeginRemoveRows(QModelIndex,int,int)));
        disconnect(m_model, SIGNAL(rowsRemoved(QModelIndex,int,int)),
                this, SLOT(onRowRemoved(QModelIndex,int,int)));
    }
    if (model) {
        m_model = model;
        connect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
                   this, SLOT(onDataChanged(QModelIndex,QModelIndex,QVector<int>)));
        connect(m_model, SIGNAL(rowsInserted(QModelIndex,int,int)),
                   this, SLOT(onRowsInserted(QModelIndex,int,int)));
        connect(m_model, SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)),
                this, SLOT(onBeginRemoveRows(QModelIndex,int,int)));
        connect(m_model, SIGNAL(rowsRemoved(QModelIndex,int,int)),
                this, SLOT(onRowRemoved(QModelIndex,int,int)));
    }
}

int ModelMapper::nestlingDepth(SessionItem *item, int level)
{
    if (item == nullptr || item == m_model->rootItem())
        return -1;
    if (item == m_item)
        return level;
    return nestlingDepth(item->parent(), level + 1);

}

void ModelMapper::callOnValueChange()
{
    if (m_active && m_onValueChange.size() > 0) {
        for (auto f : m_onValueChange) {
            f();
        }
    }
}

void ModelMapper::callOnPropertyChange(const QString &name)
{
    if (m_active && m_onPropertyChange.size() > 0) {
        for (auto f : m_onPropertyChange) {
            f(name);
        }
    }
}

void ModelMapper::callOnChildPropertyChange(SessionItem *item, const QString &name)
{
    if (m_active && m_onChildPropertyChange.size() > 0) {
        for (auto f : m_onChildPropertyChange) {
            f(item, name);
        }
    }
}

void ModelMapper::callOnParentChange(SessionItem *new_parent)
{
    if (m_active && m_onParentChange.size() > 0) {
        for (auto f : m_onParentChange) {
            f(new_parent);
        }
    }
}

void ModelMapper::callOnChildrenChange()
{
    if (m_active && m_onChildrenChange.size() > 0) {
        for (auto f : m_onChildrenChange) {
            f();
        }
    }
}

void ModelMapper::callOnSiblingsChange()
{
    if (m_active && m_onSiblingsChange.size() > 0) {
        for (auto f : m_onSiblingsChange) {
            f();
        }
    }
}

void ModelMapper::callOnAnyChildChange(SessionItem *item)
{
    if (m_active && m_onAnyChildChange.size() > 0) {
        for (auto f : m_onAnyChildChange) {
            f(item);
        }
    }
}

void ModelMapper::onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                                const QVector<int> &/*roles*/)
{
    if (topLeft.parent() != bottomRight.parent())
        return; // range must be from the same parent

    SessionItem *item = m_model->itemForIndex(topLeft);

    int nestling = nestlingDepth(item);
    if (nestling == 0) {
        callOnValueChange();
    }
    if (nestling == 1) {
        // something happened with our children
        if (SessionItem *item = m_model->itemForIndex(topLeft)) {
            // only care f
            const QString tag = m_item->tagFromItem(item);
            if (!tag.isEmpty()) {
                callOnPropertyChange(tag);
            }
        }
    }
    if (nestling > 1) {
        if (SessionItem *parent = item->parent()) {
            const QString tag = parent->tagFromItem(item);
            if (!tag.isEmpty()) {
                callOnChildPropertyChange(parent, tag);
            }
        }
    }
    if (nestling > 0) {
        callOnAnyChildChange(item);
    }
}

void ModelMapper::onRowsInserted(const QModelIndex &parent, int first, int /*last*/)
{
    SessionItem *newChild = m_model->itemForIndex(parent.child(first, 0));

    int nestling = nestlingDepth(newChild);

    if (newChild) {
        if (m_item == newChild) {
            callOnParentChange(m_model->itemForIndex(parent));
        }
    }
    if (nestling == 1) {

        callOnChildrenChange();

        // inform siblings about the change
        // FIXME SessionItems with invalid parent index (i.e. IView's located on top of graphics scene like ParticleView) should be also notified to update the label
        if(SessionItem *parent = newChild->parent()) {
//            QVector<SessionItem *> items = parent->getItems(parent->tagFromItem(newChild));
            QVector<SessionItem *> items = parent->getChildrenOfType(newChild->modelType());
            foreach(SessionItem *sibling, items) {
                if(m_item == sibling) callOnSiblingsChange();
            }
        }
    }

    if (nestling > 0) {
        callOnAnyChildChange(newChild);
    }

}

void ModelMapper::onBeginRemoveRows(const QModelIndex &parent, int first, int /*last*/)
{
    SessionItem *oldChild = m_model->itemForIndex(parent.child(first, 0));

    int nestling = nestlingDepth(m_model->itemForIndex(parent));

    if (oldChild) {
        if (m_item == oldChild) {
            callOnParentChange(m_model->itemForIndex(parent));
        }
        if (nestling == 0) {

            callOnChildrenChange();

            // inform siblings about the change
            if(SessionItem *parent = oldChild->parent()) {
    //            QVector<SessionItem *> items = parent->getItems(parent->tagFromItem(newChild));
                QVector<SessionItem *> items = parent->getChildrenOfType(oldChild->modelType());
                foreach(SessionItem *sibling, items) {
                    if(m_item == sibling) callOnSiblingsChange();
                }
            }
        }
    }

}

void ModelMapper::onRowRemoved(const QModelIndex &parent, int /*first*/, int /*last*/)
{
    int nestling = nestlingDepth(m_model->itemForIndex(parent));

    if (nestling >= 0 || m_model->itemForIndex(parent) == m_item->parent()) {
        callOnAnyChildChange(nullptr);
    }
}
