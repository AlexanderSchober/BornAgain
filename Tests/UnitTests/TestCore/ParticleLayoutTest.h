#ifndef PARTICLELAYOUTTEST_H
#define PARTICLELAYOUTTEST_H

#include "ParticleLayout.h"
#include "InterferenceFunctionNone.h"

class ParticleLayoutTest : public :: testing :: Test {

protected:
    ParticleLayoutTest(){}
    virtual ~ParticleLayoutTest(){}

};


TEST_F(ParticleLayoutTest, ParticleLayoutInitial)
{
    ParticleLayout particleDecoration;

    EXPECT_EQ("ParticleLayout", particleDecoration.getName());
    EXPECT_EQ(size_t(0), particleDecoration.getNumberOfParticles());
    EXPECT_EQ(size_t(0), particleDecoration.getNumberOfInterferenceFunctions());
}


TEST_F(ParticleLayoutTest, ParticleLayoutInitByValue)
{
    Particle particle;

    ParticleLayout particleDecoration(particle, 2.0);

    EXPECT_EQ("ParticleLayout", particleDecoration.getName());
    EXPECT_EQ(size_t(1), particleDecoration.getNumberOfParticles());
    EXPECT_EQ(size_t(0), particleDecoration.getNumberOfInterferenceFunctions());


    const IAbstractParticle * p_particle = particleDecoration.getParticle(size_t(0));
    EXPECT_TRUE(NULL!=p_particle);
    EXPECT_EQ(2.0, particleDecoration.getAbundanceOfParticle(size_t(0)));

    EXPECT_EQ(size_t(0), particleDecoration.getNumberOfInterferenceFunctions());

}


TEST_F(ParticleLayoutTest, ParticleLayoutInitByRef)
{
    Particle particle;

    ParticleLayout particleDecoration(particle, -2.0);

    EXPECT_EQ("ParticleLayout", particleDecoration.getName());
    EXPECT_EQ(size_t(1), particleDecoration.getNumberOfParticles());
    EXPECT_EQ(size_t(0), particleDecoration.getNumberOfInterferenceFunctions());


    const IAbstractParticle * p_particle = particleDecoration.getParticle(size_t(0));
    EXPECT_TRUE(NULL!=p_particle);
    EXPECT_EQ(-2.0, particleDecoration.getAbundanceOfParticle(size_t(0)));
}


TEST_F(ParticleLayoutTest, ParticleLayoutAddParticleInfo)
{
    ParticleLayout particleDecoration;

    Particle particle;
    particleDecoration.addParticle(particle, -2.0);

    EXPECT_EQ(size_t(1), particleDecoration.getNumberOfParticles());

    Particle particle2;
    particleDecoration.addParticle(particle2, 0.1);

    EXPECT_EQ(size_t(2), particleDecoration.getNumberOfParticles());

    const IAbstractParticle * p_particle = particleDecoration.getParticle(size_t(0));
    EXPECT_TRUE(NULL!=p_particle);
    EXPECT_EQ(-2.0, particleDecoration.getAbundanceOfParticle(size_t(0)));

    const IAbstractParticle * p_particle2 = particleDecoration.getParticle(size_t(1));
    EXPECT_TRUE(NULL!=p_particle2);
    EXPECT_EQ(0.1, particleDecoration.getAbundanceOfParticle(size_t(1)));
}


TEST_F(ParticleLayoutTest, ParticleLayoutAddParticle)
{
    ParticleLayout particleDecoration;

    Particle particle1;
    Particle particle2;
    Particle particle3;
    Particle particle4;

    RotationZ transform3(45.*Units::degree);
    RotationZ transform4(45.*Units::degree);

    particleDecoration.addParticle(particle1);
    particleDecoration.addParticle(particle2, 2.2);
    particleDecoration.addParticle(particle3, transform3);
    particleDecoration.addParticle(particle4, transform4, -4.2);

    EXPECT_EQ(size_t(4), particleDecoration.getNumberOfParticles());

    const IAbstractParticle * p_particle1 = particleDecoration.getParticle(size_t(0));
    EXPECT_TRUE(NULL!=p_particle1);
    EXPECT_EQ(1.0, particleDecoration.getAbundanceOfParticle(size_t(0)));

    const IAbstractParticle * p_particle2 = particleDecoration.getParticle(size_t(1));
    EXPECT_TRUE(NULL!=p_particle2);
    EXPECT_EQ(2.2, particleDecoration.getAbundanceOfParticle(size_t(1)));

    const IAbstractParticle * p_particle3 = particleDecoration.getParticle(size_t(2));
    EXPECT_TRUE(NULL!=p_particle3);
    EXPECT_EQ(1.0, particleDecoration.getAbundanceOfParticle(size_t(2)));

    const IAbstractParticle * p_particle4 = particleDecoration.getParticle(size_t(3));
    EXPECT_TRUE(NULL!=p_particle4);
    EXPECT_EQ(-4.2, particleDecoration.getAbundanceOfParticle(size_t(3)));
}


