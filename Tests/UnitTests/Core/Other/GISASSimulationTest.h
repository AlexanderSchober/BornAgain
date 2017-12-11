#include "Beam.h"
#include "BornAgainNamespace.h"
#include "GISASSimulation.h"
#include "IMultiLayerBuilder.h"
#include "Layer.h"
#include "MultiLayer.h"
#include "OutputData.h"
#include "google_test.h"
#include <cmath>
#include <memory>

class GISASSimulationTest : public ::testing::Test
{
protected:
    ~GISASSimulationTest();
    GISASSimulation m_simulation;
};

GISASSimulationTest::~GISASSimulationTest() = default;

TEST_F(GISASSimulationTest, SimulationInitialState)
{
    EXPECT_EQ(BornAgain::GISASSimulationType, m_simulation.getName());
    EXPECT_EQ(nullptr, m_simulation.sample());
    EXPECT_EQ(0u, m_simulation.numberOfSimulationElements());
    EXPECT_THROW(m_simulation.getDetectorIntensity(), std::runtime_error);
    EXPECT_EQ(1u, m_simulation.getChildren().size());
}

TEST_F(GISASSimulationTest, SimulationConstruction)
{
    MultiLayer multi_layer;
    GISASSimulation simulation(multi_layer);
    EXPECT_EQ(BornAgain::GISASSimulationType, simulation.getName());
    EXPECT_NE(nullptr, simulation.sample());
    EXPECT_EQ(0u, simulation.numberOfSimulationElements());
    EXPECT_THROW(simulation.getDetectorIntensity(), std::runtime_error);
    EXPECT_EQ(2u, simulation.getChildren().size());

    simulation.setDetectorParameters(10, -2.0, 2.0, 20, 0.0, 2.0);
    EXPECT_EQ(BornAgain::GISASSimulationType, simulation.getName());
    EXPECT_NE(nullptr, simulation.sample());
    EXPECT_EQ(200u, simulation.numberOfSimulationElements());
    EXPECT_NO_THROW(simulation.getDetectorIntensity());
    EXPECT_EQ(2u, simulation.getChildren().size());
}

TEST_F(GISASSimulationTest, SimulationClone)
{
    auto p_clone = m_simulation.clone();
    EXPECT_EQ(BornAgain::GISASSimulationType, p_clone->getName());
    EXPECT_EQ(nullptr, p_clone->sample());
    EXPECT_EQ(0u, p_clone->numberOfSimulationElements());
    EXPECT_THROW(p_clone->getDetectorIntensity(), std::runtime_error);
    EXPECT_EQ(1u, p_clone->getChildren().size());
    delete p_clone;

    MultiLayer multi_layer;
    GISASSimulation simulation(multi_layer);
    simulation.setDetectorParameters(10, -2.0, 2.0, 20, 0.0, 2.0);
    p_clone = simulation.clone();
    EXPECT_EQ(BornAgain::GISASSimulationType, p_clone->getName());
    EXPECT_NE(nullptr, p_clone->sample());
    EXPECT_EQ(200u, p_clone->numberOfSimulationElements());
    EXPECT_NO_THROW(p_clone->getDetectorIntensity());
    EXPECT_EQ(2u, p_clone->getChildren().size());
    delete p_clone;
}
