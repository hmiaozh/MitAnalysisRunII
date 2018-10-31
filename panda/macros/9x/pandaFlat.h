//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Oct 22 12:52:12 2018 by ROOT version 6.10/09
// from TTree events/events
// found on file: /data/t3home000/ceballos/panda/v_004_0/qqZZ.root
//////////////////////////////////////////////////////////

#ifndef pandaFlat_h
#define pandaFlat_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class pandaFlat {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         sf_btag0;
   Float_t         sf_btag1;
   Float_t         sf_btag2;
   Float_t         sf_btagGT0;
   Float_t         sf_btag0BUp;
   Float_t         sf_btag1BUp;
   Float_t         sf_btag2BUp;
   Float_t         sf_btagGT0BUp;
   Float_t         sf_btag0BDown;
   Float_t         sf_btag1BDown;
   Float_t         sf_btag2BDown;
   Float_t         sf_btagGT0BDown;
   Float_t         sf_btag0MUp;
   Float_t         sf_btag1MUp;
   Float_t         sf_btag2MUp;
   Float_t         sf_btagGT0MUp;
   Float_t         sf_btag0MDown;
   Float_t         sf_btag1MDown;
   Float_t         sf_btag2MDown;
   Float_t         sf_btagGT0MDown;
   Int_t           runNumber;
   Int_t           lumiNumber;
   ULong64_t       eventNumber;
   Int_t           isData;
   Int_t           npv;
   Int_t           pu;
   Float_t         rho;
   Float_t         mcWeight;
   Int_t           trigger;
   Int_t           metFilter;
   Int_t           egmFilter;
   Float_t         filter_maxRecoil;
   Int_t           filter_whichRecoil;
   Int_t           badECALFilter;
   Float_t         sf_ewkV;
   Float_t         sf_qcdV;
   Float_t         sf_ewkV2j;
   Float_t         sf_qcdV2j;
   Float_t         sf_qcdV_VBF;
   Float_t         sf_qcdV_VBF2l;
   Float_t         sf_qcdV_VBFTight;
   Float_t         sf_qcdV_VBF2lTight;
   Float_t         sf_qcdTT;
   Float_t         sf_lepID;
   Float_t         sf_lepIso;
   Float_t         sf_lepTrack;
   Float_t         sf_pho;
   Float_t         sf_eleTrig;
   Float_t         sf_muTrig;
   Float_t         sf_phoTrig;
   Float_t         sf_metTrig;
   Float_t         sf_metTrigZmm;
   Float_t         sf_metTrigVBF;
   Float_t         sf_metTrigZmmVBF;
   Float_t         sf_l1Prefire;
   Float_t         sf_pu;
   Float_t         sf_npv;
   Float_t         sf_tt;
   Float_t         sf_phoPurity;
   Float_t         sumETRaw;
   Float_t         pfmetRaw;
   Float_t         pfmet;
   Float_t         pfmet_JESTotalUp;
   Float_t         pfmet_JESTotalDown;
   Float_t         pfmetphi;
   Float_t         pfmetphi_JESTotalUp;
   Float_t         pfmetphi_JESTotalDown;
   Float_t         pfmetnomu;
   Float_t         pfmetnomu_JESTotalUp;
   Float_t         pfmetnomu_JESTotalDown;
   Float_t         puppimet;
   Float_t         puppimet_JESTotalUp;
   Float_t         puppimet_JESTotalDown;
   Float_t         puppimetphi;
   Float_t         puppimetphi_JESTotalUp;
   Float_t         puppimetphi_JESTotalDown;
   Float_t         calomet;
   Float_t         calometphi;
   Float_t         pfcalobalance;
   Float_t         sumET;
   Float_t         trkmet;
   Float_t         trkmetphi;
   Float_t         trkmetDZ;
   Float_t         trkmetDZphi;
   Int_t           whichRecoil;
   Float_t         dphipfmet;
   Float_t         dphipfmet_JESTotalUp;
   Float_t         dphipfmet_JESTotalDown;
   Float_t         trueGenBosonPt;
   Float_t         genBosonPt;
   Float_t         genBosonEta;
   Float_t         genBosonMass;
   Float_t         genBosonPhi;
   Float_t         genJet1Pt;
   Float_t         genJet2Pt;
   Float_t         genJet1Eta;
   Float_t         genJet2Eta;
   Int_t           nJet;
   Int_t           nJot;
   Int_t           nJot_JESTotalUp;
   Int_t           nJot_JESTotalDown;
   Int_t           nJotMax;
   Float_t         jotPt[2];
   Float_t         jotPt_JESTotalUp[2];
   Float_t         jotPt_JESTotalDown[2];
   Float_t         jotEta[2];
   Float_t         jotPhi[2];
   Float_t         jotCSV[2];
   Int_t           jotVBFID[2];
   Float_t         barrelJet1Pt;
   Float_t         barrelJet1Eta;
   Float_t         barrelHT;
   Float_t         barrelHTMiss;
   Float_t         barrelJet12Pt;
   Float_t         jot12Mass;
   Float_t         jot12Mass_JESTotalUp;
   Float_t         jot12Mass_JESTotalDown;
   Float_t         jot12DEta;
   Float_t         jot12DEta_JESTotalUp;
   Float_t         jot12DEta_JESTotalDown;
   Float_t         jot12DPhi;
   Float_t         jot12DPhi_JESTotalUp;
   Float_t         jot12DPhi_JESTotalDown;
   Int_t           jetNBtags;
   Int_t           jetNBtags_JESTotalUp;
   Int_t           jetNBtags_JESTotalDown;
   Int_t           jetNMBtags;
   Int_t           jetNMBtags_JESTotalUp;
   Int_t           jetNMBtags_JESTotalDown;
   Int_t           nHF;
   Int_t           nB;
   Int_t           nBGenJets;
   Int_t           nStatus2BHadrons;
   Float_t         genFatJetPt;
   Int_t           genFatJetNProngs;
   Int_t           nLoosePhoton;
   Int_t           nTightPhoton;
   Int_t           loosePho1IsTight;
   Float_t         loosePho1Pt;
   Float_t         loosePho1Eta;
   Float_t         loosePho1Phi;
   Int_t           loosePho1SelBit;
   Int_t           looseGenPho1PdgId;
   Int_t           nLooseLep;
   Int_t           nLooseElectron;
   Int_t           nLooseMuon;
   Int_t           nTightLep;
   Int_t           nTightElectron;
   Int_t           nTightMuon;
   Float_t         electronPt[4];   //[nLooseElectron]
   Float_t         electronEta[4];   //[nLooseElectron]
   Float_t         electronPhi[4];   //[nLooseElectron]
   Int_t           electronSelBit[4];   //[nLooseElectron]
   Int_t           electronPdgId[4];   //[nLooseElectron]
   Float_t         muonPt[4];   //[nLooseMuon]
   Float_t         muonEta[4];   //[nLooseMuon]
   Float_t         muonPhi[4];   //[nLooseMuon]
   Int_t           muonSelBit[4];   //[nLooseMuon]
   Int_t           muonPdgId[4];   //[nLooseMuon]
   Float_t         sf_zz;
   Float_t         sf_zzUnc;
   Float_t         sf_wz;
   Float_t         sf_vh;
   Float_t         sf_vhUp;
   Float_t         sf_vhDown;
   Float_t         diLepMass;
   Int_t           nTau;
   Float_t         mT;
   Float_t         mT_JESTotalUp;
   Float_t         mT_JESTotalDown;
   Float_t         scaleUp;
   Float_t         scaleDown;
   Float_t         pdfUp;
   Float_t         pdfDown;
   Float_t         scale[6];
   Float_t         lheHT;
   Int_t           isGS;
   Float_t         genMjj;
   Float_t         electronSfLoose[4];   //[nLooseElectron]
   Float_t         electronSfMedium[4];   //[nLooseElectron]
   Float_t         electronSfTight[4];   //[nLooseElectron]
   Float_t         electronSfMvaWP90[4];   //[nLooseElectron]
   Float_t         electronSfMvaWP80[4];   //[nLooseElectron]
   Float_t         electronSfUnc[4];   //[nLooseElectron]
   Float_t         electronSfReco[4];   //[nLooseElectron]
   Float_t         electronD0[4];   //[nLooseElectron]
   Float_t         electronDZ[4];   //[nLooseElectron]
   Int_t           electronNMissingHits[4];   //[nLooseElectron]
   Int_t           electronTripleCharge[4];   //[nLooseElectron]
   Float_t         electronCombIso[4];   //[nLooseElectron]
   Float_t         muonSfLoose[4];   //[nLooseMuon]
   Float_t         muonSfMedium[4];   //[nLooseMuon]
   Float_t         muonSfTight[4];   //[nLooseMuon]
   Float_t         muonSfUnc[4];   //[nLooseMuon]
   Float_t         muonSfReco[4];   //[nLooseMuon]
   Float_t         muonD0[4];   //[nLooseMuon]
   Float_t         muonDZ[4];   //[nLooseMuon]
   Int_t           muonIsSoftMuon[4];   //[nLooseMuon]
   Float_t         muonCombIso[4];   //[nLooseMuon]
   Float_t         genLep1Pt;
   Float_t         genLep1Eta;
   Float_t         genLep1Phi;
   Int_t           genLep1PdgId;
   Float_t         genLep2Pt;
   Float_t         genLep2Eta;
   Float_t         genLep2Phi;
   Int_t           genLep2PdgId;
   Float_t         genLep3Pt;
   Float_t         genLep3Eta;
   Float_t         genLep3Phi;
   Int_t           genLep3PdgId;
   Float_t         genLep4Pt;
   Float_t         genLep4Eta;
   Float_t         genLep4Phi;
   Int_t           genLep4PdgId;
   Float_t         genWPlusPt;
   Float_t         genWMinusPt;
   Float_t         genWPlusEta;
   Float_t         genWMinusEta;
   Int_t           looseGenLep1PdgId;
   Int_t           looseGenLep2PdgId;
   Int_t           looseGenLep3PdgId;
   Int_t           looseGenLep4PdgId;
   Float_t         normalizedWeight;

   // List of branches
   TBranch        *b_sf_btag0;   //!
   TBranch        *b_sf_btag1;   //!
   TBranch        *b_sf_btag2;   //!
   TBranch        *b_sf_btagGT0;   //!
   TBranch        *b_sf_btag0BUp;   //!
   TBranch        *b_sf_btag1BUp;   //!
   TBranch        *b_sf_btag2BUp;   //!
   TBranch        *b_sf_btagGT0BUp;   //!
   TBranch        *b_sf_btag0BDown;   //!
   TBranch        *b_sf_btag1BDown;   //!
   TBranch        *b_sf_btag2BDown;   //!
   TBranch        *b_sf_btagGT0BDown;   //!
   TBranch        *b_sf_btag0MUp;   //!
   TBranch        *b_sf_btag1MUp;   //!
   TBranch        *b_sf_btag2MUp;   //!
   TBranch        *b_sf_btagGT0MUp;   //!
   TBranch        *b_sf_btag0MDown;   //!
   TBranch        *b_sf_btag1MDown;   //!
   TBranch        *b_sf_btag2MDown;   //!
   TBranch        *b_sf_btagGT0MDown;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_lumiNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_isData;   //!
   TBranch        *b_npv;   //!
   TBranch        *b_pu;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_mcWeight;   //!
   TBranch        *b_trigger;   //!
   TBranch        *b_metFilter;   //!
   TBranch        *b_egmFilter;   //!
   TBranch        *b_filter_maxRecoil;   //!
   TBranch        *b_filter_whichRecoil;   //!
   TBranch        *b_badECALFilter;   //!
   TBranch        *b_sf_ewkV;   //!
   TBranch        *b_sf_qcdV;   //!
   TBranch        *b_sf_ewkV2j;   //!
   TBranch        *b_sf_qcdV2j;   //!
   TBranch        *b_sf_qcdV_VBF;   //!
   TBranch        *b_sf_qcdV_VBF2l;   //!
   TBranch        *b_sf_qcdV_VBFTight;   //!
   TBranch        *b_sf_qcdV_VBF2lTight;   //!
   TBranch        *b_sf_qcdTT;   //!
   TBranch        *b_sf_lepID;   //!
   TBranch        *b_sf_lepIso;   //!
   TBranch        *b_sf_lepTrack;   //!
   TBranch        *b_sf_pho;   //!
   TBranch        *b_sf_eleTrig;   //!
   TBranch        *b_sf_muTrig;   //!
   TBranch        *b_sf_phoTrig;   //!
   TBranch        *b_sf_metTrig;   //!
   TBranch        *b_sf_metTrigZmm;   //!
   TBranch        *b_sf_metTrigVBF;   //!
   TBranch        *b_sf_metTrigZmmVBF;   //!
   TBranch        *b_sf_l1Prefire;   //!
   TBranch        *b_sf_pu;   //!
   TBranch        *b_sf_npv;   //!
   TBranch        *b_sf_tt;   //!
   TBranch        *b_sf_phoPurity;   //!
   TBranch        *b_sumETRaw;   //!
   TBranch        *b_pfmetRaw;   //!
   TBranch        *b_pfmet;   //!
   TBranch        *b_pfmet_JESTotalUp;   //!
   TBranch        *b_pfmet_JESTotalDown;   //!
   TBranch        *b_pfmetphi;   //!
   TBranch        *b_pfmetphi_JESTotalUp;   //!
   TBranch        *b_pfmetphi_JESTotalDown;   //!
   TBranch        *b_pfmetnomu;   //!
   TBranch        *b_pfmetnomu_JESTotalUp;   //!
   TBranch        *b_pfmetnomu_JESTotalDown;   //!
   TBranch        *b_puppimet;   //!
   TBranch        *b_puppimet_JESTotalUp;   //!
   TBranch        *b_puppimet_JESTotalDown;   //!
   TBranch        *b_puppimetphi;   //!
   TBranch        *b_puppimetphi_JESTotalUp;   //!
   TBranch        *b_puppimetphi_JESTotalDown;   //!
   TBranch        *b_calomet;   //!
   TBranch        *b_calometphi;   //!
   TBranch        *b_pfcalobalance;   //!
   TBranch        *b_sumET;   //!
   TBranch        *b_trkmet;   //!
   TBranch        *b_trkmetphi;   //!
   TBranch        *b_trkmetDZ;   //!
   TBranch        *b_trkmetDZphi;   //!
   TBranch        *b_whichRecoil;   //!
   TBranch        *b_dphipfmet;   //!
   TBranch        *b_dphipfmet_JESTotalUp;   //!
   TBranch        *b_dphipfmet_JESTotalDown;   //!
   TBranch        *b_trueGenBosonPt;   //!
   TBranch        *b_genBosonPt;   //!
   TBranch        *b_genBosonEta;   //!
   TBranch        *b_genBosonMass;   //!
   TBranch        *b_genBosonPhi;   //!
   TBranch        *b_genJet1Pt;   //!
   TBranch        *b_genJet2Pt;   //!
   TBranch        *b_genJet1Eta;   //!
   TBranch        *b_genJet2Eta;   //!
   TBranch        *b_nJet;   //!
   TBranch        *b_nJot;   //!
   TBranch        *b_nJot_JESTotalUp;   //!
   TBranch        *b_nJot_JESTotalDown;   //!
   TBranch        *b_nJotMax;   //!
   TBranch        *b_jotPt;   //!
   TBranch        *b_jotPt_JESTotalUp;   //!
   TBranch        *b_jotPt_JESTotalDown;   //!
   TBranch        *b_jotEta;   //!
   TBranch        *b_jotPhi;   //!
   TBranch        *b_jotCSV;   //!
   TBranch        *b_jotVBFID;   //!
   TBranch        *b_barrelJet1Pt;   //!
   TBranch        *b_barrelJet1Eta;   //!
   TBranch        *b_barrelHT;   //!
   TBranch        *b_barrelHTMiss;   //!
   TBranch        *b_barrelJet12Pt;   //!
   TBranch        *b_jot12Mass;   //!
   TBranch        *b_jot12Mass_JESTotalUp;   //!
   TBranch        *b_jot12Mass_JESTotalDown;   //!
   TBranch        *b_jot12DEta;   //!
   TBranch        *b_jot12DEta_JESTotalUp;   //!
   TBranch        *b_jot12DEta_JESTotalDown;   //!
   TBranch        *b_jot12DPhi;   //!
   TBranch        *b_jot12DPhi_JESTotalUp;   //!
   TBranch        *b_jot12DPhi_JESTotalDown;   //!
   TBranch        *b_jetNBtags;   //!
   TBranch        *b_jetNBtags_JESTotalUp;   //!
   TBranch        *b_jetNBtags_JESTotalDown;   //!
   TBranch        *b_jetNMBtags;   //!
   TBranch        *b_jetNMBtags_JESTotalUp;   //!
   TBranch        *b_jetNMBtags_JESTotalDown;   //!
   TBranch        *b_nHF;   //!
   TBranch        *b_nB;   //!
   TBranch        *b_nBGenJets;   //!
   TBranch        *b_nStatus2BHadrons;   //!
   TBranch        *b_genFatJetPt;   //!
   TBranch        *b_genFatJetNProngs;   //!
   TBranch        *b_nLoosePhoton;   //!
   TBranch        *b_nTightPhoton;   //!
   TBranch        *b_loosePho1IsTight;   //!
   TBranch        *b_loosePho1Pt;   //!
   TBranch        *b_loosePho1Eta;   //!
   TBranch        *b_loosePho1Phi;   //!
   TBranch        *b_loosePho1SelBit;   //!
   TBranch        *b_looseGenPho1PdgId;   //!
   TBranch        *b_nLooseLep;   //!
   TBranch        *b_nLooseElectron;   //!
   TBranch        *b_nLooseMuon;   //!
   TBranch        *b_nTightLep;   //!
   TBranch        *b_nTightElectron;   //!
   TBranch        *b_nTightMuon;   //!
   TBranch        *b_electronPt;   //!
   TBranch        *b_electronEta;   //!
   TBranch        *b_electronPhi;   //!
   TBranch        *b_electronSelBit;   //!
   TBranch        *b_electronPdgId;   //!
   TBranch        *b_muonPt;   //!
   TBranch        *b_muonEta;   //!
   TBranch        *b_muonPhi;   //!
   TBranch        *b_muonSelBit;   //!
   TBranch        *b_muonPdgId;   //!
   TBranch        *b_sf_zz;   //!
   TBranch        *b_sf_zzUnc;   //!
   TBranch        *b_sf_wz;   //!
   TBranch        *b_sf_vh;   //!
   TBranch        *b_sf_vhUp;   //!
   TBranch        *b_sf_vhDown;   //!
   TBranch        *b_diLepMass;   //!
   TBranch        *b_nTau;   //!
   TBranch        *b_mT;   //!
   TBranch        *b_mT_JESTotalUp;   //!
   TBranch        *b_mT_JESTotalDown;   //!
   TBranch        *b_scaleUp;   //!
   TBranch        *b_scaleDown;   //!
   TBranch        *b_pdfUp;   //!
   TBranch        *b_pdfDown;   //!
   TBranch        *b_scale;   //!
   TBranch        *b_lheHT;   //!
   TBranch        *b_isGS;   //!
   TBranch        *b_genMjj;   //!
   TBranch        *b_electronSfLoose;   //!
   TBranch        *b_electronSfMedium;   //!
   TBranch        *b_electronSfTight;   //!
   TBranch        *b_electronSfMvaWP90;   //!
   TBranch        *b_electronSfMvaWP80;   //!
   TBranch        *b_electronSfUnc;   //!
   TBranch        *b_electronSfReco;   //!
   TBranch        *b_electronD0;   //!
   TBranch        *b_electronDZ;   //!
   TBranch        *b_electronNMissingHits;   //!
   TBranch        *b_electronTripleCharge;   //!
   TBranch        *b_electronCombIso;   //!
   TBranch        *b_muonSfLoose;   //!
   TBranch        *b_muonSfMedium;   //!
   TBranch        *b_muonSfTight;   //!
   TBranch        *b_muonSfUnc;   //!
   TBranch        *b_muonSfReco;   //!
   TBranch        *b_muonD0;   //!
   TBranch        *b_muonDZ;   //!
   TBranch        *b_muonIsSoftMuon;   //!
   TBranch        *b_muonCombIso;   //!
   TBranch        *b_genLep1Pt;   //!
   TBranch        *b_genLep1Eta;   //!
   TBranch        *b_genLep1Phi;   //!
   TBranch        *b_genLep1PdgId;   //!
   TBranch        *b_genLep2Pt;   //!
   TBranch        *b_genLep2Eta;   //!
   TBranch        *b_genLep2Phi;   //!
   TBranch        *b_genLep2PdgId;   //!
   TBranch        *b_genLep3Pt;   //!
   TBranch        *b_genLep3Eta;   //!
   TBranch        *b_genLep3Phi;   //!
   TBranch        *b_genLep3PdgId;   //!
   TBranch        *b_genLep4Pt;   //!
   TBranch        *b_genLep4Eta;   //!
   TBranch        *b_genLep4Phi;   //!
   TBranch        *b_genLep4PdgId;   //!
   TBranch        *b_genWPlusPt;   //!
   TBranch        *b_genWMinusPt;   //!
   TBranch        *b_genWPlusEta;   //!
   TBranch        *b_genWMinusEta;   //!
   TBranch        *b_looseGenLep1PdgId;   //!
   TBranch        *b_looseGenLep2PdgId;   //!
   TBranch        *b_looseGenLep3PdgId;   //!
   TBranch        *b_looseGenLep4PdgId;   //!
   TBranch        *b_normalizedWeight;   //!

   pandaFlat(TTree *tree=0);
   virtual ~pandaFlat();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef pandaFlat_cxx
