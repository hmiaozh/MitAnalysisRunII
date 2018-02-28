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
const int debug = 0;

void wwssAnalysis(
unsigned int period = 0
){

  double lumi = 35.9;
  if     (period == 1) lumi = 19.3;
  else if(period == 2) lumi = 16.6;
  //*******************************************************
  //Input Files
  //*******************************************************
  TString filesPath    = "/data/t3home000/ceballos/panda/v_002_0/";
  vector<TString> infileName_;
  vector<int> infileCat_;

  infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	       infileCat_.push_back(0);

  infileName_.push_back(Form("%sWpWp_EWK.root" ,filesPath.Data())); 	       infileCat_.push_back(1);

  infileName_.push_back(Form("%sWpWp_QCD.root" ,filesPath.Data())); 	       infileCat_.push_back(2);

  infileName_.push_back(Form("%sWZ.root" ,filesPath.Data()));		       infileCat_.push_back(3);
  infileName_.push_back(Form("%sWGstar.root" ,filesPath.Data()));	       infileCat_.push_back(3);

  infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	       infileCat_.push_back(4);
  infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	       infileCat_.push_back(4);

  infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	       infileCat_.push_back(5);
  infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	       infileCat_.push_back(5);

  infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data()));		       infileCat_.push_back(6);
  infileName_.push_back(Form("%sggWW.root" ,filesPath.Data()));		       infileCat_.push_back(6);
  infileName_.push_back(Form("%sTT.root" ,filesPath.Data()));		       infileCat_.push_back(6);
  infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		       infileCat_.push_back(6);
  infileName_.push_back(Form("%sDYNJetsToLL.root" ,filesPath.Data()));         infileCat_.push_back(6);
  infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	       infileCat_.push_back(6);

  infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));		       infileCat_.push_back(7);

  infileName_.push_back(Form("%sWWdps.root" ,filesPath.Data())); 	       infileCat_.push_back(8);

  TString puPath = "MitAnalysisRunII/data/80x/puWeights_80x_37ifb.root";
  TFile *fPUFile = TFile::Open(Form("%s",puPath.Data()));
  TH1D *fhDPU     = (TH1D*)(fPUFile->Get("puWeights"));     assert(fhDPU);     fhDPU    ->SetDirectory(0);
  TH1D *fhDPUUp   = (TH1D*)(fPUFile->Get("puWeightsUp"));   assert(fhDPUUp);   fhDPUUp  ->SetDirectory(0);
  TH1D *fhDPUDown = (TH1D*)(fPUFile->Get("puWeightsDown")); assert(fhDPUDown); fhDPUDown->SetDirectory(0);
  delete fPUFile;

  TFile *fLepton_Fakes = TFile::Open(Form("MitAnalysisRunII/data/80x/histoFakeEtaPt_80x_37ifb.root"));
  TH2D* histoFakeEffSelMediumEtaPt_m = (TH2D*)fLepton_Fakes->Get("histoFakeEffSel0EtaPt_0"); histoFakeEffSelMediumEtaPt_m->SetDirectory(0);
  TH2D* histoFakeEffSelMediumEtaPt_e = (TH2D*)fLepton_Fakes->Get("histoFakeEffSel0EtaPt_1"); histoFakeEffSelMediumEtaPt_e->SetDirectory(0);
  TH2D* histoFakeEffSelTightEtaPt_m  = (TH2D*)fLepton_Fakes->Get("histoFakeEffSel4EtaPt_0"); histoFakeEffSelTightEtaPt_m ->SetDirectory(0);
  TH2D* histoFakeEffSelTightEtaPt_e  = (TH2D*)fLepton_Fakes->Get("histoFakeEffSel4EtaPt_1"); histoFakeEffSelTightEtaPt_e ->SetDirectory(0);
  fLepton_Fakes->Close();

