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

#include "MitAnalysisRunII/panda/macros/10x_g/pandaFlat.C"
#include "MitAnalysisRunII/panda/macros/10x_g/common.h"

void skimmingAnalysis_vbfg(int year, bool specialMC = false)
{

  vector<TString> infileName_;
  TString inpPath;
  TString outPath;
  if     (year == 2018){
  }
  else if(year == 2017) {
    inpPath = "/scratch5/bmaier/darkg/2017/vbfg_v_012_v3/";
    outPath = "/data/t3home000/ceballos/panda/v_vbfg_2017_0/";
  }
  else if(year == 2016) {
  }
  else {
    return;
  }

  if(specialMC == false){
    infileName_.push_back(Form("DarkPhotonVBFHM1000.root"));
    infileName_.push_back(Form("DarkPhotonVBFHM125.root"));
    infileName_.push_back(Form("DarkPhotonVBFHM150.root"));
    infileName_.push_back(Form("DarkPhotonVBFHM200.root"));
    infileName_.push_back(Form("DarkPhotonVBFHM300.root"));
    infileName_.push_back(Form("DarkPhotonVBFHM500.root"));
    infileName_.push_back(Form("DarkPhotonVBFHM800.root"));
    infileName_.push_back(Form("Diboson_ww_CP5.root"));
    infileName_.push_back(Form("Diboson_wz_CP5.root"));
    infileName_.push_back(Form("Diboson_zz_CP5.root"));
    infileName_.push_back(Form("GJets_ht200to400_CP5.root"));
    infileName_.push_back(Form("GJets_ht400to600_CP5.root"));
    infileName_.push_back(Form("GJets_ht600toinf_CP5.root"));
    infileName_.push_back(Form("SingleElectron.root"));
    infileName_.push_back(Form("SingleMuon.root"));
    infileName_.push_back(Form("SinglePhoton.root"));
    infileName_.push_back(Form("SingleTop_tG_CP5.root"));
    infileName_.push_back(Form("TTbar_GJets_CP5.root"));
    infileName_.push_back(Form("WGtoLNuG_lo.root"));
    infileName_.push_back(Form("WGtoLNuG_nlo.root"));
    infileName_.push_back(Form("WJets_EWKWMinus.root"));
    infileName_.push_back(Form("WJets_EWKWPlus.root"));
    infileName_.push_back(Form("WJets_ht100to200_CP5.root"));
    infileName_.push_back(Form("WJets_ht1200to2500_CP5.root"));
    infileName_.push_back(Form("WJets_ht200to400_CP5.root"));
    infileName_.push_back(Form("WJets_ht2500toinf_CP5.root"));
    infileName_.push_back(Form("WJets_ht400to600_CP5.root"));
    infileName_.push_back(Form("WJets_ht600to800_CP5.root"));
    infileName_.push_back(Form("WJets_ht800to1200_CP5.root"));
    infileName_.push_back(Form("WJets_lo_incl_CP5.root"));
    infileName_.push_back(Form("WZG.root"));
    infileName_.push_back(Form("ZGTo2LG_nlo.root"));
    infileName_.push_back(Form("ZJets_EWK.root"));
    infileName_.push_back(Form("ZJets_bQuarks.root"));
    infileName_.push_back(Form("ZJets_ht100to200_CP5.root"));
    infileName_.push_back(Form("ZJets_ht1200to2500_CP5.root"));
    infileName_.push_back(Form("ZJets_ht200to400_CP5.root"));
    infileName_.push_back(Form("ZJets_ht2500toinf_CP5.root"));
    infileName_.push_back(Form("ZJets_ht400to600_CP5.root"));
    infileName_.push_back(Form("ZJets_ht600to800_CP5.root"));
    infileName_.push_back(Form("ZJets_ht800to1200_CP5.root"));
    infileName_.push_back(Form("ZJets_inclNLO_CP5.root"));
    infileName_.push_back(Form("ZJets_lo_CP5.root"));
    infileName_.push_back(Form("ZJets_m4_ht100to200_CP5.root"));
    infileName_.push_back(Form("ZJets_m4_ht200to400_CP5.root"));
    infileName_.push_back(Form("ZJets_m4_ht400to600_CP5.root"));
    infileName_.push_back(Form("ZJets_m4_ht600toinf_CP5.root"));
    infileName_.push_back(Form("ZJets_m4_ht70to100_CP5.root"));
    infileName_.push_back(Form("ZtoNuNu_EWK.root"));
    infileName_.push_back(Form("MET.root"));
  }

  for(UInt_t ifile=0; ifile<infileName_.size(); ifile++) {
    printf("sampleNames(%d): %s\n",ifile,infileName_[ifile].Data());
    TFile *the_input_file = TFile::Open(Form("%s%s",inpPath.Data(),infileName_[ifile].Data()));
    if(!the_input_file) continue;
    TTree *the_input_tree = (TTree*)the_input_file->FindObjectAny("events");
    
    TFile *outputFile = new TFile(Form("%s%s",outPath.Data(),infileName_[ifile].Data()), "RECREATE");
    outputFile->cd();
    outputFile->SaveSelf(kTRUE);
    TTree *normalizedTree = the_input_tree->CloneTree(0);

    UInt_t N_pass[2] = {0, 0};
    pandaFlat thePandaFlat(the_input_tree);
    Long64_t nentries = thePandaFlat.fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = thePandaFlat.LoadTree(jentry);
      if (ientry < 0) break;
      nb = thePandaFlat.fChain->GetEntry(jentry);   nbytes += nb;
      if (jentry%1000000 == 0) printf("--- reading event %8lld (%8lld) of %8lld\n",jentry,ientry,nentries);

      int skimFilter = -1;
      TLorentzVector vFakePhoton,vPhoton,vPhotonUp,vPhotonDown;
      bool passPhoSel = TMath::Abs(thePandaFlat.loosePho1Eta) < 2.5 && thePandaFlat.loosePho1Pt > 80;
      if     (passPhoSel == true) {
        skimFilter = 0;
      }
      else if(thePandaFlat.nLooseLep >= 1) {
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
        if(looseLepPt[0] > 80) skimFilter = 1;
      }

      if(skimFilter == -1) continue;
      N_pass[skimFilter]++;
      normalizedTree->Fill();
    } // end event loop
    normalizedTree->Write();
    outputFile->Close();
    printf("Filter efficiency: %.3f %.3f = %.3f\n",
          (double)N_pass[0]/nentries,(double)N_pass[1]/nentries,
	  (double)(N_pass[0]+N_pass[1])/nentries);
  } // end samples loop
}