pandaFlat::pandaFlat(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/data/t3home000/ceballos/panda/v_004_0/qqZZ.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/data/t3home000/ceballos/panda/v_004_0/qqZZ.root");
      }
      f->GetObject("events",tree);

   }
   Init(tree);
}

pandaFlat::~pandaFlat()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t pandaFlat::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t pandaFlat::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void pandaFlat::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("sf_btag0", &sf_btag0, &b_sf_btag0);
   fChain->SetBranchAddress("sf_btag1", &sf_btag1, &b_sf_btag1);
   fChain->SetBranchAddress("sf_btag2", &sf_btag2, &b_sf_btag2);
   fChain->SetBranchAddress("sf_btagGT0", &sf_btagGT0, &b_sf_btagGT0);
   fChain->SetBranchAddress("sf_btag0BUp", &sf_btag0BUp, &b_sf_btag0BUp);
   fChain->SetBranchAddress("sf_btag1BUp", &sf_btag1BUp, &b_sf_btag1BUp);
   fChain->SetBranchAddress("sf_btag2BUp", &sf_btag2BUp, &b_sf_btag2BUp);
   fChain->SetBranchAddress("sf_btagGT0BUp", &sf_btagGT0BUp, &b_sf_btagGT0BUp);
   fChain->SetBranchAddress("sf_btag0BDown", &sf_btag0BDown, &b_sf_btag0BDown);
   fChain->SetBranchAddress("sf_btag1BDown", &sf_btag1BDown, &b_sf_btag1BDown);
   fChain->SetBranchAddress("sf_btag2BDown", &sf_btag2BDown, &b_sf_btag2BDown);
   fChain->SetBranchAddress("sf_btagGT0BDown", &sf_btagGT0BDown, &b_sf_btagGT0BDown);
   fChain->SetBranchAddress("sf_btag0MUp", &sf_btag0MUp, &b_sf_btag0MUp);
   fChain->SetBranchAddress("sf_btag1MUp", &sf_btag1MUp, &b_sf_btag1MUp);
   fChain->SetBranchAddress("sf_btag2MUp", &sf_btag2MUp, &b_sf_btag2MUp);
   fChain->SetBranchAddress("sf_btagGT0MUp", &sf_btagGT0MUp, &b_sf_btagGT0MUp);
   fChain->SetBranchAddress("sf_btag0MDown", &sf_btag0MDown, &b_sf_btag0MDown);
   fChain->SetBranchAddress("sf_btag1MDown", &sf_btag1MDown, &b_sf_btag1MDown);
   fChain->SetBranchAddress("sf_btag2MDown", &sf_btag2MDown, &b_sf_btag2MDown);
   fChain->SetBranchAddress("sf_btagGT0MDown", &sf_btagGT0MDown, &b_sf_btagGT0MDown);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("lumiNumber", &lumiNumber, &b_lumiNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("isData", &isData, &b_isData);
   fChain->SetBranchAddress("npv", &npv, &b_npv);
   fChain->SetBranchAddress("pu", &pu, &b_pu);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("mcWeight", &mcWeight, &b_mcWeight);
   fChain->SetBranchAddress("trigger", &trigger, &b_trigger);
   fChain->SetBranchAddress("metFilter", &metFilter, &b_metFilter);
   fChain->SetBranchAddress("egmFilter", &egmFilter, &b_egmFilter);
   fChain->SetBranchAddress("filter_maxRecoil", &filter_maxRecoil, &b_filter_maxRecoil);
   fChain->SetBranchAddress("filter_whichRecoil", &filter_whichRecoil, &b_filter_whichRecoil);
   fChain->SetBranchAddress("badECALFilter", &badECALFilter, &b_badECALFilter);
   fChain->SetBranchAddress("sf_ewkV", &sf_ewkV, &b_sf_ewkV);
   fChain->SetBranchAddress("sf_qcdV", &sf_qcdV, &b_sf_qcdV);
   fChain->SetBranchAddress("sf_ewkV2j", &sf_ewkV2j, &b_sf_ewkV2j);
   fChain->SetBranchAddress("sf_qcdV2j", &sf_qcdV2j, &b_sf_qcdV2j);
   fChain->SetBranchAddress("sf_qcdV_VBF", &sf_qcdV_VBF, &b_sf_qcdV_VBF);
   fChain->SetBranchAddress("sf_qcdV_VBF2l", &sf_qcdV_VBF2l, &b_sf_qcdV_VBF2l);
   fChain->SetBranchAddress("sf_qcdV_VBFTight", &sf_qcdV_VBFTight, &b_sf_qcdV_VBFTight);
   fChain->SetBranchAddress("sf_qcdV_VBF2lTight", &sf_qcdV_VBF2lTight, &b_sf_qcdV_VBF2lTight);
   fChain->SetBranchAddress("sf_qcdTT", &sf_qcdTT, &b_sf_qcdTT);
   fChain->SetBranchAddress("sf_lepID", &sf_lepID, &b_sf_lepID);
   fChain->SetBranchAddress("sf_lepIso", &sf_lepIso, &b_sf_lepIso);
   fChain->SetBranchAddress("sf_lepTrack", &sf_lepTrack, &b_sf_lepTrack);
   fChain->SetBranchAddress("sf_pho", &sf_pho, &b_sf_pho);
   fChain->SetBranchAddress("sf_eleTrig", &sf_eleTrig, &b_sf_eleTrig);
   fChain->SetBranchAddress("sf_muTrig", &sf_muTrig, &b_sf_muTrig);
   fChain->SetBranchAddress("sf_phoTrig", &sf_phoTrig, &b_sf_phoTrig);
   fChain->SetBranchAddress("sf_metTrig", &sf_metTrig, &b_sf_metTrig);
   fChain->SetBranchAddress("sf_metTrigZmm", &sf_metTrigZmm, &b_sf_metTrigZmm);
   fChain->SetBranchAddress("sf_metTrigVBF", &sf_metTrigVBF, &b_sf_metTrigVBF);
   fChain->SetBranchAddress("sf_metTrigZmmVBF", &sf_metTrigZmmVBF, &b_sf_metTrigZmmVBF);
   fChain->SetBranchAddress("sf_l1Prefire", &sf_l1Prefire, &b_sf_l1Prefire);
   fChain->SetBranchAddress("sf_pu", &sf_pu, &b_sf_pu);
   fChain->SetBranchAddress("sf_npv", &sf_npv, &b_sf_npv);
   fChain->SetBranchAddress("sf_tt", &sf_tt, &b_sf_tt);
   fChain->SetBranchAddress("sf_phoPurity", &sf_phoPurity, &b_sf_phoPurity);
   fChain->SetBranchAddress("sumETRaw", &sumETRaw, &b_sumETRaw);
   fChain->SetBranchAddress("pfmetRaw", &pfmetRaw, &b_pfmetRaw);
   fChain->SetBranchAddress("pfmet", &pfmet, &b_pfmet);
   fChain->SetBranchAddress("pfmet_JESTotalUp", &pfmet_JESTotalUp, &b_pfmet_JESTotalUp);
   fChain->SetBranchAddress("pfmet_JESTotalDown", &pfmet_JESTotalDown, &b_pfmet_JESTotalDown);
   fChain->SetBranchAddress("pfmetphi", &pfmetphi, &b_pfmetphi);
   fChain->SetBranchAddress("pfmetphi_JESTotalUp", &pfmetphi_JESTotalUp, &b_pfmetphi_JESTotalUp);
   fChain->SetBranchAddress("pfmetphi_JESTotalDown", &pfmetphi_JESTotalDown, &b_pfmetphi_JESTotalDown);
   fChain->SetBranchAddress("pfmetnomu", &pfmetnomu, &b_pfmetnomu);
   fChain->SetBranchAddress("pfmetnomu_JESTotalUp", &pfmetnomu_JESTotalUp, &b_pfmetnomu_JESTotalUp);
   fChain->SetBranchAddress("pfmetnomu_JESTotalDown", &pfmetnomu_JESTotalDown, &b_pfmetnomu_JESTotalDown);
   fChain->SetBranchAddress("puppimet", &puppimet, &b_puppimet);
   fChain->SetBranchAddress("puppimet_JESTotalUp", &puppimet_JESTotalUp, &b_puppimet_JESTotalUp);
   fChain->SetBranchAddress("puppimet_JESTotalDown", &puppimet_JESTotalDown, &b_puppimet_JESTotalDown);
   fChain->SetBranchAddress("puppimetphi", &puppimetphi, &b_puppimetphi);
   fChain->SetBranchAddress("puppimetphi_JESTotalUp", &puppimetphi_JESTotalUp, &b_puppimetphi_JESTotalUp);
   fChain->SetBranchAddress("puppimetphi_JESTotalDown", &puppimetphi_JESTotalDown, &b_puppimetphi_JESTotalDown);
   fChain->SetBranchAddress("calomet", &calomet, &b_calomet);
   fChain->SetBranchAddress("calometphi", &calometphi, &b_calometphi);
   fChain->SetBranchAddress("pfcalobalance", &pfcalobalance, &b_pfcalobalance);
   fChain->SetBranchAddress("sumET", &sumET, &b_sumET);
   fChain->SetBranchAddress("trkmet", &trkmet, &b_trkmet);
   fChain->SetBranchAddress("trkmetphi", &trkmetphi, &b_trkmetphi);
   fChain->SetBranchAddress("trkmetDZ", &trkmetDZ, &b_trkmetDZ);
   fChain->SetBranchAddress("trkmetDZphi", &trkmetDZphi, &b_trkmetDZphi);
   fChain->SetBranchAddress("whichRecoil", &whichRecoil, &b_whichRecoil);
   fChain->SetBranchAddress("dphipfmet", &dphipfmet, &b_dphipfmet);
   fChain->SetBranchAddress("dphipfmet_JESTotalUp", &dphipfmet_JESTotalUp, &b_dphipfmet_JESTotalUp);
   fChain->SetBranchAddress("dphipfmet_JESTotalDown", &dphipfmet_JESTotalDown, &b_dphipfmet_JESTotalDown);
   fChain->SetBranchAddress("trueGenBosonPt", &trueGenBosonPt, &b_trueGenBosonPt);
   fChain->SetBranchAddress("genBosonPt", &genBosonPt, &b_genBosonPt);
   fChain->SetBranchAddress("genBosonEta", &genBosonEta, &b_genBosonEta);
   fChain->SetBranchAddress("genBosonMass", &genBosonMass, &b_genBosonMass);
   fChain->SetBranchAddress("genBosonPhi", &genBosonPhi, &b_genBosonPhi);
   fChain->SetBranchAddress("genJet1Pt", &genJet1Pt, &b_genJet1Pt);
   fChain->SetBranchAddress("genJet2Pt", &genJet2Pt, &b_genJet2Pt);
   fChain->SetBranchAddress("genJet1Eta", &genJet1Eta, &b_genJet1Eta);
   fChain->SetBranchAddress("genJet2Eta", &genJet2Eta, &b_genJet2Eta);
   fChain->SetBranchAddress("nJet", &nJet, &b_nJet);
   fChain->SetBranchAddress("nJot", &nJot, &b_nJot);
   fChain->SetBranchAddress("nJot_JESTotalUp", &nJot_JESTotalUp, &b_nJot_JESTotalUp);
   fChain->SetBranchAddress("nJot_JESTotalDown", &nJot_JESTotalDown, &b_nJot_JESTotalDown);
   fChain->SetBranchAddress("nJotMax", &nJotMax, &b_nJotMax);
   fChain->SetBranchAddress("jotPt", jotPt, &b_jotPt);
   fChain->SetBranchAddress("jotPt_JESTotalUp", jotPt_JESTotalUp, &b_jotPt_JESTotalUp);
   fChain->SetBranchAddress("jotPt_JESTotalDown", jotPt_JESTotalDown, &b_jotPt_JESTotalDown);
   fChain->SetBranchAddress("jotEta", jotEta, &b_jotEta);
   fChain->SetBranchAddress("jotPhi", jotPhi, &b_jotPhi);
   fChain->SetBranchAddress("jotCSV", jotCSV, &b_jotCSV);
   fChain->SetBranchAddress("jotVBFID", jotVBFID, &b_jotVBFID);
   fChain->SetBranchAddress("barrelJet1Pt", &barrelJet1Pt, &b_barrelJet1Pt);
   fChain->SetBranchAddress("barrelJet1Eta", &barrelJet1Eta, &b_barrelJet1Eta);
   fChain->SetBranchAddress("barrelHT", &barrelHT, &b_barrelHT);
   fChain->SetBranchAddress("barrelHTMiss", &barrelHTMiss, &b_barrelHTMiss);
   fChain->SetBranchAddress("barrelJet12Pt", &barrelJet12Pt, &b_barrelJet12Pt);
   fChain->SetBranchAddress("jot12Mass", &jot12Mass, &b_jot12Mass);
   fChain->SetBranchAddress("jot12Mass_JESTotalUp", &jot12Mass_JESTotalUp, &b_jot12Mass_JESTotalUp);
   fChain->SetBranchAddress("jot12Mass_JESTotalDown", &jot12Mass_JESTotalDown, &b_jot12Mass_JESTotalDown);
   fChain->SetBranchAddress("jot12DEta", &jot12DEta, &b_jot12DEta);
   fChain->SetBranchAddress("jot12DEta_JESTotalUp", &jot12DEta_JESTotalUp, &b_jot12DEta_JESTotalUp);
   fChain->SetBranchAddress("jot12DEta_JESTotalDown", &jot12DEta_JESTotalDown, &b_jot12DEta_JESTotalDown);
   fChain->SetBranchAddress("jot12DPhi", &jot12DPhi, &b_jot12DPhi);
   fChain->SetBranchAddress("jot12DPhi_JESTotalUp", &jot12DPhi_JESTotalUp, &b_jot12DPhi_JESTotalUp);
   fChain->SetBranchAddress("jot12DPhi_JESTotalDown", &jot12DPhi_JESTotalDown, &b_jot12DPhi_JESTotalDown);
   fChain->SetBranchAddress("jetNBtags", &jetNBtags, &b_jetNBtags);
   fChain->SetBranchAddress("jetNBtags_JESTotalUp", &jetNBtags_JESTotalUp, &b_jetNBtags_JESTotalUp);
   fChain->SetBranchAddress("jetNBtags_JESTotalDown", &jetNBtags_JESTotalDown, &b_jetNBtags_JESTotalDown);
   fChain->SetBranchAddress("jetNMBtags", &jetNMBtags, &b_jetNMBtags);
   fChain->SetBranchAddress("jetNMBtags_JESTotalUp", &jetNMBtags_JESTotalUp, &b_jetNMBtags_JESTotalUp);
   fChain->SetBranchAddress("jetNMBtags_JESTotalDown", &jetNMBtags_JESTotalDown, &b_jetNMBtags_JESTotalDown);
   fChain->SetBranchAddress("nHF", &nHF, &b_nHF);
   fChain->SetBranchAddress("nB", &nB, &b_nB);
   fChain->SetBranchAddress("nBGenJets", &nBGenJets, &b_nBGenJets);
   fChain->SetBranchAddress("nStatus2BHadrons", &nStatus2BHadrons, &b_nStatus2BHadrons);
   fChain->SetBranchAddress("genFatJetPt", &genFatJetPt, &b_genFatJetPt);
   fChain->SetBranchAddress("genFatJetNProngs", &genFatJetNProngs, &b_genFatJetNProngs);
   fChain->SetBranchAddress("nLoosePhoton", &nLoosePhoton, &b_nLoosePhoton);
   fChain->SetBranchAddress("nTightPhoton", &nTightPhoton, &b_nTightPhoton);
   fChain->SetBranchAddress("loosePho1IsTight", &loosePho1IsTight, &b_loosePho1IsTight);
   fChain->SetBranchAddress("loosePho1Pt", &loosePho1Pt, &b_loosePho1Pt);
   fChain->SetBranchAddress("loosePho1Eta", &loosePho1Eta, &b_loosePho1Eta);
   fChain->SetBranchAddress("loosePho1Phi", &loosePho1Phi, &b_loosePho1Phi);
   fChain->SetBranchAddress("loosePho1SelBit", &loosePho1SelBit, &b_loosePho1SelBit);
   fChain->SetBranchAddress("looseGenPho1PdgId", &looseGenPho1PdgId, &b_looseGenPho1PdgId);
   fChain->SetBranchAddress("nLooseLep", &nLooseLep, &b_nLooseLep);
   fChain->SetBranchAddress("nLooseElectron", &nLooseElectron, &b_nLooseElectron);
   fChain->SetBranchAddress("nLooseMuon", &nLooseMuon, &b_nLooseMuon);
   fChain->SetBranchAddress("nTightLep", &nTightLep, &b_nTightLep);
   fChain->SetBranchAddress("nTightElectron", &nTightElectron, &b_nTightElectron);
   fChain->SetBranchAddress("nTightMuon", &nTightMuon, &b_nTightMuon);
   fChain->SetBranchAddress("electronPt", electronPt, &b_electronPt);
   fChain->SetBranchAddress("electronEta", electronEta, &b_electronEta);
   fChain->SetBranchAddress("electronPhi", electronPhi, &b_electronPhi);
   fChain->SetBranchAddress("electronSelBit", electronSelBit, &b_electronSelBit);
   fChain->SetBranchAddress("electronPdgId", electronPdgId, &b_electronPdgId);
   fChain->SetBranchAddress("muonPt", muonPt, &b_muonPt);
   fChain->SetBranchAddress("muonEta", muonEta, &b_muonEta);
   fChain->SetBranchAddress("muonPhi", muonPhi, &b_muonPhi);
   fChain->SetBranchAddress("muonSelBit", muonSelBit, &b_muonSelBit);
   fChain->SetBranchAddress("muonPdgId", muonPdgId, &b_muonPdgId);
   fChain->SetBranchAddress("sf_zz", &sf_zz, &b_sf_zz);
   fChain->SetBranchAddress("sf_zzUnc", &sf_zzUnc, &b_sf_zzUnc);
   fChain->SetBranchAddress("sf_wz", &sf_wz, &b_sf_wz);
   fChain->SetBranchAddress("sf_vh", &sf_vh, &b_sf_vh);
   fChain->SetBranchAddress("sf_vhUp", &sf_vhUp, &b_sf_vhUp);
   fChain->SetBranchAddress("sf_vhDown", &sf_vhDown, &b_sf_vhDown);
   fChain->SetBranchAddress("diLepMass", &diLepMass, &b_diLepMass);
   fChain->SetBranchAddress("nTau", &nTau, &b_nTau);
   fChain->SetBranchAddress("mT", &mT, &b_mT);
   fChain->SetBranchAddress("mT_JESTotalUp", &mT_JESTotalUp, &b_mT_JESTotalUp);
   fChain->SetBranchAddress("mT_JESTotalDown", &mT_JESTotalDown, &b_mT_JESTotalDown);
   fChain->SetBranchAddress("scaleUp", &scaleUp, &b_scaleUp);
   fChain->SetBranchAddress("scaleDown", &scaleDown, &b_scaleDown);
   fChain->SetBranchAddress("pdfUp", &pdfUp, &b_pdfUp);
   fChain->SetBranchAddress("pdfDown", &pdfDown, &b_pdfDown);
   fChain->SetBranchAddress("scale", scale, &b_scale);
   fChain->SetBranchAddress("lheHT", &lheHT, &b_lheHT);
   fChain->SetBranchAddress("isGS", &isGS, &b_isGS);
   fChain->SetBranchAddress("genMjj", &genMjj, &b_genMjj);
   fChain->SetBranchAddress("electronSfLoose", electronSfLoose, &b_electronSfLoose);
   fChain->SetBranchAddress("electronSfMedium", electronSfMedium, &b_electronSfMedium);
   fChain->SetBranchAddress("electronSfTight", electronSfTight, &b_electronSfTight);
   fChain->SetBranchAddress("electronSfMvaWP90", electronSfMvaWP90, &b_electronSfMvaWP90);
   fChain->SetBranchAddress("electronSfMvaWP80", electronSfMvaWP80, &b_electronSfMvaWP80);
   fChain->SetBranchAddress("electronSfUnc", electronSfUnc, &b_electronSfUnc);
   fChain->SetBranchAddress("electronSfReco", electronSfReco, &b_electronSfReco);
   fChain->SetBranchAddress("electronD0", electronD0, &b_electronD0);
   fChain->SetBranchAddress("electronDZ", electronDZ, &b_electronDZ);
   fChain->SetBranchAddress("electronNMissingHits", electronNMissingHits, &b_electronNMissingHits);
   fChain->SetBranchAddress("electronTripleCharge", electronTripleCharge, &b_electronTripleCharge);
   fChain->SetBranchAddress("electronCombIso", electronCombIso, &b_electronCombIso);
   fChain->SetBranchAddress("muonSfLoose", muonSfLoose, &b_muonSfLoose);
   fChain->SetBranchAddress("muonSfMedium", muonSfMedium, &b_muonSfMedium);
   fChain->SetBranchAddress("muonSfTight", muonSfTight, &b_muonSfTight);
   fChain->SetBranchAddress("muonSfUnc", muonSfUnc, &b_muonSfUnc);
   fChain->SetBranchAddress("muonSfReco", muonSfReco, &b_muonSfReco);
   fChain->SetBranchAddress("muonD0", muonD0, &b_muonD0);
   fChain->SetBranchAddress("muonDZ", muonDZ, &b_muonDZ);
   fChain->SetBranchAddress("muonIsSoftMuon", muonIsSoftMuon, &b_muonIsSoftMuon);
   fChain->SetBranchAddress("muonCombIso", muonCombIso, &b_muonCombIso);
   fChain->SetBranchAddress("genLep1Pt", &genLep1Pt, &b_genLep1Pt);
   fChain->SetBranchAddress("genLep1Eta", &genLep1Eta, &b_genLep1Eta);
   fChain->SetBranchAddress("genLep1Phi", &genLep1Phi, &b_genLep1Phi);
   fChain->SetBranchAddress("genLep1PdgId", &genLep1PdgId, &b_genLep1PdgId);
   fChain->SetBranchAddress("genLep2Pt", &genLep2Pt, &b_genLep2Pt);
   fChain->SetBranchAddress("genLep2Eta", &genLep2Eta, &b_genLep2Eta);
   fChain->SetBranchAddress("genLep2Phi", &genLep2Phi, &b_genLep2Phi);
   fChain->SetBranchAddress("genLep2PdgId", &genLep2PdgId, &b_genLep2PdgId);
   fChain->SetBranchAddress("genLep3Pt", &genLep3Pt, &b_genLep3Pt);
   fChain->SetBranchAddress("genLep3Eta", &genLep3Eta, &b_genLep3Eta);
   fChain->SetBranchAddress("genLep3Phi", &genLep3Phi, &b_genLep3Phi);
   fChain->SetBranchAddress("genLep3PdgId", &genLep3PdgId, &b_genLep3PdgId);
   fChain->SetBranchAddress("genLep4Pt", &genLep4Pt, &b_genLep4Pt);
   fChain->SetBranchAddress("genLep4Eta", &genLep4Eta, &b_genLep4Eta);
   fChain->SetBranchAddress("genLep4Phi", &genLep4Phi, &b_genLep4Phi);
   fChain->SetBranchAddress("genLep4PdgId", &genLep4PdgId, &b_genLep4PdgId);
   fChain->SetBranchAddress("genWPlusPt", &genWPlusPt, &b_genWPlusPt);
   fChain->SetBranchAddress("genWMinusPt", &genWMinusPt, &b_genWMinusPt);
   fChain->SetBranchAddress("genWPlusEta", &genWPlusEta, &b_genWPlusEta);
   fChain->SetBranchAddress("genWMinusEta", &genWMinusEta, &b_genWMinusEta);
   fChain->SetBranchAddress("looseGenLep1PdgId", &looseGenLep1PdgId, &b_looseGenLep1PdgId);
   fChain->SetBranchAddress("looseGenLep2PdgId", &looseGenLep2PdgId, &b_looseGenLep2PdgId);
   fChain->SetBranchAddress("looseGenLep3PdgId", &looseGenLep3PdgId, &b_looseGenLep3PdgId);
   fChain->SetBranchAddress("looseGenLep4PdgId", &looseGenLep4PdgId, &b_looseGenLep4PdgId);
   fChain->SetBranchAddress("normalizedWeight", &normalizedWeight, &b_normalizedWeight);
   Notify();
}

Bool_t pandaFlat::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void pandaFlat::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t pandaFlat::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef pandaFlat_cxx
