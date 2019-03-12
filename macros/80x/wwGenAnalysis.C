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

#include "NeroProducer/Core/interface/BareEvent.hpp"
#include "NeroProducer/Core/interface/BareJets.hpp"
#include "NeroProducer/Core/interface/BareLeptons.hpp"
#include "NeroProducer/Core/interface/BareTaus.hpp"
#include "NeroProducer/Core/interface/BareMet.hpp"
#include "NeroProducer/Core/interface/BareTrigger.hpp"
#include "NeroProducer/Core/interface/BareVertex.hpp"
#include "NeroProducer/Core/interface/BareMonteCarlo.hpp"

#include "MitAnalysisRunII/macros/80x/factors.h"
#include "MitAnalysisRunII/macros/80x/BTagCalibrationStandalone.cc"

#include "MitAnalysisRunII/macros/LeptonScaleLookup.h"

#include "WWAnalysis/resummation/WWpTreweight.h"

enum selType                     { SIGSEL,   SSSEL,   TOPSEL,   DYSEL,   PRESEL, nSelTypes};
TString selTypeName[nSelTypes]= { "SIGSEL", "SSSEL", "TOPSEL", "DYSEL", "PRESEL"};

enum systType                     {JESUP=0, JESDOWN,  METUP,  METDOWN,   JERUP,   JERDOWN, nSystTypes};
TString systTypeName[nSystTypes]= {"JESUP","JESDOWN","METUP","METDOWN", "JERUP", "JERDOWN"};

const double bTagCuts[1] = {0.5426}; // 0.5426/0.8484/0.9535 (check BTagCalibration2Reader!)

double ww_norm_unc_qcd[6] = {1.011920,0.983286,0.977908,0.991886,1.024528,1.010472};
double ww_norm_unc_pdf = 1.014691;
double ww_norm_unc_ptwei[4] = {0.996073,1.000986,1.011810,0.953619};
//double ww_norm_unc_qcd[6] = {1,1,1,1,1,1};
//double ww_norm_unc_pdf = 1;
//double ww_norm_unc_ptwei[4] = {1,1,1,1};

bool isMINIAOD = true;
double mcPrescale = 1.0;
bool usePureMC = false;
bool applyGStarVeto = true; 
int period = 1;
const bool useDYMVA = false;
const bool usePUPPI = false;
const bool useTopCR = true;
const bool useDYCR = false;

const int debug = 0;

double topNorm[3]  = {0.81,0.95,1.00};
double topNormE[3] = {0.09,0.11,0.01};

