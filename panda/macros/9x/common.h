#include "TH1D.h"
#include "TH2D.h"

double WSSF_2016[5]  = {1.442872,1.158301,0.957394,0.965762,0.911107};
double WSSFE_2016[5] = {0.287472,0.115321,0.054188,0.024140,0.031171};
double WSSF_2017[5]  = {2.100562,0.945322,1.547166,1.527053,1.472856};
double WSSFE_2017[5] = {0.285970,0.133781,0.061368,0.034251,0.035350};
double WSSF_2018[5]  = {1.621258,1.985028,1.382802,1.429252,1.247797};
double WSSFE_2018[5] = {0.164411,0.078717,0.038409,0.018284,0.018743};

const bool useZZWZEWKUnc = true;

enum selYear {Y2016, Y2017, Y2018, nYears};
const double lumiV[nYears] = {35.9, 41.5, 56.1};
const double lumiE[nYears] = {1.025, 1.023, 1.050};
const double totalLumiV = lumiV[Y2016] + lumiV[Y2017] + lumiV[Y2018];

double ewkCorrWpWp(double mjj){
  double fitPar[2]={ -5.37274e+00, -7.33731e-03};
  double xs = TMath::Max(1.0+(fitPar[0] + mjj*fitPar[1])*0.01,0.0);
  return xs;
}

enum LepSelectionBit {
 kLoose   =(1<<0),
 kFake    =(1<<1),
 kMedium  =(1<<2),
 kTight   =(1<<3),
 kDxyz    =(1<<4),
 kEleMvaWP90=(1<<5),
 kEleMvaWP80=(1<<6),
 kMvaMedium    =(1<<7),
 kMvaTight     =(1<<8),
 kMiniIsoMedium=(1<<9),
 kMiniIsoTight =(1<<10)
};

enum PhoSelectionBit {
 pMedium  =(1<<0),
 pTight   =(1<<1),
 pHighPt  =(1<<2),
 pCsafeVeto =(1<<3),
 pPixelVeto =(1<<4),
 pTrkVeto   =(1<<5)
};

enum TriggerBits {
  kMETTrig     = 0,
  kSingleEleTrig,
  kSinglePhoTrig,
  kSingleMuTrig,
  kDoubleMuTrig,
  kDoubleEleTrig,
  kEMuTrig,
  kJetHTTrig,
  kMuFakeTrig,
  kEleFakeTrig,
  kNTrig
};

enum plotCategory {
  kPlotData      , // 0 
  kPlotqqWW      , // 1  
  kPlotggWW      , // 2  
  kPlotTop       , // 3  
  kPlotDY        , // 4  
  kPlotZZ        , // 5  
  kPlotWZ        , // 6  
  kPlotEWKWZ     , // 7  
  kPlotVVV       , // 8  
  kPlotVG        , // 9  
  kPlotNonPrompt , //10  
  kPlotHiggs     , //11  
  kPlotEWKSSWW   , //12   
  kPlotQCDSSWW   , //13   
  kPlotDPSWW     , //14   
  kPlotWS        , //15   
  kPlotEM        , //16   
  kPlotBSM       , //17 
  kPlotSignal0   , //18
  kPlotSignal1   , //19
  kPlotSignal2   , //20
  kPlotSignal3   , //21
  nPlotCategories
};

std::map<int, TString> plotBaseNames={
  { kPlotData	   , "Data" },
  { kPlotqqWW	   , "qqWW" },
  { kPlotggWW	   , "ggWW" },
  { kPlotTop	   , "Top" },
  { kPlotDY	   , "DY" },
  { kPlotZZ	   , "ZZ" },
  { kPlotWZ	   , "WZ" },
  { kPlotEWKWZ	   , "EWKWZ" },
  { kPlotVVV	   , "VVV" },
  { kPlotVG	   , "VG" },
  { kPlotNonPrompt , "NonPrompt" },
  { kPlotHiggs     , "Higgs" },
  { kPlotEWKSSWW   , "EWKSSWW" },
  { kPlotQCDSSWW   , "QCDSSWW" },
  { kPlotDPSWW     , "DPSWW" },
  { kPlotWS	   , "WS" },
  { kPlotEM	   , "EM" },
  { kPlotBSM	   , "BSM" },
  { kPlotSignal0   , "Signal0" },
  { kPlotSignal1   , "Signal1" },
  { kPlotSignal2   , "Signal2" },
  { kPlotSignal3   , "Signal3" }
}; 

