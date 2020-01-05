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

#include "TMVA/Reader.h"
#include "MitAnalysisRunII/panda/macros/9x/pandaFlat.C"
#include "MitAnalysisRunII/panda/macros/9x/common.h"
#include "MitAnalysisRunII/panda/macros/9x/applyCorrections.h"

const double mcPrescale = 1;
const bool usePureMC = false;
const int debug = 0;
const bool showSyst = true;
const bool produceMVAInputs = false;
const bool isPseudoData = false;

double syst_WZl[2] = {1.010, 1.012};

// fidAna == 0 (SM), 1 (SM-altWZ), 2 (MJJ), 3 (MLL), 4 (AQGC), 5(long)

enum systType                     {JESUP=0, JESDOWN,  JERUP,  JERDOWN, nSystTypes};
TString systTypeName[nSystTypes]= {"JESUP","JESDOWN","JERUP","JERDOWN"};

void sswwAnalysis(
int year, int fidAna = 0, bool isDesk014 = false, TString WZName = "WZ3l_MG"
){
  int nTypeLepSel[2] = {-1, -1};
  int whichYear = -1;
  if     (year == 2016) {whichYear = Y2016; nTypeLepSel[0] =  2; nTypeLepSel[1] = 7;}
  else if(year == 2017) {whichYear = Y2017; nTypeLepSel[0] = 13; nTypeLepSel[1] = 7;}
  else if(year == 2018) {whichYear = Y2018; nTypeLepSel[0] = 15; nTypeLepSel[1] = 7;}
  else {printf("Wrong year (%d)!\n",year); return;}

  TString fidAnaName = "";
  if(fidAna >= 1) fidAnaName = Form("_fiducial%d",fidAna);

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
  TString trgSFPath = Form("MitAnalysisRunII/data/90x/trigger/histo_triggerEff_sel0_%d.root",year);
  TString effSFPath = Form("MitAnalysisRunII/data/90x/eff/histoDY0EffSFStudy_%d.root",year);
  //TString npvPath = Form("MitAnalysisRunII/data/90x/pu/npvWeights_%d.root",year);
  if     (year == 2018) {
    filesPath = Form("%s/ceballos/panda/v_006_1/",inputFolder.Data());
    puPath = "MitAnalysisRunII/data/90x/pu/puWeights_90x_2018.root";

    if     (WZName == "WZ3l_MG"){
      infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	          infileCat_.push_back(kPlotData);

      if(fidAna == 5) {
      infileName_.push_back(Form("%sWWjj_SS_long.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotSignal0);
      infileName_.push_back(Form("%sWWjj_SS_lttt.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotSignal1);
      }
      else {
      //infileName_.push_back(Form("%sWpWp_EWK.root" ,filesPath.Data())); 	  infileCat_.push_back(kPlotEWKSSWW);
      infileName_.push_back(Form("%sWWjj_SS_long.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotEWKSSWW);
      infileName_.push_back(Form("%sWWjj_SS_lttt.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotEWKSSWW);
      }
      infileName_.push_back(Form("%sWZ3l_MG_EWK.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotEWKWZ);
      if(fidAna == 4) {
      infileName_.push_back(Form("%sWWjj_SS_dim8_ewk.root" ,filesPath.Data()));   infileCat_.push_back(kPlotEWKSSWW_dim8);
      infileName_.push_back(Form("%sWZjj_dim8_ewk.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotEWKWZ_dim8);
      }

      infileName_.push_back(Form("%sWpWp_QCD.root" ,filesPath.Data())); 	  infileCat_.push_back(kPlotQCDSSWW);

      infileName_.push_back(Form("%sWZ3l_MG_QCD.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWZ);

      infileName_.push_back(Form("%sZZJJ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);
      //infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);
      //infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);

      infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotTVX);
      infileName_.push_back(Form("%sTTVV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotTVX);

      infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sggWW.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sDYNJetsToLL.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotWS);

      infileName_.push_back(Form("%sVG_M120.root" ,filesPath.Data()));            infileCat_.push_back(kPlotVG);

      infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotOther);
      infileName_.push_back(Form("%sWWdps.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotOther);

    }
    else if(WZName == "WZ3l_powheg"){
      infileName_.push_back(Form("%sWZ3l_powheg.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWZ);
    }
    else if(WZName == "WZ3l_amcnlo"){
      infileName_.push_back(Form("%sWZ3l_amcnlo.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWZ);
    }
    else if(WZName == "WZ3l_MG_only"){
      infileName_.push_back(Form("%sWZ3l_MG_QCD.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWZ);
    }
    else {
      printf("Wrong WZName (%s), exit\n",WZName.Data());
      return;
    }
  }
  else if(year == 2017) {
    filesPath = Form("%s/ceballos/panda/v_004_1/",inputFolder.Data());
    puPath = "MitAnalysisRunII/data/90x/pu/puWeights_90x_2017.root";

    if     (WZName == "WZ3l_MG"){
      infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	          infileCat_.push_back(kPlotData);

      if(fidAna == 5) {
      infileName_.push_back(Form("%sWWjj_SS_long.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotSignal0);
      infileName_.push_back(Form("%sWWjj_SS_lttt.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotSignal1);
      }
      else {
      //infileName_.push_back(Form("%sWpWp_EWK.root" ,filesPath.Data())); 	  infileCat_.push_back(kPlotEWKSSWW);
      infileName_.push_back(Form("%sWWjj_SS_long.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotEWKSSWW);
      infileName_.push_back(Form("%sWWjj_SS_lttt.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotEWKSSWW);
      }
      infileName_.push_back(Form("%sWZ3l_MG_EWK.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotEWKWZ);
      if(fidAna == 4) {
      infileName_.push_back(Form("%sWWjj_SS_dim8_ewk.root" ,filesPath.Data()));   infileCat_.push_back(kPlotEWKSSWW_dim8);
      infileName_.push_back(Form("%sWZjj_dim8_ewk.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotEWKWZ_dim8);
      }

      infileName_.push_back(Form("%sWpWp_QCD.root" ,filesPath.Data())); 	  infileCat_.push_back(kPlotQCDSSWW);

      infileName_.push_back(Form("%sWZ3l_MG_QCD.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWZ);

      infileName_.push_back(Form("%sZZJJ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);
      //infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);
      //infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);

      infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotTVX);
      infileName_.push_back(Form("%sTTVV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotTVX);

      infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sggWW.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sDYNJetsToLL.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotWS);

      infileName_.push_back(Form("%sVG_M120.root" ,filesPath.Data()));            infileCat_.push_back(kPlotVG);

      infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotOther);
      infileName_.push_back(Form("%sWWdps.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotOther);
    }
    else if(WZName == "WZ3l_powheg"){
      infileName_.push_back(Form("%sWZ3l_powheg.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWZ);
    }
    else if(WZName == "WZ3l_amcnlo"){
      infileName_.push_back(Form("%sWZ3l_amcnlo.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWZ);
    }
    else if(WZName == "WZ3l_powheg_mll1"){
      infileName_.push_back(Form("%sWZ3l_powheg_mll1.root" ,filesPath.Data()));   infileCat_.push_back(kPlotWZ);
    }
    else if(WZName == "WZ3l_MG_only"){
      infileName_.push_back(Form("%sWZ3l_MG_QCD.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWZ);
    }
    else {
      printf("Wrong WZName (%s), exit\n",WZName.Data());
      return;
    }
  }
  else if(year == 2016) {
    filesPath = Form("%s/ceballos/panda/v_002_1/",inputFolder.Data());
    puPath = "MitAnalysisRunII/data/90x/pu/puWeights_90x_2016.root";

    if     (WZName == "WZ3l_MG"){
      infileName_.push_back(Form("%sdata.root",filesPath.Data()));		  infileCat_.push_back(kPlotData);

      if(fidAna == 5) {
      infileName_.push_back(Form("%sWWjj_SS_long.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotSignal0);
      infileName_.push_back(Form("%sWWjj_SS_lttt.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotSignal1);
      }
      else {
      //infileName_.push_back(Form("%sWpWp_EWK.root" ,filesPath.Data())); 	  infileCat_.push_back(kPlotEWKSSWW);
      infileName_.push_back(Form("%sWWjj_SS_long.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotEWKSSWW);
      infileName_.push_back(Form("%sWWjj_SS_lttt.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotEWKSSWW);
      }
      infileName_.push_back(Form("%sWZ3l_MG_EWK.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotEWKWZ);
      if(fidAna == 4) {
      infileName_.push_back(Form("%sWWjj_SS_dim8_ewk.root" ,filesPath.Data()));   infileCat_.push_back(kPlotEWKSSWW_dim8);
      infileName_.push_back(Form("%sWZjj_dim8_ewk.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotEWKWZ_dim8);
      }

      infileName_.push_back(Form("%sWpWp_QCD.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotQCDSSWW);

      infileName_.push_back(Form("%sWZ3l_MG_QCD.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotWZ);

      infileName_.push_back(Form("%sZZJJ.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotZZ);
      //infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotZZ);
      //infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotZZ);

      infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotTVX);

      infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sggWW.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sTW.root" ,filesPath.Data())); 		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sDYNJetsToLL.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sH125.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);

      infileName_.push_back(Form("%sVG_M120.root" ,filesPath.Data()));            infileCat_.push_back(kPlotVG);

      infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotOther);
      infileName_.push_back(Form("%sWWdps.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotOther);
    }
    else if(WZName == "WZ3l_powheg"){
      infileName_.push_back(Form("%sWZ.root" ,filesPath.Data()));                 infileCat_.push_back(kPlotWZ);
      infileName_.push_back(Form("%sWGstar.root" ,filesPath.Data()));             infileCat_.push_back(kPlotWZ);
    }
    else if(WZName == "WZ3l_MG_only"){
      infileName_.push_back(Form("%sWZ3l_MG_QCD.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWZ);
    }
  }
  else {
    return;
  }

  //infileName_.clear();infileCat_.clear();
  //infileName_.push_back(Form("%sWpWp_EWK.root" ,filesPath.Data())); infileCat_.push_back(kPlotEWKSSWW);
  //infileName_.push_back(Form("%sWZ3l_amcnlo.root" ,filesPath.Data())); infileCat_.push_back(kPlotWZ);
  //infileName_.push_back(Form("%sWZ3l_MG_QCD.root" ,filesPath.Data())); infileCat_.push_back(kPlotWZ);
  //infileName_.push_back(Form("%sWZ3l_MG_EWK.root" ,filesPath.Data())); infileCat_.push_back(kPlotEWKWZ);
  //infileName_.push_back(Form("%sWWjj_SS_dim8_ewk.root" ,filesPath.Data())); infileCat_.push_back(kPlotEWKSSWW_dim8);
  //infileName_.push_back(Form("%sWZjj_dim8_ewk.root" ,filesPath.Data())); infileCat_.push_back(kPlotEWKWZ_dim8);
  //infileName_.push_back(Form("%sWWjj_SS_long.root" ,filesPath.Data())); infileCat_.push_back(kPlotEWKSSWW);
  //infileName_.push_back(Form("%sWWjj_SS_lttt.root" ,filesPath.Data())); infileCat_.push_back(kPlotEWKSSWW);
  //infileName_.push_back(Form("%sTZQ.root" ,"/data/t3home000/ceballos/panda/v_004_0/")); infileCat_.push_back(kPlotTVX);

  TFile *fLepton_Fakes = TFile::Open(fLepton_FakesName.Data());
  TH2D* histoFakeEffSelMediumEtaPt_m = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_2_0"); histoFakeEffSelMediumEtaPt_m->SetDirectory(0);
  TH2D* histoFakeEffSelMediumEtaPt_e = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_0_1"); histoFakeEffSelMediumEtaPt_e->SetDirectory(0);
  TH2D* histoFakeEffSelTightEtaPt_m  = (TH2D*)fLepton_Fakes->Get(Form("histoFakeEffSelEtaPt_%d_0",nTypeLepSel[0])); histoFakeEffSelTightEtaPt_m ->SetDirectory(0);	
  TH2D* histoFakeEffSelTightEtaPt_e  = (TH2D*)fLepton_Fakes->Get(Form("histoFakeEffSelEtaPt_%d_1",nTypeLepSel[1])); histoFakeEffSelTightEtaPt_e ->SetDirectory(0);
  fLepton_Fakes->Close();

  TFile *fLepton_Eff = TFile::Open(effSFPath.Data());
  TH2D* histoLepEffSelMediumEtaPt_m = (TH2D*)fLepton_Eff->Get("histoEffSFStudy_2_0"); histoLepEffSelMediumEtaPt_m->SetDirectory(0);
  TH2D* histoLepEffSelMediumEtaPt_e = (TH2D*)fLepton_Eff->Get("histoEffSFStudy_0_1"); histoLepEffSelMediumEtaPt_e->SetDirectory(0);
  TH2D* histoLepEffSelTightEtaPt_m  = (TH2D*)fLepton_Eff->Get(Form("histoEffSFStudy_%d_0",nTypeLepSel[0])); histoLepEffSelTightEtaPt_m ->SetDirectory(0);   
  TH2D* histoLepEffSelTightEtaPt_e  = (TH2D*)fLepton_Eff->Get(Form("histoEffSFStudy_%d_1",nTypeLepSel[1])); histoLepEffSelTightEtaPt_e ->SetDirectory(0);
  fLepton_Eff->Close();

  TFile *fPUFile = TFile::Open(Form("%s",puPath.Data()));
  TH1D *fhDPU     = (TH1D*)(fPUFile->Get("puWeights"));     assert(fhDPU);     fhDPU    ->SetDirectory(0);
  TH1D *fhDPUUp   = (TH1D*)(fPUFile->Get("puWeightsUp"));   assert(fhDPUUp);   fhDPUUp  ->SetDirectory(0);
  TH1D *fhDPUDown = (TH1D*)(fPUFile->Get("puWeightsDown")); assert(fhDPUDown); fhDPUDown->SetDirectory(0);
  delete fPUFile;

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

  //TFile *fNPVFile = TFile::Open(Form("%s",npvPath.Data()));
  //TH1D *fhDNPV    = (TH1D*)(fNPVFile->Get("npvWeights"));   assert(fhDNPV);    fhDNPV	->SetDirectory(0);
  //delete fNPVFile;

  TFile *fVVEWKCorr = TFile::Open("MitAnalysisRunII/data/90x/theory/VV_NLO_LO_CMS_mjj.root");
  TH1D *hWZ_KF_CMS     = (TH1D*)(fVVEWKCorr->Get("hWZ_KF_CMS"));     assert(hWZ_KF_CMS    ); hWZ_KF_CMS    ->SetDirectory(0);
  TH1D *hWZ_KF_CMSUp   = (TH1D*)(fVVEWKCorr->Get("hWZ_KF_CMSUp"));   assert(hWZ_KF_CMSUp  ); hWZ_KF_CMSUp  ->SetDirectory(0);
  TH1D *hWZ_KF_CMSDown = (TH1D*)(fVVEWKCorr->Get("hWZ_KF_CMSDown")); assert(hWZ_KF_CMSDown); hWZ_KF_CMSDown->SetDirectory(0);
  TH1D *hWW_KF_CMS     = (TH1D*)(fVVEWKCorr->Get("hWW_KF_CMS"));     assert(hWW_KF_CMS    ); hWW_KF_CMS    ->SetDirectory(0);
  TH1D *hWW_KF_CMSUp   = (TH1D*)(fVVEWKCorr->Get("hWW_KF_CMSUp"));   assert(hWW_KF_CMSUp  ); hWW_KF_CMSUp  ->SetDirectory(0);
  TH1D *hWW_KF_CMSDown = (TH1D*)(fVVEWKCorr->Get("hWW_KF_CMSDown")); assert(hWW_KF_CMSDown); hWW_KF_CMSDown->SetDirectory(0);
  delete fVVEWKCorr;

  const int nBinMJJ = 8; Float_t xbinsMJJ[nBinMJJ+1] = {500,650,800,1000,1200,1500,1800,2300,3000};
  const int nBinMJJCR = 4; Float_t xbinsMJJCR[nBinMJJCR+1] = {500,800,1200,1800,3000};
  const int nBinMLL = 4; Float_t xbinsMLL[nBinMLL+1] = {20, 80, 140, 240, 500};
  const int nBinWZBDT = 8; Float_t xbinsWZBDT[nBinWZBDT+1] = {-1.000,-0.280,-0.000, 0.230, 0.430, 0.600, 0.740, 0.860, 1.000};
  const int nBinWWBDT = 7; Float_t xbinsWWBDT[nBinWWBDT+1] = {-1.000,-0.244, 0.040, 0.243, 0.401, 0.535, 0.662, 1.000}; // V1_v6
  int nBinMVAAux = 0;
  if     (fidAna == 0 || fidAna == 2 || fidAna == 3) nBinMVAAux = nBinMJJ*nBinMLL + 3*nBinMJJCR + nBinWZBDT;
  else if(fidAna == 1) nBinMVAAux = nBinMJJ*nBinMLL + nBinMJJ + 2 + 12;
  else if(fidAna == 4) nBinMVAAux = 4*5 + 4 + 2 + 6;
  else if(fidAna == 5) nBinMVAAux = nBinMJJCR*nBinWWBDT + nBinWWBDT + 2*nBinMJJCR + 12;
  const int nBinMVA = nBinMVAAux; Float_t xbins[nBinMVA+1];
  for(int nb=0; nb<=nBinMVA; nb++) xbins[nb] = -0.5 + nb;

  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 92;
  TH1D* histo[allPlots][nPlotCategories];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    if     (thePlot >=   0 && thePlot <=   4) {nBinPlot =2500; xminPlot = 500.0; xmaxPlot = 3000.0;}
    else if(thePlot >=   5 && thePlot <=   9) {nBinPlot =  22; xminPlot =  2.5; xmaxPlot = 8.0;}
    else if(thePlot >=  10 && thePlot <=  14) {nBinPlot =   8; xminPlot = -0.5; xmaxPlot = 7.5;}
    else if(thePlot >=  15 && thePlot <=  19) {nBinPlot =  50; xminPlot = 50.0; xmaxPlot = 450;}
    else if(thePlot >=  20 && thePlot <=  24) {nBinPlot =  50; xminPlot = -5.0; xmaxPlot = 5.0;}
    else if(thePlot >=  25 && thePlot <=  29) {nBinPlot =   4; xminPlot =  1.5; xmaxPlot = 5.5;}
    else if(thePlot >=  30 && thePlot <=  32) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 500.0;}
    else if(thePlot >=  33 && thePlot <=  35) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 200.0;}
    else if(thePlot >=  36 && thePlot <=  38) {nBinPlot =   6; xminPlot = -0.5; xmaxPlot = 5.5;}
    else if(thePlot >=  39 && thePlot <=  41) {nBinPlot =  80; xminPlot =  0.0; xmaxPlot = 8.0;}
    else if(thePlot >=  42 && thePlot <=  44) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot =2000;}
    else if(thePlot >=  45 && thePlot <=  47) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 1.0;}
    else if(thePlot >=  48 && thePlot <=  53) {nBinPlot =   5; xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >=  54 && thePlot <=  54) {nBinPlot = 200; xminPlot =500.0; xmaxPlot =2500;}
    else if(thePlot >=  55 && thePlot <=  55) {nBinPlot =  80; xminPlot =  0.0; xmaxPlot = 8.0;}
    else if(thePlot >=  56 && thePlot <=  56) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 1.0;}
    else if(thePlot >=  57 && thePlot <=  59) {nBinPlot =   5; xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >=  60 && thePlot <=  60) {nBinPlot = 100; xminPlot = 50.0; xmaxPlot = 450;}
    else if(thePlot >=  61 && thePlot <=  61) {nBinPlot = 100; xminPlot = -5.0; xmaxPlot = 5.0;}
    else if(thePlot >=  62 && thePlot <=  62) {nBinPlot = 100; xminPlot = 20.0; xmaxPlot = 220;}
    else if(thePlot >=  63 && thePlot <=  63) {nBinPlot =  50; xminPlot =  0.0; xmaxPlot = 2.5;}
    else if(thePlot >=  64 && thePlot <=  65) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 1.0;}
    else if(thePlot >=  66 && thePlot <=  67) {nBinPlot = 500; xminPlot =  0.0; xmaxPlot = 500.0;}
    else if(thePlot >=  68 && thePlot <=  76) {nBinPlot = 100; xminPlot = 20.0; xmaxPlot = 220;}
    else if(thePlot >=  77 && thePlot <=  77) {nBinPlot = 200; xminPlot = -1.0; xmaxPlot = 1.0;}
    else if(thePlot >=  78 && thePlot <=  78) {nBinPlot = 20; xminPlot =  0.0; xmaxPlot = 1000;}
    else if(thePlot >=  79 && thePlot <=  83) {nBinPlot = 12; xminPlot = 200; xmaxPlot = 500.0;}
    else if(thePlot >=  84 && thePlot <=  88) {nBinPlot =  22; xminPlot =  2.5; xmaxPlot = 8.0;}
    else if(thePlot >=  89 && thePlot <=  90) {nBinPlot = 2000; xminPlot = -1.0; xmaxPlot = 1.0;}
    if     (thePlot == allPlots-1)            for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinMVA, xbins);
    else if(thePlot >=   0 && thePlot <=   4) for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinMJJ, xbinsMJJ);
    else if(thePlot >=  66 && thePlot <=  67) for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinMLL, xbinsMLL);
    else if(thePlot >=  77 && thePlot <=  77) for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinWZBDT, xbinsWZBDT);
    else if(thePlot >=  89 && thePlot <=  90) for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinWWBDT, xbinsWWBDT);
    else                                      for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinPlot, xminPlot, xmaxPlot);
  }

  TH1D* histo_MVA = new TH1D("histo_MVA", "histo_MVA", nBinMVA, xbins); histo_MVA->Sumw2();

  TH1D *histo_aqgc_ft0_Baseline[2][nscan_ft0];
  TH1D *histo_aqgc_ft1_Baseline[2][nscan_ft1];
  TH1D *histo_aqgc_ft2_Baseline[2][nscan_ft2];
  TH1D *histo_aqgc_fm0_Baseline[2][nscan_fm0];
  TH1D *histo_aqgc_fm1_Baseline[2][nscan_fm1];
  TH1D *histo_aqgc_fm6_Baseline[2][nscan_fm6];
  TH1D *histo_aqgc_fm7_Baseline[2][nscan_fm7];
  TH1D *histo_aqgc_fs0_Baseline[2][nscan_fs0];
  TH1D *histo_aqgc_fs1_Baseline[2][nscan_fs1];

  for(int nb=0; nb<2; nb++){
    for(int iscan=0; iscan<nscan_ft0; iscan++) histo_aqgc_ft0_Baseline[nb][iscan]=(TH1D*)histo_MVA->Clone(Form("histo_aqgc_%d_ft0_%s",nb,AQGC_ft0_range[iscan].Data()));
    for(int iscan=0; iscan<nscan_ft1; iscan++) histo_aqgc_ft1_Baseline[nb][iscan]=(TH1D*)histo_MVA->Clone(Form("histo_aqgc_%d_ft1_%s",nb,AQGC_ft1_range[iscan].Data()));
    for(int iscan=0; iscan<nscan_ft2; iscan++) histo_aqgc_ft2_Baseline[nb][iscan]=(TH1D*)histo_MVA->Clone(Form("histo_aqgc_%d_ft2_%s",nb,AQGC_ft2_range[iscan].Data()));
    for(int iscan=0; iscan<nscan_fm0; iscan++) histo_aqgc_fm0_Baseline[nb][iscan]=(TH1D*)histo_MVA->Clone(Form("histo_aqgc_%d_fm0_%s",nb,AQGC_fm0_range[iscan].Data()));
    for(int iscan=0; iscan<nscan_fm1; iscan++) histo_aqgc_fm1_Baseline[nb][iscan]=(TH1D*)histo_MVA->Clone(Form("histo_aqgc_%d_fm1_%s",nb,AQGC_fm1_range[iscan].Data()));
    for(int iscan=0; iscan<nscan_fm6; iscan++) histo_aqgc_fm6_Baseline[nb][iscan]=(TH1D*)histo_MVA->Clone(Form("histo_aqgc_%d_fm6_%s",nb,AQGC_fm6_range[iscan].Data()));
    for(int iscan=0; iscan<nscan_fm7; iscan++) histo_aqgc_fm7_Baseline[nb][iscan]=(TH1D*)histo_MVA->Clone(Form("histo_aqgc_%d_fm7_%s",nb,AQGC_fm7_range[iscan].Data()));
    for(int iscan=0; iscan<nscan_fs0; iscan++) histo_aqgc_fs0_Baseline[nb][iscan]=(TH1D*)histo_MVA->Clone(Form("histo_aqgc_%d_fs0_%s",nb,AQGC_fs0_range[iscan].Data()));
    for(int iscan=0; iscan<nscan_fs1; iscan++) histo_aqgc_fs1_Baseline[nb][iscan]=(TH1D*)histo_MVA->Clone(Form("histo_aqgc_%d_fs1_%s",nb,AQGC_fs1_range[iscan].Data()));
  }

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
  TH1D *histo_JERBoundingUp[nYears][nPlotCategories];
  TH1D *histo_JERBoundingDown[nYears][nPlotCategories];
  TH1D *histo_PreFireBoundingUp[nYears][nPlotCategories];
  TH1D *histo_PreFireBoundingDown[nYears][nPlotCategories];
  TH1D *histo_TriggerBoundingUp[nYears][nPlotCategories];
  TH1D *histo_TriggerBoundingDown[nYears][nPlotCategories];
  TH1D *histo_WSBoundingUp[nPlotCategories];
  TH1D *histo_WSBoundingDown[nPlotCategories];
  TH1D *histo_EWKCorrVVUp[nPlotCategories];
  TH1D *histo_EWKCorrVVDown[nPlotCategories];
  TH1D *histo_EWKqqZZCorrUp[nPlotCategories];
  TH1D *histo_EWKqqZZCorrDown[nPlotCategories];
  TH1D *histo_ggZZCorrUp[nPlotCategories];
  TH1D *histo_ggZZCorrDown[nPlotCategories];
  TH1D *histo_WZTauHUp[nPlotCategories];
  TH1D *histo_WZTauHDown[nPlotCategories];
  TH1D *histo_WZTauLUp[nPlotCategories];
  TH1D *histo_WZTauLDown[nPlotCategories];
  
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
    histo_PUBoundingUp		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_puUp"           , plotBaseNames[ic].Data()));
    histo_PUBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_puDown"         , plotBaseNames[ic].Data()));
    for(int ny=0; ny<nYears; ny++){
    histo_BTAGBBoundingUp    [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_btagb_%dUp"     , plotBaseNames[ic].Data(),2016+ny));
    histo_BTAGBBoundingDown  [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_btagb_%dDown"   , plotBaseNames[ic].Data(),2016+ny));
    histo_BTAGLBoundingUp    [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_btagl_%dUp"     , plotBaseNames[ic].Data(),2016+ny));
    histo_BTAGLBoundingDown  [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_btagl_%dDown"   , plotBaseNames[ic].Data(),2016+ny));
    histo_JESBoundingUp      [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_jes_%dUp"	   , plotBaseNames[ic].Data(),2016+ny));
    histo_JESBoundingDown    [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_jes_%dDown"	   , plotBaseNames[ic].Data(),2016+ny));
    histo_JERBoundingUp      [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_jer_%dUp"	   , plotBaseNames[ic].Data(),2016+ny));
    histo_JERBoundingDown    [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_jer_%dDown"	   , plotBaseNames[ic].Data(),2016+ny));
    histo_PreFireBoundingUp  [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_prefire_%dUp"   , plotBaseNames[ic].Data(),2016+ny));
    histo_PreFireBoundingDown[ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_prefire_%dDown" , plotBaseNames[ic].Data(),2016+ny));
    histo_TriggerBoundingUp  [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_trigger_%dUp"   , plotBaseNames[ic].Data(),2016+ny));
    histo_TriggerBoundingDown[ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_trigger_%dDown" , plotBaseNames[ic].Data(),2016+ny));
    }
    histo_WSBoundingUp          [ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_wseffUp"        , plotBaseNames[ic].Data()));
    histo_WSBoundingDown        [ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_wseffDown"      , plotBaseNames[ic].Data()));
    histo_EWKCorrVVUp           [ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKCorrVV%sUp"	  , plotBaseNames[ic].Data(), plotBaseNames[ic].Data()));
    histo_EWKCorrVVDown         [ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKCorrVV%sDown"	  , plotBaseNames[ic].Data(), plotBaseNames[ic].Data()));
    histo_EWKqqZZCorrUp 	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKqqZZCorrUp"      , plotBaseNames[ic].Data()));
    histo_EWKqqZZCorrDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKqqZZCorrDown"    , plotBaseNames[ic].Data()));
    histo_ggZZCorrUp		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_ggZZCorrUp"         , plotBaseNames[ic].Data()));
    histo_ggZZCorrDown		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_ggZZCorrDown"       , plotBaseNames[ic].Data()));
    histo_WZTauHUp		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_WZTauHUp"           , plotBaseNames[ic].Data()));
    histo_WZTauHDown		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_WZTauHDown"         , plotBaseNames[ic].Data()));
    histo_WZTauLUp		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_WZTauLUp"           , plotBaseNames[ic].Data()));
    histo_WZTauLDown		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_WZTauLDown"         , plotBaseNames[ic].Data()));
  }

  // Begin MVA-weigths initialization
  int category;
  unsigned long long int  eventNum;
  double weight;
  float mvamjj, mvadetajj, mvadphijj, mvajetpt1, mvajetpt2, mvajeteta1, mvajeteta2, mvanjets;
  float mvaWpt, mvaZpt, mvaVVmt, mvaWlZdeta;
  float mvazstar, mvazep1, mvazep2, mvazep3, mvamaxzep, mvaj1Zdr, mvaj2Zdr, mvapttot, mvasumpttot;
  float mvaleppt1, mvaleppt2, mvalepeta1, mvalepeta2, mvadphill, mvadrll, mvamll;
  float mvaWWInputs[25];
  TString bdtWWWeights="";
  //bdtWWWeights="MitAnalysisRunII/BDT/ssww_WWDec_V0/bdt_BDTG_26var.weights.xml"; // 26var, ptj50/50
  //bdtWWWeights="MitAnalysisRunII/BDT/ssww_WWDec_V0/bdt_BDTG_25var.weights.xml"; // 25var, ptj50/50
  //bdtWWWeights="MitAnalysisRunII/BDT/ssww_WWDec_V1/bdt_BDTG_v1.weights.xml"; // 25var, ptj30/50
  //bdtWWWeights="MitAnalysisRunII/BDT/ssww_WWDec_V1/bdt_BDTG_v2.weights.xml"; // 25var, ptj50/50
  //bdtWWWeights="MitAnalysisRunII/BDT/ssww_WWDec_V1/bdt_BDTG_v3.weights.xml"; // 26var, ptj50/50
  bdtWWWeights="MitAnalysisRunII/BDT/ssww_WWDec_V1/bdt_BDTG_v6.weights.xml"; // 25var, ptj30/50, other bkg. in training
  //bdtWWWeights="MitAnalysisRunII/BDT/ssww_WWDec_V1/bdt_BDTG_v7.weights.xml"; // 25var, ptj30/50, multiclass

  TMVA::Reader *theReaderWW = new TMVA::Reader("Silent");
  //theReaderWW->AddVariable("mvamjj"	,&mvaWWInputs[ 0]);  
  theReaderWW->AddVariable("mvadetajj"  ,&mvaWWInputs[ 0]);
  theReaderWW->AddVariable("mvadphijj"  ,&mvaWWInputs[ 1]);
  theReaderWW->AddVariable("mvajetpt1"  ,&mvaWWInputs[ 2]);
  theReaderWW->AddVariable("mvajetpt2"  ,&mvaWWInputs[ 3]);
  theReaderWW->AddVariable("mvajeteta1" ,&mvaWWInputs[ 4]);
  theReaderWW->AddVariable("mvajeteta2" ,&mvaWWInputs[ 5]);
  theReaderWW->AddVariable("mvaWpt"	,&mvaWWInputs[ 6]);
  theReaderWW->AddVariable("mvaZpt"	,&mvaWWInputs[ 7]);
  theReaderWW->AddVariable("mvaVVmt"	,&mvaWWInputs[ 8]);
  theReaderWW->AddVariable("mvazstar"	,&mvaWWInputs[ 9]);
  theReaderWW->AddVariable("mvazep1"	,&mvaWWInputs[10]);
  theReaderWW->AddVariable("mvazep2"	,&mvaWWInputs[11]);
  theReaderWW->AddVariable("mvamaxzep"  ,&mvaWWInputs[12]);
  theReaderWW->AddVariable("mvaj1Zdr"	,&mvaWWInputs[13]);
  theReaderWW->AddVariable("mvaj2Zdr"	,&mvaWWInputs[14]);
  theReaderWW->AddVariable("mvapttot"	,&mvaWWInputs[15]);
  theReaderWW->AddVariable("mvasumpttot",&mvaWWInputs[16]);
  theReaderWW->AddVariable("mvaleppt1"  ,&mvaWWInputs[17]);
  theReaderWW->AddVariable("mvaleppt2"  ,&mvaWWInputs[18]);
  theReaderWW->AddVariable("mvalepeta1" ,&mvaWWInputs[19]);
  theReaderWW->AddVariable("mvalepeta2" ,&mvaWWInputs[20]);
  theReaderWW->AddVariable("mvadphill"  ,&mvaWWInputs[21]);
  theReaderWW->AddVariable("mvadrll"	,&mvaWWInputs[22]);
  theReaderWW->AddVariable("mvamll"	,&mvaWWInputs[23]);
  theReaderWW->AddVariable("(mvaleppt1*mvaleppt2)/(mvajetpt1*mvajetpt2)"  ,&mvaWWInputs[24]);
  theReaderWW->BookMVA("BDT", bdtWWWeights.Data());

  float mvaWZInputs[13];
  TString bdtWZWeights="";
  bdtWZWeights="MitAnalysisRunII/BDT/ssww_WZNov_V0/bdt_BDTG_13var_detajj2p5.weights.xml";

  TMVA::Reader *theReaderWZ = new TMVA::Reader("Silent");
  theReaderWZ->AddVariable("mvamjj"    ,&mvaWZInputs[0]);
  theReaderWZ->AddVariable("mvadetajj" ,&mvaWZInputs[1]);
  theReaderWZ->AddVariable("mvadphijj" ,&mvaWZInputs[2]);
  theReaderWZ->AddVariable("mvajetpt1" ,&mvaWZInputs[3]);
  theReaderWZ->AddVariable("mvajetpt2" ,&mvaWZInputs[4]);
  theReaderWZ->AddVariable("mvajeteta1",&mvaWZInputs[5]);
  theReaderWZ->AddVariable("mvaWlZdeta",&mvaWZInputs[6]);
  theReaderWZ->AddVariable("mvazstar"  ,&mvaWZInputs[7]);
  theReaderWZ->AddVariable("mvazep1"   ,&mvaWZInputs[8]);
  theReaderWZ->AddVariable("mvazep2"   ,&mvaWZInputs[9]);
  theReaderWZ->AddVariable("mvazep3"   ,&mvaWZInputs[10]);
  theReaderWZ->AddVariable("mvaj1Zdr"  ,&mvaWZInputs[11]);
  theReaderWZ->AddVariable("mvapttot/mvasumpttot" ,&mvaWZInputs[12]);
  theReaderWZ->BookMVA("BDT", bdtWZWeights.Data());
  // End MVA-weigths initialization

  //*******************************************************
  // Chain Loop
  //*******************************************************
  for(UInt_t ifile=0; ifile<infileName_.size(); ifile++) {
    printf("sampleNames(%d): %s\n",ifile,infileName_[ifile].Data());
    TFile *the_input_file = TFile::Open(infileName_[ifile].Data());
    TTree *the_input_tree = (TTree*)the_input_file->FindObjectAny("events");

    if(debug != 0 && infileCat_[ifile] != 0) return;

    // Begin MVA-ntuple initialization
    char outMVAfile[200];
    sprintf(outMVAfile,"mva_%d_%d_%d%s.root",ifile,infileCat_[ifile],year,fidAnaName.Data()); 
    TFile *mvaoutf = new TFile(outMVAfile,"recreate");
    TTree *mvatree = new TTree("mvatree","mvatree");

    mvatree->Branch("category",   &category,    "category/I");
    mvatree->Branch("eventNum",   &eventNum,    "eventNum/I");
    mvatree->Branch("weight",     &weight,      "weight/D");
    mvatree->Branch("mvamjj",     &mvamjj,      "mvamjj/F");
    mvatree->Branch("mvadetajj",  &mvadetajj,   "mvadetajj/F"); 
    mvatree->Branch("mvadphijj",  &mvadphijj,   "mvadphijj/F");  
    mvatree->Branch("mvajetpt1",  &mvajetpt1,   "mvajetpt1/F"); 
    mvatree->Branch("mvajetpt2",  &mvajetpt2,   "mvajetpt2/F"); 
    mvatree->Branch("mvajeteta1", &mvajeteta1,  "mvajeteta1/F");
    mvatree->Branch("mvajeteta2", &mvajeteta2,  "mvajeteta2/F");
    mvatree->Branch("mvanjets",   &mvanjets,    "mvanjets/F");  
    mvatree->Branch("mvaWpt",     &mvaWpt,      "mvaWpt/F");    
    mvatree->Branch("mvaZpt",     &mvaZpt,      "mvaZpt/F");    
    mvatree->Branch("mvaVVmt",    &mvaVVmt,     "mvaVVmt/F");   
    mvatree->Branch("mvaWlZdeta", &mvaWlZdeta,  "mvaWlZdeta/F");
    mvatree->Branch("mvazstar",   &mvazstar,    "mvazstar/F");  
    mvatree->Branch("mvazep1",    &mvazep1,     "mvazep1/F");   
    mvatree->Branch("mvazep2",    &mvazep2,     "mvazep2/F");   
    mvatree->Branch("mvazep3",    &mvazep3,     "mvazep3/F");   
    mvatree->Branch("mvamaxzep",  &mvamaxzep,   "mvamaxzep/F"); 
    mvatree->Branch("mvaj1Zdr",   &mvaj1Zdr,    "mvaj1Zdr/F");  
    mvatree->Branch("mvaj2Zdr",   &mvaj2Zdr,    "mvaj2Zdr/F");  
    mvatree->Branch("mvapttot",   &mvapttot,    "mvapttot/F");  
    mvatree->Branch("mvasumpttot",&mvasumpttot, "mvasumpttot");
    mvatree->Branch("mvaleppt1",  &mvaleppt1,   "mvaleppt1/F"); 
    mvatree->Branch("mvaleppt2",  &mvaleppt2,   "mvaleppt2/F"); 
    mvatree->Branch("mvalepeta1", &mvalepeta1,  "mvalepeta1/F");
    mvatree->Branch("mvalepeta2", &mvalepeta2,  "mvalepeta2/F");
    mvatree->Branch("mvadphill",  &mvadphill,   "mvadphill/F");
    mvatree->Branch("mvadrll",    &mvadrll,     "mvadrll/F");
    mvatree->Branch("mvamll",     &mvamll,      "mvamll/F");    
    // Begin MVA-ntuple initialization

    pandaFlat thePandaFlat(the_input_tree,infileName_[ifile].Contains("dim8"));
    double theMCPrescale = 1.0; if(infileCat_[ifile] != kPlotData) theMCPrescale = mcPrescale;
    Long64_t nentries = thePandaFlat.fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = thePandaFlat.LoadTree(jentry);
      if (ientry < 0) break;
      nb = thePandaFlat.fChain->GetEntry(jentry);   nbytes += nb;
      if (jentry%1000000 == 0) printf("--- reading event %8lld (%8lld) of %8lld\n",jentry,ientry,nentries);
      if (infileCat_[ifile] != kPlotData && jentry%(int)theMCPrescale != 0) continue;

      if(debug == 2) printf("STEP1 %llu\n",thePandaFlat.eventNumber);

      bool passTrigger = (thePandaFlat.trigger & (1<<kEMuTrig)) != 0       || (thePandaFlat.trigger & (1<<kDoubleMuTrig)) != 0  ||
                         (thePandaFlat.trigger & (1<<kSingleMuTrig)) != 0  || (thePandaFlat.trigger & (1<<kDoubleEleTrig)) != 0 ||
                         (thePandaFlat.trigger & (1<<kSingleEleTrig)) != 0;
      if(passTrigger == false) continue;
      if(thePandaFlat.metFilter == 0) continue;
      if(debug == 2) printf("STEP2 %llu\n",thePandaFlat.eventNumber);

      bool passJetPtEtaCut = false;
      if(thePandaFlat.nJot >= 2){
        if(fidAna == 5) {
          passJetPtEtaCut = thePandaFlat.jotPt[0] > 50 && thePandaFlat.jotPt[1] > 50;
	}
	else {
          passJetPtEtaCut = thePandaFlat.jotPt[0] > 50 && thePandaFlat.jotPt[1] > 50;
	}
	if(TMath::Abs(thePandaFlat.jotEta[0]) > 2.4) passJetPtEtaCut = passJetPtEtaCut && thePandaFlat.jotPt[0] > 50;
	if(TMath::Abs(thePandaFlat.jotEta[1]) > 2.4) passJetPtEtaCut = passJetPtEtaCut && thePandaFlat.jotPt[1] > 50;
      }
      if(passJetPtEtaCut == false) continue;

      if(thePandaFlat.nLooseLep < 2 || thePandaFlat.nLooseLep > 4) continue;
      if(debug == 2) printf("STEP3 %llu\n",thePandaFlat.eventNumber);

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
      if(thePandaFlat.nLooseLep >= 3) isNotMCFake = isNotMCFake && thePandaFlat.looseGenLep3PdgId != 0;
      if(thePandaFlat.nLooseLep >= 4) isNotMCFake = isNotMCFake && thePandaFlat.looseGenLep4PdgId != 0;
      if(theCategory != kPlotData && theCategory != kPlotVG && isNotMCFake == false && usePureMC == false) continue;

      vector<TLorentzVector> vLoose;
      vector<int> idLep;
      bool passLooseLepId = true;
      int qTot = 0;
      unsigned int countLeptonTight = 0;
      for(int i=0; i<thePandaFlat.nLooseLep; i++) {
        idLep.push_back(0);
        if(abs(looseLepPdgId[i])==13) {
	  if	 (year == 2016 && (looseLepSelBit[i] & kTight) == kTight && (looseLepSelBit[i] & kDxyz) == kDxyz) idLep[i] = 1;
	  else if(year == 2017 && (looseLepSelBit[i] & kMvaTight) == kMvaTight && (looseLepSelBit[i] & kMiniIsoTight) == kMiniIsoTight) idLep[i] = 1;
	  else if(year == 2018 && (looseLepSelBit[i] & kTight) == kTight && (looseLepSelBit[i] & kDxyz) == kDxyz && (looseLepSelBit[i] & kMiniIsoTight) == kMiniIsoTight) idLep[i] = 1;
	}
	else {
          if     (year == 2016 && (looseLepSelBit[i] & kEleMvaWP80) == kEleMvaWP80 && looseLepTripleCharge[i] == 1) idLep[i] = 1;
	  //else if(year == 2017 && (looseLepSelBit[i] & kTight) == kTight && (looseLepSelBit[i] & kDxyz) == kDxyz && looseLepMissingHits[i] == 0 && looseLepTripleCharge[i] == 1) idLep[i] = 1;
          else if(year == 2017 && (looseLepSelBit[i] & kEleMvaWP80) == kEleMvaWP80 && looseLepTripleCharge[i] == 1) idLep[i] = 1;
	  else if(year == 2018 && (looseLepSelBit[i] & kEleMvaWP80) == kEleMvaWP80 && looseLepTripleCharge[i] == 1) idLep[i] = 1;
	}
	countLeptonTight = countLeptonTight + (idLep[i] > 0);
        double thePDGMass = mass_mu;
        if(abs(looseLepPdgId[i])==11) thePDGMass = mass_el;
	TLorentzVector vLepTemp; vLepTemp.SetPtEtaPhiM(looseLepPt[i],looseLepEta[i],looseLepPhi[i],thePDGMass);
        vLoose.push_back(vLepTemp);

	qTot = qTot + abs(looseLepPdgId[i])/looseLepPdgId[i];

        passLooseLepId = passLooseLepId && ((looseLepSelBit[i] & kFake) == kFake);
      }
      qTot = -qTot;
      if(debug == 2) printf("STEP4 %llu %d %d %d %zu\n",thePandaFlat.eventNumber,passLooseLepId,qTot,countLeptonTight,idLep.size());
      if(passLooseLepId == false) continue;
      if(usePureMC == true && countLeptonTight != idLep.size()) continue;
      if(infileName_[ifile].Contains("dim8") && countLeptonTight != idLep.size()) continue;
      if(debug == 2) printf("STEP5 %llu\n",thePandaFlat.eventNumber);

      int lepType = -1; double muSFUnc = 1.0; double elSFUnc = 1.0; double theLepSFUnc = 1.012;
      if     (thePandaFlat.nLooseLep == 2){
        if     (abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13) {lepType = 0; muSFUnc = theLepSFUnc*theLepSFUnc;}
        else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11) {lepType = 1; elSFUnc = theLepSFUnc*theLepSFUnc;}
        else  {lepType = 2; muSFUnc = theLepSFUnc; elSFUnc = theLepSFUnc;}
      }
      else if(thePandaFlat.nLooseLep == 3){
        if     (abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13 && abs(looseLepPdgId[2])==13) {lepType = 0; muSFUnc = theLepSFUnc*theLepSFUnc*theLepSFUnc;}
        else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11 && abs(looseLepPdgId[2])==11) {lepType = 3; elSFUnc = theLepSFUnc*theLepSFUnc*theLepSFUnc;}
        else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11) {lepType = 1; muSFUnc = theLepSFUnc; elSFUnc = theLepSFUnc*theLepSFUnc;}
        else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[2])==11) {lepType = 1; muSFUnc = theLepSFUnc; elSFUnc = theLepSFUnc*theLepSFUnc;}
        else if(abs(looseLepPdgId[1])==11 && abs(looseLepPdgId[2])==11) {lepType = 1; muSFUnc = theLepSFUnc; elSFUnc = theLepSFUnc*theLepSFUnc;}
        else if(abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13) {lepType = 2; muSFUnc = theLepSFUnc*theLepSFUnc; elSFUnc = theLepSFUnc;}
        else if(abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[2])==13) {lepType = 2; muSFUnc = theLepSFUnc*theLepSFUnc; elSFUnc = theLepSFUnc;}
        else if(abs(looseLepPdgId[1])==13 && abs(looseLepPdgId[2])==13) {lepType = 2; muSFUnc = theLepSFUnc*theLepSFUnc; elSFUnc = theLepSFUnc;}
        else {printf("Impossible lepton combination: %d %d %d\n",looseLepPdgId[0],looseLepPdgId[1],looseLepPdgId[2]); continue;}
      }
      else if(thePandaFlat.nLooseLep == 4){
        int nmu = (abs(looseLepPdgId[0])==13) + (abs(looseLepPdgId[1])==13) + (abs(looseLepPdgId[2])==13) + (abs(looseLepPdgId[3])==13);
        int nel = (abs(looseLepPdgId[0])==11) + (abs(looseLepPdgId[1])==11) + (abs(looseLepPdgId[2])==11) + (abs(looseLepPdgId[3])==11);
        if     (nmu == 4 && nel == 0) {lepType = 0; muSFUnc = theLepSFUnc*theLepSFUnc*theLepSFUnc*theLepSFUnc;}
        else if(nmu == 0 && nel == 4) {lepType = 1; elSFUnc = theLepSFUnc*theLepSFUnc*theLepSFUnc*theLepSFUnc;}
        else if(nmu == 2 && nel == 2) {lepType = 2; muSFUnc = theLepSFUnc*theLepSFUnc; elSFUnc = theLepSFUnc*theLepSFUnc;}
        else if(nmu == 3 && nel == 1) {lepType = 3; muSFUnc = theLepSFUnc*theLepSFUnc*theLepSFUnc; elSFUnc = theLepSFUnc;}
        else if(nmu == 1 && nel == 3) {lepType = 3; muSFUnc = theLepSFUnc; elSFUnc = theLepSFUnc*theLepSFUnc*theLepSFUnc;}
        else {printf("Impossible lepton combination: %d %d %d %d\n",looseLepPdgId[0],looseLepPdgId[1],looseLepPdgId[2],looseLepPdgId[3]); continue;}
      }

      TLorentzVector vMet,vTrkMet,vMetUp,vMetDown;
      vTrkMet.SetPtEtaPhiM(thePandaFlat.trkmet,0.0,thePandaFlat.trkmetphi,0.0);
      vMet    .SetPtEtaPhiM(thePandaFlat.pfmet,0.0,thePandaFlat.pfmetphi,0.0);
      vMetUp  .SetPtEtaPhiM(thePandaFlat.pfmet_JESTotalUp  ,0.0,thePandaFlat.pfmetphi_JESTotalUp  ,0.0);
      vMetDown.SetPtEtaPhiM(thePandaFlat.pfmet_JESTotalDown,0.0,thePandaFlat.pfmetphi_JESTotalDown,0.0);
      //vMet    .SetPx(vMet    .Px()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 0));
      //vMet    .SetPy(vMet    .Py()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 1));
      //vMetUp  .SetPx(vMetUp  .Px()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 0));
      //vMetUp  .SetPy(vMetUp  .Py()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 1));
      //vMetDown.SetPx(vMetDown.Px()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 0));
      //vMetDown.SetPy(vMetDown.Py()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 1));

      double mllZ = 10000; double mllmin = 10000;
      TLorentzVector vZ1l1,vZ1l2,vZ2l1,vZ2l2,vWln,alllep;
      int whichWln = -1;
      if     (vLoose.size() == 2){
        vZ1l1  = vLoose[0];
        vZ1l2  = vLoose[1];
	mllZ   = (vLoose[0]+vLoose[1]).M();
	mllmin = (vLoose[0]+vLoose[1]).M();
	whichWln = 9; // random number greater or equal than 0
	alllep = vLoose[0]+vLoose[1];
      }
      else if(vLoose.size() == 3){
        if((vLoose[0]+vLoose[1]).M() < mllmin) mllmin = (vLoose[0]+vLoose[1]).M();
        if((vLoose[0]+vLoose[2]).M() < mllmin) mllmin = (vLoose[0]+vLoose[2]).M();
        if((vLoose[1]+vLoose[2]).M() < mllmin) mllmin = (vLoose[1]+vLoose[2]).M();
	alllep = vLoose[0]+vLoose[1]+vLoose[2];
	if(abs(looseLepPdgId[0]) == abs(looseLepPdgId[1]) && looseLepPdgId[0] != looseLepPdgId[1]) {
          if(fabs((vLoose[0]+vLoose[1]).M()-91.1876) < fabs(mllZ-91.1876)) {
	    mllZ  = (vLoose[0]+vLoose[1]).M();
	    vZ1l1 = vLoose[0];
	    vZ1l2 = vLoose[1];
	    vWln  = vLoose[2];
	    whichWln = 2;
	  }
	}
	if(abs(looseLepPdgId[0]) == abs(looseLepPdgId[2]) && looseLepPdgId[0] != looseLepPdgId[2]) {
          if(fabs((vLoose[0]+vLoose[2]).M()-91.1876) < fabs(mllZ-91.1876)) {
            mllZ  = (vLoose[0]+vLoose[2]).M();
	    vZ1l1 = vLoose[0];
	    vZ1l2 = vLoose[2];
	    vWln  = vLoose[1];
	    whichWln = 1;
	  }
	}
	if(abs(looseLepPdgId[1]) == abs(looseLepPdgId[2]) && looseLepPdgId[1] != looseLepPdgId[2]) {
          if(fabs((vLoose[1]+vLoose[2]).M()-91.1876) < fabs(mllZ-91.1876)) {
            mllZ  = (vLoose[1]+vLoose[2]).M();
	    vZ1l1 = vLoose[1];
	    vZ1l2 = vLoose[2];
	    vWln  = vLoose[0];
	    whichWln = 0;
	  }
	}
      }
      else if(vLoose.size() == 4){
	alllep = vLoose[0]+vLoose[1]+vLoose[2]+vLoose[4];
	if(abs(looseLepPdgId[0]) == abs(looseLepPdgId[1]) && looseLepPdgId[0] != looseLepPdgId[1]) {
          if((vLoose[0]+vLoose[1]).M() < mllmin) mllmin = (vLoose[0]+vLoose[1]).M();
          if(fabs((vLoose[0]+vLoose[1]).M()-91.1876) < fabs(mllZ-91.1876)) {
	    mllZ = (vLoose[0]+vLoose[1]).M();
	    vZ1l1 = vLoose[0];
	    vZ1l2 = vLoose[1];
	    vZ2l1 = vLoose[2];
	    vZ2l2 = vLoose[3];
	    whichWln = 0;
	  }
	}
	if(abs(looseLepPdgId[0]) == abs(looseLepPdgId[2]) && looseLepPdgId[0] != looseLepPdgId[2]) {
          if((vLoose[0]+vLoose[2]).M() < mllmin) mllmin = (vLoose[0]+vLoose[2]).M();
          if(fabs((vLoose[0]+vLoose[2]).M()-91.1876) < fabs(mllZ-91.1876)) {
            mllZ = (vLoose[0]+vLoose[2]).M();
	    vZ1l1 = vLoose[0];
	    vZ1l2 = vLoose[2];
	    vZ2l1 = vLoose[1];
	    vZ2l2 = vLoose[3];
	    whichWln = 1;
	  }
	}
	if(abs(looseLepPdgId[0]) == abs(looseLepPdgId[3]) && looseLepPdgId[0] != looseLepPdgId[3]) {
          if((vLoose[0]+vLoose[3]).M() < mllmin) mllmin = (vLoose[0]+vLoose[3]).M();
          if(fabs((vLoose[0]+vLoose[3]).M()-91.1876) < fabs(mllZ-91.1876)) {
            mllZ = (vLoose[0]+vLoose[3]).M();
	    vZ1l1 = vLoose[0];
	    vZ1l2 = vLoose[3];
	    vZ2l1 = vLoose[1];
	    vZ2l2 = vLoose[2];
	    whichWln = 2;
	  }
	}
	if(abs(looseLepPdgId[1]) == abs(looseLepPdgId[2]) && looseLepPdgId[1] != looseLepPdgId[2]) {
          if((vLoose[1]+vLoose[2]).M() < mllmin) mllmin = (vLoose[1]+vLoose[2]).M();
          if(fabs((vLoose[1]+vLoose[2]).M()-91.1876) < fabs(mllZ-91.1876)) {
            mllZ = (vLoose[1]+vLoose[2]).M();
	    vZ1l1 = vLoose[1];
	    vZ1l2 = vLoose[2];
	    vZ2l1 = vLoose[0];
	    vZ2l2 = vLoose[3];
	    whichWln = 3;
	  }
	}
	if(abs(looseLepPdgId[1]) == abs(looseLepPdgId[3]) && looseLepPdgId[1] != looseLepPdgId[3]) {
          if((vLoose[1]+vLoose[3]).M() < mllmin) mllmin = (vLoose[1]+vLoose[3]).M();
          if(fabs((vLoose[1]+vLoose[3]).M()-91.1876) < fabs(mllZ-91.1876)) {
            mllZ = (vLoose[1]+vLoose[3]).M();
	    vZ1l1 = vLoose[1];
	    vZ1l2 = vLoose[3];
	    vZ2l1 = vLoose[0];
	    vZ2l2 = vLoose[2];
	    whichWln = 4;
	  }
	}
	if(abs(looseLepPdgId[2]) == abs(looseLepPdgId[3]) && looseLepPdgId[2] != looseLepPdgId[3]) {
          if((vLoose[2]+vLoose[3]).M() < mllmin) mllmin = (vLoose[2]+vLoose[3]).M();
          if(fabs((vLoose[2]+vLoose[3]).M()-91.1876) < fabs(mllZ-91.1876)) {
            mllZ = (vLoose[2]+vLoose[3]).M();
	    vZ1l1 = vLoose[2];
	    vZ1l2 = vLoose[3];
	    vZ2l1 = vLoose[0];
	    vZ2l2 = vLoose[1];
	    whichWln = 5;
	  }
	}
      }

      if(whichWln == -1) continue;

      double theEtaJERCorr[2] = {1,1};
      if(thePandaFlat.nJot >= 2){
        int theBinEtaJERCorr[2] = {histoEtaJERCorr->GetXaxis()->FindBin(TMath::Abs(thePandaFlat.jotEta[0]))-1,
                                   histoEtaJERCorr->GetXaxis()->FindBin(TMath::Abs(thePandaFlat.jotEta[1]))-1};

        if(theBinEtaJERCorr[0] < 0 || theBinEtaJERCorr[0] > nBinEtaJERCorr+1 ||
	   theBinEtaJERCorr[1] < 0 || theBinEtaJERCorr[1] > nBinEtaJERCorr+1) printf("PROBLEM with theBinEtaJERCorr\n");

        theEtaJERCorr[0] = 1.0 + gRandom->Gaus(0.0,0.10)*JERSF[theBinEtaJERCorr[0]];
        theEtaJERCorr[1] = 1.0 + gRandom->Gaus(0.0,0.10)*JERSF[theBinEtaJERCorr[1]];
      }

      TLorentzVector vJot1;        vJot1.SetPtEtaPhiM       (thePandaFlat.jotPt[0]                 ,thePandaFlat.jotEta[0],thePandaFlat.jotPhi[0],0.0);
      TLorentzVector vJot2;        vJot2.SetPtEtaPhiM       (thePandaFlat.jotPt[1]                 ,thePandaFlat.jotEta[1],thePandaFlat.jotPhi[1],0.0);
      TLorentzVector vJot1JESUp;   vJot1JESUp.SetPtEtaPhiM  (thePandaFlat.jotPt_JESTotalUp[0]      ,thePandaFlat.jotEta[0],thePandaFlat.jotPhi[0],0.0);
      TLorentzVector vJot2JESUp;   vJot2JESUp.SetPtEtaPhiM  (thePandaFlat.jotPt_JESTotalUp[1]      ,thePandaFlat.jotEta[1],thePandaFlat.jotPhi[1],0.0);
      TLorentzVector vJot1JERUp;   vJot1JERUp.SetPtEtaPhiM  (thePandaFlat.jotPt[0]*theEtaJERCorr[0],thePandaFlat.jotEta[0],thePandaFlat.jotPhi[0],0.0);
      TLorentzVector vJot2JERUp;   vJot2JERUp.SetPtEtaPhiM  (thePandaFlat.jotPt[1]*theEtaJERCorr[1],thePandaFlat.jotEta[1],thePandaFlat.jotPhi[1],0.0);
      TLorentzVector vJot1JESDown; vJot1JESDown.SetPtEtaPhiM(thePandaFlat.jotPt_JESTotalDown[0]    ,thePandaFlat.jotEta[0],thePandaFlat.jotPhi[0],0.0);
      TLorentzVector vJot2JESDown; vJot2JESDown.SetPtEtaPhiM(thePandaFlat.jotPt_JESTotalDown[1]    ,thePandaFlat.jotEta[1],thePandaFlat.jotPhi[1],0.0);
      TLorentzVector vJot1JERDown; vJot1JERDown.SetPtEtaPhiM(thePandaFlat.jotPt[0]/theEtaJERCorr[0],thePandaFlat.jotEta[0],thePandaFlat.jotPhi[0],0.0);
      TLorentzVector vJot2JERDown; vJot2JERDown.SetPtEtaPhiM(thePandaFlat.jotPt[1]/theEtaJERCorr[1],thePandaFlat.jotEta[1],thePandaFlat.jotPhi[1],0.0);

      double massJJ         = thePandaFlat.jot12Mass;		   //(vJot1+vJot2).M();
      double massJJJESUp    = thePandaFlat.jot12Mass_JESTotalUp;   //(vJot1JESUp+vJot2JESUp).M();
      double massJJJESDown  = thePandaFlat.jot12Mass_JESTotalDown; //(vJot1JESDown+vJot2JESDown).M();
      double massJJJERUp    = thePandaFlat.jot12Mass*theEtaJERCorr[0]*theEtaJERCorr[1];
      double massJJJERDown  = thePandaFlat.jot12Mass/theEtaJERCorr[0]/theEtaJERCorr[1];
      double deltaEtaJJ     = thePandaFlat.jot12DEta;		   //TMath::Abs(vJot1.Eta()       -vJot2.Eta());
      double deltaEtaJJUp   = thePandaFlat.jot12DEta_JESTotalUp;   //TMath::Abs(vJot1JESUp.Eta()  -vJot2JESUp.Eta());
      double deltaEtaJJDown = thePandaFlat.jot12DEta_JESTotalDown; //TMath::Abs(vJot1JESDown.Eta()-vJot2JESDown.Eta());
      double deltaPhiJJ     = thePandaFlat.jot12DPhi;	           //TMath::Abs(vJot1.Phi()       -vJot2.Phi());
      double deltaPhiJJUp   = thePandaFlat.jot12DPhi_JESTotalUp;   //TMath::Abs(vJot1JESUp.Phi()  -vJot2JESUp.Phi());
      double deltaPhiJJDown = thePandaFlat.jot12DPhi_JESTotalDown; //TMath::Abs(vJot1JESDown.Phi()-vJot2JESDown.Phi());

      bool passJetPtEtaSyst[nSystTypes] = {false, false, false, false};
      if(thePandaFlat.nJot >= 2){
        if(fidAna == 5) {
          passJetPtEtaSyst[0] = vJot1JESUp.Pt()   > 50 && vJot2JESUp.Pt()   > 50;
          passJetPtEtaSyst[1] = vJot1JESDown.Pt() > 50 && vJot2JESDown.Pt() > 50;
          passJetPtEtaSyst[2] = vJot1JERUp.Pt()   > 50 && vJot2JERUp.Pt()   > 50;
          passJetPtEtaSyst[3] = vJot1JERDown.Pt() > 50 && vJot2JERDown.Pt() > 50;
	}
	else {
          passJetPtEtaSyst[0] = vJot1JESUp.Pt()   > 50 && vJot2JESUp.Pt()   > 50;
          passJetPtEtaSyst[1] = vJot1JESDown.Pt() > 50 && vJot2JESDown.Pt() > 50;
          passJetPtEtaSyst[2] = vJot1JERUp.Pt()   > 50 && vJot2JERUp.Pt()   > 50;
          passJetPtEtaSyst[3] = vJot1JERDown.Pt() > 50 && vJot2JERDown.Pt() > 50;
	}
	if(TMath::Abs(vJot1.Eta()) > 2.4) {
          passJetPtEtaSyst[0] = passJetPtEtaSyst[0] && vJot1JESUp.Pt()   > 50;
          passJetPtEtaSyst[1] = passJetPtEtaSyst[1] && vJot1JESDown.Pt() > 50;
          passJetPtEtaSyst[2] = passJetPtEtaSyst[2] && vJot1JERUp.Pt()   > 50;
          passJetPtEtaSyst[3] = passJetPtEtaSyst[3] && vJot1JERDown.Pt() > 50;
	}
	if(TMath::Abs(vJot2.Eta()) > 2.4) {
          passJetPtEtaSyst[0] = passJetPtEtaSyst[0] && vJot2JESUp.Pt()   > 50;
          passJetPtEtaSyst[1] = passJetPtEtaSyst[1] && vJot2JESDown.Pt() > 50;
          passJetPtEtaSyst[2] = passJetPtEtaSyst[2] && vJot2JERUp.Pt()   > 50;
          passJetPtEtaSyst[3] = passJetPtEtaSyst[3] && vJot2JERDown.Pt() > 50;
	}
      }

      bool passMJJ        = thePandaFlat.nJot              >= 2 && massJJ        > 500 && passJetPtEtaCut;
      bool passMJJJESUp   = thePandaFlat.nJot_JESTotalUp   >= 2 && massJJJESUp   > 500 && passJetPtEtaSyst[0];
      bool passMJJJESDown = thePandaFlat.nJot_JESTotalDown >= 2 && massJJJESDown > 500 && passJetPtEtaSyst[1];
      bool passMJJJERUp   = thePandaFlat.nJot              >= 2 && massJJJERUp   > 500 && passJetPtEtaSyst[2];
      bool passMJJJERDown = thePandaFlat.nJot              >= 2 && massJJJERDown > 500 && passJetPtEtaSyst[3];
      bool passDEtaJJ     = thePandaFlat.nJot		   >= 2 && deltaEtaJJ	  > 2.5;
      bool passDEtaJJUp   = thePandaFlat.nJot_JESTotalUp   >= 2 && deltaEtaJJUp   > 2.5;
      bool passDEtaJJDown = thePandaFlat.nJot_JESTotalDown >= 2 && deltaEtaJJDown > 2.5;
      bool passCRMJJ         = thePandaFlat.nJot              >= 2 && massJJ        > 200 && massJJ	   <= 500 && passJetPtEtaCut;
      bool passCRMJJJESUp    = thePandaFlat.nJot_JESTotalUp   >= 2 && massJJJESUp   > 200 && massJJJESUp   <= 500 && passJetPtEtaSyst[0];
      bool passCRMJJJESDown  = thePandaFlat.nJot_JESTotalDown >= 2 && massJJJESDown > 200 && massJJJESDown <= 500 && passJetPtEtaSyst[1];
      bool passCRMJJJERUp    = thePandaFlat.nJot              >= 2 && massJJJERUp   > 200 && massJJJERUp   <= 500 && passJetPtEtaSyst[2];
      bool passCRMJJJERDown  = thePandaFlat.nJot              >= 2 && massJJJERDown > 200 && massJJJERDown <= 500 && passJetPtEtaSyst[3];

      TLorentzVector totSystem = vMet,totSystemJESUp = vMetUp,totSystemJESDown = vMetDown,totSystemJERUp = vMet, totSystemJERDown = vMet;
      double sumPtTot = vMet.Pt(), sumPtTotJESUp = vMetUp.Pt(), sumPtTotJESDown = vMetDown.Pt(), sumPtTotJERUp = vMet.Pt(), sumPtTotJERDown = vMet.Pt();
      double maxLeptonZep = 0; double maxLeptonZepUp = 0; double maxLeptonZepDown = 0;
      double vvZepSS[4] = {0.,0.,0.,0.};double vvZepSSUp[4] = {0.,0.,0.,0.};double vvZepSSDown[4] = {0.,0.,0.,0};
      for(unsigned int i=0; i<vLoose.size(); i++) {
        totSystem        = totSystem        + vLoose[i]; sumPtTot        = sumPtTot        + vLoose[i].Pt();
        totSystemJESUp   = totSystemJESUp   + vLoose[i]; sumPtTotJESUp   = sumPtTotJESUp   + vLoose[i].Pt();
        totSystemJESDown = totSystemJESDown + vLoose[i]; sumPtTotJESDown = sumPtTotJESDown + vLoose[i].Pt();
        totSystemJERUp   = totSystemJERUp   + vLoose[i]; sumPtTotJERUp   = sumPtTotJERUp   + vLoose[i].Pt();
        totSystemJERDown = totSystemJERDown + vLoose[i]; sumPtTotJERDown = sumPtTotJERDown + vLoose[i].Pt();
	vvZepSS[i]     = TMath::Abs(vLoose[i].Eta()-(vJot1.Eta()+vJot2.Eta())/2.)/deltaEtaJJ;
	vvZepSSUp[i]   = TMath::Abs(vLoose[i].Eta()-(vJot1JESUp.Eta()+vJot2JESUp.Eta())/2.)/deltaEtaJJUp;
	vvZepSSDown[i] = TMath::Abs(vLoose[i].Eta()-(vJot1JESDown.Eta()+vJot2JESDown.Eta())/2.)/deltaEtaJJDown;
        if(TMath::Abs(vLoose[i].Eta()-(vJot1.Eta()+vJot2.Eta())/2.)/deltaEtaJJ > maxLeptonZep)
          maxLeptonZep     = TMath::Abs(vLoose[i].Eta()-(vJot1.Eta()+vJot2.Eta())/2.)/deltaEtaJJ;
        if(TMath::Abs(vLoose[i].Eta()-(vJot1JESUp.Eta()+vJot2JESUp.Eta())/2.)/deltaEtaJJUp > maxLeptonZepUp)
	  maxLeptonZepUp   = TMath::Abs(vLoose[i].Eta()-(vJot1JESUp.Eta()+vJot2JESUp.Eta())/2.)/deltaEtaJJUp;
        if(TMath::Abs(vLoose[i].Eta()-(vJot1JESDown.Eta()+vJot2JESDown.Eta())/2.)/deltaEtaJJDown > maxLeptonZepDown)
	  maxLeptonZepDown = TMath::Abs(vLoose[i].Eta()-(vJot1JESDown.Eta()+vJot2JESDown.Eta())/2.)/deltaEtaJJDown;
      }
      totSystem          = totSystem        + vJot1        + vJot2;        sumPtTot        = sumPtTot        + vJot1.Pt()        + vJot2.Pt();
      totSystemJESUp     = totSystemJESUp   + vJot1JESUp   + vJot2JESUp;   sumPtTotJESUp   = sumPtTotJESUp   + vJot1JESUp.Pt()   + vJot2JESUp.Pt();
      totSystemJESDown   = totSystemJESDown + vJot1JESDown + vJot2JESDown; sumPtTotJESDown = sumPtTotJESDown + vJot1JESDown.Pt() + vJot2JESDown.Pt();
      totSystemJERUp     = totSystemJERUp   + vJot1JERUp   + vJot2JERUp;   sumPtTotJERUp   = sumPtTotJERUp   + vJot1JERUp.Pt()   + vJot2JERUp.Pt();
      totSystemJERDown   = totSystemJERDown + vJot1JERDown + vJot2JERDown; sumPtTotJERDown = sumPtTotJERDown + vJot1JERDown.Pt() + vJot2JERDown.Pt();

      double maxLeptonZepCut = 0.75;
      bool passZepMax     = thePandaFlat.nJot              >= 2 && maxLeptonZep     < maxLeptonZepCut;
      bool passZepMaxUp   = thePandaFlat.nJot_JESTotalUp   >= 2 && maxLeptonZepUp   < maxLeptonZepCut;
      bool passZepMaxDown = thePandaFlat.nJot_JESTotalDown >= 2 && maxLeptonZepDown < maxLeptonZepCut;

      double wzZep = 0; double wzZepUp = 0; double wzZepDown = 0;
      wzZep	= TMath::Abs(alllep.Eta()-(vJot1.Eta()+vJot2.Eta())/2.)/deltaEtaJJ;
      wzZepUp	= TMath::Abs(alllep.Eta()-(vJot1JESUp.Eta()+vJot2JESUp.Eta())/2.)/deltaEtaJJUp;
      wzZepDown = TMath::Abs(alllep.Eta()-(vJot1JESDown.Eta()+vJot2JESDown.Eta())/2.)/deltaEtaJJDown;
      bool passwzZep     = thePandaFlat.nJot              >= 2 && wzZep     < 1.00;
      bool passwzZepUp   = thePandaFlat.nJot_JESTotalUp   >= 2 && wzZepUp   < 1.00;
      bool passwzZepDown = thePandaFlat.nJot_JESTotalDown >= 2 && wzZepDown < 1.00;

      double deltaPhiAllleptonMet     = TMath::Abs(alllep.DeltaPhi(vMet));
      double deltaPhiAllleptonMetUp   = TMath::Abs(alllep.DeltaPhi(vMetUp));
      double deltaPhiAllleptonMetDown = TMath::Abs(alllep.DeltaPhi(vMetDown));
      double mtVV     = TMath::Sqrt(2.0*alllep.Pt()*vMet.Pt()    *(1.0 - cos(deltaPhiAllleptonMet    )));
      double mtVVUp   = TMath::Sqrt(2.0*alllep.Pt()*vMetUp.Pt()  *(1.0 - cos(deltaPhiAllleptonMetUp  )));
      double mtVVDown = TMath::Sqrt(2.0*alllep.Pt()*vMetDown.Pt()*(1.0 - cos(deltaPhiAllleptonMetDown)));

      TLorentzVector vW     = vWln + vMet;
      TLorentzVector vWUp   = vWln + vMetUp;
      TLorentzVector vWDown = vWln + vMetDown;

      double zzZep = 0; double zzZepUp = 0; double zzZepDown = 0;
      zzZep	= TMath::Abs(alllep.Eta()-(vJot1.Eta()+vJot2.Eta())/2.)/deltaEtaJJ;
      zzZepUp	= TMath::Abs(alllep.Eta()-(vJot1JESUp.Eta()+vJot2JESUp.Eta())/2.)/deltaEtaJJUp;
      zzZepDown = TMath::Abs(alllep.Eta()-(vJot1JESDown.Eta()+vJot2JESDown.Eta())/2.)/deltaEtaJJDown;
      bool passzzZep	 = thePandaFlat.nJot		  >= 2 && zzZep     < 0.75;
      bool passzzZepUp   = thePandaFlat.nJot_JESTotalUp   >= 2 && zzZepUp   < 0.75;
      bool passzzZepDown = thePandaFlat.nJot_JESTotalDown >= 2 && zzZepDown < 0.75;
 
      bool passMLL   = mllZ > 20 && (fabs(mllZ-91.1876) > 15 || lepType != 1);
      bool passWWMET = vMet.Pt() > 30; bool passWWMETUp = vMetUp.Pt() > 30;bool passWWMETDown = vMetDown.Pt() > 30;
      bool passWZMET = vMet.Pt() > 30; bool passWZMETUp = vMetUp.Pt() > 30;bool passWZMETDown = vMetDown.Pt() > 30;
      bool passNjets = thePandaFlat.nJot >= 2; bool passNjetsUp = thePandaFlat.nJot_JESTotalUp >= 2; bool passNjetsDown = thePandaFlat.nJot_JESTotalDown >= 2;
      bool passBtagVeto = thePandaFlat.jetNMBtags == 0; bool passBtagVetoUp = thePandaFlat.jetNMBtags_JESTotalUp == 0; bool passBtagVetoDown = thePandaFlat.jetNMBtags_JESTotalDown == 0;
      bool passTauVeto = thePandaFlat.nTau == 0;

      double dphill = TMath::Abs(vZ1l1.DeltaPhi(vZ1l2));
      double detall = TMath::Abs(vZ1l1.Eta()-vZ1l2.Eta());
      double drll = sqrt(dphill*dphill+detall*detall);

      //                                                               0        1              2              3               4               5               6                 7            8     
      bool passSel[9]        = {qTot != 0 && thePandaFlat.nLooseLep == 2, passMLL, passWWMET    , passNjets    , passDEtaJJ    , passMJJ       , passZepMax    , passBtagVeto    , passTauVeto};
      bool passSelJESUp[9]   = {qTot != 0 && thePandaFlat.nLooseLep == 2, passMLL, passWWMETUp  , passNjetsUp  , passDEtaJJUp  , passMJJJESUp  , passZepMaxUp  , passBtagVetoUp  , passTauVeto};
      bool passSelJESDown[9] = {qTot != 0 && thePandaFlat.nLooseLep == 2, passMLL, passWWMETDown, passNjetsDown, passDEtaJJDown, passMJJJESDown, passZepMaxDown, passBtagVetoDown, passTauVeto};
      bool passSelJERUp[9]   = {qTot != 0 && thePandaFlat.nLooseLep == 2, passMLL, passWWMET	, passNjets    , passDEtaJJ    , passMJJJERUp  , passZepMax    , passBtagVeto	 , passTauVeto};
      bool passSelJERDown[9] = {qTot != 0 && thePandaFlat.nLooseLep == 2, passMLL, passWWMET    , passNjets    , passDEtaJJ    , passMJJJERDown, passZepMax    , passBtagVeto    , passTauVeto};

      bool passZZPresel = whichWln >= 0 && thePandaFlat.nLooseLep == 4 && lepType <= 2 && mllmin > 4 &&
                          fabs((vZ1l1+vZ1l2).M()-91.1876) < 15 && fabs((vZ2l1+vZ2l2).M()-91.1876) < 15;
      bool passWZPresel = whichWln >= 0 && thePandaFlat.nLooseLep == 3 && alllep.M() > 100 &&
                          fabs(mllZ-91.1876) < 15 && mllmin > 4 && vWln.Pt() > 20;
      bool passWWSel        = passSel[0]        && passSel[1]        && passSel[2]        && passSel[3]        && passSel[4]        && passSel[5]        && passSel[6]        && passSel[7]        && passSel[8];
      bool passWWSelJESUp   = passSelJESUp[0]   && passSelJESUp[1]   && passSelJESUp[2]   && passSelJESUp[3]   && passSelJESUp[4]   && passSelJESUp[5]   && passSelJESUp[6]   && passSelJESUp[7]   && passSelJESUp[8];
      bool passWWSelJESDown = passSelJESDown[0] && passSelJESDown[1] && passSelJESDown[2] && passSelJESDown[3] && passSelJESDown[4] && passSelJESDown[5] && passSelJESDown[6] && passSelJESDown[7] && passSelJESDown[8];
      bool passWWSelJERUp   = passSelJERUp[0]   && passSelJERUp[1]   && passSelJERUp[2]   && passSelJERUp[3]   && passSelJERUp[4]   && passSelJERUp[5]   && passSelJERUp[6]   && passSelJERUp[7]   && passSelJERUp[8];
      bool passWWSelJERDown = passSelJERDown[0] && passSelJERDown[1] && passSelJERDown[2] && passSelJERDown[3] && passSelJERDown[4] && passSelJERDown[5] && passSelJERDown[6] && passSelJERDown[7] && passSelJERDown[8];
      bool passBtagSel        = passSel[0]        && passSel[1]        && passSel[2]        && passSel[3]        && passSel[4]        && passSel[5]        && passSel[6]        && !passSel[7]        && passSel[8];
      bool passBtagSelJESUp   = passSelJESUp[0]   && passSelJESUp[1]   && passSelJESUp[2]   && passSelJESUp[3]   && passSelJESUp[4]   && passSelJESUp[5]   && passSelJESUp[6]   && !passSelJESUp[7]   && passSelJESUp[8];
      bool passBtagSelJESDown = passSelJESDown[0] && passSelJESDown[1] && passSelJESDown[2] && passSelJESDown[3] && passSelJESDown[4] && passSelJESDown[5] && passSelJESDown[6] && !passSelJESDown[7] && passSelJESDown[8];
      bool passBtagSelJERUp   = passSelJERUp[0]   && passSelJERUp[1]   && passSelJERUp[2]   && passSelJERUp[3]   && passSelJERUp[4]   && passSelJERUp[5]   && passSelJERUp[6]   && !passSelJERUp[7]   && passSelJERUp[8];
      bool passBtagSelJERDown = passSelJERDown[0] && passSelJERDown[1] && passSelJERDown[2] && passSelJERDown[3] && passSelJERDown[4] && passSelJERDown[5] && passSelJERDown[6] && !passSelJERDown[7] && passSelJERDown[8];
      bool passZZSel        = passZZPresel && passSel[3]        && passSel[4]         && passSel[5]        && passzzZep;
      bool passZZSelJESUp   = passZZPresel && passSelJESUp[3]   && passSelJESUp[4]    && passSelJESUp[5]   && passzzZepUp;
      bool passZZSelJESDown = passZZPresel && passSelJESDown[3] && passSelJESDown[4]  && passSelJESDown[5] && passzzZepDown;
      bool passZZSelJERUp   = passZZPresel && passSelJERUp[3]   && passSelJERUp[4]    && passSelJERUp[5]   && passzzZepUp;
      bool passZZSelJERDown = passZZPresel && passSelJERDown[3] && passSelJERDown[4]  && passSelJERDown[5] && passzzZepDown;
      bool passWZbSel        = passWZPresel && passWZMET     && passSel[3]        && passSel[4]         && passSel[5]        && passwzZep     && !passSel[7]        && passSel[8];
      bool passWZbSelJESUp   = passWZPresel && passWZMETUp   && passSelJESUp[3]   && passSelJESUp[4]    && passSelJESUp[5]   && passwzZepUp   && !passSelJESUp[7]   && passSelJESUp[8];
      bool passWZbSelJESDown = passWZPresel && passWZMETDown && passSelJESDown[3] && passSelJESDown[4]  && passSelJESDown[5] && passwzZepDown && !passSelJESDown[7] && passSelJESDown[8];
      bool passWZbSelJERUp   = passWZPresel && passWZMET     && passSelJERUp[3]   && passSelJERUp[4]    && passSelJERUp[5]   && passwzZep     && !passSelJERUp[7]	&& passSelJERUp[8];
      bool passWZbSelJERDown = passWZPresel && passWZMET     && passSelJERDown[3] && passSelJERDown[4]  && passSelJERDown[5] && passwzZep     && !passSelJERDown[7] && passSelJERDown[8];
      bool passEWKWZSel        = passWZPresel && passWZMET     && passSel[3]        && passSel[4]         && passSel[5]	       && passwzZep     && passSel[7]        && passSel[8];
      bool passEWKWZSelJESUp   = passWZPresel && passWZMETUp   && passSelJESUp[3]   && passSelJESUp[4]    && passSelJESUp[5]   && passwzZepUp   && passSelJESUp[7]   && passSelJESUp[8];
      bool passEWKWZSelJESDown = passWZPresel && passWZMETDown && passSelJESDown[3] && passSelJESDown[4]  && passSelJESDown[5] && passwzZepDown && passSelJESDown[7] && passSelJESDown[8];
      bool passEWKWZSelJERUp   = passWZPresel && passWZMET     && passSelJERUp[3]   && passSelJERUp[4]    && passSelJERUp[5]   && passwzZep     && passSelJERUp[7]   && passSelJERUp[8];
      bool passEWKWZSelJERDown = passWZPresel && passWZMET     && passSelJERDown[3] && passSelJERDown[4]  && passSelJERDown[5] && passwzZep     && passSelJERDown[7] && passSelJERDown[8];

      int passQCDSel = -1;
      if     (passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[4] && passCRMJJ && passSel[6] &&  passSel[7] && passSel[8]) passQCDSel = 0;
      else if(passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[4] && passCRMJJ && passSel[6] && !passSel[7] && passSel[8]) passQCDSel = 1;
      else if(passZZPresel && passSel[3] && passSel[4] && passCRMJJ && passzzZep) passQCDSel = 2;
      else if(passWZPresel && passWZMET && passSel[3] && passSel[4] && passCRMJJ && passwzZep && !passSel[7] && passSel[8]) passQCDSel = 3;
      else if(passWZPresel && passWZMET && passSel[3] && passSel[4] && passCRMJJ && passwzZep &&  passSel[7] && passSel[8]) passQCDSel = 4;

      bool passZSel      = passSel[0]     && mllZ > 20      && !passSel[2]     && passSel[3]     && passSel[4]     && passSel[5]     && passSel[6]     && passSel[7]     && passSel[8];

      bool passPresel    = passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[5] && !passWWSel;

      bool passAllButOneSel[8] = {
        passSel[0] &&               passSel[2] && passSel[3] && passSel[4] && passSel[5] && passSel[6] && passSel[7] && passSel[8],
        passSel[0] && passSel[1] &&               passSel[3] && passSel[4] && passSel[5] && passSel[6] && passSel[7] && passSel[8],
	passSel[0] && passSel[1] && passSel[2]&&                                                          passSel[7] && passSel[8],
	passSel[0] && passSel[1] && passSel[2] && passSel[3] &&               passSel[5] && passSel[6] && passSel[7] && passSel[8],
	passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[4] &&               passSel[6] && passSel[7] && passSel[8],
	passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[4] && passSel[5] &&               passSel[7] && passSel[8],
	passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[4] && passSel[5] && passSel[6]               && passSel[8],
	passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[4] && passSel[5] && passSel[6] && passSel[7]
      };

      int dataCardSel = -1;int dataCardSelJESUp = -1;int dataCardSelJESDown = -1;int dataCardSelJERUp = -1;int dataCardSelJERDown = -1;
      if     (passWWSel)    dataCardSel = 0;
      else if(passBtagSel)  dataCardSel = 1;
      else if(passZZSel)    dataCardSel = 2;
      else if(passWZbSel)   dataCardSel = 3;
      else if(passEWKWZSel) dataCardSel = 4;
      if     (passWWSelJESUp)    dataCardSelJESUp = 0;
      else if(passBtagSelJESUp)  dataCardSelJESUp = 1;
      else if(passZZSelJESUp)    dataCardSelJESUp = 2;
      else if(passWZbSelJESUp)   dataCardSelJESUp = 3;
      else if(passEWKWZSelJESUp) dataCardSelJESUp = 4;
      if     (passWWSelJESDown)    dataCardSelJESDown = 0;
      else if(passBtagSelJESDown)  dataCardSelJESDown = 1;
      else if(passZZSelJESDown)    dataCardSelJESDown = 2;
      else if(passWZbSelJESDown)   dataCardSelJESDown = 3;
      else if(passEWKWZSelJESDown) dataCardSelJESDown = 4;
      if     (passWWSelJERUp)    dataCardSelJERUp = 0;
      else if(passBtagSelJERUp)  dataCardSelJERUp = 1;
      else if(passZZSelJERUp)    dataCardSelJERUp = 2;
      else if(passWZbSelJERUp)   dataCardSelJERUp = 3;
      else if(passEWKWZSelJERUp) dataCardSelJERUp = 4;
      if     (passWWSelJERDown)    dataCardSelJERDown = 0;
      else if(passBtagSelJERDown)  dataCardSelJERDown = 1;
      else if(passZZSelJERDown)    dataCardSelJERDown = 2;
      else if(passWZbSelJERDown)   dataCardSelJERDown = 3;
      else if(passEWKWZSelJERDown) dataCardSelJERDown = 4;

      bool passSystCuts[nSystTypes] = {dataCardSelJESUp >= 0, dataCardSelJESDown >= 0, dataCardSelJERUp >= 0, dataCardSelJERDown >= 0};

      double rw_aqgc_ft0[nscan_ft0] =  {thePandaFlat.rw_ft0_m2p0, thePandaFlat.rw_ft0_m1p8, thePandaFlat.rw_ft0_m1p4, thePandaFlat.rw_ft0_m1p2, thePandaFlat.rw_ft0_m1p0,
					thePandaFlat.rw_ft0_m0p7, thePandaFlat.rw_ft0_m0p5, thePandaFlat.rw_ft0_m0p3, thePandaFlat.rw_ft0_m0p2, thePandaFlat.rw_ft0_m0p18, 
					thePandaFlat.rw_ft0_m0p14, thePandaFlat.rw_ft0_m0p12, thePandaFlat.rw_ft0_m0p1, thePandaFlat.rw_ft0_m0p08, thePandaFlat.rw_ft0_m0p06, 
					thePandaFlat.rw_ft0_m0p04, thePandaFlat.rw_ft0_m0p02, thePandaFlat.rw_ft0_0p02, thePandaFlat.rw_ft0_0p04, 
					thePandaFlat.rw_ft0_0p06, thePandaFlat.rw_ft0_0p08, thePandaFlat.rw_ft0_0p1, thePandaFlat.rw_ft0_0p12, thePandaFlat.rw_ft0_0p14, 
					thePandaFlat.rw_ft0_0p18, thePandaFlat.rw_ft0_0p2, thePandaFlat.rw_ft0_0p3, thePandaFlat.rw_ft0_0p5, thePandaFlat.rw_ft0_0p7, 
					thePandaFlat.rw_ft0_1p0, thePandaFlat.rw_ft0_1p2, thePandaFlat.rw_ft0_1p4, thePandaFlat.rw_ft0_1p8, thePandaFlat.rw_ft0_2p0}; 

      double rw_aqgc_ft1[nscan_ft1] =  {thePandaFlat.rw_ft1_m2p0, thePandaFlat.rw_ft1_m1p8, thePandaFlat.rw_ft1_m1p4, thePandaFlat.rw_ft1_m1p2, thePandaFlat.rw_ft1_m1p0,
                                        thePandaFlat.rw_ft1_m0p7, thePandaFlat.rw_ft1_m0p5, thePandaFlat.rw_ft1_m0p3, thePandaFlat.rw_ft1_m0p2, thePandaFlat.rw_ft1_m0p18,
                                        thePandaFlat.rw_ft1_m0p14, thePandaFlat.rw_ft1_m0p12, thePandaFlat.rw_ft1_m0p1, thePandaFlat.rw_ft1_m0p08, thePandaFlat.rw_ft1_m0p06,
                                        thePandaFlat.rw_ft1_m0p04, thePandaFlat.rw_ft1_m0p02, thePandaFlat.rw_ft1_0p02, thePandaFlat.rw_ft1_0p04,
                                        thePandaFlat.rw_ft1_0p06, thePandaFlat.rw_ft1_0p08, thePandaFlat.rw_ft1_0p1, thePandaFlat.rw_ft1_0p12, thePandaFlat.rw_ft1_0p14,
                                        thePandaFlat.rw_ft1_0p18, thePandaFlat.rw_ft1_0p2, thePandaFlat.rw_ft1_0p3, thePandaFlat.rw_ft1_0p5, thePandaFlat.rw_ft1_0p7,
                                        thePandaFlat.rw_ft1_1p0, thePandaFlat.rw_ft1_1p2, thePandaFlat.rw_ft1_1p4, thePandaFlat.rw_ft1_1p8, thePandaFlat.rw_ft1_2p0};

      double rw_aqgc_ft2[nscan_ft2] =  {thePandaFlat.rw_ft2_m4p5, thePandaFlat.rw_ft2_m3p9, thePandaFlat.rw_ft2_m3p4, thePandaFlat.rw_ft2_m2p9, thePandaFlat.rw_ft2_m2p5,
                                        thePandaFlat.rw_ft2_m1p7, thePandaFlat.rw_ft2_m1p2, thePandaFlat.rw_ft2_m0p9, thePandaFlat.rw_ft2_m0p7, thePandaFlat.rw_ft2_m0p5,
                                        thePandaFlat.rw_ft2_m0p32, thePandaFlat.rw_ft2_m0p26, thePandaFlat.rw_ft2_m0p2, thePandaFlat.rw_ft2_m0p14, thePandaFlat.rw_ft2_m0p08,
                                        thePandaFlat.rw_ft2_m0p04, thePandaFlat.rw_ft2_m0p02, thePandaFlat.rw_ft2_0p02, thePandaFlat.rw_ft2_0p04,
                                        thePandaFlat.rw_ft2_0p08, thePandaFlat.rw_ft2_0p14, thePandaFlat.rw_ft2_0p2, thePandaFlat.rw_ft2_0p26, thePandaFlat.rw_ft2_0p32,
                                        thePandaFlat.rw_ft2_0p5, thePandaFlat.rw_ft2_0p7, thePandaFlat.rw_ft2_0p9, thePandaFlat.rw_ft2_1p2, thePandaFlat.rw_ft2_1p7,
                                        thePandaFlat.rw_ft2_2p5, thePandaFlat.rw_ft2_2p9, thePandaFlat.rw_ft2_3p4, thePandaFlat.rw_ft2_3p9, thePandaFlat.rw_ft2_4p5};

      double rw_aqgc_fm0[nscan_fm0] =  {thePandaFlat.rw_fm0_m10, thePandaFlat.rw_fm0_m9, thePandaFlat.rw_fm0_m8, thePandaFlat.rw_fm0_m7, thePandaFlat.rw_fm0_m6, 
					thePandaFlat.rw_fm0_m5, thePandaFlat.rw_fm0_m4, thePandaFlat.rw_fm0_m3, thePandaFlat.rw_fm0_m2p0, thePandaFlat.rw_fm0_m1p5, 
					thePandaFlat.rw_fm0_m1p0, thePandaFlat.rw_fm0_m0p9, thePandaFlat.rw_fm0_m0p8, thePandaFlat.rw_fm0_m0p7, thePandaFlat.rw_fm0_m0p6, 
					thePandaFlat.rw_fm0_m0p5, thePandaFlat.rw_fm0_m0p4, thePandaFlat.rw_fm0_m0p3, thePandaFlat.rw_fm0_m0p2, thePandaFlat.rw_fm0_m0p1, 
					thePandaFlat.rw_fm0_0p1, thePandaFlat.rw_fm0_0p2, thePandaFlat.rw_fm0_0p3, thePandaFlat.rw_fm0_0p4, 
					thePandaFlat.rw_fm0_0p5, thePandaFlat.rw_fm0_0p6, thePandaFlat.rw_fm0_0p7, thePandaFlat.rw_fm0_0p8, thePandaFlat.rw_fm0_0p9, 
					thePandaFlat.rw_fm0_1p0, thePandaFlat.rw_fm0_1p5, thePandaFlat.rw_fm0_2p0, thePandaFlat.rw_fm0_3, thePandaFlat.rw_fm0_4, 
					thePandaFlat.rw_fm0_5, thePandaFlat.rw_fm0_6, thePandaFlat.rw_fm0_7, thePandaFlat.rw_fm0_8, thePandaFlat.rw_fm0_9, thePandaFlat.rw_fm0_10};

      double rw_aqgc_fm1[nscan_fm1] =  {thePandaFlat.rw_fm1_m30, thePandaFlat.rw_fm1_m28, thePandaFlat.rw_fm1_m23p0, thePandaFlat.rw_fm1_m21, thePandaFlat.rw_fm1_m18, 
					thePandaFlat.rw_fm1_m15, thePandaFlat.rw_fm1_m13, thePandaFlat.rw_fm1_m10, thePandaFlat.rw_fm1_m5p0, thePandaFlat.rw_fm1_m3p0, 
					thePandaFlat.rw_fm1_m2p5, thePandaFlat.rw_fm1_m2p1, thePandaFlat.rw_fm1_m1p8, thePandaFlat.rw_fm1_m1p5, thePandaFlat.rw_fm1_m1p2, 
					thePandaFlat.rw_fm1_m0p9, thePandaFlat.rw_fm1_m0p6, thePandaFlat.rw_fm1_m0p3, thePandaFlat.rw_fm1_0p3, 
					thePandaFlat.rw_fm1_0p6, thePandaFlat.rw_fm1_0p9, thePandaFlat.rw_fm1_1p2, thePandaFlat.rw_fm1_1p5, thePandaFlat.rw_fm1_1p8, 
					thePandaFlat.rw_fm1_2p1, thePandaFlat.rw_fm1_2p5, thePandaFlat.rw_fm1_3p0, thePandaFlat.rw_fm1_5p0, thePandaFlat.rw_fm1_10, 
					thePandaFlat.rw_fm1_13, thePandaFlat.rw_fm1_15, thePandaFlat.rw_fm1_18, thePandaFlat.rw_fm1_21, thePandaFlat.rw_fm1_23p0, 
					thePandaFlat.rw_fm1_28, thePandaFlat.rw_fm1_30};

      double rw_aqgc_fm6[nscan_fm6] =  {thePandaFlat.rw_fm6_m20, thePandaFlat.rw_fm6_m18, thePandaFlat.rw_fm6_m15, thePandaFlat.rw_fm6_m12, thePandaFlat.rw_fm6_m10,
                                        thePandaFlat.rw_fm6_m7, thePandaFlat.rw_fm6_m5, thePandaFlat.rw_fm6_m3, thePandaFlat.rw_fm6_m2p0, thePandaFlat.rw_fm6_m1p8,
                                        thePandaFlat.rw_fm6_m1p6, thePandaFlat.rw_fm6_m1p4, thePandaFlat.rw_fm6_m1p2, thePandaFlat.rw_fm6_m1p0, thePandaFlat.rw_fm6_m0p7,
                                        thePandaFlat.rw_fm6_m0p5, thePandaFlat.rw_fm6_m0p2, thePandaFlat.rw_fm6_0p2, thePandaFlat.rw_fm6_0p5, 
					thePandaFlat.rw_fm6_0p7, thePandaFlat.rw_fm6_1p0, thePandaFlat.rw_fm6_1p2, thePandaFlat.rw_fm6_1p4, thePandaFlat.rw_fm6_1p6, 
					thePandaFlat.rw_fm6_1p8, thePandaFlat.rw_fm6_2p0, thePandaFlat.rw_fm6_3, thePandaFlat.rw_fm6_5, thePandaFlat.rw_fm6_7, 
					thePandaFlat.rw_fm6_10, thePandaFlat.rw_fm6_12, thePandaFlat.rw_fm6_15, thePandaFlat.rw_fm6_18, thePandaFlat.rw_fm6_20};

      double rw_aqgc_fm7[nscan_fm7] =  {thePandaFlat.rw_fm7_m40, thePandaFlat.rw_fm7_m35, thePandaFlat.rw_fm7_m30, thePandaFlat.rw_fm7_m25, thePandaFlat.rw_fm7_m20,
                                        thePandaFlat.rw_fm7_m15, thePandaFlat.rw_fm7_m10, thePandaFlat.rw_fm7_m5p0, thePandaFlat.rw_fm7_m3p5, thePandaFlat.rw_fm7_m3p0,
                                        thePandaFlat.rw_fm7_m2p5, thePandaFlat.rw_fm7_m2p0, thePandaFlat.rw_fm7_m1p5, thePandaFlat.rw_fm7_m1p0, thePandaFlat.rw_fm7_m0p5,
                                        thePandaFlat.rw_fm7_0p5, thePandaFlat.rw_fm7_1p0, thePandaFlat.rw_fm7_1p5, thePandaFlat.rw_fm7_2p0, 
					thePandaFlat.rw_fm7_2p5, thePandaFlat.rw_fm7_3p0, thePandaFlat.rw_fm7_3p5, thePandaFlat.rw_fm7_5p0, thePandaFlat.rw_fm7_10, 
					thePandaFlat.rw_fm7_15, thePandaFlat.rw_fm7_20, thePandaFlat.rw_fm7_25, thePandaFlat.rw_fm7_30, thePandaFlat.rw_fm7_35, thePandaFlat.rw_fm7_40};

      double rw_aqgc_fs0[nscan_fs0] =  {thePandaFlat.rw_fs0_m50, thePandaFlat.rw_fs0_m45, thePandaFlat.rw_fs0_m40, thePandaFlat.rw_fs0_m35, thePandaFlat.rw_fs0_m30,
                                        thePandaFlat.rw_fs0_m20, thePandaFlat.rw_fs0_m10, thePandaFlat.rw_fs0_m8, thePandaFlat.rw_fs0_m6, thePandaFlat.rw_fs0_m5,
                                        thePandaFlat.rw_fs0_m4, thePandaFlat.rw_fs0_m3p0, thePandaFlat.rw_fs0_m2p5, thePandaFlat.rw_fs0_m2p0, thePandaFlat.rw_fs0_m1p5,
					thePandaFlat.rw_fs0_m1p2, thePandaFlat.rw_fs0_m1p0, thePandaFlat.rw_fs0_m0p8, thePandaFlat.rw_fs0_m0p6, thePandaFlat.rw_fs0_m0p4,
                                        thePandaFlat.rw_fs0_m0p2, thePandaFlat.rw_fs0_0p2, thePandaFlat.rw_fs0_0p4, thePandaFlat.rw_fs0_0p6, 
					thePandaFlat.rw_fs0_0p8, thePandaFlat.rw_fs0_1p0, thePandaFlat.rw_fs0_1p2, thePandaFlat.rw_fs0_1p5, thePandaFlat.rw_fs0_2p0, 
					thePandaFlat.rw_fs0_2p5, thePandaFlat.rw_fs0_3p0, thePandaFlat.rw_fs0_4, thePandaFlat.rw_fs0_5, thePandaFlat.rw_fs0_6, 
					thePandaFlat.rw_fs0_8, thePandaFlat.rw_fs0_10, thePandaFlat.rw_fs0_20, thePandaFlat.rw_fs0_30, thePandaFlat.rw_fs0_35, 
					thePandaFlat.rw_fs0_40, thePandaFlat.rw_fs0_45, thePandaFlat.rw_fs0_50};

      double rw_aqgc_fs1[nscan_fs1] =  {thePandaFlat.rw_fs1_m35, thePandaFlat.rw_fs1_m33, thePandaFlat.rw_fs1_m30, thePandaFlat.rw_fs1_m25, thePandaFlat.rw_fs1_m20,
                                        thePandaFlat.rw_fs1_m15, thePandaFlat.rw_fs1_m10, thePandaFlat.rw_fs1_m7p5, thePandaFlat.rw_fs1_m5p0, thePandaFlat.rw_fs1_m4p0, 
					thePandaFlat.rw_fs1_m3p0, thePandaFlat.rw_fs1_m2p5, thePandaFlat.rw_fs1_m2p0, thePandaFlat.rw_fs1_m1p5, thePandaFlat.rw_fs1_m1p0, 
					thePandaFlat.rw_fs1_m0p5, thePandaFlat.rw_fs1_0p5, thePandaFlat.rw_fs1_1p0, thePandaFlat.rw_fs1_1p5, 
					thePandaFlat.rw_fs1_2p0, thePandaFlat.rw_fs1_2p5, thePandaFlat.rw_fs1_3p0, thePandaFlat.rw_fs1_4p0, thePandaFlat.rw_fs1_5p0, 
					thePandaFlat.rw_fs1_7p5, thePandaFlat.rw_fs1_10, thePandaFlat.rw_fs1_15, thePandaFlat.rw_fs1_20, thePandaFlat.rw_fs1_25, 
					thePandaFlat.rw_fs1_30, thePandaFlat.rw_fs1_33, thePandaFlat.rw_fs1_35};
      double totalWeight = 1.0; double puWeight = 1.0; double puWeightUp = 1.0; double puWeightDown = 1.0; double effWSUnc = 1.0; double sf_l1PrefireE = 1.0;
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

	//double npvWeight = nPUScaleFactor(fhDNPV, thePandaFlat.npv);

        totalWeight = thePandaFlat.normalizedWeight * lumiV[whichYear] * puWeight * thePandaFlat.sf_l1Prefire * looseLepSF[0] * looseLepSF[1] * triggerWeights[0] * theMCPrescale;
	if(thePandaFlat.nLooseLep == 3)      totalWeight = totalWeight * looseLepSF[2];
	else if(thePandaFlat.nLooseLep == 4) totalWeight = totalWeight * looseLepSF[2] * looseLepSF[3];

        if(passBtagVeto) totalWeight = totalWeight * thePandaFlat.sf_btag0;
        else             totalWeight = totalWeight * thePandaFlat.sf_btagGT0;

        //if(infileCat_[ifile] == kPlotWZ)                                                totalWeight = totalWeight * thePandaFlat.sf_wz;
	//if(infileCat_[ifile] == kPlotZZ && infileName_[ifile].Contains("qqZZ") == true) totalWeight = totalWeight * thePandaFlat.sf_zz;
	//if((infileCat_[ifile] == kPlotEWKSSWW || infileCat_[ifile] == kPlotEWKSSWW_dim8) && thePandaFlat.genMjj > 500) totalWeight = totalWeight * hWW_KF_CMS->GetBinContent(hWW_KF_CMS->GetXaxis()->FindFixBin(TMath::Min(thePandaFlat.genMjj,1999.999f)));
	//if((infileCat_[ifile] == kPlotEWKWZ || infileCat_[ifile] == kPlotEWKWZ_dim8) && thePandaFlat.genMjj > 500) totalWeight = totalWeight * hWZ_KF_CMS->GetBinContent(hWZ_KF_CMS->GetXaxis()->FindFixBin(TMath::Min(thePandaFlat.genMjj,2999.999f)));

        double effSF = 1.0;
        for(unsigned int nl=0; nl<idLep.size(); nl++){
          if(idLep[nl] == 0) continue;
          bool applyTight = true;
          effSF = effSF * lepScaleFactor(vLoose[nl].Pt(),vLoose[nl].Eta(),TMath::Abs(looseLepPdgId[nl]),applyTight,histoLepEffSelMediumEtaPt_m,histoLepEffSelMediumEtaPt_e,histoLepEffSelTightEtaPt_m,histoLepEffSelTightEtaPt_e);
          if(effSF == 0){printf("effSF == 0!: %f %f %d \n",vLoose[nl].Pt(),vLoose[nl].Eta(),TMath::Abs(looseLepPdgId[nl])); return;}
        }
        totalWeight = totalWeight * effSF;

        bool isRS = thePandaFlat.looseGenLep1PdgId > 0 && thePandaFlat.looseGenLep2PdgId > 0;
        if(thePandaFlat.nLooseLep >= 3) isRS = isRS && thePandaFlat.looseGenLep3PdgId > 0;
        if(thePandaFlat.nLooseLep >= 4) isRS = isRS && thePandaFlat.looseGenLep4PdgId > 0;
	if     (!isRS && infileName_[ifile].Contains("dim8")) totalWeight = 0.0;
	else if(!isRS && theCategory != kPlotVG) {
	  theCategory = kPlotWS;
	  int theWSLepton = -1;
	  if     (thePandaFlat.nLooseLep >= 2 && abs(looseLepPdgId[0]) == 11 && thePandaFlat.looseGenLep1PdgId < 0) theWSLepton = 0;
	  else if(thePandaFlat.nLooseLep >= 2 && abs(looseLepPdgId[1]) == 11 && thePandaFlat.looseGenLep2PdgId < 0) theWSLepton = 1;
	  else if(thePandaFlat.nLooseLep >= 3 && abs(looseLepPdgId[2]) == 11 && thePandaFlat.looseGenLep3PdgId < 0) theWSLepton = 2;
	  else if(thePandaFlat.nLooseLep >= 4 && abs(looseLepPdgId[3]) == 11 && thePandaFlat.looseGenLep4PdgId < 0) theWSLepton = 3;
          if(theWSLepton >= 0){
	    int nEta = histoWSEtaCorr->GetXaxis()->FindBin(TMath::Min(TMath::Abs(vLoose[theWSLepton].Eta()),2.4999))-1;
	    if(nEta >= nBinWSEtaCorr) printf("Problem with WSSF\n");
	    totalWeight = totalWeight * WSSF[nEta];
	    effWSUnc = 1.0 + (WSSFE[nEta]+0.15);
	  }
	}
      }

      if(usePureMC == false && countLeptonTight != idLep.size()){
        double fakeSF = 1.0;
        for(unsigned int nl=0; nl<idLep.size(); nl++){
          if(idLep[nl] == 1) continue;
          bool applyTight = true;
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

      if(theCategory != kPlotData){
        totalWeight = totalWeight * mcCorrection(0, year, thePandaFlat.jetNMBtags,thePandaFlat.jetNBtags, thePandaFlat.nJot, 0.0, theCategory);
      }

      if((passWWSel || passEWKWZSel) && produceMVAInputs == true){
        category    = theCategory;
        eventNum    = thePandaFlat.eventNumber;
        weight      = totalWeight;
        mvamjj      = (float)massJJ;
        mvadetajj   = (float)deltaEtaJJ;
        mvadphijj   = (float)deltaPhiJJ;
        mvajetpt1   = (float)vJot1.Pt();
        mvajetpt2   = (float)vJot2.Pt();
        mvajeteta1  = (float)vJot1.Eta();
        mvajeteta2  = (float)vJot2.Eta();
	mvanjets    = (float)thePandaFlat.nJot;
        mvaWpt      = (float)vW.Pt();
        mvaZpt      = (float)(vZ1l1+vZ1l2).Pt();
        mvaVVmt     = (float)mtVV;
        mvaWlZdeta  = (float)TMath::Abs(vWln.Eta()-(vZ1l1+vZ1l2).Eta());
        mvazstar    = (float)wzZep;
        mvazep1     = (float)vvZepSS[0];
        mvazep2     = (float)vvZepSS[1];
        mvazep3     = (float)vvZepSS[2];
	mvamaxzep   = (float)maxLeptonZep;
        mvaj1Zdr    = (float)TMath::Sqrt(TMath::Power(TMath::Abs(vJot1.Eta()-(vZ1l1+vZ1l2).Eta()),2)+TMath::Power(TMath::Abs(vJot1.DeltaPhi(vZ1l1+vZ1l2)),2));
        mvaj2Zdr    = (float)TMath::Sqrt(TMath::Power(TMath::Abs(vJot2.Eta()-(vZ1l1+vZ1l2).Eta()),2)+TMath::Power(TMath::Abs(vJot2.DeltaPhi(vZ1l1+vZ1l2)),2));
        mvapttot    = (float)totSystem.Pt();
        mvasumpttot = (float)sumPtTot;
	mvaleppt1   = (float)vZ1l1.Pt();
	mvaleppt2   = (float)vZ1l2.Pt();
	mvalepeta1  = (float)vZ1l1.Eta();
	mvalepeta2  = (float)vZ1l2.Eta();
	mvadphill   = (float)dphill;
	mvadrll     = (float)drll;
	mvamll      = (float)(vZ1l1+vZ1l2).M();
        
        mvatree->Fill();
      }

      double bdtWWValue[3] = {0.0,0.0,0.0}, bdtWWValueJESUp[3] = {0.0,0.0,0.0}, bdtWWValueJESDown[3] = {0.0,0.0,0.0}, bdtWWValueJERUp[3] = {0.0,0.0,0.0}, bdtWWValueJERDown[3] = {0.0,0.0,0.0};
      if(passWWSel || passBtagSel){
        //mvaWWInputs[ 0] = (float)massJJ;
        mvaWWInputs[ 0] = (float)deltaEtaJJ;
        mvaWWInputs[ 1] = (float)deltaPhiJJ;
	mvaWWInputs[ 2] = (float)vJot1.Pt();
        mvaWWInputs[ 3] = (float)vJot2.Pt();
        mvaWWInputs[ 4] = (float)vJot1.Eta();
        mvaWWInputs[ 5] = (float)vJot2.Eta();
	mvaWWInputs[ 6] = (float)vW.Pt();
	mvaWWInputs[ 7] = (float)(vZ1l1+vZ1l2).Pt();
	mvaWWInputs[ 8] = (float)mtVV;
	mvaWWInputs[ 9] = (float)wzZep;
	mvaWWInputs[10] = (float)vvZepSS[0];
	mvaWWInputs[11] = (float)vvZepSS[1];
	mvaWWInputs[12] = (float)maxLeptonZep;
	mvaWWInputs[13] = (float)TMath::Sqrt(TMath::Power(TMath::Abs(vJot1.Eta()-(vZ1l1+vZ1l2).Eta()),2)+TMath::Power(TMath::Abs(vJot1.DeltaPhi(vZ1l1+vZ1l2)),2));
	mvaWWInputs[14] = (float)TMath::Sqrt(TMath::Power(TMath::Abs(vJot2.Eta()-(vZ1l1+vZ1l2).Eta()),2)+TMath::Power(TMath::Abs(vJot2.DeltaPhi(vZ1l1+vZ1l2)),2));
	mvaWWInputs[15] = (float)totSystem.Pt()/sumPtTot;
	mvaWWInputs[16] = (float)totSystem.Pt();
	mvaWWInputs[17] = (float)vZ1l1.Pt();
	mvaWWInputs[18] = (float)vZ1l2.Pt();
	mvaWWInputs[19] = (float)vZ1l1.Eta();
	mvaWWInputs[20] = (float)vZ1l2.Eta();
	mvaWWInputs[21] = (float)dphill;
	mvaWWInputs[22] = (float)drll;
	mvaWWInputs[23] = (float)(vZ1l1+vZ1l2).M();
	mvaWWInputs[24] = (float)(vZ1l1.Pt()*vZ1l2.Pt())/(vJot1.Pt()*vJot2.Pt());
        bdtWWValue[0] = TMath::Min(theReaderWW->EvaluateMVA("BDT"),0.999);
        //const std::vector< Float_t > mvaV = theReaderWW->EvaluateMulticlass("BDT");
	//bdtWWValue[0] = TMath::Min(mvaV[2],0.999);
	//bdtWWValue[1] = TMath::Min(mvaV[1],0.999);
	//bdtWWValue[2] = TMath::Min(mvaV[0],0.999);
      }
      if(passWWSelJESUp || passBtagSelJESUp){
        //mvaWWInputs[ 0] = (float)massJJJESUp;
        mvaWWInputs[ 0] = (float)deltaEtaJJUp;
        mvaWWInputs[ 1] = (float)deltaPhiJJUp;
	mvaWWInputs[ 2] = (float)vJot1JESUp.Pt();
        mvaWWInputs[ 3] = (float)vJot2JESUp.Pt();
        mvaWWInputs[ 4] = (float)vJot1JESUp.Eta();
        mvaWWInputs[ 5] = (float)vJot2JESUp.Eta();
	mvaWWInputs[ 6] = (float)vWUp.Pt();
	mvaWWInputs[ 7] = (float)(vZ1l1+vZ1l2).Pt();
	mvaWWInputs[ 8] = (float)mtVVUp;
	mvaWWInputs[ 9] = (float)wzZepUp;
	mvaWWInputs[10] = (float)vvZepSSUp[0];
	mvaWWInputs[11] = (float)vvZepSSUp[1];
	mvaWWInputs[12] = (float)maxLeptonZepUp;
	mvaWWInputs[13] = (float)TMath::Sqrt(TMath::Power(TMath::Abs(vJot1JESUp.Eta()-(vZ1l1+vZ1l2).Eta()),2)+TMath::Power(TMath::Abs(vJot1JESUp.DeltaPhi(vZ1l1+vZ1l2)),2));
	mvaWWInputs[14] = (float)TMath::Sqrt(TMath::Power(TMath::Abs(vJot2JESUp.Eta()-(vZ1l1+vZ1l2).Eta()),2)+TMath::Power(TMath::Abs(vJot2JESUp.DeltaPhi(vZ1l1+vZ1l2)),2));
	mvaWWInputs[15] = (float)totSystemJESUp.Pt()/sumPtTotJESUp;
	mvaWWInputs[16] = (float)totSystemJESUp.Pt();
	mvaWWInputs[17] = (float)vZ1l1.Pt();
	mvaWWInputs[18] = (float)vZ1l2.Pt();
	mvaWWInputs[19] = (float)vZ1l1.Eta();
	mvaWWInputs[20] = (float)vZ1l2.Eta();
	mvaWWInputs[21] = (float)dphill;
	mvaWWInputs[22] = (float)drll;
	mvaWWInputs[23] = (float)(vZ1l1+vZ1l2).M();
	mvaWWInputs[24] = (float)(vZ1l1.Pt()*vZ1l2.Pt())/(vJot1JESUp.Pt()*vJot2JESUp.Pt()); 
        bdtWWValueJESUp[0] = TMath::Min(theReaderWW->EvaluateMVA("BDT"),0.999);
        //const std::vector< Float_t > mvaV = theReaderWW->EvaluateMulticlass("BDT");
	//bdtWWValueJESUp[0] = TMath::Min(mvaV[2],0.999);
	//bdtWWValueJESUp[1] = TMath::Min(mvaV[1],0.999);
	//bdtWWValueJESUp[2] = TMath::Min(mvaV[0],0.999);
      }
      if(passWWSelJESDown || passBtagSelJESDown){
        //mvaWWInputs[ 0] = (float)massJJJESDown;
        mvaWWInputs[ 0] = (float)deltaEtaJJDown;
        mvaWWInputs[ 1] = (float)deltaPhiJJDown;
	mvaWWInputs[ 2] = (float)vJot1JESDown.Pt();
        mvaWWInputs[ 3] = (float)vJot2JESDown.Pt();
        mvaWWInputs[ 4] = (float)vJot1JESDown.Eta();
        mvaWWInputs[ 5] = (float)vJot2JESDown.Eta();
	mvaWWInputs[ 6] = (float)vWDown.Pt();
	mvaWWInputs[ 7] = (float)(vZ1l1+vZ1l2).Pt();
	mvaWWInputs[ 8] = (float)mtVVDown;
	mvaWWInputs[ 9] = (float)wzZepDown;
	mvaWWInputs[10] = (float)vvZepSSDown[0];
	mvaWWInputs[11] = (float)vvZepSSDown[1];
	mvaWWInputs[12] = (float)maxLeptonZepDown;
	mvaWWInputs[13] = (float)TMath::Sqrt(TMath::Power(TMath::Abs(vJot1JESDown.Eta()-(vZ1l1+vZ1l2).Eta()),2)+TMath::Power(TMath::Abs(vJot1JESDown.DeltaPhi(vZ1l1+vZ1l2)),2));
	mvaWWInputs[14] = (float)TMath::Sqrt(TMath::Power(TMath::Abs(vJot2JESDown.Eta()-(vZ1l1+vZ1l2).Eta()),2)+TMath::Power(TMath::Abs(vJot2JESDown.DeltaPhi(vZ1l1+vZ1l2)),2));
	mvaWWInputs[15] = (float)totSystemJESDown.Pt()/sumPtTotJESDown;
	mvaWWInputs[16] = (float)totSystemJESDown.Pt();
	mvaWWInputs[17] = (float)vZ1l1.Pt();
	mvaWWInputs[18] = (float)vZ1l2.Pt();
	mvaWWInputs[19] = (float)vZ1l1.Eta();
	mvaWWInputs[20] = (float)vZ1l2.Eta();
	mvaWWInputs[21] = (float)dphill;
	mvaWWInputs[22] = (float)drll;
	mvaWWInputs[23] = (float)(vZ1l1+vZ1l2).M();
	mvaWWInputs[24] = (float)(vZ1l1.Pt()*vZ1l2.Pt())/(vJot1JESDown.Pt()*vJot2JESDown.Pt()); 
        bdtWWValueJESDown[0] = TMath::Min(theReaderWW->EvaluateMVA("BDT"),0.999);
        //const std::vector< Float_t > mvaV = theReaderWW->EvaluateMulticlass("BDT");
	//bdtWWValueJESDown[0] = TMath::Min(mvaV[2],0.999);
	//bdtWWValueJESDown[1] = TMath::Min(mvaV[1],0.999);
	//bdtWWValueJESDown[2] = TMath::Min(mvaV[0],0.999);
      }
      if(passWWSelJERUp || passBtagSelJERUp){
        //mvaWWInputs[ 0] = (float)massJJJERUp;
        mvaWWInputs[ 0] = (float)deltaEtaJJ;
        mvaWWInputs[ 1] = (float)deltaPhiJJ;
	mvaWWInputs[ 2] = (float)vJot1JERUp.Pt();
        mvaWWInputs[ 3] = (float)vJot2JERUp.Pt();
        mvaWWInputs[ 4] = (float)vJot1JERUp.Eta();
        mvaWWInputs[ 5] = (float)vJot2JERUp.Eta();
	mvaWWInputs[ 6] = (float)vW.Pt();
	mvaWWInputs[ 7] = (float)(vZ1l1+vZ1l2).Pt();
	mvaWWInputs[ 8] = (float)mtVV;
	mvaWWInputs[ 9] = (float)wzZep;
	mvaWWInputs[10] = (float)vvZepSS[0];
	mvaWWInputs[11] = (float)vvZepSS[1];
	mvaWWInputs[12] = (float)maxLeptonZep;
	mvaWWInputs[13] = (float)TMath::Sqrt(TMath::Power(TMath::Abs(vJot1JERUp.Eta()-(vZ1l1+vZ1l2).Eta()),2)+TMath::Power(TMath::Abs(vJot1JERUp.DeltaPhi(vZ1l1+vZ1l2)),2));
	mvaWWInputs[14] = (float)TMath::Sqrt(TMath::Power(TMath::Abs(vJot2JERUp.Eta()-(vZ1l1+vZ1l2).Eta()),2)+TMath::Power(TMath::Abs(vJot2JERUp.DeltaPhi(vZ1l1+vZ1l2)),2));
	mvaWWInputs[15] = (float)totSystemJERUp.Pt()/sumPtTotJERUp;
	mvaWWInputs[16] = (float)totSystemJERUp.Pt();
	mvaWWInputs[17] = (float)vZ1l1.Pt();
	mvaWWInputs[18] = (float)vZ1l2.Pt();
	mvaWWInputs[19] = (float)vZ1l1.Eta();
	mvaWWInputs[20] = (float)vZ1l2.Eta();
	mvaWWInputs[21] = (float)dphill;
	mvaWWInputs[22] = (float)drll;
	mvaWWInputs[23] = (float)(vZ1l1+vZ1l2).M();
	mvaWWInputs[24] = (float)(vZ1l1.Pt()*vZ1l2.Pt())/(vJot1JERUp.Pt()*vJot2JERUp.Pt()); 
        bdtWWValueJERUp[0] = TMath::Min(theReaderWW->EvaluateMVA("BDT"),0.999);
        //const std::vector< Float_t > mvaV = theReaderWW->EvaluateMulticlass("BDT");
	//bdtWWValueJERUp[0] = TMath::Min(mvaV[2],0.999);
	//bdtWWValueJERUp[1] = TMath::Min(mvaV[1],0.999);
	//bdtWWValueJERUp[2] = TMath::Min(mvaV[0],0.999);
      }
      if(passWWSelJERDown || passBtagSelJERDown){
        //mvaWWInputs[ 0] = (float)massJJJERDown;
        mvaWWInputs[ 0] = (float)deltaEtaJJ;
        mvaWWInputs[ 1] = (float)deltaPhiJJ;
	mvaWWInputs[ 2] = (float)vJot1JERDown.Pt();
        mvaWWInputs[ 3] = (float)vJot2JERDown.Pt();
        mvaWWInputs[ 4] = (float)vJot1JERDown.Eta();
        mvaWWInputs[ 5] = (float)vJot2JERDown.Eta();
	mvaWWInputs[ 6] = (float)vW.Pt();
	mvaWWInputs[ 7] = (float)(vZ1l1+vZ1l2).Pt();
	mvaWWInputs[ 8] = (float)mtVV;
	mvaWWInputs[ 9] = (float)wzZep;
	mvaWWInputs[10] = (float)vvZepSS[0];
	mvaWWInputs[11] = (float)vvZepSS[1];
	mvaWWInputs[12] = (float)maxLeptonZep;
	mvaWWInputs[13] = (float)TMath::Sqrt(TMath::Power(TMath::Abs(vJot1JERDown.Eta()-(vZ1l1+vZ1l2).Eta()),2)+TMath::Power(TMath::Abs(vJot1JERDown.DeltaPhi(vZ1l1+vZ1l2)),2));
	mvaWWInputs[14] = (float)TMath::Sqrt(TMath::Power(TMath::Abs(vJot2JERDown.Eta()-(vZ1l1+vZ1l2).Eta()),2)+TMath::Power(TMath::Abs(vJot2JERDown.DeltaPhi(vZ1l1+vZ1l2)),2));
	mvaWWInputs[15] = (float)totSystemJERDown.Pt()/sumPtTotJERDown;
	mvaWWInputs[16] = (float)totSystemJERDown.Pt();
	mvaWWInputs[17] = (float)vZ1l1.Pt();
	mvaWWInputs[18] = (float)vZ1l2.Pt();
	mvaWWInputs[19] = (float)vZ1l1.Eta();
	mvaWWInputs[20] = (float)vZ1l2.Eta();
	mvaWWInputs[21] = (float)dphill;
	mvaWWInputs[22] = (float)drll;
	mvaWWInputs[23] = (float)(vZ1l1+vZ1l2).M();
	mvaWWInputs[24] = (float)(vZ1l1.Pt()*vZ1l2.Pt())/(vJot1JERDown.Pt()*vJot2JERDown.Pt()); 
        bdtWWValueJERDown[0] = TMath::Min(theReaderWW->EvaluateMVA("BDT"),0.999);
        //const std::vector< Float_t > mvaV = theReaderWW->EvaluateMulticlass("BDT");
	//bdtWWValueJERDown[0] = TMath::Min(mvaV[2],0.999);
	//bdtWWValueJERDown[1] = TMath::Min(mvaV[1],0.999);
	//bdtWWValueJERDown[2] = TMath::Min(mvaV[0],0.999);
      }

      double bdtWZValue = 0.0, bdtWZValueJESUp = 0.0, bdtWZValueJESDown = 0.0, bdtWZValueJERUp = 0.0, bdtWZValueJERDown = 0.0;
      if(passEWKWZSel){
        mvaWZInputs[0]  = (float)massJJ;
        mvaWZInputs[1]  = (float)deltaEtaJJ;
        mvaWZInputs[2]  = (float)deltaPhiJJ;
	mvaWZInputs[3]  = (float)vJot1.Pt();
        mvaWZInputs[4]  = (float)vJot2.Pt();
        mvaWZInputs[5]  = (float)vJot1.Eta();
        mvaWZInputs[6]  = (float)TMath::Abs(vWln.Eta()-(vZ1l1+vZ1l2).Eta());
	mvaWZInputs[7]  = (float)wzZep;
	mvaWZInputs[8]  = (float)vvZepSS[0];
	mvaWZInputs[9]  = (float)vvZepSS[1];
	mvaWZInputs[10] = (float)vvZepSS[2];
	mvaWZInputs[11] = (float)TMath::Sqrt(TMath::Power(TMath::Abs(vJot1.Eta()-(vZ1l1+vZ1l2).Eta()),2)+TMath::Power(TMath::Abs(vJot1.DeltaPhi(vZ1l1+vZ1l2)),2));
	mvaWZInputs[12] = (float)totSystem.Pt()/sumPtTot;
        bdtWZValue = TMath::Min(theReaderWZ->EvaluateMVA("BDT"),0.999);
      }

      if(passEWKWZSelJESUp){
        mvaWZInputs[0]  = (float)massJJJESUp;
        mvaWZInputs[1]  = (float)deltaEtaJJUp;
        mvaWZInputs[2]  = (float)deltaPhiJJUp;
	mvaWZInputs[3]  = (float)vJot1JESUp.Pt();
        mvaWZInputs[4]  = (float)vJot2JESUp.Pt();
        mvaWZInputs[5]  = (float)vJot1JESUp.Eta();
        mvaWZInputs[6]  = (float)TMath::Abs(vWln.Eta()-(vZ1l1+vZ1l2).Eta());
	mvaWZInputs[7]  = (float)wzZepUp;
	mvaWZInputs[8]  = (float)vvZepSSUp[0];
	mvaWZInputs[9]  = (float)vvZepSSUp[1];
	mvaWZInputs[10] = (float)vvZepSSUp[2];
	mvaWZInputs[11] = (float)TMath::Sqrt(TMath::Power(TMath::Abs(vJot1JESUp.Eta()-(vZ1l1+vZ1l2).Eta()),2)+TMath::Power(TMath::Abs(vJot1JESUp.DeltaPhi(vZ1l1+vZ1l2)),2));
	mvaWZInputs[12] = (float)totSystemJESUp.Pt()/sumPtTotJESUp;
        bdtWZValueJESUp = TMath::Min(theReaderWZ->EvaluateMVA("BDT"),0.999);
      }

      if(passEWKWZSelJESDown){
        mvaWZInputs[0]  = (float)massJJJESDown;
        mvaWZInputs[1]  = (float)deltaEtaJJDown;
        mvaWZInputs[2]  = (float)deltaPhiJJDown;
	mvaWZInputs[3]  = (float)vJot1JESDown.Pt();
        mvaWZInputs[4]  = (float)vJot2JESDown.Pt();
        mvaWZInputs[5]  = (float)vJot1JESDown.Eta();
        mvaWZInputs[6]  = (float)TMath::Abs(vWln.Eta()-(vZ1l1+vZ1l2).Eta());
	mvaWZInputs[7]  = (float)wzZepDown;
	mvaWZInputs[8]  = (float)vvZepSSDown[0];
	mvaWZInputs[9]  = (float)vvZepSSDown[1];
	mvaWZInputs[10] = (float)vvZepSSDown[2];
	mvaWZInputs[11] = (float)TMath::Sqrt(TMath::Power(TMath::Abs(vJot1JESDown.Eta()-(vZ1l1+vZ1l2).Eta()),2)+TMath::Power(TMath::Abs(vJot1JESDown.DeltaPhi(vZ1l1+vZ1l2)),2));
	mvaWZInputs[12] = (float)totSystemJESDown.Pt()/sumPtTotJESDown;
        bdtWZValueJESDown = TMath::Min(theReaderWZ->EvaluateMVA("BDT"),0.999);
      }
      if(passEWKWZSelJERUp){
        mvaWZInputs[0]  = (float)massJJJERUp;
        mvaWZInputs[1]  = (float)deltaEtaJJ;
        mvaWZInputs[2]  = (float)deltaPhiJJ;
	mvaWZInputs[3]  = (float)vJot1JERUp.Pt();
        mvaWZInputs[4]  = (float)vJot2JERUp.Pt();
        mvaWZInputs[5]  = (float)vJot1JERUp.Eta();
        mvaWZInputs[6]  = (float)TMath::Abs(vWln.Eta()-(vZ1l1+vZ1l2).Eta());
	mvaWZInputs[7]  = (float)wzZep;
	mvaWZInputs[8]  = (float)vvZepSS[0];
	mvaWZInputs[9]  = (float)vvZepSS[1];
	mvaWZInputs[10] = (float)vvZepSS[2];
	mvaWZInputs[11] = (float)TMath::Sqrt(TMath::Power(TMath::Abs(vJot1JERUp.Eta()-(vZ1l1+vZ1l2).Eta()),2)+TMath::Power(TMath::Abs(vJot1JERUp.DeltaPhi(vZ1l1+vZ1l2)),2));
	mvaWZInputs[12] = (float)totSystemJERUp.Pt()/sumPtTotJERUp;
        bdtWZValueJERUp = TMath::Min(theReaderWZ->EvaluateMVA("BDT"),0.999);
      }

      if(passEWKWZSelJERDown){
        mvaWZInputs[0]  = (float)massJJJERDown;
        mvaWZInputs[1]  = (float)deltaEtaJJ;
        mvaWZInputs[2]  = (float)deltaPhiJJ;
	mvaWZInputs[3]  = (float)vJot1JERDown.Pt();
        mvaWZInputs[4]  = (float)vJot2JERDown.Pt();
        mvaWZInputs[5]  = (float)vJot1JERDown.Eta();
        mvaWZInputs[6]  = (float)TMath::Abs(vWln.Eta()-(vZ1l1+vZ1l2).Eta());
	mvaWZInputs[7]  = (float)wzZep;
	mvaWZInputs[8]  = (float)vvZepSS[0];
	mvaWZInputs[9]  = (float)vvZepSS[1];
	mvaWZInputs[10] = (float)vvZepSS[2];
	mvaWZInputs[11] = (float)TMath::Sqrt(TMath::Power(TMath::Abs(vJot1JERDown.Eta()-(vZ1l1+vZ1l2).Eta()),2)+TMath::Power(TMath::Abs(vJot1JERDown.DeltaPhi(vZ1l1+vZ1l2)),2));
	mvaWZInputs[12] = (float)totSystemJERDown.Pt()/sumPtTotJERDown;
        bdtWZValueJERDown = TMath::Min(theReaderWZ->EvaluateMVA("BDT"),0.999);
      }

      if(theCategory == kPlotEWKSSWW && (fidAna == 2 || fidAna == 3) &&
         thePandaFlat.genLep1Pt > 20 && TMath::Abs(thePandaFlat.genLep1Eta) < 2.5 && TMath::Abs(thePandaFlat.genLep1PdgId) != 15 &&
	 thePandaFlat.genLep2Pt > 20 && TMath::Abs(thePandaFlat.genLep2Eta) < 2.5 && TMath::Abs(thePandaFlat.genLep2PdgId) != 15 && 
	 thePandaFlat.genJet1Pt > 50 && TMath::Abs(thePandaFlat.genJet1Eta) < 5.0 &&
	 thePandaFlat.genJet2Pt > 50 && TMath::Abs(thePandaFlat.genJet2Eta) < 5.0){
        TLorentzVector vGen1,vGen2;
        double thePDGMass = mass_mu;
        if(abs(thePandaFlat.genLep1PdgId)==11) thePDGMass = mass_el;
        vGen1.SetPtEtaPhiM(thePandaFlat.genLep1Pt,thePandaFlat.genLep1Eta,thePandaFlat.genLep1Phi,thePDGMass);
        thePDGMass = mass_mu;
        if(abs(thePandaFlat.genLep2PdgId)==11) thePDGMass = mass_el;
        vGen2.SetPtEtaPhiM(thePandaFlat.genLep2Pt,thePandaFlat.genLep2Eta,thePandaFlat.genLep2Phi,thePDGMass);
	if((vGen1+vGen2).M() > 20){
	  if     (fidAna == 2){
            if     (thePandaFlat.genMjj >  500 && thePandaFlat.genMjj <=  800) theCategory = kPlotSignal0;
	    else if(thePandaFlat.genMjj >  800 && thePandaFlat.genMjj <= 1200) theCategory = kPlotSignal1;
	    else if(thePandaFlat.genMjj > 1200 && thePandaFlat.genMjj <= 1800) theCategory = kPlotSignal2;
	    else if(thePandaFlat.genMjj > 1800)                                theCategory = kPlotSignal3;
	  }
	  else if(fidAna == 3){
            if     ((vGen1+vGen2).M() >  xbinsMLL[0] && (vGen1+vGen2).M() <= xbinsMLL[1]) theCategory = kPlotSignal0;
	    else if((vGen1+vGen2).M() >  xbinsMLL[1] && (vGen1+vGen2).M() <= xbinsMLL[2]) theCategory = kPlotSignal1;
	    else if((vGen1+vGen2).M() >  xbinsMLL[2] && (vGen1+vGen2).M() <= xbinsMLL[3]) theCategory = kPlotSignal2;
	    else if((vGen1+vGen2).M() >  xbinsMLL[3])                                     theCategory = kPlotSignal3;
          }
        } // mll>20
      }

      int qTotCat = 0; if(qTot<0) qTotCat = 1;

      if(dataCardSel >= 0) histo[dataCardSel+ 0][theCategory]->Fill(TMath::Min(massJJ,xbinsMJJ[nBinMJJ]-0.0001),totalWeight);
      if(dataCardSel >= 0) histo[dataCardSel+ 5][theCategory]->Fill(TMath::Min(deltaEtaJJ,7.999),totalWeight);
      if(dataCardSel >= 0) histo[dataCardSel+10][theCategory]->Fill((double)(lepType+4*qTotCat),totalWeight);
      if(dataCardSel >= 0) histo[dataCardSel+15][theCategory]->Fill(TMath::Min(vJot1.Pt(),449.999),totalWeight);
      if(dataCardSel >= 0) histo[dataCardSel+15][theCategory]->Fill(TMath::Min(vJot2.Pt(),449.999),totalWeight);
      if(dataCardSel >= 0) histo[dataCardSel+20][theCategory]->Fill(vJot1.Eta(),totalWeight);
      if(dataCardSel >= 0) histo[dataCardSel+20][theCategory]->Fill(vJot2.Eta(),totalWeight);
      if(dataCardSel >= 0) histo[dataCardSel+25][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJot,5.499),totalWeight);
      if(passAllButOneSel[0])histo[lepType+ 30][theCategory]->Fill(TMath::Min(mllZ,499.999),totalWeight);
      if(passAllButOneSel[1])histo[lepType+ 33][theCategory]->Fill(TMath::Min(vMet.Pt(),199.999),totalWeight);
      if(passAllButOneSel[2])histo[lepType+ 36][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJot,5.499),totalWeight);
      if(passAllButOneSel[3])histo[lepType+ 39][theCategory]->Fill(TMath::Min(deltaEtaJJ,7.999),totalWeight);
      if(passAllButOneSel[4])histo[lepType+ 42][theCategory]->Fill(TMath::Min(massJJ,1999.999),totalWeight);
      if(passAllButOneSel[5])histo[lepType+ 45][theCategory]->Fill(TMath::Min(maxLeptonZep,0.999),totalWeight);
      if(passAllButOneSel[6])histo[lepType+ 48][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNMBtags,4.499),totalWeight);
      if(passAllButOneSel[7])histo[lepType+ 51][theCategory]->Fill(TMath::Min((double)thePandaFlat.nTau,4.499),totalWeight);
      if(passPresel)         histo[         54][theCategory]->Fill(TMath::Min(massJJ,2499.999),totalWeight);
      if(passPresel)         histo[         55][theCategory]->Fill(TMath::Min(deltaEtaJJ,7.999),totalWeight);
      if(passPresel)         histo[         56][theCategory]->Fill(TMath::Min(maxLeptonZep,0.999),totalWeight);
      if(passPresel)         histo[         57][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNBtags,4.499),totalWeight);
      if(passPresel)         histo[         58][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNMBtags,4.499),totalWeight);
      if(passPresel && thePandaFlat.jetNBtags > 0)
                             histo[         59][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNMBtags,4.499),totalWeight);
      if(passPresel)         histo[         60][theCategory]->Fill(TMath::Min(vJot1.Pt(),449.999),totalWeight);
      if(passPresel)         histo[         60][theCategory]->Fill(TMath::Min(vJot2.Pt(),449.999),totalWeight);
      if(passPresel)         histo[         61][theCategory]->Fill(vJot1.Eta(),totalWeight);
      if(passPresel)         histo[         61][theCategory]->Fill(vJot2.Eta(),totalWeight);
      if(passPresel)         histo[         62][theCategory]->Fill(TMath::Min(vZ1l1.Pt(),219.999),totalWeight);
      if(passPresel)         histo[         62][theCategory]->Fill(TMath::Min(vZ1l2.Pt(),219.999),totalWeight);
      if(passPresel)         histo[         63][theCategory]->Fill(TMath::Abs(vZ1l1.Eta()),totalWeight);
      if(passPresel)         histo[         63][theCategory]->Fill(TMath::Abs(vZ1l2.Eta()),totalWeight);
      if(passPresel)         histo[         64][theCategory]->Fill(TMath::Max((double)TMath::Max(thePandaFlat.jotCSV[0],thePandaFlat.jotCSV[1]),0.001),totalWeight);
      if(passPresel)         histo[         65][theCategory]->Fill(TMath::Max((double)TMath::Min(thePandaFlat.jotCSV[0],thePandaFlat.jotCSV[1]),0.001),totalWeight);
      if(passWWSel)          histo[         66][theCategory]->Fill(TMath::Min(mllZ,xbinsMLL[nBinMLL]-0.0001),totalWeight);
      if(passBtagSel)        histo[         67][theCategory]->Fill(TMath::Min(mllZ,xbinsMLL[nBinMLL]-0.0001),totalWeight);
      if(passWWSel)          histo[lepType+ 68][theCategory]->Fill(TMath::Min(vZ1l1.Pt(),219.999),totalWeight);
      if(passWWSel)          histo[lepType+ 71][theCategory]->Fill(TMath::Min(vZ1l2.Pt(),219.999),totalWeight);
      if(passZSel)           histo[lepType+ 74][theCategory]->Fill(TMath::Min(mllZ,219.999),totalWeight);
      if(passEWKWZSel)       histo[         77][theCategory]->Fill(TMath::Max(-0.999, TMath::Min(bdtWZValue,0.999)),totalWeight);
      if(passEWKWZSel)       histo[         78][theCategory]->Fill(TMath::Min(mtVV,999.999),totalWeight);
      if(passQCDSel >= 0)    histo[passQCDSel+79][theCategory]->Fill(massJJ,totalWeight);
      if(passQCDSel >= 0)    histo[passQCDSel+84][theCategory]->Fill(TMath::Min(deltaEtaJJ,7.999),totalWeight);
      if(passWWSel)          histo[         89][theCategory]->Fill(TMath::Max(-0.999, TMath::Min(bdtWWValue[0],0.999)),totalWeight);
      if(passBtagSel)        histo[         90][theCategory]->Fill(TMath::Max(-0.999, TMath::Min(bdtWWValue[0],0.999)),totalWeight);
      //if(passWWSel) {
      //  double theBDTWW =0; int BDTCat = -1;
      //  if     (bdtWWValue[0] > bdtWWValue[1] && bdtWWValue[0] > bdtWWValue[2]) {theBDTWW = bdtWWValue[0]; BDTCat = 0;}
      //  else if(bdtWWValue[1] > bdtWWValue[0] && bdtWWValue[1] > bdtWWValue[2]) {theBDTWW = bdtWWValue[1]; BDTCat = 1;}
      //  else if(bdtWWValue[2] > bdtWWValue[0] && bdtWWValue[2] > bdtWWValue[1]) {theBDTWW = bdtWWValue[2]; BDTCat = 2;}
      //  else printf("IMPOSSIBLE\n");
      //  histo[83+BDTCat][theCategory]->Fill(TMath::Max(0.001, TMath::Min(theBDTWW,0.999)),totalWeight);
      //}

      if((theCategory == kPlotData && passEWKWZSel && debug == 1) || debug == 2){
        printf("DATA %d %d %llu | %d %d | %d -> %d %d %d %d %d %d %d %d %d | %.1f %.1f %.1f %.1f %.2f | %.1f %.1f %.1f %d | %.2f %.2f %.2f %.2f %.2f %.2f / %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",
	thePandaFlat.runNumber,thePandaFlat.lumiNumber,thePandaFlat.eventNumber,theCategory,lepType,
	passEWKWZSel,passSel[0],passSel[1],passSel[2],passSel[3],passSel[4],passSel[5],passSel[6],passSel[7],passSel[8],
	mllZ,vMet.Pt(),deltaEtaJJ,massJJ,maxLeptonZep,
	fabs(mllZ-91.1876),mllmin,vWln.Pt(),whichWln,vJot1.Pt(),vJot1.Eta(),vJot1.Phi(),vJot2.Pt(),vJot2.Eta(),vJot2.Phi(),
	vLoose[0].Pt(),vLoose[0].Eta(),vLoose[0].Phi(),vLoose[1].Pt(),vLoose[1].Eta(),vLoose[1].Phi(),vLoose[2].Pt(),vLoose[2].Eta(),vLoose[2].Phi());
      }

      if(1){
        double MVAVar        = -1;
        double MVAVarJESUp   = -1;
        double MVAVarJESDown = -1;
        double MVAVarJERUp   = -1;
        double MVAVarJERDown = -1;
        if     (fidAna == 0 || fidAna == 2 || fidAna == 3){
          double typeSelAux0 = 0;
	  for(int ib=0; ib<nBinMLL; ib++){
	     if(TMath::Min(mllZ,xbinsMLL[nBinMLL]-0.001) < xbinsMLL[ib+1]) {typeSelAux0 = ib; break;}
	  }
          double typeSelAux1[5] = {0,0,0,0,0};
	  for(int ib=0; ib<nBinMJJ; ib++){
	     if(TMath::Min(massJJ       ,xbinsMJJ[nBinMJJ]-0.001) < xbinsMJJ[ib+1]) {typeSelAux1[0] = ib; break;}
	  }
	  for(int ib=0; ib<nBinMJJ; ib++){
	     if(TMath::Min(massJJJESUp  ,xbinsMJJ[nBinMJJ]-0.001) < xbinsMJJ[ib+1]) {typeSelAux1[1] = ib; break;}
	  }
	  for(int ib=0; ib<nBinMJJ; ib++){
	     if(TMath::Min(massJJJESDown,xbinsMJJ[nBinMJJ]-0.001) < xbinsMJJ[ib+1]) {typeSelAux1[2] = ib; break;}
	  }
	  for(int ib=0; ib<nBinMJJ; ib++){
	     if(TMath::Min(massJJJERUp  ,xbinsMJJ[nBinMJJ]-0.001) < xbinsMJJ[ib+1]) {typeSelAux1[3] = ib; break;}
	  }
	  for(int ib=0; ib<nBinMJJ; ib++){
	     if(TMath::Min(massJJJERDown,xbinsMJJ[nBinMJJ]-0.001) < xbinsMJJ[ib+1]) {typeSelAux1[4] = ib; break;}
	  }
          double typeSelAux1CR[5] = {0,0,0,0,0};
	  for(int ib=0; ib<nBinMJJCR; ib++){
	     if(TMath::Min(massJJ       ,xbinsMJJCR[nBinMJJCR]-0.001) < xbinsMJJCR[ib+1]) {typeSelAux1CR[0] = ib; break;}
	  }
	  for(int ib=0; ib<nBinMJJCR; ib++){
	     if(TMath::Min(massJJJESUp  ,xbinsMJJCR[nBinMJJCR]-0.001) < xbinsMJJCR[ib+1]) {typeSelAux1CR[1] = ib; break;}
	  }
	  for(int ib=0; ib<nBinMJJCR; ib++){
	     if(TMath::Min(massJJJESDown,xbinsMJJCR[nBinMJJCR]-0.001) < xbinsMJJCR[ib+1]) {typeSelAux1CR[2] = ib; break;}
	  }
	  for(int ib=0; ib<nBinMJJCR; ib++){
	     if(TMath::Min(massJJJERUp  ,xbinsMJJCR[nBinMJJCR]-0.001) < xbinsMJJCR[ib+1]) {typeSelAux1CR[3] = ib; break;}
	  }
	  for(int ib=0; ib<nBinMJJCR; ib++){
	     if(TMath::Min(massJJJERDown,xbinsMJJCR[nBinMJJCR]-0.001) < xbinsMJJCR[ib+1]) {typeSelAux1CR[4] = ib; break;}
	  }
          double bdtWZValueBin[5] = {0,0,0,0,0};
	  for(int ib=0; ib<nBinWZBDT; ib++){
	     if(bdtWZValue        < xbinsWZBDT[ib+1]) {bdtWZValueBin[0] = ib; break;}
	  }
	  for(int ib=0; ib<nBinWZBDT; ib++){
	     if(bdtWZValueJESUp   < xbinsWZBDT[ib+1]) {bdtWZValueBin[1] = ib; break;}
	  }
	  for(int ib=0; ib<nBinWZBDT; ib++){
	     if(bdtWZValueJESDown < xbinsWZBDT[ib+1]) {bdtWZValueBin[2] = ib; break;}
	  }
	  for(int ib=0; ib<nBinWZBDT; ib++){
	     if(bdtWZValueJERUp   < xbinsWZBDT[ib+1]) {bdtWZValueBin[3] = ib; break;}
	  }
	  for(int ib=0; ib<nBinWZBDT; ib++){
	     if(bdtWZValueJERDown < xbinsWZBDT[ib+1]) {bdtWZValueBin[4] = ib; break;}
	  }

          int whichBin = 0;
          if     (dataCardSel        == 0) MVAVar        = typeSelAux0 + nBinMLL*typeSelAux1[whichBin];
          else if(dataCardSel        == 1) MVAVar        = nBinMJJ*nBinMLL + typeSelAux1CR[whichBin];
          else if(dataCardSel        == 2) MVAVar        = nBinMJJ*nBinMLL +   nBinMJJCR + typeSelAux1CR[whichBin];
          else if(dataCardSel        == 3) MVAVar        = nBinMJJ*nBinMLL + 2*nBinMJJCR + typeSelAux1CR[whichBin];
          else if(dataCardSel        == 4) MVAVar        = nBinMJJ*nBinMLL + 3*nBinMJJCR + bdtWZValueBin[whichBin];

          whichBin = 1;
          if     (dataCardSelJESUp   == 0) MVAVarJESUp   = typeSelAux0 + nBinMLL*typeSelAux1[whichBin];
          else if(dataCardSelJESUp   == 1) MVAVarJESUp   = nBinMJJ*nBinMLL + typeSelAux1CR[whichBin];
          else if(dataCardSelJESUp   == 2) MVAVarJESUp   = nBinMJJ*nBinMLL +   nBinMJJCR + typeSelAux1CR[whichBin];
          else if(dataCardSelJESUp   == 3) MVAVarJESUp   = nBinMJJ*nBinMLL + 2*nBinMJJCR + typeSelAux1CR[whichBin];
          else if(dataCardSelJESUp   == 4) MVAVarJESUp   = nBinMJJ*nBinMLL + 3*nBinMJJCR + bdtWZValueBin[whichBin];

          whichBin = 2;
          if     (dataCardSelJESDown == 0) MVAVarJESDown = typeSelAux0 + nBinMLL*typeSelAux1[whichBin];
          else if(dataCardSelJESDown == 1) MVAVarJESDown = nBinMJJ*nBinMLL + typeSelAux1CR[whichBin];
          else if(dataCardSelJESDown == 2) MVAVarJESDown = nBinMJJ*nBinMLL +   nBinMJJCR + typeSelAux1CR[whichBin];
          else if(dataCardSelJESDown == 3) MVAVarJESDown = nBinMJJ*nBinMLL + 2*nBinMJJCR + typeSelAux1CR[whichBin];
          else if(dataCardSelJESDown == 4) MVAVarJESDown = nBinMJJ*nBinMLL + 3*nBinMJJCR + bdtWZValueBin[whichBin];

          whichBin = 3;
          if     (dataCardSelJERUp   == 0) MVAVarJERUp   = typeSelAux0 + nBinMLL*typeSelAux1[whichBin];
          else if(dataCardSelJERUp   == 1) MVAVarJERUp   = nBinMJJ*nBinMLL + typeSelAux1CR[whichBin];
          else if(dataCardSelJERUp   == 2) MVAVarJERUp   = nBinMJJ*nBinMLL +   nBinMJJCR + typeSelAux1CR[whichBin];
          else if(dataCardSelJERUp   == 3) MVAVarJERUp   = nBinMJJ*nBinMLL + 2*nBinMJJCR + typeSelAux1CR[whichBin];
          else if(dataCardSelJERUp   == 4) MVAVarJERUp   = nBinMJJ*nBinMLL + 3*nBinMJJCR + bdtWZValueBin[whichBin];

          whichBin = 4;
          if     (dataCardSelJERDown == 0) MVAVarJERDown = typeSelAux0 + nBinMLL*typeSelAux1[whichBin];
          else if(dataCardSelJERDown == 1) MVAVarJERDown = nBinMJJ*nBinMLL + typeSelAux1CR[whichBin];
          else if(dataCardSelJERDown == 2) MVAVarJERDown = nBinMJJ*nBinMLL +   nBinMJJCR + typeSelAux1CR[whichBin];
          else if(dataCardSelJERDown == 3) MVAVarJERDown = nBinMJJ*nBinMLL + 2*nBinMJJCR + typeSelAux1CR[whichBin];
          else if(dataCardSelJERDown == 4) MVAVarJERDown = nBinMJJ*nBinMLL + 3*nBinMJJCR + bdtWZValueBin[whichBin];
        }
        else if(fidAna == 1){
          double typeSelAux0 = 0;
	  for(int ib=0; ib<nBinMLL; ib++){
	     if(TMath::Min(mllZ,xbinsMLL[nBinMLL]-0.001) < xbinsMLL[ib+1]) {typeSelAux0 = ib; break;}
	  }
          double typeSelAux1[5] = {0,0,0,0,0};
	  for(int ib=0; ib<nBinMJJ; ib++){
	     if(TMath::Min(massJJ       ,xbinsMJJ[nBinMJJ]-0.001) < xbinsMJJ[ib+1]) {typeSelAux1[0] = ib; break;}
	  }
	  for(int ib=0; ib<nBinMJJ; ib++){
	     if(TMath::Min(massJJJESUp  ,xbinsMJJ[nBinMJJ]-0.001) < xbinsMJJ[ib+1]) {typeSelAux1[1] = ib; break;}
	  }
	  for(int ib=0; ib<nBinMJJ; ib++){
	     if(TMath::Min(massJJJESDown,xbinsMJJ[nBinMJJ]-0.001) < xbinsMJJ[ib+1]) {typeSelAux1[2] = ib; break;}
	  }
	  for(int ib=0; ib<nBinMJJ; ib++){
	     if(TMath::Min(massJJJERUp  ,xbinsMJJ[nBinMJJ]-0.001) < xbinsMJJ[ib+1]) {typeSelAux1[3] = ib; break;}
	  }
	  for(int ib=0; ib<nBinMJJ; ib++){
	     if(TMath::Min(massJJJERDown,xbinsMJJ[nBinMJJ]-0.001) < xbinsMJJ[ib+1]) {typeSelAux1[4] = ib; break;}
	  }
          double typeSelAux2[5] = {0,0,0,0,0};
          if     (massJJ        < 1000) typeSelAux2[0] = 0;
	  else if(massJJ        < 1500) typeSelAux2[0] = 1;
	  else if(massJJ        < 2000) typeSelAux2[0] = 2;
	  else                          typeSelAux2[0] = 3;
          if     (massJJJESUp   < 1000) typeSelAux2[1] = 0;
	  else if(massJJJESUp   < 1500) typeSelAux2[1] = 1;
	  else if(massJJJESUp   < 2000) typeSelAux2[1] = 2;
	  else                          typeSelAux2[1] = 3;
          if     (massJJJESDown < 1000) typeSelAux2[2] = 0;
	  else if(massJJJESDown < 1500) typeSelAux2[2] = 1;
	  else if(massJJJESDown < 2000) typeSelAux2[2] = 2;
	  else                          typeSelAux2[2] = 3;
          if     (massJJJERUp   < 1000) typeSelAux2[3] = 0;
	  else if(massJJJERUp   < 1500) typeSelAux2[3] = 1;
	  else if(massJJJERUp   < 2000) typeSelAux2[3] = 2;
	  else                          typeSelAux2[3] = 3;
          if     (massJJJERDown < 1000) typeSelAux2[4] = 0;
	  else if(massJJJERDown < 1500) typeSelAux2[4] = 1;
	  else if(massJJJERDown < 2000) typeSelAux2[4] = 2;
	  else                          typeSelAux2[4] = 3;
          double typeSelAux3[5] = {0,0,0,0,0};
          if     (deltaEtaJJ     < 4.0) typeSelAux3[0] = 0;
          else if(deltaEtaJJ     < 5.0) typeSelAux3[0] = 1;
	  else                          typeSelAux3[0] = 2;
          if     (deltaEtaJJUp   < 4.0) typeSelAux3[1] = 0;
          else if(deltaEtaJJUp   < 5.0) typeSelAux3[1] = 1;
	  else                          typeSelAux3[1] = 2;
          if     (deltaEtaJJDown < 4.0) typeSelAux3[2] = 0;
          else if(deltaEtaJJDown < 5.0) typeSelAux3[2] = 1;
	  else                          typeSelAux3[2] = 2;
          typeSelAux3[3] = typeSelAux3[0];
          typeSelAux3[4] = typeSelAux3[0];

          int whichBin = 0;
          if     (dataCardSel        == 0) MVAVar        = typeSelAux0 + nBinMLL*typeSelAux1[whichBin];
          else if(dataCardSel        == 1) MVAVar        = nBinMJJ*nBinMLL + typeSelAux1[whichBin];
          else if(dataCardSel        == 2) MVAVar        = nBinMJJ*nBinMLL + nBinMJJ + 0;
          else if(dataCardSel        == 3) MVAVar        = nBinMJJ*nBinMLL + nBinMJJ + 1;
          else if(dataCardSel        == 4) MVAVar        = nBinMJJ*nBinMLL + nBinMJJ + 2 + typeSelAux2[whichBin] + 4*typeSelAux3[whichBin];

          whichBin = 1;
          if     (dataCardSelJESUp   == 0) MVAVarJESUp   = typeSelAux0 + nBinMLL*typeSelAux1[whichBin];
          else if(dataCardSelJESUp   == 1) MVAVarJESUp   = nBinMJJ*nBinMLL + typeSelAux1[whichBin];
          else if(dataCardSelJESUp   == 2) MVAVarJESUp   = nBinMJJ*nBinMLL + nBinMJJ + 0;
          else if(dataCardSelJESUp   == 3) MVAVarJESUp   = nBinMJJ*nBinMLL + nBinMJJ + 1;
          else if(dataCardSelJESUp   == 4) MVAVarJESUp   = nBinMJJ*nBinMLL + nBinMJJ + 2 + typeSelAux2[whichBin] + 4*typeSelAux3[whichBin];

          whichBin = 2;
          if     (dataCardSelJESDown == 0) MVAVarJESDown = typeSelAux0 + nBinMLL*typeSelAux1[whichBin];
          else if(dataCardSelJESDown == 1) MVAVarJESDown = nBinMJJ*nBinMLL + typeSelAux1[whichBin];
          else if(dataCardSelJESDown == 2) MVAVarJESDown = nBinMJJ*nBinMLL + nBinMJJ + 0;
          else if(dataCardSelJESDown == 3) MVAVarJESDown = nBinMJJ*nBinMLL + nBinMJJ + 1;
          else if(dataCardSelJESDown == 4) MVAVarJESDown = nBinMJJ*nBinMLL + nBinMJJ + 2 + typeSelAux2[whichBin] + 4*typeSelAux3[whichBin];

          whichBin = 3;
          if     (dataCardSelJERUp   == 0) MVAVarJERUp   = typeSelAux0 + nBinMLL*typeSelAux1[whichBin];
          else if(dataCardSelJERUp   == 1) MVAVarJERUp   = nBinMJJ*nBinMLL + typeSelAux1[whichBin];
          else if(dataCardSelJERUp   == 2) MVAVarJERUp   = nBinMJJ*nBinMLL + nBinMJJ + 0;
          else if(dataCardSelJERUp   == 3) MVAVarJERUp   = nBinMJJ*nBinMLL + nBinMJJ + 1;
          else if(dataCardSelJERUp   == 4) MVAVarJERUp   = nBinMJJ*nBinMLL + nBinMJJ + 2 + typeSelAux2[whichBin] + 4*typeSelAux3[whichBin];

          whichBin = 4;
          if     (dataCardSelJERDown == 0) MVAVarJERDown = typeSelAux0 + nBinMLL*typeSelAux1[whichBin];
          else if(dataCardSelJERDown == 1) MVAVarJERDown = nBinMJJ*nBinMLL + typeSelAux1[whichBin];
          else if(dataCardSelJERDown == 2) MVAVarJERDown = nBinMJJ*nBinMLL + nBinMJJ + 0;
          else if(dataCardSelJERDown == 3) MVAVarJERDown = nBinMJJ*nBinMLL + nBinMJJ + 1;
          else if(dataCardSelJERDown == 4) MVAVarJERDown = nBinMJJ*nBinMLL + nBinMJJ + 2 + typeSelAux2[whichBin] + 4*typeSelAux3[whichBin];
        }
        else if(fidAna == 4){
          double typeSelAux0 = 0;
          if     (mllZ < 150) typeSelAux0 = 0;
          else if(mllZ < 300) typeSelAux0 = 1;
          else if(mllZ < 450) typeSelAux0 = 2;
          else if(mllZ < 600) typeSelAux0 = 3;
          else                typeSelAux0 = 4;
          double typeSelAux1[5] = {0,0,0,0,0};
          if     (massJJ        <  800) typeSelAux1[0] = 0;
	  else if(massJJ        < 1200) typeSelAux1[0] = 1;
	  else if(massJJ        < 1800) typeSelAux1[0] = 2;
	  else                          typeSelAux1[0] = 3; 
          if     (massJJJESUp   <  800) typeSelAux1[1] = 0;
	  else if(massJJJESUp   < 1200) typeSelAux1[1] = 1;
	  else if(massJJJESUp   < 1800) typeSelAux1[1] = 2;
	  else                          typeSelAux1[1] = 3; 
          if     (massJJJESDown <  800) typeSelAux1[2] = 0;
	  else if(massJJJESDown < 1200) typeSelAux1[2] = 1;
	  else if(massJJJESDown < 1800) typeSelAux1[2] = 2;
	  else                          typeSelAux1[2] = 3; 
          if     (massJJJERUp   <  800) typeSelAux1[3] = 0;
	  else if(massJJJERUp   < 1200) typeSelAux1[3] = 1;
	  else if(massJJJERUp   < 1800) typeSelAux1[3] = 2;
	  else                          typeSelAux1[3] = 3; 
          if     (massJJJERDown <  800) typeSelAux1[4] = 0;
	  else if(massJJJERDown < 1200) typeSelAux1[4] = 1;
	  else if(massJJJERDown < 1800) typeSelAux1[4] = 2;
	  else                          typeSelAux1[4] = 3; 

          double typeSelAux2[5] = {0,0,0,0,0};
          if     (mtVV <  300) typeSelAux2[0] = 0;
	  else if(mtVV <  600) typeSelAux2[0] = 1;
	  else                 typeSelAux2[0] = 2;
	  if(massJJ > 1200) typeSelAux2[0] += 3;
          if     (mtVVUp <  300) typeSelAux2[1] = 0;
	  else if(mtVVUp <  600) typeSelAux2[1] = 1;
	  else                   typeSelAux2[1] = 2;
	  if(massJJJESUp > 1200) typeSelAux2[1] += 3;
          if     (mtVVDown <  300) typeSelAux2[2] = 0;
	  else if(mtVVDown <  600) typeSelAux2[2] = 1;
	  else                     typeSelAux2[2] = 2;
	  if(massJJJESDown > 1200) typeSelAux2[2] += 3;
          typeSelAux2[3] = typeSelAux2[0];
          typeSelAux2[4] = typeSelAux2[0];

          int whichBin = 0;
          if     (dataCardSel        == 0) MVAVar        = typeSelAux0 + 5*typeSelAux1[whichBin];
          else if(dataCardSel        == 1) MVAVar        = 20 + typeSelAux1[whichBin];
          else if(dataCardSel        == 2) MVAVar        = 24;
          else if(dataCardSel        == 3) MVAVar        = 25;
          else if(dataCardSel        == 4) MVAVar        = 26 + typeSelAux2[whichBin];

          whichBin = 1;
          if     (dataCardSelJESUp   == 0) MVAVarJESUp   = typeSelAux0 + 5*typeSelAux1[whichBin];
          else if(dataCardSelJESUp   == 1) MVAVarJESUp   = 20 + typeSelAux1[whichBin];
          else if(dataCardSelJESUp   == 2) MVAVarJESUp   = 24;
          else if(dataCardSelJESUp   == 3) MVAVarJESUp   = 25;
          else if(dataCardSelJESUp   == 4) MVAVarJESUp   = 26 + typeSelAux2[whichBin];

          whichBin = 2;
          if     (dataCardSelJESDown == 0) MVAVarJESDown = typeSelAux0 + 5*typeSelAux1[whichBin];
          else if(dataCardSelJESDown == 1) MVAVarJESDown = 20 + typeSelAux1[whichBin];
          else if(dataCardSelJESDown == 2) MVAVarJESDown = 24;
          else if(dataCardSelJESDown == 3) MVAVarJESDown = 25;
          else if(dataCardSelJESDown == 4) MVAVarJESDown = 26 + typeSelAux2[whichBin];

          whichBin = 3;
          if     (dataCardSelJERUp   == 0) MVAVarJERUp   = typeSelAux0 + 5*typeSelAux1[whichBin];
          else if(dataCardSelJERUp   == 1) MVAVarJERUp   = 20 + typeSelAux1[whichBin];
          else if(dataCardSelJERUp   == 2) MVAVarJERUp   = 24;
          else if(dataCardSelJERUp   == 3) MVAVarJERUp   = 25;
          else if(dataCardSelJERUp   == 4) MVAVarJERUp   = 26 + typeSelAux2[whichBin];

          whichBin = 4;
          if     (dataCardSelJERDown == 0) MVAVarJERDown = typeSelAux0 + 5*typeSelAux1[whichBin];
          else if(dataCardSelJERDown == 1) MVAVarJERDown = 20 + typeSelAux1[whichBin];
          else if(dataCardSelJERDown == 2) MVAVarJERDown = 24;
          else if(dataCardSelJERDown == 3) MVAVarJERDown = 25;
          else if(dataCardSelJERDown == 4) MVAVarJERDown = 26 + typeSelAux2[whichBin];

	  if(MVAVar >= 32) printf("Problem with MVAVar %f %f %f %f %d\n",MVAVar,typeSelAux0,typeSelAux1[0],typeSelAux2[0],dataCardSel);
	}
        else if(fidAna == 5){
          double bdtWWValueBin[5] = {0,0,0,0,0};
	  for(int ib=0; ib<nBinWWBDT; ib++){
	     if(bdtWWValue[0]        < xbinsWWBDT[ib+1]) {bdtWWValueBin[0] = ib; break;}
	  }
	  for(int ib=0; ib<nBinWWBDT; ib++){
	     if(bdtWWValueJESUp[0]   < xbinsWWBDT[ib+1]) {bdtWWValueBin[1] = ib; break;}
	  }
	  for(int ib=0; ib<nBinWWBDT; ib++){
	     if(bdtWWValueJESDown[0] < xbinsWWBDT[ib+1]) {bdtWWValueBin[2] = ib; break;}
	  }
	  for(int ib=0; ib<nBinWWBDT; ib++){
	     if(bdtWWValueJERUp[0]   < xbinsWWBDT[ib+1]) {bdtWWValueBin[3] = ib; break;}
	  }
	  for(int ib=0; ib<nBinWWBDT; ib++){
	     if(bdtWWValueJERDown[0] < xbinsWWBDT[ib+1]) {bdtWWValueBin[4] = ib; break;}
	  }
          double typeSelAux1[5] = {0,0,0,0,0};
	  for(int ib=0; ib<nBinMJJ; ib++){
	     if(TMath::Min(massJJ       ,xbinsMJJ[nBinMJJ]-0.001) < xbinsMJJ[ib+1]) {typeSelAux1[0] = ib; break;}
	  }
	  for(int ib=0; ib<nBinMJJ; ib++){
	     if(TMath::Min(massJJJESUp  ,xbinsMJJ[nBinMJJ]-0.001) < xbinsMJJ[ib+1]) {typeSelAux1[1] = ib; break;}
	  }
	  for(int ib=0; ib<nBinMJJ; ib++){
	     if(TMath::Min(massJJJESDown,xbinsMJJ[nBinMJJ]-0.001) < xbinsMJJ[ib+1]) {typeSelAux1[2] = ib; break;}
	  }
	  for(int ib=0; ib<nBinMJJ; ib++){
	     if(TMath::Min(massJJJERUp  ,xbinsMJJ[nBinMJJ]-0.001) < xbinsMJJ[ib+1]) {typeSelAux1[3] = ib; break;}
	  }
	  for(int ib=0; ib<nBinMJJ; ib++){
	     if(TMath::Min(massJJJERDown,xbinsMJJ[nBinMJJ]-0.001) < xbinsMJJ[ib+1]) {typeSelAux1[4] = ib; break;}
	  }
          double typeSelAux1CR[5] = {0,0,0,0,0};
	  for(int ib=0; ib<nBinMJJCR; ib++){
	     if(TMath::Min(massJJ       ,xbinsMJJCR[nBinMJJCR]-0.001) < xbinsMJJCR[ib+1]) {typeSelAux1CR[0] = ib; break;}
	  }
	  for(int ib=0; ib<nBinMJJCR; ib++){
	     if(TMath::Min(massJJJESUp  ,xbinsMJJCR[nBinMJJCR]-0.001) < xbinsMJJCR[ib+1]) {typeSelAux1CR[1] = ib; break;}
	  }
	  for(int ib=0; ib<nBinMJJCR; ib++){
	     if(TMath::Min(massJJJESDown,xbinsMJJCR[nBinMJJCR]-0.001) < xbinsMJJCR[ib+1]) {typeSelAux1CR[2] = ib; break;}
	  }
	  for(int ib=0; ib<nBinMJJCR; ib++){
	     if(TMath::Min(massJJJERUp  ,xbinsMJJCR[nBinMJJCR]-0.001) < xbinsMJJCR[ib+1]) {typeSelAux1CR[3] = ib; break;}
	  }
	  for(int ib=0; ib<nBinMJJCR; ib++){
	     if(TMath::Min(massJJJERDown,xbinsMJJCR[nBinMJJCR]-0.001) < xbinsMJJCR[ib+1]) {typeSelAux1CR[4] = ib; break;}
	  }
          double typeSelAux2[5] = {0,0,0,0,0};
          if     (massJJ        < 1000) typeSelAux2[0] = 0;
	  else if(massJJ        < 1500) typeSelAux2[0] = 1;
	  else if(massJJ        < 2000) typeSelAux2[0] = 2;
	  else                          typeSelAux2[0] = 3; 
          if     (massJJJESUp   < 1000) typeSelAux2[1] = 0;
	  else if(massJJJESUp   < 1500) typeSelAux2[1] = 1;
	  else if(massJJJESUp   < 2000) typeSelAux2[1] = 2;
	  else                          typeSelAux2[1] = 3; 
          if     (massJJJESDown < 1000) typeSelAux2[2] = 0;
	  else if(massJJJESDown < 1500) typeSelAux2[2] = 1;
	  else if(massJJJESDown < 2000) typeSelAux2[2] = 2;
	  else                          typeSelAux2[2] = 3;
          if     (massJJJERUp   < 1000) typeSelAux2[3] = 0;
	  else if(massJJJERUp   < 1500) typeSelAux2[3] = 1;
	  else if(massJJJERUp   < 2000) typeSelAux2[3] = 2;
	  else                          typeSelAux2[3] = 3; 
          if     (massJJJERDown < 1000) typeSelAux2[4] = 0;
	  else if(massJJJERDown < 1500) typeSelAux2[4] = 1;
	  else if(massJJJERDown < 2000) typeSelAux2[4] = 2;
	  else                          typeSelAux2[4] = 3;
          double typeSelAux3[5] = {0,0,0,0,0};
          if     (deltaEtaJJ     < 4.0) typeSelAux3[0] = 0;
          else if(deltaEtaJJ     < 5.0) typeSelAux3[0] = 1;
	  else                          typeSelAux3[0] = 2;
          if     (deltaEtaJJUp   < 4.0) typeSelAux3[1] = 0;
          else if(deltaEtaJJUp   < 5.0) typeSelAux3[1] = 1;
	  else                          typeSelAux3[1] = 2;
          if     (deltaEtaJJDown < 4.0) typeSelAux3[2] = 0;
          else if(deltaEtaJJDown < 5.0) typeSelAux3[2] = 1;
	  else                          typeSelAux3[2] = 2;
          typeSelAux3[3] = typeSelAux3[0];
          typeSelAux3[4] = typeSelAux3[0];

          int whichBin = 0;
          if     (dataCardSel        == 0) MVAVar        = typeSelAux1CR[whichBin] + nBinMJJCR*bdtWWValueBin[whichBin];
          else if(dataCardSel        == 1) MVAVar        = nBinMJJCR*nBinWWBDT + bdtWWValueBin[whichBin];
          else if(dataCardSel        == 2) MVAVar        = nBinMJJCR*nBinWWBDT + nBinWWBDT + typeSelAux1CR[whichBin];
          else if(dataCardSel        == 3) MVAVar        = nBinMJJCR*nBinWWBDT + nBinWWBDT +   nBinMJJCR + typeSelAux1CR[whichBin];
          else if(dataCardSel        == 4) MVAVar        = nBinMJJCR*nBinWWBDT + nBinWWBDT + 2*nBinMJJCR + typeSelAux2[whichBin] + 4*typeSelAux3[whichBin];

          whichBin = 1;
          if     (dataCardSelJESUp   == 0) MVAVarJESUp   = typeSelAux1CR[whichBin] + nBinMJJCR*bdtWWValueBin[whichBin];
          else if(dataCardSelJESUp   == 1) MVAVarJESUp   = nBinMJJCR*nBinWWBDT + bdtWWValueBin[whichBin];
          else if(dataCardSelJESUp   == 2) MVAVarJESUp   = nBinMJJCR*nBinWWBDT + nBinWWBDT + typeSelAux1CR[whichBin];
          else if(dataCardSelJESUp   == 3) MVAVarJESUp   = nBinMJJCR*nBinWWBDT + nBinWWBDT +   nBinMJJCR + typeSelAux1CR[whichBin];
          else if(dataCardSelJESUp   == 4) MVAVarJESUp   = nBinMJJCR*nBinWWBDT + nBinWWBDT + 2*nBinMJJCR + typeSelAux2[whichBin] + 4*typeSelAux3[whichBin];

          whichBin = 2;
          if     (dataCardSelJESDown == 0) MVAVarJESDown = typeSelAux1CR[whichBin] + nBinMJJCR*bdtWWValueBin[whichBin];
          else if(dataCardSelJESDown == 1) MVAVarJESDown = nBinMJJCR*nBinWWBDT + bdtWWValueBin[whichBin];
          else if(dataCardSelJESDown == 2) MVAVarJESDown = nBinMJJCR*nBinWWBDT + nBinWWBDT + typeSelAux1CR[whichBin];
          else if(dataCardSelJESDown == 3) MVAVarJESDown = nBinMJJCR*nBinWWBDT + nBinWWBDT +   nBinMJJCR + typeSelAux1CR[whichBin];
          else if(dataCardSelJESDown == 4) MVAVarJESDown = nBinMJJCR*nBinWWBDT + nBinWWBDT + 2*nBinMJJCR + typeSelAux2[whichBin] + 4*typeSelAux3[whichBin];

          whichBin = 3;
          if     (dataCardSelJERUp   == 0) MVAVarJERUp   = typeSelAux1CR[whichBin] + nBinMJJCR*bdtWWValueBin[whichBin];
          else if(dataCardSelJERUp   == 1) MVAVarJERUp   = nBinMJJCR*nBinWWBDT + bdtWWValueBin[whichBin];
          else if(dataCardSelJERUp   == 2) MVAVarJERUp   = nBinMJJCR*nBinWWBDT + nBinWWBDT + typeSelAux1CR[whichBin];
          else if(dataCardSelJERUp   == 3) MVAVarJERUp   = nBinMJJCR*nBinWWBDT + nBinWWBDT +   nBinMJJCR + typeSelAux1CR[whichBin];
          else if(dataCardSelJERUp   == 4) MVAVarJERUp   = nBinMJJCR*nBinWWBDT + nBinWWBDT + 2*nBinMJJCR + typeSelAux2[whichBin] + 4*typeSelAux3[whichBin];

          whichBin = 4;
          if     (dataCardSelJERDown == 0) MVAVarJERDown = typeSelAux1CR[whichBin] + nBinMJJCR*bdtWWValueBin[whichBin];
          else if(dataCardSelJERDown == 1) MVAVarJERDown = nBinMJJCR*nBinWWBDT + bdtWWValueBin[whichBin];
          else if(dataCardSelJERDown == 2) MVAVarJERDown = nBinMJJCR*nBinWWBDT + nBinWWBDT + typeSelAux1CR[whichBin];
          else if(dataCardSelJERDown == 3) MVAVarJERDown = nBinMJJCR*nBinWWBDT + nBinWWBDT +   nBinMJJCR + typeSelAux1CR[whichBin];
          else if(dataCardSelJERDown == 4) MVAVarJERDown = nBinMJJCR*nBinWWBDT + nBinWWBDT + 2*nBinMJJCR + typeSelAux2[whichBin] + 4*typeSelAux3[whichBin];
        }

        // Avoid QCD scale weights that are anomalous high
        double maxQCDscale = (TMath::Abs(thePandaFlat.scale[0])+TMath::Abs(thePandaFlat.scale[1])+TMath::Abs(thePandaFlat.scale[2])+
	                      TMath::Abs(thePandaFlat.scale[3])+TMath::Abs(thePandaFlat.scale[4])+TMath::Abs(thePandaFlat.scale[5]))/6.0;
        if(maxQCDscale == 0) maxQCDscale = 1;

        double sf_ewkcorrvv_unc = 1.0; double sf_ewkcorrzz_unc = 1.0; double sf_ggcorrzz_unc = 1.0; double sf_corrwzzz_unc = 1.0;
	//if(theCategory == kPlotWZ) sf_ewkcorrvv_unc = 1.02;
	//if(theCategory == kPlotZZ && infileName_[ifile].Contains("qqZZ") == true) sf_ewkcorrzz_unc = thePandaFlat.sf_zzUnc;
	//else if(theCategory == kPlotZZ) sf_ggcorrzz_unc = 1.10;
	if((theCategory == kPlotEWKSSWW || theCategory == kPlotEWKSSWW_dim8) && thePandaFlat.genMjj > 500) sf_ewkcorrvv_unc = hWW_KF_CMSUp->GetBinContent(hWW_KF_CMSUp->GetXaxis()->FindFixBin(TMath::Min(thePandaFlat.genMjj,1999.999f)))/
	                                                                                     hWW_KF_CMS  ->GetBinContent(hWW_KF_CMS  ->GetXaxis()->FindFixBin(TMath::Min(thePandaFlat.genMjj,1999.999f)));
	if((theCategory == kPlotEWKWZ || theCategory == kPlotEWKWZ_dim8) && thePandaFlat.genMjj > 500) sf_ewkcorrvv_unc = hWZ_KF_CMSUp->GetBinContent(hWZ_KF_CMSUp->GetXaxis()->FindFixBin(TMath::Min(thePandaFlat.genMjj,2999.999f)))/
	                                                                                   hWZ_KF_CMS  ->GetBinContent(hWZ_KF_CMS  ->GetXaxis()->FindFixBin(TMath::Min(thePandaFlat.genMjj,2999.999f)));

        if     (theCategory == kPlotData && dataCardSel >= 0){
          histo_Baseline[theCategory]->Fill(MVAVar,totalWeight);
        }
        else if(theCategory != kPlotData){
	  if(dataCardSel >= 0) {
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
            histo_WSBoundingUp   [theCategory]->Fill(MVAVar,totalWeight*effWSUnc);
            histo_WSBoundingDown [theCategory]->Fill(MVAVar,totalWeight/effWSUnc);
	    histo_EWKCorrVVUp    [theCategory]->Fill(MVAVar,totalWeight*sf_ewkcorrvv_unc);
	    histo_EWKCorrVVDown  [theCategory]->Fill(MVAVar,totalWeight/sf_ewkcorrvv_unc);
	    histo_EWKqqZZCorrUp  [theCategory]->Fill(MVAVar,totalWeight*sf_ewkcorrzz_unc);
	    histo_EWKqqZZCorrDown[theCategory]->Fill(MVAVar,totalWeight/sf_ewkcorrzz_unc);
	    histo_ggZZCorrUp     [theCategory]->Fill(MVAVar,totalWeight*sf_ggcorrzz_unc);
	    histo_ggZZCorrDown   [theCategory]->Fill(MVAVar,totalWeight/sf_ggcorrzz_unc);
	    if(vLoose.size() == 2){
	      histo_WZTauHUp     [theCategory]->Fill(MVAVar,totalWeight*syst_WZl[0]);
	      histo_WZTauHDown   [theCategory]->Fill(MVAVar,totalWeight/syst_WZl[0]);
	      histo_WZTauLUp     [theCategory]->Fill(MVAVar,totalWeight*syst_WZl[1]);
	      histo_WZTauLDown   [theCategory]->Fill(MVAVar,totalWeight/syst_WZl[1]);
	    }
	    else {
	      histo_WZTauHUp     [theCategory]->Fill(MVAVar,totalWeight);
	      histo_WZTauHDown   [theCategory]->Fill(MVAVar,totalWeight);
	      histo_WZTauLUp     [theCategory]->Fill(MVAVar,totalWeight);
	      histo_WZTauLDown   [theCategory]->Fill(MVAVar,totalWeight);
	    }
	      
	  }
	  for(int ny=0; ny<nYears; ny++){
	    if(ny == whichYear) {
              if(passSystCuts[JESUP])   histo_JESBoundingUp  [ny][theCategory]->Fill(MVAVarJESUp  ,totalWeight);
              if(passSystCuts[JESDOWN]) histo_JESBoundingDown[ny][theCategory]->Fill(MVAVarJESDown,totalWeight);
              if(passSystCuts[JERUP])   histo_JERBoundingUp  [ny][theCategory]->Fill(MVAVarJERUp  ,totalWeight);
              if(passSystCuts[JERDOWN]) histo_JERBoundingDown[ny][theCategory]->Fill(MVAVarJERDown,totalWeight);
            } else {
              if(dataCardSel >= 0) histo_JESBoundingUp  [ny][theCategory]->Fill(MVAVar,totalWeight);
              if(dataCardSel >= 0) histo_JESBoundingDown[ny][theCategory]->Fill(MVAVar,totalWeight);
              if(dataCardSel >= 0) histo_JERBoundingUp  [ny][theCategory]->Fill(MVAVar,totalWeight);
              if(dataCardSel >= 0) histo_JERBoundingDown[ny][theCategory]->Fill(MVAVar,totalWeight);
	    }
	  }
        } // end if theCategory
        if((theCategory == kPlotEWKSSWW_dim8 || theCategory == kPlotEWKWZ_dim8) && dataCardSel >= 0) {
	  int nAQGCcat = 0;
	  if(theCategory == kPlotEWKWZ_dim8) nAQGCcat = 1;
          for(int iscan = 0; iscan < nscan_ft0; iscan++){
            rw_aqgc_ft0[iscan] = totalWeight * (rw_aqgc_ft0[iscan] - thePandaFlat.rw_ft0_0);
            histo_aqgc_ft0_Baseline[nAQGCcat][iscan]->Fill(MVAVar,rw_aqgc_ft0[iscan]);
          }
	  for(int iscan = 0; iscan < nscan_ft1; iscan++){
            rw_aqgc_ft1[iscan] = totalWeight * (rw_aqgc_ft1[iscan] - thePandaFlat.rw_ft1_0);
	    histo_aqgc_ft1_Baseline[nAQGCcat][iscan]->Fill(MVAVar,rw_aqgc_ft1[iscan]);
          }
          for(int iscan = 0; iscan < nscan_ft2; iscan++){
            rw_aqgc_ft2[iscan] = totalWeight * (rw_aqgc_ft2[iscan] - thePandaFlat.rw_ft2_0);
            histo_aqgc_ft2_Baseline[nAQGCcat][iscan]->Fill(MVAVar,rw_aqgc_ft2[iscan]);
          }
          for(int iscan = 0; iscan < nscan_fm0; iscan++){
            rw_aqgc_fm0[iscan] = totalWeight * (rw_aqgc_fm0[iscan] - thePandaFlat.rw_fm0_0);
            histo_aqgc_fm0_Baseline[nAQGCcat][iscan]->Fill(MVAVar,rw_aqgc_fm0[iscan]);
          }
          for(int iscan = 0; iscan < nscan_fm1; iscan++){
            rw_aqgc_fm1[iscan] = totalWeight * (rw_aqgc_fm1[iscan] - thePandaFlat.rw_fm1_0);
            histo_aqgc_fm1_Baseline[nAQGCcat][iscan]->Fill(MVAVar,rw_aqgc_fm1[iscan]);
          }
          for(int iscan = 0; iscan < nscan_fm6; iscan++){
            rw_aqgc_fm6[iscan] = totalWeight * (rw_aqgc_fm6[iscan] - thePandaFlat.rw_fm6_0);
            histo_aqgc_fm6_Baseline[nAQGCcat][iscan]->Fill(MVAVar,rw_aqgc_fm6[iscan]);
          }
          for(int iscan = 0; iscan < nscan_fm7; iscan++){
            rw_aqgc_fm7[iscan] = totalWeight * (rw_aqgc_fm7[iscan] - thePandaFlat.rw_fm7_0);
            histo_aqgc_fm7_Baseline[nAQGCcat][iscan]->Fill(MVAVar,rw_aqgc_fm7[iscan]);
          }
          for(int iscan = 0; iscan < nscan_fs0; iscan++){
            rw_aqgc_fs0[iscan] = totalWeight * (rw_aqgc_fs0[iscan] - thePandaFlat.rw_fs0_0p0);
            histo_aqgc_fs0_Baseline[nAQGCcat][iscan]->Fill(MVAVar,rw_aqgc_fs0[iscan]);
          }
          for(int iscan = 0; iscan < nscan_fs1; iscan++){
            rw_aqgc_fs1[iscan] = totalWeight * (rw_aqgc_fs1[iscan] - thePandaFlat.rw_fs1_0);
            histo_aqgc_fs1_Baseline[nAQGCcat][iscan]->Fill(MVAVar,rw_aqgc_fs1[iscan]);
          }
        } // end if dim8
      } // end if(1)

    } // end events loop
    mvaoutf->cd();
    mvaoutf->Write();
    mvaoutf->Close();
    if(produceMVAInputs == false) system(Form("rm -f %s",outMVAfile));
    the_input_file->Close();
  } // end chain loop

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
      histo_JERBoundingUp      [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_JERBoundingUp      [ny][ic]->GetBinContent(nb),0.0f));
      histo_JERBoundingDown    [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_JERBoundingDown    [ny][ic]->GetBinContent(nb),0.0f));
      histo_PreFireBoundingUp  [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_PreFireBoundingUp  [ny][ic]->GetBinContent(nb),0.0f));
      histo_PreFireBoundingDown[ny][ic]->SetBinContent(nb, TMath::Max((float)histo_PreFireBoundingDown[ny][ic]->GetBinContent(nb),0.0f));
      histo_TriggerBoundingUp  [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_TriggerBoundingUp  [ny][ic]->GetBinContent(nb),0.0f));
      histo_TriggerBoundingDown[ny][ic]->SetBinContent(nb, TMath::Max((float)histo_TriggerBoundingDown[ny][ic]->GetBinContent(nb),0.0f));
      }
      histo_WSBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_WSBoundingUp	        [ic]->GetBinContent(nb),0.0f));
      histo_WSBoundingDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_WSBoundingDown	[ic]->GetBinContent(nb),0.0f));
      histo_EWKCorrVVUp 	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKCorrVVUp		[ic]->GetBinContent(nb),0.0f));
      histo_EWKCorrVVDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKCorrVVDown 	[ic]->GetBinContent(nb),0.0f));
      histo_EWKqqZZCorrUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKqqZZCorrUp 	[ic]->GetBinContent(nb),0.0f));
      histo_EWKqqZZCorrDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKqqZZCorrDown	[ic]->GetBinContent(nb),0.0f));
      histo_ggZZCorrUp  	  [ic]->SetBinContent(nb, TMath::Max((float)histo_ggZZCorrUp		[ic]->GetBinContent(nb),0.0f));
      histo_ggZZCorrDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_ggZZCorrDown          [ic]->GetBinContent(nb),0.0f));
      histo_WZTauHUp  	          [ic]->SetBinContent(nb, TMath::Max((float)histo_WZTauHUp              [ic]->GetBinContent(nb),0.0f));
      histo_WZTauHDown	          [ic]->SetBinContent(nb, TMath::Max((float)histo_WZTauHDown	        [ic]->GetBinContent(nb),0.0f));
      histo_WZTauLUp  	          [ic]->SetBinContent(nb, TMath::Max((float)histo_WZTauLUp              [ic]->GetBinContent(nb),0.0f));
      histo_WZTauLDown	          [ic]->SetBinContent(nb, TMath::Max((float)histo_WZTauLDown	        [ic]->GetBinContent(nb),0.0f));
    }
    histo_PUBoundingUp	[ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_PUBoundingUp  [ic]->GetSumOfWeights());
    histo_PUBoundingDown[ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_PUBoundingDown[ic]->GetSumOfWeights());
    if     ((fidAna == 2 || fidAna == 3 || fidAna == 5) && (ic == kPlotEWKWZ || ic == kPlotEWKSSWW ||
       ic == kPlotSignal0 || ic == kPlotSignal1 || ic == kPlotSignal2 || ic == kPlotSignal3)) {
      histo_QCDScaleUp   [ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_QCDScaleUp   [ic]->GetSumOfWeights());
      histo_QCDScaleDown [ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_QCDScaleDown [ic]->GetSumOfWeights());
      histo_EWKCorrVVUp  [ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_EWKCorrVVUp  [ic]->GetSumOfWeights());
      histo_EWKCorrVVDown[ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_EWKCorrVVDown[ic]->GetSumOfWeights());
    }
    else if(ic == kPlotZZ || ic == kPlotTVX || ic == kPlotWZ) {
      histo_QCDScaleUp     [ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_QCDScaleUp	  [ic]->GetSumOfWeights());
      histo_QCDScaleDown   [ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_QCDScaleDown   [ic]->GetSumOfWeights());
      histo_EWKCorrVVUp    [ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_EWKCorrVVUp    [ic]->GetSumOfWeights());
      histo_EWKCorrVVDown  [ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_EWKCorrVVDown  [ic]->GetSumOfWeights());
      histo_EWKqqZZCorrUp  [ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_EWKqqZZCorrUp  [ic]->GetSumOfWeights());
      histo_EWKqqZZCorrDown[ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_EWKqqZZCorrDown[ic]->GetSumOfWeights());
      histo_ggZZCorrUp     [ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_ggZZCorrUp	  [ic]->GetSumOfWeights());
      histo_ggZZCorrDown   [ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_ggZZCorrDown   [ic]->GetSumOfWeights());
    }
  }

  if(isPseudoData == true){
    histo_Baseline[kPlotData]->Scale(0);
    for(int ic=1; ic<nPlotCategories; ic++) {histo_Baseline[kPlotData]->Add(histo_Baseline[ic]); /*histo_Baseline[ic]->Scale(0);*/}
  }

  for(int ic=0; ic<nPlotCategories; ic++) if(ic != kPlotEWKSSWW_dim8 && ic != kPlotEWKWZ_dim8) histo[allPlots-1][ic]->Add(histo_Baseline[ic]);

  for(int nAQGCcat=0; nAQGCcat<2; nAQGCcat++){
    for(int nb=1; nb<=histo_Baseline[kPlotEWKWZ_dim8]->GetNbinsX(); nb++){
      for(int iscan = 0; iscan < nscan_ft0; iscan++){
	histo_aqgc_ft0_Baseline[nAQGCcat][iscan]->SetBinContent(nb, TMath::Max((float)histo_aqgc_ft0_Baseline[nAQGCcat][iscan]->GetBinContent(nb),0.0f));
      }
      for(int iscan = 0; iscan < nscan_ft1; iscan++){
	histo_aqgc_ft1_Baseline[nAQGCcat][iscan]->SetBinContent(nb, TMath::Max((float)histo_aqgc_ft1_Baseline[nAQGCcat][iscan]->GetBinContent(nb),0.0f));
      }
      for(int iscan = 0; iscan < nscan_ft2; iscan++){
	histo_aqgc_ft2_Baseline[nAQGCcat][iscan]->SetBinContent(nb, TMath::Max((float)histo_aqgc_ft2_Baseline[nAQGCcat][iscan]->GetBinContent(nb),0.0f));
      }
      for(int iscan = 0; iscan < nscan_fm0; iscan++){
	histo_aqgc_fm0_Baseline[nAQGCcat][iscan]->SetBinContent(nb, TMath::Max((float)histo_aqgc_fm0_Baseline[nAQGCcat][iscan]->GetBinContent(nb),0.0f));
      }
      for(int iscan = 0; iscan < nscan_fm1; iscan++){
	histo_aqgc_fm1_Baseline[nAQGCcat][iscan]->SetBinContent(nb, TMath::Max((float)histo_aqgc_fm1_Baseline[nAQGCcat][iscan]->GetBinContent(nb),0.0f));
      }
      for(int iscan = 0; iscan < nscan_fm6; iscan++){
	histo_aqgc_fm6_Baseline[nAQGCcat][iscan]->SetBinContent(nb, TMath::Max((float)histo_aqgc_fm6_Baseline[nAQGCcat][iscan]->GetBinContent(nb),0.0f));
      }
      for(int iscan = 0; iscan < nscan_fm7; iscan++){
	histo_aqgc_fm7_Baseline[nAQGCcat][iscan]->SetBinContent(nb, TMath::Max((float)histo_aqgc_fm7_Baseline[nAQGCcat][iscan]->GetBinContent(nb),0.0f));
      }
      for(int iscan = 0; iscan < nscan_fs0; iscan++){
	histo_aqgc_fs0_Baseline[nAQGCcat][iscan]->SetBinContent(nb, TMath::Max((float)histo_aqgc_fs0_Baseline[nAQGCcat][iscan]->GetBinContent(nb),0.0f));
      }
      for(int iscan = 0; iscan < nscan_fs1; iscan++){
	histo_aqgc_fs1_Baseline[nAQGCcat][iscan]->SetBinContent(nb, TMath::Max((float)histo_aqgc_fs1_Baseline[nAQGCcat][iscan]->GetBinContent(nb),0.0f));
      }
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

      printf("uncertainties JERUp\n");
      for(unsigned ic=0; ic<nPlotCategories; ic++) {
	if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
           printf("%10s: ",plotBaseNames[ic].Data());
          for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_JERBoundingUp[ny][ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      }
      printf("uncertainties JERDown\n");
      for(unsigned ic=0; ic<nPlotCategories; ic++) {
	if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
           printf("%10s: ",plotBaseNames[ic].Data());
          for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_JERBoundingDown[ny][ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
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

    printf("uncertainties WSUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_WSBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties WSDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_WSBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties EWKCorrVVUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_EWKCorrVVUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties EWKCorrVVDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_EWKCorrVVDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
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

    printf("uncertainties ggZZCorrUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_ggZZCorrUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties ggZZCorrDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_ggZZCorrDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties WZTauHUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_WZTauHUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties WZTauHDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_WZTauHDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties WZTauLUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_WZTauLUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties WZTauLDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_WZTauLDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
  }

  // Filling datacards input root file
  char outputLimits[200];
  sprintf(outputLimits,"ssww_%d%s_input.root",year,fidAnaName.Data());
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
    histo_JERBoundingUp 	[ny][ic]->Write();
    histo_JERBoundingDown	[ny][ic]->Write();
    histo_PreFireBoundingUp 	[ny][ic]->Write();
    histo_PreFireBoundingDown	[ny][ic]->Write();
    histo_TriggerBoundingUp 	[ny][ic]->Write();
    histo_TriggerBoundingDown	[ny][ic]->Write();
    }
    histo_WSBoundingUp          [ic]->Write();
    histo_WSBoundingDown        [ic]->Write();
    histo_EWKCorrVVUp		[ic]->Write();
    histo_EWKCorrVVDown 	[ic]->Write();
    histo_EWKqqZZCorrUp 	[ic]->Write();
    histo_EWKqqZZCorrDown	[ic]->Write();
    histo_ggZZCorrUp		[ic]->Write();
    histo_ggZZCorrDown  	[ic]->Write();
    histo_WZTauHUp              [ic]->Write();
    histo_WZTauHDown	        [ic]->Write();
    histo_WZTauLUp              [ic]->Write();
    histo_WZTauLDown	        [ic]->Write();
  }
  outFileLimits->Close();

  // Filling datacards txt file
  char outputLimitsCard[200];  					  
  sprintf(outputLimitsCard,"datacard_ssww_%d%s.txt",year,fidAnaName.Data());
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
    if     (ic != kPlotEWKSSWW && 
            ic != kPlotSignal0 && ic != kPlotSignal1 && 
            ic != kPlotSignal2 && ic != kPlotSignal3)
	                        newcardShape << Form("%d  ", ic);
    else if(ic == kPlotSignal0) newcardShape << Form("%d  ", -1);
    else if(ic == kPlotSignal1) newcardShape << Form("%d  ", -2);
    else if(ic == kPlotSignal2) newcardShape << Form("%d  ", -3);
    else if(ic == kPlotSignal3) newcardShape << Form("%d  ", -4);
    else                        newcardShape << Form("%d  ",  0);
  }
  newcardShape << Form("\n");

  newcardShape << Form("rate  ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("%f  ", histo_Baseline[ic]->GetSumOfWeights());
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_fake_m_%d    lnN     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("1.15 ");
    else                     newcardShape << Form("- ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_fake_e_%d    lnN     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("1.15 ");
    else                     newcardShape << Form("- ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("lumi_13TeV_%d    lnN     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("%6.3f ",lumiE[whichYear]);
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_momres_m    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("%6.3f ",1.005);
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_momres_e    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("%6.3f ",1.005);
  }
  newcardShape << Form("\n");

  newcardShape << Form("EWKCorrVV%s    shape     ",plotBaseNames[kPlotEWKSSWW].Data());
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotEWKSSWW) newcardShape << Form("- ");
    else                   newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("EWKCorrVV%s    shape	 ",plotBaseNames[kPlotEWKWZ].Data());
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotEWKWZ) newcardShape << Form("- ");
    else		 newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  //newcardShape << Form("EWKCorrVV%s	 shape     ",plotBaseNames[kPlotWZ].Data());
  //for (int ic=0; ic<nPlotCategories; ic++){
  //  if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
  //  if(ic != kPlotWZ) newcardShape << Form("- ");
  //  else		newcardShape << Form("1.0 ");
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

  newcardShape << Form("WZTauH    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotWZ && ic != kPlotEWKWZ) newcardShape << Form("- ");
    else	                          newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("WZTauL    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotWZ && ic != kPlotEWKWZ) newcardShape << Form("- ");
    else	                          newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  for(unsigned ic=0; ic<nPlotCategories; ic++) {
    if(ic== kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("QCDScale_%s_ACCEPT    shape   ",plotBaseNames[ic].Data());
    for(unsigned ic2=0; ic2<nPlotCategories; ic2++) {
      if(ic2 == kPlotData || histo_Baseline[ic2]->GetSumOfWeights() <= 0) continue;
          if(ic==ic2) newcardShape << Form("1.0  ");
          else       newcardShape << Form("-  ");
      }
      newcardShape << Form("\n");
  }

  newcardShape << Form("PDF    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_eff_m    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_eff_e    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_wseff    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotWS) newcardShape << Form("1.0 ");
    else              newcardShape << Form("- ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_pu    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_btagb_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_btagl_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_jes_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt || ic == kPlotDY) newcardShape << Form("- ");
    else                                      newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_jer_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt || ic == kPlotDY) newcardShape << Form("- ");
    else                                      newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_prefire_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_trigger_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_ssww_tvxnorm rateParam * %s 1 [0.1,3]\n",plotBaseNames[kPlotTVX].Data());
  newcardShape << Form("CMS_ssww_zznorm  rateParam * %s 1 [0.1,3]\n",plotBaseNames[kPlotZZ].Data());

  newcardShape << Form("ch1 autoMCStats 0\n");

  newcardShape.close();

  // Writing standard histograms
  char output[200];
  if(fidAna == 0 || fidAna == 5){
    for(int thePlot=0; thePlot<allPlots; thePlot++){
      sprintf(output,"histossww_%d_%d%s.root",year,thePlot,fidAnaName.Data());
      TFile* outFilePlotsNote = new TFile(output,"recreate");
      outFilePlotsNote->cd();
      double totBck = 0;
      for(int i=1; i<nPlotCategories; i++) if(histo[thePlot][i]->GetSumOfWeights() > 0) totBck = totBck + histo[thePlot][i]->GetSumOfWeights();
      printf("(%2d) %7.1f vs. %7.1f ",thePlot,histo[thePlot][0]->GetSumOfWeights(),totBck);
      printf("(");
      for(int i=1; i<nPlotCategories; i++) if(i!=kPlotSignal0 && i!=kPlotSignal1 && i!=kPlotSignal2 && i!=kPlotSignal3) printf("%7.1f ",TMath::Max(histo[thePlot][i]->GetSumOfWeights(),0.0));
      printf(")\n");
      for(int np=0; np<nPlotCategories; np++) {histo[thePlot][np]->SetNameTitle(Form("histo%d",np),Form("histo%d",np));histo[thePlot][np]->Write();}
      outFilePlotsNote->Close();
    }
  }

  if(fidAna == 4){
    TH1D *histo_dim8_QCDScaleUp[2];
    TH1D *histo_dim8_QCDScaleDown[2];
    TH1D *histo_dim8_PDFBoundingUp[2];
    TH1D *histo_dim8_PDFBoundingDown[2];
    TH1D *histo_dim8_LepEffMBoundingUp[2];
    TH1D *histo_dim8_LepEffMBoundingDown[2];
    TH1D *histo_dim8_LepEffEBoundingUp[2];
    TH1D *histo_dim8_LepEffEBoundingDown[2];
    TH1D *histo_dim8_PUBoundingUp[2];
    TH1D *histo_dim8_PUBoundingDown[2];
    TH1D *histo_dim8_BTAGBBoundingUp[nYears][2];
    TH1D *histo_dim8_BTAGBBoundingDown[nYears][2];
    TH1D *histo_dim8_BTAGLBoundingUp[nYears][2];
    TH1D *histo_dim8_BTAGLBoundingDown[nYears][2];
    TH1D *histo_dim8_JESBoundingUp[nYears][2];
    TH1D *histo_dim8_JESBoundingDown[nYears][2];
    TH1D *histo_dim8_JERBoundingUp[nYears][2];
    TH1D *histo_dim8_JERBoundingDown[nYears][2];
    TH1D *histo_dim8_PreFireBoundingUp[nYears][2];
    TH1D *histo_dim8_PreFireBoundingDown[nYears][2];
    TH1D *histo_dim8_TriggerBoundingUp[nYears][2];
    TH1D *histo_dim8_TriggerBoundingDown[nYears][2];
    TH1D *histo_dim8_WSBoundingUp[2];
    TH1D *histo_dim8_WSBoundingDown[2];
    TH1D *histo_dim8_EWKCorrVVUp[2];
    TH1D *histo_dim8_EWKCorrVVDown[2];
    TH1D *histo_dim8_EWKqqZZCorrUp[2];
    TH1D *histo_dim8_EWKqqZZCorrDown[2];
    TH1D *histo_dim8_ggZZCorrUp[2];
    TH1D *histo_dim8_ggZZCorrDown[2];
    TH1D *histo_dim8_WZTauHUp[2];
    TH1D *histo_dim8_WZTauHDown[2];
    TH1D *histo_dim8_WZTauLUp[2];
    TH1D *histo_dim8_WZTauLDown[2];
    for(int nAQGCcat=0; nAQGCcat<2; nAQGCcat++) {
      int iref = kPlotEWKSSWW_dim8;
      if(nAQGCcat == 1) iref = kPlotEWKWZ_dim8;

      histo_dim8_QCDScaleUp          [nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_QCDScale_%s_ACCEPTUp"  , plotBaseNames[iref].Data(), plotBaseNames[iref].Data()));
      histo_dim8_QCDScaleDown        [nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_QCDScale_%s_ACCEPTDown", plotBaseNames[iref].Data(), plotBaseNames[iref].Data()));
      histo_dim8_PDFBoundingUp 	     [nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_PDFUp"		     , plotBaseNames[iref].Data()));
      histo_dim8_PDFBoundingDown     [nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_PDFDown"  	     , plotBaseNames[iref].Data()));
      histo_dim8_LepEffMBoundingUp   [nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_CMS_eff_mUp"	     , plotBaseNames[iref].Data()));
      histo_dim8_LepEffMBoundingDown [nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_CMS_eff_mDown"	     , plotBaseNames[iref].Data()));
      histo_dim8_LepEffEBoundingUp   [nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_CMS_eff_eUp"	     , plotBaseNames[iref].Data()));
      histo_dim8_LepEffEBoundingDown [nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_CMS_eff_eDown"	     , plotBaseNames[iref].Data()));
      histo_dim8_PUBoundingUp	     [nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_CMS_puUp" 	     , plotBaseNames[iref].Data()));
      histo_dim8_PUBoundingDown      [nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_CMS_puDown"	     , plotBaseNames[iref].Data()));
      for(int ny=0; ny<nYears; ny++){
      histo_dim8_BTAGBBoundingUp    [ny][nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_CMS_btagb_%dUp"     , plotBaseNames[iref].Data(),2016+ny));
      histo_dim8_BTAGBBoundingDown  [ny][nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_CMS_btagb_%dDown"   , plotBaseNames[iref].Data(),2016+ny));
      histo_dim8_BTAGLBoundingUp    [ny][nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_CMS_btagl_%dUp"     , plotBaseNames[iref].Data(),2016+ny));
      histo_dim8_BTAGLBoundingDown  [ny][nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_CMS_btagl_%dDown"   , plotBaseNames[iref].Data(),2016+ny));
      histo_dim8_JESBoundingUp      [ny][nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_CMS_jes_%dUp"       , plotBaseNames[iref].Data(),2016+ny));
      histo_dim8_JESBoundingDown    [ny][nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_CMS_jes_%dDown"     , plotBaseNames[iref].Data(),2016+ny));
      histo_dim8_JERBoundingUp      [ny][nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_CMS_jer_%dUp"       , plotBaseNames[iref].Data(),2016+ny));
      histo_dim8_JERBoundingDown    [ny][nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_CMS_jer_%dDown"     , plotBaseNames[iref].Data(),2016+ny));
      histo_dim8_PreFireBoundingUp  [ny][nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_CMS_prefire_%dUp"   , plotBaseNames[iref].Data(),2016+ny));
      histo_dim8_PreFireBoundingDown[ny][nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_CMS_prefire_%dDown" , plotBaseNames[iref].Data(),2016+ny));
      histo_dim8_TriggerBoundingUp  [ny][nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_CMS_trigger_%dUp"   , plotBaseNames[iref].Data(),2016+ny));
      histo_dim8_TriggerBoundingDown[ny][nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_CMS_trigger_%dDown" , plotBaseNames[iref].Data(),2016+ny));
      }
      histo_dim8_WSBoundingUp        [nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_CMS_wseffUp"	  , plotBaseNames[iref].Data()));
      histo_dim8_WSBoundingDown      [nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_CMS_wseffDown"	  , plotBaseNames[iref].Data()));
      histo_dim8_EWKCorrVVUp         [nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_EWKCorrVV%sUp"	  , plotBaseNames[iref].Data(), plotBaseNames[iref].Data()));
      histo_dim8_EWKCorrVVDown       [nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_EWKCorrVV%sDown"    , plotBaseNames[iref].Data(), plotBaseNames[iref].Data()));
      histo_dim8_EWKqqZZCorrUp 	     [nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_EWKqqZZCorrUp"	  , plotBaseNames[iref].Data()));
      histo_dim8_EWKqqZZCorrDown     [nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_EWKqqZZCorrDown"    , plotBaseNames[iref].Data()));
      histo_dim8_ggZZCorrUp	     [nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_ggZZCorrUp"	  , plotBaseNames[iref].Data()));
      histo_dim8_ggZZCorrDown	     [nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_ggZZCorrDown"	  , plotBaseNames[iref].Data()));
      histo_dim8_WZTauHUp	     [nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_WZTauHUp"	          , plotBaseNames[iref].Data()));
      histo_dim8_WZTauHDown	     [nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_WZTauHDown"	  , plotBaseNames[iref].Data()));
      histo_dim8_WZTauLUp	     [nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_WZTauLUp"	          , plotBaseNames[iref].Data()));
      histo_dim8_WZTauLDown	     [nAQGCcat] = (TH1D*)histo_MVA->Clone(Form("histo_dim8_%s_WZTauLDown"	  , plotBaseNames[iref].Data()));

      histo_dim8_QCDScaleUp             [nAQGCcat]->Add(histo_QCDScaleUp	     [iref]); histo_dim8_QCDScaleUp		[nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_QCDScaleDown           [nAQGCcat]->Add(histo_QCDScaleDown	     [iref]); histo_dim8_QCDScaleDown		[nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_PDFBoundingUp          [nAQGCcat]->Add(histo_PDFBoundingUp  	     [iref]); histo_dim8_PDFBoundingUp	        [nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_PDFBoundingDown        [nAQGCcat]->Add(histo_PDFBoundingDown	     [iref]); histo_dim8_PDFBoundingDown	[nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_LepEffMBoundingUp      [nAQGCcat]->Add(histo_LepEffMBoundingUp	     [iref]); histo_dim8_LepEffMBoundingUp	[nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_LepEffMBoundingDown    [nAQGCcat]->Add(histo_LepEffMBoundingDown    [iref]); histo_dim8_LepEffMBoundingDown    [nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_LepEffEBoundingUp      [nAQGCcat]->Add(histo_LepEffEBoundingUp	     [iref]); histo_dim8_LepEffEBoundingUp	[nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_LepEffEBoundingDown    [nAQGCcat]->Add(histo_LepEffEBoundingDown    [iref]); histo_dim8_LepEffEBoundingDown    [nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_PUBoundingUp           [nAQGCcat]->Add(histo_PUBoundingUp	     [iref]); histo_dim8_PUBoundingUp	        [nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_PUBoundingDown         [nAQGCcat]->Add(histo_PUBoundingDown         [iref]); histo_dim8_PUBoundingDown         [nAQGCcat]->Divide(histo_Baseline[iref]);
      for(int ny=0; ny<nYears; ny++){
      histo_dim8_BTAGBBoundingUp    [ny][nAQGCcat]->Add(histo_BTAGBBoundingUp    [ny][iref]); histo_dim8_BTAGBBoundingUp    [ny][nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_BTAGBBoundingDown  [ny][nAQGCcat]->Add(histo_BTAGBBoundingDown  [ny][iref]); histo_dim8_BTAGBBoundingDown  [ny][nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_BTAGLBoundingUp    [ny][nAQGCcat]->Add(histo_BTAGLBoundingUp    [ny][iref]); histo_dim8_BTAGLBoundingUp    [ny][nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_BTAGLBoundingDown  [ny][nAQGCcat]->Add(histo_BTAGLBoundingDown  [ny][iref]); histo_dim8_BTAGLBoundingDown  [ny][nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_JESBoundingUp      [ny][nAQGCcat]->Add(histo_JESBoundingUp      [ny][iref]); histo_dim8_JESBoundingUp      [ny][nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_JESBoundingDown    [ny][nAQGCcat]->Add(histo_JESBoundingDown    [ny][iref]); histo_dim8_JESBoundingDown    [ny][nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_JERBoundingUp      [ny][nAQGCcat]->Add(histo_JERBoundingUp      [ny][iref]); histo_dim8_JERBoundingUp      [ny][nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_JERBoundingDown    [ny][nAQGCcat]->Add(histo_JERBoundingDown    [ny][iref]); histo_dim8_JERBoundingDown    [ny][nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_PreFireBoundingUp  [ny][nAQGCcat]->Add(histo_PreFireBoundingUp  [ny][iref]); histo_dim8_PreFireBoundingUp  [ny][nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_PreFireBoundingDown[ny][nAQGCcat]->Add(histo_PreFireBoundingDown[ny][iref]); histo_dim8_PreFireBoundingDown[ny][nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_TriggerBoundingUp  [ny][nAQGCcat]->Add(histo_TriggerBoundingUp  [ny][iref]); histo_dim8_TriggerBoundingUp  [ny][nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_TriggerBoundingDown[ny][nAQGCcat]->Add(histo_TriggerBoundingDown[ny][iref]); histo_dim8_TriggerBoundingDown[ny][nAQGCcat]->Divide(histo_Baseline[iref]);
      }
      histo_dim8_WSBoundingUp           [nAQGCcat]->Add(histo_WSBoundingUp           [iref]); histo_dim8_WSBoundingUp	        [nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_WSBoundingDown         [nAQGCcat]->Add(histo_WSBoundingDown 	     [iref]); histo_dim8_WSBoundingDown	        [nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_EWKCorrVVUp            [nAQGCcat]->Add(histo_EWKCorrVVUp	     [iref]); histo_dim8_EWKCorrVVUp 	        [nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_EWKCorrVVDown          [nAQGCcat]->Add(histo_EWKCorrVVDown  	     [iref]); histo_dim8_EWKCorrVVDown	        [nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_EWKqqZZCorrUp          [nAQGCcat]->Add(histo_EWKqqZZCorrUp  	     [iref]); histo_dim8_EWKqqZZCorrUp	        [nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_EWKqqZZCorrDown        [nAQGCcat]->Add(histo_EWKqqZZCorrDown	     [iref]); histo_dim8_EWKqqZZCorrDown	[nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_ggZZCorrUp             [nAQGCcat]->Add(histo_ggZZCorrUp	     [iref]); histo_dim8_ggZZCorrUp		[nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_ggZZCorrDown           [nAQGCcat]->Add(histo_ggZZCorrDown	     [iref]); histo_dim8_ggZZCorrDown		[nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_WZTauHUp               [nAQGCcat]->Add(histo_WZTauHUp	             [iref]); histo_dim8_WZTauHUp		[nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_WZTauHDown             [nAQGCcat]->Add(histo_WZTauHDown	     [iref]); histo_dim8_WZTauHDown		[nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_WZTauLUp               [nAQGCcat]->Add(histo_WZTauLUp	             [iref]); histo_dim8_WZTauLUp		[nAQGCcat]->Divide(histo_Baseline[iref]);
      histo_dim8_WZTauLDown             [nAQGCcat]->Add(histo_WZTauLDown	     [iref]); histo_dim8_WZTauLDown		[nAQGCcat]->Divide(histo_Baseline[iref]);
    }
    int nscanTot = nscan_ft0 + nscan_ft1 + nscan_ft2 + nscan_fm0 + nscan_fm1 + nscan_fm6 + nscan_fm7 + nscan_fs0 + nscan_fs1;
    TH1D *histoAQGC[2];
    histoAQGC[0] = (TH1D*)histo_MVA->Clone(Form("histoAQGC_0"));
    histoAQGC[1] = (TH1D*)histo_MVA->Clone(Form("histoAQGC_1"));
    for(int iscan=0; iscan<nscanTot; iscan++){
      int theScan = iscan;
      TString AQGC_range = "dummy";
      if     (iscan < nscan_ft0) {theScan = theScan - (0); AQGC_range = AQGCParaName[0] + "_" + AQGC_ft0_range[theScan];}
      else if(iscan < nscan_ft0+nscan_ft1) {theScan = theScan - (nscan_ft0); AQGC_range = AQGCParaName[1] + "_" + AQGC_ft1_range[theScan];}
      else if(iscan < nscan_ft0+nscan_ft1+nscan_ft2) {theScan = theScan - (nscan_ft0+nscan_ft1); AQGC_range = AQGCParaName[2] + "_" + AQGC_ft2_range[theScan];}
      else if(iscan < nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0) {theScan = theScan - (nscan_ft0+nscan_ft1+nscan_ft2); AQGC_range = AQGCParaName[3] + "_" + AQGC_fm0_range[theScan];}
      else if(iscan < nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0+nscan_fm1) {theScan = theScan - (nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0); AQGC_range = AQGCParaName[4] + "_" + AQGC_fm1_range[theScan];}
      else if(iscan < nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0+nscan_fm1+nscan_fm6) {theScan = theScan - (nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0+nscan_fm1); AQGC_range = AQGCParaName[5] + "_" + AQGC_fm6_range[theScan];}
      else if(iscan < nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0+nscan_fm1+nscan_fm6+nscan_fm7) {theScan = theScan - (nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0+nscan_fm1+nscan_fm6); AQGC_range = AQGCParaName[6] + "_" + AQGC_fm7_range[theScan];}
      else if(iscan < nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0+nscan_fm1+nscan_fm6+nscan_fm7+nscan_fs0) {theScan = theScan - (nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0+nscan_fm1+nscan_fm6+nscan_fm7); AQGC_range = AQGCParaName[7] + "_" + AQGC_fs0_range[theScan];}
      else if(iscan < nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0+nscan_fm1+nscan_fm6+nscan_fm7+nscan_fs0+nscan_fs1) {theScan = theScan - (nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0+nscan_fm1+nscan_fm6+nscan_fm7+nscan_fs0); AQGC_range = AQGCParaName[8] + "_" + AQGC_fs1_range[theScan];}
      bool isZeroYield[2] = {false, false};
      for(int nAQGCcat=0; nAQGCcat<2; nAQGCcat++) {
        histoAQGC[nAQGCcat]->Reset();
	if(iscan < nscan_ft0) histoAQGC[nAQGCcat]->Add(histo_aqgc_ft0_Baseline[nAQGCcat][theScan]);
        else if(iscan < nscan_ft0+nscan_ft1) histoAQGC[nAQGCcat]->Add(histo_aqgc_ft1_Baseline[nAQGCcat][theScan]);
	else if(iscan < nscan_ft0+nscan_ft1+nscan_ft2) histoAQGC[nAQGCcat]->Add(histo_aqgc_ft2_Baseline[nAQGCcat][theScan]);
	else if(iscan < nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0) histoAQGC[nAQGCcat]->Add(histo_aqgc_fm0_Baseline[nAQGCcat][theScan]);
	else if(iscan < nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0+nscan_fm1) histoAQGC[nAQGCcat]->Add(histo_aqgc_fm1_Baseline[nAQGCcat][theScan]); 
	else if(iscan < nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0+nscan_fm1+nscan_fm6) histoAQGC[nAQGCcat]->Add(histo_aqgc_fm6_Baseline[nAQGCcat][theScan]);  
	else if(iscan < nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0+nscan_fm1+nscan_fm6+nscan_fm7) histoAQGC[nAQGCcat]->Add(histo_aqgc_fm7_Baseline[nAQGCcat][theScan]); 
	else if(iscan < nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0+nscan_fm1+nscan_fm6+nscan_fm7+nscan_fs0) histoAQGC[nAQGCcat]->Add(histo_aqgc_fs0_Baseline[nAQGCcat][theScan]); 
	else if(iscan < nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0+nscan_fm1+nscan_fm6+nscan_fm7+nscan_fs0+nscan_fs1) histoAQGC[nAQGCcat]->Add(histo_aqgc_fs1_Baseline[nAQGCcat][theScan]);
        int iref = kPlotEWKSSWW_dim8;
	if(nAQGCcat == 1) iref = kPlotEWKWZ_dim8;
	if(histoAQGC[nAQGCcat]->GetSumOfWeights() <= 0.01) {
	  isZeroYield[nAQGCcat] = true;
	}
	else {
          printf("%s(%6.2f,%6.2f) ",AQGC_range.Data(),histoAQGC[nAQGCcat]->GetSumOfWeights(),histo_Baseline[iref]->GetSumOfWeights());
	  if(histo_Baseline[iref]->GetSumOfWeights() <= 0) printf(" PROBLEM ");
	  double aqgcNorm = aqgcNorm = histoAQGC[nAQGCcat]->GetSumOfWeights()/histo_Baseline[iref]->GetSumOfWeights();
	  histo_Baseline[iref]->Reset(); 
	  histo_Baseline[iref]->Add(histoAQGC[nAQGCcat]);
	  histo_QCDScaleUp             [iref]->Scale(0);  histo_QCDScaleUp	       [iref]->Add(histo_Baseline[iref]); histo_QCDScaleUp	       [iref]->Multiply(histo_dim8_QCDScaleUp		  [nAQGCcat]);
	  histo_QCDScaleDown  	       [iref]->Scale(0);  histo_QCDScaleDown	       [iref]->Add(histo_Baseline[iref]); histo_QCDScaleDown	       [iref]->Multiply(histo_dim8_QCDScaleDown 	  [nAQGCcat]);
	  histo_PDFBoundingUp 	       [iref]->Scale(0);  histo_PDFBoundingUp	       [iref]->Add(histo_Baseline[iref]); histo_PDFBoundingUp	       [iref]->Multiply(histo_dim8_PDFBoundingUp	  [nAQGCcat]);
	  histo_PDFBoundingDown	       [iref]->Scale(0);  histo_PDFBoundingDown        [iref]->Add(histo_Baseline[iref]); histo_PDFBoundingDown        [iref]->Multiply(histo_dim8_PDFBoundingDown	  [nAQGCcat]);
	  histo_LepEffMBoundingUp      [iref]->Scale(0);  histo_LepEffMBoundingUp      [iref]->Add(histo_Baseline[iref]); histo_LepEffMBoundingUp      [iref]->Multiply(histo_dim8_LepEffMBoundingUp	  [nAQGCcat]);
	  histo_LepEffMBoundingDown    [iref]->Scale(0);  histo_LepEffMBoundingDown    [iref]->Add(histo_Baseline[iref]); histo_LepEffMBoundingDown    [iref]->Multiply(histo_dim8_LepEffMBoundingDown    [nAQGCcat]);
	  histo_LepEffEBoundingUp      [iref]->Scale(0);  histo_LepEffEBoundingUp      [iref]->Add(histo_Baseline[iref]); histo_LepEffEBoundingUp      [iref]->Multiply(histo_dim8_LepEffEBoundingUp	  [nAQGCcat]);
	  histo_LepEffEBoundingDown    [iref]->Scale(0);  histo_LepEffEBoundingDown    [iref]->Add(histo_Baseline[iref]); histo_LepEffEBoundingDown    [iref]->Multiply(histo_dim8_LepEffEBoundingDown    [nAQGCcat]);
	  histo_PUBoundingUp  	       [iref]->Scale(0);  histo_PUBoundingUp	       [iref]->Add(histo_Baseline[iref]); histo_PUBoundingUp	       [iref]->Multiply(histo_dim8_PUBoundingUp 	  [nAQGCcat]);
	  histo_PUBoundingDown	       [iref]->Scale(0);  histo_PUBoundingDown         [iref]->Add(histo_Baseline[iref]); histo_PUBoundingDown         [iref]->Multiply(histo_dim8_PUBoundingDown	  [nAQGCcat]);
	  for(int ny=0; ny<nYears; ny++){
	  histo_BTAGBBoundingUp    [ny][iref]->Scale(0);  histo_BTAGBBoundingUp    [ny][iref]->Add(histo_Baseline[iref]); histo_BTAGBBoundingUp    [ny][iref]->Multiply(histo_dim8_BTAGBBoundingUp    [ny][nAQGCcat]);
	  histo_BTAGBBoundingDown  [ny][iref]->Scale(0);  histo_BTAGBBoundingDown  [ny][iref]->Add(histo_Baseline[iref]); histo_BTAGBBoundingDown  [ny][iref]->Multiply(histo_dim8_BTAGBBoundingDown  [ny][nAQGCcat]);
	  histo_BTAGLBoundingUp    [ny][iref]->Scale(0);  histo_BTAGLBoundingUp    [ny][iref]->Add(histo_Baseline[iref]); histo_BTAGLBoundingUp    [ny][iref]->Multiply(histo_dim8_BTAGLBoundingUp    [ny][nAQGCcat]);
	  histo_BTAGLBoundingDown  [ny][iref]->Scale(0);  histo_BTAGLBoundingDown  [ny][iref]->Add(histo_Baseline[iref]); histo_BTAGLBoundingDown  [ny][iref]->Multiply(histo_dim8_BTAGLBoundingDown  [ny][nAQGCcat]);
	  histo_JESBoundingUp 	   [ny][iref]->Scale(0);  histo_JESBoundingUp	   [ny][iref]->Add(histo_Baseline[iref]); histo_JESBoundingUp	   [ny][iref]->Multiply(histo_dim8_JESBoundingUp      [ny][nAQGCcat]);
	  histo_JESBoundingDown	   [ny][iref]->Scale(0);  histo_JESBoundingDown    [ny][iref]->Add(histo_Baseline[iref]); histo_JESBoundingDown    [ny][iref]->Multiply(histo_dim8_JESBoundingDown    [ny][nAQGCcat]);
	  histo_JERBoundingUp 	   [ny][iref]->Scale(0);  histo_JERBoundingUp	   [ny][iref]->Add(histo_Baseline[iref]); histo_JERBoundingUp	   [ny][iref]->Multiply(histo_dim8_JERBoundingUp      [ny][nAQGCcat]);
	  histo_JERBoundingDown	   [ny][iref]->Scale(0);  histo_JERBoundingDown    [ny][iref]->Add(histo_Baseline[iref]); histo_JERBoundingDown    [ny][iref]->Multiply(histo_dim8_JERBoundingDown    [ny][nAQGCcat]);
	  histo_PreFireBoundingUp  [ny][iref]->Scale(0);  histo_PreFireBoundingUp  [ny][iref]->Add(histo_Baseline[iref]); histo_PreFireBoundingUp  [ny][iref]->Multiply(histo_dim8_PreFireBoundingUp  [ny][nAQGCcat]);
	  histo_PreFireBoundingDown[ny][iref]->Scale(0);  histo_PreFireBoundingDown[ny][iref]->Add(histo_Baseline[iref]); histo_PreFireBoundingDown[ny][iref]->Multiply(histo_dim8_PreFireBoundingDown[ny][nAQGCcat]);
	  histo_TriggerBoundingUp  [ny][iref]->Scale(0);  histo_TriggerBoundingUp  [ny][iref]->Add(histo_Baseline[iref]); histo_TriggerBoundingUp  [ny][iref]->Multiply(histo_dim8_TriggerBoundingUp  [ny][nAQGCcat]);
	  histo_TriggerBoundingDown[ny][iref]->Scale(0);  histo_TriggerBoundingDown[ny][iref]->Add(histo_Baseline[iref]); histo_TriggerBoundingDown[ny][iref]->Multiply(histo_dim8_TriggerBoundingDown[ny][nAQGCcat]);
	  }
	  histo_WSBoundingUp           [iref]->Scale(0); histo_WSBoundingUp            [iref]->Add(histo_Baseline[iref]); histo_WSBoundingUp	       [iref]->Multiply(histo_dim8_WSBoundingUp 	  [nAQGCcat]);
	  histo_WSBoundingDown         [iref]->Scale(0); histo_WSBoundingDown	       [iref]->Add(histo_Baseline[iref]); histo_WSBoundingDown         [iref]->Multiply(histo_dim8_WSBoundingDown	  [nAQGCcat]);
	  histo_EWKCorrVVUp            [iref]->Scale(0); histo_EWKCorrVVUp	       [iref]->Add(histo_Baseline[iref]); histo_EWKCorrVVUp	       [iref]->Multiply(histo_dim8_EWKCorrVVUp  	  [nAQGCcat]);
	  histo_EWKCorrVVDown          [iref]->Scale(0); histo_EWKCorrVVDown	       [iref]->Add(histo_Baseline[iref]); histo_EWKCorrVVDown	       [iref]->Multiply(histo_dim8_EWKCorrVVDown	  [nAQGCcat]);
	  histo_EWKqqZZCorrUp          [iref]->Scale(0); histo_EWKqqZZCorrUp	       [iref]->Add(histo_Baseline[iref]); histo_EWKqqZZCorrUp	       [iref]->Multiply(histo_dim8_EWKqqZZCorrUp	  [nAQGCcat]);
	  histo_EWKqqZZCorrDown        [iref]->Scale(0); histo_EWKqqZZCorrDown         [iref]->Add(histo_Baseline[iref]); histo_EWKqqZZCorrDown        [iref]->Multiply(histo_dim8_EWKqqZZCorrDown	  [nAQGCcat]);
	  histo_ggZZCorrUp             [iref]->Scale(0); histo_ggZZCorrUp	       [iref]->Add(histo_Baseline[iref]); histo_ggZZCorrUp	       [iref]->Multiply(histo_dim8_ggZZCorrUp		  [nAQGCcat]);
	  histo_ggZZCorrDown           [iref]->Scale(0); histo_ggZZCorrDown	       [iref]->Add(histo_Baseline[iref]); histo_ggZZCorrDown	       [iref]->Multiply(histo_dim8_ggZZCorrDown 	  [nAQGCcat]);
	  histo_WZTauHUp               [iref]->Scale(0); histo_WZTauHUp	               [iref]->Add(histo_Baseline[iref]); histo_WZTauHUp	       [iref]->Multiply(histo_dim8_WZTauHUp		  [nAQGCcat]);
	  histo_WZTauHDown             [iref]->Scale(0); histo_WZTauHDown	       [iref]->Add(histo_Baseline[iref]); histo_WZTauHDown	       [iref]->Multiply(histo_dim8_WZTauHDown 	          [nAQGCcat]);
	  histo_WZTauLUp               [iref]->Scale(0); histo_WZTauLUp	               [iref]->Add(histo_Baseline[iref]); histo_WZTauLUp	       [iref]->Multiply(histo_dim8_WZTauLUp		  [nAQGCcat]);
	  histo_WZTauLDown             [iref]->Scale(0); histo_WZTauLDown	       [iref]->Add(histo_Baseline[iref]); histo_WZTauLDown	       [iref]->Multiply(histo_dim8_WZTauLDown 	          [nAQGCcat]);
	}
      }
      if(isZeroYield[0] == false || isZeroYield[1] == false) printf("\n");

      sprintf(outputLimits,"ssww_aqgc_%s_%d%s_input.root",AQGC_range.Data(),year,fidAnaName.Data());
      TFile* outFileLimits = new TFile(outputLimits,"recreate");
      outFileLimits->cd();
      for(unsigned ic=0; ic<nPlotCategories; ic++) {
	if(ic != kPlotData && histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
	if(ic == kPlotEWKSSWW_dim8 && isZeroYield[0] == true) continue;
	if(ic == kPlotEWKWZ_dim8 && isZeroYield[1] == true) continue;
	histo_Baseline		[ic]->Write();
	if(ic == kPlotData) continue;
	histo_QCDScaleUp         [ic]->Write();
	histo_QCDScaleDown  	 [ic]->Write();
	histo_PDFBoundingUp 	 [ic]->Write();
	histo_PDFBoundingDown	 [ic]->Write();
	histo_LepEffMBoundingUp	 [ic]->Write();
	histo_LepEffMBoundingDown[ic]->Write();
	histo_LepEffEBoundingUp  [ic]->Write();
	histo_LepEffEBoundingDown[ic]->Write();
	histo_PUBoundingUp  	 [ic]->Write();
	histo_PUBoundingDown	 [ic]->Write();
	for(int ny=0; ny<nYears; ny++){
	histo_BTAGBBoundingUp	 [ny][ic]->Write();
	histo_BTAGBBoundingDown	 [ny][ic]->Write();
	histo_BTAGLBoundingUp	 [ny][ic]->Write();
	histo_BTAGLBoundingDown	 [ny][ic]->Write();
	histo_JESBoundingUp 	 [ny][ic]->Write();
	histo_JESBoundingDown	 [ny][ic]->Write();
	histo_JERBoundingUp 	 [ny][ic]->Write();
	histo_JERBoundingDown	 [ny][ic]->Write();
	histo_PreFireBoundingUp  [ny][ic]->Write();
	histo_PreFireBoundingDown[ny][ic]->Write();
	histo_TriggerBoundingUp  [ny][ic]->Write();
	histo_TriggerBoundingDown[ny][ic]->Write();
	}
	histo_WSBoundingUp   [ic]->Write();
	histo_WSBoundingDown [ic]->Write();
	histo_EWKCorrVVUp    [ic]->Write();
	histo_EWKCorrVVDown  [ic]->Write();
	histo_EWKqqZZCorrUp  [ic]->Write();
	histo_EWKqqZZCorrDown[ic]->Write();
	histo_ggZZCorrUp     [ic]->Write();
	histo_ggZZCorrDown   [ic]->Write();
	histo_WZTauHUp       [ic]->Write();
	histo_WZTauHDown     [ic]->Write();
	histo_WZTauLUp       [ic]->Write();
	histo_WZTauLDown     [ic]->Write();
      }
      outFileLimits->Close();
    }
  } // end if fidAna == 4
}
