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

#include "MitAnalysisRunII/panda/macros/80x/pandaFlat.C"
#include "MitAnalysisRunII/panda/macros/80x/common.h"

void TnPAnalysis(
int whichDY = 3, 
int whichAnaFlow = 0
){

  double lumi = 35.8;
  //*******************************************************
  //Input Files
  //*******************************************************
  TString filesPath    = "/data/t3home000/ceballos/panda/v_005_0/";
  vector<TString> infileName_;
  vector<int> infileCat_;

  if(whichAnaFlow == 0 || whichAnaFlow == 1){
    infileName_.push_back(Form("%sdata.root",filesPath.Data()));		 infileCat_.push_back(0);

    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data()));		 infileCat_.push_back(2);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data()));		 infileCat_.push_back(2);
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		 infileCat_.push_back(2);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		         infileCat_.push_back(2);
    infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data()));		 infileCat_.push_back(2);
    infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data()));		 infileCat_.push_back(2);
    infileName_.push_back(Form("%sWZ.root" ,filesPath.Data())); 		 infileCat_.push_back(2);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));		 infileCat_.push_back(2);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));		 infileCat_.push_back(2);
    infileName_.push_back(Form("%sWGstar.root" ,filesPath.Data()));		 infileCat_.push_back(2);
    infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));		         infileCat_.push_back(2);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data()));		 infileCat_.push_back(2);
  }

  if(whichAnaFlow == 0 || whichAnaFlow == 2){
    if     (whichDY == 0)
   {infileName_.push_back(Form("%sDYJetsToLL_M-50_LO_Pt000To050.root" ,filesPath.Data()));  infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_M-50_LO_Pt100to200.root" ,filesPath.Data()));  infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_M-50_LO_Pt200toInf.root" ,filesPath.Data()));  infileCat_.push_back(1);
    }
    else if(whichDY == 1)
   {infileName_.push_back(Form("%sDYJetsToLL_M-50_NLO.root",filesPath.Data()));  infileCat_.push_back(1);}
    else if(whichDY == 2)
   {infileName_.push_back(Form("%sDYJetsToLL_POWHEG.root",filesPath.Data()));    infileCat_.push_back(1);}
    else if(whichDY == 3)
   {infileName_.push_back(Form("%sDYJetsToLL_Pt0To50.root",filesPath.Data()));   infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_Pt50To100.root",filesPath.Data())); infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_Pt100To250.root",filesPath.Data()));infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_Pt250To400.root",filesPath.Data()));infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_Pt400To650.root",filesPath.Data()));infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_Pt650ToInf.root",filesPath.Data()));infileCat_.push_back(1);
    }
    else {return;}
  }

  TFile *fLepton_Eta_SF = TFile::Open(Form("MitAnalysisRunII/data/80x/scalefactors_80x_eta_sf_37ifb_ori.root"));
  TH1D* scalefactors_Muon_Eta = (TH1D*)fLepton_Eta_SF->Get("scalefactors_Muon_Eta"); scalefactors_Muon_Eta->SetDirectory(0);
  TH1D* scalefactors_Electron_Eta = (TH1D*)fLepton_Eta_SF->Get("scalefactors_Electron_Eta"); scalefactors_Electron_Eta->SetDirectory(0);
  fLepton_Eta_SF->Close();

  TFile *fLepton_SF_mu_central = TFile::Open(Form("MitAnalysisRunII/data/80x/scalefactors_80x_dylan_MediumIdOnly_ori.root"));
  TH2D* scalefactors_Medium_Muon = (TH2D*)fLepton_SF_mu_central->Get("scalefactors_Medium_Muon"); scalefactors_Medium_Muon->SetDirectory(0);
  fLepton_SF_mu_central->Close();

  TFile *fLepton_SF_el_central = TFile::Open(Form("MitAnalysisRunII/data/80x/scalefactors_80x_dylan_MediumIdOnly_ori.root"));
  TH2D* scalefactors_Medium_Electron = (TH2D*)fLepton_SF_el_central->Get("scalefactors_Medium_Electron"); scalefactors_Medium_Electron->SetDirectory(0);
  fLepton_SF_el_central->Close();

  double getMaxPtForSFs[2] = {scalefactors_Medium_Muon                  ->GetYaxis()->GetBinCenter(scalefactors_Medium_Muon		     ->GetNbinsY()),
                              scalefactors_Medium_Electron              ->GetYaxis()->GetBinCenter(scalefactors_Medium_Electron		     ->GetNbinsY())
		              };

  const int nBinEta = 28; Float_t xbinsEta[nBinEta+1] = {-2.4,-2.3,-2.2,-2.1,-2.0,-1.7,-1.6,-1.5,-1.4,-1.2,-0.8,-0.5,-0.3,-0.2,0.0,
                                                          0.2, 0.3, 0.5, 0.8, 1.2, 1.4, 1.5, 1.6, 1.7, 2.0, 2.1, 2.2, 2.3, 2.4};

  const int nBinPt = 20; Float_t xbinsPt[nBinPt+1] = {20,21,22,23,24,25,26,27,28,29,30,32,35,40,45,50,60,80,100,200,1000};

  TH2D *den_HLT_Muon[2];
  TH2D *num_HLT_Muon[2];
  TH2D *eff_HLT_Muon[2];
  TH2D *ratio_HLT_Muon = new TH2D(Form("ratio_HLT_Muon"), Form("ratio_HLT_Muon"), nBinEta, xbinsEta, nBinPt, xbinsPt);

  TH2D *den_HLT_Electron[2];
  TH2D *num_HLT_Electron[2];
  TH2D *eff_HLT_Electron[2];
  TH2D *ratio_HLT_Electron = new TH2D(Form("ratio_HLT_Electron"), Form("ratio_HLT_Electron"), nBinEta, xbinsEta, nBinPt, xbinsPt);
  for(int i=0; i<2; i++){
   den_HLT_Muon[i] = new TH2D(Form("den_HLT_Muon_%d",i), Form("den_HLT_Muon_%d",i), nBinEta, xbinsEta, nBinPt, xbinsPt);
   num_HLT_Muon[i] = new TH2D(Form("num_HLT_Muon_%d",i), Form("num_HLT_Muon_%d",i), nBinEta, xbinsEta, nBinPt, xbinsPt);
   eff_HLT_Muon[i] = new TH2D(Form("eff_HLT_Muon_%d",i), Form("eff_HLT_Muon_%d",i), nBinEta, xbinsEta, nBinPt, xbinsPt);
   den_HLT_Electron[i] = new TH2D(Form("den_HLT_Electron_%d",i), Form("den_HLT_Electron_%d",i), nBinEta, xbinsEta, nBinPt, xbinsPt);
   num_HLT_Electron[i] = new TH2D(Form("num_HLT_Electron_%d",i), Form("num_HLT_Electron_%d",i), nBinEta, xbinsEta, nBinPt, xbinsPt);
   eff_HLT_Electron[i] = new TH2D(Form("eff_HLT_Electron_%d",i), Form("eff_HLT_Electron_%d",i), nBinEta, xbinsEta, nBinPt, xbinsPt);
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

      if(thePandaFlat.nLooseLep != 2) continue;

      if(TMath::Abs(thePandaFlat.looseLep1PdgId)!=TMath::Abs(thePandaFlat.looseLep2PdgId))continue;

      if(TMath::Abs(thePandaFlat.looseLep1Eta) >= 2.4 || TMath::Abs(thePandaFlat.looseLep2Eta) >= 2.4) continue;

      if(thePandaFlat.looseLep1Pt <= 20 || thePandaFlat.looseLep2Pt <= 20)continue;

      int lepType = -1;
      if     (abs(thePandaFlat.looseLep1PdgId)==13 && abs(thePandaFlat.looseLep2PdgId)==13 && thePandaFlat.looseLep1PdgId*thePandaFlat.looseLep2PdgId<0) lepType = 0;
      else if(abs(thePandaFlat.looseLep1PdgId)==11 && abs(thePandaFlat.looseLep2PdgId)==11 && thePandaFlat.looseLep1PdgId*thePandaFlat.looseLep2PdgId<0) lepType = 1;
      else if(abs(thePandaFlat.looseLep1PdgId)==13 && abs(thePandaFlat.looseLep2PdgId)==11 && thePandaFlat.looseLep1PdgId*thePandaFlat.looseLep2PdgId<0) lepType = 2;
      else if(abs(thePandaFlat.looseLep1PdgId)==11 && abs(thePandaFlat.looseLep2PdgId)==13 && thePandaFlat.looseLep1PdgId*thePandaFlat.looseLep2PdgId<0) lepType = 2;
      else if(abs(thePandaFlat.looseLep1PdgId)==13 && abs(thePandaFlat.looseLep2PdgId)==13 && thePandaFlat.looseLep1PdgId*thePandaFlat.looseLep2PdgId>0) lepType = 3;
      else if(abs(thePandaFlat.looseLep1PdgId)==11 && abs(thePandaFlat.looseLep2PdgId)==11 && thePandaFlat.looseLep1PdgId*thePandaFlat.looseLep2PdgId>0) lepType = 4;
      else if(abs(thePandaFlat.looseLep1PdgId)==13 && abs(thePandaFlat.looseLep2PdgId)==11 && thePandaFlat.looseLep1PdgId*thePandaFlat.looseLep2PdgId>0) lepType = 5;
      else if(abs(thePandaFlat.looseLep1PdgId)==11 && abs(thePandaFlat.looseLep2PdgId)==13 && thePandaFlat.looseLep1PdgId*thePandaFlat.looseLep2PdgId>0) lepType = 5;
      else {printf("Impossible dilepton combination: %d %d\n",thePandaFlat.looseLep1PdgId,thePandaFlat.looseLep2PdgId); continue;}

      double thePDGMass[2] = {mass_mu, mass_mu};
      if     (abs(lepType) == 1) {thePDGMass[0] = mass_el; thePDGMass[1] = mass_el;}
      else if(abs(lepType) == 2 && abs(thePandaFlat.looseLep1PdgId)==11) {thePDGMass[0] = mass_el;}
      else if(abs(lepType) == 2 && abs(thePandaFlat.looseLep2PdgId)==11) {thePDGMass[1] = mass_el;}
      TLorentzVector vLoose1,vLoose2;
      vLoose1.SetPtEtaPhiM(thePandaFlat.looseLep1Pt,thePandaFlat.looseLep1Eta,thePandaFlat.looseLep1Phi,thePDGMass[0]);
      vLoose2.SetPtEtaPhiM(thePandaFlat.looseLep2Pt,thePandaFlat.looseLep2Eta,thePandaFlat.looseLep2Phi,thePDGMass[1]);
      bool passMllSel = TMath::Abs((vLoose1+vLoose2).M()-91.1876) < 15;
      if(passMllSel == false)continue;

      bool passLepId = ((thePandaFlat.looseLep1SelBit & kMedium) == kMedium) && ((thePandaFlat.looseLep2SelBit & kMedium) == kMedium);
      if(passLepId == false) continue;

      bool passTrigger = (thePandaFlat.trigger & kMuTagTrig) == kMuTagTrig || (thePandaFlat.trigger & kEGTagTrig) == kEGTagTrig;
      if(passTrigger == false) continue;

      int theCategory = infileCat_[ifile];
      double totalWeight = 1.0;
      if(theCategory != 0){

        double the_eta_sf[2] = {1.0, 1.0};
        if(abs(thePandaFlat.looseLep1PdgId)==13){
          double etal = thePandaFlat.looseLep1Eta; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
          int binEta = scalefactors_Muon_Eta->GetXaxis()->FindFixBin(etal);
          the_eta_sf[0] = scalefactors_Muon_Eta->GetBinContent(binEta);
        } else {
          double etal = thePandaFlat.looseLep1Eta; if(etal >= 2.5) etal = 2.4999; else if(etal <= -2.5) etal = -2.4999;
          int binEta = scalefactors_Electron_Eta->GetXaxis()->FindFixBin(etal);
          the_eta_sf[0] = scalefactors_Electron_Eta->GetBinContent(binEta);
        }        
        if(abs(thePandaFlat.looseLep2PdgId)==13){
          double etal = thePandaFlat.looseLep2Eta; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
          int binEta = scalefactors_Muon_Eta->GetXaxis()->FindFixBin(etal);
          the_eta_sf[1] = scalefactors_Muon_Eta->GetBinContent(binEta);
        } else {
          double etal = thePandaFlat.looseLep2Eta; if(etal >= 2.5) etal = 2.4999; else if(etal <= -2.5) etal = -2.4999;
          int binEta = scalefactors_Electron_Eta->GetXaxis()->FindFixBin(etal);
          the_eta_sf[1] = scalefactors_Electron_Eta->GetBinContent(binEta);
        }

        double sfWeightLepEff[2] = {1.0, 1.0};
        if(abs(thePandaFlat.looseLep1PdgId)==13){
          double etal = thePandaFlat.looseLep1Eta; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
          int binXT   = scalefactors_Medium_Muon->GetXaxis()->FindFixBin(etal);
          int binYT_c = scalefactors_Medium_Muon->GetYaxis()->FindFixBin(TMath::Min((double)thePandaFlat.looseLep1Pt,getMaxPtForSFs[0]));
	  sfWeightLepEff[0]        = scalefactors_Medium_Muon                   ->GetBinContent(binXT,binYT_c);
        } else {
          double etal = thePandaFlat.looseLep1Eta; if(etal >= 2.5) etal = 2.4999; else if(etal <= -2.5) etal = -2.4999;
          int binXT   = scalefactors_Medium_Electron->GetXaxis()->FindFixBin(etal);
          int binYT_c = scalefactors_Medium_Electron->GetYaxis()->FindFixBin(TMath::Min((double)thePandaFlat.looseLep1Pt,getMaxPtForSFs[1]));
	  sfWeightLepEff[0]        = scalefactors_Medium_Electron                   ->GetBinContent(binXT,binYT_c);
        }
        if(abs(thePandaFlat.looseLep2PdgId)==13){
          double etal = thePandaFlat.looseLep2Eta; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
          int binXT   = scalefactors_Medium_Muon->GetXaxis()->FindFixBin(etal);
          int binYT_c = scalefactors_Medium_Muon->GetYaxis()->FindFixBin(TMath::Min((double)thePandaFlat.looseLep2Pt,getMaxPtForSFs[0]));
	  sfWeightLepEff[1]        = scalefactors_Medium_Muon                   ->GetBinContent(binXT,binYT_c);
        } else {
          double etal = thePandaFlat.looseLep2Eta; if(etal >= 2.5) etal = 2.4999; else if(etal <= -2.5) etal = -2.4999;
          int binXT   = scalefactors_Medium_Electron->GetXaxis()->FindFixBin(etal);
          int binYT_c = scalefactors_Medium_Electron->GetYaxis()->FindFixBin(TMath::Min((double)thePandaFlat.looseLep2Pt,getMaxPtForSFs[1]));
	  sfWeightLepEff[1]        = scalefactors_Medium_Electron                   ->GetBinContent(binXT,binYT_c);
        }

        totalWeight = thePandaFlat.normalizedWeight * lumi * thePandaFlat.sf_pu *
		      the_eta_sf[0] * sfWeightLepEff[0] *
		      the_eta_sf[1] * sfWeightLepEff[1];

        if(theCategory == 2) totalWeight = -1.0 * totalWeight;
      }
      int theChan = 1;
      if(theCategory == 0 || theCategory == 2) theChan = 0;

      double xprobeLep1 = thePandaFlat.looseLep1Eta;
      double xprobeLep2 = thePandaFlat.looseLep2Eta;

      if(abs(thePandaFlat.looseLep1PdgId)==13 && (thePandaFlat.looseLep1SelBit & kTrigger) == kTrigger){
        den_HLT_Muon[theChan]->Fill(xprobeLep2,thePandaFlat.looseLep2Pt,totalWeight);
        if((thePandaFlat.looseLep2SelBit & kTrigger) == kTrigger) {
          num_HLT_Muon[theChan]->Fill(xprobeLep2,thePandaFlat.looseLep2Pt,totalWeight);
        }
      }       
      if(abs(thePandaFlat.looseLep1PdgId)==11 && (thePandaFlat.looseLep1SelBit & kTrigger) == kTrigger){
        den_HLT_Electron[theChan]->Fill(xprobeLep2,thePandaFlat.looseLep2Pt,totalWeight);
        if((thePandaFlat.looseLep2SelBit & kTrigger) == kTrigger) {
          num_HLT_Electron[theChan]->Fill(xprobeLep2,thePandaFlat.looseLep2Pt,totalWeight);
        }
      }

      if(abs(thePandaFlat.looseLep2PdgId)==13 && (thePandaFlat.looseLep2SelBit & kTrigger) == kTrigger){
        den_HLT_Muon[theChan]->Fill(xprobeLep1,thePandaFlat.looseLep1Pt,totalWeight);
        if((thePandaFlat.looseLep1SelBit & kTrigger) == kTrigger) {
          num_HLT_Muon[theChan]->Fill(xprobeLep1,thePandaFlat.looseLep1Pt,totalWeight);
        }
      }       
      if(abs(thePandaFlat.looseLep2PdgId)==11 && (thePandaFlat.looseLep2SelBit & kTrigger) == kTrigger){
        den_HLT_Electron[theChan]->Fill(xprobeLep1,thePandaFlat.looseLep1Pt,totalWeight);
        if((thePandaFlat.looseLep1SelBit & kTrigger) == kTrigger) {
          num_HLT_Electron[theChan]->Fill(xprobeLep1,thePandaFlat.looseLep1Pt,totalWeight);
        }
      }

    } // end events loop
    the_input_file->Close();
  } // end chain loop

  double eff, unc;
  for(int i=1; i<=eff_HLT_Muon[0]->GetNbinsX(); i++){
    for(int j=1; j<=eff_HLT_Muon[0]->GetNbinsY(); j++){
      printf("mu(%2d,%2d) mu: ",i,j);
      for(int ncha=0; ncha<2; ncha++){
        eff = 0.0; unc = 1.0;
	if(den_HLT_Muon[ncha]->GetBinContent(i,j) > 0 && num_HLT_Muon[ncha]->GetBinContent(i,j)){
          eff = TMath::Min(num_HLT_Muon[ncha]->GetBinContent(i,j)/den_HLT_Muon[ncha]->GetBinContent(i,j),1.0);
          unc = sqrt(eff*(1-eff)/den_HLT_Muon[ncha]->GetBinContent(i,j));
	}
        eff_HLT_Muon[ncha]->SetBinContent(i,j,eff);
        eff_HLT_Muon[ncha]->SetBinError  (i,j,unc);
	if(ncha == 0) printf("data = "); else printf("mc = ");
        printf("%.3f(%7.1f/%7.1f) %.3f ",eff,num_HLT_Muon[ncha]->GetBinContent(i,j),den_HLT_Muon[ncha]->GetBinContent(i,j),unc);
      }
      printf("\n");
    }
  }

  for(int i=1; i<=eff_HLT_Electron[0]->GetNbinsX(); i++){
    for(int j=1; j<=eff_HLT_Electron[0]->GetNbinsY(); j++){
      printf("mu(%2d,%2d) mu: ",i,j);
      for(int ncha=0; ncha<2; ncha++){
        eff = 0.0; unc = 1.0;
	if(den_HLT_Electron[ncha]->GetBinContent(i,j) > 0 && num_HLT_Electron[ncha]->GetBinContent(i,j) > 0){
          eff = TMath::Min(num_HLT_Electron[ncha]->GetBinContent(i,j)/den_HLT_Electron[ncha]->GetBinContent(i,j),1.0);
          unc = sqrt(eff*(1-eff)/den_HLT_Electron[ncha]->GetBinContent(i,j));
	}
        eff_HLT_Electron[ncha]->SetBinContent(i,j,eff);
        eff_HLT_Electron[ncha]->SetBinError  (i,j,unc);
 	if(ncha == 0) printf("data = "); else printf("mc = ");
        printf("%.3f(%7.1f/%7.1f) %.3f ",eff,num_HLT_Electron[ncha]->GetBinContent(i,j),den_HLT_Electron[ncha]->GetBinContent(i,j),unc);
      }
      printf("\n");
    }
  }

  ratio_HLT_Muon    ->Add(eff_HLT_Muon[0]);
  ratio_HLT_Muon    ->Divide(eff_HLT_Muon[1]);
  ratio_HLT_Electron->Add(eff_HLT_Electron[0]);
  ratio_HLT_Electron->Divide(eff_HLT_Electron[1]);

  char output[200];
  sprintf(output,"histo_hlttrigger_dy%d.root",whichDY);	
  TFile* outFilePlotsHistos = new TFile(output,"recreate");
  outFilePlotsHistos->cd();
  for(int ncha=0; ncha<2; ncha++){
    den_HLT_Muon[ncha]    ->Write();
    num_HLT_Muon[ncha]    ->Write();
    eff_HLT_Muon[ncha]    ->Write();
    den_HLT_Electron[ncha]->Write();
    num_HLT_Electron[ncha]->Write();
    eff_HLT_Electron[ncha]->Write();
  }
  ratio_HLT_Muon    ->Write();
  ratio_HLT_Electron->Write();
  outFilePlotsHistos->Close();

}
