#ifndef MYPARTICLEBUILDER_H
#define MYPARTICLEBUILDER_H
#include "IFormFactor.h"
#include "Particle.h"
#include "IStochasticParameter.h"
#include "ParticleLayout.h"
#include "LabelSample.h"

//! @class ParticleBuilder
//! @ingroup samples_internal
//! @brief To build set of particles with similar properties

class LabelSample;

class BA_CORE_API_ MyParticleBuilder
{
public:
    MyParticleBuilder();
    virtual ~MyParticleBuilder();

    //! Sets prototype for particle production
    //! @param particle   prototype of particle
    //! @param name       parameter name in the parameter pool of given prototype
    //! @param parameter  variation type
    //! @param scale      global scale factor for probabilities
    void setPrototype(const Particle& particle, std::string name, const StochasticParameter<double>& param, double scale=1.0);

    //! plant particles in given decoration
    void plantParticles(ParticleLayout& decor, LabelSample *labelSample);

private:
    Particle *m_prototype; //!< prototype of the particle, all particles will be cloned from it
    std::string m_parameter_name; //!< name of parameter to variate
    StochasticParameter<double > *m_parameter;
    double m_scale; //!< global scale factor for probabilities 
};

#endif // MYPARTICLEBUILDER_H
