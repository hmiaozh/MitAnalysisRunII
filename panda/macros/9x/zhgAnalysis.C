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

const bool isDEBUG = false;
const double mcPrescale = 1;
const bool usePureMC = true;
enum selType                     { ZHGSEL,   BTAGSEL,   ZLGSEL,   WZSEL,   WZGSEL,   ZZSEL,   WWSEL, nSelTypes};
TString selTypeName[nSelTypes]=  {"ZHGSEL", "BTAGSEL", "ZLGSEL", "WZSEL", "WZGSEL", "ZZSEL", "WWSEL"};

void zhgAnalysis(
unsigned int period = 0
){

  double lumi = 35.9;
  if     (period == 1) lumi = 19.3;
  else if(period == 2) lumi = 16.6;
  //*******************************************************
  //Input Files
  //*******************************************************
  TString filesPath    = "/data/t3home000/ceballos/panda/v_007_0/";
  vector<TString> infileName_;
  vector<int> infileCat_;


  infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	       infileCat_.push_back(0);
  if(usePureMC == true){
  infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data())); infileCat_.push_back(1);
  infileName_.push_back(Form("%sDYJetsToLL_M-50_NLO.root",filesPath.Data()));  infileCat_.push_back(1);
  infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	       infileCat_.push_back(1);
  infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	       infileCat_.push_back(1);
  infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		       infileCat_.push_back(1);
  infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		       infileCat_.push_back(1);
  }
  infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));		       infileCat_.push_back(2);
  infileName_.push_back(Form("%sWGstar.root" ,filesPath.Data()));	       infileCat_.push_back(2);

  infileName_.push_back(Form("%sWZ.root" ,filesPath.Data()));		       infileCat_.push_back(3);

  infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	       infileCat_.push_back(4);
  infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	       infileCat_.push_back(4);

  infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	       infileCat_.push_back(5);
  infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	       infileCat_.push_back(5);

  infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	       infileCat_.push_back(6);

  infileName_.push_back(Form("%sDarkPhoton_ZH_powheg_M-125.root" ,filesPath.Data())); infileCat_.push_back(7);

  TFile *fLepton_Fakes = TFile::Open(Form("MitAnalysisRunII/data/80x/histoFakeEtaPt_80x_37ifb.root"));
  TH2D* histoFakeEffSelMediumEtaPt_m = (TH2D*)fLepton_Fakes->Get("histoFakeEffSel0EtaPt_0"); histoFakeEffSelMediumEtaPt_m->SetDirectory(0);
  TH2D* histoFakeEffSelMediumEtaPt_e = (TH2D*)fLepton_Fakes->Get("histoFakeEffSel0EtaPt_1"); histoFakeEffSelMediumEtaPt_e->SetDirectory(0);
  TH2D* histoFakeEffSelTightEtaPt_m  = (TH2D*)fLepton_Fakes->Get("histoFakeEffSel2EtaPt_0"); histoFakeEffSelTightEtaPt_m ->SetDirectory(0);
  TH2D* histoFakeEffSelTightEtaPt_e  = (TH2D*)fLepton_Fakes->Get("histoFakeEffSel2EtaPt_1"); histoFakeEffSelTightEtaPt_e ->SetDirectory(0);
  fLepton_Fakes->Close();

  TFile *fLepton_Eta_SF = TFile::Open(Form("MitAnalysisRunII/data/80x/scalefactors_80x_eta_sf_37ifb_period%d.root",period));
  TH1D* scalefactors_Muon_Eta = (TH1D*)fLepton_Eta_SF->Get("scalefactors_Muon_Eta"); scalefactors_Muon_Eta->SetDirectory(0);
  TH1D* scalefactors_Electron_Eta = (TH1D*)fLepton_Eta_SF->Get("scalefactors_Electron_Eta"); scalefactors_Electron_Eta->SetDirectory(0);
  fLepton_Eta_SF->Close();

  TFile *fLepton_SF_mu_central = TFile::Open(Form("MitAnalysisRunII/data/80x/scalefactors_80x_dylan_MediumIdOnly_period%d.root",period));
  TH2D* scalefactors_Medium_Muon = (TH2D*)fLepton_SF_mu_central->Get("scalefactors_Medium_Muon"); scalefactors_Medium_Muon->SetDirectory(0);
  fLepton_SF_mu_central->Close();

  TFile *fLepton_SF_el_central = TFile::Open(Form("MitAnalysisRunII/data/80x/scalefactors_80x_dylan_MediumIdOnly_period%d.root",period));
  TH2D* scalefactors_Medium_Electron = (TH2D*)fLepton_SF_el_central->Get("scalefactors_Medium_Electron"); scalefactors_Medium_Electron->SetDirectory(0);
  fLepton_SF_el_central->Close();

  TFile *fPhotonSF = TFile::Open(Form("MitAnalysisRunII/data/80x/photon_scalefactors_37ifb.root"));
  TH2D *fhDPhotonSF       = (TH2D*)(fPhotonSF->Get("EGamma_SF2D")); assert(fhDPhotonSF); fhDPhotonSF->SetDirectory(0);
  TH2D *fhDElectronVetoSF = (TH2D*)(fPhotonSF->Get("Scaling_Factors_HasPix_R9 Inclusive")); assert(fhDElectronVetoSF); fhDElectronVetoSF->SetDirectory(0);
  delete fPhotonSF;

  double getMaxPtForSFs[2] = {scalefactors_Medium_Muon                  ->GetYaxis()->GetBinCenter(scalefactors_Medium_Muon		     ->GetNbinsY()),
                              scalefactors_Medium_Electron              ->GetYaxis()->GetBinCenter(scalefactors_Medium_Electron		     ->GetNbinsY())
		              };

  const int MVAVarType = 0; const int nBinMVA = 5; Double_t xbins[nBinMVA+1] = {0, 75, 100, 125, 150, 175}; TString addChan = "";

  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 35;
  const int histBins = 8;
  TH1D* histo[allPlots][histBins];
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
    else if(thePlot >=  34 && thePlot <=  34) {nBinPlot = 2;   xminPlot = -0.5; xmaxPlot = 1.5;}
    TH1D* histos;
    if(thePlot <= 2) histos = new TH1D("histos", "histos", nBinMVA, xbins);
    else             histos = new TH1D("histos", "histos", nBinPlot, xminPlot, xmaxPlot);
    histos->Sumw2();
    for(int i=0; i<histBins; i++) histo[thePlot][i] = (TH1D*) histos->Clone(Form("histo%d",i));
    histos->Reset();histos->Clear();
  }

  //*******************************************************
  // Chain Loop
  //*******************************************************
  for(UInt_t ifile=0; ifile<infileName_.size(); ifile++) {
    printf("sampleNames(%d): %s\n",ifile,infileName_[ifile].Data());
    TFile *the_input_file = TFile::Open(infileName_[ifile].Data());
    TTree *the_input_tree = (TTree*)the_input_file->FindObjectAny("events");
    
    pandaFlat thePandaFlat(the_input_tree);
    double theMCPrescale = 1.0; if(infileCat_[ifile] != 0) theMCPrescale = mcPrescale;
    Long64_t nentries = thePandaFlat.fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = thePandaFlat.LoadTree(jentry);
      if (ientry < 0) break;
      nb = thePandaFlat.fChain->GetEntry(jentry);   nbytes += nb;
      if (jentry%1000000 == 0) printf("--- reading event %8lld (%8lld) of %8lld\n",jentry,ientry,nentries);
      if (infileCat_[ifile] != 0 && jentry%(int)theMCPrescale != 0) continue;

      if(infileCat_[ifile] == 0 && ((period == 1 && thePandaFlat.runNumber > 278802) || (period == 2 && thePandaFlat.runNumber <= 278802))) continue;

      bool passTrigger = (thePandaFlat.trigger & kEMuTrig)       == kEMuTrig        || (thePandaFlat.trigger & kDoubleMuTrig)  == kDoubleMuTrig  ||
                         (thePandaFlat.trigger & kSingleMuTrig)  == kSingleMuTrig   || (thePandaFlat.trigger & kDoubleEleTrig) == kDoubleEleTrig ||
                         (thePandaFlat.trigger & kSingleEleTrig) == kSingleEleTrig;
      if(passTrigger == false) continue;

      if(thePandaFlat.nLooseLep < 2 || thePandaFlat.nLooseLep > 4) continue;

      vector<float>  looseLepPt,looseLepEta,looseLepPhi;
      vector<int> looseLepSelBit,looseLepPdgId;
      int ptSelCuts[3] = {0,0,0};
      for(int i=0; i<thePandaFlat.nLooseMuon; i++){
        looseLepPt.push_back(thePandaFlat.muonPt[i]);
        looseLepEta.push_back(thePandaFlat.muonEta[i]);
        looseLepPhi.push_back(thePandaFlat.muonPhi[i]);
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
      if(theCategory != 0 && theCategory != 2 && isNotMCFake == false && usePureMC == false) continue;

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
      if(passLooseLepId == false) continue;
      if(usePureMC == true && countLeptonTight != idLep.size()) continue;

      int lepType = -1;
      if     (thePandaFlat.nLooseLep == 2){
        if     (abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13) lepType = 0;
        else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11) lepType = 1;
        else  lepType = 2;
      }
      else if(thePandaFlat.nLooseLep == 3){
        if     (abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13 && abs(looseLepPdgId[2])==13) lepType = 0;
        else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11 && abs(looseLepPdgId[2])==11) lepType = 3;
        else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11) lepType = 1;
        else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[2])==11) lepType = 1;
        else if(abs(looseLepPdgId[1])==11 && abs(looseLepPdgId[2])==11) lepType = 1;
        else if(abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13) lepType = 2;
        else if(abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[2])==13) lepType = 2;
        else if(abs(looseLepPdgId[1])==13 && abs(looseLepPdgId[2])==13) lepType = 2;
        else {printf("Impossible dilepton combination: %d %d %d\n",looseLepPdgId[0],looseLepPdgId[1],looseLepPdgId[2]); continue;}
      }
      else if(thePandaFlat.nLooseLep == 4){
        int nmu = (abs(looseLepPdgId[0])==13) + (abs(looseLepPdgId[1])==13) + (abs(looseLepPdgId[2])==13) + (abs(looseLepPdgId[3])==13);
        int nel = (abs(looseLepPdgId[0])==11) + (abs(looseLepPdgId[1])==11) + (abs(looseLepPdgId[2])==11) + (abs(looseLepPdgId[3])==11);
        if     (nmu == 4 && nel == 0) lepType = 0;
        else if(nmu == 0 && nel == 4) lepType = 1;
        else if(nmu == 2 && nel == 2) lepType = 2;
        else if(nmu == 3 && nel == 1) lepType = 3;
        else if(nmu == 1 && nel == 3) lepType = 3;
        else {printf("Impossible dilepton combination: %d %d %d %d\n",looseLepPdgId[0],looseLepPdgId[1],looseLepPdgId[2],looseLepPdgId[3]); continue;}
      }

      TLorentzVector vMET,vTrkMet;
      vMET.SetPtEtaPhiM(thePandaFlat.pfmet,0.0,thePandaFlat.pfmetphi,0.0);
      vTrkMet.SetPtEtaPhiM(thePandaFlat.trkmet,0.0,thePandaFlat.trkmetphi,0.0);

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
	if(whichWln >= 0 && tightWlnId == true) idLep[whichWln] = 2;
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

      double dPhiJetMET = -1.0;
      vector<int> idJet30;
      vector<TLorentzVector> vJet;
      TLorentzVector vJetTemp;
      if(thePandaFlat.jet1Pt > 10) {vJetTemp.SetPtEtaPhiM(thePandaFlat.jet1Pt,thePandaFlat.jet1Eta,thePandaFlat.jet1Phi,0.0); vJet.push_back(vJetTemp);}
      if(thePandaFlat.jet2Pt > 10) {vJetTemp.SetPtEtaPhiM(thePandaFlat.jet2Pt,thePandaFlat.jet2Eta,thePandaFlat.jet2Phi,0.0); vJet.push_back(vJetTemp);}
      for(unsigned int nj=0; nj<vJet.size(); nj++){

        Bool_t isLepton = kFALSE;
	for(unsigned int i=0; i<vLoose.size(); i++){
	  if(vLoose[i].Pt() > 0) if(vLoose[i].DeltaR(vJet[nj]) < 0.3) isLepton = kTRUE;
	}
        if(isLepton == kTRUE) continue;

        if(vJet[nj].Pt() > 30)  idJet30.push_back(nj);

        if( dPhiJetMET == -1 && vJet[nj].Pt() > 30) dPhiJetMET = TMath::Abs(vJet[nj].DeltaPhi(vMET));
      }

      double dPhiGMET = 0;
      double mTGMET = 0;
      TLorentzVector dilep = vZ1l1+vZ1l2;
      TLorentzVector dilepG = vZ1l1+vZ1l2;
      if(theMinSelType >= 0){
        dilepG = dilepG + theG;
	dPhiGMET = TMath::Abs(theG.DeltaPhi(vMET));
        mTGMET = TMath::Sqrt(2.0*theG.Pt()*vMET.Pt()*(1.0 - cos(dPhiGMET)));
      }

      double dPhiDiLepGMET = TMath::Abs(dilepG.DeltaPhi(vMET));
      bool passZMass = mllmin > 4.0 && TMath::Abs(mllZ-91.1876) < 15.0;
      bool passZMassSB = mllZ > 110 && mllZ < 200;
      bool passMET    = vMET.Pt() > 100;
      bool passMETMin = vMET.Pt() > 60;
      bool passPTLL   = dilep.Pt() > 60;

      double ptFracG = TMath::Abs(dilepG.Pt()-vMET.Pt())/dilep.Pt();
      bool passPTFracG   = ptFracG < 0.4;
      bool passDPhiZGMET = dPhiDiLepGMET > 2.5;
      bool passNjets = thePandaFlat.nJot <= 2;

      bool passBtagVeto = thePandaFlat.jetNMBtags == 0;
      double dphill = TMath::Abs(vZ1l1.DeltaPhi(vZ1l2));
      double detall = TMath::Abs(vZ1l1.Eta()-vZ1l2.Eta());
      double drll = sqrt(dphill*dphill+detall*detall);

      bool passDPhiJetMET   = dPhiJetMET == -1 || dPhiJetMET >= 0.5;
      bool passTauVeto      = thePandaFlat.nTau == 0;
      bool passMT           = mTGMET < 175.0;

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

     for(int i=0; i<10; i++) passNMinusOne[i] = mllmin > 4.0 && theMinSelType == 0 && lepType != 2 && passNMinusOne[i];

      double totalWeight = 1.0;
      if(theCategory != 0){
        double the_eta_sf[4] = {1.0, 1.0, 1.0, 1.0};
        double sfWeightLepEff[4] = {1.0, 1.0, 1.0, 1.0};
	for(unsigned int i=0; i<vLoose.size(); i++){
          if(abs(looseLepPdgId[i])==13){
            double etal = looseLepEta[i]; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
            int binEta = scalefactors_Muon_Eta->GetXaxis()->FindFixBin(etal);
            the_eta_sf[i] = scalefactors_Muon_Eta->GetBinContent(binEta);
          } else {
            double etal = looseLepEta[i]; if(etal >= 2.5) etal = 2.4999; else if(etal <= -2.5) etal = -2.4999;
            int binEta = scalefactors_Electron_Eta->GetXaxis()->FindFixBin(etal);
            the_eta_sf[i] = scalefactors_Electron_Eta->GetBinContent(binEta);
          }        
          if(abs(looseLepPdgId[i])==13){
            double etal = looseLepEta[i]; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
            int binXT   = scalefactors_Medium_Muon->GetXaxis()->FindFixBin(etal);
            int binYT_c = scalefactors_Medium_Muon->GetYaxis()->FindFixBin(TMath::Min((double)looseLepPt[i],getMaxPtForSFs[0]));
	    sfWeightLepEff[i] = scalefactors_Medium_Muon->GetBinContent(binXT,binYT_c);
          } else {
            double etal = looseLepEta[i]; if(etal >= 2.5) etal = 2.4999; else if(etal <= -2.5) etal = -2.4999;
            int binXT   = scalefactors_Medium_Electron->GetXaxis()->FindFixBin(etal);
            int binYT_c = scalefactors_Medium_Electron->GetYaxis()->FindFixBin(TMath::Min((double)looseLepPt[i],getMaxPtForSFs[1]));
	    sfWeightLepEff[i] = scalefactors_Medium_Electron->GetBinContent(binXT,binYT_c);
          }
        }

        totalWeight = thePandaFlat.normalizedWeight * lumi * thePandaFlat.sf_pu * the_eta_sf[0] * the_eta_sf[1] * the_eta_sf[2] * the_eta_sf[3] * sfWeightLepEff[0] * sfWeightLepEff[1] * sfWeightLepEff[2] * sfWeightLepEff[3] * theMCPrescale;

        if     (infileCat_[ifile] == 3)                                                totalWeight = totalWeight * thePandaFlat.sf_wz;
	else if(infileCat_[ifile] == 4 && infileName_[ifile].Contains("qqZZ") == true) totalWeight = totalWeight * thePandaFlat.sf_zz;

	if(passPhoSel == true) {
          double photonSF = 1.0;
          if     (thePandaFlat.looseGenPho1PdgId == 1) {
            photonSF = electronToPhotonSF(vPhoton.Pt());
	  }
          else if(thePandaFlat.looseGenPho1PdgId == 3) {
            photonSF = effhDPhotonScaleFactor(vPhoton.Pt(), vPhoton.Eta(), "medium", fhDPhotonSF, fhDElectronVetoSF);
	  }
	  totalWeight = totalWeight * photonSF;
	}

      }

      if(usePureMC == false && countLeptonTight != idLep.size()){
        double fakeSF = 1.0;
        for(unsigned int nl=0; nl<idLep.size(); nl++){
          if(idLep[nl] != 0) continue;
          bool applyTight = false;
          if(whichWln == (int)nl) applyTight = true;
          if(nl == 0) fakeSF = fakeSF * fakeRateFactor(TMath::Min((double)looseLepPt[0],44.999),TMath::Abs(looseLepEta[0]),TMath::Abs(looseLepPdgId[0]),applyTight,histoFakeEffSelMediumEtaPt_m,histoFakeEffSelMediumEtaPt_e,histoFakeEffSelTightEtaPt_m,histoFakeEffSelTightEtaPt_e);
          if(nl == 1) fakeSF = fakeSF * fakeRateFactor(TMath::Min((double)looseLepPt[1],44.999),TMath::Abs(looseLepEta[1]),TMath::Abs(looseLepPdgId[1]),applyTight,histoFakeEffSelMediumEtaPt_m,histoFakeEffSelMediumEtaPt_e,histoFakeEffSelTightEtaPt_m,histoFakeEffSelTightEtaPt_e);
          if(nl == 2) fakeSF = fakeSF * fakeRateFactor(TMath::Min((double)looseLepPt[2],44.999),TMath::Abs(looseLepEta[2]),TMath::Abs(looseLepPdgId[2]),applyTight,histoFakeEffSelMediumEtaPt_m,histoFakeEffSelMediumEtaPt_e,histoFakeEffSelTightEtaPt_m,histoFakeEffSelTightEtaPt_e);
          if(nl == 3) fakeSF = fakeSF * fakeRateFactor(TMath::Min((double)looseLepPt[3],44.999),TMath::Abs(looseLepEta[3]),TMath::Abs(looseLepPdgId[3]),applyTight,histoFakeEffSelMediumEtaPt_m,histoFakeEffSelMediumEtaPt_e,histoFakeEffSelTightEtaPt_m,histoFakeEffSelTightEtaPt_e);
          theCategory = 1;
        }
        if     (infileCat_[ifile] != 0 && countLeptonTight == idLep.size()-4) fakeSF = +1.0 * fakeSF; // fourth fake, MC
        else if(infileCat_[ifile] != 0 && countLeptonTight == idLep.size()-3) fakeSF = -1.0 * fakeSF; // triple fake, MC
        else if(infileCat_[ifile] != 0 && countLeptonTight == idLep.size()-2) fakeSF = +1.0 * fakeSF; // double fake, MC
        else if(infileCat_[ifile] != 0 && countLeptonTight == idLep.size()-1) fakeSF = -1.0 * fakeSF; // single fake, MC
        else if(infileCat_[ifile] == 0 && countLeptonTight == idLep.size()-4) fakeSF = -1.0 * fakeSF; // fourth fake, data
        else if(infileCat_[ifile] == 0 && countLeptonTight == idLep.size()-3) fakeSF = +1.0 * fakeSF; // triple fake, data
        else if(infileCat_[ifile] == 0 && countLeptonTight == idLep.size()-2) fakeSF = -1.0 * fakeSF; // double fake, data
        else if(infileCat_[ifile] == 0 && countLeptonTight == idLep.size()-1) fakeSF = +1.0 * fakeSF; // single fake, data
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
      if(passNMinusOne[ 5])  histo[29][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNMBtags,3.499),totalWeight);
      if(passNMinusOne[ 6])  histo[30][theCategory]->Fill(TMath::Min(dilep.Pt(),199.999),totalWeight);
      if(passNMinusOne[ 7])  histo[31][theCategory]->Fill(dPhiJetMET,totalWeight);
      if(passNMinusOne[ 8])  histo[32][theCategory]->Fill(TMath::Min((double)thePandaFlat.nTau,3.499),totalWeight);
      if(passNMinusOne[ 9])  histo[33][theCategory]->Fill(TMath::Min(mTGMET,399.999),totalWeight);
      if(passAllCuts[ZHGSEL] &&
         lepType != 2)       histo[34][theCategory]->Fill((double)((thePandaFlat.loosePho1SelBit & pTrkVeto) == pTrkVeto),totalWeight);

    } // end events loop
    the_input_file->Close();
  } // end chain loop

  char output[200];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    sprintf(output,"histoZHG_%d.root",thePlot);	
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    double totBck = 0;
    for(int i=1; i<histBins-1; i++) totBck = totBck + histo[thePlot][i]->GetSumOfWeights();
    printf("(%2d) %7.1f vs. %7.1f ",thePlot,histo[thePlot][0]->GetSumOfWeights(),totBck);
    printf("(");
    for(int i=1; i<histBins; i++) printf("%7.1f ",histo[thePlot][i]->GetSumOfWeights());
    printf(")\n");
    for(int np=0; np<histBins; np++) histo[thePlot][np]->Write();
    outFilePlotsNote->Close();
  }

}
