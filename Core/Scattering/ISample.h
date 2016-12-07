// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/ISample.h
//! @brief     Defines interface class ISample.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISAMPLE_H
#define ISAMPLE_H

#include "ICloneable.h"
#include "INode.h"
#include "ISampleVisitor.h"
#include <vector>

class IMaterial;

//! Pure virtual base class for sample components and properties related to scattering.
//! @ingroup samples_internal

class BA_CORE_API_ ISample : public ICloneable, public INode
{
public:
    //! Returns a clone of this ISample object.
    ISample* clone() const override=0;

    //! Returns a clone with inverted magnetic fields.
    virtual ISample* cloneInvertB() const;

    //! Calls the ISampleVisitor's visit method.
    virtual void accept(ISampleVisitor* p_visitor) const=0;

    //! Returns textual representation of this and its descendants.
    virtual std::string to_str(int indent=0) const;

    //! Returns nullptr, unless overwritten to return a specific material.
    virtual const IMaterial* getMaterial() const { return nullptr; }

    //! Returns nullptr, unless overwritten to return a specific material.
    virtual const IMaterial* getAmbientMaterial() const { return nullptr; }

    //! Returns set of unique materials contained in this ISample.
    std::vector<const IMaterial*> containedMaterials() const;

    template<class T> std::vector<const T*> containedSubclass() const;

    //! Registers child in the container.
    void registerChild(ISample* sample);

    //! Removes registered child from the container
    void deregisterChild(ISample* sample);

    //! Returns a vector of children (const).
    virtual std::vector<const ISample*> getChildren() const;

    //! Adds parameters from local pool to external pool and recursively calls its direct children.
    virtual std::string addParametersToExternalPool(
        const std::string& path, ParameterPool* external_pool, int copy_number = -1) const;

private:
    //! List of registered children.
    std::vector<ISample*> m_samples;

};

//! Returns vector of children of type T.
template<class T>
std::vector<const T*> ISample::containedSubclass() const
{
    std::vector<const T*> result;
    if( const T* t = dynamic_cast<const T*>(this) )
        result.push_back( t );
    for( const ISample* child: getChildren() )
        for( const T* t: child->containedSubclass<T>() )
            result.push_back( t );
    return result;
}

#endif // ISAMPLE_H
