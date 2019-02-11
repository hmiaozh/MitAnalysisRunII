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
#include <thread>
#include "TRandom.h"
#include "TLorentzVector.h"

#include "MitAnalysisRunII/panda/macros/9x/pandaFlat.C"
#include "MitAnalysisRunII/panda/macros/9x/common.h"

const double mcPrescale = 1;
bool multithread=true;

void zAnalysis_cern(int year, int type = 0)
{
  vector<TString> infileName_;
  vector<int> infileCat_;

  double lumi;
  TString filesPath;
  TString puPath;
  if     (year == 2017) {
    lumi = 41.5;
    filesPath = "/eos/cms/store/user/ceballos/Zstudy/y2017/";
    puPath = "MitAnalysisRunII/data/90x/puWeights_90x_2017.root";

    if     (type==0||type==1){
      infileName_.push_back(Form("%sdata.root", filesPath.Data()));                infileCat_.push_back(kPlotData);
    }
    else if(type==0||type==2){
      infileName_.push_back(Form("%sDYJetsToLL.root",filesPath.Data()));           infileCat_.push_back(kPlotDY);
    }
    else if(type==0||type==3){
      infileName_.push_back(Form("%sWW.root",filesPath.Data()));                   infileCat_.push_back(kPlotqqWW);
      infileName_.push_back(Form("%sWZ.root",filesPath.Data()));                   infileCat_.push_back(kPlotWZ);
      infileName_.push_back(Form("%sZZ.root",filesPath.Data()));                   infileCat_.push_back(kPlotZZ);
      infileName_.push_back(Form("%sTT2L.root",filesPath.Data()));                 infileCat_.push_back(kPlotTop);
      infileName_.push_back(Form("%sTW.root",filesPath.Data()));                   infileCat_.push_back(kPlotTop);
    }
    else {
      printf("Wrong type (%d)\n",type);
      return;
    }
  }
  else if(year == 2016) {
    lumi = 35.9;
    filesPath = "/eos/cms/store/user/ceballos/Zstudy/y2016/";
    puPath = "MitAnalysisRunII/data/80x/puWeights_80x_37ifb.root";

    if     (type==0||type==1){
      infileName_.push_back(Form("%sdata.root", filesPath.Data()));                infileCat_.push_back(kPlotData);
    }
    else if(type==0||type==2){
      infileName_.push_back(Form("%sDYJetsToLL_Pt0To50.root",filesPath.Data()));   infileCat_.push_back(kPlotDY);
      infileName_.push_back(Form("%sDYJetsToLL_Pt50To100.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
      infileName_.push_back(Form("%sDYJetsToLL_Pt100To250.root",filesPath.Data()));infileCat_.push_back(kPlotDY);
      infileName_.push_back(Form("%sDYJetsToLL_Pt250To400.root",filesPath.Data()));infileCat_.push_back(kPlotDY);
      infileName_.push_back(Form("%sDYJetsToLL_Pt400To650.root",filesPath.Data()));infileCat_.push_back(kPlotDY);
      infileName_.push_back(Form("%sDYJetsToLL_Pt650ToInf.root",filesPath.Data()));infileCat_.push_back(kPlotDY);
    }
    else if(type==0||type==3){
      infileName_.push_back(Form("%sWW.root" ,filesPath.Data()));                  infileCat_.push_back(kPlotqqWW);
      infileName_.push_back(Form("%sWZ.root" ,filesPath.Data()));                  infileCat_.push_back(kPlotWZ);
      infileName_.push_back(Form("%sZZ.root" ,filesPath.Data()));                  infileCat_.push_back(kPlotZZ);
      infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));                infileCat_.push_back(kPlotTop);
      infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));                  infileCat_.push_back(kPlotTop);
    }
    else {
      printf("Wrong type (%d)\n",type);
      return;
    }
  }
  else {
    return;
  }

 TFile *fPUFile = TFile::Open(Form("%s",puPath.Data()));
  TH1D *fhDPU     = (TH1D*)(fPUFile->Get("puWeights"));     assert(fhDPU);     fhDPU    ->SetDirectory(0);
  TH1D *fhDPUUp   = (TH1D*)(fPUFile->Get("puWeightsUp"));   assert(fhDPUUp);   fhDPUUp  ->SetDirectory(0);
  TH1D *fhDPUDown = (TH1D*)(fPUFile->Get("puWeightsDown")); assert(fhDPUDown); fhDPUDown->SetDirectory(0);
  delete fPUFile;

  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 80;
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

    TH1D* histos = new TH1D("histos", "histos", nBinPlot, xminPlot, xmaxPlot);
    histos->Sumw2();
    for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = (TH1D*) histos->Clone(Form("histo%d",i));
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
        looseLepSelBit.push_back(thePandaFlat.electronSelBit[i]);
        looseLepSF.push_back(thePandaFlat.electronSfReco[i] * thePandaFlat.electronSfMedium[i]);
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

        passLooseLepId = passLooseLepId && ((looseLepSelBit[i] & kMedium) == kMedium);
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
      vMet    .SetPtEtaPhiM(thePandaFlat.pfmet,0.0,thePandaFlat.pfmetphi,0.0);
      vMetUp  .SetPtEtaPhiM(thePandaFlat.pfmet_JESTotalUp  ,0.0,thePandaFlat.pfmetphi_JESTotalUp  ,0.0);
      vMetDown.SetPtEtaPhiM(thePandaFlat.pfmet_JESTotalDown,0.0,thePandaFlat.pfmetphi_JESTotalDown,0.0);

      double dPhiDiLepMET = TMath::Abs(dilep.DeltaPhi(vMet));
      double ptFrac = TMath::Abs(dilep.Pt()-vMet.Pt())/dilep.Pt();
      double caloMinusPFMETRel = TMath::Abs(thePandaFlat.calomet-thePandaFlat.pfmet)/thePandaFlat.pfmet;
      double dphill = TMath::Abs(vLoose[0].DeltaPhi(vLoose[1]));
      double detall = TMath::Abs(vLoose[0].Eta()-vLoose[1].Eta());
      double drll = sqrt(dphill*dphill+detall*detall);
      double mtW = TMath::Sqrt(2.0*dilep.Pt()*vMet.Pt()*(1.0 - TMath::Cos(dPhiDiLepMET)));

      bool passSel = ((lepType != 2 && TMath::Abs(dilep.M()-91.1876) < 15) || 
                      (lepType == 2 && dilep.M() > 50 && thePandaFlat.jetNBtags > 0)) 
                      && vLoose[0].Pt() > 25 && vLoose[1].Pt() > 25;
      if(passSel == false) continue;

      double totalWeight = 1.0; double sfWS = 1.0; double puWeight = 1.0; double npvWeight = 1.0;
      if     (theCategory != kPlotData){
        puWeight  = nPUScaleFactor(fhDPU,  thePandaFlat.pu);

        totalWeight = thePandaFlat.normalizedWeight * lumi * puWeight * thePandaFlat.sf_l1Prefire * looseLepSF[0] * looseLepSF[1];
      }

      if(qTot == 0) histo[lepType+ 0][theCategory]->Fill(dilep.M(),totalWeight);
      else          histo[lepType+ 3][theCategory]->Fill(dilep.M(),totalWeight*sfWS);

      if(qTot != 0) continue;

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

    } // end event loop
  } // end samples loop

  char output[200];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    sprintf(output,"histoDY%d_%d_%d.root",type,year,thePlot);	
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    double totBck = 0;
    for(int i=1; i<nPlotCategories; i++) totBck =totBck + histo[thePlot][i]->GetSumOfWeights();
    printf("(%d) %f vs. %f\n",thePlot,histo[thePlot][0]->GetSumOfWeights(),totBck);
    for(int np=0; np<nPlotCategories; np++) histo[thePlot][np]->Write();
    outFilePlotsNote->Close();
  }

}
