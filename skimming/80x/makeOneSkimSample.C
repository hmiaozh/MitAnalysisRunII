#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TString.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>

//#include "DYMVA_WWxsec_2015/dymva_0jet_BDT.class.C"
//#include "DYMVA_WWxsec_2015/dymva_1jet_BDT.class.C"
//#include "DYMVA_WWxsec_2015/dymva_jets_BDT.class.C"

#include "NeroProducer/Core/interface/BareAll.hpp"
#include "NeroProducer/Core/interface/BareEvent.hpp"
#include "NeroProducer/Core/interface/BareMonteCarlo.hpp"
#include "NeroProducer/Core/interface/BareLeptons.hpp"
#include "NeroProducer/Core/interface/BarePhotons.hpp"
#include "NeroProducer/Core/interface/BareMet.hpp"
#include "NeroProducer/Core/interface/BareTrigger.hpp"
#include "NeroProducer/Core/interface/BareJets.hpp"
#include "NeroProducer/Core/interface/BareVertex.hpp"
#include "MitAna/Utils/interface/SimpleTable.h"

#include "MitAnalysisRunII/macros/80x/factors.h"
#include "WWAnalysis/resummation/WWpTreweight.h"

// selection bits
//            - 0  ==> ptl1>20 && ptl2>10
//            - 1  ==> QCD enriched sample
//            - 2  ==> 3l
//            - 3  ==> e-mu + MET
//            - 4  ==> Z+MET
//            - 5  ==> one photon, ptg>60
//            - 6  ==> same-sign
//            - 7  ==> e+mu + met>30 + mjj>500 + detajj>2.5

// filterType == -1 ==> all events included in the skimmed ntuple

