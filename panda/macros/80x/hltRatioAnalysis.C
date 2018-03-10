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
#include "TLorentzVector.h"

#include "MitAnalysisRunII/panda/macros/80x/pandaFlat.C"
#include "MitAnalysisRunII/panda/macros/80x/common.h"

void hltRatioAnalysis(
int typeAna = 1
){

  //*******************************************************
  //Input Files
  //*******************************************************
  TString filesPath    = "/data/t3home000/ceballos/panda/v_001_0/";
  vector<TString> infileName_;
  vector<int> infileCat_;

  if     (typeAna == 0){
    infileName_.push_back(Form("%sMET.root" ,filesPath.Data())); 			 infileCat_.push_back(0);
  }
  else if(typeAna == 1){
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 			 infileCat_.push_back(1);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 			 infileCat_.push_back(1);
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data())); 			 infileCat_.push_back(1);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));				 infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data()));  	 infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_Pt0To50.root" ,filesPath.Data()));		 infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_Pt100To250.root" ,filesPath.Data()));	 infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_Pt250To400.root" ,filesPath.Data()));	 infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_Pt400To650.root" ,filesPath.Data()));	 infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_Pt50To100.root" ,filesPath.Data())); 	 infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_M-50_NLO.root",filesPath.Data()));		 infileCat_.push_back(1);
  }

  TFile *fefficiency_hlt = TFile::Open(Form("MitAnalysisRunII/data/80x/efficiency_hlt_80x.root"));
  TH2D* eff_HLT_Muon     = (TH2D*)fefficiency_hlt->Get("eff_HLT_Muon");     eff_HLT_Muon    ->SetDirectory(0);
  TH2D* eff_HLT_Electron = (TH2D*)fefficiency_hlt->Get("eff_HLT_Electron"); eff_HLT_Electron->SetDirectory(0);
  fefficiency_hlt->Close();

  TH2D *den_HLT_Muon_idTight  = (TH2D*)eff_HLT_Muon->Clone("den_HLT_Muon_idTight");  den_HLT_Muon_idTight->Reset();
  TH2D *num_HLT_Muon_idTight  = (TH2D*)eff_HLT_Muon->Clone("num_HLT_Muon_idTight");  num_HLT_Muon_idTight->Reset();
  TH2D *eff_HLT_Muon_idTight  = (TH2D*)eff_HLT_Muon->Clone("eff_HLT_Muon_idTight");  eff_HLT_Muon_idTight->Reset();
  TH2D *den_HLT_Muon_idMedium = (TH2D*)eff_HLT_Muon->Clone("den_HLT_Muon_idMedium"); den_HLT_Muon_idMedium->Reset();
  TH2D *num_HLT_Muon_idMedium = (TH2D*)eff_HLT_Muon->Clone("num_HLT_Muon_idMedium"); num_HLT_Muon_idMedium->Reset();
  TH2D *eff_HLT_Muon_idMedium = (TH2D*)eff_HLT_Muon->Clone("eff_HLT_Muon_idMedium"); eff_HLT_Muon_idMedium->Reset();
  TH2D *ratio_HLT_Muon        = (TH2D*)eff_HLT_Muon->Clone("ratio_HLT_Muon");        ratio_HLT_Muon       ->Reset();

  TH2D *den_HLT_Electron_idTight  = (TH2D*)eff_HLT_Electron->Clone("den_HLT_Electron_idTight");  den_HLT_Electron_idTight->Reset();
  TH2D *num_HLT_Electron_idTight  = (TH2D*)eff_HLT_Electron->Clone("num_HLT_Electron_idTight");  num_HLT_Electron_idTight->Reset();
  TH2D *eff_HLT_Electron_idTight  = (TH2D*)eff_HLT_Electron->Clone("eff_HLT_Electron_idTight");  eff_HLT_Electron_idTight->Reset();
  TH2D *den_HLT_Electron_idMedium = (TH2D*)eff_HLT_Electron->Clone("den_HLT_Electron_idMedium"); den_HLT_Electron_idMedium->Reset();
  TH2D *num_HLT_Electron_idMedium = (TH2D*)eff_HLT_Electron->Clone("num_HLT_Electron_idMedium"); num_HLT_Electron_idMedium->Reset();
  TH2D *eff_HLT_Electron_idMedium = (TH2D*)eff_HLT_Electron->Clone("eff_HLT_Electron_idMedium"); eff_HLT_Electron_idMedium->Reset();
  TH2D *ratio_HLT_Electron        = (TH2D*)eff_HLT_Electron->Clone("ratio_HLT_Electron");        ratio_HLT_Electron       ->Reset();

  TFile *fLepton_Eta_SF = TFile::Open(Form("MitAnalysisRunII/data/80x/scalefactors_80x_eta_sf_37ifb_ori.root"));
  TH1D* scalefactors_Muon_Eta = (TH1D*)fLepton_Eta_SF->Get("scalefactors_Muon_Eta"); scalefactors_Muon_Eta->SetDirectory(0);
  TH1D* scalefactors_Electron_Eta = (TH1D*)fLepton_Eta_SF->Get("scalefactors_Electron_Eta"); scalefactors_Electron_Eta->SetDirectory(0);
  fLepton_Eta_SF->Close();

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

      if(TMath::Abs(thePandaFlat.looseLep1Eta) >= 2.4 || TMath::Abs(thePandaFlat.looseLep2Eta) >= 2.4) continue;
      if(TMath::Abs(thePandaFlat.looseLep1PdgId)==TMath::Abs(thePandaFlat.looseLep2PdgId))continue;
      if(thePandaFlat.looseLep1Pt <= 20 || thePandaFlat.looseLep2Pt <= 20)continue;

      int theCategory = infileCat_[ifile];
      double totalWeight = 1.0;
      if(theCategory != 0){

        double the_eta_sf[2] = {1.0, 1.0};
        if(abs(thePandaFlat.looseLep1PdgId)==13){
          double etal = thePandaFlat.looseLep1Eta; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
          int binEta = scalefactors_Muon_Eta->GetXaxis()->FindFixBin(etal);
          the_eta_sf[0] = scalefactors_Muon_Eta->GetBinContent(binEta);
        } else {
          double etal = thePandaFlat.looseLep1Eta; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
          int binEta = scalefactors_Electron_Eta->GetXaxis()->FindFixBin(etal);
          the_eta_sf[0] = scalefactors_Electron_Eta->GetBinContent(binEta);
        }        
        if(abs(thePandaFlat.looseLep2PdgId)==13){
          double etal = thePandaFlat.looseLep2Eta; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
          int binEta = scalefactors_Muon_Eta->GetXaxis()->FindFixBin(etal);
          the_eta_sf[1] = scalefactors_Muon_Eta->GetBinContent(binEta);
        } else {
          double etal = thePandaFlat.looseLep2Eta; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
          int binEta = scalefactors_Electron_Eta->GetXaxis()->FindFixBin(etal);
          the_eta_sf[1] = scalefactors_Electron_Eta->GetBinContent(binEta);
        }

        totalWeight = thePandaFlat.sf_pu * the_eta_sf[0] * the_eta_sf[1];
      }
      
      if((thePandaFlat.looseLep1SelBit & kTight) == kTight && (thePandaFlat.looseLep1SelBit & kFake) == kFake){
        if(abs(thePandaFlat.looseLep1PdgId)==13){
          den_HLT_Muon_idTight->Fill(thePandaFlat.looseLep1Eta,thePandaFlat.looseLep1Pt,totalWeight);
	  if((thePandaFlat.trigger & kMuTagTrig) == kMuTagTrig) {
            num_HLT_Muon_idTight->Fill(thePandaFlat.looseLep1Eta,thePandaFlat.looseLep1Pt,totalWeight);
	  }
        } else {
          den_HLT_Electron_idTight->Fill(thePandaFlat.looseLep1Eta,thePandaFlat.looseLep1Pt,totalWeight);
	  if((thePandaFlat.trigger & kEGTagTrig) == kEGTagTrig) {
            num_HLT_Electron_idTight->Fill(thePandaFlat.looseLep1Eta,thePandaFlat.looseLep1Pt,totalWeight);
	  }
	}
      }

      if((thePandaFlat.looseLep1SelBit & kMedium) == kMedium){
        if(abs(thePandaFlat.looseLep1PdgId)==13){
          den_HLT_Muon_idMedium->Fill(thePandaFlat.looseLep1Eta,thePandaFlat.looseLep1Pt,totalWeight);
	  if((thePandaFlat.trigger & kMuTagTrig) == kMuTagTrig) {
            num_HLT_Muon_idMedium->Fill(thePandaFlat.looseLep1Eta,thePandaFlat.looseLep1Pt,totalWeight);
	  }
        } else {
          den_HLT_Electron_idMedium->Fill(thePandaFlat.looseLep1Eta,thePandaFlat.looseLep1Pt,totalWeight);
	  if((thePandaFlat.trigger & kEGTagTrig) == kEGTagTrig) {
            num_HLT_Electron_idMedium->Fill(thePandaFlat.looseLep1Eta,thePandaFlat.looseLep1Pt,totalWeight);
	  }
	}
      }
      
      if((thePandaFlat.looseLep2SelBit & kTight) == kTight && (thePandaFlat.looseLep2SelBit & kFake) == kFake){
        if(abs(thePandaFlat.looseLep2PdgId)==13){
          den_HLT_Muon_idTight->Fill(thePandaFlat.looseLep2Eta,thePandaFlat.looseLep2Pt,totalWeight);
	  if((thePandaFlat.trigger & kMuTagTrig) == kMuTagTrig) {
            num_HLT_Muon_idTight->Fill(thePandaFlat.looseLep2Eta,thePandaFlat.looseLep2Pt,totalWeight);
	  }
        } else {
          den_HLT_Electron_idTight->Fill(thePandaFlat.looseLep2Eta,thePandaFlat.looseLep2Pt,totalWeight);
	  if((thePandaFlat.trigger & kEGTagTrig) == kEGTagTrig) {
            num_HLT_Electron_idTight->Fill(thePandaFlat.looseLep2Eta,thePandaFlat.looseLep2Pt,totalWeight);
	  }
	}
      }

      if((thePandaFlat.looseLep2SelBit & kMedium) == kMedium){
        if(abs(thePandaFlat.looseLep2PdgId)==13){
          den_HLT_Muon_idMedium->Fill(thePandaFlat.looseLep2Eta,thePandaFlat.looseLep2Pt,totalWeight);
	  if((thePandaFlat.trigger & kMuTagTrig) == kMuTagTrig) {
            num_HLT_Muon_idMedium->Fill(thePandaFlat.looseLep2Eta,thePandaFlat.looseLep2Pt,totalWeight);
	  }
        } else {
          den_HLT_Electron_idMedium->Fill(thePandaFlat.looseLep2Eta,thePandaFlat.looseLep2Pt,totalWeight);
	  if((thePandaFlat.trigger & kEGTagTrig) == kEGTagTrig) {
            num_HLT_Electron_idMedium->Fill(thePandaFlat.looseLep2Eta,thePandaFlat.looseLep2Pt,totalWeight);
	  }
	}
      }

    } // end events loop
    the_input_file->Close();
  } // end chain loop

  double eff, unc;
  for(int i=1; i<=eff_HLT_Muon_idTight->GetNbinsX(); i++){
    for(int j=1; j<=eff_HLT_Muon_idTight->GetNbinsY(); j++){
      eff = num_HLT_Muon_idTight->GetBinContent(i,j)/den_HLT_Muon_idTight->GetBinContent(i,j);
      unc = sqrt(eff*(1-eff)/den_HLT_Muon_idTight->GetBinContent(i,j));
      eff_HLT_Muon_idTight->SetBinContent(i,j,eff);
      eff_HLT_Muon_idTight->SetBinError  (i,j,unc);
      printf("(%2d,%2d) mutight/medium: %.3f(%7.1f/%7.1f) %.3f / ",i,j,eff,num_HLT_Muon_idTight->GetBinContent(i,j),den_HLT_Muon_idTight->GetBinContent(i,j),unc);

      eff = num_HLT_Muon_idMedium->GetBinContent(i,j)/den_HLT_Muon_idMedium->GetBinContent(i,j);
      unc = sqrt(eff*(1-eff)/den_HLT_Muon_idMedium->GetBinContent(i,j));
      eff_HLT_Muon_idMedium->SetBinContent(i,j,eff);
      eff_HLT_Muon_idMedium->SetBinError  (i,j,unc);
      printf("%.3f(%7.1f/%7.1f) %.3f | %.3f %.3f\n",eff,num_HLT_Muon_idMedium->GetBinContent(i,j),den_HLT_Muon_idMedium->GetBinContent(i,j),unc,eff_HLT_Muon->GetBinContent(i,j),eff_HLT_Muon->GetBinError(i,j));
    }
  }

  for(int i=1; i<=eff_HLT_Electron_idTight->GetNbinsX(); i++){
    for(int j=1; j<=eff_HLT_Electron_idTight->GetNbinsY(); j++){
      eff = num_HLT_Electron_idTight->GetBinContent(i,j)/den_HLT_Electron_idTight->GetBinContent(i,j);
      unc = sqrt(eff*(1-eff)/den_HLT_Electron_idTight->GetBinContent(i,j));
      eff_HLT_Electron_idTight->SetBinContent(i,j,eff);
      eff_HLT_Electron_idTight->SetBinError  (i,j,unc);
      printf("(%2d,%2d) etight/medium: %.3f(%7.1f/%7.1f) %.3f / ",i,j,eff,num_HLT_Electron_idTight->GetBinContent(i,j),den_HLT_Electron_idTight->GetBinContent(i,j),unc);

      eff = num_HLT_Electron_idMedium->GetBinContent(i,j)/den_HLT_Electron_idMedium->GetBinContent(i,j);
      unc = sqrt(eff*(1-eff)/den_HLT_Electron_idMedium->GetBinContent(i,j));
      eff_HLT_Electron_idMedium->SetBinContent(i,j,eff);
      eff_HLT_Electron_idMedium->SetBinError  (i,j,unc);
      printf("%.3f(%7.1f/%7.1f) %.3f | %.3f %.3f\n",eff,num_HLT_Electron_idMedium->GetBinContent(i,j),den_HLT_Electron_idMedium->GetBinContent(i,j),unc,eff_HLT_Electron->GetBinContent(i,j),eff_HLT_Electron->GetBinError(i,j));

    }
  }
  ratio_HLT_Muon    ->Add(eff_HLT_Muon_idMedium);
  ratio_HLT_Muon    ->Divide(eff_HLT_Muon_idTight);
  ratio_HLT_Electron->Add(eff_HLT_Electron_idMedium);
  ratio_HLT_Electron->Divide(eff_HLT_Electron_idTight);

  char output[200];
  sprintf(output,"histo_trigger_ratio_ana%d.root",typeAna);	
  TFile* outFilePlotsHistos = new TFile(output,"recreate");
  outFilePlotsHistos->cd();
  den_HLT_Muon_idTight     ->Write();
  num_HLT_Muon_idTight     ->Write();
  eff_HLT_Muon_idTight     ->Write();
  den_HLT_Muon_idMedium    ->Write();
  num_HLT_Muon_idMedium    ->Write();
  eff_HLT_Muon_idMedium    ->Write();
  ratio_HLT_Muon           ->Write();
  den_HLT_Electron_idTight     ->Write();
  num_HLT_Electron_idTight     ->Write();
  eff_HLT_Electron_idTight     ->Write();
  den_HLT_Electron_idMedium    ->Write();
  num_HLT_Electron_idMedium    ->Write();
  eff_HLT_Electron_idMedium    ->Write();
  ratio_HLT_Electron           ->Write();
  outFilePlotsHistos->Close();

}
