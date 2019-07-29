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

const bool isSingleLeptonAna = false;
const bool isDEBUG = false;
const bool showSyst = true;
const unsigned int period = 0;
const double mcPrescale = 1;
const bool usePureMC = true; // if true, passLooseLepId not applied
enum selType                     { VBFGSEL,   LGSEL,   LLGSEL,   LSEL,   GJSEL, nSelTypes};
TString selTypeName[nSelTypes]=  {"VBFGSEL", "LGSEL", "LLGSEL", "LSEL", "GJSEL"};
enum systType                     {JESUP=0, JESDOWN, nSystTypes};
TString systTypeName[nSystTypes]= {"JESUP","JESDOWN"};

const double pdfUncs[2] = {1.010, 1.016};

void vbfgAnalysis(
int year, int mH = 125
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
  TString fLepton_FakesName = Form("MitAnalysisRunII/data/90x/histoFakeEtaPt_%d.root",year);
  TString puPath;
  TString photonSFPath;
  TString elephoSFPath = Form("MitAnalysisRunII/data/90x/histoDY0LGSF_%d.root",year);
  TString trgSFPath = Form("MitAnalysisRunII/data/10x_g/histoTriggerSFVBFG_%d.root",year);
  TString effSFPath = Form("MitAnalysisRunII/data/90x/histoDY0EffSFStudy_%d.root",year);
  //TString npvPath = Form("MitAnalysisRunII/data/90x/npvWeights_%d.root",year);
  if(year == 2018) {
    filesPath = Form("/scratch5/bmaier/darkg/2018/vbfg_v_013_v6/");
    puPath = "MitAnalysisRunII/data/90x/puWeights_90x_2018.root";
    photonSFPath = "MitAnalysisRunII/data/90x/2018_PhotonsMedium.root";

    infileName_.push_back(Form("%sdata.root","/data/t3home000/ceballos/panda/v_vbfg_2018_0/")); infileCat_.push_back(kPlotData);

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
    infileName_.push_back(Form("%sZtoNuNu_EWK_CP5.root" ,filesPath.Data()));          infileCat_.push_back(kPlotDY);

    infileName_.push_back(Form("%sTTbar_GJets_CP5.root" ,filesPath.Data()));          infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sSingleTop_tG_CP5.root" ,filesPath.Data()));         infileCat_.push_back(kPlotTop);

    infileName_.push_back(Form("%sWZG.root" ,filesPath.Data()));		      infileCat_.push_back(kPlotVVV);

    infileName_.push_back(Form("%sWGtoLNuG_nlo.root" ,filesPath.Data())); 	      infileCat_.push_back(kPlotWG);

    infileName_.push_back(Form("%sZGTo2LG_nlo.root" ,filesPath.Data())); 	      infileCat_.push_back(kPlotZG);

    infileName_.push_back(Form("%sGJets_ht100to200_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotGJ);
    infileName_.push_back(Form("%sGJets_ht200to400_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotGJ);
    infileName_.push_back(Form("%sGJets_ht400to600_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotGJ);
    infileName_.push_back(Form("%sGJets_ht600toinf_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotGJ);

    infileName_.push_back(Form("%sDarkPhotonVBFHM%d.root" ,filesPath.Data(),mH));     infileCat_.push_back(kPlotBSM);
  }
  else if(year == 2017) {
    filesPath = Form("/scratch5/bmaier/darkg/2017/vbfg_v_012_v5/");
    puPath = "MitAnalysisRunII/data/90x/puWeights_90x_2017.root";
    photonSFPath = "MitAnalysisRunII/data/90x/egammaEffi.txt_EGM2D_runBCDEF_passingMedium94X.root";

    infileName_.push_back(Form("%sdata.root","/data/t3home000/ceballos/panda/v_vbfg_2017_0/")); infileCat_.push_back(kPlotData);

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

    infileName_.push_back(Form("%sDarkPhotonVBFHM%d.root" ,filesPath.Data(),mH));     infileCat_.push_back(kPlotBSM);
  }
  else if(year == 2016) {
    filesPath = Form("");
    puPath = "MitAnalysisRunII/data/80x/puWeights_80x_37ifb.root";
    photonSFPath = "MitAnalysisRunII/data/80x/photon_scalefactors_37ifb.root";

  }
  else {
    return;
  }

  //infileName_.clear();infileCat_.clear();
  //infileName_.push_back(Form("%sDarkPhotonVBFHM%d.root" ,filesPath.Data(),mH));     infileCat_.push_back(kPlotBSM);
  //infileName_.push_back(Form("%sGJets_ht100to200_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotGJ);
  //infileName_.push_back(Form("%sGJets_ht200to400_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotGJ);
  //infileName_.push_back(Form("%sGJets_ht400to600_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotGJ);
  //infileName_.push_back(Form("%sGJets_ht600toinf_CP5.root" ,filesPath.Data()));     infileCat_.push_back(kPlotGJ);

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

  TFile *ftrgSF = TFile::Open(trgSFPath.Data());
  TH1D *trgSF = (TH1D*)(ftrgSF->Get("hDTrgSF_2")); assert(trgSF); trgSF->SetDirectory(0);
  delete ftrgSF;

  // 0: SR (mjj<=1100), 1: passLGSel, 2: passLLGSel, 3: passLSel, 4: passGJSel, 5: SR (mjj>1100)
  const int nBinMVA1D = 7; Double_t xbins1D[nBinMVA1D+1] = {0, 40, 80, 120, 160, 200, 300, 1000};
  const int nBinMVA = nBinMVA1D*6; Double_t xbins[nBinMVA+1];
  for(int chan=0; chan<7; chan++) for(int i=0; i<=nBinMVA1D; i++) xbins[i+nBinMVA1D*chan] = xbins1D[i] + 1000*chan;
  //for(int chan=0; chan<7; chan++) for(int i=0; i<=nBinMVA1D; i++) printf("BinMVA(%2d): %f\n",i+nBinMVA1D*chan,xbins[i+nBinMVA1D*chan]);

  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 86;
  TH1D* histo[allPlots][nPlotCategories];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    bool is1DMT = false;
    if     (thePlot >=   0 && thePlot <=   4) {is1DMT = true;}
    //if     (thePlot >=   0 && thePlot <=   4) {nBinPlot =100;  xminPlot =  0.0; xmaxPlot = 1000;}
    else if(thePlot >=   5 && thePlot <=   9) {nBinPlot = 50;  xminPlot =  0.0; xmaxPlot = 500;}
    else if(thePlot >=  10 && thePlot <=  14) {nBinPlot = 5;   xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >=  15 && thePlot <=  19) {nBinPlot = 24;  xminPlot =  0.0; xmaxPlot = 3.0;}
    else if(thePlot >=  20 && thePlot <=  24) {nBinPlot = 40;  xminPlot =  0.0; xmaxPlot = 2000;}
    else if(thePlot >=  25 && thePlot <=  29) {nBinPlot = 40;  xminPlot =  0.0; xmaxPlot = 8;}
    else if(thePlot >=  30 && thePlot <=  34) {nBinPlot = 8;   xminPlot = -0.5; xmaxPlot = 7.5;}
    else if(thePlot >=  35 && thePlot <=  39) {nBinPlot = 4;   xminPlot = -0.5; xmaxPlot = 3.5;}
    else if(thePlot >=  40 && thePlot <=  44) {nBinPlot = 4;   xminPlot = -0.5; xmaxPlot = 3.5;}
    else if(thePlot >=  45 && thePlot <=  49) {nBinPlot = 25;  xminPlot =  0.0; xmaxPlot = 2.5;}
    else if(thePlot >=  50 && thePlot <=  54) {nBinPlot = 50;  xminPlot = 80.0; xmaxPlot = 480.0;}
    else if(thePlot >=  55 && thePlot <=  59) {nBinPlot = 24;  xminPlot =  0.0; xmaxPlot = 3.0;}
    else if(thePlot >=  60 && thePlot <=  64) {nBinPlot = 50;  xminPlot =  0.0; xmaxPlot = 5.0;}
    else if(thePlot >=  65 && thePlot <=  69) {nBinPlot = 30;  xminPlot =  0.0; xmaxPlot = 3.0;}
    else if(thePlot >=  70 && thePlot <=  74) {nBinPlot = 40;  xminPlot =  0.0; xmaxPlot = 1.0;}
    else if(thePlot >=  75 && thePlot <=  84) {nBinPlot = 10;  xminPlot =  0.0; xmaxPlot = 5.0;}
    if     (thePlot == allPlots-1) for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinMVA, xbins);
    else if(is1DMT == true)        for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinMVA1D, xbins1D);
    else                           for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinPlot, xminPlot, xmaxPlot);
  }

  TH1D* histo_MVA = new TH1D("histo_MVA", "histo_MVA", nBinMVA, xbins); histo_MVA->Sumw2();

  TH1D *histo_Baseline[nPlotCategories];
  TH1D *histo_QCDScaleBounding[nPlotCategories][6];
  TH1D *histo_QCDScaleUp[nPlotCategories];
  TH1D *histo_QCDScaleDown[nPlotCategories];
  TH1D *histo_PDFBoundingUp[nPlotCategories];
  TH1D *histo_PDFBoundingDown[nPlotCategories];
  TH1D *histo_LepEffMBoundingUp[nPlotCategories];
  TH1D *histo_LepEffMBoundingDown[nPlotCategories];
  TH1D *histo_LepEffEBoundingUp[nPlotCategories];
  TH1D *histo_LepEffEBoundingDown[nPlotCategories];
  TH1D *histo_ScaleMBoundingUp[nPlotCategories];
  TH1D *histo_ScaleMBoundingDown[nPlotCategories];
  TH1D *histo_ScaleEBoundingUp[nPlotCategories];
  TH1D *histo_ScaleEBoundingDown[nPlotCategories];
  TH1D *histo_ScaleGBoundingUp[nPlotCategories];
  TH1D *histo_ScaleGBoundingDown[nPlotCategories];
  TH1D *histo_PUBoundingUp[nPlotCategories];
  TH1D *histo_PUBoundingDown[nPlotCategories];
  TH1D *histo_BTAGBBoundingUp[nYears][nPlotCategories];
  TH1D *histo_BTAGBBoundingDown[nYears][nPlotCategories];
  TH1D *histo_BTAGLBoundingUp[nYears][nPlotCategories];
  TH1D *histo_BTAGLBoundingDown[nYears][nPlotCategories];
  TH1D *histo_JESBoundingUp[nYears][nPlotCategories];
  TH1D *histo_JESBoundingDown[nYears][nPlotCategories];
  TH1D *histo_PreFireBoundingUp[nYears][nPlotCategories];
  TH1D *histo_PreFireBoundingDown[nYears][nPlotCategories];
  TH1D *histo_TriggerBoundingUp[nYears][nPlotCategories];
  TH1D *histo_TriggerBoundingDown[nYears][nPlotCategories];
  TH1D *histo_PhoEffBoundingUp[nPlotCategories];
  TH1D *histo_PhoEffBoundingDown[nPlotCategories];
  TH1D *histo_PhoFakeBoundingUp[nPlotCategories];
  TH1D *histo_PhoFakeBoundingDown[nPlotCategories];
  TH1D *histo_ElToPhRateBoundingUp[nPlotCategories];
  TH1D *histo_ElToPhRateBoundingDown[nPlotCategories];
  TH1D *histo_EWKCorrWZUp[nPlotCategories];
  TH1D *histo_EWKCorrWZDown[nPlotCategories];
  TH1D *histo_EWKqqZZCorrUp[nPlotCategories];
  TH1D *histo_EWKqqZZCorrDown[nPlotCategories];
  TH1D *histo_ggZZCorrUp[nPlotCategories];
  TH1D *histo_ggZZCorrDown[nPlotCategories];
  
  for(unsigned ic=kPlotData; ic!=nPlotCategories; ic++) {
    for(int i=0; i<6; i++)  histo_QCDScaleBounding[ic][i] = (TH1D*)histo_MVA->Clone(Form("histo_%s_%d_QCDScaleBounding",plotBaseNames[ic].Data(),i));
    histo_Baseline              [ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s"                    , plotBaseNames[ic].Data()));
    histo_QCDScaleUp            [ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_QCDScale_%s_ACCEPTUp"         , plotBaseNames[ic].Data(), plotBaseNames[ic].Data()));
    histo_QCDScaleDown          [ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_QCDScale_%s_ACCEPTDown"       , plotBaseNames[ic].Data(), plotBaseNames[ic].Data()));
    histo_PDFBoundingUp 	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_PDFUp"              , plotBaseNames[ic].Data()));
    histo_PDFBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_PDFDown"            , plotBaseNames[ic].Data()));
    histo_LepEffMBoundingUp	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_eff_mUp"        , plotBaseNames[ic].Data()));
    histo_LepEffMBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_eff_mDown"      , plotBaseNames[ic].Data()));
    histo_LepEffEBoundingUp	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_eff_eUp"        , plotBaseNames[ic].Data()));
    histo_LepEffEBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_eff_eDown"      , plotBaseNames[ic].Data()));
    histo_ScaleMBoundingUp	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_scale_mUp"      , plotBaseNames[ic].Data()));
    histo_ScaleMBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_scale_mDown"    , plotBaseNames[ic].Data()));
    histo_ScaleEBoundingUp	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_scale_eUp"      , plotBaseNames[ic].Data()));
    histo_ScaleEBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_scale_eDown"    , plotBaseNames[ic].Data()));
    histo_ScaleGBoundingUp	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_scale_pUp"      , plotBaseNames[ic].Data()));
    histo_ScaleGBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_scale_pDown"    , plotBaseNames[ic].Data()));
    histo_PUBoundingUp		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_puUp"           , plotBaseNames[ic].Data()));
    histo_PUBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_puDown"         , plotBaseNames[ic].Data()));
    for(int ny=0; ny<nYears; ny++){
    histo_BTAGBBoundingUp    [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_btagb_%dUp"     , plotBaseNames[ic].Data(),2016+ny));
    histo_BTAGBBoundingDown  [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_btagb_%dDown"   , plotBaseNames[ic].Data(),2016+ny));
    histo_BTAGLBoundingUp    [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_btagl_%dUp"     , plotBaseNames[ic].Data(),2016+ny));
    histo_BTAGLBoundingDown  [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_btagl_%dDown"   , plotBaseNames[ic].Data(),2016+ny));
    histo_JESBoundingUp      [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_jes_%dUp"	   , plotBaseNames[ic].Data(),2016+ny));
    histo_JESBoundingDown    [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_jes_%dDown"	   , plotBaseNames[ic].Data(),2016+ny));
    histo_PreFireBoundingUp  [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_prefire_%dUp"   , plotBaseNames[ic].Data(),2016+ny));
    histo_PreFireBoundingDown[ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_prefire_%dDown" , plotBaseNames[ic].Data(),2016+ny));
    histo_TriggerBoundingUp  [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_trigger_%dUp"   , plotBaseNames[ic].Data(),2016+ny));
    histo_TriggerBoundingDown[ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_trigger_%dDown" , plotBaseNames[ic].Data(),2016+ny));
    }
    histo_PhoEffBoundingUp	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_eff_photonUp"   , plotBaseNames[ic].Data()));
    histo_PhoEffBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_eff_photonDown" , plotBaseNames[ic].Data()));
    histo_PhoFakeBoundingUp	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fake_photonUp"  , plotBaseNames[ic].Data()));
    histo_PhoFakeBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fake_photonDown", plotBaseNames[ic].Data()));
    histo_ElToPhRateBoundingUp	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fake_elUp"      , plotBaseNames[ic].Data()));
    histo_ElToPhRateBoundingDown[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fake_elDown"    , plotBaseNames[ic].Data()));
    histo_EWKCorrWZUp		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKWZCorrUp"        , plotBaseNames[ic].Data()));
    histo_EWKCorrWZDown 	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKWZCorrDown"      , plotBaseNames[ic].Data()));
    histo_EWKqqZZCorrUp 	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKqqZZCorrUp"      , plotBaseNames[ic].Data()));
    histo_EWKqqZZCorrDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKqqZZCorrDown"    , plotBaseNames[ic].Data()));
    histo_ggZZCorrUp		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_ggZZCorrUp"         , plotBaseNames[ic].Data()));
    histo_ggZZCorrDown		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_ggZZCorrDown"       , plotBaseNames[ic].Data()));
  }
  TH1D *histo_GJNorm0Up   = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_GJNorm0_%dUp"   , plotBaseNames[kPlotGJ].Data(),year));
  TH1D *histo_GJNorm0Down = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_GJNorm0_%dDown" , plotBaseNames[kPlotGJ].Data(),year));
  TH1D *histo_GJNorm1Up   = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_GJNorm1_%dUp"   , plotBaseNames[kPlotGJ].Data(),year));
  TH1D *histo_GJNorm1Down = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_GJNorm1_%dDown" , plotBaseNames[kPlotGJ].Data(),year));
  TH1D *histo_GJNorm2Up   = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_GJNorm2_%dUp"   , plotBaseNames[kPlotGJ].Data(),year));
  TH1D *histo_GJNorm2Down = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_GJNorm2_%dDown" , plotBaseNames[kPlotGJ].Data(),year));
  TH1D *histo_GJNorm3Up   = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_GJNorm3_%dUp"   , plotBaseNames[kPlotGJ].Data(),year));
  TH1D *histo_GJNorm3Down = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_GJNorm3_%dDown" , plotBaseNames[kPlotGJ].Data(),year));

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

      bool passTrigger = (thePandaFlat.trigger & (1<<kVBFPhoTrig)) != 0;
      if(passTrigger == false) continue;
      if(thePandaFlat.metFilter == 0) continue;

      if(thePandaFlat.nLooseLep > 2) continue;

      TLorentzVector vFakePhoton,vPhoton,vPhotonUp,vPhotonDown;
      bool passPhoSel = TMath::Abs(thePandaFlat.loosePho1Eta) < 2.5
             && (thePandaFlat.loosePho1SelBit & pMedium) == pMedium
	     && (thePandaFlat.loosePho1SelBit & pCsafeVeto) == pCsafeVeto
	     && (thePandaFlat.loosePho1SelBit & pPixelVeto) == pPixelVeto;
      if(passPhoSel == true) {
        vPhoton.SetPtEtaPhiM(thePandaFlat.loosePho1Pt, thePandaFlat.loosePho1Eta, thePandaFlat.loosePho1Phi, 0);
	if(vPhoton.Pt() <= ptMin) passPhoSel = false;
      }
 
      if(!passPhoSel && thePandaFlat.nLooseLep != 1) continue;

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
	if(looseLepPt[looseLepPt.size()-1] > ptMin) ptSelCuts[0]++;
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
	if(looseLepPt[looseLepPt.size()-1] > ptMin) ptSelCuts[0]++;
      }

      if(!passPhoSel && ptSelCuts[0] != 1) continue;

      if((int)looseLepPt.size() != thePandaFlat.nLooseLep) printf("IMPOSSIBLE\n");

      int theCategory = infileCat_[ifile];
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
      else if(thePandaFlat.nLooseLep == 2){
        if     (abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13) {lepType = 0; muSFUnc = 1.015*1.015;}
        else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11) {lepType = 1; elSFUnc = 1.015*1.015;}
        else  {lepType = 2; muSFUnc = 1.015; elSFUnc = 1.015;}
      }

      TLorentzVector vMet,vMetUp,vMetDown;
      vMet    .SetPtEtaPhiM(thePandaFlat.pfmet,0.0,thePandaFlat.pfmetphi,0.0);
      vMetUp  .SetPtEtaPhiM(thePandaFlat.pfmet_JESTotalUp,0.0,thePandaFlat.pfmetphi_JESTotalUp,0.0);
      vMetDown.SetPtEtaPhiM(thePandaFlat.pfmet_JESTotalDown,0.0,thePandaFlat.pfmetphi_JESTotalDown,0.0);

      if(usePureMC == true && countLeptonTight != idLep.size()) continue;

      double mLL = 91.1876;
      int theMinSelType = -1;
      TLorentzVector theG;
      if     (passPhoSel == true  && vLoose.size() == 0){       
        theMinSelType = 0;
        theG = vPhoton;
      }
      else if(passPhoSel == true  && vLoose.size() == 1){
        theMinSelType = 1;
        theG = vPhoton;
	vMet	 = vMet     + vLoose[0];
	vMetUp   = vMetUp   + vLoose[0];
	vMetDown = vMetDown + vLoose[0];
      }
      else if(passPhoSel == true  && vLoose.size() == 2 && TMath::Abs(qTot) == 0 && lepType != 2){
        theMinSelType = 2;
        theG = vPhoton;
	vMet	 = vMet     + vLoose[0] + vLoose[1];
	vMetUp   = vMetUp   + vLoose[0] + vLoose[1];
	vMetDown = vMetDown + vLoose[0] + vLoose[1];
	mLL = (vLoose[0]+vLoose[1]).M();
      }
      else if(passPhoSel == false  && vLoose.size() == 1 && lepType == 1){
        theMinSelType = 3;
        theG = vLoose[0];
      }

      if(theMinSelType == -1) continue;

      double dPhiJetMET = thePandaFlat.dphipfmet; double dPhiJetMETUp = thePandaFlat.dphipfmet_JESTotalUp; double dPhiJetMETDown = thePandaFlat.dphipfmet_JESTotalDown;
      double dPhiJetG = 100.0; double dRJetG = 100.0;
      for(int i=0; i<TMath::Min(thePandaFlat.nJot,2); i++){
        if(thePandaFlat.jotPt[i] <= 30) continue;
        TLorentzVector vJetTemp;
        vJetTemp.SetPtEtaPhiM(thePandaFlat.jotPt[i],thePandaFlat.jotEta[i],thePandaFlat.jotPhi[i],0.0);
        //if(dPhiJetMET > TMath::Abs(vJetTemp.DeltaPhi(vMet))) dPhiJetMET = TMath::Abs(vJetTemp.DeltaPhi(vMet));
        if(dPhiJetG > TMath::Abs(vJetTemp.DeltaPhi(theG))) dPhiJetG = TMath::Abs(vJetTemp.DeltaPhi(theG));
        if(dRJetG > TMath::Abs(vJetTemp.DeltaR(theG))) dRJetG = TMath::Abs(vJetTemp.DeltaR(theG));
      }
      if(theMinSelType == 0 && dPhiJetMET < 0.5) theMinSelType = 4;

      double dPhiGMET = 0; double dPhiGMETUp = 0;double dPhiGMETDown = 0;
      double mTGMET = 0;   double mTGMETUp = 0;  double mTGMETDown = 0;
      if(theMinSelType >= 0){
	dPhiGMET     = TMath::Abs(theG.DeltaPhi(vMet    )); 
	dPhiGMETUp   = TMath::Abs(theG.DeltaPhi(vMetUp  )); 
	dPhiGMETDown = TMath::Abs(theG.DeltaPhi(vMetDown));
        mTGMET     = TMath::Sqrt(2.0*theG.Pt()*vMet    .Pt()*(1.0 - cos(dPhiGMET    ))); 
	mTGMETUp   = TMath::Sqrt(2.0*theG.Pt()*vMetUp  .Pt()*(1.0 - cos(dPhiGMETUp  ))); 
	mTGMETDown = TMath::Sqrt(2.0*theG.Pt()*vMetDown.Pt()*(1.0 - cos(dPhiGMETDown)));
      }

      bool passZMass = TMath::Abs(mLL-91.1876) < 15.0;
      bool passMET = vMet.Pt() > 100; bool passMETUp = vMetUp.Pt() > 100; bool passMETDown = vMetDown.Pt() > 100;

      if(isDEBUG && dPhiGMET < 0.1) printf("%d %f %f %f %f %f %f\n",theMinSelType,mTGMET,dPhiGMET,theG.Phi(),vMet.Phi(),theG.Pt(),vMet.Pt());

      bool passNjets     = thePandaFlat.nJot              >= 2 && thePandaFlat.jotPt[0] > 50 && thePandaFlat.jotPt[1] > 50;
      bool passNjetsUp   = thePandaFlat.nJot_JESTotalUp   >= 2 && thePandaFlat.jotPt_JESTotalUp[0] > 50 && thePandaFlat.jotPt_JESTotalUp[1] > 50;
      bool passNjetsDown = thePandaFlat.nJot_JESTotalDown >= 2 && thePandaFlat.jotPt_JESTotalDown[0] > 50 && thePandaFlat.jotPt_JESTotalDown[1] > 50;
      TLorentzVector vJot1;     vJot1.SetPtEtaPhiM    (thePandaFlat.jotPt[0],thePandaFlat.jotEta[0],thePandaFlat.jotPhi[0],0.0);
      TLorentzVector vJot2;     vJot2.SetPtEtaPhiM    (thePandaFlat.jotPt[1],thePandaFlat.jotEta[1],thePandaFlat.jotPhi[1],0.0);
      TLorentzVector vJot1Up;   vJot1Up.SetPtEtaPhiM  (thePandaFlat.jotPt_JESTotalUp[0],thePandaFlat.jotEta[0],thePandaFlat.jotPhi[0],0.0);
      TLorentzVector vJot2Up;   vJot2Up.SetPtEtaPhiM  (thePandaFlat.jotPt_JESTotalUp[1],thePandaFlat.jotEta[1],thePandaFlat.jotPhi[1],0.0);
      TLorentzVector vJot1Down; vJot1Down.SetPtEtaPhiM(thePandaFlat.jotPt_JESTotalDown[0],thePandaFlat.jotEta[0],thePandaFlat.jotPhi[0],0.0);
      TLorentzVector vJot2Down; vJot2Down.SetPtEtaPhiM(thePandaFlat.jotPt_JESTotalDown[1],thePandaFlat.jotEta[1],thePandaFlat.jotPhi[1],0.0);

      double massJJ         = thePandaFlat.jot12Mass;
      double massJJUp       = thePandaFlat.jot12Mass_JESTotalUp;
      double massJJDown     = thePandaFlat.jot12Mass_JESTotalDown;
      double deltaEtaJJ     = thePandaFlat.jot12DEta;
      double deltaEtaJJUp   = thePandaFlat.jot12DEta_JESTotalUp;
      double deltaEtaJJDown = thePandaFlat.jot12DEta_JESTotalDown;
      double deltaPhiJJ     = thePandaFlat.jot12DPhi;
      double deltaPhiJJUp   = thePandaFlat.jot12DPhi_JESTotalUp;
      double deltaPhiJJDown = thePandaFlat.jot12DPhi_JESTotalDown;

      double gZep     = TMath::Min(TMath::Abs(theG.Eta()-(vJot1.Eta()+vJot2.Eta())/2.)/deltaEtaJJ,0.999);
      double gZepUp   = TMath::Min(TMath::Abs(theG.Eta()-(vJot1Up.Eta()+vJot2Up.Eta())/2.)/deltaEtaJJUp,0.999);
      double gZepDown = TMath::Min(TMath::Abs(theG.Eta()-(vJot1Down.Eta()+vJot2Down.Eta())/2.)/deltaEtaJJDown,0.999);

      bool passMJJ     = thePandaFlat.nJot              >= 2 && massJJ     > 500;
      bool passMJJUp   = thePandaFlat.nJot_JESTotalUp   >= 2 && massJJUp   > 500;
      bool passMJJDown = thePandaFlat.nJot_JESTotalDown >= 2 && massJJDown > 500;
      bool passDEtaJJ     = thePandaFlat.nJot		   >= 2 && deltaEtaJJ	  > 3.0 && vJot1.Eta()*vJot2.Eta() < 0;
      bool passDEtaJJUp   = thePandaFlat.nJot_JESTotalUp   >= 2 && deltaEtaJJUp   > 3.0 && vJot1.Eta()*vJot2.Eta() < 0;
      bool passDEtaJJDown = thePandaFlat.nJot_JESTotalDown >= 2 && deltaEtaJJDown > 3.0 && vJot1.Eta()*vJot2.Eta() < 0;
      bool passgZep     = thePandaFlat.nJot		 >= 2 && gZep	  < 0.6;
      bool passgZepUp   = thePandaFlat.nJot_JESTotalUp   >= 2 && gZepUp   < 0.6;
      bool passgZepDown = thePandaFlat.nJot_JESTotalDown >= 2 && gZepDown < 0.6;

      //bool passBtagVeto     = thePandaFlat.jetNMBtags == 0; 
      //bool passBtagVetoUp   = thePandaFlat.jetNMBtags_JESTotalUp == 0; 
      //bool passBtagVetoDown = thePandaFlat.jetNMBtags_JESTotalDown == 0;
      //bool passTauVeto = thePandaFlat.nTau == 0;

      bool passDPhiJetMET     = dPhiJetMET     >= 1.0 || theMinSelType == 4;
      bool passDPhiJetMETUp   = dPhiJetMETUp   >= 1.0 || theMinSelType == 4;
      bool passDPhiJetMETDown = dPhiJetMETDown >= 1.0 || theMinSelType == 4;

      const int numberOfCuts = 8;
      //                                                 0         1       2         3              4       5          6        7
      bool passCutEvol[numberOfCuts] = {theMinSelType >= 0,passZMass,passMET,passNjets,passDPhiJetMET,passMJJ,passDEtaJJ,passgZep};
      bool passCutEvolAll = true;

      if(isDEBUG && theMinSelType >= 0) printf("DEBUG %d %d %d %d %d %d %d\n",theMinSelType,passZMass,passMET,passNjets,passDPhiJetMET,passMJJ,passDEtaJJ);

      bool passAllCuts[nSelTypes] = {                   
     theMinSelType == 0 && passZMass && passMET && passNjets && passDPhiJetMET && passMJJ && passDEtaJJ && passgZep, // VBFGSEL
     theMinSelType == 1 && passZMass && passMET && passNjets && passDPhiJetMET && passMJJ && passDEtaJJ && passgZep, // LGSEL
     theMinSelType == 2 && passZMass && passMET && passNjets && passDPhiJetMET && passMJJ && passDEtaJJ && passgZep, // LLGSEL
     theMinSelType == 3 && passZMass && passMET && passNjets && passDPhiJetMET && passMJJ && passDEtaJJ && passgZep, // LSEL
     theMinSelType == 4 && passZMass && passMET && passNjets && passDPhiJetMET && passMJJ && passDEtaJJ && passgZep  // GJSEL
                                    };

      bool passNMinusOne[6] = {
     theMinSelType >= 0 && passZMass &&            passNjets && passDPhiJetMET && passMJJ && passDEtaJJ && passgZep,
     theMinSelType >= 0 && passZMass && passMET &&              passDPhiJetMET,
     theMinSelType >= 0 && passZMass && passMET && passNjets &&                   passMJJ && passDEtaJJ && passgZep,
     theMinSelType >= 0 && passZMass && passMET && passNjets && passDPhiJetMET            && passDEtaJJ && passgZep,
     theMinSelType >= 0 && passZMass && passMET && passNjets && passDPhiJetMET && passMJJ               && passgZep,
     theMinSelType >= 0 && passZMass && passMET && passNjets && passDPhiJetMET && passMJJ && passDEtaJJ
                                    };

      bool passVBFGSel     = theMinSelType == 0 && passZMass && passMET     && passNjets     && passDPhiJetMET     && passMJJ	  && passDEtaJJ     && passgZep    ;
      bool passVBFGSelUp   = theMinSelType == 0 && passZMass && passMETUp   && passNjetsUp   && passDPhiJetMETUp   && passMJJUp   && passDEtaJJUp   && passgZepUp  ;
      bool passVBFGSelDown = theMinSelType == 0 && passZMass && passMETDown && passNjetsDown && passDPhiJetMETDown && passMJJDown && passDEtaJJDown && passgZepDown;
      bool passLGSel       = theMinSelType == 1 && passZMass && passMET     && passNjets     && passDPhiJetMET     && passMJJ	  && passDEtaJJ     && passgZep    ;
      bool passLGSelUp     = theMinSelType == 1 && passZMass && passMETUp   && passNjetsUp   && passDPhiJetMETUp   && passMJJUp   && passDEtaJJUp   && passgZepUp  ;
      bool passLGSelDown   = theMinSelType == 1 && passZMass && passMETDown && passNjetsDown && passDPhiJetMETDown && passMJJDown && passDEtaJJDown && passgZepDown;
      bool passLLGSel      = theMinSelType == 2 && passZMass && passMET     && passNjets     && passDPhiJetMET     && passMJJ	  && passDEtaJJ     && passgZep    ;
      bool passLLGSelUp    = theMinSelType == 2 && passZMass && passMETUp   && passNjetsUp   && passDPhiJetMETUp   && passMJJUp   && passDEtaJJUp   && passgZepUp  ;
      bool passLLGSelDown  = theMinSelType == 2 && passZMass && passMETDown && passNjetsDown && passDPhiJetMETDown && passMJJDown && passDEtaJJDown && passgZepDown;
      bool passLSel	   = theMinSelType == 3 && passZMass && passMET     && passNjets     && passDPhiJetMET     && passMJJ	  && passDEtaJJ     && passgZep    ;
      bool passLSelUp	   = theMinSelType == 3 && passZMass && passMETUp   && passNjetsUp   && passDPhiJetMETUp   && passMJJUp   && passDEtaJJUp   && passgZepUp  ;
      bool passLSelDown    = theMinSelType == 3 && passZMass && passMETDown && passNjetsDown && passDPhiJetMETDown && passMJJDown && passDEtaJJDown && passgZepDown;
      bool passGJSel	   = theMinSelType == 4 && passZMass && passMET     && passNjets     && passDPhiJetMET     && passMJJ	  && passDEtaJJ     && passgZep    ;
      bool passGJSelUp	   = theMinSelType == 4 && passZMass && passMETUp   && passNjetsUp   && passDPhiJetMETUp   && passMJJUp   && passDEtaJJUp   && passgZepUp  ;
      bool passGJSelDown   = theMinSelType == 4 && passZMass && passMETDown && passNjetsDown && passDPhiJetMETDown && passMJJDown && passDEtaJJDown && passgZepDown;

      int dataCardSel = -1; int dataCardSelUp = -1;int dataCardSelDown = -1;
      if     (passVBFGSel) dataCardSel = 0;
      else if(passLGSel)   dataCardSel = 1;
      else if(passLLGSel)  dataCardSel = 2;
      else if(passLSel)    dataCardSel = 3;
      else if(passGJSel)   dataCardSel = 4;

      if     (passVBFGSelUp) dataCardSelUp = 0;
      else if(passLGSelUp)   dataCardSelUp = 1;
      else if(passLLGSelUp)  dataCardSelUp = 2;
      else if(passLSelUp)    dataCardSelUp = 3;
      else if(passGJSelUp)   dataCardSelUp = 4;

      if     (passVBFGSelDown) dataCardSelDown = 0;
      else if(passLGSelDown)   dataCardSelDown = 1;
      else if(passLLGSelDown)  dataCardSelDown = 2;
      else if(passLSelDown)    dataCardSelDown = 3;
      else if(passGJSelDown)   dataCardSelDown = 4;

      bool passSystCuts[nSystTypes] = {dataCardSelUp  >= 0, dataCardSelDown  >= 0
                                       };

      double photonSFUnc[3] = {1.0, 1.0, 1.0};
      double totalWeight = 1.0; double puWeight = 1.0; double puWeightUp = 1.0; double puWeightDown = 1.0; double sf_l1PrefireE = 1.0;
      double triggerWeights[2] = {1.0, 0.0};
      if(theCategory != kPlotData){
	puWeight     = nPUScaleFactor(fhDPU,    thePandaFlat.pu);
        puWeightUp   = nPUScaleFactor(fhDPUUp,  thePandaFlat.pu);
        puWeightDown = nPUScaleFactor(fhDPUDown,thePandaFlat.pu);

        sf_l1PrefireE = 1.0 + TMath::Abs(1.0 - thePandaFlat.sf_l1Prefire) * 0.2;

	//double npvWeight = nPUScaleFactor(fhDNPV, thePandaFlat.npv);

	if(passPhoSel == true && year == 2017) {
	  int nphbin = trgSF->GetXaxis()->FindBin(TMath::Min((double)vPhoton.Pt(), 399.99));
          triggerWeights[0] = trgSF->GetBinContent(nphbin);
          triggerWeights[1] = trgSF->GetBinError(nphbin)/triggerWeights[0];
        }

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

      if(passAllCuts[VBFGSEL]) {
        srYields [thePandaFlat.looseGenPho1PdgId] = srYields [thePandaFlat.looseGenPho1PdgId] + totalWeight;
        srYieldsE[thePandaFlat.looseGenPho1PdgId] = srYieldsE[thePandaFlat.looseGenPho1PdgId] + totalWeight * totalWeight;
      }

      if(dataCardSel >= 0) histo[ 0+theMinSelType][theCategory]->Fill(TMath::Min(mTGMET,999.999),totalWeight);
      if(passNMinusOne[0]) histo[ 5+theMinSelType][theCategory]->Fill(TMath::Min(vMet.Pt(),499.999),totalWeight);
      if(passNMinusOne[1]) histo[10+theMinSelType][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJot,4.499),totalWeight);
      if(passNMinusOne[2]) histo[15+theMinSelType][theCategory]->Fill(TMath::Min(dPhiJetMET,2.999),totalWeight);
      if(passNMinusOne[3]) histo[20+theMinSelType][theCategory]->Fill(TMath::Min(massJJ,1999.999),totalWeight);
      if(passNMinusOne[4]) histo[25+theMinSelType][theCategory]->Fill(TMath::Min(deltaEtaJJ,7.999),totalWeight);
      for(int i=0; i<numberOfCuts; i++) {passCutEvolAll = passCutEvolAll && passCutEvol[i]; if(passCutEvolAll) histo[30+theMinSelType][theCategory]->Fill((double)i,totalWeight);}
      if(dataCardSel >= 0) histo[35+theMinSelType][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNMBtags,3.499),totalWeight);
      if(dataCardSel >= 0) histo[40+theMinSelType][theCategory]->Fill(TMath::Min((double)thePandaFlat.nTau,3.499),totalWeight);
      if(dataCardSel >= 0) histo[45+theMinSelType][theCategory]->Fill(TMath::Abs(theG.Eta()),totalWeight);
      if(dataCardSel >= 0) histo[50+theMinSelType][theCategory]->Fill(TMath::Min(theG.Pt(),479.999),totalWeight);
      if(dataCardSel >= 0) histo[55+theMinSelType][theCategory]->Fill(TMath::Min(dPhiJetG,2.999),totalWeight);
      if(dataCardSel >= 0) histo[60+theMinSelType][theCategory]->Fill(TMath::Min(dRJetG,4.999),totalWeight);
      if(dataCardSel >= 0) histo[65+theMinSelType][theCategory]->Fill(TMath::Min(dPhiGMET,2.999),totalWeight);
      if(passNMinusOne[5]) histo[70+theMinSelType][theCategory]->Fill(gZep,totalWeight);
      if(dataCardSel >= 0) histo[75+theMinSelType][theCategory]->Fill(TMath::Max(TMath::Abs(thePandaFlat.jotEta[0]),TMath::Abs(thePandaFlat.jotEta[1])),totalWeight);
      if(dataCardSel >= 0) histo[80+theMinSelType][theCategory]->Fill(TMath::Min(TMath::Abs(thePandaFlat.jotEta[0]),TMath::Abs(thePandaFlat.jotEta[1])),totalWeight);

      if(1){ // Begin datacard making
        double MVAVar     = TMath::Min(mTGMET    ,999.999);
        double MVAVarUp   = TMath::Min(mTGMETUp  ,999.999);
        double MVAVarDown = TMath::Min(mTGMETDown,999.999);

        if(dataCardSel     >= 0) {MVAVar     = MVAVar	  +  dataCardSel     * 1000;}
        if(dataCardSelUp   >= 0) {MVAVarUp   = MVAVarUp   +  dataCardSelUp   * 1000;}
        if(dataCardSelDown >= 0) {MVAVarDown = MVAVarDown +  dataCardSelDown * 1000;}

        if(dataCardSel     == 0 && massJJ     > 1500) {MVAVar     = MVAVar     +  5000;}
        if(dataCardSelUp   == 0 && massJJUp   > 1500) {MVAVarUp   = MVAVarUp   +  5000;}
        if(dataCardSelDown == 0 && massJJDown > 1500) {MVAVarDown = MVAVarDown +  5000;}

        double rndWeights[6] = {1,1,1,1,1,1};
	rndWeights[0] = 1+gRandom->Uniform()*0.02;
	rndWeights[1] = 1-gRandom->Uniform()*0.02;
	rndWeights[2] = 1+gRandom->Uniform()*0.02;
	rndWeights[3] = 1-gRandom->Uniform()*0.02;
	rndWeights[4] = 1+gRandom->Uniform()*0.02;
	rndWeights[5] = 1-gRandom->Uniform()*0.02;

        // Avoid QCD scale weights that are anomalous high
        double maxQCDscale = (TMath::Abs(thePandaFlat.scale[0])+TMath::Abs(thePandaFlat.scale[1])+TMath::Abs(thePandaFlat.scale[2])+
	                      TMath::Abs(thePandaFlat.scale[3])+TMath::Abs(thePandaFlat.scale[4])+TMath::Abs(thePandaFlat.scale[5]))/6.0;
        if(maxQCDscale == 0) maxQCDscale = 1;

        double sf_ewkcorrwz_unc = 1.0; double sf_ewkcorrzz_unc = 1.0; double sf_ggcorrzz_unc = 1.0;
	if(theCategory == kPlotWZ) sf_ewkcorrwz_unc = 1.02;
	if     (theCategory == kPlotZZ && infileName_[ifile].Contains("qqZZ") == true) sf_ewkcorrzz_unc = thePandaFlat.sf_zzUnc;
	else if(theCategory == kPlotZZ) sf_ggcorrzz_unc = 1.10;

        if     (theCategory == kPlotData && dataCardSel >= 0){
          histo_Baseline[theCategory]->Fill(MVAVar,totalWeight);
        }
        else if(theCategory != kPlotData){
	  if(dataCardSel >= 0) {
	    double pdf_error = pdfUncs[0]; if(theCategory == kPlotBSM) pdf_error = pdfUncs[1];
	    histo_Baseline[theCategory]->Fill(MVAVar,totalWeight);
	    histo_QCDScaleBounding[theCategory][0]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[0])/maxQCDscale);
	    histo_QCDScaleBounding[theCategory][1]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[1])/maxQCDscale);
	    histo_QCDScaleBounding[theCategory][2]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[2])/maxQCDscale);
	    histo_QCDScaleBounding[theCategory][3]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[3])/maxQCDscale);
	    histo_QCDScaleBounding[theCategory][4]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[4])/maxQCDscale);
	    histo_QCDScaleBounding[theCategory][5]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[5])/maxQCDscale);
	    histo_PDFBoundingUp[theCategory]  ->Fill(MVAVar,totalWeight*TMath::Max((double)thePandaFlat.pdfUp,pdf_error));
	    histo_PDFBoundingDown[theCategory]->Fill(MVAVar,totalWeight*TMath::Min((double)thePandaFlat.pdfDown,1.0/pdf_error));
            histo_LepEffMBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*muSFUnc); histo_LepEffEBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*elSFUnc);
            histo_LepEffMBoundingDown[theCategory]->Fill(MVAVar,totalWeight/muSFUnc); histo_LepEffEBoundingDown[theCategory]->Fill(MVAVar,totalWeight/elSFUnc);
            histo_PUBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*puWeightUp  /puWeight);
            histo_PUBoundingDown[theCategory]->Fill(MVAVar,totalWeight*puWeightDown/puWeight);
	    for(int ny=0; ny<nYears; ny++){
	      if(ny == whichYear) {
                histo_BTAGBBoundingUp  [ny][theCategory]->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0BUp  /thePandaFlat.sf_btag0);
                histo_BTAGBBoundingDown[ny][theCategory]->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0BDown/thePandaFlat.sf_btag0);
                histo_BTAGLBoundingUp  [ny][theCategory]->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0MUp  /thePandaFlat.sf_btag0);
                histo_BTAGLBoundingDown[ny][theCategory]->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0MDown/thePandaFlat.sf_btag0);
                histo_PreFireBoundingUp  [ny][theCategory]->Fill(MVAVar,totalWeight*sf_l1PrefireE);
                histo_PreFireBoundingDown[ny][theCategory]->Fill(MVAVar,totalWeight/sf_l1PrefireE);
                histo_TriggerBoundingUp  [ny][theCategory]->Fill(MVAVar,totalWeight*(1+triggerWeights[1]));
                histo_TriggerBoundingDown[ny][theCategory]->Fill(MVAVar,totalWeight/(1+triggerWeights[1]));
              } else {
                histo_BTAGBBoundingUp  [ny][theCategory]->Fill(MVAVar,totalWeight);
                histo_BTAGBBoundingDown[ny][theCategory]->Fill(MVAVar,totalWeight);
                histo_BTAGLBoundingUp  [ny][theCategory]->Fill(MVAVar,totalWeight);
                histo_BTAGLBoundingDown[ny][theCategory]->Fill(MVAVar,totalWeight);
                histo_PreFireBoundingUp  [ny][theCategory]->Fill(MVAVar,totalWeight);
                histo_PreFireBoundingDown[ny][theCategory]->Fill(MVAVar,totalWeight);		
                histo_TriggerBoundingUp  [ny][theCategory]->Fill(MVAVar,totalWeight);
                histo_TriggerBoundingDown[ny][theCategory]->Fill(MVAVar,totalWeight);
	      }
	    }
	    histo_PhoEffBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*photonSFUnc[0]);
	    histo_PhoEffBoundingDown[theCategory]->Fill(MVAVar,totalWeight/photonSFUnc[0]);
	    histo_PhoFakeBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*photonSFUnc[1]);
	    histo_PhoFakeBoundingDown[theCategory]->Fill(MVAVar,totalWeight/photonSFUnc[1]);
	    histo_ElToPhRateBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*photonSFUnc[2]);
	    histo_ElToPhRateBoundingDown[theCategory]->Fill(MVAVar,totalWeight/photonSFUnc[2]);
	    histo_EWKCorrWZUp  [theCategory]->Fill(MVAVar,totalWeight*sf_ewkcorrwz_unc);
	    histo_EWKCorrWZDown[theCategory]->Fill(MVAVar,totalWeight/sf_ewkcorrwz_unc);
	    histo_EWKqqZZCorrUp  [theCategory]->Fill(MVAVar,totalWeight*sf_ewkcorrzz_unc);
	    histo_EWKqqZZCorrDown[theCategory]->Fill(MVAVar,totalWeight/sf_ewkcorrzz_unc);
	    histo_ggZZCorrUp  [theCategory]->Fill(MVAVar,totalWeight*sf_ggcorrzz_unc);
	    histo_ggZZCorrDown[theCategory]->Fill(MVAVar,totalWeight/sf_ggcorrzz_unc);
	  }
	  for(int ny=0; ny<nYears; ny++){
	    if(ny == whichYear) {
              if(passSystCuts[JESUP])   histo_JESBoundingUp  [ny][theCategory]->Fill(MVAVarUp  ,totalWeight);
              if(passSystCuts[JESDOWN]) histo_JESBoundingDown[ny][theCategory]->Fill(MVAVarDown,totalWeight);
            } else {
              if(dataCardSel >= 0) histo_JESBoundingUp  [ny][theCategory]->Fill(MVAVar,totalWeight);
              if(dataCardSel >= 0) histo_JESBoundingDown[ny][theCategory]->Fill(MVAVar,totalWeight);
	    }
	  }
          if(passSystCuts[VBFGSEL]) histo_ScaleMBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*rndWeights[0]);
          if(passSystCuts[VBFGSEL]) histo_ScaleMBoundingDown[theCategory]->Fill(MVAVar,totalWeight*rndWeights[1]);
          if(passSystCuts[VBFGSEL]) histo_ScaleEBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*rndWeights[2]);
          if(passSystCuts[VBFGSEL]) histo_ScaleEBoundingDown[theCategory]->Fill(MVAVar,totalWeight*rndWeights[3]);
          if(passSystCuts[VBFGSEL]) histo_ScaleGBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*rndWeights[4]);
          if(passSystCuts[VBFGSEL]) histo_ScaleGBoundingDown[theCategory]->Fill(MVAVar,totalWeight*rndWeights[5]);
        }
      } // End datacard making
    } // end events loop
    printf("srYields: %.2f +/- %.2f / %.2f +/- %.2f / %.2f +/- %.2f / %.2f +/- %.2f\n",
            srYields[0],sqrt(srYieldsE[0]),srYields[1],sqrt(srYieldsE[1]),
            srYields[2],sqrt(srYieldsE[2]),srYields[3],sqrt(srYieldsE[3]));
    the_input_file->Close();
  } // end chain loop

  for(int ic=1; ic<nPlotCategories; ic++) if(histo_Baseline[ic]->GetSumOfWeights() < 0) histo_Baseline[ic]->Scale(0.0);
  for(int ic=0; ic<nPlotCategories; ic++) histo[allPlots-1][ic]->Add(histo_Baseline[ic]);

  // 0 cat
  histo_GJNorm0Up  ->Add(histo_Baseline[kPlotGJ]);
  histo_GJNorm0Down->Add(histo_Baseline[kPlotGJ]);
  for(int i=0*nBinMVA1D+1; i<=0*nBinMVA1D+nBinMVA1D; i++) {
    histo_GJNorm0Up  ->SetBinContent(i,histo_GJNorm0Up  ->GetBinContent(i)*10.0);
    histo_GJNorm0Down->SetBinContent(i,histo_GJNorm0Down->GetBinContent(i)/10.0);
  }
  // 1 cat
  histo_GJNorm1Up  ->Add(histo_Baseline[kPlotGJ]);
  histo_GJNorm1Down->Add(histo_Baseline[kPlotGJ]);
  for(int i=5*nBinMVA1D+1; i<=5*nBinMVA1D+nBinMVA1D; i++) {
    histo_GJNorm1Up  ->SetBinContent(i,histo_GJNorm1Up  ->GetBinContent(i)*10.0);
    histo_GJNorm1Down->SetBinContent(i,histo_GJNorm1Down->GetBinContent(i)/10.0);
  }
  // 2 cat (not used)
  histo_GJNorm2Up  ->Add(histo_Baseline[kPlotGJ]);
  histo_GJNorm2Down->Add(histo_Baseline[kPlotGJ]);
  for(int i=2*nBinMVA1D+1; i<=2*nBinMVA1D+nBinMVA1D; i++) {
    histo_GJNorm2Up  ->SetBinContent(i,histo_GJNorm2Up  ->GetBinContent(i)*10.0);
    histo_GJNorm2Down->SetBinContent(i,histo_GJNorm2Down->GetBinContent(i)/10.0);
  }
  // 3 cat (not used)
  histo_GJNorm3Up  ->Add(histo_Baseline[kPlotGJ]);
  histo_GJNorm3Down->Add(histo_Baseline[kPlotGJ]);
  for(int i=3*nBinMVA1D+1; i<=3*nBinMVA1D+nBinMVA1D; i++) {
    histo_GJNorm3Up  ->SetBinContent(i,histo_GJNorm3Up  ->GetBinContent(i)*10.0);
    histo_GJNorm3Down->SetBinContent(i,histo_GJNorm3Down->GetBinContent(i)/10.0);
  }
 
   double qcdScaleTotal[2] = {0.0345, 0.2200}; // use sigma(ZH) (0.0345) instead of sigma(qq->ZZ) (0.0055) and sigma(gg->ZH) (0.2200)
  double pdfTotal[2] = {0.016, 0.051};
  double syst_WZl[2] = {1.010, 1.012};

  for(unsigned ic=0; ic<nPlotCategories; ic++) {
    if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    for(int nb=1; nb<=histo_Baseline[ic]->GetNbinsX(); nb++){
      // compute QCD scale uncertainties bin-by-bin
      double diffQCDScale[6] = {
       TMath::Abs(histo_QCDScaleBounding[ic][0]->GetBinContent(nb)-histo_Baseline[ic]->GetBinContent(nb)),
       TMath::Abs(histo_QCDScaleBounding[ic][1]->GetBinContent(nb)-histo_Baseline[ic]->GetBinContent(nb)),
       TMath::Abs(histo_QCDScaleBounding[ic][2]->GetBinContent(nb)-histo_Baseline[ic]->GetBinContent(nb)),
       TMath::Abs(histo_QCDScaleBounding[ic][3]->GetBinContent(nb)-histo_Baseline[ic]->GetBinContent(nb)),
       TMath::Abs(histo_QCDScaleBounding[ic][4]->GetBinContent(nb)-histo_Baseline[ic]->GetBinContent(nb)),
       TMath::Abs(histo_QCDScaleBounding[ic][5]->GetBinContent(nb)-histo_Baseline[ic]->GetBinContent(nb))};

      double systQCDScale = diffQCDScale[0];
      for(int nqcd=1; nqcd<6; nqcd++) {
        if(diffQCDScale[nqcd] > systQCDScale) systQCDScale = diffQCDScale[nqcd];
      }

      if(histo_Baseline[ic]->GetBinContent(nb) > 0) 
        systQCDScale = 1.0+systQCDScale/histo_Baseline[ic]->GetBinContent(nb);
      else systQCDScale = 1;

      histo_QCDScaleUp  [ic]->SetBinContent(nb, histo_Baseline[ic]->GetBinContent(nb)*systQCDScale);
      histo_QCDScaleDown[ic]->SetBinContent(nb, histo_Baseline[ic]->GetBinContent(nb)/systQCDScale);

      histo_Baseline              [ic]->SetBinContent(nb, TMath::Max((float)histo_Baseline		[ic]->GetBinContent(nb),1e-7f));
      histo_QCDScaleUp  	  [ic]->SetBinContent(nb, TMath::Max((float)histo_QCDScaleUp		[ic]->GetBinContent(nb),1e-7f));
      histo_QCDScaleDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_QCDScaleDown  	[ic]->GetBinContent(nb),1e-7f));
      histo_PDFBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PDFBoundingUp 	[ic]->GetBinContent(nb),1e-7f));
      histo_PDFBoundingDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PDFBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      histo_LepEffMBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_LepEffMBoundingUp	[ic]->GetBinContent(nb),1e-7f));
      histo_LepEffMBoundingDown   [ic]->SetBinContent(nb, TMath::Max((float)histo_LepEffMBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      histo_LepEffEBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_LepEffEBoundingUp	[ic]->GetBinContent(nb),1e-7f));
      histo_LepEffEBoundingDown   [ic]->SetBinContent(nb, TMath::Max((float)histo_LepEffEBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      histo_ScaleMBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_ScaleMBoundingUp      [ic]->GetBinContent(nb),1e-7f));
      histo_ScaleMBoundingDown    [ic]->SetBinContent(nb, TMath::Max((float)histo_ScaleMBoundingDown    [ic]->GetBinContent(nb),1e-7f));
      histo_ScaleEBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_ScaleEBoundingUp      [ic]->GetBinContent(nb),1e-7f));
      histo_ScaleEBoundingDown    [ic]->SetBinContent(nb, TMath::Max((float)histo_ScaleEBoundingDown    [ic]->GetBinContent(nb),1e-7f));
      histo_ScaleGBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_ScaleGBoundingUp      [ic]->GetBinContent(nb),1e-7f));
      histo_ScaleGBoundingDown    [ic]->SetBinContent(nb, TMath::Max((float)histo_ScaleGBoundingDown    [ic]->GetBinContent(nb),1e-7f));
      histo_PUBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PUBoundingUp  	[ic]->GetBinContent(nb),1e-7f));
      histo_PUBoundingDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PUBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      for(int ny=0; ny<nYears; ny++){
      histo_BTAGBBoundingUp    [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_BTAGBBoundingUp    [ny][ic]->GetBinContent(nb),1e-7f));
      histo_BTAGBBoundingDown  [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_BTAGBBoundingDown  [ny][ic]->GetBinContent(nb),1e-7f));
      histo_BTAGLBoundingUp    [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_BTAGLBoundingUp    [ny][ic]->GetBinContent(nb),1e-7f));
      histo_BTAGLBoundingDown  [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_BTAGLBoundingDown  [ny][ic]->GetBinContent(nb),1e-7f));
      histo_JESBoundingUp      [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_JESBoundingUp      [ny][ic]->GetBinContent(nb),1e-7f));
      histo_JESBoundingDown    [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_JESBoundingDown    [ny][ic]->GetBinContent(nb),1e-7f));
      histo_PreFireBoundingUp  [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_PreFireBoundingUp  [ny][ic]->GetBinContent(nb),1e-7f));
      histo_PreFireBoundingDown[ny][ic]->SetBinContent(nb, TMath::Max((float)histo_PreFireBoundingDown[ny][ic]->GetBinContent(nb),1e-7f));
      histo_TriggerBoundingUp  [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_TriggerBoundingUp  [ny][ic]->GetBinContent(nb),1e-7f));
      histo_TriggerBoundingDown[ny][ic]->SetBinContent(nb, TMath::Max((float)histo_TriggerBoundingDown[ny][ic]->GetBinContent(nb),1e-7f));
      }
      histo_PhoEffBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PhoEffBoundingUp	[ic]->GetBinContent(nb),1e-7f));
      histo_PhoEffBoundingDown    [ic]->SetBinContent(nb, TMath::Max((float)histo_PhoEffBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      histo_PhoFakeBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PhoFakeBoundingUp	[ic]->GetBinContent(nb),1e-7f));
      histo_PhoFakeBoundingDown   [ic]->SetBinContent(nb, TMath::Max((float)histo_PhoFakeBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      histo_ElToPhRateBoundingUp  [ic]->SetBinContent(nb, TMath::Max((float)histo_ElToPhRateBoundingUp  [ic]->GetBinContent(nb),1e-7f));
      histo_ElToPhRateBoundingDown[ic]->SetBinContent(nb, TMath::Max((float)histo_ElToPhRateBoundingDown[ic]->GetBinContent(nb),1e-7f));
      histo_EWKCorrWZUp 	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKCorrWZUp		[ic]->GetBinContent(nb),1e-7f));
      histo_EWKCorrWZDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKCorrWZDown 	[ic]->GetBinContent(nb),1e-7f));
      histo_EWKqqZZCorrUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKqqZZCorrUp 	[ic]->GetBinContent(nb),1e-7f));
      histo_EWKqqZZCorrDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKqqZZCorrDown	[ic]->GetBinContent(nb),1e-7f));
      histo_ggZZCorrUp  	  [ic]->SetBinContent(nb, TMath::Max((float)histo_ggZZCorrUp		[ic]->GetBinContent(nb),1e-7f));
      histo_ggZZCorrDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_ggZZCorrDown  	[ic]->GetBinContent(nb),1e-7f));
    }
    //histo_PUBoundingUp	[ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_PUBoundingUp  [ic]->GetSumOfWeights());
    //histo_PUBoundingDown[ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_PUBoundingDown[ic]->GetSumOfWeights());
    if(ic == kPlotBSM || ic == kPlotGJ || ic == kPlotWG || ic == kPlotWJ) {
      histo_QCDScaleUp  [ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_QCDScaleUp  [ic]->GetSumOfWeights());
      histo_QCDScaleDown[ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_QCDScaleDown[ic]->GetSumOfWeights());
    }
  }

  if(showSyst == true){
    printf("Yields\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) printf("%6.2f ",histo_Baseline[ic]->GetBinContent(i)); printf("\n");
    }
    printf("uncertainties Statistical\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_Baseline[ic]->GetBinError(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties QCDSCALEUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_QCDScaleUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties QCDSCALEDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_QCDScaleDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties PDFUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_PDFBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties PDFDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_PDFBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties LEPEFFMUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_LepEffMBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties LEPEFFMDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_LepEffMBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties LEPEFFEUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_LepEffEBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties LEPEFFEDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_LepEffEBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties ScaleMUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_ScaleMBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties ScaleMDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_ScaleMBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties ScaleEUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_ScaleEBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties ScaleEDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_ScaleEBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties ScaleGUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_ScaleGBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties ScaleGDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_ScaleGBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties PUUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_PUBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties PUDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_PUBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    for(int ny=0; ny<nYears; ny++){
      printf("uncertainties year (%d)\n",ny);
      printf("uncertainties BTAGBUp\n");
      for(unsigned ic=0; ic<nPlotCategories; ic++) {
	if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
           printf("%10s: ",plotBaseNames[ic].Data());
          for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_BTAGBBoundingUp[ny][ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      }
      printf("uncertainties BTAGBDown\n");
      for(unsigned ic=0; ic<nPlotCategories; ic++) {
	if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
           printf("%10s: ",plotBaseNames[ic].Data());
          for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_BTAGBBoundingDown[ny][ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      }

      printf("uncertainties BTAGLUp\n");
      for(unsigned ic=0; ic<nPlotCategories; ic++) {
	if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
           printf("%10s: ",plotBaseNames[ic].Data());
          for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_BTAGLBoundingUp[ny][ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      }
      printf("uncertainties BTAGLDown\n");
      for(unsigned ic=0; ic<nPlotCategories; ic++) {
	if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
           printf("%10s: ",plotBaseNames[ic].Data());
          for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_BTAGLBoundingDown[ny][ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      }

      printf("uncertainties JESUp\n");
      for(unsigned ic=0; ic<nPlotCategories; ic++) {
	if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
           printf("%10s: ",plotBaseNames[ic].Data());
          for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_JESBoundingUp[ny][ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      }
      printf("uncertainties JESDown\n");
      for(unsigned ic=0; ic<nPlotCategories; ic++) {
	if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
           printf("%10s: ",plotBaseNames[ic].Data());
          for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_JESBoundingDown[ny][ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      }

      printf("uncertainties PreFireUp\n");
      for(unsigned ic=0; ic<nPlotCategories; ic++) {
	if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
           printf("%10s: ",plotBaseNames[ic].Data());
          for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_PreFireBoundingUp[ny][ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      }
      printf("uncertainties PreFireDown\n");
      for(unsigned ic=0; ic<nPlotCategories; ic++) {
	if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
           printf("%10s: ",plotBaseNames[ic].Data());
          for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_PreFireBoundingDown[ny][ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      }

      printf("uncertainties TriggerUp\n");
      for(unsigned ic=0; ic<nPlotCategories; ic++) {
	if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
           printf("%10s: ",plotBaseNames[ic].Data());
          for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_TriggerBoundingUp[ny][ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      }
      printf("uncertainties TriggerDown\n");
      for(unsigned ic=0; ic<nPlotCategories; ic++) {
	if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
           printf("%10s: ",plotBaseNames[ic].Data());
          for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_TriggerBoundingDown[ny][ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      }
      printf("---------\n");
    }

    printf("uncertainties PHOEFFUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_PhoEffBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties PHOEFFDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_PhoEffBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties PHOFakeUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_PhoFakeBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties PHOFakeDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_PhoFakeBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties ElToPhRateUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_ElToPhRateBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties ElToPhRateDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_ElToPhRateBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties EWKCorrWZUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_EWKCorrWZUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties EWKCorrWZDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_EWKCorrWZDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties EWKqqCorrZZUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_EWKqqZZCorrUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties EWKqqCorrZZDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_EWKqqZZCorrDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties ggCorrZZUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_ggZZCorrUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties ggCorrZZDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_ggZZCorrDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
  }

  // Filling datacards input root file
  char outputLimits[200];
  sprintf(outputLimits,"vbfg_%d_mH%d_input.root",year,mH);
  TFile* outFileLimits = new TFile(outputLimits,"recreate");
  outFileLimits->cd();

  double theScale;
  for(unsigned ic=0; ic<nPlotCategories; ic++) {
    if(ic != kPlotData && histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    histo_Baseline		[ic]->Write();
    if(ic == kPlotData) continue;
    histo_QCDScaleUp		[ic]->Write();
    histo_QCDScaleDown  	[ic]->Write();
    histo_PDFBoundingUp 	[ic]->Write();
    histo_PDFBoundingDown	[ic]->Write();
    histo_LepEffMBoundingUp	[ic]->Write();
    histo_LepEffMBoundingDown	[ic]->Write();
    histo_LepEffEBoundingUp	[ic]->Write();
    histo_LepEffEBoundingDown	[ic]->Write();
    histo_ScaleMBoundingUp      [ic]->Write();
    histo_ScaleMBoundingDown    [ic]->Write();
    histo_ScaleEBoundingUp      [ic]->Write();
    histo_ScaleEBoundingDown    [ic]->Write();
    histo_ScaleGBoundingUp      [ic]->Write();
    histo_ScaleGBoundingDown    [ic]->Write();
    histo_PUBoundingUp  	[ic]->Write();
    histo_PUBoundingDown	[ic]->Write();
    for(int ny=0; ny<nYears; ny++){
    histo_BTAGBBoundingUp	[ny][ic]->Write();
    histo_BTAGBBoundingDown	[ny][ic]->Write();
    histo_BTAGLBoundingUp	[ny][ic]->Write();
    histo_BTAGLBoundingDown	[ny][ic]->Write();
    histo_JESBoundingUp 	[ny][ic]->Write();
    histo_JESBoundingDown	[ny][ic]->Write();
    histo_PreFireBoundingUp 	[ny][ic]->Write();
    histo_PreFireBoundingDown	[ny][ic]->Write();
    histo_TriggerBoundingUp 	[ny][ic]->Write();
    histo_TriggerBoundingDown	[ny][ic]->Write();
    }
    histo_PhoEffBoundingUp	[ic]->Write();
    histo_PhoEffBoundingDown	[ic]->Write();
    histo_PhoFakeBoundingUp	[ic]->Write();
    histo_PhoFakeBoundingDown	[ic]->Write();
    histo_ElToPhRateBoundingUp  [ic]->Write();
    histo_ElToPhRateBoundingDown[ic]->Write();
    histo_EWKCorrWZUp		[ic]->Write();
    histo_EWKCorrWZDown 	[ic]->Write();
    histo_EWKqqZZCorrUp 	[ic]->Write();
    histo_EWKqqZZCorrDown	[ic]->Write();
    histo_ggZZCorrUp		[ic]->Write();
    histo_ggZZCorrDown  	[ic]->Write();
  }
  histo_GJNorm0Up  ->Write();
  histo_GJNorm0Down->Write();
  histo_GJNorm1Up  ->Write();
  histo_GJNorm1Down->Write();
  histo_GJNorm2Up  ->Write();
  histo_GJNorm2Down->Write();
  histo_GJNorm3Up  ->Write();
  histo_GJNorm3Down->Write();
  outFileLimits->Close();


  // Filling datacards txt file
  char outputLimitsCard[200];  					  
  sprintf(outputLimitsCard,"datacard_vbfg_mH%d_%d.txt",mH,year);
  ofstream newcardShape;
  newcardShape.open(outputLimitsCard);
  newcardShape << Form("imax * number of channels\n");
  newcardShape << Form("jmax * number of background minus 1\n");
  newcardShape << Form("kmax * number of nuisance parameters\n");

  newcardShape << Form("shapes    *   *   %s  histo_$PROCESS histo_$PROCESS_$SYSTEMATIC\n",outputLimits);
  newcardShape << Form("shapes data_obs * %s  histo_Data\n",outputLimits);

  newcardShape << Form("Observation %f\n",histo_Baseline[kPlotData]->GetSumOfWeights());

  newcardShape << Form("bin   ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("ch1  ");
  }
  newcardShape << Form("\n");
 
  newcardShape << Form("process  ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("%s  ", plotBaseNames[ic].Data());
  }
  newcardShape << Form("\n");


  newcardShape << Form("process  ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotBSM) newcardShape << Form("%d  ", ic);
    else               newcardShape << Form("%d  ", 0);
  }
  newcardShape << Form("\n");

  newcardShape << Form("rate  ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("%f  ", histo_Baseline[ic]->GetSumOfWeights());
  }
  newcardShape << Form("\n");

  newcardShape << Form("lumi_13TeV_%d    lnN     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("%6.3f ",lumiE[whichYear]);
  }
  newcardShape << Form("\n");

  newcardShape << Form("UEPS    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotBSM) newcardShape << Form(" - ");
    else               newcardShape << Form("%f  ", 1.02);
  }
  newcardShape << Form("\n");

  //newcardShape << Form("EWKWZCorr    shape     ");
  //for (int ic=0; ic<nPlotCategories; ic++){
  //  if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
  //  if(ic != kPlotWZ) newcardShape << Form("- ");
  //  else              newcardShape << Form("1.0 ");
  //}
  //newcardShape << Form("\n");

  //newcardShape << Form("EWKqqZZCorr    shape     ");
  //for (int ic=0; ic<nPlotCategories; ic++){
  //  if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
  //  if(ic != kPlotZZ) newcardShape << Form("- ");
  //  else              newcardShape << Form("1.0 ");
  //}
  //newcardShape << Form("\n");

  //newcardShape << Form("ggZZCorr    shape     ");
  //for (int ic=0; ic<nPlotCategories; ic++){
  //  if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
  //  if(ic != kPlotZZ) newcardShape << Form("- ");
  //  else              newcardShape << Form("1.0 ");
  //}
  //newcardShape << Form("\n");

  //newcardShape << Form("WZ_lep    lnN     ");
  //for (int ic=0; ic<nPlotCategories; ic++){
  //  if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
  //  if(ic != kPlotWZ) newcardShape << Form("- ");
  //  else              newcardShape << Form("%f ",syst_WZl[0]);
  //}
  //newcardShape << Form("\n");

  //newcardShape << Form("WZ_tau    lnN     ");
  //for (int ic=0; ic<nPlotCategories; ic++){
  //  if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
  //  if(ic != kPlotWZ) newcardShape << Form("- ");
  //  else              newcardShape << Form("%f ",syst_WZl[1]);
  //}
  //newcardShape << Form("\n");

  newcardShape << Form("QCDscaleTotal_ZH    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotBSM) newcardShape << Form("- ");
    else               newcardShape << Form("%f ",1.0+qcdScaleTotal[0]);
  }
  newcardShape << Form("\n");

  for(unsigned ic=0; ic<nPlotCategories; ic++) {
    if(ic== kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("QCDScale_%s_ACCEPT    shape   ",plotBaseNames[ic].Data());
    for(unsigned ic2=0; ic2<nPlotCategories; ic2++) {
      if(ic2 == kPlotData || histo_Baseline[ic2]->GetSumOfWeights() <= 0) continue;
          if(ic==ic2) newcardShape << Form("1.0  ");
          else        newcardShape << Form("-  ");
      }
      newcardShape << Form("\n");
  }

  newcardShape << Form("PDF    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_eff_m    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_eff_e    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_scale_m    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_scale_e    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_scale_p    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_pu    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  //newcardShape << Form("CMS_btagb_%d    shape     ",year);
  //for (int ic=0; ic<nPlotCategories; ic++){
  //  if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
  //  newcardShape << Form("1.0 ");
  //}
  //newcardShape << Form("\n");

  //newcardShape << Form("CMS_btagl_%d    shape     ",year);
  //for (int ic=0; ic<nPlotCategories; ic++){
  //  if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
  //  newcardShape << Form("1.0 ");
  //}
  //newcardShape << Form("\n");

  newcardShape << Form("CMS_jes_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_prefire_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_trigger_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_eff_photon    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_fake_photon    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_fake_el    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_GJNorm0_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotGJ) newcardShape << Form("1.0 ");
    else              newcardShape << Form("- ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_GJNorm1_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotGJ) newcardShape << Form("1.0 ");
    else              newcardShape << Form("- ");
  }
  newcardShape << Form("\n");

  /*newcardShape << Form("CMS_GJNorm2_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotGJ) newcardShape << Form("1.0 ");
    else              newcardShape << Form("- ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_GJNorm3_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotGJ) newcardShape << Form("1.0 ");
    else              newcardShape << Form("- ");
  }
  newcardShape << Form("\n");*/

  newcardShape << Form("ch1 autoMCStats 0\n");

  newcardShape << Form("CMS_vbfg_wgnorm  rateParam * %s 1 [0,10]\n",plotBaseNames[kPlotWG].Data());
  //newcardShape << Form("CMS_vbfg_zgnorm  rateParam * %s 1 [0,10]\n",plotBaseNames[kPlotDY].Data());
  //newcardShape << Form("CMS_vbfg_zgnorm  rateParam * %s 1 [0,10]\n",plotBaseNames[kPlotZG].Data());
  newcardShape << Form("CMS_vbfg_wlnorm  rateParam * %s 1 [0,10]\n",plotBaseNames[kPlotWJ].Data());
  //newcardShape << Form("CMS_vbfg_gjnorm  rateParam * %s 1 [0,10]\n",plotBaseNames[kPlotGJ].Data());

  newcardShape.close();

  // Writing standard histograms
  char output[200];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    sprintf(output,"histoVBFG_mH%d_%d_%d.root",mH,year,thePlot);	
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    double totBck = 0;
    for(int i=1; i<nPlotCategories; i++) if(histo[thePlot][i]->GetSumOfWeights() < 0) histo[thePlot][i]->Scale(0.0);
    for(int i=1; i<nPlotCategories; i++) if(i != kPlotBSM) totBck = totBck + histo[thePlot][i]->GetSumOfWeights();
    printf("(%2d) %7.1f vs. %7.1f ",thePlot,histo[thePlot][0]->GetSumOfWeights(),totBck);
    printf("(");
    for(int i=1; i<nPlotCategories; i++) printf("%7.1f ",histo[thePlot][i]->GetSumOfWeights());
    printf(")\n");
    for(int np=0; np<nPlotCategories; np++) {histo[thePlot][np]->SetNameTitle(Form("histo%d",np),Form("histo%d",np));histo[thePlot][np]->Write();}
    outFilePlotsNote->Close();
  }

}
