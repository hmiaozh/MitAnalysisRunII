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
  kPlotWW        , // 1  
  kPlotZZ        , // 2  
  kPlotWZ        , // 3  
  kPlotWJ        , // 4  
  kPlotDY        , // 5  
  kPlotTop       , // 6  
  kPlotVVV       , // 7  
  kPlotWG        , // 8  
  kPlotZG        , // 9  
  kPlotGJ        , //10 
  kPlotNonPrompt , //11  
  kPlotBSM       , //12 
  nPlotCategories
};

std::map<int, TString> plotBaseNames={
  { kPlotData	   , "Data" },
  { kPlotWW	   , "WW" },
  { kPlotZZ	   , "ZZ" },
  { kPlotWZ	   , "WZ" },
  { kPlotWJ	   , "WJ" },
  { kPlotDY	   , "DY" },
  { kPlotTop	   , "Top" },
  { kPlotVVV	   , "VVV" },
  { kPlotWG	   , "WG" },
  { kPlotZG        , "ZG" },
  { kPlotGJ	   , "GJ" },
  { kPlotNonPrompt , "NonPrompt" },
  { kPlotBSM	   , "BSM" }
}; 

std::map<int, int> plotColors={
  { kPlotData	   , kBlack},
  { kPlotWW	   , kAzure-9},
  { kPlotZZ	   , TColor::GetColor(155,152,204)},
  { kPlotWZ	   , kViolet-9},
  { kPlotWJ	   , 901},
  { kPlotDY	   , kAzure-2},
  { kPlotTop	   , kYellow},
  { kPlotVVV	   , 809},
  { kPlotWG	   , 419},
  { kPlotZG        , kAzure-9},
  { kPlotGJ	   , kGreen-5},
  { kPlotNonPrompt , kOrange},
  { kPlotBSM	   , kGreen}
}; 

std::map<int, TString> plotNames={
    { kPlotData      , "Data"},
    { kPlotWW        , "WW"},
    { kPlotZZ	     , "ZZ"},
    { kPlotWZ	     , "WZ"},
    { kPlotWJ        , "W+jets"},
    { kPlotDY	     , "Z+jets"},
    { kPlotTop       , "Top quark"},
    { kPlotVVV       , "VVV"},
    { kPlotWG	     , "W#gamma" },
    { kPlotZG        , "Z#gamma"},
    { kPlotGJ	     , "#gamma+jets"},
    { kPlotNonPrompt , "Nonprompt"},
    { kPlotBSM       , "BSM"}
};

const double mass_el = 0.000510998928;
const double mass_mu = 0.10566;

double mcCorrection(int type, int year, int infileCat){
  double totalWeight = 1.0;

  if     (type == 0){ // VBFG
    if(year == 2017) totalWeight = totalWeight * 0.45;

    if     (year == 2017 && infileCat == kPlotWG) totalWeight = totalWeight * 0.45;
    else if(year == 2017 && infileCat == kPlotGJ) totalWeight = totalWeight * 0.45;
    else if(year == 2017 && infileCat == kPlotWJ) totalWeight = totalWeight * 0.70;

 }

  return totalWeight;
}
