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

const bool showSyst = true;
const double mcPrescale = 1;
const bool usePureMC = false; // if true, passLooseLepId not applied

enum systType                     {JESUP=0, JESDOWN,  METUP,  METDOWN, nSystTypes};
TString systTypeName[nSystTypes]= {"JESUP","JESDOWN","METUP","METDOWN"};

void wzAnalysis(
int year, TString WZName = "default"
){

  //*******************************************************
  //Inputs
  //*******************************************************
  vector<TString> infileName_;
  vector<int> infileCat_;

  double lumi;
  TString filesPath;
  TString fLepton_FakesName;
  TString puPath;
  if(year == 2017) {
    lumi = 41.5;
    filesPath = "/data/t3home000/ceballos/panda/v_004_0/";
    fLepton_FakesName = "MitAnalysisRunII/data/90x/histoFakeEtaPt_2017.root";
    puPath = "MitAnalysisRunII/data/90x/puWeights_90x.root";

    if(WZName == "default"){
      infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	             infileCat_.push_back(kPlotData);
      if(usePureMC == true){
	infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	             infileCat_.push_back(kPlotNonPrompt);
	infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	             infileCat_.push_back(kPlotNonPrompt);
	infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		     infileCat_.push_back(kPlotNonPrompt);
	infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		     infileCat_.push_back(kPlotNonPrompt);
	infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data())); infileCat_.push_back(kPlotNonPrompt);
	infileName_.push_back(Form("%sDYJetsToLL_M-50_LO.root",filesPath.Data()));   infileCat_.push_back(kPlotNonPrompt);
	infileName_.push_back(Form("%sWZno3l.root" ,filesPath.Data()));	             infileCat_.push_back(kPlotNonPrompt);
      }
      infileName_.push_back(Form("%sVG.root" ,filesPath.Data())); 		     infileCat_.push_back(kPlotVG);
      infileName_.push_back(Form("%sWZ3l_powheg_mll1.root" ,filesPath.Data()));      infileCat_.push_back(kPlotWZ);
      infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data()));	             infileCat_.push_back(kPlotZZ);
      infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data()));	             infileCat_.push_back(kPlotZZ);
      infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));	             infileCat_.push_back(kPlotVVV);
      infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));	             infileCat_.push_back(kPlotVVV);
      infileName_.push_back(Form("%sTTVV.root" ,filesPath.Data()));	             infileCat_.push_back(kPlotVVV);
      infileName_.push_back(Form("%sH125.root" ,filesPath.Data()));	             infileCat_.push_back(kPlotHiggs);
    } 
    else if(WZName == "WZ3l_powheg"){
      infileName_.push_back(Form("%sWZ3l_powheg.root" ,filesPath.Data()));           infileCat_.push_back(kPlotWZ);
    }
    else if(WZName == "WZ3l_amcnlo"){
      infileName_.push_back(Form("%sWZ3l_amcnlo.root" ,filesPath.Data()));           infileCat_.push_back(kPlotWZ);
    }
    else if(WZName == "WZ3l_powheg_mll1"){
      infileName_.push_back(Form("%sWZ3l_powheg_mll1.root" ,filesPath.Data()));      infileCat_.push_back(kPlotWZ);
    }
    else if(WZName == "WZ3l_MG"){
      infileName_.push_back(Form("%sWZ3l_MG_QCD.root" ,filesPath.Data()));           infileCat_.push_back(kPlotWZ);
    }
    else {
      printf("Wrong WZName (%s), exit\n",WZName.Data());
      return;
    }
  }
  else if(year == 2016) {
    lumi = 35.9;
    filesPath = "/data/t3home000/ceballos/panda/v_002_0/";
    fLepton_FakesName = "MitAnalysisRunII/data/90x/histoFakeEtaPt_2016.root";
    puPath = "MitAnalysisRunII/data/80x/puWeights_80x_37ifb.root";

    if(WZName == "WZ3l_powheg"){
      infileName_.push_back(Form("%sWZ.root" ,filesPath.Data()));                     infileCat_.push_back(kPlotWZ);
      infileName_.push_back(Form("%sWGstar.root" ,filesPath.Data()));                 infileCat_.push_back(kPlotWZ);
    }
    else if(WZName == "WZ3l_MG"){
      infileName_.push_back(Form("%sWZ3l_MG_QCD.root" ,filesPath.Data()));            infileCat_.push_back(kPlotWZ);
    }
    else {
      infileName_.push_back(Form("%sdata.root",filesPath.Data()));		      infileCat_.push_back(kPlotData);
      if(usePureMC == true){
	infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data()));		      infileCat_.push_back(kPlotNonPrompt);
	infileName_.push_back(Form("%sggWW.root" ,filesPath.Data()));		      infileCat_.push_back(kPlotNonPrompt);
	infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		      infileCat_.push_back(kPlotNonPrompt);
	infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		      infileCat_.push_back(kPlotNonPrompt);
	infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data()));  infileCat_.push_back(kPlotNonPrompt);
	infileName_.push_back(Form("%sDYJetsToLL_Pt0To50.root",filesPath.Data()));    infileCat_.push_back(kPlotNonPrompt);
	infileName_.push_back(Form("%sDYJetsToLL_Pt50To100.root",filesPath.Data()));  infileCat_.push_back(kPlotNonPrompt);
	infileName_.push_back(Form("%sDYJetsToLL_Pt100To250.root",filesPath.Data())); infileCat_.push_back(kPlotNonPrompt);
	infileName_.push_back(Form("%sDYJetsToLL_Pt250To400.root",filesPath.Data())); infileCat_.push_back(kPlotNonPrompt);
	infileName_.push_back(Form("%sDYJetsToLL_Pt400To650.root",filesPath.Data())); infileCat_.push_back(kPlotNonPrompt);
	infileName_.push_back(Form("%sDYJetsToLL_Pt650ToInf.root",filesPath.Data())); infileCat_.push_back(kPlotNonPrompt);
      }
      infileName_.push_back(Form("%sVG.root" ,filesPath.Data())); 		      infileCat_.push_back(kPlotVG);
      infileName_.push_back(Form("%sWZ.root" ,filesPath.Data()));                     infileCat_.push_back(kPlotWZ);
      infileName_.push_back(Form("%sWGstar.root" ,filesPath.Data()));                 infileCat_.push_back(kPlotWZ);
      infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data()));		      infileCat_.push_back(kPlotZZ);
      infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data()));		      infileCat_.push_back(kPlotZZ);
      infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));		      infileCat_.push_back(kPlotVVV);
      infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));		      infileCat_.push_back(kPlotVVV);
      infileName_.push_back(Form("%sH125.root" ,filesPath.Data()));		      infileCat_.push_back(kPlotHiggs);
    }
  }
  else {
    return;
  }

  TFile *fLepton_Fakes = TFile::Open(fLepton_FakesName.Data());
  TH2D* histoFakeEffSelMediumEtaPt_m = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_0_0"); histoFakeEffSelMediumEtaPt_m->SetDirectory(0);
  TH2D* histoFakeEffSelMediumEtaPt_e = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_0_1"); histoFakeEffSelMediumEtaPt_e->SetDirectory(0);

  //TH2D* histoFakeEffSelTightEtaPt_m = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_2_0"); histoFakeEffSelTightEtaPt_m ->SetDirectory(0);
  //TH2D* histoFakeEffSelTightEtaPt_e = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_2_1"); histoFakeEffSelTightEtaPt_e ->SetDirectory(0);
  TH2D* histoFakeEffSelTightEtaPt_m = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_0_0");;
  if	 (year == 2016) {histoFakeEffSelTightEtaPt_m = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_2_0");  printf("2016 tight mu sel\n");}
  else if(year == 2017) {histoFakeEffSelTightEtaPt_m = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_13_0"); printf("2017 tight mu sel\n");}
  histoFakeEffSelTightEtaPt_m ->SetDirectory(0);
  TH2D* histoFakeEffSelTightEtaPt_e  = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_6_1"); histoFakeEffSelTightEtaPt_e ->SetDirectory(0);

  fLepton_Fakes->Close();

  TFile *fPUFile = TFile::Open(Form("%s",puPath.Data()));
  TH1D *fhDPU     = (TH1D*)(fPUFile->Get("puWeights"));     assert(fhDPU);     fhDPU    ->SetDirectory(0);
  TH1D *fhDPUUp   = (TH1D*)(fPUFile->Get("puWeightsUp"));   assert(fhDPUUp);   fhDPUUp  ->SetDirectory(0);
  TH1D *fhDPUDown = (TH1D*)(fPUFile->Get("puWeightsDown")); assert(fhDPUDown); fhDPUDown->SetDirectory(0);
  delete fPUFile;

  const int nBinMVA = 10; Float_t xbins[nBinMVA+1] = {100, 125, 150, 175, 200, 250, 300, 350, 400, 500, 600};

  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 74;
  TH1D* histo[allPlots][nPlotCategories];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    if     (thePlot >=  0 && thePlot <=  9) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 100;}
    else if(thePlot >= 10 && thePlot <= 44) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >= 45 && thePlot <= 59) {nBinPlot =   5; xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >= 60 && thePlot <= 69) {nBinPlot =  50; xminPlot =100.0; xmaxPlot = 300;}
    else if(thePlot >= 70 && thePlot <= 70) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = TMath::Pi();}
    else if(thePlot >= 71 && thePlot <= 71) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 1.0;}
    else if(thePlot >= 72 && thePlot <= 72) {nBinPlot =  30; xminPlot =  0.0; xmaxPlot = 3.0;}
    TH1D* histos;
    if(thePlot == allPlots-1) histos = new TH1D("histos", "histos", nBinMVA, xbins);
    else                      histos = new TH1D("histos", "histos", nBinPlot, xminPlot, xmaxPlot);
    histos->Sumw2();
    for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = (TH1D*) histos->Clone(Form("histo%d",i));
    histos->Reset();histos->Clear();
  }

  TH1D* histoWZSelEvol = new TH1D("histoWZSelEvol", "histoWZSelEvol", 16, -0.5, 15.5);

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
      if (infileCat_[ifile] != kPlotData && jentry%(int)theMCPrescale != 0) continue;

      if(infileCat_[ifile] == kPlotWZ) histoWZSelEvol->Fill(0.,thePandaFlat.normalizedWeight * lumi);
      bool passTrigger = (thePandaFlat.trigger & (1<<kEMuTrig)) != 0       || (thePandaFlat.trigger & (1<<kDoubleMuTrig)) != 0  ||
                         (thePandaFlat.trigger & (1<<kSingleMuTrig)) != 0  || (thePandaFlat.trigger & (1<<kDoubleEleTrig)) != 0 ||
                         (thePandaFlat.trigger & (1<<kSingleEleTrig)) != 0;
      if(passTrigger == false) continue;
      if(thePandaFlat.metFilter == 0) continue;
      if(infileCat_[ifile] == kPlotWZ) histoWZSelEvol->Fill(1.,thePandaFlat.normalizedWeight * lumi);

      if(thePandaFlat.nLooseLep != 3) continue;
      if(infileCat_[ifile] == kPlotWZ) histoWZSelEvol->Fill(2.,thePandaFlat.normalizedWeight * lumi);

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

      if(TMath::Abs(looseLepEta[0]) >= 2.4 || TMath::Abs(looseLepEta[1]) >= 2.4 || TMath::Abs(looseLepEta[2]) >= 2.4) continue;
      if(infileCat_[ifile] == kPlotWZ) histoWZSelEvol->Fill(3.,thePandaFlat.normalizedWeight * lumi);

      if(!(ptSelCuts[0] >= 1 && ptSelCuts[1] >= 2 && ptSelCuts[2] >= 3)) continue;
      if(infileCat_[ifile] == kPlotWZ) histoWZSelEvol->Fill(4.,thePandaFlat.normalizedWeight * lumi);

      int theCategory = infileCat_[ifile];
      bool isNotMCFake = thePandaFlat.looseGenLep1PdgId != 0 && thePandaFlat.looseGenLep2PdgId != 0 && thePandaFlat.looseGenLep3PdgId != 0;
      if(theCategory != kPlotData && theCategory != kPlotVG && isNotMCFake == false && usePureMC == false) continue;
      if(infileCat_[ifile] == kPlotWZ) histoWZSelEvol->Fill(5.,thePandaFlat.normalizedWeight * lumi);

      bool passLooseLepId = ((looseLepSelBit[0] & kFake) == kFake) && ((looseLepSelBit[1] & kFake) == kFake) && ((looseLepSelBit[2] & kFake) == kFake);
      if(passLooseLepId == false && usePureMC == false) continue;
      if(infileCat_[ifile] == kPlotWZ) histoWZSelEvol->Fill(6.,thePandaFlat.normalizedWeight * lumi);

      vector<int> idLep;
      unsigned int countLeptonTight = 0;
      for(int i=0; i<thePandaFlat.nLooseLep; i++) {
        idLep.push_back(0);
        if     (abs(looseLepPdgId[i])==13 && (looseLepSelBit[i] & kMedium) == kMedium) idLep[i] = 1;
        else if(abs(looseLepPdgId[i])==11 && (looseLepSelBit[i] & kMedium) == kMedium) idLep[i] = 1;
	countLeptonTight = countLeptonTight + (idLep[i] > 0);
      }

      int qTot = abs(looseLepPdgId[0])/looseLepPdgId[0] + abs(looseLepPdgId[1])/looseLepPdgId[1] + abs(looseLepPdgId[2])/looseLepPdgId[2];
      if(abs(qTot) != 1) continue;
      if(infileCat_[ifile] == kPlotWZ) histoWZSelEvol->Fill(7.,thePandaFlat.normalizedWeight * lumi);

      int lepType = -1; double muSFUnc = 1.0; double elSFUnc = 1.0;
      if     (abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13 && abs(looseLepPdgId[2])==13) {lepType = 0; muSFUnc = 1.015*1.015*1.015;}
      else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11 && abs(looseLepPdgId[2])==11) {lepType = 3; elSFUnc = 1.015*1.015*1.015;}
      else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11) {lepType = 1; muSFUnc = 1.015; elSFUnc = 1.015*1.015;}
      else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[2])==11) {lepType = 1; muSFUnc = 1.015; elSFUnc = 1.015*1.015;}
      else if(abs(looseLepPdgId[1])==11 && abs(looseLepPdgId[2])==11) {lepType = 1; muSFUnc = 1.015; elSFUnc = 1.015*1.015;}
      else if(abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13) {lepType = 2; muSFUnc = 1.015*1.015; elSFUnc = 1.015;}
      else if(abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[2])==13) {lepType = 2; muSFUnc = 1.015*1.015; elSFUnc = 1.015;}
      else if(abs(looseLepPdgId[1])==13 && abs(looseLepPdgId[2])==13) {lepType = 2; muSFUnc = 1.015*1.015; elSFUnc = 1.015;}
      else {printf("Impossible dilepton combination: %d %d %d\n",looseLepPdgId[0],looseLepPdgId[1],looseLepPdgId[2]); continue;}

      double mllZ = 10000; double mllmin = 10000;
      TLorentzVector vLoose1,vLoose2,vLoose3,vMet,vMetUp,vMetDown;
      TLorentzVector vZl1,vZl2,vWln;
      vMet.SetPtEtaPhiM(thePandaFlat.pfmet,0.0,thePandaFlat.pfmetphi,0.0);
      vMetUp  .SetPtEtaPhiM(thePandaFlat.pfmet_JESTotalUp  ,0.0,thePandaFlat.pfmetphi_JESTotalUp  ,0.0);
      vMetDown.SetPtEtaPhiM(thePandaFlat.pfmet_JESTotalDown,0.0,thePandaFlat.pfmetphi_JESTotalDown,0.0);
      double thePDGMass[3] = {mass_mu, mass_mu, mass_mu};
      if(abs(looseLepPdgId[0])==11) thePDGMass[0] = mass_el;
      if(abs(looseLepPdgId[1])==11) thePDGMass[1] = mass_el;
      if(abs(looseLepPdgId[2])==11) thePDGMass[2] = mass_el;
      vLoose1.SetPtEtaPhiM(looseLepPt[0],looseLepEta[0],looseLepPhi[0],thePDGMass[0]);
      vLoose2.SetPtEtaPhiM(looseLepPt[1],looseLepEta[1],looseLepPhi[1],thePDGMass[1]);
      vLoose3.SetPtEtaPhiM(looseLepPt[2],looseLepEta[2],looseLepPhi[2],thePDGMass[2]);

      bool tightWlnId = false; int whichWln = -1;
      if(abs(looseLepPdgId[0]) == abs(looseLepPdgId[1]) && looseLepPdgId[0] != looseLepPdgId[1]) {
        if((vLoose1+vLoose2).M() < mllmin) mllmin = (vLoose1+vLoose2).M();
        if(fabs((vLoose1+vLoose2).M()-91.1876) < fabs(mllZ-91.1876)) {
	  mllZ = (vLoose1+vLoose2).M();
	  vZl1 = vLoose1;
	  vZl2 = vLoose2;
	  vWln = vLoose3;
	  //tightWlnId = (looseLepSelBit[2] & kTight) == kTight && (looseLepSelBit[2] & kDxyz) == kDxyz;
	  if	 (abs(looseLepPdgId[2])==13 && year == 2016) tightWlnId = (looseLepSelBit[2] & kTight) == kTight && (looseLepSelBit[2] & kDxyz) == kDxyz;
	  else if(abs(looseLepPdgId[2])==13 && year == 2017) tightWlnId = (looseLepSelBit[2] & kMvaTight) == kMvaTight && (looseLepSelBit[2] & kMiniIsoTight) == kMiniIsoTight;
	  else  					     tightWlnId = (looseLepSelBit[2] & kEleMvaWP80) == kEleMvaWP80;
	  whichWln = 2;
	}
      }
      if(abs(looseLepPdgId[0]) == abs(looseLepPdgId[2]) && looseLepPdgId[0] != looseLepPdgId[2]) {
        if((vLoose1+vLoose3).M() < mllmin) mllmin = (vLoose1+vLoose3).M();
        if(fabs((vLoose1+vLoose3).M()-91.1876) < fabs(mllZ-91.1876)) {
          mllZ = (vLoose1+vLoose3).M();
	  vZl1 = vLoose1;
	  vZl2 = vLoose3;
	  vWln = vLoose2;
	  //tightWlnId = (looseLepSelBit[1] & kTight) == kTight && (looseLepSelBit[1] & kDxyz) == kDxyz;
	  if	 (abs(looseLepPdgId[1])==13 && year == 2016) tightWlnId = (looseLepSelBit[1] & kTight) == kTight && (looseLepSelBit[1] & kDxyz) == kDxyz;
	  else if(abs(looseLepPdgId[1])==13 && year == 2017) tightWlnId = (looseLepSelBit[1] & kMvaTight) == kMvaTight && (looseLepSelBit[1] & kMiniIsoTight) == kMiniIsoTight;
	  else  					     tightWlnId = (looseLepSelBit[1] & kEleMvaWP80) == kEleMvaWP80;
	  whichWln = 1;
	}
      }
      if(abs(looseLepPdgId[1]) == abs(looseLepPdgId[2]) && looseLepPdgId[1] != looseLepPdgId[2]) {
        if((vLoose2+vLoose3).M() < mllmin) mllmin = (vLoose2+vLoose3).M();
        if(fabs((vLoose2+vLoose3).M()-91.1876) < fabs(mllZ-91.1876)) {
          mllZ = (vLoose2+vLoose3).M();
	  vZl1 = vLoose2;
	  vZl2 = vLoose3;
	  vWln = vLoose1;
	  //tightWlnId = (looseLepSelBit[0] & kTight) == kTight && (looseLepSelBit[0] & kDxyz) == kDxyz;
	  if	 (abs(looseLepPdgId[0])==13 && year == 2016) tightWlnId = (looseLepSelBit[0] & kTight) == kTight && (looseLepSelBit[0] & kDxyz) == kDxyz;
	  else if(abs(looseLepPdgId[0])==13 && year == 2017) tightWlnId = (looseLepSelBit[0] & kMvaTight) == kMvaTight && (looseLepSelBit[0] & kMiniIsoTight) == kMiniIsoTight;
	  else  					     tightWlnId = (looseLepSelBit[0] & kEleMvaWP80) == kEleMvaWP80;
	  whichWln = 0;
	}
      }
      if(whichWln == -1) continue;
      if(tightWlnId == false && idLep[whichWln] == 1) {countLeptonTight = countLeptonTight - 1; idLep[whichWln] = 0;};

      if(infileCat_[ifile] == kPlotWZ) histoWZSelEvol->Fill(8.,thePandaFlat.normalizedWeight * lumi);

      if(usePureMC == true && countLeptonTight != idLep.size()) continue;
      if(infileCat_[ifile] == kPlotWZ && countLeptonTight == idLep.size()) histoWZSelEvol->Fill(9.,thePandaFlat.normalizedWeight * lumi);

      bool passBtagVeto = thePandaFlat.jetNMBtags == 0;

      bool passSel[6] = {mllmin > 4, fabs(mllZ-91.1876) < 15, vWln.Pt() > 20, vMet.Pt() > 30, (vLoose1+vLoose2+vLoose3).M() > 100, passBtagVeto};
      bool passWZSel  = passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[4] &&  passSel[5];
      bool passTopSel = passSel[0] && passSel[1] && passSel[2]               && passSel[4] && !passSel[5];
      bool passAllButOneSel[6] = {
                      passSel[1] && passSel[2] && passSel[3] && passSel[4] && passSel[5],
        passSel[0] &&               passSel[2] && passSel[3] && passSel[4] && passSel[5],
        passSel[0] && passSel[1] &&               passSel[3] && passSel[4] && passSel[5],
        passSel[0] && passSel[1] && passSel[2] &&               passSel[4] && passSel[5],
        passSel[0] && passSel[1] && passSel[2] && passSel[3] &&               passSel[5],
        passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[4]
      };

      if(infileCat_[ifile] == kPlotWZ && countLeptonTight == idLep.size() && passSel[0]) histoWZSelEvol->Fill(10.,thePandaFlat.normalizedWeight * lumi);
      if(infileCat_[ifile] == kPlotWZ && countLeptonTight == idLep.size() && passSel[0] && passSel[1]) histoWZSelEvol->Fill(11.,thePandaFlat.normalizedWeight * lumi);
      if(infileCat_[ifile] == kPlotWZ && countLeptonTight == idLep.size() && passSel[0] && passSel[1] && passSel[2]) histoWZSelEvol->Fill(12.,thePandaFlat.normalizedWeight * lumi);
      if(infileCat_[ifile] == kPlotWZ && countLeptonTight == idLep.size() && passSel[0] && passSel[1] && passSel[2] && passSel[3]) histoWZSelEvol->Fill(13.,thePandaFlat.normalizedWeight * lumi);
      if(infileCat_[ifile] == kPlotWZ && countLeptonTight == idLep.size() && passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[4]) histoWZSelEvol->Fill(14.,thePandaFlat.normalizedWeight * lumi);
      if(infileCat_[ifile] == kPlotWZ && countLeptonTight == idLep.size() && passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[4] && passSel[5]) histoWZSelEvol->Fill(15.,thePandaFlat.normalizedWeight * lumi);

      double deltaPhiLeptonMet = TMath::Abs(vWln.DeltaPhi(vMet));
      double mt = TMath::Sqrt(2.0*vWln.Pt()*vMet.Pt()*(1.0 - cos(deltaPhiLeptonMet)));

      // ZXLike selection
      TLorentzVector vMetZXLike = vMet + vWln; TLorentzVector vMetZXLikeUp = vMetUp + vWln; TLorentzVector vMetZXLikeDown = vMetDown + vWln;
      TLorentzVector dilep = vZl1 + vZl2;

      bool passMET = vMetZXLike.Pt() > 100; bool passMETUp = vMetZXLikeUp.Pt() > 100;  bool passMETDown = vMetZXLikeDown.Pt() > 100;

      bool passPTLL = dilep.Pt() > 60;
      double ptFrac = TMath::Abs(dilep.Pt()-vMetZXLike.Pt())/dilep.Pt(); double ptFracUp = TMath::Abs(dilep.Pt()-vMetZXLikeUp.Pt())/dilep.Pt(); double ptFracDown = TMath::Abs(dilep.Pt()-vMetZXLikeDown.Pt())/dilep.Pt();
      bool passPTFrac = ptFrac < 0.4; bool passPTFracUp = ptFracUp < 0.4; bool passPTFracDown = ptFracDown < 0.4;

      double dPhiDiLepMET = TMath::Abs(dilep.DeltaPhi(vMetZXLike)); double dPhiDiLepMETUp = TMath::Abs(dilep.DeltaPhi(vMetZXLikeUp)); double dPhiDiLepMETDown = TMath::Abs(dilep.DeltaPhi(vMetZXLikeDown));
      bool passDPhiZMET = dPhiDiLepMET > 2.5; bool passDPhiZMETUp = dPhiDiLepMETUp > 2.5; bool passDPhiZMETDown = dPhiDiLepMETDown > 2.5;

      bool passNjets = thePandaFlat.nJot <= 2;
      bool passNjetsUp = thePandaFlat.nJot_JESTotalUp <= 2;
      bool passNjetsDown = thePandaFlat.nJot_JESTotalDown <= 2;

      double dphill = TMath::Abs(vZl1.DeltaPhi(vZl2));
      double detall = TMath::Abs(vZl1.Eta()-vZl2.Eta());
      double drll = sqrt(dphill*dphill+detall*detall);
      bool passDRLL = drll < 1.8;

      bool passZXLikeSel      = passWZSel && passNjets && passMET && passPTFrac && passDPhiZMET && passPTLL && passDRLL;
      bool passZXLooseLikeSel = passWZSel && passNjets && passMET && passPTFrac && passDPhiZMET && passPTLL && passDRLL;

      bool passSystCuts[nSystTypes] = {                   
      passWZSel && passNjetsUp   && passMETUp	&& passPTFracUp    && passDPhiZMETUp   && passPTLL && passDRLL,
      passWZSel && passNjetsDown && passMETDown && passPTFracDown  && passDPhiZMETDown && passPTLL && passDRLL,
      passWZSel && passNjets     && passMET     && passPTFrac      && passDPhiZMET     && passPTLL && passDRLL,
      passWZSel && passNjets     && passMET     && passPTFrac      && passDPhiZMET     && passPTLL && passDRLL
                                    };

      double totalWeight = 1.0; double puWeight = 1.0; double puWeightUp = 1.0; double puWeightDown = 1.0;
      if(theCategory != kPlotData){
	puWeight     = nPUScaleFactor(fhDPU,    thePandaFlat.pu);
        puWeightUp   = nPUScaleFactor(fhDPUUp,  thePandaFlat.pu);
        puWeightDown = nPUScaleFactor(fhDPUDown,thePandaFlat.pu);

        if(passBtagVeto) totalWeight = thePandaFlat.normalizedWeight * lumi * puWeight * thePandaFlat.sf_l1Prefire * thePandaFlat.sf_btag0   * looseLepSF[0] * looseLepSF[1] * looseLepSF[2];
        else             totalWeight = thePandaFlat.normalizedWeight * lumi * puWeight * thePandaFlat.sf_l1Prefire * thePandaFlat.sf_btagGT0 * looseLepSF[0] * looseLepSF[1] * looseLepSF[2];

        if     (infileCat_[ifile] == kPlotWZ)                                                totalWeight = totalWeight * thePandaFlat.sf_wz;
	else if(infileCat_[ifile] == kPlotZZ && infileName_[ifile].Contains("qqZZ") == true) totalWeight = totalWeight * thePandaFlat.sf_zz;
      }

      if(usePureMC == false && countLeptonTight != idLep.size()){
        double fakeSF = 1.0;
        for(unsigned int nl=0; nl<idLep.size(); nl++){
          if(idLep[nl] == 1) continue;
          bool applyTight = false;
          if(whichWln == (int)nl) applyTight = true;
          fakeSF = fakeSF * fakeRateFactor(TMath::Min((double)looseLepPt[nl],44.999),TMath::Abs(looseLepEta[nl]),TMath::Abs(looseLepPdgId[nl]),applyTight,histoFakeEffSelMediumEtaPt_m,histoFakeEffSelMediumEtaPt_e,histoFakeEffSelTightEtaPt_m,histoFakeEffSelTightEtaPt_e);
          theCategory = kPlotNonPrompt;
        }
        if     (infileCat_[ifile] != kPlotData && countLeptonTight == idLep.size()-3) fakeSF = -1.0 * fakeSF; // triple fake, MC
        else if(infileCat_[ifile] != kPlotData && countLeptonTight == idLep.size()-2) fakeSF = +1.0 * fakeSF; // double fake, MC
        else if(infileCat_[ifile] != kPlotData && countLeptonTight == idLep.size()-1) fakeSF = -1.0 * fakeSF; // single fake, MC
        else if(infileCat_[ifile] == kPlotData && countLeptonTight == idLep.size()-3) fakeSF = +1.0 * fakeSF; // triple fake, data
        else if(infileCat_[ifile] == kPlotData && countLeptonTight == idLep.size()-2) fakeSF = -1.0 * fakeSF; // double fake, data
        else if(infileCat_[ifile] == kPlotData && countLeptonTight == idLep.size()-1) fakeSF = +1.0 * fakeSF; // single fake, data
        else printf("IMPOSSIBLE FAKE OPTION\n");
        totalWeight = totalWeight * fakeSF;
      }

      if(passAllButOneSel[0]){histo[lepType+ 0][theCategory]->Fill(TMath::Min(mllmin,99.999),totalWeight);                        histo[ 4][theCategory]->Fill(TMath::Min(mllmin,99.999),totalWeight);}
      if(passAllButOneSel[1]){histo[lepType+ 5][theCategory]->Fill(TMath::Min(fabs(mllZ-91.1876),99.999),totalWeight);            histo[ 9][theCategory]->Fill(TMath::Min(fabs(mllZ-91.1876),99.999),totalWeight);}
      if(passAllButOneSel[2]){histo[lepType+10][theCategory]->Fill(TMath::Min(vWln.Pt(),199.999),totalWeight);                    histo[14][theCategory]->Fill(TMath::Min(vWln.Pt(),199.999),totalWeight);}
      if(passAllButOneSel[3]){histo[lepType+15][theCategory]->Fill(TMath::Min(vMet.Pt(),199.999),totalWeight);			  histo[19][theCategory]->Fill(TMath::Min(vMet.Pt(),199.999),totalWeight);}
      if(passAllButOneSel[4]){histo[lepType+20][theCategory]->Fill(TMath::Min((vLoose1+vLoose2+vLoose3).M(),199.999),totalWeight);histo[24][theCategory]->Fill(TMath::Min((vLoose1+vLoose2+vLoose3).M(),199.999),totalWeight);}
      if(passWZSel)          {histo[lepType+25][theCategory]->Fill(TMath::Min(vZl1.Pt(),199.999),totalWeight);                    histo[29][theCategory]->Fill(TMath::Min(vZl1.Pt(),199.999),totalWeight);}
      if(passWZSel)          {histo[lepType+30][theCategory]->Fill(TMath::Min(vZl2.Pt(),199.999),totalWeight);                    histo[34][theCategory]->Fill(TMath::Min(vZl2.Pt(),199.999),totalWeight);}
      if(passWZSel)          {histo[lepType+35][theCategory]->Fill(TMath::Min(mt,199.999),totalWeight);                           histo[39][theCategory]->Fill(TMath::Min(mt,199.999),totalWeight);}
      if(passTopSel)         {histo[lepType+40][theCategory]->Fill(TMath::Min(vMet.Pt(),199.999),totalWeight);			  histo[44][theCategory]->Fill(TMath::Min(vMet.Pt(),199.999),totalWeight);}
      if(passWZSel)          {histo[lepType+45][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJot,4.499),totalWeight);      histo[49][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJot,4.499),totalWeight);}
      if(passTopSel)         {histo[lepType+50][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJot,4.499),totalWeight);      histo[54][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJot,4.499),totalWeight);}
      if(passAllButOneSel[5]){histo[lepType+55][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNMBtags,4.499),totalWeight);histo[59][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNMBtags,4.499),totalWeight);}
      if(passZXLikeSel)      {histo[lepType+60][theCategory]->Fill(TMath::Min(vMetZXLike.Pt(),299.999),totalWeight);		  histo[64][theCategory]->Fill(TMath::Min(vMetZXLike.Pt(),299.999),totalWeight);}
      if(passZXLooseLikeSel) {histo[lepType+65][theCategory]->Fill(TMath::Min(vMetZXLike.Pt(),299.999),totalWeight);		  histo[69][theCategory]->Fill(TMath::Min(vMetZXLike.Pt(),299.999),totalWeight);}
      if(passWZSel && passNjets && passMET) {histo[70][theCategory]->Fill(TMath::Abs(dilep.DeltaPhi(vMetZXLike)),totalWeight);}
      if(passWZSel && passNjets && passMET) {histo[71][theCategory]->Fill(TMath::Min(TMath::Abs(dilep.Pt()-vMetZXLike.Pt())/dilep.Pt(),0.999),totalWeight);}
      if(passWZSel && passNjets && passMET) {histo[72][theCategory]->Fill(TMath::Min(drll,2.99),totalWeight);}

      double MVAVar = TMath::Min(vMetZXLike.Pt(),xbins[nBinMVA]-0.0001); double MVAVarUp = TMath::Min(vMetZXLikeUp.Pt(),xbins[nBinMVA]-0.0001); double MVAVarDown = TMath::Min(vMetZXLikeDown.Pt(),xbins[nBinMVA]-0.0001);
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

        if     (theCategory == kPlotData && passZXLooseLikeSel){
          histo_Baseline[theCategory]->Fill(MVAVar,totalWeight);
        }
        else if(theCategory != kPlotData){
	  if(passZXLooseLikeSel) {
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
      histo_JESBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_JESBoundingUp 	[ic]->GetBinContent(nb),1e-7f));
      histo_JESBoundingDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_JESBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      histo_METBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_METBoundingUp 	[ic]->GetBinContent(nb),1e-7f));
      histo_METBoundingDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_METBoundingDown	[ic]->GetBinContent(nb),1e-7f));
    }
    histo_PUBoundingUp	[ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_PUBoundingUp  [ic]->GetSumOfWeights());
    histo_PUBoundingDown[ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_PUBoundingDown[ic]->GetSumOfWeights());
    if(ic == kPlotWZ || ic == kPlotZZ || ic == kPlotBSM) {
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
  sprintf(outputLimits,"wz_%d_input.root",year);
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
    histo_JESBoundingUp 	[ic]->Write();
    histo_JESBoundingDown	[ic]->Write();
    histo_METBoundingUp 	[ic]->Write();
    histo_METBoundingDown	[ic]->Write();
  }
  outFileLimits->Close();


  // Filling datacards txt file
  char outputLimitsCard[200];  					  
  sprintf(outputLimitsCard,"datacard_wz_%d.txt",year);
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

  newcardShape << Form("CMS_fake    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("1.2 ");
    else                     newcardShape << Form("- ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("lumi_13TeV    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("%6.3f ",lumiE);
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

  newcardShape << Form("CMS_trigger    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("%6.3f ",1.010);
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

  newcardShape << Form("CMS_pu    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_btagb    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_btagl    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
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
  //  if(ic == kPlotNonPrompt) newcardShape << Form("- ");
  //  else                     newcardShape << Form("1.0 ");
  //}
  //newcardShape << Form("\n");

  if(useZZWZEWKUnc == true){
    newcardShape << Form("CMS_hinv_vvnorm_bin_%d  rateParam * %s 1 [0.1,10]\n",year,plotBaseNames[kPlotZZ].Data());
    newcardShape << Form("CMS_hinv_vvnorm_bin_%d  rateParam * %s 1 [0.1,10]\n",year,plotBaseNames[kPlotWZ].Data());
  }

  newcardShape << Form("ch1 autoMCStats 0\n");

  newcardShape.close();

  char output[200];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    sprintf(output,"histoWZ_%d_%d.root",year,thePlot);	
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    double totBck = 0;
    for(int i=1; i<nPlotCategories; i++) totBck = totBck + histo[thePlot][i]->GetSumOfWeights();
    printf("(%2d) %7.1f vs. %7.1f ",thePlot,histo[thePlot][0]->GetSumOfWeights(),totBck);
    printf("(");
    for(int i=1; i<nPlotCategories; i++) printf("%7.1f ",histo[thePlot][i]->GetSumOfWeights());
    printf(")\n");
    for(int np=0; np<nPlotCategories; np++) histo[thePlot][np]->Write();
    outFilePlotsNote->Close();
  }
  {
    sprintf(output,"histoWZSelEvol_%d.root",year);	
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    histoWZSelEvol->Write();
    outFilePlotsNote->Close();
  }

}
