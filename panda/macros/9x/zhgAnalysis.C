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
enum selType                     { ZHGSEL,   BTAGSEL,   ZLGSEL,   WZSEL,   WZGSEL,   ZZSEL,   WWSEL, nSelTypes};
TString selTypeName[nSelTypes]=  {"ZHGSEL", "BTAGSEL", "ZLGSEL", "WZSEL", "WZGSEL", "ZZSEL", "WWSEL"};
enum systType                     {JESUP=0, JESDOWN,  METUP,  METDOWN, nSystTypes};
TString systTypeName[nSystTypes]= {"JESUP","JESDOWN","METUP","METDOWN"};

void zhgAnalysis(
int year
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
  TString photonSFPath;
  if(year == 2017) {
    lumi = 41.5;
    filesPath = "/data/t3home000/ceballos/panda/v_004_0/";
    fLepton_FakesName = "MitAnalysisRunII/data/90x/histoFakeEtaPt_2017.root";
    puPath = "MitAnalysisRunII/data/90x/puWeights_90x.root";
    photonSFPath = "MitAnalysisRunII/data/90x/egammaEffi.txt_EGM2D_runBCDEF_passingMedium94X.root";

    infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	         infileCat_.push_back(kPlotData);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		 infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		         infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data())); infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sDYNJetsToLL_NLO.root",filesPath.Data()));      infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));		         infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sWZ3l_powheg_mll1.root" ,filesPath.Data()));    infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTVV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sZH_ZToLL_HToGDarkG_M125.root" ,filesPath.Data())); infileCat_.push_back(kPlotBSM);
  }
  else if(year == 2016) {
    lumi = 35.9;
    filesPath = "/data/t3home000/ceballos/panda/v_002_0/";
    fLepton_FakesName = "MitAnalysisRunII/data/90x/histoFakeEtaPt_2016.root";
    puPath = "MitAnalysisRunII/data/80x/puWeights_80x_37ifb.root";
    photonSFPath = "MitAnalysisRunII/data/80x/photon_scalefactors_37ifb.root";

    infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	          infileCat_.push_back(kPlotData);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		          infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data()));  infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sDYJetsToLL_Pt0To50.root",filesPath.Data()));    infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sDYJetsToLL_Pt50To100.root",filesPath.Data()));  infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sDYJetsToLL_Pt100To250.root",filesPath.Data())); infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sDYJetsToLL_Pt250To400.root",filesPath.Data())); infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sDYJetsToLL_Pt400To650.root",filesPath.Data())); infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sDYJetsToLL_Pt650ToInf.root",filesPath.Data())); infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));		          infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sWZ.root" ,filesPath.Data()));	                  infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sWGstar.root" ,filesPath.Data()));               infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sZH_ZToLL_HToGDarkG_M125.root" ,filesPath.Data())); infileCat_.push_back(kPlotBSM);
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

  TFile *fPhotonSF = TFile::Open(photonSFPath.Data());
  TH2D *fhDPhotonSF       = (TH2D*)(fPhotonSF->Get("EGamma_SF2D")); assert(fhDPhotonSF); fhDPhotonSF->SetDirectory(0);
  TH2D *fhDElectronVetoSF = (TH2D*)(fPhotonSF->Get("Scaling_Factors_HasPix_R9 Inclusive")); assert(fhDElectronVetoSF); fhDElectronVetoSF->SetDirectory(0);
  delete fPhotonSF;

  const int MVAVarType = 0; const int nBinMVA = 6; Double_t xbins[nBinMVA+1] = {-10, 0, 75, 100, 125, 150, 175}; TString addChan = "";

  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 37;
  TH1D* histo[allPlots][nPlotCategories];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    if     (thePlot >=   0 && thePlot <=  23) {nBinPlot = 175; xminPlot =  0.0; xmaxPlot = 175;}
    else if(thePlot >=  24 && thePlot <=  24) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 100;}
    else if(thePlot >=  25 && thePlot <=  25) {nBinPlot = 5;   xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >=  26 && thePlot <=  26) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >=  27 && thePlot <=  27) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 2;}
    else if(thePlot >=  28 && thePlot <=  28) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = TMath::Pi();}
    else if(thePlot >=  29 && thePlot <=  29) {nBinPlot = 4;   xminPlot = -0.5; xmaxPlot = 3.5;}
    else if(thePlot >=  30 && thePlot <=  30) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >=  31 && thePlot <=  31) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = TMath::Pi();}
    else if(thePlot >=  32 && thePlot <=  32) {nBinPlot = 4;   xminPlot = -0.5; xmaxPlot = 3.5;}
    else if(thePlot >=  33 && thePlot <=  33) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 400;}
    else if(thePlot >=  34 && thePlot <=  34) {nBinPlot = 50;  xminPlot =  0.0; xmaxPlot = 2.5;}
    else if(thePlot >=  35 && thePlot <=  35) {nBinPlot = 2;   xminPlot = -0.5; xmaxPlot = 1.5;}
    TH1D* histos;
    if(thePlot == allPlots-1) histos = new TH1D("histos", "histos", nBinMVA, xbins);
    else                      histos = new TH1D("histos", "histos", nBinPlot, xminPlot, xmaxPlot);
    histos->Sumw2();
    for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = (TH1D*) histos->Clone(Form("histo%d",i));
    histos->Reset();histos->Clear();
  }

  TH1D* histoZHGSelEvol = new TH1D("histoZHGSelEvol", "histoZHGSelEvol", 18, -0.5, 17.5);

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
  TH1D *histo_PhoEffBoundingUp[nPlotCategories];
  TH1D *histo_PhoEffBoundingDown[nPlotCategories];
  TH1D *histo_ElToPhRateBoundingUp[nPlotCategories];
  TH1D *histo_ElToPhRateBoundingDown[nPlotCategories];
  TH1D *histo_EWKCorrWZUp[nPlotCategories];
  TH1D *histo_EWKCorrWZDown[nPlotCategories];
  TH1D *histo_EWKqqZZCorrUp[nPlotCategories];
  TH1D *histo_EWKqqZZCorrDown[nPlotCategories];
  TH1D *histo_ggZZCorrUp[nPlotCategories];
  TH1D *histo_ggZZCorrDown[nPlotCategories];
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
    histo_PhoEffBoundingUp	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_eff_photonUp"   , plotBaseNames[ic].Data()));
    histo_PhoEffBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_eff_photonDown" , plotBaseNames[ic].Data()));
    histo_ElToPhRateBoundingUp	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fake_elUp"      , plotBaseNames[ic].Data()));
    histo_ElToPhRateBoundingDown[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fake_elDown"    , plotBaseNames[ic].Data()));
    histo_EWKCorrWZUp		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKWZCorrUp"        , plotBaseNames[ic].Data()));
    histo_EWKCorrWZDown 	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKWZCorrDown"      , plotBaseNames[ic].Data()));
    histo_EWKqqZZCorrUp 	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKqqZZCorrUp"      , plotBaseNames[ic].Data()));
    histo_EWKqqZZCorrDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKqqZZCorrDown"    , plotBaseNames[ic].Data()));
    histo_ggZZCorrUp		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_ggZZCorrUp"         , plotBaseNames[ic].Data()));
    histo_ggZZCorrDown		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_ggZZCorrDown"       , plotBaseNames[ic].Data()));
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

      if(infileCat_[ifile] == kPlotWZ) histoZHGSelEvol->Fill(0.,thePandaFlat.normalizedWeight * lumi);
      bool passTrigger = (thePandaFlat.trigger & (1<<kEMuTrig)) != 0       || (thePandaFlat.trigger & (1<<kDoubleMuTrig)) != 0  ||
                         (thePandaFlat.trigger & (1<<kSingleMuTrig)) != 0  || (thePandaFlat.trigger & (1<<kDoubleEleTrig)) != 0 ||
                         (thePandaFlat.trigger & (1<<kSingleEleTrig)) != 0;
      if(passTrigger == false) continue;
      if(thePandaFlat.metFilter == 0) continue;
      if(infileCat_[ifile] == kPlotWZ) histoZHGSelEvol->Fill(1.,thePandaFlat.normalizedWeight * lumi);

      if(thePandaFlat.nLooseLep < 2 || thePandaFlat.nLooseLep > 4) continue;

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
      if(infileCat_[ifile] == kPlotWZ) histoZHGSelEvol->Fill(2.,thePandaFlat.normalizedWeight * lumi);

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
        if((looseLepSelBit[i] & kMedium) == kMedium) idLep[i] = 1;
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
      if(infileCat_[ifile] == kPlotWZ) histoZHGSelEvol->Fill(3.,thePandaFlat.normalizedWeight * lumi);

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
        else {printf("Impossible dilepton combination: %d %d %d\n",looseLepPdgId[0],looseLepPdgId[1],looseLepPdgId[2]); continue;}
      }
      else if(thePandaFlat.nLooseLep == 4){
        int nmu = (abs(looseLepPdgId[0])==13) + (abs(looseLepPdgId[1])==13) + (abs(looseLepPdgId[2])==13) + (abs(looseLepPdgId[3])==13);
        int nel = (abs(looseLepPdgId[0])==11) + (abs(looseLepPdgId[1])==11) + (abs(looseLepPdgId[2])==11) + (abs(looseLepPdgId[3])==11);
        if     (nmu == 4 && nel == 0) {lepType = 0; muSFUnc = 1.015*1.015*1.015*1.015;}
        else if(nmu == 0 && nel == 4) {lepType = 1; elSFUnc = 1.015*1.015*1.015*1.015;}
        else if(nmu == 2 && nel == 2) {lepType = 2; muSFUnc = 1.015*1.015; elSFUnc = 1.015*1.015;}
        else if(nmu == 3 && nel == 1) {lepType = 3; muSFUnc = 1.015*1.015*1.015; elSFUnc = 1.015;}
        else if(nmu == 1 && nel == 3) {lepType = 3; muSFUnc = 1.015; elSFUnc = 1.015*1.015*1.015;}
        else {printf("Impossible dilepton combination: %d %d %d %d\n",looseLepPdgId[0],looseLepPdgId[1],looseLepPdgId[2],looseLepPdgId[3]); continue;}
      }

      TLorentzVector vMET,vTrkMet,vMETUp,vMETDown;
      vMET.SetPtEtaPhiM(thePandaFlat.pfmet,0.0,thePandaFlat.pfmetphi,0.0);
      vTrkMet.SetPtEtaPhiM(thePandaFlat.trkmet,0.0,thePandaFlat.trkmetphi,0.0);
      vMETUp  .SetPtEtaPhiM(thePandaFlat.pfmet_JESTotalUp  ,0.0,thePandaFlat.pfmetphi_JESTotalUp  ,0.0);
      vMETDown.SetPtEtaPhiM(thePandaFlat.pfmet_JESTotalDown,0.0,thePandaFlat.pfmetphi_JESTotalDown,0.0);

      double dPhiLepMETMin = 999; double dPhiLepTrackMETMin = 999;
      for(unsigned int i=0; i<vLoose.size(); i++){
        if(dPhiLepMETMin      > TMath::Abs(vLoose[i].DeltaPhi(vMET))   ) dPhiLepMETMin      = TMath::Abs(vLoose[i].DeltaPhi(vMET));
	if(dPhiLepTrackMETMin > TMath::Abs(vLoose[i].DeltaPhi(vTrkMet))) dPhiLepTrackMETMin = TMath::Abs(vLoose[i].DeltaPhi(vTrkMet));
      }

      double PMET[1] = {vMET.Pt()};
      double PTrackMET[1] = {vTrkMet.Pt()};
      if(dPhiLepMETMin < TMath::Pi()/2) {PMET[0] = PMET[0] * sin(dPhiLepMETMin);}
      if(dPhiLepTrackMETMin < TMath::Pi()/2) {PTrackMET[0] = PTrackMET[0] * sin(dPhiLepTrackMETMin);}
      double minPMET[1] = {TMath::Min(PMET[0],PTrackMET[0])};

      bool passPhoSel = thePandaFlat.loosePho1Pt > 25 && TMath::Abs(thePandaFlat.loosePho1Eta) < 2.5
             && (thePandaFlat.loosePho1SelBit & pMedium) == pMedium 
	     && (thePandaFlat.loosePho1SelBit & pCsafeVeto) == pCsafeVeto 
	     && (thePandaFlat.loosePho1SelBit & pPixelVeto) == pPixelVeto;
      TLorentzVector vPhoton;
      vPhoton.SetPtEtaPhiM(thePandaFlat.loosePho1Pt, thePandaFlat.loosePho1Eta, thePandaFlat.loosePho1Phi, 0);

      double mllZ = 10000; double mllmin = 10000;
      TLorentzVector vZ1l1,vZ1l2,vZ2l1,vZ2l2,vWln;
      bool tightWlnId = false; int whichWln = -1;
      if     (vLoose.size() == 2){
        vZ1l1  = vLoose[0];
        vZ1l2  = vLoose[1];
	mllZ   = (vLoose[0]+vLoose[1]).M();
	mllmin = (vLoose[0]+vLoose[1]).M();
      }
      else if(vLoose.size() == 3){
	if(abs(looseLepPdgId[0]) == abs(looseLepPdgId[1]) && looseLepPdgId[0] != looseLepPdgId[1]) {
          if((vLoose[0]+vLoose[1]).M() < mllmin) mllmin = (vLoose[0]+vLoose[1]).M();
          if(fabs((vLoose[0]+vLoose[1]).M()-91.1876) < fabs(mllZ-91.1876)) {
	    mllZ  = (vLoose[0]+vLoose[1]).M();
	    vZ1l1 = vLoose[0];
	    vZ1l2 = vLoose[1];
	    vWln  = vLoose[2];
	    tightWlnId = (looseLepSelBit[2] & kTight) == kTight && (looseLepSelBit[2] & kDxyz) == kDxyz;
	    whichWln = 2;
	  }
	}
	if(abs(looseLepPdgId[0]) == abs(looseLepPdgId[2]) && looseLepPdgId[0] != looseLepPdgId[2]) {
          if((vLoose[0]+vLoose[2]).M() < mllmin) mllmin = (vLoose[0]+vLoose[2]).M();
          if(fabs((vLoose[0]+vLoose[2]).M()-91.1876) < fabs(mllZ-91.1876)) {
            mllZ  = (vLoose[0]+vLoose[2]).M();
	    vZ1l1 = vLoose[0];
	    vZ1l2 = vLoose[2];
	    vWln  = vLoose[1];
	    tightWlnId = (looseLepSelBit[1] & kTight) == kTight && (looseLepSelBit[1] & kDxyz) == kDxyz;
	    whichWln = 1;
	  }
	}
	if(abs(looseLepPdgId[1]) == abs(looseLepPdgId[2]) && looseLepPdgId[1] != looseLepPdgId[2]) {
          if((vLoose[1]+vLoose[2]).M() < mllmin) mllmin = (vLoose[1]+vLoose[2]).M();
          if(fabs((vLoose[1]+vLoose[2]).M()-91.1876) < fabs(mllZ-91.1876)) {
            mllZ  = (vLoose[1]+vLoose[2]).M();
	    vZ1l1 = vLoose[1];
	    vZ1l2 = vLoose[2];
	    vWln  = vLoose[0];
	    tightWlnId = (looseLepSelBit[0] & kTight) == kTight && (looseLepSelBit[0] & kDxyz) == kDxyz;
	    whichWln = 0;
	  }
	}
        if(whichWln >= 0 && tightWlnId == false && idLep[whichWln] == 1) {countLeptonTight = countLeptonTight - 1; idLep[whichWln] = 0;};
      }
      else if(vLoose.size() == 4){
	if(abs(looseLepPdgId[0]) == abs(looseLepPdgId[1]) && looseLepPdgId[0] != looseLepPdgId[1]) {
          if((vLoose[0]+vLoose[1]).M() < mllmin) mllmin = (vLoose[0]+vLoose[1]).M();
          if(fabs((vLoose[0]+vLoose[1]).M()-91.1876) < fabs(mllZ-91.1876)) {
	    mllZ = (vLoose[0]+vLoose[1]).M();
	    vZ1l1 = vLoose[0];
	    vZ1l2 = vLoose[1];
	    vZ2l1 = vLoose[2];
	    vZ2l2 = vLoose[3];
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
	  }
	}
      }

      if(usePureMC == true && countLeptonTight != idLep.size()) continue; // It needs to be applied again
      if(infileCat_[ifile] == kPlotWZ) histoZHGSelEvol->Fill(4.,thePandaFlat.normalizedWeight * lumi);

      int theMinSelType = -1;
      TLorentzVector theG;
      if     (passPhoSel == true  && vLoose.size() == 2 && TMath::Abs(qTot) == 0){
        theMinSelType = 0;
        theG = vPhoton;
      }
      else if(passPhoSel == false && vLoose.size() == 3 && whichWln >= 0 && tightWlnId == true && TMath::Abs(qTot) == 1){       
        theMinSelType = 1;
        theG = vLoose[whichWln]; 
      }
      else if(passPhoSel == true  && vLoose.size() == 3 && whichWln >= 0 && tightWlnId == true && TMath::Abs(qTot) == 1){       
        theMinSelType = 2;
        vMET.SetPx(vMET.Px()+vLoose[whichWln].Px());
        vMET.SetPy(vMET.Py()+vLoose[whichWln].Px());
        theG = vPhoton;
      }
      else if(passPhoSel == false && vLoose.size() == 4 && vZ2l1.Pt() > 0 && vZ2l2.Pt() > 0 && TMath::Abs((vZ2l1 + vZ2l2).M()-91.1876) < 15.0 && TMath::Abs(qTot) == 0){     
        theMinSelType = 3;
        theG = vZ2l1 + vZ2l2;
      }

      if(theMinSelType == -1) continue;
      if(infileCat_[ifile] == kPlotWZ) histoZHGSelEvol->Fill(5.,thePandaFlat.normalizedWeight * lumi);

      double dPhiJetMET = -1.0;
      if(thePandaFlat.jotPt[0] > 30) {
        TLorentzVector vJetTemp;
        vJetTemp.SetPtEtaPhiM(thePandaFlat.jotPt[0],thePandaFlat.jotEta[0],thePandaFlat.jotPhi[0],0.0);
        dPhiJetMET = TMath::Abs(vJetTemp.DeltaPhi(vMET));
      }

      double dPhiGMET = 0; double dPhiGMETUp = 0;double dPhiGMETDown = 0;
      double mTGMET = 0;   double mTGMETUp = 0;  double mTGMETDown = 0;
      TLorentzVector dilep = vZ1l1+vZ1l2;
      TLorentzVector dilepG = vZ1l1+vZ1l2;
      if(theMinSelType >= 0){
        dilepG = dilepG + theG;
	dPhiGMET = TMath::Abs(theG.DeltaPhi(vMET));
	dPhiGMETUp = TMath::Abs(theG.DeltaPhi(vMETUp));
	dPhiGMETDown = TMath::Abs(theG.DeltaPhi(vMETDown));
        mTGMET = TMath::Sqrt(2.0*theG.Pt()*vMET.Pt()*(1.0 - cos(dPhiGMET)));
	dPhiGMETUp = TMath::Abs(theG.DeltaPhi(vMETUp));
        mTGMETUp = TMath::Sqrt(2.0*theG.Pt()*vMETUp.Pt()*(1.0 - cos(dPhiGMETUp)));
	dPhiGMETDown = TMath::Abs(theG.DeltaPhi(vMETDown));
        mTGMETDown = TMath::Sqrt(2.0*theG.Pt()*vMETDown.Pt()*(1.0 - cos(dPhiGMETDown)));
      }

      double dPhiDiLepGMET = TMath::Abs(dilepG.DeltaPhi(vMET)); double dPhiDiLepGMETUp = TMath::Abs(dilepG.DeltaPhi(vMETUp)); double dPhiDiLepGMETDown = TMath::Abs(dilepG.DeltaPhi(vMETDown));
      bool passZMass = mllmin > 4.0 && TMath::Abs(mllZ-91.1876) < 15.0;
      bool passZMassSB = mllZ > 110 && mllZ < 200;
      bool passMET    = vMET.Pt() > 110; bool passMETUp    = vMETUp.Pt() > 110; bool passMETDown    = vMETDown.Pt() > 110;
      bool passMETMin = vMET.Pt() > 60;  bool passMETMinUp = vMETUp.Pt() > 60;  bool passMETMinDown = vMETDown.Pt() > 60;
      bool passPTLL   = dilep.Pt() > 60;

      double ptFracG = TMath::Abs(dilepG.Pt()-vMET.Pt())/dilepG.Pt(); double ptFracGUp = TMath::Abs(dilepG.Pt()-vMETUp.Pt())/dilepG.Pt(); double ptFracGDown = TMath::Abs(dilepG.Pt()-vMETDown.Pt())/dilepG.Pt();
      bool passPTFracG = ptFracG < 0.4; bool passPTFracGUp = ptFracGUp < 0.4; bool passPTFracGDown = ptFracGDown < 0.4;
      bool passDPhiZGMET = dPhiDiLepGMET > 2.5; bool passDPhiZGMETUp = dPhiDiLepGMETUp > 2.5; bool passDPhiZGMETDown = dPhiDiLepGMETDown > 2.5;
      bool passNjets = thePandaFlat.nJot <= 2;
      bool passNjetsUp = thePandaFlat.nJot_JESTotalUp <= 2;
      bool passNjetsDown = thePandaFlat.nJot_JESTotalDown <= 2;

      bool passBtagVeto = thePandaFlat.jetNBtags == 0; bool passBtagVetoUp = thePandaFlat.jetNBtags_JESTotalUp == 0; bool passBtagVetoDown = thePandaFlat.jetNBtags_JESTotalDown == 0;
      double dphill = TMath::Abs(vZ1l1.DeltaPhi(vZ1l2));
      double detall = TMath::Abs(vZ1l1.Eta()-vZ1l2.Eta());
      double drll = sqrt(dphill*dphill+detall*detall);

      bool passDPhiJetMET   = dPhiJetMET == -1 || dPhiJetMET >= 0.5;
      bool passTauVeto      = thePandaFlat.nTau == 0;
      bool passMT = mTGMET < 175.0; bool passMTUp = mTGMETUp < 175.0; bool passMTDown = mTGMETDown < 175.0;

      if(isDEBUG && vLoose.size() == 4) printf("DEBUG %d %d %d %d %d %d %d %d %d %d %d | %f %f\n",theMinSelType,passZMass,passNjets,passMET,passPTFracG,passDPhiZGMET,passBtagVeto,passPTLL,passDPhiJetMET,passTauVeto,passMT,mllmin,TMath::Abs(mllZ-91.1876));

      bool passAllCuts[nSelTypes] = {                   
     theMinSelType == 0 && passZMass   && passNjets && passMET    && passPTFracG && passDPhiZGMET &&  passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT,   // ZHGSEL
     theMinSelType == 0 && passZMass   && passNjets && passMET    && passPTFracG && passDPhiZGMET && !passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT,   // BTAGSEL
     theMinSelType == 0 && passZMass   &&              passMET    &&                                                  passPTLL &&                   passTauVeto && passMT,   // ZLGSEL
     theMinSelType == 1 && passZMass   && passNjets && passMET    && passPTFracG && passDPhiZGMET &&  passBtagVeto && passPTLL && passDPhiJetMET &&                passMT,   // WZSEL
     theMinSelType == 2 && passZMass   && passNjets && passMET    && passPTFracG && passDPhiZGMET &&  passBtagVeto && passPTLL && passDPhiJetMET &&	           passMT,   // WZGSEL
     theMinSelType == 3 && passZMass   && passNjets && passMETMin && passPTFracG && passDPhiZGMET &&  passBtagVeto && passPTLL && passDPhiJetMET &&  	           passMT,   // ZZSEL
     theMinSelType == 0 && passZMassSB && passNjets && passMET    && passPTFracG && passDPhiZGMET &&  passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT    // WWSEL
                                    };

      bool passNMinusOne[10] = {
     		  passNjets && passMET && passPTFracG && passDPhiZGMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT,
     passZMass &&	       passMET && passPTFracG && passDPhiZGMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT,
     passZMass && passNjets &&  	  passPTFracG && passDPhiZGMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT,
     passZMass && passNjets && passMET &&		 passDPhiZGMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT,
     passZMass && passNjets && passMET && passPTFracG &&		  passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT,
     passZMass && passNjets && passMET && passPTFracG && passDPhiZGMET &&		  passPTLL && passDPhiJetMET && passTauVeto && passMT,
     passZMass && passNjets && passMET && passPTFracG && passDPhiZGMET && passBtagVeto &&	      passDPhiJetMET && passTauVeto && passMT,
     passZMass && passNjets && passMET && passPTFracG && passDPhiZGMET && passBtagVeto && passPTLL &&			passTauVeto && passMT,
     passZMass && passNjets && passMET && passPTFracG && passDPhiZGMET && passBtagVeto && passPTLL && passDPhiJetMET && 	       passMT,
     passZMass && passNjets && passMET && passPTFracG && passDPhiZGMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto
                                    };

      bool passSystCuts[nSystTypes] = {                   
     theMinSelType == 0 && passZMass   && passNjetsUp	&& passMETUp   && passPTFracGUp   && passDPhiZGMETUp   &&  passBtagVetoUp   && passPTLL && passDPhiJetMET && passTauVeto && passMTUp,
     theMinSelType == 0 && passZMass   && passNjetsDown && passMETDown && passPTFracGDown && passDPhiZGMETDown &&  passBtagVetoDown && passPTLL && passDPhiJetMET && passTauVeto && passMTDown,
     theMinSelType == 0 && passZMass   && passNjets     && passMET     && passPTFracG     && passDPhiZGMET     &&  passBtagVeto     && passPTLL && passDPhiJetMET && passTauVeto && passMT,
     theMinSelType == 0 && passZMass   && passNjets     && passMET     && passPTFracG     && passDPhiZGMET     &&  passBtagVeto     && passPTLL && passDPhiJetMET && passTauVeto && passMT
                                    };
      for(int i=0; i<10; i++) passNMinusOne[i] = mllmin > 4.0 && theMinSelType == 0 && lepType != 2 && passNMinusOne[i];

      if(infileCat_[ifile] == kPlotWZ && countLeptonTight == idLep.size()) histoZHGSelEvol->Fill(6.,thePandaFlat.normalizedWeight * lumi);
      if(infileCat_[ifile] == kPlotWZ && countLeptonTight == idLep.size() && theMinSelType == 0) histoZHGSelEvol->Fill(7.,thePandaFlat.normalizedWeight * lumi);
      if(infileCat_[ifile] == kPlotWZ && countLeptonTight == idLep.size() && theMinSelType == 0 && passZMass) histoZHGSelEvol->Fill(8.,thePandaFlat.normalizedWeight * lumi);
      if(infileCat_[ifile] == kPlotWZ && countLeptonTight == idLep.size() && theMinSelType == 0 && passZMass   && passNjets) histoZHGSelEvol->Fill(9.,thePandaFlat.normalizedWeight * lumi);
      if(infileCat_[ifile] == kPlotWZ && countLeptonTight == idLep.size() && theMinSelType == 0 && passZMass   && passNjets && passMET) histoZHGSelEvol->Fill(10.,thePandaFlat.normalizedWeight * lumi);
      if(infileCat_[ifile] == kPlotWZ && countLeptonTight == idLep.size() && theMinSelType == 0 && passZMass   && passNjets && passMET    && passPTFracG) histoZHGSelEvol->Fill(11.,thePandaFlat.normalizedWeight * lumi);
      if(infileCat_[ifile] == kPlotWZ && countLeptonTight == idLep.size() && theMinSelType == 0 && passZMass   && passNjets && passMET    && passPTFracG && passDPhiZGMET) histoZHGSelEvol->Fill(12.,thePandaFlat.normalizedWeight * lumi);
      if(infileCat_[ifile] == kPlotWZ && countLeptonTight == idLep.size() && theMinSelType == 0 && passZMass   && passNjets && passMET    && passPTFracG && passDPhiZGMET &&  passBtagVeto) histoZHGSelEvol->Fill(13.,thePandaFlat.normalizedWeight * lumi);
      if(infileCat_[ifile] == kPlotWZ && countLeptonTight == idLep.size() && theMinSelType == 0 && passZMass   && passNjets && passMET    && passPTFracG && passDPhiZGMET &&  passBtagVeto && passPTLL) histoZHGSelEvol->Fill(14.,thePandaFlat.normalizedWeight * lumi);
      if(infileCat_[ifile] == kPlotWZ && countLeptonTight == idLep.size() && theMinSelType == 0 && passZMass   && passNjets && passMET    && passPTFracG && passDPhiZGMET &&  passBtagVeto && passPTLL && passDPhiJetMET) histoZHGSelEvol->Fill(15.,thePandaFlat.normalizedWeight * lumi);
      if(infileCat_[ifile] == kPlotWZ && countLeptonTight == idLep.size() && theMinSelType == 0 && passZMass   && passNjets && passMET    && passPTFracG && passDPhiZGMET &&  passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto) histoZHGSelEvol->Fill(16.,thePandaFlat.normalizedWeight * lumi);
      if(infileCat_[ifile] == kPlotWZ && countLeptonTight == idLep.size() && theMinSelType == 0 && passZMass   && passNjets && passMET    && passPTFracG && passDPhiZGMET &&  passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT) histoZHGSelEvol->Fill(17.,thePandaFlat.normalizedWeight * lumi);

      double photonSFUnc[2] = {1.0, 1.0};
      double totalWeight = 1.0; double puWeight = 1.0; double puWeightUp = 1.0; double puWeightDown = 1.0;
      if(theCategory != kPlotData){
        double triggerWeights[2] = {1.0, 0.0};
	if(thePandaFlat.nLooseLep == 2) {
          trigger_sf(triggerWeights, trgEff, trgEffE, lepType, looseLepPt[0], TMath::Abs(looseLepEta[0]), looseLepPt[1], TMath::Abs(looseLepEta[1]));
        }
	puWeight     = nPUScaleFactor(fhDPU,    thePandaFlat.pu);
        puWeightUp   = nPUScaleFactor(fhDPUUp,  thePandaFlat.pu);
        puWeightDown = nPUScaleFactor(fhDPUDown,thePandaFlat.pu);

        if(infileCat_[ifile] == kPlotBSM) {puWeight = 1.0; puWeightUp = 1.0; puWeightDown = 1.0;} // TEMPORAL UNTIL WE GET OFFICIAL PRODUCTION

        if(passBtagVeto) totalWeight = thePandaFlat.normalizedWeight * lumi * puWeight * thePandaFlat.sf_l1Prefire * looseLepSF[0] * looseLepSF[1] * triggerWeights[0] * thePandaFlat.sf_btag0   * theMCPrescale;
        else             totalWeight = thePandaFlat.normalizedWeight * lumi * puWeight * thePandaFlat.sf_l1Prefire * looseLepSF[0] * looseLepSF[1] * triggerWeights[0] * thePandaFlat.sf_btagGT0 * theMCPrescale;

        if     (infileCat_[ifile] == kPlotWZ)                                                totalWeight = totalWeight * thePandaFlat.sf_wz;
	else if(infileCat_[ifile] == kPlotZZ && infileName_[ifile].Contains("qqZZ") == true) totalWeight = totalWeight * thePandaFlat.sf_zz;

	if(passPhoSel == true) {
          double photonSF = 1.0;
          if     (thePandaFlat.looseGenPho1PdgId == 1) {
            photonSF = electronToPhotonSF(vPhoton.Pt()); photonSFUnc[1] = 1.10;
	  }
          else if(thePandaFlat.looseGenPho1PdgId == 3) {
            photonSF = effhDPhotonScaleFactor(vPhoton.Pt(), vPhoton.Eta(), "medium", fhDPhotonSF, fhDElectronVetoSF); photonSFUnc[0] = 1.02;
	  }
	  totalWeight = totalWeight * photonSF;
	}

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

      if(passAllCuts[ZHGSEL])histo[lepType+  0][theCategory]->Fill(TMath::Min(mTGMET,199.999),totalWeight);
      if(passAllCuts[BTAGSEL])histo[lepType+ 3][theCategory]->Fill(TMath::Min(mTGMET,199.999),totalWeight);
      if(passAllCuts[ZLGSEL])histo[lepType+  6][theCategory]->Fill(TMath::Min(mTGMET,199.999),totalWeight);
      if(passAllCuts[WZSEL])histo[lepType+   9][theCategory]->Fill(TMath::Min(mTGMET,199.999),totalWeight);
      if(passAllCuts[WZGSEL])histo[lepType+ 13][theCategory]->Fill(TMath::Min(mTGMET,199.999),totalWeight);
      if(passAllCuts[ZZSEL])histo[lepType+  17][theCategory]->Fill(TMath::Min(mTGMET,199.999),totalWeight);
      if(passAllCuts[WWSEL])histo[lepType+  21][theCategory]->Fill(TMath::Min(mTGMET,199.999),totalWeight);
      if(passNMinusOne[ 0])  histo[24][theCategory]->Fill(TMath::Min(TMath::Abs(mllZ-91.1876),99.999),totalWeight);
      if(passNMinusOne[ 1])  histo[25][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJot,4.4999),totalWeight);
      if(passNMinusOne[ 2])  histo[26][theCategory]->Fill(TMath::Min(vMET.Pt(),199.999),totalWeight);
      if(passNMinusOne[ 3])  histo[27][theCategory]->Fill(TMath::Min(ptFracG,1.999),totalWeight);
      if(passNMinusOne[ 4])  histo[28][theCategory]->Fill(dPhiDiLepGMET,totalWeight);
      if(passNMinusOne[ 5])  histo[29][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNBtags,3.499),totalWeight);
      if(passNMinusOne[ 6])  histo[30][theCategory]->Fill(TMath::Min(dilep.Pt(),199.999),totalWeight);
      if(passNMinusOne[ 7])  histo[31][theCategory]->Fill(dPhiJetMET,totalWeight);
      if(passNMinusOne[ 8])  histo[32][theCategory]->Fill(TMath::Min((double)thePandaFlat.nTau,3.499),totalWeight);
      if(passNMinusOne[ 9])  histo[33][theCategory]->Fill(TMath::Min(mTGMET,399.999),totalWeight);
      if(passAllCuts[ZHGSEL] && lepType != 2) histo[34][theCategory]->Fill(TMath::Abs(theG.Eta()),totalWeight);
      if(passAllCuts[ZHGSEL] && lepType != 2) histo[35][theCategory]->Fill((double)((thePandaFlat.loosePho1SelBit & pTrkVeto) == pTrkVeto),totalWeight);

      if(1){
        double MVAVar     = TMath::Min(mTGMET    ,xbins[nBinMVA]-0.0001);
        double MVAVarUp   = TMath::Min(mTGMETUp  ,xbins[nBinMVA]-0.0001);
        double MVAVarDown = TMath::Min(mTGMETDown,xbins[nBinMVA]-0.0001);
        if(lepType == 2) {MVAVar = -0.5; MVAVarUp = -0.5; MVAVarDown = -0.5; }

        // Avoid QCD scale weights that are anomalous high
        double maxQCDscale = (TMath::Abs(thePandaFlat.scale[0])+TMath::Abs(thePandaFlat.scale[1])+TMath::Abs(thePandaFlat.scale[2])+
	                      TMath::Abs(thePandaFlat.scale[3])+TMath::Abs(thePandaFlat.scale[4])+TMath::Abs(thePandaFlat.scale[5]))/6.0;
        if(maxQCDscale == 0) maxQCDscale = 1;

        double sf_ewkcorrwz_unc = 1.0; double sf_ewkcorrzz_unc = 1.0; double sf_ggcorrzz_unc = 1.0;
	if(theCategory == kPlotWZ) sf_ewkcorrwz_unc = 1.02;
	if     (theCategory == kPlotZZ && infileName_[ifile].Contains("qqZZ") == true) sf_ewkcorrzz_unc = thePandaFlat.sf_zzUnc;
	else if(theCategory == kPlotZZ) sf_ggcorrzz_unc = 1.10;

        if     (theCategory == kPlotData && passAllCuts[ZHGSEL]){
          histo_Baseline[theCategory]->Fill(MVAVar,totalWeight);
        }
        else if(theCategory != kPlotData){
	  if(passAllCuts[ZHGSEL]) {
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
	    histo_PhoEffBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*photonSFUnc[0]);
	    histo_PhoEffBoundingDown[theCategory]->Fill(MVAVar,totalWeight/photonSFUnc[0]);
	    histo_ElToPhRateBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*photonSFUnc[1]);
	    histo_ElToPhRateBoundingDown[theCategory]->Fill(MVAVar,totalWeight/photonSFUnc[1]);
	    histo_EWKCorrWZUp  [theCategory]->Fill(MVAVar,totalWeight*sf_ewkcorrwz_unc);
	    histo_EWKCorrWZDown[theCategory]->Fill(MVAVar,totalWeight/sf_ewkcorrwz_unc);
	    histo_EWKqqZZCorrUp  [theCategory]->Fill(MVAVar,totalWeight*sf_ewkcorrzz_unc);
	    histo_EWKqqZZCorrDown[theCategory]->Fill(MVAVar,totalWeight/sf_ewkcorrzz_unc);
	    histo_ggZZCorrUp  [theCategory]->Fill(MVAVar,totalWeight*sf_ggcorrzz_unc);
	    histo_ggZZCorrDown[theCategory]->Fill(MVAVar,totalWeight/sf_ggcorrzz_unc);
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
      histo_PhoEffBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PhoEffBoundingUp	[ic]->GetBinContent(nb),1e-7f));
      histo_PhoEffBoundingDown    [ic]->SetBinContent(nb, TMath::Max((float)histo_PhoEffBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      histo_ElToPhRateBoundingUp  [ic]->SetBinContent(nb, TMath::Max((float)histo_ElToPhRateBoundingUp  [ic]->GetBinContent(nb),1e-7f));
      histo_ElToPhRateBoundingDown[ic]->SetBinContent(nb, TMath::Max((float)histo_ElToPhRateBoundingDown[ic]->GetBinContent(nb),1e-7f));
      histo_EWKCorrWZUp 	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKCorrWZUp		[ic]->GetBinContent(nb),1e-7f));
      histo_EWKCorrWZDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKCorrWZDown 	[ic]->GetBinContent(nb),1e-7f));
      histo_EWKqqZZCorrUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKqqZZCorrUp 	[ic]->GetBinContent(nb),1e-7f));
      histo_EWKqqZZCorrDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKqqZZCorrDown	[ic]->GetBinContent(nb),1e-7f));
      histo_ggZZCorrUp  	  [ic]->SetBinContent(nb, TMath::Max((float)histo_ggZZCorrUp		[ic]->GetBinContent(nb),1e-7f));
      histo_ggZZCorrDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_ggZZCorrDown  	[ic]->GetBinContent(nb),1e-7f));
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

    printf("uncertainties PHOEFFUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_PhoEffBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties PHOEFFDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_PhoEffBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties ElToPhRateUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_ElToPhRateBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties ElToPhRateDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_ElToPhRateBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
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
  sprintf(outputLimits,"zhg_%d_input.root",year);
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
    histo_PhoEffBoundingUp	[ic]->Write();
    histo_PhoEffBoundingDown	[ic]->Write();
    histo_ElToPhRateBoundingUp  [ic]->Write();
    histo_ElToPhRateBoundingDown[ic]->Write();
    histo_EWKCorrWZUp		[ic]->Write();
    histo_EWKCorrWZDown 	[ic]->Write();
    histo_EWKqqZZCorrUp 	[ic]->Write();
    histo_EWKqqZZCorrDown	[ic]->Write();
    histo_ggZZCorrUp		[ic]->Write();
    histo_ggZZCorrDown  	[ic]->Write();
    histo_JESBoundingUp 	[ic]->Write();
    histo_JESBoundingDown	[ic]->Write();
    histo_METBoundingUp 	[ic]->Write();
    histo_METBoundingDown	[ic]->Write();
  }
  outFileLimits->Close();


  // Filling datacards txt file
  char outputLimitsCard[200];  					  
  sprintf(outputLimitsCard,"datacard_zhg_%d.txt",year);
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
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  //newcardShape << Form("CMS_met    shape     ");
  //for (int ic=0; ic<nPlotCategories; ic++){
  //  if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
  //  newcardShape << Form("1.0 ");
  //}
  //newcardShape << Form("\n");

  newcardShape << Form("CMS_eff_photon    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_fake_el    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("ch1 autoMCStats 0\n");

  newcardShape << Form("CMS_hzg_emnorm  rateParam * %s 1 [0,10]\n",plotBaseNames[kPlotEM].Data());

  newcardShape.close();

  // Writing standard histograms
  char output[200];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    sprintf(output,"histoZHG_%d_%d.root",year,thePlot);	
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

  {
    sprintf(output,"histoZHGSelEvol_%d.root",year);	
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    histoZHGSelEvol->Write();
    outFilePlotsNote->Close();
  }

}
