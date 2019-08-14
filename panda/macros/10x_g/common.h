#include "TH1D.h"
#include "TH2D.h"

enum selYear {Y2016, Y2017, Y2018, nYears};
const double lumiV[nYears] = {27.5, 41.5, 60.0};
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
   pTrkVeto   =(1<<5),
   pMediumNM1  =(1<<6),
   pMediumPanda =(1<<7)
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
    kVBFPhoTrig,
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

  if(infileCat == kPlotBSM) totalWeight = totalWeight * 0.1; // 3.782;

  if     (type == 0){ // VBFG
    if     (year == 2016 && infileCat == kPlotWG) totalWeight = totalWeight * 0.20;
    else if(year == 2017 && infileCat == kPlotWG) totalWeight = totalWeight * 0.25;
    else if(year == 2018 && infileCat == kPlotWG) totalWeight = totalWeight * 0.25;

    else if(year == 2016 && infileCat == kPlotWJ) totalWeight = totalWeight * 1.85;
    else if(year == 2017 && infileCat == kPlotWJ) totalWeight = totalWeight * 1.05;
    else if(year == 2018 && infileCat == kPlotWJ) totalWeight = totalWeight * 1.70;

    else if(year == 2016 && infileCat == kPlotGJ) totalWeight = totalWeight * 2.10;
    else if(year == 2017 && infileCat == kPlotGJ) totalWeight = totalWeight * 3.00;
    else if(year == 2018 && infileCat == kPlotGJ) totalWeight = totalWeight * 3.00;

 }

  return totalWeight;
}