/*
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
*/

  TFile *fTrackElectronReco_SF = TFile::Open(Form("MitAnalysisRunII/data/80x/scalefactors_80x_egpog_37ifb.root"));
  TH2D *fhDeltrksf= (TH2D*)(fTrackElectronReco_SF->Get("scalefactors_Reco_Electron")); assert(fhDeltrksf); fhDeltrksf->SetDirectory(0);
  delete fTrackElectronReco_SF;

  TFile *fElSF = TFile::Open(Form("MitAnalysisRunII/data/80x/scalefactors_80x_egpog_37ifb.root"));
  TH2D *fhDElMediumSF = (TH2D*)(fElSF->Get("scalefactors_Medium_Electron"));
  TH2D *fhDElTightSF = (TH2D*)(fElSF->Get("scalefactors_Tight_Electron"));
  assert(fhDElMediumSF);
  assert(fhDElTightSF);
  fhDElMediumSF->SetDirectory(0);
  fhDElTightSF->SetDirectory(0);
  delete fElSF;

  TFile *fElVeryTightSF = TFile::Open(Form("MitAnalysisRunII/data/80x/veryTightSF_37ifb.root"));
  TH1D *fhDVeryTightSF = (TH1D*)(fElVeryTightSF->Get("veryTightSF"));
  assert(fhDVeryTightSF);
  fhDVeryTightSF->SetDirectory(0);
  delete fElVeryTightSF;

  TFile *fTrackMuonReco_SF = TFile::Open(Form("MitAnalysisRunII/data/80x/Tracking_EfficienciesAndSF_BCDEFGH.root"));
  TH1D *fhDmutrksfptg10 = (TH1D*)(fTrackMuonReco_SF->Get("ratio_eff_eta3_dr030e030_corr")); assert(fhDmutrksfptg10); fhDmutrksfptg10->SetDirectory(0);
  delete fTrackMuonReco_SF;

  TFile *fMuSF = TFile::Open(Form("MitAnalysisRunII/data/80x/muon_scalefactors_37ifb.root"));
  TH2D *fhDMuMediumSF = (TH2D*)(fMuSF->Get("scalefactors_TightId_Muon")); assert(fhDMuMediumSF); fhDMuMediumSF->SetDirectory(0);
  delete fMuSF;

  TFile *fMuIsoSF = TFile::Open(Form("MitAnalysisRunII/data/80x/muon_scalefactors_37ifb.root"));
  TH2D *fhDMuIsoSF = (TH2D*)(fMuIsoSF->Get("scalefactors_Iso_MuonTightId")); assert(fhDMuIsoSF); fhDMuIsoSF->SetDirectory(0);
  delete fMuIsoSF;

/*
  double getMaxPtForSFs[2] = {scalefactors_Medium_Muon                  ->GetYaxis()->GetBinCenter(scalefactors_Medium_Muon		     ->GetNbinsY()),
                              scalefactors_Medium_Electron              ->GetYaxis()->GetBinCenter(scalefactors_Medium_Electron		     ->GetNbinsY())
		              };
*/

  const int nBinMVA = 4; Float_t xbins[nBinMVA+1] = {500, 800, 1100, 1500, 2000};
  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 37;
  const int histBins = 10;
  TH1D* histo[allPlots][histBins];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    if     (thePlot >=   0 && thePlot <=   5) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >=   6 && thePlot <=   8) {nBinPlot =   5; xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >=   9 && thePlot <=  11) {nBinPlot =  80; xminPlot =  0.0; xmaxPlot = 8.0;}
    else if(thePlot >=  12 && thePlot <=  14) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot =2000;}
    else if(thePlot >=  15 && thePlot <=  17) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 1.0;}
    else if(thePlot >=  15 && thePlot <=  23) {nBinPlot =   5; xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >=  24 && thePlot <=  29) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    TH1D* histos;
    if(thePlot >=  30 && thePlot <=  36) histos = new TH1D("histos", "histos", nBinMVA, xbins);
    else                                 histos = new TH1D("histos", "histos", nBinPlot, xminPlot, xmaxPlot);
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

    if(debug != 0 && infileCat_[ifile] != 0) return;
    
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

