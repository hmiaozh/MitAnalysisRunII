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

void fakeRateAnalysis(
unsigned int period = 0
){

  double minLepPt[2] = {10.0, 12.0};

  double lumi = 35.8;
  if     (period == 1) lumi = 19.3;
  else if(period == 2) lumi = 16.5;
  //*******************************************************
  //Input Files
  //*******************************************************
  TString filesPath    = "/data/t3home000/ceballos/panda/v_003_0/";
  vector<TString> infileName_;
  vector<int> infileCat_;

  infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	       infileCat_.push_back(0);
  infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	       infileCat_.push_back(1);
  infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	       infileCat_.push_back(1);
  infileName_.push_back(Form("%sTT.root" ,filesPath.Data()));		       infileCat_.push_back(1);
  infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		       infileCat_.push_back(1);
  infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	       infileCat_.push_back(1);
  infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	       infileCat_.push_back(1);
  infileName_.push_back(Form("%sWZ.root" ,filesPath.Data()));		       infileCat_.push_back(1);
  infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	       infileCat_.push_back(1);
  infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	       infileCat_.push_back(1);
  infileName_.push_back(Form("%sWGstar.root" ,filesPath.Data()));	       infileCat_.push_back(1);
  infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));		       infileCat_.push_back(1);
  infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	       infileCat_.push_back(1);
  infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data())); infileCat_.push_back(2);
  infileName_.push_back(Form("%sDYJetsToLL_M-50_NLO.root",filesPath.Data()));  infileCat_.push_back(2);
  infileName_.push_back(Form("%sWJets.root" ,filesPath.Data()));               infileCat_.push_back(3);

  TFile *fnpvWeights = TFile::Open(Form("MitAnalysisRunII/data/80x/npvWeights_2016_FakeTriggers.root"));
  TH1D* hDnpvWeights = (TH1D*)fnpvWeights->Get("npvWeights"); hDnpvWeights->SetDirectory(0);
  fnpvWeights->Close();

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

  double getMaxPtForSFs[2] = {scalefactors_Medium_Muon                  ->GetYaxis()->GetBinCenter(scalefactors_Medium_Muon		     ->GetNbinsY()),
                              scalefactors_Medium_Electron              ->GetYaxis()->GetBinCenter(scalefactors_Medium_Electron		     ->GetNbinsY())
		              };

  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 34;
  const int histBins = 4;
  TH1D* histo[allPlots][histBins];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    if     (thePlot >=  0 && thePlot <=  1) {nBinPlot = 120; xminPlot = 91.1876-15; xmaxPlot = 91.1876+15;}
    else if(thePlot >=  2 && thePlot <=  3) {nBinPlot = 100; xminPlot = -0.5; xmaxPlot =99.5;}
    else if(thePlot >=  4 && thePlot <= 33) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot =200;}
    TH1D* histos = new TH1D("histos", "histos", nBinPlot, xminPlot, xmaxPlot);
    histos->Sumw2();
    for(int i=0; i<histBins; i++) histo[thePlot][i] = (TH1D*) histos->Clone(Form("histo%d",i));
    histos->Reset();histos->Clear();
  }

  double prescales[2][7]; for(int i=0; i<2; i++) for(int j=0; j<7; j++) prescales[i][j] = 1.0;
  TH1D* histoZllPt[2][histBins];
  TH1D* histoWlnPt[2][histBins];
  TH2D* histoFakeDenEtaPt[2][histBins];
  TH2D* histoFakeNumSel0EtaPt[2][histBins];
  TH2D* histoFakeNumSel1EtaPt[2][histBins];
  TH2D* histoFakeNumSel2EtaPt[2][histBins];
  TH2D* histoFakeNumSel3EtaPt[2][histBins];
  TH2D* histoFakeNumSel4EtaPt[2][histBins];
  TH2D* histoFakeEffSel0EtaPt[2];
  TH2D* histoFakeEffSel1EtaPt[2];
  TH2D* histoFakeEffSel2EtaPt[2];
  TH2D* histoFakeEffSel3EtaPt[2];
  TH2D* histoFakeEffSel4EtaPt[2];
  for(int i=0; i<2; i++){
    for(int j=0; j<histBins; j++){
      histoZllPt[i][j] = new TH1D(Form("histoZllPt_%d_%d",i,j), Form("histoZllPt_%d_%d",i,j), 7, 10, 45);
      histoWlnPt[i][j] = new TH1D(Form("histoWlnPt_%d_%d",i,j), Form("histoWlnPt_%d_%d",i,j), 7, 10, 45);
      histoFakeDenEtaPt[i][j] = new TH2D(Form("histoFakeDenEtaPt_%d_%d",i,j), Form("histoFakeDenEtaPt_%d_%d",i,j), 6, 0, 2.5, 7, 10, 45);
      histoFakeNumSel0EtaPt[i][j] = new TH2D(Form("histoFakeNumSel0EtaPt_%d_%d",i,j), Form("histoFakeNumSel0EtaPt_%d_%d",i,j), 6, 0, 2.5, 7, 10, 45);
      histoFakeNumSel1EtaPt[i][j] = new TH2D(Form("histoFakeNumSel1EtaPt_%d_%d",i,j), Form("histoFakeNumSel1EtaPt_%d_%d",i,j), 6, 0, 2.5, 7, 10, 45);
      histoFakeNumSel2EtaPt[i][j] = new TH2D(Form("histoFakeNumSel2EtaPt_%d_%d",i,j), Form("histoFakeNumSel2EtaPt_%d_%d",i,j), 6, 0, 2.5, 7, 10, 45);
      histoFakeNumSel3EtaPt[i][j] = new TH2D(Form("histoFakeNumSel3EtaPt_%d_%d",i,j), Form("histoFakeNumSel3EtaPt_%d_%d",i,j), 6, 0, 2.5, 7, 10, 45);
      histoFakeNumSel4EtaPt[i][j] = new TH2D(Form("histoFakeNumSel4EtaPt_%d_%d",i,j), Form("histoFakeNumSel4EtaPt_%d_%d",i,j), 6, 0, 2.5, 7, 10, 45);
      if(j==0){
      histoFakeEffSel0EtaPt[i] = new TH2D(Form("histoFakeEffSel0EtaPt_%d",i), Form("histoFakeEffSel0EtaPt_%d",i), 6, 0, 2.5, 7, 10, 45);
      histoFakeEffSel1EtaPt[i] = new TH2D(Form("histoFakeEffSel1EtaPt_%d",i), Form("histoFakeEffSel1EtaPt_%d",i), 6, 0, 2.5, 7, 10, 45);
      histoFakeEffSel2EtaPt[i] = new TH2D(Form("histoFakeEffSel2EtaPt_%d",i), Form("histoFakeEffSel2EtaPt_%d",i), 6, 0, 2.5, 7, 10, 45);
      histoFakeEffSel3EtaPt[i] = new TH2D(Form("histoFakeEffSel3EtaPt_%d",i), Form("histoFakeEffSel3EtaPt_%d",i), 6, 0, 2.5, 7, 10, 45);
      histoFakeEffSel4EtaPt[i] = new TH2D(Form("histoFakeEffSel4EtaPt_%d",i), Form("histoFakeEffSel4EtaPt_%d",i), 6, 0, 2.5, 7, 10, 45);
      }
    }
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

      if(infileCat_[ifile] == 0 && ((period == 1 && thePandaFlat.runNumber > 278802) || (period == 2 && thePandaFlat.runNumber <= 278802))) continue;

      vector<float>  looseLepPt,looseLepEta,looseLepPhi;
      vector<int> looseLepSelBit,looseLepPdgId,looseLepTripleCharge,looseLepMissingHits;
      int ptSelCuts[3] = {0,0,0};
      for(int i=0; i<thePandaFlat.nLooseMuon; i++){
        looseLepPt.push_back(thePandaFlat.muonPt[i]);
        looseLepEta.push_back(thePandaFlat.muonEta[i]);
        looseLepPhi.push_back(thePandaFlat.muonPhi[i]);
        looseLepSelBit.push_back(thePandaFlat.muonSelBit[i]);
        looseLepPdgId.push_back(thePandaFlat.muonPdgId[i]);
        looseLepTripleCharge.push_back(1);
        looseLepMissingHits.push_back(0);
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
        looseLepTripleCharge.push_back(thePandaFlat.electronTripleCharge[i]);
        looseLepMissingHits.push_back(thePandaFlat.electronNMissingHits[i]);
	if(thePandaFlat.electronPt[i] > 25) ptSelCuts[0]++;
	if(thePandaFlat.electronPt[i] > 20) ptSelCuts[1]++;
	if(thePandaFlat.electronPt[i] > 10) ptSelCuts[2]++;
      }

      if((int)looseLepPt.size() != thePandaFlat.nLooseLep) printf("IMPOSSIBLE\n");

      int lepType = -1;
      TLorentzVector vLoose1,vLoose2;
      bool passFakeTrigger = (thePandaFlat.trigger & (1<<kMuFakeTrig)) != 0 || (thePandaFlat.trigger & (1<<kEleFakeTrig)) != 0;
      bool passPresel = false;
      double mll = 0.0;
      if(passFakeTrigger == true){
	if(thePandaFlat.nLooseLep == 2 && looseLepPdgId[0]+looseLepPdgId[1] == 0){
          if     (abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13 && looseLepPdgId[0]*looseLepPdgId[1]<0) lepType = 0;
          else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11 && looseLepPdgId[0]*looseLepPdgId[1]<0) lepType = 1;
          else if(abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==11 && looseLepPdgId[0]*looseLepPdgId[1]<0) lepType = 2;
          else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==13 && looseLepPdgId[0]*looseLepPdgId[1]<0) lepType = 2;
          else if(abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13 && looseLepPdgId[0]*looseLepPdgId[1]>0) lepType = 3;
          else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11 && looseLepPdgId[0]*looseLepPdgId[1]>0) lepType = 4;
          else if(abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==11 && looseLepPdgId[0]*looseLepPdgId[1]>0) lepType = 5;
          else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==13 && looseLepPdgId[0]*looseLepPdgId[1]>0) lepType = 5;
          else {printf("Impossible dilepton combination: %d %d\n",looseLepPdgId[0],looseLepPdgId[1]); continue;}
          double thePDGMass[2] = {mass_mu, mass_mu};
          if     (lepType == 1) {thePDGMass[0] = mass_el; thePDGMass[1] = mass_el;}
          else if(lepType == 2 && abs(looseLepPdgId[0])==11) {thePDGMass[0] = mass_el;}
          else if(lepType == 2 && abs(looseLepPdgId[1])==11) {thePDGMass[1] = mass_el;}
          vLoose1.SetPtEtaPhiM(looseLepPt[0],looseLepEta[0],looseLepPhi[0],thePDGMass[0]);
          vLoose2.SetPtEtaPhiM(looseLepPt[1],looseLepEta[1],looseLepPhi[1],thePDGMass[1]);
	  mll = (vLoose1+vLoose2).M();
        }
        if(mll > 70.0 || thePandaFlat.nLooseLep == 1) passPresel = true;
      }
      if(passPresel == false) {printf("IMPOSSIBLE\n"); printf("%f %d %f\n",mll,thePandaFlat.nLooseLep,thePandaFlat.diLepMass);}
      if(passPresel == false) return;
      if(passPresel == false) continue;

      int theCategory = infileCat_[ifile];
      bool isNotMCFake = (thePandaFlat.nLooseLep == 1 && thePandaFlat.looseGenLep1PdgId != 0) ||
                         (thePandaFlat.nLooseLep == 2 && thePandaFlat.looseGenLep1PdgId != 0 && thePandaFlat.looseGenLep2PdgId != 0);
      if(theCategory != 0 && isNotMCFake == false) continue;

      bool passMllSel = false;
      TLorentzVector vMet;
      vMet.SetPtEtaPhiM(thePandaFlat.pfmet,0.0,thePandaFlat.pfmetphi,0.0);
      if(thePandaFlat.nLooseLep == 2) {
        passMllSel = TMath::Abs((vLoose1+vLoose2).M()-91.1876) < 15 && lepType <= 1;
      }
      else if(thePandaFlat.nLooseLep == 1) {
        if     (abs(looseLepPdgId[0])==13) lepType = 0;
        else if(abs(looseLepPdgId[0])==11) lepType = 1;
        double thePDGMass[1] = {mass_mu};
        if     (abs(lepType) == 1) {thePDGMass[0] = mass_el;}
        vLoose1.SetPtEtaPhiM(looseLepPt[0],looseLepEta[0],looseLepPhi[0],thePDGMass[0]);
      }

      bool passJetSel = kFALSE;
      if((lepType == 0 && thePandaFlat.nJot >= 1) || 
         (lepType == 1 && thePandaFlat.nJot >= 1)) passJetSel = kTRUE;
      if(passJetSel == kFALSE) continue;

      double deltaPhiLeptonMet = TMath::Abs(vLoose1.DeltaPhi(vMet));
      double mt = TMath::Sqrt(2.0*vLoose1.Pt()*vMet.Pt()*(1.0 - cos(deltaPhiLeptonMet)));

      bool passZSel = thePandaFlat.nLooseLep == 2 && passMllSel && (lepType == 0 || lepType == 1) && vLoose1.Pt() > minLepPt[lepType] && vLoose2.Pt() > minLepPt[lepType] && 
                     (looseLepSelBit[0] & kFake) == kFake && (looseLepSelBit[1] & kFake) == kFake;
      bool passWSel = thePandaFlat.nLooseLep == 1 && mt > 50.0 && vMet.Pt() > 30.0 && vLoose1.Pt() > minLepPt[lepType] && 
                     ((looseLepSelBit[0] & kFake) == kFake);
      bool passWLoose1Sel = thePandaFlat.nLooseLep == 1 && vMet.Pt() > 30.0 && vLoose1.Pt() > minLepPt[lepType] && 
                     ((looseLepSelBit[0] & kFake) == kFake);
      bool passWLoose2Sel = thePandaFlat.nLooseLep == 1 && mt > 50.0 && vLoose1.Pt() > minLepPt[lepType] && 
                     ((looseLepSelBit[0] & kFake) == kFake);
      bool passFakeNumSel = thePandaFlat.nLooseLep == 1 && vMet.Pt() < 30.0 && mt < 20.0 && vLoose1.Pt() > minLepPt[lepType];

      double totalWeight = 1.0;
      if(theCategory != 0){
        int binNpv = hDnpvWeights->GetXaxis()->FindFixBin(TMath::Min((double)thePandaFlat.npv,49.499));
	double npvWeights = hDnpvWeights->GetBinContent(binNpv);
        double the_eta_sf[2] = {1.0, 1.0};
        if(abs(looseLepPdgId[0])==13){
          double etal = looseLepEta[0]; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
          int binEta = scalefactors_Muon_Eta->GetXaxis()->FindFixBin(etal);
          the_eta_sf[0] = scalefactors_Muon_Eta->GetBinContent(binEta);
        } else {
          double etal = looseLepEta[0]; if(etal >= 2.5) etal = 2.4999; else if(etal <= -2.5) etal = -2.4999;
          int binEta = scalefactors_Electron_Eta->GetXaxis()->FindFixBin(etal);
          the_eta_sf[0] = scalefactors_Electron_Eta->GetBinContent(binEta);
        }        
        if(thePandaFlat.nLooseLep == 2){
          if(abs(looseLepPdgId[1])==13){
            double etal = looseLepEta[1]; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
            int binEta = scalefactors_Muon_Eta->GetXaxis()->FindFixBin(etal);
            the_eta_sf[1] = scalefactors_Muon_Eta->GetBinContent(binEta);
          } else {
            double etal = looseLepEta[1]; if(etal >= 2.5) etal = 2.4999; else if(etal <= -2.5) etal = -2.4999;
            int binEta = scalefactors_Electron_Eta->GetXaxis()->FindFixBin(etal);
            the_eta_sf[1] = scalefactors_Electron_Eta->GetBinContent(binEta);
          }
	}
        totalWeight = thePandaFlat.normalizedWeight * lumi * thePandaFlat.sf_pu * the_eta_sf[0] * the_eta_sf[1] * npvWeights;
      }

      int binPt = histoZllPt[0][0]->GetXaxis()->FindFixBin(TMath::Min(vLoose1.Pt(),44.999))-1;
      if(passZSel == true) {
        histo[lepType+ 0][theCategory]->Fill((vLoose1+vLoose2).M(),totalWeight);
        histo[lepType+ 2][theCategory]->Fill(TMath::Min((double)thePandaFlat.npv,99.499),totalWeight);
	histoZllPt[lepType][theCategory]->Fill(TMath::Min(vLoose2.Pt(),44.999),totalWeight);
      }
      if(passWSel == true) {
        histo[lepType+ 4][theCategory]->Fill(TMath::Min(vLoose1.Pt(),199.999),totalWeight);
	histoWlnPt[lepType][theCategory]->Fill(TMath::Min(vLoose1.Pt(),44.999),totalWeight);
      }
      if(passWLoose1Sel == true) {
        histo[lepType+  6 + 2*binPt][theCategory]->Fill(TMath::Min(mt,199.999),totalWeight);
      }
      if(passWLoose2Sel == true) {
        histo[lepType+ 20 + 2*binPt][theCategory]->Fill(TMath::Min(vMet.Pt(),199.999),totalWeight);
      }

      if(passFakeNumSel == true) {
        if((looseLepSelBit[0] & kFake)   == kFake  ) histoFakeDenEtaPt[lepType][theCategory]    ->Fill(TMath::Min(TMath::Abs(vLoose1.Eta()),2.499),TMath::Min(vLoose1.Pt(),44.999),totalWeight);
        if((looseLepSelBit[0] & kFake)   == kFake &&
	   (looseLepSelBit[0] & kMedium) == kMedium) histoFakeNumSel0EtaPt[lepType][theCategory]->Fill(TMath::Min(TMath::Abs(vLoose1.Eta()),2.499),TMath::Min(vLoose1.Pt(),44.999),totalWeight);
        if((looseLepSelBit[0] & kFake)   == kFake &&
	   (looseLepSelBit[0] & kTight) == kTight)   histoFakeNumSel1EtaPt[lepType][theCategory]->Fill(TMath::Min(TMath::Abs(vLoose1.Eta()),2.499),TMath::Min(vLoose1.Pt(),44.999),totalWeight);
        if((looseLepSelBit[0] & kFake)   == kFake &&
	   (looseLepSelBit[0] & kTight) == kTight &&
	   (looseLepSelBit[0] & kDxyz) == kDxyz)     histoFakeNumSel2EtaPt[lepType][theCategory]->Fill(TMath::Min(TMath::Abs(vLoose1.Eta()),2.499),TMath::Min(vLoose1.Pt(),44.999),totalWeight);
        if((looseLepSelBit[0] & kFake)   == kFake &&
	   (looseLepSelBit[0] & kTight) == kTight &&
	   (looseLepSelBit[0] & kDxyz) == kDxyz   &&
	    looseLepMissingHits[0] == 0)             histoFakeNumSel3EtaPt[lepType][theCategory]->Fill(TMath::Min(TMath::Abs(vLoose1.Eta()),2.499),TMath::Min(vLoose1.Pt(),44.999),totalWeight);
        if((looseLepSelBit[0] & kFake)   == kFake &&
	   (looseLepSelBit[0] & kTight) == kTight &&
	   (looseLepSelBit[0] & kDxyz) == kDxyz   &&
	    looseLepMissingHits[0] == 0           &&
	    looseLepTripleCharge[0] == 1)            histoFakeNumSel4EtaPt[lepType][theCategory]->Fill(TMath::Min(TMath::Abs(vLoose1.Eta()),2.499),TMath::Min(vLoose1.Pt(),44.999),totalWeight);
      }

    } // end events loop
    the_input_file->Close();
  } // end chain loop

  char output[200];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    sprintf(output,"histoFake_%d.root",thePlot);	
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    double totBck = 0;
    for(int i=1; i<histBins; i++) totBck = totBck + histo[thePlot][i]->GetSumOfWeights();
    printf("(%d) %f vs. %f\n",thePlot,histo[thePlot][0]->GetSumOfWeights(),totBck);
    for(int np=0; np<histBins; np++) histo[thePlot][np]->Write();
    outFilePlotsNote->Close();
  }

  {
    for(int thePlot=0; thePlot<2; thePlot++){
      sprintf(output,"histoZllPt_%d.root",thePlot);	
      TFile* outFilePlotsNote = new TFile(output,"recreate");
      outFilePlotsNote->cd();
      for(int np=0; np<histBins; np++) histoZllPt[thePlot][np]->Write();
      outFilePlotsNote->Close();
      printf("PrescalesZll(%d): ",thePlot);
      for(int i=1; i<=histoZllPt[thePlot][0]->GetNbinsX(); i++){
        double bkg = histoZllPt[thePlot][1]->GetBinContent(i) + histoZllPt[thePlot][2]->GetBinContent(i) + histoZllPt[thePlot][3]->GetBinContent(i);
        if(histoZllPt[thePlot][1]->GetBinContent(i) > 0) prescales[thePlot][i-1] = histoZllPt[thePlot][0]->GetBinContent(i)/bkg;
        printf(" %.5f ",prescales[thePlot][i-1]);
      }
      printf("\n");
    }
  }

  {
    for(int thePlot=0; thePlot<2; thePlot++){
      sprintf(output,"histoWlnPt_%d.root",thePlot);	
      TFile* outFilePlotsNote = new TFile(output,"recreate");
      outFilePlotsNote->cd();
      for(int np=0; np<histBins; np++) histoWlnPt[thePlot][np]->Write();
      outFilePlotsNote->Close();
      printf("PrescalesWln(%d): ",thePlot);
      for(int i=1; i<=histoWlnPt[thePlot][0]->GetNbinsX(); i++){
        double prescaleWln = 1.0;
	double bkg = histoWlnPt[thePlot][1]->GetBinContent(i) + histoWlnPt[thePlot][2]->GetBinContent(i) + histoWlnPt[thePlot][3]->GetBinContent(i);
        if(histoWlnPt[thePlot][1]->GetBinContent(i) > 0) prescaleWln = histoWlnPt[thePlot][0]->GetBinContent(i)/bkg;
        printf(" %.5f ",prescaleWln);
      }
      printf("\n");
    }
  }

  {
    sprintf(output,"histoFakeEtaPt.root"); 
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    double den,num,eff,unc;
    for(int thePlot=0; thePlot<2; thePlot++){
      for(int i=1; i<=histoFakeDenEtaPt[thePlot][0]->GetNbinsX(); i++){
        for(int j=1; j<=histoFakeDenEtaPt[thePlot][0]->GetNbinsY(); j++){
          den = histoFakeDenEtaPt[thePlot][0]    ->GetBinContent(i,j) - (histoFakeDenEtaPt[thePlot][1]    ->GetBinContent(i,j)+histoFakeDenEtaPt[thePlot][2]    ->GetBinContent(i,j)+histoFakeDenEtaPt[thePlot][3]    ->GetBinContent(i,j))*prescales[thePlot][j-1];
          num = histoFakeNumSel0EtaPt[thePlot][0]->GetBinContent(i,j) - (histoFakeNumSel0EtaPt[thePlot][1]->GetBinContent(i,j)+histoFakeNumSel0EtaPt[thePlot][2]->GetBinContent(i,j)+histoFakeNumSel0EtaPt[thePlot][3]->GetBinContent(i,j))*prescales[thePlot][j-1];
          eff = 1.0; unc = 0.0;
          if(den > 0 && num > 0){
            eff = num / den;
            unc = sqrt(eff*(1-eff)/den);
	  }
          else if(den > 0){
            eff = 0.0;
            unc = TMath::Min(sqrt(1.0/den),0.999);
          }
          histoFakeEffSel0EtaPt[thePlot]->SetBinContent(i,j,eff);
          histoFakeEffSel0EtaPt[thePlot]->SetBinError  (i,j,unc);

          num = histoFakeNumSel1EtaPt[thePlot][0]->GetBinContent(i,j) - (histoFakeNumSel1EtaPt[thePlot][1]->GetBinContent(i,j)+histoFakeNumSel1EtaPt[thePlot][2]->GetBinContent(i,j)+histoFakeNumSel1EtaPt[thePlot][3]->GetBinContent(i,j))*prescales[thePlot][j-1];
          eff = 1.0; unc = 0.0;
          if(den > 0 && num > 0){
            eff = num / den;
            unc = sqrt(eff*(1-eff)/den);
	  }
          else if(den > 0){
            eff = 0.0;
            unc = TMath::Min(sqrt(1.0/den),0.999);
          }
          histoFakeEffSel1EtaPt[thePlot]->SetBinContent(i,j,eff);
          histoFakeEffSel1EtaPt[thePlot]->SetBinError  (i,j,unc);

          num = histoFakeNumSel2EtaPt[thePlot][0]->GetBinContent(i,j) - (histoFakeNumSel2EtaPt[thePlot][1]->GetBinContent(i,j)+histoFakeNumSel2EtaPt[thePlot][2]->GetBinContent(i,j)+histoFakeNumSel2EtaPt[thePlot][3]->GetBinContent(i,j))*prescales[thePlot][j-1];
          eff = 1.0; unc = 0.0;
          if(den > 0 && num > 0){
            eff = num / den;
            unc = sqrt(eff*(1-eff)/den);
	  }
          else if(den > 0){
            eff = 0.0;
            unc = TMath::Min(sqrt(1.0/den),0.999);
          }
          histoFakeEffSel2EtaPt[thePlot]->SetBinContent(i,j,eff);
          histoFakeEffSel2EtaPt[thePlot]->SetBinError  (i,j,unc);

          num = histoFakeNumSel3EtaPt[thePlot][0]->GetBinContent(i,j) - (histoFakeNumSel3EtaPt[thePlot][1]->GetBinContent(i,j)+histoFakeNumSel3EtaPt[thePlot][2]->GetBinContent(i,j)+histoFakeNumSel3EtaPt[thePlot][3]->GetBinContent(i,j))*prescales[thePlot][j-1];
          eff = 1.0; unc = 0.0;
          if(den > 0 && num > 0){
            eff = num / den;
            unc = sqrt(eff*(1-eff)/den);
	  }
          else if(den > 0){
            eff = 0.0;
            unc = TMath::Min(sqrt(1.0/den),0.999);
          }
          histoFakeEffSel3EtaPt[thePlot]->SetBinContent(i,j,eff);
          histoFakeEffSel3EtaPt[thePlot]->SetBinError  (i,j,unc);

          num = histoFakeNumSel4EtaPt[thePlot][0]->GetBinContent(i,j) - (histoFakeNumSel4EtaPt[thePlot][1]->GetBinContent(i,j)+histoFakeNumSel4EtaPt[thePlot][2]->GetBinContent(i,j)+histoFakeNumSel4EtaPt[thePlot][3]->GetBinContent(i,j))*prescales[thePlot][j-1];
          eff = 1.0; unc = 0.0;
          if(den > 0 && num > 0){
            eff = num / den;
            unc = sqrt(eff*(1-eff)/den);
	  }
          else if(den > 0){
            eff = 0.0;
            unc = TMath::Min(sqrt(1.0/den),0.999);
          }
          histoFakeEffSel4EtaPt[thePlot]->SetBinContent(i,j,eff);
          histoFakeEffSel4EtaPt[thePlot]->SetBinError  (i,j,unc);

	  printf("(%d,%d): %9.1f %9.1f %9.1f %9.1f %9.1f %9.1f / %9.1f %9.1f %9.1f %9.1f %9.1f %9.1f / %9.1f %9.1f %9.1f %9.1f %9.1f %9.1f / %9.1f %9.1f %9.1f %9.1f %9.1f %9.1f = %5.3f %5.3f %5.3f %5.3f %5.3f - %7.5f\n",i,j,
	  histoFakeDenEtaPt[thePlot][0]->GetBinContent(i,j),histoFakeNumSel0EtaPt[thePlot][0]->GetBinContent(i,j),histoFakeNumSel1EtaPt[thePlot][0]->GetBinContent(i,j),histoFakeNumSel2EtaPt[thePlot][0]->GetBinContent(i,j),histoFakeNumSel3EtaPt[thePlot][0]->GetBinContent(i,j),histoFakeNumSel4EtaPt[thePlot][0]->GetBinContent(i,j),
	  histoFakeDenEtaPt[thePlot][1]->GetBinContent(i,j),histoFakeNumSel0EtaPt[thePlot][1]->GetBinContent(i,j),histoFakeNumSel1EtaPt[thePlot][1]->GetBinContent(i,j),histoFakeNumSel2EtaPt[thePlot][1]->GetBinContent(i,j),histoFakeNumSel3EtaPt[thePlot][1]->GetBinContent(i,j),histoFakeNumSel4EtaPt[thePlot][1]->GetBinContent(i,j),
	  histoFakeDenEtaPt[thePlot][2]->GetBinContent(i,j),histoFakeNumSel0EtaPt[thePlot][2]->GetBinContent(i,j),histoFakeNumSel1EtaPt[thePlot][2]->GetBinContent(i,j),histoFakeNumSel2EtaPt[thePlot][2]->GetBinContent(i,j),histoFakeNumSel3EtaPt[thePlot][2]->GetBinContent(i,j),histoFakeNumSel4EtaPt[thePlot][2]->GetBinContent(i,j),
	  histoFakeDenEtaPt[thePlot][3]->GetBinContent(i,j),histoFakeNumSel0EtaPt[thePlot][3]->GetBinContent(i,j),histoFakeNumSel1EtaPt[thePlot][3]->GetBinContent(i,j),histoFakeNumSel2EtaPt[thePlot][3]->GetBinContent(i,j),histoFakeNumSel3EtaPt[thePlot][3]->GetBinContent(i,j),histoFakeNumSel4EtaPt[thePlot][3]->GetBinContent(i,j),
          histoFakeEffSel0EtaPt[thePlot]->GetBinContent(i,j),histoFakeEffSel1EtaPt[thePlot]->GetBinContent(i,j),histoFakeEffSel2EtaPt[thePlot]->GetBinContent(i,j),histoFakeEffSel3EtaPt[thePlot]->GetBinContent(i,j),histoFakeEffSel4EtaPt[thePlot]->GetBinContent(i,j),
	  prescales[thePlot][j-1]);
        }
      }
      for(int np=0; np<histBins; np++) histoFakeDenEtaPt[thePlot][np]->Write();
      for(int np=0; np<histBins; np++) histoFakeNumSel0EtaPt[thePlot][np]->Write();
      for(int np=0; np<histBins; np++) histoFakeNumSel1EtaPt[thePlot][np]->Write();
      for(int np=0; np<histBins; np++) histoFakeNumSel2EtaPt[thePlot][np]->Write();
      for(int np=0; np<histBins; np++) histoFakeNumSel3EtaPt[thePlot][np]->Write();
      for(int np=0; np<histBins; np++) histoFakeNumSel4EtaPt[thePlot][np]->Write();
      histoFakeEffSel0EtaPt[thePlot]->Write();
      histoFakeEffSel1EtaPt[thePlot]->Write();
      histoFakeEffSel2EtaPt[thePlot]->Write();
      histoFakeEffSel3EtaPt[thePlot]->Write();
      histoFakeEffSel4EtaPt[thePlot]->Write();
    }
    outFilePlotsNote->Close();
  }
}
