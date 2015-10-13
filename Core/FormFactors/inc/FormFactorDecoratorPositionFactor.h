// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorDecoratorPositionFactor.h
//! @brief     Defines class FormFactorDecoratorPositionFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDECORATORPOSITIONFACTOR_H_
#define FORMFACTORDECORATORPOSITIONFACTOR_H_

#include "Types.h"
#include "IFormFactorDecorator.h"

//! @class FormFactorDecoratorPositionFactor
//! @ingroup formfactors_internal
//! @brief Decorates a formfactor with a position dependent phase factor.

class BA_CORE_API_ FormFactorDecoratorPositionFactor : public IFormFactorDecorator
{
public:
    FormFactorDecoratorPositionFactor(const IFormFactor &form_factor, kvector_t position);
    virtual ~FormFactorDecoratorPositionFactor()
    {
    }
    virtual FormFactorDecoratorPositionFactor *clone() const;
    virtual void accept(ISampleVisitor *visitor) const
    {
        visitor->visit(this);
    }

    virtual complex_t evaluate(const WavevectorInfo& wavevectors) const;

#ifndef GCCXML_SKIP_THIS
    virtual Eigen::Matrix2cd evaluatePol(const cvector_t &k_i, const Bin1DCVector &k_f_bin) const;
#endif

    virtual int getNumberOfStochasticParameters() const
    {
        return mp_form_factor->getNumberOfStochasticParameters();
    }

protected:
    kvector_t m_position;

private:
    complex_t getPositionFactor(const cvector_t &q) const;
};

inline FormFactorDecoratorPositionFactor::FormFactorDecoratorPositionFactor(
    const IFormFactor &form_factor, kvector_t position)
    : IFormFactorDecorator(form_factor), m_position(position)
{
    setName("FormFactorDecoratorPositionFactor");
}

inline FormFactorDecoratorPositionFactor *FormFactorDecoratorPositionFactor::clone() const
{
    return new FormFactorDecoratorPositionFactor(*mp_form_factor, m_position);
}

inline complex_t FormFactorDecoratorPositionFactor::evaluate(const WavevectorInfo& wavevectors) const
{
    cvector_t q = wavevectors.getMiddleQ();
    complex_t pos_factor = getPositionFactor(q);
    return pos_factor * mp_form_factor->evaluate(wavevectors);
}

inline Eigen::Matrix2cd FormFactorDecoratorPositionFactor::evaluatePol(const cvector_t &k_i,
                                                             const Bin1DCVector &k_f_bin) const
{
    cvector_t q = k_i - k_f_bin.getMidPoint();
    complex_t pos_factor = getPositionFactor(q);
    return pos_factor * mp_form_factor->evaluatePol(k_i, k_f_bin);
}

inline complex_t FormFactorDecoratorPositionFactor::getPositionFactor(const cvector_t &q) const
{
    complex_t qr = q.x() * m_position.x() + q.y() * m_position.y() + q.z() * m_position.z();
    complex_t pos_factor = std::exp(complex_t(0.0, 1.0) * qr);
    return pos_factor;
}

#endif /* FORMFACTORDECORATORPOSITIONFACTOR_H_ */
