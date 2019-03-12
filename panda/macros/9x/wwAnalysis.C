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
int year
){
  int nTypeLepSel[2] = {-1, -1};
  int whichYear = -1;
  if     (year == 2016) {whichYear = Y2016; nTypeLepSel[0] =  2; nTypeLepSel[1] = 6;}
  else if(year == 2017) {whichYear = Y2017; nTypeLepSel[0] = 13; nTypeLepSel[1] = 6;}
  else if(year == 2018) {whichYear = Y2018; nTypeLepSel[0] = 15; nTypeLepSel[1] = 6;}
  else {printf("Wrong year (%d)!\n",year); return;}

  //*******************************************************
  //Inputs
  //*******************************************************
  vector<TString> infileName_;
  vector<int> infileCat_;

  TString filesPath;
  TString fLepton_FakesName = Form("MitAnalysisRunII/data/90x/histoFakeEtaPt_%d.root",year);
  TString trgSFPath = Form("MitAnalysisRunII/data/90x/histo_triggerEff_sel0_%d.root",year);
  TString effSFPath = Form("MitAnalysisRunII/data/90x/histoDY0EffSFStudy_%d.root",year);
  if(year == 2018) {
    filesPath = "/data/t3home000/ceballos/panda/v_006_0/";

    infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	         infileCat_.push_back(kPlotData);
    infileName_.push_back(Form("%sWWinc.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotqqWW);
    //infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotqqWW);
    //infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotggWW);
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));                infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		         infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_M-50_LO.root",filesPath.Data()));   infileCat_.push_back(kPlotDY);
    //infileName_.push_back(Form("%sWZno3l.root" ,filesPath.Data()));	         infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sWZ3l_powheg.root" ,filesPath.Data()));         infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTVV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));		         infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotHiggs);
  }
  else if(year == 2017) {
    filesPath = "/data/t3home000/ceballos/panda/v_004_0/";

    infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	         infileCat_.push_back(kPlotData);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotqqWW);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotggWW);
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));                infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		         infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_M-50_LO.root",filesPath.Data()));   infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sWZno3l.root" ,filesPath.Data()));	         infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sWZ3l_powheg_mll1.root" ,filesPath.Data()));    infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTVV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));		         infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotHiggs);
  }
  else if(year == 2016) {
    filesPath = "/data/t3home000/ceballos/panda/v_002_0/";

    infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	          infileCat_.push_back(kPlotData);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotqqWW);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotggWW);
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));                 infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		          infileCat_.push_back(kPlotTop);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data()));  infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt0To50.root",filesPath.Data()));    infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt50To100.root",filesPath.Data()));  infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt100To250.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt250To400.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt400To650.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt650ToInf.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sWZ.root" ,filesPath.Data()));	                  infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sWGstar.root" ,filesPath.Data()));               infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));		          infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotHiggs);
  }
  else {
    return;
  }

  TFile *fLepton_Fakes = TFile::Open(fLepton_FakesName.Data());
  TH2D* histoFakeEffSelMediumEtaPt_m = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_2_0"); histoFakeEffSelMediumEtaPt_m->SetDirectory(0);
  TH2D* histoFakeEffSelMediumEtaPt_e = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_0_1"); histoFakeEffSelMediumEtaPt_e->SetDirectory(0);
  TH2D* histoFakeEffSelTightEtaPt_m  = (TH2D*)fLepton_Fakes->Get(Form("histoFakeEffSelEtaPt_%d_0",nTypeLepSel[0])); histoFakeEffSelTightEtaPt_m ->SetDirectory(0);	
  TH2D* histoFakeEffSelTightEtaPt_e  = (TH2D*)fLepton_Fakes->Get(Form("histoFakeEffSelEtaPt_%d_1",nTypeLepSel[1])); histoFakeEffSelTightEtaPt_e ->SetDirectory(0);
  fLepton_Fakes->Close();

  TFile *fLepton_Eff = TFile::Open(effSFPath.Data());
  TH2D* histoLepEffSelMediumEtaPt_m = (TH2D*)fLepton_Eff->Get("histoEffSFStudy_2_0"); histoLepEffSelMediumEtaPt_m->SetDirectory(0);
  TH2D* histoLepEffSelMediumEtaPt_e = (TH2D*)fLepton_Eff->Get("histoEffSFStudy_0_1"); histoLepEffSelMediumEtaPt_e->SetDirectory(0);
  TH2D* histoLepEffSelTightEtaPt_m  = (TH2D*)fLepton_Eff->Get(Form("histoEffSFStudy_%d_0",nTypeLepSel[0])); histoLepEffSelTightEtaPt_m ->SetDirectory(0);   
  TH2D* histoLepEffSelTightEtaPt_e  = (TH2D*)fLepton_Eff->Get(Form("histoEffSFStudy_%d_1",nTypeLepSel[1])); histoLepEffSelTightEtaPt_e ->SetDirectory(0);
  fLepton_Eff->Close();

  TFile *ftrgSF = TFile::Open(trgSFPath.Data());
  TH2D *trgSFMMBB = (TH2D*)(ftrgSF->Get("trgSFMMBB")); assert(trgSFMMBB); trgSFMMBB->SetDirectory(0);
  TH2D *trgSFMMEB = (TH2D*)(ftrgSF->Get("trgSFMMEB")); assert(trgSFMMEB); trgSFMMEB->SetDirectory(0);
  TH2D *trgSFMMBE = (TH2D*)(ftrgSF->Get("trgSFMMBE")); assert(trgSFMMBE); trgSFMMBE->SetDirectory(0);
  TH2D *trgSFMMEE = (TH2D*)(ftrgSF->Get("trgSFMMEE")); assert(trgSFMMEE); trgSFMMEE->SetDirectory(0);
  TH2D *trgSFEEBB = (TH2D*)(ftrgSF->Get("trgSFEEBB")); assert(trgSFEEBB); trgSFEEBB->SetDirectory(0);
  TH2D *trgSFEEEB = (TH2D*)(ftrgSF->Get("trgSFEEEB")); assert(trgSFEEEB); trgSFEEEB->SetDirectory(0);
  TH2D *trgSFEEBE = (TH2D*)(ftrgSF->Get("trgSFEEBE")); assert(trgSFEEBE); trgSFEEBE->SetDirectory(0);
  TH2D *trgSFEEEE = (TH2D*)(ftrgSF->Get("trgSFEEEE")); assert(trgSFEEEE); trgSFEEEE->SetDirectory(0);
  TH2D *trgSFMEBB = (TH2D*)(ftrgSF->Get("trgSFMEBB")); assert(trgSFMEBB); trgSFMEBB->SetDirectory(0);
  TH2D *trgSFMEEB = (TH2D*)(ftrgSF->Get("trgSFMEEB")); assert(trgSFMEEB); trgSFMEEB->SetDirectory(0);
  TH2D *trgSFMEBE = (TH2D*)(ftrgSF->Get("trgSFMEBE")); assert(trgSFMEBE); trgSFMEBE->SetDirectory(0);
  TH2D *trgSFMEEE = (TH2D*)(ftrgSF->Get("trgSFMEEE")); assert(trgSFMEEE); trgSFMEEE->SetDirectory(0);
  TH2D *trgSFEMBB = (TH2D*)(ftrgSF->Get("trgSFEMBB")); assert(trgSFEMBB); trgSFEMBB->SetDirectory(0);
  TH2D *trgSFEMEB = (TH2D*)(ftrgSF->Get("trgSFEMEB")); assert(trgSFEMEB); trgSFEMEB->SetDirectory(0);
  TH2D *trgSFEMBE = (TH2D*)(ftrgSF->Get("trgSFEMBE")); assert(trgSFEMBE); trgSFEMBE->SetDirectory(0);
  TH2D *trgSFEMEE = (TH2D*)(ftrgSF->Get("trgSFEMEE")); assert(trgSFEMEE); trgSFEMEE->SetDirectory(0);
  delete ftrgSF;

  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 162;
  TH1D* histo[allPlots][nPlotCategories];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    if     (thePlot >=   0 && thePlot <=  44) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >=  45 && thePlot <=  53) {nBinPlot =   5; xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >=  54 && thePlot <=  80) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >=  81 && thePlot <=  89) {nBinPlot =  90; xminPlot =  0.0; xmaxPlot = 180;}
    else if(thePlot >=  90 && thePlot <= 116) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >= 117 && thePlot <= 125) {nBinPlot =  90; xminPlot =  0.0; xmaxPlot = 180;}
    else if(thePlot >= 126 && thePlot <= 152) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >= 153 && thePlot <= 162) {nBinPlot =  90; xminPlot =  0.0; xmaxPlot = 180;}
    for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinPlot, xminPlot, xmaxPlot);
  }

  //*******************************************************
  // Chain Loop
  //*******************************************************
  for(UInt_t ifile=0; ifile<infileName_.size(); ifile++) {
    printf("sampleNames(%d): %s\n",ifile,infileName_[ifile].Data());
    TFile *the_input_file = TFile::Open(infileName_[ifile].Data());
    TTree *the_input_tree = (TTree*)the_input_file->FindObjectAny("events");
    
    pandaFlat thePandaFlat(the_input_tree);
    double theMCPrescale = 1.0; if(infileCat_[ifile] != kPlotData) theMCPrescale = mcPrescale;
    Long64_t nentries = thePandaFlat.fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = thePandaFlat.LoadTree(jentry);
      if (ientry < 0) break;
      nb = thePandaFlat.fChain->GetEntry(jentry);   nbytes += nb;
      if (jentry%1000000 == 0) printf("--- reading event %8lld (%8lld) of %8lld\n",jentry,ientry,nentries);
      if (infileCat_[ifile] != kPlotData && jentry%(int)theMCPrescale != 0) continue;

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

      if(!(ptSelCuts[0] >= 1 && ptSelCuts[1] >= 2 && ptSelCuts[2] >= thePandaFlat.nLooseLep)) continue;

      int theCategory = infileCat_[ifile];
      bool isNotMCFake = thePandaFlat.looseGenLep1PdgId != 0 && thePandaFlat.looseGenLep2PdgId != 0;
      if(theCategory != kPlotData && theCategory != kPlotVG && isNotMCFake == false && usePureMC == false) continue;

      vector<TLorentzVector> vLoose;
      vector<int> idLep;
      bool passLooseLepId = true;
      int qTot = 0;
      unsigned int countLeptonTight = 0;
      for(int i=0; i<thePandaFlat.nLooseLep; i++) {
        idLep.push_back(0);
        //if((looseLepSelBit[i] & kTight) == kTight && (looseLepSelBit[i] & kDxyz) == kDxyz && looseLepMissingHits[i] == 0) idLep[i] = 1;
        if(abs(looseLepPdgId[i])==13) {
	  if     (year == 2016 && (looseLepSelBit[i] & kTight) == kTight && (looseLepSelBit[i] & kDxyz) == kDxyz) idLep[i] = 1;
	  else if(year == 2017 && (looseLepSelBit[i] & kMvaTight) == kMvaTight && (looseLepSelBit[i] & kMiniIsoTight) == kMiniIsoTight) idLep[i] = 1;
	  else if(year == 2018 && (looseLepSelBit[i] & kTight) == kTight && (looseLepSelBit[i] & kDxyz) == kDxyz && (looseLepSelBit[i] & kMiniIsoTight) == kMiniIsoTight) idLep[i] = 1;
	}
	else {
          if((looseLepSelBit[i] & kEleMvaWP80) == kEleMvaWP80) idLep[i] = 1;
	}
	countLeptonTight = countLeptonTight + (idLep[i] > 0);
        double thePDGMass = mass_mu;
        if(abs(looseLepPdgId[i])==11) thePDGMass = mass_el;
	TLorentzVector vLepTemp; vLepTemp.SetPtEtaPhiM(looseLepPt[i],looseLepEta[i],looseLepPhi[i],thePDGMass);
        vLoose.push_back(vLepTemp);

	qTot = qTot + abs(looseLepPdgId[i])/looseLepPdgId[i];

        passLooseLepId = passLooseLepId && ((looseLepSelBit[i] & kFake) == kFake);
      }

      if(passLooseLepId == false) continue;

      int lepType = -1;
      if     (abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13) lepType = 0;
      else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11) lepType = 1;
      else  lepType = 2;

      TLorentzVector vMet,vTrkMet,vMetUp,vMetDown;
      vTrkMet.SetPtEtaPhiM(thePandaFlat.trkmet,0.0,thePandaFlat.trkmetphi,0.0);
      if     (year == 2016 || year == 2018) {
        vMet    .SetPtEtaPhiM(thePandaFlat.pfmet,0.0,thePandaFlat.pfmetphi,0.0);
        vMetUp  .SetPtEtaPhiM(thePandaFlat.pfmet_JESTotalUp  ,0.0,thePandaFlat.pfmetphi_JESTotalUp  ,0.0);
        vMetDown.SetPtEtaPhiM(thePandaFlat.pfmet_JESTotalDown,0.0,thePandaFlat.pfmetphi_JESTotalDown,0.0);
      } 
      else if(year == 2017){
        vMet    .SetPtEtaPhiM(thePandaFlat.puppimet,0.0,thePandaFlat.puppimetphi,0.0);
        vMetUp  .SetPtEtaPhiM(thePandaFlat.puppimet_JESTotalUp  ,0.0,thePandaFlat.puppimetphi_JESTotalUp  ,0.0);
        vMetDown.SetPtEtaPhiM(thePandaFlat.puppimet_JESTotalDown,0.0,thePandaFlat.puppimetphi_JESTotalDown,0.0);
      }
      TLorentzVector dilep = vLoose[0] + vLoose[1];

      double dPhiLepMETMin = TMath::Min(TMath::Abs(vLoose[0].DeltaPhi(vMet)), TMath::Abs(vLoose[1].DeltaPhi(vMet)));
      double dPhiLepTrackMETMin = TMath::Min(TMath::Abs(vLoose[0].DeltaPhi(vTrkMet)), TMath::Abs(vLoose[1].DeltaPhi(vTrkMet)));

      double PMET[1] = {vMet.Pt()};
      double PTrackMET[1] = {vTrkMet.Pt()};
      if(dPhiLepMETMin < TMath::Pi()/2) {PMET[0] = PMET[0] * sin(dPhiLepMETMin);}
      if(dPhiLepTrackMETMin < TMath::Pi()/2) {PTrackMET[0] = PTrackMET[0] * sin(dPhiLepTrackMETMin);}
      double minPMET[1] = {TMath::Min(PMET[0],PTrackMET[0])};

      bool passBtagVeto = thePandaFlat.jetNBtags == 0;

      bool passSel[7] = {qTot == 0, dilep.M() > 20, fabs(dilep.M()-91.1876) > 15 || lepType == 2, minPMET[0] > 20, minPMET[0] > 45 || lepType == 2, 
                         dilep.Pt() > 30 && (dilep.Pt() > 45 ||  lepType == 2), passBtagVeto};

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
      int lepTypeOri = lepType;
      lepType = lepType + 3*(int)thePandaFlat.nJot;

      double totalWeight = 1.0;
      if(theCategory != kPlotData){
        double triggerWeights[2] = {1.0, 0.0};
	trigger_sf(triggerWeights,thePandaFlat.nLooseLep,
	trgSFMMBB,trgSFMMEB,trgSFMMBE,trgSFMMEE,trgSFEEBB,trgSFEEEB,trgSFEEBE,trgSFEEEE,
	trgSFMEBB,trgSFMEEB,trgSFMEBE,trgSFMEEE,trgSFEMBB,trgSFEMEB,trgSFEMBE,trgSFEMEE,
	looseLepPt[0], TMath::Abs(looseLepEta[0]), abs(looseLepPdgId[0]),
	looseLepPt[1], TMath::Abs(looseLepEta[1]), abs(looseLepPdgId[1]));
        if(passBtagVeto) totalWeight = thePandaFlat.normalizedWeight * lumiV[whichYear] * thePandaFlat.sf_pu * thePandaFlat.sf_l1Prefire * looseLepSF[0] * looseLepSF[1] * thePandaFlat.sf_btag0   * triggerWeights[0] * theMCPrescale;
        else             totalWeight = thePandaFlat.normalizedWeight * lumiV[whichYear] * thePandaFlat.sf_pu * thePandaFlat.sf_l1Prefire * looseLepSF[0] * looseLepSF[1] * thePandaFlat.sf_btagGT0 * triggerWeights[0] * theMCPrescale;

        if     (infileCat_[ifile] == kPlotWZ)                                                totalWeight = totalWeight * thePandaFlat.sf_wz;
	else if(infileCat_[ifile] == kPlotZZ && infileName_[ifile].Contains("qqZZ") == true) totalWeight = totalWeight * thePandaFlat.sf_zz;

        double effSF = 1.0;
        for(unsigned int nl=0; nl<idLep.size(); nl++){
          if(idLep[nl] == 0) continue;
          bool applyTight = true;
          effSF = effSF * lepScaleFactor(looseLepPt[nl],looseLepEta[nl],TMath::Abs(looseLepPdgId[nl]),applyTight,histoLepEffSelMediumEtaPt_m,histoLepEffSelMediumEtaPt_e,histoLepEffSelTightEtaPt_m,histoLepEffSelTightEtaPt_e);
          if(effSF == 0){printf("effSF == 0!: %f %f %d \n",looseLepPt[nl],looseLepEta[nl],TMath::Abs(looseLepPdgId[nl])); return;}
        }
        totalWeight = totalWeight * effSF;
      }

      if(usePureMC == false && countLeptonTight != idLep.size()){
        double fakeSF = 1.0;
        for(unsigned int nl=0; nl<idLep.size(); nl++){
          if(idLep[nl] == 1) continue;
          bool applyTight = true;
          fakeSF = fakeSF * fakeRateFactor(TMath::Min((double)looseLepPt[nl],44.999),TMath::Abs(looseLepEta[nl]),TMath::Abs(looseLepPdgId[nl]),applyTight,histoFakeEffSelMediumEtaPt_m,histoFakeEffSelMediumEtaPt_e,histoFakeEffSelTightEtaPt_m,histoFakeEffSelTightEtaPt_e);
          theCategory = kPlotNonPrompt;
        }
        if     (infileCat_[ifile] != kPlotData && countLeptonTight == idLep.size()-2) fakeSF = +1.0 * fakeSF; // double fake, MC
        else if(infileCat_[ifile] != kPlotData && countLeptonTight == idLep.size()-1) fakeSF = -1.0 * fakeSF; // single fake, MC
        else if(infileCat_[ifile] == kPlotData && countLeptonTight == idLep.size()-2) fakeSF = -1.0 * fakeSF; // double fake, data
        else if(infileCat_[ifile] == kPlotData && countLeptonTight == idLep.size()-1) fakeSF = +1.0 * fakeSF; // single fake, data
        else printf("IMPOSSIBLE FAKE OPTION\n");
        totalWeight = totalWeight * fakeSF;
      }

      if(passAllButOneSel[0])histo[lepType+  0][theCategory]->Fill(TMath::Min(dilep.M(),199.999),totalWeight);
      if(passAllButOneSel[1])histo[lepType+  9][theCategory]->Fill(TMath::Min(minPMET[0],199.999),totalWeight);
      if(passAllButOneSel[1])histo[lepType+ 18][theCategory]->Fill(TMath::Min(vMet.Pt(),199.999),totalWeight);
      if(passAllButOneSel[1])histo[lepType+ 27][theCategory]->Fill(TMath::Min(vTrkMet.Pt(),199.999),totalWeight);
      if(passAllButOneSel[2])histo[lepType+ 36][theCategory]->Fill(TMath::Min(dilep.Pt(),199.999),totalWeight);
      if(passAllButOneSel[3])histo[lepType+ 45][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNBtags,4.499),totalWeight);
      if(passWWSel)          histo[lepType+ 54][theCategory]->Fill(TMath::Min(vLoose[0].Pt(),199.999),totalWeight);
      if(passWWSel)          histo[lepType+ 63][theCategory]->Fill(TMath::Min(vLoose[1].Pt(),199.999),totalWeight);
      if(passWWSel)          histo[lepType+ 72][theCategory]->Fill(TMath::Min(dilep.M(),199.999),totalWeight);
      if(passWWSel)          histo[lepType+ 81][theCategory]->Fill(TMath::Abs(vLoose[0].DeltaPhi(vLoose[1]))*180/TMath::Pi(),totalWeight);
      if(passSSSel)          histo[lepType+ 90][theCategory]->Fill(TMath::Min(vLoose[0].Pt(),199.999),totalWeight);
      if(passSSSel)          histo[lepType+ 99][theCategory]->Fill(TMath::Min(vLoose[1].Pt(),199.999),totalWeight);
      if(passSSSel)          histo[lepType+108][theCategory]->Fill(TMath::Min(dilep.M(),199.999),totalWeight);
      if(passSSSel)          histo[lepType+117][theCategory]->Fill(TMath::Abs(vLoose[0].DeltaPhi(vLoose[1]))*180/TMath::Pi(),totalWeight);
      if(passTopSel)         histo[lepType+126][theCategory]->Fill(TMath::Min(vLoose[0].Pt(),199.999),totalWeight);
      if(passTopSel)         histo[lepType+135][theCategory]->Fill(TMath::Min(vLoose[1].Pt(),199.999),totalWeight);
      if(passTopSel)         histo[lepType+144][theCategory]->Fill(TMath::Min(dilep.M(),199.999),totalWeight);
      if(passTopSel)         histo[lepType+153][theCategory]->Fill(TMath::Abs(vLoose[0].DeltaPhi(vMet))*180/TMath::Pi(),totalWeight);

    } // end events loop
    the_input_file->Close();
  } // end chain loop

  char output[200];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    sprintf(output,"histoWW_%d_%d.root",year,thePlot);	
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    double totBck = 0;
    for(int i=1; i<nPlotCategories; i++) totBck = totBck + histo[thePlot][i]->GetSumOfWeights();
    printf("(%2d) %7.1f vs. %7.1f ",thePlot,histo[thePlot][0]->GetSumOfWeights(),totBck);
    printf("(");
    for(int i=1; i<nPlotCategories; i++) printf("%7.1f ",histo[thePlot][i]->GetSumOfWeights());
    printf(")\n");
    for(int np=0; np<nPlotCategories; np++) {histo[thePlot][np]->SetNameTitle(Form("histo%d",np),Form("histo%d",np));histo[thePlot][np]->Write();}
    outFilePlotsNote->Close();
  }

}