std::map<int, int> plotColors={
  { kPlotData	   , kBlack},
  { kPlotqqWW	   , kAzure-9},
  { kPlotggWW	   , 901},
  { kPlotTop	   , kYellow},
  { kPlotDY	   , kAzure-2},
  { kPlotZZ	   , TColor::GetColor(155,152,204)},
  { kPlotWZ	   , kViolet-9},
  { kPlotEWKWZ     , kCyan+3},
  { kPlotVVV	   , 809},
  { kPlotVG	   , 419},
  { kPlotNonPrompt , kAzure-5},
  { kPlotHiggs     , 842},
  { kPlotEWKSSWW   , 832},
  { kPlotQCDSSWW   , 798},
  { kPlotDPSWW     , TColor::GetColor(248,206,104)},
  { kPlotWS	   , kAzure+10},
  { kPlotEM	   , kGreen-5},
  { kPlotBSM	   , kGreen},
  { kPlotSignal0   , kMagenta+1},
  { kPlotSignal1   , kMagenta+2},
  { kPlotSignal2   , kMagenta+3},
  { kPlotSignal3   , kMagenta+4}
}; 

std::map<int, TString> plotNames={
    { kPlotData      , "Data"},
    { kPlotqqWW      , "qq #rightarrow WW"},
    { kPlotggWW      , "gg #rightarrow WW"},
    { kPlotTop       , "Top quark"},
    { kPlotDY	     , "Drell-Yan"},
    { kPlotZZ	     , "ZZ"},
    { kPlotWZ	     , "WZ"},
    { kPlotEWKWZ     , "EWK WZ"},
    { kPlotVVV       , "VVV"},
    { kPlotVG	     , "V#gamma" },
    { kPlotNonPrompt , "Nonprompt"},
    { kPlotHiggs     , "Higgs"},
    { kPlotEWKSSWW   , "EWK W^{#pm}W^{#pm}"},
    { kPlotQCDSSWW   , "QCD W^{#pm}W^{#pm}"},
    { kPlotDPSWW     , "DPS W^{#pm}W^{#pm}"},
    { kPlotWS	     , "Wrong sign"},
    { kPlotEM	     , "Top-quark/WW"},
    { kPlotBSM       , "BSM"},
    { kPlotSignal0   , "Signal 0"},
    { kPlotSignal1   , "Signal 1"},
    { kPlotSignal2   , "Signal 2"},
    { kPlotSignal3   , "Signal 3"}
};

const double mass_el = 0.000510998928;
const double mass_mu = 0.10566;

double mcCorrection(int year, int jetNMBtags, int jetNBtags, int infileCat){
  double totalWeight = 1.0;

  if	 (year == 2017 && jetNMBtags > 0) totalWeight = totalWeight * 0.60;
  else if(year == 2017 && jetNBtags  > 0) totalWeight = totalWeight * 0.85;

  if	 (year == 2018 && jetNMBtags > 0) totalWeight = totalWeight * 0.65;
  else if(year == 2018 && jetNBtags  > 0) totalWeight = totalWeight * 1.00;

  return totalWeight;
}

double fakeRateFactor(double pt, double eta, int pdgId, bool applyTight, TH2D *histoFakeEffSelMediumEtaPt_m, TH2D *histoFakeEffSelMediumEtaPt_e, TH2D *histoFakeEffSelTightEtaPt_m, TH2D *histoFakeEffSelTightEtaPt_e){
  double etal = eta; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
  int binXT = histoFakeEffSelMediumEtaPt_m->GetXaxis()->FindFixBin(etal);
  int binYT = histoFakeEffSelMediumEtaPt_m->GetYaxis()->FindFixBin(pt);
  
  double rate = 1.0;
  if     (TMath::Abs(pdgId) == 13 && applyTight == false) rate = TMath::Min(histoFakeEffSelMediumEtaPt_m->GetBinContent(binXT,binYT),0.999);
  else if(TMath::Abs(pdgId) == 13 && applyTight == true)  rate = TMath::Min(histoFakeEffSelTightEtaPt_m ->GetBinContent(binXT,binYT),0.999);
  else if(TMath::Abs(pdgId) == 11 && applyTight == false) rate = TMath::Min(histoFakeEffSelMediumEtaPt_e->GetBinContent(binXT,binYT),0.999);
  else if(TMath::Abs(pdgId) == 11 && applyTight == true)  rate = TMath::Min(histoFakeEffSelTightEtaPt_e ->GetBinContent(binXT,binYT),0.999);
  else printf("IMPOSSIBLE COMPUTING FAKE RATES\n");

  //if(pt<20 && applyTight == true) rate = 2*rate/(1+rate);

  return rate/(1-rate);
}

