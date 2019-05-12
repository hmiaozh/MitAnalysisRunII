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

const double prescale = 0.1;

void skimmingAnalysis(int year)
{

  vector<TString> infileName_;
  TString inpPath;
  TString outPath;
  if     (year == 2017) {
    inpPath = "/eos/cms/store/user/ceballos/Zstudy/y2017/";
    outPath = "/eos/cms/store/user/ceballos/Zstudy/y2017/skimming/";
  }
  else if(year == 2016) {
    inpPath = "/eos/cms/store/user/ceballos/Zstudy/y2016/";
    outPath = "/eos/cms/store/user/ceballos/Zstudy/y2016/skimming/";
  }
  else {
    return;
  }

  infileName_.push_back(Form("DYJetsToLL.root"));
  infileName_.push_back(Form("DYJetsToLL_Pt0To50.root"));
  infileName_.push_back(Form("DYJetsToLL_Pt50To100.root"));
  infileName_.push_back(Form("DYJetsToLL_Pt100To250.root"));
  infileName_.push_back(Form("DYJetsToLL_Pt250To400.root"));
  infileName_.push_back(Form("DYJetsToLL_Pt400To650.root"));
  infileName_.push_back(Form("DYJetsToLL_Pt650ToInf.root"));
  infileName_.push_back(Form("TT2L.root"));
  infileName_.push_back(Form("TW.root"));
  infileName_.push_back(Form("WW.root"));
  infileName_.push_back(Form("WZ.root"));
  infileName_.push_back(Form("ZZ.root"));
  infileName_.push_back(Form("data.root"));

  for(UInt_t ifile=0; ifile<infileName_.size(); ifile++) {
    printf("sampleNames(%d): %s\n",ifile,infileName_[ifile].Data());
    TFile *the_input_file = TFile::Open(Form("%s%s",inpPath.Data(),infileName_[ifile].Data()));
    if(!the_input_file) continue;
    TTree *the_input_tree = (TTree*)the_input_file->FindObjectAny("events");
    
    TFile *outputFile = new TFile(Form("%s%s",outPath.Data(),infileName_[ifile].Data()), "RECREATE");
    outputFile->cd();
    outputFile->SaveSelf(kTRUE);
    TTree *normalizedTree = the_input_tree->CloneTree(0);

    UInt_t N_pass[3] = {0, 0, 0};
    pandaFlat thePandaFlat(the_input_tree);
    Long64_t nentries = thePandaFlat.fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = thePandaFlat.LoadTree(jentry);
      if (ientry < 0) break;
      nb = thePandaFlat.fChain->GetEntry(jentry);   nbytes += nb;
      if (jentry%1000000 == 0) printf("--- reading event %8lld (%8lld) of %8lld\n",jentry,ientry,nentries);

      int skimFilter = -1;
      if     (thePandaFlat.nLooseLep != 2) {
        skimFilter = -1;
      }
      else if(thePandaFlat.nLooseLep == 2) {
        vector<float>  looseLepPt,looseLepEta,looseLepPhi;
        vector<int> looseLepPdgId;
        for(int i=0; i<thePandaFlat.nLooseMuon; i++){
          looseLepPt.push_back(thePandaFlat.muonPt[i]);
          looseLepEta.push_back(thePandaFlat.muonEta[i]);
          looseLepPhi.push_back(thePandaFlat.muonPhi[i]);
          looseLepPdgId.push_back(thePandaFlat.muonPdgId[i]);
        }
        for(int i=0; i<thePandaFlat.nLooseElectron; i++){
          looseLepPt.push_back(thePandaFlat.electronPt[i]);
          looseLepEta.push_back(thePandaFlat.electronEta[i]);
          looseLepPhi.push_back(thePandaFlat.electronPhi[i]);
          looseLepPdgId.push_back(thePandaFlat.electronPdgId[i]);
        }
	if(TMath::Abs(looseLepPdgId[0]) == TMath::Abs(looseLepPdgId[1])){
          TLorentzVector dilep;
          for(int i=0; i<thePandaFlat.nLooseLep; i++) {
            double thePDGMass = mass_mu;
            if(abs(looseLepPdgId[i])==11) thePDGMass = mass_el;
	    TLorentzVector vLepTemp; vLepTemp.SetPtEtaPhiM(looseLepPt[i],looseLepEta[i],looseLepPhi[i],thePDGMass);
            dilep = dilep + vLepTemp;
          }
          if(looseLepPt[0] > 25.0 && looseLepPt[1] > 25.0 &&
             TMath::Abs(dilep.M()-91.1876) < 15 && gRandom->Uniform() < prescale) skimFilter = 0;
	}
      }

      if(thePandaFlat.metFilter == 0) continue;
      if(skimFilter == -1) continue;
      N_pass[skimFilter]++;
      normalizedTree->Fill();
    } // end event loop
    normalizedTree->Write();
    outputFile->Close();
    printf("Filter efficiency: %.3f %.3f %.3f = %.3f\n",
          (double)N_pass[0]/nentries/prescale,(double)N_pass[1]/nentries/prescale,(double)N_pass[2]/nentries/prescale,
	  (double)(N_pass[0]+N_pass[1]+N_pass[2])/nentries/prescale);
  } // end samples loop
}
