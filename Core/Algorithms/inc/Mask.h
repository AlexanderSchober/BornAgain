// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/Mask.h
//! @brief     Defines classes Mask, MaskIndexModulus, MaskCoordinates. 
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef MASK_H_
#define MASK_H_

#include "MaskCoordinateFunction.h"

//! Base class for masking OutputData elements

class Mask : public ICloneable
{
 public:
    template <class TValue, class TContainer> friend class OutputDataIterator;
    template <class TValue> friend class OutputData;
    explicit Mask(Mask *p_submask=0)
        : m_own_index(0), m_max_index(0), mp_submask(p_submask) {}
    virtual ~Mask() { delete mp_submask; }
    virtual Mask *clone() const;

    size_t getFirstValidIndex();
    size_t getNextIndex(size_t total_index);
    void setMaxIndex(size_t max_index);

    size_t getOwnIndex() const { return m_own_index; }
    size_t getMaxIndex() const { return m_max_index; }

 protected:
    virtual bool isMasked(size_t total_index) const;
    size_t m_own_index;
    size_t m_max_index;
    Mask *mp_submask;
 private:
    size_t nextSubIndex(size_t total_index);
};

//! Mask based on the index modulo a given number

class MaskIndexModulus : public Mask
{
 public:
    MaskIndexModulus(size_t modulus, size_t remainder, Mask *p_submask=0)
        : Mask(p_submask), m_modulus(modulus), m_remainder(remainder) {}
    virtual ~MaskIndexModulus() {}
    virtual MaskIndexModulus *clone() const;

 protected:
    virtual bool isMasked(size_t total_index) const;

 private:
    size_t m_modulus;
    size_t m_remainder;
};

//! Mask based on the coordinates

class MaskCoordinates : public Mask
{
 public:
    MaskCoordinates(size_t rank, const int *dims, Mask *p_submask=0);
    virtual ~MaskCoordinates();
    virtual MaskCoordinates *clone() const;

    void setMaskCoordinateFunction(MaskCoordinateFunction *p_mask_function);

 protected:
    virtual bool isMasked(size_t total_index) const;

 private:
    void setCachedCoordinates(size_t index) const;
    size_t m_rank;
    int *m_dims;
    mutable int *m_coordinates;
    MaskCoordinateFunction *mp_mask_function;
};

#endif /* MASK_H_ */