TEST_F(ParticleLayoutTest, ParticleLayoutAbundanceFraction)
{
    ParticleLayout particleDecoration;

    Particle particle1;
    Particle particle2;
    Particle particle3;
    Particle particle4;

    RotationY transform3(45.*Units::degree);
    RotationZ transform4(45.*Units::degree);

    particleDecoration.addParticle(particle1);
    EXPECT_EQ(1.0, particleDecoration.getAbundanceOfParticle(size_t(0)));

    particleDecoration.addParticle(particle2, 2.0);
    EXPECT_EQ(2.0, particleDecoration.getAbundanceOfParticle(size_t(1)));

    particleDecoration.addParticle(particle3, transform3);
    EXPECT_EQ(1.0, particleDecoration.getAbundanceOfParticle(size_t(2)));

    particleDecoration.addParticle(particle4, transform4, 4.0);
    EXPECT_EQ(4.0, particleDecoration.getAbundanceOfParticle(size_t(3)));
}


TEST_F(ParticleLayoutTest, ParticleLayoutClone)
{
    ParticleLayout particleDecoration;

    Particle particle1;
    Particle particle2;
    Particle particle3;
    Particle particle4;

    RotationY transform3(45.*Units::degree);
    RotationZ transform4(45.*Units::degree);

    particleDecoration.addParticle(particle1);
    particleDecoration.addParticle(particle2, 2.0);
    particleDecoration.addParticle(particle3, transform3);
    particleDecoration.addParticle(particle4, transform4, 4.0);

    HomogeneousMaterial mat5("core", 0, 0);
    Particle particle5(mat5);
    particleDecoration.addParticle(particle5, 0.0);

    particleDecoration.addInterferenceFunction(new InterferenceFunctionNone());
    particleDecoration.addInterferenceFunction(new InterferenceFunctionNone());
    particleDecoration.addInterferenceFunction(new InterferenceFunctionNone());

    ParticleLayout * clone = particleDecoration.clone();

    EXPECT_EQ("ParticleLayout", clone->getName());

    const IAbstractParticle * p_particle1 = clone->getParticle(size_t(0));
    EXPECT_TRUE(NULL!=p_particle1);
    EXPECT_EQ(1.0, particleDecoration.getAbundanceOfParticle(size_t(0)));

    const IAbstractParticle * p_particle2 = clone->getParticle(size_t(1));
    EXPECT_TRUE(NULL!=p_particle2);
    EXPECT_EQ(2.0, particleDecoration.getAbundanceOfParticle(size_t(1)));

    const IAbstractParticle * p_particle3 = clone->getParticle(size_t(2));
    EXPECT_TRUE(NULL!=p_particle3);
    EXPECT_EQ(1.0, particleDecoration.getAbundanceOfParticle(size_t(2)));

    const IAbstractParticle * p_particle4 = clone->getParticle(size_t(3));
    EXPECT_TRUE(NULL!=p_particle4);
    EXPECT_EQ(4.0, particleDecoration.getAbundanceOfParticle(size_t(3)));

    const IAbstractParticle * p_particle5 = clone->getParticle(size_t(4));
    EXPECT_TRUE(NULL!=p_particle5);
    EXPECT_EQ(0.0, particleDecoration.getAbundanceOfParticle(size_t(4)));

    EXPECT_EQ(size_t(3), clone->getNumberOfInterferenceFunctions());
    EXPECT_EQ(size_t(3), clone->getInterferenceFunctions().size());
    EXPECT_TRUE(NULL!=clone->getInterferenceFunction(size_t(0)));
    EXPECT_TRUE(NULL!=clone->getInterferenceFunction(size_t(1)));
    EXPECT_TRUE(NULL!=clone->getInterferenceFunction(size_t(2)));
}