double nPUScaleFactor(TH1D *fhDPU, float npu){
  double mynpu = TMath::Min(npu,(float)99.999);
  Int_t npuxbin = fhDPU->GetXaxis()->FindBin(mynpu);
  return fhDPU->GetBinContent(npuxbin);
}

double electronToPhotonSF(double pt, int year){
  double effDA = 1.0;
  double effMC = 1.0;
  if     (year == 2016) {
     effDA = (0.0052 + 1.114 * TMath::Power(pt + 122.84, -0.75));
     effMC = (0.0050 + 2.922 * TMath::Power(pt +  87.23, -1.18));
  }
  else if(year == 2017 || year == 2018) {
     effDA = (0.0256 + 3.000 * TMath::Power(pt + 10.78, -1.43));
     effMC = (0.0068 + 0.029 * TMath::Power(pt - 22.10, -0.45));
  }
  //printf("electronToPhotonSF (pt=%.1f): %f/%f=%f\n",pt,effDA,effMC,effDA/effMC);

  return effDA/effMC;
}

double effhDPhotonScaleFactor(double pt, double eta, TString type, TH2D *fhDIdSF, TH2D *fhDVetoSF){

  if(pt>=200) pt = +199.999;

  if     (eta>=+2.4) eta = +2.399;
  else if(eta<=-2.4) eta = -2.399;

  Int_t binXA = 0;
  Int_t binYA = 0;
  Int_t binXB = 0;
  Int_t binYB = 0;

  binXA = fhDIdSF  ->GetXaxis()->FindFixBin(eta);binYA = fhDIdSF  ->GetYaxis()->FindFixBin(pt);
  
  eta = abs(eta); if(eta < 1.5) eta = 1.0; else eta = 2.0;
  binXB = fhDVetoSF->GetXaxis()->FindFixBin(eta);binYB = fhDVetoSF->GetYaxis()->FindFixBin(pt);

  double idSF   = fhDIdSF  ->GetBinContent(binXA, binYA);
  double vetoSF = fhDVetoSF->GetBinContent(binXB, binYB);
  
  if(idSF <= 0 || vetoSF <= 0) printf("photonSF <= 0! %f %f %d %d %d %d - %f %f\n",idSF,vetoSF,binXA,binYA,binXB,binYB,pt,eta);

  return idSF*vetoSF;
}

