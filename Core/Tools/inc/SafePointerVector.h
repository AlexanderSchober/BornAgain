// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/SafePointerVector.h
//! @brief     Defines and implements template class SafePointerVector.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef SAFEPOINTERVECTOR_H_
#define SAFEPOINTERVECTOR_H_

#include <vector>
using std::size_t;

//! Safe handling of vectors of pointers that are owned by the vector

template <class T> class SafePointerVector
{
 public:
    typedef typename std::vector<T *>::iterator iterator;
    typedef typename std::vector<T *>::const_iterator const_iterator;
    SafePointerVector();
    SafePointerVector(const SafePointerVector &other);
    virtual ~SafePointerVector();

    SafePointerVector &operator=(const SafePointerVector &right);
    size_t size() const;
    bool empty() const;
    void push_back(T *pointer);
    T *operator[](size_t index);
    const T *operator[](size_t index) const;
    iterator begin() { return m_pointers.begin(); }
    const_iterator begin() const { return m_pointers.begin(); }
    iterator end() { return m_pointers.end(); }
    const_iterator end() const { return m_pointers.end(); }

    std::vector<T *> getSTLVector() const { return m_pointers; }

    T *back() { return m_pointers.back(); }
    const T *back() const { return m_pointers.back(); }
    void clear();
 private:
    std::vector<T *> m_pointers;
};

template<class T> SafePointerVector<T>::SafePointerVector() : m_pointers()
{
}

template<class T> SafePointerVector<T>::SafePointerVector(const SafePointerVector<T> &other)
{
    for (const_iterator it = other.begin();
            it != other.end(); ++it) {
        m_pointers.push_back((*it)->clone());
    }
}

template<class T> SafePointerVector<T>::~SafePointerVector()
{
    clear();
}

template<class T> SafePointerVector<T> &SafePointerVector<T>::operator=(
        const SafePointerVector<T> &right)
{
    if (this == &right) return *this;
    clear();
    for (const_iterator it = right.begin();
            it != right.end(); ++it) {
        m_pointers.push_back((*it)->clone());
    }
    return *this;
}

template<class T>
inline size_t SafePointerVector<T>::size() const
{
    return m_pointers.size();
}

template<class T>
inline bool SafePointerVector<T>::empty() const
{
    return m_pointers.empty();
}

template<class T>
inline void SafePointerVector<T>::push_back(T* pointer)
{
    m_pointers.push_back(pointer);
}

template<class T>
inline T* SafePointerVector<T>::operator[](size_t index)
{
    return m_pointers[index];
}

template<class T>
inline const T* SafePointerVector<T>::operator[](size_t index) const
{
    return m_pointers[index];
}

template<class T> void SafePointerVector<T>::clear()
{
    for (iterator it = begin(); it != end(); ++it) {
        delete (*it);
    }
    m_pointers.clear();
}

#endif /* SAFEPOINTERVECTOR_H_ */