void wwGenAnalysis(
 unsigned int nJetsType,
 int theControlRegion = 0,
 int shapeAnaType = 0,
 TString typeLepSel = "defaultTight",
 bool isMIT = false
 ){

  if(debug != 0) usePureMC = true;

  // File instances on EOS
  TString filesPathDA  = "root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/ceballos/Nero/output_80x/met_";
  TString filesPathMC  = "/eos/cms/store/caf/user/ceballos/Nero/output_80x/";
  TString filesPathMC2 = "root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/ceballos/Nero/output_80x/mc/met_";
  // File instances on T3 hadoop
  if(isMIT){
    filesPathDA   = "/mnt/hadoop/scratch/ceballos/Nero/v2.2/output_80x/data/met_";
    filesPathMC	  = "/mnt/hadoop/scratch/ceballos/Nero/v2.2/output_80x/mc/met_";
    filesPathMC2  = "/mnt/hadoop/scratch/ceballos/Nero/v2.2/output_80x/mc/met_";
  }
  Double_t lumi = 35.9;

  double maxUnc = 1.30;
  double minUnc = 0.70;
  const int nGenBins = 16;
  const int nRecBins = 29;
  double jetPtCut = 30.0; double jetEtaCut = 4.5; double ptLMinCut = 20.0;

  if	 (shapeAnaType == 7) jetPtCut = 30.0;
  else if(shapeAnaType == 8) jetPtCut = 25.0;
  else if(shapeAnaType == 9) jetPtCut = 35.0;

  if(shapeAnaType == 10) jetEtaCut =  2.4;

  if(shapeAnaType >= 1) ptLMinCut =  20.0;

  //*******************************************************
  //Input Files
  //*******************************************************
  vector<TString> infilenamev;  
  vector<Int_t> infilecatv;  

  TString puPath = "";
  TString triggerSuffix = "*";
  if(isMINIAOD) triggerSuffix = "";
  if      (period==1){
  puPath = "MitAnalysisRunII/data/80x/puWeights_80x_37ifb.root";

  infilenamev.push_back(Form("%sWWTo2L2Nu_13TeV-powheg_nocuts.root",filesPathMC.Data()));                                            infilecatv.push_back(1);

  infilenamev.push_back(Form("%sGluGluWWTo2L2Nu_MCFM_13TeV_nocuts.root",filesPathMC.Data()));					      infilecatv.push_back(2);

  }
  else {assert(0); return;}

  if(infilenamev.size() != infilecatv.size()) {assert(0); return;}

  double denBTagging[5][5][3],jetEpsBtagLOOSE[5][5][3];
  double numBTaggingLOOSE[5][5][3];
  for(int i0=0; i0<5; i0++) {
    for(int i1=0; i1<5; i1++) {
      for(int i2=0; i2<3; i2++) {
        denBTagging[i0][i1][i2] = 0.0;
        numBTaggingLOOSE[i0][i1][i2] = 0.0;
	if     (i2==BTagEntry::FLAV_B)    jetEpsBtagLOOSE[i0][i1][i2] = jetEpsBtagBLOOSE[i0][i1];
	else if(i2==BTagEntry::FLAV_C)    jetEpsBtagLOOSE[i0][i1][i2] = jetEpsBtagCLOOSE[i0][i1];
	else if(i2==BTagEntry::FLAV_UDSG) jetEpsBtagLOOSE[i0][i1][i2] = jetEpsBtagLLOOSE[i0][i1];
      }
    }
  }

  //Float_t fMVACut[4][4];
  //InitializeJetIdCuts(fMVACut);

  BTagCalibration2 *btagCalib = new BTagCalibration2("csvv2","MitAnalysisRunII/data/80x/CSVv2_Moriond17_B_H.csv");
  BTagCalibration2Reader btagReaderBCLOOSE(btagCalib,BTagEntry::OP_LOOSE,"comb","central");
  BTagCalibration2Reader btagReaderLLOOSE(btagCalib,BTagEntry::OP_LOOSE,"incl","central");
  BTagCalibration2Reader btagReaderBCLOOSEUP(btagCalib,BTagEntry::OP_LOOSE,"comb","up");
  BTagCalibration2Reader btagReaderLLOOSEUP(btagCalib,BTagEntry::OP_LOOSE,"incl","up");
  BTagCalibration2Reader btagReaderBCLOOSEDOWN(btagCalib,BTagEntry::OP_LOOSE,"comb","down");
  BTagCalibration2Reader btagReaderLLOOSEDOWN(btagCalib,BTagEntry::OP_LOOSE,"incl","down");

  WWpTreweight theWWpTreweight(
              "WWAnalysis/resummation/central.dat",
              "WWAnalysis/resummation/resum_up.dat",
              "WWAnalysis/resummation/resum_down.dat",
              "WWAnalysis/resummation/scale_up.dat",
              "WWAnalysis/resummation/scale_down.dat",
              "WWAnalysis/resummation/nnlo_central.dat",
              "WWAnalysis/resummation/powheg_2l2nu_nlo.dat",
              "WWAnalysis/resummation/powheg_2l2nu_qup_nlo.dat",
              "WWAnalysis/resummation/powheg_2l2nu_qdown_nlo.dat",
              "WWAnalysis/resummation/powheg_2l2nu_sup_nlo.dat",
              "WWAnalysis/resummation/powheg_2l2nu_sdown_nlo.dat",
              "WWAnalysis/resummation/powheg_2l2nu_nnlo.dat");

  float dymva_= -999.;
  unsigned int nlep_= -1;
  unsigned int njets_= -1;

  LeptonScaleLookup trigLookup(Form("MitAnalysisRunII/data/76x/scalefactors_hww.root"));

  TFile *fWWEWKCorrFile = TFile::Open(Form("MitAnalysisRunII/data/80x/WWEWKCorr/WW_EWK_Corr.root"));
  TH1D *fhDWWEWKCorr = (TH1D*)(fWWEWKCorrFile->Get("ratio_Ptlm")); assert(fhDWWEWKCorr); fhDWWEWKCorr->SetDirectory(0);
  //TH1D *fhDWWEWKCorr = (TH1D*)(fWWEWKCorrFile->Get("ratio_Mll")); assert(fhDWWEWKCorr); fhDWWEWKCorr->SetDirectory(0);
  delete fWWEWKCorrFile;

  TFile *fPUFile = TFile::Open(Form("%s",puPath.Data()));
  TH1D *fhDPU     = (TH1D*)(fPUFile->Get("puWeights"));     assert(fhDPU);    fhDPU    ->SetDirectory(0);
  TH1D *fhDPUUp   = (TH1D*)(fPUFile->Get("puWeightsUp"));   assert(fhDPUUp);  fhDPUUp  ->SetDirectory(0);
  TH1D *fhDPUDown = (TH1D*)(fPUFile->Get("puWeightsDown")); assert(fhDPUDown);fhDPUDown->SetDirectory(0);
  delete fPUFile;

  TFile *fTrackElectronReco_SF = TFile::Open(Form("MitAnalysisRunII/data/80x/scalefactors_80x_egpog_37ifb.root"));
  TH2D *fhDeltrksf= (TH2D*)(fTrackElectronReco_SF->Get("scalefactors_Reco_Electron")); assert(fhDeltrksf); fhDeltrksf->SetDirectory(0);
  delete fTrackElectronReco_SF;

  TFile *fElSF_latinos = TFile::Open(Form("MitAnalysisRunII/data/80x/scalefactors_80x_latinos_37ifb.root"));
  TFile *fElSF = TFile::Open(Form("MitAnalysisRunII/data/80x/scalefactors_80x_egpog_37ifb.root"));
  TH2D *fhDElMediumSF = (TH2D*)(fElSF->Get("scalefactors_Medium_Electron"));
  TH2D *fhDElTightSF;
  if(strcmp(typeLepSel.Data(),"defaultTight")==0){
    printf("Using defaultTight SF\n");
    fhDElTightSF = (TH2D*)(fElSF_latinos->Get("scalefactors_Tight_Electron"));
  } else {
    fhDElTightSF = (TH2D*)(fElSF->Get("scalefactors_Tight_Electron"));
  }
  assert(fhDElMediumSF);
  assert(fhDElTightSF);
  fhDElMediumSF->SetDirectory(0);
  fhDElTightSF->SetDirectory(0);
  delete fElSF;
  delete fElSF_latinos;

  TString theVeryTightSFName = "MitAnalysisRunII/data/80x/veryTightSF_37ifb.root";
  if(strcmp(typeLepSel.Data(),"veryverytight")==0){
    theVeryTightSFName = "MitAnalysisRunII/data/80x/veryveryTightSF_37ifb.root";
    printf("Using veryverytight SF\n");
  }
  TFile *fElVeryTightSF = TFile::Open(Form("%s",theVeryTightSFName.Data()));
  TH1D *fhDVeryTightSF = (TH1D*)(fElVeryTightSF->Get("veryTightSF"));
  assert(fhDVeryTightSF);
  fhDVeryTightSF->SetDirectory(0);
  delete fElVeryTightSF;

  TFile *fTrackMuonReco_SF = TFile::Open(Form("MitAnalysisRunII/data/80x/Tracking_EfficienciesAndSF_BCDEFGH.root"));
  TH1D *fhDmutrksfptg10 = (TH1D*)(fTrackMuonReco_SF->Get("ratio_eff_eta3_dr030e030_corr")); assert(fhDmutrksfptg10); fhDmutrksfptg10->SetDirectory(0);
  delete fTrackMuonReco_SF;

  TFile *fMuSF = TFile::Open(Form("MitAnalysisRunII/data/80x/muon_scalefactors_37ifb.root"));
  TH2D *fhDMuMediumSF = (TH2D*)(fMuSF->Get("scalefactors_TightId_Muon")); assert(fhDMuMediumSF); fhDMuMediumSF->SetDirectory(0);
  //TFile *fMuSF = TFile::Open(Form("MitAnalysisRunII/data/80x/MuonID_Z_RunBCD_prompt80X_7p65.root"));
  //TH2D *fhDMuMediumSF = (TH2D*)(fMuSF->Get("MC_NUM_TightIDandIPCut_DEN_genTracks_PAR_pt_spliteta_bin1/abseta_pt_ratio")); assert(fhDMuMediumSF); fhDMuMediumSF->SetDirectory(0);
  delete fMuSF;

  TFile *fMuIsoSF = TFile::Open(Form("MitAnalysisRunII/data/80x/muon_scalefactors_37ifb.root"));
  TH2D *fhDMuIsoSF = (TH2D*)(fMuIsoSF->Get("scalefactors_Iso_MuonTightId")); assert(fhDMuIsoSF); fhDMuIsoSF->SetDirectory(0);
  //TFile *fMuIsoSF = TFile::Open(Form("MitAnalysisRunII/data/80x/MuonIso_Z_RunBCD_prompt80X_7p65.root"));
  //TH2D *fhDMuIsoSF = (TH2D*)(fMuIsoSF->Get("MC_NUM_TightRelIso_DEN_TightID_PAR_pt_spliteta_bin1/abseta_pt_ratio")); assert(fhDMuIsoSF); fhDMuIsoSF->SetDirectory(0);
  delete fMuIsoSF;

  TFile *fzpt_ratio = TFile::Open(Form("MitAnalysisRunII/data/80x/zpt_ratio_80x.root"));
  TH1D *fhDzpt_ratio = (TH1D*)(fzpt_ratio->Get("zpt_ratio")); assert(fhDzpt_ratio); fhDzpt_ratio->SetDirectory(0);
  delete fzpt_ratio;

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

  double xmin = 0.0;
  double xmax = 1.0;
  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 15;
  const int histBins = 12;
  TH1D* histo[allPlots][histBins];
  TString processName[histBins] = {".Data", ".qqWW", ".ggWW", "..Top", "...DY", "...VV", "..VVV", "...WG", "..WGS", "WjetsM", "WjetsE", "Higgs"};

  for(int thePlot=0; thePlot<allPlots; thePlot++){
    TH1D* histos;
    if     (thePlot >=  0 && thePlot <= 14) {nBinPlot = 40; xminPlot = 0.0; xmaxPlot = 200.0;}
    histos = new TH1D("histos", "histos", nBinPlot, xminPlot, xmaxPlot);
    histos->Sumw2();
    for(int i=0; i<histBins; i++) histo[thePlot][i] = (TH1D*) histos->Clone(Form("histo%d",i));
    histos->Reset();histos->Clear();
 }
  //*******************************************************
  // Chain Loop
  //*******************************************************
  for(UInt_t ifile=0; ifile<infilenamev.size(); ifile++) {
    printf("sampleNames(%d): %s\n",ifile,infilenamev[ifile].Data());

    TFile *the_input_file = TFile::Open(infilenamev[ifile].Data());
    TTree *the_input_tree = (TTree*)the_input_file->FindObjectAny("events");
    //TTree *the_input_all  = (TTree*)the_input_file->FindObjectAny("all");
    TTree *the_PDF_tree   = (TTree*)the_input_file->FindObjectAny("pdfReweight");

    BareEvent eventEvent;
    eventEvent.setBranchAddresses(the_input_tree);

    BareJets eventJets;
    if(usePUPPI) eventJets.setBranchAddresses(the_input_tree,"puppi");
    else         eventJets.setBranchAddresses(the_input_tree);

    BareLeptons eventLeptons;
    eventLeptons.setBranchAddresses(the_input_tree);

    BareTaus eventTaus;
    eventTaus.setBranchAddresses(the_input_tree);

    BareMet eventMet;
    eventMet.SetExtend();
    eventMet.setBranchAddresses(the_input_tree);

    BareTrigger eventTrigger;
    eventTrigger.setBranchAddresses(the_input_tree);

    BareVertex eventVertex;
    eventVertex.setBranchAddresses(the_input_tree);

    BareMonteCarlo eventMonteCarlo;
    eventMonteCarlo.setBranchAddresses(the_input_tree);
 
    if(useDYMVA == true){
      the_input_tree->SetBranchAddress("dymva", &dymva_);
      the_input_tree->SetBranchAddress("nlep", &nlep_ );
      the_input_tree->SetBranchAddress("njets", &njets_);
    }

    TNamed *triggerNames = (TNamed*)the_input_file->FindObjectAny("triggerNames");
    char **tokens;
    size_t numtokens;
    tokens = strsplit(triggerNames->GetTitle(), ",", &numtokens);
    if(ifile == 0){
      for (int i = 0; i < (int)numtokens; i++) {
        printf("triggerNames(%2d): \"%s\"\n",(int)i,tokens[i]);
      }
    }
    else {
    }

    double theMCPrescale = mcPrescale;
    if(infilecatv[ifile] == 0) theMCPrescale = 1.0;
    for (int i=0; i<int(the_input_tree->GetEntries()/theMCPrescale); ++i) {
      if(i%100000==0) printf("event %d out of %d\n",i,(int)the_input_tree->GetEntries());

      the_input_tree->GetEntry(i);
 
      int initPDFTag = 0;
      if((*eventMonteCarlo.pdfRwgt).size() == 0) initPDFTag = -1;

      // begin event weighting
      vector<bool> isGenDupl; vector<bool> isNeuDupl;
      vector<int>wBoson;
      vector<int>zBoson;
      int numberQuarks[2] = {0,0};
      TLorentzVector lepNegGen(0,0,0,0);
      for(int ngen0=0; ngen0<eventMonteCarlo.p4->GetEntriesFast(); ngen0++) {

        if((int)(*eventMonteCarlo.pdgId)[ngen0] == 11 || (int)(*eventMonteCarlo.pdgId)[ngen0] == 13) lepNegGen = ( *(TLorentzVector*)(eventMonteCarlo.p4->At(ngen0)) );

        if(TMath::Abs((int)(*eventMonteCarlo.pdgId)[ngen0]) == 4 && ((TLorentzVector*)(*eventMonteCarlo.p4)[ngen0])->Pt() > 15) numberQuarks[0]++;
        if(TMath::Abs((int)(*eventMonteCarlo.pdgId)[ngen0]) == 5 && ((TLorentzVector*)(*eventMonteCarlo.p4)[ngen0])->Pt() > 15) numberQuarks[1]++;
        if(TMath::Abs((int)(*eventMonteCarlo.pdgId)[ngen0]) == 24) {
	  wBoson.push_back(ngen0);
	}
        if(TMath::Abs((int)(*eventMonteCarlo.pdgId)[ngen0]) == 23) {
	  zBoson.push_back(ngen0);
	}
        // begin neutrinos
        isNeuDupl.push_back(0);
	bool isGoodNFlags = ((*eventMonteCarlo.flags)[ngen0] & BareMonteCarlo::PromptFinalState) == BareMonteCarlo::PromptFinalState ||
            		   ((*eventMonteCarlo.flags)[ngen0] & BareMonteCarlo::DirectPromptTauDecayProductFinalState) == BareMonteCarlo::DirectPromptTauDecayProductFinalState;
        isGoodNFlags = isGoodNFlags && (TMath::Abs((int)(*eventMonteCarlo.pdgId)[ngen0]) == 12 || TMath::Abs((int)(*eventMonteCarlo.pdgId)[ngen0]) == 14 || TMath::Abs((int)(*eventMonteCarlo.pdgId)[ngen0]) == 16);
        if(isGoodNFlags == false) isNeuDupl[ngen0] = 1;

        isGenDupl.push_back(0);
        // begin charged leptons
	bool isGoodFlags = ((*eventMonteCarlo.flags)[ngen0] & BareMonteCarlo::PromptFinalState) == BareMonteCarlo::PromptFinalState ||
            		   ((*eventMonteCarlo.flags)[ngen0] & BareMonteCarlo::DirectPromptTauDecayProductFinalState) == BareMonteCarlo::DirectPromptTauDecayProductFinalState;
        isGoodFlags = isGoodFlags && (TMath::Abs((int)(*eventMonteCarlo.pdgId)[ngen0]) == 11 || TMath::Abs((int)(*eventMonteCarlo.pdgId)[ngen0]) == 13);
        if(isGoodFlags == false) isGenDupl[ngen0] = 1;
      }

      TLorentzVector the_rhoP4(0,0,0,0); double theLeptonHT = 0.0;
      int genLep = 0;
      for(int ngen=0; ngen<eventMonteCarlo.p4->GetEntriesFast(); ngen++) {
        if(isNeuDupl[ngen] == 0 || isGenDupl[ngen] == 0) {
	  the_rhoP4 = the_rhoP4 + *(TLorentzVector*)(*eventMonteCarlo.p4)[ngen];
	  theLeptonHT = theLeptonHT + ((TLorentzVector*)(*eventMonteCarlo.p4)[ngen])->Pt();
	}
	if(isGenDupl[ngen] == 1) continue;
        genLep++;
      }

      double theEWKCorr = 1.0; double theEWKCorrE = 1.0;
      double the_rhoWW = 0.0; if(theLeptonHT > 0) the_rhoWW = the_rhoP4.Pt()/theLeptonHT;
      if((infilecatv[ifile] == 1 || infilecatv[ifile] == 2) && lepNegGen.Pt() > 0 && the_rhoWW <= 0.3){
        Int_t EWKValbin = fhDWWEWKCorr->GetXaxis()->FindBin(TMath::Min(lepNegGen.Pt(),499.999));
	if(EWKValbin >= 0) theEWKCorr  = fhDWWEWKCorr->GetBinContent(EWKValbin);
	if(EWKValbin >= 0) theEWKCorrE = 1.0+fhDWWEWKCorr->GetBinError(EWKValbin)/fhDWWEWKCorr->GetBinContent(EWKValbin);
      }

      double thePtwwWeight[5] = {1.0,1.0,1.0,1.0,1.0};
      TLorentzVector wwSystem;
      if(infilecatv[ifile] == 1 && wBoson.size() == 2){
        wwSystem = ( *(TLorentzVector*)(eventMonteCarlo.p4->At(wBoson[0])) ) + ( *(TLorentzVector*)(eventMonteCarlo.p4->At(wBoson[1])) ); 
        Int_t nptwwbin[5] = {fhDWWPtRatio	   ->GetXaxis()->FindBin(TMath::Min(wwSystem.Pt(),499.999)),
	                     fhDWWPtRatio_scaleup  ->GetXaxis()->FindBin(TMath::Min(wwSystem.Pt(),499.999)),
	                     fhDWWPtRatio_scaledown->GetXaxis()->FindBin(TMath::Min(wwSystem.Pt(),499.999)),
	                     fhDWWPtRatio_resumup  ->GetXaxis()->FindBin(TMath::Min(wwSystem.Pt(),499.999)),
	                     fhDWWPtRatio_resumdown->GetXaxis()->FindBin(TMath::Min(wwSystem.Pt(),499.999))};
        thePtwwWeight[0] = fhDWWPtRatio 	 ->GetBinContent(nptwwbin[0])*1.035;
	thePtwwWeight[1] = fhDWWPtRatio_scaleup  ->GetBinContent(nptwwbin[1]);
	thePtwwWeight[2] = fhDWWPtRatio_scaledown->GetBinContent(nptwwbin[2]);
	thePtwwWeight[3] = fhDWWPtRatio_resumup  ->GetBinContent(nptwwbin[3]);
	thePtwwWeight[4] = fhDWWPtRatio_resumdown->GetBinContent(nptwwbin[4]);
      }

      double maxQCDscale = (TMath::Abs((double)eventMonteCarlo.r1f2)+TMath::Abs((double)eventMonteCarlo.r1f5)+TMath::Abs((double)eventMonteCarlo.r2f1)+
        		    TMath::Abs((double)eventMonteCarlo.r2f2)+TMath::Abs((double)eventMonteCarlo.r5f1)+TMath::Abs((double)eventMonteCarlo.r5f5))/6.0;
      double PDFAvg = 0.0;
      if(initPDFTag != -1)
      for(int npdf=0; npdf<100; npdf++) PDFAvg = PDFAvg + TMath::Abs((double)(*eventMonteCarlo.pdfRwgt)[npdf+initPDFTag]);
      PDFAvg = PDFAvg/100.0;
 
      double theLumi  = 1.0; if(infilecatv[ifile] != 0) theLumi  = lumi;

      int theCategory = infilecatv[ifile];
      double mcWeight = eventMonteCarlo.mcWeight;
      if(infilecatv[ifile] == 0) mcWeight = 1.0;
      double totalWeightA = mcWeight*theLumi;
      double totalWeightB = mcWeight*theLumi*thePtwwWeight[0];
      double totalWeightC = mcWeight*theLumi*thePtwwWeight[0]*theEWKCorr;
      double totalWeightD = mcWeight*theLumi*theEWKCorr;

      // end event weighting
      for(int thePlot=0; thePlot<allPlots; thePlot++){
        bool makePlot = true;double theVar = TMath::Min(wwSystem.Pt(),199.999);
        if(makePlot && thePlot ==  0) histo[thePlot][theCategory]->Fill(theVar,totalWeightA);
        if(makePlot && thePlot ==  1) histo[thePlot][theCategory]->Fill(theVar,totalWeightB);
        if(makePlot && thePlot ==  2) histo[thePlot][theCategory]->Fill(theVar,totalWeightC);
        if(makePlot && thePlot ==  3) histo[thePlot][theCategory]->Fill(theVar,totalWeightD);
        if(makePlot && thePlot ==  4) histo[thePlot][theCategory]->Fill(theVar,totalWeightC*thePtwwWeight[1]);
        if(makePlot && thePlot ==  5) histo[thePlot][theCategory]->Fill(theVar,totalWeightC*thePtwwWeight[2]);
        if(makePlot && thePlot ==  6) histo[thePlot][theCategory]->Fill(theVar,totalWeightC*thePtwwWeight[3]);
        if(makePlot && thePlot ==  7) histo[thePlot][theCategory]->Fill(theVar,totalWeightC*thePtwwWeight[4]);
        if(makePlot && thePlot ==  8) histo[thePlot][theCategory]->Fill(theVar,totalWeightC*TMath::Abs((double)eventMonteCarlo.r1f2)/maxQCDscale);
        if(makePlot && thePlot ==  9) histo[thePlot][theCategory]->Fill(theVar,totalWeightC*TMath::Abs((double)eventMonteCarlo.r1f5)/maxQCDscale);
        if(makePlot && thePlot == 10) histo[thePlot][theCategory]->Fill(theVar,totalWeightC*TMath::Abs((double)eventMonteCarlo.r2f1)/maxQCDscale);
        if(makePlot && thePlot == 11) histo[thePlot][theCategory]->Fill(theVar,totalWeightC*TMath::Abs((double)eventMonteCarlo.r2f2)/maxQCDscale);
        if(makePlot && thePlot == 12) histo[thePlot][theCategory]->Fill(theVar,totalWeightC*TMath::Abs((double)eventMonteCarlo.r5f1)/maxQCDscale);
        if(makePlot && thePlot == 13) histo[thePlot][theCategory]->Fill(theVar,totalWeightC*TMath::Abs((double)eventMonteCarlo.r5f5)/maxQCDscale);
      }
    }
    the_input_file->Close();
  } // end of chain

  char output[200];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    char output[200];
    sprintf(output,"histoww_nice%d_cr%d_shapeType%d_%d.root",nJetsType,theControlRegion,shapeAnaType,thePlot);  	
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    for(int np=0; np<histBins; np++) histo[thePlot][np]->Write();
    printf("(%2d) ",thePlot);
    for(int np=0; np<histBins; np++) printf("%f ",histo[thePlot][np]->GetSumOfWeights());
    printf("\n");
    outFilePlotsNote->Close();
  }
  int np = 1;
  double weightDefault = histo[2][np]->GetSumOfWeights();
  printf("ptWW: %.6f %.6f %.6f %.6f\n",
  histo[4][np]->GetSumOfWeights()/weightDefault,histo[5][np]->GetSumOfWeights()/weightDefault,
  histo[6][np]->GetSumOfWeights()/weightDefault,histo[7][np]->GetSumOfWeights()/weightDefault);
  printf("QCDScale: %.6f %.6f %.6f %.6f %.6f %.6f\n",
  histo[ 8][np]->GetSumOfWeights()/weightDefault,histo[ 9][np]->GetSumOfWeights()/weightDefault,
  histo[10][np]->GetSumOfWeights()/weightDefault,histo[11][np]->GetSumOfWeights()/weightDefault,
  histo[12][np]->GetSumOfWeights()/weightDefault,histo[13][np]->GetSumOfWeights()/weightDefault);
}
