#include "TestDiffuseReflection.h"
#include "MultiLayer.h"
#include "SampleFactory.h"
#include "DWBADiffuseReflection.h"
#include "OutputData.h"
#include "DrawHelper.h"

#include <iostream>
#include "TCanvas.h"
#include "TGraph.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TApplication.h"
#include "TStyle.h"




TestDiffuseReflection::TestDiffuseReflection() :
    m_alphaMin(0.0*Units::degree),
    m_alphaMax(2.0*Units::degree),
    m_npoints(101)
{
    std::cout << "TestDiffuseScattering::TestDiffuseReflection() -> Info." << std::endl;

    // Performance log
    // 18.06.2012       diffuse   :  Cpu Time =   7.67 seconds  (MultilayerOffspecTestcase1a,MultilayerOffspecTestcase1b, MultilayerOffspecTestcase2a, MultilayerOffspecTestcase2b)
}


/* ************************************************************************* */
//! offspecular (diffuse) reflection for several standard samples
/* ************************************************************************* */
void TestDiffuseReflection::execute()
{
    std::cout << "TestDiffuseScattering::execute() -> Info." << std::endl;
    DWBADiffuseReflection calc;

    std::vector<std::string > snames;
    snames.push_back("MultilayerOffspecTestcase1a");
    snames.push_back("MultilayerOffspecTestcase1b");
    snames.push_back("MultilayerOffspecTestcase2a");
    snames.push_back("MultilayerOffspecTestcase2b");

    std::vector<MultiLayer *> samples;
    for(size_t i_sample=0; i_sample<snames.size(); i_sample++){
        samples.push_back( dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem(snames[i_sample])) );
    }

    kvector_t ki, kf;
    for(size_t i_sample=0; i_sample<samples.size(); i_sample++){
        m_sample = samples[i_sample];

        // specular reflectivity alpha_i = alpha_f
        m_data_spec = new OutputData<double >;
        m_data_spec->addAxis(std::string("alpha_i"), m_alphaMin, m_alphaMax, m_npoints);
        m_data_spec->resetIndex();
        while (m_data_spec->hasNext()) {
            double alpha_i = m_data_spec->getCurrentValueOfAxis<double>("alpha_i");
            ki.setLambdaAlphaPhi(1.54*Units::angstrom, -alpha_i, 0.0);
            kf.setLambdaAlphaPhi(1.54*Units::angstrom, alpha_i, 0.0);
            //double r = calc.execute0(*m_sample, ki, kf);
            calc.execute(*m_sample, ki, kf);
            //std::cout << " " << calc.getDiffuseAutocorr() << " " << calc.getDiffuseCrosscorr()
            //          << " sum:" << calc.getDiffuseAutocorr()+calc.getDiffuseCrosscorr()
            //          //<< " " << calc.diffuse_crosscorr2()
            //          << std::endl;
            m_data_spec->next() = calc.getDiffuseAutocorr() + calc.getDiffuseCrosscorr();
        }

        // offspecular reflectivity
        m_data_offspec = new OutputData<double >;
        m_data_offspec->addAxis(std::string("alpha_i"), m_alphaMin, m_alphaMax, m_npoints);
        m_data_offspec->addAxis(std::string("alpha_f"), m_alphaMin, m_alphaMax, m_npoints);
        m_data_spec->resetIndex();
        while (m_data_offspec->hasNext()) {
            double alpha_i = m_data_offspec->getCurrentValueOfAxis<double>("alpha_i");
            double alpha_f = m_data_offspec->getCurrentValueOfAxis<double>("alpha_f");
            ki.setLambdaAlphaPhi(1.54*Units::angstrom, -alpha_i, 0.0);
            kf.setLambdaAlphaPhi(1.54*Units::angstrom, alpha_f, 0.0);
            //double r = calc.execute0(*m_sample, ki, kf);
            calc.execute(*m_sample, ki, kf);
            m_data_offspec->next() = calc.getDiffuseAutocorr() + calc.getDiffuseCrosscorr();
        }

        draw();

        delete m_data_spec;
        delete m_data_offspec;
    }

