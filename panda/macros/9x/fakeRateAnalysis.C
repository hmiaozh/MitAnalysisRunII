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
int year, int nbjets = 0
){
  int whichYear = -1;
  if     (year == 2016) whichYear = Y2016;
  else if(year == 2017) whichYear = Y2017;
  else if(year == 2018) whichYear = Y2018;
  else {printf("Wrong year (%d)!\n",year); return;}

  double minLepPt[2] = {10.0, 12.0};

  TString addSuffix = "";
  if(nbjets > 0) addSuffix = "_btagged";

  //*******************************************************
  //Inputs
  //*******************************************************
  vector<TString> infileName_;
  vector<int> infileCat_;

  TString filesPath;
  TString fnpvWeightsFileName;
  TString puPath;
  if     (year == 2018) {
    filesPath = "/data/t3home000/ceballos/panda/v_007_0/";
    fnpvWeightsFileName = "MitAnalysisRunII/data/90x/npvWeights_2018_FakeTriggers.root";
    puPath = "MitAnalysisRunII/data/90x/puWeights_90x_2018.root";

    infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	         infileCat_.push_back(0);
    infileName_.push_back(Form("%sWWinc.root" ,filesPath.Data())); 	         infileCat_.push_back(1);
    //infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	           infileCat_.push_back(1);
    //infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	           infileCat_.push_back(1);
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		 infileCat_.push_back(1);
    infileName_.push_back(Form("%sTT1L.root" ,filesPath.Data()));		 infileCat_.push_back(1);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));                  infileCat_.push_back(1);
    infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(1);
    infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(1);
    //infileName_.push_back(Form("%sWZno3l.root" ,filesPath.Data()));	           infileCat_.push_back(1);
    infileName_.push_back(Form("%sWZ3l_amcnlo.root" ,filesPath.Data()));         infileCat_.push_back(1);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	         infileCat_.push_back(1);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	         infileCat_.push_back(1);
    infileName_.push_back(Form("%sTTVV.root" ,filesPath.Data()));  	         infileCat_.push_back(1);
    infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));		         infileCat_.push_back(1);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	         infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data())); infileCat_.push_back(2);
    infileName_.push_back(Form("%sDYJetsToLL_M-50_LO.root",filesPath.Data()));   infileCat_.push_back(2);
    infileName_.push_back(Form("%sWJets.root" ,filesPath.Data()));               infileCat_.push_back(3);
  }
  else if(year == 2017) {
    filesPath = "/data/t3home000/ceballos/panda/v_005_0/";
    fnpvWeightsFileName = "MitAnalysisRunII/data/90x/npvWeights_2017_FakeTriggers.root";
    puPath = "MitAnalysisRunII/data/90x/puWeights_90x_2017.root";

    infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	         infileCat_.push_back(0);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	         infileCat_.push_back(1);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	         infileCat_.push_back(1);
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		 infileCat_.push_back(1);
    infileName_.push_back(Form("%sTT1L.root" ,filesPath.Data()));		 infileCat_.push_back(1);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		         infileCat_.push_back(1);
    infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(1);
    infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(1);
    infileName_.push_back(Form("%sWZno3l.root" ,filesPath.Data()));	         infileCat_.push_back(1);
    infileName_.push_back(Form("%sWZ3l_powheg.root" ,filesPath.Data()));         infileCat_.push_back(1);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	         infileCat_.push_back(1);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	         infileCat_.push_back(1);
    infileName_.push_back(Form("%sTTVV.root" ,filesPath.Data()));  	         infileCat_.push_back(1);
    infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));		         infileCat_.push_back(1);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	         infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data())); infileCat_.push_back(2);
    infileName_.push_back(Form("%sDYJetsToLL_M-50_LO.root",filesPath.Data()));   infileCat_.push_back(2);
    infileName_.push_back(Form("%sWJets.root" ,filesPath.Data()));               infileCat_.push_back(3);
  }
  else if(year == 2016) {
    filesPath = "/data/t3home000/ceballos/panda/v_003_0/";
    fnpvWeightsFileName = "MitAnalysisRunII/data/90x/npvWeights_2016_FakeTriggers.root";
    puPath = "MitAnalysisRunII/data/80x/puWeights_80x_37ifb.root";

    infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	         infileCat_.push_back(0);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	         infileCat_.push_back(1);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	         infileCat_.push_back(1);
    infileName_.push_back(Form("%sTT.root" ,filesPath.Data()));		         infileCat_.push_back(1);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		         infileCat_.push_back(1);
    infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(1);
    infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(1);
    infileName_.push_back(Form("%sWZ.root" ,filesPath.Data()));	                 infileCat_.push_back(1);
    infileName_.push_back(Form("%sWGstar.root" ,filesPath.Data()));	         infileCat_.push_back(1);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	         infileCat_.push_back(1);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	         infileCat_.push_back(1);
    infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));		         infileCat_.push_back(1);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	         infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data())); infileCat_.push_back(2);
    infileName_.push_back(Form("%sDYJetsToLL_M-50_NLO.root",filesPath.Data()));  infileCat_.push_back(2);
    infileName_.push_back(Form("%sWJets.root" ,filesPath.Data()));               infileCat_.push_back(3);
  }
  else {
    return;
  }
  
  TFile *fnpvWeights = TFile::Open(fnpvWeightsFileName.Data());
  TH1D* hDnpvWeights = (TH1D*)fnpvWeights->Get("npvWeights"); hDnpvWeights->SetDirectory(0);
  fnpvWeights->Close();

  TFile *fPUFile = TFile::Open(Form("%s",puPath.Data()));
  TH1D *fhDPU     = (TH1D*)(fPUFile->Get("puWeights"));     assert(fhDPU);     fhDPU    ->SetDirectory(0);
  delete fPUFile;

  const int nLepSel = 16;
  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 26;
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

  const int nBinPt  = 5; Double_t xPtbins [nBinPt+1 ] = {10.0, 20.0, 25.0, 30.0, 35.0, 45.0};
  const int nBinEta = 4; Double_t xEtabins[nBinEta+1] = {0.0, 1.0, 1.5, 2.0, 2.5};

  double prescales[2][nBinPt]; for(int i=0; i<2; i++) for(int j=0; j<nBinPt; j++) prescales[i][j] = 1.0;
  TH1D* histoZllPt[2][histBins];
  TH1D* histoWlnPt[2][histBins];
  TH2D* histoFakeDenEtaPt[2][histBins];
  TH2D* histoFakeNumSelEtaPt[nLepSel][2][histBins];
  TH2D* histoFakeEffSelEtaPt[nLepSel][2];
  for(int i=0; i<2; i++){
    for(int j=0; j<histBins; j++){
      histoZllPt[i][j] = new TH1D(Form("histoZllPt_%d_%d",i,j), Form("histoZllPt_%d_%d",i,j), nBinPt, xPtbins);
      histoWlnPt[i][j] = new TH1D(Form("histoWlnPt_%d_%d",i,j), Form("histoWlnPt_%d_%d",i,j), nBinPt, xPtbins);
      histoFakeDenEtaPt[i][j] = new TH2D(Form("histoFakeDenEtaPt_%d_%d",i,j), Form("histoFakeDenEtaPt_%d_%d",i,j), nBinEta, xEtabins, nBinPt, xPtbins);
      for(int nsel=0; nsel<nLepSel; nsel++){
        histoFakeNumSelEtaPt[nsel][i][j] = new TH2D(Form("histoFakeNumSelEtaPt_%d_%d_%d",nsel,i,j), Form("histoFakeNumSelEtaPt_%d_%d_%d",nsel,i,j), nBinEta, xEtabins, nBinPt, xPtbins);
        if(j==0) histoFakeEffSelEtaPt[nsel][i] = new TH2D(Form("histoFakeEffSelEtaPt_%d_%d",nsel,i), Form("histoFakeEffSelEtaPt_%d_%d",nsel,i), nBinEta, xEtabins, nBinPt, xPtbins);
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

      if(thePandaFlat.metFilter == 0) continue;

      vector<float>  looseLepPt,looseLepEta,looseLepPhi,looseLepSF;
      vector<int> looseLepSelBit,looseLepPdgId,looseLepTripleCharge,looseLepMissingHits;
      int ptSelCuts[3] = {0,0,0};
      for(int i=0; i<thePandaFlat.nLooseMuon; i++){
        looseLepPt.push_back(thePandaFlat.muonPt[i]);
        looseLepEta.push_back(thePandaFlat.muonEta[i]);
        looseLepPhi.push_back(thePandaFlat.muonPhi[i]);
        looseLepSF.push_back(thePandaFlat.muonSfReco[i] * thePandaFlat.muonSfMedium[i]);
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
        looseLepSF.push_back(thePandaFlat.electronSfReco[i] * thePandaFlat.electronSfMedium[i]);
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
      if     (year == 2016) vMet.SetPtEtaPhiM(thePandaFlat.pfmet,0.0,thePandaFlat.pfmetphi,0.0);
      else if(year == 2017) vMet.SetPtEtaPhiM(thePandaFlat.puppimet,0.0,thePandaFlat.puppimetphi,0.0);
      else if(year == 2018) vMet.SetPtEtaPhiM(thePandaFlat.pfmet,0.0,thePandaFlat.pfmetphi,0.0);
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
      if(((lepType == 0 && thePandaFlat.nJot >= 1) || 
          (lepType == 1 && thePandaFlat.nJot >= 1)) &&
	  thePandaFlat.jetNBtags >= nbjets) passJetSel = kTRUE;
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
	double puWeight = nPUScaleFactor(fhDPU, thePandaFlat.pu);
        int binNpv = hDnpvWeights->GetXaxis()->FindFixBin(TMath::Min((double)thePandaFlat.npv,49.499));
	double npvWeights = hDnpvWeights->GetBinContent(binNpv);
        
        totalWeight = thePandaFlat.normalizedWeight * (lumiV[whichYear]/1000.) * puWeight * thePandaFlat.sf_l1Prefire * looseLepSF[0] * npvWeights;
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
        histo[lepType+ 16 + 2*binPt][theCategory]->Fill(TMath::Min(vMet.Pt(),199.999),totalWeight);
      }

      if(passFakeNumSel == true) {
        bool passLepSel[nLepSel+1] = {(looseLepSelBit[0] & kFake) == kFake, 
	                              (looseLepSelBit[0] & kFake) == kFake && (looseLepSelBit[0] & kMedium) == kMedium,
	                              (looseLepSelBit[0] & kFake) == kFake && (looseLepSelBit[0] & kTight) == kTight,
	                              (looseLepSelBit[0] & kFake) == kFake && (looseLepSelBit[0] & kTight) == kTight && (looseLepSelBit[0] & kDxyz) == kDxyz,
	                              (looseLepSelBit[0] & kFake) == kFake && (looseLepSelBit[0] & kTight) == kTight && (looseLepSelBit[0] & kDxyz) == kDxyz && looseLepMissingHits[0] == 0,
	                              (looseLepSelBit[0] & kFake) == kFake && (looseLepSelBit[0] & kTight) == kTight && (looseLepSelBit[0] & kDxyz) == kDxyz && looseLepMissingHits[0] == 0 && looseLepTripleCharge[0] == 1,
			              (looseLepSelBit[0] & kFake) == kFake && (looseLepSelBit[0] & kEleMvaWP90) == kEleMvaWP90,
			              (looseLepSelBit[0] & kFake) == kFake && (looseLepSelBit[0] & kEleMvaWP80) == kEleMvaWP80,
			              (looseLepSelBit[0] & kFake) == kFake && (looseLepSelBit[0] & kEleMvaWP80) == kEleMvaWP80 && looseLepTripleCharge[0] == 1,
			              (looseLepSelBit[0] & kFake) == kFake && (looseLepSelBit[0] & kMvaMedium) == kMvaMedium,
			              (looseLepSelBit[0] & kFake) == kFake && (looseLepSelBit[0] & kMvaTight) == kMvaTight,
			              (looseLepSelBit[0] & kFake) == kFake && (looseLepSelBit[0] & kMiniIsoMedium) == kMiniIsoMedium,
			              (looseLepSelBit[0] & kFake) == kFake && (looseLepSelBit[0] & kMiniIsoTight) == kMiniIsoTight,
			              (looseLepSelBit[0] & kFake) == kFake && (looseLepSelBit[0] & kMvaMedium) == kMvaMedium && (looseLepSelBit[0] & kMiniIsoMedium) == kMiniIsoMedium,
			              (looseLepSelBit[0] & kFake) == kFake && (looseLepSelBit[0] & kMvaTight) == kMvaTight && (looseLepSelBit[0] & kMiniIsoTight) == kMiniIsoTight,
			              (looseLepSelBit[0] & kFake) == kFake && (looseLepSelBit[0] & kTight) == kTight && (looseLepSelBit[0] & kDxyz) == kDxyz && (looseLepSelBit[0] & kMiniIsoMedium) == kMiniIsoMedium,
			              (looseLepSelBit[0] & kFake) == kFake && (looseLepSelBit[0] & kTight) == kTight && (looseLepSelBit[0] & kDxyz) == kDxyz && (looseLepSelBit[0] & kMiniIsoTight) == kMiniIsoTight
			             };
        if(passLepSel[0]) histoFakeDenEtaPt[lepType][theCategory]->Fill(TMath::Min(TMath::Abs(vLoose1.Eta()),2.499),TMath::Min(vLoose1.Pt(),44.999),totalWeight);
        for(int nsel=0; nsel<nLepSel; nsel++){
	  if(passLepSel[nsel+1]) histoFakeNumSelEtaPt[nsel][lepType][theCategory]->Fill(TMath::Min(TMath::Abs(vLoose1.Eta()),2.499),TMath::Min(vLoose1.Pt(),44.999),totalWeight);
        }
      }
    } // end events loop
    the_input_file->Close();
  } // end chain loop

  char output[200];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    sprintf(output,"histoFake_%d_%d%s.root",year,thePlot,addSuffix.Data());	
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
      sprintf(output,"histoZllPt_%d_%d%s.root",year,thePlot,addSuffix.Data());	
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
      sprintf(output,"histoWlnPt_%d_%d%s.root",year,thePlot,addSuffix.Data());	
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
    sprintf(output,"histoFakeEtaPt_%d%s.root",year,addSuffix.Data()); 
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    double den,num,eff,unc;
    for(int thePlot=0; thePlot<2; thePlot++){
      printf("**************************** thePlot = %d ****************************\n",thePlot);
      for(int i=1; i<=histoFakeDenEtaPt[thePlot][0]->GetNbinsX(); i++){
        for(int j=1; j<=histoFakeDenEtaPt[thePlot][0]->GetNbinsY(); j++){
          for(int nsel=0; nsel<nLepSel; nsel++){
            den = histoFakeDenEtaPt[thePlot][0]         ->GetBinContent(i,j) - (histoFakeDenEtaPt[thePlot][1]         ->GetBinContent(i,j)+histoFakeDenEtaPt[thePlot][2]         ->GetBinContent(i,j)+histoFakeDenEtaPt[thePlot][3]         ->GetBinContent(i,j))*prescales[thePlot][j-1];
            num = histoFakeNumSelEtaPt[nsel][thePlot][0]->GetBinContent(i,j) - (histoFakeNumSelEtaPt[nsel][thePlot][1]->GetBinContent(i,j)+histoFakeNumSelEtaPt[nsel][thePlot][2]->GetBinContent(i,j)+histoFakeNumSelEtaPt[nsel][thePlot][3]->GetBinContent(i,j))*prescales[thePlot][j-1];
            eff = 1.0; unc = 0.0;
            if(den > 0 && num > 0){
              eff = num / den;
              unc = sqrt(eff*(1-eff)/den);
	    }
            else if(den > 0){
              eff = 0.0;
              unc = TMath::Min(sqrt(1.0/den),0.999);
            }
            histoFakeEffSelEtaPt[nsel][thePlot]->SetBinContent(i,j,eff);
            histoFakeEffSelEtaPt[nsel][thePlot]->SetBinError  (i,j,unc);
	    printf("(%d,%d,%2d): %9.1f %9.1f %9.1f %9.1f / %9.1f %9.1f %9.1f %9.1f = %9.1f %9.1f %5.3f %5.3f %5.3f - %7.5f\n",i,j,nsel,
	    histoFakeNumSelEtaPt[nsel][thePlot][0]->GetBinContent(i,j),histoFakeNumSelEtaPt[nsel][thePlot][1]->GetBinContent(i,j),histoFakeNumSelEtaPt[nsel][thePlot][2]->GetBinContent(i,j),histoFakeNumSelEtaPt[nsel][thePlot][3]->GetBinContent(i,j),
	    histoFakeDenEtaPt         [thePlot][0]->GetBinContent(i,j),histoFakeDenEtaPt         [thePlot][1]->GetBinContent(i,j),histoFakeDenEtaPt         [thePlot][2]->GetBinContent(i,j),histoFakeDenEtaPt         [thePlot][3]->GetBinContent(i,j),
	    num,den,eff,unc,histoFakeEffSelEtaPt[nsel][thePlot]->GetBinContent(i,j),prescales[thePlot][j-1]);
          }
        }
      }
      for(int np=0; np<histBins; np++) histoFakeDenEtaPt[thePlot][np]->Write();
      for(int np=0; np<histBins; np++) for(int nsel=0; nsel<nLepSel; nsel++) histoFakeNumSelEtaPt[nsel][thePlot][np]->Write();
      for(int nsel=0; nsel<nLepSel; nsel++) histoFakeEffSelEtaPt[nsel][thePlot]->Write();
    }
    outFilePlotsNote->Close();
  }
}
