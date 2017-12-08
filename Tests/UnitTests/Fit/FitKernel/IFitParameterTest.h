#include "google_test.h"
#include "IFitParameter.h"
#include <memory>

class IFitParameterTest : public ::testing::Test
{
protected:
    IFitParameterTest(){}
    virtual ~IFitParameterTest(){}
};

TEST_F(IFitParameterTest, Initial)
{
    IFitParameter par;
    EXPECT_EQ(std::string(), par.name());
    EXPECT_EQ(0.0, par.value());
    EXPECT_EQ(0.0, par.startValue());
    EXPECT_EQ(0.0, par.step());
    EXPECT_EQ(0.0, par.error());
    EXPECT_TRUE(par.limits().isLimitless());
}

TEST_F(IFitParameterTest, Constructors)
{
    const std::string name("name");
    const double value(1.0);

    IFitParameter par(name, value);
    EXPECT_EQ(name, par.name());
    EXPECT_EQ(value, par.value());
    EXPECT_EQ(value, par.startValue());
    EXPECT_EQ(0.0, par.step());
    EXPECT_EQ(0.0, par.error());
    EXPECT_TRUE(par.limits().isLimitless());

    const AttLimits limits = AttLimits::limited(1.0, 2.0);
    const double step(0.01);

    IFitParameter par2(name, value, limits, step);
    EXPECT_EQ(name, par2.name());
    EXPECT_EQ(value, par2.value());
    EXPECT_EQ(value, par2.startValue());
    EXPECT_EQ(step, par2.step());
    EXPECT_EQ(0.0, par2.error());
    EXPECT_EQ(limits, par2.limits());
}

TEST_F(IFitParameterTest, Setters)
{
    const std::string name("name");
    const double start_value(1.0);
    const double value(2.0);
    const AttLimits limits = AttLimits::limited(1.0, 2.0);
    const double error(0.02);
    const double step(0.01);

    IFitParameter par(name, start_value);
    par.setValue(value);

    EXPECT_EQ(value, par.value());
    EXPECT_EQ(start_value, par.startValue());

    par.setError(error);
    EXPECT_EQ(error, par.error());

    par.setLimits(limits);
    EXPECT_EQ(limits, par.limits());

    par.setStep(step);
    EXPECT_EQ(step, par.step());
}

TEST_F(IFitParameterTest, CompoundSetters)
{
    const std::string name("name");
    const double start_value(1.0);
    const double step(0.1);
    const double lim1(1.0), lim2(2.0);

    IFitParameter par(name, start_value);

    par.setStep(step).setLowerLimited(lim1);
    EXPECT_EQ(step, par.step());
    EXPECT_TRUE(par.limits().isLowerLimited());
    EXPECT_EQ(par.limits().lowerLimit(), lim1);
    EXPECT_EQ(par.limits().upperLimit(), 0.0);

    par.setStep(step).setUpperLimited(lim2);
    EXPECT_TRUE(par.limits().isUpperLimited());
    EXPECT_EQ(par.limits().lowerLimit(), 0.0);
    EXPECT_EQ(par.limits().upperLimit(), lim2);

    par.setStep(step).setLimited(lim1, lim2);
    EXPECT_TRUE(par.limits().isLimited());
    EXPECT_EQ(par.limits().lowerLimit(), lim1);
    EXPECT_EQ(par.limits().upperLimit(), lim2);

    par.setStep(step).setFixed();
    EXPECT_TRUE(par.limits().isFixed());
    EXPECT_EQ(par.limits().lowerLimit(), 0.0);
    EXPECT_EQ(par.limits().upperLimit(), 0.0);
}

TEST_F(IFitParameterTest, Clone)
{
    const double start_value(1.0), value(2.0), error(0.1), step(0.01), lim1(10.0), lim2(10.0);
    IFitParameter par("par1", start_value, AttLimits::limited(lim1, lim2), step);
    par.setValue(value);
    par.setError(error);
    std::unique_ptr<IFitParameter> clone(par.clone());

    EXPECT_EQ("par1", clone->name());
    EXPECT_EQ(start_value, clone->startValue());
    EXPECT_EQ(value, clone->value());
    EXPECT_EQ(error, clone->error());
    EXPECT_EQ(step, clone->step());
    EXPECT_EQ(lim1, clone->limits().lowerLimit());
    EXPECT_EQ(lim2, clone->limits().upperLimit());
}
