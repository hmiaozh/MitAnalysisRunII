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
#include "MitAnalysisRunII/panda/macros/9x/applyCorrections.h"

const double mcPrescale = 1;

void zAnalysis(int year, bool isTopSel = false, int whichDY = 0,  int debug = 0)
{
  int whichYear = -1;
  if     (year == 2016) whichYear = Y2016;
  else if(year == 2017) whichYear = Y2017;
  else if(year == 2018) whichYear = Y2018;
  else {printf("Wrong year (%d)!\n",year); return;}

  double k_eff = 0.8;

  //*******************************************************
  //Inputs
  //*******************************************************
  double WSSF[nBinEtaCorr],WSSFE[nBinEtaCorr];
  double muScaleCorr[nBinEtaCorr],elScaleCorr[nBinEtaCorr];
  if     (year == 2016){
    for(int i=0; i<nBinEtaCorr; i++) {WSSF[i] = WSSF_2016[i]; WSSFE[i] = WSSFE_2016[i]; muScaleCorr[i] = muScaleCorr_2016[i]; elScaleCorr[i] = elScaleCorr_2016[i];}
  }
  else if(year == 2017){
    for(int i=0; i<nBinEtaCorr; i++) {WSSF[i] = WSSF_2017[i]; WSSFE[i] = WSSFE_2017[i]; muScaleCorr[i] = muScaleCorr_2017[i]; elScaleCorr[i] = elScaleCorr_2017[i];}
  }
  else if(year == 2018){
    for(int i=0; i<nBinEtaCorr; i++) {WSSF[i] = WSSF_2018[i]; WSSFE[i] = WSSFE_2018[i]; muScaleCorr[i] = muScaleCorr_2018[i]; elScaleCorr[i] = elScaleCorr_2018[i];}
  }

  printf("muScale:\n");for(int i=0; i<nBinEtaCorr; i++) printf("%f,",muScaleCorr[i]); printf("\n");
  printf("elScale:\n");for(int i=0; i<nBinEtaCorr; i++) printf("%f,",elScaleCorr[i]); printf("\n");

  vector<TString> infileName_;
  vector<int> infileCat_;

  TString filesPath;
  TString fLepton_FakesName = Form("MitAnalysisRunII/data/90x/histoFakeEtaPt_%d.root",year);
  TString puPath;
  TString npvPath = Form("MitAnalysisRunII/data/90x/npvWeights_%d.root",year);
  TString photonSFPath;
  TString elephoSFPath = Form("MitAnalysisRunII/data/90x/histoDY0LGSF_%d.root",year);
  TString trgSFPath = Form("MitAnalysisRunII/data/90x/histo_triggerEff_sel0_%d.root",year);
  if     (year == 2018){
    filesPath = "/data/t3home000/ceballos/panda/v_006_0/";
    puPath = "MitAnalysisRunII/data/90x/puWeights_90x_2018.root";
    photonSFPath = "MitAnalysisRunII/data/90x/2018_PhotonsMedium.root";

    infileName_.push_back(Form("%sdata.root", filesPath.Data()));                infileCat_.push_back(kPlotData);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	           infileCat_.push_back(kPlotqqWW);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	           infileCat_.push_back(kPlotggWW);
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
    infileName_.push_back(Form("%sWZno3l.root" ,filesPath.Data()));              infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sWZ3l_amcnlo.root" ,filesPath.Data()));         infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));                 infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));                 infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTVV.root" ,filesPath.Data()));                infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));                  infileCat_.push_back(kPlotVG);
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
    infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));                  infileCat_.push_back(kPlotVG);
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
    infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));                   infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotHiggs);
  }
  else {
    return;
  }

  //infileName_.clear();infileCat_.clear();
  //infileName_.push_back(Form("%sDYJetsToLL_M-50_NLO.root",filesPath.Data()));   infileCat_.push_back(kPlotDY);

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

  TFile *fNPVFile = TFile::Open(Form("%s",npvPath.Data()));
  TH1D *fhDNPV    = (TH1D*)(fNPVFile->Get("npvWeights"));   assert(fhDNPV);    fhDNPV   ->SetDirectory(0);
  delete fNPVFile;

  TFile *fPhotonSF = TFile::Open(photonSFPath.Data());
  TH2D *fhDPhotonSF       = (TH2D*)(fPhotonSF->Get("EGamma_SF2D")); assert(fhDPhotonSF); fhDPhotonSF->SetDirectory(0);
  TH2D *fhDElectronVetoSF = (TH2D*)(fPhotonSF->Get("Scaling_Factors_HasPix_R9 Inclusive")); assert(fhDElectronVetoSF); fhDElectronVetoSF->SetDirectory(0);
  delete fPhotonSF;

  TFile *fElePhoSF = TFile::Open(elephoSFPath.Data());
  TH2D *fhDElePhoSF    = (TH2D*)(fElePhoSF->Get("histoLGSF"));    assert(fhDElePhoSF);    fhDElePhoSF  ->SetDirectory(0);
  TH2D *fhDElePhoEffda = (TH2D*)(fElePhoSF->Get("histoLGEffda")); assert(fhDElePhoEffda); fhDElePhoEffda->SetDirectory(0);
  delete fElePhoSF;

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

  TFile *fSingleTrgSF = TFile::Open(Form("MitAnalysisRunII/data/90x/histoDY0TriggerSFStudy_%d.root",year));
  TH2D *muTrgEffSF = (TH2D*)(fSingleTrgSF->Get("histoTrgEffStudy_1_0")); assert(muTrgEffSF); muTrgEffSF->SetDirectory(0);
  TH2D *elTrgEffSF = (TH2D*)(fSingleTrgSF->Get("histoTrgEffStudy_3_0")); assert(elTrgEffSF); elTrgEffSF->SetDirectory(0);
  delete fSingleTrgSF;

  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 128;
  TH1D* histo[allPlots][nPlotCategories];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    if     (thePlot >=  0 && thePlot <=  1) {nBinPlot = 120; xminPlot = 91.1876-15; xmaxPlot = 91.1876+15;}
    else if(thePlot >=  2 && thePlot <=  2) {nBinPlot = 200; xminPlot = 50.0; xmaxPlot = 250;}
    else if(thePlot >=  3 && thePlot <=  4) {nBinPlot = 120; xminPlot = 91.1876-15; xmaxPlot = 91.1876+15;}
    else if(thePlot >=  5 && thePlot <=  5) {nBinPlot = 200; xminPlot = 50.0; xmaxPlot = 250;}
    else if(thePlot >=  6 && thePlot <= 11) {nBinPlot =  10; xminPlot = -0.5; xmaxPlot = 9.5;}
    else if(thePlot >= 12 && thePlot <= 23) {nBinPlot = 400; xminPlot =  0.0; xmaxPlot = 400;}
    else if(thePlot >= 24 && thePlot <= 26) {nBinPlot = 100; xminPlot =  -TMath::Pi(); xmaxPlot = TMath::Pi();}
    else if(thePlot >= 27 && thePlot <= 35) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = TMath::Pi();}
    else if(thePlot >= 36 && thePlot <= 41) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 5.0;}
    else if(thePlot >= 42 && thePlot <= 44) {nBinPlot =  80; xminPlot = -0.5; xmaxPlot = 79.5;}
    else if(thePlot >= 45 && thePlot <= 47) {nBinPlot = 100; xminPlot = -2.5; xmaxPlot = 2.5;}
    else if(thePlot >= 48 && thePlot <= 50) {nBinPlot = 200; xminPlot = 20.0; xmaxPlot = 220;}
    else if(thePlot >= 51 && thePlot <= 56) {nBinPlot =   5; xminPlot = -0.5; xmaxPlot = 4.5;}

    else if(thePlot >= 57 && thePlot <= 57) {nBinPlot = 200; xminPlot = 30.0; xmaxPlot = 230;}
    else if(thePlot >= 58 && thePlot <= 58) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 1.0;}
    else if(thePlot >= 59 && thePlot <= 59) {nBinPlot = 200; xminPlot = -5.0; xmaxPlot = 5.0;}
    else if(thePlot >= 60 && thePlot <= 60) {nBinPlot = 100; xminPlot = -TMath::Pi(); xmaxPlot = TMath::Pi();}
    else if(thePlot >= 61 && thePlot <= 86) {nBinPlot = 400; xminPlot =  0.0; xmaxPlot = 400;}
    else if(thePlot >= 87 && thePlot <= 87) {nBinPlot = 100; xminPlot =  -TMath::Pi(); xmaxPlot = TMath::Pi();}
    else if(thePlot >= 88 && thePlot <=117) {nBinPlot = 120; xminPlot = 91.1876-15; xmaxPlot = 91.1876+15;}
    else if(thePlot >=118 && thePlot <=118) {nBinPlot = 50; xminPlot =  0.0; xmaxPlot = 2000;}
    else if(thePlot >=119 && thePlot <=119) {nBinPlot = 50; xminPlot =  0.0; xmaxPlot = 8.0;}
    else if(thePlot >=120 && thePlot <=120) {nBinPlot = 50; xminPlot =  0.0; xmaxPlot = TMath::Pi();}
    else if(thePlot >=121 && thePlot <=121) {nBinPlot = 50; xminPlot = -5.0; xmaxPlot = 5.0;}
    else if(thePlot >=122 && thePlot <=122) {nBinPlot = 50; xminPlot = 30.0; xmaxPlot = 430;}
    else if(thePlot >=123 && thePlot <=123) {nBinPlot = 50; xminPlot =500.0; xmaxPlot = 2500;}
    else if(thePlot >=124 && thePlot <=124) {nBinPlot = 50; xminPlot =  0.0; xmaxPlot = 8.0;}
    else if(thePlot >=125 && thePlot <=125) {nBinPlot = 50; xminPlot =  0.0; xmaxPlot = TMath::Pi();}
    else if(thePlot >=126 && thePlot <=126) {nBinPlot = 50; xminPlot = -5.0; xmaxPlot = 5.0;}
    else if(thePlot >=127 && thePlot <=127) {nBinPlot = 50; xminPlot = 30.0; xmaxPlot = 430;}

    if(isTopSel == true && (thePlot >= 0 && thePlot <= 5)) {nBinPlot = 200; xminPlot = 15.0; xmaxPlot = 55;}

    for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinPlot, xminPlot, xmaxPlot);
  }

  TH1D* histoEGStudy[12][nPlotCategories];
  const int nBinLGPt  =  7; Float_t xbinsLGPt [nBinLGPt+1]  = {25,30,35,40,45,50,60,125};
  const int nBinLGEta =  4; Float_t xbinsLGEta[nBinLGEta+1] = {0.0,0.5,1.0,1.5,2.5};
  TH2D* histoLGSF = new TH2D("histoLGSF", "histoLGSF", nBinLGEta, xbinsLGEta, nBinLGPt, xbinsLGPt);
  TH2D* histoLGEffda = new TH2D("histoLGEffda", "histoLGEffda", nBinLGEta, xbinsLGEta, nBinLGPt, xbinsLGPt);
  TH2D* histoLGEffmc = new TH2D("histoLGEffmc", "histoLGEffmc", nBinLGEta, xbinsLGEta, nBinLGPt, xbinsLGPt);
  TH1D* histoEGStudyMass[nBinLGEta*nBinLGPt*2][nPlotCategories];
  {
    nBinPlot = 120; xminPlot = 91.1876-15; xmaxPlot = 91.1876+15;
    TH1D* histos = new TH1D("histos", "histos", nBinPlot, xminPlot, xmaxPlot);
    histos->Sumw2();
    for(int nsel=0; nsel<2; nsel++){
      for(int i=0; i<nPlotCategories; i++) histoEGStudy[nsel][i] = (TH1D*) histos->Clone(Form("histo%d",i));
    }
    for(int nsel=0; nsel<nBinLGEta*nBinLGPt*2; nsel++){
      for(int i=0; i<nPlotCategories; i++) histoEGStudyMass[nsel][i] = (TH1D*) histos->Clone(Form("histo%d",i));
    }
    histos->Reset();histos->Clear();
  }
  {
    TH1D* histos = new TH1D("histos", "histos", nBinLGPt, xbinsLGPt);
    histos->Sumw2();
    for(int nsel=2; nsel<12; nsel++){
      for(int i=0; i<nPlotCategories; i++) histoEGStudy[nsel][i] = (TH1D*) histos->Clone(Form("histo%d",i));
    }
    histos->Reset();histos->Clear();
  }

  TH1D* histoMGStudy[2][nPlotCategories];
  for(int i=0; i<nPlotCategories; i++) histoMGStudy[0][i] = new TH1D(Form("histoMGStudy_%d_%d",0,i), Form("histoMGStudy_%d_%d",0,i), 120, 91.1876-15, 91.1876+15);
  for(int i=0; i<nPlotCategories; i++) histoMGStudy[1][i] = new TH1D(Form("histoMGStudy_%d_%d",1,i), Form("histoMGStudy_%d_%d",1,i), 100, 0, 200);
 
  const int nWSBins = 5;
  TH1D* histoWSStudy[nWSBins][nWSBins][4]; nBinPlot = 120; xminPlot = 91.1876-15; xmaxPlot = 91.1876+15;
  for(int i=0; i<nWSBins; i++){
    for(int j=0; j<nWSBins; j++){
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

  const int METBins = 20;
  TH1D* histoMETStudy[4][METBins][2]; nBinPlot = 2000; xminPlot = -200; xmaxPlot = 200;
  for(int mtype=0; mtype<4; mtype++){
    for(int nh=0; nh<METBins; nh++){
      for(int nc=0; nc<2; nc++){
        histoMETStudy[mtype][nh][nc] = new TH1D(Form("histoMETStudy_%d_%d_%d",mtype,nh,nc), Form("histoMETStudy_%d_%d_%d",mtype,nh,nc), nBinPlot, xminPlot, xmaxPlot);
      }
    }
  }

  const int allDataHEMPlots = 12;
  TH1D* histoDataHEM[allDataHEMPlots][4];
  for(int thePlot=0; thePlot<allDataHEMPlots; thePlot++){
    if     (thePlot >=  0 && thePlot <=  0) {nBinPlot = 120; xminPlot = 91.1876-15; xmaxPlot = 91.1876+15;}
    else if(thePlot >=  1 && thePlot <=  1) {nBinPlot =   5; xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >=  2 && thePlot <=  3) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 400;}
    else if(thePlot >=  4 && thePlot <=  4) {nBinPlot = 100; xminPlot =  -TMath::Pi(); xmaxPlot = TMath::Pi();}
    else if(thePlot >=  5 && thePlot <=  5) {nBinPlot =  50; xminPlot =  0.0; xmaxPlot = TMath::Pi();}
    else if(thePlot >=  6 && thePlot <=  6) {nBinPlot =  80; xminPlot = -0.5; xmaxPlot = 79.5;}
    else if(thePlot >=  7 && thePlot <= 10) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 400;}
    else if(thePlot >= 11 && thePlot <= 11) {nBinPlot =  24; xminPlot =  0.0; xmaxPlot = 3.0;}
    for(int i=0; i<4; i++) histoDataHEM[thePlot][i] = new TH1D(Form("histoDataHEM_%d_%d",thePlot,i), Form("histoDataHEM_%d_%d",thePlot,i), nBinPlot, xminPlot, xmaxPlot);
  }

  const int allHEMPlots = 23;
  TH1D* histoHEM[allHEMPlots][nPlotCategories];
  for(int thePlot=0; thePlot<allHEMPlots; thePlot++){
    if     (thePlot >=  0 && thePlot <=  1) {nBinPlot = 120; xminPlot = 91.1876-15; xmaxPlot = 91.1876+15;}
    else if(thePlot >=  2 && thePlot <=  3) {nBinPlot = 100; xminPlot = 20.0; xmaxPlot = 220;}
    else if(thePlot >=  4 && thePlot <=  5) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 400;}
    else if(thePlot >=  6 && thePlot <=  7) {nBinPlot =   5; xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >=  8 && thePlot <=  9) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 400;}
    else if(thePlot >= 10 && thePlot <= 11) {nBinPlot = 100; xminPlot = 30.0; xmaxPlot = 230;}
    else if(thePlot >= 12 && thePlot <= 13) {nBinPlot = 100; xminPlot = 20.0; xmaxPlot = 220;}
    else if(thePlot >= 14 && thePlot <= 18) {nBinPlot = 100; xminPlot =  -TMath::Pi(); xmaxPlot = TMath::Pi();}
    else if(thePlot >= 19 && thePlot <= 19) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = TMath::Pi();}
    else if(thePlot >= 20 && thePlot <= 20) {nBinPlot = 100; xminPlot =  -TMath::Pi(); xmaxPlot = TMath::Pi();}
    else if(thePlot >= 21 && thePlot <= 21) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = TMath::Pi();}
    else if(thePlot >= 22 && thePlot <= 22) {nBinPlot = 100; xminPlot =  -TMath::Pi(); xmaxPlot = TMath::Pi();}
    for(int i=0; i<nPlotCategories; i++) histoHEM[thePlot][i] = new TH1D(Form("histoHEM_%d_%d",thePlot,i), Form("histoHEM_%d_%d",thePlot,i), nBinPlot, xminPlot, xmaxPlot);
  }

  const int nTrgBinPt  = 17; Float_t xTrgBinPt [nTrgBinPt +1] = {20,22,24,26,28,30,32,34,36,38,40,45,50,55,60,70,100,120};
  const int nTrgBinEta =  9; Float_t xTrgBinEta[nTrgBinEta+1] = {-2.5,-2.0,-1.5,-1.0,-0.5,0.5,1.0,1.5,2.0,2.5};
  TH2D* histoTrgEffStudy[4][2];
  TH2D* histoMuTrgEffSF = new TH2D(Form("histoMuTrgEffSF"), Form("histoMuTrgEffSF"), nTrgBinEta, xTrgBinEta, nTrgBinPt, xTrgBinPt); histoMuTrgEffSF->Sumw2();
  TH2D* histoElTrgEffSF = new TH2D(Form("histoElTrgEffSF"), Form("histoElTrgEffSF"), nTrgBinEta, xTrgBinEta, nTrgBinPt, xTrgBinPt); histoElTrgEffSF->Sumw2();
  for(int thePlot=0; thePlot<4; thePlot++){
    for(int i=0; i<2; i++) {
      histoTrgEffStudy[thePlot][i] = new TH2D(Form("histoTrgEffStudy_%d_%d",thePlot,i), Form("histoTrgEffStudy_%d_%d",thePlot,i), nTrgBinEta, xTrgBinEta, nTrgBinPt, xTrgBinPt);
      histoTrgEffStudy[thePlot][i]->Sumw2();
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

      if(thePandaFlat.metFilter == 0) continue;

      if(thePandaFlat.nLooseLep > 2 || thePandaFlat.nLooseLep == 0) continue;

      vector<float>  looseLepPt,looseLepEta,looseLepPhi,looseLepSF,looseLepIso;
      vector<int> looseLepSelBit,looseLepPdgId,looseLepTripleCharge,looseLepMissingHits;
      int ptSelCuts[3] = {0,0,0};
      for(int i=0; i<thePandaFlat.nLooseMuon; i++){
        int nBinEtaCorr = histoEtaCorr->GetXaxis()->FindBin(TMath::Min((double)TMath::Abs(thePandaFlat.muonEta[i]),2.4999))-1;
        if(infileCat_[ifile]==kPlotData)
        looseLepPt.push_back(thePandaFlat.muonPt[i]);
        else
        looseLepPt.push_back(thePandaFlat.muonPt[i] * muScaleCorr[nBinEtaCorr]);
        looseLepEta.push_back(thePandaFlat.muonEta[i]);
        looseLepPhi.push_back(thePandaFlat.muonPhi[i]);
        looseLepSF.push_back(thePandaFlat.muonSfReco[i] * thePandaFlat.muonSfTight[i]);
        looseLepSelBit.push_back(thePandaFlat.muonSelBit[i]);
        looseLepPdgId.push_back(thePandaFlat.muonPdgId[i]);
        looseLepTripleCharge.push_back(1);
        looseLepMissingHits.push_back(0);
        looseLepIso.push_back(thePandaFlat.muonCombIso[i]);
	if(looseLepPt[looseLepPt.size()-1] > 25) ptSelCuts[0]++;
	if(looseLepPt[looseLepPt.size()-1] > 20) ptSelCuts[1]++;
	if(looseLepPt[looseLepPt.size()-1] > 10) ptSelCuts[2]++;
      }
      for(int i=0; i<thePandaFlat.nLooseElectron; i++){
        int nBinEtaCorr = histoEtaCorr->GetXaxis()->FindBin(TMath::Min((double)TMath::Abs(thePandaFlat.electronEta[i]),2.4999))-1;
        if(infileCat_[ifile]==kPlotData)
        looseLepPt.push_back(thePandaFlat.electronPt[i]);
        else
        looseLepPt.push_back(thePandaFlat.electronPt[i] * elScaleCorr[nBinEtaCorr]);
        looseLepEta.push_back(thePandaFlat.electronEta[i]);
        looseLepPhi.push_back(thePandaFlat.electronPhi[i]);
        looseLepSelBit.push_back(thePandaFlat.electronSelBit[i]);
        looseLepSF.push_back(thePandaFlat.electronSfReco[i] * thePandaFlat.electronSfMedium[i]);
        looseLepPdgId.push_back(thePandaFlat.electronPdgId[i]);
        looseLepTripleCharge.push_back(thePandaFlat.electronTripleCharge[i]);
        looseLepMissingHits.push_back(thePandaFlat.electronNMissingHits[i]);
        looseLepIso.push_back(thePandaFlat.electronCombIso[i]);
	if(looseLepPt[looseLepPt.size()-1] > 25) ptSelCuts[0]++;
	if(looseLepPt[looseLepPt.size()-1] > 20) ptSelCuts[1]++;
	if(looseLepPt[looseLepPt.size()-1] > 10) ptSelCuts[2]++;
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
      // Trigger study
      bool passTrgSel = lepType == 2 && thePandaFlat.nLooseLep == 2 && dilep.M() > 50 && thePandaFlat.jetNBtags > 0 && vLoose[0].Pt() > 20 && vLoose[1].Pt() > 20 && countLeptonTight == 2;
      if(passTrgSel){
        double totalTrgWeight = 1.0;
	if(infileCat_[ifile] != kPlotData){
          double puWeight  = nPUScaleFactor(fhDPU,  thePandaFlat.pu);
          double npvWeight = nPUScaleFactor(fhDNPV, thePandaFlat.npv);
          totalTrgWeight      = thePandaFlat.normalizedWeight * lumiV[whichYear] * puWeight * thePandaFlat.sf_l1Prefire * looseLepSF[0] * looseLepSF[1] * npvWeight;
        }
	if     (abs(looseLepPdgId[0])==13 && (thePandaFlat.trigger & (1<<kSingleMuTrig)) != 0){
	  histoTrgEffStudy[2][infileCat_[ifile] != kPlotData]->Fill(vLoose[1].Eta(),TMath::Min(vLoose[1].Pt(),119.999),totalTrgWeight);
	  if((thePandaFlat.trigger & (1<<kSingleEleTrig)) != 0){
	    histoTrgEffStudy[3][infileCat_[ifile] != kPlotData]->Fill(vLoose[1].Eta(),TMath::Min(vLoose[1].Pt(),119.999),totalTrgWeight);
	  }
	}
	else if(abs(looseLepPdgId[0])==11 && (thePandaFlat.trigger & (1<<kSingleEleTrig)) != 0){
	  histoTrgEffStudy[0][infileCat_[ifile] != kPlotData]->Fill(vLoose[1].Eta(),TMath::Min(vLoose[1].Pt(),119.999),totalTrgWeight);
	  if((thePandaFlat.trigger & (1<<kSingleMuTrig)) != 0){
	    histoTrgEffStudy[1][infileCat_[ifile] != kPlotData]->Fill(vLoose[1].Eta(),TMath::Min(vLoose[1].Pt(),119.999),totalTrgWeight);
	  }
	}
	if     (abs(looseLepPdgId[1])==13 && (thePandaFlat.trigger & (1<<kSingleMuTrig)) != 0){
	  histoTrgEffStudy[2][infileCat_[ifile] != kPlotData]->Fill(vLoose[0].Eta(),TMath::Min(vLoose[0].Pt(),119.999),totalTrgWeight);
	  if((thePandaFlat.trigger & (1<<kSingleEleTrig)) != 0){
	    histoTrgEffStudy[3][infileCat_[ifile] != kPlotData]->Fill(vLoose[0].Eta(),TMath::Min(vLoose[0].Pt(),119.999),totalTrgWeight);
	  }
	}
	else if(abs(looseLepPdgId[1])==11 && (thePandaFlat.trigger & (1<<kSingleEleTrig)) != 0){
	  histoTrgEffStudy[0][infileCat_[ifile] != kPlotData]->Fill(vLoose[0].Eta(),TMath::Min(vLoose[0].Pt(),119.999),totalTrgWeight);
	  if((thePandaFlat.trigger & (1<<kSingleMuTrig)) != 0){
	    histoTrgEffStudy[1][infileCat_[ifile] != kPlotData]->Fill(vLoose[0].Eta(),TMath::Min(vLoose[0].Pt(),119.999),totalTrgWeight);
	  }
	}
      }

      bool passTrigger = (thePandaFlat.trigger & (1<<kEMuTrig)) != 0       || (thePandaFlat.trigger & (1<<kDoubleMuTrig)) != 0  ||
                         (thePandaFlat.trigger & (1<<kSingleMuTrig)) != 0  || (thePandaFlat.trigger & (1<<kDoubleEleTrig)) != 0 ||
                         (thePandaFlat.trigger & (1<<kSingleEleTrig)) != 0;
      TLorentzVector vMet,vTrkMet,vCorrMet;
      vTrkMet.SetPtEtaPhiM(thePandaFlat.trkmet,0.0,thePandaFlat.trkmetphi,0.0);
      if     (year == 2016 || year == 2018) {
        vMet    .SetPtEtaPhiM(thePandaFlat.pfmet,0.0,thePandaFlat.pfmetphi,0.0);
        vCorrMet.SetPtEtaPhiM(thePandaFlat.pfmet,0.0,thePandaFlat.pfmetphi,0.0);
      } 
      else if(year == 2017){
        vMet    .SetPtEtaPhiM(thePandaFlat.puppimet,0.0,thePandaFlat.puppimetphi,0.0);
        vCorrMet.SetPtEtaPhiM(thePandaFlat.puppimet,0.0,thePandaFlat.puppimetphi,0.0);
      }
      vCorrMet.SetPx(vMet.Px()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 0));
      vCorrMet.SetPy(vMet.Py()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 1));

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
      bool passLGSel[2] = {thePandaFlat.nLooseLep == 2 && countLeptonTight == 2 && vLoose[0].Pt() > 25 && vLoose[1].Pt() > 25 && lepType != 0 && TMath::Abs(dilep.M()-91.1876) < 15 && qTot == 0,
                           thePandaFlat.nLooseLep == 1 && countLeptonTight == 1 && vLoose[0].Pt() > 25 && passPhoSel && TMath::Abs((vLoose[0]+vPhoton).M()-91.1876) < 15};
      //if((passLGSel[0] || passLGSel[1]) && (infileCat_[ifile] == kPlotData || lepType != 2) && (thePandaFlat.trigger & (1<<kSingleEleTrig)) != 0){
      if((passLGSel[0] || passLGSel[1]) && (infileCat_[ifile] == kPlotData || lepType != 2) && passTrigger){
        int theCategoryLG = infileCat_[ifile];
        double totalLGWeight = 1.0;
	if(theCategoryLG != kPlotData){
          double puWeight  = nPUScaleFactor(fhDPU,  thePandaFlat.pu);
          double npvWeight = nPUScaleFactor(fhDNPV, thePandaFlat.npv);
          totalLGWeight = thePandaFlat.normalizedWeight * lumiV[whichYear] * npvWeight * puWeight * thePandaFlat.sf_l1Prefire * looseLepSF[0];
        }
        if(passLGSel[0]){
	  if(theCategoryLG != kPlotData){
            bool isNotMCFake = thePandaFlat.looseGenLep1PdgId != 0 && thePandaFlat.looseGenLep2PdgId != 0;
            if(theCategoryLG != kPlotData && isNotMCFake == false) totalLGWeight = 0; // theCategoryLG = kPlotNonPrompt;
	    if(theCategoryLG == kPlotqqWW || theCategoryLG == kPlotggWW || theCategoryLG == kPlotTop || theCategoryLG == kPlotHiggs || theCategoryLG == kPlotVG) totalLGWeight = 0;
            double triggerLGWeights[2] = {1.0, 0.0};
	    //trigger_sf(triggerLGWeights,thePandaFlat.nLooseLep,
	    //trgSFMMBB,trgSFMMEB,trgSFMMBE,trgSFMMEE,trgSFEEBB,trgSFEEEB,trgSFEEBE,trgSFEEEE,
	    //trgSFMEBB,trgSFMEEB,trgSFMEBE,trgSFMEEE,trgSFEMBB,trgSFEMEB,trgSFEMBE,trgSFEMEE,
	    //vLoose[0].Pt(), TMath::Abs(vLoose[0].Eta()), abs(looseLepPdgId[0]),
	    //vLoose[1].Pt(), TMath::Abs(vLoose[1].Eta()), abs(looseLepPdgId[1]));
	    totalLGWeight = totalLGWeight * looseLepSF[1] * triggerLGWeights[0];
	  }
	  else if(theCategoryLG == kPlotData && lepType == 2){
	    theCategoryLG = kPlotNonPrompt;
	    totalLGWeight = totalLGWeight * k_eff;
	  }
	  else if(lepType == 2){
	    printf("IMPOSSIBLE\n");
	  }
	  histoEGStudy[0][theCategoryLG]->Fill(dilep.M(),totalLGWeight);
	  if(TMath::Abs(dilep.M()-91.1876) < 10){ // Tighter mass window for the actual study
	    histoEGStudy[2][theCategoryLG]->Fill(TMath::Min((double)vLoose[0].Pt(), 124.999),totalLGWeight);
	    if     (TMath::Abs(vLoose[0].Eta()) < 0.5) histoEGStudy[3][theCategoryLG]->Fill(TMath::Min((double)vLoose[0].Pt(), 124.999),totalLGWeight);
	    else if(TMath::Abs(vLoose[0].Eta()) < 1.0) histoEGStudy[4][theCategoryLG]->Fill(TMath::Min((double)vLoose[0].Pt(), 124.999),totalLGWeight);
	    else if(TMath::Abs(vLoose[0].Eta()) < 1.5) histoEGStudy[5][theCategoryLG]->Fill(TMath::Min((double)vLoose[0].Pt(), 124.999),totalLGWeight);
	    else if(TMath::Abs(vLoose[0].Eta()) < 2.5) histoEGStudy[6][theCategoryLG]->Fill(TMath::Min((double)vLoose[0].Pt(), 124.999),totalLGWeight);
	    histoEGStudy[2][theCategoryLG]->Fill(TMath::Min((double)vLoose[1].Pt(), 124.999),totalLGWeight);
	    if     (TMath::Abs(vLoose[1].Eta()) < 0.5) histoEGStudy[3][theCategoryLG]->Fill(TMath::Min((double)vLoose[1].Pt(), 124.999),totalLGWeight);
	    else if(TMath::Abs(vLoose[1].Eta()) < 1.0) histoEGStudy[4][theCategoryLG]->Fill(TMath::Min((double)vLoose[1].Pt(), 124.999),totalLGWeight);
	    else if(TMath::Abs(vLoose[1].Eta()) < 1.5) histoEGStudy[5][theCategoryLG]->Fill(TMath::Min((double)vLoose[1].Pt(), 124.999),totalLGWeight);
	    else if(TMath::Abs(vLoose[1].Eta()) < 2.5) histoEGStudy[6][theCategoryLG]->Fill(TMath::Min((double)vLoose[1].Pt(), 124.999),totalLGWeight);
	  }
	  Int_t mlgxbin = nBinLGPt*(histoLGSF->GetXaxis()->FindBin(TMath::Abs(vLoose[0].Eta()))-1)+
	                           (histoLGSF->GetYaxis()->FindBin(TMath::Min((double)vLoose[0].Pt(), 124.999))-1);
          histoEGStudyMass[mlgxbin][theCategoryLG]->Fill(dilep.M(),totalLGWeight);
	        mlgxbin = nBinLGPt*(histoLGSF->GetXaxis()->FindBin(TMath::Abs(vLoose[1].Eta()))-1)+
	                           (histoLGSF->GetYaxis()->FindBin(TMath::Min((double)vLoose[1].Pt(), 124.999))-1);
          histoEGStudyMass[mlgxbin][theCategoryLG]->Fill(dilep.M(),totalLGWeight);
	}
	else {
	  if(theCategoryLG != kPlotData){
            bool isNotMCFake = thePandaFlat.looseGenLep1PdgId != 0 && thePandaFlat.looseGenPho1PdgId == 1;
            if(theCategoryLG != kPlotData && isNotMCFake == false) totalLGWeight = 0; // theCategoryLG = kPlotNonPrompt;
	    if(theCategoryLG == kPlotqqWW || theCategoryLG == kPlotggWW || theCategoryLG == kPlotTop || theCategoryLG == kPlotHiggs) totalLGWeight = 0;
            double triggerLGWeights[2] = {1.0, 0.0};
            //triggerLGWeights[0] = elTrgEffSF->GetBinContent(
	    //                      elTrgEffSF->GetXaxis()->FindFixBin(vLoose[0].Eta()),
	    //                      elTrgEffSF->GetYaxis()->FindFixBin(TMath::Min(vLoose[0].Pt(),119.99)));
            double photonSF = 1.0;
            if     (thePandaFlat.looseGenPho1PdgId == 1) { // This is what we want to measure
	    }
            else if(thePandaFlat.looseGenPho1PdgId == 3) {
              photonSF = effhDPhotonScaleFactor(vPhoton.Pt(), vPhoton.Eta(), "medium", fhDPhotonSF, fhDElectronVetoSF);
	    }
	    totalLGWeight = totalLGWeight * photonSF * triggerLGWeights[0];
	  }
	  else if(theCategoryLG == kPlotData && lepType == 2){
	    theCategoryLG = kPlotNonPrompt;
	    totalLGWeight = totalLGWeight * k_eff;
	  }
	  else if(lepType == 2){
	    printf("IMPOSSIBLE\n");
	  }
	  histoEGStudy[1][theCategoryLG]->Fill((vLoose[0]+vPhoton).M(),totalLGWeight);
	  if(TMath::Abs((vLoose[0]+vPhoton).M()-91.1876) < 10){ // Tighter mass window for the actual study
	    histoEGStudy[7][theCategoryLG]->Fill(TMath::Min((double)vPhoton.Pt(), 124.999),totalLGWeight);
	    if     (TMath::Abs(vPhoton.Eta()) < 0.5) histoEGStudy[ 8][theCategoryLG]->Fill(TMath::Min((double)vPhoton.Pt(), 124.999),totalLGWeight);
	    else if(TMath::Abs(vPhoton.Eta()) < 1.0) histoEGStudy[ 9][theCategoryLG]->Fill(TMath::Min((double)vPhoton.Pt(), 124.999),totalLGWeight);
	    else if(TMath::Abs(vPhoton.Eta()) < 1.5) histoEGStudy[10][theCategoryLG]->Fill(TMath::Min((double)vPhoton.Pt(), 124.999),totalLGWeight);
	    else if(TMath::Abs(vPhoton.Eta()) < 2.5) histoEGStudy[11][theCategoryLG]->Fill(TMath::Min((double)vPhoton.Pt(), 124.999),totalLGWeight);
          }
	  Int_t mlgxbin = nBinLGPt*(histoLGSF->GetXaxis()->FindBin(TMath::Abs(vPhoton.Eta()))-1)+
	                           (histoLGSF->GetYaxis()->FindBin(TMath::Min((double)vPhoton.Pt(), 124.999))-1);
          histoEGStudyMass[nBinLGPt*nBinLGEta+mlgxbin][theCategoryLG]->Fill((vLoose[0]+vPhoton).M(),totalLGWeight);
	}
      } // end eg analysis

      // begin mg analysis
      if(passLGSel[1] && lepType == 2 && (thePandaFlat.trigger & (1<<kSingleMuTrig)) != 0){
        int theCategoryLG = infileCat_[ifile];
        double totalLGWeight = 1.0;
	if(theCategoryLG != kPlotData){
          double puWeight  = nPUScaleFactor(fhDPU,  thePandaFlat.pu);
          double npvWeight = nPUScaleFactor(fhDNPV, thePandaFlat.npv);
          totalLGWeight = thePandaFlat.normalizedWeight * lumiV[whichYear] * npvWeight * puWeight * thePandaFlat.sf_l1Prefire * looseLepSF[0];

          bool isNotMCFake = thePandaFlat.looseGenLep1PdgId != 0 && thePandaFlat.looseGenPho1PdgId == 1;
          if(theCategoryLG != kPlotData && isNotMCFake == false) theCategoryLG = kPlotNonPrompt;
          double triggerLGWeights[2] = {1.0, 0.0};
	  triggerLGWeights[0]  = muTrgEffSF->GetBinContent(
	                         muTrgEffSF->GetXaxis()->FindFixBin(vLoose[0].Eta()),
	                         muTrgEffSF->GetYaxis()->FindFixBin(TMath::Min(vLoose[0].Pt(),119.99)));
          double photonSF = 1.0;
          if	 (thePandaFlat.looseGenPho1PdgId == 1) {
	    int nxbin = fhDElePhoSF->GetXaxis()->FindBin(TMath::Abs(vPhoton.Eta()));
	    int nybin = fhDElePhoSF->GetYaxis()->FindBin(TMath::Min((double)vPhoton.Pt(), 124.999));
            photonSF = fhDElePhoSF->GetBinContent(nxbin, nybin);
	  }
          else if(thePandaFlat.looseGenPho1PdgId == 3) {
            photonSF = effhDPhotonScaleFactor(vPhoton.Pt(), vPhoton.Eta(), "medium", fhDPhotonSF, fhDElectronVetoSF);
	  }
	  totalLGWeight = totalLGWeight * photonSF * triggerLGWeights[0];
        }
	histoMGStudy[0][theCategoryLG]->Fill((vLoose[0]+vPhoton).M(),totalLGWeight);
        double dPhiGMET = TMath::Abs(vPhoton.DeltaPhi(vMet));
	histoMGStudy[1][theCategoryLG]->Fill(TMath::Min(TMath::Sqrt(2.0*vPhoton.Pt()*vMet.Pt()*(1.0 - cos(dPhiGMET))), 199.999),totalLGWeight);
      } // end mg analysis

      if(passTrigger == false) continue;

      double dPhiDiLepMET = TMath::Abs(dilep.DeltaPhi(vMet));
      double dPhiDiLepCorrMET = TMath::Abs(dilep.DeltaPhi(vCorrMet));
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

      // dilepton anaysis from now one
      if(thePandaFlat.nLooseLep != 2) continue;

      bool passSel = ((lepType != 2 && TMath::Abs(dilep.M()-91.1876) < 15) || (lepType == 2 && dilep.M() > 50 && thePandaFlat.jetNBtags > 0)) && vLoose[0].Pt() > 20 && vLoose[1].Pt() > 20;
      if     (isTopSel == true && lepType == 2) passSel = dilep.M() > 50 && vLoose[0].Pt() > 25 && vLoose[1].Pt() > 25 && mtW > 50 && thePandaFlat.nJet >= 1;
      else if(isTopSel == true && lepType != 2) passSel = dilep.M() > 15 && dilep.M() < 55 && vLoose[0].Pt() > 25 && vLoose[1].Pt() > 25 && thePandaFlat.nJet == 1 && thePandaFlat.nJot >= 2 && thePandaFlat.jetNBtags >= 1;
      if(passSel == false) continue;

      double totalWeight = 1.0; double sfWS = 1.0; double totalWeightNoVtx = 1.0;
      if     (theCategory != kPlotData){
        double triggerWeights[2] = {1.0, 0.0};
	trigger_sf(triggerWeights,thePandaFlat.nLooseLep,
	trgSFMMBB,trgSFMMEB,trgSFMMBE,trgSFMMEE,trgSFEEBB,trgSFEEEB,trgSFEEBE,trgSFEEEE,
	trgSFMEBB,trgSFMEEB,trgSFMEBE,trgSFMEEE,trgSFEMBB,trgSFEMEB,trgSFEMBE,trgSFEMEE,
	vLoose[0].Pt(), TMath::Abs(vLoose[0].Eta()), abs(looseLepPdgId[0]),
	vLoose[1].Pt(), TMath::Abs(vLoose[1].Eta()), abs(looseLepPdgId[1]));

        double puWeight  = nPUScaleFactor(fhDPU,  thePandaFlat.pu);
        double npvWeight = nPUScaleFactor(fhDNPV, thePandaFlat.npv);

        totalWeight      = thePandaFlat.normalizedWeight * lumiV[whichYear] * puWeight * thePandaFlat.sf_l1Prefire * looseLepSF[0] * looseLepSF[1] * triggerWeights[0] * npvWeight;
        totalWeightNoVtx = thePandaFlat.normalizedWeight * lumiV[whichYear] * puWeight * thePandaFlat.sf_l1Prefire * looseLepSF[0] * looseLepSF[1] * triggerWeights[0];

        if     (infileCat_[ifile] == kPlotWZ)                                                totalWeight = totalWeight * thePandaFlat.sf_wz;
	else if(infileCat_[ifile] == kPlotZZ && infileName_[ifile].Contains("qqZZ") == true) totalWeight = totalWeight * thePandaFlat.sf_zz;
	else if(infileCat_[ifile] == kPlotVG) totalWeight = 0.0;

        totalWeight = totalWeight * mcCorrection(2, year, thePandaFlat.jetNMBtags,thePandaFlat.jetNBtags, thePandaFlat.nJot, dPhiDiLepMET, infileCat_[ifile]);

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
	    sfWS = WSSF[histoEtaCorr->GetXaxis()->FindBin(TMath::Min(TMath::Abs(vLoose[theWSLepton].Eta()),2.4999))-1];
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
	  nEta[i] = histoEtaCorr->GetXaxis()->FindBin(TMath::Min(TMath::Abs(vLoose[i].Eta()),2.4999))-1;
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
      histo[lepType+12][theCategory]->Fill(TMath::Min(dilep.Pt(), 399.999),totalWeight);
      histo[lepType+15][theCategory]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeight);
      histo[lepType+18][theCategory]->Fill(TMath::Min((double)thePandaFlat.trkmet, 399.999),totalWeight);
      histo[lepType+21][theCategory]->Fill(TMath::Min((double)vCorrMet.Pt(), 399.999),totalWeight);
      histo[lepType+24][theCategory]->Fill(vMet.Phi(),totalWeight);
      histo[lepType+27][theCategory]->Fill(dPhiDiLepMET,totalWeight);
      histo[lepType+30][theCategory]->Fill(dPhiDiLepCorrMET,totalWeight);
      histo[lepType+33][theCategory]->Fill(dphill,totalWeight);
      histo[lepType+36][theCategory]->Fill(TMath::Min(ptFrac,4.999),totalWeight);
      histo[lepType+39][theCategory]->Fill(TMath::Min(drll,4.999),totalWeight);
      histo[lepType+42][theCategory]->Fill(TMath::Min((double)thePandaFlat.npv,79.499),totalWeight);
      histo[lepType+45][theCategory]->Fill(vLoose[0].Eta(),totalWeight);
      histo[lepType+45][theCategory]->Fill(vLoose[1].Eta(),totalWeight);
      histo[lepType+48][theCategory]->Fill(TMath::Min((double)vLoose[0].Pt(), 219.999),totalWeight);
      histo[lepType+48][theCategory]->Fill(TMath::Min((double)vLoose[1].Pt(), 219.999),totalWeight);
      histo[lepType+51][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNBtags,4.4999),totalWeight);
      histo[lepType+54][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNMBtags,4.4999),totalWeight);

      // only for mm/ee events
      if(lepType == 2) continue;

      if(thePandaFlat.nJot == 1){
        histo[57][theCategory]->Fill(TMath::Min((double)thePandaFlat.jotPt[0],229.9999),totalWeight);
	if(TMath::Abs(thePandaFlat.jotEta[0]) < 2.4)
        histo[58][theCategory]->Fill(TMath::Max(TMath::Min((double)thePandaFlat.jotCSV[0],0.999),0.001),totalWeight);
        histo[59][theCategory]->Fill(thePandaFlat.jotEta[0],totalWeight);     
        histo[60][theCategory]->Fill(thePandaFlat.jotPhi[0],totalWeight);
        if(thePandaFlat.jotPt[0] > 60.0){
	  if     (TMath::Abs(thePandaFlat.jotEta[0]) < 2.4){
            histo[61][theCategory]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeight);
            histo[62][theCategory]->Fill(TMath::Min((double)vCorrMet.Pt(), 399.999),totalWeight);
            histo[63][theCategory]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeightNoVtx);
            histo[64][theCategory]->Fill(TMath::Min((double)vCorrMet.Pt(), 399.999),totalWeightNoVtx);
          }
	  else if(TMath::Abs(thePandaFlat.jotEta[0]) < 3.139){
            histo[65][theCategory]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeight);
            histo[66][theCategory]->Fill(TMath::Min((double)vCorrMet.Pt(), 399.999),totalWeight);
            histo[67][theCategory]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeightNoVtx);
            histo[68][theCategory]->Fill(TMath::Min((double)vCorrMet.Pt(), 399.999),totalWeightNoVtx);
          }
	  else {
            histo[69][theCategory]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeight);
            histo[70][theCategory]->Fill(TMath::Min((double)vCorrMet.Pt(), 399.999),totalWeight);
            histo[71][theCategory]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeightNoVtx);
            histo[72][theCategory]->Fill(TMath::Min((double)vCorrMet.Pt(), 399.999),totalWeightNoVtx);
	  }
	} // ptjet > 50
      } // njet == 1
      histo[73][theCategory]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeight);
      histo[74][theCategory]->Fill(TMath::Min((double)vCorrMet.Pt(), 399.999),totalWeight);
      histo[75][theCategory]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeightNoVtx);
      histo[76][theCategory]->Fill(TMath::Min((double)vCorrMet.Pt(), 399.999),totalWeightNoVtx);
      if(thePandaFlat.jotPt[0] > 100){
        histo[77][theCategory]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeight);
        histo[78][theCategory]->Fill(TMath::Min((double)vCorrMet.Pt(), 399.999),totalWeight);
        histo[79][theCategory]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeightNoVtx);
        histo[80][theCategory]->Fill(TMath::Min((double)vCorrMet.Pt(), 399.999),totalWeightNoVtx);
      }
      if(thePandaFlat.jotPt[0] > 100 && TMath::Abs(thePandaFlat.jotEta[0]) < 2.5){
        histo[81][theCategory]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeight);
        histo[82][theCategory]->Fill(TMath::Min((double)vCorrMet.Pt(), 399.999),totalWeight);
        histo[83][theCategory]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeightNoVtx);
        histo[84][theCategory]->Fill(TMath::Min((double)vCorrMet.Pt(), 399.999),totalWeightNoVtx);
      }
      histo[85][theCategory]->Fill(TMath::Min((double)thePandaFlat.pfmetRaw, 399.999),totalWeight);
      histo[86][theCategory]->Fill(TMath::Min((double)thePandaFlat.calomet, 399.999),totalWeight);
      histo[87][theCategory]->Fill(vCorrMet.Phi(),totalWeight);

      // Mass study
      int nEtaMass[2] = {-1, -1};
      if     (TMath::Abs(vLoose[0].Eta()) < 0.5) nEtaMass[0] = 0;
      else if(TMath::Abs(vLoose[0].Eta()) < 1.0) nEtaMass[0] = 1;
      else if(TMath::Abs(vLoose[0].Eta()) < 1.5) nEtaMass[0] = 2;
      else if(TMath::Abs(vLoose[0].Eta()) < 2.0) nEtaMass[0] = 3;
      else				         nEtaMass[0] = 4;
      if     (TMath::Abs(vLoose[1].Eta()) < 0.5) nEtaMass[1] = 0;
      else if(TMath::Abs(vLoose[1].Eta()) < 1.0) nEtaMass[1] = 1;
      else if(TMath::Abs(vLoose[1].Eta()) < 1.5) nEtaMass[1] = 2;
      else if(TMath::Abs(vLoose[1].Eta()) < 2.0) nEtaMass[1] = 3;
      else				         nEtaMass[1] = 4;
      if     (nEtaMass[0] == nEtaMass[1])           histo[5*lepType+ 88 + nEtaMass[0]][theCategory]->Fill(dilep.M(),totalWeight);
      else if((nEtaMass[0] == 0 && nEtaMass[1] == 1) ||
              (nEtaMass[0] == 1 && nEtaMass[1] == 0)) histo[lepType+ 98][theCategory]->Fill(dilep.M(),totalWeight);
      else if((nEtaMass[0] == 0 && nEtaMass[1] == 2) ||
              (nEtaMass[0] == 2 && nEtaMass[1] == 0)) histo[lepType+100][theCategory]->Fill(dilep.M(),totalWeight);
      else if((nEtaMass[0] == 0 && nEtaMass[1] == 3) ||
              (nEtaMass[0] == 3 && nEtaMass[1] == 0)) histo[lepType+102][theCategory]->Fill(dilep.M(),totalWeight);
      else if((nEtaMass[0] == 0 && nEtaMass[1] == 4) ||
              (nEtaMass[0] == 4 && nEtaMass[1] == 0)) histo[lepType+104][theCategory]->Fill(dilep.M(),totalWeight);
      else if((nEtaMass[0] == 1 && nEtaMass[1] == 2) ||
              (nEtaMass[0] == 2 && nEtaMass[1] == 1)) histo[lepType+106][theCategory]->Fill(dilep.M(),totalWeight);
      else if((nEtaMass[0] == 1 && nEtaMass[1] == 3) ||
              (nEtaMass[0] == 3 && nEtaMass[1] == 1)) histo[lepType+108][theCategory]->Fill(dilep.M(),totalWeight);
      else if((nEtaMass[0] == 1 && nEtaMass[1] == 4) ||
              (nEtaMass[0] == 4 && nEtaMass[1] == 1)) histo[lepType+110][theCategory]->Fill(dilep.M(),totalWeight);
      else if((nEtaMass[0] == 2 && nEtaMass[1] == 3) ||
              (nEtaMass[0] == 3 && nEtaMass[1] == 2)) histo[lepType+112][theCategory]->Fill(dilep.M(),totalWeight);
      else if((nEtaMass[0] == 2 && nEtaMass[1] == 4) ||
              (nEtaMass[0] == 4 && nEtaMass[1] == 2)) histo[lepType+114][theCategory]->Fill(dilep.M(),totalWeight);
      else if((nEtaMass[0] == 3 && nEtaMass[1] == 4) ||
              (nEtaMass[0] == 4 && nEtaMass[1] == 3)) histo[lepType+116][theCategory]->Fill(dilep.M(),totalWeight);
      else printf("IMPOSSIBLE MASS COMBINATION %d %d\n",nEtaMass[0],nEtaMass[1]);

      // Dijet study
      if(thePandaFlat.nJot >= 2 && thePandaFlat.jotEta[0]*thePandaFlat.jotEta[1] < 0 &&
        (thePandaFlat.jotPt[0] > 50 || TMath::Abs(thePandaFlat.jotEta[0]) < 2.4) &&
	(thePandaFlat.jotPt[1] > 50 || TMath::Abs(thePandaFlat.jotEta[1]) < 2.4)){
        histo[118][theCategory]->Fill(thePandaFlat.jot12Mass,totalWeight);
        histo[119][theCategory]->Fill(thePandaFlat.jot12DEta,totalWeight);
        histo[120][theCategory]->Fill(thePandaFlat.jot12DPhi,totalWeight);
        histo[121][theCategory]->Fill(thePandaFlat.jotEta[0],totalWeight);histo[121][theCategory]->Fill(thePandaFlat.jotEta[1],totalWeight);
        histo[122][theCategory]->Fill(thePandaFlat.jotPt[0],totalWeight);histo[122][theCategory]->Fill(thePandaFlat.jotPt[1],totalWeight);
        if(thePandaFlat.jot12Mass > 500){
          histo[123][theCategory]->Fill(thePandaFlat.jot12Mass,totalWeight);
          histo[124][theCategory]->Fill(thePandaFlat.jot12DEta,totalWeight);
          histo[125][theCategory]->Fill(thePandaFlat.jot12DPhi,totalWeight);
          histo[126][theCategory]->Fill(thePandaFlat.jotEta[0],totalWeight);histo[126][theCategory]->Fill(thePandaFlat.jotEta[1],totalWeight);
          histo[127][theCategory]->Fill(thePandaFlat.jotPt[0],totalWeight);histo[127][theCategory]->Fill(thePandaFlat.jotPt[1],totalWeight);
	}
      }

      // HEM study
      if(year == 2018){
        double dPhiJetMET = -0.5;
	if(thePandaFlat.nJot >= 1){
          TLorentzVector vJetTemp;
          vJetTemp.SetPtEtaPhiM(thePandaFlat.jotPt[0],thePandaFlat.jotEta[0],thePandaFlat.jotPhi[0],0.0);
          dPhiJetMET = TMath::Abs(vJetTemp.DeltaPhi(vMet));
	}
	if(theCategory == kPlotData){
          int isHEMRun = (int)(thePandaFlat.runNumber >= 319077);
	  histoDataHEM[0][isHEMRun]->Fill(dilep.M(),totalWeight);
	  histoDataHEM[1][isHEMRun]->Fill(TMath::Min((double)thePandaFlat.nJot,4.4999),totalWeight);
	  histoDataHEM[2][isHEMRun]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeight);
	  histoDataHEM[3][isHEMRun]->Fill(TMath::Min(dilep.Pt(), 399.999),totalWeight);
	  histoDataHEM[4][isHEMRun]->Fill(vMet.Phi(),totalWeight);
	  histoDataHEM[5][isHEMRun]->Fill(dPhiDiLepMET,totalWeight);
	  histoDataHEM[6][isHEMRun]->Fill(TMath::Min((double)thePandaFlat.npv,79.499),totalWeight);
	  if     (thePandaFlat.nJot == 0) histoDataHEM[7][isHEMRun]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeight);
	  else if(thePandaFlat.nJot == 1) histoDataHEM[8][isHEMRun]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeight);
	  if     (thePandaFlat.nJot == 1 && TMath::Abs(thePandaFlat.jotEta[0]) < 2.5) histoDataHEM[ 9][isHEMRun]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeight);
	  else if(thePandaFlat.nJot == 1) histoDataHEM[10][isHEMRun]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeight);
	  histoDataHEM[11][isHEMRun]->Fill(TMath::Min(dPhiJetMET, 2.999),totalWeight);
          int isABCRun = (int)(thePandaFlat.runNumber <= 320393)+2;
	  histoDataHEM[0][isABCRun]->Fill(dilep.M(),totalWeight);
	  histoDataHEM[1][isABCRun]->Fill(TMath::Min((double)thePandaFlat.nJot,4.4999),totalWeight);
	  histoDataHEM[2][isABCRun]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeight);
	  histoDataHEM[3][isABCRun]->Fill(TMath::Min(dilep.Pt(), 399.999),totalWeight);
	  histoDataHEM[4][isABCRun]->Fill(vMet.Phi(),totalWeight);
	  histoDataHEM[5][isABCRun]->Fill(dPhiDiLepMET,totalWeight);
	  histoDataHEM[6][isABCRun]->Fill(TMath::Min((double)thePandaFlat.npv,79.499),totalWeight);
	  if     (thePandaFlat.nJot == 0) histoDataHEM[7][isABCRun]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeight);
	  else if(thePandaFlat.nJot == 1) histoDataHEM[8][isABCRun]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeight);
	  if     (thePandaFlat.nJot == 1 && TMath::Abs(thePandaFlat.jotEta[0]) < 2.5) histoDataHEM[ 9][isABCRun]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeight);
	  else if(thePandaFlat.nJot == 1) histoDataHEM[10][isABCRun]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeight);
	  histoDataHEM[11][isABCRun]->Fill(TMath::Min(dPhiJetMET, 2.999),totalWeight);
	}
	bool isLSR = (vLoose[0].Eta() > -3.0 && vLoose[0].Eta() < -1.3 && vLoose[0].Phi() > -1.57 && vLoose[0].Phi() < -0.87) ||
                     (vLoose[1].Eta() > -3.0 && vLoose[1].Eta() < -1.3 && vLoose[1].Phi() > -1.57 && vLoose[1].Phi() < -0.87);
	bool isLCR = (vLoose[0].Eta() > -3.0 && vLoose[0].Eta() < -1.3 && vLoose[0].Phi() > -0.87 && vLoose[0].Phi() < -0.17) ||
                     (vLoose[1].Eta() > -3.0 && vLoose[1].Eta() < -1.3 && vLoose[1].Phi() > -0.87 && vLoose[1].Phi() < -0.17);
	if(isLSR) histoHEM[0][theCategory]->Fill(dilep.M(),totalWeight);
	if(isLCR) histoHEM[1][theCategory]->Fill(dilep.M(),totalWeight);
	if(isLSR) histoHEM[2][theCategory]->Fill(TMath::Min((double)vLoose[0].Pt(), 219.999),totalWeight);
	if(isLCR) histoHEM[3][theCategory]->Fill(TMath::Min((double)vLoose[0].Pt(), 219.999),totalWeight);
	if(isLSR) histoHEM[4][theCategory]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeight);
	if(isLCR) histoHEM[5][theCategory]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeight);
	if(thePandaFlat.nJot >= 1){
          bool isJSR = thePandaFlat.jotEta[0] > -3.0 && thePandaFlat.jotEta[0] < -1.3 && thePandaFlat.jotPhi[0] > -1.57 && thePandaFlat.jotPhi[0] < -0.87;
          bool isJCR = thePandaFlat.jotEta[0] > -3.0 && thePandaFlat.jotEta[0] < -1.3 && thePandaFlat.jotPhi[0] > -0.87 && thePandaFlat.jotPhi[0] < -0.17;
	  if(isJSR) histoHEM[ 6][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJot,4.4999),totalWeight);
	  if(isJCR) histoHEM[ 7][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJot,4.4999),totalWeight);
	  if(isJSR) histoHEM[ 8][theCategory]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeight);
	  if(isJCR) histoHEM[ 9][theCategory]->Fill(TMath::Min((double)vMet.Pt(), 399.999),totalWeight);
	  if(isJSR) histoHEM[10][theCategory]->Fill(TMath::Min((double)thePandaFlat.jotPt[0], 229.999),totalWeight);
	  if(isJCR) histoHEM[11][theCategory]->Fill(TMath::Min((double)thePandaFlat.jotPt[0], 229.999),totalWeight);
          if(isJSR) histoHEM[12][theCategory]->Fill(TMath::Min((double)vLoose[0].Pt(), 219.999),totalWeight);
          if(isJCR) histoHEM[13][theCategory]->Fill(TMath::Min((double)vLoose[0].Pt(), 219.999),totalWeight);
	}
	if(vLoose[0].Eta() > -3.0 && vLoose[0].Eta() < -1.3){
          if(abs(looseLepPdgId[0]) == 13) histoHEM[14][theCategory]->Fill(vLoose[0].Phi(),totalWeight);
	  else                            histoHEM[15][theCategory]->Fill(vLoose[0].Phi(),totalWeight);
	}
	if(vLoose[1].Eta() > -3.0 && vLoose[1].Eta() < -1.3){
          if(abs(looseLepPdgId[1]) == 13) histoHEM[14][theCategory]->Fill(vLoose[1].Phi(),totalWeight);
	  else                            histoHEM[15][theCategory]->Fill(vLoose[1].Phi(),totalWeight);
	}
	if(passPhoSel == true && vPhoton.Eta() > -3.0 && vPhoton.Eta() < -1.3){
          histoHEM[16][theCategory]->Fill(vPhoton.Phi(),totalWeight);
	}
	if(thePandaFlat.nJot == 1){
          if(thePandaFlat.jotEta[0] > -3.0 && thePandaFlat.jotEta[0] < -1.3){
            histoHEM[17][theCategory]->Fill(thePandaFlat.jotPhi[0],totalWeight);
	    if(vMet.Pt() > 50){
              histoHEM[18][theCategory]->Fill(thePandaFlat.jotPhi[0],totalWeight);
	      histoHEM[19][theCategory]->Fill(dPhiJetMET,totalWeight);
	    }
	  }
	  if(vMet.Pt() > 50){
            histoHEM[20][theCategory]->Fill(thePandaFlat.jotPhi[0],totalWeight);
	    histoHEM[21][theCategory]->Fill(dPhiJetMET,totalWeight);
	    if(dPhiJetMET > 2.6){
              histoHEM[22][theCategory]->Fill(thePandaFlat.jotPhi[0],totalWeight);
	    }
	  }
	  
        }
      } // End HEM1516 study

      // Lepton efficiency study     
      int theEffStudyCategory = 0; double totalEffStudyWeight = totalWeight;
      if     (theCategory == kPlotData) {}
      else if(theCategory == kPlotDY)   {theEffStudyCategory = 1;}
      else			       {totalEffStudyWeight = -1.0 * totalEffStudyWeight;};
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
          if(passLepSel[nsel]) histoEffStudy[nsel][lepType][theEffStudyCategory]->Fill(vLoose[ilep].Eta(),TMath::Min((double)vLoose[ilep].Pt(), 99.999),totalEffStudyWeight);
	}
      }

      if(thePandaFlat.npv < 80){
	histoMETStudy[0][(int)thePandaFlat.npv/4][theEffStudyCategory]->Fill(vMet.Px(),totalEffStudyWeight);
	histoMETStudy[1][(int)thePandaFlat.npv/4][theEffStudyCategory]->Fill(vMet.Py(),totalEffStudyWeight);
	histoMETStudy[2][(int)thePandaFlat.npv/4][theEffStudyCategory]->Fill(vCorrMet.Px(),totalEffStudyWeight);
	histoMETStudy[3][(int)thePandaFlat.npv/4][theEffStudyCategory]->Fill(vCorrMet.Py(),totalEffStudyWeight);
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
  printf("--------------ZMass---------------\n");
  {
  printf("muScale:%f,%f,%f,%f,%f\n",histo[88][kPlotData]->GetMean()/histo[88][kPlotDY]->GetMean(),histo[89][kPlotData]->GetMean()/histo[89][kPlotDY]->GetMean(),
                                    histo[90][kPlotData]->GetMean()/histo[90][kPlotDY]->GetMean(),histo[91][kPlotData]->GetMean()/histo[91][kPlotDY]->GetMean(),
				    histo[92][kPlotData]->GetMean()/histo[92][kPlotDY]->GetMean());
  printf("elScale:%f,%f,%f,%f,%f\n",histo[93][kPlotData]->GetMean()/histo[93][kPlotDY]->GetMean(),histo[94][kPlotData]->GetMean()/histo[94][kPlotDY]->GetMean(),
                                    histo[95][kPlotData]->GetMean()/histo[95][kPlotDY]->GetMean(),histo[96][kPlotData]->GetMean()/histo[96][kPlotDY]->GetMean(),
				    histo[97][kPlotData]->GetMean()/histo[97][kPlotDY]->GetMean());
  }

  { // Trigger study
    for(int nt=0; nt<2; nt++){
      histoTrgEffStudy[1][nt]->Divide(histoTrgEffStudy[0][nt]);
      histoTrgEffStudy[3][nt]->Divide(histoTrgEffStudy[2][nt]);
    }
    histoMuTrgEffSF->Add(histoTrgEffStudy[1][0]); histoMuTrgEffSF->Divide(histoTrgEffStudy[1][1]);
    histoElTrgEffSF->Add(histoTrgEffStudy[3][0]); histoElTrgEffSF->Divide(histoTrgEffStudy[3][1]);
    sprintf(output,"histoDY%d%sTriggerSFStudy_%d.root",whichDY,addSuffix.Data(),year);	
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    histoMuTrgEffSF->Write();
    histoElTrgEffSF->Write();
    for(int nt=0; nt<2; nt++){
      histoTrgEffStudy[1][nt]->Write();
      histoTrgEffStudy[3][nt]->Write();
    }
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
    int iterWS = 0;
    for(int i=0; i<nWSBins; i++){
      for(int j=0; j<nWSBins; j++){
        if(j>i) continue;
        double eff[2]  = {histoWSStudy[i][j][1]->GetSumOfWeights()/histoWSStudy[i][j][0]->GetSumOfWeights(),
	                  histoWSStudy[i][j][3]->GetSumOfWeights()/histoWSStudy[i][j][2]->GetSumOfWeights()
			 };
        double effE[2] = {sqrt((1-eff[0])*eff[0]/histoWSStudy[i][j][0]->GetSumOfWeights()),
	                  sqrt((1-eff[1])*eff[1]/histoWSStudy[i][j][2]->GetSumOfWeights())
			 };
        //printf("(%d,%d): %.7f+/-%.7f/%.7f+/-%.7f = %.7f+/-%.7f\n",i,j,eff[0],effE[0],eff[1],effE[1],eff[0]/eff[1],eff[0]/eff[1]*sqrt(effE[0]/eff[0]*effE[0]/eff[0]+effE[1]/eff[1]*effE[1]/eff[1]));
        printf("zA[%2d]=%.7f;errorzA[%2d]=%.7f;zB[%2d]=%.7f;errorzB[%2d]=%.7f;\n",iterWS,eff[0],iterWS,effE[0],iterWS,eff[1],iterWS,effE[1]);
	iterWS++;
      }
    }

    sprintf(output,"histoDY%dWSStudy_%d%s.root",whichDY,year,addSuffix.Data());	
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    for(int i=0; i<nWSBins; i++){
      for(int j=0; j<nWSBins; j++){
        if(j>i) continue;
        for(int np=0; np<4; np++){
          histoWSStudy[i][j][np]->Write();
        }
      }
    }
    outFilePlotsNote->Close();
  }

  { // EG study, making pain text format gStyle->SetPaintTextFormat(".3f")
    printf("---------------EG Study---------------\n");
    int valLL[4] = {3, 4, 5, 6};
    int valLG[4] = {8, 9,10,11};
    double effda, effmc, effdaE, effmcE, sf, sfE;
    for(int netab=0; netab<4; netab++){
      for(int i=1; i<=histoEGStudy[valLL[netab]][0]->GetNbinsX(); i++){
        double totBck[2] = {0, 0};
        for(int ic=1; ic<nPlotCategories; ic++) {
          if(ic == kPlotDY) continue;
          totBck[0] = totBck[0] + histoEGStudy[valLL[netab]][ic]->GetBinContent(i);
          totBck[1] = totBck[1] + histoEGStudy[valLG[netab]][ic]->GetBinContent(i);
        }
        effda = (histoEGStudy[valLG[netab]][kPlotData]->GetBinContent(i)-totBck[1]) /
                (histoEGStudy[valLL[netab]][kPlotData]->GetBinContent(i)-totBck[0]);
        effmc = histoEGStudy[valLG[netab]][kPlotDY]->GetBinContent(i) /
                histoEGStudy[valLL[netab]][kPlotDY]->GetBinContent(i);
        effdaE = sqrt((1-effda)*effda/(histoEGStudy[valLL[netab]][kPlotData]->GetBinContent(i)-totBck[0]));
        effmcE = sqrt((1-effmc)*effmc/histoEGStudy[valLL[netab]][kPlotDY]->GetBinContent(i));
        sf = effda/effmc;
        sfE = effda/effmc*sqrt(effdaE/effda*effdaE/effda+effmcE/effmc*effmcE/effmc);
        printf("(%d,%2d): %.3f +/- %.3f / %.3f +/- %.3f = %.3f +/- %.3f\n",netab,i,effda,effdaE,effmc,effmcE,sf,sfE);
        histoLGEffda->SetBinContent(netab+1, i, effda );
        histoLGEffda->SetBinError  (netab+1, i, effdaE);
        histoLGEffmc->SetBinContent(netab+1, i, effmc );
        histoLGEffmc->SetBinError  (netab+1, i, effmcE);
        histoLGSF   ->SetBinContent(netab+1, i, sf    );
        histoLGSF   ->SetBinError  (netab+1, i, sqrt(sfE*sfE+0.2*0.2));
      } // pt bins
    } // 4 eta bins
    sprintf(output,"histoDY%dLGSF_%d%s.root",whichDY,year,addSuffix.Data());
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    histoLGSF   ->GetXaxis()->SetTitle("|#eta^{#gamma}|");histoLGSF   ->GetYaxis()->SetTitle("p_{T}^{#gamma} [GeV]");histoLGSF   ->Write();
    histoLGEffda->GetXaxis()->SetTitle("|#eta^{#gamma}|");histoLGEffda->GetYaxis()->SetTitle("p_{T}^{#gamma} [GeV]");histoLGEffda->Write();
    histoLGEffmc->GetXaxis()->SetTitle("|#eta^{#gamma}|");histoLGEffmc->GetYaxis()->SetTitle("p_{T}^{#gamma} [GeV]");histoLGEffmc->Write();
    outFilePlotsNote->Close();
    for(int np=0; np<12; np++){
      sprintf(output,"histoDY%dEGStudy_%d%s_%d.root",whichDY,year,addSuffix.Data(),np);
      TFile* outFilePlotsNote = new TFile(output,"recreate");
      outFilePlotsNote->cd();
      double totBck = 0;
      for(int i=1; i<nPlotCategories; i++) totBck = totBck + histoEGStudy[np][i]->GetSumOfWeights();
      printf("(%d) %f (%f+%f+%f+%f+%f+%f+%f+%f+%f+%f)=%f\n",np,histoEGStudy[np][0]->GetSumOfWeights(),
      histoEGStudy[np][1]->GetSumOfWeights(),histoEGStudy[np][2]->GetSumOfWeights(),
      histoEGStudy[np][3]->GetSumOfWeights(),histoEGStudy[np][4]->GetSumOfWeights(),
      histoEGStudy[np][5]->GetSumOfWeights(),histoEGStudy[np][6]->GetSumOfWeights(),
      histoEGStudy[np][7]->GetSumOfWeights(),histoEGStudy[np][8]->GetSumOfWeights(),
      histoEGStudy[np][9]->GetSumOfWeights(),histoEGStudy[np][10]->GetSumOfWeights(),
      totBck);
      double totBckNoZ = totBck - histoEGStudy[np][kPlotDY]->GetSumOfWeights();
      histoEGStudy[np][kPlotDY]->Scale((histoEGStudy[np][kPlotData]->GetSumOfWeights()-totBckNoZ)/histoEGStudy[np][kPlotDY]->GetSumOfWeights());
      for(int nc=0; nc<nPlotCategories; nc++) histoEGStudy[np][nc]->Write();
      outFilePlotsNote->Close();
    }
    for(int np=0; np<nBinLGEta*nBinLGPt*2; np++){
      sprintf(output,"histoDY%dEGStudyMass_%d%s_%d.root",whichDY,year,addSuffix.Data(),np);
      TFile* outFilePlotsNote = new TFile(output,"recreate");
      outFilePlotsNote->cd();
      double totBck = 0;
      for(int i=1; i<nPlotCategories; i++) totBck = totBck + histoEGStudyMass[np][i]->GetSumOfWeights();
      printf("(%d) %f (%f+%f+%f+%f+%f+%f+%f+%f+%f+%f)=%f\n",np,histoEGStudyMass[np][0]->GetSumOfWeights(),
      histoEGStudyMass[np][1]->GetSumOfWeights(),histoEGStudyMass[np][2]->GetSumOfWeights(),
      histoEGStudyMass[np][3]->GetSumOfWeights(),histoEGStudyMass[np][4]->GetSumOfWeights(),
      histoEGStudyMass[np][5]->GetSumOfWeights(),histoEGStudyMass[np][6]->GetSumOfWeights(),
      histoEGStudyMass[np][7]->GetSumOfWeights(),histoEGStudyMass[np][8]->GetSumOfWeights(),
      histoEGStudyMass[np][9]->GetSumOfWeights(),histoEGStudyMass[np][10]->GetSumOfWeights(),
      totBck);
      double totBckNoZ = totBck - histoEGStudyMass[np][kPlotDY]->GetSumOfWeights();
      histoEGStudyMass[np][kPlotDY]->Scale((histoEGStudyMass[np][kPlotData]->GetSumOfWeights()-totBckNoZ)/histoEGStudyMass[np][kPlotDY]->GetSumOfWeights());
      for(int nc=0; nc<nPlotCategories; nc++) histoEGStudyMass[np][nc]->Write();
      outFilePlotsNote->Close();
    }
  }

  { // MG study
    printf("---------------MG Study---------------\n");
    for(int np=0; np<2; np++){
      sprintf(output,"histoDY%dMGStudy_%d%s_%d.root",whichDY,year,addSuffix.Data(),np);
      TFile* outFilePlotsNote = new TFile(output,"recreate");
      outFilePlotsNote->cd();
      double totBck = 0;
      for(int i=1; i<nPlotCategories; i++) totBck = totBck + histoMGStudy[np][i]->GetSumOfWeights();
      printf("(%d) %f (%f+%f+%f+%f+%f+%f+%f+%f+%f+%f)=%f\n",np,histoMGStudy[np][0]->GetSumOfWeights(),
      histoMGStudy[np][1]->GetSumOfWeights(),histoMGStudy[np][2]->GetSumOfWeights(),
      histoMGStudy[np][3]->GetSumOfWeights(),histoMGStudy[np][4]->GetSumOfWeights(),
      histoMGStudy[np][5]->GetSumOfWeights(),histoMGStudy[np][6]->GetSumOfWeights(),
      histoMGStudy[np][7]->GetSumOfWeights(),histoMGStudy[np][8]->GetSumOfWeights(),
      histoMGStudy[np][9]->GetSumOfWeights(),histoMGStudy[np][10]->GetSumOfWeights(),
      totBck);
      for(int nc=0; nc<nPlotCategories; nc++) {histoMGStudy[np][nc]->SetNameTitle(Form("histo%d",nc),Form("histo%d",nc));histoMGStudy[np][nc]->Write();}
      outFilePlotsNote->Close();
    }
  }

  {
    printf("---------------MET Study---------------\n");
    sprintf(output,"histoDY%dMETStudy_%d%s.root",whichDY,year,addSuffix.Data());
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    for(int mtype=0; mtype<4; mtype++){
      for(int nh=0; nh<METBins; nh++){
        for(int nc=0; nc<2; nc++){
          histoMETStudy[mtype][nh][nc]->Write();
        }
      }
    }
    outFilePlotsNote->Close();
    for(int mtype=0; mtype<4; mtype++){
      for(int nc=0; nc<2; nc++){
        printf("(%d,%d) ",mtype,nc); for(int nh=0; nh<METBins; nh++) printf(",%9.5f",histoMETStudy[mtype][nh][nc]->GetMean()); printf("\n");
        printf("(%d,%d) ",mtype,nc); for(int nh=0; nh<METBins; nh++) printf(",%9.5f",histoMETStudy[mtype][nh][nc]->GetMeanError()); printf("\n");
      }
    }
  }
  if(year == 2018){
    printf("---------------HEM Study---------------\n");
    sprintf(output,"histoDataHEMDY%dzll_%d%s.root",whichDY,year,addSuffix.Data());	
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    for(int thePlot=0; thePlot<allDataHEMPlots; thePlot++){
      for(int i=0; i<4; i++) histoDataHEM[thePlot][i]->Write();
    }
    outFilePlotsNote->Close();
    for(int thePlot=0; thePlot<allHEMPlots; thePlot++){
      sprintf(output,"histoHEMDY%dzll_%d_%d%s.root",whichDY,year,thePlot,addSuffix.Data());	
      TFile* outFilePlotsNote = new TFile(output,"recreate");
      outFilePlotsNote->cd();
      double totBck = 0;
      for(int i=1; i<nPlotCategories; i++) totBck =totBck + histoHEM[thePlot][i]->GetSumOfWeights();
      printf("(%d) %f (%f+%f+%f+%f+%f+%f+%f+%f)=%f\n",thePlot,histoHEM[thePlot][0]->GetSumOfWeights(),
      histoHEM[thePlot][1]->GetSumOfWeights(),histoHEM[thePlot][2]->GetSumOfWeights(),
      histoHEM[thePlot][3]->GetSumOfWeights(),histoHEM[thePlot][4]->GetSumOfWeights(),
      histoHEM[thePlot][5]->GetSumOfWeights(),histoHEM[thePlot][6]->GetSumOfWeights(),
      histoHEM[thePlot][7]->GetSumOfWeights(),histoHEM[thePlot][8]->GetSumOfWeights(),
      totBck);
      for(int np=0; np<nPlotCategories; np++) {histoHEM[thePlot][np]->SetNameTitle(Form("histo%d",np),Form("histo%d",np));histoHEM[thePlot][np]->Write();}
      outFilePlotsNote->Close();
    }
  }
}
