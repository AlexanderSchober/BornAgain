#include "FitStrategyAdjustParameters.h"
#include "FitSuite.h"
#include "MessageService.h"


FitStrategyAdjustParameters::FitStrategyAdjustParameters(const FitStrategyAdjustParameters &other)
    : IFitStrategy(other)
    , m_fix_all(other.m_fix_all)
    , m_release_all(other.m_release_all)
    , m_pars_to_fix(other.m_pars_to_fix)
    , m_pars_to_release(other.m_pars_to_release)
    , m_preserve_original_values(other.m_preserve_original_values)
{

}


//! strategy which fixes/releases fit parameters and then call minimizer
void FitStrategyAdjustParameters::execute()
{
    if( !m_fit_suite ) throw NullPointerException("FitSuiteStrategyAdjustParameters::execute() -> FitSuite doesn't exists");
    FitSuiteParameters *fitParameters = m_fit_suite->getFitParameters();

    // fixing all parameters at they current values
    if( m_fix_all ) {
        for(FitSuiteParameters::iterator it = fitParameters->begin(); it!=fitParameters->end(); ++it) {
            (*it)->setFixed(true);
        }
    }

    // releasing all parameters
    if( m_release_all ) {
        for(FitSuiteParameters::iterator it = fitParameters->begin(); it!=fitParameters->end(); ++it) {
            msglog(MSG::DEBUG2) << "FitSuiteStrategyAdjustParameters::execute() -> releasing " << (*it)->getName();
            (*it)->setFixed(false);
        }
    }

    // fixing dedicated list of fit parameters
    for(std::vector<std::string >::iterator it = m_pars_to_fix.begin(); it!= m_pars_to_fix.end(); ++it) {
        msglog(MSG::DEBUG2) << "FitSuiteStrategyAdjustParameters::execute() -> fixing " << (*it);
        fitParameters->getParameter((*it))->setFixed(true);
    }

    // releasing dedicated list of fit parameters
    for(std::vector<std::string >::iterator it = m_pars_to_release.begin(); it!= m_pars_to_release.end(); ++it) {
        msglog(MSG::DEBUG2) << "FitSuiteStrategyAdjustParameters::execute() -> releasing " << (*it);
        fitParameters->getParameter((*it))->setFixed(false);
    }

    // saving original param values
    std::vector<double > original_param_values = fitParameters->getValues();

    // calling minimization
    m_fit_suite->minimize();

    // returning parameters to original values as they were before minimization
    if(m_preserve_original_values) {
        fitParameters->setValues(original_param_values);
    }
}




