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

#include "MitAnalysisRunII/panda/macros/9x/pandaFlat.C"
#include "MitAnalysisRunII/panda/macros/9x/common.h"
#include "MitAnalysisRunII/panda/macros/9x/applyCorrections.h"

const bool isDEBUG = false;
const bool showSyst = true;
const unsigned int period = 0;
const double mcPrescale = 1;
const bool usePureMC = true; // if true, passLooseLepId not applied
enum selType                     { ZHSEL,   ZHTIGHTSEL,   BTAGSEL,   ZLLSEL,   WWSEL,   PRESEL,   DYSEL, nSelTypes};
TString selTypeName[nSelTypes]=  {"ZHSEL", "ZHTIGHTSEL", "BTAGSEL", "ZLLSEL", "WWSEL", "PRESEL" ,"DYSEL"};
enum systType                     {JESUP=0, JESDOWN,  METUP,  METDOWN, nSystTypes};
TString systTypeName[nSystTypes]= {"JESUP","JESDOWN","METUP","METDOWN"};
bool isDesk014 = false;

void zhAnalysis(
int year, int jetValue, TString whichBSMName = "", bool isBlinded = false
){
  int whichYear = -1;
  if     (year == 2016) whichYear = Y2016;
  else if(year == 2017) whichYear = Y2017;
  else if(year == 2018) whichYear = Y2018;
  else {printf("Wrong year (%d)!\n",year); return;}

  TString inputFolder = "/data/t3home000";
  if(isDesk014 == true) inputFolder = "/local";

  //*******************************************************
  //Inputs
  //*******************************************************
  double WSSF[nBinWSEtaCorr],WSSFE[nBinWSEtaCorr];
  double muScaleCorr[nBinLepEtaCorr],elScaleCorr[nBinLepEtaCorr];
  if     (year == 2016){
    for(int i=0; i<nBinWSEtaCorr; i++) {WSSF[i] = WSSF_2016[i]; WSSFE[i] = WSSFE_2016[i];} 
    for(int i=0; i<nBinLepEtaCorr; i++) {muScaleCorr[i] = muScaleCorr_2016[i]; elScaleCorr[i] = elScaleCorr_2016[i];}
  }
  else if(year == 2017){
    for(int i=0; i<nBinWSEtaCorr; i++) {WSSF[i] = WSSF_2017[i]; WSSFE[i] = WSSFE_2017[i];}
    for(int i=0; i<nBinLepEtaCorr; i++) {muScaleCorr[i] = muScaleCorr_2017[i]; elScaleCorr[i] = elScaleCorr_2017[i];}
  }
  else if(year == 2018){
    for(int i=0; i<nBinWSEtaCorr; i++) {WSSF[i] = WSSF_2018[i]; WSSFE[i] = WSSFE_2018[i];}
    for(int i=0; i<nBinLepEtaCorr; i++) {muScaleCorr[i] = muScaleCorr_2018[i]; elScaleCorr[i] = elScaleCorr_2018[i];}
  }

  printf("muScale:\n");for(int i=0; i<nBinLepEtaCorr; i++) printf("%f,",muScaleCorr[i]); printf("\n");
  printf("elScale:\n");for(int i=0; i<nBinLepEtaCorr; i++) printf("%f,",elScaleCorr[i]); printf("\n");

  vector<TString> infileName_;
  vector<int> infileCat_;

  TString filesPath;
  TString fLepton_FakesName = Form("MitAnalysisRunII/data/90x/fakes/histoFakeEtaPt_%d.root",year);
  TString puPath;
  TString npvPath = Form("MitAnalysisRunII/data/90x/pu/npvWeights_%d.root",year);
  TString trgSFPath = Form("MitAnalysisRunII/data/90x/trigger/histo_triggerEff_sel0_%d.root",year);
  TString effSFPath = Form("MitAnalysisRunII/data/90x/eff/histoDY0EffSFStudy_%d.root",year);
  if     (year == 2018) {
    filesPath = Form("%s/ceballos/panda/v_006_1/",inputFolder.Data());
    puPath = "MitAnalysisRunII/data/90x/pu/puWeights_90x_2018.root";

    infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	         infileCat_.push_back(kPlotData);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data()));                infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data()));                infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		 infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));                  infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYNJetsToLL_NLO.root",filesPath.Data()));      infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sWZ3l_amcnlo.root" ,filesPath.Data()));         infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTVV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    if(whichBSMName == ""){
      infileName_.push_back(Form("%sqqZH125inv.root" ,filesPath.Data()));          infileCat_.push_back(kPlotBSM);
      infileName_.push_back(Form("%sggZH125inv.root" ,filesPath.Data()));          infileCat_.push_back(kPlotBSM);
    }
    else {
      infileName_.push_back(Form("%s%s.root" ,filesPath.Data(),whichBSMName.Data())); infileCat_.push_back(kPlotBSM);
    }
  }
  else if(year == 2017) {
    filesPath = Form("%s/ceballos/panda/v_004_1/",inputFolder.Data());
    puPath = "MitAnalysisRunII/data/90x/pu/puWeights_90x_2017.root";

    infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	         infileCat_.push_back(kPlotData);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		 infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		         infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data())); infileCat_.push_back(kPlotDY);
    //infileName_.push_back(Form("%sDYJetsToLL_M-50_LO.root",filesPath.Data()));   infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYNJetsToLL_NLO.root",filesPath.Data()));      infileCat_.push_back(kPlotDY);
    //infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));                  infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sWZ3l_amcnlo.root" ,filesPath.Data()));         infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTVV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    if(whichBSMName == ""){
      infileName_.push_back(Form("%sqqZH125inv.root" ,filesPath.Data()));          infileCat_.push_back(kPlotBSM);
      infileName_.push_back(Form("%sggZH125inv.root" ,filesPath.Data()));          infileCat_.push_back(kPlotBSM);
    }
    else {
      infileName_.push_back(Form("%s%s.root" ,filesPath.Data(),whichBSMName.Data())); infileCat_.push_back(kPlotBSM);
    }
  }
  else if(year == 2016) {
    filesPath = Form("%s/ceballos/panda/v_002_1/",inputFolder.Data());
    puPath = "MitAnalysisRunII/data/90x/pu/puWeights_90x_2016.root";

    infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	          infileCat_.push_back(kPlotData);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		          infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data()));  infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt0To50.root",filesPath.Data()));    infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt50To100.root",filesPath.Data()));  infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt100To250.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt250To400.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt400To650.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt650ToInf.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
    //infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));                   infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sWZ.root" ,filesPath.Data()));	                  infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sWGstar.root" ,filesPath.Data()));               infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotVVV);
    if(whichBSMName == ""){
      infileName_.push_back(Form("%sqqZH125inv.root" ,filesPath.Data()));          infileCat_.push_back(kPlotBSM);
      infileName_.push_back(Form("%sggZH125inv.root" ,filesPath.Data()));          infileCat_.push_back(kPlotBSM);
    }
    else {
      infileName_.push_back(Form("%s%s.root" ,filesPath.Data(),whichBSMName.Data())); infileCat_.push_back(kPlotBSM);
    }
  }
  else {
    return;
  }

  //infileName_.clear();infileCat_.clear();
  //infileName_.push_back(Form("%sqqZH125inv.root" ,filesPath.Data()));	       infileCat_.push_back(kPlotBSM);
  //infileName_.push_back(Form("%sggZH125inv.root" ,filesPath.Data()));	       infileCat_.push_back(kPlotBSM);

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

  TFile *fNPVFile = TFile::Open(Form("%s",npvPath.Data()));
  TH1D *fhDNPV    = (TH1D*)(fNPVFile->Get("npvWeights"));   assert(fhDNPV);    fhDNPV	->SetDirectory(0);
  delete fNPVFile;

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

  TString fileADDName = "ADDMonoZ_MD_2_d_2"; // dummy for practical purposes!
  if(whichBSMName.Contains("ADD") == true) fileADDName = whichBSMName;
  TFile *fADDRatios = TFile::Open(Form("MitAnalysisRunII/data/90x/add/%s_%d.root",fileADDName.Data(),year));
  TH1D* histoADDRatio = (TH1D*)fADDRatios->Get("ratio;1"); histoADDRatio->SetDirectory(0);
  fADDRatios->Close();

  //const int nBinMVA = 36; Float_t xbins[nBinMVA+1] = {0,  80, 100, 125, 150, 175, 200, 250, 300, 350, 400, 500, 600,1000,
  //						        1080,1100,1125,1150,1175,1200,1250,1300,1350,1400,1500,1600,2000,
  //						        2100,2125,2150,2200,3000,
  //						        3100,3125,3150,3200,4000};
  //const int nBinMVA = 26; Float_t xbins[nBinMVA+1] = {0,  80, 100, 125, 150, 175, 200, 250, 300, 350, 400, 500, 600,1000,
  //						        1080,1100,1125,1150,1175,1200,1250,1300,1350,1400,1500,1600,2000};
  const int nBinMVA = 13; Float_t xbins[nBinMVA+1] = {0,  80, 100, 125, 150, 175, 200, 250, 300, 350, 400, 500, 600,1000};
  const int nBin1DMET = 12; Float_t xbins1DMET[nBin1DMET+1] = {80, 100, 125, 150, 175, 200, 250, 300, 350, 400, 500, 600, 1000};

  const double metMax = 999.999;

  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 82;
  TH1D* histo[allPlots][nPlotCategories];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    bool is1DPlot = false;
    if     (thePlot >=   0 && thePlot <=   2) {nBinPlot = 100; xminPlot =100.0; xmaxPlot = 500;}
    else if(thePlot >=   3 && thePlot <=  14) {nBinPlot = 160; xminPlot = 80.0; xmaxPlot = 240;}
    else if(thePlot >=  15 && thePlot <=  17) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 100;}
    else if(thePlot >=  18 && thePlot <=  20) {nBinPlot = 5;   xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >=  21 && thePlot <=  23) {nBinPlot = 160; xminPlot = 80.0; xmaxPlot = 240;}
    else if(thePlot >=  24 && thePlot <=  26) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 1;}
    else if(thePlot >=  27 && thePlot <=  29) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = TMath::Pi();}
    else if(thePlot >=  30 && thePlot <=  32) {nBinPlot = 4;   xminPlot = -0.5; xmaxPlot = 3.5;}
    else if(thePlot >=  33 && thePlot <=  35) {nBinPlot = 200; xminPlot = 50.0; xmaxPlot = 250;}
    else if(thePlot >=  36 && thePlot <=  38) {nBinPlot = nBinPlot = 24;  xminPlot =  0.0; xmaxPlot = 3.0;}
    else if(thePlot >=  39 && thePlot <=  41) {nBinPlot = 4;   xminPlot = -0.5; xmaxPlot = 3.5;}
    else if(thePlot >=  42 && thePlot <=  44) {nBinPlot = 40;  xminPlot =  0.0; xmaxPlot = 4.0;}
    else if(thePlot >=  45 && thePlot <=  47) {nBinPlot = 10;  xminPlot = -0.5; xmaxPlot = 9.5;}
    else if(thePlot >=  48 && thePlot <=  53) {is1DPlot = true;}
    else if(thePlot >=  54 && thePlot <=  56) {nBinPlot = 24;  xminPlot =  0.0; xmaxPlot = 3.0;}
    else if(thePlot >=  57 && thePlot <=  59) {nBinPlot = 160; xminPlot = 80.0; xmaxPlot = 240;}
    else if(thePlot >=  60 && thePlot <=  62) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 1;}
    else if(thePlot >=  63 && thePlot <=  65) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = TMath::Pi();}
    else if(thePlot >=  66 && thePlot <=  68) {nBinPlot = 4;   xminPlot = -0.5; xmaxPlot = 3.5;}
    else if(thePlot >=  69 && thePlot <=  69) {nBinPlot =100;  xminPlot = -5.0; xmaxPlot = 5.0;}
    else if(thePlot >=  70 && thePlot <=  70) {nBinPlot = 5;   xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >=  71 && thePlot <=  71) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = TMath::Pi();}
    else if(thePlot >=  72 && thePlot <=  72) {nBinPlot = 24;  xminPlot =  0.0; xmaxPlot = 3.0;}
    else if(thePlot >=  73 && thePlot <=  73) {nBinPlot = 100; xminPlot = -TMath::Pi(); xmaxPlot = TMath::Pi();}
    else if(thePlot >=  74 && thePlot <=  74) {nBinPlot = 40;  xminPlot =  0.0; xmaxPlot = 1.0;}
    else if(thePlot >=  75 && thePlot <=  78) {is1DPlot = true;}
    else if(thePlot >=  79 && thePlot <=  79) {nBinPlot = 100; xminPlot = 25.0; xmaxPlot = 425.0;}
    else if(thePlot >=  80 && thePlot <=  80) {nBinPlot = 100; xminPlot = 20.0; xmaxPlot = 220.0;}
    if(thePlot == allPlots-1) for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinMVA, xbins);
    else if(is1DPlot == true) for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBin1DMET, xbins1DMET);
    else                      for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinPlot, xminPlot, xmaxPlot);
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
  TH1D *histo_EWKCorrWZUp[nPlotCategories];
  TH1D *histo_EWKCorrWZDown[nPlotCategories];
  TH1D *histo_EWKqqZZCorrUp[nPlotCategories];
  TH1D *histo_EWKqqZZCorrDown[nPlotCategories];
  TH1D *histo_ggZZCorrUp[nPlotCategories];
  TH1D *histo_ggZZCorrDown[nPlotCategories];
  TH1D *histo_CorrWZZZUp[nPlotCategories];
  TH1D *histo_CorrWZZZDown[nPlotCategories];
  TH1D *histo_EWKCorrZHUp[nPlotCategories];
  TH1D *histo_EWKCorrZHDown[nPlotCategories];
  
  for(unsigned ic=kPlotData; ic!=nPlotCategories; ic++) {
    for(int i=0; i<6; i++)  histo_QCDScaleBounding[ic][i] = (TH1D*)histo_MVA->Clone(Form("histo_%s_%d_QCDScaleBounding",plotBaseNames[ic].Data(),i));
    histo_Baseline              [ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s"                    , plotBaseNames[ic].Data()));
    histo_QCDScaleUp            [ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_QCDScale_%s_ACCEPTUp"   , plotBaseNames[ic].Data(), plotBaseNames[ic].Data()));
    histo_QCDScaleDown          [ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_QCDScale_%s_ACCEPTDown" , plotBaseNames[ic].Data(), plotBaseNames[ic].Data()));
    histo_PDFBoundingUp 	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_PDFUp"              , plotBaseNames[ic].Data()));
    histo_PDFBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_PDFDown"            , plotBaseNames[ic].Data()));
    histo_LepEffMBoundingUp	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_eff_mUp"        , plotBaseNames[ic].Data()));
    histo_LepEffMBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_eff_mDown"      , plotBaseNames[ic].Data()));
    histo_LepEffEBoundingUp	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_eff_eUp"        , plotBaseNames[ic].Data()));
    histo_LepEffEBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_eff_eDown"      , plotBaseNames[ic].Data()));
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
    histo_EWKCorrWZUp		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKWZCorrUp"        , plotBaseNames[ic].Data()));
    histo_EWKCorrWZDown 	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKWZCorrDown"      , plotBaseNames[ic].Data()));
    histo_EWKqqZZCorrUp 	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKqqZZCorrUp"      , plotBaseNames[ic].Data()));
    histo_EWKqqZZCorrDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKqqZZCorrDown"    , plotBaseNames[ic].Data()));
    histo_ggZZCorrUp		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_ggZZCorrUp"         , plotBaseNames[ic].Data()));
    histo_ggZZCorrDown		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_ggZZCorrDown"       , plotBaseNames[ic].Data()));
    histo_CorrWZZZUp		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CorrWZZZUp"         , plotBaseNames[ic].Data()));
    histo_CorrWZZZDown		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CorrWZZZDown"       , plotBaseNames[ic].Data()));
    histo_EWKCorrZHUp		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKZHCorrUp"        , plotBaseNames[ic].Data()));
    histo_EWKCorrZHDown 	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKZHCorrDown"      , plotBaseNames[ic].Data()));
  }

  //*******************************************************
  // Chain Loop
  //*******************************************************
  for(UInt_t ifile=0; ifile<infileName_.size(); ifile++) {
    printf("sampleNames(%d): %s\n",ifile,infileName_[ifile].Data());
    TFile *the_input_file = TFile::Open(infileName_[ifile].Data());
    TTree *the_input_tree = (TTree*)the_input_file->FindObjectAny("events");
    
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

      bool passTrigger = (thePandaFlat.trigger & (1<<kEMuTrig)) != 0       || (thePandaFlat.trigger & (1<<kDoubleMuTrig)) != 0  ||
                         (thePandaFlat.trigger & (1<<kSingleMuTrig)) != 0  || (thePandaFlat.trigger & (1<<kDoubleEleTrig)) != 0 ||
                         (thePandaFlat.trigger & (1<<kSingleEleTrig)) != 0;
      if(passTrigger == false) continue;
      if(thePandaFlat.metFilter == 0) continue;

      if(thePandaFlat.nLooseLep != 2) continue;

      vector<float>  looseLepPt,looseLepEta,looseLepPhi,looseLepSF,looseLepIso;
      vector<int> looseLepSelBit,looseLepPdgId,looseLepTripleCharge,looseLepMissingHits;
      int ptSelCuts[3] = {0,0,0};
      for(int i=0; i<thePandaFlat.nLooseMuon; i++){
        int nBinLepEtaCorr = histoLepEtaCorr->GetXaxis()->FindBin(TMath::Min((double)TMath::Abs(thePandaFlat.muonEta[i]),2.4999))-1;
        if(infileCat_[ifile]==kPlotData)
        looseLepPt.push_back(thePandaFlat.muonPt[i]);
        else
        looseLepPt.push_back(thePandaFlat.muonPt[i] * muScaleCorr[nBinLepEtaCorr]);
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
        int nBinLepEtaCorr = histoLepEtaCorr->GetXaxis()->FindBin(TMath::Min((double)TMath::Abs(thePandaFlat.electronEta[i]),2.4999))-1;
        if(infileCat_[ifile]==kPlotData)
        looseLepPt.push_back(thePandaFlat.electronPt[i]);
        else
        looseLepPt.push_back(thePandaFlat.electronPt[i] * elScaleCorr[nBinLepEtaCorr]);
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

      if(!(ptSelCuts[0] >= 1 && ptSelCuts[1] >= 2 && ptSelCuts[2] >= thePandaFlat.nLooseLep)) continue;

      int theCategory = infileCat_[ifile];
      bool isNotMCFake = thePandaFlat.looseGenLep1PdgId != 0 && thePandaFlat.looseGenLep2PdgId != 0;
      if(theCategory != kPlotData && theCategory != kPlotVG && isNotMCFake == false && usePureMC == false) continue;

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
      if(passLooseLepId == false && usePureMC == false) continue;
      if(usePureMC == true && countLeptonTight != idLep.size()) continue;

      int lepType = -1; double muSFUnc = 1.0; double elSFUnc = 1.0; 
      if     (thePandaFlat.nLooseLep == 2){
        if     (abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13) {lepType = 0; muSFUnc = 1.015*1.015;}
        else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11) {lepType = 1; elSFUnc = 1.015*1.015;}
        else  {lepType = 2; muSFUnc = 1.015; elSFUnc = 1.015;}
      }

      TLorentzVector vMet,vTrkMet,vMetUp,vMetDown;
      vTrkMet.SetPtEtaPhiM(thePandaFlat.trkmet,0.0,thePandaFlat.trkmetphi,0.0);
      vMet    .SetPtEtaPhiM(thePandaFlat.pfmet,0.0,thePandaFlat.pfmetphi,0.0);
      vMetUp  .SetPtEtaPhiM(thePandaFlat.pfmet_JESTotalUp  ,0.0,thePandaFlat.pfmetphi_JESTotalUp  ,0.0);
      vMetDown.SetPtEtaPhiM(thePandaFlat.pfmet_JESTotalDown,0.0,thePandaFlat.pfmetphi_JESTotalDown,0.0);
      vMet    .SetPx(vMet    .Px()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 0));
      vMet    .SetPy(vMet    .Py()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 1));
      vMetUp  .SetPx(vMetUp  .Px()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 0));
      vMetUp  .SetPy(vMetUp  .Py()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 1));
      vMetDown.SetPx(vMetDown.Px()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 0));
      vMetDown.SetPy(vMetDown.Py()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 1));

      double dPhiLepMETMin = 999; double dPhiLepTrackMETMin = 999;
      for(unsigned int i=0; i<vLoose.size(); i++){
        if(dPhiLepMETMin      > TMath::Abs(vLoose[i].DeltaPhi(vMet))   ) dPhiLepMETMin      = TMath::Abs(vLoose[i].DeltaPhi(vMet));
	if(dPhiLepTrackMETMin > TMath::Abs(vLoose[i].DeltaPhi(vTrkMet))) dPhiLepTrackMETMin = TMath::Abs(vLoose[i].DeltaPhi(vTrkMet));
      }
      double dPhiMETTrackMETMin = TMath::Abs(vMet.DeltaPhi(vTrkMet));

      double PMET[1] = {vMet.Pt()};
      double PTrackMET[1] = {vTrkMet.Pt()};
      if(dPhiLepMETMin < TMath::Pi()/2) {PMET[0] = PMET[0] * sin(dPhiLepMETMin);}
      if(dPhiLepTrackMETMin < TMath::Pi()/2) {PTrackMET[0] = PTrackMET[0] * sin(dPhiLepTrackMETMin);}
      double minPMET[1] = {TMath::Min(PMET[0],PTrackMET[0])};

      double mllZ = 10000;
      TLorentzVector vZ1l1,vZ1l2;
      if     (vLoose.size() == 2){
        vZ1l1  = vLoose[0];
        vZ1l2  = vLoose[1];
	mllZ   = (vLoose[0]+vLoose[1]).M();
      }

      TLorentzVector dilep = vZ1l1+vZ1l2; TLorentzVector dilepJet = dilep;
      double sumHT = vZ1l1.Pt() + vZ1l2.Pt();
      double dPhiJetMET = -1.0; double dPhiJetMETUp = -1.0; double dPhiJetMETDown = -1.0;
      if(thePandaFlat.nJot > 0 && thePandaFlat.jotPt[0] > 30) {
        TLorentzVector vJetTemp;
        vJetTemp.SetPtEtaPhiM(thePandaFlat.jotPt[0],thePandaFlat.jotEta[0],thePandaFlat.jotPhi[0],0.0);
        dPhiJetMET = TMath::Abs(vJetTemp.DeltaPhi(vMet));
	sumHT = sumHT + thePandaFlat.jotPt[0];
	dilepJet = dilepJet + vJetTemp;
      }
      if(thePandaFlat.nJot_JESTotalUp > 0 && thePandaFlat.jotPt_JESTotalUp[0] > 30) {
        TLorentzVector vJetTemp;
        vJetTemp.SetPtEtaPhiM(thePandaFlat.jotPt_JESTotalUp[0],thePandaFlat.jotEta[0],thePandaFlat.jotPhi[0],0.0);
        dPhiJetMETUp = TMath::Abs(vJetTemp.DeltaPhi(vMetUp));
      }
      if(thePandaFlat.nJot_JESTotalDown > 0 && thePandaFlat.jotPt_JESTotalDown[0] > 30) {
        TLorentzVector vJetTemp;
        vJetTemp.SetPtEtaPhiM(thePandaFlat.jotPt_JESTotalDown[0],thePandaFlat.jotEta[0],thePandaFlat.jotPhi[0],0.0);
        dPhiJetMETDown = TMath::Abs(vJetTemp.DeltaPhi(vMetDown));
      }

      if(!(dilep.Pt() > 60 && (vMet.Pt() > 70 || vMetUp.Pt() > 70 ||vMetDown.Pt() > 70) && (thePandaFlat.nLooseLep != 2 || TMath::Abs(dilep.M()-125) < 75))) continue;

      double dPhiDiLepMET = TMath::Abs(dilep.DeltaPhi(vMet)); double dPhiDiLepMETUp = TMath::Abs(dilep.DeltaPhi(vMetUp)); double dPhiDiLepMETDown = TMath::Abs(dilep.DeltaPhi(vMetDown));
      double mT = TMath::Sqrt(2.0*dilep.Pt()*vMet.Pt()*(1.0 - cos(dPhiDiLepMET)));

      bool passZMass = TMath::Abs(mllZ-91.1876) < 15.0;
      bool passZMassSB = mllZ > 110 && mllZ < 200;
      bool passMETTight = vMet.Pt()     > 100;
      bool passMET      = vMet.Pt()     >  80 && (lepType != 2 || vMet.Pt()     > 100);
      bool passMETUp    = vMetUp.Pt()   >  80 && (lepType != 2 || vMetUp.Pt()   > 100);
      bool passMETDown  = vMetDown.Pt() >  80 && (lepType != 2 || vMetDown.Pt() > 100);
      bool passPTLL   = dilep.Pt() > 60;

      double ptFrac     = TMath::Abs(dilep.Pt()-vMet.Pt()    )/dilep.Pt();
      double ptFracUp   = TMath::Abs(dilep.Pt()-vMetUp.Pt()  )/dilep.Pt();
      double ptFracDown = TMath::Abs(dilep.Pt()-vMetDown.Pt())/dilep.Pt();
      bool passPTFrac     = ptFrac     < 0.4;
      bool passPTFracUp   = ptFracUp   < 0.4;
      bool passPTFracDown = ptFracDown < 0.4;
      bool passDPhiZMET     = dPhiDiLepMET     > 2.6;
      bool passDPhiZMETUp   = dPhiDiLepMETUp   > 2.6;
      bool passDPhiZMETDown = dPhiDiLepMETDown > 2.6;
      bool passDPhiZMETTight = dPhiDiLepMET > 2.6;
      bool passJetEtaCut[3] = {true, true, true};
      if(thePandaFlat.nJot              >= 1 && year == 2017) passJetEtaCut[0] = TMath::Abs(thePandaFlat.jotEta[0]) < 2.5;
      if(thePandaFlat.nJot_JESTotalUp   >= 1 && year == 2017) passJetEtaCut[1] = TMath::Abs(thePandaFlat.jotEta[0]) < 2.5;
      if(thePandaFlat.nJot_JESTotalDown >= 1 && year == 2017) passJetEtaCut[2] = TMath::Abs(thePandaFlat.jotEta[0]) < 2.5;
      bool passNjets     = thePandaFlat.nJot              == jetValue && passJetEtaCut[0];
      bool passNjetsUp   = thePandaFlat.nJot_JESTotalUp   == jetValue && passJetEtaCut[1];
      bool passNjetsDown = thePandaFlat.nJot_JESTotalDown == jetValue && passJetEtaCut[2];

      bool passBtagVeto = thePandaFlat.jetNMBtags == 0; bool passBtagVetoUp = thePandaFlat.jetNMBtags_JESTotalUp == 0; bool passBtagVetoDown = thePandaFlat.jetNMBtags_JESTotalDown == 0;
      double dphill = TMath::Abs(vZ1l1.DeltaPhi(vZ1l2));
      double detall = TMath::Abs(vZ1l1.Eta()-vZ1l2.Eta());
      double drll = sqrt(dphill*dphill+detall*detall);
      bool passDRLL = drll < 1.8;

      bool passDPhiJetMET     = dPhiJetMET     == -1 || dPhiJetMET     >= 0.5;
      bool passDPhiJetMETUp   = dPhiJetMETUp   == -1 || dPhiJetMETUp   >= 0.5;
      bool passDPhiJetMETDown = dPhiJetMETDown == -1 || dPhiJetMETDown >= 0.5;
      bool passTauVeto = thePandaFlat.nTau == 0;

      //                               0       1         2            3                 4            5        6              7          8           9
      bool passCutEvol[10] = {passZMass,passPTLL,passNjets,passBtagVeto,passDPhiZMETTight,passMETTight,passDRLL,passDPhiJetMET,passPTFrac,passTauVeto};
      bool passCutEvolAll = true;

      bool passAllCuts[nSelTypes] = {                   
      passZMass   && passNjets && passMET      && passPTFrac && passDPhiZMET      &&  passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passDRLL,   // ZHSEL
      passZMass   && passNjets && passMETTight && passPTFrac && passDPhiZMETTight &&  passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passDRLL,   // ZHTIGHTSEL
      passZMass   && passNjets && passMETTight && passPTFrac && passDPhiZMETTight && !passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passDRLL,   // BTAGSEL
      passZMass   &&              passMETTight &&                                                     passPTLL &&                   passTauVeto,               // ZLLSEL
      passZMassSB && passNjets && passMETTight && passPTFrac && passDPhiZMETTight &&  passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passDRLL,   // WWSEL
      passZMass   && passNjets && passMET      &&                                                     passPTLL &&                   passTauVeto,               // PRESEL
      passZMass   && passNjets && passMET      && passPTFrac &&                       passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto                // DYSEL
                                    };

      bool passNMinusOne[10] = {
     		  passNjets && passMETTight && passPTFrac && passDPhiZMETTight && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passDRLL,
     passZMass &&	       passMETTight && passPTFrac && passDPhiZMETTight && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passDRLL,
     passZMass && passNjets &&  	       passPTFrac && passDPhiZMETTight && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passDRLL,
     passZMass && passNjets && passMETTight &&	             passDPhiZMETTight && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passDRLL,
     passZMass && passNjets && passMETTight && passPTFrac &&                      passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passDRLL,
     passZMass && passNjets && passMETTight && passPTFrac && passDPhiZMETTight &&                 passPTLL && passDPhiJetMET && passTauVeto && passDRLL,
     passZMass && passNjets && passMETTight && passPTFrac && passDPhiZMETTight && passBtagVeto &&             passDPhiJetMET && passTauVeto && passDRLL,
     passZMass && passNjets && passMETTight && passPTFrac && passDPhiZMETTight && passBtagVeto && passPTLL &&                   passTauVeto && passDRLL,
     passZMass && passNjets && passMETTight && passPTFrac && passDPhiZMETTight && passBtagVeto && passPTLL && passDPhiJetMET                && passDRLL,
     passZMass && passNjets && passMETTight && passPTFrac && passDPhiZMETTight && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto
                                    };

      bool passSystCuts[nSystTypes] = {                   
      passZMass   && passNjetsUp   && passMETUp   && passPTFracUp   && passDPhiZMETUp   &&  passBtagVetoUp   && passPTLL && passDPhiJetMETUp   && passTauVeto && passDRLL,
      passZMass   && passNjetsDown && passMETDown && passPTFracDown && passDPhiZMETDown &&  passBtagVetoDown && passPTLL && passDPhiJetMETDown && passTauVeto && passDRLL,
      passZMass   && passNjets     && passMET     && passPTFrac     && passDPhiZMET     &&  passBtagVeto     && passPTLL && passDPhiJetMET     && passTauVeto && passDRLL,
      passZMass   && passNjets     && passMET     && passPTFrac     && passDPhiZMET     &&  passBtagVeto     && passPTLL && passDPhiJetMET     && passTauVeto && passDRLL
                                    };

      double totalWeight = 1.0; double puWeight = 1.0; double puWeightUp = 1.0; double puWeightDown = 1.0; double sf_l1PrefireE = 1.0;
      double sf_EWKZH = 1.0; double sf_EWKZHUp = 1.0; double sf_EWKZHDown = 1.0;
      double triggerWeights[2] = {1.0, 0.0};
      if(theCategory != kPlotData){
	trigger_sf(triggerWeights,thePandaFlat.nLooseLep,
	trgSFMMBB,trgSFMMEB,trgSFMMBE,trgSFMMEE,trgSFEEBB,trgSFEEEB,trgSFEEBE,trgSFEEEE,
	trgSFMEBB,trgSFMEEB,trgSFMEBE,trgSFMEEE,trgSFEMBB,trgSFEMEB,trgSFEMBE,trgSFEMEE,
	vLoose[0].Pt(), TMath::Abs(vLoose[0].Eta()), abs(looseLepPdgId[0]),
	vLoose[1].Pt(), TMath::Abs(vLoose[1].Eta()), abs(looseLepPdgId[1]));
	puWeight     = nPUScaleFactor(fhDPU,    thePandaFlat.pu);
        puWeightUp   = nPUScaleFactor(fhDPUUp,  thePandaFlat.pu);
        puWeightDown = nPUScaleFactor(fhDPUDown,thePandaFlat.pu);

        sf_l1PrefireE = 1.0 + TMath::Abs(1.0 - thePandaFlat.sf_l1Prefire) * 0.2;

	double npvWeight = 1; // nPUScaleFactor(fhDNPV, thePandaFlat.npv);

        if(passBtagVeto) totalWeight = thePandaFlat.normalizedWeight * lumiV[whichYear] * npvWeight * puWeight * thePandaFlat.sf_l1Prefire * thePandaFlat.sf_btag0   * looseLepSF[0] * looseLepSF[1] * triggerWeights[0] * theMCPrescale;
        else	         totalWeight = thePandaFlat.normalizedWeight * lumiV[whichYear] * npvWeight * puWeight * thePandaFlat.sf_l1Prefire * thePandaFlat.sf_btagGT0 * looseLepSF[0] * looseLepSF[1] * triggerWeights[0] * theMCPrescale;

        if     (infileCat_[ifile] == kPlotWZ)                                                totalWeight = totalWeight * thePandaFlat.sf_wz;
	else if(infileCat_[ifile] == kPlotZZ && infileName_[ifile].Contains("qqZZ") == true) totalWeight = totalWeight * thePandaFlat.sf_zz;

        int theFileCat[2] = {infileCat_[ifile], 0};
        totalWeight = totalWeight * mcCorrection(1, year, thePandaFlat.jetNMBtags,thePandaFlat.jetNBtags, thePandaFlat.nJot, dPhiDiLepMET, theFileCat, thePandaFlat.eventNumber);

        if(infileCat_[ifile] == kPlotDY && year == 2018 && thePandaFlat.normalizedWeight < -0.05 && vMet.Pt() > 100) totalWeight = 0.0;
/*
	else if(infileCat_[ifile] == kPlotEM && passBtagVeto && year == 2016) totalWeight = totalWeight * 1.30;
	else if(infileCat_[ifile] == kPlotEM && passBtagVeto && year == 2017) totalWeight = totalWeight * 1.20;
	else if(infileCat_[ifile] == kPlotEM &&                 year == 2018) totalWeight = totalWeight * 1.55;

	else if(infileCat_[ifile] == kPlotDY && year == 2016) totalWeight = totalWeight * 0.75;
	else if(infileCat_[ifile] == kPlotDY && year == 2017) totalWeight = totalWeight * 0.90;
	else if(infileCat_[ifile] == kPlotDY && year == 2018) totalWeight = totalWeight * 1.50;

        if     (infileCat_[ifile] == kPlotDY && year == 2016 && lepType == 0) totalWeight = totalWeight * (1.09180-ptFrac*0.104392);
        else if(infileCat_[ifile] == kPlotDY && year == 2016 && lepType == 1) totalWeight = totalWeight * (1.15117-ptFrac*0.141021);

        if     (infileCat_[ifile] == kPlotDY && year == 2017 && TMath::Abs(thePandaFlat.jotEta[0]) < 10 && lepType == 0) {
	  if     (thePandaFlat.jotEta[0] >= -4.0 && thePandaFlat.jotEta[0] < -3.5) totalWeight = totalWeight * 2.35;
	  else if(thePandaFlat.jotEta[0] >= -3.5 && thePandaFlat.jotEta[0] < -3.0) totalWeight = totalWeight * 2.35;
	  else if(thePandaFlat.jotEta[0] >= -3.0 && thePandaFlat.jotEta[0] < -2.5) totalWeight = totalWeight * 3.30;
	  else if(thePandaFlat.jotEta[0] >   2.5 && thePandaFlat.jotEta[0] <  3.0) totalWeight = totalWeight * 3.20;
	  else if(thePandaFlat.jotEta[0] >   3.0 && thePandaFlat.jotEta[0] <  3.5) totalWeight = totalWeight * 3.40;
	  else if(thePandaFlat.jotEta[0] >   3.5 && thePandaFlat.jotEta[0] <  4.0) totalWeight = totalWeight * 7.00;
	}
        else if(infileCat_[ifile] == kPlotDY && year == 2017 && TMath::Abs(thePandaFlat.jotEta[0]) < 10 && lepType == 1) {
	  if     (thePandaFlat.jotEta[0] >= -4.0 && thePandaFlat.jotEta[0] < -3.5) totalWeight = totalWeight * 6.00;
	  else if(thePandaFlat.jotEta[0] >= -3.5 && thePandaFlat.jotEta[0] < -3.0) totalWeight = totalWeight * 2.95;
	  else if(thePandaFlat.jotEta[0] >= -3.0 && thePandaFlat.jotEta[0] < -2.5) totalWeight = totalWeight * 1.20;
	  else if(thePandaFlat.jotEta[0] >   2.5 && thePandaFlat.jotEta[0] <  3.0) totalWeight = totalWeight * 2.25;
	  else if(thePandaFlat.jotEta[0] >   3.0 && thePandaFlat.jotEta[0] <  3.5) totalWeight = totalWeight * 1.00;
	  else if(thePandaFlat.jotEta[0] >   3.5 && thePandaFlat.jotEta[0] <  4.0) totalWeight = totalWeight * 2.00;
	}

	if     (infileCat_[ifile] == kPlotDY && year == 2016 && thePandaFlat.nJot == 0) totalWeight = totalWeight * 1.5;
	else if(infileCat_[ifile] == kPlotDY && year == 2016 && thePandaFlat.nJot == 1) totalWeight = totalWeight * 1.0;
	else if(infileCat_[ifile] == kPlotDY && year == 2017 && thePandaFlat.nJot == 0) totalWeight = totalWeight * 2.5;
	else if(infileCat_[ifile] == kPlotDY && year == 2017 && thePandaFlat.nJot == 1) totalWeight = totalWeight * 0.8;
	else if(infileCat_[ifile] == kPlotDY && year == 2018 && thePandaFlat.nJot == 0) totalWeight = totalWeight * 5.0;
	else if(infileCat_[ifile] == kPlotDY && year == 2018 && thePandaFlat.nJot == 1) totalWeight = totalWeight * 1.0;
*/
	
	if(infileCat_[ifile] == kPlotBSM && infileName_[ifile].Contains("qqZH") == true){
	  sf_EWKZH     = thePandaFlat.sf_vh;
	  sf_EWKZHUp   = thePandaFlat.sf_vhUp;
	  sf_EWKZHDown = thePandaFlat.sf_vhDown;
	}
	totalWeight = totalWeight * sf_EWKZH;

        if(infileCat_[ifile] == kPlotBSM && whichBSMName.Contains("ADD") == true){
          double genDilPt = dilep.Pt();
          if(thePandaFlat.genLep1Pt > 0 && TMath::Abs(thePandaFlat.genLep1Eta) < 5 &&
	     thePandaFlat.genLep2Pt > 0 && TMath::Abs(thePandaFlat.genLep2Eta) < 5){
            TLorentzVector vGen1,vGen2;
            double thePDGMass = mass_mu;
            if(abs(thePandaFlat.genLep1PdgId)==11) thePDGMass = mass_el;
            vGen1.SetPtEtaPhiM(thePandaFlat.genLep1Pt,thePandaFlat.genLep1Eta,thePandaFlat.genLep1Phi,thePDGMass);
            thePDGMass = mass_mu;
            if(abs(thePandaFlat.genLep2PdgId)==11) thePDGMass = mass_el;
            vGen2.SetPtEtaPhiM(thePandaFlat.genLep2Pt,thePandaFlat.genLep2Eta,thePandaFlat.genLep2Phi,thePDGMass);
            genDilPt = (vGen1+vGen2).Pt();
	  }
	  int genBinDilPt = histoADDRatio->GetXaxis()->FindFixBin(TMath::Max(TMath::Min(genDilPt,3999.999),50.001));
	  totalWeight = totalWeight * histoADDRatio->GetBinContent(genBinDilPt);
	  if     (year == 2016 && whichBSMName == "ADDMonoZ_MD_1_d_2") totalWeight = totalWeight * 27.0;
	  else if(year == 2016 && whichBSMName == "ADDMonoZ_MD_2_d_2") totalWeight = totalWeight * 1.20;
	  else if(year == 2016 && whichBSMName == "ADDMonoZ_MD_3_d_2") totalWeight = totalWeight * 1.50;
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

      if(isBlinded && lepType != 2 && passAllCuts[ZHTIGHTSEL] && theCategory == kPlotData) continue; // remove ee/mm data events that pass the full tight ZH selection

      if(passAllCuts[ZHTIGHTSEL]) histo[lepType+  0][theCategory]->Fill(TMath::Min(mT,499.999),totalWeight);
      if(passAllCuts[ZHSEL])      histo[lepType+  3][theCategory]->Fill(TMath::Min(vMet.Pt(),239.999),totalWeight);
      if(passAllCuts[BTAGSEL])    histo[lepType+  6][theCategory]->Fill(TMath::Min(vMet.Pt(),239.999),totalWeight);
      if(passAllCuts[ZLLSEL])     histo[lepType+  9][theCategory]->Fill(TMath::Min(vMet.Pt(),239.999),totalWeight);
      if(passAllCuts[WWSEL])      histo[lepType+ 12][theCategory]->Fill(TMath::Min(vMet.Pt(),239.999),totalWeight);
      if(passNMinusOne[ 0])       histo[lepType+ 15][theCategory]->Fill(TMath::Min(TMath::Abs(mllZ-91.1876),99.999),totalWeight);
      if(passNMinusOne[ 1])       histo[lepType+ 18][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJot,4.4999),totalWeight);
      if(passNMinusOne[ 2] &&
         vMet.Pt() > 80)          histo[lepType+ 21][theCategory]->Fill(TMath::Min(vMet.Pt(),239.999),totalWeight);
      if(passNMinusOne[ 3])       histo[lepType+ 24][theCategory]->Fill(TMath::Min(ptFrac,0.999),totalWeight);
      if(passNMinusOne[ 4])       histo[lepType+ 27][theCategory]->Fill(dPhiDiLepMET,totalWeight);
      if(passNMinusOne[ 5])       histo[lepType+ 30][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNBtags,3.499),totalWeight);
      if(passNMinusOne[ 6])       histo[lepType+ 33][theCategory]->Fill(TMath::Min(dilep.Pt(),249.999),totalWeight);
      if(passNMinusOne[ 7] && TMath::Abs(thePandaFlat.jotEta[0]) < 2.5)
                                  histo[lepType+ 36][theCategory]->Fill(TMath::Min(dPhiJetMET,2.999),totalWeight);
      if(passNMinusOne[ 8])       histo[lepType+ 39][theCategory]->Fill(TMath::Min((double)thePandaFlat.nTau,3.499),totalWeight);
      if(passNMinusOne[ 9])       histo[lepType+ 42][theCategory]->Fill(TMath::Min((double)drll,3.999),totalWeight);
      for(int i=0; i<10; i++) {passCutEvolAll = passCutEvolAll && passCutEvol[i]; if(passCutEvolAll) histo[lepType+45][theCategory]->Fill((double)i,totalWeight);}
      if(passAllCuts[ZHSEL] && lepType != 2 && thePandaFlat.nJot == 0 && passMET &&  passDPhiZMETTight) histo[48][theCategory]->Fill(TMath::Min(vMet.Pt(),metMax),totalWeight);
      if(passAllCuts[ZHSEL] && lepType != 2 && thePandaFlat.nJot == 0 && passMET && !passDPhiZMETTight) histo[49][theCategory]->Fill(TMath::Min(vMet.Pt(),metMax),totalWeight);
      if(passAllCuts[ZHSEL] && lepType != 2 && thePandaFlat.nJot == 1 && passMET &&  passDPhiZMETTight) histo[50][theCategory]->Fill(TMath::Min(vMet.Pt(),metMax),totalWeight);
      if(passAllCuts[ZHSEL] && lepType != 2 && thePandaFlat.nJot == 1 && passMET && !passDPhiZMETTight) histo[51][theCategory]->Fill(TMath::Min(vMet.Pt(),metMax),totalWeight);
      if(passAllCuts[ZHSEL] && lepType == 2 && thePandaFlat.nJot <= 1 && passMET &&  passDPhiZMETTight) histo[52][theCategory]->Fill(TMath::Min(vMet.Pt(),metMax),totalWeight);
      if(passAllCuts[ZHSEL] && lepType == 2 && thePandaFlat.nJot <= 1 && passMET && !passDPhiZMETTight) histo[53][theCategory]->Fill(TMath::Min(vMet.Pt(),metMax),totalWeight);
      if(passAllCuts[PRESEL] && !passAllCuts[ZHTIGHTSEL]) histo[lepType+ 54][theCategory]->Fill(TMath::Min(dPhiJetMET,2.999),totalWeight);
      if(passAllCuts[PRESEL] && !passAllCuts[ZHTIGHTSEL]) histo[lepType+ 57][theCategory]->Fill(TMath::Min(vMet.Pt(),239.999),totalWeight);
      if(passAllCuts[PRESEL] && !passAllCuts[ZHTIGHTSEL]) histo[lepType+ 60][theCategory]->Fill(TMath::Min(ptFrac,0.999),totalWeight);
      if(passAllCuts[PRESEL] && !passAllCuts[ZHTIGHTSEL]) histo[lepType+ 63][theCategory]->Fill(dPhiDiLepMET,totalWeight);
      if(passAllCuts[PRESEL] && !passAllCuts[ZHTIGHTSEL]) histo[lepType+ 66][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNBtags,3.499),totalWeight);
      if((passNMinusOne[ 1] ||
          passNMinusOne[ 4] ||
          passNMinusOne[ 7]) && lepType != 2) {
	    histo[69][theCategory]->Fill(thePandaFlat.jotEta[0],totalWeight);
	    histo[70][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJot,4.4999),totalWeight);
	    histo[71][theCategory]->Fill(dPhiDiLepMET,totalWeight);
	    histo[72][theCategory]->Fill(TMath::Min(dPhiJetMET,2.999),totalWeight);
      }
      if(passAllCuts[ZHTIGHTSEL] && thePandaFlat.nJot >= 1 && lepType != 2) histo[73][theCategory]->Fill(thePandaFlat.jotPhi[0],totalWeight);
      if(passAllCuts[ZHTIGHTSEL] && lepType != 2) histo[74][theCategory]->Fill(dilepJet.Pt()/sumHT,totalWeight);
      if(passAllCuts[DYSEL] && lepType != 2){
	  bool passA = dilepJet.Pt()/sumHT > 0.60 && passMETTight;
	  bool passB = passDPhiZMETTight && passDRLL;
	  if     ( passA &&  passB)  histo[75][theCategory]->Fill(TMath::Min(vMet.Pt(),metMax),totalWeight);
	  else if( passA && !passB)  histo[76][theCategory]->Fill(TMath::Min(vMet.Pt(),metMax),totalWeight);
	  else if(!passA &&  passB)  histo[77][theCategory]->Fill(TMath::Min(vMet.Pt(),metMax),totalWeight);
	  else if(!passA && !passB)  histo[78][theCategory]->Fill(TMath::Min(vMet.Pt(),metMax),totalWeight);
      }
      if(passAllCuts[ZHTIGHTSEL] && lepType != 2) histo[79][theCategory]->Fill(TMath::Min(TMath::Max(vLoose[0].Pt(),vLoose[1].Pt()),424.999),totalWeight);
      if(passAllCuts[ZHTIGHTSEL] && lepType != 2) histo[80][theCategory]->Fill(TMath::Min(TMath::Min(vLoose[0].Pt(),vLoose[1].Pt()),219.999),totalWeight);

      //double MVAVar = TMath::Min(vMet.Pt(),xbins[nBinMVA]-0.0001); double MVAVarUp = TMath::Min(vMetUp.Pt(),xbins[nBinMVA]-0.0001); double MVAVarDown = TMath::Min(vMetDown.Pt(),xbins[nBinMVA]-0.0001);
      double MVAVar = TMath::Min(vMet.Pt(),metMax); double MVAVarUp = TMath::Min(vMetUp.Pt(),metMax); double MVAVarDown = TMath::Min(vMetDown.Pt(),metMax);
      if     (lepType == 2) {MVAVar = 0.5; MVAVarUp = 0.5; MVAVarDown = 0.5; }
      //if(thePandaFlat.nJot              == 1) MVAVar     = MVAVar     + 1000;
      //if(thePandaFlat.nJot_JESTotalUp   == 1) MVAVarUp   = MVAVarUp   + 1000;
      //if(thePandaFlat.nJot_JESTotalDown == 1) MVAVarDown = MVAVarDown + 1000;
      //if(dPhiDiLepMET     <= 2.6) MVAVar     = MVAVar     + 2000;
      //if(dPhiDiLepMETUp   <= 2.6) MVAVarUp   = MVAVarUp   + 2000;
      //if(dPhiDiLepMETDown <= 2.6) MVAVarDown = MVAVarDown + 2000;
      //else if(lepType == 1) {
      //  if(MVAVar     >= 100) MVAVar	 = MVAVar     + 1000;
      //  if(MVAVarUp   >= 100) MVAVarUp   = MVAVarUp   + 1000;
      //  if(MVAVarDown >= 100) MVAVarDown = MVAVarDown + 1000;
      //}
      if(1){

        // Avoid QCD scale weights that are anomalous high
        double maxQCDscale = (TMath::Abs(thePandaFlat.scale[0])+TMath::Abs(thePandaFlat.scale[1])+TMath::Abs(thePandaFlat.scale[2])+
	                      TMath::Abs(thePandaFlat.scale[3])+TMath::Abs(thePandaFlat.scale[4])+TMath::Abs(thePandaFlat.scale[5]))/6.0;
        if(maxQCDscale == 0) maxQCDscale = 1;

        double sf_ewkcorrwz_unc = 1.0; double sf_ewkcorrzz_unc = 1.0; double sf_ggcorrzz_unc = 1.0; double sf_corrwzzz_unc = 1.0;
	if(theCategory == kPlotWZ) sf_ewkcorrwz_unc = 1.02;
	if     (theCategory == kPlotZZ && infileName_[ifile].Contains("qqZZ") == true) sf_ewkcorrzz_unc = thePandaFlat.sf_zzUnc;
	else if(theCategory == kPlotZZ) sf_ggcorrzz_unc = 1.10;

	if(theCategory == kPlotZZ) sf_corrwzzz_unc = 1.02 * sf_ewkcorrzz_unc * sf_ggcorrzz_unc;

        if     (theCategory == kPlotData && passAllCuts[ZHSEL]){
          histo_Baseline[theCategory]->Fill(MVAVar,totalWeight);
        }
        else if(theCategory != kPlotData){
	  if(passAllCuts[ZHSEL]) {
	    histo_Baseline[theCategory]->Fill(MVAVar,totalWeight);
	    histo_QCDScaleBounding[theCategory][0]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[0])/maxQCDscale);
	    histo_QCDScaleBounding[theCategory][1]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[1])/maxQCDscale);
	    histo_QCDScaleBounding[theCategory][2]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[2])/maxQCDscale);
	    histo_QCDScaleBounding[theCategory][3]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[3])/maxQCDscale);
	    histo_QCDScaleBounding[theCategory][4]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[4])/maxQCDscale);
	    histo_QCDScaleBounding[theCategory][5]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[5])/maxQCDscale);
	    histo_PDFBoundingUp[theCategory]  ->Fill(MVAVar,totalWeight*TMath::Max((double)thePandaFlat.pdfUp,1.01));
	    histo_PDFBoundingDown[theCategory]->Fill(MVAVar,totalWeight*TMath::Min((double)thePandaFlat.pdfDown,0.99));
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
	    histo_EWKCorrWZUp  [theCategory]->Fill(MVAVar,totalWeight*sf_ewkcorrwz_unc);
	    histo_EWKCorrWZDown[theCategory]->Fill(MVAVar,totalWeight/sf_ewkcorrwz_unc);
	    histo_EWKqqZZCorrUp  [theCategory]->Fill(MVAVar,totalWeight*sf_ewkcorrzz_unc);
	    histo_EWKqqZZCorrDown[theCategory]->Fill(MVAVar,totalWeight/sf_ewkcorrzz_unc);
	    histo_ggZZCorrUp  [theCategory]->Fill(MVAVar,totalWeight*sf_ggcorrzz_unc);
	    histo_ggZZCorrDown[theCategory]->Fill(MVAVar,totalWeight/sf_ggcorrzz_unc);
	    histo_CorrWZZZUp  [theCategory]->Fill(MVAVar,totalWeight*sf_corrwzzz_unc);
	    histo_CorrWZZZDown[theCategory]->Fill(MVAVar,totalWeight/sf_corrwzzz_unc);
	    histo_EWKCorrZHUp  [theCategory]->Fill(MVAVar,totalWeight*sf_EWKZHUp  /sf_EWKZH);
	    histo_EWKCorrZHDown[theCategory]->Fill(MVAVar,totalWeight*sf_EWKZHDown/sf_EWKZH);
	  }
	  for(int ny=0; ny<nYears; ny++){
	    if(ny == whichYear) {
              if(passSystCuts[JESUP])   histo_JESBoundingUp  [ny][theCategory]->Fill(MVAVarUp  ,totalWeight);
              if(passSystCuts[JESDOWN]) histo_JESBoundingDown[ny][theCategory]->Fill(MVAVarDown,totalWeight);
            } else {
              if(passAllCuts[ZHSEL]) histo_JESBoundingUp  [ny][theCategory]->Fill(MVAVar,totalWeight);
              if(passAllCuts[ZHSEL]) histo_JESBoundingDown[ny][theCategory]->Fill(MVAVar,totalWeight);
	    }
	  }
        }
      }

    } // end events loop
    the_input_file->Close();
  } // end chain loop

  for(int ic=0; ic<nPlotCategories; ic++) histo[allPlots-1][ic]->Add(histo_Baseline[ic]);

  double qcdScaleTotal[2] = {0.0345, 0.2200}; // use sigma(ZH) (0.0345) instead of sigma(qq->ZZ) (0.0055) and sigma(gg->ZH) (0.2200)
  if(whichBSMName != "") {qcdScaleTotal[0] = 0.0; qcdScaleTotal[1] = 0.0;}
  double pdfTotal[2] = {0.016, 0.051};
  double syst_WZl[2] = {1.010, 1.012};

  for(unsigned ic=0; ic<nPlotCategories; ic++) {
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
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

      histo_Baseline              [ic]->SetBinContent(nb, TMath::Max((float)histo_Baseline		[ic]->GetBinContent(nb),0.0f));
      histo_QCDScaleUp  	  [ic]->SetBinContent(nb, TMath::Max((float)histo_QCDScaleUp		[ic]->GetBinContent(nb),0.0f));
      histo_QCDScaleDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_QCDScaleDown  	[ic]->GetBinContent(nb),0.0f));
      histo_PDFBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PDFBoundingUp 	[ic]->GetBinContent(nb),0.0f));
      histo_PDFBoundingDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PDFBoundingDown	[ic]->GetBinContent(nb),0.0f));
      histo_LepEffMBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_LepEffMBoundingUp	[ic]->GetBinContent(nb),0.0f));
      histo_LepEffMBoundingDown   [ic]->SetBinContent(nb, TMath::Max((float)histo_LepEffMBoundingDown	[ic]->GetBinContent(nb),0.0f));
      histo_LepEffEBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_LepEffEBoundingUp	[ic]->GetBinContent(nb),0.0f));
      histo_LepEffEBoundingDown   [ic]->SetBinContent(nb, TMath::Max((float)histo_LepEffEBoundingDown	[ic]->GetBinContent(nb),0.0f));
      histo_PUBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PUBoundingUp  	[ic]->GetBinContent(nb),0.0f));
      histo_PUBoundingDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PUBoundingDown	[ic]->GetBinContent(nb),0.0f));
      for(int ny=0; ny<nYears; ny++){
      histo_BTAGBBoundingUp    [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_BTAGBBoundingUp    [ny][ic]->GetBinContent(nb),0.0f));
      histo_BTAGBBoundingDown  [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_BTAGBBoundingDown  [ny][ic]->GetBinContent(nb),0.0f));
      histo_BTAGLBoundingUp    [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_BTAGLBoundingUp    [ny][ic]->GetBinContent(nb),0.0f));
      histo_BTAGLBoundingDown  [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_BTAGLBoundingDown  [ny][ic]->GetBinContent(nb),0.0f));
      histo_JESBoundingUp      [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_JESBoundingUp      [ny][ic]->GetBinContent(nb),0.0f));
      histo_JESBoundingDown    [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_JESBoundingDown    [ny][ic]->GetBinContent(nb),0.0f));
      histo_PreFireBoundingUp  [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_PreFireBoundingUp  [ny][ic]->GetBinContent(nb),0.0f));
      histo_PreFireBoundingDown[ny][ic]->SetBinContent(nb, TMath::Max((float)histo_PreFireBoundingDown[ny][ic]->GetBinContent(nb),0.0f));
      histo_TriggerBoundingUp  [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_TriggerBoundingUp  [ny][ic]->GetBinContent(nb),0.0f));
      histo_TriggerBoundingDown[ny][ic]->SetBinContent(nb, TMath::Max((float)histo_TriggerBoundingDown[ny][ic]->GetBinContent(nb),0.0f));
      }
      histo_EWKCorrWZUp 	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKCorrWZUp		[ic]->GetBinContent(nb),0.0f));
      histo_EWKCorrWZDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKCorrWZDown 	[ic]->GetBinContent(nb),0.0f));
      histo_EWKqqZZCorrUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKqqZZCorrUp 	[ic]->GetBinContent(nb),0.0f));
      histo_EWKqqZZCorrDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKqqZZCorrDown	[ic]->GetBinContent(nb),0.0f));
      histo_ggZZCorrUp  	  [ic]->SetBinContent(nb, TMath::Max((float)histo_ggZZCorrUp		[ic]->GetBinContent(nb),0.0f));
      histo_ggZZCorrDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_ggZZCorrDown  	[ic]->GetBinContent(nb),0.0f));
      histo_CorrWZZZUp  	  [ic]->SetBinContent(nb, TMath::Max((float)histo_CorrWZZZUp		[ic]->GetBinContent(nb),0.0f));
      histo_CorrWZZZDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_CorrWZZZDown  	[ic]->GetBinContent(nb),0.0f));
      histo_EWKCorrZHUp 	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKCorrZHUp		[ic]->GetBinContent(nb),0.0f));
      histo_EWKCorrZHDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKCorrZHDown 	[ic]->GetBinContent(nb),0.0f));
    }
    histo_PUBoundingUp	[ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_PUBoundingUp  [ic]->GetSumOfWeights());
    histo_PUBoundingDown[ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_PUBoundingDown[ic]->GetSumOfWeights());
    if     (ic == kPlotBSM && whichBSMName != "") {
      // Do nothing
    }
    else if(ic == kPlotWZ || ic == kPlotZZ || ic == kPlotBSM || ic == kPlotEM || ic == kPlotDY) {
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

    printf("uncertainties CorrZZWZUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_CorrWZZZUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties CorrZZWZDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_CorrWZZZDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties EWKCorrZHUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_EWKCorrZHUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties EWKCorrZHDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_EWKCorrZHDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
  }

  // Filling datacards input root file
  char outputLimits[200];
  sprintf(outputLimits,"zh%s_%d_%dj_input.root",whichBSMName.Data(),year,jetValue);
  TFile* outFileLimits = new TFile(outputLimits,"recreate");
  outFileLimits->cd();

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
    histo_EWKCorrWZUp		[ic]->Write();
    histo_EWKCorrWZDown 	[ic]->Write();
    histo_EWKqqZZCorrUp 	[ic]->Write();
    histo_EWKqqZZCorrDown	[ic]->Write();
    histo_ggZZCorrUp		[ic]->Write();
    histo_ggZZCorrDown  	[ic]->Write();
    histo_CorrWZZZUp		[ic]->Write();
    histo_CorrWZZZDown  	[ic]->Write();
    histo_EWKCorrZHUp		[ic]->Write();
    histo_EWKCorrZHDown 	[ic]->Write();
  }
  outFileLimits->Close();


  // Filling datacards txt file
  char outputLimitsCard[200];  					  
  sprintf(outputLimitsCard,"datacard_zh%s_%d_%dj.txt",whichBSMName.Data(),year,jetValue);
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

  newcardShape << Form("CMS_momres_m    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("%6.3f ",1.005);
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_momres_e    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("%6.3f ",1.005);
  }
  newcardShape << Form("\n");

  newcardShape << Form("UEPS    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotBSM) newcardShape << Form(" - ");
    else               newcardShape << Form("%f  ", 1.02);
  }
  newcardShape << Form("\n");

  if(useZZWZEWKUnc == false){
    newcardShape << Form("EWKWZCorr    shape     ");
    for (int ic=0; ic<nPlotCategories; ic++){
      if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
      if(ic != kPlotWZ) newcardShape << Form("- ");
      else              newcardShape << Form("1.0 ");
    }
    newcardShape << Form("\n");

    newcardShape << Form("EWKqqZZCorr    shape     ");
    for (int ic=0; ic<nPlotCategories; ic++){
      if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
      if(ic != kPlotZZ) newcardShape << Form("- ");
      else              newcardShape << Form("1.0 ");
    }
    newcardShape << Form("\n");

    newcardShape << Form("ggZZCorr    shape     ");
    for (int ic=0; ic<nPlotCategories; ic++){
      if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
      if(ic != kPlotZZ) newcardShape << Form("- ");
      else              newcardShape << Form("1.0 ");
    }
    newcardShape << Form("\n");
  }
  else {
    newcardShape << Form("CorrWZZZ    shape     ");
    for (int ic=0; ic<nPlotCategories; ic++){
      if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
      if(ic != kPlotZZ) newcardShape << Form("- ");
      else              newcardShape << Form("1.0 ");
    }
    newcardShape << Form("\n");
  }

  newcardShape << Form("EWKZHCorr    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotBSM) newcardShape << Form("- ");
    else	       newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("WZ_lep    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotWZ) newcardShape << Form("- ");
    else              newcardShape << Form("%f ",syst_WZl[0]);
  }
  newcardShape << Form("\n");

  newcardShape << Form("WZ_tau    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotWZ) newcardShape << Form("- ");
    else              newcardShape << Form("%f ",syst_WZl[1]);
  }
  newcardShape << Form("\n");

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

  newcardShape << Form("CMS_pu    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_btagb_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_btagl_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_jes_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt || ic == kPlotDY) newcardShape << Form("- ");
    else                                      newcardShape << Form("1.0 ");
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

  if(useZZWZEWKUnc == true){
    newcardShape << Form("CMS_hinv_vvnorm_bin_%d  rateParam * %s 1 [0.1,10]\n",year,plotBaseNames[kPlotZZ].Data());
    newcardShape << Form("CMS_hinv_vvnorm_bin_%d  rateParam * %s 1 [0.1,10]\n",year,plotBaseNames[kPlotWZ].Data());
  }
  else {
    newcardShape << Form("CMS_hinv_zznorm_bin_%d  rateParam * %s 1 [0.1,10]\n",year,plotBaseNames[kPlotZZ].Data());
    newcardShape << Form("CMS_hinv_wznorm_bin_%d  rateParam * %s 1 [0.1,10]\n",year,plotBaseNames[kPlotWZ].Data());
  }
  newcardShape << Form("CMS_hinv_emnorm_bin_%d  rateParam * %s 1 [0.1,10]\n",year,plotBaseNames[kPlotEM].Data());
  newcardShape << Form("CMS_hinv_dynorm%d_bin_%d  rateParam * %s 1 [0.1,10]\n",jetValue,year,plotBaseNames[kPlotDY].Data());

  newcardShape << Form("ch1 autoMCStats 0\n");

  newcardShape.close();

  // Writing standard histograms
  char output[200];
  if(whichBSMName == ""){
    for(int thePlot=0; thePlot<allPlots; thePlot++){
      sprintf(output,"histoZH%s_%d_%dj_%d.root",whichBSMName.Data(),year,jetValue,thePlot);	
      TFile* outFilePlotsNote = new TFile(output,"recreate");
      outFilePlotsNote->cd();
      double totBck = 0;
      for(int i=1; i<nPlotCategories; i++) if(i != kPlotBSM) totBck = totBck + histo[thePlot][i]->GetSumOfWeights();
      printf("(%2d) %7.1f vs. %7.1f ",thePlot,histo[thePlot][0]->GetSumOfWeights(),totBck);
      printf("(");
      for(int i=1; i<nPlotCategories; i++) printf("%7.1f ",histo[thePlot][i]->GetSumOfWeights());
      printf(")\n");
      for(int np=0; np<nPlotCategories; np++) {histo[thePlot][np]->SetNameTitle(Form("histo%d",np),Form("histo%d",np));histo[thePlot][np]->Write();}
      outFilePlotsNote->Close();
    }
  }

}