double effhDScaleFactor(double pt, double eta, int nsel, TString type, TH2D *fhDMuMediumSF, TH2D *fhDElMediumSF, TH2D *fhDElTightSF, 
TH1D *fhDMuTrkSF, TH2D *fhDElTrkSF, int npv, bool useMuIsoSF, TH2D *fhDMuIsoSF, TH1D *fhDVeryTightSF, bool applyTrkSF = true){

  if     (pt>=100 && TMath::Abs(nsel) == 13) pt =  +99.999;
  else if(pt>=200 && TMath::Abs(nsel) == 11) pt = +199.999;

  if     (eta>=+2.4) eta = +2.399;
  else if(eta<=-2.4) eta = -2.399;

  double trkSF = 1.0;
  if(TMath::Abs(nsel) == 13){
    Int_t binXT = fhDMuTrkSF->GetXaxis()->FindFixBin(eta);
    if(applyTrkSF) trkSF = fhDMuTrkSF->GetBinContent(binXT);
    if(trkSF <= 0) printf("trkSF <= 0! %f %d - %f %f\n",trkSF,binXT,pt,eta);
  }
  else if(TMath::Abs(nsel) == 11){
    Int_t binXT = fhDElTrkSF->GetXaxis()->FindFixBin(eta);
    Int_t binYT = fhDElTrkSF->GetYaxis()->FindFixBin(200.0);
    if(applyTrkSF) trkSF = fhDElTrkSF->GetBinContent(binXT,binYT);
    if(trkSF <= 0) printf("trkSF <= 0! %f %d %d - %f %f %d\n",trkSF,binXT,binYT,pt,eta,npv);
    //Int_t binXT = fhDElTrkSF->GetXaxis()->FindFixBin(eta);
    //Int_t binYT = fhDElTrkSF->GetYaxis()->FindFixBin(npv);
    //if(applyTrkSF) trkSF = fhDElTrkSF->GetBinContent(binXT,binYT);
    //if(trkSF <= 0) printf("trkSF <= 0! %f %d %d - %f %f %d\n",trkSF,binXT,binYT,pt,eta,npv);
  }
  if(trkSF <= 0) trkSF = 1.0;

  if(TMath::Abs(nsel) == 13) eta = abs(eta);
  if(TMath::Abs(nsel) == 13 && useMuIsoSF == true && pt <= 20) pt = 20.001;

  Int_t binXA = 0;
  Int_t binYA = 0;
  Int_t binXB = 0;
  Int_t binYB = 0;

  if     (TMath::Abs(nsel) == 13 && (type== "medium" || type== "default"   || type== "defaultTight"   || type== "verytight" || type== "veryverytight" || type== "medium_mva" || type== "default_mva"))  {binXA = fhDMuMediumSF->GetXaxis()->FindFixBin(eta);binYA = fhDMuMediumSF->GetYaxis()->FindFixBin(pt);}
  else if(TMath::Abs(nsel) == 11 && (type== "medium" || type== "medium_mva"))                                                                                                                           {binXA = fhDElMediumSF->GetXaxis()->FindFixBin(eta);binYA = fhDElMediumSF->GetYaxis()->FindFixBin(pt);}
  else if(TMath::Abs(nsel) == 11 && (type== "default"||type== "defaultTight" || type== "verytight" || type== "veryverytight" || type== "default_mva"))                                                  {binXA = fhDElTightSF ->GetXaxis()->FindFixBin(eta);binYA = fhDElTightSF ->GetYaxis()->FindFixBin(pt);}
  else    printf("PROBLEM WITH BINS\n");

  double result = 0.0;
  if     (TMath::Abs(nsel) == 13 && (type== "medium" || type== "default"   || type== "defaultTight"   || type== "verytight" || type== "veryverytight" || type== "medium_mva" || type== "default_mva")) result = fhDMuMediumSF->GetBinContent(binXA, binYA);
  else if(TMath::Abs(nsel) == 11 && (type== "medium" || type== "medium_mva"))                                                                                                                          result = fhDElMediumSF->GetBinContent(binXA, binYA);
  else if(TMath::Abs(nsel) == 11 &&( type== "default"|| type== "defaultTight"   || type== "verytight" || type== "veryverytight" || type== "default_mva"))                                              result = fhDElTightSF ->GetBinContent(binXA, binYA);

  if(result <= 0) printf("Result <= 0! %f %d %d %d - %f %f\n",result,nsel,binXA,binYA,pt,eta);
  if(result <= 0) result = 1.0;

  double isoSF = 1.0;
  if(useMuIsoSF == true && TMath::Abs(nsel) == 13) {
    binXB = fhDMuIsoSF->GetXaxis()->FindFixBin(eta);binYB = fhDMuIsoSF->GetYaxis()->FindFixBin(pt);
    isoSF = fhDMuIsoSF->GetBinContent(binXB, binYB);
    if(isoSF <= 0) printf("IsoSF <= 0! %f %d %d %d - %f %f\n",isoSF,nsel,binXA,binYA,pt,eta);
    if(isoSF <= 0) isoSF = 1.0;
  }

  double effVeryTight = 1.0;
  if     (TMath::Abs(nsel) == 11 && (type== "verytight" || type== "veryverytight")) {
    Int_t binXT = fhDVeryTightSF->GetXaxis()->FindFixBin(eta);
    effVeryTight = fhDVeryTightSF->GetBinContent(binXT);
  }
  //else if(TMath::Abs(nsel) == 13 && (type== "verytight" || type== "veryverytight")) {
  //  if     (pt <  30) effVeryTight = 0.992754;
  //  else if(pt <  40) effVeryTight = 0.993588;
  //  else if(pt <  50) effVeryTight = 0.994453;
  //  else if(pt <  60) effVeryTight = 0.995199;
  //  else if(pt <  80) effVeryTight = 0.996272;
  //  else if(pt < 100) effVeryTight = 0.996282;
  //  else              effVeryTight = 0.996406;
  //}
  //printf("eff: %f %f %f - %f %f - %d %d %d %d\n",result,trkSF,isoSF,pt,eta,binXA,binYA,binXB,binYB);

  return result*trkSF*isoSF*effVeryTight;
}
