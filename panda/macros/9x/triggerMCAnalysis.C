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
#include "TRandom.h"
#include "TLorentzVector.h"

#include "MitAnalysisRunII/panda/macros/9x/pandaFlat.C"
#include "MitAnalysisRunII/panda/macros/9x/common.h"

const double mcPrescale = 1;

void triggerMCAnalysis()
{
  double lumi = 40.0;
  TString filesPath    = "/data/t3home000/ceballos/panda/v_004_0/";
  TString pileUpName = "MitAnalysisRunII/data/90x/puWeights_90x.root";

  //*******************************************************
  //Input Files
  //*******************************************************
  vector<TString> infileName_;
  vector<Int_t> infileCat_;
  infileName_.push_back(Form("%sZllHbb_alltriggers.root",filesPath.Data()));      infileCat_.push_back(0);
  infileName_.push_back(Form("%sZllHbb_officialtriggers.root",filesPath.Data())); infileCat_.push_back(1);
  infileName_.push_back(Form("%sWlnHbb_alltriggers.root",filesPath.Data()));      infileCat_.push_back(2);
  infileName_.push_back(Form("%sWlnHbb_officialtriggers.root",filesPath.Data())); infileCat_.push_back(3);

  TFile *fPUFile = TFile::Open(pileUpName.Data());
  TH1D *fhDPU = (TH1D*)(fPUFile->Get("puWeights")); assert(fhDPU); fhDPU->SetDirectory(0);
  delete fPUFile;

  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 64;
  const int histBins = 9;
  TH1D* histo[allPlots][histBins];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    if     (thePlot >=  0 && thePlot <=  5) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >=  6 && thePlot <= 11) {nBinPlot =  50; xminPlot =  0.0; xmaxPlot = 2.5;}
    else if(thePlot >= 12 && thePlot <= 14) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 400;}
    else if(thePlot >= 15 && thePlot <= 20) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >= 21 && thePlot <= 26) {nBinPlot =  50; xminPlot =  0.0; xmaxPlot = 2.5;}
    else if(thePlot >= 27 && thePlot <= 29) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 400;}
    else if(thePlot >= 30 && thePlot <= 35) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >= 36 && thePlot <= 41) {nBinPlot =  50; xminPlot =  0.0; xmaxPlot = 2.5;}
    else if(thePlot >= 42 && thePlot <= 44) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 400;}

    else if(thePlot >= 46 && thePlot <= 47) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >= 48 && thePlot <= 49) {nBinPlot =  50; xminPlot =  0.0; xmaxPlot = 2.5;}
    else if(thePlot >= 50 && thePlot <= 51) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 400;}
    else if(thePlot >= 52 && thePlot <= 53) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >= 54 && thePlot <= 55) {nBinPlot =  50; xminPlot =  0.0; xmaxPlot = 2.5;}
    else if(thePlot >= 56 && thePlot <= 57) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 400;}
    else if(thePlot >= 58 && thePlot <= 59) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >= 60 && thePlot <= 61) {nBinPlot =  50; xminPlot =  0.0; xmaxPlot = 2.5;}
    else if(thePlot >= 62 && thePlot <= 63) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 400;}

    TH1D* histos = new TH1D("histos", "histos", nBinPlot, xminPlot, xmaxPlot);
    histos->Sumw2();
    for(int i=0; i<histBins; i++) histo[thePlot][i] = (TH1D*) histos->Clone(Form("histo%d",i));
    histos->Reset();histos->Clear();
  }

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
     
      if(thePandaFlat.nLooseLep < 1 || thePandaFlat.nJot < 2) continue;

      int theCategory = infileCat_[ifile];

      bool passFullTrigger = (thePandaFlat.trigger & (1<<kEMuTrig)) != 0       || (thePandaFlat.trigger & (1<<kDoubleMuTrig)) != 0  ||
                             (thePandaFlat.trigger & (1<<kSingleMuTrig)) != 0  || (thePandaFlat.trigger & (1<<kDoubleEleTrig)) != 0 ||
                             (thePandaFlat.trigger & (1<<kSingleEleTrig)) != 0;

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
	if(thePandaFlat.electronPt[i] > 35) ptSelCuts[2]++;
      }

      if((int)looseLepPt.size() != thePandaFlat.nLooseLep) printf("IMPOSSIBLE\n");

      double sfPileUp = nPUScaleFactor(fhDPU,thePandaFlat.pu);

      double totalWeight = thePandaFlat.normalizedWeight * lumi * sfPileUp * thePandaFlat.sf_l1Prefire;

      // 2-l study
      if(thePandaFlat.nLooseLep >= 2 && ptSelCuts[0] >= 1 && ptSelCuts[1] >= 2 && theCategory <= 1) {
        bool passLepId = ((looseLepSelBit[0] & kMedium) == kMedium) && ((looseLepSelBit[1] & kMedium) == kMedium);
        if(passLepId == true) {
          int lepType = -1;
          if     (abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13) lepType = 0;
          else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11) lepType = 1;
          else lepType = 2;
          double thePDGMass[2] = {mass_mu, mass_mu};
          if     (abs(lepType) == 1) {thePDGMass[0] = mass_el; thePDGMass[1] = mass_el;}
          else if(abs(lepType) == 2 && abs(looseLepPdgId[0])==11) {thePDGMass[0] = mass_el;}
          else if(abs(lepType) == 2 && abs(looseLepPdgId[1])==11) {thePDGMass[1] = mass_el;}
          TLorentzVector v1,v2;
          v1.SetPtEtaPhiM(looseLepPt[0],looseLepEta[0],looseLepPhi[0],thePDGMass[0]);
          v2.SetPtEtaPhiM(looseLepPt[1],looseLepEta[1],looseLepPhi[1],thePDGMass[1]);
	  histo[lepType+ 0][theCategory]->Fill(TMath::Min(v1.Pt(),199.999),totalWeight);
	  histo[lepType+ 3][theCategory]->Fill(TMath::Min(v2.Pt(),199.999),totalWeight);
	  histo[lepType+ 6][theCategory]->Fill(TMath::Abs(v1.Eta()),totalWeight);
	  histo[lepType+ 9][theCategory]->Fill(TMath::Abs(v2.Eta()),totalWeight);
	  histo[lepType+12][theCategory]->Fill(TMath::Min((v1+v2).Pt(),399.999),totalWeight);
	  if(passFullTrigger == true){
	    histo[lepType+15][theCategory]->Fill(TMath::Min(v1.Pt(),199.999),totalWeight);
	    histo[lepType+18][theCategory]->Fill(TMath::Min(v2.Pt(),199.999),totalWeight);
	    histo[lepType+21][theCategory]->Fill(TMath::Abs(v1.Eta()),totalWeight);
	    histo[lepType+24][theCategory]->Fill(TMath::Abs(v2.Eta()),totalWeight);
  	    histo[lepType+27][theCategory]->Fill(TMath::Min((v1+v2).Pt(),399.999),totalWeight);
	  }
	  if(lepType == 0 && (thePandaFlat.trigger & (1<<kDoubleMuTrig)) != 0){
	    histo[30][theCategory]->Fill(TMath::Min(v1.Pt(),199.999),totalWeight);
	    histo[33][theCategory]->Fill(TMath::Min(v2.Pt(),199.999),totalWeight);
	    histo[36][theCategory]->Fill(TMath::Abs(v1.Eta()),totalWeight);
	    histo[39][theCategory]->Fill(TMath::Abs(v2.Eta()),totalWeight);
            histo[42][theCategory]->Fill(TMath::Min((v1+v2).Pt(),399.999),totalWeight);
	  }
	  if(lepType == 1 && (thePandaFlat.trigger & (1<<kDoubleEleTrig)) != 0){
	    histo[31][theCategory]->Fill(TMath::Min(v1.Pt(),199.999),totalWeight);
	    histo[34][theCategory]->Fill(TMath::Min(v2.Pt(),199.999),totalWeight);
	    histo[37][theCategory]->Fill(TMath::Abs(v1.Eta()),totalWeight);
	    histo[40][theCategory]->Fill(TMath::Abs(v2.Eta()),totalWeight);
	    histo[43][theCategory]->Fill(TMath::Min((v1+v2).Pt(),399.999),totalWeight);
	  }
	  if(lepType == 1 && (thePandaFlat.trigger & (1<<kEMuTrig)) != 0){
	    histo[32][theCategory]->Fill(TMath::Min(v1.Pt(),199.999),totalWeight);
	    histo[35][theCategory]->Fill(TMath::Min(v2.Pt(),199.999),totalWeight);
	    histo[38][theCategory]->Fill(TMath::Abs(v1.Eta()),totalWeight);
	    histo[41][theCategory]->Fill(TMath::Abs(v2.Eta()),totalWeight);
	    histo[44][theCategory]->Fill(TMath::Min((v1+v2).Pt(),399.999),totalWeight);
	  }
	}
      }
      // 1-l study
      else if(thePandaFlat.nLooseLep >= 1 && ptSelCuts[2] >= 1 && theCategory >= 2) {
        theCategory = theCategory - 2;
        bool passLepId = ((looseLepSelBit[0] & kTight) == kTight);
        if(passLepId == true) {
          int lepType = -1;
          if     (abs(looseLepPdgId[0])==13) lepType = 0;
          else if(abs(looseLepPdgId[0])==11) lepType = 1;
          double thePDGMass[1] = {mass_mu};
          if     (abs(lepType) == 1) {thePDGMass[0] = mass_el;}
          TLorentzVector v1,metP4;
          v1.SetPtEtaPhiM(looseLepPt[0],looseLepEta[0],looseLepPhi[0],thePDGMass[0]);
          metP4.SetPtEtaPhiM(thePandaFlat.pfmet,0,thePandaFlat.pfmetphi,0);
	  histo[lepType+46][theCategory]->Fill(TMath::Min(v1.Pt(),199.999),totalWeight);
	  histo[lepType+48][theCategory]->Fill(TMath::Abs(v1.Eta()),totalWeight);
	  histo[lepType+50][theCategory]->Fill(TMath::Min((v1+metP4).Pt(),399.999),totalWeight);
	  if(passFullTrigger == true){
	    histo[lepType+52][theCategory]->Fill(TMath::Min(v1.Pt(),199.999),totalWeight);
	    histo[lepType+54][theCategory]->Fill(TMath::Abs(v1.Eta()),totalWeight);
  	    histo[lepType+56][theCategory]->Fill(TMath::Min((v1+metP4).Pt(),399.999),totalWeight);
	  }
	  if(lepType == 0 && (thePandaFlat.trigger & (1<<kSingleMuTrig)) != 0){
	    histo[58][theCategory]->Fill(TMath::Min(v1.Pt(),199.999),totalWeight);
	    histo[60][theCategory]->Fill(TMath::Abs(v1.Eta()),totalWeight);
  	    histo[62][theCategory]->Fill(TMath::Min((v1+metP4).Pt(),399.999),totalWeight);
	  }
	  if(lepType == 1 && (thePandaFlat.trigger & (1<<kSingleEleTrig)) != 0){
	    histo[59][theCategory]->Fill(TMath::Min(v1.Pt(),199.999),totalWeight);
	    histo[61][theCategory]->Fill(TMath::Abs(v1.Eta()),totalWeight);
  	    histo[63][theCategory]->Fill(TMath::Min((v1+metP4).Pt(),399.999),totalWeight);
	  }
	}
      }

    } // end event loop
  } // end samples loop

  char output[200];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    TString addSuffix = "";
    sprintf(output,"histoMCTrigger_%d%s.root",thePlot,addSuffix.Data());	
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    printf("(%2d) %8.3f / %8.3f\n",thePlot,
    histo[thePlot][0]->GetSumOfWeights(),histo[thePlot][1]->GetSumOfWeights());
    for(int np=0; np<histBins; np++) histo[thePlot][np]->Write();
    outFilePlotsNote->Close();
  }

}
