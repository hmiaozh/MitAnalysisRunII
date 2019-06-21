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
#include "MitAnalysisRunII/panda/macros/9x/applyCorrections.h"

void skimmingAnalysis(int year, bool specialMC = false)
{

  vector<TString> infileName_;
  TString inpPath;
  TString outPath;
  if     (year == 2018){
    inpPath = "/data/t3home000/ceballos/panda/v_006_0/";
    outPath = "/data/t3home000/ceballos/panda/v_006_1/";
  }
  else if(year == 2017) {
    inpPath = "/data/t3home000/ceballos/panda/v_004_0/";
    outPath = "/data/t3home000/ceballos/panda/v_004_1/";
  }
  else if(year == 2016) {
    inpPath = "/data/t3home000/ceballos/panda/v_002_0/";
    outPath = "/data/t3home000/ceballos/panda/v_002_1/";
  }
  else {
    return;
  }

  if(specialMC == false){
    infileName_.push_back(Form("Unpart_ZToLL_SU-0_dU-1p01.root"));
    infileName_.push_back(Form("Unpart_ZToLL_SU-0_dU-1p02.root"));
    infileName_.push_back(Form("Unpart_ZToLL_SU-0_dU-1p04.root"));
    infileName_.push_back(Form("Unpart_ZToLL_SU-0_dU-1p06.root"));
    infileName_.push_back(Form("Unpart_ZToLL_SU-0_dU-1p09.root"));
    infileName_.push_back(Form("Unpart_ZToLL_SU-0_dU-1p10.root"));
    infileName_.push_back(Form("Unpart_ZToLL_SU-0_dU-1p20.root"));
    infileName_.push_back(Form("Unpart_ZToLL_SU-0_dU-1p30.root"));
    infileName_.push_back(Form("Unpart_ZToLL_SU-0_dU-1p40.root"));
    infileName_.push_back(Form("Unpart_ZToLL_SU-0_dU-1p50.root"));
    infileName_.push_back(Form("Unpart_ZToLL_SU-0_dU-1p60.root"));
    infileName_.push_back(Form("Unpart_ZToLL_SU-0_dU-1p70.root"));
    infileName_.push_back(Form("Unpart_ZToLL_SU-0_dU-1p80.root"));
    infileName_.push_back(Form("Unpart_ZToLL_SU-0_dU-1p90.root"));
    infileName_.push_back(Form("Unpart_ZToLL_SU-0_dU-2p00.root"));
    infileName_.push_back(Form("Unpart_ZToLL_SU-0_dU-2p20.root"));
    infileName_.push_back(Form("ADDMonoZ_MD_1_d_2.root"));
    infileName_.push_back(Form("ADDMonoZ_MD_1_d_3.root"));
    infileName_.push_back(Form("ADDMonoZ_MD_1_d_4.root"));
    infileName_.push_back(Form("ADDMonoZ_MD_1_d_5.root"));
    infileName_.push_back(Form("ADDMonoZ_MD_1_d_6.root"));
    infileName_.push_back(Form("ADDMonoZ_MD_1_d_7.root"));
    infileName_.push_back(Form("ADDMonoZ_MD_2_d_2.root"));
    infileName_.push_back(Form("ADDMonoZ_MD_2_d_3.root"));
    infileName_.push_back(Form("ADDMonoZ_MD_2_d_4.root"));
    infileName_.push_back(Form("ADDMonoZ_MD_2_d_5.root"));
    infileName_.push_back(Form("ADDMonoZ_MD_2_d_6.root"));
    infileName_.push_back(Form("ADDMonoZ_MD_2_d_7.root"));
    infileName_.push_back(Form("ADDMonoZ_MD_3_d_2.root"));
    infileName_.push_back(Form("ADDMonoZ_MD_3_d_3.root"));
    infileName_.push_back(Form("ADDMonoZ_MD_3_d_4.root"));
    infileName_.push_back(Form("ADDMonoZ_MD_3_d_5.root"));
    infileName_.push_back(Form("ADDMonoZ_MD_3_d_6.root"));
    infileName_.push_back(Form("ADDMonoZ_MD_3_d_7.root"));
    infileName_.push_back(Form("DYJetsToLL_M-10to50.root"));
    infileName_.push_back(Form("DYJetsToLL_M-50_LO.root"));
    infileName_.push_back(Form("DYJetsToLL_M-50_NLO.root"));
    infileName_.push_back(Form("DYJetsToLL_Pt0To50.root"));
    infileName_.push_back(Form("DYJetsToLL_Pt100To250.root"));
    infileName_.push_back(Form("DYJetsToLL_Pt250To400.root"));
    infileName_.push_back(Form("DYJetsToLL_Pt400To650.root"));
    infileName_.push_back(Form("DYJetsToLL_Pt50To100.root"));
    infileName_.push_back(Form("DYJetsToLL_Pt650ToInf.root"));
    infileName_.push_back(Form("DYJetsToTauTau.root"));
    infileName_.push_back(Form("DYNJetsToLL.root"));
    infileName_.push_back(Form("DYNJetsToLL_NLO.root"));
    infileName_.push_back(Form("H125.root"));
    infileName_.push_back(Form("TT.root"));
    infileName_.push_back(Form("TT2L.root"));
    infileName_.push_back(Form("TTV.root"));
    infileName_.push_back(Form("TTVV.root"));
    infileName_.push_back(Form("TW.root"));
    infileName_.push_back(Form("TWlx.root"));
    infileName_.push_back(Form("VG.root"));
    infileName_.push_back(Form("VG_M120.root"));
    infileName_.push_back(Form("VVV.root"));
    infileName_.push_back(Form("WGstar.root"));
    infileName_.push_back(Form("WJets.root"));
    infileName_.push_back(Form("WWdps.root"));
    infileName_.push_back(Form("WZ.root"));
    infileName_.push_back(Form("WZ3l_MG_EWK.root"));
    infileName_.push_back(Form("WZ3l_MG_QCD.root"));
    infileName_.push_back(Form("WZ3l_amcnlo.root"));
    infileName_.push_back(Form("WZ3l_powheg.root"));
    infileName_.push_back(Form("WZ3l_powheg_mll1.root"));
    infileName_.push_back(Form("WZno3l.root"));
    infileName_.push_back(Form("WpWp_EWK.root"));
    infileName_.push_back(Form("WpWp_EWK_QCD.root"));
    infileName_.push_back(Form("WpWp_QCD.root"));
    infileName_.push_back(Form("ZZJJ.root"));
    infileName_.push_back(Form("data.root"));
    infileName_.push_back(Form("ggWW.root"));
    infileName_.push_back(Form("ggZZ.root"));
    infileName_.push_back(Form("qqWW.root"));
    infileName_.push_back(Form("qqZZ.root"));
    infileName_.push_back(Form("ggZH125inv.root"));
    infileName_.push_back(Form("qqZH110inv.root"));
    infileName_.push_back(Form("qqZH125inv.root"));
    infileName_.push_back(Form("qqZH150inv.root"));
    infileName_.push_back(Form("qqZH200inv.root"));
    infileName_.push_back(Form("qqZH300inv.root"));
    infileName_.push_back(Form("qqZH400inv.root"));
    infileName_.push_back(Form("qqZH500inv.root"));
    infileName_.push_back(Form("qqZH600inv.root"));
    infileName_.push_back(Form("qqZH800inv.root"));
    infileName_.push_back(Form("qqZH1000inv.root"));
  } else {
    infileName_.push_back(Form("ZH_ZToLL_HToGDarkG_M125.root"));
    infileName_.push_back(Form("ZH_ZToLL_HToGDarkG_M200.root"));
    infileName_.push_back(Form("ZH_ZToLL_HToGDarkG_M300.root"));
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
      if     (thePandaFlat.nLooseLep < 1) {
        skimFilter = -1;
      }
      else if(thePandaFlat.nLooseLep >= 3) {
        skimFilter = 0;
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
        if(looseLepPdgId[0] * looseLepPdgId[1] > 0) skimFilter = 1;
	// only not selected events yet
	if(skimFilter == -1){
          TLorentzVector dilep;
          for(int i=0; i<thePandaFlat.nLooseLep; i++) {
            double thePDGMass = mass_mu;
            if(abs(looseLepPdgId[i])==11) thePDGMass = mass_el;
	    TLorentzVector vLepTemp; vLepTemp.SetPtEtaPhiM(looseLepPt[i],looseLepEta[i],looseLepPhi[i],thePDGMass);
            dilep = dilep + vLepTemp;
          }
          TLorentzVector vMet,vMetUp,vMetDown;
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
          if(dilep.Pt() > 60 && (vMet.Pt() > 70 || vMetUp.Pt() > 70 ||vMetDown.Pt() > 70) && (thePandaFlat.nLooseLep != 2 || TMath::Abs(dilep.M()-125) < 75)) skimFilter = 2;
	}
      }

      if(skimFilter == -1) continue;
      N_pass[skimFilter]++;
      normalizedTree->Fill();
    } // end event loop
    normalizedTree->Write();
    outputFile->Close();
    printf("Filter efficiency: %.3f %.3f %.3f = %.3f\n",
          (double)N_pass[0]/nentries,(double)N_pass[1]/nentries,(double)N_pass[2]/nentries,
	  (double)(N_pass[0]+N_pass[1]+N_pass[2])/nentries);
  } // end samples loop
}