TEST_F(ParticleLayoutTest, ParticleLayoutCloneInvertB)
{
    ParticleLayout particleDecoration;

    HomogeneousMaterial mat1("Air",0,0);
    Particle particle1(mat1);

    HomogeneousMaterial mat2("Stone",0,0);
    Particle particle2(mat2);

    HomogeneousMaterial mat3("wood",0,0);
    Particle particle3(mat3);

    HomogeneousMaterial mat4("silica",0,0);
    Particle particle4(mat4);

    RotationY transform3(45.*Units::degree);
    RotationZ transform4(45.*Units::degree);


    particleDecoration.addParticle(particle1);
    particleDecoration.addParticle(particle2, 2.0);
    particleDecoration.addParticle(particle3, transform3);
    particleDecoration.addParticle(particle4, transform4, 4.0);

    HomogeneousMaterial mat5("core",0,0);
    Particle particle5(mat5);
    particleDecoration.addParticle(particle5, 0.0);

    particleDecoration.addInterferenceFunction(new InterferenceFunctionNone());
    particleDecoration.addInterferenceFunction(new InterferenceFunctionNone());
    particleDecoration.addInterferenceFunction(new InterferenceFunctionNone());

    ParticleLayout * clone = particleDecoration.cloneInvertB();

    EXPECT_EQ("ParticleLayout_inv", clone->getName());

    const IAbstractParticle * p_particle1 = clone->getParticle(size_t(0));
    EXPECT_TRUE(NULL!=p_particle1);
    EXPECT_EQ(1.0, particleDecoration.getAbundanceOfParticle(size_t(0)));

    const IAbstractParticle * p_particle2 = clone->getParticle(size_t(1));
    EXPECT_TRUE(NULL!=p_particle2);
    EXPECT_EQ(2.0, particleDecoration.getAbundanceOfParticle(size_t(1)));

    const IAbstractParticle * p_particle3 = clone->getParticle(size_t(2));
    EXPECT_TRUE(NULL!=p_particle3);
    EXPECT_EQ(1.0, particleDecoration.getAbundanceOfParticle(size_t(2)));

    const IAbstractParticle * p_particle4 = clone->getParticle(size_t(3));
    EXPECT_TRUE(NULL!=p_particle4);
    EXPECT_EQ(4.0, particleDecoration.getAbundanceOfParticle(size_t(3)));

    const IAbstractParticle * p_particle5 = clone->getParticle(size_t(4));
    EXPECT_TRUE(NULL!=p_particle5);
    EXPECT_EQ(0.0, particleDecoration.getAbundanceOfParticle(size_t(4)));

    EXPECT_EQ(size_t(3), clone->getNumberOfInterferenceFunctions());
    EXPECT_EQ(size_t(3), clone->getInterferenceFunctions().size());
    EXPECT_TRUE(NULL!=clone->getInterferenceFunction(size_t(0)));
    EXPECT_TRUE(NULL!=clone->getInterferenceFunction(size_t(1)));
    EXPECT_TRUE(NULL!=clone->getInterferenceFunction(size_t(2)));
}


TEST_F(ParticleLayoutTest, ParticleLayoutInterferenceFunction)
{
    ParticleLayout particleDecoration;

    particleDecoration.addInterferenceFunction(new InterferenceFunctionNone());
    particleDecoration.addInterferenceFunction(new InterferenceFunctionNone());
    particleDecoration.addInterferenceFunction(new InterferenceFunctionNone());

    EXPECT_EQ(size_t(3), particleDecoration.getNumberOfInterferenceFunctions());
    EXPECT_EQ(size_t(3), particleDecoration.getInterferenceFunctions().size());
    EXPECT_TRUE(NULL!=particleDecoration.getInterferenceFunction(size_t(0)));
    EXPECT_TRUE(NULL!=particleDecoration.getInterferenceFunction(size_t(1)));
    EXPECT_TRUE(NULL!=particleDecoration.getInterferenceFunction(size_t(2)));
}


#endif // PARTICLELAYOUTTEST_H
