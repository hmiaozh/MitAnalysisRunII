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

#include "MitAnalysisRunII/panda/macros/9x/pandaFlat.C"
#include "MitAnalysisRunII/panda/macros/9x/common.h"

const int nTrgBinPt1  =  4; Float_t xTrgBinPt1[nTrgBinPt1+1]   = {25,30,35,50,10000};
const int nTrgBinPt2  =  4; Float_t xTrgBinPt2[nTrgBinPt2+1]   = {15,25,30,50,10000};
const int nTrgBinEta1 =  2; Float_t xTrgBinEta1[nTrgBinEta1+1] = {0.0,1.5,2.5};
const int nTrgBinEta2 =  2; Float_t xTrgBinEta2[nTrgBinEta2+1] = {0.0,1.5,2.5};
TH1D *hDTrgBinPt1  = new TH1D(Form("hDTrgBinPt1"),  Form("hDTrgBinPt1"),  nTrgBinPt1,  xTrgBinPt1);
TH1D *hDTrgBinPt2  = new TH1D(Form("hDTrgBinPt2"),  Form("hDTrgBinPt2"),  nTrgBinPt2,  xTrgBinPt2);
TH1D *hDTrgBinEta1 = new TH1D(Form("hDTrgBinEta1"), Form("hDTrgBinEta1"), nTrgBinEta1, xTrgBinEta1);
TH1D *hDTrgBinEta2 = new TH1D(Form("hDTrgBinEta2"), Form("hDTrgBinEta2"), nTrgBinEta2, xTrgBinEta2);

