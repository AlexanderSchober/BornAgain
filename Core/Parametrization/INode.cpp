// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/INode.cpp
//! @brief     Implements class INode.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "INode.h"
#include "StringUsageMap.h"
#include "Exceptions.h"
#include "NodeUtils.h"
#include <algorithm>

std::string INode::to_str() const
{
    return NodeUtils::nodeToString(*this);
}

void INode::registerChild(INode *sample)
{
    if(!sample)
        throw Exceptions::NullPointerException(
            "ISample::registerChild -> Error. Null pointer.");
    m_samples.push_back(sample);
}

//! remove registered child from the container

void INode::deregisterChild(INode* sample)
{
    auto it = std::find(m_samples.begin(), m_samples.end(), sample);
    if (it != m_samples.end())
        m_samples.erase(it);
}

std::vector<const INode *> INode::getChildren() const
{
    return {};
//    std::vector<const INode*> result;
//    for (size_t i=0; i<m_samples.size(); ++i)
//        result.push_back(m_samples[i]);
//    return result;
}

std::string INode::addParametersToExternalPool(
    const std::string& path, ParameterPool* external_pool, int copy_number) const
{
    std::string new_path
        = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // We need a mechanism to handle cases with multiple children with the same name.
    // First run through all direct children and save their names
    StringUsageMap strUsageMap;
    for (size_t i = 0; i < m_samples.size(); ++i)
        strUsageMap.add(new_path + m_samples[i]->getName()); // saving child names

    // Now run through the direct children again and assign a copy number for
    // all children with the same name
    StringUsageMap strUsageMap2;
    for (size_t i = 0; i < m_samples.size(); ++i) {
        std::string child_name = new_path + m_samples[i]->getName();
        strUsageMap2.add(child_name);
        // Copy number starts from 0:
        int ncopy = strUsageMap2[child_name] - 1;

        // If the child is the only one with that name, we do not want any copy number:
        if (strUsageMap[child_name] == 1)
            ncopy = -1;

        m_samples[i]->addParametersToExternalPool(new_path, external_pool, ncopy);
    }
    return new_path;
}
