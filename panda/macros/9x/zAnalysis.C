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
#include "MitAnalysisRunII/panda/macros/9x/trigger_auxiliar.h"

const double mcPrescale = 1;

void zAnalysis(int year, bool isTopSel = false, int whichDY = 0,  int debug = 0)
{
  // trigger
  double trgEff [3][nTrgBinPt1][nTrgBinPt2][nTrgBinEta1][nTrgBinEta2];
  double trgEffE[3][nTrgBinPt1][nTrgBinPt2][nTrgBinEta1][nTrgBinEta2];
  initialize_trgEff(trgEff, trgEffE, year);
  double k_eff = sqrt(20285930./12446486.);

  //*******************************************************
  //Inputs
  //*******************************************************
  double WSSF[5],WSSFE[5];
  if     (year == 2016){
    for(int i=0; i<5; i++) {WSSF[i] = WSSF_2016[i]; WSSFE[i] = WSSFE_2016[i];}
  }
  else if(year == 2017){
    for(int i=0; i<5; i++) {WSSF[i] = WSSF_2017[i]; WSSFE[i] = WSSFE_2017[i];}
  }

  vector<TString> infileName_;
  vector<int> infileCat_;

  double lumi;
  TString filesPath;
  TString fLepton_FakesName;
  TString puPath;
  TString npvPath;
  if(year == 2017) {
    lumi = 41.5;
    filesPath = "/data/t3home000/ceballos/panda/v_004_0/";
    fLepton_FakesName = "MitAnalysisRunII/data/90x/histoFakeEtaPt_2017.root";
    puPath = "MitAnalysisRunII/data/90x/puWeights_90x.root";
    npvPath = "MitAnalysisRunII/data/90x/npvWeights_2017.root";

    infileName_.push_back(Form("%sdata.root",filesPath.Data()));                 infileCat_.push_back(kPlotData);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotqqWW);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotggWW);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data())); infileCat_.push_back(kPlotDY);
    if     (whichDY == 0){
    infileName_.push_back(Form("%sDYJetsToLL_M-50_NLO.root",filesPath.Data()));  infileCat_.push_back(kPlotDY);
    }
    else if(whichDY == 1){
    infileName_.push_back(Form("%sDYNJetsToLL_NLO.root",filesPath.Data()));      infileCat_.push_back(kPlotDY);
    //infileName_.push_back(Form("%sDYJetsToLL_M-50_NLO.root",filesPath.Data()));  infileCat_.push_back(kPlotDY);
    }
    else if(whichDY == 2){
    infileName_.push_back(Form("%sDYNJetsToLL.root",filesPath.Data()));          infileCat_.push_back(kPlotDY);
    }
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));                infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));                  infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sWZno3l.root" ,filesPath.Data()));              infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sWZ3l_powheg.root" ,filesPath.Data()));         infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));                 infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));                 infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTVV.root" ,filesPath.Data()));                infileCat_.push_back(kPlotVVV);
    //infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));                  infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotHiggs);
  }
  else if(year == 2016) {
    lumi = 35.9;
    filesPath = "/data/t3home000/ceballos/panda/v_002_0/";
    fLepton_FakesName = "MitAnalysisRunII/data/90x/histoFakeEtaPt_2016.root";
    puPath = "MitAnalysisRunII/data/80x/puWeights_80x_37ifb.root";
    npvPath = "MitAnalysisRunII/data/90x/npvWeights_2016.root";

    infileName_.push_back(Form("%sdata.root",filesPath.Data()));                  infileCat_.push_back(kPlotData);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotqqWW);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotggWW);
    if     (whichDY == 0 || whichDY == 1){
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data()));  infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt0To50.root",filesPath.Data()));    infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt50To100.root",filesPath.Data()));  infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt100To250.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt250To400.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt400To650.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt650ToInf.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
    }
    else if(whichDY == 2){
    infileName_.push_back(Form("%sDYNJetsToLL.root",filesPath.Data()));          infileCat_.push_back(kPlotDY);
    }
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));                 infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));                   infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sWZ.root" ,filesPath.Data()));                   infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sWGstar.root" ,filesPath.Data()));               infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));                  infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));                  infileCat_.push_back(kPlotVVV);
    //infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));                   infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotHiggs);
  }
  else {
    return;
  }

  TFile *fLepton_Fakes = TFile::Open(fLepton_FakesName.Data());
  TH2D* histoFakeEffSelMediumEtaPt_m = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_0_0"); histoFakeEffSelMediumEtaPt_m->SetDirectory(0);
  TH2D* histoFakeEffSelMediumEtaPt_e = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_0_1"); histoFakeEffSelMediumEtaPt_e->SetDirectory(0);
  TH2D* histoFakeEffSelTightEtaPt_m  = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_2_0"); histoFakeEffSelTightEtaPt_m ->SetDirectory(0);
  TH2D* histoFakeEffSelTightEtaPt_e  = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_2_1"); histoFakeEffSelTightEtaPt_e ->SetDirectory(0);

  TFile *fPUFile = TFile::Open(Form("%s",puPath.Data()));
  TH1D *fhDPU     = (TH1D*)(fPUFile->Get("puWeights"));     assert(fhDPU);     fhDPU    ->SetDirectory(0);
  TH1D *fhDPUUp   = (TH1D*)(fPUFile->Get("puWeightsUp"));   assert(fhDPUUp);   fhDPUUp  ->SetDirectory(0);
  TH1D *fhDPUDown = (TH1D*)(fPUFile->Get("puWeightsDown")); assert(fhDPUDown); fhDPUDown->SetDirectory(0);
  delete fPUFile;

  TFile *fNPVFile = TFile::Open(Form("%s",npvPath.Data()));
  TH1D *fhDNPV    = (TH1D*)(fNPVFile->Get("npvWeights"));   assert(fhDNPV);    fhDNPV   ->SetDirectory(0);
  delete fNPVFile;

  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 78;
  TH1D* histo[allPlots][nPlotCategories];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    if     (thePlot >=  0 && thePlot <=  1) {nBinPlot = 120; xminPlot = 91.1876-15; xmaxPlot = 91.1876+15;}
    else if(thePlot >=  2 && thePlot <=  2) {nBinPlot = 200; xminPlot = 50.0; xmaxPlot = 250;}
    else if(thePlot >=  3 && thePlot <=  4) {nBinPlot = 120; xminPlot = 91.1876-15; xmaxPlot = 91.1876+15;}
    else if(thePlot >=  5 && thePlot <=  5) {nBinPlot = 200; xminPlot = 50.0; xmaxPlot = 250;}
    else if(thePlot >=  6 && thePlot <= 11) {nBinPlot =  10; xminPlot = -0.5; xmaxPlot = 9.5;}
    else if(thePlot >= 12 && thePlot <= 14) {nBinPlot =1000; xminPlot =  0.0; xmaxPlot =1000;}
    else if(thePlot >= 15 && thePlot <= 29) {nBinPlot = 500; xminPlot =  0.0; xmaxPlot = 500;}
    else if(thePlot >= 30 && thePlot <= 35) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = TMath::Pi();}
    else if(thePlot >= 36 && thePlot <= 41) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 5.0;}
    else if(thePlot >= 42 && thePlot <= 47) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 5.0;}
    else if(thePlot >= 48 && thePlot <= 50) {nBinPlot =  80; xminPlot = -0.5; xmaxPlot = 79.5;}
    else if(thePlot >= 51 && thePlot <= 56) {nBinPlot = 100; xminPlot = -2.5; xmaxPlot = 2.5;}
    else if(thePlot >= 57 && thePlot <= 62) {nBinPlot = 200; xminPlot = 25.0; xmaxPlot = 225;}
    else if(thePlot >= 63 && thePlot <= 68) {nBinPlot =   5; xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >= 69 && thePlot <= 71) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >= 72 && thePlot <= 74) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 1.0;}
    else if(thePlot >= 75 && thePlot <= 77) {nBinPlot = 200; xminPlot = -5.0; xmaxPlot = 5.0;}
    
    if(isTopSel == true && (thePlot >= 0 && thePlot <= 5)) {nBinPlot = 200; xminPlot = 50.0; xmaxPlot = 250;}

    TH1D* histos = new TH1D("histos", "histos", nBinPlot, xminPlot, xmaxPlot);
    histos->Sumw2();
    for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = (TH1D*) histos->Clone(Form("histo%d",i));
    histos->Reset();histos->Clear();
  }

  TH1D* histoWSStudy[5][5][4]; nBinPlot = 120; xminPlot = 91.1876-15; xmaxPlot = 91.1876+15;
  for(int i=0; i<5; i++){
    for(int j=0; j<5; j++){
      for(int np=0; np<4; np++){
        histoWSStudy[i][j][np] = new TH1D(Form("histoWSStudy_%d_%d_%d",i,j,np), Form("histoWSStudy_%d_%d_%d",i,j,np), nBinPlot, xminPlot, xmaxPlot);
        histoWSStudy[i][j][np]->Sumw2();
      }
    }
  }

  TH1D* histoEffStudy[8][nPlotCategories];TH1D* histoFakeStudy[8][nPlotCategories]; nBinPlot =  17; xminPlot = -0.5; xmaxPlot = 16.5;
  {
    TH1D* histos = new TH1D("histos", "histos", nBinPlot, xminPlot, xmaxPlot);
    histos->Sumw2();
    for(int np=0; np<8; np++){
      for(int i=0; i<nPlotCategories; i++) histoEffStudy[np][i]  = (TH1D*) histos->Clone(Form("histo%d",i));
      for(int i=0; i<nPlotCategories; i++) histoFakeStudy[np][i] = (TH1D*) histos->Clone(Form("histo%d",i));
    }
    histos->Reset();histos->Clear();
  }

  TH1D* histoPtEffStudy[4][17][nPlotCategories];; nBinPlot =  20; xminPlot = 25; xmaxPlot = 125;
  {
    TH1D* histos = new TH1D("histos", "histos", nBinPlot, xminPlot, xmaxPlot);
    histos->Sumw2();
    for(int np=0; np<4; np++){
      for(int nsel=0; nsel<17; nsel++){
        for(int i=0; i<nPlotCategories; i++) histoPtEffStudy[np][nsel][i] = (TH1D*) histos->Clone(Form("histo%d",i));
      }
    }
    histos->Reset();histos->Clear();
  }

  for(UInt_t ifile=0; ifile<infileName_.size(); ifile++) {
    printf("sampleNames(%d): %s\n",ifile,infileName_[ifile].Data());
    TFile *the_input_file = TFile::Open(infileName_[ifile].Data());
    TTree *the_input_tree = (TTree*)the_input_file->FindObjectAny("events");
    
    pandaFlat thePandaFlat(the_input_tree);
    double theMCPrescale = 1.00; if(infileCat_[ifile] != 0) theMCPrescale = mcPrescale;
    Long64_t nentries = thePandaFlat.fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = thePandaFlat.LoadTree(jentry);
      if (ientry < 0) break;
      nb = thePandaFlat.fChain->GetEntry(jentry);   nbytes += nb;
      if (jentry%1000000 == 0) printf("--- reading event %8lld (%8lld) of %8lld\n",jentry,ientry,nentries);
      if (infileCat_[ifile] != 0 && jentry%(int)theMCPrescale != 0) continue;

      bool passTrigger = (thePandaFlat.trigger & (1<<kEMuTrig)) != 0       || (thePandaFlat.trigger & (1<<kDoubleMuTrig)) != 0  ||
                         (thePandaFlat.trigger & (1<<kSingleMuTrig)) != 0  || (thePandaFlat.trigger & (1<<kDoubleEleTrig)) != 0 ||
                         (thePandaFlat.trigger & (1<<kSingleEleTrig)) != 0;
      if(passTrigger == false) continue;
      if(thePandaFlat.metFilter == 0) continue;

      if(thePandaFlat.nLooseLep != 2) continue;

      vector<float>  looseLepPt,looseLepEta,looseLepPhi,looseLepSF;
      vector<int> looseLepSelBit,looseLepPdgId,looseLepTripleCharge,looseLepMissingHits;
      int ptSelCuts[3] = {0,0,0};
      for(int i=0; i<thePandaFlat.nLooseMuon; i++){
        looseLepPt.push_back(thePandaFlat.muonPt[i]);
        looseLepEta.push_back(thePandaFlat.muonEta[i]);
        looseLepPhi.push_back(thePandaFlat.muonPhi[i]);
        looseLepSF.push_back(thePandaFlat.muonSfReco[i] * thePandaFlat.muonSfTight[i]);
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
        looseLepSF.push_back(thePandaFlat.electronSfReco[i] * thePandaFlat.electronSfTight[i]);
        looseLepPdgId.push_back(thePandaFlat.electronPdgId[i]);
        looseLepTripleCharge.push_back(thePandaFlat.electronTripleCharge[i]);
        looseLepMissingHits.push_back(thePandaFlat.electronNMissingHits[i]);
        if(thePandaFlat.electronPt[i] > 25) ptSelCuts[0]++;
        if(thePandaFlat.electronPt[i] > 20) ptSelCuts[1]++;
        if(thePandaFlat.electronPt[i] > 10) ptSelCuts[2]++;
      }

      if((int)looseLepPt.size() != thePandaFlat.nLooseLep) printf("IMPOSSIBLE\n");

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
      int theCategory = infileCat_[ifile];

      int lepType = -1;
      if     (abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13) lepType = 0;
      else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11) lepType = 1;
      else                                                            lepType = 2;

      TLorentzVector dilep = vLoose[0]+vLoose[1];
      TLorentzVector vMet,vTrkMet,vMetUp,vMetDown;
      vTrkMet.SetPtEtaPhiM(thePandaFlat.trkmet,0.0,thePandaFlat.trkmetphi,0.0);
      if     (year == 2016) {
        vMet    .SetPtEtaPhiM(thePandaFlat.pfmet,0.0,thePandaFlat.pfmetphi,0.0);
        vMetUp  .SetPtEtaPhiM(thePandaFlat.pfmet_JESTotalUp  ,0.0,thePandaFlat.pfmetphi_JESTotalUp  ,0.0);
        vMetDown.SetPtEtaPhiM(thePandaFlat.pfmet_JESTotalDown,0.0,thePandaFlat.pfmetphi_JESTotalDown,0.0);
      } 
      else if(year == 2017){
        vMet    .SetPtEtaPhiM(thePandaFlat.puppimet,0.0,thePandaFlat.puppimetphi,0.0);
        vMetUp  .SetPtEtaPhiM(thePandaFlat.puppimet_JESTotalUp  ,0.0,thePandaFlat.puppimetphi_JESTotalUp  ,0.0);
        vMetDown.SetPtEtaPhiM(thePandaFlat.puppimet_JESTotalDown,0.0,thePandaFlat.puppimetphi_JESTotalDown,0.0);
      }

      double dPhiDiLepMET = TMath::Abs(dilep.DeltaPhi(vMet));
      double ptFrac = TMath::Abs(dilep.Pt()-vMet.Pt())/dilep.Pt();
      double caloMinusPFMETRel = TMath::Abs(thePandaFlat.calomet-thePandaFlat.pfmet)/thePandaFlat.pfmet;
      double dphill = TMath::Abs(vLoose[0].DeltaPhi(vLoose[1]));
      double detall = TMath::Abs(vLoose[0].Eta()-vLoose[1].Eta());
      double drll = sqrt(dphill*dphill+detall*detall);
      double mtW = TMath::Sqrt(2.0*dilep.Pt()*vMet.Pt()*(1.0 - TMath::Cos(dPhiDiLepMET)));

      // Different requirements depending on the DY sample
      bool passDYSampleSel = true;
      if     (whichDY == 1) passDYSampleSel = dilep.Pt() > 60;
      else if(whichDY == 2) passDYSampleSel = thePandaFlat.nJot >= 1;
      if(passDYSampleSel == false) continue;

      bool passSel = ((lepType != 2 && TMath::Abs(dilep.M()-91.1876) < 15) || (lepType == 2 && dilep.M() > 50 && thePandaFlat.jetNBtags > 0)) && vLoose[0].Pt() > 25 && vLoose[1].Pt() > 25;
      if(isTopSel == true) passSel = (TMath::Abs(dilep.M()-91.1876) > 15 || lepType == 2) && dilep.M() > 50 && vLoose[0].Pt() > 25 && vLoose[1].Pt() > 25 && mtW > 50 && thePandaFlat.nJot >= 1;
      if(passSel == false) continue;

      double totalWeight = 1.0; double sfWS = 1.0; double puWeight = 1.0; double npvWeight = 1.0;
      if     (theCategory != kPlotData){
        double triggerWeights[2];
        trigger_sf(triggerWeights, trgEff, trgEffE, lepType, looseLepPt[0], TMath::Abs(looseLepEta[0]), looseLepPt[1], TMath::Abs(looseLepEta[1]));

        puWeight  = nPUScaleFactor(fhDPU,  thePandaFlat.pu);
        npvWeight = nPUScaleFactor(fhDNPV, thePandaFlat.npv);

        totalWeight = thePandaFlat.normalizedWeight * lumi * puWeight * thePandaFlat.sf_l1Prefire * looseLepSF[0] * looseLepSF[1] * triggerWeights[0] * npvWeight;
        //totalWeight = thePandaFlat.normalizedWeight * lumi * puWeight * thePandaFlat.sf_l1Prefire * looseLepSF[0] * looseLepSF[1] * triggerWeights[0];

        bool isRS = thePandaFlat.looseGenLep1PdgId > 0 && thePandaFlat.looseGenLep2PdgId > 0;
        if(thePandaFlat.nLooseLep >= 3) isRS = isRS && thePandaFlat.looseGenLep3PdgId > 0;
        if(thePandaFlat.nLooseLep >= 4) isRS = isRS && thePandaFlat.looseGenLep4PdgId > 0;
	if(!isRS && theCategory != kPlotVG) {
	  //theCategory = kPlotWS; // do not change the category for these studies
	  int theWSLepton = -1;
	  if     (thePandaFlat.nLooseLep >= 2 && abs(looseLepPdgId[0]) == 11 && thePandaFlat.looseGenLep1PdgId < 0) theWSLepton = 0;
	  else if(thePandaFlat.nLooseLep >= 2 && abs(looseLepPdgId[1]) == 11 && thePandaFlat.looseGenLep2PdgId < 0) theWSLepton = 1;
	  else if(thePandaFlat.nLooseLep >= 3 && abs(looseLepPdgId[2]) == 11 && thePandaFlat.looseGenLep3PdgId < 0) theWSLepton = 2;
	  else if(thePandaFlat.nLooseLep >= 4 && abs(looseLepPdgId[3]) == 11 && thePandaFlat.looseGenLep4PdgId < 0) theWSLepton = 3;
          if(theWSLepton >= 0){
	    int nEta;
            if     (TMath::Abs(looseLepEta[theWSLepton]) < 0.5) nEta = 0;
            else if(TMath::Abs(looseLepEta[theWSLepton]) < 1.0) nEta = 1;
            else if(TMath::Abs(looseLepEta[theWSLepton]) < 1.5) nEta = 2;
            else if(TMath::Abs(looseLepEta[theWSLepton]) < 2.0) nEta = 3;
            else                                                nEta = 4;
	    sfWS = WSSF[nEta];
	  }
	}
      }

      bool passSSWWLepId = false;
      if     (year == 2016) {
        passSSWWLepId = (looseLepSelBit[0] & kFake) == kFake && (looseLepSelBit[0] & kEleMvaWP80) == kEleMvaWP80 && looseLepTripleCharge[0] == 1 &&
         	        (looseLepSelBit[1] & kFake) == kFake && (looseLepSelBit[1] & kEleMvaWP80) == kEleMvaWP80 && looseLepTripleCharge[1] == 1;
      }
      else if(year == 2017){
        passSSWWLepId = (looseLepSelBit[0] & kFake) == kFake && (looseLepSelBit[0] & kTight) == kTight && (looseLepSelBit[0] & kDxyz) == kDxyz && looseLepMissingHits[0] == 0 && looseLepTripleCharge[0] == 1 &&
           		(looseLepSelBit[1] & kFake) == kFake && (looseLepSelBit[1] & kTight) == kTight && (looseLepSelBit[1] & kDxyz) == kDxyz && looseLepMissingHits[1] == 0 && looseLepTripleCharge[1] == 1;
      }
      if(passSSWWLepId && lepType == 1) {
        int theWSStudyCategory = 0; double totalWSStudyWeight = totalWeight;
	if     (theCategory == kPlotData) {}
	else if(theCategory == kPlotDY)   {theWSStudyCategory = 1;}
	else                              {totalWSStudyWeight = -1.0 * totalWSStudyWeight;};
	int nEta[2];
	for(int i=0; i<2; i++){
	  if     (TMath::Abs(looseLepEta[i]) < 0.5) nEta[i] = 0;
	  else if(TMath::Abs(looseLepEta[i]) < 1.0) nEta[i] = 1;
	  else if(TMath::Abs(looseLepEta[i]) < 1.5) nEta[i] = 2;
	  else if(TMath::Abs(looseLepEta[i]) < 2.0) nEta[i] = 3;
	  else                                      nEta[i] = 4;
        }
        if(passSSWWLepId){
	  if(nEta[0] >= nEta[1]) histoWSStudy[nEta[0]][nEta[1]][(qTot!=0)+2*theWSStudyCategory]->Fill(dilep.M(),totalWSStudyWeight);
	  else                   histoWSStudy[nEta[1]][nEta[0]][(qTot!=0)+2*theWSStudyCategory]->Fill(dilep.M(),totalWSStudyWeight);
	}
      }

      if(qTot == 0) histo[lepType+ 0][theCategory]->Fill(dilep.M(),totalWeight);
      else          histo[lepType+ 3][theCategory]->Fill(dilep.M(),totalWeight*sfWS);

      if(qTot == 0) {
	histo[lepType+ 6][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJet,9.4999),totalWeight);
	histo[lepType+ 9][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJot,9.4999),totalWeight);
	histo[lepType+12][theCategory]->Fill(TMath::Min(dilep.Pt(), 999.999),totalWeight);
	histo[lepType+15][theCategory]->Fill(TMath::Min((double)thePandaFlat.pfmet, 499.999),totalWeight);
	histo[lepType+18][theCategory]->Fill(TMath::Min((double)thePandaFlat.puppimet, 499.999),totalWeight);
	histo[lepType+21][theCategory]->Fill(TMath::Min((double)thePandaFlat.calomet, 499.999),totalWeight);
	histo[lepType+24][theCategory]->Fill(TMath::Min((double)thePandaFlat.trkmet, 499.999),totalWeight);
	histo[lepType+27][theCategory]->Fill(TMath::Min(mtW, 499.999),totalWeight);
	histo[lepType+30][theCategory]->Fill(dPhiDiLepMET,totalWeight);
	histo[lepType+33][theCategory]->Fill(dphill,totalWeight);
	histo[lepType+36][theCategory]->Fill(TMath::Min(ptFrac,4.999),totalWeight);
	histo[lepType+39][theCategory]->Fill(TMath::Min(caloMinusPFMETRel,4.999),totalWeight);
	histo[lepType+42][theCategory]->Fill(TMath::Min(detall,4.999),totalWeight);
	histo[lepType+45][theCategory]->Fill(TMath::Min(drll,4.999),totalWeight);
	histo[lepType+48][theCategory]->Fill(TMath::Min((double)thePandaFlat.npv,79.499),totalWeight);
	histo[lepType+51][theCategory]->Fill(looseLepEta[0],totalWeight);
	histo[lepType+54][theCategory]->Fill(looseLepEta[1],totalWeight);
	histo[lepType+57][theCategory]->Fill(TMath::Min((double)looseLepPt[0], 224.999),totalWeight);
	histo[lepType+60][theCategory]->Fill(TMath::Min((double)looseLepPt[1], 224.999),totalWeight);
	histo[lepType+63][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNBtags,4.4999),totalWeight);
	histo[lepType+66][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNMBtags,4.4999),totalWeight);
	if(thePandaFlat.nJot >= 1){
	  histo[lepType+69][theCategory]->Fill(TMath::Min((double)thePandaFlat.jotPt[0],199.9999),totalWeight);
	  histo[lepType+72][theCategory]->Fill(TMath::Max(TMath::Min((double)thePandaFlat.jotCSV[0],0.999),0.001),totalWeight);
	  histo[lepType+75][theCategory]->Fill(thePandaFlat.jotEta[0],totalWeight);	
	}
      }

      const int nLepSel = 16+1;
      for(int ilep=0; ilep<thePandaFlat.nLooseLep; ilep++){
        bool passLepSel[nLepSel] = {
              (looseLepSelBit[ilep] & kFake) == kFake, 
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kMedium) == kMedium,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kTight) == kTight,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kTight) == kTight && (looseLepSelBit[ilep] & kDxyz) == kDxyz,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kTight) == kTight && (looseLepSelBit[ilep] & kDxyz) == kDxyz && looseLepMissingHits[ilep] == 0,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kTight) == kTight && (looseLepSelBit[ilep] & kDxyz) == kDxyz && looseLepMissingHits[ilep] == 0 && looseLepTripleCharge[ilep] == 1,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kEleMvaWP90) == kEleMvaWP90,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kEleMvaWP80) == kEleMvaWP80,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kEleMvaWP80) == kEleMvaWP80 && looseLepTripleCharge[ilep] == 1,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kMvaMedium) == kMvaMedium,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kMvaTight) == kMvaTight,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kMiniIsoMedium) == kMiniIsoMedium,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kMiniIsoTight) == kMiniIsoTight,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kMvaMedium) == kMvaMedium && (looseLepSelBit[ilep] & kMiniIsoMedium) == kMiniIsoMedium,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kMvaTight) == kMvaTight && (looseLepSelBit[ilep] & kMiniIsoTight) == kMiniIsoTight,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kMvaMedium) == kMvaMedium && (looseLepSelBit[ilep] & kMiniIsoMedium) == kMiniIsoMedium && (looseLepSelBit[ilep] & kDxyz) == kDxyz,
	      (looseLepSelBit[ilep] & kFake) == kFake && (looseLepSelBit[ilep] & kMvaTight) == kMvaTight && (looseLepSelBit[ilep] & kMiniIsoTight) == kMiniIsoTight && (looseLepSelBit[ilep] & kDxyz) == kDxyz  	      
	     };

        if(qTot == 0 && lepType != 2) { // only for opposite-sign mm/ee events
          for(int nsel=0; nsel<nLepSel; nsel++){
	    if(passLepSel[nsel]) histoEffStudy[lepType+2*(TMath::Abs(looseLepEta[ilep]) > 1.475)+4*(looseLepPt[ilep] < 40)][theCategory]->Fill((double)nsel,totalWeight);
	    if(passLepSel[nsel]) histoPtEffStudy[lepType+2*(TMath::Abs(looseLepEta[ilep]) > 1.475)][nsel][theCategory]->Fill(TMath::Min((double)looseLepPt[ilep], 124.999),totalWeight);
          }
	}
        if(ilep == 1 && lepType == 0 && qTot != 0) { // only for same-sign mm events
          for(int nsel=0; nsel<nLepSel; nsel++){
	    if(passLepSel[nsel]) histoFakeStudy[0+2*(TMath::Abs(looseLepEta[ilep]) > 1.475)+4*(looseLepPt[ilep] < 40)][theCategory]->Fill((double)nsel,totalWeight);
          }
	}
        if(ilep == 1 && lepType == 2 && qTot != 0 && dilep.M() > 100 && dilep.M() < 200 && abs(looseLepPdgId[ilep]) == 11) { // only for same-sign em events with 100 < mll < 200
          for(int nsel=0; nsel<nLepSel; nsel++){
	    if(passLepSel[nsel]) histoFakeStudy[1+2*(TMath::Abs(looseLepEta[ilep]) > 1.475)+4*(looseLepPt[ilep] < 40)][theCategory]->Fill((double)nsel,totalWeight);
          }
	}
      }

    } // end event loop
  } // end samples loop

  TString addSuffix = "";
  if(isTopSel == true) addSuffix = "_topsel";
  char output[200];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    sprintf(output,"histoDY%dzll_%d_%d%s.root",whichDY,year,thePlot,addSuffix.Data());	
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    double totBck = 0;
    for(int i=1; i<nPlotCategories; i++) totBck =totBck + histo[thePlot][i]->GetSumOfWeights();
    printf("(%d) %f (%f+%f+%f+%f+%f+%f+%f+%f)=%f\n",thePlot,histo[thePlot][0]->GetSumOfWeights(),
    histo[thePlot][1]->GetSumOfWeights(),histo[thePlot][2]->GetSumOfWeights(),
    histo[thePlot][3]->GetSumOfWeights(),histo[thePlot][4]->GetSumOfWeights(),
    histo[thePlot][5]->GetSumOfWeights(),histo[thePlot][6]->GetSumOfWeights(),
    histo[thePlot][6]->GetSumOfWeights(),histo[thePlot][8]->GetSumOfWeights(),
    totBck);
    for(int np=0; np<nPlotCategories; np++) histo[thePlot][np]->Write();
    outFilePlotsNote->Close();
  }

  { // Lepton efficiency study
    printf("---------------Lepton Efficiency Study---------------\n");
    for(int np=0; np<8; np++){
      sprintf(output,"histoDY%dEffStudy_%d%s_%d.root",whichDY,year,addSuffix.Data(),np);	
      TFile* outFilePlotsNote = new TFile(output,"recreate");
      for(int nc=0; nc<nPlotCategories; nc++) histoEffStudy[np][nc]->Write();
      outFilePlotsNote->Close();
      printf("Region: %d DA ",np);
      for(int i=2; i<=histoEffStudy[np][kPlotData]->GetNbinsX(); i++){
        printf("%.3f ",histoEffStudy[np][kPlotData]->GetBinContent(i)/histoEffStudy[np][kPlotData]->GetBinContent(1));
      }
      printf("\n");
      printf("Region: %d MC ",np);
      for(int i=2; i<=histoEffStudy[np][kPlotDY]->GetNbinsX(); i++){
        printf("%.3f ",histoEffStudy[np][kPlotDY]->GetBinContent(i)/histoEffStudy[np][kPlotDY]->GetBinContent(1));
      }
      printf("\n");
    }

    for(int np=0; np<4; np++){
      for(int nsel=0; nsel<17; nsel++){
        sprintf(output,"histoDY%dPtEffStudysel%d_%d%s_%d.root",whichDY,nsel,year,addSuffix.Data(),np);	
        TFile* outFilePlotsNote = new TFile(output,"recreate");
        for(int nc=0; nc<nPlotCategories; nc++) histoPtEffStudy[np][nsel][nc]->Write();
        outFilePlotsNote->Close();
      }
    }

  }

  { // Lepton Fake study
    printf("---------------Lepton Fake Study---------------\n");
    for(int np=0; np<8; np++){
      sprintf(output,"histoDY%dFakeStudy_%d%s_%d.root",whichDY,year,addSuffix.Data(),np);	
      TFile* outFilePlotsNote = new TFile(output,"recreate");
      for(int nc=0; nc<nPlotCategories; nc++) histoFakeStudy[np][nc]->Write();
      outFilePlotsNote->Close();
      printf("Region: %d ",np);
      double theDataDen = histoFakeStudy[np][kPlotData]->GetBinContent(1);
      double sumBckDen = 0;
      for(int nc=0; nc<nPlotCategories; nc++) {if(nc!=kPlotData) sumBckDen = sumBckDen + histoFakeStudy[np][nc]->GetBinContent(1);}
      for(int i=2; i<=histoFakeStudy[np][kPlotData]->GetNbinsX(); i++){
        double theDataNum = histoFakeStudy[np][kPlotData]->GetBinContent(i);
	double sumBckNum  = 0.0;
	for(int nc=0; nc<nPlotCategories; nc++) {if(nc!=kPlotData) sumBckNum = sumBckNum + histoFakeStudy[np][nc]->GetBinContent(i);}
        printf("%.3f ",(theDataNum-sumBckNum)/(theDataDen-sumBckDen));
      }
      printf("\n");
    }
  }

  { // Wrong Sign study
    printf("---------------Wrong Sign Study---------------\n");
    for(int i=0; i<5; i++){
      for(int j=0; j<5; j++){
        if(j>i) continue;
        double eff[2]  = {histoWSStudy[i][j][1]->GetSumOfWeights()/histoWSStudy[i][j][0]->GetSumOfWeights(),
	                  histoWSStudy[i][j][3]->GetSumOfWeights()/histoWSStudy[i][j][2]->GetSumOfWeights()
			 };
        double effE[2] = {sqrt((1-eff[0])*eff[0]/histoWSStudy[i][j][0]->GetSumOfWeights()),
	                  sqrt((1-eff[1])*eff[1]/histoWSStudy[i][j][2]->GetSumOfWeights())
			 };
        printf("(%d,%d): %.7f+/-%.7f/%.7f+/-%.7f = %.7f+/-%.7f\n",i,j,eff[0],effE[0],eff[1],effE[1],eff[0]/eff[1],eff[0]/eff[1]*sqrt(effE[0]/eff[0]*effE[0]/eff[0]+effE[1]/eff[1]*effE[1]/eff[1]));
      }
    }
    
    sprintf(output,"histoDY%dWSStudy_%d%s.root",whichDY,year,addSuffix.Data());	
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    for(int i=0; i<5; i++){
      for(int j=0; j<5; j++){
        if(j>i) continue;
        for(int np=0; np<4; np++){
          histoWSStudy[i][j][np]->Write();
        }
      }
    }
    outFilePlotsNote->Close();
  }

}