void triggerAnalysis(
int year,
int whichLepSel = 0
){

  //*******************************************************
  //Input Files
  //*******************************************************
  TString filesPath;
  TString puPath;
  vector<TString> infileName_;
  vector<int> infileCat_;

  if     (year == 2018){
    filesPath = "/data/t3home000/ceballos/panda/v_006_0/";
    puPath = "MitAnalysisRunII/data/90x/puWeights_90x_2018.root";
    infileName_.push_back(Form("%sMET.root",filesPath.Data()));                   infileCat_.push_back(0);
    infileName_.push_back(Form("%sWWinc.root" ,filesPath.Data()));                infileCat_.push_back(1);
    //infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data()));                 infileCat_.push_back(1);
    //infileName_.push_back(Form("%sggWW.root" ,filesPath.Data()));                 infileCat_.push_back(1);
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		  infileCat_.push_back(1);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));                   infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_M-50_LO.root",filesPath.Data()));    infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_M-50_NLO.root",filesPath.Data()));   infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYNJetsToLL.root",filesPath.Data()));           infileCat_.push_back(1);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	          infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYNJetsToLL_NLO.root",filesPath.Data()));       infileCat_.push_back(1);
  }
  else if(year == 2017){
    filesPath = "/data/t3home000/ceballos/panda/v_004_0/";
    puPath = "MitAnalysisRunII/data/90x/puWeights_90x_2017.root";
    infileName_.push_back(Form("%sMET.root",filesPath.Data()));                   infileCat_.push_back(0);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data()));		  infileCat_.push_back(1);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data()));		  infileCat_.push_back(1);
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		  infileCat_.push_back(1);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		          infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_M-50_LO.root",filesPath.Data()));    infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_M-50_NLO.root",filesPath.Data()));   infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYNJetsToLL_NLO.root",filesPath.Data()));       infileCat_.push_back(1);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	          infileCat_.push_back(1);
  }
  else if(year == 2016){
    filesPath = "/data/t3home000/ceballos/panda/v_002_0/";
    puPath = "MitAnalysisRunII/data/80x/puWeights_80x_37ifb.root";
    infileName_.push_back(Form("%sMET.root",filesPath.Data()));		          infileCat_.push_back(0);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	          infileCat_.push_back(1);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	          infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data()));  infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_M-50_NLO.root" ,filesPath.Data()));  infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_Pt0To50.root",filesPath.Data()));    infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_Pt50To100.root",filesPath.Data()));  infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_Pt100To250.root",filesPath.Data())); infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_Pt250To400.root",filesPath.Data())); infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_Pt400To650.root",filesPath.Data())); infileCat_.push_back(1);
    infileName_.push_back(Form("%sDYJetsToLL_Pt650ToInf.root",filesPath.Data())); infileCat_.push_back(1);
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));                 infileCat_.push_back(1);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));                   infileCat_.push_back(1);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	          infileCat_.push_back(1);
  }

  TFile *fPUFile = TFile::Open(puPath.Data());
  TH1D *fhDPU = (TH1D*)(fPUFile->Get("puWeights")); assert(fhDPU); fhDPU->SetDirectory(0);
  delete fPUFile;

  double trgEffDen[2][4][nTrgBinPt1][nTrgBinPt2][nTrgBinEta1][nTrgBinEta2];
  memset(trgEffDen, 0.0, 2 * 4 * nTrgBinPt1 * nTrgBinPt2 * nTrgBinEta1 * nTrgBinEta2 * sizeof(double));
  double trgEffNum[2][4][nTrgBinPt1][nTrgBinPt2][nTrgBinEta1][nTrgBinEta2];
  memset(trgEffNum, 0.0, 2 * 4 * nTrgBinPt1 * nTrgBinPt2 * nTrgBinEta1 * nTrgBinEta2 * sizeof(double));

  double xminPlot = 0.0;
  double xmaxPlot = 1.0;
  int nBinPlot = 200;
  const int allCategories = 2; // processes (data and MC)
  const int histBins = 4; // final states (mm, ee, me, em)
  const int allPlots = 12; // plots
  TH1D* histo[allCategories][histBins][allPlots];

  for(int thePlot=0; thePlot<allPlots; thePlot++){
    if     (thePlot >=  0 && thePlot <=  1) {nBinPlot =  60; xminPlot = -0.5; xmaxPlot =  59.5;}
    else if(thePlot >=  2 && thePlot <=  7) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 400.0;}
    else if(thePlot >=  8 && thePlot <= 11) {nBinPlot =  20; xminPlot = -2.5; xmaxPlot =   2.5;}
    TH1D* histos = new TH1D("histos", "histos", nBinPlot, xminPlot, xmaxPlot);
    histos->Sumw2();
    for(int i=0; i<histBins; i++) {
      for(int j=0; j<allCategories; j++) {
        histo[j][i][thePlot] = (TH1D*) histos->Clone(Form("histo_%d_%d_%d",j,i,thePlot));
      }
    }
    histos->Clear();
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

      if(thePandaFlat.nLooseLep < 2) continue;

      vector<float>  looseLepPt,looseLepEta,looseLepPhi,looseLepSF;
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
        looseLepSF.push_back(thePandaFlat.muonSfReco[i]*thePandaFlat.muonSfMedium[i]);
	if(thePandaFlat.muonPt[i] > 25) ptSelCuts[0]++;
	if(thePandaFlat.muonPt[i] > 15) ptSelCuts[1]++;
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
        looseLepSF.push_back(thePandaFlat.electronSfReco[i]*thePandaFlat.electronSfMedium[i]);
	if(thePandaFlat.electronPt[i] > 25) ptSelCuts[0]++;
	if(thePandaFlat.electronPt[i] > 15) ptSelCuts[1]++;
	if(thePandaFlat.electronPt[i] > 10) ptSelCuts[2]++;
      }

      if((int)looseLepPt.size() != thePandaFlat.nLooseLep) printf("IMPOSSIBLE\n");

      if(!(ptSelCuts[0] >= 1 && ptSelCuts[1] >= 2)) continue;

      bool passLepId = false;
      if     (whichLepSel == 0) passLepId = ((looseLepSelBit[0] & kFake  ) == kFake  ) && ((looseLepSelBit[1] & kFake  ) == kFake  );
      else if(whichLepSel == 1) passLepId = ((looseLepSelBit[0] & kMedium) == kMedium) && ((looseLepSelBit[1] & kMedium) == kMedium);
      if(passLepId == false) continue;

      int lepType = -1;
      if     (abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13) lepType = 0;
      else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11) lepType = 1;
      else if(abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==11) lepType = 2;
      else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==13) lepType = 2;
      else  {printf("IMPOSSIBLE\n");}

      TLorentzVector vLoose1,vLoose2;
      double thePDGMass[2] = {mass_mu, mass_mu};
      if(abs(looseLepPdgId[0])==11) thePDGMass[0] = mass_el;
      if(abs(looseLepPdgId[1])==11) thePDGMass[1] = mass_el;
      if(looseLepPt[0] > looseLepPt[1]){
        vLoose1.SetPtEtaPhiM(looseLepPt[0],looseLepEta[0],looseLepPhi[0],thePDGMass[0]);
        vLoose2.SetPtEtaPhiM(looseLepPt[1],looseLepEta[1],looseLepPhi[1],thePDGMass[1]);
      } else {
        vLoose2.SetPtEtaPhiM(looseLepPt[0],looseLepEta[0],looseLepPhi[0],thePDGMass[0]);
        vLoose1.SetPtEtaPhiM(looseLepPt[1],looseLepEta[1],looseLepPhi[1],thePDGMass[1]);
      }
      TLorentzVector dilep = vLoose1+vLoose2;

      if(dilep.M() <= 12) continue;
      if(vLoose1.Pt() <= 25 || vLoose2.Pt() <= 15 || TMath::Abs(vLoose1.Eta()) >= 2.5 || TMath::Abs(vLoose2.Eta()) >= 2.5) continue;

      int npt1  = hDTrgBinPt1 ->GetXaxis()->FindFixBin(vLoose1.Pt())-1;
      int npt2  = hDTrgBinPt2 ->GetXaxis()->FindFixBin(vLoose2.Pt())-1;
      int neta1 = hDTrgBinEta1->GetXaxis()->FindFixBin(TMath::Abs(vLoose1.Eta()))-1;
      int neta2 = hDTrgBinEta2->GetXaxis()->FindFixBin(TMath::Abs(vLoose2.Eta()))-1;

      if(npt1 == -1 || npt2 == -1 || neta1 == -1 || neta2 == -1) printf("PROBLEM %d %d %d %d\n",npt1,npt2,neta1,neta2);

      int theCategory = infileCat_[ifile];
      double totalWeight = 1.0;
      if(theCategory != 0){
        double sfPileUp = nPUScaleFactor(fhDPU,thePandaFlat.pu);

        totalWeight = sfPileUp * looseLepSF[0] * looseLepSF[1];
      }

      trgEffDen[theCategory][lepType][npt1][npt2][neta1][neta2] = trgEffDen[theCategory][lepType][npt1][npt2][neta1][neta2] + totalWeight;
      histo[theCategory][lepType][ 0]->Fill(1.0,totalWeight);
      histo[theCategory][lepType][ 2]->Fill(TMath::Min(vLoose1.Pt(),399.999),totalWeight);
      histo[theCategory][lepType][ 4]->Fill(TMath::Min(vLoose2.Pt(),399.999),totalWeight);
      histo[theCategory][lepType][ 5]->Fill(TMath::Min(dilep.Pt(),399.999),totalWeight);
      histo[theCategory][lepType][ 8]->Fill(vLoose1.Eta(),totalWeight);
      histo[theCategory][lepType][10]->Fill(vLoose2.Eta(),totalWeight);

      bool passTrigger = (thePandaFlat.trigger & (1<<kEMuTrig)) != 0       || (thePandaFlat.trigger & (1<<kDoubleMuTrig)) != 0  ||
                         (thePandaFlat.trigger & (1<<kSingleMuTrig)) != 0  || (thePandaFlat.trigger & (1<<kDoubleEleTrig)) != 0 ||
                         (thePandaFlat.trigger & (1<<kSingleEleTrig)) != 0;

      if(passTrigger){
        trgEffNum[theCategory][lepType][npt1][npt2][neta1][neta2] = trgEffNum[theCategory][lepType][npt1][npt2][neta1][neta2] + totalWeight;
        histo[theCategory][lepType][ 1]->Fill(1.0,totalWeight);
        histo[theCategory][lepType][ 3]->Fill(TMath::Min(vLoose1.Pt(),399.999),totalWeight);
        histo[theCategory][lepType][ 5]->Fill(TMath::Min(vLoose2.Pt(),399.999),totalWeight);
        histo[theCategory][lepType][ 7]->Fill(TMath::Min(dilep.Pt(),399.999),totalWeight);
        histo[theCategory][lepType][ 9]->Fill(vLoose1.Eta(),totalWeight);
        histo[theCategory][lepType][11]->Fill(vLoose2.Eta(),totalWeight);
      }
    } // end events loop
    the_input_file->Close();
  } // end chain loop

  double eff, unc;
  for(int ntypel=0; ntypel<4; ntypel++){
    for(int npt1=0; npt1<nTrgBinPt1; npt1++){
      for(int npt2=0; npt2<nTrgBinPt2; npt2++){
    	for(int neta1=0; neta1<nTrgBinEta1; neta1++){
    	  for(int neta2=0; neta2<nTrgBinEta2; neta2++){
            double eff0 = 1.0; double unc0 = 1.0;
            if(trgEffDen[0][ntypel][npt1][npt2][neta1][neta2] > 0) {
              eff0 = trgEffNum[0][ntypel][npt1][npt2][neta1][neta2]/
	             trgEffDen[0][ntypel][npt1][npt2][neta1][neta2];
              unc0 = sqrt(eff0*(1-eff0)/trgEffDen[0][ntypel][npt1][npt2][neta1][neta2])/5.0;
	      if(eff0 == 1) unc0 = 1./sqrt(trgEffDen[0][ntypel][npt1][npt2][neta1][neta2])/5.0;
            }
            double eff1 = 1.0; double unc1 = 1.0;
            if(trgEffDen[1][ntypel][npt1][npt2][neta1][neta2] > 0) {
              eff1 = trgEffNum[1][ntypel][npt1][npt2][neta1][neta2]/
	             trgEffDen[1][ntypel][npt1][npt2][neta1][neta2];
              unc1 = sqrt(eff1*(1-eff1)/trgEffDen[1][ntypel][npt1][npt2][neta1][neta2])/5.0;
	      if(eff1 == 1) unc1 = 1./sqrt(trgEffDen[1][ntypel][npt1][npt2][neta1][neta2])/5.0;
            }
	    if(trgEffDen[0][ntypel][npt1][npt2][neta1][neta2] > 0) {
    	      printf("trgEff[%d][%d][%d][%d][%d] = %8.5f +/- %8.5f;| %8.5f +/- %8.5f = %8.5f +/- %8.5f (%8.5f)\n",ntypel,npt1,npt2,neta1,neta2,eff0,unc0,eff1,unc1,eff0/eff1,unc0/eff1,eff0/eff1*sqrt(unc0/eff0*unc0/eff0+unc1/eff1*unc1/eff1));
	    }
    	  }
        }
      }
    }
  }

  char output[200];
  sprintf(output,"histo_trigger%d_histos_sel%d.root",year,whichLepSel);	
  TFile* outFilePlotsHistos = new TFile(output,"recreate");
  outFilePlotsHistos->cd();
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    for(int i=0; i<histBins; i++) {
      for(int j=0; j<allCategories; j++) {
        histo[j][i][thePlot]->Write();
        //printf("aaa %d %d %d %f\n",j,i,thePlot,histo[j][i][thePlot]->GetSumOfWeights());
      }
    }
  }
  outFilePlotsHistos->Close();

  for(int thePlot=0; thePlot<allPlots/2; thePlot++){
    for(int theCat=0; theCat<allCategories; theCat++){
      for(int theType=0; theType<histBins; theType++){
        for(int i=1; i<=histo[theCat][theType][2*thePlot+1]->GetNbinsX(); i++){
	  eff = 1; unc = 1;
	  if(histo[theCat][theType][2*thePlot]->GetBinContent(i) > 0){
            eff = histo[theCat][theType][2*thePlot+1]->GetBinContent(i)/histo[theCat][theType][2*thePlot]->GetBinContent(i);
            unc =sqrt(eff*(1-eff)/histo[theCat][theType][2*thePlot]->GetBinContent(i));
	  }
	  histo[theCat][theType][2*thePlot+1]->SetBinContent(i,eff);
	  histo[theCat][theType][2*thePlot+1]->SetBinError(i,unc);
        }
      }
    }
  }

  sprintf(output,"histo_trigger%d_eff_sel%d.root",year,whichLepSel);	
  TFile* outFilePlotsEff = new TFile(output,"recreate");
  outFilePlotsEff->cd();
  for(int theCat=0; theCat<allCategories; theCat++){
    for(int theType=0; theType<histBins; theType++){
      histo[theCat][theType][ 1]->Write();
      histo[theCat][theType][ 3]->Write();
      histo[theCat][theType][ 5]->Write();
      histo[theCat][theType][ 7]->Write();
      histo[theCat][theType][ 9]->Write();
      histo[theCat][theType][11]->Write();
    }
  }
  outFilePlotsEff->Close();

}
