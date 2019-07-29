#include "TH1D.h"
#include "TH2D.h"

const int nBinEtaCorr = 5; Float_t xbinsEtaCorr[nBinEtaCorr+1] = {0.0,0.5,1.0,1.5,2.0,2.5};
TH1D* histoEtaCorr = new TH1D("histoEtaCorr", "histoEtaCorr", nBinEtaCorr, xbinsEtaCorr);

double WSSF_2016[nBinEtaCorr]  = {1.449462,1.142217,0.937766,0.980463,0.977853};
double WSSFE_2016[nBinEtaCorr] = {0.273395,0.109201,0.050027,0.021754,0.027159};
double WSSF_2017[nBinEtaCorr]  = {1.955172,1.017924,1.560682,1.522460,1.459353};
double WSSFE_2017[nBinEtaCorr] = {0.284191,0.129495,0.058164,0.031983,0.032598};
double WSSF_2018[nBinEtaCorr]  = {1.665308,2.192745,1.390234,1.391202,1.275081};
double WSSFE_2018[nBinEtaCorr] = {0.245861,0.130005,0.052591,0.024503,0.024187};

double muScaleCorr_2016[nBinEtaCorr] = {1.000357,0.999957,1.000507,0.999696,1.000437};
double elScaleCorr_2016[nBinEtaCorr] = {1.000266,0.998870,0.998902,0.998738,0.998196};
double muScaleCorr_2017[nBinEtaCorr] = {0.999975,1.000012,1.000195,0.999833,1.000353};
double elScaleCorr_2017[nBinEtaCorr] = {0.999903,0.998566,0.999513,1.000157,1.000000};
double muScaleCorr_2018[nBinEtaCorr] = {0.999928,0.999837,0.999989,0.999455,0.999739};
double elScaleCorr_2018[nBinEtaCorr] = {1.002245,1.003784,0.997714,0.990361,1.010238};

const bool useZZWZEWKUnc = true;

double ewkCorrWpWp(double mjj){
  double fitPar[2]={ -5.37274e+00, -7.33731e-03};
  double xs = TMath::Max(1.0+(fitPar[0] + mjj*fitPar[1])*0.01,0.0);
  return xs;
}

enum selYear {Y2016, Y2017, Y2018, nYears};
const double lumiV[nYears] = {35.9, 41.5, 60.0};
const double lumiE[nYears] = {1.025, 1.023, 1.025};
const double totalLumiV = lumiV[Y2016] + lumiV[Y2017] + lumiV[Y2018];

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
  { kPlotNonPrompt , kAzure-9},
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
    { kPlotEM	     , "Top quark/WW"},
    { kPlotBSM       , "BSM"},
    { kPlotSignal0   , "Signal 0"},
    { kPlotSignal1   , "Signal 1"},
    { kPlotSignal2   , "Signal 2"},
    { kPlotSignal3   , "Signal 3"}
};

const double mass_el = 0.000510998928;
const double mass_mu = 0.10566;

double mcCorrection(int type, int year, int jetNMBtags, int jetNBtags, int nJot, double dphillmet, int infileCat){
  double totalWeight = 1.0;

  if     (type == 0){ // SSWW
    if     (year == 2017 && jetNMBtags > 0) totalWeight = totalWeight * 0.70;
    else if(year == 2017 && jetNBtags  > 0) totalWeight = totalWeight * 0.95;

    if     (year == 2018 && jetNMBtags > 0) totalWeight = totalWeight * 0.70;
    else if(year == 2018 && jetNBtags  > 0) totalWeight = totalWeight * 1.00;
  }
  else if(type == 1){ // ZH
    if     (year == 2016 && infileCat == kPlotDY && nJot == 0) totalWeight = totalWeight * 1.40;
    else if(year == 2016 && infileCat == kPlotDY && nJot >= 1) totalWeight = totalWeight * 0.88;

    else if(year == 2017 && infileCat == kPlotDY && nJot == 0) totalWeight = totalWeight * 1.45;
    else if(year == 2017 && infileCat == kPlotDY && nJot >= 1) totalWeight = totalWeight * 1.10;

    else if(year == 2018 && infileCat == kPlotDY && nJot == 0) totalWeight = totalWeight * 2.40;
    else if(year == 2018 && infileCat == kPlotDY && nJot >= 1) totalWeight = totalWeight * 1.70;
  }

  if(type == 1 || type  == 2){ // ZH or Z
    if     (year == 2016 && infileCat == kPlotDY) totalWeight = totalWeight * (0.986772 + 0.00796195 * dphillmet);
 
    else if(year == 2017 && infileCat == kPlotDY) totalWeight = totalWeight * (0.968796 + 0.01901070 * dphillmet);

    else if(year == 2018 && infileCat == kPlotDY) totalWeight = totalWeight * (0.917654 + 0.04973930 * dphillmet);
  }

  return totalWeight;
}
