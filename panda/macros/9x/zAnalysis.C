#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TString.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <iostream>
#include <fstream>
#include "TRandom.h"
#include "TLorentzVector.h"

#include "MitAnalysisRunII/panda/macros/9x/pandaFlat.C"
#include "MitAnalysisRunII/panda/macros/9x/common.h"

const double mcPrescale = 1;

void zAnalysis(int year, bool isTopSel = false, int whichDY = 0,  int debug = 0)
{
  int whichYear = -1;
  if     (year == 2016) whichYear = Y2016;
  else if(year == 2017) whichYear = Y2017;
  else if(year == 2018) whichYear = Y2018;
  else {printf("Wrong year (%d)!\n",year); return;}

  double k_eff = sqrt(20285930./12446486.);

  //*******************************************************
  //Inputs
  //*******************************************************
  double WSSF[5],WSSFE[5];
  if     (year == 2016){
    for(int i=0; i<5; i++) {WSSF[i] = WSSF_2016[i]; WSSFE[i] = WSSFE_2016[i];}
  }
  else if(year == 2017){
    for(int i=0; i<5; i++) {WSSF[i] = WSSF_2017[i]; WSSFE[i] = WSSFE_2017[i];}
  }
  else if(year == 2018){
    for(int i=0; i<5; i++) {WSSF[i] = WSSF_2018[i]; WSSFE[i] = WSSFE_2018[i];}
  }

  vector<TString> infileName_;
  vector<int> infileCat_;

  TString filesPath;
  TString fLepton_FakesName = Form("MitAnalysisRunII/data/90x/histoFakeEtaPt_%d.root",year);
  TString puPath;
  //TString npvPath = Form("MitAnalysisRunII/data/90x/npvWeights_%d.root",year);
  TString photonSFPath;
  TString trgSFPath = Form("MitAnalysisRunII/data/90x/histo_triggerEff_sel0_%d.root",year);
  if     (year == 2018){
    filesPath = "/data/t3home000/ceballos/panda/v_006_0/";
    puPath = "MitAnalysisRunII/data/90x/puWeights_90x_2018.root";
    photonSFPath = "MitAnalysisRunII/data/90x/2018_PhotonsMedium.root";

    infileName_.push_back(Form("%sdata.root", filesPath.Data()));                infileCat_.push_back(kPlotData);
    infileName_.push_back(Form("%sWWinc.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotqqWW);
    //infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	           infileCat_.push_back(kPlotqqWW);
    //infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	           infileCat_.push_back(kPlotggWW);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data())); infileCat_.push_back(kPlotDY);
    if     (whichDY == 0){
    infileName_.push_back(Form("%sDYJetsToLL_M-50_LO.root",filesPath.Data()));   infileCat_.push_back(kPlotDY);
    }
    else if(whichDY == 1){
    infileName_.push_back(Form("%sDYNJetsToLL_NLO.root",filesPath.Data()));      infileCat_.push_back(kPlotDY);
    //infileName_.push_back(Form("%sDYJetsToLL_M-50_NLO.root",filesPath.Data()));  infileCat_.push_back(kPlotDY);
    }
    else if(whichDY == 2){
    //infileName_.push_back(Form("%sDYNJetsToLL.root",filesPath.Data()));          infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYNJetsToLL_NLO.root",filesPath.Data()));      infileCat_.push_back(kPlotDY);
    }
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));                infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));                  infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    //infileName_.push_back(Form("%sWZno3l.root" ,filesPath.Data()));              infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sWZ3l_amcnlo.root" ,filesPath.Data()));         infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));                 infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));                 infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTVV.root" ,filesPath.Data()));                infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotHiggs);
  }
  else if(year == 2017) {
    filesPath = "/data/t3home000/ceballos/panda/v_004_0/";
    puPath = "MitAnalysisRunII/data/90x/puWeights_90x_2017.root";
    photonSFPath = "MitAnalysisRunII/data/90x/egammaEffi.txt_EGM2D_runBCDEF_passingMedium94X.root";

    infileName_.push_back(Form("%sdata.root", filesPath.Data()));                infileCat_.push_back(kPlotData);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotqqWW);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotggWW);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data())); infileCat_.push_back(kPlotDY);
    if     (whichDY == 0){
    infileName_.push_back(Form("%sDYJetsToLL_M-50_NLO.root",filesPath.Data()));  infileCat_.push_back(kPlotDY);
    }
    else if(whichDY == 1){
    infileName_.push_back(Form("%sDYNJetsToLL_NLO.root",filesPath.Data()));      infileCat_.push_back(kPlotDY);
    //infileName_.push_back(Form("%sDYJetsToLL_M-50_NLO.root",filesPath.Data()));  infileCat_.push_back(kPlotDY);
    }
    else if(whichDY == 2){
    //infileName_.push_back(Form("%sDYNJetsToLL.root",filesPath.Data()));          infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYNJetsToLL_NLO.root",filesPath.Data()));      infileCat_.push_back(kPlotDY);
    }
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));                infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));                  infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sWZno3l.root" ,filesPath.Data()));              infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sWZ3l_powheg.root" ,filesPath.Data()));         infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));                 infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));                 infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTVV.root" ,filesPath.Data()));                infileCat_.push_back(kPlotVVV);
    //infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));                  infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotHiggs);
  }
  else if(year == 2016) {
    filesPath = "/data/t3home000/ceballos/panda/v_002_0/";
    puPath = "MitAnalysisRunII/data/80x/puWeights_80x_37ifb.root";
    photonSFPath = "MitAnalysisRunII/data/80x/photon_scalefactors_37ifb.root";

    infileName_.push_back(Form("%sdata.root",filesPath.Data()));                  infileCat_.push_back(kPlotData);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotqqWW);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotggWW);
    if     (whichDY == 0 || whichDY == 1 || whichDY == 2){
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data()));  infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt0To50.root",filesPath.Data()));    infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt50To100.root",filesPath.Data()));  infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt100To250.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt250To400.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt400To650.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt650ToInf.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
    }
    else if(whichDY == 2){
    infileName_.push_back(Form("%sDYNJetsToLL.root",filesPath.Data()));          infileCat_.push_back(kPlotDY);
    }
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));                 infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));                   infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sWZ.root" ,filesPath.Data()));                   infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sWGstar.root" ,filesPath.Data()));               infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));                  infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));                  infileCat_.push_back(kPlotVVV);
    //infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));                   infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotHiggs);
  }
  else {
    return;
  }

  TFile *fLepton_Fakes = TFile::Open(fLepton_FakesName.Data());
  TH2D* histoFakeEffSelMediumEtaPt_m = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_0_0"); histoFakeEffSelMediumEtaPt_m->SetDirectory(0);
  TH2D* histoFakeEffSelMediumEtaPt_e = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_0_1"); histoFakeEffSelMediumEtaPt_e->SetDirectory(0);
  TH2D* histoFakeEffSelTightEtaPt_m  = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_2_0"); histoFakeEffSelTightEtaPt_m ->SetDirectory(0);
  TH2D* histoFakeEffSelTightEtaPt_e  = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_2_1"); histoFakeEffSelTightEtaPt_e ->SetDirectory(0);

  TFile *fPUFile = TFile::Open(Form("%s",puPath.Data()));
  TH1D *fhDPU     = (TH1D*)(fPUFile->Get("puWeights"));     assert(fhDPU);     fhDPU    ->SetDirectory(0);
  TH1D *fhDPUUp   = (TH1D*)(fPUFile->Get("puWeightsUp"));   assert(fhDPUUp);   fhDPUUp  ->SetDirectory(0);
  TH1D *fhDPUDown = (TH1D*)(fPUFile->Get("puWeightsDown")); assert(fhDPUDown); fhDPUDown->SetDirectory(0);
  delete fPUFile;

  //TFile *fNPVFile = TFile::Open(Form("%s",npvPath.Data()));
  //TH1D *fhDNPV    = (TH1D*)(fNPVFile->Get("npvWeights"));   assert(fhDNPV);    fhDNPV   ->SetDirectory(0);
  //delete fNPVFile;

  TFile *fPhotonSF = TFile::Open(photonSFPath.Data());
  TH2D *fhDPhotonSF       = (TH2D*)(fPhotonSF->Get("EGamma_SF2D")); assert(fhDPhotonSF); fhDPhotonSF->SetDirectory(0);
  TH2D *fhDElectronVetoSF = (TH2D*)(fPhotonSF->Get("Scaling_Factors_HasPix_R9 Inclusive")); assert(fhDElectronVetoSF); fhDElectronVetoSF->SetDirectory(0);
  delete fPhotonSF;

  TFile *ftrgSF = TFile::Open(trgSFPath.Data());
  TH2D *trgSFMMBB = (TH2D*)(ftrgSF->Get("trgSFMMBB")); assert(trgSFMMBB); trgSFMMBB->SetDirectory(0);
  TH2D *trgSFMMEB = (TH2D*)(ftrgSF->Get("trgSFMMEB")); assert(trgSFMMEB); trgSFMMEB->SetDirectory(0);
  TH2D *trgSFMMBE = (TH2D*)(ftrgSF->Get("trgSFMMBE")); assert(trgSFMMBE); trgSFMMBE->SetDirectory(0);
  TH2D *trgSFMMEE = (TH2D*)(ftrgSF->Get("trgSFMMEE")); assert(trgSFMMEE); trgSFMMEE->SetDirectory(0);
  TH2D *trgSFEEBB = (TH2D*)(ftrgSF->Get("trgSFEEBB")); assert(trgSFEEBB); trgSFEEBB->SetDirectory(0);
  TH2D *trgSFEEEB = (TH2D*)(ftrgSF->Get("trgSFEEEB")); assert(trgSFEEEB); trgSFEEEB->SetDirectory(0);
  TH2D *trgSFEEBE = (TH2D*)(ftrgSF->Get("trgSFEEBE")); assert(trgSFEEBE); trgSFEEBE->SetDirectory(0);
  TH2D *trgSFEEEE = (TH2D*)(ftrgSF->Get("trgSFEEEE")); assert(trgSFEEEE); trgSFEEEE->SetDirectory(0);
  TH2D *trgSFMEBB = (TH2D*)(ftrgSF->Get("trgSFMEBB")); assert(trgSFMEBB); trgSFMEBB->SetDirectory(0);
  TH2D *trgSFMEEB = (TH2D*)(ftrgSF->Get("trgSFMEEB")); assert(trgSFMEEB); trgSFMEEB->SetDirectory(0);
  TH2D *trgSFMEBE = (TH2D*)(ftrgSF->Get("trgSFMEBE")); assert(trgSFMEBE); trgSFMEBE->SetDirectory(0);
  TH2D *trgSFMEEE = (TH2D*)(ftrgSF->Get("trgSFMEEE")); assert(trgSFMEEE); trgSFMEEE->SetDirectory(0);
  TH2D *trgSFEMBB = (TH2D*)(ftrgSF->Get("trgSFEMBB")); assert(trgSFEMBB); trgSFEMBB->SetDirectory(0);
  TH2D *trgSFEMEB = (TH2D*)(ftrgSF->Get("trgSFEMEB")); assert(trgSFEMEB); trgSFEMEB->SetDirectory(0);
  TH2D *trgSFEMBE = (TH2D*)(ftrgSF->Get("trgSFEMBE")); assert(trgSFEMBE); trgSFEMBE->SetDirectory(0);
  TH2D *trgSFEMEE = (TH2D*)(ftrgSF->Get("trgSFEMEE")); assert(trgSFEMEE); trgSFEMEE->SetDirectory(0);
  delete ftrgSF;

  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 81;
  TH1D* histo[allPlots][nPlotCategories];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    if     (thePlot >=  0 && thePlot <=  1) {nBinPlot = 120; xminPlot = 91.1876-15; xmaxPlot = 91.1876+15;}
    else if(thePlot >=  2 && thePlot <=  2) {nBinPlot = 200; xminPlot = 50.0; xmaxPlot = 250;}
    else if(thePlot >=  3 && thePlot <=  4) {nBinPlot = 120; xminPlot = 91.1876-15; xmaxPlot = 91.1876+15;}
    else if(thePlot >=  5 && thePlot <=  5) {nBinPlot = 200; xminPlot = 50.0; xmaxPlot = 250;}
    else if(thePlot >=  6 && thePlot <= 11) {nBinPlot =  10; xminPlot = -0.5; xmaxPlot = 9.5;}
    else if(thePlot >= 12 && thePlot <= 14) {nBinPlot =1000; xminPlot =  0.0; xmaxPlot =1000;}
    else if(thePlot >= 15 && thePlot <= 29) {nBinPlot = 500; xminPlot =  0.0; xmaxPlot = 500;}
    else if(thePlot >= 30 && thePlot <= 35) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = TMath::Pi();}
    else if(thePlot >= 36 && thePlot <= 41) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 5.0;}
    else if(thePlot >= 42 && thePlot <= 47) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 5.0;}
    else if(thePlot >= 48 && thePlot <= 50) {nBinPlot =  80; xminPlot = -0.5; xmaxPlot = 79.5;}
    else if(thePlot >= 51 && thePlot <= 56) {nBinPlot = 100; xminPlot = -2.5; xmaxPlot = 2.5;}
    else if(thePlot >= 57 && thePlot <= 62) {nBinPlot = 200; xminPlot = 25.0; xmaxPlot = 225;}
    else if(thePlot >= 63 && thePlot <= 68) {nBinPlot =   5; xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >= 69 && thePlot <= 71) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >= 72 && thePlot <= 74) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 1.0;}
    else if(thePlot >= 75 && thePlot <= 77) {nBinPlot = 200; xminPlot = -5.0; xmaxPlot = 5.0;}
    else if(thePlot >= 78 && thePlot <= 80) {nBinPlot = 100; xminPlot = -TMath::Pi(); xmaxPlot = TMath::Pi();}
    
    if(isTopSel == true && (thePlot >= 0 && thePlot <= 5)) {nBinPlot = 200; xminPlot = 15.0; xmaxPlot = 55;}

    for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinPlot, xminPlot, xmaxPlot);
  }

  TH1D* histoLGStudy[14][nPlotCategories];
  const int nBinLGPt  =  8; Float_t xbinsLGPt [nBinLGPt+1]  = {25,30,35,40,45,50,55,70,125};
  const int nBinLGEta =  5; Float_t xbinsLGEta[nBinLGEta+1] = {0.0,0.5,1.0,1.5,2.0,2.5};
  TH2D* histoLGSF = new TH2D("histoLGSF", "histoLGSF", nBinLGEta, xbinsLGEta, nBinLGPt, xbinsLGPt);
  TH2D* histoLGEffda = new TH2D("histoLGEffda", "histoLGEffda", nBinLGEta, xbinsLGEta, nBinLGPt, xbinsLGPt);
  TH2D* histoLGEffmc = new TH2D("histoLGEffmc", "histoLGEffmc", nBinLGEta, xbinsLGEta, nBinLGPt, xbinsLGPt);
  TH1D* histoLGStudyMLG[nBinLGEta*nBinLGPt][nPlotCategories];
  {
    nBinPlot = 120; xminPlot = 91.1876-15; xmaxPlot = 91.1876+15;
    TH1D* histos = new TH1D("histos", "histos", nBinPlot, xminPlot, xmaxPlot);
    histos->Sumw2();
    for(int nsel=0; nsel<2; nsel++){
      for(int i=0; i<nPlotCategories; i++) histoLGStudy[nsel][i] = (TH1D*) histos->Clone(Form("histo%d",i));
    }
    for(int nsel=0; nsel<nBinLGEta*nBinLGPt; nsel++){
      for(int i=0; i<nPlotCategories; i++) histoLGStudyMLG[nsel][i] = (TH1D*) histos->Clone(Form("histo%d",i));
    }
    histos->Reset();histos->Clear();
  }
  {
    TH1D* histos = new TH1D("histos", "histos", nBinLGPt, xbinsLGPt);
    histos->Sumw2();
    for(int nsel=2; nsel<14; nsel++){
      for(int i=0; i<nPlotCategories; i++) histoLGStudy[nsel][i] = (TH1D*) histos->Clone(Form("histo%d",i));
    }
    histos->Reset();histos->Clear();
  }

  TH1D* histoWSStudy[5][5][4]; nBinPlot = 120; xminPlot = 91.1876-15; xmaxPlot = 91.1876+15;
  for(int i=0; i<5; i++){
    for(int j=0; j<5; j++){
      for(int np=0; np<4; np++){
        histoWSStudy[i][j][np] = new TH1D(Form("histoWSStudy_%d_%d_%d",i,j,np), Form("histoWSStudy_%d_%d_%d",i,j,np), nBinPlot, xminPlot, xmaxPlot);
        histoWSStudy[i][j][np]->Sumw2();
      }
    }
  }

  const int nEffBinEta = 10; Float_t xEffBinEta[nEffBinEta+1] = {-2.5,-2.0,-1.5,-1.0,-0.5,0.0,0.5,1.0,1.5,2.0,2.5};
  const int nEffBinPt  = 10; Float_t xEffBinPt [nEffBinPt +1] = {20,25,30,35,40,50,55,60,70,85,100};
  const int nLepSel = 16; const int nBaseSel[2] {2, 0};
  TH2D* histoEffStudy[nLepSel][2][2];
  for(int nsel=0; nsel<nLepSel; nsel++){
    for(int nt=0; nt<2; nt++){
      for(int nc=0; nc<2; nc++) histoEffStudy[nsel][nt][nc] = new TH2D(Form("histoEffStudy_%d_%d_%d",nsel,nt,nc), Form("histoEffStudy_%d_%d_%d",nsel,nt,nc), nEffBinEta, xEffBinEta, nEffBinPt, xEffBinPt);
    }
  }
  TH2D* histoEffSFStudy[nLepSel][2];
  for(int nsel=0; nsel<nLepSel; nsel++){
    for(int nt=0; nt<2; nt++){
      histoEffSFStudy[nsel][nt] = new TH2D(Form("histoEffSFStudy_%d_%d",nsel,nt), Form("histoEffSFStudy_%d_%d",nsel,nt), nEffBinEta, xEffBinEta, nEffBinPt, xEffBinPt);
    }
  }

  for(UInt_t ifile=0; ifile<infileName_.size(); ifile++) {
    printf("sampleNames(%d): %s\n",ifile,infileName_[ifile].Data());
    TFile *the_input_file = TFile::Open(infileName_[ifile].Data());
    TTree *the_input_tree = (TTree*)the_input_file->FindObjectAny("events");
    
    pandaFlat thePandaFlat(the_input_tree);
    double theMCPrescale = 1.00; if(infileCat_[ifile] != 0) theMCPrescale = mcPrescale;
    Long64_t nentries = thePandaFlat.fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = thePandaFlat.LoadTree(jentry);
      if (ientry < 0) break;
      nb = thePandaFlat.fChain->GetEntry(jentry);   nbytes += nb;
      if (jentry%1000000 == 0) printf("--- reading event %8lld (%8lld) of %8lld\n",jentry,ientry,nentries);
      if (infileCat_[ifile] != 0 && jentry%(int)theMCPrescale != 0) continue;

      bool passTrigger = (thePandaFlat.trigger & (1<<kEMuTrig)) != 0       || (thePandaFlat.trigger & (1<<kDoubleMuTrig)) != 0  ||
                         (thePandaFlat.trigger & (1<<kSingleMuTrig)) != 0  || (thePandaFlat.trigger & (1<<kDoubleEleTrig)) != 0 ||
                         (thePandaFlat.trigger & (1<<kSingleEleTrig)) != 0;
      if(passTrigger == false) continue;
      if(thePandaFlat.metFilter == 0) continue;

      if(thePandaFlat.nLooseLep > 2 || thePandaFlat.nLooseLep == 0) continue;

      vector<float>  looseLepPt,looseLepEta,looseLepPhi,looseLepSF;
      vector<int> looseLepSelBit,looseLepPdgId,looseLepTripleCharge,looseLepMissingHits;
      for(int i=0; i<thePandaFlat.nLooseMuon; i++){
        looseLepPt.push_back(thePandaFlat.muonPt[i]);
        looseLepEta.push_back(thePandaFlat.muonEta[i]);
        looseLepPhi.push_back(thePandaFlat.muonPhi[i]);
        looseLepSF.push_back(thePandaFlat.muonSfReco[i] * thePandaFlat.muonSfTight[i]);
        looseLepSelBit.push_back(thePandaFlat.muonSelBit[i]);
        looseLepPdgId.push_back(thePandaFlat.muonPdgId[i]);
        looseLepTripleCharge.push_back(1);
        looseLepMissingHits.push_back(0);
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
      }

      if((int)looseLepPt.size() != thePandaFlat.nLooseLep) printf("IMPOSSIBLE\n");

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
      if(passLooseLepId == false && !((thePandaFlat.nLooseLep == 1 && countLeptonTight == 1) ||
                                      (thePandaFlat.nLooseLep == 2 && countLeptonTight == 2))) continue;
      int theCategory = infileCat_[ifile];

      int lepType = -1;
      if     (thePandaFlat.nLooseLep == 2){
        if     (abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13) lepType = 0;
        else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11) lepType = 1;
        else                                                            lepType = 2;
      }
      else if(thePandaFlat.nLooseLep == 1){
        if     (abs(looseLepPdgId[0])==13) lepType = 2;
        else if(abs(looseLepPdgId[0])==11) lepType = 1;
      }
      else {
        printf("IMPOSSIBLE\n");
	return;
      }

      TLorentzVector dilep = vLoose[0]+vLoose[1];
      TLorentzVector vMet,vTrkMet,vMetUp,vMetDown;
      vTrkMet.SetPtEtaPhiM(thePandaFlat.trkmet,0.0,thePandaFlat.trkmetphi,0.0);
      if     (year == 2016 || year == 2018) {
        vMet    .SetPtEtaPhiM(thePandaFlat.pfmet,0.0,thePandaFlat.pfmetphi,0.0);
        vMetUp  .SetPtEtaPhiM(thePandaFlat.pfmet_JESTotalUp  ,0.0,thePandaFlat.pfmetphi_JESTotalUp  ,0.0);
        vMetDown.SetPtEtaPhiM(thePandaFlat.pfmet_JESTotalDown,0.0,thePandaFlat.pfmetphi_JESTotalDown,0.0);
      } 
      else if(year == 2017){
        vMet    .SetPtEtaPhiM(thePandaFlat.puppimet,0.0,thePandaFlat.puppimetphi,0.0);
        vMetUp  .SetPtEtaPhiM(thePandaFlat.puppimet_JESTotalUp  ,0.0,thePandaFlat.puppimetphi_JESTotalUp  ,0.0);
        vMetDown.SetPtEtaPhiM(thePandaFlat.puppimet_JESTotalDown,0.0,thePandaFlat.puppimetphi_JESTotalDown,0.0);
      }

      double dPhiDiLepMET = TMath::Abs(dilep.DeltaPhi(vMet));
      double ptFrac = TMath::Abs(dilep.Pt()-vMet.Pt())/dilep.Pt();
      double caloMinusPFMETRel = TMath::Abs(thePandaFlat.calomet-thePandaFlat.pfmet)/thePandaFlat.pfmet;
      double dphill = TMath::Abs(vLoose[0].DeltaPhi(vLoose[1]));
      double detall = TMath::Abs(vLoose[0].Eta()-vLoose[1].Eta());
      double drll = sqrt(dphill*dphill+detall*detall);
      double mtW = TMath::Sqrt(2.0*dilep.Pt()*vMet.Pt()*(1.0 - TMath::Cos(dPhiDiLepMET)));

      // Different requirements depending on the DY sample
      bool passDYSampleSel = true;
      //if     (whichDY == 1) passDYSampleSel = dilep.Pt() > 60;
      //else if(whichDY == 2) passDYSampleSel = thePandaFlat.nJot >= 1;
      if     (whichDY == 1) passDYSampleSel = dilep.Pt() > 100 && thePandaFlat.nJot == 0;
      else if(whichDY == 2) passDYSampleSel = dilep.Pt() > 100 && thePandaFlat.nJot == 1;
      if(passDYSampleSel == false) continue;

      // lepton-photon pair analysis,
      bool passPhoSel = false;
      TLorentzVector vPhoton;
      if(thePandaFlat.nLoosePhoton>=1){
        passPhoSel = thePandaFlat.loosePho1Pt > 25 && TMath::Abs(thePandaFlat.loosePho1Eta) < 2.5
                 && (thePandaFlat.loosePho1SelBit & pMedium)    == pMedium
                 && (thePandaFlat.loosePho1SelBit & pCsafeVeto) == pCsafeVeto
                 && (thePandaFlat.loosePho1SelBit & pPixelVeto) == pPixelVeto;
        vPhoton.SetPtEtaPhiM(thePandaFlat.loosePho1Pt, thePandaFlat.loosePho1Eta, thePandaFlat.loosePho1Phi, 0);
      }
      bool passLGSel[2] = {thePandaFlat.nLooseLep == 2 && countLeptonTight == 2 && vLoose[0].Pt() > 25 && vLoose[1].Pt() > 25 && lepType != 2 && TMath::Abs(dilep.M()-91.1876) < 15 && qTot == 0,
                           thePandaFlat.nLooseLep == 1 && countLeptonTight == 1 && vLoose[0].Pt() > 25 && passPhoSel && TMath::Abs((vLoose[0]+vPhoton).M()-91.1876) < 15};
      if((passLGSel[0] || passLGSel[1]) && lepType == 1){
        int theCategoryLG = infileCat_[ifile];
        double totalLGWeight = 1.0;
	if(theCategoryLG != kPlotData){
          double puWeight  = nPUScaleFactor(fhDPU,  thePandaFlat.pu);
          totalLGWeight = thePandaFlat.normalizedWeight * lumiV[whichYear] * puWeight * thePandaFlat.sf_l1Prefire * looseLepSF[0];
        }
        if(passLGSel[0]){
	  if(theCategoryLG != kPlotData){
            bool isNotMCFake = thePandaFlat.looseGenLep1PdgId != 0 && thePandaFlat.looseGenLep2PdgId != 0;
            if(theCategoryLG != kPlotData && isNotMCFake == false) theCategoryLG = kPlotNonPrompt;
            double triggerLGWeights[2] = {1.0, 0.0};
	    trigger_sf(triggerLGWeights,thePandaFlat.nLooseLep,
	    trgSFMMBB,trgSFMMEB,trgSFMMBE,trgSFMMEE,trgSFEEBB,trgSFEEEB,trgSFEEBE,trgSFEEEE,
	    trgSFMEBB,trgSFMEEB,trgSFMEBE,trgSFMEEE,trgSFEMBB,trgSFEMEB,trgSFEMBE,trgSFEMEE,
	    looseLepPt[0], TMath::Abs(looseLepEta[0]), abs(looseLepPdgId[0]),
	    looseLepPt[1], TMath::Abs(looseLepEta[1]), abs(looseLepPdgId[1]));
	    totalLGWeight = totalLGWeight * looseLepSF[1] * triggerLGWeights[0];
	  }
	  histoLGStudy[0][theCategoryLG]->Fill(dilep.M(),totalLGWeight);
	  if(TMath::Abs(dilep.M()-91.1876) < 10){ // Tighter mass window for the actual study
	    histoLGStudy[2][theCategoryLG]->Fill(TMath::Min((double)looseLepPt[0], 124.999),totalLGWeight);
	    if     (TMath::Abs(looseLepEta[0]) < 0.5) histoLGStudy[3][theCategoryLG]->Fill(TMath::Min((double)looseLepPt[0], 124.999),totalLGWeight);
	    else if(TMath::Abs(looseLepEta[0]) < 1.0) histoLGStudy[4][theCategoryLG]->Fill(TMath::Min((double)looseLepPt[0], 124.999),totalLGWeight);
	    else if(TMath::Abs(looseLepEta[0]) < 1.5) histoLGStudy[5][theCategoryLG]->Fill(TMath::Min((double)looseLepPt[0], 124.999),totalLGWeight);
	    else if(TMath::Abs(looseLepEta[0]) < 2.0) histoLGStudy[6][theCategoryLG]->Fill(TMath::Min((double)looseLepPt[0], 124.999),totalLGWeight);
	    else if(TMath::Abs(looseLepEta[0]) < 2.5) histoLGStudy[7][theCategoryLG]->Fill(TMath::Min((double)looseLepPt[0], 124.999),totalLGWeight);
	    histoLGStudy[2][theCategoryLG]->Fill(TMath::Min((double)looseLepPt[1], 124.999),totalLGWeight);
	    if     (TMath::Abs(looseLepEta[1]) < 0.5) histoLGStudy[3][theCategoryLG]->Fill(TMath::Min((double)looseLepPt[1], 124.999),totalLGWeight);
	    else if(TMath::Abs(looseLepEta[1]) < 1.0) histoLGStudy[4][theCategoryLG]->Fill(TMath::Min((double)looseLepPt[1], 124.999),totalLGWeight);
	    else if(TMath::Abs(looseLepEta[1]) < 1.5) histoLGStudy[5][theCategoryLG]->Fill(TMath::Min((double)looseLepPt[1], 124.999),totalLGWeight);
	    else if(TMath::Abs(looseLepEta[1]) < 2.0) histoLGStudy[6][theCategoryLG]->Fill(TMath::Min((double)looseLepPt[1], 124.999),totalLGWeight);
	    else if(TMath::Abs(looseLepEta[1]) < 2.5) histoLGStudy[7][theCategoryLG]->Fill(TMath::Min((double)looseLepPt[1], 124.999),totalLGWeight);
	  }
	}
	else {
	  if(theCategoryLG != kPlotData){
            bool isNotMCFake = thePandaFlat.looseGenLep1PdgId != 0 && thePandaFlat.looseGenPho1PdgId == 1;
            if(theCategoryLG != kPlotData && isNotMCFake == false) theCategoryLG = kPlotNonPrompt;
            double triggerLGWeights[2] = {1.0, 0.0};
	    trigger_sf(triggerLGWeights,2,
	    trgSFMMBB,trgSFMMEB,trgSFMMBE,trgSFMMEE,trgSFEEBB,trgSFEEEB,trgSFEEBE,trgSFEEEE,
	    trgSFMEBB,trgSFMEEB,trgSFMEBE,trgSFMEEE,trgSFEMBB,trgSFEMEB,trgSFEMBE,trgSFEMEE,
	    looseLepPt[0], TMath::Abs(looseLepEta[0]), abs(looseLepPdgId[0]),
	    vPhoton.Pt(), TMath::Abs(vPhoton.Eta()), 11);
            double photonSF = 1.0;
            if     (thePandaFlat.looseGenPho1PdgId == 1) { // This is what we want to measure
	    }
            else if(thePandaFlat.looseGenPho1PdgId == 3) {
              photonSF = effhDPhotonScaleFactor(vPhoton.Pt(), vPhoton.Eta(), "medium", fhDPhotonSF, fhDElectronVetoSF);
	    }
	    totalLGWeight = totalLGWeight * photonSF * triggerLGWeights[0];
	  }
	  histoLGStudy[1][theCategoryLG]->Fill((vLoose[0]+vPhoton).M(),totalLGWeight);
	  if(TMath::Abs((vLoose[0]+vPhoton).M()-91.1876) < 10){ // Tighter mass window for the actual study
	    histoLGStudy[8][theCategoryLG]->Fill(TMath::Min((double)looseLepPt[0], 124.999),totalLGWeight);
	    if     (TMath::Abs(looseLepEta[0]) < 0.5) histoLGStudy[ 9][theCategoryLG]->Fill(TMath::Min((double)looseLepPt[0], 124.999),totalLGWeight);
	    else if(TMath::Abs(looseLepEta[0]) < 1.0) histoLGStudy[10][theCategoryLG]->Fill(TMath::Min((double)looseLepPt[0], 124.999),totalLGWeight);
	    else if(TMath::Abs(looseLepEta[0]) < 1.5) histoLGStudy[11][theCategoryLG]->Fill(TMath::Min((double)looseLepPt[0], 124.999),totalLGWeight);
	    else if(TMath::Abs(looseLepEta[0]) < 2.0) histoLGStudy[12][theCategoryLG]->Fill(TMath::Min((double)looseLepPt[0], 124.999),totalLGWeight);
	    else if(TMath::Abs(looseLepEta[0]) < 2.5) histoLGStudy[13][theCategoryLG]->Fill(TMath::Min((double)looseLepPt[0], 124.999),totalLGWeight);
	    histoLGStudy[8][theCategoryLG]->Fill(TMath::Min((double)vPhoton.Pt(), 124.999),totalLGWeight);
	    if     (TMath::Abs(vPhoton.Eta()) < 0.5) histoLGStudy[ 9][theCategoryLG]->Fill(TMath::Min((double)vPhoton.Pt(), 124.999),totalLGWeight);
	    else if(TMath::Abs(vPhoton.Eta()) < 1.0) histoLGStudy[10][theCategoryLG]->Fill(TMath::Min((double)vPhoton.Pt(), 124.999),totalLGWeight);
	    else if(TMath::Abs(vPhoton.Eta()) < 1.5) histoLGStudy[11][theCategoryLG]->Fill(TMath::Min((double)vPhoton.Pt(), 124.999),totalLGWeight);
	    else if(TMath::Abs(vPhoton.Eta()) < 2.0) histoLGStudy[12][theCategoryLG]->Fill(TMath::Min((double)vPhoton.Pt(), 124.999),totalLGWeight);
	    else if(TMath::Abs(vPhoton.Eta()) < 2.5) histoLGStudy[13][theCategoryLG]->Fill(TMath::Min((double)vPhoton.Pt(), 124.999),totalLGWeight);
          }
	  Int_t mlgxbin = nBinLGPt*(histoLGSF->GetXaxis()->FindBin(TMath::Abs(vPhoton.Eta()))-1)+
	                           (histoLGSF->GetYaxis()->FindBin(TMath::Min((double)vPhoton.Pt(), 124.999))-1);
          histoLGStudyMLG[mlgxbin][theCategoryLG]->Fill((vLoose[0]+vPhoton).M(),totalLGWeight);
	}
      }

      // dilepton anaysis from now one
      if(thePandaFlat.nLooseLep != 2) continue;

      bool passSel = ((lepType != 2 && TMath::Abs(dilep.M()-91.1876) < 15) || (lepType == 2 && dilep.M() > 50 && thePandaFlat.jetNBtags > 0)) && vLoose[0].Pt() > 20 && vLoose[1].Pt() > 20;
      if     (isTopSel == true && lepType == 2) passSel = dilep.M() > 50 && vLoose[0].Pt() > 25 && vLoose[1].Pt() > 25 && mtW > 50 && thePandaFlat.nJet >= 1;
      else if(isTopSel == true && lepType != 2) passSel = dilep.M() > 15 && dilep.M() < 55 && vLoose[0].Pt() > 25 && vLoose[1].Pt() > 25 && thePandaFlat.nJet == 1 && thePandaFlat.nJot >= 2 && thePandaFlat.jetNBtags >= 1;
      if(passSel == false) continue;

      double totalWeight = 1.0; double sfWS = 1.0; double puWeight = 1.0; double npvWeight = 1.0;
      if     (theCategory != kPlotData){
        double triggerWeights[2] = {1.0, 0.0};
	trigger_sf(triggerWeights,thePandaFlat.nLooseLep,
	trgSFMMBB,trgSFMMEB,trgSFMMBE,trgSFMMEE,trgSFEEBB,trgSFEEEB,trgSFEEBE,trgSFEEEE,
	trgSFMEBB,trgSFMEEB,trgSFMEBE,trgSFMEEE,trgSFEMBB,trgSFEMEB,trgSFEMBE,trgSFEMEE,
	looseLepPt[0], TMath::Abs(looseLepEta[0]), abs(looseLepPdgId[0]),
	looseLepPt[1], TMath::Abs(looseLepEta[1]), abs(looseLepPdgId[1]));

        puWeight  = nPUScaleFactor(fhDPU,  thePandaFlat.pu);
        //npvWeight = nPUScaleFactor(fhDNPV, thePandaFlat.npv);

        totalWeight = thePandaFlat.normalizedWeight * lumiV[whichYear] * puWeight * thePandaFlat.sf_l1Prefire * looseLepSF[0] * looseLepSF[1] * triggerWeights[0];

        if     (infileCat_[ifile] == kPlotWZ)                                                totalWeight = totalWeight * thePandaFlat.sf_wz;
	else if(infileCat_[ifile] == kPlotZZ && infileName_[ifile].Contains("qqZZ") == true) totalWeight = totalWeight * thePandaFlat.sf_zz;

        bool isRS = thePandaFlat.looseGenLep1PdgId > 0 && thePandaFlat.looseGenLep2PdgId > 0;
        if(thePandaFlat.nLooseLep >= 3) isRS = isRS && thePandaFlat.looseGenLep3PdgId > 0;
        if(thePandaFlat.nLooseLep >= 4) isRS = isRS && thePandaFlat.looseGenLep4PdgId > 0;
	if(!isRS && theCategory != kPlotVG) {
	  //theCategory = kPlotWS; // do not change the category for these studies
	  int theWSLepton = -1;
	  if     (thePandaFlat.nLooseLep >= 2 && abs(looseLepPdgId[0]) == 11 && thePandaFlat.looseGenLep1PdgId < 0) theWSLepton = 0;
	  else if(thePandaFlat.nLooseLep >= 2 && abs(looseLepPdgId[1]) == 11 && thePandaFlat.looseGenLep2PdgId < 0) theWSLepton = 1;
	  else if(thePandaFlat.nLooseLep >= 3 && abs(looseLepPdgId[2]) == 11 && thePandaFlat.looseGenLep3PdgId < 0) theWSLepton = 2;
	  else if(thePandaFlat.nLooseLep >= 4 && abs(looseLepPdgId[3]) == 11 && thePandaFlat.looseGenLep4PdgId < 0) theWSLepton = 3;
          if(theWSLepton >= 0){
	    int nEta;
            if     (TMath::Abs(looseLepEta[theWSLepton]) < 0.5) nEta = 0;
            else if(TMath::Abs(looseLepEta[theWSLepton]) < 1.0) nEta = 1;
            else if(TMath::Abs(looseLepEta[theWSLepton]) < 1.5) nEta = 2;
            else if(TMath::Abs(looseLepEta[theWSLepton]) < 2.0) nEta = 3;
            else                                                nEta = 4;
	    sfWS = WSSF[nEta];
	  }
	}
      }

      // Wrong-sign study
      bool passSSWWLepId = false;
      if     (year == 2016 || year == 2018) {
        passSSWWLepId = (looseLepSelBit[0] & kFake) == kFake && (looseLepSelBit[0] & kEleMvaWP80) == kEleMvaWP80 && looseLepTripleCharge[0] == 1 &&
         	        (looseLepSelBit[1] & kFake) == kFake && (looseLepSelBit[1] & kEleMvaWP80) == kEleMvaWP80 && looseLepTripleCharge[1] == 1;
      }
      else if(year == 2017){
        passSSWWLepId = (looseLepSelBit[0] & kFake) == kFake && (looseLepSelBit[0] & kTight) == kTight && (looseLepSelBit[0] & kDxyz) == kDxyz && looseLepMissingHits[0] == 0 && looseLepTripleCharge[0] == 1 &&
           		(looseLepSelBit[1] & kFake) == kFake && (looseLepSelBit[1] & kTight) == kTight && (looseLepSelBit[1] & kDxyz) == kDxyz && looseLepMissingHits[1] == 0 && looseLepTripleCharge[1] == 1;
      }
      if(passSSWWLepId && lepType == 1) {
        int theWSStudyCategory = 0; double totalWSStudyWeight = totalWeight;
	if     (theCategory == kPlotData) {}
	else if(theCategory == kPlotDY)   {theWSStudyCategory = 1;}
	else                              {totalWSStudyWeight = -1.0 * totalWSStudyWeight;};
	int nEta[2];
	for(int i=0; i<2; i++){
	  if     (TMath::Abs(looseLepEta[i]) < 0.5) nEta[i] = 0;
	  else if(TMath::Abs(looseLepEta[i]) < 1.0) nEta[i] = 1;
	  else if(TMath::Abs(looseLepEta[i]) < 1.5) nEta[i] = 2;
	  else if(TMath::Abs(looseLepEta[i]) < 2.0) nEta[i] = 3;
	  else                                      nEta[i] = 4;
        }
        if(passSSWWLepId){
	  if(nEta[0] >= nEta[1]) histoWSStudy[nEta[0]][nEta[1]][(qTot!=0)+2*theWSStudyCategory]->Fill(dilep.M(),totalWSStudyWeight);
	  else                   histoWSStudy[nEta[1]][nEta[0]][(qTot!=0)+2*theWSStudyCategory]->Fill(dilep.M(),totalWSStudyWeight);
	}
      }

      // two well-identified leptons from this point
      if(countLeptonTight != 2) continue;

      if(qTot == 0) histo[lepType+ 0][theCategory]->Fill(dilep.M(),totalWeight);
      else          histo[lepType+ 3][theCategory]->Fill(dilep.M(),totalWeight*sfWS);

      if(qTot != 0) continue;

      histo[lepType+ 6][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJet,9.4999),totalWeight);
      histo[lepType+ 9][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJot,9.4999),totalWeight);
      histo[lepType+12][theCategory]->Fill(TMath::Min(dilep.Pt(), 999.999),totalWeight);
      histo[lepType+15][theCategory]->Fill(TMath::Min((double)thePandaFlat.pfmet, 499.999),totalWeight);
      histo[lepType+18][theCategory]->Fill(TMath::Min((double)thePandaFlat.pfmetRaw, 499.999),totalWeight);
      histo[lepType+21][theCategory]->Fill(TMath::Min((double)thePandaFlat.calomet, 499.999),totalWeight);
      histo[lepType+24][theCategory]->Fill(TMath::Min((double)thePandaFlat.trkmet, 499.999),totalWeight);
      histo[lepType+27][theCategory]->Fill(TMath::Min(mtW, 499.999),totalWeight);
      histo[lepType+30][theCategory]->Fill(dPhiDiLepMET,totalWeight);
      histo[lepType+33][theCategory]->Fill(dphill,totalWeight);
      histo[lepType+36][theCategory]->Fill(TMath::Min(ptFrac,4.999),totalWeight);
      histo[lepType+39][theCategory]->Fill(TMath::Min(caloMinusPFMETRel,4.999),totalWeight);
      histo[lepType+42][theCategory]->Fill(TMath::Min(detall,4.999),totalWeight);
      histo[lepType+45][theCategory]->Fill(TMath::Min(drll,4.999),totalWeight);
      histo[lepType+48][theCategory]->Fill(TMath::Min((double)thePandaFlat.npv,79.499),totalWeight);
      histo[lepType+51][theCategory]->Fill(looseLepEta[0],totalWeight);
      histo[lepType+54][theCategory]->Fill(looseLepEta[1],totalWeight);
      histo[lepType+57][theCategory]->Fill(TMath::Min((double)looseLepPt[0], 224.999),totalWeight);
      histo[lepType+60][theCategory]->Fill(TMath::Min((double)looseLepPt[1], 224.999),totalWeight);
      histo[lepType+63][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNBtags,4.4999),totalWeight);
      histo[lepType+66][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNMBtags,4.4999),totalWeight);
      if(thePandaFlat.nJot >= 1){
        histo[lepType+69][theCategory]->Fill(TMath::Min((double)thePandaFlat.jotPt[0],199.9999),totalWeight);
        histo[lepType+72][theCategory]->Fill(TMath::Max(TMath::Min((double)thePandaFlat.jotCSV[0],0.999),0.001),totalWeight);
        histo[lepType+75][theCategory]->Fill(thePandaFlat.jotEta[0],totalWeight);     
        histo[lepType+78][theCategory]->Fill(thePandaFlat.jotPhi[0],totalWeight);     
      }

      // only for mm/ee events
      if(lepType == 2) continue;

      // Lepton efficiency study     
      int theEffStudyCategory = 0; double totalEffStudyWeight = totalWeight;
      if     (theCategory == kPlotData) {}
      else if(theCategory == kPlotDY)	{theEffStudyCategory = 1;}
      else				{totalEffStudyWeight = -1.0 * totalEffStudyWeight;};
      for(int ilep=0; ilep<thePandaFlat.nLooseLep; ilep++){
        bool passLepSel[nLepSel] = {
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kMedium) == kMedium,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kTight) == kTight,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kTight) == kTight && (looseLepSelBit[ilep] & kDxyz) == kDxyz,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kTight) == kTight && (looseLepSelBit[ilep] & kDxyz) == kDxyz && looseLepMissingHits[ilep] == 0,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kTight) == kTight && (looseLepSelBit[ilep] & kDxyz) == kDxyz && looseLepMissingHits[ilep] == 0 && looseLepTripleCharge[ilep] == 1,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kEleMvaWP90) == kEleMvaWP90,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kEleMvaWP80) == kEleMvaWP80,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kEleMvaWP80) == kEleMvaWP80 && looseLepTripleCharge[ilep] == 1,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kMvaMedium) == kMvaMedium,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kMvaTight) == kMvaTight,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kMiniIsoMedium) == kMiniIsoMedium,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kMiniIsoTight) == kMiniIsoTight,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kMvaMedium) == kMvaMedium && (looseLepSelBit[ilep] & kMiniIsoMedium) == kMiniIsoMedium,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kMvaTight) == kMvaTight && (looseLepSelBit[ilep] & kMiniIsoTight) == kMiniIsoTight,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kTight) == kTight && (looseLepSelBit[ilep] & kDxyz) == kDxyz && (looseLepSelBit[ilep] & kMiniIsoMedium) == kMiniIsoMedium,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kTight) == kTight && (looseLepSelBit[ilep] & kDxyz) == kDxyz && (looseLepSelBit[ilep] & kMiniIsoTight) == kMiniIsoTight	      
	     };
        for(int nsel=0; nsel<nLepSel; nsel++){
	  if(passLepSel[nsel]) histoEffStudy[nsel][lepType][theEffStudyCategory]->Fill(looseLepEta[ilep],TMath::Min((double)looseLepPt[ilep], 99.999),totalEffStudyWeight);
        }
      }

    } // end event loop
  } // end samples loop

  printf("---------------Yields---------------\n");
  TString addSuffix = "";
  if(isTopSel == true) addSuffix = "_topsel";
  char output[200];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    sprintf(output,"histoDY%dzll_%d_%d%s.root",whichDY,year,thePlot,addSuffix.Data());	
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    double totBck = 0;
    for(int i=1; i<nPlotCategories; i++) totBck =totBck + histo[thePlot][i]->GetSumOfWeights();
    printf("(%d) %f (%f+%f+%f+%f+%f+%f+%f+%f)=%f\n",thePlot,histo[thePlot][0]->GetSumOfWeights(),
    histo[thePlot][1]->GetSumOfWeights(),histo[thePlot][2]->GetSumOfWeights(),
    histo[thePlot][3]->GetSumOfWeights(),histo[thePlot][4]->GetSumOfWeights(),
    histo[thePlot][5]->GetSumOfWeights(),histo[thePlot][6]->GetSumOfWeights(),
    histo[thePlot][7]->GetSumOfWeights(),histo[thePlot][8]->GetSumOfWeights(),
    totBck);
    for(int np=0; np<nPlotCategories; np++) {histo[thePlot][np]->SetNameTitle(Form("histo%d",np),Form("histo%d",np));histo[thePlot][np]->Write();}
    outFilePlotsNote->Close();
  }

  { // Lepton efficiency study
    printf("---------------Lepton Efficiency Study---------------\n");
    sprintf(output,"histoDY%d%sEffSFStudy_%d.root",whichDY,addSuffix.Data(),year);	
    TFile* outFileEffSF = new TFile(output,"recreate");
    outFileEffSF->cd();
    for(int nt=0; nt<2; nt++){
      for(int nsel=0; nsel<nLepSel; nsel++){
        for(int neta=1; neta<=nEffBinEta; neta++){
          for(int npt=1; npt<=nEffBinPt; npt++){
            double eff[2]  = {histoEffStudy[nsel][nt][0]->GetBinContent(neta,npt)/histoEffStudy[nBaseSel[nt]][nt][0]->GetBinContent(neta,npt),
	                      histoEffStudy[nsel][nt][1]->GetBinContent(neta,npt)/histoEffStudy[nBaseSel[nt]][nt][1]->GetBinContent(neta,npt)
			 };
            double effE[2] = {sqrt((1-eff[0])*eff[0]/histoEffStudy[nBaseSel[nt]][nt][0]->GetBinContent(neta,npt)),
	                      sqrt((1-eff[1])*eff[1]/histoEffStudy[nBaseSel[nt]][nt][1]->GetBinContent(neta,npt))
			 };
            printf("(%d,%2d,%2d,%2d): %.3f+/-%.3f/%.3f+/-%.3f = %.3f+/-%.3f\n",nt,nsel,neta,npt,eff[0],effE[0],eff[1],effE[1],eff[0]/eff[1],sqrt(eff[0]/eff[1])*sqrt(effE[0]/eff[0]*effE[0]/eff[0]+effE[1]/eff[1]*effE[1]/eff[1]));
            histoEffSFStudy[nsel][nt]->SetBinContent(neta,npt,eff[0]/eff[1]);
            histoEffSFStudy[nsel][nt]->SetBinError  (neta,npt,eff[0]/eff[1]*sqrt(effE[0]/eff[0]*effE[0]/eff[0]+effE[1]/eff[1]*effE[1]/eff[1]));
          }
	}
        histoEffSFStudy[nsel][nt]->Write();
        histoEffStudy[nsel][nt][0]->Write();
        histoEffStudy[nsel][nt][1]->Write();
      }
    }
    outFileEffSF->Close();
  }

  { // Wrong Sign study
    printf("---------------Wrong Sign Study---------------\n");
    for(int i=0; i<5; i++){
      for(int j=0; j<5; j++){
        if(j>i) continue;
        double eff[2]  = {histoWSStudy[i][j][1]->GetSumOfWeights()/histoWSStudy[i][j][0]->GetSumOfWeights(),
	                  histoWSStudy[i][j][3]->GetSumOfWeights()/histoWSStudy[i][j][2]->GetSumOfWeights()
			 };
        double effE[2] = {sqrt((1-eff[0])*eff[0]/histoWSStudy[i][j][0]->GetSumOfWeights()),
	                  sqrt((1-eff[1])*eff[1]/histoWSStudy[i][j][2]->GetSumOfWeights())
			 };
        printf("(%d,%d): %.7f+/-%.7f/%.7f+/-%.7f = %.7f+/-%.7f\n",i,j,eff[0],effE[0],eff[1],effE[1],eff[0]/eff[1],eff[0]/eff[1]*sqrt(effE[0]/eff[0]*effE[0]/eff[0]+effE[1]/eff[1]*effE[1]/eff[1]));
      }
    }

    sprintf(output,"histoDY%dWSStudy_%d%s.root",whichDY,year,addSuffix.Data());	
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    for(int i=0; i<5; i++){
      for(int j=0; j<5; j++){
        if(j>i) continue;
        for(int np=0; np<4; np++){
          histoWSStudy[i][j][np]->Write();
        }
      }
    }
    outFilePlotsNote->Close();
  }

  { // LG study, making pain text format gStyle->SetPaintTextFormat(".3f")
    printf("---------------LG Study---------------\n");
    int valLL[5] = {3, 4, 5, 6, 7};
    int valLG[5] = {9,10,11,12,13};
    double effda, effmc, effdaE, effmcE, sf, sfE;
    for(int netab=0; netab<5; netab++){
      for(int i=1; i<=histoLGStudy[valLL[netab]][0]->GetNbinsX(); i++){
        double totBck[2] = {0, 0};
        for(int ic=1; ic<nPlotCategories; ic++) {
          if(ic == kPlotDY) continue;
          totBck[0] = totBck[0] + histoLGStudy[valLL[netab]][ic]->GetBinContent(i);
          totBck[1] = totBck[1] + histoLGStudy[valLG[netab]][ic]->GetBinContent(i);
        }
        effda = (histoLGStudy[valLG[netab]][kPlotData]->GetBinContent(i)-totBck[1]) /
                (histoLGStudy[valLL[netab]][kPlotData]->GetBinContent(i)-totBck[0]);
        effmc = histoLGStudy[valLG[netab]][kPlotDY]->GetBinContent(i) /
                histoLGStudy[valLL[netab]][kPlotDY]->GetBinContent(i);
        effdaE = sqrt((1-effda)*effda/(histoLGStudy[valLL[netab]][kPlotData]->GetBinContent(i)-totBck[0]));
        effmcE = sqrt((1-effmc)*effmc/histoLGStudy[valLL[netab]][kPlotDY]->GetBinContent(i));
        sf = effda/effmc;
        sfE = effda/effmc*sqrt(effdaE/effda*effdaE/effda+effmcE/effmc*effmcE/effmc);
        printf("(%d,%2d): %.3f +/- %.3f / %.3f +/- %.3f = %.3f +/- %.3f\n",netab,i,effda,effdaE,effmc,effmcE,sf,sfE);
        histoLGEffda->SetBinContent(netab+1, i, effda );
        histoLGEffda->SetBinError  (netab+1, i, effdaE);
        histoLGEffmc->SetBinContent(netab+1, i, effmc );
        histoLGEffmc->SetBinError  (netab+1, i, effmcE);
        histoLGSF   ->SetBinContent(netab+1, i, sf    );
        histoLGSF   ->SetBinError  (netab+1, i, sqrt(sfE*sfE+0.1*0.1));
      } // pt bins
    } // 4 eta bins
    sprintf(output,"histoDY%dLGSF_%d%s.root",whichDY,year,addSuffix.Data());
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    histoLGSF   ->GetXaxis()->SetTitle("|#eta^{#gamma}|");histoLGSF   ->GetYaxis()->SetTitle("p_{T}^{#gamma} [GeV]");histoLGSF   ->Write();
    histoLGEffda->GetXaxis()->SetTitle("|#eta^{#gamma}|");histoLGEffda->GetYaxis()->SetTitle("p_{T}^{#gamma} [GeV]");histoLGEffda->Write();
    histoLGEffmc->GetXaxis()->SetTitle("|#eta^{#gamma}|");histoLGEffmc->GetYaxis()->SetTitle("p_{T}^{#gamma} [GeV]");histoLGEffmc->Write();
    outFilePlotsNote->Close();
    for(int np=0; np<14; np++){
      sprintf(output,"histoDY%dLGStudy_%d%s_%d.root",whichDY,year,addSuffix.Data(),np);
      TFile* outFilePlotsNote = new TFile(output,"recreate");
      outFilePlotsNote->cd();
      double totBck = 0;
      for(int i=1; i<nPlotCategories; i++) totBck = totBck + histoLGStudy[np][i]->GetSumOfWeights();
      printf("(%d) %f (%f+%f+%f+%f+%f+%f+%f+%f+%f+%f)=%f\n",np,histoLGStudy[np][0]->GetSumOfWeights(),
      histoLGStudy[np][1]->GetSumOfWeights(),histoLGStudy[np][2]->GetSumOfWeights(),
      histoLGStudy[np][3]->GetSumOfWeights(),histoLGStudy[np][4]->GetSumOfWeights(),
      histoLGStudy[np][5]->GetSumOfWeights(),histoLGStudy[np][6]->GetSumOfWeights(),
      histoLGStudy[np][7]->GetSumOfWeights(),histoLGStudy[np][8]->GetSumOfWeights(),
      histoLGStudy[np][9]->GetSumOfWeights(),histoLGStudy[np][10]->GetSumOfWeights(),
      totBck);
      double totBckNoZ = totBck - histoLGStudy[np][kPlotDY]->GetSumOfWeights();
      histoLGStudy[np][kPlotDY]->Scale((histoLGStudy[np][kPlotData]->GetSumOfWeights()-totBckNoZ)/histoLGStudy[np][kPlotDY]->GetSumOfWeights());
      for(int nc=0; nc<nPlotCategories; nc++) histoLGStudy[np][nc]->Write();
      outFilePlotsNote->Close();
    }
    for(int np=0; np<nBinLGEta*nBinLGPt; np++){
      sprintf(output,"histoDY%dLGStudyLMG_%d%s_%d.root",whichDY,year,addSuffix.Data(),np);
      TFile* outFilePlotsNote = new TFile(output,"recreate");
      outFilePlotsNote->cd();
      double totBck = 0;
      for(int i=1; i<nPlotCategories; i++) totBck = totBck + histoLGStudyMLG[np][i]->GetSumOfWeights();
      printf("(%d) %f (%f+%f+%f+%f+%f+%f+%f+%f+%f+%f)=%f\n",np,histoLGStudyMLG[np][0]->GetSumOfWeights(),
      histoLGStudyMLG[np][1]->GetSumOfWeights(),histoLGStudyMLG[np][2]->GetSumOfWeights(),
      histoLGStudyMLG[np][3]->GetSumOfWeights(),histoLGStudyMLG[np][4]->GetSumOfWeights(),
      histoLGStudyMLG[np][5]->GetSumOfWeights(),histoLGStudyMLG[np][6]->GetSumOfWeights(),
      histoLGStudyMLG[np][7]->GetSumOfWeights(),histoLGStudyMLG[np][8]->GetSumOfWeights(),
      histoLGStudyMLG[np][9]->GetSumOfWeights(),histoLGStudyMLG[np][10]->GetSumOfWeights(),
      totBck);
      double totBckNoZ = totBck - histoLGStudyMLG[np][kPlotDY]->GetSumOfWeights();
      histoLGStudyMLG[np][kPlotDY]->Scale((histoLGStudyMLG[np][kPlotData]->GetSumOfWeights()-totBckNoZ)/histoLGStudyMLG[np][kPlotDY]->GetSumOfWeights());
      for(int nc=0; nc<nPlotCategories; nc++) histoLGStudyMLG[np][nc]->Write();
      outFilePlotsNote->Close();
    }
  }
}
