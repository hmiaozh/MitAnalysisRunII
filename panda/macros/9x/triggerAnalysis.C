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
#include "TLorentzVector.h"

#include "MitAnalysisRunII/panda/macros/9x/pandaFlat.C"
#include "MitAnalysisRunII/panda/macros/9x/common.h"
#include "MitAnalysisRunII/panda/macros/9x/applyCorrections.h"

void triggerAnalysis(
int year,
int whichLepSel = 0
){

  //*******************************************************
  //Input Files
  //*******************************************************
  TString filesPath;
  TString puPath;
  vector<TString> infileName_;
  vector<int> infileCat_;

  if     (year == 2018){
    filesPath = "/data/t3home000/ceballos/panda/v_006_0/";
    puPath = "MitAnalysisRunII/data/90x/puWeights_90x_2018.root";
    infileName_.push_back(Form("%sMET.root",filesPath.Data()));                   infileCat_.push_back(0);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data()));                 infileCat_.push_back(1);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data()));                 infileCat_.push_back(1);
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		  infileCat_.push_back(1);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));                   infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_M-50_LO.root",filesPath.Data()));    infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_M-50_NLO.root",filesPath.Data()));   infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYNJetsToLL.root",filesPath.Data()));           infileCat_.push_back(1);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	          infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYNJetsToLL_NLO.root",filesPath.Data()));       infileCat_.push_back(1);
    infileName_.push_back(Form("%sZH_ZToLL_HToGDarkG_M125.root",filesPath.Data()));infileCat_.push_back(1);
    infileName_.push_back(Form("%sZH_ZToLL_HToGDarkG_M200.root",filesPath.Data()));infileCat_.push_back(1);
    infileName_.push_back(Form("%sZH_ZToLL_HToGDarkG_M300.root",filesPath.Data()));infileCat_.push_back(1);
    infileName_.push_back(Form("%sqqZH125inv.root" ,filesPath.Data()));           infileCat_.push_back(1);
    infileName_.push_back(Form("%sggZH125inv.root" ,filesPath.Data()));           infileCat_.push_back(1);
  }
  else if(year == 2017){
    filesPath = "/data/t3home000/ceballos/panda/v_004_0/";
    puPath = "MitAnalysisRunII/data/90x/puWeights_90x_2017.root";
    infileName_.push_back(Form("%sMET.root",filesPath.Data()));                   infileCat_.push_back(0);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data()));		  infileCat_.push_back(1);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data()));		  infileCat_.push_back(1);
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		  infileCat_.push_back(1);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		          infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_M-50_LO.root",filesPath.Data()));    infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_M-50_NLO.root",filesPath.Data()));   infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYNJetsToLL_NLO.root",filesPath.Data()));       infileCat_.push_back(1);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	          infileCat_.push_back(1);
    infileName_.push_back(Form("%sZH_ZToLL_HToGDarkG_M125.root",filesPath.Data()));infileCat_.push_back(1);
    infileName_.push_back(Form("%sZH_ZToLL_HToGDarkG_M200.root",filesPath.Data()));infileCat_.push_back(1);
    infileName_.push_back(Form("%sZH_ZToLL_HToGDarkG_M300.root",filesPath.Data()));infileCat_.push_back(1);
    infileName_.push_back(Form("%sqqZH125inv.root" ,filesPath.Data()));           infileCat_.push_back(1);
    infileName_.push_back(Form("%sggZH125inv.root" ,filesPath.Data()));           infileCat_.push_back(1);
  }
  else if(year == 2016){
    filesPath = "/data/t3home000/ceballos/panda/v_002_0/";
    puPath = "MitAnalysisRunII/data/80x/puWeights_80x_37ifb.root";
    infileName_.push_back(Form("%sMET.root",filesPath.Data()));		          infileCat_.push_back(0);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	          infileCat_.push_back(1);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	          infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data()));  infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_M-50_NLO.root" ,filesPath.Data()));  infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_Pt0To50.root",filesPath.Data()));    infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_Pt50To100.root",filesPath.Data()));  infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_Pt100To250.root",filesPath.Data())); infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_Pt250To400.root",filesPath.Data())); infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_Pt400To650.root",filesPath.Data())); infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_Pt650ToInf.root",filesPath.Data())); infileCat_.push_back(1);
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));                 infileCat_.push_back(1);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));                   infileCat_.push_back(1);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	          infileCat_.push_back(1);
    infileName_.push_back(Form("%sZH_ZToLL_HToGDarkG_M125.root",filesPath.Data()));infileCat_.push_back(1);
    infileName_.push_back(Form("%sZH_ZToLL_HToGDarkG_M200.root",filesPath.Data()));infileCat_.push_back(1);
    infileName_.push_back(Form("%sZH_ZToLL_HToGDarkG_M300.root",filesPath.Data()));infileCat_.push_back(1);
    infileName_.push_back(Form("%sqqZH125inv.root" ,filesPath.Data()));           infileCat_.push_back(1);
    infileName_.push_back(Form("%sggZH125inv.root" ,filesPath.Data()));           infileCat_.push_back(1);
  }

  //infileName_.clear();infileCat_.clear();
  //infileName_.push_back(Form("%sqqZH125inv.root" ,filesPath.Data()));	       infileCat_.push_back(1);

  TFile *fPUFile = TFile::Open(puPath.Data());
  TH1D *fhDPU = (TH1D*)(fPUFile->Get("puWeights")); assert(fhDPU); fhDPU->SetDirectory(0);
  delete fPUFile;

  const int nTrgBinPt1 = 7; Float_t xTrgBinPt1[nTrgBinPt1+1] = {20,25,30,35,40,50,60,70};
  const int nTrgBinPt2 = 7; Float_t xTrgBinPt2[nTrgBinPt2+1] = {20,25,30,35,40,50,60,70};
  TH2D *hDTrgNumMMBB[2];TH2D *hDTrgDenMMBB[2];
  TH2D *hDTrgNumMMEB[2];TH2D *hDTrgDenMMEB[2];
  TH2D *hDTrgNumMMBE[2];TH2D *hDTrgDenMMBE[2];
  TH2D *hDTrgNumMMEE[2];TH2D *hDTrgDenMMEE[2];
  TH2D *hDTrgNumEEBB[2];TH2D *hDTrgDenEEBB[2];
  TH2D *hDTrgNumEEEB[2];TH2D *hDTrgDenEEEB[2];
  TH2D *hDTrgNumEEBE[2];TH2D *hDTrgDenEEBE[2];
  TH2D *hDTrgNumEEEE[2];TH2D *hDTrgDenEEEE[2];
  TH2D *hDTrgNumMEBB[2];TH2D *hDTrgDenMEBB[2];
  TH2D *hDTrgNumMEEB[2];TH2D *hDTrgDenMEEB[2];
  TH2D *hDTrgNumMEBE[2];TH2D *hDTrgDenMEBE[2];
  TH2D *hDTrgNumMEEE[2];TH2D *hDTrgDenMEEE[2];
  TH2D *hDTrgNumEMBB[2];TH2D *hDTrgDenEMBB[2];
  TH2D *hDTrgNumEMEB[2];TH2D *hDTrgDenEMEB[2];
  TH2D *hDTrgNumEMBE[2];TH2D *hDTrgDenEMBE[2];
  TH2D *hDTrgNumEMEE[2];TH2D *hDTrgDenEMEE[2];
  for(int i=0; i<2; i++){
    hDTrgNumMMBB[i] = new TH2D(Form("hDTrgNumMMBB_%d",i), Form("hDTrgNumMMBB_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgNumMMEB[i] = new TH2D(Form("hDTrgNumMMEB_%d",i), Form("hDTrgNumMMEB_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgNumMMBE[i] = new TH2D(Form("hDTrgNumMMBE_%d",i), Form("hDTrgNumMMBE_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgNumMMEE[i] = new TH2D(Form("hDTrgNumMMEE_%d",i), Form("hDTrgNumMMEE_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgNumEEBB[i] = new TH2D(Form("hDTrgNumEEBB_%d",i), Form("hDTrgNumEEBB_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgNumEEEB[i] = new TH2D(Form("hDTrgNumEEEB_%d",i), Form("hDTrgNumEEEB_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgNumEEBE[i] = new TH2D(Form("hDTrgNumEEBE_%d",i), Form("hDTrgNumEEBE_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgNumEEEE[i] = new TH2D(Form("hDTrgNumEEEE_%d",i), Form("hDTrgNumEEEE_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgNumMEBB[i] = new TH2D(Form("hDTrgNumMEBB_%d",i), Form("hDTrgNumMEBB_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgNumMEEB[i] = new TH2D(Form("hDTrgNumMEEB_%d",i), Form("hDTrgNumMEEB_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgNumMEBE[i] = new TH2D(Form("hDTrgNumMEBE_%d",i), Form("hDTrgNumMEBE_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgNumMEEE[i] = new TH2D(Form("hDTrgNumMEEE_%d",i), Form("hDTrgNumMEEE_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgNumEMBB[i] = new TH2D(Form("hDTrgNumEMBB_%d",i), Form("hDTrgNumEMBB_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgNumEMEB[i] = new TH2D(Form("hDTrgNumEMEB_%d",i), Form("hDTrgNumEMEB_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgNumEMBE[i] = new TH2D(Form("hDTrgNumEMBE_%d",i), Form("hDTrgNumEMBE_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgNumEMEE[i] = new TH2D(Form("hDTrgNumEMEE_%d",i), Form("hDTrgNumEMEE_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);

    hDTrgDenMMBB[i] = new TH2D(Form("hDTrgDenMMBB_%d",i), Form("hDTrgDenMMBB_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgDenMMEB[i] = new TH2D(Form("hDTrgDenMMEB_%d",i), Form("hDTrgDenMMEB_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgDenMMBE[i] = new TH2D(Form("hDTrgDenMMBE_%d",i), Form("hDTrgDenMMBE_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgDenMMEE[i] = new TH2D(Form("hDTrgDenMMEE_%d",i), Form("hDTrgDenMMEE_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgDenEEBB[i] = new TH2D(Form("hDTrgDenEEBB_%d",i), Form("hDTrgDenEEBB_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgDenEEEB[i] = new TH2D(Form("hDTrgDenEEEB_%d",i), Form("hDTrgDenEEEB_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgDenEEBE[i] = new TH2D(Form("hDTrgDenEEBE_%d",i), Form("hDTrgDenEEBE_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgDenEEEE[i] = new TH2D(Form("hDTrgDenEEEE_%d",i), Form("hDTrgDenEEEE_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgDenMEBB[i] = new TH2D(Form("hDTrgDenMEBB_%d",i), Form("hDTrgDenMEBB_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgDenMEEB[i] = new TH2D(Form("hDTrgDenMEEB_%d",i), Form("hDTrgDenMEEB_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgDenMEBE[i] = new TH2D(Form("hDTrgDenMEBE_%d",i), Form("hDTrgDenMEBE_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgDenMEEE[i] = new TH2D(Form("hDTrgDenMEEE_%d",i), Form("hDTrgDenMEEE_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgDenEMBB[i] = new TH2D(Form("hDTrgDenEMBB_%d",i), Form("hDTrgDenEMBB_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgDenEMEB[i] = new TH2D(Form("hDTrgDenEMEB_%d",i), Form("hDTrgDenEMEB_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgDenEMBE[i] = new TH2D(Form("hDTrgDenEMBE_%d",i), Form("hDTrgDenEMBE_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
    hDTrgDenEMEE[i] = new TH2D(Form("hDTrgDenEMEE_%d",i), Form("hDTrgDenEMEE_%d",i), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
  }
  // SFs
  TH2D *hDTrgSFMMBB = new TH2D(Form("trgSFMMBB"), Form("trgSFMMBB"), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
  TH2D *hDTrgSFMMEB = new TH2D(Form("trgSFMMEB"), Form("trgSFMMEB"), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
  TH2D *hDTrgSFMMBE = new TH2D(Form("trgSFMMBE"), Form("trgSFMMBE"), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
  TH2D *hDTrgSFMMEE = new TH2D(Form("trgSFMMEE"), Form("trgSFMMEE"), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
  TH2D *hDTrgSFEEBB = new TH2D(Form("trgSFEEBB"), Form("trgSFEEBB"), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
  TH2D *hDTrgSFEEEB = new TH2D(Form("trgSFEEEB"), Form("trgSFEEEB"), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
  TH2D *hDTrgSFEEBE = new TH2D(Form("trgSFEEBE"), Form("trgSFEEBE"), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
  TH2D *hDTrgSFEEEE = new TH2D(Form("trgSFEEEE"), Form("trgSFEEEE"), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
  TH2D *hDTrgSFMEBB = new TH2D(Form("trgSFMEBB"), Form("trgSFMEBB"), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
  TH2D *hDTrgSFMEEB = new TH2D(Form("trgSFMEEB"), Form("trgSFMEEB"), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
  TH2D *hDTrgSFMEBE = new TH2D(Form("trgSFMEBE"), Form("trgSFMEBE"), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
  TH2D *hDTrgSFMEEE = new TH2D(Form("trgSFMEEE"), Form("trgSFMEEE"), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
  TH2D *hDTrgSFEMBB = new TH2D(Form("trgSFEMBB"), Form("trgSFEMBB"), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
  TH2D *hDTrgSFEMEB = new TH2D(Form("trgSFEMEB"), Form("trgSFEMEB"), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
  TH2D *hDTrgSFEMBE = new TH2D(Form("trgSFEMBE"), Form("trgSFEMBE"), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);
  TH2D *hDTrgSFEMEE = new TH2D(Form("trgSFEMEE"), Form("trgSFEMEE"), nTrgBinPt1, xTrgBinPt1, nTrgBinPt2, xTrgBinPt2);

  double xminPlot = 0.0;
  double xmaxPlot = 1.0;
  int nBinPlot = 200;
  const int allCategories = 2; // processes (data and MC)
  const int histBins = 4; // final states (mm, ee, me, em)
  const int allPlots = 12; // plots
  TH1D* histo[allCategories][histBins][allPlots];

  for(int thePlot=0; thePlot<allPlots; thePlot++){
    if     (thePlot >=  0 && thePlot <=  1) {nBinPlot =  60; xminPlot = -0.5; xmaxPlot =  59.5;}
    else if(thePlot >=  2 && thePlot <=  5) {nBinPlot =  70; xminPlot =  0.0; xmaxPlot =  70.0;}
    else if(thePlot >=  6 && thePlot <=  7) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 200.0;}
    else if(thePlot >=  8 && thePlot <= 11) {nBinPlot =  20; xminPlot = -2.5; xmaxPlot =   2.5;}
    TH1D* histos = new TH1D("histos", "histos", nBinPlot, xminPlot, xmaxPlot);
    histos->Sumw2();
    for(int i=0; i<histBins; i++) {
      for(int j=0; j<allCategories; j++) {
        histo[j][i][thePlot] = (TH1D*) histos->Clone(Form("histo_%d_%d_%d",j,i,thePlot));
      }
    }
    histos->Clear();
  }
  TH1D* histoEff[histBins][6][7];
  for(int thePlot=0; thePlot<7; thePlot++){
    nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 400.0;
    TH1D* histos = new TH1D("histos", "histos", nBinPlot, xminPlot, xmaxPlot);
    histos->Sumw2();
    for(int i=0; i<histBins; i++) {
      for(int j=0; j<6; j++) {
        histoEff[i][j][thePlot] = (TH1D*) histos->Clone(Form("histoEff_%d_%d_%d",i,j,thePlot));
      }
    }
    histos->Clear();
  }

  //*******************************************************
  // Chain Loop
  //*******************************************************
  for(UInt_t ifile=0; ifile<infileName_.size(); ifile++) {
    printf("sampleNames(%d): %s\n",ifile,infileName_[ifile].Data());
    TFile *the_input_file = TFile::Open(infileName_[ifile].Data());
    TTree *the_input_tree = (TTree*)the_input_file->FindObjectAny("events");
    
    pandaFlat thePandaFlat(the_input_tree);
    Long64_t nentries = thePandaFlat.fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = thePandaFlat.LoadTree(jentry);
      if (ientry < 0) break;
      nb = thePandaFlat.fChain->GetEntry(jentry);   nbytes += nb;
      if (jentry%1000000 == 0) printf("--- reading event %8lld (%8lld) of %8lld\n",jentry,ientry,nentries);

      if(thePandaFlat.nLooseLep != 2) continue;

      vector<float>  looseLepPt,looseLepEta,looseLepPhi,looseLepSF;
      vector<int> looseLepSelBit,looseLepPdgId,looseLepTripleCharge,looseLepMissingHits;
      for(int i=0; i<thePandaFlat.nLooseMuon; i++){
        looseLepPt.push_back(thePandaFlat.muonPt[i]);
        looseLepEta.push_back(thePandaFlat.muonEta[i]);
        looseLepPhi.push_back(thePandaFlat.muonPhi[i]);
        looseLepSelBit.push_back(thePandaFlat.muonSelBit[i]);
        looseLepPdgId.push_back(thePandaFlat.muonPdgId[i]);
        looseLepTripleCharge.push_back(1);
        looseLepMissingHits.push_back(0);
        looseLepSF.push_back(thePandaFlat.muonSfReco[i]*thePandaFlat.muonSfMedium[i]);
      }
      for(int i=0; i<thePandaFlat.nLooseElectron; i++){
        looseLepPt.push_back(thePandaFlat.electronPt[i]);
        looseLepEta.push_back(thePandaFlat.electronEta[i]);
        looseLepPhi.push_back(thePandaFlat.electronPhi[i]);
        looseLepSelBit.push_back(thePandaFlat.electronSelBit[i]);
        looseLepPdgId.push_back(thePandaFlat.electronPdgId[i]);
        looseLepTripleCharge.push_back(thePandaFlat.electronTripleCharge[i]);
        looseLepMissingHits.push_back(thePandaFlat.electronNMissingHits[i]);
        looseLepSF.push_back(thePandaFlat.electronSfReco[i]*thePandaFlat.electronSfMedium[i]);
      }

      if((int)looseLepPt.size() != thePandaFlat.nLooseLep) printf("IMPOSSIBLE\n");

      bool passLepId = false;
      if     (whichLepSel == 0) passLepId = ((looseLepSelBit[0] & kFake  ) == kFake  ) && ((looseLepSelBit[1] & kFake  ) == kFake  );
      else if(whichLepSel == 1) passLepId = ((looseLepSelBit[0] & kMedium) == kMedium) && ((looseLepSelBit[1] & kMedium) == kMedium);
      if(passLepId == false) continue;

      int lepType = -1;
      if     (abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13) lepType = 0;
      else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11) lepType = 1;
      else if(abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==11) lepType = 2;
      else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==13) lepType = 3;

      else  {printf("IMPOSSIBLE\n");}
      TLorentzVector vLoose1,vLoose2;
      double thePDGMass[2] = {mass_mu, mass_mu};
      if(abs(looseLepPdgId[0])==11) thePDGMass[0] = mass_el;
      if(abs(looseLepPdgId[1])==11) thePDGMass[1] = mass_el;
      if(looseLepPt[0] > looseLepPt[1]){
        vLoose1.SetPtEtaPhiM(looseLepPt[0],looseLepEta[0],looseLepPhi[0],thePDGMass[0]);
        vLoose2.SetPtEtaPhiM(looseLepPt[1],looseLepEta[1],looseLepPhi[1],thePDGMass[1]);
      } else {
        vLoose2.SetPtEtaPhiM(looseLepPt[0],looseLepEta[0],looseLepPhi[0],thePDGMass[0]);
        vLoose1.SetPtEtaPhiM(looseLepPt[1],looseLepEta[1],looseLepPhi[1],thePDGMass[1]);
	if     (lepType == 2) lepType = 3;
	else if(lepType == 3) lepType = 2;
      }
      TLorentzVector dilep = vLoose1+vLoose2;

      if(dilep.M() <= 12) continue;
      if(vLoose1.Pt() <= 20 || vLoose2.Pt() <= 20 || TMath::Abs(vLoose1.Eta()) >= 2.5 || TMath::Abs(vLoose2.Eta()) >= 2.5) continue;

      int neta1 = 0; if(TMath::Abs(vLoose1.Eta()) > 1.5) neta1 = 1;
      int neta2 = 0; if(TMath::Abs(vLoose2.Eta()) > 1.5) neta2 = 1;

      int theCategory = infileCat_[ifile];
      double totalWeight = 1.0;
      if(theCategory != 0){
        double sfPileUp = nPUScaleFactor(fhDPU,thePandaFlat.pu);

        totalWeight = sfPileUp * thePandaFlat.sf_l1Prefire * looseLepSF[0] * looseLepSF[1];
      }

      if     (lepType == 0 && neta1 == 0 && neta2 == 0) hDTrgDenMMBB[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
      else if(lepType == 0 && neta1 == 1 && neta2 == 0) hDTrgDenMMEB[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
      else if(lepType == 0 && neta1 == 0 && neta2 == 1) hDTrgDenMMBE[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
      else if(lepType == 0 && neta1 == 1 && neta2 == 1) hDTrgDenMMEE[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
      else if(lepType == 1 && neta1 == 0 && neta2 == 0) hDTrgDenEEBB[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
      else if(lepType == 1 && neta1 == 1 && neta2 == 0) hDTrgDenEEEB[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
      else if(lepType == 1 && neta1 == 0 && neta2 == 1) hDTrgDenEEBE[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
      else if(lepType == 1 && neta1 == 1 && neta2 == 1) hDTrgDenEEEE[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
      else if(lepType == 2 && neta1 == 0 && neta2 == 0) hDTrgDenMEBB[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
      else if(lepType == 2 && neta1 == 1 && neta2 == 0) hDTrgDenMEEB[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
      else if(lepType == 2 && neta1 == 0 && neta2 == 1) hDTrgDenMEBE[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
      else if(lepType == 2 && neta1 == 1 && neta2 == 1) hDTrgDenMEEE[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
      else if(lepType == 3 && neta1 == 0 && neta2 == 0) hDTrgDenEMBB[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
      else if(lepType == 3 && neta1 == 1 && neta2 == 0) hDTrgDenEMEB[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
      else if(lepType == 3 && neta1 == 0 && neta2 == 1) hDTrgDenEMBE[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
      else if(lepType == 3 && neta1 == 1 && neta2 == 1) hDTrgDenEMEE[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
      else {printf("Problem denominator\n"); return;}
      histo[theCategory][lepType][ 0]->Fill(1.0,totalWeight);
      histo[theCategory][lepType][ 2]->Fill(TMath::Min(vLoose1.Pt(),69.999),totalWeight);
      histo[theCategory][lepType][ 4]->Fill(TMath::Min(vLoose2.Pt(),69.999),totalWeight);
      histo[theCategory][lepType][ 5]->Fill(TMath::Min(dilep.Pt(),199.999),totalWeight);
      histo[theCategory][lepType][ 8]->Fill(vLoose1.Eta(),totalWeight);
      histo[theCategory][lepType][10]->Fill(vLoose2.Eta(),totalWeight);

      bool passLEPTrigger = (thePandaFlat.trigger & (1<<kEMuTrig)) != 0       || (thePandaFlat.trigger & (1<<kDoubleMuTrig)) != 0  ||
                            (thePandaFlat.trigger & (1<<kSingleMuTrig)) != 0  || (thePandaFlat.trigger & (1<<kDoubleEleTrig)) != 0 ||
                            (thePandaFlat.trigger & (1<<kSingleEleTrig)) != 0;

      bool passMETTrigger = (thePandaFlat.trigger & (1<<kMETTrig)) != 0;
      
      if(theCategory == 1){
        double passTrigger[6];
        passTrigger[0] = passLEPTrigger;
        passTrigger[1] = (thePandaFlat.trigger & (1<<kEMuTrig)) != 0;
        passTrigger[2] = (thePandaFlat.trigger & (1<<kDoubleMuTrig)) != 0;
        passTrigger[3] = (thePandaFlat.trigger & (1<<kSingleMuTrig)) != 0;
        passTrigger[4] = (thePandaFlat.trigger & (1<<kDoubleEleTrig)) != 0;
        passTrigger[5] = (thePandaFlat.trigger & (1<<kSingleEleTrig)) != 0;

        for(int ntrg=0; ntrg<6; ntrg++){
          histoEff[lepType][ntrg][0]->Fill(TMath::Min(dilep.Pt(),399.999),totalWeight);
          if(passTrigger[ntrg]) histoEff[lepType][ntrg][1]->Fill(TMath::Min(dilep.Pt(),399.999),totalWeight);
          if(passMETTrigger)    histoEff[lepType][ntrg][2]->Fill(TMath::Min(dilep.Pt(),399.999),totalWeight);
          if( passTrigger[ntrg] &&
             passMETTrigger)    histoEff[lepType][ntrg][3]->Fill(TMath::Min(dilep.Pt(),399.999),totalWeight);
          if(!passTrigger[ntrg] &&
              passMETTrigger)   histoEff[lepType][ntrg][4]->Fill(TMath::Min(dilep.Pt(),399.999),totalWeight);
          if( passTrigger[ntrg] &&
             !passMETTrigger)   histoEff[lepType][ntrg][5]->Fill(TMath::Min(dilep.Pt(),399.999),totalWeight);
          if(!passTrigger[ntrg] &&
             !passMETTrigger)   histoEff[lepType][ntrg][6]->Fill(TMath::Min(dilep.Pt(),399.999),totalWeight);
        }
      }

      if(passLEPTrigger){
        if     (lepType == 0 && neta1 == 0 && neta2 == 0) hDTrgNumMMBB[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
        else if(lepType == 0 && neta1 == 1 && neta2 == 0) hDTrgNumMMEB[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
        else if(lepType == 0 && neta1 == 0 && neta2 == 1) hDTrgNumMMBE[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
        else if(lepType == 0 && neta1 == 1 && neta2 == 1) hDTrgNumMMEE[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
        else if(lepType == 1 && neta1 == 0 && neta2 == 0) hDTrgNumEEBB[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
        else if(lepType == 1 && neta1 == 1 && neta2 == 0) hDTrgNumEEEB[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
        else if(lepType == 1 && neta1 == 0 && neta2 == 1) hDTrgNumEEBE[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
        else if(lepType == 1 && neta1 == 1 && neta2 == 1) hDTrgNumEEEE[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
        else if(lepType == 2 && neta1 == 0 && neta2 == 0) hDTrgNumMEBB[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
        else if(lepType == 2 && neta1 == 1 && neta2 == 0) hDTrgNumMEEB[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
        else if(lepType == 2 && neta1 == 0 && neta2 == 1) hDTrgNumMEBE[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
        else if(lepType == 2 && neta1 == 1 && neta2 == 1) hDTrgNumMEEE[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
        else if(lepType == 3 && neta1 == 0 && neta2 == 0) hDTrgNumEMBB[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
        else if(lepType == 3 && neta1 == 1 && neta2 == 0) hDTrgNumEMEB[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
        else if(lepType == 3 && neta1 == 0 && neta2 == 1) hDTrgNumEMBE[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
        else if(lepType == 3 && neta1 == 1 && neta2 == 1) hDTrgNumEMEE[theCategory]->Fill(TMath::Min(vLoose1.Pt(),69.999),TMath::Min(vLoose2.Pt(),69.999),totalWeight);
	else {printf("Problem numerator\n"); return;}
        histo[theCategory][lepType][ 1]->Fill(1.0,totalWeight);
        histo[theCategory][lepType][ 3]->Fill(TMath::Min(vLoose1.Pt(),69.999),totalWeight);
        histo[theCategory][lepType][ 5]->Fill(TMath::Min(vLoose2.Pt(),69.999),totalWeight);
        histo[theCategory][lepType][ 7]->Fill(TMath::Min(dilep.Pt(),199.999),totalWeight);
        histo[theCategory][lepType][ 9]->Fill(vLoose1.Eta(),totalWeight);
        histo[theCategory][lepType][11]->Fill(vLoose2.Eta(),totalWeight);
      }
    } // end events loop
    the_input_file->Close();
  } // end chain loop

  double eff[2], unc[2];
  for(int npt1=1; npt1<=nTrgBinPt1; npt1++){
    for(int npt2=1; npt2<=nTrgBinPt2; npt2++){
      for(int i=0; i<2; i++){ // MMBB
        eff[i] = 1; unc[i] = 0.0;
  	if(hDTrgDenMMBB[i]->GetBinContent(npt1,npt2) > 0) {
  	  eff[i] = hDTrgNumMMBB[i]->GetBinContent(npt1,npt2)/hDTrgDenMMBB[i]->GetBinContent(npt1,npt2);
  	  unc[i] = sqrt(eff[i]*(1-eff[i])/hDTrgDenMMBB[i]->GetBinContent(npt1,npt2))/5.0;
          if(eff[i] == 0 || eff[i] == 1) unc[i] = 1./sqrt(hDTrgDenMMBB[i]->GetBinContent(npt1,npt2))/5.0;
  	}
      }
      hDTrgSFMMBB->SetBinContent(npt1,npt2,eff[0]/eff[1]);
      hDTrgSFMMBB->SetBinError (npt1,npt2,eff[0]/eff[1]*sqrt(unc[0]/eff[0]*unc[0]/eff[0]+unc[1]/eff[1]*unc[1]/eff[1]));
      printf("hDTrgSFMMBB[%d][%d] = %8.5f +/- %8.5f | %8.5f +/- %8.5f = %8.5f +/- %8.5f\n",npt1,npt2,eff[0],unc[0],eff[1],unc[1],hDTrgSFMMBB->GetBinContent(npt1,npt2),hDTrgSFMMBB->GetBinError(npt1,npt2));

      for(int i=0; i<2; i++){ // MMEB
        eff[i] = 1; unc[i] = 0.0;
  	if(hDTrgDenMMEB[i]->GetBinContent(npt1,npt2) > 0) {
  	  eff[i] = hDTrgNumMMEB[i]->GetBinContent(npt1,npt2)/hDTrgDenMMEB[i]->GetBinContent(npt1,npt2);
  	  unc[i] = sqrt(eff[i]*(1-eff[i])/hDTrgDenMMEB[i]->GetBinContent(npt1,npt2))/5.0;
          if(eff[i] == 0 || eff[i] == 1) unc[i] = 1./sqrt(hDTrgDenMMEB[i]->GetBinContent(npt1,npt2))/5.0;
  	}
      }
      hDTrgSFMMEB->SetBinContent(npt1,npt2,eff[0]/eff[1]);
      hDTrgSFMMEB->SetBinError (npt1,npt2,eff[0]/eff[1]*sqrt(unc[0]/eff[0]*unc[0]/eff[0]+unc[1]/eff[1]*unc[1]/eff[1]));
      printf("hDTrgSFMMEB[%d][%d] = %8.5f +/- %8.5f | %8.5f +/- %8.5f = %8.5f +/- %8.5f\n",npt1,npt2,eff[0],unc[0],eff[1],unc[1],hDTrgSFMMEB->GetBinContent(npt1,npt2),hDTrgSFMMEB->GetBinError(npt1,npt2));

      for(int i=0; i<2; i++){ // MMBE
        eff[i] = 1; unc[i] = 0.0;
  	if(hDTrgDenMMBE[i]->GetBinContent(npt1,npt2) > 0) {
  	  eff[i] = hDTrgNumMMBE[i]->GetBinContent(npt1,npt2)/hDTrgDenMMBE[i]->GetBinContent(npt1,npt2);
  	  unc[i] = sqrt(eff[i]*(1-eff[i])/hDTrgDenMMBE[i]->GetBinContent(npt1,npt2))/5.0;
          if(eff[i] == 0 || eff[i] == 1) unc[i] = 1./sqrt(hDTrgDenMMBE[i]->GetBinContent(npt1,npt2))/5.0;
  	}
      }
      hDTrgSFMMBE->SetBinContent(npt1,npt2,eff[0]/eff[1]);
      hDTrgSFMMBE->SetBinError (npt1,npt2,eff[0]/eff[1]*sqrt(unc[0]/eff[0]*unc[0]/eff[0]+unc[1]/eff[1]*unc[1]/eff[1]));
      printf("hDTrgSFMMBE[%d][%d] = %8.5f +/- %8.5f | %8.5f +/- %8.5f = %8.5f +/- %8.5f\n",npt1,npt2,eff[0],unc[0],eff[1],unc[1],hDTrgSFMMBE->GetBinContent(npt1,npt2),hDTrgSFMMBE->GetBinError(npt1,npt2));

      for(int i=0; i<2; i++){ // MMEE
        eff[i] = 1; unc[i] = 0.0;
  	if(hDTrgDenMMEE[i]->GetBinContent(npt1,npt2) > 0) {
  	  eff[i] = hDTrgNumMMEE[i]->GetBinContent(npt1,npt2)/hDTrgDenMMEE[i]->GetBinContent(npt1,npt2);
  	  unc[i] = sqrt(eff[i]*(1-eff[i])/hDTrgDenMMEE[i]->GetBinContent(npt1,npt2))/5.0;
          if(eff[i] == 0 || eff[i] == 1) unc[i] = 1./sqrt(hDTrgDenMMEE[i]->GetBinContent(npt1,npt2))/5.0;
  	}
      }
      hDTrgSFMMEE->SetBinContent(npt1,npt2,eff[0]/eff[1]);
      hDTrgSFMMEE->SetBinError (npt1,npt2,eff[0]/eff[1]*sqrt(unc[0]/eff[0]*unc[0]/eff[0]+unc[1]/eff[1]*unc[1]/eff[1]));
      printf("hDTrgSFMMEE[%d][%d] = %8.5f +/- %8.5f | %8.5f +/- %8.5f = %8.5f +/- %8.5f\n",npt1,npt2,eff[0],unc[0],eff[1],unc[1],hDTrgSFMMEE->GetBinContent(npt1,npt2),hDTrgSFMMEE->GetBinError(npt1,npt2));

      for(int i=0; i<2; i++){ // EEBB
        eff[i] = 1; unc[i] = 0.0;
  	if(hDTrgDenEEBB[i]->GetBinContent(npt1,npt2) > 0) {
  	  eff[i] = hDTrgNumEEBB[i]->GetBinContent(npt1,npt2)/hDTrgDenEEBB[i]->GetBinContent(npt1,npt2);
  	  unc[i] = sqrt(eff[i]*(1-eff[i])/hDTrgDenEEBB[i]->GetBinContent(npt1,npt2))/5.0;
          if(eff[i] == 0 || eff[i] == 1) unc[i] = 1./sqrt(hDTrgDenEEBB[i]->GetBinContent(npt1,npt2))/5.0;
  	}
      }
      hDTrgSFEEBB->SetBinContent(npt1,npt2,eff[0]/eff[1]);
      hDTrgSFEEBB->SetBinError (npt1,npt2,eff[0]/eff[1]*sqrt(unc[0]/eff[0]*unc[0]/eff[0]+unc[1]/eff[1]*unc[1]/eff[1]));
      printf("hDTrgSFEEBB[%d][%d] = %8.5f +/- %8.5f | %8.5f +/- %8.5f = %8.5f +/- %8.5f\n",npt1,npt2,eff[0],unc[0],eff[1],unc[1],hDTrgSFEEBB->GetBinContent(npt1,npt2),hDTrgSFEEBB->GetBinError(npt1,npt2));

      for(int i=0; i<2; i++){ // EEEB
        eff[i] = 1; unc[i] = 0.0;
  	if(hDTrgDenEEEB[i]->GetBinContent(npt1,npt2) > 0) {
  	  eff[i] = hDTrgNumEEEB[i]->GetBinContent(npt1,npt2)/hDTrgDenEEEB[i]->GetBinContent(npt1,npt2);
  	  unc[i] = sqrt(eff[i]*(1-eff[i])/hDTrgDenEEEB[i]->GetBinContent(npt1,npt2))/5.0;
          if(eff[i] == 0 || eff[i] == 1) unc[i] = 1./sqrt(hDTrgDenEEEB[i]->GetBinContent(npt1,npt2))/5.0;
  	}
      }
      hDTrgSFEEEB->SetBinContent(npt1,npt2,eff[0]/eff[1]);
      hDTrgSFEEEB->SetBinError (npt1,npt2,eff[0]/eff[1]*sqrt(unc[0]/eff[0]*unc[0]/eff[0]+unc[1]/eff[1]*unc[1]/eff[1]));
      printf("hDTrgSFEEEB[%d][%d] = %8.5f +/- %8.5f | %8.5f +/- %8.5f = %8.5f +/- %8.5f\n",npt1,npt2,eff[0],unc[0],eff[1],unc[1],hDTrgSFEEEB->GetBinContent(npt1,npt2),hDTrgSFEEEB->GetBinError(npt1,npt2));

      for(int i=0; i<2; i++){ // EEBE
        eff[i] = 1; unc[i] = 0.0;
  	if(hDTrgDenEEBE[i]->GetBinContent(npt1,npt2) > 0) {
  	  eff[i] = hDTrgNumEEBE[i]->GetBinContent(npt1,npt2)/hDTrgDenEEBE[i]->GetBinContent(npt1,npt2);
  	  unc[i] = sqrt(eff[i]*(1-eff[i])/hDTrgDenEEBE[i]->GetBinContent(npt1,npt2))/5.0;
          if(eff[i] == 0 || eff[i] == 1) unc[i] = 1./sqrt(hDTrgDenEEBE[i]->GetBinContent(npt1,npt2))/5.0;
  	}
      }
      hDTrgSFEEBE->SetBinContent(npt1,npt2,eff[0]/eff[1]);
      hDTrgSFEEBE->SetBinError (npt1,npt2,eff[0]/eff[1]*sqrt(unc[0]/eff[0]*unc[0]/eff[0]+unc[1]/eff[1]*unc[1]/eff[1]));
      printf("hDTrgSFEEBE[%d][%d] = %8.5f +/- %8.5f | %8.5f +/- %8.5f = %8.5f +/- %8.5f\n",npt1,npt2,eff[0],unc[0],eff[1],unc[1],hDTrgSFEEBE->GetBinContent(npt1,npt2),hDTrgSFEEBE->GetBinError(npt1,npt2));

      for(int i=0; i<2; i++){ // EEEE
        eff[i] = 1; unc[i] = 0.0;
  	if(hDTrgDenEEEE[i]->GetBinContent(npt1,npt2) > 0) {
  	  eff[i] = hDTrgNumEEEE[i]->GetBinContent(npt1,npt2)/hDTrgDenEEEE[i]->GetBinContent(npt1,npt2);
  	  unc[i] = sqrt(eff[i]*(1-eff[i])/hDTrgDenEEEE[i]->GetBinContent(npt1,npt2))/5.0;
          if(eff[i] == 0 || eff[i] == 1) unc[i] = 1./sqrt(hDTrgDenEEEE[i]->GetBinContent(npt1,npt2))/5.0;
  	}
      }
      hDTrgSFEEEE->SetBinContent(npt1,npt2,eff[0]/eff[1]);
      hDTrgSFEEEE->SetBinError (npt1,npt2,eff[0]/eff[1]*sqrt(unc[0]/eff[0]*unc[0]/eff[0]+unc[1]/eff[1]*unc[1]/eff[1]));
      printf("hDTrgSFEEEE[%d][%d] = %8.5f +/- %8.5f | %8.5f +/- %8.5f = %8.5f +/- %8.5f\n",npt1,npt2,eff[0],unc[0],eff[1],unc[1],hDTrgSFEEEE->GetBinContent(npt1,npt2),hDTrgSFEEEE->GetBinError(npt1,npt2));

      for(int i=0; i<2; i++){ // MEBB
        eff[i] = 1; unc[i] = 0.0;
  	if(hDTrgDenMEBB[i]->GetBinContent(npt1,npt2) > 0) {
  	  eff[i] = hDTrgNumMEBB[i]->GetBinContent(npt1,npt2)/hDTrgDenMEBB[i]->GetBinContent(npt1,npt2);
  	  unc[i] = sqrt(eff[i]*(1-eff[i])/hDTrgDenMEBB[i]->GetBinContent(npt1,npt2))/5.0;
          if(eff[i] == 0 || eff[i] == 1) unc[i] = 1./sqrt(hDTrgDenMEBB[i]->GetBinContent(npt1,npt2))/5.0;
  	}
      }
      hDTrgSFMEBB->SetBinContent(npt1,npt2,eff[0]/eff[1]);
      hDTrgSFMEBB->SetBinError (npt1,npt2,eff[0]/eff[1]*sqrt(unc[0]/eff[0]*unc[0]/eff[0]+unc[1]/eff[1]*unc[1]/eff[1]));
      printf("hDTrgSFMEBB[%d][%d] = %8.5f +/- %8.5f | %8.5f +/- %8.5f = %8.5f +/- %8.5f\n",npt1,npt2,eff[0],unc[0],eff[1],unc[1],hDTrgSFMEBB->GetBinContent(npt1,npt2),hDTrgSFMEBB->GetBinError(npt1,npt2));

      for(int i=0; i<2; i++){ // MEEB
        eff[i] = 1; unc[i] = 0.0;
  	if(hDTrgDenMEEB[i]->GetBinContent(npt1,npt2) > 0) {
  	  eff[i] = hDTrgNumMEEB[i]->GetBinContent(npt1,npt2)/hDTrgDenMEEB[i]->GetBinContent(npt1,npt2);
  	  unc[i] = sqrt(eff[i]*(1-eff[i])/hDTrgDenMEEB[i]->GetBinContent(npt1,npt2))/5.0;
          if(eff[i] == 0 || eff[i] == 1) unc[i] = 1./sqrt(hDTrgDenMEEB[i]->GetBinContent(npt1,npt2))/5.0;
  	}
      }
      hDTrgSFMEEB->SetBinContent(npt1,npt2,eff[0]/eff[1]);
      hDTrgSFMEEB->SetBinError (npt1,npt2,eff[0]/eff[1]*sqrt(unc[0]/eff[0]*unc[0]/eff[0]+unc[1]/eff[1]*unc[1]/eff[1]));
      printf("hDTrgSFMEEB[%d][%d] = %8.5f +/- %8.5f | %8.5f +/- %8.5f = %8.5f +/- %8.5f\n",npt1,npt2,eff[0],unc[0],eff[1],unc[1],hDTrgSFMEEB->GetBinContent(npt1,npt2),hDTrgSFMEEB->GetBinError(npt1,npt2));

      for(int i=0; i<2; i++){ // MEBE
        eff[i] = 1; unc[i] = 0.0;
  	if(hDTrgDenMEBE[i]->GetBinContent(npt1,npt2) > 0) {
  	  eff[i] = hDTrgNumMEBE[i]->GetBinContent(npt1,npt2)/hDTrgDenMEBE[i]->GetBinContent(npt1,npt2);
  	  unc[i] = sqrt(eff[i]*(1-eff[i])/hDTrgDenMEBE[i]->GetBinContent(npt1,npt2))/5.0;
          if(eff[i] == 0 || eff[i] == 1) unc[i] = 1./sqrt(hDTrgDenMEBE[i]->GetBinContent(npt1,npt2))/5.0;
  	}
      }
      hDTrgSFMEBE->SetBinContent(npt1,npt2,eff[0]/eff[1]);
      hDTrgSFMEBE->SetBinError (npt1,npt2,eff[0]/eff[1]*sqrt(unc[0]/eff[0]*unc[0]/eff[0]+unc[1]/eff[1]*unc[1]/eff[1]));
      printf("hDTrgSFMEBE[%d][%d] = %8.5f +/- %8.5f | %8.5f +/- %8.5f = %8.5f +/- %8.5f\n",npt1,npt2,eff[0],unc[0],eff[1],unc[1],hDTrgSFMEBE->GetBinContent(npt1,npt2),hDTrgSFMEBE->GetBinError(npt1,npt2));

      for(int i=0; i<2; i++){ // MEEE
        eff[i] = 1; unc[i] = 0.0;
  	if(hDTrgDenMEEE[i]->GetBinContent(npt1,npt2) > 0) {
  	  eff[i] = hDTrgNumMEEE[i]->GetBinContent(npt1,npt2)/hDTrgDenMEEE[i]->GetBinContent(npt1,npt2);
  	  unc[i] = sqrt(eff[i]*(1-eff[i])/hDTrgDenMEEE[i]->GetBinContent(npt1,npt2))/5.0;
          if(eff[i] == 0 || eff[i] == 1) unc[i] = 1./sqrt(hDTrgDenMEEE[i]->GetBinContent(npt1,npt2))/5.0;
  	}
      }
      hDTrgSFMEEE->SetBinContent(npt1,npt2,eff[0]/eff[1]);
      hDTrgSFMEEE->SetBinError (npt1,npt2,eff[0]/eff[1]*sqrt(unc[0]/eff[0]*unc[0]/eff[0]+unc[1]/eff[1]*unc[1]/eff[1]));
      printf("hDTrgSFMEEE[%d][%d] = %8.5f +/- %8.5f | %8.5f +/- %8.5f = %8.5f +/- %8.5f\n",npt1,npt2,eff[0],unc[0],eff[1],unc[1],hDTrgSFMEEE->GetBinContent(npt1,npt2),hDTrgSFMEEE->GetBinError(npt1,npt2));

      for(int i=0; i<2; i++){ // EMBB
        eff[i] = 1; unc[i] = 0.0;
  	if(hDTrgDenEMBB[i]->GetBinContent(npt1,npt2) > 0) {
  	  eff[i] = hDTrgNumEMBB[i]->GetBinContent(npt1,npt2)/hDTrgDenEMBB[i]->GetBinContent(npt1,npt2);
  	  unc[i] = sqrt(eff[i]*(1-eff[i])/hDTrgDenEMBB[i]->GetBinContent(npt1,npt2))/5.0;
          if(eff[i] == 0 || eff[i] == 1) unc[i] = 1./sqrt(hDTrgDenEMBB[i]->GetBinContent(npt1,npt2))/5.0;
  	}
      }
      hDTrgSFEMBB->SetBinContent(npt1,npt2,eff[0]/eff[1]);
      hDTrgSFEMBB->SetBinError (npt1,npt2,eff[0]/eff[1]*sqrt(unc[0]/eff[0]*unc[0]/eff[0]+unc[1]/eff[1]*unc[1]/eff[1]));
      printf("hDTrgSFEMBB[%d][%d] = %8.5f +/- %8.5f | %8.5f +/- %8.5f = %8.5f +/- %8.5f\n",npt1,npt2,eff[0],unc[0],eff[1],unc[1],hDTrgSFEMBB->GetBinContent(npt1,npt2),hDTrgSFEMBB->GetBinError(npt1,npt2));

      for(int i=0; i<2; i++){ // EMEB
        eff[i] = 1; unc[i] = 0.0;
  	if(hDTrgDenEMEB[i]->GetBinContent(npt1,npt2) > 0) {
  	  eff[i] = hDTrgNumEMEB[i]->GetBinContent(npt1,npt2)/hDTrgDenEMEB[i]->GetBinContent(npt1,npt2);
  	  unc[i] = sqrt(eff[i]*(1-eff[i])/hDTrgDenEMEB[i]->GetBinContent(npt1,npt2))/5.0;
          if(eff[i] == 0 || eff[i] == 1) unc[i] = 1./sqrt(hDTrgDenEMEB[i]->GetBinContent(npt1,npt2))/5.0;
  	}
      }
      hDTrgSFEMEB->SetBinContent(npt1,npt2,eff[0]/eff[1]);
      hDTrgSFEMEB->SetBinError (npt1,npt2,eff[0]/eff[1]*sqrt(unc[0]/eff[0]*unc[0]/eff[0]+unc[1]/eff[1]*unc[1]/eff[1]));
      printf("hDTrgSFEMEB[%d][%d] = %8.5f +/- %8.5f | %8.5f +/- %8.5f = %8.5f +/- %8.5f\n",npt1,npt2,eff[0],unc[0],eff[1],unc[1],hDTrgSFEMEB->GetBinContent(npt1,npt2),hDTrgSFEMEB->GetBinError(npt1,npt2));

      for(int i=0; i<2; i++){ // EMBE
        eff[i] = 1; unc[i] = 0.0;
  	if(hDTrgDenEMBE[i]->GetBinContent(npt1,npt2) > 0) {
  	  eff[i] = hDTrgNumEMBE[i]->GetBinContent(npt1,npt2)/hDTrgDenEMBE[i]->GetBinContent(npt1,npt2);
  	  unc[i] = sqrt(eff[i]*(1-eff[i])/hDTrgDenEMBE[i]->GetBinContent(npt1,npt2))/5.0;
          if(eff[i] == 0 || eff[i] == 1) unc[i] = 1./sqrt(hDTrgDenEMBE[i]->GetBinContent(npt1,npt2))/5.0;
  	}
      }
      hDTrgSFEMBE->SetBinContent(npt1,npt2,eff[0]/eff[1]);
      hDTrgSFEMBE->SetBinError (npt1,npt2,eff[0]/eff[1]*sqrt(unc[0]/eff[0]*unc[0]/eff[0]+unc[1]/eff[1]*unc[1]/eff[1]));
      printf("hDTrgSFEMBE[%d][%d] = %8.5f +/- %8.5f | %8.5f +/- %8.5f = %8.5f +/- %8.5f\n",npt1,npt2,eff[0],unc[0],eff[1],unc[1],hDTrgSFEMBE->GetBinContent(npt1,npt2),hDTrgSFEMBE->GetBinError(npt1,npt2));

      for(int i=0; i<2; i++){ // EMEE
        eff[i] = 1; unc[i] = 0.0;
  	if(hDTrgDenEMEE[i]->GetBinContent(npt1,npt2) > 0) {
  	  eff[i] = hDTrgNumEMEE[i]->GetBinContent(npt1,npt2)/hDTrgDenEMEE[i]->GetBinContent(npt1,npt2);
  	  unc[i] = sqrt(eff[i]*(1-eff[i])/hDTrgDenEMEE[i]->GetBinContent(npt1,npt2))/5.0;
          if(eff[i] == 0 || eff[i] == 1) unc[i] = 1./sqrt(hDTrgDenEMEE[i]->GetBinContent(npt1,npt2))/5.0;
  	}
      }
      hDTrgSFEMEE->SetBinContent(npt1,npt2,eff[0]/eff[1]);
      hDTrgSFEMEE->SetBinError (npt1,npt2,eff[0]/eff[1]*sqrt(unc[0]/eff[0]*unc[0]/eff[0]+unc[1]/eff[1]*unc[1]/eff[1]));
      printf("hDTrgSFEMEE[%d][%d] = %8.5f +/- %8.5f | %8.5f +/- %8.5f = %8.5f +/- %8.5f\n",npt1,npt2,eff[0],unc[0],eff[1],unc[1],hDTrgSFEMEE->GetBinContent(npt1,npt2),hDTrgSFEMEE->GetBinError(npt1,npt2));

    }
  }
  
  char output[200];
  sprintf(output,"histo_trigger_sel%d_%d.root",whichLepSel,year);	
  TFile* outFilePlotsHistos = new TFile(output,"recreate");
  outFilePlotsHistos->cd();
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    for(int i=0; i<histBins; i++) {
      for(int j=0; j<allCategories; j++) {
        histo[j][i][thePlot]->Write();
      }
    }
  }
  outFilePlotsHistos->Close();

  sprintf(output,"histo_triggerEffBias_sel%d_%d.root",whichLepSel,year);	
  TFile* outFileEffBiasHistos = new TFile(output,"recreate");
  outFileEffBiasHistos->cd();
  for(int ntrg=0; ntrg<6; ntrg++){
    for(int nt=0; nt<4; nt++){
      double total = histoEff[nt][ntrg][0]->GetSumOfWeights();
      if(total <= 0) continue;
      printf("eff(LL)eff(MET)/eff(LL+MET) (%d,%d) = %.3f X %.3f / %.3f = %.3f | %.3f X %.3f / %.3f = %.3f\n",ntrg,nt,
      histoEff[nt][ntrg][1]->GetSumOfWeights()/total,histoEff[nt][ntrg][2]->GetSumOfWeights()/total,histoEff[nt][ntrg][3]->GetSumOfWeights()/total,
      histoEff[nt][ntrg][1]->GetSumOfWeights()*histoEff[nt][ntrg][2]->GetSumOfWeights()/histoEff[nt][ntrg][3]->GetSumOfWeights()/total,
      histoEff[nt][ntrg][4]->GetSumOfWeights()/total,histoEff[nt][ntrg][5]->GetSumOfWeights()/total,histoEff[nt][ntrg][6]->GetSumOfWeights()/total,
      histoEff[nt][ntrg][4]->GetSumOfWeights()*histoEff[nt][ntrg][5]->GetSumOfWeights()/histoEff[nt][ntrg][6]->GetSumOfWeights()/total);
      histoEff[nt][ntrg][1]->Divide(histoEff[nt][ntrg][0]);
      histoEff[nt][ntrg][2]->Divide(histoEff[nt][ntrg][0]);
      histoEff[nt][ntrg][3]->Divide(histoEff[nt][ntrg][0]);
      histoEff[nt][ntrg][4]->Divide(histoEff[nt][ntrg][0]);
      histoEff[nt][ntrg][5]->Divide(histoEff[nt][ntrg][0]);
      histoEff[nt][ntrg][6]->Divide(histoEff[nt][ntrg][0]);
      histoEff[nt][ntrg][0]->Reset();
      histoEff[nt][ntrg][0]->Add(histoEff[nt][ntrg][1]);
      histoEff[nt][ntrg][0]->Multiply(histoEff[nt][ntrg][2]);
      histoEff[nt][ntrg][0]->Divide(histoEff[nt][ntrg][3]);
      for(int i=0; i<7; i++) histoEff[nt][ntrg][i]->Write();
    }
  }
  outFileEffBiasHistos->Close();

  for(int thePlot=0; thePlot<6; thePlot++){
    for(int theCat=0; theCat<allCategories; theCat++){
      for(int theType=0; theType<histBins; theType++){
        for(int i=1; i<=histo[theCat][theType][2*thePlot+1]->GetNbinsX(); i++){
	  eff[0] = 1; unc[0] = 0;
	  if(histo[theCat][theType][2*thePlot]->GetBinContent(i) > 0){
            eff[0] = histo[theCat][theType][2*thePlot+1]->GetBinContent(i)/histo[theCat][theType][2*thePlot]->GetBinContent(i);
            unc[0] =sqrt(eff[0]*(1-eff[0])/histo[theCat][theType][2*thePlot]->GetBinContent(i));
	  }
	  histo[theCat][theType][2*thePlot+1]->SetBinContent(i,eff[0]);
	  histo[theCat][theType][2*thePlot+1]->SetBinError(i,unc[0]);
        }
      }
    }
  }

  sprintf(output,"histo_triggerEffPlots_sel%d_%d.root",whichLepSel,year);	
  TFile* outFileEffPlots = new TFile(output,"recreate");
  outFileEffPlots->cd();
  for(int theCat=0; theCat<allCategories; theCat++){
    for(int theType=0; theType<histBins; theType++){
      histo[theCat][theType][ 1]->Write();
      histo[theCat][theType][ 3]->Write();
      histo[theCat][theType][ 5]->Write();
      histo[theCat][theType][ 7]->Write();
      histo[theCat][theType][ 9]->Write();
      histo[theCat][theType][11]->Write();
    }
  }
  outFileEffPlots->Close();

  sprintf(output,"histo_triggerEff_sel%d_%d.root",whichLepSel,year);	
  TFile* outFileEff = new TFile(output,"recreate");
  outFileEff->cd();
  hDTrgSFMMBB->GetXaxis()->SetTitle("p_{T}^{leading} [GeV]");hDTrgSFMMBB->GetYaxis()->SetTitle("p_{T}^{trailing} [GeV]");hDTrgSFMMBB->Write();
  hDTrgSFMMEB->GetXaxis()->SetTitle("p_{T}^{leading} [GeV]");hDTrgSFMMEB->GetYaxis()->SetTitle("p_{T}^{trailing} [GeV]");hDTrgSFMMEB->Write();
  hDTrgSFMMBE->GetXaxis()->SetTitle("p_{T}^{leading} [GeV]");hDTrgSFMMBE->GetYaxis()->SetTitle("p_{T}^{trailing} [GeV]");hDTrgSFMMBE->Write();
  hDTrgSFMMEE->GetXaxis()->SetTitle("p_{T}^{leading} [GeV]");hDTrgSFMMEE->GetYaxis()->SetTitle("p_{T}^{trailing} [GeV]");hDTrgSFMMEE->Write();
  hDTrgSFEEBB->GetXaxis()->SetTitle("p_{T}^{leading} [GeV]");hDTrgSFEEBB->GetYaxis()->SetTitle("p_{T}^{trailing} [GeV]");hDTrgSFEEBB->Write();
  hDTrgSFEEEB->GetXaxis()->SetTitle("p_{T}^{leading} [GeV]");hDTrgSFEEEB->GetYaxis()->SetTitle("p_{T}^{trailing} [GeV]");hDTrgSFEEEB->Write();
  hDTrgSFEEBE->GetXaxis()->SetTitle("p_{T}^{leading} [GeV]");hDTrgSFEEBE->GetYaxis()->SetTitle("p_{T}^{trailing} [GeV]");hDTrgSFEEBE->Write();
  hDTrgSFEEEE->GetXaxis()->SetTitle("p_{T}^{leading} [GeV]");hDTrgSFEEEE->GetYaxis()->SetTitle("p_{T}^{trailing} [GeV]");hDTrgSFEEEE->Write();
  hDTrgSFMEBB->GetXaxis()->SetTitle("p_{T}^{leading} [GeV]");hDTrgSFMEBB->GetYaxis()->SetTitle("p_{T}^{trailing} [GeV]");hDTrgSFMEBB->Write();
  hDTrgSFMEEB->GetXaxis()->SetTitle("p_{T}^{leading} [GeV]");hDTrgSFMEEB->GetYaxis()->SetTitle("p_{T}^{trailing} [GeV]");hDTrgSFMEEB->Write();
  hDTrgSFMEBE->GetXaxis()->SetTitle("p_{T}^{leading} [GeV]");hDTrgSFMEBE->GetYaxis()->SetTitle("p_{T}^{trailing} [GeV]");hDTrgSFMEBE->Write();
  hDTrgSFMEEE->GetXaxis()->SetTitle("p_{T}^{leading} [GeV]");hDTrgSFMEEE->GetYaxis()->SetTitle("p_{T}^{trailing} [GeV]");hDTrgSFMEEE->Write();
  hDTrgSFEMBB->GetXaxis()->SetTitle("p_{T}^{leading} [GeV]");hDTrgSFEMBB->GetYaxis()->SetTitle("p_{T}^{trailing} [GeV]");hDTrgSFEMBB->Write();
  hDTrgSFEMEB->GetXaxis()->SetTitle("p_{T}^{leading} [GeV]");hDTrgSFEMEB->GetYaxis()->SetTitle("p_{T}^{trailing} [GeV]");hDTrgSFEMEB->Write();
  hDTrgSFEMBE->GetXaxis()->SetTitle("p_{T}^{leading} [GeV]");hDTrgSFEMBE->GetYaxis()->SetTitle("p_{T}^{trailing} [GeV]");hDTrgSFEMBE->Write();
  hDTrgSFEMEE->GetXaxis()->SetTitle("p_{T}^{leading} [GeV]");hDTrgSFEMEE->GetYaxis()->SetTitle("p_{T}^{trailing} [GeV]");hDTrgSFEMEE->Write();
  outFileEff->Close();
}
