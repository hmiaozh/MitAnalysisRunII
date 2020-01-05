#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TString.h>
#include <TRandom.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <iostream>
#include <fstream>
#include "TLorentzVector.h"

#include "MitAnalysisRunII/panda/macros/10x_g/pandaFlat.C"
#include "MitAnalysisRunII/panda/macros/10x_g/common.h"
#include "MitAnalysisRunII/panda/macros/9x/applyCorrections.h"

const bool isDEBUG = false;
const double mcPrescale = 1;
const bool usePureMC = true;

void vbfgTriggerAnalysis(
int year
){
  double ptMin = 200;
  int whichYear = -1;
  if     (year == 2016) {whichYear = Y2016; ptMin = 80.;}
  else if(year == 2017) {whichYear = Y2017; ptMin = 200.;}
  else if(year == 2018) {whichYear = Y2018; ptMin = 80.;}
  else {printf("Wrong year (%d)!\n",year); return;}

  //*******************************************************
  //Inputs
  //*******************************************************
  vector<TString> infileName_;
  vector<int> infileCat_;

  TString filesPath;
  TString fLepton_FakesName = Form("MitAnalysisRunII/data/90x/fakes/histoFakeEtaPt_%d.root",year);
  TString puPath;
  TString photonSFPath;
  TString elephoSFPath = Form("MitAnalysisRunII/data/90x/eff/histoDY0LGSF_%d.root",year);
  TString trgSFPath = Form("MitAnalysisRunII/data/90x/histo_triggerEff_sel0_%d.root",year);
  TString effSFPath = Form("MitAnalysisRunII/data/90x/eff/histoDY0EffSFStudy_%d.root",year);
  //TString npvPath = Form("MitAnalysisRunII/data/90x/pu/npvWeights_%d.root",year);
  if(year == 2018) {
    filesPath = Form("/scratch5/bmaier/darkg/2018/vbfg_v_013_v6/");
    puPath = "MitAnalysisRunII/data/90x/pu/puWeights_90x_2018.root";
    photonSFPath = "MitAnalysisRunII/data/90x/eff/photon_scalefactors_2018.root";

    infileName_.push_back(Form("%sSingleMuon.root",filesPath.Data()));  	      infileCat_.push_back(kPlotData);

    infileName_.push_back(Form("%sDiboson_ww_CP5.root" ,filesPath.Data()));           infileCat_.push_back(kPlotWW);

    infileName_.push_back(Form("%sDiboson_wz_CP5.root" ,filesPath.Data()));           infileCat_.push_back(kPlotWZ);

    infileName_.push_back(Form("%sDiboson_zz_CP5.root" ,filesPath.Data()));           infileCat_.push_back(kPlotZZ);

    infileName_.push_back(Form("%sWJets_ht100to200_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotWJ);
    infileName_.push_back(Form("%sWJets_ht200to400_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotWJ);
    infileName_.push_back(Form("%sWJets_ht400to600_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotWJ);
    infileName_.push_back(Form("%sWJets_ht600to800_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotWJ);
    infileName_.push_back(Form("%sWJets_ht800to1200_CP5.root" ,filesPath.Data()));    infileCat_.push_back(kPlotWJ);
    infileName_.push_back(Form("%sWJets_ht1200to2500_CP5.root" ,filesPath.Data()));   infileCat_.push_back(kPlotWJ);
    infileName_.push_back(Form("%sWJets_ht2500toinf_CP5.root" ,filesPath.Data()));    infileCat_.push_back(kPlotWJ);
    infileName_.push_back(Form("%sWJets_EWKWPlus.root" ,filesPath.Data()));           infileCat_.push_back(kPlotWJ);
    infileName_.push_back(Form("%sWJets_EWKWMinus.root" ,filesPath.Data()));          infileCat_.push_back(kPlotWJ);

    infileName_.push_back(Form("%sZJets_ht100to200_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZJets_ht200to400_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZJets_ht400to600_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZJets_ht600to800_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZJets_ht800to1200_CP5.root" ,filesPath.Data()));    infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZJets_ht1200to2500_CP5.root" ,filesPath.Data()));   infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZJets_ht2500toinf_CP5.root" ,filesPath.Data()));    infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZJets_lo_CP5.root" ,filesPath.Data()));             infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZJets_EWK.root" ,filesPath.Data()));                infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZtoNuNu_ht100to200_CP5.root" ,filesPath.Data()));   infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZtoNuNu_ht200to400_CP5.root" ,filesPath.Data()));   infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZtoNuNu_ht400to600_CP5.root" ,filesPath.Data()));   infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZtoNuNu_ht600to800_CP5.root" ,filesPath.Data()));   infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZtoNuNu_ht800to1200_CP5.root" ,filesPath.Data()));  infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZtoNuNu_ht1200to2500_CP5.root" ,filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZtoNuNu_ht2500toinf_CP5.root" ,filesPath.Data()));  infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZtoNuNu_EWK.root" ,filesPath.Data()));              infileCat_.push_back(kPlotDY);

    infileName_.push_back(Form("%sTTbar_GJets_CP5.root" ,filesPath.Data()));          infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sSingleTop_tG_CP5.root" ,filesPath.Data()));         infileCat_.push_back(kPlotTop);

    infileName_.push_back(Form("%sWZG.root" ,filesPath.Data()));		      infileCat_.push_back(kPlotVVV);

    infileName_.push_back(Form("%sWGtoLNuG_nlo.root" ,filesPath.Data())); 	      infileCat_.push_back(kPlotWG);

    infileName_.push_back(Form("%sZGTo2LG_nlo.root" ,filesPath.Data())); 	      infileCat_.push_back(kPlotZG);

    infileName_.push_back(Form("%sGJets_ht100to200_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotGJ);
    infileName_.push_back(Form("%sGJets_ht200to400_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotGJ);
    infileName_.push_back(Form("%sGJets_ht400to600_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotGJ);
    infileName_.push_back(Form("%sGJets_ht600toinf_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotGJ);
  }
  else if(year == 2017) {
    filesPath = Form("/scratch5/bmaier/darkg/2017/vbfg_v_012_v6/");
    puPath = "MitAnalysisRunII/data/90x/pu/puWeights_90x_2017.root";
    photonSFPath = "MitAnalysisRunII/data/90x/eff/photon_scalefactors_2017.root";

    infileName_.push_back(Form("%sSingleMuon.root",filesPath.Data()));  	      infileCat_.push_back(kPlotData);

    infileName_.push_back(Form("%sDiboson_ww_CP5.root" ,filesPath.Data()));           infileCat_.push_back(kPlotWW);

    infileName_.push_back(Form("%sDiboson_wz_CP5.root" ,filesPath.Data()));           infileCat_.push_back(kPlotWZ);

    infileName_.push_back(Form("%sDiboson_zz_CP5.root" ,filesPath.Data()));           infileCat_.push_back(kPlotZZ);

    infileName_.push_back(Form("%sWJets_ht100to200_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotWJ);
    infileName_.push_back(Form("%sWJets_ht200to400_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotWJ);
    infileName_.push_back(Form("%sWJets_ht400to600_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotWJ);
    infileName_.push_back(Form("%sWJets_ht600to800_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotWJ);
    infileName_.push_back(Form("%sWJets_ht800to1200_CP5.root" ,filesPath.Data()));    infileCat_.push_back(kPlotWJ);
    infileName_.push_back(Form("%sWJets_ht1200to2500_CP5.root" ,filesPath.Data()));   infileCat_.push_back(kPlotWJ);
    infileName_.push_back(Form("%sWJets_ht2500toinf_CP5.root" ,filesPath.Data()));    infileCat_.push_back(kPlotWJ);
    infileName_.push_back(Form("%sWJets_EWKWPlus.root" ,filesPath.Data()));           infileCat_.push_back(kPlotWJ);
    infileName_.push_back(Form("%sWJets_EWKWMinus.root" ,filesPath.Data()));          infileCat_.push_back(kPlotWJ);

    infileName_.push_back(Form("%sZJets_ht100to200_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZJets_ht200to400_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZJets_ht400to600_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZJets_ht600to800_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZJets_ht800to1200_CP5.root" ,filesPath.Data()));    infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZJets_ht1200to2500_CP5.root" ,filesPath.Data()));   infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZJets_ht2500toinf_CP5.root" ,filesPath.Data()));    infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZJets_EWK.root" ,filesPath.Data()));                infileCat_.push_back(kPlotDY);
    //infileName_.push_back(Form("%sZtoNuNu_ht100to200_CP5.root" ,filesPath.Data()));   infileCat_.push_back(kPlotDY);
    //infileName_.push_back(Form("%sZtoNuNu_ht200to400_CP5.root" ,filesPath.Data()));   infileCat_.push_back(kPlotDY);
    //infileName_.push_back(Form("%sZtoNuNu_ht400to600_CP5.root" ,filesPath.Data()));   infileCat_.push_back(kPlotDY);
    //infileName_.push_back(Form("%sZtoNuNu_ht600to800_CP5.root" ,filesPath.Data()));   infileCat_.push_back(kPlotDY);
    //infileName_.push_back(Form("%sZtoNuNu_ht800to1200_CP5.root" ,filesPath.Data()));  infileCat_.push_back(kPlotDY);
    //infileName_.push_back(Form("%sZtoNuNu_ht1200to2500_CP5.root" ,filesPath.Data())); infileCat_.push_back(kPlotDY);
    //infileName_.push_back(Form("%sZtoNuNu_ht2500toinf_CP5.root" ,filesPath.Data()));  infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZtoNuNu_EWK.root" ,filesPath.Data()));              infileCat_.push_back(kPlotDY);

    infileName_.push_back(Form("%sTTbar_GJets_CP5.root" ,filesPath.Data()));          infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sSingleTop_tG_CP5.root" ,filesPath.Data()));         infileCat_.push_back(kPlotTop);

    infileName_.push_back(Form("%sWZG.root" ,filesPath.Data()));		      infileCat_.push_back(kPlotVVV);

    infileName_.push_back(Form("%sWGtoLNuG_nlo.root" ,filesPath.Data())); 	      infileCat_.push_back(kPlotWG);

    infileName_.push_back(Form("%sZGTo2LG_nlo.root" ,filesPath.Data())); 	      infileCat_.push_back(kPlotZG);

    infileName_.push_back(Form("%sGJets_ht100to200_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotGJ);
    infileName_.push_back(Form("%sGJets_ht200to400_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotGJ);
    infileName_.push_back(Form("%sGJets_ht400to600_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotGJ);
    infileName_.push_back(Form("%sGJets_ht600toinf_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotGJ);
  }
  else if(year == 2016) {
    filesPath = Form("");
    puPath = "MitAnalysisRunII/data/90x/pu/puWeights_90x_2016.root";
    photonSFPath = "MitAnalysisRunII/data/90x/eff/photon_scalefactors_2016.root";

    infileName_.push_back(Form("%sSingleMuon.root",filesPath.Data()));  	      infileCat_.push_back(kPlotData);

    infileName_.push_back(Form("%sDiboson_ww.root" ,filesPath.Data()));           infileCat_.push_back(kPlotWW);

    infileName_.push_back(Form("%sDiboson_wz.root" ,filesPath.Data()));           infileCat_.push_back(kPlotWZ);

    infileName_.push_back(Form("%sDiboson_zz.root" ,filesPath.Data()));           infileCat_.push_back(kPlotZZ);

    infileName_.push_back(Form("%sWJets_ht100to200.root" ,filesPath.Data()));     infileCat_.push_back(kPlotWJ);
    infileName_.push_back(Form("%sWJets_ht200to400.root" ,filesPath.Data()));     infileCat_.push_back(kPlotWJ);
    infileName_.push_back(Form("%sWJets_ht400to600.root" ,filesPath.Data()));     infileCat_.push_back(kPlotWJ);
    infileName_.push_back(Form("%sWJets_ht600to800.root" ,filesPath.Data()));     infileCat_.push_back(kPlotWJ);
    infileName_.push_back(Form("%sWJets_ht800to1200.root" ,filesPath.Data()));    infileCat_.push_back(kPlotWJ);
    infileName_.push_back(Form("%sWJets_ht1200to2500.root" ,filesPath.Data()));   infileCat_.push_back(kPlotWJ);
    infileName_.push_back(Form("%sWJets_ht2500toinf.root" ,filesPath.Data()));    infileCat_.push_back(kPlotWJ);
    infileName_.push_back(Form("%sWJets_EWKWPlus.root" ,filesPath.Data()));       infileCat_.push_back(kPlotWJ);
    infileName_.push_back(Form("%sWJets_EWKWMinus.root" ,filesPath.Data()));      infileCat_.push_back(kPlotWJ);

    infileName_.push_back(Form("%sZJets_ht100to200.root" ,filesPath.Data()));     infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZJets_ht200to400.root" ,filesPath.Data()));     infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZJets_ht400to600.root" ,filesPath.Data()));     infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZJets_ht600to800.root" ,filesPath.Data()));     infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZJets_ht800to1200.root" ,filesPath.Data()));    infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZJets_ht1200to2500.root" ,filesPath.Data()));   infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZJets_ht2500toinf.root" ,filesPath.Data()));    infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZJets_EWK.root" ,filesPath.Data()));                infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZtoNuNu_ht100to200_CP5.root" ,filesPath.Data()));   infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZtoNuNu_ht200to400_CP5.root" ,filesPath.Data()));   infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZtoNuNu_ht400to600_CP5.root" ,filesPath.Data()));   infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZtoNuNu_ht600to800_CP5.root" ,filesPath.Data()));   infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZtoNuNu_ht800to1200_CP5.root" ,filesPath.Data()));  infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZtoNuNu_ht1200to2500_CP5.root" ,filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZtoNuNu_ht2500toinf_CP5.root" ,filesPath.Data()));  infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sZtoNuNu_EWK.root" ,filesPath.Data()));              infileCat_.push_back(kPlotDY);

    infileName_.push_back(Form("%sTTbar_GJets.root" ,filesPath.Data()));          infileCat_.push_back(kPlotTop);
    //infileName_.push_back(Form("%sSingleTop_tG.root" ,filesPath.Data()));         infileCat_.push_back(kPlotTop);

    infileName_.push_back(Form("%sWZG.root" ,filesPath.Data()));		      infileCat_.push_back(kPlotVVV);

    //infileName_.push_back(Form("%sWGtoLNuG_nlo.root" ,filesPath.Data())); 	      infileCat_.push_back(kPlotWG);

    infileName_.push_back(Form("%sZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root" ,filesPath.Data())); infileCat_.push_back(kPlotZG);

    infileName_.push_back(Form("%sGJets_ht100to200.root" ,filesPath.Data()));     infileCat_.push_back(kPlotGJ);
    infileName_.push_back(Form("%sGJets_ht200to400.root" ,filesPath.Data()));     infileCat_.push_back(kPlotGJ);
    infileName_.push_back(Form("%sGJets_ht400to600.root" ,filesPath.Data()));     infileCat_.push_back(kPlotGJ);
    infileName_.push_back(Form("%sGJets_ht600toinf.root" ,filesPath.Data()));     infileCat_.push_back(kPlotGJ);

    infileName_.push_back(Form("%sDarkPhotonVBFHM%d.root" ,filesPath.Data(),mH));     infileCat_.push_back(kPlotBSM);
  }
  else {
    return;
  }

  //infileName_.clear();infileCat_.clear();
  //infileName_.push_back(Form("%sDarkPhotonVBFHM%d.root" ,filesPath.Data(),mH));     infileCat_.push_back(kPlotBSM);

  TFile *fLepton_Fakes = TFile::Open(fLepton_FakesName.Data());
  TH2D* histoFakeEffSelMediumEtaPt_m = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_2_0"); histoFakeEffSelMediumEtaPt_m->SetDirectory(0);
  TH2D* histoFakeEffSelMediumEtaPt_e = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_0_1"); histoFakeEffSelMediumEtaPt_e->SetDirectory(0);
  TH2D* histoFakeEffSelTightEtaPt_m  = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_2_0"); histoFakeEffSelTightEtaPt_m ->SetDirectory(0);
  TH2D* histoFakeEffSelTightEtaPt_e  = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_0_1"); histoFakeEffSelTightEtaPt_e ->SetDirectory(0);

  TFile *fLepton_Eff = TFile::Open(effSFPath.Data());
  TH2D* histoLepEffSelMediumEtaPt_m = (TH2D*)fLepton_Eff->Get("histoEffSFStudy_2_0"); histoLepEffSelMediumEtaPt_m->SetDirectory(0);
  TH2D* histoLepEffSelMediumEtaPt_e = (TH2D*)fLepton_Eff->Get("histoEffSFStudy_0_1"); histoLepEffSelMediumEtaPt_e->SetDirectory(0);
  TH2D* histoLepEffSelTightEtaPt_m  = (TH2D*)fLepton_Eff->Get("histoEffSFStudy_2_0"); histoLepEffSelTightEtaPt_m ->SetDirectory(0);   
  TH2D* histoLepEffSelTightEtaPt_e  = (TH2D*)fLepton_Eff->Get("histoEffSFStudy_0_1"); histoLepEffSelTightEtaPt_e ->SetDirectory(0);
  fLepton_Eff->Close();

  TFile *fPUFile = TFile::Open(Form("%s",puPath.Data()));
  TH1D *fhDPU     = (TH1D*)(fPUFile->Get("puWeights"));     assert(fhDPU);     fhDPU    ->SetDirectory(0);
  TH1D *fhDPUUp   = (TH1D*)(fPUFile->Get("puWeightsUp"));   assert(fhDPUUp);   fhDPUUp  ->SetDirectory(0);
  TH1D *fhDPUDown = (TH1D*)(fPUFile->Get("puWeightsDown")); assert(fhDPUDown); fhDPUDown->SetDirectory(0);
  delete fPUFile;

  TFile *fPhotonSF = TFile::Open(photonSFPath.Data());
  TH2D *fhDPhotonSF       = (TH2D*)(fPhotonSF->Get("EGamma_SF2D")); assert(fhDPhotonSF); fhDPhotonSF->SetDirectory(0);
  TH2D *fhDElectronVetoSF = (TH2D*)(fPhotonSF->Get("Scaling_Factors_HasPix_R9 Inclusive")); assert(fhDElectronVetoSF); fhDElectronVetoSF->SetDirectory(0);
  delete fPhotonSF;

  TFile *fElePhoSF = TFile::Open(elephoSFPath.Data());
  TH2D *fhDElePhoSF    = (TH2D*)(fElePhoSF->Get("histoLGSF"));    assert(fhDElePhoSF);    fhDElePhoSF  ->SetDirectory(0);
  TH2D *fhDElePhoEffda = (TH2D*)(fElePhoSF->Get("histoLGEffda")); assert(fhDElePhoEffda); fhDElePhoEffda->SetDirectory(0);
  delete fElePhoSF;

  const int nBinMVA1D = 15; Double_t xbins1D[nBinMVA1D+1] = {0, 25, 50, 75, 100, 125, 150, 175, 200, 250, 300, 400, 500, 600, 800, 1000};

  const int nTheCategories = 2;
  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 10;
  TH1D* histo[allPlots][nTheCategories];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    bool is1DMT = false;
    if     (thePlot >=   0 && thePlot <=   1) {nBinPlot = 10;   xminPlot =30.0; xmaxPlot = 430;}
    else if(thePlot >=   2 && thePlot <=   3) {nBinPlot =  5;  xminPlot =  0.0; xmaxPlot = 2.5;}
    else if(thePlot >=   4 && thePlot <=   5) {nBinPlot = 40;  xminPlot =ptMin; xmaxPlot = 400.0;}
    else if(thePlot >=   6 && thePlot <=   7) {nBinPlot =  5;  xminPlot =500.0; xmaxPlot = 2500;}
    else if(thePlot >=   8 && thePlot <=   9) {nBinPlot =  5;  xminPlot =  3.0; xmaxPlot = 8;}
    for(int i=0; i<nTheCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinPlot, xminPlot, xmaxPlot);
  }
  TH1D* hDTrgSF[5];
  for(int thePlot=0; thePlot<5; thePlot++){
    if     (thePlot >=   0 && thePlot <=   0) {nBinPlot = 10;   xminPlot =30.0; xmaxPlot = 430;}
    else if(thePlot >=   1 && thePlot <=   1) {nBinPlot =  5;  xminPlot =  0.0; xmaxPlot = 2.5;}
    else if(thePlot >=   2 && thePlot <=   2) {nBinPlot = 40;  xminPlot =ptMin; xmaxPlot = 400.0;}
    else if(thePlot >=   3 && thePlot <=   3) {nBinPlot =  5;  xminPlot =500.0; xmaxPlot = 2500;}
    else if(thePlot >=   4 && thePlot <=   4) {nBinPlot =  5;  xminPlot =  3.0; xmaxPlot = 8;}
    hDTrgSF[thePlot] = new TH1D(Form("hDTrgSF_%d",thePlot), Form("hDTrgSF_%d",thePlot), nBinPlot, xminPlot, xmaxPlot);
  }

  //*******************************************************
  // Chain Loop
  //*******************************************************
  for(UInt_t ifile=0; ifile<infileName_.size(); ifile++) {
    printf("sampleNames(%d): %s\n",ifile,infileName_[ifile].Data());
    TFile *the_input_file = TFile::Open(infileName_[ifile].Data());
    TTree *the_input_tree = (TTree*)the_input_file->FindObjectAny("events");

    double srYields[4]  = {0., 0., 0., 0.};
    double srYieldsE[4] = {0., 0., 0., 0.};
    pandaFlat thePandaFlat(the_input_tree);
    double theMCPrescale = 1.0; if(infileCat_[ifile] != kPlotData) theMCPrescale = mcPrescale;
    Long64_t nentries = thePandaFlat.fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = thePandaFlat.LoadTree(jentry);
      if (ientry < 0) break;
      nb = thePandaFlat.fChain->GetEntry(jentry);   nbytes += nb;
      if (jentry%1000000 == 0) printf("--- reading event %8lld (%8lld) of %8lld\n",jentry,ientry,nentries);
      if (infileCat_[ifile] != 0 && jentry%(int)theMCPrescale != 0) continue;

      bool passTrigger = (thePandaFlat.trigger & (1<<kSingleMuTrig)) != 0;
      if(passTrigger == false) continue;
      if(thePandaFlat.metFilter == 0) continue;

      if(thePandaFlat.nLooseLep != 1) continue;

      TLorentzVector vFakePhoton,vPhoton,vPhotonUp,vPhotonDown;
      bool passPhoSel = TMath::Abs(thePandaFlat.loosePho1Eta) < 2.5
             && (thePandaFlat.loosePho1SelBit & pMedium) == pMedium
	     && (thePandaFlat.loosePho1SelBit & pCsafeVeto) == pCsafeVeto
	     && (thePandaFlat.loosePho1SelBit & pPixelVeto) == pPixelVeto;
      if(passPhoSel == true) {
        vPhoton.SetPtEtaPhiM(thePandaFlat.loosePho1Pt, thePandaFlat.loosePho1Eta, thePandaFlat.loosePho1Phi, 0);
	if(vPhoton.Pt() <= ptMin) passPhoSel = false;
      }

      vector<float>  looseLepPt,looseLepEta,looseLepPhi,looseLepSF,looseLepIso;
      vector<int> looseLepSelBit,looseLepPdgId,looseLepTripleCharge,looseLepMissingHits;
      int ptSelCuts[1] = {0};
      for(int i=0; i<thePandaFlat.nLooseMuon; i++){
        looseLepPt.push_back(thePandaFlat.muonPt[i]);
        looseLepEta.push_back(thePandaFlat.muonEta[i]);
        looseLepPhi.push_back(thePandaFlat.muonPhi[i]);
        looseLepSF.push_back(thePandaFlat.muonSfReco[i] * thePandaFlat.muonSfTight[i]);
        looseLepSelBit.push_back(thePandaFlat.muonSelBit[i]);
        looseLepPdgId.push_back(thePandaFlat.muonPdgId[i]);
        looseLepTripleCharge.push_back(1);
        looseLepMissingHits.push_back(0);
        looseLepIso.push_back(thePandaFlat.muonCombIso[i]);
	if(looseLepPt[looseLepPt.size()-1] > 30) ptSelCuts[0]++;
      }
      for(int i=0; i<thePandaFlat.nLooseElectron; i++){
        looseLepPt.push_back(thePandaFlat.electronPt[i]);
        looseLepEta.push_back(thePandaFlat.electronEta[i]);
        looseLepPhi.push_back(thePandaFlat.electronPhi[i]);
        looseLepSelBit.push_back(thePandaFlat.electronSelBit[i]);
        looseLepSF.push_back(thePandaFlat.electronSfReco[i] * thePandaFlat.electronSfMedium[i]);
        looseLepPdgId.push_back(thePandaFlat.electronPdgId[i]);
        looseLepTripleCharge.push_back(thePandaFlat.electronTripleCharge[i]);
        looseLepMissingHits.push_back(thePandaFlat.electronNMissingHits[i]);
        looseLepIso.push_back(thePandaFlat.electronCombIso[i]);
	if(looseLepPt[looseLepPt.size()-1] > 30) ptSelCuts[0]++;
      }

      if(ptSelCuts[0] != 1) continue;

      if((int)looseLepPt.size() != thePandaFlat.nLooseLep) printf("IMPOSSIBLE\n");

      int theCategory = infileCat_[ifile];
      if(theCategory != kPlotData) theCategory = 1;
      vector<TLorentzVector> vLoose;
      vector<int> idLep;
      bool passLooseLepId = true;
      int qTot = 0;
      unsigned int countLeptonTight = 0;
      for(int i=0; i<thePandaFlat.nLooseLep; i++) {
        idLep.push_back(0);
        if     (abs(looseLepPdgId[i])==13 && (looseLepSelBit[i] & kTight)  == kTight  && (looseLepSelBit[i] & kDxyz)  == kDxyz) idLep[i] = 1;
        else if(abs(looseLepPdgId[i])==11 && (looseLepSelBit[i] & kMedium) == kMedium) idLep[i] = 1;
	countLeptonTight = countLeptonTight + (idLep[i] > 0);

        double thePDGMass = mass_mu;
        if(abs(looseLepPdgId[i])==11) thePDGMass = mass_el;
	TLorentzVector vLepTemp; vLepTemp.SetPtEtaPhiM(looseLepPt[i],looseLepEta[i],looseLepPhi[i],thePDGMass);
        vLoose.push_back(vLepTemp);

	qTot = qTot + abs(looseLepPdgId[i])/looseLepPdgId[i];

        passLooseLepId = passLooseLepId && ((looseLepSelBit[i] & kFake) == kFake);
      }

      int lepType = -1; double muSFUnc = 1.0; double elSFUnc = 1.0;
      if     (thePandaFlat.nLooseLep == 1){
        if     (abs(looseLepPdgId[0])==13) {lepType = 0; muSFUnc = 1.015;}
        else if(abs(looseLepPdgId[0])==11) {lepType = 1; elSFUnc = 1.015;}
      }

      TLorentzVector vMet;
      vMet    .SetPtEtaPhiM(thePandaFlat.pfmet,0.0,thePandaFlat.pfmetphi,0.0);

      if(usePureMC == true && countLeptonTight != idLep.size()) continue;

      TLorentzVector theG = vPhoton;

      bool passMET = vMet.Pt() > 30;

      bool passNjets = thePandaFlat.nJot >= 2 && thePandaFlat.jotPt[0] > 50 && thePandaFlat.jotPt[1] > 50;
      TLorentzVector vJot1; vJot1.SetPtEtaPhiM(thePandaFlat.jotPt[0],thePandaFlat.jotEta[0],thePandaFlat.jotPhi[0],0.0);
      TLorentzVector vJot2; vJot2.SetPtEtaPhiM(thePandaFlat.jotPt[1],thePandaFlat.jotEta[1],thePandaFlat.jotPhi[1],0.0);

      double massJJ     = (vJot1+vJot2).M();
      double deltaEtaJJ = TMath::Abs(vJot1.Eta()-vJot2.Eta());

      bool passMJJ    = thePandaFlat.nJot >= 2 && massJJ > 500;
      bool passDEtaJJ = thePandaFlat.nJot >= 2 && deltaEtaJJ > 3.0 && vJot1.Eta()*vJot2.Eta() < 0;

      bool passWln = passMET && lepType == 0;
      bool passWlng = passWln && passPhoSel && TMath::Abs(theG.DeltaPhi(vLoose[0])) > 0.1;
      bool passWlnvbfg = passWlng && passNjets && passMJJ && passDEtaJJ;

      bool passVBFTrigger = (thePandaFlat.trigger & (1<<kVBFPhoTrig)) != 0;

      double photonSFUnc[3] = {1.0, 1.0, 1.0};
      double totalWeight = 1.0; double puWeight = 1.0; double puWeightUp = 1.0; double puWeightDown = 1.0; double sf_l1PrefireE = 1.0;
      double triggerWeights[2] = {1.0, 0.0};
      if(theCategory != kPlotData){
	puWeight     = nPUScaleFactor(fhDPU,    thePandaFlat.pu);
        puWeightUp   = nPUScaleFactor(fhDPUUp,  thePandaFlat.pu);
        puWeightDown = nPUScaleFactor(fhDPUDown,thePandaFlat.pu);

        sf_l1PrefireE = 1.0 + TMath::Abs(1.0 - thePandaFlat.sf_l1Prefire) * 0.2;

	//double npvWeight = nPUScaleFactor(fhDNPV, thePandaFlat.npv);

        totalWeight = thePandaFlat.normalizedWeight * lumiV[whichYear] * 1000 * puWeight * thePandaFlat.sf_l1Prefire * triggerWeights[0] * theMCPrescale;

        for(unsigned int nl=0; nl<idLep.size(); nl++) totalWeight = totalWeight * looseLepSF[nl];

        if     (infileCat_[ifile] == kPlotWZ)                                                totalWeight = totalWeight * thePandaFlat.sf_wz;
	else if(infileCat_[ifile] == kPlotZZ && infileName_[ifile].Contains("qqZZ") == true) totalWeight = totalWeight * thePandaFlat.sf_zz;

        if(theCategory != kPlotData){
          totalWeight = totalWeight * mcCorrection(0, year, infileCat_[ifile]);
        }

	if(passPhoSel == true) {
          double photonSF = 1.0;
          if     (thePandaFlat.looseGenPho1PdgId == 1) {
	    int nxbin = fhDElePhoSF->GetXaxis()->FindBin(TMath::Abs(vPhoton.Eta()));
	    int nybin = fhDElePhoSF->GetYaxis()->FindBin(TMath::Min((double)vPhoton.Pt(), 124.999));
            photonSF = fhDElePhoSF->GetBinContent(nxbin, nybin);
	    photonSFUnc[2] = (photonSF+fhDElePhoSF->GetBinError(nxbin, nybin))/photonSF;
	  }
          else if(thePandaFlat.looseGenPho1PdgId == 3) {
            photonSF = effhDPhotonScaleFactor(vPhoton.Pt(), vPhoton.Eta(), "medium", fhDPhotonSF, fhDElectronVetoSF); photonSFUnc[0] = 1.02;
	  }
          else {
            photonSF = 1.0; photonSFUnc[1] = 1.10;
	  }
	  totalWeight = totalWeight * photonSF;
	}

        double effSF = 1.0;
        for(unsigned int nl=0; nl<idLep.size(); nl++){
          if(idLep[nl] == 0) continue;
          bool applyTight = false;
          effSF = effSF * lepScaleFactor(vLoose[nl].Pt(),vLoose[nl].Eta(),TMath::Abs(looseLepPdgId[nl]),applyTight,histoLepEffSelMediumEtaPt_m,histoLepEffSelMediumEtaPt_e,histoLepEffSelTightEtaPt_m,histoLepEffSelTightEtaPt_e);
          if(effSF == 0){printf("effSF == 0!: %f %f %d \n",vLoose[nl].Pt(),vLoose[nl].Eta(),TMath::Abs(looseLepPdgId[nl])); return;}
        }
        totalWeight = totalWeight * effSF;
      }

      if(usePureMC == false && countLeptonTight != idLep.size()){
        double fakeSF = 1.0;
        for(unsigned int nl=0; nl<idLep.size(); nl++){
          if(idLep[nl] == 1) continue;
          bool applyTight = false;
          fakeSF = fakeSF * fakeRateFactor(TMath::Min((double)vLoose[nl].Pt(),44.999),TMath::Abs(vLoose[nl].Eta()),TMath::Abs(looseLepPdgId[nl]),applyTight,histoFakeEffSelMediumEtaPt_m,histoFakeEffSelMediumEtaPt_e,histoFakeEffSelTightEtaPt_m,histoFakeEffSelTightEtaPt_e);
          theCategory = kPlotNonPrompt;
        }
        if     (infileCat_[ifile] != kPlotData && countLeptonTight == idLep.size()-4) fakeSF = +1.0 * fakeSF; // fourth fake, MC
        else if(infileCat_[ifile] != kPlotData && countLeptonTight == idLep.size()-3) fakeSF = -1.0 * fakeSF; // triple fake, MC
        else if(infileCat_[ifile] != kPlotData && countLeptonTight == idLep.size()-2) fakeSF = +1.0 * fakeSF; // double fake, MC
        else if(infileCat_[ifile] != kPlotData && countLeptonTight == idLep.size()-1) fakeSF = -1.0 * fakeSF; // single fake, MC
        else if(infileCat_[ifile] == kPlotData && countLeptonTight == idLep.size()-4) fakeSF = -1.0 * fakeSF; // fourth fake, data
        else if(infileCat_[ifile] == kPlotData && countLeptonTight == idLep.size()-3) fakeSF = +1.0 * fakeSF; // triple fake, data
        else if(infileCat_[ifile] == kPlotData && countLeptonTight == idLep.size()-2) fakeSF = -1.0 * fakeSF; // double fake, data
        else if(infileCat_[ifile] == kPlotData && countLeptonTight == idLep.size()-1) fakeSF = +1.0 * fakeSF; // single fake, data
        else printf("IMPOSSIBLE FAKE OPTION\n");
        totalWeight = totalWeight * fakeSF;
      }

      if(passWlng) histo[ 0][theCategory]->Fill(TMath::Min(vMet.Pt(),429.999),totalWeight);
      if(passWlng) histo[ 2][theCategory]->Fill(TMath::Abs(theG.Eta()),totalWeight);
      if(passWlng) histo[ 4][theCategory]->Fill(TMath::Min(theG.Pt(),399.999),totalWeight);
      if(passWlnvbfg) histo[ 6][theCategory]->Fill(TMath::Min(massJJ,2499.999),totalWeight);
      if(passWlnvbfg) histo[ 8][theCategory]->Fill(TMath::Min(deltaEtaJJ,7.999),totalWeight);
      if(passWlng && passVBFTrigger) histo[ 1][theCategory]->Fill(TMath::Min(vMet.Pt(),499.999),totalWeight);
      if(passWlng && passVBFTrigger) histo[ 3][theCategory]->Fill(TMath::Abs(theG.Eta()),totalWeight);
      if(passWlng && passVBFTrigger) histo[ 5][theCategory]->Fill(TMath::Min(theG.Pt(),399.999),totalWeight);
      if(passWlnvbfg && passVBFTrigger) histo[ 7][theCategory]->Fill(TMath::Min(massJJ,2499.999),totalWeight);
      if(passWlnvbfg && passVBFTrigger) histo[ 9][theCategory]->Fill(TMath::Min(deltaEtaJJ,7.999),totalWeight);

    } // end events loop
    the_input_file->Close();
  } // end chain loop

  // Writing standard histograms
  char output[200];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    sprintf(output,"histoTriggerVBFG_%d_%d.root",year,thePlot);	
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    double totBck = 0;
    for(int i=1; i<nTheCategories; i++) if(histo[thePlot][i]->GetSumOfWeights() < 0) histo[thePlot][i]->Scale(0.0);
    for(int i=1; i<nTheCategories; i++) if(i != kPlotBSM) totBck = totBck + histo[thePlot][i]->GetSumOfWeights();
    printf("(%2d) %7.1f vs. %7.1f ",thePlot,histo[thePlot][0]->GetSumOfWeights(),totBck);
    printf("(");
    for(int i=1; i<nTheCategories; i++) printf("%7.1f ",histo[thePlot][i]->GetSumOfWeights());
    printf(")\n");
    for(int np=0; np<nTheCategories; np++) {histo[thePlot][np]->SetNameTitle(Form("histo%d",np),Form("histo%d",np));histo[thePlot][np]->Write();}
    outFilePlotsNote->Close();
  }

  sprintf(output,"histoTriggerSFVBFG_%d.root",year); 
  TFile* outFilePlotsNote = new TFile(output,"recreate");
  outFilePlotsNote->cd();
  double eff[2], unc[2];
  for(int nb=0; nb<5; nb++){
    for(int npt=1; npt<=histo[2*nb][0]->GetNbinsX(); npt++){
      for(int i=0; i<2; i++){ 
        eff[i] = 1; unc[i] = 0.0;
        if(histo[2*nb][i]->GetBinContent(npt) > 0) {
          eff[i] = TMath::Min(histo[2*nb+1][i]->GetBinContent(npt)/histo[2*nb][i]->GetBinContent(npt),1.0);
          unc[i] = sqrt(eff[i]*(1-eff[i])/histo[2*nb][i]->GetBinContent(npt))/5.0;
          if(eff[i] == 0 || eff[i] == 1) unc[i] = 1./sqrt(histo[2*nb][i]->GetBinContent(npt))/5.0;
        }
      }
      hDTrgSF[nb]->SetBinContent(npt,eff[0]/eff[1]);
      hDTrgSF[nb]->SetBinError(npt,eff[0]/eff[1]*sqrt(unc[0]/eff[0]*unc[0]/eff[0]+unc[1]/eff[1]*unc[1]/eff[1]));
      printf("(%2d %2d) %.3f +/- %.3f | %.3f +/- %.3f = %.3f +/- %.3f\n",nb,npt,eff[0],unc[0],eff[1],unc[1],hDTrgSF[nb]->GetBinContent(npt),hDTrgSF[nb]->GetBinError(npt));
    }
    hDTrgSF[nb]->Write();
  }
  outFilePlotsNote->Close();
}
