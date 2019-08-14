//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Aug  6 10:01:23 2019 by ROOT version 6.12/07
// from TTree events/events
// found on file: /scratch5/bmaier/darkg/2018/vbfg_v_013_v6/WZG.root
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
   Float_t         sf_sjbtag0;
   Float_t         sf_sjbtag1;
   Float_t         sf_sjbtag2;
   Float_t         sf_sjbtagGT0;
   Float_t         sf_btag0BUp;
   Float_t         sf_btag1BUp;
   Float_t         sf_btag2BUp;
   Float_t         sf_btagGT0BUp;
   Float_t         sf_sjbtag0BUp;
   Float_t         sf_sjbtag1BUp;
   Float_t         sf_sjbtag2BUp;
   Float_t         sf_sjbtagGT0BUp;
   Float_t         sf_btag0BDown;
   Float_t         sf_btag1BDown;
   Float_t         sf_btag2BDown;
   Float_t         sf_btagGT0BDown;
   Float_t         sf_sjbtag0BDown;
   Float_t         sf_sjbtag1BDown;
   Float_t         sf_sjbtag2BDown;
   Float_t         sf_sjbtagGT0BDown;
   Float_t         sf_btag0MUp;
   Float_t         sf_btag1MUp;
   Float_t         sf_btag2MUp;
   Float_t         sf_btagGT0MUp;
   Float_t         sf_sjbtag0MUp;
   Float_t         sf_sjbtag1MUp;
   Float_t         sf_sjbtag2MUp;
   Float_t         sf_sjbtagGT0MUp;
   Float_t         sf_btag0MDown;
   Float_t         sf_btag1MDown;
   Float_t         sf_btag2MDown;
   Float_t         sf_btagGT0MDown;
   Float_t         sf_sjbtag0MDown;
   Float_t         sf_sjbtag1MDown;
   Float_t         sf_sjbtag2MDown;
   Float_t         sf_sjbtagGT0MDown;
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
   Int_t           category;
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
   Float_t         puppiUWmag;
   Float_t         puppiUWmag_JESTotalUp;
   Float_t         puppiUWmag_JESTotalDown;
   Float_t         puppiUZmag;
   Float_t         puppiUZmag_JESTotalUp;
   Float_t         puppiUZmag_JESTotalDown;
   Float_t         puppiUAmag;
   Float_t         puppiUAmag_JESTotalUp;
   Float_t         puppiUAmag_JESTotalDown;
   Float_t         puppiUperp;
   Float_t         puppiUperp_JESTotalUp;
   Float_t         puppiUperp_JESTotalDown;
   Float_t         puppiUpara;
   Float_t         puppiUpara_JESTotalUp;
   Float_t         puppiUpara_JESTotalDown;
   Float_t         puppiUmag;
   Float_t         puppiUmag_JESTotalUp;
   Float_t         puppiUmag_JESTotalDown;
   Float_t         pfUWmag;
   Float_t         pfUWmag_JESTotalUp;
   Float_t         pfUWmag_JESTotalDown;
   Float_t         pfUZmag;
   Float_t         pfUZmag_JESTotalUp;
   Float_t         pfUZmag_JESTotalDown;
   Float_t         pfUAmag;
   Float_t         pfUAmag_JESTotalUp;
   Float_t         pfUAmag_JESTotalDown;
   Float_t         pfUperp;
   Float_t         pfUperp_JESTotalUp;
   Float_t         pfUperp_JESTotalDown;
   Float_t         pfUpara;
   Float_t         pfUpara_JESTotalUp;
   Float_t         pfUpara_JESTotalDown;
   Float_t         pfUmag;
   Float_t         pfUmag_JESTotalUp;
   Float_t         pfUmag_JESTotalDown;
   Float_t         puppiUWphi;
   Float_t         puppiUWphi_JESTotalUp;
   Float_t         puppiUWphi_JESTotalDown;
   Float_t         puppiUZphi;
   Float_t         puppiUZphi_JESTotalUp;
   Float_t         puppiUZphi_JESTotalDown;
   Float_t         puppiUAphi;
   Float_t         puppiUAphi_JESTotalUp;
   Float_t         puppiUAphi_JESTotalDown;
   Float_t         puppiUphi;
   Float_t         puppiUphi_JESTotalUp;
   Float_t         puppiUphi_JESTotalDown;
   Float_t         pfUWphi;
   Float_t         pfUWphi_JESTotalUp;
   Float_t         pfUWphi_JESTotalDown;
   Float_t         pfUZphi;
   Float_t         pfUZphi_JESTotalUp;
   Float_t         pfUZphi_JESTotalDown;
   Float_t         pfUAphi;
   Float_t         pfUAphi_JESTotalUp;
   Float_t         pfUAphi_JESTotalDown;
   Float_t         pfUphi;
   Float_t         pfUphi_JESTotalUp;
   Float_t         pfUphi_JESTotalDown;
   Float_t         dphipfmet;
   Float_t         dphipfmet_JESTotalUp;
   Float_t         dphipfmet_JESTotalDown;
   Float_t         dphipuppimet;
   Float_t         dphipuppimet_JESTotalUp;
   Float_t         dphipuppimet_JESTotalDown;
   Float_t         dphipuppiUW;
   Float_t         dphipuppiUW_JESTotalUp;
   Float_t         dphipuppiUW_JESTotalDown;
   Float_t         dphipuppiUZ;
   Float_t         dphipuppiUZ_JESTotalUp;
   Float_t         dphipuppiUZ_JESTotalDown;
   Float_t         dphipuppiUA;
   Float_t         dphipuppiUA_JESTotalUp;
   Float_t         dphipuppiUA_JESTotalDown;
   Float_t         dphipfUW;
   Float_t         dphipfUW_JESTotalUp;
   Float_t         dphipfUW_JESTotalDown;
   Float_t         dphipfUZ;
   Float_t         dphipfUZ_JESTotalUp;
   Float_t         dphipfUZ_JESTotalDown;
   Float_t         dphipfUA;
   Float_t         dphipfUA_JESTotalUp;
   Float_t         dphipfUA_JESTotalDown;
   Float_t         dphipuppiU;
   Float_t         dphipuppiU_JESTotalUp;
   Float_t         dphipuppiU_JESTotalDown;
   Float_t         dphipfU;
   Float_t         dphipfU_JESTotalUp;
   Float_t         dphipfU_JESTotalDown;
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
   Int_t           nJot_JESAbsoluteMPFBiasUp;
   Int_t           nJot_JESAbsoluteMPFBiasDown;
   Int_t           nJot_JESAbsoluteScaleUp;
   Int_t           nJot_JESAbsoluteScaleDown;
   Int_t           nJot_JESAbsoluteStatUp;
   Int_t           nJot_JESAbsoluteStatDown;
   Int_t           nJot_JESFlavorQCDUp;
   Int_t           nJot_JESFlavorQCDDown;
   Int_t           nJot_JESFragmentationUp;
   Int_t           nJot_JESFragmentationDown;
   Int_t           nJot_JESPileUpDataMCUp;
   Int_t           nJot_JESPileUpDataMCDown;
   Int_t           nJot_JESPileUpPtBBUp;
   Int_t           nJot_JESPileUpPtBBDown;
   Int_t           nJot_JESPileUpPtEC1Up;
   Int_t           nJot_JESPileUpPtEC1Down;
   Int_t           nJot_JESPileUpPtEC2Up;
   Int_t           nJot_JESPileUpPtEC2Down;
   Int_t           nJot_JESPileUpPtRefUp;
   Int_t           nJot_JESPileUpPtRefDown;
   Int_t           nJot_JESRelativeFSRUp;
   Int_t           nJot_JESRelativeFSRDown;
   Int_t           nJot_JESRelativeJEREC1Up;
   Int_t           nJot_JESRelativeJEREC1Down;
   Int_t           nJot_JESRelativePtBBUp;
   Int_t           nJot_JESRelativePtBBDown;
   Int_t           nJot_JESRelativePtEC1Up;
   Int_t           nJot_JESRelativePtEC1Down;
   Int_t           nJot_JESRelativePtEC2Up;
   Int_t           nJot_JESRelativePtEC2Down;
   Int_t           nJot_JESRelativeStatECUp;
   Int_t           nJot_JESRelativeStatECDown;
   Int_t           nJot_JESRelativeStatFSRUp;
   Int_t           nJot_JESRelativeStatFSRDown;
   Int_t           nJot_JESSinglePionECALUp;
   Int_t           nJot_JESSinglePionECALDown;
   Int_t           nJot_JESSinglePionHCALUp;
   Int_t           nJot_JESSinglePionHCALDown;
   Int_t           nJot_JESTimePtEtaUp;
   Int_t           nJot_JESTimePtEtaDown;
   Int_t           nJotMax;
   Float_t         jotPt[2];
   Float_t         jotPt_JESTotalUp[2];
   Float_t         jotPt_JESTotalDown[2];
   Float_t         jotPt_JESAbsoluteMPFBiasUp[2];
   Float_t         jotPt_JESAbsoluteMPFBiasDown[2];
   Float_t         jotPt_JESAbsoluteScaleUp[2];
   Float_t         jotPt_JESAbsoluteScaleDown[2];
   Float_t         jotPt_JESAbsoluteStatUp[2];
   Float_t         jotPt_JESAbsoluteStatDown[2];
   Float_t         jotPt_JESFlavorQCDUp[2];
   Float_t         jotPt_JESFlavorQCDDown[2];
   Float_t         jotPt_JESFragmentationUp[2];
   Float_t         jotPt_JESFragmentationDown[2];
   Float_t         jotPt_JESPileUpDataMCUp[2];
   Float_t         jotPt_JESPileUpDataMCDown[2];
   Float_t         jotPt_JESPileUpPtBBUp[2];
   Float_t         jotPt_JESPileUpPtBBDown[2];
   Float_t         jotPt_JESPileUpPtEC1Up[2];
   Float_t         jotPt_JESPileUpPtEC1Down[2];
   Float_t         jotPt_JESPileUpPtEC2Up[2];
   Float_t         jotPt_JESPileUpPtEC2Down[2];
   Float_t         jotPt_JESPileUpPtRefUp[2];
   Float_t         jotPt_JESPileUpPtRefDown[2];
   Float_t         jotPt_JESRelativeFSRUp[2];
   Float_t         jotPt_JESRelativeFSRDown[2];
   Float_t         jotPt_JESRelativeJEREC1Up[2];
   Float_t         jotPt_JESRelativeJEREC1Down[2];
   Float_t         jotPt_JESRelativePtBBUp[2];
   Float_t         jotPt_JESRelativePtBBDown[2];
   Float_t         jotPt_JESRelativePtEC1Up[2];
   Float_t         jotPt_JESRelativePtEC1Down[2];
   Float_t         jotPt_JESRelativePtEC2Up[2];
   Float_t         jotPt_JESRelativePtEC2Down[2];
   Float_t         jotPt_JESRelativeStatECUp[2];
   Float_t         jotPt_JESRelativeStatECDown[2];
   Float_t         jotPt_JESRelativeStatFSRUp[2];
   Float_t         jotPt_JESRelativeStatFSRDown[2];
   Float_t         jotPt_JESSinglePionECALUp[2];
   Float_t         jotPt_JESSinglePionECALDown[2];
   Float_t         jotPt_JESSinglePionHCALUp[2];
   Float_t         jotPt_JESSinglePionHCALDown[2];
   Float_t         jotPt_JESTimePtEtaUp[2];
   Float_t         jotPt_JESTimePtEtaDown[2];
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
   Int_t           jetNBtags_JESAbsoluteMPFBiasUp;
   Int_t           jetNBtags_JESAbsoluteMPFBiasDown;
   Int_t           jetNBtags_JESAbsoluteScaleUp;
   Int_t           jetNBtags_JESAbsoluteScaleDown;
   Int_t           jetNBtags_JESAbsoluteStatUp;
   Int_t           jetNBtags_JESAbsoluteStatDown;
   Int_t           jetNBtags_JESFlavorQCDUp;
   Int_t           jetNBtags_JESFlavorQCDDown;
   Int_t           jetNBtags_JESFragmentationUp;
   Int_t           jetNBtags_JESFragmentationDown;
   Int_t           jetNBtags_JESPileUpDataMCUp;
   Int_t           jetNBtags_JESPileUpDataMCDown;
   Int_t           jetNBtags_JESPileUpPtBBUp;
   Int_t           jetNBtags_JESPileUpPtBBDown;
   Int_t           jetNBtags_JESPileUpPtEC1Up;
   Int_t           jetNBtags_JESPileUpPtEC1Down;
   Int_t           jetNBtags_JESPileUpPtEC2Up;
   Int_t           jetNBtags_JESPileUpPtEC2Down;
   Int_t           jetNBtags_JESPileUpPtRefUp;
   Int_t           jetNBtags_JESPileUpPtRefDown;
   Int_t           jetNBtags_JESRelativeFSRUp;
   Int_t           jetNBtags_JESRelativeFSRDown;
   Int_t           jetNBtags_JESRelativeJEREC1Up;
   Int_t           jetNBtags_JESRelativeJEREC1Down;
   Int_t           jetNBtags_JESRelativePtBBUp;
   Int_t           jetNBtags_JESRelativePtBBDown;
   Int_t           jetNBtags_JESRelativePtEC1Up;
   Int_t           jetNBtags_JESRelativePtEC1Down;
   Int_t           jetNBtags_JESRelativePtEC2Up;
   Int_t           jetNBtags_JESRelativePtEC2Down;
   Int_t           jetNBtags_JESRelativeStatECUp;
   Int_t           jetNBtags_JESRelativeStatECDown;
   Int_t           jetNBtags_JESRelativeStatFSRUp;
   Int_t           jetNBtags_JESRelativeStatFSRDown;
   Int_t           jetNBtags_JESSinglePionECALUp;
   Int_t           jetNBtags_JESSinglePionECALDown;
   Int_t           jetNBtags_JESSinglePionHCALUp;
   Int_t           jetNBtags_JESSinglePionHCALDown;
   Int_t           jetNBtags_JESTimePtEtaUp;
   Int_t           jetNBtags_JESTimePtEtaDown;
   Int_t           jetNMBtags;
   Int_t           jetNMBtags_JESTotalUp;
   Int_t           jetNMBtags_JESTotalDown;
   Int_t           jetNMBtags_JESAbsoluteMPFBiasUp;
   Int_t           jetNMBtags_JESAbsoluteMPFBiasDown;
   Int_t           jetNMBtags_JESAbsoluteScaleUp;
   Int_t           jetNMBtags_JESAbsoluteScaleDown;
   Int_t           jetNMBtags_JESAbsoluteStatUp;
   Int_t           jetNMBtags_JESAbsoluteStatDown;
   Int_t           jetNMBtags_JESFlavorQCDUp;
   Int_t           jetNMBtags_JESFlavorQCDDown;
   Int_t           jetNMBtags_JESFragmentationUp;
   Int_t           jetNMBtags_JESFragmentationDown;
   Int_t           jetNMBtags_JESPileUpDataMCUp;
   Int_t           jetNMBtags_JESPileUpDataMCDown;
   Int_t           jetNMBtags_JESPileUpPtBBUp;
   Int_t           jetNMBtags_JESPileUpPtBBDown;
   Int_t           jetNMBtags_JESPileUpPtEC1Up;
   Int_t           jetNMBtags_JESPileUpPtEC1Down;
   Int_t           jetNMBtags_JESPileUpPtEC2Up;
   Int_t           jetNMBtags_JESPileUpPtEC2Down;
   Int_t           jetNMBtags_JESPileUpPtRefUp;
   Int_t           jetNMBtags_JESPileUpPtRefDown;
   Int_t           jetNMBtags_JESRelativeFSRUp;
   Int_t           jetNMBtags_JESRelativeFSRDown;
   Int_t           jetNMBtags_JESRelativeJEREC1Up;
   Int_t           jetNMBtags_JESRelativeJEREC1Down;
   Int_t           jetNMBtags_JESRelativePtBBUp;
   Int_t           jetNMBtags_JESRelativePtBBDown;
   Int_t           jetNMBtags_JESRelativePtEC1Up;
   Int_t           jetNMBtags_JESRelativePtEC1Down;
   Int_t           jetNMBtags_JESRelativePtEC2Up;
   Int_t           jetNMBtags_JESRelativePtEC2Down;
   Int_t           jetNMBtags_JESRelativeStatECUp;
   Int_t           jetNMBtags_JESRelativeStatECDown;
   Int_t           jetNMBtags_JESRelativeStatFSRUp;
   Int_t           jetNMBtags_JESRelativeStatFSRDown;
   Int_t           jetNMBtags_JESSinglePionECALUp;
   Int_t           jetNMBtags_JESSinglePionECALDown;
   Int_t           jetNMBtags_JESSinglePionHCALUp;
   Int_t           jetNMBtags_JESSinglePionHCALDown;
   Int_t           jetNMBtags_JESTimePtEtaUp;
   Int_t           jetNMBtags_JESTimePtEtaDown;
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
   Float_t         loosePho1r9;
   Float_t         loosePho1chIso;
   Float_t         loosePho1nhIso;
   Float_t         loosePho1phIso;
   Float_t         loosePho1hOverE;
   Float_t         loosePho1sieie;
   Int_t           loosePho1SelBit;
   Int_t           looseGenPho1PdgId;
   Float_t         alterPho1Pt;
   Float_t         alterPho1Eta;
   Float_t         alterPho1Phi;
   Float_t         alterPho1r9;
   Float_t         alterPho1chIso;
   Float_t         alterPho1nhIso;
   Float_t         alterPho1phIso;
   Float_t         alterPho1hOverE;
   Float_t         alterPho1sieie;
   Int_t           alterPho1SelBit;
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
   Int_t           electronPhoMatch[4];   //[nLooseElectron]
   Int_t           electronLPhoMatch[4];   //[nLooseElectron]
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
   TBranch        *b_sf_sjbtag0;   //!
   TBranch        *b_sf_sjbtag1;   //!
   TBranch        *b_sf_sjbtag2;   //!
   TBranch        *b_sf_sjbtagGT0;   //!
   TBranch        *b_sf_btag0BUp;   //!
   TBranch        *b_sf_btag1BUp;   //!
   TBranch        *b_sf_btag2BUp;   //!
   TBranch        *b_sf_btagGT0BUp;   //!
   TBranch        *b_sf_sjbtag0BUp;   //!
   TBranch        *b_sf_sjbtag1BUp;   //!
   TBranch        *b_sf_sjbtag2BUp;   //!
   TBranch        *b_sf_sjbtagGT0BUp;   //!
   TBranch        *b_sf_btag0BDown;   //!
   TBranch        *b_sf_btag1BDown;   //!
   TBranch        *b_sf_btag2BDown;   //!
   TBranch        *b_sf_btagGT0BDown;   //!
   TBranch        *b_sf_sjbtag0BDown;   //!
   TBranch        *b_sf_sjbtag1BDown;   //!
   TBranch        *b_sf_sjbtag2BDown;   //!
   TBranch        *b_sf_sjbtagGT0BDown;   //!
   TBranch        *b_sf_btag0MUp;   //!
   TBranch        *b_sf_btag1MUp;   //!
   TBranch        *b_sf_btag2MUp;   //!
   TBranch        *b_sf_btagGT0MUp;   //!
   TBranch        *b_sf_sjbtag0MUp;   //!
   TBranch        *b_sf_sjbtag1MUp;   //!
   TBranch        *b_sf_sjbtag2MUp;   //!
   TBranch        *b_sf_sjbtagGT0MUp;   //!
   TBranch        *b_sf_btag0MDown;   //!
   TBranch        *b_sf_btag1MDown;   //!
   TBranch        *b_sf_btag2MDown;   //!
   TBranch        *b_sf_btagGT0MDown;   //!
   TBranch        *b_sf_sjbtag0MDown;   //!
   TBranch        *b_sf_sjbtag1MDown;   //!
   TBranch        *b_sf_sjbtag2MDown;   //!
   TBranch        *b_sf_sjbtagGT0MDown;   //!
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
   TBranch        *b_category;   //!
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
   TBranch        *b_puppiUWmag;   //!
   TBranch        *b_puppiUWmag_JESTotalUp;   //!
   TBranch        *b_puppiUWmag_JESTotalDown;   //!
   TBranch        *b_puppiUZmag;   //!
   TBranch        *b_puppiUZmag_JESTotalUp;   //!
   TBranch        *b_puppiUZmag_JESTotalDown;   //!
   TBranch        *b_puppiUAmag;   //!
   TBranch        *b_puppiUAmag_JESTotalUp;   //!
   TBranch        *b_puppiUAmag_JESTotalDown;   //!
   TBranch        *b_puppiUperp;   //!
   TBranch        *b_puppiUperp_JESTotalUp;   //!
   TBranch        *b_puppiUperp_JESTotalDown;   //!
   TBranch        *b_puppiUpara;   //!
   TBranch        *b_puppiUpara_JESTotalUp;   //!
   TBranch        *b_puppiUpara_JESTotalDown;   //!
   TBranch        *b_puppiUmag;   //!
   TBranch        *b_puppiUmag_JESTotalUp;   //!
   TBranch        *b_puppiUmag_JESTotalDown;   //!
   TBranch        *b_pfUWmag;   //!
   TBranch        *b_pfUWmag_JESTotalUp;   //!
   TBranch        *b_pfUWmag_JESTotalDown;   //!
   TBranch        *b_pfUZmag;   //!
   TBranch        *b_pfUZmag_JESTotalUp;   //!
   TBranch        *b_pfUZmag_JESTotalDown;   //!
   TBranch        *b_pfUAmag;   //!
   TBranch        *b_pfUAmag_JESTotalUp;   //!
   TBranch        *b_pfUAmag_JESTotalDown;   //!
   TBranch        *b_pfUperp;   //!
   TBranch        *b_pfUperp_JESTotalUp;   //!
   TBranch        *b_pfUperp_JESTotalDown;   //!
   TBranch        *b_pfUpara;   //!
   TBranch        *b_pfUpara_JESTotalUp;   //!
   TBranch        *b_pfUpara_JESTotalDown;   //!
   TBranch        *b_pfUmag;   //!
   TBranch        *b_pfUmag_JESTotalUp;   //!
   TBranch        *b_pfUmag_JESTotalDown;   //!
   TBranch        *b_puppiUWphi;   //!
   TBranch        *b_puppiUWphi_JESTotalUp;   //!
   TBranch        *b_puppiUWphi_JESTotalDown;   //!
   TBranch        *b_puppiUZphi;   //!
   TBranch        *b_puppiUZphi_JESTotalUp;   //!
   TBranch        *b_puppiUZphi_JESTotalDown;   //!
   TBranch        *b_puppiUAphi;   //!
   TBranch        *b_puppiUAphi_JESTotalUp;   //!
   TBranch        *b_puppiUAphi_JESTotalDown;   //!
   TBranch        *b_puppiUphi;   //!
   TBranch        *b_puppiUphi_JESTotalUp;   //!
   TBranch        *b_puppiUphi_JESTotalDown;   //!
   TBranch        *b_pfUWphi;   //!
   TBranch        *b_pfUWphi_JESTotalUp;   //!
   TBranch        *b_pfUWphi_JESTotalDown;   //!
   TBranch        *b_pfUZphi;   //!
   TBranch        *b_pfUZphi_JESTotalUp;   //!
   TBranch        *b_pfUZphi_JESTotalDown;   //!
   TBranch        *b_pfUAphi;   //!
   TBranch        *b_pfUAphi_JESTotalUp;   //!
   TBranch        *b_pfUAphi_JESTotalDown;   //!
   TBranch        *b_pfUphi;   //!
   TBranch        *b_pfUphi_JESTotalUp;   //!
   TBranch        *b_pfUphi_JESTotalDown;   //!
   TBranch        *b_dphipfmet;   //!
   TBranch        *b_dphipfmet_JESTotalUp;   //!
   TBranch        *b_dphipfmet_JESTotalDown;   //!
   TBranch        *b_dphipuppimet;   //!
   TBranch        *b_dphipuppimet_JESTotalUp;   //!
   TBranch        *b_dphipuppimet_JESTotalDown;   //!
   TBranch        *b_dphipuppiUW;   //!
   TBranch        *b_dphipuppiUW_JESTotalUp;   //!
   TBranch        *b_dphipuppiUW_JESTotalDown;   //!
   TBranch        *b_dphipuppiUZ;   //!
   TBranch        *b_dphipuppiUZ_JESTotalUp;   //!
   TBranch        *b_dphipuppiUZ_JESTotalDown;   //!
   TBranch        *b_dphipuppiUA;   //!
   TBranch        *b_dphipuppiUA_JESTotalUp;   //!
   TBranch        *b_dphipuppiUA_JESTotalDown;   //!
   TBranch        *b_dphipfUW;   //!
   TBranch        *b_dphipfUW_JESTotalUp;   //!
   TBranch        *b_dphipfUW_JESTotalDown;   //!
   TBranch        *b_dphipfUZ;   //!
   TBranch        *b_dphipfUZ_JESTotalUp;   //!
   TBranch        *b_dphipfUZ_JESTotalDown;   //!
   TBranch        *b_dphipfUA;   //!
   TBranch        *b_dphipfUA_JESTotalUp;   //!
   TBranch        *b_dphipfUA_JESTotalDown;   //!
   TBranch        *b_dphipuppiU;   //!
   TBranch        *b_dphipuppiU_JESTotalUp;   //!
   TBranch        *b_dphipuppiU_JESTotalDown;   //!
   TBranch        *b_dphipfU;   //!
   TBranch        *b_dphipfU_JESTotalUp;   //!
   TBranch        *b_dphipfU_JESTotalDown;   //!
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
   TBranch        *b_nJot_JESAbsoluteMPFBiasUp;   //!
   TBranch        *b_nJot_JESAbsoluteMPFBiasDown;   //!
   TBranch        *b_nJot_JESAbsoluteScaleUp;   //!
   TBranch        *b_nJot_JESAbsoluteScaleDown;   //!
   TBranch        *b_nJot_JESAbsoluteStatUp;   //!
   TBranch        *b_nJot_JESAbsoluteStatDown;   //!
   TBranch        *b_nJot_JESFlavorQCDUp;   //!
   TBranch        *b_nJot_JESFlavorQCDDown;   //!
   TBranch        *b_nJot_JESFragmentationUp;   //!
   TBranch        *b_nJot_JESFragmentationDown;   //!
   TBranch        *b_nJot_JESPileUpDataMCUp;   //!
   TBranch        *b_nJot_JESPileUpDataMCDown;   //!
   TBranch        *b_nJot_JESPileUpPtBBUp;   //!
   TBranch        *b_nJot_JESPileUpPtBBDown;   //!
   TBranch        *b_nJot_JESPileUpPtEC1Up;   //!
   TBranch        *b_nJot_JESPileUpPtEC1Down;   //!
   TBranch        *b_nJot_JESPileUpPtEC2Up;   //!
   TBranch        *b_nJot_JESPileUpPtEC2Down;   //!
   TBranch        *b_nJot_JESPileUpPtRefUp;   //!
   TBranch        *b_nJot_JESPileUpPtRefDown;   //!
   TBranch        *b_nJot_JESRelativeFSRUp;   //!
   TBranch        *b_nJot_JESRelativeFSRDown;   //!
   TBranch        *b_nJot_JESRelativeJEREC1Up;   //!
   TBranch        *b_nJot_JESRelativeJEREC1Down;   //!
   TBranch        *b_nJot_JESRelativePtBBUp;   //!
   TBranch        *b_nJot_JESRelativePtBBDown;   //!
   TBranch        *b_nJot_JESRelativePtEC1Up;   //!
   TBranch        *b_nJot_JESRelativePtEC1Down;   //!
   TBranch        *b_nJot_JESRelativePtEC2Up;   //!
   TBranch        *b_nJot_JESRelativePtEC2Down;   //!
   TBranch        *b_nJot_JESRelativeStatECUp;   //!
   TBranch        *b_nJot_JESRelativeStatECDown;   //!
   TBranch        *b_nJot_JESRelativeStatFSRUp;   //!
   TBranch        *b_nJot_JESRelativeStatFSRDown;   //!
   TBranch        *b_nJot_JESSinglePionECALUp;   //!
   TBranch        *b_nJot_JESSinglePionECALDown;   //!
   TBranch        *b_nJot_JESSinglePionHCALUp;   //!
   TBranch        *b_nJot_JESSinglePionHCALDown;   //!
   TBranch        *b_nJot_JESTimePtEtaUp;   //!
   TBranch        *b_nJot_JESTimePtEtaDown;   //!
   TBranch        *b_nJotMax;   //!
   TBranch        *b_jotPt;   //!
   TBranch        *b_jotPt_JESTotalUp;   //!
   TBranch        *b_jotPt_JESTotalDown;   //!
   TBranch        *b_jotPt_JESAbsoluteMPFBiasUp;   //!
   TBranch        *b_jotPt_JESAbsoluteMPFBiasDown;   //!
   TBranch        *b_jotPt_JESAbsoluteScaleUp;   //!
   TBranch        *b_jotPt_JESAbsoluteScaleDown;   //!
   TBranch        *b_jotPt_JESAbsoluteStatUp;   //!
   TBranch        *b_jotPt_JESAbsoluteStatDown;   //!
   TBranch        *b_jotPt_JESFlavorQCDUp;   //!
   TBranch        *b_jotPt_JESFlavorQCDDown;   //!
   TBranch        *b_jotPt_JESFragmentationUp;   //!
   TBranch        *b_jotPt_JESFragmentationDown;   //!
   TBranch        *b_jotPt_JESPileUpDataMCUp;   //!
   TBranch        *b_jotPt_JESPileUpDataMCDown;   //!
   TBranch        *b_jotPt_JESPileUpPtBBUp;   //!
   TBranch        *b_jotPt_JESPileUpPtBBDown;   //!
   TBranch        *b_jotPt_JESPileUpPtEC1Up;   //!
   TBranch        *b_jotPt_JESPileUpPtEC1Down;   //!
   TBranch        *b_jotPt_JESPileUpPtEC2Up;   //!
   TBranch        *b_jotPt_JESPileUpPtEC2Down;   //!
   TBranch        *b_jotPt_JESPileUpPtRefUp;   //!
   TBranch        *b_jotPt_JESPileUpPtRefDown;   //!
   TBranch        *b_jotPt_JESRelativeFSRUp;   //!
   TBranch        *b_jotPt_JESRelativeFSRDown;   //!
   TBranch        *b_jotPt_JESRelativeJEREC1Up;   //!
   TBranch        *b_jotPt_JESRelativeJEREC1Down;   //!
   TBranch        *b_jotPt_JESRelativePtBBUp;   //!
   TBranch        *b_jotPt_JESRelativePtBBDown;   //!
   TBranch        *b_jotPt_JESRelativePtEC1Up;   //!
   TBranch        *b_jotPt_JESRelativePtEC1Down;   //!
   TBranch        *b_jotPt_JESRelativePtEC2Up;   //!
   TBranch        *b_jotPt_JESRelativePtEC2Down;   //!
   TBranch        *b_jotPt_JESRelativeStatECUp;   //!
   TBranch        *b_jotPt_JESRelativeStatECDown;   //!
   TBranch        *b_jotPt_JESRelativeStatFSRUp;   //!
   TBranch        *b_jotPt_JESRelativeStatFSRDown;   //!
   TBranch        *b_jotPt_JESSinglePionECALUp;   //!
   TBranch        *b_jotPt_JESSinglePionECALDown;   //!
   TBranch        *b_jotPt_JESSinglePionHCALUp;   //!
   TBranch        *b_jotPt_JESSinglePionHCALDown;   //!
   TBranch        *b_jotPt_JESTimePtEtaUp;   //!
   TBranch        *b_jotPt_JESTimePtEtaDown;   //!
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
   TBranch        *b_jetNBtags_JESAbsoluteMPFBiasUp;   //!
   TBranch        *b_jetNBtags_JESAbsoluteMPFBiasDown;   //!
   TBranch        *b_jetNBtags_JESAbsoluteScaleUp;   //!
   TBranch        *b_jetNBtags_JESAbsoluteScaleDown;   //!
   TBranch        *b_jetNBtags_JESAbsoluteStatUp;   //!
   TBranch        *b_jetNBtags_JESAbsoluteStatDown;   //!
   TBranch        *b_jetNBtags_JESFlavorQCDUp;   //!
   TBranch        *b_jetNBtags_JESFlavorQCDDown;   //!
   TBranch        *b_jetNBtags_JESFragmentationUp;   //!
   TBranch        *b_jetNBtags_JESFragmentationDown;   //!
   TBranch        *b_jetNBtags_JESPileUpDataMCUp;   //!
   TBranch        *b_jetNBtags_JESPileUpDataMCDown;   //!
   TBranch        *b_jetNBtags_JESPileUpPtBBUp;   //!
   TBranch        *b_jetNBtags_JESPileUpPtBBDown;   //!
   TBranch        *b_jetNBtags_JESPileUpPtEC1Up;   //!
   TBranch        *b_jetNBtags_JESPileUpPtEC1Down;   //!
   TBranch        *b_jetNBtags_JESPileUpPtEC2Up;   //!
   TBranch        *b_jetNBtags_JESPileUpPtEC2Down;   //!
   TBranch        *b_jetNBtags_JESPileUpPtRefUp;   //!
   TBranch        *b_jetNBtags_JESPileUpPtRefDown;   //!
   TBranch        *b_jetNBtags_JESRelativeFSRUp;   //!
   TBranch        *b_jetNBtags_JESRelativeFSRDown;   //!
   TBranch        *b_jetNBtags_JESRelativeJEREC1Up;   //!
   TBranch        *b_jetNBtags_JESRelativeJEREC1Down;   //!
   TBranch        *b_jetNBtags_JESRelativePtBBUp;   //!
   TBranch        *b_jetNBtags_JESRelativePtBBDown;   //!
   TBranch        *b_jetNBtags_JESRelativePtEC1Up;   //!
   TBranch        *b_jetNBtags_JESRelativePtEC1Down;   //!
   TBranch        *b_jetNBtags_JESRelativePtEC2Up;   //!
   TBranch        *b_jetNBtags_JESRelativePtEC2Down;   //!
   TBranch        *b_jetNBtags_JESRelativeStatECUp;   //!
   TBranch        *b_jetNBtags_JESRelativeStatECDown;   //!
   TBranch        *b_jetNBtags_JESRelativeStatFSRUp;   //!
   TBranch        *b_jetNBtags_JESRelativeStatFSRDown;   //!
   TBranch        *b_jetNBtags_JESSinglePionECALUp;   //!
   TBranch        *b_jetNBtags_JESSinglePionECALDown;   //!
   TBranch        *b_jetNBtags_JESSinglePionHCALUp;   //!
   TBranch        *b_jetNBtags_JESSinglePionHCALDown;   //!
   TBranch        *b_jetNBtags_JESTimePtEtaUp;   //!
   TBranch        *b_jetNBtags_JESTimePtEtaDown;   //!
   TBranch        *b_jetNMBtags;   //!
   TBranch        *b_jetNMBtags_JESTotalUp;   //!
   TBranch        *b_jetNMBtags_JESTotalDown;   //!
   TBranch        *b_jetNMBtags_JESAbsoluteMPFBiasUp;   //!
   TBranch        *b_jetNMBtags_JESAbsoluteMPFBiasDown;   //!
   TBranch        *b_jetNMBtags_JESAbsoluteScaleUp;   //!
   TBranch        *b_jetNMBtags_JESAbsoluteScaleDown;   //!
   TBranch        *b_jetNMBtags_JESAbsoluteStatUp;   //!
   TBranch        *b_jetNMBtags_JESAbsoluteStatDown;   //!
   TBranch        *b_jetNMBtags_JESFlavorQCDUp;   //!
   TBranch        *b_jetNMBtags_JESFlavorQCDDown;   //!
   TBranch        *b_jetNMBtags_JESFragmentationUp;   //!
   TBranch        *b_jetNMBtags_JESFragmentationDown;   //!
   TBranch        *b_jetNMBtags_JESPileUpDataMCUp;   //!
   TBranch        *b_jetNMBtags_JESPileUpDataMCDown;   //!
   TBranch        *b_jetNMBtags_JESPileUpPtBBUp;   //!
   TBranch        *b_jetNMBtags_JESPileUpPtBBDown;   //!
   TBranch        *b_jetNMBtags_JESPileUpPtEC1Up;   //!
   TBranch        *b_jetNMBtags_JESPileUpPtEC1Down;   //!
   TBranch        *b_jetNMBtags_JESPileUpPtEC2Up;   //!
   TBranch        *b_jetNMBtags_JESPileUpPtEC2Down;   //!
   TBranch        *b_jetNMBtags_JESPileUpPtRefUp;   //!
   TBranch        *b_jetNMBtags_JESPileUpPtRefDown;   //!
   TBranch        *b_jetNMBtags_JESRelativeFSRUp;   //!
   TBranch        *b_jetNMBtags_JESRelativeFSRDown;   //!
   TBranch        *b_jetNMBtags_JESRelativeJEREC1Up;   //!
   TBranch        *b_jetNMBtags_JESRelativeJEREC1Down;   //!
   TBranch        *b_jetNMBtags_JESRelativePtBBUp;   //!
   TBranch        *b_jetNMBtags_JESRelativePtBBDown;   //!
   TBranch        *b_jetNMBtags_JESRelativePtEC1Up;   //!
   TBranch        *b_jetNMBtags_JESRelativePtEC1Down;   //!
   TBranch        *b_jetNMBtags_JESRelativePtEC2Up;   //!
   TBranch        *b_jetNMBtags_JESRelativePtEC2Down;   //!
   TBranch        *b_jetNMBtags_JESRelativeStatECUp;   //!
   TBranch        *b_jetNMBtags_JESRelativeStatECDown;   //!
   TBranch        *b_jetNMBtags_JESRelativeStatFSRUp;   //!
   TBranch        *b_jetNMBtags_JESRelativeStatFSRDown;   //!
   TBranch        *b_jetNMBtags_JESSinglePionECALUp;   //!
   TBranch        *b_jetNMBtags_JESSinglePionECALDown;   //!
   TBranch        *b_jetNMBtags_JESSinglePionHCALUp;   //!
   TBranch        *b_jetNMBtags_JESSinglePionHCALDown;   //!
   TBranch        *b_jetNMBtags_JESTimePtEtaUp;   //!
   TBranch        *b_jetNMBtags_JESTimePtEtaDown;   //!
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
   TBranch        *b_loosePho1r9;   //!
   TBranch        *b_loosePho1chIso;   //!
   TBranch        *b_loosePho1nhIso;   //!
   TBranch        *b_loosePho1phIso;   //!
   TBranch        *b_loosePho1hOverE;   //!
   TBranch        *b_loosePho1sieie;   //!
   TBranch        *b_loosePho1SelBit;   //!
   TBranch        *b_looseGenPho1PdgId;   //!
   TBranch        *b_alterPho1Pt;   //!
   TBranch        *b_alterPho1Eta;   //!
   TBranch        *b_alterPho1Phi;   //!
   TBranch        *b_alterPho1r9;   //!
   TBranch        *b_alterPho1chIso;   //!
   TBranch        *b_alterPho1nhIso;   //!
   TBranch        *b_alterPho1phIso;   //!
   TBranch        *b_alterPho1hOverE;   //!
   TBranch        *b_alterPho1sieie;   //!
   TBranch        *b_alterPho1SelBit;   //!
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
   TBranch        *b_electronPhoMatch;   //!
   TBranch        *b_electronLPhoMatch;   //!
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
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/scratch5/bmaier/darkg/2018/vbfg_v_013_v6/WZG.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/scratch5/bmaier/darkg/2018/vbfg_v_013_v6/WZG.root");
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
   fChain->SetBranchAddress("sf_sjbtag0", &sf_sjbtag0, &b_sf_sjbtag0);
   fChain->SetBranchAddress("sf_sjbtag1", &sf_sjbtag1, &b_sf_sjbtag1);
   fChain->SetBranchAddress("sf_sjbtag2", &sf_sjbtag2, &b_sf_sjbtag2);
   fChain->SetBranchAddress("sf_sjbtagGT0", &sf_sjbtagGT0, &b_sf_sjbtagGT0);
   fChain->SetBranchAddress("sf_btag0BUp", &sf_btag0BUp, &b_sf_btag0BUp);
   fChain->SetBranchAddress("sf_btag1BUp", &sf_btag1BUp, &b_sf_btag1BUp);
   fChain->SetBranchAddress("sf_btag2BUp", &sf_btag2BUp, &b_sf_btag2BUp);
   fChain->SetBranchAddress("sf_btagGT0BUp", &sf_btagGT0BUp, &b_sf_btagGT0BUp);
   fChain->SetBranchAddress("sf_sjbtag0BUp", &sf_sjbtag0BUp, &b_sf_sjbtag0BUp);
   fChain->SetBranchAddress("sf_sjbtag1BUp", &sf_sjbtag1BUp, &b_sf_sjbtag1BUp);
   fChain->SetBranchAddress("sf_sjbtag2BUp", &sf_sjbtag2BUp, &b_sf_sjbtag2BUp);
   fChain->SetBranchAddress("sf_sjbtagGT0BUp", &sf_sjbtagGT0BUp, &b_sf_sjbtagGT0BUp);
   fChain->SetBranchAddress("sf_btag0BDown", &sf_btag0BDown, &b_sf_btag0BDown);
   fChain->SetBranchAddress("sf_btag1BDown", &sf_btag1BDown, &b_sf_btag1BDown);
   fChain->SetBranchAddress("sf_btag2BDown", &sf_btag2BDown, &b_sf_btag2BDown);
   fChain->SetBranchAddress("sf_btagGT0BDown", &sf_btagGT0BDown, &b_sf_btagGT0BDown);
   fChain->SetBranchAddress("sf_sjbtag0BDown", &sf_sjbtag0BDown, &b_sf_sjbtag0BDown);
   fChain->SetBranchAddress("sf_sjbtag1BDown", &sf_sjbtag1BDown, &b_sf_sjbtag1BDown);
   fChain->SetBranchAddress("sf_sjbtag2BDown", &sf_sjbtag2BDown, &b_sf_sjbtag2BDown);
   fChain->SetBranchAddress("sf_sjbtagGT0BDown", &sf_sjbtagGT0BDown, &b_sf_sjbtagGT0BDown);
   fChain->SetBranchAddress("sf_btag0MUp", &sf_btag0MUp, &b_sf_btag0MUp);
   fChain->SetBranchAddress("sf_btag1MUp", &sf_btag1MUp, &b_sf_btag1MUp);
   fChain->SetBranchAddress("sf_btag2MUp", &sf_btag2MUp, &b_sf_btag2MUp);
   fChain->SetBranchAddress("sf_btagGT0MUp", &sf_btagGT0MUp, &b_sf_btagGT0MUp);
   fChain->SetBranchAddress("sf_sjbtag0MUp", &sf_sjbtag0MUp, &b_sf_sjbtag0MUp);
   fChain->SetBranchAddress("sf_sjbtag1MUp", &sf_sjbtag1MUp, &b_sf_sjbtag1MUp);
   fChain->SetBranchAddress("sf_sjbtag2MUp", &sf_sjbtag2MUp, &b_sf_sjbtag2MUp);
   fChain->SetBranchAddress("sf_sjbtagGT0MUp", &sf_sjbtagGT0MUp, &b_sf_sjbtagGT0MUp);
   fChain->SetBranchAddress("sf_btag0MDown", &sf_btag0MDown, &b_sf_btag0MDown);
   fChain->SetBranchAddress("sf_btag1MDown", &sf_btag1MDown, &b_sf_btag1MDown);
   fChain->SetBranchAddress("sf_btag2MDown", &sf_btag2MDown, &b_sf_btag2MDown);
   fChain->SetBranchAddress("sf_btagGT0MDown", &sf_btagGT0MDown, &b_sf_btagGT0MDown);
   fChain->SetBranchAddress("sf_sjbtag0MDown", &sf_sjbtag0MDown, &b_sf_sjbtag0MDown);
   fChain->SetBranchAddress("sf_sjbtag1MDown", &sf_sjbtag1MDown, &b_sf_sjbtag1MDown);
   fChain->SetBranchAddress("sf_sjbtag2MDown", &sf_sjbtag2MDown, &b_sf_sjbtag2MDown);
   fChain->SetBranchAddress("sf_sjbtagGT0MDown", &sf_sjbtagGT0MDown, &b_sf_sjbtagGT0MDown);
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
   fChain->SetBranchAddress("category", &category, &b_category);
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
   fChain->SetBranchAddress("puppiUWmag", &puppiUWmag, &b_puppiUWmag);
   fChain->SetBranchAddress("puppiUWmag_JESTotalUp", &puppiUWmag_JESTotalUp, &b_puppiUWmag_JESTotalUp);
   fChain->SetBranchAddress("puppiUWmag_JESTotalDown", &puppiUWmag_JESTotalDown, &b_puppiUWmag_JESTotalDown);
   fChain->SetBranchAddress("puppiUZmag", &puppiUZmag, &b_puppiUZmag);
   fChain->SetBranchAddress("puppiUZmag_JESTotalUp", &puppiUZmag_JESTotalUp, &b_puppiUZmag_JESTotalUp);
   fChain->SetBranchAddress("puppiUZmag_JESTotalDown", &puppiUZmag_JESTotalDown, &b_puppiUZmag_JESTotalDown);
   fChain->SetBranchAddress("puppiUAmag", &puppiUAmag, &b_puppiUAmag);
   fChain->SetBranchAddress("puppiUAmag_JESTotalUp", &puppiUAmag_JESTotalUp, &b_puppiUAmag_JESTotalUp);
   fChain->SetBranchAddress("puppiUAmag_JESTotalDown", &puppiUAmag_JESTotalDown, &b_puppiUAmag_JESTotalDown);
   fChain->SetBranchAddress("puppiUperp", &puppiUperp, &b_puppiUperp);
   fChain->SetBranchAddress("puppiUperp_JESTotalUp", &puppiUperp_JESTotalUp, &b_puppiUperp_JESTotalUp);
   fChain->SetBranchAddress("puppiUperp_JESTotalDown", &puppiUperp_JESTotalDown, &b_puppiUperp_JESTotalDown);
   fChain->SetBranchAddress("puppiUpara", &puppiUpara, &b_puppiUpara);
   fChain->SetBranchAddress("puppiUpara_JESTotalUp", &puppiUpara_JESTotalUp, &b_puppiUpara_JESTotalUp);
   fChain->SetBranchAddress("puppiUpara_JESTotalDown", &puppiUpara_JESTotalDown, &b_puppiUpara_JESTotalDown);
   fChain->SetBranchAddress("puppiUmag", &puppiUmag, &b_puppiUmag);
   fChain->SetBranchAddress("puppiUmag_JESTotalUp", &puppiUmag_JESTotalUp, &b_puppiUmag_JESTotalUp);
   fChain->SetBranchAddress("puppiUmag_JESTotalDown", &puppiUmag_JESTotalDown, &b_puppiUmag_JESTotalDown);
   fChain->SetBranchAddress("pfUWmag", &pfUWmag, &b_pfUWmag);
   fChain->SetBranchAddress("pfUWmag_JESTotalUp", &pfUWmag_JESTotalUp, &b_pfUWmag_JESTotalUp);
   fChain->SetBranchAddress("pfUWmag_JESTotalDown", &pfUWmag_JESTotalDown, &b_pfUWmag_JESTotalDown);
   fChain->SetBranchAddress("pfUZmag", &pfUZmag, &b_pfUZmag);
   fChain->SetBranchAddress("pfUZmag_JESTotalUp", &pfUZmag_JESTotalUp, &b_pfUZmag_JESTotalUp);
   fChain->SetBranchAddress("pfUZmag_JESTotalDown", &pfUZmag_JESTotalDown, &b_pfUZmag_JESTotalDown);
   fChain->SetBranchAddress("pfUAmag", &pfUAmag, &b_pfUAmag);
   fChain->SetBranchAddress("pfUAmag_JESTotalUp", &pfUAmag_JESTotalUp, &b_pfUAmag_JESTotalUp);
   fChain->SetBranchAddress("pfUAmag_JESTotalDown", &pfUAmag_JESTotalDown, &b_pfUAmag_JESTotalDown);
   fChain->SetBranchAddress("pfUperp", &pfUperp, &b_pfUperp);
   fChain->SetBranchAddress("pfUperp_JESTotalUp", &pfUperp_JESTotalUp, &b_pfUperp_JESTotalUp);
   fChain->SetBranchAddress("pfUperp_JESTotalDown", &pfUperp_JESTotalDown, &b_pfUperp_JESTotalDown);
   fChain->SetBranchAddress("pfUpara", &pfUpara, &b_pfUpara);
   fChain->SetBranchAddress("pfUpara_JESTotalUp", &pfUpara_JESTotalUp, &b_pfUpara_JESTotalUp);
   fChain->SetBranchAddress("pfUpara_JESTotalDown", &pfUpara_JESTotalDown, &b_pfUpara_JESTotalDown);
   fChain->SetBranchAddress("pfUmag", &pfUmag, &b_pfUmag);
   fChain->SetBranchAddress("pfUmag_JESTotalUp", &pfUmag_JESTotalUp, &b_pfUmag_JESTotalUp);
   fChain->SetBranchAddress("pfUmag_JESTotalDown", &pfUmag_JESTotalDown, &b_pfUmag_JESTotalDown);
   fChain->SetBranchAddress("puppiUWphi", &puppiUWphi, &b_puppiUWphi);
   fChain->SetBranchAddress("puppiUWphi_JESTotalUp", &puppiUWphi_JESTotalUp, &b_puppiUWphi_JESTotalUp);
   fChain->SetBranchAddress("puppiUWphi_JESTotalDown", &puppiUWphi_JESTotalDown, &b_puppiUWphi_JESTotalDown);
   fChain->SetBranchAddress("puppiUZphi", &puppiUZphi, &b_puppiUZphi);
   fChain->SetBranchAddress("puppiUZphi_JESTotalUp", &puppiUZphi_JESTotalUp, &b_puppiUZphi_JESTotalUp);
   fChain->SetBranchAddress("puppiUZphi_JESTotalDown", &puppiUZphi_JESTotalDown, &b_puppiUZphi_JESTotalDown);
   fChain->SetBranchAddress("puppiUAphi", &puppiUAphi, &b_puppiUAphi);
   fChain->SetBranchAddress("puppiUAphi_JESTotalUp", &puppiUAphi_JESTotalUp, &b_puppiUAphi_JESTotalUp);
   fChain->SetBranchAddress("puppiUAphi_JESTotalDown", &puppiUAphi_JESTotalDown, &b_puppiUAphi_JESTotalDown);
   fChain->SetBranchAddress("puppiUphi", &puppiUphi, &b_puppiUphi);
   fChain->SetBranchAddress("puppiUphi_JESTotalUp", &puppiUphi_JESTotalUp, &b_puppiUphi_JESTotalUp);
   fChain->SetBranchAddress("puppiUphi_JESTotalDown", &puppiUphi_JESTotalDown, &b_puppiUphi_JESTotalDown);
   fChain->SetBranchAddress("pfUWphi", &pfUWphi, &b_pfUWphi);
   fChain->SetBranchAddress("pfUWphi_JESTotalUp", &pfUWphi_JESTotalUp, &b_pfUWphi_JESTotalUp);
   fChain->SetBranchAddress("pfUWphi_JESTotalDown", &pfUWphi_JESTotalDown, &b_pfUWphi_JESTotalDown);
   fChain->SetBranchAddress("pfUZphi", &pfUZphi, &b_pfUZphi);
   fChain->SetBranchAddress("pfUZphi_JESTotalUp", &pfUZphi_JESTotalUp, &b_pfUZphi_JESTotalUp);
   fChain->SetBranchAddress("pfUZphi_JESTotalDown", &pfUZphi_JESTotalDown, &b_pfUZphi_JESTotalDown);
   fChain->SetBranchAddress("pfUAphi", &pfUAphi, &b_pfUAphi);
   fChain->SetBranchAddress("pfUAphi_JESTotalUp", &pfUAphi_JESTotalUp, &b_pfUAphi_JESTotalUp);
   fChain->SetBranchAddress("pfUAphi_JESTotalDown", &pfUAphi_JESTotalDown, &b_pfUAphi_JESTotalDown);
   fChain->SetBranchAddress("pfUphi", &pfUphi, &b_pfUphi);
   fChain->SetBranchAddress("pfUphi_JESTotalUp", &pfUphi_JESTotalUp, &b_pfUphi_JESTotalUp);
   fChain->SetBranchAddress("pfUphi_JESTotalDown", &pfUphi_JESTotalDown, &b_pfUphi_JESTotalDown);
   fChain->SetBranchAddress("dphipfmet", &dphipfmet, &b_dphipfmet);
   fChain->SetBranchAddress("dphipfmet_JESTotalUp", &dphipfmet_JESTotalUp, &b_dphipfmet_JESTotalUp);
   fChain->SetBranchAddress("dphipfmet_JESTotalDown", &dphipfmet_JESTotalDown, &b_dphipfmet_JESTotalDown);
   fChain->SetBranchAddress("dphipuppimet", &dphipuppimet, &b_dphipuppimet);
   fChain->SetBranchAddress("dphipuppimet_JESTotalUp", &dphipuppimet_JESTotalUp, &b_dphipuppimet_JESTotalUp);
   fChain->SetBranchAddress("dphipuppimet_JESTotalDown", &dphipuppimet_JESTotalDown, &b_dphipuppimet_JESTotalDown);
   fChain->SetBranchAddress("dphipuppiUW", &dphipuppiUW, &b_dphipuppiUW);
   fChain->SetBranchAddress("dphipuppiUW_JESTotalUp", &dphipuppiUW_JESTotalUp, &b_dphipuppiUW_JESTotalUp);
   fChain->SetBranchAddress("dphipuppiUW_JESTotalDown", &dphipuppiUW_JESTotalDown, &b_dphipuppiUW_JESTotalDown);
   fChain->SetBranchAddress("dphipuppiUZ", &dphipuppiUZ, &b_dphipuppiUZ);
   fChain->SetBranchAddress("dphipuppiUZ_JESTotalUp", &dphipuppiUZ_JESTotalUp, &b_dphipuppiUZ_JESTotalUp);
   fChain->SetBranchAddress("dphipuppiUZ_JESTotalDown", &dphipuppiUZ_JESTotalDown, &b_dphipuppiUZ_JESTotalDown);
   fChain->SetBranchAddress("dphipuppiUA", &dphipuppiUA, &b_dphipuppiUA);
   fChain->SetBranchAddress("dphipuppiUA_JESTotalUp", &dphipuppiUA_JESTotalUp, &b_dphipuppiUA_JESTotalUp);
   fChain->SetBranchAddress("dphipuppiUA_JESTotalDown", &dphipuppiUA_JESTotalDown, &b_dphipuppiUA_JESTotalDown);
   fChain->SetBranchAddress("dphipfUW", &dphipfUW, &b_dphipfUW);
   fChain->SetBranchAddress("dphipfUW_JESTotalUp", &dphipfUW_JESTotalUp, &b_dphipfUW_JESTotalUp);
   fChain->SetBranchAddress("dphipfUW_JESTotalDown", &dphipfUW_JESTotalDown, &b_dphipfUW_JESTotalDown);
   fChain->SetBranchAddress("dphipfUZ", &dphipfUZ, &b_dphipfUZ);
   fChain->SetBranchAddress("dphipfUZ_JESTotalUp", &dphipfUZ_JESTotalUp, &b_dphipfUZ_JESTotalUp);
   fChain->SetBranchAddress("dphipfUZ_JESTotalDown", &dphipfUZ_JESTotalDown, &b_dphipfUZ_JESTotalDown);
   fChain->SetBranchAddress("dphipfUA", &dphipfUA, &b_dphipfUA);
   fChain->SetBranchAddress("dphipfUA_JESTotalUp", &dphipfUA_JESTotalUp, &b_dphipfUA_JESTotalUp);
   fChain->SetBranchAddress("dphipfUA_JESTotalDown", &dphipfUA_JESTotalDown, &b_dphipfUA_JESTotalDown);
   fChain->SetBranchAddress("dphipuppiU", &dphipuppiU, &b_dphipuppiU);
   fChain->SetBranchAddress("dphipuppiU_JESTotalUp", &dphipuppiU_JESTotalUp, &b_dphipuppiU_JESTotalUp);
   fChain->SetBranchAddress("dphipuppiU_JESTotalDown", &dphipuppiU_JESTotalDown, &b_dphipuppiU_JESTotalDown);
   fChain->SetBranchAddress("dphipfU", &dphipfU, &b_dphipfU);
   fChain->SetBranchAddress("dphipfU_JESTotalUp", &dphipfU_JESTotalUp, &b_dphipfU_JESTotalUp);
   fChain->SetBranchAddress("dphipfU_JESTotalDown", &dphipfU_JESTotalDown, &b_dphipfU_JESTotalDown);
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
   fChain->SetBranchAddress("nJot_JESAbsoluteMPFBiasUp", &nJot_JESAbsoluteMPFBiasUp, &b_nJot_JESAbsoluteMPFBiasUp);
   fChain->SetBranchAddress("nJot_JESAbsoluteMPFBiasDown", &nJot_JESAbsoluteMPFBiasDown, &b_nJot_JESAbsoluteMPFBiasDown);
   fChain->SetBranchAddress("nJot_JESAbsoluteScaleUp", &nJot_JESAbsoluteScaleUp, &b_nJot_JESAbsoluteScaleUp);
   fChain->SetBranchAddress("nJot_JESAbsoluteScaleDown", &nJot_JESAbsoluteScaleDown, &b_nJot_JESAbsoluteScaleDown);
   fChain->SetBranchAddress("nJot_JESAbsoluteStatUp", &nJot_JESAbsoluteStatUp, &b_nJot_JESAbsoluteStatUp);
   fChain->SetBranchAddress("nJot_JESAbsoluteStatDown", &nJot_JESAbsoluteStatDown, &b_nJot_JESAbsoluteStatDown);
   fChain->SetBranchAddress("nJot_JESFlavorQCDUp", &nJot_JESFlavorQCDUp, &b_nJot_JESFlavorQCDUp);
   fChain->SetBranchAddress("nJot_JESFlavorQCDDown", &nJot_JESFlavorQCDDown, &b_nJot_JESFlavorQCDDown);
   fChain->SetBranchAddress("nJot_JESFragmentationUp", &nJot_JESFragmentationUp, &b_nJot_JESFragmentationUp);
   fChain->SetBranchAddress("nJot_JESFragmentationDown", &nJot_JESFragmentationDown, &b_nJot_JESFragmentationDown);
   fChain->SetBranchAddress("nJot_JESPileUpDataMCUp", &nJot_JESPileUpDataMCUp, &b_nJot_JESPileUpDataMCUp);
   fChain->SetBranchAddress("nJot_JESPileUpDataMCDown", &nJot_JESPileUpDataMCDown, &b_nJot_JESPileUpDataMCDown);
   fChain->SetBranchAddress("nJot_JESPileUpPtBBUp", &nJot_JESPileUpPtBBUp, &b_nJot_JESPileUpPtBBUp);
   fChain->SetBranchAddress("nJot_JESPileUpPtBBDown", &nJot_JESPileUpPtBBDown, &b_nJot_JESPileUpPtBBDown);
   fChain->SetBranchAddress("nJot_JESPileUpPtEC1Up", &nJot_JESPileUpPtEC1Up, &b_nJot_JESPileUpPtEC1Up);
   fChain->SetBranchAddress("nJot_JESPileUpPtEC1Down", &nJot_JESPileUpPtEC1Down, &b_nJot_JESPileUpPtEC1Down);
   fChain->SetBranchAddress("nJot_JESPileUpPtEC2Up", &nJot_JESPileUpPtEC2Up, &b_nJot_JESPileUpPtEC2Up);
   fChain->SetBranchAddress("nJot_JESPileUpPtEC2Down", &nJot_JESPileUpPtEC2Down, &b_nJot_JESPileUpPtEC2Down);
   fChain->SetBranchAddress("nJot_JESPileUpPtRefUp", &nJot_JESPileUpPtRefUp, &b_nJot_JESPileUpPtRefUp);
   fChain->SetBranchAddress("nJot_JESPileUpPtRefDown", &nJot_JESPileUpPtRefDown, &b_nJot_JESPileUpPtRefDown);
   fChain->SetBranchAddress("nJot_JESRelativeFSRUp", &nJot_JESRelativeFSRUp, &b_nJot_JESRelativeFSRUp);
   fChain->SetBranchAddress("nJot_JESRelativeFSRDown", &nJot_JESRelativeFSRDown, &b_nJot_JESRelativeFSRDown);
   fChain->SetBranchAddress("nJot_JESRelativeJEREC1Up", &nJot_JESRelativeJEREC1Up, &b_nJot_JESRelativeJEREC1Up);
   fChain->SetBranchAddress("nJot_JESRelativeJEREC1Down", &nJot_JESRelativeJEREC1Down, &b_nJot_JESRelativeJEREC1Down);
   fChain->SetBranchAddress("nJot_JESRelativePtBBUp", &nJot_JESRelativePtBBUp, &b_nJot_JESRelativePtBBUp);
   fChain->SetBranchAddress("nJot_JESRelativePtBBDown", &nJot_JESRelativePtBBDown, &b_nJot_JESRelativePtBBDown);
   fChain->SetBranchAddress("nJot_JESRelativePtEC1Up", &nJot_JESRelativePtEC1Up, &b_nJot_JESRelativePtEC1Up);
   fChain->SetBranchAddress("nJot_JESRelativePtEC1Down", &nJot_JESRelativePtEC1Down, &b_nJot_JESRelativePtEC1Down);
   fChain->SetBranchAddress("nJot_JESRelativePtEC2Up", &nJot_JESRelativePtEC2Up, &b_nJot_JESRelativePtEC2Up);
   fChain->SetBranchAddress("nJot_JESRelativePtEC2Down", &nJot_JESRelativePtEC2Down, &b_nJot_JESRelativePtEC2Down);
   fChain->SetBranchAddress("nJot_JESRelativeStatECUp", &nJot_JESRelativeStatECUp, &b_nJot_JESRelativeStatECUp);
   fChain->SetBranchAddress("nJot_JESRelativeStatECDown", &nJot_JESRelativeStatECDown, &b_nJot_JESRelativeStatECDown);
   fChain->SetBranchAddress("nJot_JESRelativeStatFSRUp", &nJot_JESRelativeStatFSRUp, &b_nJot_JESRelativeStatFSRUp);
   fChain->SetBranchAddress("nJot_JESRelativeStatFSRDown", &nJot_JESRelativeStatFSRDown, &b_nJot_JESRelativeStatFSRDown);
   fChain->SetBranchAddress("nJot_JESSinglePionECALUp", &nJot_JESSinglePionECALUp, &b_nJot_JESSinglePionECALUp);
   fChain->SetBranchAddress("nJot_JESSinglePionECALDown", &nJot_JESSinglePionECALDown, &b_nJot_JESSinglePionECALDown);
   fChain->SetBranchAddress("nJot_JESSinglePionHCALUp", &nJot_JESSinglePionHCALUp, &b_nJot_JESSinglePionHCALUp);
   fChain->SetBranchAddress("nJot_JESSinglePionHCALDown", &nJot_JESSinglePionHCALDown, &b_nJot_JESSinglePionHCALDown);
   fChain->SetBranchAddress("nJot_JESTimePtEtaUp", &nJot_JESTimePtEtaUp, &b_nJot_JESTimePtEtaUp);
   fChain->SetBranchAddress("nJot_JESTimePtEtaDown", &nJot_JESTimePtEtaDown, &b_nJot_JESTimePtEtaDown);
   fChain->SetBranchAddress("nJotMax", &nJotMax, &b_nJotMax);
   fChain->SetBranchAddress("jotPt", jotPt, &b_jotPt);
   fChain->SetBranchAddress("jotPt_JESTotalUp", jotPt_JESTotalUp, &b_jotPt_JESTotalUp);
   fChain->SetBranchAddress("jotPt_JESTotalDown", jotPt_JESTotalDown, &b_jotPt_JESTotalDown);
   fChain->SetBranchAddress("jotPt_JESAbsoluteMPFBiasUp", jotPt_JESAbsoluteMPFBiasUp, &b_jotPt_JESAbsoluteMPFBiasUp);
   fChain->SetBranchAddress("jotPt_JESAbsoluteMPFBiasDown", jotPt_JESAbsoluteMPFBiasDown, &b_jotPt_JESAbsoluteMPFBiasDown);
   fChain->SetBranchAddress("jotPt_JESAbsoluteScaleUp", jotPt_JESAbsoluteScaleUp, &b_jotPt_JESAbsoluteScaleUp);
   fChain->SetBranchAddress("jotPt_JESAbsoluteScaleDown", jotPt_JESAbsoluteScaleDown, &b_jotPt_JESAbsoluteScaleDown);
   fChain->SetBranchAddress("jotPt_JESAbsoluteStatUp", jotPt_JESAbsoluteStatUp, &b_jotPt_JESAbsoluteStatUp);
   fChain->SetBranchAddress("jotPt_JESAbsoluteStatDown", jotPt_JESAbsoluteStatDown, &b_jotPt_JESAbsoluteStatDown);
   fChain->SetBranchAddress("jotPt_JESFlavorQCDUp", jotPt_JESFlavorQCDUp, &b_jotPt_JESFlavorQCDUp);
   fChain->SetBranchAddress("jotPt_JESFlavorQCDDown", jotPt_JESFlavorQCDDown, &b_jotPt_JESFlavorQCDDown);
   fChain->SetBranchAddress("jotPt_JESFragmentationUp", jotPt_JESFragmentationUp, &b_jotPt_JESFragmentationUp);
   fChain->SetBranchAddress("jotPt_JESFragmentationDown", jotPt_JESFragmentationDown, &b_jotPt_JESFragmentationDown);
   fChain->SetBranchAddress("jotPt_JESPileUpDataMCUp", jotPt_JESPileUpDataMCUp, &b_jotPt_JESPileUpDataMCUp);
   fChain->SetBranchAddress("jotPt_JESPileUpDataMCDown", jotPt_JESPileUpDataMCDown, &b_jotPt_JESPileUpDataMCDown);
   fChain->SetBranchAddress("jotPt_JESPileUpPtBBUp", jotPt_JESPileUpPtBBUp, &b_jotPt_JESPileUpPtBBUp);
   fChain->SetBranchAddress("jotPt_JESPileUpPtBBDown", jotPt_JESPileUpPtBBDown, &b_jotPt_JESPileUpPtBBDown);
   fChain->SetBranchAddress("jotPt_JESPileUpPtEC1Up", jotPt_JESPileUpPtEC1Up, &b_jotPt_JESPileUpPtEC1Up);
   fChain->SetBranchAddress("jotPt_JESPileUpPtEC1Down", jotPt_JESPileUpPtEC1Down, &b_jotPt_JESPileUpPtEC1Down);
   fChain->SetBranchAddress("jotPt_JESPileUpPtEC2Up", jotPt_JESPileUpPtEC2Up, &b_jotPt_JESPileUpPtEC2Up);
   fChain->SetBranchAddress("jotPt_JESPileUpPtEC2Down", jotPt_JESPileUpPtEC2Down, &b_jotPt_JESPileUpPtEC2Down);
   fChain->SetBranchAddress("jotPt_JESPileUpPtRefUp", jotPt_JESPileUpPtRefUp, &b_jotPt_JESPileUpPtRefUp);
   fChain->SetBranchAddress("jotPt_JESPileUpPtRefDown", jotPt_JESPileUpPtRefDown, &b_jotPt_JESPileUpPtRefDown);
   fChain->SetBranchAddress("jotPt_JESRelativeFSRUp", jotPt_JESRelativeFSRUp, &b_jotPt_JESRelativeFSRUp);
   fChain->SetBranchAddress("jotPt_JESRelativeFSRDown", jotPt_JESRelativeFSRDown, &b_jotPt_JESRelativeFSRDown);
   fChain->SetBranchAddress("jotPt_JESRelativeJEREC1Up", jotPt_JESRelativeJEREC1Up, &b_jotPt_JESRelativeJEREC1Up);
   fChain->SetBranchAddress("jotPt_JESRelativeJEREC1Down", jotPt_JESRelativeJEREC1Down, &b_jotPt_JESRelativeJEREC1Down);
   fChain->SetBranchAddress("jotPt_JESRelativePtBBUp", jotPt_JESRelativePtBBUp, &b_jotPt_JESRelativePtBBUp);
   fChain->SetBranchAddress("jotPt_JESRelativePtBBDown", jotPt_JESRelativePtBBDown, &b_jotPt_JESRelativePtBBDown);
   fChain->SetBranchAddress("jotPt_JESRelativePtEC1Up", jotPt_JESRelativePtEC1Up, &b_jotPt_JESRelativePtEC1Up);
   fChain->SetBranchAddress("jotPt_JESRelativePtEC1Down", jotPt_JESRelativePtEC1Down, &b_jotPt_JESRelativePtEC1Down);
   fChain->SetBranchAddress("jotPt_JESRelativePtEC2Up", jotPt_JESRelativePtEC2Up, &b_jotPt_JESRelativePtEC2Up);
   fChain->SetBranchAddress("jotPt_JESRelativePtEC2Down", jotPt_JESRelativePtEC2Down, &b_jotPt_JESRelativePtEC2Down);
   fChain->SetBranchAddress("jotPt_JESRelativeStatECUp", jotPt_JESRelativeStatECUp, &b_jotPt_JESRelativeStatECUp);
   fChain->SetBranchAddress("jotPt_JESRelativeStatECDown", jotPt_JESRelativeStatECDown, &b_jotPt_JESRelativeStatECDown);
   fChain->SetBranchAddress("jotPt_JESRelativeStatFSRUp", jotPt_JESRelativeStatFSRUp, &b_jotPt_JESRelativeStatFSRUp);
   fChain->SetBranchAddress("jotPt_JESRelativeStatFSRDown", jotPt_JESRelativeStatFSRDown, &b_jotPt_JESRelativeStatFSRDown);
   fChain->SetBranchAddress("jotPt_JESSinglePionECALUp", jotPt_JESSinglePionECALUp, &b_jotPt_JESSinglePionECALUp);
   fChain->SetBranchAddress("jotPt_JESSinglePionECALDown", jotPt_JESSinglePionECALDown, &b_jotPt_JESSinglePionECALDown);
   fChain->SetBranchAddress("jotPt_JESSinglePionHCALUp", jotPt_JESSinglePionHCALUp, &b_jotPt_JESSinglePionHCALUp);
   fChain->SetBranchAddress("jotPt_JESSinglePionHCALDown", jotPt_JESSinglePionHCALDown, &b_jotPt_JESSinglePionHCALDown);
   fChain->SetBranchAddress("jotPt_JESTimePtEtaUp", jotPt_JESTimePtEtaUp, &b_jotPt_JESTimePtEtaUp);
   fChain->SetBranchAddress("jotPt_JESTimePtEtaDown", jotPt_JESTimePtEtaDown, &b_jotPt_JESTimePtEtaDown);
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
   fChain->SetBranchAddress("jetNBtags_JESAbsoluteMPFBiasUp", &jetNBtags_JESAbsoluteMPFBiasUp, &b_jetNBtags_JESAbsoluteMPFBiasUp);
   fChain->SetBranchAddress("jetNBtags_JESAbsoluteMPFBiasDown", &jetNBtags_JESAbsoluteMPFBiasDown, &b_jetNBtags_JESAbsoluteMPFBiasDown);
   fChain->SetBranchAddress("jetNBtags_JESAbsoluteScaleUp", &jetNBtags_JESAbsoluteScaleUp, &b_jetNBtags_JESAbsoluteScaleUp);
   fChain->SetBranchAddress("jetNBtags_JESAbsoluteScaleDown", &jetNBtags_JESAbsoluteScaleDown, &b_jetNBtags_JESAbsoluteScaleDown);
   fChain->SetBranchAddress("jetNBtags_JESAbsoluteStatUp", &jetNBtags_JESAbsoluteStatUp, &b_jetNBtags_JESAbsoluteStatUp);
   fChain->SetBranchAddress("jetNBtags_JESAbsoluteStatDown", &jetNBtags_JESAbsoluteStatDown, &b_jetNBtags_JESAbsoluteStatDown);
   fChain->SetBranchAddress("jetNBtags_JESFlavorQCDUp", &jetNBtags_JESFlavorQCDUp, &b_jetNBtags_JESFlavorQCDUp);
   fChain->SetBranchAddress("jetNBtags_JESFlavorQCDDown", &jetNBtags_JESFlavorQCDDown, &b_jetNBtags_JESFlavorQCDDown);
   fChain->SetBranchAddress("jetNBtags_JESFragmentationUp", &jetNBtags_JESFragmentationUp, &b_jetNBtags_JESFragmentationUp);
   fChain->SetBranchAddress("jetNBtags_JESFragmentationDown", &jetNBtags_JESFragmentationDown, &b_jetNBtags_JESFragmentationDown);
   fChain->SetBranchAddress("jetNBtags_JESPileUpDataMCUp", &jetNBtags_JESPileUpDataMCUp, &b_jetNBtags_JESPileUpDataMCUp);
   fChain->SetBranchAddress("jetNBtags_JESPileUpDataMCDown", &jetNBtags_JESPileUpDataMCDown, &b_jetNBtags_JESPileUpDataMCDown);
   fChain->SetBranchAddress("jetNBtags_JESPileUpPtBBUp", &jetNBtags_JESPileUpPtBBUp, &b_jetNBtags_JESPileUpPtBBUp);
   fChain->SetBranchAddress("jetNBtags_JESPileUpPtBBDown", &jetNBtags_JESPileUpPtBBDown, &b_jetNBtags_JESPileUpPtBBDown);
   fChain->SetBranchAddress("jetNBtags_JESPileUpPtEC1Up", &jetNBtags_JESPileUpPtEC1Up, &b_jetNBtags_JESPileUpPtEC1Up);
   fChain->SetBranchAddress("jetNBtags_JESPileUpPtEC1Down", &jetNBtags_JESPileUpPtEC1Down, &b_jetNBtags_JESPileUpPtEC1Down);
   fChain->SetBranchAddress("jetNBtags_JESPileUpPtEC2Up", &jetNBtags_JESPileUpPtEC2Up, &b_jetNBtags_JESPileUpPtEC2Up);
   fChain->SetBranchAddress("jetNBtags_JESPileUpPtEC2Down", &jetNBtags_JESPileUpPtEC2Down, &b_jetNBtags_JESPileUpPtEC2Down);
   fChain->SetBranchAddress("jetNBtags_JESPileUpPtRefUp", &jetNBtags_JESPileUpPtRefUp, &b_jetNBtags_JESPileUpPtRefUp);
   fChain->SetBranchAddress("jetNBtags_JESPileUpPtRefDown", &jetNBtags_JESPileUpPtRefDown, &b_jetNBtags_JESPileUpPtRefDown);
   fChain->SetBranchAddress("jetNBtags_JESRelativeFSRUp", &jetNBtags_JESRelativeFSRUp, &b_jetNBtags_JESRelativeFSRUp);
   fChain->SetBranchAddress("jetNBtags_JESRelativeFSRDown", &jetNBtags_JESRelativeFSRDown, &b_jetNBtags_JESRelativeFSRDown);
   fChain->SetBranchAddress("jetNBtags_JESRelativeJEREC1Up", &jetNBtags_JESRelativeJEREC1Up, &b_jetNBtags_JESRelativeJEREC1Up);
   fChain->SetBranchAddress("jetNBtags_JESRelativeJEREC1Down", &jetNBtags_JESRelativeJEREC1Down, &b_jetNBtags_JESRelativeJEREC1Down);
   fChain->SetBranchAddress("jetNBtags_JESRelativePtBBUp", &jetNBtags_JESRelativePtBBUp, &b_jetNBtags_JESRelativePtBBUp);
   fChain->SetBranchAddress("jetNBtags_JESRelativePtBBDown", &jetNBtags_JESRelativePtBBDown, &b_jetNBtags_JESRelativePtBBDown);
   fChain->SetBranchAddress("jetNBtags_JESRelativePtEC1Up", &jetNBtags_JESRelativePtEC1Up, &b_jetNBtags_JESRelativePtEC1Up);
   fChain->SetBranchAddress("jetNBtags_JESRelativePtEC1Down", &jetNBtags_JESRelativePtEC1Down, &b_jetNBtags_JESRelativePtEC1Down);
   fChain->SetBranchAddress("jetNBtags_JESRelativePtEC2Up", &jetNBtags_JESRelativePtEC2Up, &b_jetNBtags_JESRelativePtEC2Up);
   fChain->SetBranchAddress("jetNBtags_JESRelativePtEC2Down", &jetNBtags_JESRelativePtEC2Down, &b_jetNBtags_JESRelativePtEC2Down);
   fChain->SetBranchAddress("jetNBtags_JESRelativeStatECUp", &jetNBtags_JESRelativeStatECUp, &b_jetNBtags_JESRelativeStatECUp);
   fChain->SetBranchAddress("jetNBtags_JESRelativeStatECDown", &jetNBtags_JESRelativeStatECDown, &b_jetNBtags_JESRelativeStatECDown);
   fChain->SetBranchAddress("jetNBtags_JESRelativeStatFSRUp", &jetNBtags_JESRelativeStatFSRUp, &b_jetNBtags_JESRelativeStatFSRUp);
   fChain->SetBranchAddress("jetNBtags_JESRelativeStatFSRDown", &jetNBtags_JESRelativeStatFSRDown, &b_jetNBtags_JESRelativeStatFSRDown);
   fChain->SetBranchAddress("jetNBtags_JESSinglePionECALUp", &jetNBtags_JESSinglePionECALUp, &b_jetNBtags_JESSinglePionECALUp);
   fChain->SetBranchAddress("jetNBtags_JESSinglePionECALDown", &jetNBtags_JESSinglePionECALDown, &b_jetNBtags_JESSinglePionECALDown);
   fChain->SetBranchAddress("jetNBtags_JESSinglePionHCALUp", &jetNBtags_JESSinglePionHCALUp, &b_jetNBtags_JESSinglePionHCALUp);
   fChain->SetBranchAddress("jetNBtags_JESSinglePionHCALDown", &jetNBtags_JESSinglePionHCALDown, &b_jetNBtags_JESSinglePionHCALDown);
   fChain->SetBranchAddress("jetNBtags_JESTimePtEtaUp", &jetNBtags_JESTimePtEtaUp, &b_jetNBtags_JESTimePtEtaUp);
   fChain->SetBranchAddress("jetNBtags_JESTimePtEtaDown", &jetNBtags_JESTimePtEtaDown, &b_jetNBtags_JESTimePtEtaDown);
   fChain->SetBranchAddress("jetNMBtags", &jetNMBtags, &b_jetNMBtags);
   fChain->SetBranchAddress("jetNMBtags_JESTotalUp", &jetNMBtags_JESTotalUp, &b_jetNMBtags_JESTotalUp);
   fChain->SetBranchAddress("jetNMBtags_JESTotalDown", &jetNMBtags_JESTotalDown, &b_jetNMBtags_JESTotalDown);
   fChain->SetBranchAddress("jetNMBtags_JESAbsoluteMPFBiasUp", &jetNMBtags_JESAbsoluteMPFBiasUp, &b_jetNMBtags_JESAbsoluteMPFBiasUp);
   fChain->SetBranchAddress("jetNMBtags_JESAbsoluteMPFBiasDown", &jetNMBtags_JESAbsoluteMPFBiasDown, &b_jetNMBtags_JESAbsoluteMPFBiasDown);
   fChain->SetBranchAddress("jetNMBtags_JESAbsoluteScaleUp", &jetNMBtags_JESAbsoluteScaleUp, &b_jetNMBtags_JESAbsoluteScaleUp);
   fChain->SetBranchAddress("jetNMBtags_JESAbsoluteScaleDown", &jetNMBtags_JESAbsoluteScaleDown, &b_jetNMBtags_JESAbsoluteScaleDown);
   fChain->SetBranchAddress("jetNMBtags_JESAbsoluteStatUp", &jetNMBtags_JESAbsoluteStatUp, &b_jetNMBtags_JESAbsoluteStatUp);
   fChain->SetBranchAddress("jetNMBtags_JESAbsoluteStatDown", &jetNMBtags_JESAbsoluteStatDown, &b_jetNMBtags_JESAbsoluteStatDown);
   fChain->SetBranchAddress("jetNMBtags_JESFlavorQCDUp", &jetNMBtags_JESFlavorQCDUp, &b_jetNMBtags_JESFlavorQCDUp);
   fChain->SetBranchAddress("jetNMBtags_JESFlavorQCDDown", &jetNMBtags_JESFlavorQCDDown, &b_jetNMBtags_JESFlavorQCDDown);
   fChain->SetBranchAddress("jetNMBtags_JESFragmentationUp", &jetNMBtags_JESFragmentationUp, &b_jetNMBtags_JESFragmentationUp);
   fChain->SetBranchAddress("jetNMBtags_JESFragmentationDown", &jetNMBtags_JESFragmentationDown, &b_jetNMBtags_JESFragmentationDown);
   fChain->SetBranchAddress("jetNMBtags_JESPileUpDataMCUp", &jetNMBtags_JESPileUpDataMCUp, &b_jetNMBtags_JESPileUpDataMCUp);
   fChain->SetBranchAddress("jetNMBtags_JESPileUpDataMCDown", &jetNMBtags_JESPileUpDataMCDown, &b_jetNMBtags_JESPileUpDataMCDown);
   fChain->SetBranchAddress("jetNMBtags_JESPileUpPtBBUp", &jetNMBtags_JESPileUpPtBBUp, &b_jetNMBtags_JESPileUpPtBBUp);
   fChain->SetBranchAddress("jetNMBtags_JESPileUpPtBBDown", &jetNMBtags_JESPileUpPtBBDown, &b_jetNMBtags_JESPileUpPtBBDown);
   fChain->SetBranchAddress("jetNMBtags_JESPileUpPtEC1Up", &jetNMBtags_JESPileUpPtEC1Up, &b_jetNMBtags_JESPileUpPtEC1Up);
   fChain->SetBranchAddress("jetNMBtags_JESPileUpPtEC1Down", &jetNMBtags_JESPileUpPtEC1Down, &b_jetNMBtags_JESPileUpPtEC1Down);
   fChain->SetBranchAddress("jetNMBtags_JESPileUpPtEC2Up", &jetNMBtags_JESPileUpPtEC2Up, &b_jetNMBtags_JESPileUpPtEC2Up);
   fChain->SetBranchAddress("jetNMBtags_JESPileUpPtEC2Down", &jetNMBtags_JESPileUpPtEC2Down, &b_jetNMBtags_JESPileUpPtEC2Down);
   fChain->SetBranchAddress("jetNMBtags_JESPileUpPtRefUp", &jetNMBtags_JESPileUpPtRefUp, &b_jetNMBtags_JESPileUpPtRefUp);
   fChain->SetBranchAddress("jetNMBtags_JESPileUpPtRefDown", &jetNMBtags_JESPileUpPtRefDown, &b_jetNMBtags_JESPileUpPtRefDown);
   fChain->SetBranchAddress("jetNMBtags_JESRelativeFSRUp", &jetNMBtags_JESRelativeFSRUp, &b_jetNMBtags_JESRelativeFSRUp);
   fChain->SetBranchAddress("jetNMBtags_JESRelativeFSRDown", &jetNMBtags_JESRelativeFSRDown, &b_jetNMBtags_JESRelativeFSRDown);
   fChain->SetBranchAddress("jetNMBtags_JESRelativeJEREC1Up", &jetNMBtags_JESRelativeJEREC1Up, &b_jetNMBtags_JESRelativeJEREC1Up);
   fChain->SetBranchAddress("jetNMBtags_JESRelativeJEREC1Down", &jetNMBtags_JESRelativeJEREC1Down, &b_jetNMBtags_JESRelativeJEREC1Down);
   fChain->SetBranchAddress("jetNMBtags_JESRelativePtBBUp", &jetNMBtags_JESRelativePtBBUp, &b_jetNMBtags_JESRelativePtBBUp);
   fChain->SetBranchAddress("jetNMBtags_JESRelativePtBBDown", &jetNMBtags_JESRelativePtBBDown, &b_jetNMBtags_JESRelativePtBBDown);
   fChain->SetBranchAddress("jetNMBtags_JESRelativePtEC1Up", &jetNMBtags_JESRelativePtEC1Up, &b_jetNMBtags_JESRelativePtEC1Up);
   fChain->SetBranchAddress("jetNMBtags_JESRelativePtEC1Down", &jetNMBtags_JESRelativePtEC1Down, &b_jetNMBtags_JESRelativePtEC1Down);
   fChain->SetBranchAddress("jetNMBtags_JESRelativePtEC2Up", &jetNMBtags_JESRelativePtEC2Up, &b_jetNMBtags_JESRelativePtEC2Up);
   fChain->SetBranchAddress("jetNMBtags_JESRelativePtEC2Down", &jetNMBtags_JESRelativePtEC2Down, &b_jetNMBtags_JESRelativePtEC2Down);
   fChain->SetBranchAddress("jetNMBtags_JESRelativeStatECUp", &jetNMBtags_JESRelativeStatECUp, &b_jetNMBtags_JESRelativeStatECUp);
   fChain->SetBranchAddress("jetNMBtags_JESRelativeStatECDown", &jetNMBtags_JESRelativeStatECDown, &b_jetNMBtags_JESRelativeStatECDown);
   fChain->SetBranchAddress("jetNMBtags_JESRelativeStatFSRUp", &jetNMBtags_JESRelativeStatFSRUp, &b_jetNMBtags_JESRelativeStatFSRUp);
   fChain->SetBranchAddress("jetNMBtags_JESRelativeStatFSRDown", &jetNMBtags_JESRelativeStatFSRDown, &b_jetNMBtags_JESRelativeStatFSRDown);
   fChain->SetBranchAddress("jetNMBtags_JESSinglePionECALUp", &jetNMBtags_JESSinglePionECALUp, &b_jetNMBtags_JESSinglePionECALUp);
   fChain->SetBranchAddress("jetNMBtags_JESSinglePionECALDown", &jetNMBtags_JESSinglePionECALDown, &b_jetNMBtags_JESSinglePionECALDown);
   fChain->SetBranchAddress("jetNMBtags_JESSinglePionHCALUp", &jetNMBtags_JESSinglePionHCALUp, &b_jetNMBtags_JESSinglePionHCALUp);
   fChain->SetBranchAddress("jetNMBtags_JESSinglePionHCALDown", &jetNMBtags_JESSinglePionHCALDown, &b_jetNMBtags_JESSinglePionHCALDown);
   fChain->SetBranchAddress("jetNMBtags_JESTimePtEtaUp", &jetNMBtags_JESTimePtEtaUp, &b_jetNMBtags_JESTimePtEtaUp);
   fChain->SetBranchAddress("jetNMBtags_JESTimePtEtaDown", &jetNMBtags_JESTimePtEtaDown, &b_jetNMBtags_JESTimePtEtaDown);
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
   fChain->SetBranchAddress("loosePho1r9", &loosePho1r9, &b_loosePho1r9);
   fChain->SetBranchAddress("loosePho1chIso", &loosePho1chIso, &b_loosePho1chIso);
   fChain->SetBranchAddress("loosePho1nhIso", &loosePho1nhIso, &b_loosePho1nhIso);
   fChain->SetBranchAddress("loosePho1phIso", &loosePho1phIso, &b_loosePho1phIso);
   fChain->SetBranchAddress("loosePho1hOverE", &loosePho1hOverE, &b_loosePho1hOverE);
   fChain->SetBranchAddress("loosePho1sieie", &loosePho1sieie, &b_loosePho1sieie);
   fChain->SetBranchAddress("loosePho1SelBit", &loosePho1SelBit, &b_loosePho1SelBit);
   fChain->SetBranchAddress("looseGenPho1PdgId", &looseGenPho1PdgId, &b_looseGenPho1PdgId);
   fChain->SetBranchAddress("alterPho1Pt", &alterPho1Pt, &b_alterPho1Pt);
   fChain->SetBranchAddress("alterPho1Eta", &alterPho1Eta, &b_alterPho1Eta);
   fChain->SetBranchAddress("alterPho1Phi", &alterPho1Phi, &b_alterPho1Phi);
   fChain->SetBranchAddress("alterPho1r9", &alterPho1r9, &b_alterPho1r9);
   fChain->SetBranchAddress("alterPho1chIso", &alterPho1chIso, &b_alterPho1chIso);
   fChain->SetBranchAddress("alterPho1nhIso", &alterPho1nhIso, &b_alterPho1nhIso);
   fChain->SetBranchAddress("alterPho1phIso", &alterPho1phIso, &b_alterPho1phIso);
   fChain->SetBranchAddress("alterPho1hOverE", &alterPho1hOverE, &b_alterPho1hOverE);
   fChain->SetBranchAddress("alterPho1sieie", &alterPho1sieie, &b_alterPho1sieie);
   fChain->SetBranchAddress("alterPho1SelBit", &alterPho1SelBit, &b_alterPho1SelBit);
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
   fChain->SetBranchAddress("electronPhoMatch", electronPhoMatch, &b_electronPhoMatch);
   fChain->SetBranchAddress("electronLPhoMatch", electronLPhoMatch, &b_electronLPhoMatch);
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
