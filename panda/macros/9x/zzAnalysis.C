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

const double mcPrescale = 1;
const bool usePureMC = false;

void zzAnalysis(
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
  infileName_.push_back(Form("%sDYJetsToLL_M-50_LO.root",filesPath.Data()));   infileCat_.push_back(1);
  infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	       infileCat_.push_back(1);
  infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	       infileCat_.push_back(1);
  infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		       infileCat_.push_back(1);
  infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		       infileCat_.push_back(1);
  infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));		       infileCat_.push_back(2);
  infileName_.push_back(Form("%sWGstar.root" ,filesPath.Data()));	       infileCat_.push_back(2);
  infileName_.push_back(Form("%sWZ.root" ,filesPath.Data()));		       infileCat_.push_back(3);
  }
  infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	       infileCat_.push_back(4);
  infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	       infileCat_.push_back(4);
  infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	       infileCat_.push_back(5);
  infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	       infileCat_.push_back(5);
  infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	       infileCat_.push_back(6);

  //infileName_.clear();infileCat_.clear();
  //infileName_.push_back(Form("PandaAnalysis/Flat/test/testskim.root")); infileCat_.push_back(4);
  //infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	       infileCat_.push_back(4);
  //infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	       infileCat_.push_back(4);

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

  double getMaxPtForSFs[2] = {scalefactors_Medium_Muon                  ->GetYaxis()->GetBinCenter(scalefactors_Medium_Muon		     ->GetNbinsY()),
                              scalefactors_Medium_Electron              ->GetYaxis()->GetBinCenter(scalefactors_Medium_Electron		     ->GetNbinsY())
		              };

  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 55;
  const int histBins = 7;
  TH1D* histo[allPlots][histBins];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    if     (thePlot >=  0 && thePlot <= 14) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 100;}
    else if(thePlot >= 15 && thePlot <= 19) {nBinPlot = 800; xminPlot =  0.0; xmaxPlot = 800;}
    else if(thePlot >= 20 && thePlot <= 44) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >= 45 && thePlot <= 54) {nBinPlot =   5; xminPlot = -0.5; xmaxPlot = 4.5;}
    TH1D* histos = new TH1D("histos", "histos", nBinPlot, xminPlot, xmaxPlot);
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
    double nTrigger[6] = {0,0,0,0,0,0};
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = thePandaFlat.LoadTree(jentry);
      if (ientry < 0) break;
      nb = thePandaFlat.fChain->GetEntry(jentry);   nbytes += nb;
      if (jentry%1000000 == 0) printf("--- reading event %8lld (%8lld) of %8lld\n",jentry,ientry,nentries);
      if (infileCat_[ifile] != 0 && jentry%(int)theMCPrescale != 0) continue;

      if(infileCat_[ifile] == 0 && ((period == 1 && thePandaFlat.runNumber > 278802) || (period == 2 && thePandaFlat.runNumber <= 278802))) continue;

      bool passTrigger = (thePandaFlat.trigger & (1<<kEMuTrig)) != 0       || (thePandaFlat.trigger & (1<<kDoubleMuTrig)) != 0  ||
                         (thePandaFlat.trigger & (1<<kSingleMuTrig)) != 0  || (thePandaFlat.trigger & (1<<kDoubleEleTrig)) != 0 ||
                         (thePandaFlat.trigger & (1<<kSingleEleTrig)) != 0;
      if(passTrigger == false) continue;

      if(thePandaFlat.nLooseLep != 4) continue;

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

      if(TMath::Abs(looseLepEta[0]) >= 2.4 || TMath::Abs(looseLepEta[1]) >= 2.4 || TMath::Abs(looseLepEta[2]) >= 2.4 || TMath::Abs(looseLepEta[3]) >= 2.4) continue;

      if(!(ptSelCuts[0] >= 1 && ptSelCuts[1] >= 2 && ptSelCuts[2] >= 4)) continue;

      int theCategory = infileCat_[ifile];
      bool isNotMCFake = thePandaFlat.looseGenLep1PdgId != 0 && thePandaFlat.looseGenLep2PdgId != 0 && thePandaFlat.looseGenLep3PdgId != 0 && thePandaFlat.looseGenLep4PdgId != 0;
      if(theCategory != 0 && theCategory != 2 && isNotMCFake == false && usePureMC == false) continue;

      vector<int> idLep; idLep.push_back(0); idLep.push_back(0); idLep.push_back(0); idLep.push_back(0);
      bool passLooseLepId = ((looseLepSelBit[0] & kFake) == kFake) && ((looseLepSelBit[1] & kFake) == kFake) && ((looseLepSelBit[2] & kFake) == kFake) && ((looseLepSelBit[3] & kFake) == kFake);
      if(passLooseLepId == false) continue;

      if((looseLepSelBit[0] & kMedium) == kMedium) idLep[0] = 1;
      if((looseLepSelBit[1] & kMedium) == kMedium) idLep[1] = 1;
      if((looseLepSelBit[2] & kMedium) == kMedium) idLep[2] = 1;
      if((looseLepSelBit[3] & kMedium) == kMedium) idLep[3] = 1;

      int qTot = abs(looseLepPdgId[0])/looseLepPdgId[0] + abs(looseLepPdgId[1])/looseLepPdgId[1] + abs(looseLepPdgId[2])/looseLepPdgId[2] + abs(looseLepPdgId[3])/looseLepPdgId[3];
      if(abs(qTot) != 0) continue;

      int nmu = (abs(looseLepPdgId[0])==13) + (abs(looseLepPdgId[1])==13) + (abs(looseLepPdgId[2])==13) + (abs(looseLepPdgId[3])==13);
      int nel = (abs(looseLepPdgId[0])==11) + (abs(looseLepPdgId[1])==11) + (abs(looseLepPdgId[2])==11) + (abs(looseLepPdgId[3])==11);
      int lepType = -1;
      if     (nmu == 4 && nel == 0) lepType = 0;
      else if(nmu == 0 && nel == 4) lepType = 1;
      else if(nmu == 2 && nel == 2) lepType = 2;
      else if(nmu == 3 && nel == 1) lepType = 3;
      else if(nmu == 1 && nel == 3) lepType = 3;
      else {printf("Impossible dilepton combination: %d %d %d %d\n",looseLepPdgId[0],looseLepPdgId[1],looseLepPdgId[2],looseLepPdgId[3]); continue;}

      double mllZ = 10000; double mllmin = 10000;
      TLorentzVector vLoose1,vLoose2,vLoose3,vLoose4,vMet;
      TLorentzVector vZ1l1,vZ1l2,vZ2l1,vZ2l2;
      vMet.SetPtEtaPhiM(thePandaFlat.pfmet,0.0,thePandaFlat.pfmetphi,0.0);
      double thePDGMass[4] = {mass_mu, mass_mu, mass_mu, mass_mu};
      if(abs(looseLepPdgId[0])==11) thePDGMass[0] = mass_el;
      if(abs(looseLepPdgId[1])==11) thePDGMass[1] = mass_el;
      if(abs(looseLepPdgId[2])==11) thePDGMass[2] = mass_el;
      if(abs(looseLepPdgId[3])==11) thePDGMass[3] = mass_el;
      vLoose1.SetPtEtaPhiM(looseLepPt[0],looseLepEta[0],looseLepPhi[0],thePDGMass[0]);
      vLoose2.SetPtEtaPhiM(looseLepPt[1],looseLepEta[1],looseLepPhi[1],thePDGMass[1]);
      vLoose3.SetPtEtaPhiM(looseLepPt[2],looseLepEta[2],looseLepPhi[2],thePDGMass[2]);
      vLoose4.SetPtEtaPhiM(looseLepPt[3],looseLepEta[3],looseLepPhi[3],thePDGMass[3]);

      if(abs(looseLepPdgId[0]) == abs(looseLepPdgId[1]) && looseLepPdgId[0] != looseLepPdgId[1]) {
        if((vLoose1+vLoose2).M() < mllmin) mllmin = (vLoose1+vLoose2).M();
        if(fabs((vLoose1+vLoose2).M()-91.1876) < fabs(mllZ-91.1876)) {
	  mllZ = (vLoose1+vLoose2).M();
	  vZ1l1 = vLoose1;
	  vZ1l2 = vLoose2;
	  vZ2l1 = vLoose3;
	  vZ2l2 = vLoose4;
	}
      }
      if(abs(looseLepPdgId[0]) == abs(looseLepPdgId[2]) && looseLepPdgId[0] != looseLepPdgId[2]) {
        if((vLoose1+vLoose3).M() < mllmin) mllmin = (vLoose1+vLoose3).M();
        if(fabs((vLoose1+vLoose3).M()-91.1876) < fabs(mllZ-91.1876)) {
          mllZ = (vLoose1+vLoose3).M();
	  vZ1l1 = vLoose1;
	  vZ1l2 = vLoose3;
	  vZ2l1 = vLoose2;
	  vZ2l2 = vLoose4;
	}
      }
      if(abs(looseLepPdgId[0]) == abs(looseLepPdgId[3]) && looseLepPdgId[0] != looseLepPdgId[3]) {
        if((vLoose1+vLoose4).M() < mllmin) mllmin = (vLoose1+vLoose4).M();
        if(fabs((vLoose1+vLoose4).M()-91.1876) < fabs(mllZ-91.1876)) {
          mllZ = (vLoose1+vLoose4).M();
	  vZ1l1 = vLoose1;
	  vZ1l2 = vLoose4;
	  vZ2l1 = vLoose2;
	  vZ2l2 = vLoose3;
	}
      }
      if(abs(looseLepPdgId[1]) == abs(looseLepPdgId[2]) && looseLepPdgId[1] != looseLepPdgId[2]) {
        if((vLoose2+vLoose3).M() < mllmin) mllmin = (vLoose2+vLoose3).M();
        if(fabs((vLoose2+vLoose3).M()-91.1876) < fabs(mllZ-91.1876)) {
          mllZ = (vLoose2+vLoose3).M();
	  vZ1l1 = vLoose2;
	  vZ1l2 = vLoose3;
	  vZ2l1 = vLoose1;
	  vZ2l2 = vLoose4;
	}
      }
      if(abs(looseLepPdgId[1]) == abs(looseLepPdgId[3]) && looseLepPdgId[1] != looseLepPdgId[3]) {
        if((vLoose2+vLoose4).M() < mllmin) mllmin = (vLoose2+vLoose4).M();
        if(fabs((vLoose2+vLoose4).M()-91.1876) < fabs(mllZ-91.1876)) {
          mllZ = (vLoose2+vLoose4).M();
	  vZ1l1 = vLoose2;
	  vZ1l2 = vLoose4;
	  vZ2l1 = vLoose1;
	  vZ2l2 = vLoose3;
	}
      }
      if(abs(looseLepPdgId[2]) == abs(looseLepPdgId[3]) && looseLepPdgId[2] != looseLepPdgId[3]) {
        if((vLoose3+vLoose4).M() < mllmin) mllmin = (vLoose3+vLoose4).M();
        if(fabs((vLoose3+vLoose4).M()-91.1876) < fabs(mllZ-91.1876)) {
          mllZ = (vLoose3+vLoose4).M();
	  vZ1l1 = vLoose3;
	  vZ1l2 = vLoose4;
	  vZ2l1 = vLoose1;
	  vZ2l2 = vLoose2;
	}
      }

      unsigned int countLeptonTight = (idLep[0] > 0) + (idLep[1] > 0) + (idLep[2] > 0) + (idLep[3] > 0);

      bool passSel[6] = {mllmin > 4, fabs(mllZ-91.1876) < 30, fabs((vZ2l1+vZ2l2).M()-91.1876) < 30 || lepType == 3};
      bool passZZSel  = passSel[0] && passSel[1] && passSel[2];
      bool passAllButOneSel[3] = {
                      passSel[1] && passSel[2],
        passSel[0]               && passSel[2],
	passSel[0] && passSel[1]
      };
      if(usePureMC == true && countLeptonTight != idLep.size()) continue;

      double totalWeight = 1.0;
      if(theCategory != 0){
        double the_eta_sf[4] = {1.0, 1.0, 1.0, 1.0};
        if(abs(looseLepPdgId[0])==13){
          double etal = looseLepEta[0]; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
          int binEta = scalefactors_Muon_Eta->GetXaxis()->FindFixBin(etal);
          the_eta_sf[0] = scalefactors_Muon_Eta->GetBinContent(binEta);
        } else {
          double etal = looseLepEta[0]; if(etal >= 2.5) etal = 2.4999; else if(etal <= -2.5) etal = -2.4999;
          int binEta = scalefactors_Electron_Eta->GetXaxis()->FindFixBin(etal);
          the_eta_sf[0] = scalefactors_Electron_Eta->GetBinContent(binEta);
        }        
        if(abs(looseLepPdgId[1])==13){
          double etal = looseLepEta[1]; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
          int binEta = scalefactors_Muon_Eta->GetXaxis()->FindFixBin(etal);
          the_eta_sf[1] = scalefactors_Muon_Eta->GetBinContent(binEta);
        } else {
          double etal = looseLepEta[1]; if(etal >= 2.5) etal = 2.4999; else if(etal <= -2.5) etal = -2.4999;
          int binEta = scalefactors_Electron_Eta->GetXaxis()->FindFixBin(etal);
          the_eta_sf[1] = scalefactors_Electron_Eta->GetBinContent(binEta);
        }
        if(abs(looseLepPdgId[2])==13){
          double etal = looseLepEta[2]; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
          int binEta = scalefactors_Muon_Eta->GetXaxis()->FindFixBin(etal);
          the_eta_sf[2] = scalefactors_Muon_Eta->GetBinContent(binEta);
        } else {
          double etal = looseLepEta[2]; if(etal >= 2.5) etal = 2.4999; else if(etal <= -2.5) etal = -2.4999;
          int binEta = scalefactors_Electron_Eta->GetXaxis()->FindFixBin(etal);
          the_eta_sf[2] = scalefactors_Electron_Eta->GetBinContent(binEta);
        }
        if(abs(looseLepPdgId[3])==13){
          double etal = looseLepEta[3]; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
          int binEta = scalefactors_Muon_Eta->GetXaxis()->FindFixBin(etal);
          the_eta_sf[3] = scalefactors_Muon_Eta->GetBinContent(binEta);
        } else {
          double etal = looseLepEta[3]; if(etal >= 2.5) etal = 2.4999; else if(etal <= -2.5) etal = -2.4999;
          int binEta = scalefactors_Electron_Eta->GetXaxis()->FindFixBin(etal);
          the_eta_sf[3] = scalefactors_Electron_Eta->GetBinContent(binEta);
        }

        double sfWeightLepEff[4] = {1.0, 1.0, 1.0, 1.0};
        if(abs(looseLepPdgId[0])==13){
          double etal = looseLepEta[0]; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
          int binXT   = scalefactors_Medium_Muon->GetXaxis()->FindFixBin(etal);
          int binYT_c = scalefactors_Medium_Muon->GetYaxis()->FindFixBin(TMath::Min((double)looseLepPt[0],getMaxPtForSFs[0]));
	  sfWeightLepEff[0] = scalefactors_Medium_Muon                   ->GetBinContent(binXT,binYT_c);
        } else {
          double etal = looseLepEta[0]; if(etal >= 2.5) etal = 2.4999; else if(etal <= -2.5) etal = -2.4999;
          int binXT   = scalefactors_Medium_Electron->GetXaxis()->FindFixBin(etal);
          int binYT_c = scalefactors_Medium_Electron->GetYaxis()->FindFixBin(TMath::Min((double)looseLepPt[0],getMaxPtForSFs[1]));
	  sfWeightLepEff[0] = scalefactors_Medium_Electron                   ->GetBinContent(binXT,binYT_c);
        }
        if(abs(looseLepPdgId[1])==13){
          double etal = looseLepEta[1]; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
          int binXT   = scalefactors_Medium_Muon->GetXaxis()->FindFixBin(etal);
          int binYT_c = scalefactors_Medium_Muon->GetYaxis()->FindFixBin(TMath::Min((double)looseLepPt[1],getMaxPtForSFs[0]));
	  sfWeightLepEff[1] = scalefactors_Medium_Muon->GetBinContent(binXT,binYT_c);
        } else {
          double etal = looseLepEta[1]; if(etal >= 2.5) etal = 2.4999; else if(etal <= -2.5) etal = -2.4999;
          int binXT   = scalefactors_Medium_Electron->GetXaxis()->FindFixBin(etal);
          int binYT_c = scalefactors_Medium_Electron->GetYaxis()->FindFixBin(TMath::Min((double)looseLepPt[1],getMaxPtForSFs[1]));
	  sfWeightLepEff[1] = scalefactors_Medium_Electron->GetBinContent(binXT,binYT_c);
        }
        if(abs(looseLepPdgId[2])==13){
          double etal = looseLepEta[2]; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
          int binXT   = scalefactors_Medium_Muon->GetXaxis()->FindFixBin(etal);
          int binYT_c = scalefactors_Medium_Muon->GetYaxis()->FindFixBin(TMath::Min((double)looseLepPt[2],getMaxPtForSFs[0]));
	  sfWeightLepEff[2] = scalefactors_Medium_Muon->GetBinContent(binXT,binYT_c);
        } else {
          double etal = looseLepEta[2]; if(etal >= 2.5) etal = 2.4999; else if(etal <= -2.5) etal = -2.4999;
          int binXT   = scalefactors_Medium_Electron->GetXaxis()->FindFixBin(etal);
          int binYT_c = scalefactors_Medium_Electron->GetYaxis()->FindFixBin(TMath::Min((double)looseLepPt[2],getMaxPtForSFs[1]));
	  sfWeightLepEff[2] = scalefactors_Medium_Electron->GetBinContent(binXT,binYT_c);
        }
        if(abs(looseLepPdgId[3])==13){
          double etal = looseLepEta[3]; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
          int binXT   = scalefactors_Medium_Muon->GetXaxis()->FindFixBin(etal);
          int binYT_c = scalefactors_Medium_Muon->GetYaxis()->FindFixBin(TMath::Min((double)looseLepPt[3],getMaxPtForSFs[0]));
	  sfWeightLepEff[3] = scalefactors_Medium_Muon->GetBinContent(binXT,binYT_c);
        } else {
          double etal = looseLepEta[3]; if(etal >= 2.5) etal = 2.4999; else if(etal <= -2.5) etal = -2.4999;
          int binXT   = scalefactors_Medium_Electron->GetXaxis()->FindFixBin(etal);
          int binYT_c = scalefactors_Medium_Electron->GetYaxis()->FindFixBin(TMath::Min((double)looseLepPt[3],getMaxPtForSFs[1]));
	  sfWeightLepEff[3] = scalefactors_Medium_Electron->GetBinContent(binXT,binYT_c);
        }

        totalWeight = thePandaFlat.normalizedWeight * lumi * thePandaFlat.sf_pu * the_eta_sf[0] * the_eta_sf[1] * the_eta_sf[2] * the_eta_sf[3] * sfWeightLepEff[0] * sfWeightLepEff[1] * sfWeightLepEff[2] * sfWeightLepEff[3] * theMCPrescale;

        if     (infileCat_[ifile] == 3)                                                totalWeight = totalWeight * thePandaFlat.sf_wz;
	else if(infileCat_[ifile] == 4 && infileName_[ifile].Contains("qqZZ") == true) totalWeight = totalWeight * thePandaFlat.sf_zz;
      }

      if(usePureMC == false && countLeptonTight != idLep.size()){
        double fakeSF = 1.0;
        for(unsigned int nl=0; nl<idLep.size(); nl++){
          if(idLep[nl] != 0) continue;
          bool applyTight = false;
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

      if(passZZSel){
        if((thePandaFlat.trigger & kEMuTrig)       == kEMuTrig)       nTrigger[0] = nTrigger[0] + totalWeight;
        if((thePandaFlat.trigger & kDoubleMuTrig)  == kDoubleMuTrig)  nTrigger[1] = nTrigger[1] + totalWeight;
        if((thePandaFlat.trigger & kSingleMuTrig)  == kSingleMuTrig)  nTrigger[2] = nTrigger[2] + totalWeight;
        if((thePandaFlat.trigger & kDoubleEleTrig) == kDoubleEleTrig) nTrigger[3] = nTrigger[3] + totalWeight;
        if((thePandaFlat.trigger & kSingleEleTrig) == kSingleEleTrig) nTrigger[4] = nTrigger[4] + totalWeight;
        nTrigger[5] = nTrigger[5] + totalWeight;
      }

      if(passAllButOneSel[0]){histo[lepType+ 0][theCategory]->Fill(TMath::Min(mllmin,99.999),totalWeight);                                if(lepType != 3) histo[ 4][theCategory]->Fill(TMath::Min(mllmin,99.999),totalWeight);}
      if(passAllButOneSel[1]){histo[lepType+ 5][theCategory]->Fill(TMath::Min(fabs(mllZ-91.1876),99.999),totalWeight);                    if(lepType != 3) histo[ 9][theCategory]->Fill(TMath::Min(fabs(mllZ-91.1876),99.999),totalWeight);}
      if(passAllButOneSel[2]){histo[lepType+10][theCategory]->Fill(TMath::Min(fabs((vZ2l1+vZ2l2).M()-91.1876),99.999),totalWeight);       if(lepType != 3) histo[14][theCategory]->Fill(TMath::Min(fabs((vZ2l1+vZ2l2).M()-91.1876),99.999),totalWeight);}
      if(passZZSel)          {histo[lepType+15][theCategory]->Fill(TMath::Min((vLoose1+vLoose2+vLoose3+vLoose4).M(),799.999),totalWeight);if(lepType != 3) histo[19][theCategory]->Fill(TMath::Min((vLoose1+vLoose2+vLoose3).M(),799.999),totalWeight);}
      if(passZZSel)          {histo[lepType+20][theCategory]->Fill(TMath::Min(vZ1l1.Pt(),199.999),totalWeight);                           if(lepType != 3) histo[24][theCategory]->Fill(TMath::Min(vZ1l1.Pt(),199.999),totalWeight);}
      if(passZZSel)          {histo[lepType+25][theCategory]->Fill(TMath::Min(vZ1l2.Pt(),199.999),totalWeight);                           if(lepType != 3) histo[29][theCategory]->Fill(TMath::Min(vZ1l2.Pt(),199.999),totalWeight);}
      if(passZZSel)          {histo[lepType+30][theCategory]->Fill(TMath::Min(vZ2l1.Pt(),199.999),totalWeight);                           if(lepType != 3) histo[34][theCategory]->Fill(TMath::Min(vZ2l1.Pt(),199.999),totalWeight);}
      if(passZZSel)          {histo[lepType+35][theCategory]->Fill(TMath::Min(vZ2l2.Pt(),199.999),totalWeight);                           if(lepType != 3) histo[39][theCategory]->Fill(TMath::Min(vZ2l2.Pt(),199.999),totalWeight);}
      if(passZZSel)          {histo[lepType+40][theCategory]->Fill(TMath::Min(vMet.Pt(),199.999),totalWeight);			          if(lepType != 3) histo[44][theCategory]->Fill(TMath::Min(vMet.Pt(),199.999),totalWeight);}
      if(passZZSel)          {histo[lepType+45][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJot,4.499),totalWeight);              if(lepType != 3) histo[49][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJot,4.499),totalWeight);}
      if(passZZSel)          {histo[lepType+50][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNMBtags,4.499),totalWeight);        if(lepType != 3) histo[54][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNMBtags,4.499),totalWeight);}

    } // end events loop
    the_input_file->Close();
    printf("%6.3f %6.3f %6.3f %6.3f %6.3f\n",nTrigger[0]/nTrigger[5],nTrigger[1]/nTrigger[5],nTrigger[2]/nTrigger[5],nTrigger[3]/nTrigger[5],nTrigger[4]/nTrigger[5]);
  } // end chain loop

  char output[200];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    sprintf(output,"histoZZ_%d.root",thePlot);	
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    double totBck = 0;
    for(int i=1; i<histBins; i++) totBck = totBck + histo[thePlot][i]->GetSumOfWeights();
    printf("(%2d) %7.1f vs. %7.1f ",thePlot,histo[thePlot][0]->GetSumOfWeights(),totBck);
    printf("(");
    for(int i=1; i<histBins; i++) printf("%7.1f ",histo[thePlot][i]->GetSumOfWeights());
    printf(")\n");
    for(int np=0; np<histBins; np++) histo[thePlot][np]->Write();
    outFilePlotsNote->Close();
  }

}