/*
      bool thePass = 
thePandaFlat.eventNumber==1025531578||
thePandaFlat.eventNumber==1106346517||
thePandaFlat.eventNumber==1107000932||
thePandaFlat.eventNumber==1120935894||
thePandaFlat.eventNumber==1362462045||
thePandaFlat.eventNumber==1477447549||
thePandaFlat.eventNumber==14922993||
thePandaFlat.eventNumber==156554433||
thePandaFlat.eventNumber==168600482||
thePandaFlat.eventNumber==171252139||
thePandaFlat.eventNumber==194278287||
thePandaFlat.eventNumber==201072338||
thePandaFlat.eventNumber==220352201||
thePandaFlat.eventNumber==2378805578||
thePandaFlat.eventNumber==2430712569||
thePandaFlat.eventNumber==2483823317||
thePandaFlat.eventNumber==2525037200||
thePandaFlat.eventNumber==255112868||
thePandaFlat.eventNumber==256349102||
thePandaFlat.eventNumber==257610842||
thePandaFlat.eventNumber==270384226||
thePandaFlat.eventNumber==275980633||
thePandaFlat.eventNumber==3181264902||
thePandaFlat.eventNumber==330584857||
thePandaFlat.eventNumber==331539711||
thePandaFlat.eventNumber==341944318||
thePandaFlat.eventNumber==3426009362||
thePandaFlat.eventNumber==37040930||
thePandaFlat.eventNumber==387590979||
thePandaFlat.eventNumber==391681141||
thePandaFlat.eventNumber==395496974||
thePandaFlat.eventNumber==409879368||
thePandaFlat.eventNumber==412643666||
thePandaFlat.eventNumber==4762850171||
thePandaFlat.eventNumber==484129863||
thePandaFlat.eventNumber==522190092||
thePandaFlat.eventNumber==564507384||
thePandaFlat.eventNumber==691413995||
thePandaFlat.eventNumber==750424129||
thePandaFlat.eventNumber==766727802||
thePandaFlat.eventNumber==802191129||
thePandaFlat.eventNumber==838885397||
thePandaFlat.eventNumber==899428150||
thePandaFlat.eventNumber==913523305;
      if(debug == 2 && thePass == false) continue;
*/
      if(debug == 2) printf("STEP1 %llu\n",thePandaFlat.eventNumber);

      if(infileCat_[ifile] == 0 && ((period == 1 && thePandaFlat.runNumber > 278802) || (period == 2 && thePandaFlat.runNumber <= 278802))) continue;

      bool passTrigger = (thePandaFlat.trigger & (1<<kEMuTrig)) != 0       || (thePandaFlat.trigger & (1<<kDoubleMuTrig)) != 0  ||
                         (thePandaFlat.trigger & (1<<kSingleMuTrig)) != 0  || (thePandaFlat.trigger & (1<<kDoubleEleTrig)) != 0 ||
                         (thePandaFlat.trigger & (1<<kSingleEleTrig)) != 0;
      if(passTrigger == false) continue;
      if(debug == 2) printf("STEP2 %llu\n",thePandaFlat.eventNumber);

      if(thePandaFlat.nLooseLep < 2 || thePandaFlat.nLooseLep > 3) continue;
      if(debug == 2) printf("STEP3 %llu\n",thePandaFlat.eventNumber);

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

      if(!(ptSelCuts[0] >= 1 && ptSelCuts[1] >= 2 && ptSelCuts[2] >= thePandaFlat.nLooseLep)) continue;

      int theCategory = infileCat_[ifile];
      bool isNotMCFake = thePandaFlat.looseGenLep1PdgId != 0 && thePandaFlat.looseGenLep2PdgId != 0;
      if(thePandaFlat.nLooseLep >= 3) isNotMCFake = isNotMCFake && thePandaFlat.looseGenLep3PdgId != 0;
      if(thePandaFlat.nLooseLep >= 4) isNotMCFake = isNotMCFake && thePandaFlat.looseGenLep4PdgId != 0;
      if(theCategory != 0 && theCategory != 7 && isNotMCFake == false && usePureMC == false) continue;

      vector<TLorentzVector> vLoose;
      vector<int> idLep;
      bool passLooseLepId = true;
      int qTot = 0;
      unsigned int countLeptonTight = 0;
      for(int i=0; i<thePandaFlat.nLooseLep; i++) {
        idLep.push_back(0);
        if((looseLepSelBit[i] & kTight) == kTight && (looseLepSelBit[i] & kDxyz) == kDxyz && looseLepTripleCharge[i] == 1 && looseLepMissingHits[i] == 0) idLep[i] = 1;
	countLeptonTight = countLeptonTight + (idLep[i] > 0);

        double thePDGMass = mass_mu;
        if(abs(looseLepPdgId[i])==11) thePDGMass = mass_el;
	TLorentzVector vLepTemp; vLepTemp.SetPtEtaPhiM(looseLepPt[i],looseLepEta[i],looseLepPhi[i],thePDGMass);
        vLoose.push_back(vLepTemp);

	qTot = qTot + abs(looseLepPdgId[i])/looseLepPdgId[i];

        passLooseLepId = passLooseLepId && ((looseLepSelBit[i] & kFake) == kFake);
      }
      if(debug == 2) printf("STEP4 %llu %d %d %d %zu\n",thePandaFlat.eventNumber,passLooseLepId,qTot,countLeptonTight,idLep.size());
      if(passLooseLepId == false) continue;
      if(usePureMC == true && countLeptonTight != idLep.size()) continue;
      if(debug == 2) printf("STEP5 %llu\n",thePandaFlat.eventNumber);

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

      double mllZ = 10000; double mllmin = 10000;
      TLorentzVector vZ1l1,vZ1l2,vWln;
      int whichWln = -1;
      if     (vLoose.size() == 2){
        vZ1l1  = vLoose[0];
        vZ1l2  = vLoose[1];
	mllZ   = (vLoose[0]+vLoose[1]).M();
	mllmin = (vLoose[0]+vLoose[1]).M();
	whichWln = 2;
      }
      else if(vLoose.size() == 3){
	if(abs(looseLepPdgId[0]) == abs(looseLepPdgId[1]) && looseLepPdgId[0] != looseLepPdgId[1]) {
          if((vLoose[0]+vLoose[1]).M() < mllmin) mllmin = (vLoose[0]+vLoose[1]).M();
          if(fabs((vLoose[0]+vLoose[1]).M()-91.1876) < fabs(mllZ-91.1876)) {
	    mllZ  = (vLoose[0]+vLoose[1]).M();
	    vZ1l1 = vLoose[0];
	    vZ1l2 = vLoose[1];
	    vWln  = vLoose[2];
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
	    whichWln = 0;
	  }
	}
	if(whichWln >= 0) idLep[whichWln] = 2;
      }

      if(whichWln == -1) continue;

      TLorentzVector vJot1; vJot1.SetPtEtaPhiM(thePandaFlat.jot1Pt,thePandaFlat.jot1Eta,thePandaFlat.jot1Phi,0.0);
      TLorentzVector vJot2; vJot2.SetPtEtaPhiM(thePandaFlat.jot2Pt,thePandaFlat.jot2Eta,thePandaFlat.jot2Phi,0.0);

      double deltaEtaJJ = TMath::Abs(vJot1.Eta()-vJot2.Eta());
      bool passDEtaJJ = thePandaFlat.nJot >= 2 && deltaEtaJJ > 2.5;
      bool passMJJ = thePandaFlat.nJot >= 2 && (vJot1+vJot2).M() > 500;

      double theLeptonZ[2];
      theLeptonZ[0] = TMath::Min(TMath::Abs(vZ1l1.Eta()-(vJot1.Eta()+vJot2.Eta())/2.)/deltaEtaJJ,0.999);
      theLeptonZ[1] = TMath::Min(TMath::Abs(vZ1l2.Eta()-(vJot1.Eta()+vJot2.Eta())/2.)/deltaEtaJJ,0.999);
      bool passZMax = thePandaFlat.nJot >= 2 && TMath::Max(theLeptonZ[0],theLeptonZ[1]) < 0.75;

      bool passMLL   = mllZ > 20 && (fabs(mllZ-91.1876) > 15 || lepType != 1);
      bool passMET   = vMET.Pt() > 40;
      bool passNjets = thePandaFlat.nJot >= 2;
      bool passBtagVeto = thePandaFlat.jetNMBtags == 0;
      bool passTauVeto = thePandaFlat.nTau == 0;
      //                                                        0        1        2          3           4        5         6             7            8     
      bool passSel[9] = {qTot != 0 && thePandaFlat.nLooseLep == 2, passMLL, passMET, passNjets, passDEtaJJ, passMJJ, passZMax, passBtagVeto, passTauVeto};

      bool passWWSel = passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[4] && passSel[5] && passSel[6] && passSel[7] && passSel[8];
      bool passWZSel = whichWln >= 0 && thePandaFlat.nLooseLep == 3 && 
                       fabs(mllZ-91.1876) < 15 && mllmin > 4 &&
		       vWln.Pt() > 20 &&
		       passSel[2] && passSel[3] && passSel[4] && passSel[5] && passSel[7] && passSel[8];
      bool passAllButOneSel[8] = {
        passSel[0] &&               passSel[2] && passSel[3] && passSel[4] && passSel[5] && passSel[6] && passSel[7] && passSel[8],
        passSel[0] && passSel[1] &&               passSel[3] && passSel[4] && passSel[5] && passSel[6] && passSel[7] && passSel[8],
	passSel[0] && passSel[1] && passSel[2]&&                                                          passSel[7] && passSel[8],
	passSel[0] && passSel[1] && passSel[2] && passSel[3] &&               passSel[5] && passSel[6] && passSel[7] && passSel[8],
	passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[4] &&               passSel[6] && passSel[7] && passSel[8],
	passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[4] && passSel[5] &&               passSel[7] && passSel[8],
	passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[4] && passSel[5] && passSel[6]               && passSel[8],
	passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[4] && passSel[5] && passSel[6] && passSel[7]
      };

      double totalWeight = 1.0; double puWeight = 1.0; double puWeightUp = 1.0; double puWeightDown = 1.0;
      if(theCategory != 0){
        puWeight     = nPUScaleFactor(fhDPU,    thePandaFlat.pu);
        puWeightUp   = nPUScaleFactor(fhDPUUp,  thePandaFlat.pu);
        puWeightDown = nPUScaleFactor(fhDPUDown,thePandaFlat.pu);
        double the_eta_sf[4] = {1.0, 1.0, 1.0, 1.0};
        double sfWeightLepEff[4] = {1.0, 1.0, 1.0, 1.0};
	for(unsigned int i=0; i<vLoose.size(); i++){
           sfWeightLepEff[i] = effhDScaleFactor(looseLepPt[i],
	        looseLepEta[i],TMath::Abs(looseLepPdgId[i]),
	  	"verytight",fhDMuMediumSF,fhDElMediumSF,fhDElTightSF,fhDmutrksfptg10,fhDeltrksf,thePandaFlat.npv,true,fhDMuIsoSF,fhDVeryTightSF,true);

/*
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
*/
        }

        totalWeight = thePandaFlat.normalizedWeight * lumi * puWeight * 
	  the_eta_sf[0] * the_eta_sf[1] * the_eta_sf[2] * the_eta_sf[3] * 
	  sfWeightLepEff[0] * sfWeightLepEff[1] * sfWeightLepEff[2] * sfWeightLepEff[3] * 
	  thePandaFlat.sf_btag0 * theMCPrescale;

        if     (infileCat_[ifile] == 3)                                                totalWeight = totalWeight * thePandaFlat.sf_wz;
	else if(infileCat_[ifile] == 4 && infileName_[ifile].Contains("qqZZ") == true) totalWeight = totalWeight * thePandaFlat.sf_zz;

        bool isRS = thePandaFlat.looseGenLep1PdgId > 0 && thePandaFlat.looseGenLep2PdgId > 0;
        if(thePandaFlat.nLooseLep >= 3) isRS = isRS && thePandaFlat.looseGenLep3PdgId > 0;
        if(thePandaFlat.nLooseLep >= 4) isRS = isRS && thePandaFlat.looseGenLep4PdgId > 0;
	if(!isRS) theCategory = 6;
      }

      if(usePureMC == false && countLeptonTight != idLep.size()){
        double fakeSF = 1.0;
        for(unsigned int nl=0; nl<idLep.size(); nl++){
          if(idLep[nl] != 0) continue;
          bool applyTight = true;
          if(nl == 0) fakeSF = fakeSF * fakeRateFactor(TMath::Min((double)looseLepPt[0],44.999),TMath::Abs(looseLepEta[0]),TMath::Abs(looseLepPdgId[0]),applyTight,histoFakeEffSelMediumEtaPt_m,histoFakeEffSelMediumEtaPt_e,histoFakeEffSelTightEtaPt_m,histoFakeEffSelTightEtaPt_e);
          if(nl == 1) fakeSF = fakeSF * fakeRateFactor(TMath::Min((double)looseLepPt[1],44.999),TMath::Abs(looseLepEta[1]),TMath::Abs(looseLepPdgId[1]),applyTight,histoFakeEffSelMediumEtaPt_m,histoFakeEffSelMediumEtaPt_e,histoFakeEffSelTightEtaPt_m,histoFakeEffSelTightEtaPt_e);
          if(nl == 2) fakeSF = fakeSF * fakeRateFactor(TMath::Min((double)looseLepPt[2],44.999),TMath::Abs(looseLepEta[2]),TMath::Abs(looseLepPdgId[2]),applyTight,histoFakeEffSelMediumEtaPt_m,histoFakeEffSelMediumEtaPt_e,histoFakeEffSelTightEtaPt_m,histoFakeEffSelTightEtaPt_e);
          if(nl == 3) fakeSF = fakeSF * fakeRateFactor(TMath::Min((double)looseLepPt[3],44.999),TMath::Abs(looseLepEta[3]),TMath::Abs(looseLepPdgId[3]),applyTight,histoFakeEffSelMediumEtaPt_m,histoFakeEffSelMediumEtaPt_e,histoFakeEffSelTightEtaPt_m,histoFakeEffSelTightEtaPt_e);
          theCategory = 9;
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

      if(passAllButOneSel[0])histo[lepType+  0][theCategory]->Fill(TMath::Min(mllZ,199.999),totalWeight);
      if(passAllButOneSel[1])histo[lepType+  3][theCategory]->Fill(TMath::Min(vMET.Pt(),199.999),totalWeight);
      if(passAllButOneSel[2])histo[lepType+  6][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJot,5.499),totalWeight);
      if(passAllButOneSel[3])histo[lepType+  9][theCategory]->Fill(TMath::Min(TMath::Abs(vJot1.Eta()-vJot2.Eta()),7.999),totalWeight);
      if(passAllButOneSel[4])histo[lepType+ 12][theCategory]->Fill(TMath::Min((vJot1+vJot2).M(),1999.999),totalWeight);
      if(passAllButOneSel[5])histo[lepType+ 15][theCategory]->Fill(TMath::Min(TMath::Max(theLeptonZ[0],theLeptonZ[1]),0.999),totalWeight);
      if(passAllButOneSel[6])histo[lepType+ 18][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNBtags,4.499),totalWeight);
      if(passAllButOneSel[7])histo[lepType+ 21][theCategory]->Fill(TMath::Min((double)thePandaFlat.nTau,4.499),totalWeight);
      if(passWWSel)          histo[lepType+ 24][theCategory]->Fill(TMath::Min(vZ1l1.Pt(),199.999),totalWeight);
      if(passWWSel)          histo[lepType+ 27][theCategory]->Fill(TMath::Min(vZ1l2.Pt(),199.999),totalWeight);
      if(passWWSel)          histo[lepType+ 30][theCategory]->Fill(TMath::Min((vJot1+vJot2).M(),1999.999),totalWeight);
      if(passWZSel)          histo[lepType+ 33][theCategory]->Fill(TMath::Min((vJot1+vJot2).M(),1999.999),totalWeight);

      if((theCategory == 0 && passWWSel && debug == 1) || debug == 2){
        printf("DATA %d %d %llu | %d %d | %d -> %d %d %d %d %d %d %d %d %d | %f %f %f %f %f %f %f\n",
	thePandaFlat.runNumber,thePandaFlat.lumiNumber,thePandaFlat.eventNumber,theCategory,lepType,
	passWWSel,passSel[0],passSel[1],passSel[2],passSel[3],passSel[4],passSel[5],passSel[6],passSel[7],passSel[8],
	mllZ,vMET.Pt(),vJot1.Pt(),vJot2.Pt(),TMath::Abs(vJot1.Eta()-vJot2.Eta()),(vJot1+vJot2).M(),TMath::Max(theLeptonZ[0],theLeptonZ[1]));
      }

    } // end events loop
    the_input_file->Close();
  } // end chain loop

  char output[200];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    sprintf(output,"histoWWSS_%d.root",thePlot);	
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
