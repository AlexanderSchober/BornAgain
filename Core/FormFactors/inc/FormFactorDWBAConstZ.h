// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      FormFactors/FormFactorDWBAConstZ.h 
//! @brief     Defines class FormFactorDWBAConstZ.
//
// ************************************************************************** //

#ifndef FORMFACTORDWBACONSTZ_H_
#define FORMFACTORDWBACONSTZ_H_

#include "FormFactorDWBA.h"

//! ?

class FormFactorDWBAConstZ: public FormFactorDWBA
{
public:
	FormFactorDWBAConstZ(IFormFactor* p_form_factor, double depth=0.0);
    virtual ~FormFactorDWBAConstZ();
    virtual FormFactorDWBAConstZ *clone() const;

    virtual complex_t evaluate(const cvector_t &k_i, const Bin1DCVector &k_f_bin,
    		double alpha_i, double alpha_f) const;
protected:
    double m_depth;

private:
    inline complex_t getDepthPhase(const complex_t &q_z) const
    {
        complex_t exponent = -complex_t(0.0,1.0)*q_z*m_depth; // Minus sign for depth (m_depth > 0)
        return std::exp(exponent);
    }

};

#endif /* FORMFACTORDWBACONSTZ_H_ */