//    // difference between samples
//    double dalpha = (m_alphaMax - m_alphaMin) / (m_npoints-1);
//    TH2D h2("h2","h2", m_npoints, Units::rad2deg(m_alphaMin-dalpha/2.), Units::rad2deg(m_alphaMax+dalpha/2.), m_npoints, Units::rad2deg(m_alphaMin-dalpha/2.), Units::rad2deg(m_alphaMax+dalpha/2.) );
//    h2.SetStats(0);
//    m_data_offspec = new OutputData<double >;
//    m_data_offspec->addAxis(std::string("alpha_i"), m_alphaMin, m_alphaMax, m_npoints);
//    m_data_offspec->addAxis(std::string("alpha_f"), m_alphaMin, m_alphaMax, m_npoints);
//    m_data_offspec->resetIndex();
//    while (m_data_offspec->hasNext()) {
//        double alpha_i = m_data_offspec->getCurrentValueOfAxis<double>("alpha_i");
//        double alpha_f = m_data_offspec->getCurrentValueOfAxis<double>("alpha_f");
//        ki.setLambdaAlphaPhi(1.54*Units::angstrom, -alpha_i, 0.0);
//        kf.setLambdaAlphaPhi(1.54*Units::angstrom, alpha_f, 0.0);
//        double r = calc.execute0(*samples[0], ki, kf) - calc.execute0(*samples[0], ki, kf);
//        h2.Fill(alpha_i, alpha_f, r);
//        m_data_offspec->next() = r;
//    }
//    TCanvas *c3 = new TCanvas("c3","c3",1024, 768);
//    c3->Divide(2,2);
//    c3->cd(1);
//    gPad->SetRightMargin(0.2);
//    gPad->SetTopMargin(0.12);
//    h2.DrawCopy("CONT4 Z");

//    c3->cd(2);
//    gPad->SetRightMargin(0.2);
//    gPad->SetTopMargin(0.12);
//    m_hists[0].Add(&m_hists[1],-1.0);
//    m_hists[0].DrawCopy("CONT4 Z");


    for(size_t i_sample=0; i_sample<samples.size(); i_sample++){
        delete samples[i_sample];
    }
    samples.clear();

}



void TestDiffuseReflection::draw()
{
    // specular plot
    TGraph *gr = new TGraph(m_npoints);
    m_data_spec->resetIndex();
    int i_point=0;
    while (m_data_spec->hasNext())
    {
        double alpha_i = m_data_spec->getCurrentValueOfAxis<double>("alpha_i");
        double r = m_data_spec->next();
        gr->SetPoint(i_point++, Units::rad2deg(alpha_i), r);
    }

    // off specular plot
    double dalpha = (m_alphaMax - m_alphaMin) / (m_npoints-1);
    TH2D h2("h2","h2", m_npoints, Units::rad2deg(m_alphaMin-dalpha/2.), Units::rad2deg(m_alphaMax+dalpha/2.), m_npoints, Units::rad2deg(m_alphaMin-dalpha/2.), Units::rad2deg(m_alphaMax+dalpha/2.) );
    h2.SetContour(50);
    h2.SetMinimum(0.001);
    h2.SetStats(0);
    m_data_offspec->resetIndex();
    while (m_data_offspec->hasNext()) {
        double alpha_i = m_data_offspec->getCurrentValueOfAxis<double>("alpha_i");
        double alpha_f = m_data_offspec->getCurrentValueOfAxis<double>("alpha_f");
        double r = m_data_offspec->next();
        h2.Fill( Units::rad2deg(alpha_i), Units::rad2deg(alpha_f), r);
    }

    // create name of canvas different for each new call of this method
    static int ncall=0;
    std::ostringstream os;
    os << (ncall++) << std::endl;
    std::string cname = std::string("c1_test_diffuse_reflection")+os.str();
    TCanvas *c1 = new TCanvas(cname.c_str(),"Diffuse reflection",1024,768);
    DrawHelper::instance().SetMagnifier(c1);

//    c1->Divide(2,2);
//    c1->cd(1);
//    gr->Draw("apl");

//    c1->cd(2);
    c1->cd();
    gPad->SetRightMargin(0.2);
    gStyle->SetPalette(1);
    gPad->SetLogz();
    h2.DrawCopy("CONT4 Z");

}

