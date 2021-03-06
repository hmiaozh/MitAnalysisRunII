#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TString.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>

#include "NeroProducer/Core/interface/BareMonteCarlo.hpp"
#include "NeroProducer/Core/interface/BareEvent.hpp"
#include "NeroProducer/Core/interface/BareJets.hpp"
#include "NeroProducer/Core/interface/BareLeptons.hpp"
#include "NeroProducer/Core/interface/BarePhotons.hpp"
#include "NeroProducer/Core/interface/BareMet.hpp"
#include "NeroProducer/Core/interface/BareTrigger.hpp"
#include "NeroProducer/Core/interface/BareVertex.hpp"

#include "MitAnalysisRunII/macros/80x/factors.h"

int whichSkim = 1;
double mcPrescale = 5.0;

bool isMINIAOD = true;

void QCDAnalysis(
 Int_t typeSel = 4,
 TString typeLepSel = "medium",
 Int_t applyPrescale = 1,
 bool isMIT = true
 ){

  Int_t period = 1;
  // File instances on EOS
  TString filesPathDA = "root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/ceballos/Nero/output_80x/";
  TString filesPathMC  = "root://eoscms.cern.ch//eos/cms/store/caf/user/ceballos/Nero/output_80x/";
  TString filesPathMC2 = "root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/ceballos/Nero/output_80x/mc/";
  // File instances on T3 hadoop
  if(isMIT){
    filesPathDA   = "/mnt/hadoop/scratch/ceballos/Nero/v2.2/output_80x/data/";
    filesPathMC   = "/mnt/hadoop/scratch/ceballos/Nero/v2.2/output_80x/mc/";
    filesPathMC2  = "/mnt/hadoop/scratch/ceballos/Nero/v2.2/output_80x/mc/";
  }
  Double_t lumi = 35.9;

  Double_t prescale[6];

  double denFRDA[5][6] = {0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0};
  double numFRDA[5][6] = {0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0};
  double denFRBG[5][6] = {0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0};
  double numFRBG[5][6] = {0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0};

  double denSFDA[6]    = {0,0,0,0,0,0};
  double denSFBG[6]    = {0,0,0,0,0,0};

  double denLGTDA[8]    = {0,0,0,0, 0,0,0,0};
  double denLGTBG[8]    = {0,0,0,0, 0,0,0,0};
  double denLGPDA[8]    = {0,0,0,0, 0,0,0,0};
  double denLGPBG[8]    = {0,0,0,0, 0,0,0,0};

  double minLepPt = 10.0;
  if(typeSel == 11) minLepPt = 12.0;

  //*******************************************************
  //Input Files
  //*******************************************************
  vector<TString> infilenamev;  
  vector<Int_t> infilecatv;  

  TString triggerSuffix = "*";
  if(isMINIAOD) triggerSuffix = "";
  TString puPath = "";
  if     (period==0){
  }
  else if(period==1){
  if     (typeSel == 11) {prescale[0]=0.00237;prescale[1]=0.00260;prescale[2]=0.00251;prescale[3]=0.00251;prescale[4]=0.00254;prescale[5]=0.00256;}
  else if(typeSel == 13) {prescale[0]=0.00565;prescale[1]=0.00639;prescale[2]=0.00680;prescale[3]=0.00661;prescale[4]=0.00633;prescale[5]=0.00656;}

  puPath = "MitAnalysisRunII/data/80x/puWeights_80x_37ifb.root";

  if(isMINIAOD) {
    infilenamev.push_back(Form("%sdata_Run2016B.root",filesPathDA.Data())); infilecatv.push_back(0);
    infilenamev.push_back(Form("%sdata_Run2016C.root",filesPathDA.Data())); infilecatv.push_back(0);
    infilenamev.push_back(Form("%sdata_Run2016D.root",filesPathDA.Data())); infilecatv.push_back(0);
    infilenamev.push_back(Form("%sdata_Run2016E.root",filesPathDA.Data())); infilecatv.push_back(0);
    infilenamev.push_back(Form("%sdata_Run2016F.root",filesPathDA.Data())); infilecatv.push_back(0);
    infilenamev.push_back(Form("%sdata_Run2016G.root",filesPathDA.Data())); infilecatv.push_back(0);
    infilenamev.push_back(Form("%sdata_Run2016H.root",filesPathDA.Data())); infilecatv.push_back(0);
  } else {
  }

  infilenamev.push_back(Form("%sWWTo2L2Nu_13TeV-powheg.root",filesPathMC.Data()));                                            infilecatv.push_back(1);
  infilenamev.push_back(Form("%sGluGluWWTo2L2Nu_MCFM_13TeV.root",filesPathMC.Data()));					      infilecatv.push_back(1);

  infilenamev.push_back(Form("%sDYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root",filesPathMC.Data()));        infilecatv.push_back(2);
  infilenamev.push_back(Form("%sDYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root",filesPathMC.Data()));	      infilecatv.push_back(2);

  infilenamev.push_back(Form("%sTTTo2L2Nu_13TeV-powheg.root",filesPathMC2.Data()));					      infilecatv.push_back(3);
  infilenamev.push_back(Form("%sTTToSemiLeptonic_13TeV-powheg.root",filesPathMC2.Data()));				      infilecatv.push_back(3);
  infilenamev.push_back(Form("%sST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1.root",filesPathMC.Data()));    infilecatv.push_back(3);
  infilenamev.push_back(Form("%sST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1.root",filesPathMC.Data()));infilecatv.push_back(3);

  infilenamev.push_back(Form("%sZZTo2L2Nu_13TeV_powheg_pythia8.root",filesPathMC.Data()));  				      infilecatv.push_back(4);
  infilenamev.push_back(Form("%sGluGluToContinToZZTo2mu2nu_13TeV_MCFM701_pythia8.root",filesPathMC.Data()));		      infilecatv.push_back(4);
  infilenamev.push_back(Form("%sGluGluToContinToZZTo2e2nu_13TeV_MCFM701_pythia8.root",filesPathMC.Data()));		      infilecatv.push_back(4);
  infilenamev.push_back(Form("%sZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8.root",filesPathMC.Data()));			      infilecatv.push_back(4);
  infilenamev.push_back(Form("%sZZTo4L_13TeV_powheg_pythia8.root",filesPathMC.Data()));					      infilecatv.push_back(4);
  infilenamev.push_back(Form("%sGluGluToContinToZZTo2mu2tau_13TeV_MCFM701_pythia8.root",filesPathMC.Data()));	 	      infilecatv.push_back(4);
  infilenamev.push_back(Form("%sGluGluToContinToZZTo4e_13TeV_MCFM701_pythia8.root",filesPathMC.Data()));		      infilecatv.push_back(4);
  infilenamev.push_back(Form("%sGluGluToContinToZZTo4mu_13TeV_MCFM701_pythia8.root",filesPathMC.Data()));		      infilecatv.push_back(4);
  infilenamev.push_back(Form("%sGluGluToContinToZZTo4tau_13TeV_MCFM701_pythia8.root",filesPathMC.Data()));		      infilecatv.push_back(4);
  infilenamev.push_back(Form("%sGluGluToContinToZZTo2e2mu_13TeV_MCFM701_pythia8.root",filesPathMC.Data()));		      infilecatv.push_back(4);
  infilenamev.push_back(Form("%sGluGluToContinToZZTo2e2tau_13TeV_MCFM701_pythia8.root",filesPathMC.Data()));		      infilecatv.push_back(4);

  infilenamev.push_back(Form("%sWZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8.root",filesPathMC.Data()));			      infilecatv.push_back(4);
  infilenamev.push_back(Form("%sWZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8.root",filesPathMC.Data()));			      infilecatv.push_back(4);
  infilenamev.push_back(Form("%sWWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root",filesPathMC.Data())); 			      infilecatv.push_back(4);
  infilenamev.push_back(Form("%sWWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root",filesPathMC.Data())); 			      infilecatv.push_back(4);
  infilenamev.push_back(Form("%sWZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root",filesPathMC.Data()));                           infilecatv.push_back(4);
  infilenamev.push_back(Form("%sZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root",filesPathMC.Data()));                           infilecatv.push_back(4);
  infilenamev.push_back(Form("%sTTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root",filesPathMC.Data()));      infilecatv.push_back(4);
  infilenamev.push_back(Form("%sTTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root",filesPathMC.Data()));	      infilecatv.push_back(4);
  infilenamev.push_back(Form("%sTTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root",filesPathMC.Data()));	      infilecatv.push_back(4);
  infilenamev.push_back(Form("%sTTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root",filesPathMC.Data()));			      infilecatv.push_back(4);
  infilenamev.push_back(Form("%sTTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root",filesPathMC.Data()));           infilecatv.push_back(4);
  infilenamev.push_back(Form("%stZq_ll_4f_13TeV-amcatnlo-pythia8.root",filesPathMC.Data())); 		                      infilecatv.push_back(4);

  infilenamev.push_back(Form("%sWJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root",filesPathMC.Data()));		      infilecatv.push_back(5);

  infilenamev.push_back(Form("%sWGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root",filesPathMC.Data()));                  infilecatv.push_back(6);
  //infilenamev.push_back(Form("%sZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root",filesPathMC.Data()));                 infilecatv.push_back(6);

  infilenamev.push_back(Form("%sGluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8.root",filesPathMC.Data()));		      infilecatv.push_back(7);
  infilenamev.push_back(Form("%sVBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgenv628_pythia8.root",filesPathMC.Data()));              infilecatv.push_back(7);
  infilenamev.push_back(Form("%sGluGluHToTauTau_M125_13TeV_powheg_pythia8.root",filesPathMC.Data()));			      infilecatv.push_back(7);
  infilenamev.push_back(Form("%sVBFHToTauTau_M125_13TeV_powheg_pythia8.root",filesPathMC.Data()));                            infilecatv.push_back(7);
  //infilenamev.push_back(Form("%sVHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8.root",filesPathMC.Data())); 	      infilecatv.push_back(7);
  //infilenamev.push_back(Form("%sttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8.root",filesPathMC.Data()));   infilecatv.push_back(7);
  }

  //infilenamev.push_back(Form("nero.root"));     infilecatv.push_back(0);

  if(infilenamev.size() != infilecatv.size()) assert(0);

  Float_t fMVACut[4][4];
  InitializeJetIdCuts(fMVACut);

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
  if(typeLepSel == "medium_mva") fhDElMediumSF = (TH2D*)(fElSF->Get("scalefactors_MediumMVA_Electron"));
  if(typeLepSel == "default_mva") fhDElTightSF = (TH2D*)(fElSF->Get("scalefactors_TightMVA_Electron"));
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

  double xmin = 0.0;
  double xmax = 1.0;
  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 40;
  const int histBins = 8;
  TH1D* histo[allPlots][histBins];

  for(int thePlot=0; thePlot<allPlots; thePlot++){
    if     (thePlot >=  0 && thePlot <=  3) {nBinPlot = 200; xminPlot = 0.0; xmaxPlot = 200.0;}
    else if(thePlot >=  4 && thePlot <=  5) {nBinPlot =   7; xminPlot =-0.5; xmaxPlot =   6.5;}
    else if(thePlot >=  6 && thePlot <=  6) {nBinPlot =  40; xminPlot = 0.0; xmaxPlot =  40.0;}
    else if(thePlot >=  7 && thePlot <=  7) {nBinPlot =  40; xminPlot =-0.5; xmaxPlot =  39.5;}
    else if(thePlot >=  8 && thePlot <=  8) {nBinPlot = 200; xminPlot = 0.0; xmaxPlot = 200.0;}
    else if(thePlot >=  9 && thePlot <=  9) {nBinPlot =  50; xminPlot = 0.0; xmaxPlot =   2.5;}

    else if(thePlot >= 10 && thePlot <= 13) {nBinPlot = 200; xminPlot = 0.0; xmaxPlot = 200.0;}
    else if(thePlot >= 14 && thePlot <= 15) {nBinPlot =   7; xminPlot =-0.5; xmaxPlot =   6.5;}
    else if(thePlot >= 16 && thePlot <= 16) {nBinPlot =  40; xminPlot = 0.0; xmaxPlot =  40.0;}
    else if(thePlot >= 17 && thePlot <= 17) {nBinPlot =  40; xminPlot =-0.5; xmaxPlot =  39.5;}
    else if(thePlot >= 18 && thePlot <= 18) {nBinPlot = 200; xminPlot = 0.0; xmaxPlot = 200.0;}
    else if(thePlot >= 19 && thePlot <= 19) {nBinPlot =  50; xminPlot = 0.0; xmaxPlot =   2.5;}

    else if(thePlot >= 20 && thePlot <= 23) {nBinPlot = 200; xminPlot = 0.0; xmaxPlot = 200.0;}
    else if(thePlot >= 24 && thePlot <= 25) {nBinPlot =   7; xminPlot =-0.5; xmaxPlot =   6.5;}
    else if(thePlot >= 26 && thePlot <= 26) {nBinPlot =  40; xminPlot = 0.0; xmaxPlot =  40.0;}
    else if(thePlot >= 27 && thePlot <= 27) {nBinPlot =  40; xminPlot =-0.5; xmaxPlot =  39.5;}
    else if(thePlot >= 28 && thePlot <= 28) {nBinPlot = 200; xminPlot = 0.0; xmaxPlot = 200.0;}
    else if(thePlot >= 29 && thePlot <= 29) {nBinPlot =  50; xminPlot = 0.0; xmaxPlot =   2.5;}

    else if(thePlot >= 30 && thePlot <= 33) {nBinPlot = 200; xminPlot = 0.0; xmaxPlot = 200.0;}
    else if(thePlot >= 34 && thePlot <= 35) {nBinPlot =   7; xminPlot =-0.5; xmaxPlot =   6.5;}
    else if(thePlot >= 36 && thePlot <= 36) {nBinPlot =  40; xminPlot = 0.0; xmaxPlot =  40.0;}
    else if(thePlot >= 37 && thePlot <= 37) {nBinPlot =  40; xminPlot =-0.5; xmaxPlot =  39.5;}
    else if(thePlot >= 38 && thePlot <= 38) {nBinPlot = 200; xminPlot = 0.0; xmaxPlot = 200.0;}
    else if(thePlot >= 39 && thePlot <= 39) {nBinPlot =  50; xminPlot = 0.0; xmaxPlot =   2.5;}

    TH1D* histos = new TH1D("histos", "histos", nBinPlot, xminPlot, xmaxPlot);
    histos->Sumw2();
    for(int i=0; i<histBins; i++) histo[thePlot][i] = (TH1D*) histos->Clone(Form("histo%d",i));
    histos->Clear();
  }

  if(typeSel != 11 && typeSel != 13) {assert(0); return;}

  //*******************************************************
  // Chain Loop
  //*******************************************************
  for(UInt_t ifile=0; ifile<infilenamev.size(); ifile++) {
    printf("sampleNames(%d): %s\n",ifile,infilenamev[ifile].Data());

    TFile *the_input_file = TFile::Open(infilenamev[ifile].Data());
    TTree *the_input_tree = (TTree*)the_input_file->FindObjectAny("events");
    //TTree *the_input_all  = (TTree*)the_input_file->FindObjectAny("all");
    TTree *the_SelBit_tree= (TTree*)the_input_file->FindObjectAny("SelBit_tree");

    BareMonteCarlo eventMonteCarlo;
    eventMonteCarlo.setBranchAddresses(the_input_tree);

    BareEvent eventEvent;
    eventEvent.setBranchAddresses(the_input_tree);

    BareJets eventJets;
    eventJets.setBranchAddresses(the_input_tree);

    BareLeptons eventLeptons;
    eventLeptons.setBranchAddresses(the_input_tree);

    BarePhotons eventPhotons;
    eventPhotons.SetExtend();
    eventPhotons.setBranchAddresses(the_input_tree);

    BareMet eventMet;
    eventMet.SetExtend();
    eventMet.setBranchAddresses(the_input_tree);

    BareTrigger eventTrigger;
    eventTrigger.setBranchAddresses(the_input_tree);

    BareVertex eventVertex;
    eventVertex.setBranchAddresses(the_input_tree);

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

    unsigned int selBit_= 0;
    the_SelBit_tree->SetBranchAddress("selBit", &selBit_);
    Int_t nPassCuts[4][6] = {0,0,0,0,0,0,
                             0,0,0,0,0,0,
                             0,0,0,0,0,0,
                             0,0,0,0,0,0};
    double theMCPrescale = mcPrescale;
    if(infilecatv[ifile] == 0) theMCPrescale = 1.0;
    if(the_input_tree->GetEntries() != the_SelBit_tree->GetEntries()) {printf("BIG SKIMMING FAILURE\n"); return;}
    for (int i=0; i<int(the_input_tree->GetEntries()/theMCPrescale); ++i) {
      the_SelBit_tree->GetEntry(i);
      if(i%1000000==0) printf("event %d out of %d\n",i,(int)the_input_tree->GetEntries());
      if((selBit_ & 0x1<<whichSkim) == 0) continue;

      the_input_tree->GetEntry(i);

      Bool_t passFilter = kFALSE;
      Bool_t passTrigger = kFALSE;
      if(infilecatv[ifile] != 999) {
	for (int nt = 0; nt < (int)numtokens; nt++) {
	  if(typeSel == 11 &&
            (strcmp(tokens[nt],Form("HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v%s",triggerSuffix.Data())) == 0 ||
             strcmp(tokens[nt],Form("HLT_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30_v%s",triggerSuffix.Data())) == 0 ||
             strcmp(tokens[nt],Form("HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_v%s",triggerSuffix.Data())) == 0 ) &&
	    (*eventTrigger.triggerFired)[nt] == 1) passTrigger = kTRUE;
	  if(typeSel == 13 &&
	    (strcmp(tokens[nt],Form("HLT_Mu8_TrkIsoVVL_v%s",triggerSuffix.Data()))  == 0 ||              
	     strcmp(tokens[nt],Form("HLT_Mu17_TrkIsoVVL_v%s",triggerSuffix.Data())) == 0 ) &&           
	    (*eventTrigger.triggerFired)[nt] == 1) passTrigger = kTRUE;
	}
      } else { passTrigger = kTRUE;}
      if(passTrigger == kTRUE &&
         eventLeptons.p4->GetEntriesFast() >= 1 &&
         ((TLorentzVector*)(*eventLeptons.p4)[0])->Pt() > 10 && 
	 (double)((TLorentzVector*)(*eventMet.p4)[0])->Pt() < 30.0) passFilter = kTRUE;

      if(passTrigger == kTRUE) {nPassCuts[0][0]++;nPassCuts[1][0]++;nPassCuts[2][0]++;nPassCuts[3][0]++;}
      if(passFilter  == kTRUE) {nPassCuts[0][1]++;nPassCuts[1][1]++;nPassCuts[2][1]++;nPassCuts[3][1]++;}
      if(passFilter == kFALSE) continue;

      Bool_t passSel[4] = {kFALSE, kFALSE, kFALSE, kFALSE};
      TLorentzVector dilep;double deltaPhiDileptonMet = -999.0; double mtW = -999.0;
      vector<int> idLep; vector<int> idTight;
      for(int nlep=0; nlep<eventLeptons.p4->GetEntriesFast(); nlep++) {
        if(selectIdIsoCut(typeLepSel.Data(),TMath::Abs((int)(*eventLeptons.pdgId)[nlep]),TMath::Abs(((TLorentzVector*)(*eventLeptons.p4)[nlep])->Pt()),
	   TMath::Abs(((TLorentzVector*)(*eventLeptons.p4)[nlep])->Eta()),(double)(*eventLeptons.iso)[nlep],(int)(*eventLeptons.selBits)[nlep],(double)(*eventLeptons.mva)[nlep]))
	                                                                                               {idTight.push_back(1); idLep.push_back(nlep);}
        else if(((int)(*eventLeptons.selBits)[nlep] & BareLeptons::LepFake)  == BareLeptons::LepFake ) {idTight.push_back(0); idLep.push_back(nlep);}
      }

      vector<int> isGenLep;
      for(unsigned nl=0; nl<idLep.size(); nl++){
        bool isGenLepton = false;
        for(int ngen=0; ngen<eventMonteCarlo.p4->GetEntriesFast(); ngen++) {
	  bool isGoodFlags = ((*eventMonteCarlo.flags)[ngen] & BareMonteCarlo::PromptFinalState) == BareMonteCarlo::PromptFinalState ||
            		     ((*eventMonteCarlo.flags)[ngen] & BareMonteCarlo::DirectPromptTauDecayProductFinalState) == BareMonteCarlo::DirectPromptTauDecayProductFinalState;
          isGoodFlags = isGoodFlags && (TMath::Abs((int)(*eventMonteCarlo.pdgId)[ngen]) == 11 || TMath::Abs((int)(*eventMonteCarlo.pdgId)[ngen]) == 13);
          if(isGoodFlags == false) continue;
          if(TMath::Abs((int)(*eventLeptons.pdgId)[idLep[nl]]) == TMath::Abs((int)(*eventMonteCarlo.pdgId)[ngen]) &&
	    ((TLorentzVector*)(*eventLeptons.p4)[idLep[nl]])->DeltaR(*((TLorentzVector*)(*eventMonteCarlo.p4)[ngen])) < 0.3) {
	    isGenLepton = true;
	    break;
	  }
	}
	if(isGenLepton == true) isGenLep.push_back(nl);
      }
      
      vector<int> idPho;
      for(int npho=0; npho<eventPhotons.p4->GetEntriesFast(); npho++) {
        if(TMath::Abs(((TLorentzVector*)(*eventPhotons.p4)[npho])->Eta()) >= 2.5) continue;
	if(((TLorentzVector*)(*eventPhotons.p4)[npho])->Pt() <= 20.0) continue;

        bool isGoodPhoton = ((int)(*eventPhotons.selBits)[npho] & BarePhotons::PhoMedium)        == BarePhotons::PhoMedium &&
	                    ((int)(*eventPhotons.selBits)[npho] & BarePhotons::PhoElectronVeto)  == BarePhotons::PhoElectronVeto &&
			    ((int)(*eventPhotons.selBits)[npho] & BarePhotons::PhoPixelSeedVeto) == BarePhotons::PhoPixelSeedVeto;
        if(isGoodPhoton == false) continue;

        bool isRecoLepton = false;
	for(unsigned int nl=0; nl<idLep.size(); nl++){
          if(((TLorentzVector*)(*eventPhotons.p4)[npho])->DeltaR(*((TLorentzVector*)(*eventLeptons.p4)[idLep[nl]])) < 0.1)
	    {isRecoLepton = true; break;}
        }
	if(isRecoLepton == false) idPho.push_back(npho);
      }

      vector<int> idJet20,idJet30;
      for(int nj=0; nj<eventJets.p4->GetEntriesFast(); nj++){
        if(((TLorentzVector*)(*eventJets.p4)[nj])->Pt() < 10) continue;
        //bool passId = passJetId(fMVACut, (float)(*eventJets.puId)[nj], ((TLorentzVector*)(*eventJets.p4)[nj])->Pt(), TMath::Abs(((TLorentzVector*)(*eventJets.p4)[nj])->Eta()));
        //if(passId == false) continue;        

        Bool_t isLepton = kFALSE;
        for(unsigned int nl=0; nl<idLep.size(); nl++){
          if(((TLorentzVector*)(*eventJets.p4)[nj])->DeltaR(*((TLorentzVector*)(*eventLeptons.p4)[idLep[nl]])) < 0.3) isLepton = kTRUE;
	}
	if(isLepton == kTRUE) continue;

        if(((TLorentzVector*)(*eventJets.p4)[nj])->Pt() > 20)  idJet20.push_back(nj);
        if(((TLorentzVector*)(*eventJets.p4)[nj])->Pt() > 30)  idJet30.push_back(nj);
      }

      bool passJetSel = kFALSE;
      if((typeSel == 11 && idJet30.size() >= 1) || 
         (typeSel == 13 && idJet20.size() >= 1)) passJetSel = kTRUE;

      if(passJetSel == kTRUE) {nPassCuts[0][2]++;nPassCuts[1][2]++;nPassCuts[2][2]++;nPassCuts[3][2]++;}
      if(passJetSel == kFALSE) continue;

      if(1){ // Z->ll
	if(idLep.size() == 2 &&
     	  ((TLorentzVector*)(*eventLeptons.p4)[idLep[0]])->Pt() > minLepPt && 
     	  ((TLorentzVector*)(*eventLeptons.p4)[idLep[1]])->Pt() > minLepPt) nPassCuts[0][3]++;
        if(idLep.size() == 2 &&
     	  ((TLorentzVector*)(*eventLeptons.p4)[idLep[0]])->Pt() > minLepPt && 
     	  ((TLorentzVector*)(*eventLeptons.p4)[idLep[1]])->Pt() > minLepPt &&
          (int)(*eventLeptons.pdgId)[idLep[0]]*(int)(*eventLeptons.pdgId)[idLep[1]] < 0 &&
	  TMath::Abs((int)(*eventLeptons.pdgId)[idLep[0]]) == TMath::Abs((int)(*eventLeptons.pdgId)[idLep[1]]) &&
	  TMath::Abs((int)(*eventLeptons.pdgId)[idLep[0]]) == typeSel &&
	 (infilecatv[ifile] == 0 || isGenLep.size() == 2)) {
          nPassCuts[0][4]++;
          dilep = ( ( *(TLorentzVector*)(eventLeptons.p4->At(idLep[0])) ) + ( *(TLorentzVector*)(eventLeptons.p4->At(idLep[1])) ) ); 
          if(TMath::Abs(dilep.M()-91.1876)<10.0) passSel[0] = kTRUE;	
	}
      }
      if(1){ // fake
	if(idLep.size() == 1 &&
     	  ((TLorentzVector*)(*eventLeptons.p4)[idLep[0]])->Pt() > minLepPt) nPassCuts[1][3]++;
        if(idLep.size() == 1 &&
     	  ((TLorentzVector*)(*eventLeptons.p4)[idLep[0]])->Pt() > minLepPt &&
	  TMath::Abs((int)(*eventLeptons.pdgId)[idLep[0]]) == typeSel &&
	 (infilecatv[ifile] == 0 || isGenLep.size() == 1)) {
          dilep = ( *(TLorentzVector*)(eventLeptons.p4->At(idLep[0])) );
          nPassCuts[1][4]++;
          deltaPhiDileptonMet = TMath::Abs(dilep.DeltaPhi(*((TLorentzVector*)(*eventMet.p4)[0])));
          mtW = TMath::Sqrt(2.0*dilep.Pt()*((TLorentzVector*)(*eventMet.p4)[0])->Pt()*(1.0 - cos(deltaPhiDileptonMet)));
	  if(mtW < 20) passSel[1] = kTRUE;
	}
      }
      if(1){ // W->ln
        bool thePass = idLep.size() == 1 && idTight[0] == 1 && ((TLorentzVector*)(*eventLeptons.p4)[idLep[0]])->Pt() > minLepPt;
	if(thePass) nPassCuts[2][3]++;
	thePass = thePass && TMath::Abs((int)(*eventLeptons.pdgId)[idLep[0]]) == typeSel &&
	          (infilecatv[ifile] == 0 || isGenLep.size() == 1);
        if(thePass) {
          dilep = ( *(TLorentzVector*)(eventLeptons.p4->At(idLep[0])) );
          nPassCuts[2][4]++;
          deltaPhiDileptonMet = TMath::Abs(dilep.DeltaPhi(*((TLorentzVector*)(*eventMet.p4)[0])));
          mtW = TMath::Sqrt(2.0*dilep.Pt()*((TLorentzVector*)(*eventMet.p4)[0])->Pt()*(1.0 - cos(deltaPhiDileptonMet)));
	  if(mtW > 50) passSel[2] = kTRUE;
	}
      }
      if(1){ // Z->lg
        bool thePass = idLep.size() == 1 && idTight[0] == 1 && ((TLorentzVector*)(*eventLeptons.p4)[idLep[0]])->Pt() > minLepPt &&
	               idPho.size() >= 1;
	if(thePass) nPassCuts[3][3]++;
	thePass = thePass && TMath::Abs((int)(*eventLeptons.pdgId)[idLep[0]]) == typeSel;
        if(thePass) {
          nPassCuts[3][4]++;
          dilep = ( ( *(TLorentzVector*)(eventLeptons.p4->At(idLep[0])) ) + 
                    ( *(TLorentzVector*)(eventPhotons.p4->At(idPho[0])) ) ); 
          if(TMath::Abs(dilep.M()-91.1876)<10.0) passSel[3] = kTRUE;	
	}
      }

      if(passSel[0] == kTRUE) nPassCuts[0][5]++;
      if(passSel[1] == kTRUE) nPassCuts[1][5]++;
      if(passSel[2] == kTRUE) nPassCuts[2][5]++;
      if(passSel[3] == kTRUE) nPassCuts[3][5]++;
      if(passSel[0] == kFALSE && passSel[1] == kFALSE && passSel[2] == kFALSE && passSel[3] == kFALSE) continue;

      if(mtW < 0){
        deltaPhiDileptonMet = TMath::Abs(dilep.DeltaPhi(*((TLorentzVector*)(*eventMet.p4)[0])));
        mtW = TMath::Sqrt(2.0*dilep.Pt()*((TLorentzVector*)(*eventMet.p4)[0])->Pt()*(1.0 - cos(deltaPhiDileptonMet)));
      }

      double mcWeight = eventMonteCarlo.mcWeight;
      if(infilecatv[ifile] == 0) mcWeight = 1.0;
      // luminosity
      double theLumi  = 1.0; if(infilecatv[ifile] != 0) theLumi  = lumi;
      // pile-up
      double puWeight = 1.0; if(infilecatv[ifile] != 0) puWeight = nPUScaleFactor(fhDPU, (double)eventMonteCarlo.puTrueInt);
      // lepton efficiency
      double effSF = 1.0;
      if(infilecatv[ifile] != 0){
        for(unsigned int nl=0; nl<idLep.size(); nl++){
          effSF = effSF * effhDScaleFactor(((TLorentzVector*)(*eventLeptons.p4)[idLep[nl]])->Pt(),
	        ((TLorentzVector*)(*eventLeptons.p4)[idLep[nl]])->Eta(),TMath::Abs((int)(*eventLeptons.pdgId)[idLep[nl]]),
		typeLepSel.Data(),fhDMuMediumSF,fhDElMediumSF,fhDElTightSF,fhDmutrksfptg10,fhDeltrksf,eventVertex.npv,true,fhDMuIsoSF,fhDVeryTightSF,true);
        }
      }
      
      int iPt = -1;
      if     (((TLorentzVector*)(*eventLeptons.p4)[idLep[0]])->Pt() < 15){
        iPt = 0;
      }
      else if(((TLorentzVector*)(*eventLeptons.p4)[idLep[0]])->Pt() < 20){
        iPt = 1;
      }
      else if(((TLorentzVector*)(*eventLeptons.p4)[idLep[0]])->Pt() < 25){
        iPt = 2;
      }
      else if(((TLorentzVector*)(*eventLeptons.p4)[idLep[0]])->Pt() < 30){
        iPt = 3;
      }
      else if(((TLorentzVector*)(*eventLeptons.p4)[idLep[0]])->Pt() < 40){
        iPt = 4;
      }
      else {
        iPt = 5;
      }
      int iEta = -1;
      if     (TMath::Abs(((TLorentzVector*)(*eventLeptons.p4)[idLep[0]])->Eta()) < 0.5){
         iEta = 0;
      }
      else if(TMath::Abs(((TLorentzVector*)(*eventLeptons.p4)[idLep[0]])->Eta()) < 1.0){
         iEta = 1;
      }
      else if(TMath::Abs(((TLorentzVector*)(*eventLeptons.p4)[idLep[0]])->Eta()) < 1.5){
         iEta = 2;
      }
      else if(TMath::Abs(((TLorentzVector*)(*eventLeptons.p4)[idLep[0]])->Eta()) < 2.0){
         iEta = 3;
      }
      else {
         iEta = 4;
      }

      double thePrescale = 1.0;
      if(infilecatv[ifile] != 0 && applyPrescale == 1) thePrescale = prescale[iPt];

      double totalWeight = mcWeight*theLumi*puWeight*effSF*thePrescale*theMCPrescale;

      if(passSel[0] == kTRUE) {
        if(infilecatv[ifile] == 0) denSFDA[iPt] = denSFDA[iPt] + totalWeight;
        else                       denSFBG[iPt] = denSFBG[iPt] + totalWeight;
        // Adding trailing pt weights
	int iPt2 = -1;
	if     (((TLorentzVector*)(*eventLeptons.p4)[idLep[1]])->Pt() < 15){
          iPt2 = 0;
	}
	else if(((TLorentzVector*)(*eventLeptons.p4)[idLep[1]])->Pt() < 20){
          iPt2 = 1;
	}
	else if(((TLorentzVector*)(*eventLeptons.p4)[idLep[1]])->Pt() < 25){
          iPt2 = 2;
	}
	else if(((TLorentzVector*)(*eventLeptons.p4)[idLep[1]])->Pt() < 30){
          iPt2 = 3;
	}
	else if(((TLorentzVector*)(*eventLeptons.p4)[idLep[1]])->Pt() < 40){
          iPt2 = 4;
	}
	else {
          iPt2 = 5;
	}
        if(infilecatv[ifile] == 0) denSFDA[iPt2] = denSFDA[iPt2] + totalWeight;
        else                       denSFBG[iPt2] = denSFBG[iPt2] + totalWeight;
      }

      if(passSel[1] == kTRUE) {
	if(infilecatv[ifile] == 0) {
                              denFRDA[iEta][iPt] = denFRDA[iEta][iPt] + totalWeight;
          if(idTight[0] == 1) numFRDA[iEta][iPt] = numFRDA[iEta][iPt] + totalWeight;
	}
	else {
                              denFRBG[iEta][iPt] = denFRBG[iEta][iPt] + totalWeight;
          if(idTight[0] == 1) numFRBG[iEta][iPt] = numFRBG[iEta][iPt] + totalWeight;
	}
      }

      // ZLG study
      if(passSel[0] == kTRUE && ((TLorentzVector*)(*eventLeptons.p4)[idLep[0]])->Pt() > 20 && 
                                ((TLorentzVector*)(*eventLeptons.p4)[idLep[1]])->Pt() > 20) {
	int iPt1 = -1;
	if     (((TLorentzVector*)(*eventLeptons.p4)[idLep[0]])->Pt() < 25){
          iPt1 = 0;
	}
	else if(((TLorentzVector*)(*eventLeptons.p4)[idLep[0]])->Pt() < 30){
          iPt1 = 1;
	}
	else if(((TLorentzVector*)(*eventLeptons.p4)[idLep[0]])->Pt() < 40){
          iPt1 = 2;
	}
	else {
          iPt1 = 3;
	}
        if(TMath::Abs(((TLorentzVector*)(*eventLeptons.p4)[idLep[0]])->Eta()) > 1.5) iPt1 = iPt1 + 4;

	int iPt2 = -1;
	if     (((TLorentzVector*)(*eventLeptons.p4)[idLep[1]])->Pt() < 25){
          iPt2 = 0;
	}
	else if(((TLorentzVector*)(*eventLeptons.p4)[idLep[1]])->Pt() < 30){
          iPt2 = 1;
	}
	else if(((TLorentzVector*)(*eventLeptons.p4)[idLep[1]])->Pt() < 40){
          iPt2 = 2;
	}
	else {
          iPt2 = 3;
	}
        if(TMath::Abs(((TLorentzVector*)(*eventLeptons.p4)[idLep[1]])->Eta()) > 1.5) iPt2 = iPt2 + 4;

        if(infilecatv[ifile] == 0) denLGTDA[iPt1] = denLGTDA[iPt1] + totalWeight;
        else                       denLGTBG[iPt1] = denLGTBG[iPt1] + totalWeight;
        if(infilecatv[ifile] == 0) denLGTDA[iPt2] = denLGTDA[iPt2] + totalWeight;
        else                       denLGTBG[iPt2] = denLGTBG[iPt2] + totalWeight;
      }

      if(passSel[3] == kTRUE && ((TLorentzVector*)(*eventLeptons.p4)[idLep[0]])->Pt() > 20 && 
                                ((TLorentzVector*)(*eventLeptons.p4)[idPho[0]])->Pt() > 20) {
	int iPt2 = -1;
	if     (((TLorentzVector*)(*eventLeptons.p4)[idPho[0]])->Pt() < 25){
          iPt2 = 0;
	}
	else if(((TLorentzVector*)(*eventLeptons.p4)[idPho[0]])->Pt() < 30){
          iPt2 = 1;
	}
	else if(((TLorentzVector*)(*eventLeptons.p4)[idPho[0]])->Pt() < 40){
          iPt2 = 2;
	}
	else {
          iPt2 = 3;
	}
        if(TMath::Abs(((TLorentzVector*)(*eventLeptons.p4)[idPho[0]])->Eta()) > 1.5) iPt2 = iPt2 + 4;

        if(infilecatv[ifile] == 0) denLGPDA[iPt2] = denLGPDA[iPt2] + totalWeight;
        else                       denLGPBG[iPt2] = denLGPBG[iPt2] + totalWeight;
      }

      for(int thePlot=0; thePlot<allPlots; thePlot++){
        double theVar = 0.0;
        if     (thePlot ==  0 || thePlot == 10 || thePlot == 20 || thePlot == 30) theVar = TMath::Min(dilep.M(),199.999);
        else if(thePlot ==  1 || thePlot == 11 || thePlot == 21 || thePlot == 31) theVar = TMath::Min((double)((TLorentzVector*)(*eventMet.p4)[0])->Pt(),199.999);
        else if(thePlot ==  2 || thePlot == 12 || thePlot == 22 || thePlot == 32) theVar = TMath::Min(dilep.Pt(),199.999);
        else if(thePlot ==  3 || thePlot == 13 || thePlot == 23 || thePlot == 33) theVar = TMath::Min(mtW,199.999);
        else if(thePlot ==  4 || thePlot == 14 || thePlot == 24 || thePlot == 34) theVar = TMath::Min((double)idJet20.size(),6.499);
        else if(thePlot ==  5 || thePlot == 15 || thePlot == 25 || thePlot == 35) theVar = TMath::Min((double)idJet30.size(),6.499);
        else if(thePlot ==  6 || thePlot == 16 || thePlot == 26 || thePlot == 36) theVar = TMath::Min((double)eventEvent.rho,39.999);
        else if(thePlot ==  7 || thePlot == 17 || thePlot == 27 || thePlot == 37) theVar = TMath::Min((double)eventVertex.npv,39.499);
        else if(thePlot ==  8 || thePlot == 18 || thePlot == 28 || thePlot == 38) theVar = TMath::Min(((TLorentzVector*)(*eventLeptons.p4)[idLep[0]])->Pt(),199.999);
        else if(thePlot ==  9 || thePlot == 19 || thePlot == 29 || thePlot == 39) theVar = TMath::Min(TMath::Abs(((TLorentzVector*)(*eventLeptons.p4)[idLep[0]])->Eta()),2.499);
        if     (thePlot >=  0 && thePlot <=  9 && passSel[0] == kTRUE) histo[thePlot][infilecatv[ifile]]->Fill(theVar,totalWeight);
        else if(thePlot >= 10 && thePlot <= 19 && passSel[1] == kTRUE) histo[thePlot][infilecatv[ifile]]->Fill(theVar,totalWeight);
        else if(thePlot >= 20 && thePlot <= 29 && passSel[2] == kTRUE) histo[thePlot][infilecatv[ifile]]->Fill(theVar,totalWeight);
        else if(thePlot >= 30 && thePlot <= 39 && passSel[3] == kTRUE) histo[thePlot][infilecatv[ifile]]->Fill(theVar,totalWeight);
      }
    }

    for(int ns=0; ns<4; ns++){
      printf("eff_cuts(%d): ",ns);
      for(int nc=0; nc<6; nc++){
        double nminusone = the_input_tree->GetEntries();
        if(nc>0) nminusone = nPassCuts[ns][nc-1];
        printf("(%d): %8.5f(%8.5f) | ",nc,100*(double)nPassCuts[ns][nc]/the_input_tree->GetEntries(),100*(double)nPassCuts[ns][nc]/nminusone);
      }
      printf("\n");
    }
    the_input_file->Close();
  } // end of chain

  for(int ns=0; ns<4; ns++){
    printf("sel(%d) ",ns);
    for(int nc=0; nc<8; nc++){
      printf("(%d): %5.2f | ",nc,histo[ns*10][nc]->GetSumOfWeights());
    }
    printf("totalMC: %5.2f\n",histo[ns*10][1]->GetSumOfWeights()+histo[ns*10][2]->GetSumOfWeights()+histo[ns*10][3]->GetSumOfWeights()+
                              histo[ns*10][4]->GetSumOfWeights()+histo[ns*10][5]->GetSumOfWeights()+histo[ns*10][6]->GetSumOfWeights()+histo[ns*10][7]->GetSumOfWeights());
  }

  printf("Prescale**********************\n");
  for(int iPt=0; iPt<6; iPt++){
    printf("(%d): (%6.1f)/(%6.1f)=%7.5f | ",iPt,denSFDA[iPt],denSFBG[iPt],denSFDA[iPt]/denSFBG[iPt]);
    if(iPt==5) printf("\n");
  }

  printf("ZLG********************** T & P\n");
  for(int iPt=0; iPt<8; iPt++){
    printf("(%d): (%6.1f)/(%6.1f)=%7.5f | ",iPt,denLGTDA[iPt],denLGTBG[iPt],denLGTDA[iPt]/denLGTBG[iPt]);
    if(iPt==7) printf("\n");
  }
  for(int iPt=0; iPt<8; iPt++){
    printf("(%d): (%6.1f)/(%6.1f)=%7.5f | ",iPt,denLGPDA[iPt],denLGPBG[iPt],denLGPDA[iPt]/denLGPBG[iPt]);
    if(iPt==7) printf("\n");
  }

  printf("FakeRates**********************\n");
  double sumTot[2] = {0.,0.};
  for(int iEta=0; iEta<5; iEta++){
    for(int iPt=0; iPt<6; iPt++){
      sumTot[0] = sumTot[0] + denFRDA[iEta][iPt];
      sumTot[1] = sumTot[1] + denFRBG[iEta][iPt];
      printf("(%d,%d): (%6.1f-%6.1f)/(%6.1f-%6.1f)=%4.3f | ",iPt,iEta,numFRDA[iEta][iPt],numFRBG[iEta][iPt] , denFRDA[iEta][iPt],denFRBG[iEta][iPt],
                                                                     (numFRDA[iEta][iPt]-numFRBG[iEta][iPt])/(denFRDA[iEta][iPt]-denFRBG[iEta][iPt]));
      if(iPt==5) printf("\n");
    }
  }
  printf("sumTot(da/bg) = %f / %f = %f\n",sumTot[0],sumTot[1],sumTot[0]/sumTot[1]);

  if(typeSel == 11) printf("double fake_rate_e[%d][%d] = {\n",5,6);
  else              printf("double fake_rate_m[%d][%d] = {\n",5,6);
  for(int iEta=0; iEta<5; iEta++){
    for(int iPt=0; iPt<6; iPt++){
      printf("%4.3f",TMath::Abs((numFRDA[iEta][iPt]-numFRBG[iEta][iPt])/(denFRDA[iEta][iPt]-denFRBG[iEta][iPt])));
      if(iPt!=5||iEta!=4) printf(",");
      if(iPt==5) printf("\n");
    }
  }
  printf("};\n");
  
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    char output[200];
    sprintf(output,"histo_fake_%d_%s_%d.root",typeSel,typeLepSel.Data(),thePlot);	  
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    for(int np=0; np<histBins; np++) histo[thePlot][np]->Write();
    outFilePlotsNote->Close();
  }

}
