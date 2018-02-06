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

void wwAnalysis(
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

  infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	       infileCat_.push_back(1);

  infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	       infileCat_.push_back(2);

  infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		       infileCat_.push_back(3);
  infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		       infileCat_.push_back(3);

  infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data())); infileCat_.push_back(4);
  infileName_.push_back(Form("%sDYJetsToLL_M-50_LO.root",filesPath.Data()));   infileCat_.push_back(4);

  infileName_.push_back(Form("%sWZ.root" ,filesPath.Data()));		       infileCat_.push_back(5);
  infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	       infileCat_.push_back(5);
  infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	       infileCat_.push_back(5);

  infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	       infileCat_.push_back(6);
  infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	       infileCat_.push_back(6);

  infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));		       infileCat_.push_back(7);

  infileName_.push_back(Form("%sWGstar.root" ,filesPath.Data()));	       infileCat_.push_back(8);

  infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	       infileCat_.push_back(9);

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
  const int allPlots = 162;
  const int histBins = 11;
  TH1D* histo[allPlots][histBins];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    if     (thePlot >=   0 && thePlot <=  44) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >=  45 && thePlot <=  53) {nBinPlot =   5; xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >=  54 && thePlot <=  80) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >=  81 && thePlot <=  89) {nBinPlot =  90; xminPlot =  0.0; xmaxPlot = 180;}
    else if(thePlot >=  90 && thePlot <= 116) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >= 117 && thePlot <= 125) {nBinPlot =  90; xminPlot =  0.0; xmaxPlot = 180;}
    else if(thePlot >= 126 && thePlot <= 152) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >= 153 && thePlot <= 162) {nBinPlot =  90; xminPlot =  0.0; xmaxPlot = 180;}
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

      if(thePandaFlat.nLooseLep != 2) continue;

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

      if(TMath::Abs(looseLepEta[0]) >= 2.4 || TMath::Abs(looseLepEta[1]) >= 2.4) continue;

      if(!(ptSelCuts[0] >= 1 && ptSelCuts[1] >= 2)) continue;

      int theCategory = infileCat_[ifile];
      bool isNotMCFake = thePandaFlat.looseGenLep1PdgId != 0 && thePandaFlat.looseGenLep2PdgId != 0;
      if(theCategory != 0 && theCategory != 2 && isNotMCFake == false && usePureMC == false) continue;

      vector<int> idLep; idLep.push_back(0); idLep.push_back(0);
      bool passLooseLepId = ((looseLepSelBit[0] & kFake) == kFake) && ((looseLepSelBit[1] & kFake) == kFake);
      if(passLooseLepId == false) continue;

      if((looseLepSelBit[0] & kTight) == kTight && (looseLepSelBit[0] & kDxyz) == kDxyz) idLep[0] = 1;
      if((looseLepSelBit[1] & kTight) == kTight && (looseLepSelBit[1] & kDxyz) == kDxyz) idLep[1] = 1;

      int qTot = abs(looseLepPdgId[0])/looseLepPdgId[0] + abs(looseLepPdgId[1])/looseLepPdgId[1];

      int lepType = -1;
      if     (abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13) lepType = 0;
      else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11) lepType = 1;
      else  lepType = 2;

      TLorentzVector vLoose1,vLoose2,vMet,vTrkMet;
      vMet.SetPtEtaPhiM(thePandaFlat.pfmet,0.0,thePandaFlat.pfmetphi,0.0);
      vTrkMet.SetPtEtaPhiM(thePandaFlat.trkmet,0.0,thePandaFlat.trkmetphi,0.0);
      double thePDGMass[2] = {mass_mu, mass_mu};
      if(abs(looseLepPdgId[0])==11) thePDGMass[0] = mass_el;
      if(abs(looseLepPdgId[1])==11) thePDGMass[1] = mass_el;
      vLoose1.SetPtEtaPhiM(looseLepPt[0],looseLepEta[0],looseLepPhi[0],thePDGMass[0]);
      vLoose2.SetPtEtaPhiM(looseLepPt[1],looseLepEta[1],looseLepPhi[1],thePDGMass[1]);

      unsigned int countLeptonTight = (idLep[0] > 0) + (idLep[1] > 0);

      double dPhiLepMETMin = TMath::Min(TMath::Abs(vLoose1.DeltaPhi(vMet)), TMath::Abs(vLoose2.DeltaPhi(vMet)));
      double dPhiLepTrackMETMin = TMath::Min(TMath::Abs(vLoose1.DeltaPhi(vTrkMet)), TMath::Abs(vLoose2.DeltaPhi(vTrkMet)));

      double PMET[1] = {vMet.Pt()};
      double PTrackMET[1] = {vTrkMet.Pt()};
      if(dPhiLepMETMin < TMath::Pi()/2) {PMET[0] = PMET[0] * sin(dPhiLepMETMin);}
      if(dPhiLepTrackMETMin < TMath::Pi()/2) {PTrackMET[0] = PTrackMET[0] * sin(dPhiLepTrackMETMin);}
      double minPMET[1] = {TMath::Min(PMET[0],PTrackMET[0])};

      bool passSel[7] = {qTot == 0, (vLoose1+vLoose2).M() > 20, fabs((vLoose1+vLoose2).M()-91.1876) > 15 || lepType == 2, minPMET[0] > 20, minPMET[0] > 45 || lepType == 2, 
                         (vLoose1+vLoose2).Pt() > 30 && ((vLoose1+vLoose2).Pt() > 45 ||  lepType == 2), thePandaFlat.jetNBtags == 0};

      bool passWWSel  =  passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[4] && passSel[5] &&  passSel[6];
      bool passSSSel  = !passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[4] && passSel[5] &&  passSel[6];
      bool passTopSel =  passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[4] && passSel[5] && !passSel[6];
      bool passAllButOneSel[4] = {
        passSel[0] &&                             passSel[3] && passSel[4] && passSel[5] && passSel[6],
        passSel[0] && passSel[1] && passSel[2] &&                             passSel[5] && passSel[6],
        passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[4]               && passSel[6],
        passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[4] && passSel[5]
	
      };
      if(usePureMC == true && countLeptonTight != idLep.size()) continue;

      if(thePandaFlat.nJot > 2) continue;
      lepType = lepType + 3*(int)thePandaFlat.nJot;

      double totalWeight = 1.0;
      if(theCategory != 0){
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
        if(abs(looseLepPdgId[1])==13){
          double etal = looseLepEta[1]; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
          int binEta = scalefactors_Muon_Eta->GetXaxis()->FindFixBin(etal);
          the_eta_sf[1] = scalefactors_Muon_Eta->GetBinContent(binEta);
        } else {
          double etal = looseLepEta[1]; if(etal >= 2.5) etal = 2.4999; else if(etal <= -2.5) etal = -2.4999;
          int binEta = scalefactors_Electron_Eta->GetXaxis()->FindFixBin(etal);
          the_eta_sf[1] = scalefactors_Electron_Eta->GetBinContent(binEta);
        }

        double sfWeightLepEff[2] = {1.0, 1.0};
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

        totalWeight = thePandaFlat.normalizedWeight * lumi * thePandaFlat.sf_pu * the_eta_sf[0] * the_eta_sf[1] * sfWeightLepEff[0] * sfWeightLepEff[1] * theMCPrescale;

      }

      if(usePureMC == false && countLeptonTight != idLep.size()){
        double fakeSF = 1.0;
        for(unsigned int nl=0; nl<idLep.size(); nl++){
          if(idLep[nl] != 0) continue;
          bool applyTight = true;
          if(nl == 0) fakeSF = fakeSF * fakeRateFactor(TMath::Min((double)looseLepPt[0],44.999),TMath::Abs(looseLepEta[0]),TMath::Abs(looseLepPdgId[0]),applyTight,histoFakeEffSelMediumEtaPt_m,histoFakeEffSelMediumEtaPt_e,histoFakeEffSelTightEtaPt_m,histoFakeEffSelTightEtaPt_e);
          if(nl == 1) fakeSF = fakeSF * fakeRateFactor(TMath::Min((double)looseLepPt[1],44.999),TMath::Abs(looseLepEta[1]),TMath::Abs(looseLepPdgId[1]),applyTight,histoFakeEffSelMediumEtaPt_m,histoFakeEffSelMediumEtaPt_e,histoFakeEffSelTightEtaPt_m,histoFakeEffSelTightEtaPt_e);
          theCategory = 10;
        }
        if     (infileCat_[ifile] != 0 && countLeptonTight == idLep.size()-2) fakeSF = +1.0 * fakeSF; // double fake, MC
        else if(infileCat_[ifile] != 0 && countLeptonTight == idLep.size()-1) fakeSF = -1.0 * fakeSF; // single fake, MC
        else if(infileCat_[ifile] == 0 && countLeptonTight == idLep.size()-2) fakeSF = -1.0 * fakeSF; // double fake, data
        else if(infileCat_[ifile] == 0 && countLeptonTight == idLep.size()-1) fakeSF = +1.0 * fakeSF; // single fake, data
        else printf("IMPOSSIBLE FAKE OPTION\n");
        totalWeight = totalWeight * fakeSF;
      }

      if(passAllButOneSel[0])histo[lepType+  0][theCategory]->Fill(TMath::Min((vLoose1+vLoose2).M(),199.999),totalWeight);
      if(passAllButOneSel[1])histo[lepType+  9][theCategory]->Fill(TMath::Min(minPMET[0],199.999),totalWeight);
      if(passAllButOneSel[1])histo[lepType+ 18][theCategory]->Fill(TMath::Min(vMet.Pt(),199.999),totalWeight);
      if(passAllButOneSel[1])histo[lepType+ 27][theCategory]->Fill(TMath::Min(vTrkMet.Pt(),199.999),totalWeight);
      if(passAllButOneSel[2])histo[lepType+ 36][theCategory]->Fill(TMath::Min((vLoose1+vLoose2).Pt(),199.999),totalWeight);
      if(passAllButOneSel[3])histo[lepType+ 45][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNBtags,4.499),totalWeight);
      if(passWWSel)          histo[lepType+ 54][theCategory]->Fill(TMath::Min(vLoose1.Pt(),199.999),totalWeight);
      if(passWWSel)          histo[lepType+ 63][theCategory]->Fill(TMath::Min(vLoose2.Pt(),199.999),totalWeight);
      if(passWWSel)          histo[lepType+ 72][theCategory]->Fill(TMath::Min((vLoose1+vLoose2).M(),199.999),totalWeight);
      if(passWWSel)          histo[lepType+ 81][theCategory]->Fill(TMath::Abs(vLoose1.DeltaPhi(vMet))*180/TMath::Pi(),totalWeight);
      if(passSSSel)          histo[lepType+ 90][theCategory]->Fill(TMath::Min(vLoose1.Pt(),199.999),totalWeight);
      if(passSSSel)          histo[lepType+ 99][theCategory]->Fill(TMath::Min(vLoose2.Pt(),199.999),totalWeight);
      if(passSSSel)          histo[lepType+108][theCategory]->Fill(TMath::Min((vLoose1+vLoose2).M(),199.999),totalWeight);
      if(passSSSel)          histo[lepType+117][theCategory]->Fill(TMath::Abs(vLoose1.DeltaPhi(vMet))*180/TMath::Pi(),totalWeight);
      if(passTopSel)         histo[lepType+126][theCategory]->Fill(TMath::Min(vLoose1.Pt(),199.999),totalWeight);
      if(passTopSel)         histo[lepType+135][theCategory]->Fill(TMath::Min(vLoose2.Pt(),199.999),totalWeight);
      if(passTopSel)         histo[lepType+144][theCategory]->Fill(TMath::Min((vLoose1+vLoose2).M(),199.999),totalWeight);
      if(passTopSel)         histo[lepType+153][theCategory]->Fill(TMath::Abs(vLoose1.DeltaPhi(vMet))*180/TMath::Pi(),totalWeight);

    } // end events loop
    the_input_file->Close();
  } // end chain loop

  char output[200];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    sprintf(output,"histoWW_%d.root",thePlot);	
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