void makeOneSkimSample(
 TString input_file         = "nero_old.root",
 TString outputFileName     = "nero_new.root",
 TString processName        = "data",
 Int_t   filterType         = 0,
 Int_t   applyWeights       = 1,
 bool doReject0WeightEvents = false
 ){

  bool fillPDFInfo = true;
  const int totalNumberSkims = 8;
 
  bool isFilterOn[totalNumberSkims] = {true,true,true,true,true,true,true,true};
  if(filterType == 2) {isFilterOn[0] = false; isFilterOn[1] = false;}
  if(filterType == 3) {isFilterOn[0] = false; isFilterOn[1] = false; isFilterOn[3] = false;}

  TFile *the_input_file = TFile::Open(input_file.Data());
  TTree *the_input_tree = (TTree*)the_input_file->FindObjectAny("events");
  TTree *the_input_all  = (TTree*)the_input_file->FindObjectAny("all");
  TTree *the_PDF_tree   = (TTree*)the_input_file->FindObjectAny("pdfReweight");
  TH1D* the_pdfReweightSums = (TH1D*)the_input_file->FindObjectAny("pdfReweightSums");

  std::vector<std::string> theInputVars_0j;
  std::vector<std::string> theInputVars_1j;
  std::vector<std::string> theInputVars_2j;
  const char* inputVars_0j[] = { "met", "metsig", "uperp", "upara", "nGoodVertices", "dilep_pt", "min_mt", "max_mt", "min_lep_met_dphi", "max_lep_met_dphi" };
  const char* inputVars_1j[] = { "met", "metsig", "jet1_met_dphi", "upara", "uperp", "nGoodVertices", "dilep_pt", "min_mt", "max_mt", "min_lep_met_dphi", "max_lep_met_dphi", "jet1_pt", "dilep_jet1_dphi" };
  const char* inputVars_2j[] = { "met", "metsig", "min_jet_met_dphi", "max_jet_met_dphi", "upara", "uperp", "nGoodVertices", "dilep_pt", "min_mt", "max_mt", "min_lep_met_dphi", "max_lep_met_dphi", "jet1_pt", "jet2_pt", "dilep_jet1_dphi", "dilep_jet2_dphi", "jet1_jet2_dphi" };
  for (unsigned int i=0;i<10;++i) theInputVars_0j.push_back(inputVars_0j[i]);
  for (unsigned int i=0;i<13;++i) theInputVars_1j.push_back(inputVars_1j[i]);
  for (unsigned int i=0;i<17;++i) theInputVars_2j.push_back(inputVars_2j[i]);
  //dymva_0j::ReadBDT rbdtDy_0j = dymva_0j::ReadBDT(theInputVars_0j);
  //dymva_1j::ReadBDT rbdtDy_1j = dymva_1j::ReadBDT(theInputVars_1j);
  //dymva_2j::ReadBDT rbdtDy_2j = dymva_2j::ReadBDT(theInputVars_2j);

  Float_t fMVACut[4][4];
  InitializeJetIdCuts(fMVACut);
  
  WWpTreweight theWWpTreweight(
              "WWAnalysis/resummation/central.dat",
              "WWAnalysis/resummation/resum_up.dat",
              "WWAnalysis/resummation/resum_down.dat",
              "WWAnalysis/resummation/scale_up.dat",
              "WWAnalysis/resummation/scale_down.dat",
              "WWAnalysis/resummation/nnlo_central.dat",
              "WWAnalysis/resummation/powheg_2l2nu_nlo.dat",
              "WWAnalysis/resummation/powheg_2l2nu_qup_nlo.dat",
              "WWAnalysis/resummation/powheg_2l2nu_qdown_nlo.dat",
              "WWAnalysis/resummation/powheg_2l2nu_sup_nlo.dat",
              "WWAnalysis/resummation/powheg_2l2nu_sdown_nlo.dat",
              "WWAnalysis/resummation/powheg_2l2nu_nnlo.dat");

  mithep::SimpleTable xstab("$CMSSW_BASE/src/MitAnalysisRunII/data/xs.dat");
  Double_t crossSection = xstab.Get(processName.Data()) * 1000.0; // cross section in fb
  printf("crossSection(%s): %f fb\n",processName.Data(),crossSection);

  BareAll eventAll0;
  eventAll0.setBranchAddresses(the_input_all);

  BareMonteCarlo eventMonteCarlo;
  eventMonteCarlo.setBranchAddresses(the_input_tree);

  BareLeptons eventLeptons;
  eventLeptons.setBranchAddresses(the_input_tree);

  BarePhotons eventPhotons;
  eventPhotons.SetExtend();
  eventPhotons.setBranchAddresses(the_input_tree);

  BareMet eventMet;
  eventMet.SetExtend();
  eventMet.setBranchAddresses(the_input_tree);

  BareTrigger eventTrigger;
  eventTrigger.setBranchAddresses(the_input_tree);

  BareJets eventJets;
  eventJets.setBranchAddresses(the_input_tree);

  //BareVertex eventVertex;
  //eventVertex.setBranchAddresses(the_input_tree);

  float dymva_= -999.;
  unsigned int nlep_= 0;
  unsigned int njets_= 0;
  the_input_tree->Branch( "dymva", &dymva_);	 
  the_input_tree->Branch( "nlep", &nlep_);     
  the_input_tree->Branch( "njets", &njets_);	 

  TFile *outputFile = new TFile(outputFileName.Data(), "RECREATE");
  outputFile->cd();
  outputFile->SaveSelf(kTRUE);
  TTree *normalizedTree0   = the_input_all ->CloneTree(0);
  TTree *normalizedTree1   = the_input_tree->CloneTree(0);
  TTree *theClone_PDF_tree;

  TTree the_SelBit_tree("SelBit_tree","a Tree to define selection bits");
  unsigned int selBit_= 0;
  the_SelBit_tree.Branch( "selBit", &selBit_);

  if(the_PDF_tree && fillPDFInfo) {
    theClone_PDF_tree = (TTree*)the_PDF_tree->CloneTree(0);
    for (int i=0; i<the_PDF_tree->GetEntries(); ++i) {
      the_PDF_tree->GetEntry(i);
      theClone_PDF_tree->Fill();
    }
  }

  if(doReject0WeightEvents == true && the_input_all->GetEntries() != the_input_tree->GetEntries()) {printf("doReject0WeightEvents can not be true\n"); doReject0WeightEvents = false;}

  UInt_t N_all  = 0;
  UInt_t N_pass = 0;
  UInt_t Filter_pass[totalNumberSkims] = {0,0,0,0,0,0,0,0};
  Double_t sumAllEvents = 0;
  Double_t sumPassEvents = 0;
  Double_t sumPassSelection[6] = {0,0,0,0,0,0};
  for (int i=0; i<the_input_all->GetEntries(); ++i) {
    the_input_all->GetEntry(i);
    if(doReject0WeightEvents == true) the_input_tree->GetEntry(i);
    if(i%100000==0) printf("eventsAll %d out of %d\n",i,(int)the_input_all->GetEntries());
    if(doReject0WeightEvents == true && eventMonteCarlo.mcWeight == 0) continue;
    if(doReject0WeightEvents == true) eventAll0.mcWeight = (double)(*eventMonteCarlo.pdfRwgt)[164]/TMath::Abs(eventMonteCarlo.mcWeight);
    //if(doReject0WeightEvents == true) eventAll0.mcWeight = (double)(*eventMonteCarlo.pdfRwgt)[164];
    if(processName.CompareTo("data") != 0 && eventAll0.mcWeight == 0) {assert(0); printf("PROBLEM, event weight == 0\n"); return;}
    if(processName.CompareTo("data") != 0) sumAllEvents = sumAllEvents + eventAll0.mcWeight;
    else                                   sumAllEvents = sumAllEvents + 1.0;
    N_all++;
    normalizedTree0->Fill(); 
  }

  TNamed *triggerNames = (TNamed*)the_input_file->FindObjectAny("triggerNames");
  printf("triggerNames: %s %s\n",triggerNames->GetName(),triggerNames->GetTitle());
  char **tokens;
  size_t numtokens;
  tokens = strsplit(triggerNames->GetTitle(), ",", &numtokens);
  for (int i = 0; i < (int)numtokens; i++) {
    printf("triggerNames(%2d): \"%s\"\n",(int)i,tokens[i]);
  }

  for (int i=0; i<the_input_tree->GetEntries(); ++i) {
    the_input_tree->GetEntry(i);
    if(i%100000==0) printf("event %d out of %d\n",i,(int)the_input_tree->GetEntries());

    if(doReject0WeightEvents == true && eventMonteCarlo.mcWeight == 0) continue;

    // Begin gen fiducial selection
    Int_t countSelectedGenLeptons = 0;
    vector<int> idGenLep;
    for(int ngen0=0; ngen0<eventMonteCarlo.p4->GetEntriesFast(); ngen0++) {
      if(TMath::Abs((int)(*eventMonteCarlo.pdgId)[ngen0]) != 11 && TMath::Abs((int)(*eventMonteCarlo.pdgId)[ngen0]) != 13) continue;
      bool isGoodFlags = ((*eventMonteCarlo.flags)[ngen0] & BareMonteCarlo::PromptFinalState) == BareMonteCarlo::PromptFinalState ||
                         ((*eventMonteCarlo.flags)[ngen0] & BareMonteCarlo::DirectPromptTauDecayProductFinalState) == BareMonteCarlo::DirectPromptTauDecayProductFinalState;
      if(!isGoodFlags) continue;
      bool passSelLepton = 
         ((*eventMonteCarlo.flags)[ngen0] & BareMonteCarlo::PromptFinalState) == BareMonteCarlo::PromptFinalState &&
         TMath::Abs(((TLorentzVector*)(*eventMonteCarlo.p4)[ngen0])->Eta()) < 2.5 &&
         ((TLorentzVector*)(*eventMonteCarlo.p4)[ngen0])->Pt() > 20;
      if(passSelLepton) {countSelectedGenLeptons++; idGenLep.push_back(ngen0);}
    }

    if(countSelectedGenLeptons >= 2){
      vector<int> idGenJet25,idGenJet30,idGenJet35,idGenJet65;
      for(int njetgen=0; njetgen<eventMonteCarlo.jetP4->GetEntriesFast(); njetgen++) {
        if(TMath::Abs(((TLorentzVector*)(*eventMonteCarlo.jetP4)[njetgen])->Eta()) >= 5.0) continue;
        bool isGenLepton = false;
        for(unsigned int nglep = 0; nglep<idGenLep.size(); nglep++) {
          if(((TLorentzVector*)(*eventMonteCarlo.p4)[idGenLep[nglep]])->DeltaR(*((TLorentzVector*)(*eventMonteCarlo.jetP4)[njetgen])) < 0.3) {
	    isGenLepton = true;
            break;
	  }
        }
        if(isGenLepton) continue;
        if(((TLorentzVector*)(*eventMonteCarlo.jetP4)[njetgen])->Pt() > 25) idGenJet25.push_back(njetgen);
        if(((TLorentzVector*)(*eventMonteCarlo.jetP4)[njetgen])->Pt() > 30) idGenJet30.push_back(njetgen);
        if(((TLorentzVector*)(*eventMonteCarlo.jetP4)[njetgen])->Pt() > 35) idGenJet35.push_back(njetgen);
        if(((TLorentzVector*)(*eventMonteCarlo.jetP4)[njetgen])->Pt() > 65) idGenJet65.push_back(njetgen);
      }

      if(idGenJet25.size() == 0) sumPassSelection[0] = sumPassSelection[0] + eventMonteCarlo.mcWeight;
      if(idGenJet30.size() == 0) sumPassSelection[1] = sumPassSelection[1] + eventMonteCarlo.mcWeight;
      if(idGenJet35.size() == 0) sumPassSelection[2] = sumPassSelection[2] + eventMonteCarlo.mcWeight;

      if(idGenJet30.size() >= 2){
        TLorentzVector dilep = ( *(TLorentzVector*)(*eventMonteCarlo.p4)[idGenLep[0]] ) + ( *(TLorentzVector*)(*eventMonteCarlo.p4)[idGenLep[1]] );
        TLorentzVector dijet = ( *(TLorentzVector*)(*eventMonteCarlo.jetP4)[idGenJet30[0]] ) +   ( *(TLorentzVector*)(*eventMonteCarlo.jetP4)[idGenJet30[1]] );
	double deltaEtaJJ = TMath::Abs(((TLorentzVector*)(*eventMonteCarlo.jetP4)[idGenJet30[0]])->Eta()-((TLorentzVector*)(*eventMonteCarlo.jetP4)[idGenJet30[1]])->Eta());
        if(deltaEtaJJ > 2.5 && dijet.M() > 300) sumPassSelection[3] = sumPassSelection[3] + eventMonteCarlo.mcWeight;
        if(deltaEtaJJ > 2.5 && dijet.M() > 500) sumPassSelection[4] = sumPassSelection[4] + eventMonteCarlo.mcWeight;
        bool fidSelATLAS = idGenJet35.size() >= 2 && idGenJet65.size() >= 1 && deltaEtaJJ > 2.0 && dijet.M() > 500 && dilep.M() > 20 && 
                           ((TLorentzVector*)(*eventMonteCarlo.p4)[idGenLep[0]])->Pt() > 27 && ((TLorentzVector*)(*eventMonteCarlo.p4)[idGenLep[1]])->Pt() > 27 &&
                           ((TLorentzVector*)(*eventMet.p4)[0])->Pt() > 30.0;
        if(fidSelATLAS == true) sumPassSelection[5] = sumPassSelection[5] + eventMonteCarlo.mcWeight;
      }
    }
    // End gen fiducial selection

    vector<int> idOnlyLep;
    int nTypeLep[2] = {0,0};
    for(int nlep=0; nlep<eventLeptons.p4->GetEntriesFast(); nlep++) {
      if(((TLorentzVector*)(*eventLeptons.p4)[nlep])->Pt() <= 10) continue;
      
      if(((int)(*eventLeptons.selBits)[nlep] & BareLeptons::LepFake)     == BareLeptons::LepFake     ||
         ((int)(*eventLeptons.selBits)[nlep] & BareLeptons::LepMedium)   == BareLeptons::LepMedium   ||
         ((int)(*eventLeptons.selBits)[nlep] & BareLeptons::LepTight)    == BareLeptons::LepTight    ||
         ((int)(*eventLeptons.selBits)[nlep] & BareLeptons::LepMediumIP) == BareLeptons::LepMediumIP ||
         ((int)(*eventLeptons.selBits)[nlep] & BareLeptons::LepTightIP)  == BareLeptons::LepTightIP) {idOnlyLep.push_back(nlep);
	 if(TMath::Abs((int)(*eventLeptons.pdgId)[nlep]) == 11) nTypeLep[0]++;
	 if(TMath::Abs((int)(*eventLeptons.pdgId)[nlep]) == 13) nTypeLep[1]++;}
    }

    /*
    vector<int> idLep;
    for(int nlep=0; nlep<eventLeptons.p4->GetEntriesFast(); nlep++) {
      if(selectIdIsoCut("default",TMath::Abs((int)(*eventLeptons.pdgId)[nlep]),TMath::Abs(((TLorentzVector*)(*eventLeptons.p4)[nlep])->Pt()),
         TMath::Abs(((TLorentzVector*)(*eventLeptons.p4)[nlep])->Eta()),(double)(*eventLeptons.iso)[nlep],(int)(*eventLeptons.selBits)[nlep],(double)(*eventLeptons.mva)[nlep]))
        											     {idLep.push_back(nlep);}
      else if(((int)(*eventLeptons.selBits)[nlep] & BareLeptons::LepFake)  == BareLeptons::LepFake ) {idLep.push_back(nlep);}
    }
    */

    Bool_t passFilter[totalNumberSkims] = {kFALSE,kFALSE,kFALSE,kFALSE,kFALSE,kFALSE,kFALSE,kFALSE};

    // ptl>20/10 filter
    if(idOnlyLep.size() >= 2 &&
       ((TLorentzVector*)(*eventLeptons.p4)[idOnlyLep[0]])->Pt() > 20 && 
       ((TLorentzVector*)(*eventLeptons.p4)[idOnlyLep[1]])->Pt() > 10) passFilter[0] = kTRUE;

    // QCD filter
    bool passTrigger = kFALSE;
    if(processName.CompareTo("data") == 0){
      for (int nt = 0; nt < (int)numtokens; nt++) {
        if((strcmp(tokens[nt],"HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v") == 0 ||
    	    strcmp(tokens[nt],"HLT_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30_v") == 0 ||
    	    strcmp(tokens[nt],"HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_v") == 0 ||
            strcmp(tokens[nt],"HLT_Mu8_TrkIsoVVL_v")  == 0 ||  	    
            strcmp(tokens[nt],"HLT_Mu17_TrkIsoVVL_v") == 0) &&
            (*eventTrigger.triggerFired)[nt] == 1) passTrigger = kTRUE;
      }
    } else {passTrigger = kTRUE;}
    if(passTrigger == kTRUE &&
       idOnlyLep.size() >= 1 &&
       ((TLorentzVector*)(*eventLeptons.p4)[idOnlyLep[0]])->Pt() > 10 && 
       ((TLorentzVector*)(*eventMet.p4)[0])->Pt() < 30.0) passFilter[1] = kTRUE;

    // MET filter
    double maxDilepPt = 0.0;
    if(idOnlyLep.size() >= 2) {
      for(unsigned int i=0; i<idOnlyLep.size()-1; i++){
    	for(unsigned int j=i+1; j<idOnlyLep.size(); j++){
          if(( ( *(TLorentzVector*)(eventLeptons.p4->At(idOnlyLep[i])) ) + ( *(TLorentzVector*)(eventLeptons.p4->At(idOnlyLep[j])) ) ).Pt() > maxDilepPt)
    	    maxDilepPt = ( ( *(TLorentzVector*)(eventLeptons.p4->At(idOnlyLep[i])) ) + ( *(TLorentzVector*)(eventLeptons.p4->At(idOnlyLep[j])) ) ).Pt();
        }
      }
    }

    // 3l filter
    if(idOnlyLep.size() >= 3) passFilter[2] = kTRUE;

    // e-mu + MET filter
    if(idOnlyLep.size() >= 2 &&
       ((TLorentzVector*)(*eventLeptons.p4)[idOnlyLep[0]])->Pt() > 20 && 
       ((TLorentzVector*)(*eventLeptons.p4)[idOnlyLep[1]])->Pt() > 10 && 
       TMath::Min(((TLorentzVector*)(*eventMet.p4)[0])->Pt(),(double)eventMet.trackMet->Pt()) > 20.0 && nTypeLep[0] > 0 && nTypeLep[1] > 0
       ) passFilter[3] = kTRUE;

    // Z + MET filter
    if(idOnlyLep.size() >= 2 &&
       ((TLorentzVector*)(*eventLeptons.p4)[idOnlyLep[0]])->Pt() > 20 && 
       ((TLorentzVector*)(*eventLeptons.p4)[idOnlyLep[1]])->Pt() > 10 && 
       maxDilepPt> 55 && ((TLorentzVector*)(*eventMet.p4)[0])->Pt() > 40) passFilter[4] = kTRUE;

    /*
    dymva_= -999.;
    nlep_= 0;
    njets_= 0;
    if(idLep.size() >= 2){
      // Begin DYMVA implementation
      TLorentzVector dilep(( ( *(TLorentzVector*)(eventLeptons.p4->At(idLep[0])) ) + ( *(TLorentzVector*)(eventLeptons.p4->At(idLep[1])) ) )); 
      double the_met = ((TLorentzVector*)(*eventMet.p4)[0])->Pt();
      double the_metsig = ((TLorentzVector*)(*eventMet.p4)[0])->Pt()/sqrt((double)eventMet.sumEtRaw);
      TVector2 metv(((TLorentzVector*)(*eventMet.p4)[0])->Px(), ((TLorentzVector*)(*eventMet.p4)[0])->Py());
      TVector2 dilv(dilep.Px(), dilep.Py());
      TVector2 utv = -1.*(metv+dilv);
      double phiv = utv.DeltaPhi(dilv);
      double the_upara = utv.Mod()*TMath::Cos(phiv);
      double the_uperp = utv.Mod()*TMath::Sin(phiv);
      double the_nGoodVertices =  (double)eventVertex.npv;
      double the_dilep_pt = dilep.Pt();
      double the_min_mt = 999999.;
      double the_max_mt = -1.;
      double the_min_lep_met_dphi = 999.;
      double the_max_lep_met_dphi = -1.;
      for(unsigned nl=0; nl<idLep.size(); nl++){
        double deltaPhiLeptonMet = TMath::Abs(((TLorentzVector*)(*eventLeptons.p4)[idLep[nl]])->DeltaPhi(*((TLorentzVector*)(*eventMet.p4)[0])));
        if(the_min_lep_met_dphi > deltaPhiLeptonMet) the_min_lep_met_dphi = deltaPhiLeptonMet;      
        if(the_max_lep_met_dphi < deltaPhiLeptonMet) the_max_lep_met_dphi = deltaPhiLeptonMet;      

        double mtW = TMath::Sqrt(2.0*((TLorentzVector*)(*eventLeptons.p4)[idLep[nl]])->Pt()*((TLorentzVector*)(*eventMet.p4)[0])->Pt()*(1.0 - cos(deltaPhiLeptonMet)));
    	if(the_min_mt > mtW) the_min_mt = mtW;
    	if(the_max_mt < mtW) the_max_mt = mtW;
      }

      vector<int> idJet;
      for(int nj=0; nj<eventJets.p4->GetEntriesFast(); nj++){
        if(((TLorentzVector*)(*eventJets.p4)[nj])->Pt() < 10) continue;
        bool passId = passJetId(fMVACut, (float)(*eventJets.puId)[nj], ((TLorentzVector*)(*eventJets.p4)[nj])->Pt(), TMath::Abs(((TLorentzVector*)(*eventJets.p4)[nj])->Eta()));
        //if(passId == false) continue;

        Bool_t isLepton = kFALSE;
        for(unsigned int nl=0; nl<idLep.size(); nl++){
          if(((TLorentzVector*)(*eventJets.p4)[nj])->DeltaR(*((TLorentzVector*)(*eventLeptons.p4)[idLep[nl]])) < 0.3) isLepton = kTRUE;
    	}
    	if(isLepton == kTRUE) continue;

        if(((TLorentzVector*)(*eventJets.p4)[nj])->Pt() < 30) continue;

        idJet.push_back(nj);
      }

      double the_jet1_met_dphi = -1;
      double the_jet1_pt = -1;
      double the_dilep_jet1_dphi = -1;
      if(idJet.size() >= 1){
    	the_jet1_met_dphi = TMath::Abs(((TLorentzVector*)(*eventJets.p4)[idJet[0]])->DeltaPhi(*((TLorentzVector*)(*eventMet.p4)[0])));
    	the_jet1_pt = ((TLorentzVector*)(*eventJets.p4)[idJet[0]])->Pt();
    	the_dilep_jet1_dphi = TMath::Abs(((TLorentzVector*)(*eventJets.p4)[idJet[0]])->DeltaPhi(dilep));
      }
      double the_min_jet_met_dphi = 999.;
      double the_max_jet_met_dphi = -1.;
      double the_jet2_pt = -1;
      double the_dilep_jet2_dphi = -1;
      double the_jet1_jet2_dphi = -1.;
      if(idJet.size() >= 2){
    	double dPhiJetMET = TMath::Abs(((TLorentzVector*)(*eventJets.p4)[idJet[0]])->DeltaPhi(*((TLorentzVector*)(*eventMet.p4)[0])));
    	if(the_min_jet_met_dphi > dPhiJetMET) the_min_jet_met_dphi = dPhiJetMET;
    	if(the_max_jet_met_dphi < dPhiJetMET) the_max_jet_met_dphi = dPhiJetMET;
        dPhiJetMET = TMath::Abs(((TLorentzVector*)(*eventJets.p4)[idJet[1]])->DeltaPhi(*((TLorentzVector*)(*eventMet.p4)[0])));
    	if(the_min_jet_met_dphi > dPhiJetMET) the_min_jet_met_dphi = dPhiJetMET;
    	if(the_max_jet_met_dphi < dPhiJetMET) the_max_jet_met_dphi = dPhiJetMET;
    	the_jet2_pt = ((TLorentzVector*)(*eventJets.p4)[idJet[1]])->Pt();
    	the_dilep_jet2_dphi = TMath::Abs(((TLorentzVector*)(*eventJets.p4)[idJet[1]])->DeltaPhi(dilep));
    	the_jet1_jet2_dphi =  TMath::Abs(((TLorentzVector*)(*eventJets.p4)[idJet[0]])->DeltaPhi(*((TLorentzVector*)(*eventJets.p4)[idJet[1]])));
      }

      if     (idJet.size() == 0) {
        std::vector<double> theInputVals;
        const double inputVals[] = {the_met, the_metsig, the_uperp, the_upara, the_nGoodVertices, the_dilep_pt, the_min_mt, the_max_mt, the_min_lep_met_dphi, the_max_lep_met_dphi};
        for (int i=0;i<10;++i) theInputVals.push_back(inputVals[i]);
        dymva_ = rbdtDy_0j.GetMvaValue(theInputVals);
      }
      else if(idJet.size() == 1) {
        std::vector<double> theInputVals;
        const double inputVals[] = {the_met, the_metsig, the_jet1_met_dphi, the_upara, the_uperp, the_nGoodVertices, the_dilep_pt, the_min_mt, the_max_mt, the_min_lep_met_dphi, the_max_lep_met_dphi, the_jet1_pt, the_dilep_jet1_dphi};
        for (int i=0;i<13;++i) theInputVals.push_back(inputVals[i]);
        dymva_ = rbdtDy_1j.GetMvaValue(theInputVals);
      }
      else {
        std::vector<double> theInputVals;
        const double inputVals[] = {the_met, the_metsig, the_min_jet_met_dphi, the_max_jet_met_dphi, the_upara, the_uperp, the_nGoodVertices, the_dilep_pt, the_min_mt, the_max_mt, the_min_lep_met_dphi, the_max_lep_met_dphi, the_jet1_pt, the_jet2_pt, the_dilep_jet1_dphi, the_dilep_jet2_dphi, the_jet1_jet2_dphi};
        for (int i=0;i<17;++i) theInputVals.push_back(inputVals[i]);
        dymva_ = rbdtDy_2j.GetMvaValue(theInputVals);
      }
      nlep_ = idLep.size();
      njets_ = idJet.size();
      // End DYMVA implementation
    } // only events with tight lepton definition
    */

    // photon filter
    {
    vector<int> idPho;
    for(int npho=0; npho<eventPhotons.p4->GetEntriesFast(); npho++) {
      if(TMath::Abs(((TLorentzVector*)(*eventPhotons.p4)[npho])->Eta()) >= 2.4) continue;
      if(((TLorentzVector*)(*eventPhotons.p4)[npho])->Pt() <= 60) continue;
      if((double)(*eventPhotons.r9)[npho] > 0.9 &&
         ((int)(*eventPhotons.selBits)[npho] & BarePhotons::PhoTight)== BarePhotons::PhoTight){idPho.push_back(npho);}
    }
    bool passTrigger = kFALSE;
    if(processName.CompareTo("data") == 0) {
      for (int nt = 0; nt < (int)numtokens; nt++) {
        if((strcmp(tokens[nt],"HLT_Photon36_R9Id90_HE10_IsoM_v") == 0 ||
   	    strcmp(tokens[nt],"HLT_Photon50_R9Id90_HE10_IsoM_v") == 0 ||
   	    strcmp(tokens[nt],"HLT_Photon75_R9Id90_HE10_IsoM_v") == 0 ||
   	    strcmp(tokens[nt],"HLT_Photon90_R9Id90_HE10_IsoM_v") == 0 ||
   	    strcmp(tokens[nt],"HLT_Photon120_R9Id90_HE10_IsoM_v") == 0 ||
   	    strcmp(tokens[nt],"HLT_Photon165_R9Id90_HE10_IsoM_v") == 0) &&
            (*eventTrigger.triggerFired)[nt] == 1) passTrigger = kTRUE;
      }
    } else {passTrigger = kTRUE;}
    if(passTrigger == kTRUE &&
       idPho.size() >= 1) passFilter[5] = kTRUE;
    }

    // same-sign filter
    if(idOnlyLep.size() >= 2 &&
       ((TLorentzVector*)(*eventLeptons.p4)[idOnlyLep[0]])->Pt() > 20 && 
       ((TLorentzVector*)(*eventLeptons.p4)[idOnlyLep[1]])->Pt() > 20 &&
       (int)(*eventLeptons.pdgId)[idOnlyLep[0]]/TMath::Abs((int)(*eventLeptons.pdgId)[idOnlyLep[0]]) ==
       (int)(*eventLeptons.pdgId)[idOnlyLep[1]]/TMath::Abs((int)(*eventLeptons.pdgId)[idOnlyLep[1]])) passFilter[6] = kTRUE;

    // e+mu + met>30 + mjj>500 + detajj>2.5 filter
    if(idOnlyLep.size() >= 2 && nTypeLep[0] > 0 && nTypeLep[1] > 0 &&
       ((TLorentzVector*)(*eventMet.p4)[0])->Pt() > 30 &&
       ((TLorentzVector*)(*eventLeptons.p4)[idOnlyLep[0]])->Pt() > 25 && 
       ((TLorentzVector*)(*eventLeptons.p4)[idOnlyLep[1]])->Pt() > 20) {
      bool passVBF = false;
      for(int njA=0; njA<eventJets.p4->GetEntriesFast(); njA++){
	if(((TLorentzVector*)(*eventJets.p4)[njA])->Pt() < 30) continue;
	for(int njB=njA+1; njB<eventJets.p4->GetEntriesFast(); njB++){
          if(((TLorentzVector*)(*eventJets.p4)[njB])->Pt() < 30) continue;
          TLorentzVector dijet = ( *(TLorentzVector*)(*eventJets.p4)[njA] ) + ( *(TLorentzVector*)(*eventJets.p4)[njB] );
          double deltaEtaJJ = TMath::Abs(((TLorentzVector*)(*eventJets.p4)[njA])->Eta()-((TLorentzVector*)(*eventJets.p4)[njB])->Eta());
          if(dijet.M() > 500 && deltaEtaJJ > 2.5) {passVBF = true; break;}
	}
      }
      if(passVBF) passFilter[7] = kTRUE;
    }

    // Make sure filter is off if we do not want to use it
    for(int nf=0; nf<totalNumberSkims; nf++) if(isFilterOn[nf] == kFALSE) passFilter[nf] = kFALSE;

    selBit_ = 0;
    if(passFilter[0] == kTRUE) selBit_ |= 1UL<<0;
    if(passFilter[1] == kTRUE) selBit_ |= 1UL<<1;
    if(passFilter[2] == kTRUE) selBit_ |= 1UL<<2;
    if(passFilter[3] == kTRUE) selBit_ |= 1UL<<3;
    if(passFilter[4] == kTRUE) selBit_ |= 1UL<<4;
    if(passFilter[5] == kTRUE) selBit_ |= 1UL<<5;
    if(passFilter[6] == kTRUE) selBit_ |= 1UL<<6;
    if(passFilter[7] == kTRUE) selBit_ |= 1UL<<7;

    if(passFilter[0] == kTRUE) Filter_pass[0]++;
    if(passFilter[1] == kTRUE) Filter_pass[1]++;
    if(passFilter[2] == kTRUE) Filter_pass[2]++;
    if(passFilter[3] == kTRUE) Filter_pass[3]++;
    if(passFilter[4] == kTRUE) Filter_pass[4]++;
    if(passFilter[5] == kTRUE) Filter_pass[5]++;
    if(passFilter[6] == kTRUE) Filter_pass[6]++;
    if(passFilter[7] == kTRUE) Filter_pass[7]++;

    if((passFilter[0] == kFALSE &&
        passFilter[1] == kFALSE &&
        passFilter[2] == kFALSE &&
        passFilter[3] == kFALSE &&
        passFilter[4] == kFALSE &&
        passFilter[5] == kFALSE &&
        passFilter[6] == kFALSE &&
        passFilter[7] == kFALSE) &&
	filterType != -1) continue;
    N_pass++;

    the_SelBit_tree.Fill(); 

    if(doReject0WeightEvents == true) eventMonteCarlo.mcWeight = (double)(*eventMonteCarlo.pdfRwgt)[164]/TMath::Abs(eventMonteCarlo.mcWeight);
    //if(doReject0WeightEvents == true) eventMonteCarlo.mcWeight = (double)(*eventMonteCarlo.pdfRwgt)[164];

    if(eventMonteCarlo.mcWeight == 0 && processName.CompareTo("data") != 0) {printf("PROBLEM WIH WEIGTHS\n");return;}

    if(eventMonteCarlo.mcWeight != 0) sumPassEvents = sumPassEvents + eventMonteCarlo.mcWeight;
    else                              sumPassEvents++;

    // weight per event in fb
    if     (processName.CompareTo("data") != 0 && applyWeights == 1){
      eventMonteCarlo.mcWeight = eventMonteCarlo.mcWeight * crossSection / sumAllEvents;
    }
    else if(processName.CompareTo("data") == 0){
      eventMonteCarlo.mcWeight = 1.0;
    }

    normalizedTree1->Fill(); 
  }
  printf("Filters: %d %d %d %d %d %d %d %d\n",Filter_pass[0],Filter_pass[1],Filter_pass[2],Filter_pass[3],Filter_pass[4],Filter_pass[5],Filter_pass[6],Filter_pass[7]);
  printf("Overall ratio: %f\n",(double)(Filter_pass[0]+Filter_pass[1]+Filter_pass[2]+Filter_pass[3]+Filter_pass[4]+Filter_pass[5]+Filter_pass[6]+Filter_pass[7])/(double)N_pass);
  printf("N pass/all = %d / %d = %f | Sum pass/all = %f / %f = %f\n",N_pass,N_all,(double)N_pass/N_all,sumPassEvents,sumAllEvents,sumPassEvents/sumAllEvents);
  printf("effPassSelection: %f %f %f %f %f %f\n",sumPassSelection[0]/sumAllEvents,sumPassSelection[1]/sumAllEvents,sumPassSelection[2]/sumAllEvents,sumPassSelection[3]/sumAllEvents,sumPassSelection[4]/sumAllEvents,sumPassSelection[5]/sumAllEvents);
  normalizedTree0->Write();
  normalizedTree1->Write();
  if(the_PDF_tree && fillPDFInfo) theClone_PDF_tree->Write();
  if(the_pdfReweightSums && fillPDFInfo) the_pdfReweightSums->Write();
  triggerNames->Write();
  the_SelBit_tree.Write();
  outputFile->Close();
}
