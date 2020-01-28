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

const double mcPrescale = 1;
const bool usePureMC = false;
const bool showSyst = true;

enum systType                     {JESUP=0, JESDOWN, nSystTypes};
TString systTypeName[nSystTypes]= {"JESUP","JESDOWN"};
double ww_norm_unc_ptwei[4] = {0.996073,1.000986,1.011810,0.953619};

void wwAnalysis(
int year
){
  int nTypeLepSel[2] = {-1, -1};
  int whichYear = -1;
  if     (year == 2016) {whichYear = Y2016; nTypeLepSel[0] =  2; nTypeLepSel[1] = 6;}
  else if(year == 2017) {whichYear = Y2017; nTypeLepSel[0] = 13; nTypeLepSel[1] = 6;}
  else if(year == 2018) {whichYear = Y2018; nTypeLepSel[0] = 15; nTypeLepSel[1] = 6;}
  else {printf("Wrong year (%d)!\n",year); return;}

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
  TString trgSFPath = Form("MitAnalysisRunII/data/90x/trigger/histo_triggerEff_sel0_%d.root",year);
  TString effSFPath = Form("MitAnalysisRunII/data/90x/eff/histoDY0EffSFStudy_%d.root",year);
  TString puPath;
  //TString npvPath = Form("MitAnalysisRunII/data/90x/pu/npvWeights_%d.root",year);
  if(year == 2018) {
    filesPath = "/data/t3home000/ceballos/panda/v_006_0/";
    puPath = "MitAnalysisRunII/data/90x/pu/puWeights_90x_2018.root";

    infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	         infileCat_.push_back(kPlotData);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotqqWW);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotggWW);
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));                infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		         infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_M-50_LO.root",filesPath.Data()));   infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sWZno3l.root" ,filesPath.Data()));	         infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sWZ3l_powheg.root" ,filesPath.Data()));         infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTVV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));		         infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotHiggs);
  }
  else if(year == 2017) {
    filesPath = "/data/t3home000/ceballos/panda/v_004_0/";
    puPath = "MitAnalysisRunII/data/90x/pu/puWeights_90x_2017.root";

    infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	         infileCat_.push_back(kPlotData);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotqqWW);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotggWW);
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));                infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		         infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_M-50_LO.root",filesPath.Data()));   infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sWZno3l.root" ,filesPath.Data()));	         infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sWZ3l_powheg_mll1.root" ,filesPath.Data()));    infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTVV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));		         infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotHiggs);
  }
  else if(year == 2016) {
    filesPath = "/data/t3home000/ceballos/panda/v_002_0/";
    puPath = "MitAnalysisRunII/data/90x/pu/puWeights_90x_2016.root";

    infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	          infileCat_.push_back(kPlotData);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotqqWW);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotggWW);
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));                 infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		          infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data()));  infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt0To50.root",filesPath.Data()));    infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt50To100.root",filesPath.Data()));  infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt100To250.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt250To400.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt400To650.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt650ToInf.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sWZ.root" ,filesPath.Data()));	                  infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sWGstar.root" ,filesPath.Data()));               infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));		          infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotHiggs);
  }
  else {
    return;
  }

  //infileName_.clear();infileCat_.clear();
  //infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotqqWW);

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

  TFile *fWWEWKCorrFile = TFile::Open(Form("MitAnalysisRunII/data/80x/WWEWKCorr/WW_EWK_Corr.root"));
  TH1D *fhDWWEWKCorr = (TH1D*)(fWWEWKCorrFile->Get("ratio_Ptlm")); assert(fhDWWEWKCorr); fhDWWEWKCorr->SetDirectory(0);
  //TH1D *fhDWWEWKCorr = (TH1D*)(fWWEWKCorrFile->Get("ratio_Mll")); assert(fhDWWEWKCorr); fhDWWEWKCorr->SetDirectory(0);
  delete fWWEWKCorrFile;

  TFile *fWWPtRatio = TFile::Open(Form("MitAnalysisRunII/data/74x/MyRatioWWpTHistogramAll.root"));
  TH1D *fhDWWPtRatio           = (TH1D*)(fWWPtRatio->Get("wwpt"));
  TH1D *fhDWWPtRatio_scaleup   = (TH1D*)(fWWPtRatio->Get("wwpt_scaleup"));
  TH1D *fhDWWPtRatio_scaledown = (TH1D*)(fWWPtRatio->Get("wwpt_scaledown"));
  TH1D *fhDWWPtRatio_resumup   = (TH1D*)(fWWPtRatio->Get("wwpt_resumup"));
  TH1D *fhDWWPtRatio_resumdown = (TH1D*)(fWWPtRatio->Get("wwpt_resumdown"));
  assert(fhDWWPtRatio	       );
  assert(fhDWWPtRatio_scaleup  );
  assert(fhDWWPtRatio_scaledown);
  assert(fhDWWPtRatio_resumup  );
  assert(fhDWWPtRatio_resumdown);
  fhDWWPtRatio  	->SetDirectory(0);
  fhDWWPtRatio_scaleup  ->SetDirectory(0);
  fhDWWPtRatio_scaledown->SetDirectory(0);
  fhDWWPtRatio_resumup  ->SetDirectory(0);
  fhDWWPtRatio_resumdown->SetDirectory(0);
  delete fWWPtRatio;

  const int nBinMVA = 12; Float_t xbins[nBinMVA+1] = {0, 1000, 2000, 3000, 4000,
                                                         5000, 6000, 7000, 8000,
							 9000,10000,11000,12000,};

  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 169;
  TH1D* histo[allPlots][nPlotCategories];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    if     (thePlot >=   0 && thePlot <=  44) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >=  45 && thePlot <=  53) {nBinPlot =   5; xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >=  54 && thePlot <=  80) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >=  81 && thePlot <=  89) {nBinPlot =  90; xminPlot =  0.0; xmaxPlot = 180;}
    else if(thePlot >=  90 && thePlot <= 116) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >= 117 && thePlot <= 125) {nBinPlot =  90; xminPlot =  0.0; xmaxPlot = 180;}
    else if(thePlot >= 126 && thePlot <= 152) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >= 153 && thePlot <= 161) {nBinPlot =  90; xminPlot =  0.0; xmaxPlot = 180;}
    else if(thePlot >= 162 && thePlot <= 167) {nBinPlot = 300; xminPlot =  0.0; xmaxPlot = 300;}
    if     (thePlot == allPlots-1) for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinMVA, xbins);
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
  TH1D *histo_TopNormJetUp[3];
  TH1D *histo_TopNormJetDown[3];
  TH1D *histo_DYNormJetUp[3];
  TH1D *histo_DYNormJetDown[3];
  TH1D *histo_NonPromptNormJetUp[3];
  TH1D *histo_NonPromptNormJetDown[3];

  TH1D* histo_qqWW_CMS_MVAWW_nlo       = new TH1D( Form("histo_qqWW_CMS_MVAWW_nlo"),     Form("histo_qqWW_CMS_MVAWW_nlo"),     nBinMVA, xbins); histo_qqWW_CMS_MVAWW_nlo->Sumw2();
  TH1D* histo_qqWW_CMS_MVAWW_qup_nlo   = new TH1D( Form("histo_qqWW_WWNNLO_scaleUp"),    Form("histo_qqWW_WWNNLO_scaleUp"),    nBinMVA, xbins); histo_qqWW_CMS_MVAWW_qup_nlo->Sumw2();
  TH1D* histo_qqWW_CMS_MVAWW_qdown_nlo = new TH1D( Form("histo_qqWW_WWNNLO_scaleDown"),  Form("histo_qqWW_WWNNLO_scaleDown"),  nBinMVA, xbins); histo_qqWW_CMS_MVAWW_qdown_nlo->Sumw2();
  TH1D* histo_qqWW_CMS_MVAWW_sup_nlo   = new TH1D( Form("histo_qqWW_WWNNLO_resumUp"),    Form("histo_qqWW_WWNNLO_resumUp"),    nBinMVA, xbins); histo_qqWW_CMS_MVAWW_sup_nlo->Sumw2();
  TH1D* histo_qqWW_CMS_MVAWW_sdown_nlo = new TH1D( Form("histo_qqWW_WWNNLO_resumDown"),  Form("histo_qqWW_WWNNLO_resumDown"),  nBinMVA, xbins); histo_qqWW_CMS_MVAWW_sdown_nlo->Sumw2();

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
  }
  for(int nj=0; nj<3; nj++){
    histo_TopNormJetUp[nj]         = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_TopNormJet%dcat_%dUp"   , plotBaseNames[kPlotTop].Data(),nj,year));
    histo_TopNormJetDown[nj]       = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_TopNormJet%dcat_%dDown" , plotBaseNames[kPlotTop].Data(),nj,year));
    histo_DYNormJetUp[nj]          = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_DYNormJet%dcat_%dUp"    , plotBaseNames[kPlotDY].Data(),nj,year));
    histo_DYNormJetDown[nj]        = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_DYNormJet%dcat_%dDown"  , plotBaseNames[kPlotDY].Data(),nj,year));
    histo_NonPromptNormJetUp[nj]   = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_NonPromptNormJet%dcat_%dUp"  , plotBaseNames[kPlotNonPrompt].Data(),nj,year));
    histo_NonPromptNormJetDown[nj] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_NonPromptNormJet%dcat_%dDown", plotBaseNames[kPlotNonPrompt].Data(),nj,year));
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
      if (infileCat_[ifile] != kPlotData && jentry%(int)theMCPrescale != 0) continue;

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
        //if((looseLepSelBit[i] & kTight) == kTight && (looseLepSelBit[i] & kDxyz) == kDxyz && looseLepMissingHits[i] == 0) idLep[i] = 1;
        if(abs(looseLepPdgId[i])==13) {
	  if     (year == 2016 && (looseLepSelBit[i] & kTight) == kTight && (looseLepSelBit[i] & kDxyz) == kDxyz) idLep[i] = 1;
	  else if(year == 2017 && (looseLepSelBit[i] & kMvaTight) == kMvaTight && (looseLepSelBit[i] & kMiniIsoTight) == kMiniIsoTight) idLep[i] = 1;
	  else if(year == 2018 && (looseLepSelBit[i] & kTight) == kTight && (looseLepSelBit[i] & kDxyz) == kDxyz && (looseLepSelBit[i] & kMiniIsoTight) == kMiniIsoTight) idLep[i] = 1;
	}
	else {
          if((looseLepSelBit[i] & kEleMvaWP80) == kEleMvaWP80) idLep[i] = 1;
	}
	countLeptonTight = countLeptonTight + (idLep[i] > 0);
        double thePDGMass = mass_mu;
        if(abs(looseLepPdgId[i])==11) thePDGMass = mass_el;
	TLorentzVector vLepTemp; vLepTemp.SetPtEtaPhiM(looseLepPt[i],looseLepEta[i],looseLepPhi[i],thePDGMass);
        vLoose.push_back(vLepTemp);

	qTot = qTot + abs(looseLepPdgId[i])/looseLepPdgId[i];

        passLooseLepId = passLooseLepId && ((looseLepSelBit[i] & kFake) == kFake);
      }

      if(passLooseLepId == false) continue;

      int lepType = -1; double muSFUnc = 1.0; double elSFUnc = 1.0;
      if     (abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13) {lepType = 0; muSFUnc = 1.015*1.015;}
      else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11) {lepType = 1; muSFUnc = 1.015*1.015;}
      else {lepType = 2; muSFUnc = 1.015; elSFUnc = 1.015;}

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

      TLorentzVector dilep = vLoose[0] + vLoose[1];

      TLorentzVector vWW     = vMet     + dilep;
      TLorentzVector vWWUp   = vMetUp   + dilep;
      TLorentzVector vWWDown = vMetDown + dilep;

      double dPhiLepMET     = TMath::Min(TMath::Abs(vLoose[0].DeltaPhi(vMet    )), TMath::Abs(vLoose[1].DeltaPhi(vMet    )));
      double dPhiLepMETUp   = TMath::Min(TMath::Abs(vLoose[0].DeltaPhi(vMetUp  )), TMath::Abs(vLoose[1].DeltaPhi(vMetUp  )));
      double dPhiLepMETDown = TMath::Min(TMath::Abs(vLoose[0].DeltaPhi(vMetDown)), TMath::Abs(vLoose[1].DeltaPhi(vMetDown)));
      double dPhiLepTrackMET	 = TMath::Min(TMath::Abs(vLoose[0].DeltaPhi(vTrkMet)), TMath::Abs(vLoose[1].DeltaPhi(vTrkMet)));
      double dPhiLepTrackMETUp   = TMath::Min(TMath::Abs(vLoose[0].DeltaPhi(vTrkMet)), TMath::Abs(vLoose[1].DeltaPhi(vTrkMet)));
      double dPhiLepTrackMETDown = TMath::Min(TMath::Abs(vLoose[0].DeltaPhi(vTrkMet)), TMath::Abs(vLoose[1].DeltaPhi(vTrkMet)));

      double PMET     = vMet	.Pt(); if(dPhiLepMET	 < TMath::Pi()/2) { PMET     =  PMET	 * sin(dPhiLepMET    );}
      double PMETUp   = vMetUp  .Pt(); if(dPhiLepMETUp   < TMath::Pi()/2) { PMETUp   =  PMETUp   * sin(dPhiLepMETUp  );}
      double PMETDown = vMetDown.Pt(); if(dPhiLepMETDown < TMath::Pi()/2) { PMETDown =  PMETDown * sin(dPhiLepMETDown);}
      double PTrackMET     = vTrkMet.Pt(); if(dPhiLepTrackMET     < TMath::Pi()/2) { PTrackMET	 =  PTrackMET     * sin(dPhiLepTrackMET	 );}
      double PTrackMETUp   = vTrkMet.Pt(); if(dPhiLepTrackMETUp   < TMath::Pi()/2) { PTrackMETUp   =  PTrackMETUp   * sin(dPhiLepTrackMETUp  );}
      double PTrackMETDown = vTrkMet.Pt(); if(dPhiLepTrackMETDown < TMath::Pi()/2) { PTrackMETDown =  PTrackMETDown * sin(dPhiLepTrackMETDown);}

      double minPMET	 = TMath::Min(PMET    ,PTrackMET    );
      double minPMETUp   = TMath::Min(PMETUp  ,PTrackMETUp  );
      double minPMETDown = TMath::Min(PMETDown,PTrackMETDown);

      bool passBtagVeto     = thePandaFlat.jetNBtags == 0;
      bool passBtagVetoUp   = thePandaFlat.jetNBtags_JESTotalUp == 0;
      bool passBtagVetoDown = thePandaFlat.jetNBtags_JESTotalDown == 0;

      bool passZeroQ = qTot == 0;
      bool passZVeto = dilep.M() > 20 && (fabs(dilep.M()-91.1876) > 15 || lepType == 2);
      bool passPTLLCut = dilep.Pt() > 30 && (dilep.Pt() > 45 ||  lepType == 2);
      bool passMET     = minPMET     > 20 && (minPMET	  > 45 || lepType == 2);
      bool passMETUp   = minPMETUp   > 20 && (minPMETUp   > 45 || lepType == 2);
      bool passMETDown = minPMETDown > 20 && (minPMETDown > 45 || lepType == 2);

      bool passNjets     = thePandaFlat.nJot              <= 2;
      bool passNjetsUp   = thePandaFlat.nJot_JESTotalUp   <= 2;
      bool passNjetsDown = thePandaFlat.nJot_JESTotalDown <= 2;

      bool passWWSel       =  passZeroQ && passZVeto &&  passPTLLCut && passMET     &&  passBtagVeto     && passNjets	 ;
      bool passWWSelUp     =  passZeroQ && passZVeto &&  passPTLLCut && passMETUp   &&  passBtagVetoUp   && passNjetsUp  ;
      bool passWWSelDown   =  passZeroQ && passZVeto &&  passPTLLCut && passMETDown &&  passBtagVetoDown && passNjetsDown;

      bool passSSSel       = !passZeroQ && passZVeto &&  passPTLLCut && passMET     &&  passBtagVeto	 && passNjets	 ;
      bool passSSSelUp     = !passZeroQ && passZVeto &&  passPTLLCut && passMETUp   &&  passBtagVetoUp   && passNjetsUp  ;
      bool passSSSelDown   = !passZeroQ && passZVeto &&  passPTLLCut && passMETDown &&  passBtagVetoDown && passNjetsDown;

      bool passTopSel      =  passZeroQ && passZVeto &&  passPTLLCut && passMET     && !passBtagVeto	 && passNjets	 ;
      bool passTopSelUp    =  passZeroQ && passZVeto &&  passPTLLCut && passMETUp   && !passBtagVetoUp   && passNjetsUp  ;
      bool passTopSelDown  =  passZeroQ && passZVeto &&  passPTLLCut && passMETDown && !passBtagVetoDown && passNjetsDown;

      bool passDYttSel     =  passZeroQ && passZVeto && !passPTLLCut && passMET     &&  passBtagVeto	 && passNjets	 ;
      bool passDYttSelUp   =  passZeroQ && passZVeto && !passPTLLCut && passMETUp   &&  passBtagVetoUp   && passNjetsUp  ;
      bool passDYttSelDown =  passZeroQ && passZVeto && !passPTLLCut && passMETDown &&  passBtagVetoDown && passNjetsDown;

      bool passNoMLLSel    =  passZeroQ &&               passPTLLCut && passMET     &&  passBtagVeto     && passNjets	 ;
      bool passNoMETSel    =  passZeroQ && passZVeto &&  passPTLLCut &&                 passBtagVeto     && passNjets	 ;
      bool passNoPTLLSel   =  passZeroQ && passZVeto &&                 passMET     &&  passBtagVeto     && passNjets	 ;
      bool passNoBtagSel   =  passZeroQ && passZVeto &&  passPTLLCut && passMET                          && passNjets    ;

      int dataCardSel = -1; int dataCardSelUp = -1;int dataCardSelDown = -1;
      if     (passWWSel)   dataCardSel = 0;
      else if(passTopSel)  dataCardSel = 1;
      else if(passSSSel)   dataCardSel = 2;
      else if(passDYttSel) dataCardSel = 3;
      if     (passWWSelUp)   dataCardSelUp = 0;
      else if(passTopSelUp)  dataCardSelUp = 1;
      else if(passSSSelUp)   dataCardSelUp = 2;
      else if(passDYttSelUp) dataCardSelUp = 3;
      if     (passWWSelDown)   dataCardSelDown = 0;
      else if(passTopSelDown)  dataCardSelDown = 1;
      else if(passSSSelDown)   dataCardSelDown = 2;
      else if(passDYttSelDown) dataCardSelDown = 3;

      bool passSystCuts[nSystTypes] = {dataCardSelUp >= 0, dataCardSelDown >= 0};

      if(usePureMC == true && countLeptonTight != idLep.size()) continue;

      int lepTypeOri = lepType;
      lepType = lepType + 3*(int)TMath::Min(thePandaFlat.nJot,2);

      double totalWeight = 1.0; double puWeight = 1.0; double puWeightUp = 1.0; double puWeightDown = 1.0; double sf_l1PrefireE = 1.0;
      double triggerWeights[2] = {1.0, 0.0};
      double thePtwwWeight[5] = {1.0,1.0,1.0,1.0,1.0};
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

        if(passBtagVeto) totalWeight = thePandaFlat.normalizedWeight * lumiV[whichYear] * puWeight * thePandaFlat.sf_l1Prefire * looseLepSF[0] * looseLepSF[1] * thePandaFlat.sf_btag0   * triggerWeights[0] * theMCPrescale;
        else             totalWeight = thePandaFlat.normalizedWeight * lumiV[whichYear] * puWeight * thePandaFlat.sf_l1Prefire * looseLepSF[0] * looseLepSF[1] * thePandaFlat.sf_btagGT0 * triggerWeights[0] * theMCPrescale;

        if     (infileCat_[ifile] == kPlotWZ)                                                totalWeight = totalWeight * thePandaFlat.sf_wz;
	else if(infileCat_[ifile] == kPlotZZ && infileName_[ifile].Contains("qqZZ") == true) totalWeight = totalWeight * thePandaFlat.sf_zz;

        if(infileCat_[ifile] == kPlotqqWW){
          if(thePandaFlat.looseGenLep1PdgId != 0 && thePandaFlat.looseGenLep2PdgId != 0){
	    double thePDGMass[2] = {mass_mu, mass_mu};
	    if(abs(thePandaFlat.looseGenLep1PdgId) == 11) thePDGMass[0] = mass_el;
	    if(abs(thePandaFlat.looseGenLep2PdgId) == 11) thePDGMass[1] = mass_el;
            TLorentzVector vGen1,vGen2;
            vGen1.SetPtEtaPhiM(thePandaFlat.genLep1Pt,thePandaFlat.genLep1Eta,thePandaFlat.genLep1Phi,thePDGMass[0]);
            vGen2.SetPtEtaPhiM(thePandaFlat.genLep2Pt,thePandaFlat.genLep2Eta,thePandaFlat.genLep2Phi,thePDGMass[1]);
	    TLorentzVector wwSystem = vGen1 + vGen2 + vMet;
            Int_t nptwwbin[5] = {fhDWWPtRatio	       ->GetXaxis()->FindBin(TMath::Min(wwSystem.Pt(),499.999)),
	                         fhDWWPtRatio_scaleup  ->GetXaxis()->FindBin(TMath::Min(wwSystem.Pt(),499.999)),
	                         fhDWWPtRatio_scaledown->GetXaxis()->FindBin(TMath::Min(wwSystem.Pt(),499.999)),
	                         fhDWWPtRatio_resumup  ->GetXaxis()->FindBin(TMath::Min(wwSystem.Pt(),499.999)),
	                         fhDWWPtRatio_resumdown->GetXaxis()->FindBin(TMath::Min(wwSystem.Pt(),499.999))};
            thePtwwWeight[0] = fhDWWPtRatio          ->GetBinContent(nptwwbin[0]) * 1.020;
	    thePtwwWeight[1] = fhDWWPtRatio_scaleup  ->GetBinContent(nptwwbin[1]);
	    thePtwwWeight[2] = fhDWWPtRatio_scaledown->GetBinContent(nptwwbin[2]);
	    thePtwwWeight[3] = fhDWWPtRatio_resumup  ->GetBinContent(nptwwbin[3]);
	    thePtwwWeight[4] = fhDWWPtRatio_resumdown->GetBinContent(nptwwbin[4]);
          }
	  totalWeight = totalWeight * thePtwwWeight[0];
	}

        double effSF = 1.0;
        for(unsigned int nl=0; nl<idLep.size(); nl++){
          if(idLep[nl] == 0) continue;
          bool applyTight = true;
          effSF = effSF * lepScaleFactor(vLoose[nl].Pt(),vLoose[nl].Eta(),TMath::Abs(looseLepPdgId[nl]),applyTight,histoLepEffSelMediumEtaPt_m,histoLepEffSelMediumEtaPt_e,histoLepEffSelTightEtaPt_m,histoLepEffSelTightEtaPt_e);
          if(effSF == 0){printf("effSF == 0!: %f %f %d \n",vLoose[nl].Pt(),vLoose[nl].Eta(),TMath::Abs(looseLepPdgId[nl])); return;}
        }
        totalWeight = totalWeight * effSF;
      }

      if(usePureMC == false && countLeptonTight != idLep.size()){
        double fakeSF = 1.0;
        for(unsigned int nl=0; nl<idLep.size(); nl++){
          if(idLep[nl] == 1) continue;
          bool applyTight = true;
          fakeSF = fakeSF * fakeRateFactor(TMath::Min((double)vLoose[nl].Pt(),44.999),TMath::Abs(vLoose[nl].Eta()),TMath::Abs(looseLepPdgId[nl]),applyTight,histoFakeEffSelMediumEtaPt_m,histoFakeEffSelMediumEtaPt_e,histoFakeEffSelTightEtaPt_m,histoFakeEffSelTightEtaPt_e);
          theCategory = kPlotNonPrompt;
        }
        if     (infileCat_[ifile] != kPlotData && countLeptonTight == idLep.size()-2) fakeSF = +1.0 * fakeSF; // double fake, MC
        else if(infileCat_[ifile] != kPlotData && countLeptonTight == idLep.size()-1) fakeSF = -1.0 * fakeSF; // single fake, MC
        else if(infileCat_[ifile] == kPlotData && countLeptonTight == idLep.size()-2) fakeSF = -1.0 * fakeSF; // double fake, data
        else if(infileCat_[ifile] == kPlotData && countLeptonTight == idLep.size()-1) fakeSF = +1.0 * fakeSF; // single fake, data
        else printf("IMPOSSIBLE FAKE OPTION\n");
        totalWeight = totalWeight * fakeSF;
      }

      if(passNoMLLSel )histo[lepType+  0][theCategory]->Fill(TMath::Min(dilep.M(),199.999),totalWeight);
      if(passNoMETSel )histo[lepType+  9][theCategory]->Fill(TMath::Min(minPMET,199.999),totalWeight);
      if(passNoMETSel )histo[lepType+ 18][theCategory]->Fill(TMath::Min(vMet.Pt(),199.999),totalWeight);
      if(passDYttSel)  histo[lepType+ 27][theCategory]->Fill(TMath::Min(dilep.M(),199.999),totalWeight);
      if(passNoPTLLSel)histo[lepType+ 36][theCategory]->Fill(TMath::Min(dilep.Pt(),199.999),totalWeight);
      if(passNoBtagSel)histo[lepType+ 45][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNBtags,4.499),totalWeight);
      if(passWWSel)    histo[lepType+ 54][theCategory]->Fill(TMath::Min(vLoose[0].Pt(),199.999),totalWeight);
      if(passWWSel)    histo[lepType+ 63][theCategory]->Fill(TMath::Min(vLoose[1].Pt(),199.999),totalWeight);
      if(passWWSel)    histo[lepType+ 72][theCategory]->Fill(TMath::Min(dilep.M(),199.999),totalWeight);
      if(passWWSel)    histo[lepType+ 81][theCategory]->Fill(TMath::Abs(vLoose[0].DeltaPhi(vLoose[1]))*180/TMath::Pi(),totalWeight);
      if(passSSSel)    histo[lepType+ 90][theCategory]->Fill(TMath::Min(vLoose[0].Pt(),199.999),totalWeight);
      if(passSSSel)    histo[lepType+ 99][theCategory]->Fill(TMath::Min(vLoose[1].Pt(),199.999),totalWeight);
      if(passSSSel)    histo[lepType+108][theCategory]->Fill(TMath::Min(dilep.M(),199.999),totalWeight);
      if(passSSSel)    histo[lepType+117][theCategory]->Fill(TMath::Abs(vLoose[0].DeltaPhi(vLoose[1]))*180/TMath::Pi(),totalWeight);
      if(passTopSel)   histo[lepType+126][theCategory]->Fill(TMath::Min(vLoose[0].Pt(),199.999),totalWeight);
      if(passTopSel)   histo[lepType+135][theCategory]->Fill(TMath::Min(vLoose[1].Pt(),199.999),totalWeight);
      if(passTopSel)   histo[lepType+144][theCategory]->Fill(TMath::Min(dilep.M(),199.999),totalWeight);
      if(passTopSel)   histo[lepType+153][theCategory]->Fill(TMath::Abs(vLoose[0].DeltaPhi(vMet))*180/TMath::Pi(),totalWeight);
      if(passWWSel)    histo[lepTypeOri+162][theCategory]->Fill(TMath::Min(vWW.Pt(),299.999),totalWeight);
      if(passTopSel)   histo[lepTypeOri+165][theCategory]->Fill(TMath::Min(vWW.Pt(),299.999),totalWeight);

      if(lepTypeOri == 2){
        int typeSelAux = 0;
        if     (thePandaFlat.nJot == 0) typeSelAux = 0;
        else if(thePandaFlat.nJot == 1) typeSelAux = 1;
        else                            typeSelAux = 2;
        int typeSelAuxUp = 0;
        if     (thePandaFlat.nJot_JESTotalUp == 0) typeSelAuxUp = 0;
        else if(thePandaFlat.nJot_JESTotalUp == 1) typeSelAuxUp = 1;
        else                                       typeSelAuxUp = 2;
        int typeSelAuxDown = 0;
        if     (thePandaFlat.nJot_JESTotalDown == 0) typeSelAuxDown = 0;
        else if(thePandaFlat.nJot_JESTotalDown == 1) typeSelAuxDown = 1;
        else                                         typeSelAuxDown = 2;

        double MVAVar     = TMath::Min(vWW    .Pt(),999.999);
        double MVAVarUp   = TMath::Min(vWWUp  .Pt(),999.999);
        double MVAVarDown = TMath::Min(vWWDown.Pt(),999.999);

        if     (dataCardSel     >= 0) MVAVar     = MVAVar     + 1000 * dataCardSel     + 4000 * typeSelAux;
        if     (dataCardSelUp   >= 0) MVAVarUp   = MVAVarUp   + 1000 * dataCardSelUp   + 4000 * typeSelAuxUp;
        if     (dataCardSelDown >= 0) MVAVarDown = MVAVarDown + 1000 * dataCardSelDown + 4000 * typeSelAuxDown;

        // Avoid QCD scale weights that are anomalous high
        double maxQCDscale = (TMath::Abs(thePandaFlat.scale[0])+TMath::Abs(thePandaFlat.scale[1])+TMath::Abs(thePandaFlat.scale[2])+
	                      TMath::Abs(thePandaFlat.scale[3])+TMath::Abs(thePandaFlat.scale[4])+TMath::Abs(thePandaFlat.scale[5]))/6.0;
        if(maxQCDscale == 0) maxQCDscale = 1;

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
            if(infileCat_[ifile] == kPlotqqWW){
              histo_qqWW_CMS_MVAWW_nlo	    ->Fill(MVAVar,totalWeight);
              histo_qqWW_CMS_MVAWW_qup_nlo  ->Fill(MVAVar,totalWeight*thePtwwWeight[1]);
              histo_qqWW_CMS_MVAWW_qdown_nlo->Fill(MVAVar,totalWeight*thePtwwWeight[2]);
              histo_qqWW_CMS_MVAWW_sup_nlo  ->Fill(MVAVar,totalWeight*thePtwwWeight[3]);
              histo_qqWW_CMS_MVAWW_sdown_nlo->Fill(MVAVar,totalWeight*thePtwwWeight[4]);
	    }
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
	}
      }

    } // end events loop
    the_input_file->Close();
  } // end chain loop

  for(int ic=0; ic<nPlotCategories; ic++) histo[allPlots-1][ic]->Add(histo_Baseline[ic]);

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

      histo_Baseline              [ic]->SetBinContent(nb, TMath::Max((float)histo_Baseline		[ic]->GetBinContent(nb),0.0f));
      histo_QCDScaleUp  	  [ic]->SetBinContent(nb, TMath::Max((float)histo_QCDScaleUp		[ic]->GetBinContent(nb),0.0f));
      histo_QCDScaleDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_QCDScaleDown  	[ic]->GetBinContent(nb),0.0f));
      histo_PDFBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PDFBoundingUp 	[ic]->GetBinContent(nb),0.0f));
      histo_PDFBoundingDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PDFBoundingDown	[ic]->GetBinContent(nb),0.0f));
      histo_LepEffMBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_LepEffMBoundingUp	[ic]->GetBinContent(nb),0.0f));
      histo_LepEffMBoundingDown   [ic]->SetBinContent(nb, TMath::Max((float)histo_LepEffMBoundingDown	[ic]->GetBinContent(nb),0.0f));
      histo_LepEffEBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_LepEffEBoundingUp	[ic]->GetBinContent(nb),0.0f));
      histo_LepEffEBoundingDown   [ic]->SetBinContent(nb, TMath::Max((float)histo_LepEffEBoundingDown	[ic]->GetBinContent(nb),0.0f));
      histo_PUBoundingUp          [ic]->SetBinContent(nb, TMath::Max((float)histo_PUBoundingUp  	[ic]->GetBinContent(nb),0.0f));
      histo_PUBoundingDown        [ic]->SetBinContent(nb, TMath::Max((float)histo_PUBoundingDown	[ic]->GetBinContent(nb),0.0f));
      histo_PUBoundingDown        [ic]->SetBinContent(nb, TMath::Max((float)(2*histo_Baseline[ic]->GetBinContent(nb)-histo_PUBoundingUp[ic]->GetBinContent(nb)),0.0f));
      for(int ny=0; ny<nYears; ny++){
      histo_BTAGBBoundingUp    [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_BTAGBBoundingUp    [ny][ic]->GetBinContent(nb),0.0f));
      histo_BTAGBBoundingDown  [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_BTAGBBoundingDown  [ny][ic]->GetBinContent(nb),0.0f));
      histo_BTAGBBoundingDown  [ny][ic]->SetBinContent(nb, TMath::Max((float)(2*histo_Baseline[ic]->GetBinContent(nb)-histo_BTAGBBoundingUp[ny][ic]->GetBinContent(nb)),0.0f));
      histo_BTAGLBoundingUp    [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_BTAGLBoundingUp    [ny][ic]->GetBinContent(nb),0.0f));
      histo_BTAGLBoundingDown  [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_BTAGLBoundingDown  [ny][ic]->GetBinContent(nb),0.0f));
      histo_BTAGLBoundingDown  [ny][ic]->SetBinContent(nb, TMath::Max((float)(2*histo_Baseline[ic]->GetBinContent(nb)-histo_BTAGLBoundingUp[ny][ic]->GetBinContent(nb)),0.0f));
      histo_JESBoundingUp      [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_JESBoundingUp      [ny][ic]->GetBinContent(nb),0.0f));
      histo_JESBoundingDown    [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_JESBoundingDown    [ny][ic]->GetBinContent(nb),0.0f));
      histo_JESBoundingDown    [ny][ic]->SetBinContent(nb, TMath::Max((float)(2*histo_Baseline[ic]->GetBinContent(nb)-histo_JESBoundingUp[ny][ic]->GetBinContent(nb)),0.0f));
      histo_PreFireBoundingUp  [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_PreFireBoundingUp  [ny][ic]->GetBinContent(nb),0.0f));
      histo_PreFireBoundingDown[ny][ic]->SetBinContent(nb, TMath::Max((float)histo_PreFireBoundingDown[ny][ic]->GetBinContent(nb),0.0f));
      histo_TriggerBoundingUp  [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_TriggerBoundingUp  [ny][ic]->GetBinContent(nb),0.0f));
      histo_TriggerBoundingDown[ny][ic]->SetBinContent(nb, TMath::Max((float)histo_TriggerBoundingDown[ny][ic]->GetBinContent(nb),0.0f));
      }
    }
    histo_PUBoundingUp	[ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_PUBoundingUp  [ic]->GetSumOfWeights());
    histo_PUBoundingDown[ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_PUBoundingDown[ic]->GetSumOfWeights());
    if(ic == kPlotqqWW || ic == kPlotggWW) {
      histo_QCDScaleUp  [ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_QCDScaleUp  [ic]->GetSumOfWeights());
      histo_QCDScaleDown[ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_QCDScaleDown[ic]->GetSumOfWeights());
    }
  }

  for(int nj=0; nj<3; nj++){
    histo_TopNormJetUp[nj]        ->Add(histo_Baseline[kPlotTop]);
    histo_TopNormJetDown[nj]      ->Add(histo_Baseline[kPlotTop]);
    histo_DYNormJetUp[nj]         ->Add(histo_Baseline[kPlotDY]);
    histo_DYNormJetDown[nj]       ->Add(histo_Baseline[kPlotDY]);
    histo_NonPromptNormJetUp[nj]  ->Add(histo_Baseline[kPlotNonPrompt]);
    histo_NonPromptNormJetDown[nj]->Add(histo_Baseline[kPlotNonPrompt]);
  }
  for(int i=1; i<=4; i++) {
    histo_TopNormJetUp[0]        ->SetBinContent(i,histo_TopNormJetUp[0]        ->GetBinContent(i)*10.0);
    histo_TopNormJetDown[0]      ->SetBinContent(i,histo_TopNormJetDown[0]      ->GetBinContent(i)/10.0);
    histo_DYNormJetUp[0]         ->SetBinContent(i,histo_DYNormJetUp[0]	        ->GetBinContent(i)*10.0);
    histo_DYNormJetDown[0]       ->SetBinContent(i,histo_DYNormJetDown[0]       ->GetBinContent(i)/10.0);
    histo_NonPromptNormJetUp[0]  ->SetBinContent(i,histo_NonPromptNormJetUp[0]  ->GetBinContent(i)*10.0);
    histo_NonPromptNormJetDown[0]->SetBinContent(i,histo_NonPromptNormJetDown[0]->GetBinContent(i)/10.0);
  }
  for(int i=5; i<=8; i++) {
    histo_TopNormJetUp[1]        ->SetBinContent(i,histo_TopNormJetUp[1]	->GetBinContent(i)*10.0);
    histo_TopNormJetDown[1]      ->SetBinContent(i,histo_TopNormJetDown[1]	->GetBinContent(i)/10.0);
    histo_DYNormJetUp[1]         ->SetBinContent(i,histo_DYNormJetUp[1]	        ->GetBinContent(i)*10.0);
    histo_DYNormJetDown[1]       ->SetBinContent(i,histo_DYNormJetDown[1]	->GetBinContent(i)/10.0);
    histo_NonPromptNormJetUp[1]  ->SetBinContent(i,histo_NonPromptNormJetUp[1]  ->GetBinContent(i)*10.0);
    histo_NonPromptNormJetDown[1]->SetBinContent(i,histo_NonPromptNormJetDown[1]->GetBinContent(i)/10.0);
  }
  for(int i=9; i<=12; i++) {
    histo_TopNormJetUp[2]        ->SetBinContent(i,histo_TopNormJetUp[2]	->GetBinContent(i)*10.0);
    histo_TopNormJetDown[2]      ->SetBinContent(i,histo_TopNormJetDown[2]	->GetBinContent(i)/10.0);
    histo_DYNormJetUp[2]         ->SetBinContent(i,histo_DYNormJetUp[2]	        ->GetBinContent(i)*10.0);
    histo_DYNormJetDown[2]       ->SetBinContent(i,histo_DYNormJetDown[2]	->GetBinContent(i)/10.0);
    histo_NonPromptNormJetUp[2]  ->SetBinContent(i,histo_NonPromptNormJetUp[2]  ->GetBinContent(i)*10.0);
    histo_NonPromptNormJetDown[2]->SetBinContent(i,histo_NonPromptNormJetDown[2]->GetBinContent(i)/10.0);
  }

  double ratio_nnlo_nlo = histo_Baseline[kPlotqqWW]->GetSumOfWeights()/histo_qqWW_CMS_MVAWW_nlo->GetSumOfWeights();
  histo_qqWW_CMS_MVAWW_nlo      ->Scale(ratio_nnlo_nlo);
  histo_qqWW_CMS_MVAWW_qup_nlo  ->Scale(ratio_nnlo_nlo/ww_norm_unc_ptwei[0]);
  histo_qqWW_CMS_MVAWW_qdown_nlo->Scale(ratio_nnlo_nlo/ww_norm_unc_ptwei[1]);
  histo_qqWW_CMS_MVAWW_sup_nlo  ->Scale(ratio_nnlo_nlo/ww_norm_unc_ptwei[2]);
  histo_qqWW_CMS_MVAWW_sdown_nlo->Scale(ratio_nnlo_nlo/ww_norm_unc_ptwei[3]);

  if(showSyst == true){
    printf("Yields\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) printf("%6.2f ",histo_Baseline[ic]->GetBinContent(i)); printf("\n");
    }
    printf("uncertainties PTWW\n");
    printf("%10s: ",plotBaseNames[kPlotqqWW].Data());
    for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[kPlotqqWW]->GetBinContent(i)>0)printf("%5.1f ",histo_qqWW_CMS_MVAWW_qup_nlo  ->GetBinContent(i)/histo_Baseline[kPlotqqWW]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    printf("%10s: ",plotBaseNames[kPlotqqWW].Data());
    for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[kPlotqqWW]->GetBinContent(i)>0)printf("%5.1f ",histo_qqWW_CMS_MVAWW_qdown_nlo->GetBinContent(i)/histo_Baseline[kPlotqqWW]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    printf("%10s: ",plotBaseNames[kPlotqqWW].Data());
    for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[kPlotqqWW]->GetBinContent(i)>0)printf("%5.1f ",histo_qqWW_CMS_MVAWW_sup_nlo  ->GetBinContent(i)/histo_Baseline[kPlotqqWW]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    printf("%10s: ",plotBaseNames[kPlotqqWW].Data());
    for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[kPlotqqWW]->GetBinContent(i)>0)printf("%5.1f ",histo_qqWW_CMS_MVAWW_sdown_nlo->GetBinContent(i)/histo_Baseline[kPlotqqWW]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
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
  }

  // Filling datacards input root file
  char outputLimits[200];
  sprintf(outputLimits,"ww_%d_input.root",year);
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
  }
  for(int nj=0; nj<3; nj++){
    histo_TopNormJetUp[nj]        ->Write();
    histo_TopNormJetDown[nj]      ->Write();
    histo_DYNormJetUp[nj]         ->Write();
    histo_DYNormJetDown[nj]       ->Write();
    histo_NonPromptNormJetUp[nj]  ->Write();
    histo_NonPromptNormJetDown[nj]->Write();
  }
  histo_qqWW_CMS_MVAWW_nlo      ->Write();
  histo_qqWW_CMS_MVAWW_qup_nlo  ->Write();
  histo_qqWW_CMS_MVAWW_qdown_nlo->Write();
  histo_qqWW_CMS_MVAWW_sup_nlo  ->Write();
  histo_qqWW_CMS_MVAWW_sdown_nlo->Write();
  outFileLimits->Close();


  // Filling datacards txt file
  char outputLimitsCard[200];  					  
  sprintf(outputLimitsCard,"datacard_ww_%d.txt",year);
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
    if     (ic != kPlotqqWW && 
            ic != kPlotggWW) newcardShape << Form("%d  ", ic);
    else if(ic == kPlotqqWW) newcardShape << Form("%d  ",  0);
    else if(ic == kPlotggWW) newcardShape << Form("%d  ", -1);
  }
  newcardShape << Form("\n");

  newcardShape << Form("rate  ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("%f  ", histo_Baseline[ic]->GetSumOfWeights());
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_fake_%d    lnN     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("1.2 ");
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

  newcardShape << Form("WWNNLO_scale    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotqqWW) newcardShape << Form("1.0 ");
    else                newcardShape << Form("- ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("WWNNLO_resum    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotqqWW) newcardShape << Form("1.0 ");
    else                newcardShape << Form("- ");
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
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
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

  for(int nj=0; nj<3; nj++){
    newcardShape << Form("CMS_TopNormJet%dcat_%d    shape     ",nj,year);
    for (int ic=0; ic<nPlotCategories; ic++){
      if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
      if(ic == kPlotTop) newcardShape << Form("1.0 ");
      else               newcardShape << Form("- ");
    }
    newcardShape << Form("\n");
  }

  for(int nj=0; nj<3; nj++){
    newcardShape << Form("CMS_DYNormJet%dcat_%d    shape     ",nj,year);
    for (int ic=0; ic<nPlotCategories; ic++){
      if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
      if(ic == kPlotDY) newcardShape << Form("1.0 ");
      else              newcardShape << Form("- ");
    }
    newcardShape << Form("\n");
  }

  for(int nj=0; nj<3; nj++){
    newcardShape << Form("CMS_NonPromptNormJet%dcat_%d    shape     ",nj,year);
    for (int ic=0; ic<nPlotCategories; ic++){
      if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
      if(ic == kPlotNonPrompt) newcardShape << Form("1.0 ");
      else                     newcardShape << Form("- ");
    }
    newcardShape << Form("\n");
  }

  newcardShape << Form("ch1 autoMCStats 0\n");

  newcardShape.close();

  char output[200];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    sprintf(output,"histoWW_%d_%d.root",year,thePlot);	
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
