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
  kPlotPhotonE0  , //12  
  kPlotPhotonE1  , //13  
  kPlotBSM       , //14 
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
  { kPlotPhotonE0  , "PhotonE0" },
  { kPlotPhotonE1  , "PhotonE1" },
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
  { kPlotPhotonE0  , kBlue+3},
  { kPlotPhotonE1  , kBlue+4},
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
    { kPlotPhotonE0  , "Mismeasured #gamma low m_{jj}"},
    { kPlotPhotonE1  , "Mismeasured #gamma high m_{jj}"},
   { kPlotBSM       , "BSM"}
};

const double mass_el = 0.000510998928;
const double mass_mu = 0.10566;

double mcCorrection(int type, int year, int infileCat, double mjj, double mtg){
  double totalWeight = 1.0;

  if(infileCat == kPlotBSM) totalWeight = totalWeight * 0.1; // 3.782;

  if     (type == 0){ // VBFG
    if     (year == 2016 && infileCat == kPlotWG) totalWeight = totalWeight * 0.25;
    else if(year == 2017 && infileCat == kPlotWG) totalWeight = totalWeight * 1.00;
    else if(year == 2018 && infileCat == kPlotWG) totalWeight = totalWeight * 1.00;


    else if(year == 2016 && infileCat == kPlotWJ && mjj <  1500 && mtg <  100) totalWeight = totalWeight * 1.872004;// * 1.95 * 0.96;
    else if(year == 2016 && infileCat == kPlotWJ && mjj <  1500              ) totalWeight = totalWeight * 3.216278;// * 1.95 * 1.65;
    else if(year == 2016 && infileCat == kPlotWJ && mjj >= 1500 && mtg <  100) totalWeight = totalWeight * 1.329084;// * 1.95 * 0.68;
    else if(year == 2016 && infileCat == kPlotWJ && mjj >= 1500              ) totalWeight = totalWeight * 3.046966;// * 1.95 * 1.55;

    else if(year == 2017 && infileCat == kPlotWJ && mjj <  1500 && mtg <  100) totalWeight = totalWeight * 0.863155;// * 1.05 * 0.81;
    else if(year == 2017 && infileCat == kPlotWJ && mjj <  1500 	     ) totalWeight = totalWeight * 1.500989;// * 1.05 * 1.29;
    else if(year == 2017 && infileCat == kPlotWJ && mjj >= 1500 && mtg <  100) totalWeight = totalWeight * 0.913045;// * 1.05 * 0.86;
    else if(year == 2017 && infileCat == kPlotWJ && mjj >= 1500 	     ) totalWeight = totalWeight * 1.040936;// * 1.05 * 1.00;

    else if(year == 2018 && infileCat == kPlotWJ && mjj <  1500 && mtg <  100) totalWeight = totalWeight * 1.300613;// * 1.50 * 0.86;
    else if(year == 2018 && infileCat == kPlotWJ && mjj <  1500 	     ) totalWeight = totalWeight * 1.736664;// * 1.50 * 1.14;
    else if(year == 2018 && infileCat == kPlotWJ && mjj >= 1500 && mtg <  100) totalWeight = totalWeight * 1.083650;// * 1.50 * 0.72;
    else if(year == 2018 && infileCat == kPlotWJ && mjj >= 1500 	     ) totalWeight = totalWeight * 3.583177;// * 1.50 * 2.30;


    else if(year == 2016 && infileCat == kPlotGJ && mjj < 1500) totalWeight = totalWeight * 3.338539;// * 2.15 * 1.31;
    else if(year == 2016 && infileCat == kPlotGJ              ) totalWeight = totalWeight * 3.280275;// * 2.15 * 1.36;

    else if(year == 2017 && infileCat == kPlotGJ && mjj < 1500) totalWeight = totalWeight * 4.109783;// * 2.90 * 1.41;
    else if(year == 2017 && infileCat == kPlotGJ              ) totalWeight = totalWeight * 3.556604;// * 2.90 * 1.23;

    else if(year == 2018 && infileCat == kPlotGJ && mjj < 1500) totalWeight = totalWeight * 3.969444;// * 3.75 * 1.06;
    else if(year == 2018 && infileCat == kPlotGJ              ) totalWeight = totalWeight * 2.670423;// * 3.75 * 0.64;

 }

  return totalWeight;
}
