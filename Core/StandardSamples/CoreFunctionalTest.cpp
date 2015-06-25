// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/CoreFunctionalTest.cpp
//! @brief     Implements class CoreFunctionalTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "CoreFunctionalTest.h"
#include "GISASSimulation.h"
#include "IntensityDataFunctions.h"
#include "FileSystem.h"
#include "IntensityDataIOFactory.h"

namespace
{
const std::string directory_name_for_failed_tests = "00_failed_tests";
}

CoreFunctionalTest::CoreFunctionalTest(const std::string &name, const std::string &description,
                                       GISASSimulation *simulation, OutputData<double> *reference,
                                       double threshold)
    : IFunctionalTest(name, description), m_simulation(simulation), m_reference(reference),
      m_threshold(threshold), m_difference(0)
{
}

CoreFunctionalTest::~CoreFunctionalTest()
{
    delete m_simulation;
    delete m_reference;
}

void CoreFunctionalTest::runTest()
{
    if (!m_simulation) {
        throw NullPointerException(
            "AdvancedFunctionalTest::runTest() -> Error. Uninitialized simulation object.");
    }
    m_simulation->runSimulation();
}

int CoreFunctionalTest::analyseResults()
{
    if (!m_reference) {
        m_result = FAILED_NOREF;
    } else {
        try {
            m_difference = IntensityDataFunctions::getRelativeDifference(*m_simulation->getOutputData(),
                                                                     *m_reference);
            m_result = (m_difference > m_threshold ? FAILED_DIFF : SUCCESS);
        } catch(const std::exception &ex) {
            std::cout << "CoreFunctionalTest::analyseResults() -> Intensity data comparison failed " << std::endl;
            std::cout << ex.what() << std::endl;
            m_result = FAILED_DIFF;
        }
    }

    if (getTestResult() != SUCCESS)
        saveSimulationResults();

    return m_result;
}

void CoreFunctionalTest::printResults(std::ostream &ostr) const
{
    ostr << getFormattedInfoString();
    if (getTestResult() == SUCCESS || getTestResult() == FAILED_DIFF) {
        std::ostringstream sdiff;
        sdiff << std::setw(10) << std::left << std::scientific << std::setprecision(4)
              << m_difference;
        ostr << sdiff.str();
    }

    if (getTestResult() != SUCCESS)
        ostr << "--> " << getSimulationResultsFileNameAndPath();
}

//! Sets the name of the file to use to save the simulation results in the case of
//! failed simulation.
void CoreFunctionalTest::setSimulationResultsFileName(const std::string &file_name)
{
    m_simulation_results_file_name = file_name;
}

//! Saves simulation results into the file. Called if test has failed.
void CoreFunctionalTest::saveSimulationResults() const
{
    Utils::FileSystem::CreateDirectory(directory_name_for_failed_tests);
    IntensityDataIOFactory::writeIntensityData(*getOutputData(),
                                               getSimulationResultsFileNameAndPath());
}

//! Constructs file name to save results. Strip gzip extention if necessary.
std::string CoreFunctionalTest::getSimulationResultsFileNameAndPath() const
{
    std::string result
        = Utils::FileSystem::StripFileNameFromGzipExtention(m_simulation_results_file_name);
    result = Utils::FileSystem::GetJoinPath(directory_name_for_failed_tests, result);
    return result;
}

const OutputData<double> *CoreFunctionalTest::getOutputData() const
{
    if (m_simulation) {
        return m_simulation->getOutputData();
    }
    return 0;
}
