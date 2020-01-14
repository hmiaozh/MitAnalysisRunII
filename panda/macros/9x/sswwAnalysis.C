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

// fidAna == 0 (SM), 1 (MJJ), 2 (MLL), 3 (AQGC)

enum systType                     {JESUP=0, JESDOWN,  METUP,  METDOWN, nSystTypes};
TString systTypeName[nSystTypes]= {"JESUP","JESDOWN","METUP","METDOWN"};


const int which_para = 2;
const int which_point = 34;


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



void sswwAnalysis(
int year, int fidAna = 0, bool isDesk014 = false, TString WZName = "WZ3l_MG"
){
  int nTypeLepSel[2] = {-1, -1};
  int whichYear = -1;
  if     (year == 2016) {whichYear = Y2016; nTypeLepSel[0] =  2; nTypeLepSel[1] = 7;}
  else if(year == 2017) {whichYear = Y2017; nTypeLepSel[0] = 13; nTypeLepSel[1] = 4;}
  else if(year == 2018) {whichYear = Y2018; nTypeLepSel[0] = 15; nTypeLepSel[1] = 7;}
  else {printf("Wrong year (%d)!\n",year); return;}

  TString fidAnaName = "";
  if(fidAna >= 1) fidAnaName = Form("_fiducial%d",fidAna);

  TString inputFolder = "/data/t3home000";
  if(isDesk014 == true) inputFolder = "/local";

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
  TString trgSFPath = Form("MitAnalysisRunII/data/90x/histo_triggerEff_sel0_%d.root",year);
  TString effSFPath = Form("MitAnalysisRunII/data/90x/histoDY0EffSFStudy_%d.root",year);
  //TString npvPath = Form("MitAnalysisRunII/data/90x/npvWeights_%d.root",year);
  if     (year == 2018) {
    filesPath = Form("%s/ceballos/panda/v_006_1/",inputFolder.Data());
    puPath = "MitAnalysisRunII/data/90x/puWeights_90x_2018.root";

    if     (1){
      infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	          infileCat_.push_back(kPlotData);

      if(fidAna != 3) {
      infileName_.push_back(Form("%sWpWp_EWK.root" ,filesPath.Data())); 	  infileCat_.push_back(kPlotEWKSSWW);
      infileName_.push_back(Form("%sWZ3l_MG_EWK.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotEWKWZ);
      }
      else            {
      infileName_.push_back(Form("%sWWjj_SS_dim8_ewk.root" ,filesPath.Data()));   infileCat_.push_back(kPlotEWKSSWW);
      infileName_.push_back(Form("%sWZjj_dim8_ewk.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotEWKWZ);
      }

      infileName_.push_back(Form("%sWpWp_QCD.root" ,filesPath.Data())); 	  infileCat_.push_back(kPlotQCDSSWW);

      infileName_.push_back(Form("%sWZ3l_MG_QCD.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWZ);

      infileName_.push_back(Form("%sZZJJ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);
      //infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);
      //infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);

      infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotVVV);
      infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotVVV);
      infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotVVV);

      infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sggWW.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sDYNJetsToLL.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotWS);

      infileName_.push_back(Form("%sVG_M120.root" ,filesPath.Data()));            infileCat_.push_back(kPlotVG);

      infileName_.push_back(Form("%sWWdps.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotDPSWW);

      //if(fidAna == 3) {
      //infileName_.push_back(Form("%sWWjj_SS_dim8_ewk.root" ,filesPath.Data()));   infileCat_.push_back(kPlotEWKSSWW_dim8);
      //infileName_.push_back(Form("%sWZjj_dim8_ewk.root" ,filesPath.Data()));      infileCat_.push_back(kPlotEWKWZ_dim8);
      //}
    }
  }
  else if(year == 2017) {
    filesPath = Form("%s/ceballos/panda/v_004_1/",inputFolder.Data());
    puPath = "MitAnalysisRunII/data/90x/puWeights_90x_2017.root";

    if     (WZName == "WZ3l_MG"){
      infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	          infileCat_.push_back(kPlotData);

      if(fidAna != 3) {
      infileName_.push_back(Form("%sWpWp_EWK.root" ,filesPath.Data())); 	  infileCat_.push_back(kPlotEWKSSWW);
      infileName_.push_back(Form("%sWZ3l_MG_EWK.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotEWKWZ);
      }
      else            {
      infileName_.push_back(Form("%sWWjj_SS_dim8_ewk.root" ,filesPath.Data()));   infileCat_.push_back(kPlotEWKSSWW);
      infileName_.push_back(Form("%sWZjj_dim8_ewk.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotEWKWZ);
      }

      infileName_.push_back(Form("%sWpWp_QCD.root" ,filesPath.Data())); 	  infileCat_.push_back(kPlotQCDSSWW);

      infileName_.push_back(Form("%sWZ3l_MG_QCD.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWZ);

      infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);
      infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);

      infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotVVV);
      infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotVVV);
      infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotVVV);

      infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sggWW.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sDYNJetsToLL.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotWS);

      infileName_.push_back(Form("%sVG_M120.root" ,filesPath.Data()));            infileCat_.push_back(kPlotVG);

      infileName_.push_back(Form("%sWWdps.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotDPSWW);

      //if(fidAna == 3) {
      //infileName_.push_back(Form("%sWWjj_SS_dim8_ewk.root" ,filesPath.Data()));   infileCat_.push_back(kPlotEWKSSWW_dim8);
      //infileName_.push_back(Form("%sWZjj_dim8_ewk.root" ,filesPath.Data()));      infileCat_.push_back(kPlotEWKWZ_dim8);
      //}

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
      infileName_.push_back(Form("%sWZ3l_MG_EWK.root" ,filesPath.Data()));        infileCat_.push_back(kPlotEWKWZ);
    }
    else {
      printf("Wrong WZName (%s), exit\n",WZName.Data());
      return;
    }
  }
  else if(year == 2016) {
    filesPath = Form("%s/ceballos/panda/v_002_1/",inputFolder.Data());
    puPath = "MitAnalysisRunII/data/80x/puWeights_80x_37ifb.root";

    if     (WZName == "WZ3l_MG"){
      infileName_.push_back(Form("%sdata.root",filesPath.Data()));		  infileCat_.push_back(kPlotData);

      if(fidAna != 3) {
      infileName_.push_back(Form("%sWpWp_EWK.root" ,filesPath.Data())); 	  infileCat_.push_back(kPlotEWKSSWW);
      infileName_.push_back(Form("%sWZ3l_MG_EWK.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotEWKWZ);
      }
      else            {
      infileName_.push_back(Form("%sWWjj_SS_dim8_ewk.root" ,filesPath.Data()));   infileCat_.push_back(kPlotEWKSSWW);
      infileName_.push_back(Form("%sWZjj_dim8_ewk.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotEWKWZ);
      }

      infileName_.push_back(Form("%sWpWp_QCD.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotQCDSSWW);

      infileName_.push_back(Form("%sWZ3l_MG_QCD.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotWZ);

      infileName_.push_back(Form("%sZZJJ.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotZZ);
      //infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotZZ);
      //infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotZZ);

      infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotVVV);
      infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotVVV);

      infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sggWW.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sTW.root" ,filesPath.Data())); 		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sDYNJetsToLL.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sH125.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);

      infileName_.push_back(Form("%sVG_M120.root" ,filesPath.Data()));            infileCat_.push_back(kPlotVG);

      infileName_.push_back(Form("%sWWdps.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotDPSWW);

      //if(fidAna == 3) {
      //infileName_.push_back(Form("%sWWjj_SS_dim8_ewk.root" ,filesPath.Data()));   infileCat_.push_back(kPlotEWKSSWW_dim8);
      //infileName_.push_back(Form("%sWZjj_dim8_ewk.root" ,filesPath.Data()));      infileCat_.push_back(kPlotEWKWZ_dim8);
      //}

    }
    else if(WZName == "WZ3l_powheg"){
      infileName_.push_back(Form("%sWZ.root" ,filesPath.Data()));                 infileCat_.push_back(kPlotWZ);
      infileName_.push_back(Form("%sWGstar.root" ,filesPath.Data()));             infileCat_.push_back(kPlotWZ);
    }
    else if(WZName == "WZ3l_MG_only"){
      infileName_.push_back(Form("%sWZ3l_MG_QCD.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWZ);
      infileName_.push_back(Form("%sWZ3l_MG_EWK.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWZ);
    }
  }
  else {
    return;
  }

  //infileName_.clear();infileCat_.clear();
  //infileName_.push_back(Form("%sWpWp_EWK.root" ,filesPath.Data())); infileCat_.push_back(kPlotEWKSSWW);
  //infileName_.push_back(Form("%sWZ3l_MG_QCD.root" ,filesPath.Data())); infileCat_.push_back(kPlotWZ);
  //infileName_.push_back(Form("%sWZ3l_MG_EWK.root" ,filesPath.Data())); infileCat_.push_back(kPlotEWKWZ);
  //infileName_.push_back(Form("%sWWjj_SS_dim8_ewk.root" ,filesPath.Data())); infileCat_.push_back(kPlotEWKSSWW);
  //infileName_.push_back(Form("%sWZjj_dim8_ewk.root" ,filesPath.Data())); infileCat_.push_back(kPlotEWKWZ);

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

  TFile *fVVEWKCorr = TFile::Open("MitAnalysisRunII/data/90x/VV_NLO_LO_CMS_mjj.root");
  TH1D *hWZ_KF_CMS     = (TH1D*)(fVVEWKCorr->Get("hWZ_KF_CMS"));     assert(hWZ_KF_CMS    ); hWZ_KF_CMS    ->SetDirectory(0);
  TH1D *hWZ_KF_CMSUp   = (TH1D*)(fVVEWKCorr->Get("hWZ_KF_CMSUp"));   assert(hWZ_KF_CMSUp  ); hWZ_KF_CMSUp  ->SetDirectory(0);
  TH1D *hWZ_KF_CMSDown = (TH1D*)(fVVEWKCorr->Get("hWZ_KF_CMSDown")); assert(hWZ_KF_CMSDown); hWZ_KF_CMSDown->SetDirectory(0);
  TH1D *hWW_KF_CMS     = (TH1D*)(fVVEWKCorr->Get("hWW_KF_CMS"));     assert(hWW_KF_CMS    ); hWW_KF_CMS    ->SetDirectory(0);
  TH1D *hWW_KF_CMSUp   = (TH1D*)(fVVEWKCorr->Get("hWW_KF_CMSUp"));   assert(hWW_KF_CMSUp  ); hWW_KF_CMSUp  ->SetDirectory(0);
  TH1D *hWW_KF_CMSDown = (TH1D*)(fVVEWKCorr->Get("hWW_KF_CMSDown")); assert(hWW_KF_CMSDown); hWW_KF_CMSDown->SetDirectory(0);
  delete fVVEWKCorr;

  const int nBinMJJ = 4; Float_t xbinsMJJ[nBinMJJ+1] = {500, 800, 1200, 1800, 2000};
  const int nBinMLL = 4; Float_t xbinsMLL[nBinMLL+1] = {20, 85, 135, 210, 500};
  const int nBinBDT = 4; Float_t xbinsBDT[nBinBDT+1]  = {-0.8, -0.05, 0.15, 0.39, 0.8};
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


  //WW
  const int nBinMVA_ww =24; Float_t xbins_ww[nBinMVA_ww+1] =
                                                     {500, 800, 1200, 1800, 2000,
                                                          2800, 3200, 3800, 4000,
                                                          4800, 5200, 5800, 6000,
                                                          6800, 7200, 7800, 8000,
                                                          8800, 9200, 9800, 10000,
                                                         10800,11200,11800, 12000};

  //WZ
  const int nBinMVA_wz = 6; Float_t xbins_wz[nBinMVA_wz+1] =
                                                     {500,1200, 2000, 3200, 4000,
                                                          5200, 6000};


  const int nBinMVA_interval = 8; //unuseds regions in aQGC

/*//when want to merge mjj bins [500,1200,2000] for running aQGCs
  if(fidAna == 3){
    xbins[1] = 1200; xbins[2] = 2000; xbins[3] = 3200; xbins[4] = 4000;
    xbins[5] = 5200; xbins[6] = 6000; xbins[7] = 7200; xbins[8] = 8000;
    xbins[9] = 9200; xbins[10] = 10000; xbins[11] = 11200; xbins[12] = 12000;
    xbins[13] = 13200; xbins[14] = 14000; xbins[15] = 15200; xbins[16] = 16000;
    xbins[17] = 17200; xbins[18] = 18000; xbins[19] = 19200; xbins[20] = 20000;
    for(int i=21; i<=nBinMVA; i++) xbins[i] = 20000 + 0.001*i;
  }


  //WW
  const int nBinMVA_ww =10; Float_t xbins_ww[nBinMVA_ww+1] =
                                                     {500,1200, 2000,
                                                          3200, 4000,
                                                          5200, 6000,
                                                          7200, 8000,
							  9200, 10000};

  //WZ
  const int nBinMVA_wz = 6; Float_t xbins_wz[nBinMVA_wz+1] =
                                                     {500,1200, 2000, 3200, 4000,
                                                          5200, 6000};


  const int nBinMVA_interval = 4; //unuseds regions in aQGC
*/

  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 96;
  TH1D* histo[allPlots][nPlotCategories];

  for(int thePlot=0; thePlot<allPlots; thePlot++){
    if     (thePlot >=   0 && thePlot <=   5) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >=   6 && thePlot <=   8) {nBinPlot =   3; xminPlot =  1.5; xmaxPlot = 4.5;}
    else if(thePlot >=   9 && thePlot <=  11) {nBinPlot =  80; xminPlot =  0.0; xmaxPlot = 8.0;}
    else if(thePlot >=  12 && thePlot <=  14) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot =2000;}
    else if(thePlot >=  15 && thePlot <=  17) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 1.0;}
    else if(thePlot >=  18 && thePlot <=  23) {nBinPlot =   5; xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >=  24 && thePlot <=  29) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >=  46 && thePlot <=  51) {nBinPlot = 100; xminPlot = -5.0; xmaxPlot = 5.0;}
    else if(thePlot >=  52 && thePlot <=  54) {nBinPlot =  80; xminPlot =  0.0; xmaxPlot = 8.0;}
    else if(thePlot >=  55 && thePlot <=  57) {nBinPlot = 200; xminPlot =500.0; xmaxPlot =2500;}
    else if(thePlot >=  58 && thePlot <=  60) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 1.0;}
    else if(thePlot >=  61 && thePlot <=  69) {nBinPlot =   5; xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >=  70 && thePlot <=  72) {nBinPlot = 100; xminPlot = 50.0; xmaxPlot = 450;}
    else if(thePlot >=  73 && thePlot <=  75) {nBinPlot = 100; xminPlot = -5.0; xmaxPlot = 5.0;}
    else if(thePlot >=  76 && thePlot <=  78) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >=  79 && thePlot <=  81) {nBinPlot =  50; xminPlot =  0.0; xmaxPlot = 2.5;}
    else if(thePlot >=  82 && thePlot <=  87) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 1.0;}
    else if(thePlot >=  88 && thePlot <=  90) {nBinPlot = 200; xminPlot = 20.0; xmaxPlot = 220;}
    else if(thePlot >=  94 && thePlot <=  94) {nBinPlot = 20; xminPlot =  0.0; xmaxPlot = 1000;}
    if     (thePlot == allPlots-1){           for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinMVA, xbins);}
    else if(thePlot >=  30 && thePlot <=  39) for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinMJJ, xbinsMJJ);
    else if(thePlot >=  40 && thePlot <=  45) for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinMLL, xbinsMLL);
    else if(thePlot >=  91 && thePlot <=  92) for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinMJJ, xbinsMJJ);
    else if(thePlot >=  93 && thePlot <=  93) for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinBDT, xbinsBDT);
    else                                      for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinPlot, xminPlot, xmaxPlot);

  }

  TH1D* histo_MVA;
  TH1D* histo_MVA_dim8[2];  // 0--WW, 1--WZ
  histo_MVA = new TH1D("histo_MVA", "histo_MVA", nBinMVA, xbins); histo_MVA->Sumw2();
  if(fidAna == 3){
    histo_MVA_dim8[0] = new TH1D("histo_MVA_aqgc_ww", "histo_MVA_aqgc_ww", nBinMVA_ww, xbins_ww); histo_MVA_dim8[0]->Sumw2();
    histo_MVA_dim8[1] = new TH1D("histo_MVA_aqgc_wz", "histo_MVA_aqgc_wz", nBinMVA_wz, xbins_wz); histo_MVA_dim8[1]->Sumw2();
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

  //if(fidAna == 3){
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
  //}


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


    if(fidAna == 3){
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
    } // end if fidAna == 3
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

    // Begin MVA initialization
    char outMVAfile[200];
    sprintf(outMVAfile,"mva_%d_%d_%d%s.root",ifile,infileCat_[ifile],year,fidAnaName.Data()); 
    TFile *mvaoutf = new TFile(outMVAfile,"recreate");
    TTree *mvatree = new TTree("mvatree","mvatree");

    float mvamjj, mvadeta, mvadphi, mvazstar;
    float mvajetpt1, mvajetpt2, mvajeteta1, mvajeteta2;
    float mvavWlnpt, mvamet, mvazep1, mvazep2, mvazep3, mvamaxzep;
    float mvamtwz;
    int    category;
    unsigned long long int  eventNum;
    double weight;

    TMVA::Reader *reader;
    float mvaInputs[10];

    mvatree->Branch("mvamjj",	&mvamjj,	"mvamjj/F");
    mvatree->Branch("mvadeta",	&mvadeta,	"mvadeta/F");
    mvatree->Branch("mvadphi",	&mvadphi,	"mvadphi/F");
    mvatree->Branch("mvazstar",	&mvazstar,	"mvazstar/F");
    mvatree->Branch("mvamet",	&mvamet,	"mvamet/F");
    mvatree->Branch("mvavWlnpt",&mvavWlnpt,	"mvavWlnpt/F");
    mvatree->Branch("mvajetpt1",&mvajetpt1,	"mvajetpt1/F");
    mvatree->Branch("mvajetpt2",&mvajetpt2,	"mvajetpt2/F");
    mvatree->Branch("mvajeteta1",&mvajeteta1,	"mvajeteta1/F");
    mvatree->Branch("mvajeteta2",&mvajeteta2,	"mvajeteta2/F");
    mvatree->Branch("mvazep1",	&mvazep1,	"mvazep1/F");
    mvatree->Branch("mvazep2",	&mvazep2,	"mvazep2/F");
    mvatree->Branch("mvazep3",	&mvazep3,	"mvazep3/F");
    mvatree->Branch("mvamaxzep",&mvamaxzep,	"mvamaxzep/F");
    mvatree->Branch("mvamtwz",	&mvamtwz,	"mvamtwz/F");
    mvatree->Branch("category",	 &category,	"category/I");
    mvatree->Branch("eventNum",	 &eventNum,	"eventNum/I");
    mvatree->Branch("weight",	 &weight,	"weight/D");

    TString bdtWeights="";
    bdtWeights="MitAnalysisRunII/BDT/ssww_WZSep_V2/weights/bdt_BDT_singleClass__comb.weights.xml";

    /*
    switch(year){
      case 2016: bdtWeights="ssww_WZSep/weights/bdt_BDT_singleClass__2016.weights.xml"; break;
      case 2017: bdtWeights="ssww_WZSep/weights/bdt_BDT_singleClass__2017.weights.xml"; break;
      case 2018: bdtWeights="ssww_WZSep/weights/bdt_BDT_singleClass__2018.weights.xml"; break;
    }
    */

    TMVA::Reader *theReader = new TMVA::Reader("Silent");
    theReader->AddVariable("mvamjj",    &mvaInputs[0]);
    theReader->AddVariable("mvadeta",   &mvaInputs[1]);
    theReader->AddVariable("mvadphi",   &mvaInputs[2]);
    theReader->AddVariable("mvazep1",   &mvaInputs[3]);
    theReader->AddVariable("mvazep2",   &mvaInputs[4]);
    theReader->AddVariable("mvazep3",   &mvaInputs[5]);
    theReader->AddVariable("mvajetpt1", &mvaInputs[6]);
    theReader->AddVariable("mvajetpt2", &mvaInputs[7]);
    theReader->AddVariable("mvajeteta1",&mvaInputs[8]);
    theReader->AddVariable("mvazstar",  &mvaInputs[9]);
    //theReader->AddVariable("mvamtwz",	&mvaInputs[10]);
    theReader->BookMVA("BDT", bdtWeights.Data());
    reader = theReader;
    // End MVA initialization

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
        passJetPtEtaCut = thePandaFlat.jotPt[0] > 50 && thePandaFlat.jotPt[1] > 50;
      }
      if(passJetPtEtaCut == false) continue;

      if(thePandaFlat.nLooseLep < 2 || thePandaFlat.nLooseLep > 4) continue;
      if(debug == 2) printf("STEP3 %llu\n",thePandaFlat.eventNumber);

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
	  else if(year == 2017 && (looseLepSelBit[i] & kTight) == kTight && (looseLepSelBit[i] & kDxyz) == kDxyz && looseLepMissingHits[i] == 0 && looseLepTripleCharge[i] == 1) idLep[i] = 1;
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
      if(debug == 2) printf("STEP4 %llu %d %d %d %zu\n",thePandaFlat.eventNumber,passLooseLepId,qTot,countLeptonTight,idLep.size());
      if(passLooseLepId == false) continue;
      if(usePureMC == true && countLeptonTight != idLep.size()) continue;
      if(debug == 2) printf("STEP5 %llu\n",thePandaFlat.eventNumber);

      int lepType = -1; double muSFUnc = 1.0; double elSFUnc = 1.0;
      if     (thePandaFlat.nLooseLep == 2){
        if     (abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13) {lepType = 0; muSFUnc = 1.015*1.015;}
        else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11) {lepType = 1; elSFUnc = 1.015*1.015;}
        else  {lepType = 2; muSFUnc = 1.015; elSFUnc = 1.015;}
      }
      else if(thePandaFlat.nLooseLep == 3){
        if     (abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13 && abs(looseLepPdgId[2])==13) {lepType = 0; muSFUnc = 1.015*1.015*1.015;}
        else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11 && abs(looseLepPdgId[2])==11) {lepType = 3; elSFUnc = 1.015*1.015*1.015;}
        else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11) {lepType = 1; muSFUnc = 1.015; elSFUnc = 1.015*1.015;}
        else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[2])==11) {lepType = 1; muSFUnc = 1.015; elSFUnc = 1.015*1.015;}
        else if(abs(looseLepPdgId[1])==11 && abs(looseLepPdgId[2])==11) {lepType = 1; muSFUnc = 1.015; elSFUnc = 1.015*1.015;}
        else if(abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13) {lepType = 2; muSFUnc = 1.015*1.015; elSFUnc = 1.015;}
        else if(abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[2])==13) {lepType = 2; muSFUnc = 1.015*1.015; elSFUnc = 1.015;}
        else if(abs(looseLepPdgId[1])==13 && abs(looseLepPdgId[2])==13) {lepType = 2; muSFUnc = 1.015*1.015; elSFUnc = 1.015;}
        else {printf("Impossible lepton combination: %d %d %d\n",looseLepPdgId[0],looseLepPdgId[1],looseLepPdgId[2]); continue;}
      }
      else if(thePandaFlat.nLooseLep == 4){
        int nmu = (abs(looseLepPdgId[0])==13) + (abs(looseLepPdgId[1])==13) + (abs(looseLepPdgId[2])==13) + (abs(looseLepPdgId[3])==13);
        int nel = (abs(looseLepPdgId[0])==11) + (abs(looseLepPdgId[1])==11) + (abs(looseLepPdgId[2])==11) + (abs(looseLepPdgId[3])==11);
        if     (nmu == 4 && nel == 0) {lepType = 0; muSFUnc = 1.015*1.015*1.015*1.015;}
        else if(nmu == 0 && nel == 4) {lepType = 1; elSFUnc = 1.015*1.015*1.015*1.015;}
        else if(nmu == 2 && nel == 2) {lepType = 2; muSFUnc = 1.015*1.015; elSFUnc = 1.015*1.015;}
        else if(nmu == 3 && nel == 1) {lepType = 3; muSFUnc = 1.015*1.015*1.015; elSFUnc = 1.015;}
        else if(nmu == 1 && nel == 3) {lepType = 3; muSFUnc = 1.015; elSFUnc = 1.015*1.015*1.015;}
        else {printf("Impossible lepton combination: %d %d %d %d\n",looseLepPdgId[0],looseLepPdgId[1],looseLepPdgId[2],looseLepPdgId[3]); continue;}
      }

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
      //vMet    .SetPx(vMet    .Px()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 0));
      //vMet    .SetPy(vMet    .Py()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 1));
      //vMetUp  .SetPx(vMetUp  .Px()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 0));
      //vMetUp  .SetPy(vMetUp  .Py()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 1));
      //vMetDown.SetPx(vMetDown.Px()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 0));
      //vMetDown.SetPy(vMetDown.Py()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 1));

      double mllZ = 10000; double mllmin = 10000;
      TLorentzVector vZ1l1,vZ1l2,vZ2l1,vZ2l2,vWln,trilep,fourlep;
      int whichWln = -1;
      if     (vLoose.size() == 2){
        vZ1l1  = vLoose[0];
        vZ1l2  = vLoose[1];
	mllZ   = (vLoose[0]+vLoose[1]).M();
	mllmin = (vLoose[0]+vLoose[1]).M();
	whichWln = 9; // random number greater or equal than 0
      }
      else if(vLoose.size() == 3){
        if((vLoose[0]+vLoose[1]).M() < mllmin) mllmin = (vLoose[0]+vLoose[1]).M();
        if((vLoose[0]+vLoose[2]).M() < mllmin) mllmin = (vLoose[0]+vLoose[2]).M();
        if((vLoose[1]+vLoose[2]).M() < mllmin) mllmin = (vLoose[1]+vLoose[2]).M();
	trilep = vLoose[0]+vLoose[1]+vLoose[2];
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
	fourlep = vLoose[0]+vLoose[1]+vLoose[2]+vLoose[4];
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

      TLorentzVector vJot1;     vJot1.SetPtEtaPhiM    (thePandaFlat.jotPt[0]             ,thePandaFlat.jotEta[0],thePandaFlat.jotPhi[0],0.0);
      TLorentzVector vJot2;     vJot2.SetPtEtaPhiM    (thePandaFlat.jotPt[1]             ,thePandaFlat.jotEta[1],thePandaFlat.jotPhi[1],0.0);
      TLorentzVector vJot1Up;   vJot1Up.SetPtEtaPhiM  (thePandaFlat.jotPt_JESTotalUp[0]  ,thePandaFlat.jotEta[0],thePandaFlat.jotPhi[0],0.0);
      TLorentzVector vJot2Up;   vJot2Up.SetPtEtaPhiM  (thePandaFlat.jotPt_JESTotalUp[1]  ,thePandaFlat.jotEta[1],thePandaFlat.jotPhi[1],0.0);
      TLorentzVector vJot1Down; vJot1Down.SetPtEtaPhiM(thePandaFlat.jotPt_JESTotalDown[0],thePandaFlat.jotEta[0],thePandaFlat.jotPhi[0],0.0);
      TLorentzVector vJot2Down; vJot2Down.SetPtEtaPhiM(thePandaFlat.jotPt_JESTotalDown[1],thePandaFlat.jotEta[1],thePandaFlat.jotPhi[1],0.0);

      double massJJ         = thePandaFlat.jot12Mass;              //(vJot1+vJot2).M();
      double massJJUp       = thePandaFlat.jot12Mass_JESTotalUp;   //(vJot1Up+vJot2Up).M();
      double massJJDown     = thePandaFlat.jot12Mass_JESTotalDown; //(vJot1Down+vJot2Down).M();
      double deltaEtaJJ     = thePandaFlat.jot12DEta;              //TMath::Abs(vJot1.Eta()    -vJot2.Eta());
      double deltaEtaJJUp   = thePandaFlat.jot12DEta_JESTotalUp;   //TMath::Abs(vJot1Up.Eta()  -vJot2Up.Eta());
      double deltaEtaJJDown = thePandaFlat.jot12DEta_JESTotalDown; //TMath::Abs(vJot1Down.Eta()-vJot2Down.Eta());
      double deltaPhiJJ     = thePandaFlat.jot12DPhi;		   //TMath::Abs(vJot1.Phi()    -vJot2.Phi());
      double deltaPhiJJUp   = thePandaFlat.jot12DPhi_JESTotalUp;   //TMath::Abs(vJot1Up.Phi()  -vJot2Up.Phi());
      double deltaPhiJJDown = thePandaFlat.jot12DPhi_JESTotalDown; //TMath::Abs(vJot1Down.Phi()-vJot2Down.Phi());

      bool passMJJ     = thePandaFlat.nJot              >= 2 && massJJ     > 500;
      bool passMJJUp   = thePandaFlat.nJot_JESTotalUp   >= 2 && massJJUp   > 500;
      bool passMJJDown = thePandaFlat.nJot_JESTotalDown >= 2 && massJJDown > 500;
      bool passDEtaJJ     = thePandaFlat.nJot              >= 2 && deltaEtaJJ     > 2.5;
      bool passDEtaJJUp   = thePandaFlat.nJot_JESTotalUp   >= 2 && deltaEtaJJUp   > 2.5;
      bool passDEtaJJDown = thePandaFlat.nJot_JESTotalDown >= 2 && deltaEtaJJDown > 2.5;

      double maxLeptonZep = 0; double maxLeptonZepUp = 0; double maxLeptonZepDown = 0;
      double wzZepSS[3] = {0.,0.,0.};double wzZepSSUp[3] = {0.,0.,0.};double wzZepSSDown[3] = {0.,0.,0.};
      for(unsigned int i=0; i<vLoose.size(); i++) {
	wzZepSS[i]     = TMath::Abs(vLoose[i].Eta()-(vJot1.Eta()+vJot2.Eta())/2.)/deltaEtaJJ;
	wzZepSSUp[i]   = TMath::Abs(vLoose[i].Eta()-(vJot1Up.Eta()+vJot2Up.Eta())/2.)/deltaEtaJJUp;
	wzZepSSDown[i] = TMath::Abs(vLoose[i].Eta()-(vJot1Down.Eta()+vJot2Down.Eta())/2.)/deltaEtaJJDown;
        if(TMath::Abs(vLoose[i].Eta()-(vJot1.Eta()+vJot2.Eta())/2.)/deltaEtaJJ > maxLeptonZep)
          maxLeptonZep     = TMath::Abs(vLoose[i].Eta()-(vJot1.Eta()+vJot2.Eta())/2.)/deltaEtaJJ;
        if(TMath::Abs(vLoose[i].Eta()-(vJot1Up.Eta()+vJot2Up.Eta())/2.)/deltaEtaJJUp > maxLeptonZepUp)
	  maxLeptonZepUp   = TMath::Abs(vLoose[i].Eta()-(vJot1Up.Eta()+vJot2Up.Eta())/2.)/deltaEtaJJUp;
        if(TMath::Abs(vLoose[i].Eta()-(vJot1Down.Eta()+vJot2Down.Eta())/2.)/deltaEtaJJDown > maxLeptonZepDown)
	  maxLeptonZepDown = TMath::Abs(vLoose[i].Eta()-(vJot1Down.Eta()+vJot2Down.Eta())/2.)/deltaEtaJJDown;
      }
      bool passZepMax     = thePandaFlat.nJot              >= 2 && maxLeptonZep     < 0.75;
      bool passZepMaxUp   = thePandaFlat.nJot_JESTotalUp   >= 2 && maxLeptonZepUp   < 0.75;
      bool passZepMaxDown = thePandaFlat.nJot_JESTotalDown >= 2 && maxLeptonZepDown < 0.75;


      double wzZep = 0; double wzZepUp = 0; double wzZepDown = 0;
      wzZep	= TMath::Abs(trilep.Eta()-(vJot1.Eta()+vJot2.Eta())/2.)/deltaEtaJJ;
      wzZepUp	= TMath::Abs(trilep.Eta()-(vJot1Up.Eta()+vJot2Up.Eta())/2.)/deltaEtaJJUp;
      wzZepDown = TMath::Abs(trilep.Eta()-(vJot1Down.Eta()+vJot2Down.Eta())/2.)/deltaEtaJJDown;
      bool passwzZep     = thePandaFlat.nJot              >= 2 && wzZep     < 1.00;
      bool passwzZepUp   = thePandaFlat.nJot_JESTotalUp   >= 2 && wzZepUp   < 1.00;
      bool passwzZepDown = thePandaFlat.nJot_JESTotalDown >= 2 && wzZepDown < 1.00;

      double deltaPhiTrileptonMet     = TMath::Abs(trilep.DeltaPhi(vMet));
      double deltaPhiTrileptonMetUp   = TMath::Abs(trilep.DeltaPhi(vMetUp));
      double deltaPhiTrileptonMetDown = TMath::Abs(trilep.DeltaPhi(vMetDown));
      double mtWZ     = TMath::Sqrt(2.0*trilep.Pt()*vMet.Pt()    *(1.0 - cos(deltaPhiTrileptonMet    )));
      double mtWZUp   = TMath::Sqrt(2.0*trilep.Pt()*vMetUp.Pt()  *(1.0 - cos(deltaPhiTrileptonMetUp  )));
      double mtWZDown = TMath::Sqrt(2.0*trilep.Pt()*vMetDown.Pt()*(1.0 - cos(deltaPhiTrileptonMetDown)));

      double zzZep = 0; double zzZepUp = 0; double zzZepDown = 0;
      zzZep	= TMath::Abs(fourlep.Eta()-(vJot1.Eta()+vJot2.Eta())/2.)/deltaEtaJJ;
      zzZepUp	= TMath::Abs(fourlep.Eta()-(vJot1Up.Eta()+vJot2Up.Eta())/2.)/deltaEtaJJUp;
      zzZepDown = TMath::Abs(fourlep.Eta()-(vJot1Down.Eta()+vJot2Down.Eta())/2.)/deltaEtaJJDown;
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
      //                                                            0        1              2              3               4            5             6                 7            8     
      bool passSel[9]     = {qTot != 0 && thePandaFlat.nLooseLep == 2, passMLL, passWWMET    , passNjets    , passDEtaJJ    , passMJJ    , passZepMax    , passBtagVeto    , passTauVeto};
      bool passSelUp[9]   = {qTot != 0 && thePandaFlat.nLooseLep == 2, passMLL, passWWMETUp  , passNjetsUp  , passDEtaJJUp  , passMJJUp  , passZepMaxUp  , passBtagVetoUp  , passTauVeto};
      bool passSelDown[9] = {qTot != 0 && thePandaFlat.nLooseLep == 2, passMLL, passWWMETDown, passNjetsDown, passDEtaJJDown, passMJJDown, passZepMaxDown, passBtagVetoDown, passTauVeto};

      bool passZZPresel = whichWln >= 0 && thePandaFlat.nLooseLep == 4 && lepType <= 2 && mllmin > 4 &&
                          fabs((vZ1l1+vZ1l2).M()-91.1876) < 15 && fabs((vZ2l1+vZ2l2).M()-91.1876) < 15;
      bool passWZPresel = whichWln >= 0 && thePandaFlat.nLooseLep == 3 && trilep.M() > 100 &&
                          fabs(mllZ-91.1876) < 15 && mllmin > 4 && vWln.Pt() > 20;
      //bool passWZPresel = whichWln >= 0 && thePandaFlat.nLooseLep == 3 && trilep.M() > 100 &&
      //                    fabs(mllZ-91.1876) < 15 && mllmin > 4;
      bool passWWSel     = passSel[0]     && passSel[1]     && passSel[2]     && passSel[3]     && passSel[4]     && passSel[5]     && passSel[6]     && passSel[7]     && passSel[8];
      bool passWWSelUp   = passSelUp[0]   && passSelUp[1]   && passSelUp[2]   && passSelUp[3]   && passSelUp[4]   && passSelUp[5]   && passSelUp[6]   && passSelUp[7]   && passSelUp[8];
      bool passWWSelDown = passSelDown[0] && passSelDown[1] && passSelDown[2] && passSelDown[3] && passSelDown[4] && passSelDown[5] && passSelDown[6] && passSelDown[7] && passSelDown[8];
      bool passBtagSel     = passSel[0]     && passSel[1]     && passSel[2]     && passSel[3]     && passSel[4]     && passSel[5]     && passSel[6]     && !passSel[7]     && passSel[8];
      bool passBtagSelUp   = passSelUp[0]   && passSelUp[1]   && passSelUp[2]   && passSelUp[3]   && passSelUp[4]   && passSelUp[5]   && passSelUp[6]   && !passSelUp[7]   && passSelUp[8];
      bool passBtagSelDown = passSelDown[0] && passSelDown[1] && passSelDown[2] && passSelDown[3] && passSelDown[4] && passSelDown[5] && passSelDown[6] && !passSelDown[7] && passSelDown[8];
      bool passWZSel     = passWZPresel && passWZMET     && passSel[3]     && passSel[4]      && passSel[5]	&& passwzZep	 && passSel[7]     && passSel[8];
      bool passWZSelUp   = passWZPresel && passWZMETUp   && passSelUp[3]   && passSelUp[4]    && passSelUp[5]	&& passwzZepUp   && passSelUp[7]   && passSelUp[8];
      bool passWZSelDown = passWZPresel && passWZMETDown && passSelDown[3] && passSelDown[4]  && passSelDown[5] && passwzZepDown && passSelDown[7] && passSelDown[8];
      bool passZZSel     = passZZPresel && passSel[3]	  && passSel[4]      && passSel[5]     && passzzZep;
      bool passZZSelUp   = passZZPresel && passSelUp[3]   && passSelUp[4]    && passSelUp[5]   && passzzZepUp;
      bool passZZSelDown = passZZPresel && passSelDown[3] && passSelDown[4]  && passSelDown[5] && passzzZepDown;
      bool passWZbSel     = passWZPresel && passWZMET     && passSel[3]     && passSel[4]      && passSel[5]	 && passwzZep	  && !passSel[7]     && passSel[8];
      bool passWZbSelUp   = passWZPresel && passWZMETUp   && passSelUp[3]   && passSelUp[4]    && passSelUp[5]	 && passwzZepUp   && !passSelUp[7]   && passSelUp[8];
      bool passWZbSelDown = passWZPresel && passWZMETDown && passSelDown[3] && passSelDown[4]  && passSelDown[5] && passwzZepDown && !passSelDown[7] && passSelDown[8];

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





      int dataCardSel = -1; int dataCardSelUp = -1;int dataCardSelDown = -1;
      if     (passWWSel)   dataCardSel = 0;
      else if(passBtagSel) dataCardSel = 1;
      else if(passZZSel)   dataCardSel = 2;
      else if(passWZbSel)  dataCardSel = 3;
      else if(passWZSel)   dataCardSel = 4;
      if     (passWWSelUp)   dataCardSelUp = 0;
      else if(passBtagSelUp) dataCardSelUp = 1;
      else if(passZZSelUp)   dataCardSelUp = 2;
      else if(passWZbSelUp)  dataCardSelUp = 3;
      else if(passWZSelUp)   dataCardSelUp = 4;
      if     (passWWSelDown)   dataCardSelDown = 0;
      else if(passBtagSelDown) dataCardSelDown = 1;
      else if(passZZSelDown)   dataCardSelDown = 2;
      else if(passWZbSelDown)  dataCardSelDown = 3;
      else if(passWZSelDown)   dataCardSelDown = 4;

 
      bool passSystCuts[nSystTypes] = {dataCardSelUp >= 0, dataCardSelDown >= 0, dataCardSel >= 0, dataCardSel >= 0};

      double totalWeight = 1.0; double puWeight = 1.0; double puWeightUp = 1.0; double puWeightDown = 1.0; double effWSUnc = 1.0; double sf_l1PrefireE = 1.0;
      double triggerWeights[2] = {1.0, 0.0};
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



      //for(int ipoint=0; ipoint<nscan_ft1; ipoint++) printf("point-%i: %f", ipoint, rw_aqgc_ft1[ipoint]);

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

	//float xs_wei = 0;
	//if(xs_wei!=thePandaFlat.normalizedWeight) {printf("xs_normalized weights: %f \n", thePandaFlat.normalizedWeight);xs_wei=thePandaFlat.normalizedWeight;}


        totalWeight = thePandaFlat.normalizedWeight * lumiV[whichYear] * puWeight * thePandaFlat.sf_l1Prefire * looseLepSF[0] * looseLepSF[1] * triggerWeights[0] * theMCPrescale;
	if(thePandaFlat.nLooseLep == 3)      totalWeight = totalWeight * looseLepSF[2];
	else if(thePandaFlat.nLooseLep == 4) totalWeight = totalWeight * looseLepSF[2] * looseLepSF[3];

        if(passBtagVeto) totalWeight = totalWeight * thePandaFlat.sf_btag0;
        else             totalWeight = totalWeight * thePandaFlat.sf_btagGT0;

        if     (infileCat_[ifile] == kPlotWZ)                                                totalWeight = totalWeight * thePandaFlat.sf_wz;
	else if(infileCat_[ifile] == kPlotZZ && infileName_[ifile].Contains("qqZZ") == true) totalWeight = totalWeight * thePandaFlat.sf_zz;
        //else if(infileCat_[ifile] == kPlotEWKSSWW && thePandaFlat.genMjj > 500) totalWeight = totalWeight * hWW_KF_CMS->GetBinContent(hWW_KF_CMS->GetXaxis()->FindFixBin(TMath::Min(thePandaFlat.genMjj,1999.999f)));
        //else if(infileCat_[ifile] == kPlotEWKWZ && thePandaFlat.genMjj > 500) totalWeight = totalWeight * hWZ_KF_CMS->GetBinContent(hWZ_KF_CMS->GetXaxis()->FindFixBin(TMath::Min(thePandaFlat.genMjj,2999.999f)));

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
          if(fidAna == 3 && (theCategory == kPlotEWKSSWW || theCategory == kPlotEWKWZ)) totalWeight = totalWeight * rw_aqgc_ft0[17];
	  theCategory = kPlotWS;
	  int theWSLepton = -1;
	  if     (thePandaFlat.nLooseLep >= 2 && abs(looseLepPdgId[0]) == 11 && thePandaFlat.looseGenLep1PdgId < 0) theWSLepton = 0;
	  else if(thePandaFlat.nLooseLep >= 2 && abs(looseLepPdgId[1]) == 11 && thePandaFlat.looseGenLep2PdgId < 0) theWSLepton = 1;
	  else if(thePandaFlat.nLooseLep >= 3 && abs(looseLepPdgId[2]) == 11 && thePandaFlat.looseGenLep3PdgId < 0) theWSLepton = 2;
	  else if(thePandaFlat.nLooseLep >= 4 && abs(looseLepPdgId[3]) == 11 && thePandaFlat.looseGenLep4PdgId < 0) theWSLepton = 3;
          if(theWSLepton >= 0){
	    int nEta;
            if     (TMath::Abs(vLoose[theWSLepton].Eta()) < 0.5) nEta = 0;
            else if(TMath::Abs(vLoose[theWSLepton].Eta()) < 1.0) nEta = 1;
            else if(TMath::Abs(vLoose[theWSLepton].Eta()) < 1.5) nEta = 2;
            else if(TMath::Abs(vLoose[theWSLepton].Eta()) < 2.0) nEta = 3;
            else                                                 nEta = 4;
	    totalWeight = totalWeight * WSSF[nEta];
	    effWSUnc = WSSFE[nEta];
	  }
	}
      }

      if(usePureMC == false && countLeptonTight != idLep.size()){
        double fakeSF = 1.0;
        double aQGCuseSM = 1.0;
        if(fidAna == 3 && (theCategory == kPlotEWKSSWW || theCategory == kPlotEWKWZ)) aQGCuseSM = aQGCuseSM * rw_aqgc_ft0[17];
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
        totalWeight = totalWeight * fakeSF * aQGCuseSM;
      }


      if(theCategory != kPlotData){
        totalWeight = totalWeight * mcCorrection(0, year, thePandaFlat.jetNMBtags,thePandaFlat.jetNBtags, thePandaFlat.nJot, 0.0, infileCat_[ifile]);
      }


      double bdtValue = 0.0, bdtValueUp = 0.0, bdtValueDown = 0.0;
      if(passWZSel){
        mvaInputs[0] = (float)massJJ;
        mvaInputs[1] = (float)deltaEtaJJ;
        mvaInputs[2] = (float)deltaPhiJJ;
        mvaInputs[3] = (float)wzZepSS[0];
	mvaInputs[4] = (float)wzZepSS[1];
	mvaInputs[5] = (float)wzZepSS[2];
	mvaInputs[6] = (float)vJot1.Pt();
        mvaInputs[7] = (float)vJot2.Pt();
        mvaInputs[8] = (float)vJot1.Eta();
	mvaInputs[9] = (float)wzZep;
        //mvaInputs[10] = (float)mtWZ;
        bdtValue = reader->EvaluateMVA("BDT") ;

        category = theCategory;
        eventNum = thePandaFlat.eventNumber;
        weight   = totalWeight;
        mvamjj   = (float)massJJ;
        mvadeta  = (float)deltaEtaJJ;
        mvadphi  = (float)deltaPhiJJ;
        mvazstar = (float)wzZep;
        mvavWlnpt  = (float)vWln.Pt();
        mvamet     = (float)vMet.Pt();
        mvajetpt1  = (float)vJot1.Pt();
        mvajetpt2  = (float)vJot2.Pt();
        mvajeteta1 = (float)vJot1.Eta();
        mvajeteta2 = (float)vJot2.Eta();
        mvazep1    = (float)wzZepSS[0];
        mvazep2    = (float)wzZepSS[1];
        mvazep3    = (float)wzZepSS[2];
	mvamaxzep  = (float)maxLeptonZep;
        mvamtwz    = (float)mtWZ;

        
        mvatree->Fill();
     }

     if(passWZSelUp){
	mvaInputs[0] = (float)massJJUp;
        mvaInputs[1] = (float)deltaEtaJJUp;
        mvaInputs[2] = (float)deltaPhiJJUp;
        mvaInputs[3] = (float)wzZepSSUp[0];
        mvaInputs[4] = (float)wzZepSSUp[1];
        mvaInputs[5] = (float)wzZepSSUp[2];
	mvaInputs[6] = (float)vJot1Up.Pt();
        mvaInputs[7] = (float)vJot2Up.Pt();
        mvaInputs[8] = (float)vJot1Up.Eta();
	mvaInputs[9] = (float)wzZepUp;
        //mvaInputs[10]= (float)mtWZUp;
        bdtValueUp = reader->EvaluateMVA("BDT") ;
     }

     if(passWZSelDown){
	mvaInputs[0] = (float)massJJDown;
        mvaInputs[1] = (float)deltaEtaJJDown;
        mvaInputs[2] = (float)deltaPhiJJDown;
        mvaInputs[3] = (float)wzZepSSDown[0];
        mvaInputs[4] = (float)wzZepSSDown[1];
        mvaInputs[5] = (float)wzZepSSDown[2];
        mvaInputs[6] = (float)vJot1Down.Pt();
        mvaInputs[7] = (float)vJot2Down.Pt();
        mvaInputs[8] = (float)vJot1Down.Eta();
	mvaInputs[9] = (float)wzZepDown;
        //mvaInputs[10]= (float)mtWZDown;
        bdtValueDown = reader->EvaluateMVA("BDT") ;
      }



      if(theCategory == kPlotEWKSSWW && fidAna == 1 && 
         thePandaFlat.genLep1Pt > 20 && TMath::Abs(thePandaFlat.genLep1Eta) < 2.5 && TMath::Abs(thePandaFlat.genLep1PdgId) != 15 &&
	 thePandaFlat.genLep2Pt > 20 && TMath::Abs(thePandaFlat.genLep2Eta) < 2.5 && TMath::Abs(thePandaFlat.genLep2PdgId) != 15 && 
	 thePandaFlat.genJet1Pt > 50 && TMath::Abs(thePandaFlat.genJet1Eta) < 5.0 &&
	 thePandaFlat.genJet2Pt > 50 && TMath::Abs(thePandaFlat.genJet2Eta) < 5.0){
        if     (thePandaFlat.genMjj >  500 && thePandaFlat.genMjj <=  800) theCategory = kPlotSignal0;
	else if(thePandaFlat.genMjj >  800 && thePandaFlat.genMjj <= 1200) theCategory = kPlotSignal1;
	else if(thePandaFlat.genMjj > 1200 && thePandaFlat.genMjj <= 1800) theCategory = kPlotSignal2;
	else if(thePandaFlat.genMjj > 1800)                                theCategory = kPlotSignal3;
      }
      else if(theCategory == kPlotEWKSSWW && fidAna == 2 && 
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
        if     ((vGen1+vGen2).M() >  20 && (vGen1+vGen2).M() <=  85) theCategory = kPlotSignal0;
	else if((vGen1+vGen2).M() >  85 && (vGen1+vGen2).M() <= 135) theCategory = kPlotSignal1;
	else if((vGen1+vGen2).M() > 135 && (vGen1+vGen2).M() <= 210) theCategory = kPlotSignal2;
	else if((vGen1+vGen2).M() > 210)                             theCategory = kPlotSignal3;
      }

      double totalWeight_aqgc = totalWeight;

      if(fidAna == 3 && (theCategory == kPlotEWKSSWW || theCategory == kPlotEWKWZ)){
        totalWeight *= rw_aqgc_ft0[17];
	/*
        switch(which_para){
          case 1: totalWeight *= rw_aqgc_ft0[which_point]; break;
          case 2: totalWeight *= rw_aqgc_ft1[which_point]; break;
          case 3: totalWeight *= rw_aqgc_ft2[which_point]; break;
          case 4: totalWeight *= rw_aqgc_fm0[which_point]; break;
          case 5: totalWeight *= rw_aqgc_fm1[which_point]; break;
          case 6: totalWeight *= rw_aqgc_fm6[which_point]; break;
          case 7: totalWeight *= rw_aqgc_fm7[which_point]; break;
          case 8: totalWeight *= rw_aqgc_fs0[which_point]; break;
          case 9: totalWeight *= rw_aqgc_fs1[which_point]; break;
        }
	*/
      }
 
      if(passAllButOneSel[0])histo[lepType+  0][theCategory]->Fill(TMath::Min(mllZ,199.999),totalWeight);
      if(passAllButOneSel[1])histo[lepType+  3][theCategory]->Fill(TMath::Min(vMet.Pt(),199.999),totalWeight);
      if(passAllButOneSel[2])histo[lepType+  6][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJot,5.499),totalWeight);
      if(passAllButOneSel[3])histo[lepType+  9][theCategory]->Fill(TMath::Min(deltaEtaJJ,7.999),totalWeight);
      if(passAllButOneSel[4])histo[lepType+ 12][theCategory]->Fill(TMath::Min(massJJ,1999.999),totalWeight);
      if(passAllButOneSel[5])histo[lepType+ 15][theCategory]->Fill(TMath::Min(maxLeptonZep,0.999),totalWeight);
      if(passAllButOneSel[6])histo[lepType+ 18][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNMBtags,4.499),totalWeight);
      if(passAllButOneSel[7])histo[lepType+ 21][theCategory]->Fill(TMath::Min((double)thePandaFlat.nTau,4.499),totalWeight);
      if(passWWSel)          histo[lepType+ 24][theCategory]->Fill(TMath::Min(vZ1l1.Pt(),199.999),totalWeight);
      if(passWWSel)          histo[lepType+ 27][theCategory]->Fill(TMath::Min(vZ1l2.Pt(),199.999),totalWeight);
      if(passWWSel)          histo[lepType+ 30][theCategory]->Fill(TMath::Min(massJJ,1999.999),totalWeight);
      if(passWZSel)          histo[lepType+ 33][theCategory]->Fill(TMath::Min(massJJ,1999.999),totalWeight);
      if(passBtagSel)        histo[lepType+ 37][theCategory]->Fill(TMath::Min(massJJ,1999.999),totalWeight);
      if(passWWSel)          histo[lepType+ 40][theCategory]->Fill(TMath::Min(mllZ,xbinsMLL[nBinMLL]-0.0001),totalWeight);
      if(passBtagSel)        histo[lepType+ 43][theCategory]->Fill(TMath::Min(mllZ,xbinsMLL[nBinMLL]-0.0001),totalWeight);
      if(passWWSel)          histo[lepType+ 46][theCategory]->Fill(vJot1.Eta(),totalWeight);
      if(passWWSel)          histo[lepType+ 46][theCategory]->Fill(vJot2.Eta(),totalWeight);
      if(passBtagSel)        histo[lepType+ 49][theCategory]->Fill(vJot1.Eta(),totalWeight);
      if(passBtagSel)        histo[lepType+ 49][theCategory]->Fill(vJot2.Eta(),totalWeight);
      if(passPresel)         histo[lepType+ 52][theCategory]->Fill(TMath::Min(deltaEtaJJ,7.999),totalWeight);
      if(passPresel)         histo[lepType+ 55][theCategory]->Fill(TMath::Min(massJJ,2499.999),totalWeight);
      if(passPresel)         histo[lepType+ 58][theCategory]->Fill(TMath::Min(maxLeptonZep,0.999),totalWeight);
      if(passPresel)         histo[lepType+ 61][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNBtags,4.499),totalWeight);
      if(passPresel)         histo[lepType+ 64][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNMBtags,4.499),totalWeight);
      if(passPresel && thePandaFlat.jetNBtags > 0)
                             histo[lepType+ 67][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNMBtags,4.499),totalWeight);
      if(passPresel)         histo[lepType+ 70][theCategory]->Fill(TMath::Min((vJot1.Pt()+vJot2.Pt())/2.0,449.999),totalWeight);
      if(passPresel)         histo[lepType+ 73][theCategory]->Fill(vJot1.Eta(),totalWeight);
      if(passPresel)         histo[lepType+ 73][theCategory]->Fill(vJot2.Eta(),totalWeight);
      if(passPresel)         histo[lepType+ 76][theCategory]->Fill(TMath::Min(vZ1l1.Pt(),199.999),totalWeight);
      if(passPresel)         histo[lepType+ 76][theCategory]->Fill(TMath::Min(vZ1l2.Pt(),199.999),totalWeight);
      if(passPresel)         histo[lepType+ 79][theCategory]->Fill(TMath::Abs(vZ1l1.Eta()),totalWeight);
      if(passPresel)         histo[lepType+ 79][theCategory]->Fill(TMath::Abs(vZ1l2.Eta()),totalWeight);
      if(passPresel)         histo[lepType+ 82][theCategory]->Fill(TMath::Max((double)TMath::Max(thePandaFlat.jotCSV[0],thePandaFlat.jotCSV[1]),0.001),totalWeight);
      if(passPresel)         histo[lepType+ 85][theCategory]->Fill(TMath::Max((double)TMath::Min(thePandaFlat.jotCSV[0],thePandaFlat.jotCSV[1]),0.001),totalWeight);
      if(passZSel)           histo[lepType+ 88][theCategory]->Fill(TMath::Min(mllZ,219.999),totalWeight);

      if(passZZSel)          histo[         91][theCategory]->Fill(TMath::Min(massJJ,1999.999),totalWeight);
      if(passWZbSel)         histo[         92][theCategory]->Fill(TMath::Min(massJJ,1999.999),totalWeight);
      if(passWZSel)          histo[         93][theCategory]->Fill(TMath::Max(-0.8, TMath::Min(bdtValue,0.8)),totalWeight);	
      if(passWZSel)          histo[         94][theCategory]->Fill(TMath::Min(mtWZ,999.999),totalWeight);	

      if((theCategory == kPlotData && passWZSel && debug == 1) || debug == 2){
        printf("DATA %d %d %llu | %d %d | %d -> %d %d %d %d %d %d %d %d %d | %.1f %.1f %.1f %.1f %.2f | %.1f %.1f %.1f %d | %.2f %.2f %.2f %.2f %.2f %.2f / %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",
	thePandaFlat.runNumber,thePandaFlat.lumiNumber,thePandaFlat.eventNumber,theCategory,lepType,
	passWZSel,passSel[0],passSel[1],passSel[2],passSel[3],passSel[4],passSel[5],passSel[6],passSel[7],passSel[8],
	mllZ,vMet.Pt(),deltaEtaJJ,massJJ,maxLeptonZep,
	fabs(mllZ-91.1876),mllmin,vWln.Pt(),whichWln,vJot1.Pt(),vJot1.Eta(),vJot1.Phi(),vJot2.Pt(),vJot2.Eta(),vJot2.Phi(),
	vLoose[0].Pt(),vLoose[0].Eta(),vLoose[0].Phi(),vLoose[1].Pt(),vLoose[1].Eta(),vLoose[1].Phi(),vLoose[2].Pt(),vLoose[2].Eta(),vLoose[2].Phi());
      }


      if(1){
        double typeSelAux0 = 0;
        if     (mllZ <  85) typeSelAux0 = 0;
        else if(mllZ < 135) typeSelAux0 = 1;
        else if(mllZ < 210) typeSelAux0 = 2;
        else                typeSelAux0 = 3;
        //double typeSelAux1 = 0;
	//if(qTot>0) typeSelAux1 = 1;
        double MVAVar     = TMath::Min(massJJ     ,xbinsMJJ[nBinMJJ]-0.0001);
        double MVAVarUp   = TMath::Min(massJJUp   ,xbinsMJJ[nBinMJJ]-0.0001);
        double MVAVarDown = TMath::Min(massJJDown ,xbinsMJJ[nBinMJJ]-0.0001);
        if(fidAna != 3){
          double typeSelAux1[3] = {0,0,0};
          if(deltaEtaJJ     > 4.5) typeSelAux1[0] = 1;
          if(deltaEtaJJUp   > 4.5) typeSelAux1[1] = 1;
          if(deltaEtaJJDown > 4.5) typeSelAux1[2] = 1;
          if(dataCardSel     == 4) MVAVar     = (1 + TMath::Max(-1., TMath::Min(bdtValue,     0.7999))) * 1000;
          if(dataCardSelUp   == 4) MVAVarUp   = (1 + TMath::Max(-1., TMath::Min(bdtValueUp,   0.7999))) * 1000; 
          if(dataCardSelDown == 4) MVAVarDown = (1 + TMath::Max(-1., TMath::Min(bdtValueDown, 0.7999))) * 1000;

          if     (dataCardSel     == 0) MVAVar     = MVAVar     + 2000 * typeSelAux0 + 8000 * typeSelAux1[0];
          else if(dataCardSel     == 1) MVAVar     = MVAVar     + 16000 + 2000 * typeSelAux1[0];
          else if(dataCardSel     == 2) MVAVar     = MVAVar     + 20000;
          else if(dataCardSel     == 3) MVAVar     = MVAVar     + 22000;
          else if(dataCardSel     == 4) MVAVar     = MVAVar     + 24000;

          if     (dataCardSelUp   == 0) MVAVarUp   = MVAVarUp   + 2000 * typeSelAux0 + 8000 * typeSelAux1[1];
          else if(dataCardSelUp   == 1) MVAVarUp   = MVAVarUp   + 16000 + 2000 * typeSelAux1[1];
          else if(dataCardSelUp   == 2) MVAVarUp   = MVAVarUp   + 20000;
          else if(dataCardSelUp   == 3) MVAVarUp   = MVAVarUp   + 22000;
          else if(dataCardSelUp   == 4) MVAVarUp   = MVAVarUp   + 24000;

          if     (dataCardSelDown == 0) MVAVarDown = MVAVarDown + 2000 * typeSelAux0 + 8000 * typeSelAux1[2];
          else if(dataCardSelDown == 1) MVAVarDown = MVAVarDown + 16000 + 2000 * typeSelAux1[2];
          else if(dataCardSelDown == 2) MVAVarDown = MVAVarDown + 20000;
          else if(dataCardSelDown == 3) MVAVarDown = MVAVarDown + 22000;
          else if(dataCardSelDown == 4) MVAVarDown = MVAVarDown + 24000;
        }
        else {
          //if     (mllZ < 210) typeSelAux0 = 0;
          //else if(mllZ < 420) typeSelAux0 = 1;
          //else                typeSelAux0 = 2;

          if     (mllZ < 150) typeSelAux0 = 0;
          else if(mllZ < 300) typeSelAux0 = 1;
          else if(mllZ < 450) typeSelAux0 = 2;
          else if(mllZ < 600) typeSelAux0 = 3;
          else                typeSelAux0 = 4;


          double typeSelAux2[3] = {0,0,0};
          if     (mtWZ <  300) typeSelAux2[0] = 0;
	  else if(mtWZ <  600) typeSelAux2[0] = 1;
	  else                 typeSelAux2[0] = 2; 
          if     (mtWZUp <  300) typeSelAux2[1] = 0;
	  else if(mtWZUp <  600) typeSelAux2[1] = 1;
	  else                   typeSelAux2[1] = 2; 
          if     (mtWZDown <  300) typeSelAux2[2] = 0;
	  else if(mtWZDown <  600) typeSelAux2[2] = 1;
	  else                     typeSelAux2[2] = 2;

          /*
          if     (mtWZ <  350) typeSelAux2[0] = 0;
          else if(mtWZ <  700) typeSelAux2[0] = 1;
          else if(mtWZ <  1000) typeSelAux2[0] = 2;
          else                 typeSelAux2[0] = 3;
          if     (mtWZUp <  350) typeSelAux2[1] = 0;
          else if(mtWZUp <  700) typeSelAux2[1] = 1;
          else if(mtWZUp <  1000) typeSelAux2[1] = 2;
          else                   typeSelAux2[1] = 3; 
          if     (mtWZDown <  350) typeSelAux2[2] = 0;
          else if(mtWZDown <  700) typeSelAux2[2] = 1;
          else if(mtWZDown <  1000) typeSelAux2[2] = 2;
          else                     typeSelAux2[2] = 3;
          */

	  /*
          if     (dataCardSel     == 0)			MVAVar     = MVAVar	+ 2000 * typeSelAux0;
          else if(dataCardSel     == 1)                 MVAVar     = MVAVar     + 6000;
          else if(dataCardSel     == 2) 		MVAVar     = MVAVar     + 8000;
          else if(dataCardSel     == 3) 		MVAVar     = MVAVar     + 10000;
          else if(dataCardSel     == 4) 		MVAVar     = MVAVar     + 12000 + 2000 * typeSelAux2[0];

          if     (dataCardSelUp   == 0)			MVAVarUp   = MVAVarUp	+ 2000 * typeSelAux0;
          else if(dataCardSelUp   == 1) 		MVAVarUp   = MVAVarUp   + 6000;
          else if(dataCardSelUp   == 2) 		MVAVarUp   = MVAVarUp   + 8000;
          else if(dataCardSelUp   == 3) 		MVAVarUp   = MVAVarUp   + 10000;
          else if(dataCardSelUp   == 4) 		MVAVarUp   = MVAVarUp   + 12000 + 2000 * typeSelAux2[1];

          if     (dataCardSelDown == 0)			MVAVarDown = MVAVarDown	+ 2000 * typeSelAux0;
          else if(dataCardSelDown == 1) 		MVAVarDown = MVAVarDown + 6000;
          else if(dataCardSelDown == 2) 		MVAVarDown = MVAVarDown + 8000;
          else if(dataCardSelDown == 3) 		MVAVarDown = MVAVarDown + 10000;
          else if(dataCardSelDown == 4) 		MVAVarDown = MVAVarDown + 12000 + 2000 * typeSelAux2[2];
	  */

          if     (dataCardSel     == 0)                 MVAVar     = MVAVar     + 2000 * typeSelAux0;
          else if(dataCardSel     == 1)                 MVAVar     = MVAVar     + 10000;
          else if(dataCardSel     == 2)                 MVAVar     = MVAVar     + 12000;
          else if(dataCardSel     == 3)                 MVAVar     = MVAVar     + 14000;
          else if(dataCardSel     == 4)                 MVAVar     = MVAVar     + 16000 + 2000 * typeSelAux2[0];

          if     (dataCardSelUp   == 0)                 MVAVarUp   = MVAVarUp   + 2000 * typeSelAux0;
          else if(dataCardSelUp   == 1)                 MVAVarUp   = MVAVarUp   + 10000;
          else if(dataCardSelUp   == 2)                 MVAVarUp   = MVAVarUp   + 12000;
          else if(dataCardSelUp   == 3)                 MVAVarUp   = MVAVarUp   + 14000;
          else if(dataCardSelUp   == 4)                 MVAVarUp   = MVAVarUp   + 16000 + 2000 * typeSelAux2[1];

          if     (dataCardSelDown == 0)                 MVAVarDown = MVAVarDown + 2000 * typeSelAux0;
          else if(dataCardSelDown == 1)                 MVAVarDown = MVAVarDown + 10000;
          else if(dataCardSelDown == 2)                 MVAVarDown = MVAVarDown + 12000;
          else if(dataCardSelDown == 3)                 MVAVarDown = MVAVarDown + 14000;
          else if(dataCardSelDown == 4)                 MVAVarDown = MVAVarDown + 16000 + 2000 * typeSelAux2[2];


	}

        // Avoid QCD scale weights that are anomalous high
        double maxQCDscale = (TMath::Abs(thePandaFlat.scale[0])+TMath::Abs(thePandaFlat.scale[1])+TMath::Abs(thePandaFlat.scale[2])+
	                      TMath::Abs(thePandaFlat.scale[3])+TMath::Abs(thePandaFlat.scale[4])+TMath::Abs(thePandaFlat.scale[5]))/6.0;
        if(maxQCDscale == 0) maxQCDscale = 1;

        double sf_ewkcorrvv_unc = 1.0; double sf_ewkcorrzz_unc = 1.0; double sf_ggcorrzz_unc = 1.0; double sf_corrwzzz_unc = 1.0;
	if     (theCategory == kPlotWZ) sf_ewkcorrvv_unc = 1.02;
	else if(theCategory == kPlotZZ && infileName_[ifile].Contains("qqZZ") == true) sf_ewkcorrzz_unc = thePandaFlat.sf_zzUnc;
	else if(theCategory == kPlotZZ) sf_ggcorrzz_unc = 1.10;
	//else if((theCategory == kPlotEWKSSWW) && thePandaFlat.genMjj > 500) sf_ewkcorrvv_unc = hWW_KF_CMSUp->GetBinContent(hWW_KF_CMSUp->GetXaxis()->FindFixBin(TMath::Min(thePandaFlat.genMjj,1999.999f)))/
	//                                                                                     hWW_KF_CMS  ->GetBinContent(hWW_KF_CMS  ->GetXaxis()->FindFixBin(TMath::Min(thePandaFlat.genMjj,1999.999f)));
	//else if((theCategory == kPlotEWKWZ) && thePandaFlat.genMjj > 500) sf_ewkcorrvv_unc = hWZ_KF_CMSUp->GetBinContent(hWZ_KF_CMSUp->GetXaxis()->FindFixBin(TMath::Min(thePandaFlat.genMjj,2999.999f)))/
	//                                                                                   hWZ_KF_CMS  ->GetBinContent(hWZ_KF_CMS  ->GetXaxis()->FindFixBin(TMath::Min(thePandaFlat.genMjj,2999.999f)));



        if     (theCategory == kPlotData && dataCardSel >= 0){
          histo_Baseline[theCategory]->Fill(MVAVar,totalWeight);
        }
        else if(theCategory != kPlotData){
	  if(dataCardSel >= 0) {
            //if(theCategory == kPlotWS) printf("after reweighting SM: %f", totalWeight);
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
        }  //end else if category

        if( fidAna == 3 && ( (theCategory == kPlotEWKSSWW && (dataCardSel   == 0 || dataCardSel   == 1)) || (theCategory == kPlotEWKWZ &&  dataCardSel   == 4) ) ){

          int icc = (theCategory == kPlotEWKWZ) ? 1 : 0;
          //MVAVar  = (icc == 0) ? MVAVar : (MVAVar-12000);
          MVAVar  = (icc == 0) ? MVAVar : (MVAVar-16000);

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

    mvaoutf->cd();
    mvaoutf->Write();
    mvaoutf->Close();
    if(produceMVAInputs == false) system(Form("rm -f %s",outMVAfile));
    the_input_file->Close();
  } // end chain loop

  for(int ic=0; ic<nPlotCategories; ic++) histo[allPlots-1][ic]->Add(histo_Baseline[ic]);

  double syst_WZl[2] = {1.010, 1.012};

  for(unsigned ic=0; ic<nPlotCategories; ic++) {

    if(fidAna == 3 && ic == kPlotData){
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
      if(fidAna != 3){
        histo_Baseline            [ic]->SetBinContent(nb, TMath::Max((float)histo_Baseline		[ic]->GetBinContent(nb),1e-7f));
        histo_QCDScaleUp  	  [ic]->SetBinContent(nb, TMath::Max((float)histo_QCDScaleUp		[ic]->GetBinContent(nb),1e-7f));
        histo_QCDScaleDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_QCDScaleDown  	[ic]->GetBinContent(nb),1e-7f));
        histo_PDFBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PDFBoundingUp 	[ic]->GetBinContent(nb),1e-7f));
        histo_PDFBoundingDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PDFBoundingDown	[ic]->GetBinContent(nb),1e-7f));
        histo_LepEffMBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_LepEffMBoundingUp	[ic]->GetBinContent(nb),1e-7f));
        histo_LepEffMBoundingDown [ic]->SetBinContent(nb, TMath::Max((float)histo_LepEffMBoundingDown	[ic]->GetBinContent(nb),1e-7f));
        histo_LepEffEBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_LepEffEBoundingUp	[ic]->GetBinContent(nb),1e-7f));
        histo_LepEffEBoundingDown [ic]->SetBinContent(nb, TMath::Max((float)histo_LepEffEBoundingDown	[ic]->GetBinContent(nb),1e-7f));
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
        histo_WSBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_WSBoundingUp	        [ic]->GetBinContent(nb),1e-7f));
        histo_WSBoundingDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_WSBoundingDown	[ic]->GetBinContent(nb),1e-7f));
        histo_EWKCorrVVUp 	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKCorrVVUp		[ic]->GetBinContent(nb),1e-7f));
        histo_EWKCorrVVDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKCorrVVDown 	[ic]->GetBinContent(nb),1e-7f));
        histo_EWKqqZZCorrUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKqqZZCorrUp 	[ic]->GetBinContent(nb),1e-7f));
        histo_EWKqqZZCorrDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKqqZZCorrDown	[ic]->GetBinContent(nb),1e-7f));
        histo_ggZZCorrUp  	  [ic]->SetBinContent(nb, TMath::Max((float)histo_ggZZCorrUp		[ic]->GetBinContent(nb),1e-7f));
        histo_ggZZCorrDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_ggZZCorrDown  	[ic]->GetBinContent(nb),1e-7f));
      }else if(fidAna == 3){
        int itype = -1; int nbnew = 0;
        if(nb <= nBinMVA_ww) {itype = 0; nbnew = nb;}
        else if(nb > nBinMVA_ww + nBinMVA_interval && nb <= nBinMVA_ww + nBinMVA_wz + nBinMVA_interval){itype = 1; nbnew = nb - (nBinMVA_ww + nBinMVA_interval);}
        else continue;

        histo_dim8_Baseline            [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_Baseline              [ic]->GetBinContent(nb),1e-7f));
        histo_dim8_QCDScaleUp          [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_QCDScaleUp            [ic]->GetBinContent(nb),1e-7f));
        histo_dim8_QCDScaleDown        [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_QCDScaleDown          [ic]->GetBinContent(nb),1e-7f));
        histo_dim8_PDFBoundingUp       [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_PDFBoundingUp         [ic]->GetBinContent(nb),1e-7f));
        histo_dim8_PDFBoundingDown     [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_PDFBoundingDown       [ic]->GetBinContent(nb),1e-7f));
        histo_dim8_LepEffMBoundingUp   [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_LepEffMBoundingUp     [ic]->GetBinContent(nb),1e-7f));
        histo_dim8_LepEffMBoundingDown [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_LepEffMBoundingDown   [ic]->GetBinContent(nb),1e-7f));
        histo_dim8_LepEffEBoundingUp   [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_LepEffEBoundingUp     [ic]->GetBinContent(nb),1e-7f));
        histo_dim8_LepEffEBoundingDown [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_LepEffEBoundingDown   [ic]->GetBinContent(nb),1e-7f));
        histo_dim8_PUBoundingUp        [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_PUBoundingUp          [ic]->GetBinContent(nb),1e-7f));
        histo_dim8_PUBoundingDown      [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_PUBoundingDown        [ic]->GetBinContent(nb),1e-7f));
        for(int ny=0; ny<nYears; ny++){
        histo_dim8_BTAGBBoundingUp    [itype][ny][ic]->SetBinContent(nbnew, TMath::Max((float)histo_BTAGBBoundingUp    [ny][ic]->GetBinContent(nb),1e-7f));
        histo_dim8_BTAGBBoundingDown  [itype][ny][ic]->SetBinContent(nbnew, TMath::Max((float)histo_BTAGBBoundingDown  [ny][ic]->GetBinContent(nb),1e-7f));
        histo_dim8_BTAGLBoundingUp    [itype][ny][ic]->SetBinContent(nbnew, TMath::Max((float)histo_BTAGLBoundingUp    [ny][ic]->GetBinContent(nb),1e-7f));
        histo_dim8_BTAGLBoundingDown  [itype][ny][ic]->SetBinContent(nbnew, TMath::Max((float)histo_BTAGLBoundingDown  [ny][ic]->GetBinContent(nb),1e-7f));
        histo_dim8_JESBoundingUp      [itype][ny][ic]->SetBinContent(nbnew, TMath::Max((float)histo_JESBoundingUp      [ny][ic]->GetBinContent(nb),1e-7f));
        histo_dim8_JESBoundingDown    [itype][ny][ic]->SetBinContent(nbnew, TMath::Max((float)histo_JESBoundingDown    [ny][ic]->GetBinContent(nb),1e-7f));
        histo_dim8_PreFireBoundingUp  [itype][ny][ic]->SetBinContent(nbnew, TMath::Max((float)histo_PreFireBoundingUp  [ny][ic]->GetBinContent(nb),1e-7f));
        histo_dim8_PreFireBoundingDown[itype][ny][ic]->SetBinContent(nbnew, TMath::Max((float)histo_PreFireBoundingDown[ny][ic]->GetBinContent(nb),1e-7f));
        histo_dim8_TriggerBoundingUp  [itype][ny][ic]->SetBinContent(nbnew, TMath::Max((float)histo_TriggerBoundingUp  [ny][ic]->GetBinContent(nb),1e-7f));
        histo_dim8_TriggerBoundingDown[itype][ny][ic]->SetBinContent(nbnew, TMath::Max((float)histo_TriggerBoundingDown[ny][ic]->GetBinContent(nb),1e-7f));
        }
        histo_dim8_WSBoundingUp        [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_WSBoundingUp          [ic]->GetBinContent(nb),1e-7f));
        histo_dim8_WSBoundingDown      [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_WSBoundingDown        [ic]->GetBinContent(nb),1e-7f));
        histo_dim8_EWKCorrVVUp         [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_EWKCorrVVUp           [ic]->GetBinContent(nb),1e-7f));
        histo_dim8_EWKCorrVVDown       [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_EWKCorrVVDown         [ic]->GetBinContent(nb),1e-7f));
        histo_dim8_EWKqqZZCorrUp       [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_EWKqqZZCorrUp         [ic]->GetBinContent(nb),1e-7f));
        histo_dim8_EWKqqZZCorrDown     [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_EWKqqZZCorrDown       [ic]->GetBinContent(nb),1e-7f));
        histo_dim8_ggZZCorrUp          [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_ggZZCorrUp            [ic]->GetBinContent(nb),1e-7f));
        histo_dim8_ggZZCorrDown        [itype][ic]->SetBinContent(nbnew, TMath::Max((float)histo_ggZZCorrDown          [ic]->GetBinContent(nb),1e-7f));
      }
    } // end loop on bins

    if(fidAna != 3){
      histo_PUBoundingUp  [ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_PUBoundingUp  [ic]->GetSumOfWeights());
      histo_PUBoundingDown[ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_PUBoundingDown[ic]->GetSumOfWeights());
      if(fidAna >= 1 && (ic == kPlotWZ || ic == kPlotEWKWZ || ic == kPlotEWKSSWW ||
         ic == kPlotSignal0 || ic == kPlotSignal1 || ic == kPlotSignal2 || ic == kPlotSignal3)) {
        histo_QCDScaleUp   [ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_QCDScaleUp   [ic]->GetSumOfWeights());
        histo_QCDScaleDown [ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_QCDScaleDown [ic]->GetSumOfWeights());
        histo_EWKCorrVVUp  [ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_EWKCorrVVUp  [ic]->GetSumOfWeights());
        histo_EWKCorrVVDown[ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_EWKCorrVVDown[ic]->GetSumOfWeights());
      }
      if(ic == kPlotZZ || ic == kPlotVVV) {
        histo_QCDScaleUp     [ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_QCDScaleUp     [ic]->GetSumOfWeights());
        histo_QCDScaleDown   [ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_QCDScaleDown   [ic]->GetSumOfWeights());
        histo_EWKCorrVVUp    [ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_EWKCorrVVUp    [ic]->GetSumOfWeights());
        histo_EWKCorrVVDown  [ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_EWKCorrVVDown  [ic]->GetSumOfWeights());
        histo_EWKqqZZCorrUp  [ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_EWKqqZZCorrUp  [ic]->GetSumOfWeights());
        histo_EWKqqZZCorrDown[ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_EWKqqZZCorrDown[ic]->GetSumOfWeights());
        histo_ggZZCorrUp     [ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_ggZZCorrUp     [ic]->GetSumOfWeights());
        histo_ggZZCorrDown   [ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_ggZZCorrDown   [ic]->GetSumOfWeights());
      }
    }else if(fidAna == 3){

      for(int itype=0; itype!=2; itype++){
        histo_dim8_PUBoundingUp  [itype][ic]->Scale(histo_dim8_Baseline[itype][ic]->GetSumOfWeights()/histo_dim8_PUBoundingUp  [itype][ic]->GetSumOfWeights());
        histo_dim8_PUBoundingDown[itype][ic]->Scale(histo_dim8_Baseline[itype][ic]->GetSumOfWeights()/histo_dim8_PUBoundingDown[itype][ic]->GetSumOfWeights());
        if(ic == kPlotWZ || ic == kPlotEWKWZ || ic == kPlotEWKSSWW || ic == kPlotZZ || ic == kPlotVVV) {
          histo_dim8_QCDScaleUp   [itype][ic]->Scale(histo_dim8_Baseline[itype][ic]->GetSumOfWeights()/histo_dim8_QCDScaleUp   [itype][ic]->GetSumOfWeights());
          histo_dim8_QCDScaleDown [itype][ic]->Scale(histo_dim8_Baseline[itype][ic]->GetSumOfWeights()/histo_dim8_QCDScaleDown [itype][ic]->GetSumOfWeights());
          histo_dim8_EWKCorrVVUp  [itype][ic]->Scale(histo_dim8_Baseline[itype][ic]->GetSumOfWeights()/histo_dim8_EWKCorrVVUp  [itype][ic]->GetSumOfWeights());
          histo_dim8_EWKCorrVVDown[itype][ic]->Scale(histo_dim8_Baseline[itype][ic]->GetSumOfWeights()/histo_dim8_EWKCorrVVDown[itype][ic]->GetSumOfWeights());
          if(ic == kPlotZZ || ic == kPlotVVV){
          histo_dim8_EWKqqZZCorrUp  [itype][ic]->Scale(histo_dim8_Baseline[itype][ic]->GetSumOfWeights()/histo_dim8_EWKqqZZCorrUp  [itype][ic]->GetSumOfWeights());
          histo_dim8_EWKqqZZCorrDown[itype][ic]->Scale(histo_dim8_Baseline[itype][ic]->GetSumOfWeights()/histo_dim8_EWKqqZZCorrDown[itype][ic]->GetSumOfWeights());
          histo_dim8_ggZZCorrUp     [itype][ic]->Scale(histo_dim8_Baseline[itype][ic]->GetSumOfWeights()/histo_dim8_ggZZCorrUp     [itype][ic]->GetSumOfWeights());
          histo_dim8_ggZZCorrDown   [itype][ic]->Scale(histo_dim8_Baseline[itype][ic]->GetSumOfWeights()/histo_dim8_ggZZCorrDown   [itype][ic]->GetSumOfWeights());
          }
        }
      } 
    }  //end if fidAna  == 3
  }  //end loop on nCat

  if(fidAna == 3){
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
  } //end if fidAna == 3

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
  sprintf(outputLimits,"ssww_%d%s_input.root",year,fidAnaName.Data());

  if(fidAna != 3){
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
    histo_WSBoundingUp          [ic]->Write();
    histo_WSBoundingDown        [ic]->Write();
    histo_EWKCorrVVUp		[ic]->Write();
    histo_EWKCorrVVDown 	[ic]->Write();
    histo_EWKqqZZCorrUp 	[ic]->Write();
    histo_EWKqqZZCorrDown	[ic]->Write();
    histo_ggZZCorrUp		[ic]->Write();
    histo_ggZZCorrDown  	[ic]->Write();
  }
  outFileLimits->Close();
  }

  else if(fidAna == 3){

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
            ic != kPlotSignal2 && ic != kPlotSignal2) newcardShape << Form("%d  ", ic);
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

  newcardShape << Form("EWKCorrVV%s    shape     ",plotBaseNames[kPlotWZ].Data());
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotWZ) newcardShape << Form("- ");
    else              newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("EWKCorrVV%s    shape     ",plotBaseNames[kPlotEWKSSWW].Data());
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotEWKSSWW) newcardShape << Form("- ");
    else                   newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("EWKCorrVV%s    shape     ",plotBaseNames[kPlotEWKWZ].Data());
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotEWKWZ) newcardShape << Form("- ");
    else                 newcardShape << Form("1.0 ");
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

  newcardShape << Form("WZ_lep    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotWZ && ic != kPlotEWKWZ) newcardShape << Form("- ");
    else                                  newcardShape << Form("%f ",syst_WZl[0]);
  }
  newcardShape << Form("\n");

  newcardShape << Form("WZ_tau    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotWZ && ic != kPlotEWKWZ) newcardShape << Form("- ");
    else                                  newcardShape << Form("%f ",syst_WZl[1]);
  }
  newcardShape << Form("\n");

  for(unsigned ic=0; ic<nPlotCategories; ic++) {
    if(ic== kPlotData || ic == kPlotNonPrompt || ic == kPlotEWKWZ || ic == kPlotEWKSSWW || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
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

  if(fidAna == 0){
    newcardShape << Form("CMS_ssww_wznorm  rateParam * %s 1 [0.1,3]\n",plotBaseNames[kPlotWZ].Data());
    newcardShape << Form("CMS_ssww_wznorm  rateParam * %s 1 [0.1,3]\n",plotBaseNames[kPlotEWKWZ].Data());
  }
  newcardShape << Form("CMS_ssww_vvvnorm rateParam * %s 1 [0.1,3]\n",plotBaseNames[kPlotVVV].Data());
  newcardShape << Form("CMS_ssww_zznorm  rateParam * %s 1 [0.1,3]\n",plotBaseNames[kPlotZZ].Data());

  newcardShape << Form("ch1 autoMCStats 0\n");

  newcardShape.close();


  // Writing standard histograms
  char output[200];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    sprintf(output,"histossww_%d_%d%s.root",year,thePlot,fidAnaName.Data());	
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    double totBck = 0;
    for(int i=1; i<nPlotCategories; i++) totBck = totBck + histo[thePlot][i]->GetSumOfWeights();
    printf("(%2d) %7.1f vs. %7.1f ",thePlot,histo[thePlot][0]->GetSumOfWeights(),totBck);
    printf("(");
    for(int i=1; i<nPlotCategories; i++) printf("%7.1f ",histo[thePlot][i]->GetSumOfWeights());
    printf(")\n");
    for(int np=0; np<nPlotCategories; np++) {histo[thePlot][np]->SetNameTitle(Form("histo%d",np),Form("histo%d",np));histo[thePlot][np]->Write();}
    outFilePlotsNote->Close();
  }

}
