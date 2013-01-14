#ifndef FASTVECTOR_H
#define FASTVECTOR_H


#include "Types.h"
#include <iostream>

/* ************************************************************************* */
// container for holding kvectors with optimised location/deallocation
/* ************************************************************************* */
class KVectorContainer {
public:
    typedef std::vector<kvector_t > container_t;
    typedef container_t::const_iterator const_iterator;
    KVectorContainer(int buff_size = 3) : m_current_position(0), m_max_buff_size(buff_size), m_buffer()
    {
        m_buffer.reserve(m_max_buff_size);
        for(size_t i=0; i<m_max_buff_size; ++i) m_buffer.push_back(kvector_t(0.0, 0.0, 0.0));
    }

    inline void push_back(const kvector_t &k) {
        if(m_current_position == m_max_buff_size) {
            std::cout << "KVectorContainer::push_back() -> Info. Increasing size of the buffer from " << m_max_buff_size;
            m_max_buff_size *=2;
            std::cout << " to " << m_max_buff_size << std::endl;
            m_buffer.resize(m_max_buff_size);
        }
        m_buffer[m_current_position][0] = k[0];
        m_buffer[m_current_position][1] = k[1];
        m_buffer[m_current_position][2] = k[2];
        m_current_position++;
    }

    inline void clear() { m_current_position = 0; }

    inline size_t size() { return m_current_position; }

    void print() {
        for(size_t i=0; i<m_max_buff_size; ++i) std::cout << i << " " << m_buffer[i] << std::endl;
        std::cout << "size:" << size() << std::endl;
    }

    const_iterator begin() const { return m_buffer.begin(); }
    const_iterator end() const { return m_buffer.begin()+m_current_position; }


private:
    size_t m_current_position;
    size_t m_max_buff_size;
    container_t m_buffer;
};


#endif // FASTVECTOR_H
