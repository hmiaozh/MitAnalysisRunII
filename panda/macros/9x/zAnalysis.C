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
  double k_eff = 0.5 * sqrt(20285930./12446486.);

  //*******************************************************
  //Inputs
  //*******************************************************
  vector<TString> infileName_;
  vector<int> infileCat_;

  double lumi;
  TString filesPath;
  TString fLepton_FakesName;
  if(year == 2017) {
    lumi = 41.5;
    filesPath = "/data/t3home000/ceballos/panda/v_004_0/";

    infileName_.push_back(Form("%sdata.root",filesPath.Data()));                 infileCat_.push_back(kPlotData);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotqqWW);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotggWW);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_M-50_LO.root",filesPath.Data()));   infileCat_.push_back(kPlotDY);
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

    infileName_.push_back(Form("%sdata.root",filesPath.Data()));                  infileCat_.push_back(kPlotData);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotqqWW);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotggWW);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data()));  infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt0To50.root",filesPath.Data()));    infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt50To100.root",filesPath.Data()));  infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt100To250.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt250To400.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt400To650.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
    infileName_.push_back(Form("%sDYJetsToLL_Pt650ToInf.root",filesPath.Data())); infileCat_.push_back(kPlotDY);
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

  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 71;
  TH1D* histo[allPlots][nPlotCategories];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    if     (thePlot >=  0 && thePlot <=  1) {nBinPlot = 120; xminPlot = 91.1876-15; xmaxPlot = 91.1876+15;}
    else if(thePlot >=  2 && thePlot <=  2) {nBinPlot = 200; xminPlot = 20.0; xmaxPlot = 220;}
    else if(thePlot >=  3 && thePlot <=  8) {nBinPlot =  10; xminPlot = -0.5; xmaxPlot = 9.5;}
    else if(thePlot >=  9 && thePlot <= 11) {nBinPlot =1000; xminPlot =  0.0; xmaxPlot =1000;}
    else if(thePlot >= 12 && thePlot <= 26) {nBinPlot = 500; xminPlot =  0.0; xmaxPlot = 500;}
    else if(thePlot >= 27 && thePlot <= 32) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = TMath::Pi();}
    else if(thePlot >= 33 && thePlot <= 38) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 5.0;}
    else if(thePlot >= 39 && thePlot <= 44) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 5.0;}
    else if(thePlot >= 45 && thePlot <= 47) {nBinPlot =  80; xminPlot = -0.5; xmaxPlot = 79.5;}
    else if(thePlot >= 48 && thePlot <= 53) {nBinPlot = 100; xminPlot = -2.5; xmaxPlot = 2.5;}
    else if(thePlot >= 54 && thePlot <= 59) {nBinPlot = 200; xminPlot = 25.0; xmaxPlot = 225;}
    else if(thePlot >= 60 && thePlot <= 62) {nBinPlot =   5; xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >= 63 && thePlot <= 70) {nBinPlot = 200; xminPlot = 25.0; xmaxPlot = 225;}
    
    if(isTopSel == true && (thePlot >=  0 && thePlot <=  1)) {nBinPlot = 200; xminPlot = 20.0; xmaxPlot = 220;}

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
    double theMCPrescale = 1.0; if(infileCat_[ifile] != 0) theMCPrescale = mcPrescale;
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
      vector<int> looseLepSelBit,looseLepPdgId;
      int ptSelCuts[3] = {0,0,0};
      for(int i=0; i<thePandaFlat.nLooseMuon; i++){
        looseLepPt.push_back(thePandaFlat.muonPt[i]);
        looseLepEta.push_back(thePandaFlat.muonEta[i]);
        looseLepPhi.push_back(thePandaFlat.muonPhi[i]);
        looseLepSF.push_back(thePandaFlat.muonSfReco[i] * thePandaFlat.muonSfMedium[i]);
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
        looseLepSF.push_back(thePandaFlat.electronSfReco[i] * thePandaFlat.electronSfMedium[i]);
        looseLepSelBit.push_back(thePandaFlat.electronSelBit[i]);
        looseLepPdgId.push_back(thePandaFlat.electronPdgId[i]);
	if(thePandaFlat.electronPt[i] > 25) ptSelCuts[0]++;
	if(thePandaFlat.electronPt[i] > 20) ptSelCuts[1]++;
	if(thePandaFlat.electronPt[i] > 10) ptSelCuts[2]++;
      }

      if((int)looseLepPt.size() != thePandaFlat.nLooseLep) printf("IMPOSSIBLE\n");

      bool passLepId = ((looseLepSelBit[0] & kMedium) == kMedium) && ((looseLepSelBit[1] & kMedium) == kMedium);
      if(passLepId == false) continue;
      int theCategory = infileCat_[ifile];

      int lepType = -1;
      if     (abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13 && looseLepPdgId[0]*looseLepPdgId[1]<0) lepType = 0;
      else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11 && looseLepPdgId[0]*looseLepPdgId[1]<0) lepType = 1;
      else if(abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==11 && looseLepPdgId[0]*looseLepPdgId[1]<0) lepType = 2;
      else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==13 && looseLepPdgId[0]*looseLepPdgId[1]<0) lepType = 2;
      else if(abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13 && looseLepPdgId[0]*looseLepPdgId[1]>0) lepType = 3;
      else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11 && looseLepPdgId[0]*looseLepPdgId[1]>0) lepType = 4;
      else if(abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==11 && looseLepPdgId[0]*looseLepPdgId[1]>0) lepType = 5;
      else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==13 && looseLepPdgId[0]*looseLepPdgId[1]>0) lepType = 5;
      else printf("Impossible dilepton combination: %d %d\n",looseLepPdgId[0],looseLepPdgId[1]);

      if(lepType >= 3 || lepType == -1) continue;

      double thePDGMass[2] = {mass_mu, mass_mu};
      if     (abs(lepType) == 1) {thePDGMass[0] = mass_el; thePDGMass[1] = mass_el;}
      else if(abs(lepType) == 2 && abs(looseLepPdgId[0])==11) {thePDGMass[0] = mass_el;}
      else if(abs(lepType) == 2 && abs(looseLepPdgId[1])==11) {thePDGMass[1] = mass_el;}
      TLorentzVector v1,v2,metP4;
      v1.SetPtEtaPhiM(looseLepPt[0],looseLepEta[0],looseLepPhi[0],thePDGMass[0]);
      v2.SetPtEtaPhiM(looseLepPt[1],looseLepEta[1],looseLepPhi[1],thePDGMass[1]);
      TLorentzVector dilep = v1+v2;
      metP4.SetPtEtaPhiM(thePandaFlat.pfmet,0,thePandaFlat.pfmetphi,0);

      double dPhiDiLepMET = TMath::Abs(dilep.DeltaPhi(metP4));
      double ptFrac = TMath::Abs(dilep.Pt()-metP4.Pt())/dilep.Pt();
      double caloMinusPFMETRel = TMath::Abs(thePandaFlat.calomet-thePandaFlat.pfmet)/thePandaFlat.pfmet;
      double dphill = TMath::Abs(v1.DeltaPhi(v2));
      double detall = TMath::Abs(v1.Eta()-v2.Eta());
      double drll = sqrt(dphill*dphill+detall*detall);
      double mtW = TMath::Sqrt(2.0*dilep.Pt()*metP4.Pt()*(1.0 - TMath::Cos(dPhiDiLepMET)));

      bool passSel = (TMath::Abs((v1+v2).M()-91.1876) < 15 || (lepType == 2 && (v1+v2).M() > 50)) && v1.Pt() > 25 && v2.Pt() > 25;
      if(isTopSel == true) passSel = (TMath::Abs((v1+v2).M()-91.1876) > 15 || lepType == 2) && (v1+v2).M() > 50 && v1.Pt() > 25 && v2.Pt() > 25 && mtW > 50;
      if(passSel == false) continue;

      double totalWeight = 1.0;
      if     (theCategory != kPlotData){
        double triggerWeights[2];
        trigger_sf(triggerWeights, trgEff, trgEffE, lepType, looseLepPt[0], TMath::Abs(looseLepEta[0]), looseLepPt[1], TMath::Abs(looseLepEta[1]));
        totalWeight = thePandaFlat.normalizedWeight * lumi * thePandaFlat.sf_pu * looseLepSF[0] * looseLepSF[1] * triggerWeights[0];
      }

      bool passFakeLepId[2] = {((looseLepSelBit[0] & kFake) == kFake), ((looseLepSelBit[1] & kFake) == kFake)};

      histo[lepType+ 6][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJot,9.4999),totalWeight);
      if(isTopSel == true) passSel = passSel && thePandaFlat.nJot >= 1;
      if(passSel == false) continue;
      histo[lepType+ 0][theCategory]->Fill((v1+v2).M(),totalWeight);
      histo[lepType+ 3][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJet,9.4999),totalWeight);
      histo[lepType+ 9][theCategory]->Fill(TMath::Min((v1+v2).Pt(), 999.999),totalWeight);
      histo[lepType+12][theCategory]->Fill(TMath::Min((double)thePandaFlat.pfmet, 499.999),totalWeight);
      histo[lepType+15][theCategory]->Fill(TMath::Min((double)thePandaFlat.puppimet, 499.999),totalWeight);
      histo[lepType+18][theCategory]->Fill(TMath::Min((double)thePandaFlat.calomet, 499.999),totalWeight);
      histo[lepType+21][theCategory]->Fill(TMath::Min((double)thePandaFlat.trkmet, 499.999),totalWeight);
      histo[lepType+24][theCategory]->Fill(TMath::Min(mtW, 499.999),totalWeight);
      histo[lepType+27][theCategory]->Fill(dPhiDiLepMET,totalWeight);
      histo[lepType+30][theCategory]->Fill(dphill,totalWeight);
      histo[lepType+33][theCategory]->Fill(TMath::Min(ptFrac,4.999),totalWeight);
      histo[lepType+36][theCategory]->Fill(TMath::Min(caloMinusPFMETRel,4.999),totalWeight);
      histo[lepType+39][theCategory]->Fill(TMath::Min(detall,4.999),totalWeight);
      histo[lepType+42][theCategory]->Fill(TMath::Min(drll,4.999),totalWeight);
      histo[lepType+45][theCategory]->Fill(TMath::Min((double)thePandaFlat.npv,79.499),totalWeight);
      histo[lepType+48][theCategory]->Fill(looseLepEta[0],totalWeight);
      histo[lepType+51][theCategory]->Fill(looseLepEta[1],totalWeight);
      histo[lepType+54][theCategory]->Fill(TMath::Min((double)looseLepPt[0], 224.999),totalWeight);
      histo[lepType+57][theCategory]->Fill(TMath::Min((double)looseLepPt[1], 224.999),totalWeight);
      histo[lepType+60][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNBtags,4.4999),totalWeight);
      if     (lepType == 0){
        if     (TMath::Abs(looseLepEta[0]) < 1.475) histo[63][theCategory]->Fill(TMath::Min((double)looseLepPt[0], 224.999),totalWeight);
        else                                        histo[64][theCategory]->Fill(TMath::Min((double)looseLepPt[0], 224.999),totalWeight);
        if     (TMath::Abs(looseLepEta[1]) < 1.475) histo[63][theCategory]->Fill(TMath::Min((double)looseLepPt[1], 224.999),totalWeight);
        else                                        histo[64][theCategory]->Fill(TMath::Min((double)looseLepPt[1], 224.999),totalWeight);
        if(passFakeLepId[0]) {
          if     (TMath::Abs(looseLepEta[0]) < 1.475) histo[65][theCategory]->Fill(TMath::Min((double)looseLepPt[0], 224.999),totalWeight);
          else                                        histo[66][theCategory]->Fill(TMath::Min((double)looseLepPt[0], 224.999),totalWeight);
        }
        if(passFakeLepId[1]) {
          if     (TMath::Abs(looseLepEta[1]) < 1.475) histo[65][theCategory]->Fill(TMath::Min((double)looseLepPt[1], 224.999),totalWeight);
          else                                        histo[66][theCategory]->Fill(TMath::Min((double)looseLepPt[1], 224.999),totalWeight);
	}
      }
      else if(lepType == 1){
        if     (TMath::Abs(looseLepEta[0]) < 1.475) histo[67][theCategory]->Fill(TMath::Min((double)looseLepPt[0], 224.999),totalWeight);
        else                                        histo[68][theCategory]->Fill(TMath::Min((double)looseLepPt[0], 224.999),totalWeight);
        if     (TMath::Abs(looseLepEta[1]) < 1.475) histo[67][theCategory]->Fill(TMath::Min((double)looseLepPt[1], 224.999),totalWeight);
        else                                        histo[68][theCategory]->Fill(TMath::Min((double)looseLepPt[1], 224.999),totalWeight);
        if(passFakeLepId[0]) {
          if     (TMath::Abs(looseLepEta[0]) < 1.475) histo[69][theCategory]->Fill(TMath::Min((double)looseLepPt[0], 224.999),totalWeight);
          else                                        histo[70][theCategory]->Fill(TMath::Min((double)looseLepPt[0], 224.999),totalWeight);
        }
        if(passFakeLepId[1]) {
          if     (TMath::Abs(looseLepEta[1]) < 1.475) histo[69][theCategory]->Fill(TMath::Min((double)looseLepPt[1], 224.999),totalWeight);
          else                                        histo[70][theCategory]->Fill(TMath::Min((double)looseLepPt[1], 224.999),totalWeight);
	}
      }
      
    } // end event loop
  } // end samples loop

  char output[200];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    TString addSuffix = "";
    if(isTopSel == true) addSuffix = "_topsel";
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

}
