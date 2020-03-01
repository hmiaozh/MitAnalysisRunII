#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TString.h>
#include <TRandom.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TGraphAsymmErrors.h>
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
const double jetPtCut = 50;

double syst_WZl[2] = {1.010, 1.012};

// fidAna == 0 (SM), 1 (SM-altWZ), 2 (MJJ), 3 (MLL), 4 (AQGC), 5(long), 6(charge)

enum systType                     {JESUP=0, JESDOWN,  JERUP,  JERDOWN, nSystTypes};
TString systTypeName[nSystTypes]= {"JESUP","JESDOWN","JERUP","JERDOWN"};


const int which_para = 3;
const int which_point = 31;


//TString AQGCParaName[1] = {"ft1"};
TString AQGCParaName[9] = {"ft0","ft1","ft2","fm0","fm1","fm6","fm7","fs0","fs1"};
const int nscan_ft0 = 35;
const int nscan_ft1 = 35;
const int nscan_ft2 = 35;
const int nscan_fm0 = 41;
const int nscan_fm1 = 37;
const int nscan_fm6 = 35;
const int nscan_fm7 = 31;
const int nscan_fs0 = 43;
const int nscan_fs1 = 33;

const double AQGC_ft0_range[nscan_ft0] = {-2, -1.8, -1.4, -1.2, -1, -0.7, -0.5, -0.3, -0.2, -0.18, -0.14, -0.12, -0.1, -0.08, -0.06, -0.04, -0.02, 0., 0.02, 0.04, 0.06, 0.08, 0.1, 0.12, 0.14, 0.18, 0.2, 0.3, 0.5, 0.7, 1, 1.2, 1.4, 1.8, 2};
const double AQGC_ft1_range[nscan_ft1] = {-2, -1.8, -1.4, -1.2, -1, -0.7, -0.5, -0.3, -0.2, -0.18, -0.14, -0.12, -0.1, -0.08, -0.06, -0.04, -0.02, 0., 0.02, 0.04, 0.06, 0.08, 0.1, 0.12, 0.14, 0.18, 0.2, 0.3, 0.5, 0.7, 1, 1.2, 1.4, 1.8, 2};
const double AQGC_ft2_range[nscan_ft2] = {-4.5, -3.9, -3.4, -2.9, -2.5, -1.7, -1.2, -0.9, -0.7, -0.5, -0.32, -0.26, -0.2, -0.14, -0.08, -0.04, -0.02, 0., 0.02, 0.04, 0.08, 0.14, 0.2, 0.26, 0.32, 0.5, 0.7, 0.9, 1.2, 1.7, 2.5, 2.9, 3.4, 3.9, 4.5};
const double AQGC_fm0_range[nscan_fm0] = {-10, -9, -8, -7, -6, -5, -4, -3, -2, -1.5, -1, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0., 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.5, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const double AQGC_fm1_range[nscan_fm1] = {-30, -28, -23, -21, -18, -15, -13, -10, -5, -3, -2.5, -2.1, -1.8, -1.5, -1.2, -0.9, -0.6, -0.3, 0., 0.3, 0.6, 0.9, 1.2, 1.5, 1.8, 2.1, 2.5, 3, 5, 10, 13, 15, 18, 21, 23, 28, 30};
const double AQGC_fm6_range[nscan_fm6] = {-20, -18, -15, -12, -10, -7, -5, -3, -2, -1.8, -1.6, -1.4, -1.2, -1.0, -0.7, -0.5, -0.2, 0, 0.2, 0.5, 0.7, 1.0, 1.2, 1.4, 1.6, 1.8, 2, 3, 5, 7, 10, 12, 15, 18, 20};
const double AQGC_fm7_range[nscan_fm7] = {-40, -35, -30, -25, -20, -15, -10, -5, -3.5, -3, -2.5, -2, -1.5, -1, -0.5, 0., 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 5, 10, 15, 20, 25, 30, 35, 40};
const double AQGC_fs0_range[nscan_fs0] = {-50, -45, -40, -35, -30, -20, -10, -8, -6, -5, -4, -3, -2.5, -2, -1.5, -1.2, -1, -0.8, -0.6, -0.4, -0.2, 0., 0.2, 0.4, 0.6, 0.8, 1, 1.2, 1.5, 2, 2.5, 3, 4, 5, 6, 8, 10, 20, 30, 35, 40, 45, 50};
const double AQGC_fs1_range[nscan_fs1] = {-35, -33, -30, -25, -20, -15, -10, -7.5, -5, -4, -3, -2.5, -2, -1.5, -1, -0.5, 0., 0.5, 1, 1.5, 2, 2.5, 3, 4, 5, 7.5, 10, 15, 20, 25, 30, 33, 35};



void sswwaQGC(
int year, bool isDesk014 = false, TString WZName = "WZ3l_MG"
){
  int nTypeLepSel[2] = {-1, -1};
  int whichYear = -1;
  if     (year == 2016) {whichYear = Y2016; nTypeLepSel[0] =  2; nTypeLepSel[1] = 7;}
  else if(year == 2017) {whichYear = Y2017; nTypeLepSel[0] = 13; nTypeLepSel[1] = 7;}
  else if(year == 2018) {whichYear = Y2018; nTypeLepSel[0] = 15; nTypeLepSel[1] = 7;}
  else {printf("Wrong year (%d)!\n",year); return;}

  TString fidAnaName = "_aQGC";

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

      infileName_.push_back(Form("%sWWjj_SS_dim8_ewk.root" ,filesPath.Data()));   infileCat_.push_back(kPlotEWKSSWW);
      infileName_.push_back(Form("%sWZjj_dim8_ewk.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotEWKWZ);

      infileName_.push_back(Form("%sWpWp_QCD.root" ,filesPath.Data())); 	  infileCat_.push_back(kPlotQCDSSWW);

      infileName_.push_back(Form("%sWZ3l_MG_QCD.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWZ);

      infileName_.push_back(Form("%sZZJJQCD.root" ,filesPath.Data()));            infileCat_.push_back(kPlotZZ);
      infileName_.push_back(Form("%sZZJJEWK.root" ,filesPath.Data()));            infileCat_.push_back(kPlotZZ);
      infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data()));               infileCat_.push_back(kPlotZZ);

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

      infileName_.push_back(Form("%sWWjj_SS_dim8_ewk.root" ,filesPath.Data()));   infileCat_.push_back(kPlotEWKSSWW);
      infileName_.push_back(Form("%sWZjj_dim8_ewk.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotEWKWZ);

      infileName_.push_back(Form("%sWpWp_QCD.root" ,filesPath.Data())); 	  infileCat_.push_back(kPlotQCDSSWW);

      infileName_.push_back(Form("%sWZ3l_MG_QCD.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWZ);

      infileName_.push_back(Form("%sZZJJQCD.root" ,filesPath.Data()));            infileCat_.push_back(kPlotZZ);
      infileName_.push_back(Form("%sZZJJEWK.root" ,filesPath.Data()));            infileCat_.push_back(kPlotZZ);
      infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data()));               infileCat_.push_back(kPlotZZ);

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

      infileName_.push_back(Form("%sWWjj_SS_dim8_ewk.root" ,filesPath.Data()));   infileCat_.push_back(kPlotEWKSSWW);
      infileName_.push_back(Form("%sWZjj_dim8_ewk.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotEWKWZ);

      infileName_.push_back(Form("%sWpWp_QCD.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotQCDSSWW);

      infileName_.push_back(Form("%sWZ3l_MG_QCD.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotWZ);

      infileName_.push_back(Form("%sZZJJQCD.root" ,filesPath.Data()));            infileCat_.push_back(kPlotZZ);
      infileName_.push_back(Form("%sZZJJEWK.root" ,filesPath.Data()));            infileCat_.push_back(kPlotZZ);
      infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data()));               infileCat_.push_back(kPlotZZ);

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


  //const int nBinAQGCMTW = 3; Float_t xbinsAQGCMTW[nBinAQGCMTW+1] = {0,100,200,300,400,500,600,700,800};
  /*
  const int nBinMVA = 52; Float_t xbins[nBinMVA+1] = {500, 800, 1200, 1800, 2000,
                                                          2800, 3200, 3800, 4000,
						          4800, 5200, 5800, 6000,
						          6800, 7200, 7800, 8000,
						          8800, 9200, 9800,10000,
						         10800,11200,11800,12000,
						         12800,13200,13800,14000,
						         14800,15200,15800,16000,
						         16800,17200,17800,18000,
						         18800,19200,19800,20000,
							 20800,21200,21800,22000,
							 22800,23200,23800,24000,
						         24950,25150,25390,26000
							 };


  if(fidAna == 3){
    xbins[33] = 17200; xbins[34] = 18000;
    xbins[35] = 19200; xbins[36] = 20000;
    xbins[37] = 21200; xbins[38] = 22000;
    for(int i=39; i<=nBinMVA; i++) xbins[i] = 22000 + 0.001*i;
  }
  */

  const int nBinMJJ = 8; Float_t xbinsMJJ[nBinMJJ+1] = {500,650,800,1000,1200,1500,1800,2300,3000};
  const int nBinMJJCR = 4; Float_t xbinsMJJCR[nBinMJJCR+1] = {500,800,1200,1800,3000};
  const int nBinMLL = 4; Float_t xbinsMLL[nBinMLL+1] = {20, 80, 140, 240, 500};
  const int nBinWWMT = 5; Float_t xbinsWWMT[nBinWWMT+1] = {0., 350, 650, 850, 1050, 1250};
  const int nBinWZMT = 5; Float_t xbinsWZMT[nBinWZMT+1] = {0., 400, 750, 1050, 1350, 1650};
  const int nBinWZBDT = 8; Float_t xbinsWZBDT[nBinWZBDT+1] = {-1.000,-0.280,-0.000, 0.230, 0.430, 0.600, 0.740, 0.860, 1.000};
  const int nBinWWBDT = 7; Float_t xbinsWWBDT[nBinWWBDT+1] = {-1.000,-0.244, 0.040, 0.243, 0.401, 0.535, 0.662, 1.000}; // V1_v6


  TH1D* histo_mT_ww[nPlotCategories];
  TH1D* histo_mT_wz[nPlotCategories];
  TH2D* histo_mT_mll[nPlotCategories];
  for(int i=0; i<nPlotCategories; i++){
     histo_mT_ww[i] = new TH1D(Form("histo_mT_ww_%d",i), Form("histo_mT_ww_%d",i), nBinWWMT, xbinsWWMT);
     histo_mT_wz[i] = new TH1D(Form("histo_mT_wz_%d",i), Form("histo_mT_wz_%d",i), nBinWZMT, xbinsWZMT);
     histo_mT_mll[i]= new TH2D(Form("histo_mT_mll_%d",i), Form("histo_mT_mll_%d",i), 100 ,0,4000,100,0,2000);
  }



  const int nBinMVA = 36; Float_t xbins[nBinMVA+1];
  const int nBinMVA_ww =24; Float_t xbins_ww[nBinMVA_ww+1];
  const int nBinMVA_wz = 10; Float_t xbins_wz[nBinMVA_wz+1];
  for(int nb=0; nb<=nBinMVA; nb++) xbins[nb] = -0.5 + nb;
  for(int nb=0; nb<=nBinMVA_ww; nb++) xbins_ww[nb] = -0.5 + nb;
  for(int nb=0; nb<=nBinMVA_wz; nb++) xbins_wz[nb] = -0.5 + nb;


  const int nBinMVA_interval = 2; //unuseds regions in aQGC


  TH1D* histo[nPlotCategories];
  for(int i=0; i<nPlotCategories; i++) histo[i] = new TH1D(Form("histo_%d",i), Form("histo_%d",i), nBinMVA, xbins);


  TH1D* histo_MVA;
  TH1D* histo_MVA_dim8[2];  // 0--WW, 1--WZ
  histo_MVA = new TH1D("histo_MVA", "histo_MVA", nBinMVA, xbins); histo_MVA->Sumw2();
  histo_MVA_dim8[0] = new TH1D("histo_MVA_aqgc_ww", "histo_MVA_aqgc_ww", nBinMVA_ww, xbins_ww); histo_MVA_dim8[0]->Sumw2();
  histo_MVA_dim8[1] = new TH1D("histo_MVA_aqgc_wz", "histo_MVA_aqgc_wz", nBinMVA_wz, xbins_wz); histo_MVA_dim8[1]->Sumw2();


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

  TH1D *histo_dim8_Baseline[2][nPlotCategories];
  TH1D *histo_dim8_QCDScaleUp[2][nPlotCategories];
  TH1D *histo_dim8_QCDScaleDown[2][nPlotCategories];
  TH1D *histo_dim8_PDFBoundingUp[2][nPlotCategories];
  TH1D *histo_dim8_PDFBoundingDown[2][nPlotCategories];
  TH1D *histo_dim8_LepEffMBoundingUp[2][nPlotCategories];
  TH1D *histo_dim8_LepEffMBoundingDown[2][nPlotCategories];
  TH1D *histo_dim8_LepEffEBoundingUp[2][nPlotCategories];
  TH1D *histo_dim8_LepEffEBoundingDown[2][nPlotCategories];
  TH1D *histo_dim8_PUBoundingUp[2][nPlotCategories];
  TH1D *histo_dim8_PUBoundingDown[2][nPlotCategories];
  TH1D *histo_dim8_BTAGBBoundingUp[2][nYears][nPlotCategories];
  TH1D *histo_dim8_BTAGBBoundingDown[2][nYears][nPlotCategories];
  TH1D *histo_dim8_BTAGLBoundingUp[2][nYears][nPlotCategories];
  TH1D *histo_dim8_BTAGLBoundingDown[2][nYears][nPlotCategories];
  TH1D *histo_dim8_JESBoundingUp[2][nYears][nPlotCategories];
  TH1D *histo_dim8_JESBoundingDown[2][nYears][nPlotCategories];
  TH1D *histo_dim8_JERBoundingUp[2][nYears][nPlotCategories];
  TH1D *histo_dim8_JERBoundingDown[2][nYears][nPlotCategories];
  TH1D *histo_dim8_PreFireBoundingUp[2][nYears][nPlotCategories];
  TH1D *histo_dim8_PreFireBoundingDown[2][nYears][nPlotCategories];
  TH1D *histo_dim8_TriggerBoundingUp[2][nYears][nPlotCategories];
  TH1D *histo_dim8_TriggerBoundingDown[2][nYears][nPlotCategories];
  TH1D *histo_dim8_WSBoundingUp[2][nPlotCategories];
  TH1D *histo_dim8_WSBoundingDown[2][nPlotCategories];
  TH1D *histo_dim8_EWKCorrVVUp[2][nPlotCategories];
  TH1D *histo_dim8_EWKCorrVVDown[2][nPlotCategories];
  TH1D *histo_dim8_EWKqqZZCorrUp[2][nPlotCategories];
  TH1D *histo_dim8_EWKqqZZCorrDown[2][nPlotCategories];
  TH1D *histo_dim8_ggZZCorrUp[2][nPlotCategories];
  TH1D *histo_dim8_ggZZCorrDown[2][nPlotCategories];
  TH1D *histo_dim8_WZTauHUp[2][nPlotCategories];
  TH1D *histo_dim8_WZTauHDown[2][nPlotCategories];
  TH1D *histo_dim8_WZTauLUp[2][nPlotCategories];
  TH1D *histo_dim8_WZTauLDown[2][nPlotCategories];


  TH1D *histo_aqgc_ft0_Baseline[2][nscan_ft0];
  TH1D *histo_aqgc_ft1_Baseline[2][nscan_ft1];
  TH1D *histo_aqgc_ft2_Baseline[2][nscan_ft2];
  TH1D *histo_aqgc_fm0_Baseline[2][nscan_fm0];
  TH1D *histo_aqgc_fm1_Baseline[2][nscan_fm1];
  TH1D *histo_aqgc_fm6_Baseline[2][nscan_fm6];
  TH1D *histo_aqgc_fm7_Baseline[2][nscan_fm7];
  TH1D *histo_aqgc_fs0_Baseline[2][nscan_fs0];
  TH1D *histo_aqgc_fs1_Baseline[2][nscan_fs1];

  TGraphAsymmErrors *aqgc_ft0_full[2][nBinMVA_ww];
  TGraphAsymmErrors *aqgc_ft1_full[2][nBinMVA_ww];
  TGraphAsymmErrors *aqgc_ft2_full[2][nBinMVA_ww];
  TGraphAsymmErrors *aqgc_fm0_full[2][nBinMVA_ww];
  TGraphAsymmErrors *aqgc_fm1_full[2][nBinMVA_ww];
  TGraphAsymmErrors *aqgc_fm6_full[2][nBinMVA_ww];
  TGraphAsymmErrors *aqgc_fm7_full[2][nBinMVA_ww];
  TGraphAsymmErrors *aqgc_fs0_full[2][nBinMVA_ww];
  TGraphAsymmErrors *aqgc_fs1_full[2][nBinMVA_ww];


  
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
    histo_WZTauHUp              [ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_WZTauHUp"           , plotBaseNames[ic].Data()));
    histo_WZTauHDown            [ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_WZTauHDown"         , plotBaseNames[ic].Data()));
    histo_WZTauLUp              [ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_WZTauLUp"           , plotBaseNames[ic].Data()));
    histo_WZTauLDown            [ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_WZTauLDown"         , plotBaseNames[ic].Data()));


    for(int itype = 0; itype != 2; itype++){
      if(ic==kPlotData) histo_dim8_Baseline [itype][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("%s"                    , plotBaseNames[ic].Data()));
      else histo_dim8_Baseline              [itype][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s"              , plotBaseNames[ic].Data()));
      histo_dim8_QCDScaleUp            [itype][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_QCDScale_%s_ACCEPTUp"         , plotBaseNames[ic].Data(), plotBaseNames[ic].Data()));
      histo_dim8_QCDScaleDown          [itype][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_QCDScale_%s_ACCEPTDown"       , plotBaseNames[ic].Data(), plotBaseNames[ic].Data()));
      histo_dim8_PDFBoundingUp         [itype][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_PDFUp"              , plotBaseNames[ic].Data()));
      histo_dim8_PDFBoundingDown       [itype][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_PDFDown"            , plotBaseNames[ic].Data()));
      histo_dim8_LepEffMBoundingUp     [itype][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_eff_mUp"        , plotBaseNames[ic].Data()));
      histo_dim8_LepEffMBoundingDown   [itype][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_eff_mDown"      , plotBaseNames[ic].Data()));
      histo_dim8_LepEffEBoundingUp     [itype][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_eff_eUp"        , plotBaseNames[ic].Data()));
      histo_dim8_LepEffEBoundingDown   [itype][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_eff_eDown"      , plotBaseNames[ic].Data()));
      histo_dim8_PUBoundingUp          [itype][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_puUp"           , plotBaseNames[ic].Data()));
      histo_dim8_PUBoundingDown        [itype][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_puDown"         , plotBaseNames[ic].Data()));
      for(int ny=0; ny<nYears; ny++){
        histo_dim8_BTAGBBoundingUp    [itype][ny][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_btagb_%dUp"     , plotBaseNames[ic].Data(),2016+ny));
        histo_dim8_BTAGBBoundingDown  [itype][ny][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_btagb_%dDown"   , plotBaseNames[ic].Data(),2016+ny));
        histo_dim8_BTAGLBoundingUp    [itype][ny][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_btagl_%dUp"     , plotBaseNames[ic].Data(),2016+ny));
        histo_dim8_BTAGLBoundingDown  [itype][ny][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_btagl_%dDown"   , plotBaseNames[ic].Data(),2016+ny));
        histo_dim8_JESBoundingUp      [itype][ny][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_jes_%dUp"       , plotBaseNames[ic].Data(),2016+ny));
        histo_dim8_JESBoundingDown    [itype][ny][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_jes_%dDown"     , plotBaseNames[ic].Data(),2016+ny));
        histo_dim8_JERBoundingUp      [itype][ny][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_jer_%dUp"       , plotBaseNames[ic].Data(),2016+ny));
        histo_dim8_JERBoundingDown    [itype][ny][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_jer_%dDown"     , plotBaseNames[ic].Data(),2016+ny));
        histo_dim8_PreFireBoundingUp  [itype][ny][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_prefire_%dUp"   , plotBaseNames[ic].Data(),2016+ny));
        histo_dim8_PreFireBoundingDown[itype][ny][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_prefire_%dDown" , plotBaseNames[ic].Data(),2016+ny));
        histo_dim8_TriggerBoundingUp  [itype][ny][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_trigger_%dUp"   , plotBaseNames[ic].Data(),2016+ny));
        histo_dim8_TriggerBoundingDown[itype][ny][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_trigger_%dDown" , plotBaseNames[ic].Data(),2016+ny));
      }
      histo_dim8_WSBoundingUp          [itype][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_wseffUp"        , plotBaseNames[ic].Data()));
      histo_dim8_WSBoundingDown        [itype][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_wseffDown"      , plotBaseNames[ic].Data()));
      histo_dim8_EWKCorrVVUp           [itype][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_EWKCorrVV%sUp"      , plotBaseNames[ic].Data(), plotBaseNames[ic].Data()));
      histo_dim8_EWKCorrVVDown         [itype][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_EWKCorrVV%sDown"    , plotBaseNames[ic].Data(), plotBaseNames[ic].Data()));
      histo_dim8_EWKqqZZCorrUp         [itype][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_EWKqqZZCorrUp"      , plotBaseNames[ic].Data()));
      histo_dim8_EWKqqZZCorrDown       [itype][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_EWKqqZZCorrDown"    , plotBaseNames[ic].Data()));
      histo_dim8_ggZZCorrUp            [itype][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_ggZZCorrUp"         , plotBaseNames[ic].Data()));
      histo_dim8_ggZZCorrDown          [itype][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_ggZZCorrDown"       , plotBaseNames[ic].Data()));
      histo_dim8_WZTauHUp              [itype][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_WZTauHUp"           , plotBaseNames[ic].Data()));
      histo_dim8_WZTauHDown            [itype][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_WZTauHDown"         , plotBaseNames[ic].Data()));
      histo_dim8_WZTauLUp              [itype][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_WZTauLUp"           , plotBaseNames[ic].Data()));
      histo_dim8_WZTauLDown            [itype][ic] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_WZTauLDown"         , plotBaseNames[ic].Data()));
    }   


    if(ic == kPlotEWKWZ || ic == kPlotEWKSSWW){
      int icc = (ic == kPlotEWKWZ) ? 1 : 0;
      for(int iscan=0; iscan<nscan_ft0; iscan++) histo_aqgc_ft0_Baseline[icc][iscan]=(TH1D*)histo_MVA_dim8[icc]->Clone(Form("histo_aqgc_ft0_%s_%f", plotBaseNames[ic].Data(), AQGC_ft0_range[iscan]));
      for(int iscan=0; iscan<nscan_ft1; iscan++) histo_aqgc_ft1_Baseline[icc][iscan]=(TH1D*)histo_MVA_dim8[icc]->Clone(Form("histo_aqgc_ft1_%s_%f", plotBaseNames[ic].Data(), AQGC_ft1_range[iscan]));
      for(int iscan=0; iscan<nscan_ft2; iscan++) histo_aqgc_ft2_Baseline[icc][iscan]=(TH1D*)histo_MVA_dim8[icc]->Clone(Form("histo_aqgc_ft2_%s_%f", plotBaseNames[ic].Data(), AQGC_ft2_range[iscan]));
      for(int iscan=0; iscan<nscan_fm0; iscan++) histo_aqgc_fm0_Baseline[icc][iscan]=(TH1D*)histo_MVA_dim8[icc]->Clone(Form("histo_aqgc_fm0_%s_%f", plotBaseNames[ic].Data(), AQGC_fm0_range[iscan]));
      for(int iscan=0; iscan<nscan_fm1; iscan++) histo_aqgc_fm1_Baseline[icc][iscan]=(TH1D*)histo_MVA_dim8[icc]->Clone(Form("histo_aqgc_fm1_%s_%f", plotBaseNames[ic].Data(), AQGC_fm1_range[iscan]));
      for(int iscan=0; iscan<nscan_fm6; iscan++) histo_aqgc_fm6_Baseline[icc][iscan]=(TH1D*)histo_MVA_dim8[icc]->Clone(Form("histo_aqgc_fm6_%s_%f", plotBaseNames[ic].Data(), AQGC_fm6_range[iscan]));
      for(int iscan=0; iscan<nscan_fm7; iscan++) histo_aqgc_fm7_Baseline[icc][iscan]=(TH1D*)histo_MVA_dim8[icc]->Clone(Form("histo_aqgc_fm7_%s_%f", plotBaseNames[ic].Data(), AQGC_fm7_range[iscan]));
      for(int iscan=0; iscan<nscan_fs0; iscan++) histo_aqgc_fs0_Baseline[icc][iscan]=(TH1D*)histo_MVA_dim8[icc]->Clone(Form("histo_aqgc_fs0_%s_%f", plotBaseNames[ic].Data(), AQGC_fs0_range[iscan]));
      for(int iscan=0; iscan<nscan_fs1; iscan++) histo_aqgc_fs1_Baseline[icc][iscan]=(TH1D*)histo_MVA_dim8[icc]->Clone(Form("histo_aqgc_fs1_%s_%f", plotBaseNames[ic].Data(), AQGC_fs1_range[iscan]));

      int nBinMVA_dim8 = (icc == 0) ? nBinMVA_ww : nBinMVA_wz;
      for(int isbin=0; isbin<nBinMVA_dim8; isbin++){ 
        aqgc_ft0_full[icc][isbin] = new TGraphAsymmErrors(nscan_ft0);
        aqgc_ft1_full[icc][isbin] = new TGraphAsymmErrors(nscan_ft1);
        aqgc_ft2_full[icc][isbin] = new TGraphAsymmErrors(nscan_ft2);
        aqgc_fm0_full[icc][isbin] = new TGraphAsymmErrors(nscan_fm0);
        aqgc_fm1_full[icc][isbin] = new TGraphAsymmErrors(nscan_fm1);
        aqgc_fm6_full[icc][isbin] = new TGraphAsymmErrors(nscan_fm6);
        aqgc_fm7_full[icc][isbin] = new TGraphAsymmErrors(nscan_fm7);
        aqgc_fs0_full[icc][isbin] = new TGraphAsymmErrors(nscan_fs0);
        aqgc_fs1_full[icc][isbin] = new TGraphAsymmErrors(nscan_fs1);
        aqgc_ft0_full[icc][isbin]->SetNameTitle(Form("graph_aqgc_ft0_%s_bin%i", plotBaseNames[ic].Data(),isbin+1),Form("graph_aqgc_ft0_%s_bin%i", plotBaseNames[ic].Data(),isbin+1));
        aqgc_ft1_full[icc][isbin]->SetNameTitle(Form("graph_aqgc_ft1_%s_bin%i", plotBaseNames[ic].Data(),isbin+1),Form("graph_aqgc_ft1_%s_bin%i", plotBaseNames[ic].Data(),isbin+1));
        aqgc_ft2_full[icc][isbin]->SetNameTitle(Form("graph_aqgc_ft2_%s_bin%i", plotBaseNames[ic].Data(),isbin+1),Form("graph_aqgc_ft2_%s_bin%i", plotBaseNames[ic].Data(),isbin+1));
        aqgc_fm0_full[icc][isbin]->SetNameTitle(Form("graph_aqgc_fm0_%s_bin%i", plotBaseNames[ic].Data(),isbin+1),Form("graph_aqgc_fm0_%s_bin%i", plotBaseNames[ic].Data(),isbin+1));
        aqgc_fm1_full[icc][isbin]->SetNameTitle(Form("graph_aqgc_fm1_%s_bin%i", plotBaseNames[ic].Data(),isbin+1),Form("graph_aqgc_fm1_%s_bin%i", plotBaseNames[ic].Data(),isbin+1));
        aqgc_fm6_full[icc][isbin]->SetNameTitle(Form("graph_aqgc_fm6_%s_bin%i", plotBaseNames[ic].Data(),isbin+1),Form("graph_aqgc_fm6_%s_bin%i", plotBaseNames[ic].Data(),isbin+1));
        aqgc_fm7_full[icc][isbin]->SetNameTitle(Form("graph_aqgc_fm7_%s_bin%i", plotBaseNames[ic].Data(),isbin+1),Form("graph_aqgc_fm7_%s_bin%i", plotBaseNames[ic].Data(),isbin+1));
        aqgc_fs0_full[icc][isbin]->SetNameTitle(Form("graph_aqgc_fs0_%s_bin%i", plotBaseNames[ic].Data(),isbin+1),Form("graph_aqgc_fs0_%s_bin%i", plotBaseNames[ic].Data(),isbin+1));
        aqgc_fs1_full[icc][isbin]->SetNameTitle(Form("graph_aqgc_fs1_%s_bin%i", plotBaseNames[ic].Data(),isbin+1),Form("graph_aqgc_fs1_%s_bin%i", plotBaseNames[ic].Data(),isbin+1));
      }
    } // end if aQGC signal samples	
  }
  TH1D *histo_FakeBoundingUp  [nYears][8];
  TH1D *histo_FakeBoundingDown[nYears][8];
  TH1D *histo_dim8_FakeBoundingUp  [2][nYears][8];
  TH1D *histo_dim8_FakeBoundingDown[2][nYears][8];

  for(int ny=0; ny<nYears; ny++){
     histo_FakeBoundingUp  [ny][0] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fakeMP_%dUp"   , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
     histo_FakeBoundingDown[ny][0] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fakeMP_%dDown" , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
     histo_FakeBoundingUp  [ny][1] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fakeMN_%dUp"   , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
     histo_FakeBoundingDown[ny][1] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fakeMN_%dDown" , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
     histo_FakeBoundingUp  [ny][2] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fakeEP_%dUp"   , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
     histo_FakeBoundingDown[ny][2] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fakeEP_%dDown" , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
     histo_FakeBoundingUp  [ny][3] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fakeEN_%dUp"   , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
     histo_FakeBoundingDown[ny][3] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fakeEN_%dDown" , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
     histo_FakeBoundingUp  [ny][4] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fakeM_%dUp"    , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
     histo_FakeBoundingDown[ny][4] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fakeM_%dDown"  , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
     histo_FakeBoundingUp  [ny][5] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fakeE_%dUp"    , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
     histo_FakeBoundingDown[ny][5] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fakeE_%dDown"  , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
     histo_FakeBoundingUp  [ny][6] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fakeM3L_%dUp"  , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
     histo_FakeBoundingDown[ny][6] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fakeM3L_%dDown", plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
     histo_FakeBoundingUp  [ny][7] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fakeE3L_%dUp"  , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
     histo_FakeBoundingDown[ny][7] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fakeE3L_%dDown", plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
     for(int itype=0; itype<2; itype++){
       histo_dim8_FakeBoundingUp  [itype][ny][0] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_fakeMP_%dUp"   , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
       histo_dim8_FakeBoundingDown[itype][ny][0] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_fakeMP_%dDown" , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
       histo_dim8_FakeBoundingUp  [itype][ny][1] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_fakeMN_%dUp"   , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
       histo_dim8_FakeBoundingDown[itype][ny][1] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_fakeMN_%dDown" , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
       histo_dim8_FakeBoundingUp  [itype][ny][2] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_fakeEP_%dUp"   , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
       histo_dim8_FakeBoundingDown[itype][ny][2] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_fakeEP_%dDown" , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
       histo_dim8_FakeBoundingUp  [itype][ny][3] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_fakeEN_%dUp"   , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
       histo_dim8_FakeBoundingDown[itype][ny][3] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_fakeEN_%dDown" , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
       histo_dim8_FakeBoundingUp  [itype][ny][4] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_fakeM_%dUp"    , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
       histo_dim8_FakeBoundingDown[itype][ny][4] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_fakeM_%dDown"  , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
       histo_dim8_FakeBoundingUp  [itype][ny][5] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_fakeE_%dUp"    , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
       histo_dim8_FakeBoundingDown[itype][ny][5] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_fakeE_%dDown"  , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
       histo_dim8_FakeBoundingUp  [itype][ny][6] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_fakeM3L_%dUp"  , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
       histo_dim8_FakeBoundingDown[itype][ny][6] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_fakeM3L_%dDown", plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
       histo_dim8_FakeBoundingUp  [itype][ny][7] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_fakeE3L_%dUp"  , plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
       histo_dim8_FakeBoundingDown[itype][ny][7] = (TH1D*)histo_MVA_dim8[itype]->Clone(Form("dim8_%s_CMS_fakeE3L_%dDown", plotBaseNames[kPlotNonPrompt].Data(), 2016+ny));
     }
  }


  //*******************************************************
  // Chain Loop
  //*******************************************************
//  for(UInt_t ifile=2; ifile<3; ifile++) {
  for(UInt_t ifile=0; ifile<infileName_.size(); ifile++) {
	//if(ifile!=1 && ifile!=2 && ifile!=17 && ifile!=18) continue;
    printf("sampleNames(%d): %s\n",ifile,infileName_[ifile].Data());
    TFile *the_input_file = TFile::Open(infileName_[ifile].Data());
    TTree *the_input_tree = (TTree*)the_input_file->FindObjectAny("events");


    if(debug != 0 && infileCat_[ifile] != 0) return;


    //float xs_wei = 0;

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

      //printf("evt%i : re-weights: %f\n",jentry, thePandaFlat.rw_fm0_0p9);

      bool passTrigger = (thePandaFlat.trigger & (1<<kEMuTrig)) != 0       || (thePandaFlat.trigger & (1<<kDoubleMuTrig)) != 0  ||
                         (thePandaFlat.trigger & (1<<kSingleMuTrig)) != 0  || (thePandaFlat.trigger & (1<<kDoubleEleTrig)) != 0 ||
                         (thePandaFlat.trigger & (1<<kSingleEleTrig)) != 0;
      if(passTrigger == false) continue;
      if(thePandaFlat.metFilter == 0) continue;
      if(debug == 2) printf("STEP2 %llu\n",thePandaFlat.eventNumber);

      bool passJetPtEtaCut = false;
      if(thePandaFlat.nJot >= 2){
        passJetPtEtaCut = thePandaFlat.jotPt[0] > jetPtCut && thePandaFlat.jotPt[1] > jetPtCut;
	if(TMath::Abs(thePandaFlat.jotEta[0]) > 2.4) passJetPtEtaCut = passJetPtEtaCut && thePandaFlat.jotPt[0] > jetPtCut;
	if(TMath::Abs(thePandaFlat.jotEta[1]) > 2.4) passJetPtEtaCut = passJetPtEtaCut && thePandaFlat.jotPt[1] > jetPtCut;
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
        passJetPtEtaSyst[0] = vJot1JESUp.Pt()   > jetPtCut && vJot2JESUp.Pt()   > jetPtCut;
        passJetPtEtaSyst[1] = vJot1JESDown.Pt() > jetPtCut && vJot2JESDown.Pt() > jetPtCut;
        passJetPtEtaSyst[2] = vJot1JERUp.Pt()   > jetPtCut && vJot2JERUp.Pt()   > jetPtCut;
        passJetPtEtaSyst[3] = vJot1JERDown.Pt() > jetPtCut && vJot2JERDown.Pt() > jetPtCut;
	if(TMath::Abs(vJot1.Eta()) > 2.4) {
          passJetPtEtaSyst[0] = passJetPtEtaSyst[0] && vJot1JESUp.Pt()   > jetPtCut;
          passJetPtEtaSyst[1] = passJetPtEtaSyst[1] && vJot1JESDown.Pt() > jetPtCut;
          passJetPtEtaSyst[2] = passJetPtEtaSyst[2] && vJot1JERUp.Pt()   > jetPtCut;
          passJetPtEtaSyst[3] = passJetPtEtaSyst[3] && vJot1JERDown.Pt() > jetPtCut;
	}
	if(TMath::Abs(vJot2.Eta()) > 2.4) {
          passJetPtEtaSyst[0] = passJetPtEtaSyst[0] && vJot2JESUp.Pt()   > jetPtCut;
          passJetPtEtaSyst[1] = passJetPtEtaSyst[1] && vJot2JESDown.Pt() > jetPtCut;
          passJetPtEtaSyst[2] = passJetPtEtaSyst[2] && vJot2JERUp.Pt()   > jetPtCut;
          passJetPtEtaSyst[3] = passJetPtEtaSyst[3] && vJot2JERDown.Pt() > jetPtCut;
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

      double mt2VV    = (alllep + vMet).Mt();
      double mt2VVUp  = (alllep + vMetUp).Mt();
      double mt2VVDown= (alllep + vMetDown).Mt();


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
      //bool passWZMET = vMet.Pt() > 0; bool passWZMETUp = vMetUp.Pt() > 0;bool passWZMETDown = vMetDown.Pt() > 0;
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
      bool passQCDWZSel        = passWZPresel && passWZMET     && passSel[3]	    && passSel[4]	  && passCRMJJ        && passwzZep     && passSel[7]	    && passSel[8];
      bool passQCDWZSelJESUp   = passWZPresel && passWZMETUp   && passSelJESUp[3]   && passSelJESUp[4]    && passCRMJJJESUp   && passwzZepUp   && passSelJESUp[7]   && passSelJESUp[8];
      bool passQCDWZSelJESDown = passWZPresel && passWZMETDown && passSelJESDown[3] && passSelJESDown[4]  && passCRMJJJESDown && passwzZepDown && passSelJESDown[7] && passSelJESDown[8];
      bool passQCDWZSelJERUp   = passWZPresel && passWZMET     && passSelJERUp[3]   && passSelJERUp[4]    && passCRMJJJERUp   && passwzZep     && passSelJERUp[7]   && passSelJERUp[8];
      bool passQCDWZSelJERDown = passWZPresel && passWZMET     && passSelJERDown[3] && passSelJERDown[4]  && passCRMJJJERDown && passwzZep     && passSelJERDown[7] && passSelJERDown[8];

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
					thePandaFlat.rw_ft0_m0p04, thePandaFlat.rw_ft0_m0p02, thePandaFlat.rw_ft0_0, thePandaFlat.rw_ft0_0p02, thePandaFlat.rw_ft0_0p04, 
					thePandaFlat.rw_ft0_0p06, thePandaFlat.rw_ft0_0p08, thePandaFlat.rw_ft0_0p1, thePandaFlat.rw_ft0_0p12, thePandaFlat.rw_ft0_0p14, 
					thePandaFlat.rw_ft0_0p18, thePandaFlat.rw_ft0_0p2, thePandaFlat.rw_ft0_0p3, thePandaFlat.rw_ft0_0p5, thePandaFlat.rw_ft0_0p7, 
					thePandaFlat.rw_ft0_1p0, thePandaFlat.rw_ft0_1p2, thePandaFlat.rw_ft0_1p4, thePandaFlat.rw_ft0_1p8, thePandaFlat.rw_ft0_2p0}; 

      double rw_aqgc_ft1[nscan_ft1] =  {thePandaFlat.rw_ft1_m2p0, thePandaFlat.rw_ft1_m1p8, thePandaFlat.rw_ft1_m1p4, thePandaFlat.rw_ft1_m1p2, thePandaFlat.rw_ft1_m1p0,
                                        thePandaFlat.rw_ft1_m0p7, thePandaFlat.rw_ft1_m0p5, thePandaFlat.rw_ft1_m0p3, thePandaFlat.rw_ft1_m0p2, thePandaFlat.rw_ft1_m0p18,
                                        thePandaFlat.rw_ft1_m0p14, thePandaFlat.rw_ft1_m0p12, thePandaFlat.rw_ft1_m0p1, thePandaFlat.rw_ft1_m0p08, thePandaFlat.rw_ft1_m0p06,
                                        thePandaFlat.rw_ft1_m0p04, thePandaFlat.rw_ft1_m0p02, thePandaFlat.rw_ft1_0, thePandaFlat.rw_ft1_0p02, thePandaFlat.rw_ft1_0p04,
                                        thePandaFlat.rw_ft1_0p06, thePandaFlat.rw_ft1_0p08, thePandaFlat.rw_ft1_0p1, thePandaFlat.rw_ft1_0p12, thePandaFlat.rw_ft1_0p14,
                                        thePandaFlat.rw_ft1_0p18, thePandaFlat.rw_ft1_0p2, thePandaFlat.rw_ft1_0p3, thePandaFlat.rw_ft1_0p5, thePandaFlat.rw_ft1_0p7,
                                        thePandaFlat.rw_ft1_1p0, thePandaFlat.rw_ft1_1p2, thePandaFlat.rw_ft1_1p4, thePandaFlat.rw_ft1_1p8, thePandaFlat.rw_ft1_2p0};

      double rw_aqgc_ft2[nscan_ft2] =  {thePandaFlat.rw_ft2_m4p5, thePandaFlat.rw_ft2_m3p9, thePandaFlat.rw_ft2_m3p4, thePandaFlat.rw_ft2_m2p9, thePandaFlat.rw_ft2_m2p5,
                                        thePandaFlat.rw_ft2_m1p7, thePandaFlat.rw_ft2_m1p2, thePandaFlat.rw_ft2_m0p9, thePandaFlat.rw_ft2_m0p7, thePandaFlat.rw_ft2_m0p5,
                                        thePandaFlat.rw_ft2_m0p32, thePandaFlat.rw_ft2_m0p26, thePandaFlat.rw_ft2_m0p2, thePandaFlat.rw_ft2_m0p14, thePandaFlat.rw_ft2_m0p08,
                                        thePandaFlat.rw_ft2_m0p04, thePandaFlat.rw_ft2_m0p02, thePandaFlat.rw_ft2_0, thePandaFlat.rw_ft2_0p02, thePandaFlat.rw_ft2_0p04,
                                        thePandaFlat.rw_ft2_0p08, thePandaFlat.rw_ft2_0p14, thePandaFlat.rw_ft2_0p2, thePandaFlat.rw_ft2_0p26, thePandaFlat.rw_ft2_0p32,
                                        thePandaFlat.rw_ft2_0p5, thePandaFlat.rw_ft2_0p7, thePandaFlat.rw_ft2_0p9, thePandaFlat.rw_ft2_1p2, thePandaFlat.rw_ft2_1p7,
                                        thePandaFlat.rw_ft2_2p5, thePandaFlat.rw_ft2_2p9, thePandaFlat.rw_ft2_3p4, thePandaFlat.rw_ft2_3p9, thePandaFlat.rw_ft2_4p5};

      double rw_aqgc_fm0[nscan_fm0] =  {thePandaFlat.rw_fm0_m10, thePandaFlat.rw_fm0_m9, thePandaFlat.rw_fm0_m8, thePandaFlat.rw_fm0_m7, thePandaFlat.rw_fm0_m6, 
					thePandaFlat.rw_fm0_m5, thePandaFlat.rw_fm0_m4, thePandaFlat.rw_fm0_m3, thePandaFlat.rw_fm0_m2p0, thePandaFlat.rw_fm0_m1p5, 
					thePandaFlat.rw_fm0_m1p0, thePandaFlat.rw_fm0_m0p9, thePandaFlat.rw_fm0_m0p8, thePandaFlat.rw_fm0_m0p7, thePandaFlat.rw_fm0_m0p6, 
					thePandaFlat.rw_fm0_m0p5, thePandaFlat.rw_fm0_m0p4, thePandaFlat.rw_fm0_m0p3, thePandaFlat.rw_fm0_m0p2, thePandaFlat.rw_fm0_m0p1, 
					thePandaFlat.rw_fm0_0, thePandaFlat.rw_fm0_0p1, thePandaFlat.rw_fm0_0p2, thePandaFlat.rw_fm0_0p3, thePandaFlat.rw_fm0_0p4, 
					thePandaFlat.rw_fm0_0p5, thePandaFlat.rw_fm0_0p6, thePandaFlat.rw_fm0_0p7, thePandaFlat.rw_fm0_0p8, thePandaFlat.rw_fm0_0p9, 
					thePandaFlat.rw_fm0_1p0, thePandaFlat.rw_fm0_1p5, thePandaFlat.rw_fm0_2p0, thePandaFlat.rw_fm0_3, thePandaFlat.rw_fm0_4, 
					thePandaFlat.rw_fm0_5, thePandaFlat.rw_fm0_6, thePandaFlat.rw_fm0_7, thePandaFlat.rw_fm0_8, thePandaFlat.rw_fm0_9, thePandaFlat.rw_fm0_10};

      double rw_aqgc_fm1[nscan_fm1] =  {thePandaFlat.rw_fm1_m30, thePandaFlat.rw_fm1_m28, thePandaFlat.rw_fm1_m23p0, thePandaFlat.rw_fm1_m21, thePandaFlat.rw_fm1_m18, 
					thePandaFlat.rw_fm1_m15, thePandaFlat.rw_fm1_m13, thePandaFlat.rw_fm1_m10, thePandaFlat.rw_fm1_m5p0, thePandaFlat.rw_fm1_m3p0, 
					thePandaFlat.rw_fm1_m2p5, thePandaFlat.rw_fm1_m2p1, thePandaFlat.rw_fm1_m1p8, thePandaFlat.rw_fm1_m1p5, thePandaFlat.rw_fm1_m1p2, 
					thePandaFlat.rw_fm1_m0p9, thePandaFlat.rw_fm1_m0p6, thePandaFlat.rw_fm1_m0p3, thePandaFlat.rw_fm1_0, thePandaFlat.rw_fm1_0p3, 
					thePandaFlat.rw_fm1_0p6, thePandaFlat.rw_fm1_0p9, thePandaFlat.rw_fm1_1p2, thePandaFlat.rw_fm1_1p5, thePandaFlat.rw_fm1_1p8, 
					thePandaFlat.rw_fm1_2p1, thePandaFlat.rw_fm1_2p5, thePandaFlat.rw_fm1_3p0, thePandaFlat.rw_fm1_5p0, thePandaFlat.rw_fm1_10, 
					thePandaFlat.rw_fm1_13, thePandaFlat.rw_fm1_15, thePandaFlat.rw_fm1_18, thePandaFlat.rw_fm1_21, thePandaFlat.rw_fm1_23p0, 
					thePandaFlat.rw_fm1_28, thePandaFlat.rw_fm1_30};

      double rw_aqgc_fm6[nscan_fm6] =  {thePandaFlat.rw_fm6_m20, thePandaFlat.rw_fm6_m18, thePandaFlat.rw_fm6_m15, thePandaFlat.rw_fm6_m12, thePandaFlat.rw_fm6_m10,
                                        thePandaFlat.rw_fm6_m7, thePandaFlat.rw_fm6_m5, thePandaFlat.rw_fm6_m3, thePandaFlat.rw_fm6_m2p0, thePandaFlat.rw_fm6_m1p8,
                                        thePandaFlat.rw_fm6_m1p6, thePandaFlat.rw_fm6_m1p4, thePandaFlat.rw_fm6_m1p2, thePandaFlat.rw_fm6_m1p0, thePandaFlat.rw_fm6_m0p7,
                                        thePandaFlat.rw_fm6_m0p5, thePandaFlat.rw_fm6_m0p2, thePandaFlat.rw_fm6_0, thePandaFlat.rw_fm6_0p2, thePandaFlat.rw_fm6_0p5, 
					thePandaFlat.rw_fm6_0p7, thePandaFlat.rw_fm6_1p0, thePandaFlat.rw_fm6_1p2, thePandaFlat.rw_fm6_1p4, thePandaFlat.rw_fm6_1p6, 
					thePandaFlat.rw_fm6_1p8, thePandaFlat.rw_fm6_2p0, thePandaFlat.rw_fm6_3, thePandaFlat.rw_fm6_5, thePandaFlat.rw_fm6_7, 
					thePandaFlat.rw_fm6_10, thePandaFlat.rw_fm6_12, thePandaFlat.rw_fm6_15, thePandaFlat.rw_fm6_18, thePandaFlat.rw_fm6_20};

      double rw_aqgc_fm7[nscan_fm7] =  {thePandaFlat.rw_fm7_m40, thePandaFlat.rw_fm7_m35, thePandaFlat.rw_fm7_m30, thePandaFlat.rw_fm7_m25, thePandaFlat.rw_fm7_m20,
                                        thePandaFlat.rw_fm7_m15, thePandaFlat.rw_fm7_m10, thePandaFlat.rw_fm7_m5p0, thePandaFlat.rw_fm7_m3p5, thePandaFlat.rw_fm7_m3p0,
                                        thePandaFlat.rw_fm7_m2p5, thePandaFlat.rw_fm7_m2p0, thePandaFlat.rw_fm7_m1p5, thePandaFlat.rw_fm7_m1p0, thePandaFlat.rw_fm7_m0p5,
                                        thePandaFlat.rw_fm7_0, thePandaFlat.rw_fm7_0p5, thePandaFlat.rw_fm7_1p0, thePandaFlat.rw_fm7_1p5, thePandaFlat.rw_fm7_2p0, 
					thePandaFlat.rw_fm7_2p5, thePandaFlat.rw_fm7_3p0, thePandaFlat.rw_fm7_3p5, thePandaFlat.rw_fm7_5p0, thePandaFlat.rw_fm7_10, 
					thePandaFlat.rw_fm7_15, thePandaFlat.rw_fm7_20, thePandaFlat.rw_fm7_25, thePandaFlat.rw_fm7_30, thePandaFlat.rw_fm7_35, thePandaFlat.rw_fm7_40};

      double rw_aqgc_fs0[nscan_fs0] =  {thePandaFlat.rw_fs0_m50, thePandaFlat.rw_fs0_m45, thePandaFlat.rw_fs0_m40, thePandaFlat.rw_fs0_m35, thePandaFlat.rw_fs0_m30,
                                        thePandaFlat.rw_fs0_m20, thePandaFlat.rw_fs0_m10, thePandaFlat.rw_fs0_m8, thePandaFlat.rw_fs0_m6, thePandaFlat.rw_fs0_m5,
                                        thePandaFlat.rw_fs0_m4, thePandaFlat.rw_fs0_m3p0, thePandaFlat.rw_fs0_m2p5, thePandaFlat.rw_fs0_m2p0, thePandaFlat.rw_fs0_m1p5,
					thePandaFlat.rw_fs0_m1p2, thePandaFlat.rw_fs0_m1p0, thePandaFlat.rw_fs0_m0p8, thePandaFlat.rw_fs0_m0p6, thePandaFlat.rw_fs0_m0p4,
                                        thePandaFlat.rw_fs0_m0p2, thePandaFlat.rw_fs0_0p0, thePandaFlat.rw_fs0_0p2, thePandaFlat.rw_fs0_0p4, thePandaFlat.rw_fs0_0p6, 
					thePandaFlat.rw_fs0_0p8, thePandaFlat.rw_fs0_1p0, thePandaFlat.rw_fs0_1p2, thePandaFlat.rw_fs0_1p5, thePandaFlat.rw_fs0_2p0, 
					thePandaFlat.rw_fs0_2p5, thePandaFlat.rw_fs0_3p0, thePandaFlat.rw_fs0_4, thePandaFlat.rw_fs0_5, thePandaFlat.rw_fs0_6, 
					thePandaFlat.rw_fs0_8, thePandaFlat.rw_fs0_10, thePandaFlat.rw_fs0_20, thePandaFlat.rw_fs0_30, thePandaFlat.rw_fs0_35, 
					thePandaFlat.rw_fs0_40, thePandaFlat.rw_fs0_45, thePandaFlat.rw_fs0_50};

      double rw_aqgc_fs1[nscan_fs1] =  {thePandaFlat.rw_fs1_m35, thePandaFlat.rw_fs1_m33, thePandaFlat.rw_fs1_m30, thePandaFlat.rw_fs1_m25, thePandaFlat.rw_fs1_m20,
                                        thePandaFlat.rw_fs1_m15, thePandaFlat.rw_fs1_m10, thePandaFlat.rw_fs1_m7p5, thePandaFlat.rw_fs1_m5p0, thePandaFlat.rw_fs1_m4p0, 
					thePandaFlat.rw_fs1_m3p0, thePandaFlat.rw_fs1_m2p5, thePandaFlat.rw_fs1_m2p0, thePandaFlat.rw_fs1_m1p5, thePandaFlat.rw_fs1_m1p0, 
					thePandaFlat.rw_fs1_m0p5, thePandaFlat.rw_fs1_0, thePandaFlat.rw_fs1_0p5, thePandaFlat.rw_fs1_1p0, thePandaFlat.rw_fs1_1p5, 
					thePandaFlat.rw_fs1_2p0, thePandaFlat.rw_fs1_2p5, thePandaFlat.rw_fs1_3p0, thePandaFlat.rw_fs1_4p0, thePandaFlat.rw_fs1_5p0, 
					thePandaFlat.rw_fs1_7p5, thePandaFlat.rw_fs1_10, thePandaFlat.rw_fs1_15, thePandaFlat.rw_fs1_20, thePandaFlat.rw_fs1_25, 
					thePandaFlat.rw_fs1_30, thePandaFlat.rw_fs1_33, thePandaFlat.rw_fs1_35};




      double totalWeight = 1.0; double puWeight = 1.0; double puWeightUp = 1.0; double puWeightDown = 1.0; double effWSUnc = 1.0; double sf_l1PrefireE = 1.0;
      double theQCDScale[6] = {1,1,1,1,1,1}; double thePDFScale[2] = {1,1}; double bTagSyst[4] = {1,1,1,1};
      double triggerWeights[2] = {1.0, 0.0};double fakeWeight[4] = {0,0,0,0};

      if(theCategory != kPlotData){
        // Avoid QCD scale weights that are anomalous high
        double maxQCDscale = (TMath::Abs(thePandaFlat.scale[0])+TMath::Abs(thePandaFlat.scale[1])+TMath::Abs(thePandaFlat.scale[2])+
                              TMath::Abs(thePandaFlat.scale[3])+TMath::Abs(thePandaFlat.scale[4])+TMath::Abs(thePandaFlat.scale[5]))/6.0;
        if(maxQCDscale == 0) maxQCDscale = 1;
        for(int i=0; i<6; i++) theQCDScale[i] = TMath::Abs(thePandaFlat.scale[i])/maxQCDscale;
        thePDFScale[0] = thePandaFlat.pdfUp; thePDFScale[1] = thePandaFlat.pdfDown;
        bTagSyst[0] = thePandaFlat.sf_btag0BUp  /thePandaFlat.sf_btag0;
        bTagSyst[1] = thePandaFlat.sf_btag0BDown/thePandaFlat.sf_btag0;
        bTagSyst[2] = thePandaFlat.sf_btag0MUp  /thePandaFlat.sf_btag0;
        bTagSyst[3] = thePandaFlat.sf_btag0MDown/thePandaFlat.sf_btag0;
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

	//float xs_wei = 0;
	//if(xs_wei!=thePandaFlat.normalizedWeight) {printf("xs_normalized weights: %f \n", thePandaFlat.normalizedWeight);xs_wei=thePandaFlat.normalizedWeight;}


        totalWeight = thePandaFlat.normalizedWeight * lumiV[whichYear] * puWeight * thePandaFlat.sf_l1Prefire * looseLepSF[0] * looseLepSF[1] * triggerWeights[0] * theMCPrescale;
	if(thePandaFlat.nLooseLep == 3)      totalWeight = totalWeight * looseLepSF[2];
	else if(thePandaFlat.nLooseLep == 4) totalWeight = totalWeight * looseLepSF[2] * looseLepSF[3];

        if(passBtagVeto) totalWeight = totalWeight * thePandaFlat.sf_btag0;
        else             totalWeight = totalWeight * thePandaFlat.sf_btagGT0;

        //if(infileCat_[ifile] == kPlotWZ)                                                totalWeight = totalWeight * thePandaFlat.sf_wz;
	if(infileCat_[ifile] == kPlotZZ  && 
	   (infileName_[ifile].Contains("qqZZ") == true || infileName_[ifile].Contains("ZZJJQCD") == true)) totalWeight = totalWeight * thePandaFlat.sf_zz;
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
	if(!isRS && theCategory != kPlotVG) {
          if(theCategory == kPlotEWKSSWW || theCategory == kPlotEWKWZ) totalWeight = totalWeight * rw_aqgc_ft0[17];
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
        double aQGCuseSM = 1.0;
        if(theCategory == kPlotEWKSSWW || theCategory == kPlotEWKWZ) aQGCuseSM = aQGCuseSM * rw_aqgc_ft0[17];
        for(unsigned int nl=0; nl<idLep.size(); nl++){
          if(idLep[nl] == 1) continue;
          bool applyTight = true;
          fakeSF = fakeSF * fakeRateFactor(TMath::Min((double)vLoose[nl].Pt(),44.999),TMath::Abs(vLoose[nl].Eta()),TMath::Abs(looseLepPdgId[nl]),applyTight,histoFakeEffSelMediumEtaPt_m,histoFakeEffSelMediumEtaPt_e,histoFakeEffSelTightEtaPt_m,histoFakeEffSelTightEtaPt_e);
          theCategory = kPlotNonPrompt;
          if     (looseLepPdgId[nl]==-13) fakeWeight[0]++;
          else if(looseLepPdgId[nl]== 13) fakeWeight[1]++;
          else if(looseLepPdgId[nl]==-11) fakeWeight[2]++;
          else if(looseLepPdgId[nl]== 11) fakeWeight[3]++;
          else printf("IMPOSSIBLE OPTION\n");
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
        totalWeight = totalWeight * fakeSF * aQGCuseSM;
      }


      if(theCategory != kPlotData){
        int theFileCat[2] = {theCategory, (int)passWZbSel};
        totalWeight = totalWeight * mcCorrection(0, year, thePandaFlat.jetNMBtags,thePandaFlat.jetNBtags, thePandaFlat.nJot, 0.0, theFileCat, thePandaFlat.eventNumber);
	theCategory = theFileCat[0];
      }


      double totalWeight_aqgc = totalWeight;
      double totalWeight_plot = totalWeight;

      if(theCategory == kPlotEWKSSWW || theCategory == kPlotEWKWZ) totalWeight *= rw_aqgc_ft0[17];

      
      if(theCategory == kPlotEWKSSWW || theCategory == kPlotEWKWZ){
        //totalWeight *= rw_aqgc_ft0[17];
        switch(which_para){
          case 1: totalWeight_plot *= rw_aqgc_ft0[which_point]; break;
          case 2: totalWeight_plot *= rw_aqgc_ft1[which_point]; break;
          case 3: totalWeight_plot *= rw_aqgc_ft2[which_point]; break;
          case 4: totalWeight_plot *= rw_aqgc_fm0[which_point]; break;
          case 5: totalWeight_plot *= rw_aqgc_fm1[which_point]; break;
          case 6: totalWeight_plot *= rw_aqgc_fm6[which_point]; break;
          case 7: totalWeight_plot *= rw_aqgc_fm7[which_point]; break;
          case 8: totalWeight_plot *= rw_aqgc_fs0[which_point]; break;
          case 9: totalWeight_plot *= rw_aqgc_fs1[which_point]; break;
        }
      }
       

      if(passWWSel)          {histo_mT_ww[theCategory]->Fill(TMath::Min(mt2VV,1249.999),totalWeight); histo_mT_mll[theCategory]->Fill(TMath::Min(mt2VV,3999.999),TMath::Min(mllZ,1999.999) );}
      if(passEWKWZSel)       histo_mT_wz[theCategory]->Fill(TMath::Min(mt2VV,1649.999),totalWeight);

      if(theCategory == kPlotEWKSSWW && passWWSel) histo_mT_ww[24]->Fill(TMath::Min(mt2VV,1249.999),totalWeight_plot);
      if(theCategory == kPlotEWKWZ && passEWKWZSel)   histo_mT_wz[25]->Fill(TMath::Min(mt2VV,1649.999),totalWeight_plot);


      int qTotCat = 0; if(qTot<0) qTotCat = 1;

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

	/*
        double typeSelAux0 = 0;
        if     (mllZ < 150) typeSelAux0 = 0;
        else if(mllZ < 300) typeSelAux0 = 1;
        else if(mllZ < 450) typeSelAux0 = 2;
        else if(mllZ < 600) typeSelAux0 = 3;
        else                typeSelAux0 = 4;
	*/

	double typeSelAux0[5] = {0,0,0,0,0};
        if     (mt2VV     <  350) typeSelAux0[0] = 0;
        else if(mt2VV     <  650) typeSelAux0[0] = 1;
        else if(mt2VV     <  850) typeSelAux0[0] = 2;
        else if(mt2VV     < 1050) typeSelAux0[0] = 3;
        else                      typeSelAux0[0] = 4; 
        if     (mt2VVUp   <  350) typeSelAux0[1] = 0;
        else if(mt2VVUp   <  650) typeSelAux0[1] = 1;
        else if(mt2VVUp   <  850) typeSelAux0[1] = 2;
        else if(mt2VVUp   < 1050) typeSelAux0[1] = 3;
        else                      typeSelAux0[1] = 4; 
        if     (mt2VVDown <  350) typeSelAux0[2] = 0;
        else if(mt2VVDown <  650) typeSelAux0[2] = 1;
        else if(mt2VVDown <  850) typeSelAux0[2] = 2;
        else if(mt2VVDown < 1050) typeSelAux0[2] = 3;
        else                      typeSelAux0[2] = 4; 
	typeSelAux0[3] = typeSelAux0[0];
        typeSelAux0[4] = typeSelAux0[0];


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
	/*
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
	*/
        if     (mt2VV     <  400) typeSelAux2[0] = 0;
        else if(mt2VV     <  750) typeSelAux2[0] = 1;
        else if(mt2VV     < 1050) typeSelAux2[0] = 2;
        else if(mt2VV     < 1350) typeSelAux2[0] = 3;
        else                      typeSelAux2[0] = 4;
	if(massJJ > 1200)         typeSelAux2[0] += 5;
        if     (mt2VVUp   <  400) typeSelAux2[1] = 0;
        else if(mt2VVUp   <  750) typeSelAux2[1] = 1;
        else if(mt2VVUp   < 1050) typeSelAux2[1] = 2;
        else if(mt2VVUp   < 1350) typeSelAux2[1] = 3;
        else                      typeSelAux2[1] = 4;
	if(massJJJESUp > 1200)    typeSelAux2[1] += 5;
        if     (mt2VVDown <  400) typeSelAux2[2] = 0;
        else if(mt2VVDown <  750) typeSelAux2[2] = 1;
        else if(mt2VVDown < 1050) typeSelAux2[2] = 2;
        else if(mt2VVDown < 1350) typeSelAux2[2] = 3;
        else                      typeSelAux2[2] = 4;
	if(massJJJESDown > 1200)  typeSelAux2[2] += 5;
        typeSelAux0[3] = typeSelAux0[0];
        typeSelAux0[4] = typeSelAux0[0];

	/*
	if     (mt2VV <  600) typeSelAux2[0] = 0;
        else if(mt2VV <  1200) typeSelAux2[0] = 1;
        else                 typeSelAux2[0] = 2;
        if(massJJ > 1200) typeSelAux2[0] += 3;
        if     (mt2VVUp <  600) typeSelAux2[1] = 0;
        else if(mt2VVUp <  1200) typeSelAux2[1] = 1;
        else                   typeSelAux2[1] = 2;
        if(massJJJESUp > 1200) typeSelAux2[1] += 3;
        if     (mt2VVDown <  600) typeSelAux2[2] = 0;
        else if(mt2VVDown <  1200) typeSelAux2[2] = 1;
        else                     typeSelAux2[2] = 2;
        if(massJJJESDown > 1200) typeSelAux2[2] += 3;
        typeSelAux2[3] = typeSelAux2[0];
        typeSelAux2[4] = typeSelAux2[0];
	*/

        int whichBin = 0;
        if     (dataCardSel        == 0) MVAVar        = typeSelAux0[whichBin] + 5*typeSelAux1[whichBin];
        else if(dataCardSel        == 1) MVAVar        = 20 + typeSelAux1[whichBin];
        else if(dataCardSel        == 2) MVAVar        = 24;
        else if(dataCardSel        == 3) MVAVar        = 25;
        else if(dataCardSel        == 4) MVAVar        = 26 + typeSelAux2[whichBin];

        whichBin = 1;
        if     (dataCardSelJESUp   == 0) MVAVarJESUp   = typeSelAux0[whichBin] + 5*typeSelAux1[whichBin];
        else if(dataCardSelJESUp   == 1) MVAVarJESUp   = 20 + typeSelAux1[whichBin];
        else if(dataCardSelJESUp   == 2) MVAVarJESUp   = 24;
        else if(dataCardSelJESUp   == 3) MVAVarJESUp   = 25;
        else if(dataCardSelJESUp   == 4) MVAVarJESUp   = 26 + typeSelAux2[whichBin];

        whichBin = 2;
        if     (dataCardSelJESDown == 0) MVAVarJESDown = typeSelAux0[whichBin] + 5*typeSelAux1[whichBin];
        else if(dataCardSelJESDown == 1) MVAVarJESDown = 20 + typeSelAux1[whichBin];
        else if(dataCardSelJESDown == 2) MVAVarJESDown = 24;
        else if(dataCardSelJESDown == 3) MVAVarJESDown = 25;
        else if(dataCardSelJESDown == 4) MVAVarJESDown = 26 + typeSelAux2[whichBin];

        whichBin = 3;
        if     (dataCardSelJERUp   == 0) MVAVarJERUp   = typeSelAux0[whichBin] + 5*typeSelAux1[whichBin];
        else if(dataCardSelJERUp   == 1) MVAVarJERUp   = 20 + typeSelAux1[whichBin];
        else if(dataCardSelJERUp   == 2) MVAVarJERUp   = 24;
        else if(dataCardSelJERUp   == 3) MVAVarJERUp   = 25;
        else if(dataCardSelJERUp   == 4) MVAVarJERUp   = 26 + typeSelAux2[whichBin];

        whichBin = 4;
        if     (dataCardSelJERDown == 0) MVAVarJERDown = typeSelAux0[whichBin] + 5*typeSelAux1[whichBin];
        else if(dataCardSelJERDown == 1) MVAVarJERDown = 20 + typeSelAux1[whichBin];
        else if(dataCardSelJERDown == 2) MVAVarJERDown = 24;
        else if(dataCardSelJERDown == 3) MVAVarJERDown = 25;
        else if(dataCardSelJERDown == 4) MVAVarJERDown = 26 + typeSelAux2[whichBin];

        if(MVAVar >= 32) printf("Problem with MVAVar %f %f %f %f %d\n",MVAVar,typeSelAux0,typeSelAux1[0],typeSelAux2[0],dataCardSel);

        double sf_ewkcorrvv_unc = 1.0; double sf_ewkcorrzz_unc = 1.0; double sf_ggcorrzz_unc = 1.0; double sf_corrwzzz_unc = 1.0;
	//if(theCategory == kPlotWZ) sf_ewkcorrvv_unc = 1.02;
	if(theCategory == kPlotZZ && 
	   (infileName_[ifile].Contains("qqZZ") == true || infileName_[ifile].Contains("ZZJJQCD") == true)) sf_ewkcorrzz_unc = thePandaFlat.sf_zzUnc;
	else if(theCategory == kPlotZZ && infileName_[ifile].Contains("ggZZ") == true) sf_ggcorrzz_unc = 1.10;
	if((theCategory == kPlotEWKSSWW || theCategory == kPlotEWKSSWW_dim8) && thePandaFlat.genMjj > 500) sf_ewkcorrvv_unc = hWW_KF_CMSUp->GetBinContent(hWW_KF_CMSUp->GetXaxis()->FindFixBin(TMath::Min(thePandaFlat.genMjj,1999.999f)))/
	                                                                                     hWW_KF_CMS  ->GetBinContent(hWW_KF_CMS  ->GetXaxis()->FindFixBin(TMath::Min(thePandaFlat.genMjj,1999.999f)));
	if((theCategory == kPlotEWKWZ || theCategory == kPlotEWKWZ_dim8) && thePandaFlat.genMjj > 500) sf_ewkcorrvv_unc = hWZ_KF_CMSUp->GetBinContent(hWZ_KF_CMSUp->GetXaxis()->FindFixBin(TMath::Min(thePandaFlat.genMjj,2999.999f)))/
	                                                                                   hWZ_KF_CMS  ->GetBinContent(hWZ_KF_CMS  ->GetXaxis()->FindFixBin(TMath::Min(thePandaFlat.genMjj,2999.999f)));

        if     (theCategory == kPlotData && dataCardSel >= 0){
          histo_Baseline[theCategory]->Fill(MVAVar,totalWeight);
        }
        else if(theCategory != kPlotData){
          if(theCategory == kPlotNonPrompt){
	    double totalFake = fakeWeight[0] + fakeWeight[1] + fakeWeight[2] + fakeWeight[3];
	    if(totalFake == 0) {printf("totalFake == 0\n");return;}
	    for(int ny=0; ny<nYears; ny++){
	      if(idLep.size() >= 3) {
                histo_FakeBoundingUp  [ny][0]->Fill(MVAVar,totalWeight);
                histo_FakeBoundingDown[ny][0]->Fill(MVAVar,totalWeight);
                histo_FakeBoundingUp  [ny][1]->Fill(MVAVar,totalWeight);
                histo_FakeBoundingDown[ny][1]->Fill(MVAVar,totalWeight);
                histo_FakeBoundingUp  [ny][2]->Fill(MVAVar,totalWeight);
                histo_FakeBoundingDown[ny][2]->Fill(MVAVar,totalWeight);
                histo_FakeBoundingUp  [ny][3]->Fill(MVAVar,totalWeight);
                histo_FakeBoundingDown[ny][3]->Fill(MVAVar,totalWeight);
                histo_FakeBoundingUp  [ny][4]->Fill(MVAVar,totalWeight);
                histo_FakeBoundingDown[ny][4]->Fill(MVAVar,totalWeight);
                histo_FakeBoundingUp  [ny][5]->Fill(MVAVar,totalWeight);
                histo_FakeBoundingDown[ny][5]->Fill(MVAVar,totalWeight);
	        if(ny == whichYear) {
                  histo_FakeBoundingUp  [ny][6]->Fill(MVAVar,totalWeight*(1.0+0.3*(fakeWeight[0]+fakeWeight[1])/totalFake));
                  histo_FakeBoundingDown[ny][6]->Fill(MVAVar,totalWeight/(1.0+0.3*(fakeWeight[0]+fakeWeight[1])/totalFake));
                  histo_FakeBoundingUp  [ny][7]->Fill(MVAVar,totalWeight*(1.0+0.3*(fakeWeight[2]+fakeWeight[3])/totalFake));
                  histo_FakeBoundingDown[ny][7]->Fill(MVAVar,totalWeight/(1.0+0.3*(fakeWeight[2]+fakeWeight[3])/totalFake));
                } else {
                  histo_FakeBoundingUp  [ny][6]->Fill(MVAVar,totalWeight);
                  histo_FakeBoundingDown[ny][6]->Fill(MVAVar,totalWeight);
                  histo_FakeBoundingUp  [ny][7]->Fill(MVAVar,totalWeight);
                  histo_FakeBoundingDown[ny][7]->Fill(MVAVar,totalWeight);
		}
              } else {
                histo_FakeBoundingUp  [ny][6]->Fill(MVAVar,totalWeight);
                histo_FakeBoundingDown[ny][6]->Fill(MVAVar,totalWeight);
                histo_FakeBoundingUp  [ny][7]->Fill(MVAVar,totalWeight);
                histo_FakeBoundingDown[ny][7]->Fill(MVAVar,totalWeight);
	        if(ny == whichYear) {
                  histo_FakeBoundingUp  [ny][0]->Fill(MVAVar,totalWeight*(1.0+0.3*(fakeWeight[0])/totalFake));
                  histo_FakeBoundingDown[ny][0]->Fill(MVAVar,totalWeight/(1.0+0.3*(fakeWeight[0])/totalFake));
                  histo_FakeBoundingUp  [ny][1]->Fill(MVAVar,totalWeight*(1.0+0.3*(fakeWeight[1])/totalFake));
                  histo_FakeBoundingDown[ny][1]->Fill(MVAVar,totalWeight/(1.0+0.3*(fakeWeight[1])/totalFake));
                  histo_FakeBoundingUp  [ny][2]->Fill(MVAVar,totalWeight*(1.0+0.3*(fakeWeight[2])/totalFake));
                  histo_FakeBoundingDown[ny][2]->Fill(MVAVar,totalWeight/(1.0+0.3*(fakeWeight[2])/totalFake));
                  histo_FakeBoundingUp  [ny][3]->Fill(MVAVar,totalWeight*(1.0+0.3*(fakeWeight[3])/totalFake));
                  histo_FakeBoundingDown[ny][3]->Fill(MVAVar,totalWeight/(1.0+0.3*(fakeWeight[3])/totalFake));
                  histo_FakeBoundingUp  [ny][4]->Fill(MVAVar,totalWeight*(1.0+0.3*(fakeWeight[0]+fakeWeight[1])/totalFake));
                  histo_FakeBoundingDown[ny][4]->Fill(MVAVar,totalWeight/(1.0+0.3*(fakeWeight[0]+fakeWeight[1])/totalFake));
                  histo_FakeBoundingUp  [ny][5]->Fill(MVAVar,totalWeight*(1.0+0.3*(fakeWeight[2]+fakeWeight[3])/totalFake));
                  histo_FakeBoundingDown[ny][5]->Fill(MVAVar,totalWeight/(1.0+0.3*(fakeWeight[2]+fakeWeight[3])/totalFake));
                } else {
                  histo_FakeBoundingUp  [ny][0]->Fill(MVAVar,totalWeight);
                  histo_FakeBoundingDown[ny][0]->Fill(MVAVar,totalWeight);
                  histo_FakeBoundingUp  [ny][1]->Fill(MVAVar,totalWeight);
                  histo_FakeBoundingDown[ny][1]->Fill(MVAVar,totalWeight);
                  histo_FakeBoundingUp  [ny][2]->Fill(MVAVar,totalWeight);
                  histo_FakeBoundingDown[ny][2]->Fill(MVAVar,totalWeight);
                  histo_FakeBoundingUp  [ny][3]->Fill(MVAVar,totalWeight);
                  histo_FakeBoundingDown[ny][3]->Fill(MVAVar,totalWeight);
                  histo_FakeBoundingUp  [ny][4]->Fill(MVAVar,totalWeight);
                  histo_FakeBoundingDown[ny][4]->Fill(MVAVar,totalWeight);
                  histo_FakeBoundingUp  [ny][5]->Fill(MVAVar,totalWeight);
                  histo_FakeBoundingDown[ny][5]->Fill(MVAVar,totalWeight);
		}
	      }
	    }
	  }
	  if(dataCardSel >= 0) {
            //if(theCategory == kPlotWS) printf("after reweighting SM: %f", totalWeight);
	    histo_Baseline[theCategory]->Fill(MVAVar,totalWeight);
	    histo_QCDScaleBounding[theCategory][0]->Fill(MVAVar,totalWeight*theQCDScale[0]);
	    histo_QCDScaleBounding[theCategory][1]->Fill(MVAVar,totalWeight*theQCDScale[1]);
	    histo_QCDScaleBounding[theCategory][2]->Fill(MVAVar,totalWeight*theQCDScale[2]);
	    histo_QCDScaleBounding[theCategory][3]->Fill(MVAVar,totalWeight*theQCDScale[3]);
	    histo_QCDScaleBounding[theCategory][4]->Fill(MVAVar,totalWeight*theQCDScale[4]);
	    histo_QCDScaleBounding[theCategory][5]->Fill(MVAVar,totalWeight*theQCDScale[5]);
	    histo_PDFBoundingUp[theCategory]  ->Fill(MVAVar,totalWeight*TMath::Max(thePDFScale[0],1.01));
	    histo_PDFBoundingDown[theCategory]->Fill(MVAVar,totalWeight*TMath::Min(thePDFScale[1],0.99));
            histo_LepEffMBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*muSFUnc); histo_LepEffEBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*elSFUnc);
            histo_LepEffMBoundingDown[theCategory]->Fill(MVAVar,totalWeight/muSFUnc); histo_LepEffEBoundingDown[theCategory]->Fill(MVAVar,totalWeight/elSFUnc);
            histo_PUBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*puWeightUp  /puWeight);
            histo_PUBoundingDown[theCategory]->Fill(MVAVar,totalWeight*puWeightDown/puWeight);
	    for(int ny=0; ny<nYears; ny++){
	      if(ny == whichYear) {
                histo_BTAGBBoundingUp  [ny][theCategory]->Fill(MVAVar,totalWeight*bTagSyst[0]);
                histo_BTAGBBoundingDown[ny][theCategory]->Fill(MVAVar,totalWeight*bTagSyst[1]);
                histo_BTAGLBoundingUp  [ny][theCategory]->Fill(MVAVar,totalWeight*bTagSyst[2]);
                histo_BTAGLBoundingDown[ny][theCategory]->Fill(MVAVar,totalWeight*bTagSyst[3]);
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
        }  //end else if category

        if(  (theCategory == kPlotEWKSSWW && (dataCardSel   == 0 || dataCardSel   == 1)) || (theCategory == kPlotEWKWZ &&  dataCardSel   == 4)  ){

          int icc = (theCategory == kPlotEWKWZ) ? 1 : 0;
          //MVAVar  = (icc == 0) ? MVAVar : (MVAVar-12000);
          MVAVar  = (icc == 0) ? MVAVar : (MVAVar-26);

          for(int iscan = 0; iscan < nscan_ft0; iscan++){
            rw_aqgc_ft0[iscan] *= totalWeight_aqgc;
            histo_aqgc_ft0_Baseline[icc][iscan] -> Fill(MVAVar,rw_aqgc_ft0[iscan]);
          }
	  for(int iscan = 0; iscan < nscan_ft1; iscan++){
	    rw_aqgc_ft1[iscan] *= totalWeight_aqgc;
	    histo_aqgc_ft1_Baseline[icc][iscan] -> Fill(MVAVar,rw_aqgc_ft1[iscan]);
          }
          for(int iscan = 0; iscan < nscan_ft2; iscan++){
            rw_aqgc_ft2[iscan] *= totalWeight_aqgc;
            histo_aqgc_ft2_Baseline[icc][iscan] -> Fill(MVAVar,rw_aqgc_ft2[iscan]);
          }
          for(int iscan = 0; iscan < nscan_fm0; iscan++){
            rw_aqgc_fm0[iscan] *= totalWeight_aqgc;
            histo_aqgc_fm0_Baseline[icc][iscan] -> Fill(MVAVar,rw_aqgc_fm0[iscan]);
          }
          for(int iscan = 0; iscan < nscan_fm1; iscan++){
            rw_aqgc_fm1[iscan] *= totalWeight_aqgc;
            histo_aqgc_fm1_Baseline[icc][iscan] -> Fill(MVAVar,rw_aqgc_fm1[iscan]);
          }
          for(int iscan = 0; iscan < nscan_fm6; iscan++){
            rw_aqgc_fm6[iscan] *= totalWeight_aqgc;
            histo_aqgc_fm6_Baseline[icc][iscan] -> Fill(MVAVar,rw_aqgc_fm6[iscan]);
          }
          for(int iscan = 0; iscan < nscan_fm7; iscan++){
            rw_aqgc_fm7[iscan] *= totalWeight_aqgc;
            histo_aqgc_fm7_Baseline[icc][iscan] -> Fill(MVAVar,rw_aqgc_fm7[iscan]);
          }
          for(int iscan = 0; iscan < nscan_fs0; iscan++){
            rw_aqgc_fs0[iscan] *= totalWeight_aqgc;
            histo_aqgc_fs0_Baseline[icc][iscan] -> Fill(MVAVar,rw_aqgc_fs0[iscan]);
          }
          for(int iscan = 0; iscan < nscan_fs1; iscan++){
            rw_aqgc_fs1[iscan] *= totalWeight_aqgc;
            histo_aqgc_fs1_Baseline[icc][iscan] -> Fill(MVAVar,rw_aqgc_fs1[iscan]);
          }
        } // end else if
      } // end if(1)
    } // end events loop

    the_input_file->Close();
  } // end chain loop

  for(unsigned ic=0; ic<nPlotCategories; ic++) {

    if(ic == kPlotData){
      for(int nb=1; nb<=histo_Baseline[ic]->GetNbinsX(); nb++){
        int itype = -1; int nbnew = 0;
        if(nb <= nBinMVA_ww) {itype = 0; nbnew = nb;} 
        else if(nb > nBinMVA_ww + nBinMVA_interval && nb <= nBinMVA_ww + nBinMVA_wz + nBinMVA_interval){itype = 1; nbnew = nb - (nBinMVA_ww + nBinMVA_interval);}
        else continue;
        histo_dim8_Baseline[itype][ic]->SetBinContent(nbnew, histo_Baseline[ic]->GetBinContent(nb));
      }
    }
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
      // end QCD scale uncertainties bin-by-bin

      //Refill each bin
      int itype = -1; int nbnew = 0;
      if(nb <= nBinMVA_ww) {itype = 0; nbnew = nb;}
      else if(nb > nBinMVA_ww + nBinMVA_interval && nb <= nBinMVA_ww + nBinMVA_wz + nBinMVA_interval){itype = 1; nbnew = nb - (nBinMVA_ww + nBinMVA_interval);}
      else continue;

      if(ic == kPlotNonPrompt) histo_dim8_Baseline            [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_Baseline              [ic]->GetBinContent(nb),0.01f));
      else histo_dim8_Baseline            [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_Baseline              [ic]->GetBinContent(nb),0.0f));
      histo_dim8_QCDScaleUp          [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_QCDScaleUp            [ic]->GetBinContent(nb),0.0f));
      histo_dim8_QCDScaleDown        [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_QCDScaleDown          [ic]->GetBinContent(nb),0.0f));
      histo_dim8_PDFBoundingUp       [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_PDFBoundingUp         [ic]->GetBinContent(nb),0.0f));
      histo_dim8_PDFBoundingDown     [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_PDFBoundingDown       [ic]->GetBinContent(nb),0.0f));
      histo_dim8_LepEffMBoundingUp   [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_LepEffMBoundingUp     [ic]->GetBinContent(nb),0.0f));
      histo_dim8_LepEffMBoundingDown [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_LepEffMBoundingDown   [ic]->GetBinContent(nb),0.0f));
      histo_dim8_LepEffEBoundingUp   [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_LepEffEBoundingUp     [ic]->GetBinContent(nb),0.0f));
      histo_dim8_LepEffEBoundingDown [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_LepEffEBoundingDown   [ic]->GetBinContent(nb),0.0f));
      histo_dim8_PUBoundingUp        [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_PUBoundingUp          [ic]->GetBinContent(nb),0.0f));
      histo_dim8_PUBoundingDown      [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_PUBoundingDown        [ic]->GetBinContent(nb),0.0f));
      for(int ny=0; ny<nYears; ny++){
        if(ic == kPlotNonPrompt){
          for(int nc=0; nc<8; nc++){
            histo_dim8_FakeBoundingUp  [itype][ny][nc]->SetBinContent(nbnew, TMath::Max((float)histo_FakeBoundingUp  [ny][nc]->GetBinContent(nb),0.0f));
            histo_dim8_FakeBoundingDown[itype][ny][nc]->SetBinContent(nbnew, TMath::Max((float)histo_FakeBoundingDown[ny][nc]->GetBinContent(nb),0.0f));
          }
        }
        histo_dim8_BTAGBBoundingUp    [itype][ny][ic]->SetBinContent(nbnew, TMath::Max((float)histo_BTAGBBoundingUp    [ny][ic]->GetBinContent(nb),0.0f));
        histo_dim8_BTAGBBoundingDown  [itype][ny][ic]->SetBinContent(nbnew, TMath::Max((float)histo_BTAGBBoundingDown  [ny][ic]->GetBinContent(nb),0.0f));
        histo_dim8_BTAGLBoundingUp    [itype][ny][ic]->SetBinContent(nbnew, TMath::Max((float)histo_BTAGLBoundingUp    [ny][ic]->GetBinContent(nb),0.0f));
        histo_dim8_BTAGLBoundingDown  [itype][ny][ic]->SetBinContent(nbnew, TMath::Max((float)histo_BTAGLBoundingDown  [ny][ic]->GetBinContent(nb),0.0f));
        histo_dim8_JESBoundingUp      [itype][ny][ic]->SetBinContent(nbnew, TMath::Max((float)histo_JESBoundingUp      [ny][ic]->GetBinContent(nb),0.0f));
        histo_dim8_JESBoundingDown    [itype][ny][ic]->SetBinContent(nbnew, TMath::Max((float)histo_JESBoundingDown    [ny][ic]->GetBinContent(nb),0.0f));
        histo_dim8_JERBoundingUp      [itype][ny][ic]->SetBinContent(nbnew, TMath::Max((float)histo_JERBoundingUp      [ny][ic]->GetBinContent(nb),0.0f));
        histo_dim8_JERBoundingDown    [itype][ny][ic]->SetBinContent(nbnew, TMath::Max((float)histo_JERBoundingDown    [ny][ic]->GetBinContent(nb),0.0f));
        histo_dim8_PreFireBoundingUp  [itype][ny][ic]->SetBinContent(nbnew, TMath::Max((float)histo_PreFireBoundingUp  [ny][ic]->GetBinContent(nb),0.0f));
        histo_dim8_PreFireBoundingDown[itype][ny][ic]->SetBinContent(nbnew, TMath::Max((float)histo_PreFireBoundingDown[ny][ic]->GetBinContent(nb),0.0f));
        histo_dim8_TriggerBoundingUp  [itype][ny][ic]->SetBinContent(nbnew, TMath::Max((float)histo_TriggerBoundingUp  [ny][ic]->GetBinContent(nb),0.0f));
        histo_dim8_TriggerBoundingDown[itype][ny][ic]->SetBinContent(nbnew, TMath::Max((float)histo_TriggerBoundingDown[ny][ic]->GetBinContent(nb),0.0f));
      }
      histo_dim8_WSBoundingUp        [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_WSBoundingUp          [ic]->GetBinContent(nb),0.0f));
      histo_dim8_WSBoundingDown      [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_WSBoundingDown        [ic]->GetBinContent(nb),0.0f));
      histo_dim8_EWKCorrVVUp         [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_EWKCorrVVUp           [ic]->GetBinContent(nb),0.0f));
      histo_dim8_EWKCorrVVDown       [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_EWKCorrVVDown         [ic]->GetBinContent(nb),0.0f));
      histo_dim8_EWKqqZZCorrUp       [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_EWKqqZZCorrUp         [ic]->GetBinContent(nb),0.0f));
      histo_dim8_EWKqqZZCorrDown     [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_EWKqqZZCorrDown       [ic]->GetBinContent(nb),0.0f));
      histo_dim8_ggZZCorrUp          [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_ggZZCorrUp            [ic]->GetBinContent(nb),0.0f));
      histo_dim8_ggZZCorrDown        [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_ggZZCorrDown          [ic]->GetBinContent(nb),0.0f));
      histo_dim8_WZTauHUp  	     [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_WZTauHUp              [ic]->GetBinContent(nb),0.0f));
      histo_dim8_WZTauHDown	     [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_WZTauHDown	     [ic]->GetBinContent(nb),0.0f));
      histo_dim8_WZTauLUp  	     [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_WZTauLUp              [ic]->GetBinContent(nb),0.0f));
      histo_dim8_WZTauLDown	     [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_WZTauLDown	     [ic]->GetBinContent(nb),0.0f));
    } // end loop on bins


    for(int itype=0; itype!=2; itype++){
      histo_dim8_PUBoundingUp  [itype][ic]->Scale(histo_dim8_Baseline[itype][ic]->GetSumOfWeights()/histo_dim8_PUBoundingUp  [itype][ic]->GetSumOfWeights());
      histo_dim8_PUBoundingDown[itype][ic]->Scale(histo_dim8_Baseline[itype][ic]->GetSumOfWeights()/histo_dim8_PUBoundingDown[itype][ic]->GetSumOfWeights());
      if(ic == kPlotWZ || ic == kPlotEWKWZ || ic == kPlotEWKSSWW || ic == kPlotZZ || ic == kPlotTVX) {
        histo_dim8_QCDScaleUp   [itype][ic]->Scale(histo_dim8_Baseline[itype][ic]->GetSumOfWeights()/histo_dim8_QCDScaleUp   [itype][ic]->GetSumOfWeights());
        histo_dim8_QCDScaleDown [itype][ic]->Scale(histo_dim8_Baseline[itype][ic]->GetSumOfWeights()/histo_dim8_QCDScaleDown [itype][ic]->GetSumOfWeights());
        histo_dim8_EWKCorrVVUp  [itype][ic]->Scale(histo_dim8_Baseline[itype][ic]->GetSumOfWeights()/histo_dim8_EWKCorrVVUp  [itype][ic]->GetSumOfWeights());
        histo_dim8_EWKCorrVVDown[itype][ic]->Scale(histo_dim8_Baseline[itype][ic]->GetSumOfWeights()/histo_dim8_EWKCorrVVDown[itype][ic]->GetSumOfWeights());
        if(ic == kPlotZZ || ic == kPlotTVX || ic == kPlotWZ){
        histo_dim8_EWKqqZZCorrUp  [itype][ic]->Scale(histo_dim8_Baseline[itype][ic]->GetSumOfWeights()/histo_dim8_EWKqqZZCorrUp  [itype][ic]->GetSumOfWeights());
        histo_dim8_EWKqqZZCorrDown[itype][ic]->Scale(histo_dim8_Baseline[itype][ic]->GetSumOfWeights()/histo_dim8_EWKqqZZCorrDown[itype][ic]->GetSumOfWeights());
        histo_dim8_ggZZCorrUp     [itype][ic]->Scale(histo_dim8_Baseline[itype][ic]->GetSumOfWeights()/histo_dim8_ggZZCorrUp     [itype][ic]->GetSumOfWeights());
        histo_dim8_ggZZCorrDown   [itype][ic]->Scale(histo_dim8_Baseline[itype][ic]->GetSumOfWeights()/histo_dim8_ggZZCorrDown   [itype][ic]->GetSumOfWeights());
        }
      }
    } 
  }  //end loop on nCat

    for(int icc = 0; icc != 2; icc++){
      int irefer = (icc == 1) ? kPlotEWKWZ : kPlotEWKSSWW;
      for(int nb=1; nb<=histo_dim8_Baseline[icc][irefer]->GetNbinsX(); nb++){
        for(int iscan = 0; iscan < nscan_ft0; iscan++){
          histo_aqgc_ft0_Baseline[icc][iscan]->SetBinContent(nb, TMath::Max((float)histo_aqgc_ft0_Baseline[icc][iscan]->GetBinContent(nb),1e-7f));
        }
        for(int iscan = 0; iscan < nscan_ft1; iscan++){
          histo_aqgc_ft1_Baseline[icc][iscan]->SetBinContent(nb, TMath::Max((float)histo_aqgc_ft1_Baseline[icc][iscan]->GetBinContent(nb),1e-7f));
        }
        for(int iscan = 0; iscan < nscan_ft2; iscan++){
          histo_aqgc_ft2_Baseline[icc][iscan]->SetBinContent(nb, TMath::Max((float)histo_aqgc_ft2_Baseline[icc][iscan]->GetBinContent(nb),1e-7f));
        }
        for(int iscan = 0; iscan < nscan_fm0; iscan++){
          histo_aqgc_fm0_Baseline[icc][iscan]->SetBinContent(nb, TMath::Max((float)histo_aqgc_fm0_Baseline[icc][iscan]->GetBinContent(nb),1e-7f));
        }
        for(int iscan = 0; iscan < nscan_fm1; iscan++){
          histo_aqgc_fm1_Baseline[icc][iscan]->SetBinContent(nb, TMath::Max((float)histo_aqgc_fm1_Baseline[icc][iscan]->GetBinContent(nb),1e-7f));
        }
        for(int iscan = 0; iscan < nscan_fm6; iscan++){
          histo_aqgc_fm6_Baseline[icc][iscan]->SetBinContent(nb, TMath::Max((float)histo_aqgc_fm6_Baseline[icc][iscan]->GetBinContent(nb),1e-7f));
        }
        for(int iscan = 0; iscan < nscan_fm7; iscan++){
          histo_aqgc_fm7_Baseline[icc][iscan]->SetBinContent(nb, TMath::Max((float)histo_aqgc_fm7_Baseline[icc][iscan]->GetBinContent(nb),1e-7f));
        }
        for(int iscan = 0; iscan < nscan_fs0; iscan++){
          histo_aqgc_fs0_Baseline[icc][iscan]->SetBinContent(nb, TMath::Max((float)histo_aqgc_fs0_Baseline[icc][iscan]->GetBinContent(nb),1e-7f));
        }
        for(int iscan = 0; iscan < nscan_fs1; iscan++){
          histo_aqgc_fs1_Baseline[icc][iscan]->SetBinContent(nb, TMath::Max((float)histo_aqgc_fs1_Baseline[icc][iscan]->GetBinContent(nb),1e-7f));
        }
      }

      for(int iscan = 0; iscan < nscan_ft0; iscan++){
        histo_aqgc_ft0_Baseline[icc][iscan]->Divide(histo_dim8_Baseline[icc][irefer]);
      }
      for(int iscan = 0; iscan < nscan_ft1; iscan++){
        histo_aqgc_ft1_Baseline[icc][iscan]->Divide(histo_dim8_Baseline[icc][irefer]);
      }
      for(int iscan = 0; iscan < nscan_ft2; iscan++){
        histo_aqgc_ft2_Baseline[icc][iscan]->Divide(histo_dim8_Baseline[icc][irefer]);
      }
      for(int iscan = 0; iscan < nscan_fm0; iscan++){
        histo_aqgc_fm0_Baseline[icc][iscan]->Divide(histo_dim8_Baseline[icc][irefer]);
      }
      for(int iscan = 0; iscan < nscan_fm1; iscan++){
        histo_aqgc_fm1_Baseline[icc][iscan]->Divide(histo_dim8_Baseline[icc][irefer]);
      }
      for(int iscan = 0; iscan < nscan_fm6; iscan++){
        histo_aqgc_fm6_Baseline[icc][iscan]->Divide(histo_dim8_Baseline[icc][irefer]);
      }
      for(int iscan = 0; iscan < nscan_fm7; iscan++){
        histo_aqgc_fm7_Baseline[icc][iscan]->Divide(histo_dim8_Baseline[icc][irefer]);
      }
      for(int iscan = 0; iscan < nscan_fs0; iscan++){
        histo_aqgc_fs0_Baseline[icc][iscan]->Divide(histo_dim8_Baseline[icc][irefer]);
      }
      for(int iscan = 0; iscan < nscan_fs1; iscan++){
        histo_aqgc_fs1_Baseline[icc][iscan]->Divide(histo_dim8_Baseline[icc][irefer]);
      }

      for(int nb=1; nb<=histo_dim8_Baseline[icc][irefer]->GetNbinsX(); nb++){
        for(int iscan = 0; iscan < nscan_ft0; iscan++){
          aqgc_ft0_full[icc][nb-1]->SetPoint(iscan, AQGC_ft0_range[iscan], TMath::Max( (float)histo_aqgc_ft0_Baseline[icc][iscan]->GetBinContent(nb), 1e-7f) );
          aqgc_ft0_full[icc][nb-1]->SetPointError(iscan, (AQGC_ft0_range[iscan]-AQGC_ft0_range[(iscan-1)<0?0:iscan-1])/2 , (AQGC_ft0_range[(iscan+1)==nscan_ft0?nscan_ft0-1:iscan+1]-AQGC_ft0_range[iscan])/2, (float)histo_aqgc_ft0_Baseline[icc][iscan]->GetBinError(nb), (float)histo_aqgc_ft0_Baseline[icc][iscan]->GetBinError(nb));
        }
        for(int iscan = 0; iscan < nscan_ft1; iscan++){
          aqgc_ft1_full[icc][nb-1]->SetPoint(iscan, AQGC_ft1_range[iscan], TMath::Max( (float)histo_aqgc_ft1_Baseline[icc][iscan]->GetBinContent(nb), 1e-7f) );
          aqgc_ft1_full[icc][nb-1]->SetPointError(iscan, (AQGC_ft1_range[iscan]-AQGC_ft1_range[(iscan-1)<0?0:iscan-1])/2 , (AQGC_ft1_range[(iscan+1)==nscan_ft1?nscan_ft1-1:iscan+1]-AQGC_ft1_range[iscan])/2, (float)histo_aqgc_ft1_Baseline[icc][iscan]->GetBinError(nb), (float)histo_aqgc_ft1_Baseline[icc][iscan]->GetBinError(nb));
        }
        for(int iscan = 0; iscan < nscan_ft2; iscan++){
          aqgc_ft2_full[icc][nb-1]->SetPoint(iscan, AQGC_ft2_range[iscan], TMath::Max( (float)histo_aqgc_ft2_Baseline[icc][iscan]->GetBinContent(nb), 1e-7f) );
          aqgc_ft2_full[icc][nb-1]->SetPointError(iscan, (AQGC_ft2_range[iscan]-AQGC_ft2_range[(iscan-1)<0?0:iscan-1])/2 , (AQGC_ft2_range[(iscan+1)==nscan_ft2?nscan_ft2-1:iscan+1]-AQGC_ft2_range[iscan])/2, (float)histo_aqgc_ft2_Baseline[icc][iscan]->GetBinError(nb), (float)histo_aqgc_ft2_Baseline[icc][iscan]->GetBinError(nb));
        }
        for(int iscan = 0; iscan < nscan_fm0; iscan++){
          aqgc_fm0_full[icc][nb-1]->SetPoint(iscan, AQGC_fm0_range[iscan], TMath::Max( (float)histo_aqgc_fm0_Baseline[icc][iscan]->GetBinContent(nb), 1e-7f) );
          aqgc_fm0_full[icc][nb-1]->SetPointError(iscan, (AQGC_fm0_range[iscan]-AQGC_fm0_range[(iscan-1)<0?0:iscan-1])/2 , (AQGC_fm0_range[(iscan+1)==nscan_fm0?nscan_fm0-1:iscan+1]-AQGC_fm0_range[iscan])/2, (float)histo_aqgc_fm0_Baseline[icc][iscan]->GetBinError(nb), (float)histo_aqgc_fm0_Baseline[icc][iscan]->GetBinError(nb));
        }
        for(int iscan = 0; iscan < nscan_fm1; iscan++){
          aqgc_fm1_full[icc][nb-1]->SetPoint(iscan, AQGC_fm1_range[iscan], TMath::Max( (float)histo_aqgc_fm1_Baseline[icc][iscan]->GetBinContent(nb), 1e-7f) );
          aqgc_fm1_full[icc][nb-1]->SetPointError(iscan, (AQGC_fm1_range[iscan]-AQGC_fm1_range[(iscan-1)<0?0:iscan-1])/2 , (AQGC_fm1_range[(iscan+1)==nscan_fm1?nscan_fm1-1:iscan+1]-AQGC_fm1_range[iscan])/2, (float)histo_aqgc_fm1_Baseline[icc][iscan]->GetBinError(nb), (float)histo_aqgc_fm1_Baseline[icc][iscan]->GetBinError(nb));
        }
        for(int iscan = 0; iscan < nscan_fm6; iscan++){
          aqgc_fm6_full[icc][nb-1]->SetPoint(iscan, AQGC_fm6_range[iscan], TMath::Max( (float)histo_aqgc_fm6_Baseline[icc][iscan]->GetBinContent(nb), 1e-7f) );
          aqgc_fm6_full[icc][nb-1]->SetPointError(iscan, (AQGC_fm6_range[iscan]-AQGC_fm6_range[(iscan-1)<0?0:iscan-1])/2 , (AQGC_fm6_range[(iscan+1)==nscan_fm6?nscan_fm6-1:iscan+1]-AQGC_fm6_range[iscan])/2, (float)histo_aqgc_fm6_Baseline[icc][iscan]->GetBinError(nb), (float)histo_aqgc_fm6_Baseline[icc][iscan]->GetBinError(nb));
        }
        for(int iscan = 0; iscan < nscan_fm7; iscan++){
          aqgc_fm7_full[icc][nb-1]->SetPoint(iscan, AQGC_fm7_range[iscan], TMath::Max( (float)histo_aqgc_fm7_Baseline[icc][iscan]->GetBinContent(nb), 1e-7f) );
          aqgc_fm7_full[icc][nb-1]->SetPointError(iscan, (AQGC_fm7_range[iscan]-AQGC_fm7_range[(iscan-1)<0?0:iscan-1])/2 , (AQGC_fm7_range[(iscan+1)==nscan_fm7?nscan_fm7-1:iscan+1]-AQGC_fm7_range[iscan])/2, (float)histo_aqgc_fm7_Baseline[icc][iscan]->GetBinError(nb), (float)histo_aqgc_fm7_Baseline[icc][iscan]->GetBinError(nb));
        }
        for(int iscan = 0; iscan < nscan_fs0; iscan++){
          aqgc_fs0_full[icc][nb-1]->SetPoint(iscan, AQGC_fs0_range[iscan], TMath::Max( (float)histo_aqgc_fs0_Baseline[icc][iscan]->GetBinContent(nb), 1e-7f) );
          aqgc_fs0_full[icc][nb-1]->SetPointError(iscan, (AQGC_fs0_range[iscan]-AQGC_fs0_range[(iscan-1)<0?0:iscan-1])/2 , (AQGC_fs0_range[(iscan+1)==nscan_fs0?nscan_fs0-1:iscan+1]-AQGC_fs0_range[iscan])/2, (float)histo_aqgc_fs0_Baseline[icc][iscan]->GetBinError(nb), (float)histo_aqgc_fs0_Baseline[icc][iscan]->GetBinError(nb));
        }
        for(int iscan = 0; iscan < nscan_fs1; iscan++){
          aqgc_fs1_full[icc][nb-1]->SetPoint(iscan, AQGC_fs1_range[iscan], TMath::Max( (float)histo_aqgc_fs1_Baseline[icc][iscan]->GetBinContent(nb), 1e-7f) );
          aqgc_fs1_full[icc][nb-1]->SetPointError(iscan, (AQGC_fs1_range[iscan]-AQGC_fs1_range[(iscan-1)<0?0:iscan-1])/2 , (AQGC_fs1_range[(iscan+1)==nscan_fs1?nscan_fs1-1:iscan+1]-AQGC_fs1_range[iscan])/2, (float)histo_aqgc_fs1_Baseline[icc][iscan]->GetBinError(nb), (float)histo_aqgc_fs1_Baseline[icc][iscan]->GetBinError(nb));
        }
      }
    } // end 0, 1

  if(isPseudoData == true){
    histo_Baseline[kPlotData]->Scale(0);
    for(int ic=1; ic<nPlotCategories; ic++) {histo_Baseline[kPlotData]->Add(histo_Baseline[ic]); /*histo_Baseline[ic]->Scale(0);*/}
  }


  for(int ic=0; ic<nPlotCategories; ic++) histo[ic]->Add(histo_Baseline[ic]);


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
      printf("uncertainties fakeMPUp\n");    for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[kPlotNonPrompt]->GetBinContent(i)>0)printf("%5.1f ",histo_FakeBoundingUp  [ny][0]->GetBinContent(i)/histo_Baseline[kPlotNonPrompt]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      printf("uncertainties fakeMPDown\n");  for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[kPlotNonPrompt]->GetBinContent(i)>0)printf("%5.1f ",histo_FakeBoundingDown[ny][0]->GetBinContent(i)/histo_Baseline[kPlotNonPrompt]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      printf("uncertainties fakeMNUp\n");    for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[kPlotNonPrompt]->GetBinContent(i)>0)printf("%5.1f ",histo_FakeBoundingUp  [ny][1]->GetBinContent(i)/histo_Baseline[kPlotNonPrompt]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      printf("uncertainties fakeMNDown\n");  for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[kPlotNonPrompt]->GetBinContent(i)>0)printf("%5.1f ",histo_FakeBoundingDown[ny][1]->GetBinContent(i)/histo_Baseline[kPlotNonPrompt]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      printf("uncertainties fakeEPUp\n");    for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[kPlotNonPrompt]->GetBinContent(i)>0)printf("%5.1f ",histo_FakeBoundingUp  [ny][2]->GetBinContent(i)/histo_Baseline[kPlotNonPrompt]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      printf("uncertainties fakeEPDown\n");  for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[kPlotNonPrompt]->GetBinContent(i)>0)printf("%5.1f ",histo_FakeBoundingDown[ny][2]->GetBinContent(i)/histo_Baseline[kPlotNonPrompt]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      printf("uncertainties fakeENUp\n");    for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[kPlotNonPrompt]->GetBinContent(i)>0)printf("%5.1f ",histo_FakeBoundingUp  [ny][3]->GetBinContent(i)/histo_Baseline[kPlotNonPrompt]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      printf("uncertainties fakeENDown\n");  for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[kPlotNonPrompt]->GetBinContent(i)>0)printf("%5.1f ",histo_FakeBoundingDown[ny][3]->GetBinContent(i)/histo_Baseline[kPlotNonPrompt]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      printf("uncertainties fakeMUp\n");     for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[kPlotNonPrompt]->GetBinContent(i)>0)printf("%5.1f ",histo_FakeBoundingUp  [ny][4]->GetBinContent(i)/histo_Baseline[kPlotNonPrompt]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      printf("uncertainties fakeMDown\n");   for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[kPlotNonPrompt]->GetBinContent(i)>0)printf("%5.1f ",histo_FakeBoundingDown[ny][4]->GetBinContent(i)/histo_Baseline[kPlotNonPrompt]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      printf("uncertainties fakeEUp\n");     for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[kPlotNonPrompt]->GetBinContent(i)>0)printf("%5.1f ",histo_FakeBoundingUp  [ny][5]->GetBinContent(i)/histo_Baseline[kPlotNonPrompt]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      printf("uncertainties fakeEDown\n");   for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[kPlotNonPrompt]->GetBinContent(i)>0)printf("%5.1f ",histo_FakeBoundingDown[ny][5]->GetBinContent(i)/histo_Baseline[kPlotNonPrompt]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      printf("uncertainties fakeM3LUp\n");   for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[kPlotNonPrompt]->GetBinContent(i)>0)printf("%5.1f ",histo_FakeBoundingUp  [ny][6]->GetBinContent(i)/histo_Baseline[kPlotNonPrompt]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      printf("uncertainties fakeM3LDown\n"); for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[kPlotNonPrompt]->GetBinContent(i)>0)printf("%5.1f ",histo_FakeBoundingDown[ny][6]->GetBinContent(i)/histo_Baseline[kPlotNonPrompt]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      printf("uncertainties fakeE3LUp\n");   for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[kPlotNonPrompt]->GetBinContent(i)>0)printf("%5.1f ",histo_FakeBoundingUp  [ny][7]->GetBinContent(i)/histo_Baseline[kPlotNonPrompt]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      printf("uncertainties fakeE3LDown\n"); for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[kPlotNonPrompt]->GetBinContent(i)>0)printf("%5.1f ",histo_FakeBoundingDown[ny][7]->GetBinContent(i)/histo_Baseline[kPlotNonPrompt]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
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



    char aqgcLimits[200];
    TString file_VV[2] = {"WW","WZ"};
    TFile* aqgcFileLimits_histos[2];
    TFile* aqgcFileLimits_parabola[2][9];

    for(int ioutfile = 0; ioutfile < 2; ioutfile++){
      if(ioutfile == 0) sprintf(aqgcLimits, "aqgc_%d_histo_WWjj.root",year);
      else              sprintf(aqgcLimits, "aqgc_%d_histo_WZjj.root",year);

      aqgcFileLimits_histos[ioutfile] = new TFile(aqgcLimits,"recreate");
      aqgcFileLimits_histos[ioutfile]->cd();

      for(unsigned ic=0; ic<nPlotCategories; ic++) {
        if(ic != kPlotData && histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
        if(ioutfile == 0 && ic == kPlotEWKSSWW) continue;
        if(ioutfile == 1 && ic == kPlotEWKWZ) continue;
        histo_dim8_Baseline              [ioutfile][ic]->Write();
        if(ic == kPlotData) continue;
        histo_dim8_QCDScaleUp            [ioutfile][ic]->Write();
        histo_dim8_QCDScaleDown          [ioutfile][ic]->Write();
        histo_dim8_PDFBoundingUp         [ioutfile][ic]->Write();
        histo_dim8_PDFBoundingDown       [ioutfile][ic]->Write();
        histo_dim8_LepEffMBoundingUp     [ioutfile][ic]->Write();
        histo_dim8_LepEffMBoundingDown   [ioutfile][ic]->Write();
        histo_dim8_LepEffEBoundingUp     [ioutfile][ic]->Write();
        histo_dim8_LepEffEBoundingDown   [ioutfile][ic]->Write();
        histo_dim8_PUBoundingUp          [ioutfile][ic]->Write();
        histo_dim8_PUBoundingDown        [ioutfile][ic]->Write();
        for(int ny=0; ny<nYears; ny++){
        histo_dim8_BTAGBBoundingUp       [ioutfile][ny][ic]->Write();
        histo_dim8_BTAGBBoundingDown     [ioutfile][ny][ic]->Write();
        histo_dim8_BTAGLBoundingUp       [ioutfile][ny][ic]->Write();
        histo_dim8_BTAGLBoundingDown     [ioutfile][ny][ic]->Write();
        histo_dim8_JESBoundingUp         [ioutfile][ny][ic]->Write();
        histo_dim8_JESBoundingDown       [ioutfile][ny][ic]->Write();
        histo_dim8_JERBoundingUp 	 [ioutfile][ny][ic]->Write();
        histo_dim8_JERBoundingDown	 [ioutfile][ny][ic]->Write();
        histo_dim8_PreFireBoundingUp     [ioutfile][ny][ic]->Write();
        histo_dim8_PreFireBoundingDown   [ioutfile][ny][ic]->Write();
        histo_dim8_TriggerBoundingUp     [ioutfile][ny][ic]->Write();
        histo_dim8_TriggerBoundingDown   [ioutfile][ny][ic]->Write();
        }
        histo_dim8_WSBoundingUp          [ioutfile][ic]->Write();
        histo_dim8_WSBoundingDown        [ioutfile][ic]->Write();
        histo_dim8_EWKCorrVVUp           [ioutfile][ic]->Write();
        histo_dim8_EWKCorrVVDown         [ioutfile][ic]->Write();
        histo_dim8_EWKqqZZCorrUp         [ioutfile][ic]->Write();
        histo_dim8_EWKqqZZCorrDown       [ioutfile][ic]->Write();
        histo_dim8_ggZZCorrUp            [ioutfile][ic]->Write();
        histo_dim8_ggZZCorrDown          [ioutfile][ic]->Write();
        histo_dim8_WZTauHUp              [ioutfile][ic]->Write();
        histo_dim8_WZTauHDown	         [ioutfile][ic]->Write();
        histo_dim8_WZTauLUp              [ioutfile][ic]->Write();
        histo_dim8_WZTauLDown	         [ioutfile][ic]->Write();
      }
      for(unsigned ic=0; ic<8; ic++) {
        for(int ny=0; ny<nYears; ny++){
          histo_dim8_FakeBoundingUp  [ioutfile][ny][ic]->Write();
          histo_dim8_FakeBoundingDown[ioutfile][ny][ic]->Write();
        }
      }
    }

    aqgcFileLimits_histos[0]->cd();

    histo_dim8_Baseline              [0][kPlotEWKSSWW]->SetName("diboson");                                                                 histo_dim8_Baseline           [0][kPlotEWKSSWW]->Write();
    histo_dim8_QCDScaleUp            [0][kPlotEWKSSWW]->SetName(Form("diboson_QCDScale_%s_ACCEPTUp",  plotBaseNames[kPlotEWKSSWW].Data())); histo_dim8_QCDScaleUp         [0][kPlotEWKSSWW]->Write();
    histo_dim8_QCDScaleDown          [0][kPlotEWKSSWW]->SetName(Form("diboson_QCDScale_%s_ACCEPTDown",plotBaseNames[kPlotEWKSSWW].Data())); histo_dim8_QCDScaleDown       [0][kPlotEWKSSWW]->Write();
    histo_dim8_PDFBoundingUp         [0][kPlotEWKSSWW]->SetName("diboson_PDFUp");                                                           histo_dim8_PDFBoundingUp      [0][kPlotEWKSSWW]->Write();
    histo_dim8_PDFBoundingDown       [0][kPlotEWKSSWW]->SetName("diboson_PDFDown");                                                         histo_dim8_PDFBoundingDown    [0][kPlotEWKSSWW]->Write();
    histo_dim8_LepEffMBoundingUp     [0][kPlotEWKSSWW]->SetName("diboson_CMS_eff_mUp");                                                     histo_dim8_LepEffMBoundingUp  [0][kPlotEWKSSWW]->Write();
    histo_dim8_LepEffMBoundingDown   [0][kPlotEWKSSWW]->SetName("diboson_CMS_eff_mDown");                                                   histo_dim8_LepEffMBoundingDown[0][kPlotEWKSSWW]->Write();
    histo_dim8_LepEffEBoundingUp     [0][kPlotEWKSSWW]->SetName("diboson_CMS_eff_eUp");                                                     histo_dim8_LepEffEBoundingUp  [0][kPlotEWKSSWW]->Write();
    histo_dim8_LepEffEBoundingDown   [0][kPlotEWKSSWW]->SetName("diboson_CMS_eff_eDown");                                                   histo_dim8_LepEffEBoundingDown[0][kPlotEWKSSWW]->Write();
    histo_dim8_PUBoundingUp          [0][kPlotEWKSSWW]->SetName("diboson_CMS_puUp");                                                        histo_dim8_PUBoundingUp       [0][kPlotEWKSSWW]->Write();
    histo_dim8_PUBoundingDown        [0][kPlotEWKSSWW]->SetName("diboson_CMS_puDown");                                                      histo_dim8_PUBoundingDown     [0][kPlotEWKSSWW]->Write();
    for(int ny=0; ny<nYears; ny++){
      histo_dim8_BTAGBBoundingUp     [0][ny][kPlotEWKSSWW]->SetName(Form("diboson_CMS_btagb_%dUp"     ,2016+ny));    histo_dim8_BTAGBBoundingUp       [0][ny][kPlotEWKSSWW]->Write();
      histo_dim8_BTAGBBoundingDown   [0][ny][kPlotEWKSSWW]->SetName(Form("diboson_CMS_btagb_%dDown"   ,2016+ny));    histo_dim8_BTAGBBoundingDown     [0][ny][kPlotEWKSSWW]->Write();
      histo_dim8_BTAGLBoundingUp     [0][ny][kPlotEWKSSWW]->SetName(Form("diboson_CMS_btagl_%dUp"     ,2016+ny));    histo_dim8_BTAGLBoundingUp       [0][ny][kPlotEWKSSWW]->Write();
      histo_dim8_BTAGLBoundingDown   [0][ny][kPlotEWKSSWW]->SetName(Form("diboson_CMS_btagl_%dDown"   ,2016+ny));    histo_dim8_BTAGLBoundingDown     [0][ny][kPlotEWKSSWW]->Write();
      histo_dim8_JESBoundingUp       [0][ny][kPlotEWKSSWW]->SetName(Form("diboson_CMS_jes_%dUp"       ,2016+ny));    histo_dim8_JESBoundingUp         [0][ny][kPlotEWKSSWW]->Write();
      histo_dim8_JESBoundingDown     [0][ny][kPlotEWKSSWW]->SetName(Form("diboson_CMS_jes_%dDown"     ,2016+ny));    histo_dim8_JESBoundingDown       [0][ny][kPlotEWKSSWW]->Write();
      histo_dim8_JERBoundingUp       [0][ny][kPlotEWKSSWW]->SetName(Form("diboson_CMS_jer_%dUp"       ,2016+ny));    histo_dim8_JERBoundingUp         [0][ny][kPlotEWKSSWW]->Write();
      histo_dim8_JERBoundingDown     [0][ny][kPlotEWKSSWW]->SetName(Form("diboson_CMS_jer_%dDown"     ,2016+ny));    histo_dim8_JERBoundingDown       [0][ny][kPlotEWKSSWW]->Write();
      histo_dim8_PreFireBoundingUp   [0][ny][kPlotEWKSSWW]->SetName(Form("diboson_CMS_prefire_%dUp"   ,2016+ny));    histo_dim8_PreFireBoundingUp     [0][ny][kPlotEWKSSWW]->Write();
      histo_dim8_PreFireBoundingDown [0][ny][kPlotEWKSSWW]->SetName(Form("diboson_CMS_prefire_%dDown" ,2016+ny));    histo_dim8_PreFireBoundingDown   [0][ny][kPlotEWKSSWW]->Write();
      histo_dim8_TriggerBoundingUp   [0][ny][kPlotEWKSSWW]->SetName(Form("diboson_CMS_trigger_%dUp"   ,2016+ny));    histo_dim8_TriggerBoundingUp     [0][ny][kPlotEWKSSWW]->Write();
      histo_dim8_TriggerBoundingDown [0][ny][kPlotEWKSSWW]->SetName(Form("diboson_CMS_trigger_%dDown" ,2016+ny));    histo_dim8_TriggerBoundingDown   [0][ny][kPlotEWKSSWW]->Write();
    }
    histo_dim8_WSBoundingUp          [0][kPlotEWKSSWW]->SetName("diboson_CMS_wseffUp");                                                      histo_dim8_WSBoundingUp      [0][kPlotEWKSSWW]->Write();
    histo_dim8_WSBoundingDown        [0][kPlotEWKSSWW]->SetName("diboson_CMS_wseffDown");                                                    histo_dim8_WSBoundingDown    [0][kPlotEWKSSWW]->Write();
    histo_dim8_EWKCorrVVUp           [0][kPlotEWKSSWW]->SetName(Form("diboson_EWKCorrVV%sUp"  , plotBaseNames[kPlotEWKSSWW].Data()));        histo_dim8_EWKCorrVVUp       [0][kPlotEWKSSWW]->Write();
    histo_dim8_EWKCorrVVDown         [0][kPlotEWKSSWW]->SetName(Form("diboson_EWKCorrVV%sDown", plotBaseNames[kPlotEWKSSWW].Data()));        histo_dim8_EWKCorrVVDown     [0][kPlotEWKSSWW]->Write();
    histo_dim8_EWKqqZZCorrUp         [0][kPlotEWKSSWW]->SetName("diboson_EWKqqZZCorrUp");                                                    histo_dim8_EWKqqZZCorrUp     [0][kPlotEWKSSWW]->Write();
    histo_dim8_EWKqqZZCorrDown       [0][kPlotEWKSSWW]->SetName("diboson_EWKqqZZCorrDown");                                                  histo_dim8_EWKqqZZCorrDown   [0][kPlotEWKSSWW]->Write();
    histo_dim8_ggZZCorrUp            [0][kPlotEWKSSWW]->SetName("diboson_ggZZCorrUp");                                                       histo_dim8_ggZZCorrUp        [0][kPlotEWKSSWW]->Write();
    histo_dim8_ggZZCorrDown          [0][kPlotEWKSSWW]->SetName("diboson_ggZZCorrDown");                                                     histo_dim8_ggZZCorrDown      [0][kPlotEWKSSWW]->Write();
    histo_dim8_WZTauHUp              [0][kPlotEWKSSWW]->SetName("diboson_WZTauHUp");                                                         histo_dim8_WZTauHUp          [0][kPlotEWKSSWW]->Write();
    histo_dim8_WZTauHDown            [0][kPlotEWKSSWW]->SetName("diboson_WZTauHDown");                                                       histo_dim8_WZTauHDown        [0][kPlotEWKSSWW]->Write();
    histo_dim8_WZTauLUp              [0][kPlotEWKSSWW]->SetName("diboson_WZTauLUp");                                                         histo_dim8_WZTauLUp          [0][kPlotEWKSSWW]->Write();
    histo_dim8_WZTauLDown            [0][kPlotEWKSSWW]->SetName("diboson_WZTauLDown");                                                       histo_dim8_WZTauLDown        [0][kPlotEWKSSWW]->Write();

    aqgcFileLimits_histos[0]->Close();

    aqgcFileLimits_histos[1]->cd();

    histo_dim8_Baseline              [1][kPlotEWKWZ]->SetName("diboson");                                                                 histo_dim8_Baseline            [1][kPlotEWKWZ]->Write();
    histo_dim8_QCDScaleUp            [1][kPlotEWKWZ]->SetName(Form("diboson_QCDScale_%s_ACCEPTUp",  plotBaseNames[kPlotEWKWZ].Data()));   histo_dim8_QCDScaleUp          [1][kPlotEWKWZ]->Write();
    histo_dim8_QCDScaleDown          [1][kPlotEWKWZ]->SetName(Form("diboson_QCDScale_%s_ACCEPTDown",plotBaseNames[kPlotEWKWZ].Data()));   histo_dim8_QCDScaleDown        [1][kPlotEWKWZ]->Write();
    histo_dim8_PDFBoundingUp         [1][kPlotEWKWZ]->SetName("diboson_PDFUp");                                                           histo_dim8_PDFBoundingUp       [1][kPlotEWKWZ]->Write();
    histo_dim8_PDFBoundingDown       [1][kPlotEWKWZ]->SetName("diboson_PDFDown");                                                         histo_dim8_PDFBoundingDown     [1][kPlotEWKWZ]->Write();
    histo_dim8_LepEffMBoundingUp     [1][kPlotEWKWZ]->SetName("diboson_CMS_eff_mUp");                                                     histo_dim8_LepEffMBoundingUp   [1][kPlotEWKWZ]->Write();
    histo_dim8_LepEffMBoundingDown   [1][kPlotEWKWZ]->SetName("diboson_CMS_eff_mDown");                                                   histo_dim8_LepEffMBoundingDown [1][kPlotEWKWZ]->Write();
    histo_dim8_LepEffEBoundingUp     [1][kPlotEWKWZ]->SetName("diboson_CMS_eff_eUp");                                                     histo_dim8_LepEffEBoundingUp   [1][kPlotEWKWZ]->Write();
    histo_dim8_LepEffEBoundingDown   [1][kPlotEWKWZ]->SetName("diboson_CMS_eff_eDown");                                                   histo_dim8_LepEffEBoundingDown [1][kPlotEWKWZ]->Write();
    histo_dim8_PUBoundingUp          [1][kPlotEWKWZ]->SetName("diboson_CMS_puUp");                                                        histo_dim8_PUBoundingUp        [1][kPlotEWKWZ]->Write();
    histo_dim8_PUBoundingDown        [1][kPlotEWKWZ]->SetName("diboson_CMS_puDown");                                                      histo_dim8_PUBoundingDown      [1][kPlotEWKWZ]->Write();
    for(int ny=0; ny<nYears; ny++){
      histo_dim8_BTAGBBoundingUp     [1][ny][kPlotEWKWZ]->SetName(Form("diboson_CMS_btagb_%dUp"     ,2016+ny));    histo_dim8_BTAGBBoundingUp       [1][ny][kPlotEWKWZ]->Write();
      histo_dim8_BTAGBBoundingDown   [1][ny][kPlotEWKWZ]->SetName(Form("diboson_CMS_btagb_%dDown"   ,2016+ny));    histo_dim8_BTAGBBoundingDown     [1][ny][kPlotEWKWZ]->Write();
      histo_dim8_BTAGLBoundingUp     [1][ny][kPlotEWKWZ]->SetName(Form("diboson_CMS_btagl_%dUp"     ,2016+ny));    histo_dim8_BTAGLBoundingUp       [1][ny][kPlotEWKWZ]->Write();
      histo_dim8_BTAGLBoundingDown   [1][ny][kPlotEWKWZ]->SetName(Form("diboson_CMS_btagl_%dDown"   ,2016+ny));    histo_dim8_BTAGLBoundingDown     [1][ny][kPlotEWKWZ]->Write();
      histo_dim8_JESBoundingUp       [1][ny][kPlotEWKWZ]->SetName(Form("diboson_CMS_jes_%dUp"       ,2016+ny));    histo_dim8_JESBoundingUp         [1][ny][kPlotEWKWZ]->Write();
      histo_dim8_JESBoundingDown     [1][ny][kPlotEWKWZ]->SetName(Form("diboson_CMS_jes_%dDown"     ,2016+ny));    histo_dim8_JESBoundingDown       [1][ny][kPlotEWKWZ]->Write();
      histo_dim8_JERBoundingUp       [1][ny][kPlotEWKWZ]->SetName(Form("diboson_CMS_jer_%dUp"       ,2016+ny));    histo_dim8_JERBoundingUp         [1][ny][kPlotEWKWZ]->Write();
      histo_dim8_JERBoundingDown     [1][ny][kPlotEWKWZ]->SetName(Form("diboson_CMS_jer_%dDown"     ,2016+ny));    histo_dim8_JERBoundingDown       [1][ny][kPlotEWKWZ]->Write();
      histo_dim8_PreFireBoundingUp   [1][ny][kPlotEWKWZ]->SetName(Form("diboson_CMS_prefire_%dUp"   ,2016+ny));    histo_dim8_PreFireBoundingUp     [1][ny][kPlotEWKWZ]->Write();
      histo_dim8_PreFireBoundingDown [1][ny][kPlotEWKWZ]->SetName(Form("diboson_CMS_prefire_%dDown" ,2016+ny));    histo_dim8_PreFireBoundingDown   [1][ny][kPlotEWKWZ]->Write();
      histo_dim8_TriggerBoundingUp   [1][ny][kPlotEWKWZ]->SetName(Form("diboson_CMS_trigger_%dUp"   ,2016+ny));    histo_dim8_TriggerBoundingUp     [1][ny][kPlotEWKWZ]->Write();
      histo_dim8_TriggerBoundingDown [1][ny][kPlotEWKWZ]->SetName(Form("diboson_CMS_trigger_%dDown" ,2016+ny));    histo_dim8_TriggerBoundingDown   [1][ny][kPlotEWKWZ]->Write();
    }
    histo_dim8_WSBoundingUp          [1][kPlotEWKWZ]->SetName("diboson_CMS_wseffUp");                                                      histo_dim8_WSBoundingUp        [1][kPlotEWKWZ]->Write();
    histo_dim8_WSBoundingDown        [1][kPlotEWKWZ]->SetName("diboson_CMS_wseffDown");                                                    histo_dim8_WSBoundingDown      [1][kPlotEWKWZ]->Write();
    histo_dim8_EWKCorrVVUp           [1][kPlotEWKWZ]->SetName(Form("diboson_EWKCorrVV%sUp"  , plotBaseNames[kPlotEWKWZ].Data()));          histo_dim8_EWKCorrVVUp         [1][kPlotEWKWZ]->Write();
    histo_dim8_EWKCorrVVDown         [1][kPlotEWKWZ]->SetName(Form("diboson_EWKCorrVV%sDown", plotBaseNames[kPlotEWKWZ].Data()));          histo_dim8_EWKCorrVVDown       [1][kPlotEWKWZ]->Write();
    histo_dim8_EWKqqZZCorrUp         [1][kPlotEWKWZ]->SetName("diboson_EWKqqZZCorrUp");                                                    histo_dim8_EWKqqZZCorrUp       [1][kPlotEWKWZ]->Write();
    histo_dim8_EWKqqZZCorrDown       [1][kPlotEWKWZ]->SetName("diboson_EWKqqZZCorrDown");                                                  histo_dim8_EWKqqZZCorrDown     [1][kPlotEWKWZ]->Write();
    histo_dim8_ggZZCorrUp            [1][kPlotEWKWZ]->SetName("diboson_ggZZCorrUp");                                                       histo_dim8_ggZZCorrUp          [1][kPlotEWKWZ]->Write();
    histo_dim8_ggZZCorrDown          [1][kPlotEWKWZ]->SetName("diboson_ggZZCorrDown");                                                     histo_dim8_ggZZCorrDown        [1][kPlotEWKWZ]->Write();
    histo_dim8_WZTauHUp              [1][kPlotEWKWZ]->SetName("diboson_WZTauHUp");                                                         histo_dim8_WZTauHUp            [1][kPlotEWKWZ]->Write();
    histo_dim8_WZTauHDown            [1][kPlotEWKWZ]->SetName("diboson_WZTauHDown");                                                       histo_dim8_WZTauHDown          [1][kPlotEWKWZ]->Write();
    histo_dim8_WZTauLUp              [1][kPlotEWKWZ]->SetName("diboson_WZTauLUp");                                                         histo_dim8_WZTauLUp            [1][kPlotEWKWZ]->Write();
    histo_dim8_WZTauLDown            [1][kPlotEWKWZ]->SetName("diboson_WZTauLDown");                                                       histo_dim8_WZTauLDown          [1][kPlotEWKWZ]->Write();   

    aqgcFileLimits_histos[1]->Close();


    for(int ioutfile = 0; ioutfile < 2; ioutfile++){
      for(int ipara=0; ipara<9; ipara++){

        sprintf(aqgcLimits,"aqgc_%d_%s_%s.root",year,file_VV[ioutfile].Data(),AQGCParaName[ipara].Data());
        aqgcFileLimits_parabola[ioutfile][ipara] = new TFile(aqgcLimits,"recreate");
        aqgcFileLimits_parabola[ioutfile][ipara]->cd();

        for(int nb=1; nb<=histo_dim8_Baseline[ioutfile][0]->GetNbinsX(); nb++){
          switch(ipara){
            case 0: aqgc_ft0_full[ioutfile][nb-1]->Write(); break;
            case 1: aqgc_ft1_full[ioutfile][nb-1]->Write(); break;
            case 2: aqgc_ft2_full[ioutfile][nb-1]->Write(); break;
            case 3: aqgc_fm0_full[ioutfile][nb-1]->Write(); break;
            case 4: aqgc_fm1_full[ioutfile][nb-1]->Write(); break;
            case 5: aqgc_fm6_full[ioutfile][nb-1]->Write(); break;
            case 6: aqgc_fm7_full[ioutfile][nb-1]->Write(); break;
            case 7: aqgc_fs0_full[ioutfile][nb-1]->Write(); break;
            case 8: aqgc_fs1_full[ioutfile][nb-1]->Write(); break;
          }
        }
        aqgcFileLimits_parabola[ioutfile][ipara]->Close();
      }
    }
      

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

 newcardShape << Form("EWKqqZZCorr    shape	");
 for (int ic=0; ic<nPlotCategories; ic++){
   if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
   if(ic != kPlotZZ) newcardShape << Form("- ");
   else 	     newcardShape << Form("1.0 ");
 }
 newcardShape << Form("\n");

 newcardShape << Form("ggZZCorr    shape     ");
 for (int ic=0; ic<nPlotCategories; ic++){
   if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
   if(ic != kPlotZZ) newcardShape << Form("- ");
   else 	     newcardShape << Form("1.0 ");
 }
 newcardShape << Form("\n");

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

  newcardShape << Form("CMS_fakeM3L_%d  shape   ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("1.0 ");
    else                     newcardShape << Form("- ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_fakeE3L_%d  shape   ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("1.0 ");
    else                     newcardShape << Form("- ");
  }
  newcardShape << Form("\n");

    newcardShape << Form("CMS_fakeM_%d  shape   ",year);
    for (int ic=0; ic<nPlotCategories; ic++){
      if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
      if(ic == kPlotNonPrompt) newcardShape << Form("1.0 ");
      else                     newcardShape << Form("- ");
    }
    newcardShape << Form("\n");

    newcardShape << Form("CMS_fakeE_%d  shape   ",year);
    for (int ic=0; ic<nPlotCategories; ic++){
      if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
      if(ic == kPlotNonPrompt) newcardShape << Form("1.0 ");
      else                     newcardShape << Form("- ");
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
  sprintf(output,"histossww_%d_%s.root",year,fidAnaName.Data());
  TFile* outFilePlotsNote = new TFile(output,"recreate");
  outFilePlotsNote->cd();
  double totBck = 0;
  for(int i=1; i<nPlotCategories; i++) if(histo[i]->GetSumOfWeights() > 0) totBck = totBck + histo[i]->GetSumOfWeights();
  printf(" %7.1f vs. %7.1f ",histo[0]->GetSumOfWeights(),totBck);
  for(int np=0; np<nPlotCategories; np++) {histo[np]->SetNameTitle(Form("histo%d",np),Form("histo%d",np));histo[np]->Write();}
  for(int np=0; np<nPlotCategories; np++) {histo_mT_ww[np]->SetNameTitle(Form("histo_mt_ww_%d",np),Form("histo_mt_ww_%d",np));histo_mT_ww[np]->Write();}
  for(int np=0; np<nPlotCategories; np++) {histo_mT_wz[np]->SetNameTitle(Form("histo_mt_wz_%d",np),Form("histo_mt_wz_%d",np));histo_mT_wz[np]->Write();}
  for(int np=0; np<nPlotCategories; np++) {histo_mT_mll[np]->Write();}
  outFilePlotsNote->Close();


}
