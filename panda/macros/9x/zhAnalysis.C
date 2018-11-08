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
#include "MitAnalysisRunII/panda/macros/9x/trigger_auxiliar.h"

const bool isDEBUG = false;
const bool showSyst = true;
const unsigned int period = 0;
const double mcPrescale = 1;
const bool usePureMC = true; // if true, passLooseLepId not applied
enum selType                     { ZHSEL,   ZHTIGHTSEL,   BTAGSEL,   ZLLSEL,   WWSEL,   PRESEL, nSelTypes};
TString selTypeName[nSelTypes]=  {"ZHSEL", "ZHTIGHTSEL", "BTAGSEL", "ZLLSEL", "WWSEL", "PRESEL"};
enum systType                     {JESUP=0, JESDOWN,  METUP,  METDOWN, nSystTypes};
TString systTypeName[nSystTypes]= {"JESUP","JESDOWN","METUP","METDOWN"};

void zhAnalysis(
int year, bool isBlinded = false
){
  // trigger
  double trgEff [3][nTrgBinPt1][nTrgBinPt2][nTrgBinEta1][nTrgBinEta2];
  double trgEffE[3][nTrgBinPt1][nTrgBinPt2][nTrgBinEta1][nTrgBinEta2];
  initialize_trgEff(trgEff, trgEffE, year);

  //*******************************************************
  //Inputs
  //*******************************************************
  vector<TString> infileName_;
  vector<int> infileCat_;

  double lumi;
  TString filesPath;
  TString fLepton_FakesName;
  TString puPath;
  TString npvPath;
  if(year == 2017) {
    lumi = 41.5;
    filesPath = "/data/t3home000/ceballos/panda/v_004_0/";
    fLepton_FakesName = "MitAnalysisRunII/data/90x/histoFakeEtaPt_2017.root";
    puPath = "MitAnalysisRunII/data/90x/puWeights_90x.root";
    npvPath = "MitAnalysisRunII/data/90x/npvWeights_2017.root";

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
    infileName_.push_back(Form("%sWZ3l_powheg_mll1.root" ,filesPath.Data()));    infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTVV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sqqZH125inv.root" ,filesPath.Data()));          infileCat_.push_back(kPlotBSM);
    infileName_.push_back(Form("%sggZH125inv.root" ,filesPath.Data()));          infileCat_.push_back(kPlotBSM);
  }
  else if(year == 2016) {
    lumi = 35.9;
    filesPath = "/data/t3home000/ceballos/panda/v_002_0/";
    fLepton_FakesName = "MitAnalysisRunII/data/90x/histoFakeEtaPt_2016.root";
    puPath = "MitAnalysisRunII/data/80x/puWeights_80x_37ifb.root";
    npvPath = "MitAnalysisRunII/data/90x/npvWeights_2016.root";

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
    infileName_.push_back(Form("%sqqZH125inv.root" ,filesPath.Data()));           infileCat_.push_back(kPlotBSM);
    infileName_.push_back(Form("%sggZH125inv.root" ,filesPath.Data()));           infileCat_.push_back(kPlotBSM);
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

  TFile *fNPVFile = TFile::Open(Form("%s",npvPath.Data()));
  TH1D *fhDNPV    = (TH1D*)(fNPVFile->Get("npvWeights"));   assert(fhDNPV);    fhDNPV   ->SetDirectory(0);
  delete fNPVFile;

  //const int nBinMVA = 22; Float_t xbins[nBinMVA+1] = {0, 70, 100, 125, 150, 175, 200, 250, 300, 350, 400, 500, 600,
  //                                                               1125,1150,1175,1200,1250,1300,1350,1400,1500,1600};
  const int nBinMVA = 12; Float_t xbins[nBinMVA+1] = {0, 70, 100, 125, 150, 175, 200, 250, 300, 350, 400, 500, 600};

  const double metMax = 599.999;

  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 73;
  TH1D* histo[allPlots][nPlotCategories];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    if     (thePlot >=   0 && thePlot <=   2) {nBinPlot = 100; xminPlot =100.0; xmaxPlot = 500;}
    else if(thePlot >=   3 && thePlot <=   5) {nBinPlot = 100; xminPlot = 70.0; xmaxPlot = 270;}
    else if(thePlot >=   6 && thePlot <=  14) {nBinPlot = 100; xminPlot =100.0; xmaxPlot = 300;}
    else if(thePlot >=  15 && thePlot <=  17) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 100;}
    else if(thePlot >=  18 && thePlot <=  20) {nBinPlot = 5;   xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >=  21 && thePlot <=  23) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >=  24 && thePlot <=  26) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 1;}
    else if(thePlot >=  27 && thePlot <=  29) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = TMath::Pi();}
    else if(thePlot >=  30 && thePlot <=  32) {nBinPlot = 4;   xminPlot = -0.5; xmaxPlot = 3.5;}
    else if(thePlot >=  33 && thePlot <=  35) {nBinPlot = 200; xminPlot = 50.0; xmaxPlot = 250;}
    else if(thePlot >=  36 && thePlot <=  38) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = TMath::Pi();}
    else if(thePlot >=  39 && thePlot <=  41) {nBinPlot = 4;   xminPlot = -0.5; xmaxPlot = 3.5;}
    else if(thePlot >=  42 && thePlot <=  44) {nBinPlot = 40;  xminPlot =  0.0; xmaxPlot = 4.0;}
    else if(thePlot >=  45 && thePlot <=  47) {nBinPlot = 10;  xminPlot = -0.5; xmaxPlot = 9.5;}
    else if(thePlot >=  48 && thePlot <=  50) {nBinPlot =100;  xminPlot = -5.0; xmaxPlot = 5.0;}
    else if(thePlot >=  51 && thePlot <=  59) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = TMath::Pi();}
    else if(thePlot >=  60 && thePlot <=  62) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >=  63 && thePlot <=  65) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 1;}
    else if(thePlot >=  66 && thePlot <=  68) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = TMath::Pi();}
    else if(thePlot >=  69 && thePlot <=  71) {nBinPlot = 4;   xminPlot = -0.5; xmaxPlot = 3.5;}
    TH1D* histos;
    if(thePlot == allPlots-1) histos = new TH1D("histos", "histos", nBinMVA, xbins);
    else                      histos = new TH1D("histos", "histos", nBinPlot, xminPlot, xmaxPlot);
    histos->Sumw2();
    for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = (TH1D*) histos->Clone(Form("histo%d",i));
    histos->Reset();histos->Clear();
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
  TH1D *histo_BTAGBBoundingUp[nPlotCategories];
  TH1D *histo_BTAGBBoundingDown[nPlotCategories];
  TH1D *histo_BTAGLBoundingUp[nPlotCategories];
  TH1D *histo_BTAGLBoundingDown[nPlotCategories];
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
  TH1D *histo_JESBoundingUp[nPlotCategories];
  TH1D *histo_JESBoundingDown[nPlotCategories];
  TH1D *histo_METBoundingUp[nPlotCategories];
  TH1D *histo_METBoundingDown[nPlotCategories];
  
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
    histo_BTAGBBoundingUp	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_btagbUp"        , plotBaseNames[ic].Data()));
    histo_BTAGBBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_btagbDown"      , plotBaseNames[ic].Data()));
    histo_BTAGLBoundingUp	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_btaglUp"        , plotBaseNames[ic].Data()));
    histo_BTAGLBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_btaglDown"      , plotBaseNames[ic].Data()));
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
    histo_JESBoundingUp 	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_jesUp"          , plotBaseNames[ic].Data()));
    histo_JESBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_jesDown"        , plotBaseNames[ic].Data()));
    histo_METBoundingUp 	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_metUp"          , plotBaseNames[ic].Data()));
    histo_METBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_metDown"        , plotBaseNames[ic].Data()));
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

      vector<float>  looseLepPt,looseLepEta,looseLepPhi,looseLepSF;
      vector<int> looseLepSelBit,looseLepPdgId;
      int ptSelCuts[3] = {0,0,0};
      for(int i=0; i<thePandaFlat.nLooseMuon; i++){
        looseLepPt.push_back(thePandaFlat.muonPt[i]);
        looseLepEta.push_back(thePandaFlat.muonEta[i]);
        looseLepPhi.push_back(thePandaFlat.muonPhi[i]);
        looseLepSF.push_back(thePandaFlat.muonSfReco[i] * thePandaFlat.muonSfMedium[i]);
        looseLepSelBit.push_back(thePandaFlat.muonSelBit[i]);
        looseLepPdgId.push_back(thePandaFlat.muonPdgId[i]);
	if(thePandaFlat.muonPt[i] > 25) ptSelCuts[0]++;
	if(thePandaFlat.muonPt[i] > 20) ptSelCuts[1]++;
	if(thePandaFlat.muonPt[i] > 10) ptSelCuts[2]++;
      }
      for(int i=0; i<thePandaFlat.nLooseElectron; i++){
        looseLepPt.push_back(thePandaFlat.electronPt[i]);
        looseLepEta.push_back(thePandaFlat.electronEta[i]);
        looseLepPhi.push_back(thePandaFlat.electronPhi[i]);
        looseLepSF.push_back(thePandaFlat.electronSfReco[i] * thePandaFlat.electronSfMedium[i]);
        looseLepSelBit.push_back(thePandaFlat.electronSelBit[i]);
        looseLepPdgId.push_back(thePandaFlat.electronPdgId[i]);
	if(thePandaFlat.electronPt[i] > 25) ptSelCuts[0]++;
	if(thePandaFlat.electronPt[i] > 20) ptSelCuts[1]++;
	if(thePandaFlat.electronPt[i] > 10) ptSelCuts[2]++;
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
        if     (abs(looseLepPdgId[i])==13 && (looseLepSelBit[i] & kMedium) == kMedium) idLep[i] = 1;
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
      if     (year == 2016) {
        vMet    .SetPtEtaPhiM(thePandaFlat.pfmet,0.0,thePandaFlat.pfmetphi,0.0);
        vMetUp  .SetPtEtaPhiM(thePandaFlat.pfmet_JESTotalUp  ,0.0,thePandaFlat.pfmetphi_JESTotalUp  ,0.0);
        vMetDown.SetPtEtaPhiM(thePandaFlat.pfmet_JESTotalDown,0.0,thePandaFlat.pfmetphi_JESTotalDown,0.0);
      } 
      else if(year == 2017){
        vMet    .SetPtEtaPhiM(thePandaFlat.puppimet,0.0,thePandaFlat.puppimetphi,0.0);
        vMetUp  .SetPtEtaPhiM(thePandaFlat.puppimet_JESTotalUp  ,0.0,thePandaFlat.puppimetphi_JESTotalUp  ,0.0);
        vMetDown.SetPtEtaPhiM(thePandaFlat.puppimet_JESTotalDown,0.0,thePandaFlat.puppimetphi_JESTotalDown,0.0);
      }

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

      double dPhiJetMET = -1.0; double dPhiJetMETUp = -1.0; double dPhiJetMETDown = -1.0;
      if(thePandaFlat.nJot > 0 && thePandaFlat.jotPt[0] > 30) {
        TLorentzVector vJetTemp;
        vJetTemp.SetPtEtaPhiM(thePandaFlat.jotPt[0],thePandaFlat.jotEta[0],thePandaFlat.jotPhi[0],0.0);
        dPhiJetMET = TMath::Abs(vJetTemp.DeltaPhi(vMet));
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

      TLorentzVector dilep = vZ1l1+vZ1l2;
      double dPhiDiLepMET = TMath::Abs(dilep.DeltaPhi(vMet)); double dPhiDiLepMETUp = TMath::Abs(dilep.DeltaPhi(vMetUp)); double dPhiDiLepMETDown = TMath::Abs(dilep.DeltaPhi(vMetDown));
      double mT = TMath::Sqrt(2.0*dilep.Pt()*vMet.Pt()*(1.0 - cos(dPhiDiLepMET)));

      bool passZMass = TMath::Abs(mllZ-91.1876) < 15.0;
      bool passZMassSB = mllZ > 110 && mllZ < 200;
      bool passMET    = vMet.Pt() > 100;
      bool passMETMin     = vMet.Pt()     > 70 && (lepType != 2 || vMet.Pt()     > 100);
      bool passMETMinUp   = vMetUp.Pt()   > 70 && (lepType != 2 || vMetUp.Pt()   > 100);
      bool passMETMinDown = vMetDown.Pt() > 70 && (lepType != 2 || vMetDown.Pt() > 100);
      bool passPTLL   = dilep.Pt() > 60;

      double ptFrac     = TMath::Abs(dilep.Pt()-vMet.Pt()    )/dilep.Pt();
      double ptFracUp   = TMath::Abs(dilep.Pt()-vMetUp.Pt()  )/dilep.Pt();
      double ptFracDown = TMath::Abs(dilep.Pt()-vMetDown.Pt())/dilep.Pt();
      bool passPTFrac     = ptFrac     < 0.4;
      bool passPTFracUp   = ptFracUp   < 0.4;
      bool passPTFracDown = ptFracDown < 0.4;
      bool passDPhiZMET     = dPhiDiLepMET     > 2.5;
      bool passDPhiZMETUp   = dPhiDiLepMETUp   > 2.5;
      bool passDPhiZMETDown = dPhiDiLepMETDown > 2.5;
      bool passNjets     = thePandaFlat.nJot              <= 2;
      bool passNjetsUp   = thePandaFlat.nJot_JESTotalUp   <= 2;
      bool passNjetsDown = thePandaFlat.nJot_JESTotalDown <= 2;

      bool passBtagVeto = thePandaFlat.jetNBtags == 0; bool passBtagVetoUp = thePandaFlat.jetNBtags_JESTotalUp == 0; bool passBtagVetoDown = thePandaFlat.jetNBtags_JESTotalDown == 0;
      double dphill = TMath::Abs(vZ1l1.DeltaPhi(vZ1l2));
      double detall = TMath::Abs(vZ1l1.Eta()-vZ1l2.Eta());
      double drll = sqrt(dphill*dphill+detall*detall);
      bool passDRLL = drll < 1.8;

      bool passDPhiJetMET     = dPhiJetMET     == -1 || (dPhiJetMET     >= 0.5 && TMath::Abs(thePandaFlat.jotEta[0]) < 2.5);
      bool passDPhiJetMETUp   = dPhiJetMETUp   == -1 || (dPhiJetMETUp   >= 0.5 && TMath::Abs(thePandaFlat.jotEta[0]) < 2.5);
      bool passDPhiJetMETDown = dPhiJetMETDown == -1 || (dPhiJetMETDown >= 0.5 && TMath::Abs(thePandaFlat.jotEta[0]) < 2.5);
      bool passTauVeto    = thePandaFlat.nTau == 0;

      //                             0         1           2         3              4        5          6            7            8       9
      bool passCutEvol[10] = {passPTLL,passZMass,passTauVeto,passNjets,passDPhiJetMET,passDRLL,passPTFrac,passDPhiZMET,passBtagVeto,passMET};
      bool passCutEvolAll = true;

      bool passAllCuts[nSelTypes] = {                   
      passZMass   && passNjets && passMETMin && passPTFrac && passDPhiZMET &&  passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passDRLL,   // ZHSEL
      passZMass   && passNjets && passMET    && passPTFrac && passDPhiZMET &&  passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passDRLL,   // ZHTIGHTSEL
      passZMass   && passNjets && passMET    && passPTFrac && passDPhiZMET && !passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passDRLL,   // BTAGSEL
      passZMass   &&		  passMET    && 					       passPTLL &&		     passTauVeto,               // ZLLSEL
      passZMassSB && passNjets && passMET    && passPTFrac && passDPhiZMET &&  passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passDRLL,   // WWSEL
      passZMass   && passNjets &&                                                              passPTLL && passDPhiJetMET && passTauVeto && passDRLL    // PRESEL
                                    };

      bool passNMinusOne[10] = {
     		  passNjets && passMET && passPTFrac && passDPhiZMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passDRLL,
     passZMass &&	       passMET && passPTFrac && passDPhiZMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passDRLL,
     passZMass && passNjets &&  	  passPTFrac && passDPhiZMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passDRLL,
     passZMass && passNjets && passMET &&	        passDPhiZMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passDRLL,
     passZMass && passNjets && passMET && passPTFrac && 	        passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passDRLL,
     passZMass && passNjets && passMET && passPTFrac && passDPhiZMET && 		passPTLL && passDPhiJetMET && passTauVeto && passDRLL,
     passZMass && passNjets && passMET && passPTFrac && passDPhiZMET && passBtagVeto && 	    passDPhiJetMET && passTauVeto && passDRLL,
     passZMass && passNjets && passMET && passPTFrac && passDPhiZMET && passBtagVeto && passPTLL &&		      passTauVeto && passDRLL,
     passZMass && passNjets && passMET && passPTFrac && passDPhiZMET && passBtagVeto && passPTLL && passDPhiJetMET                && passDRLL,
     passZMass && passNjets && passMET && passPTFrac && passDPhiZMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto
                                    };

      bool passSystCuts[nSystTypes] = {                   
      passZMass   && passNjetsUp   && passMETMinUp   && passPTFracUp   && passDPhiZMETUp   &&  passBtagVetoUp   && passPTLL && passDPhiJetMETUp   && passTauVeto && passDRLL,
      passZMass   && passNjetsDown && passMETMinDown && passPTFracDown && passDPhiZMETDown &&  passBtagVetoDown && passPTLL && passDPhiJetMETDown && passTauVeto && passDRLL,
      passZMass   && passNjets     && passMETMin     && passPTFrac     && passDPhiZMET     &&  passBtagVeto     && passPTLL && passDPhiJetMET     && passTauVeto && passDRLL,
      passZMass   && passNjets     && passMETMin     && passPTFrac     && passDPhiZMET     &&  passBtagVeto     && passPTLL && passDPhiJetMET     && passTauVeto && passDRLL
                                    };

      double totalWeight = 1.0; double puWeight = 1.0; double puWeightUp = 1.0; double puWeightDown = 1.0; double npvWeight = 1.0;
      double sf_EWKZH = 1.0; double sf_EWKZHUp = 1.0; double sf_EWKZHDown = 1.0;
      if(theCategory != kPlotData){
        double triggerWeights[2] = {1.0, 0.0};
	if(thePandaFlat.nLooseLep == 2) {
          trigger_sf(triggerWeights, trgEff, trgEffE, lepType, looseLepPt[0], TMath::Abs(looseLepEta[0]), looseLepPt[1], TMath::Abs(looseLepEta[1]));
        }
	puWeight     = nPUScaleFactor(fhDPU,    thePandaFlat.pu);
        puWeightUp   = nPUScaleFactor(fhDPUUp,  thePandaFlat.pu);
        puWeightDown = nPUScaleFactor(fhDPUDown,thePandaFlat.pu);

	npvWeight = nPUScaleFactor(fhDNPV, thePandaFlat.npv);

        if(passBtagVeto) totalWeight = thePandaFlat.normalizedWeight * lumi * puWeight * thePandaFlat.sf_l1Prefire * thePandaFlat.sf_btag0   * looseLepSF[0] * looseLepSF[1] * triggerWeights[0] * theMCPrescale * npvWeight;
        else	         totalWeight = thePandaFlat.normalizedWeight * lumi * puWeight * thePandaFlat.sf_l1Prefire * thePandaFlat.sf_btagGT0 * looseLepSF[0] * looseLepSF[1] * triggerWeights[0] * theMCPrescale * npvWeight;

        if     (infileCat_[ifile] == kPlotWZ)                                                totalWeight = totalWeight * thePandaFlat.sf_wz;
	else if(infileCat_[ifile] == kPlotZZ && infileName_[ifile].Contains("qqZZ") == true) totalWeight = totalWeight * thePandaFlat.sf_zz;
	else if(infileCat_[ifile] == kPlotDY && year == 2016) totalWeight = totalWeight * 1.00;
	else if(infileCat_[ifile] == kPlotDY && year == 2017) totalWeight = totalWeight * 1.00;
	else if(infileCat_[ifile] == kPlotEM && passBtagVeto) totalWeight = totalWeight * 1.35;

        if     (infileCat_[ifile] == kPlotDY && year == 2016 && lepType == 0) totalWeight = totalWeight * (1.09180-ptFrac*0.104392);
        else if(infileCat_[ifile] == kPlotDY && year == 2016 && lepType == 1) totalWeight = totalWeight * (1.15117-ptFrac*0.141021);
        //else if(infileCat_[ifile] == kPlotDY && year == 2017 && lepType == 0) totalWeight = totalWeight * (1.15115-ptFrac*0.391765);
        //else if(infileCat_[ifile] == kPlotDY && year == 2017 && lepType == 1) totalWeight = totalWeight * (1.07009-ptFrac*0.351426);
	
	if(infileCat_[ifile] == kPlotBSM && infileName_[ifile].Contains("qqZH") == true){
	  sf_EWKZH     = thePandaFlat.sf_vh;
	  sf_EWKZHUp   = thePandaFlat.sf_vhUp;
	  sf_EWKZHDown = thePandaFlat.sf_vhDown;
	}
	totalWeight = totalWeight * sf_EWKZH;
      }

      if(usePureMC == false && countLeptonTight != idLep.size()){
        double fakeSF = 1.0;
        for(unsigned int nl=0; nl<idLep.size(); nl++){
          if(idLep[nl] == 1) continue;
          bool applyTight = false;
          fakeSF = fakeSF * fakeRateFactor(TMath::Min((double)looseLepPt[nl],44.999),TMath::Abs(looseLepEta[nl]),TMath::Abs(looseLepPdgId[nl]),applyTight,histoFakeEffSelMediumEtaPt_m,histoFakeEffSelMediumEtaPt_e,histoFakeEffSelTightEtaPt_m,histoFakeEffSelTightEtaPt_e);
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
      if(passAllCuts[ZHSEL])      histo[lepType+  3][theCategory]->Fill(TMath::Min(vMet.Pt(),269.999),totalWeight);
      if(passAllCuts[BTAGSEL])    histo[lepType+  6][theCategory]->Fill(TMath::Min(vMet.Pt(),299.999),totalWeight);
      if(passAllCuts[ZLLSEL])     histo[lepType+  9][theCategory]->Fill(TMath::Min(vMet.Pt(),299.999),totalWeight);
      if(passAllCuts[WWSEL])      histo[lepType+ 12][theCategory]->Fill(TMath::Min(vMet.Pt(),299.999),totalWeight);
      if(passNMinusOne[ 0])       histo[lepType+ 15][theCategory]->Fill(TMath::Min(TMath::Abs(mllZ-91.1876),99.999),totalWeight);
      if(passNMinusOne[ 1])       histo[lepType+ 18][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJot,4.4999),totalWeight);
      if(passNMinusOne[ 2])       histo[lepType+ 21][theCategory]->Fill(TMath::Min(vMet.Pt(),199.999),totalWeight);
      if(passNMinusOne[ 3])       histo[lepType+ 24][theCategory]->Fill(TMath::Min(ptFrac,0.999),totalWeight);
      if(passNMinusOne[ 4])       histo[lepType+ 27][theCategory]->Fill(dPhiDiLepMET,totalWeight);
      if(passNMinusOne[ 5])       histo[lepType+ 30][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNBtags,3.499),totalWeight);
      if(passNMinusOne[ 6])       histo[lepType+ 33][theCategory]->Fill(TMath::Min(dilep.Pt(),249.999),totalWeight);
      if(passNMinusOne[ 7])       histo[lepType+ 36][theCategory]->Fill(dPhiJetMET,totalWeight);
      if(passNMinusOne[ 8])       histo[lepType+ 39][theCategory]->Fill(TMath::Min((double)thePandaFlat.nTau,3.499),totalWeight);
      if(passNMinusOne[ 9])       histo[lepType+ 42][theCategory]->Fill(TMath::Min((double)drll,3.999),totalWeight);
      for(int i=0; i<10; i++) {passCutEvolAll = passCutEvolAll && passCutEvol[i]; if(passCutEvolAll) histo[lepType+45][theCategory]->Fill((double)i,totalWeight);}
      if((passNMinusOne[ 1] ||
          passNMinusOne[ 7]) &&
	  thePandaFlat.nJot >= 1) histo[lepType+ 48][theCategory]->Fill(thePandaFlat.jotEta[0],totalWeight);
      if(passNMinusOne[1] || passNMinusOne[7]) histo[lepType+ 51][theCategory]->Fill(dPhiLepMETMin,totalWeight);
      if(passNMinusOne[1] || passNMinusOne[7]) histo[lepType+ 54][theCategory]->Fill(dPhiLepTrackMETMin,totalWeight);
      if(passNMinusOne[1] || passNMinusOne[7]) histo[lepType+ 57][theCategory]->Fill(dPhiMETTrackMETMin,totalWeight);
      if(passAllCuts[PRESEL])	  histo[lepType+ 60][theCategory]->Fill(TMath::Min(vMet.Pt(),199.999),totalWeight);
      if(passAllCuts[PRESEL])	  histo[lepType+ 63][theCategory]->Fill(TMath::Min(ptFrac,0.999),totalWeight);
      if(passAllCuts[PRESEL])	  histo[lepType+ 66][theCategory]->Fill(dPhiDiLepMET,totalWeight);
      if(passAllCuts[PRESEL])	  histo[lepType+ 69][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNBtags,3.499),totalWeight);

      //double MVAVar = TMath::Min(vMet.Pt(),xbins[nBinMVA]-0.0001); double MVAVarUp = TMath::Min(vMetUp.Pt(),xbins[nBinMVA]-0.0001); double MVAVarDown = TMath::Min(vMetDown.Pt(),xbins[nBinMVA]-0.0001);
      double MVAVar = TMath::Min(vMet.Pt(),metMax); double MVAVarUp = TMath::Min(vMetUp.Pt(),metMax); double MVAVarDown = TMath::Min(vMetDown.Pt(),metMax);
      if     (lepType == 2) {MVAVar = 0.5; MVAVarUp = 0.5; MVAVarDown = 0.5; }
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
            histo_BTAGBBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0BUp  /thePandaFlat.sf_btag0);
            histo_BTAGBBoundingDown[theCategory]->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0BDown/thePandaFlat.sf_btag0);
            histo_BTAGLBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0MUp  /thePandaFlat.sf_btag0);
            histo_BTAGLBoundingDown[theCategory]->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0MDown/thePandaFlat.sf_btag0);
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
          if(passSystCuts[JESUP])  histo_JESBoundingUp  [theCategory]->Fill(MVAVarUp  ,totalWeight);
          if(passSystCuts[JESDOWN])histo_JESBoundingDown[theCategory]->Fill(MVAVarDown,totalWeight);
          if(passSystCuts[METUP])  histo_METBoundingUp  [theCategory]->Fill(MVAVar    ,totalWeight);
          if(passSystCuts[METDOWN])histo_METBoundingDown[theCategory]->Fill(MVAVar    ,totalWeight);
        }
      }

    } // end events loop
    the_input_file->Close();
  } // end chain loop

  for(int ic=0; ic<nPlotCategories; ic++) histo[allPlots-1][ic]->Add(histo_Baseline[ic]);

  double qcdScaleTotal[2] = {0.035, 0.231};
  double pdfTotal[2] = {0.016, 0.051};
  double lumiE = 1.023; if(year == 2016) lumiE = 1.025;
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

      histo_Baseline              [ic]->SetBinContent(nb, TMath::Max((float)histo_Baseline		[ic]->GetBinContent(nb),1e-7f));
      histo_QCDScaleUp  	  [ic]->SetBinContent(nb, TMath::Max((float)histo_QCDScaleUp		[ic]->GetBinContent(nb),1e-7f));
      histo_QCDScaleDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_QCDScaleDown  	[ic]->GetBinContent(nb),1e-7f));
      histo_PDFBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PDFBoundingUp 	[ic]->GetBinContent(nb),1e-7f));
      histo_PDFBoundingDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PDFBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      histo_LepEffMBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_LepEffMBoundingUp	[ic]->GetBinContent(nb),1e-7f));
      histo_LepEffMBoundingDown   [ic]->SetBinContent(nb, TMath::Max((float)histo_LepEffMBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      histo_LepEffEBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_LepEffEBoundingUp	[ic]->GetBinContent(nb),1e-7f));
      histo_LepEffEBoundingDown   [ic]->SetBinContent(nb, TMath::Max((float)histo_LepEffEBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      histo_PUBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PUBoundingUp  	[ic]->GetBinContent(nb),1e-7f));
      histo_PUBoundingDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PUBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      histo_BTAGBBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_BTAGBBoundingUp	[ic]->GetBinContent(nb),1e-7f));
      histo_BTAGBBoundingDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_BTAGBBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      histo_BTAGLBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_BTAGLBoundingUp	[ic]->GetBinContent(nb),1e-7f));
      histo_BTAGLBoundingDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_BTAGLBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      histo_EWKCorrWZUp 	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKCorrWZUp		[ic]->GetBinContent(nb),1e-7f));
      histo_EWKCorrWZDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKCorrWZDown 	[ic]->GetBinContent(nb),1e-7f));
      histo_EWKqqZZCorrUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKqqZZCorrUp 	[ic]->GetBinContent(nb),1e-7f));
      histo_EWKqqZZCorrDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKqqZZCorrDown	[ic]->GetBinContent(nb),1e-7f));
      histo_ggZZCorrUp  	  [ic]->SetBinContent(nb, TMath::Max((float)histo_ggZZCorrUp		[ic]->GetBinContent(nb),1e-7f));
      histo_ggZZCorrDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_ggZZCorrDown  	[ic]->GetBinContent(nb),1e-7f));
      histo_CorrWZZZUp  	  [ic]->SetBinContent(nb, TMath::Max((float)histo_CorrWZZZUp		[ic]->GetBinContent(nb),1e-7f));
      histo_CorrWZZZDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_CorrWZZZDown  	[ic]->GetBinContent(nb),1e-7f));
      histo_EWKCorrZHUp 	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKCorrZHUp		[ic]->GetBinContent(nb),1e-7f));
      histo_EWKCorrZHDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKCorrZHDown 	[ic]->GetBinContent(nb),1e-7f));
      histo_JESBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_JESBoundingUp 	[ic]->GetBinContent(nb),1e-7f));
      histo_JESBoundingDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_JESBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      histo_METBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_METBoundingUp 	[ic]->GetBinContent(nb),1e-7f));
      histo_METBoundingDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_METBoundingDown	[ic]->GetBinContent(nb),1e-7f));
    }
    histo_PUBoundingUp	[ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_PUBoundingUp  [ic]->GetSumOfWeights());
    histo_PUBoundingDown[ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_PUBoundingDown[ic]->GetSumOfWeights());
    if(ic == kPlotWZ || ic == kPlotZZ || ic == kPlotBSM || ic == kPlotEM || ic == kPlotDY) {
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

    printf("uncertainties BTAGBUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_BTAGBBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties BTAGBDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_BTAGBBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties BTAGLUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_BTAGLBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties BTAGLDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_BTAGLBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
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

    printf("uncertainties JESUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_JESBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties JESDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_JESBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties METUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_METBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties METDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_METBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
  }

  // Filling datacards input root file
  char outputLimits[200];
  sprintf(outputLimits,"zh_%d_input.root",year);
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
    histo_BTAGBBoundingUp	[ic]->Write();
    histo_BTAGBBoundingDown	[ic]->Write();
    histo_BTAGLBoundingUp	[ic]->Write();
    histo_BTAGLBoundingDown	[ic]->Write();
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
    histo_JESBoundingUp 	[ic]->Write();
    histo_JESBoundingDown	[ic]->Write();
    histo_METBoundingUp 	[ic]->Write();
    histo_METBoundingDown	[ic]->Write();
  }
  outFileLimits->Close();


  // Filling datacards txt file
  char outputLimitsCard[200];  					  
  sprintf(outputLimitsCard,"datacard_zh_%d.txt",year);
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

  newcardShape << Form("lumi_13TeV    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("%6.3f ",lumiE);
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

  newcardShape << Form("CMS_trigger    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("%6.3f ",1.010);
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
          else       newcardShape << Form("-  ");
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

  newcardShape << Form("CMS_btagb    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_btagl    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_jes    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt || ic == kPlotDY) newcardShape << Form("- ");
    else                                      newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  //newcardShape << Form("CMS_met    shape     ");
  //for (int ic=0; ic<nPlotCategories; ic++){
  //  if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
  //  newcardShape << Form("1.0 ");
  //}
  //newcardShape << Form("\n");

  if(useZZWZEWKUnc == true){
    newcardShape << Form("CMS_hinv_vvnorm_bin_%d  rateParam * %s 1 [0.1,10]\n",year,plotBaseNames[kPlotZZ].Data());
    newcardShape << Form("CMS_hinv_vvnorm_bin_%d  rateParam * %s 1 [0.1,10]\n",year,plotBaseNames[kPlotWZ].Data());
  }
  newcardShape << Form("CMS_hinv_emnorm_bin_%d  rateParam * %s 1 [0.1,10]\n",year,plotBaseNames[kPlotEM].Data());
  newcardShape << Form("CMS_hinv_dynorm_bin_%d  rateParam * %s 1 [0.1,10]\n",year,plotBaseNames[kPlotDY].Data());

  newcardShape << Form("ch1 autoMCStats 0\n");

  newcardShape.close();

  // Writing standard histograms
  char output[200];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    sprintf(output,"histoZH_%d_%d.root",year,thePlot);	
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    double totBck = 0;
    for(int i=1; i<nPlotCategories; i++) if(i != kPlotBSM) totBck = totBck + histo[thePlot][i]->GetSumOfWeights();
    printf("(%2d) %7.1f vs. %7.1f ",thePlot,histo[thePlot][0]->GetSumOfWeights(),totBck);
    printf("(");
    for(int i=1; i<nPlotCategories; i++) printf("%7.1f ",histo[thePlot][i]->GetSumOfWeights());
    printf(")\n");
    for(int np=0; np<nPlotCategories; np++) histo[thePlot][np]->Write();
    outFilePlotsNote->Close();
  }

}
