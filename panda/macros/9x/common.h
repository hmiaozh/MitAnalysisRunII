#include "TH1D.h"
#include "TH2D.h"

const int nBinWSEtaCorr = 4; Float_t xbinsWSEtaCorr[nBinWSEtaCorr+1] = {0.0,1.0,1.5,2.0,2.5};
TH1D* histoWSEtaCorr = new TH1D("histoWSEtaCorr", "histoWSEtaCorr", nBinWSEtaCorr, xbinsWSEtaCorr);
const int nBinWSPtCorr = 4; Float_t xbinsWSPtCorr[nBinWSPtCorr+1] = {20,35,50,75,100};
TH1D* histoWSPtCorr = new TH1D("histoWSPtCorr", "histoWSPtCorr", nBinWSPtCorr, xbinsWSPtCorr);

const int nBinEtaJERCorr = 13; Float_t xbinsEtaJERCorr[nBinEtaJERCorr+1] = {0.000,0.522,0.783,1.131,1.305,1.740,1.930,2.043,2.322,2.500,2.853,2.964,3.139,5.191};
TH1D* histoEtaJERCorr = new TH1D("histoEtaJERCorr", "histoEtaJERCorr", nBinEtaJERCorr, xbinsEtaJERCorr);
double JERSF[nBinEtaJERCorr] = {0.0222,0.0484,0.0456,0.1397,0.1470,0.0976,0.1909,0.1501,0.2020,0.5684,0.3743,0.1089,0.1524};

double WSSF_2016[nBinWSEtaCorr]  = {1.344544,0.969373,0.980854,0.989034};
double WSSFE_2016[nBinWSEtaCorr] = {0.086280,0.049862,0.021642,0.027081};
double WSSF_2017[nBinWSEtaCorr]  = {2.120786,1.705631,1.341985,1.431982};
double WSSFE_2017[nBinWSEtaCorr] = {0.102489,0.062974,0.026880,0.029367};
double WSSF_2018[nBinWSEtaCorr]  = {2.414048,1.445222,1.400950,1.293209};
double WSSFE_2018[nBinWSEtaCorr] = {0.097769,0.052131,0.024445,0.024108};

const int nBinLepEtaCorr = 5; Float_t xbinsLepEtaCorr[nBinLepEtaCorr+1] = {0.0,0.5,1.0,1.5,2.0,2.5};
TH1D* histoLepEtaCorr = new TH1D("histoLepEtaCorr", "histoLepEtaCorr", nBinLepEtaCorr, xbinsLepEtaCorr);
double muScaleCorr_2016[nBinLepEtaCorr] = {1.000357,0.999957,1.000507,0.999696,1.000437};
double elScaleCorr_2016[nBinLepEtaCorr] = {1.000266,0.998870,0.998902,0.998738,0.998196};
double muScaleCorr_2017[nBinLepEtaCorr] = {0.999975,1.000012,1.000195,0.999833,1.000353};
double elScaleCorr_2017[nBinLepEtaCorr] = {0.999903,0.998566,0.999513,1.000157,1.000000};
double muScaleCorr_2018[nBinLepEtaCorr] = {0.999928,0.999837,0.999989,0.999455,0.999739};
double elScaleCorr_2018[nBinLepEtaCorr] = {1.002245,1.003784,0.997714,0.990361,1.010238};

const bool useZZWZEWKUnc = true;

/*TString AQGCParaName[9] = {"ft0","ft1","ft2","fm0","fm1","fm6","fm7","fs0","fs1"};
const int nscan_ft0 = 34;
const int nscan_ft1 = 34;
const int nscan_ft2 = 34;
const int nscan_fm0 = 40;
const int nscan_fm1 = 36;
const int nscan_fm6 = 34;
const int nscan_fm7 = 30;
const int nscan_fs0 = 42;
const int nscan_fs1 = 32;

const TString AQGC_ft0_range[nscan_ft0] = {"m2p0", "m1p8", "m1p4", "m1p2", "m1p0", "m0p7", "m0p5", "m0p3", "m0p2", "m0p18", "m0p14", "m0p12", "m0p1", "m0p08", "m0p06", "m0p04", "m0p02", "0p02", "0p04", "0p06", "0p08", "0p1", "0p12", "0p14", "0p18", "0p2", "0p3", "0p5", "0p7", "1p0", "1p2", "1p4", "1p8", "2p0"};
const TString AQGC_ft1_range[nscan_ft1] = {"m2p0", "m1p8", "m1p4", "m1p2", "m1p0", "m0p7", "m0p5", "m0p3", "m0p2", "m0p18", "m0p14", "m0p12", "m0p1", "m0p08", "m0p06", "m0p04", "m0p02", "0p02", "0p04", "0p06", "0p08", "0p1", "0p12", "0p14", "0p18", "0p2", "0p3", "0p5", "0p7", "1p0", "1p2", "1p4", "1p8", "2p0"};
const TString AQGC_ft2_range[nscan_ft2] = {"m4p5", "m3p9", "m3p4", "m2p9", "m2p5", "m1p7", "m1p2", "m0p9", "m0p7", "m0p50", "m0p32", "m0p26", "m0p2", "m0p14", "m0p08", "m0p04", "m0p02", "0p02", "0p04", "0p08", "0p14", "0p2", "0p26", "0p32", "0p50", "0p7", "0p9", "1p2", "1p7", "2p5", "2p9", "3p4", "3p9", "4p5"};
const TString AQGC_fm0_range[nscan_fm0] = {"m10", "m9p0", "m8p0", "m7p0", "m6p0", "m5p0", "m4p0", "m3p0", "m2p0", "m1p5", "m1p0", "m0p9", "m0p8", "m0p7", "m0p6", "m0p5", "m0p4", "m0p3", "m0p2", "m0p1", "0p1", "0p2", "0p3", "0p4", "0p5", "0p6", "0p7", "0p8", "0p9", "1p0", "1p5", "2p0", "3p0", "4p0", "5p0", "6p0", "7p0", "8p0", "9p0", "10"};
const TString AQGC_fm1_range[nscan_fm1] = {"m30", "m28", "m23", "m21", "m18", "m15", "m13", "m10", "m5p0", "m3p0", "m2p5", "m2p1", "m1p8", "m1p5", "m1p2", "m0p9", "m0p6", "m0p3", "0p3", "0p6", "0p9", "1p2", "1p5", "1p8", "2p1", "2p5", "3p0", "5p0", "10", "13", "15", "18", "21", "23", "28", "30"};
const TString AQGC_fm6_range[nscan_fm6] = {"m20", "m18", "m15", "m12", "m10", "m7p0", "m5p0", "m3p0", "m2p0", "m1p8", "m1p6", "m1p4", "m1p2", "m1p0", "m0p7", "m0p5", "m0p2", "0p2", "0p5", "0p7", "1p0", "1p2", "1p4", "1p6", "1p8", "2p0", "3p0", "5p0", "7p0", "10", "12", "15", "18", "20"};
const TString AQGC_fm7_range[nscan_fm7] = {"m40", "m35", "m30", "m25", "m20", "m15", "m10", "m5p0", "m3p5", "m3p0", "m2p5", "m2p0", "m1p5", "m1p0", "m0p5", "0p5", "1p0", "1p5", "2p0", "2p5", "3p0", "3p5", "5p0", "10", "15", "20", "25", "30", "35", "40"};
const TString AQGC_fs0_range[nscan_fs0] = {"m50", "m45", "m40", "m35", "m30", "m20", "m10", "m8p0", "m6p0", "m5p0", "m4p0", "m3p0", "m2p5", "m2p0", "m1p5", "m1p2", "m1p0", "m0p8", "m0p6", "m0p4", "m0p2", "0p2", "0p4", "0p6", "0p8","1p0", "1p2", "1p5", "2p0", "2p5", "3p0", "4p0", "5p0", "6p0", "8p0", "10", "20", "30", "35", "40", "45", "50"};
const TString AQGC_fs1_range[nscan_fs1] = {"m35", "m33", "m30", "m25", "m20", "m15", "m10", "m7p5", "m5p0", "m4p0", "m3p0", "m2p5", "m2p0", "m1p5", "m1p0", "m0p5", "0p5", "1p0", "1p5", "2p0", "2p5", "3p0", "4p0", "5p0", "7p5", "10", "15", "20", "25", "30", "33", "35"};
*/

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
  kPlotData        , // 0
  kPlotqqWW        , // 1
  kPlotggWW        , // 2
  kPlotTop         , // 3
  kPlotDY          , // 4
  kPlotEWKSSWW     , // 5
  kPlotQCDSSWW     , // 6
  kPlotEWKWZ       , // 7
  kPlotWZ          , // 8
  kPlotZZ          , // 9
  kPlotNonPrompt   , //10
  kPlotVVV         , //11
  kPlotTVX         , //12
  kPlotVG          , //13
  kPlotHiggs       , //14
  kPlotDPSWW       , //15
  kPlotWS          , //16
  kPlotEM          , //17
  kPlotOther        ,//18
  kPlotBSM         , //19
  kPlotSignal0     , //20
  kPlotSignal1     , //21
  kPlotSignal2     , //22
  kPlotSignal3     , //23
  kPlotEWKSSWW_dim8, //24
  kPlotEWKWZ_dim8  , //25
  nPlotCategories
};

std::map<int, TString> plotBaseNames={
  { kPlotData      , "data_obs" },
  //{ kPlotData	     , "Data" },
  { kPlotqqWW	     , "qqWW" },
  { kPlotggWW	     , "ggWW" },
  { kPlotTop	     , "Top" },
  { kPlotDY	     , "DY" },
  { kPlotEWKSSWW     , "EWKSSWW" },
  { kPlotQCDSSWW     , "QCDSSWW" },
  { kPlotEWKWZ	     , "EWKWZ" },
  { kPlotWZ	     , "WZ" },
  { kPlotZZ	     , "ZZ" },
  { kPlotNonPrompt   , "NonPrompt" },
  { kPlotVVV	     , "VVV" },
  { kPlotTVX	     , "TVX" },
  { kPlotVG	     , "VG" },
  { kPlotHiggs       , "Higgs" },
  { kPlotDPSWW       , "DPSWW" },
  { kPlotWS	     , "WS" },
  { kPlotEM	     , "EM" },
  { kPlotOther       , "Other" },
  { kPlotBSM	     , "BSM" },
  { kPlotSignal0     , "Signal0" },
  { kPlotSignal1     , "Signal1" },
  { kPlotSignal2     , "Signal2" },
  { kPlotSignal3     , "Signal3" },
  { kPlotEWKSSWW_dim8, "EWKSSWW_dim8" },
  { kPlotEWKWZ_dim8  , "EWKWZ_dim8" }
}; 

std::map<int, int> plotColors={
  { kPlotData	     , kBlack},
  { kPlotqqWW	     , kAzure-9},
  { kPlotggWW	     , 901},
  { kPlotTop	     , kYellow},
  { kPlotDY	     , kAzure-2},
  { kPlotEWKSSWW     , TColor::GetColor(248,206,104)},
  { kPlotQCDSSWW     , TColor::GetColor(250,202,255)},
  { kPlotEWKWZ       , kCyan+3},
  { kPlotWZ	     , TColor::GetColor(222,90,106)},
  { kPlotZZ	     , kAzure-9},
  { kPlotNonPrompt   , TColor::GetColor(155,152,204)},
  { kPlotVVV	     , 809},
  { kPlotTVX	     , kViolet+6},
  { kPlotVG	     , 419},
  { kPlotHiggs       , 842},
  { kPlotDPSWW       , kGreen},
  { kPlotWS	     , kAzure+10},
  { kPlotEM	     , kGreen-5},
  { kPlotOther       , kGreen-5},
  { kPlotBSM	     , kGreen},
  { kPlotSignal0     , TColor::GetColor(248,206,104)},
  { kPlotSignal1     , kMagenta+1},
  { kPlotSignal2     , kMagenta+2},
  { kPlotSignal3     , kMagenta+3},
  { kPlotEWKSSWW_dim8, kMagenta+4},
  { kPlotEWKWZ_dim8  , kMagenta+5}
}; 

std::map<int, TString> plotNames={
    { kPlotData        , "Data"},
    { kPlotqqWW        , "qq #rightarrow WW"},
    { kPlotggWW        , "gg #rightarrow WW"},
    { kPlotTop         , "Top quark"},
    { kPlotDY	       , "Drell-Yan"},
    { kPlotEWKSSWW     , "EWK W^{#pm}W^{#pm}"},
    { kPlotQCDSSWW     , "QCD W^{#pm}W^{#pm}"},
    { kPlotEWKWZ       , "EWK WZ"},
    { kPlotWZ	       , "WZ"},
    { kPlotZZ	       , "ZZ"},
    { kPlotNonPrompt   , "Nonprompt"},
    { kPlotVVV         , "VVV"},
    { kPlotTVX         , "tVx"},
    { kPlotVG	       , "V#gamma" },
    { kPlotHiggs       , "Higgs"},
    { kPlotDPSWW       , "DPS W^{#pm}W^{#pm}"},
    { kPlotWS	       , "Wrong sign"},
    { kPlotEM	       , "Top quark/WW"},
    { kPlotOther       , "Other bkg."},
    { kPlotBSM         , "BSM"},
    { kPlotSignal0     , "Signal 0"},
    { kPlotSignal1     , "W_{X}W_{T}"},
    { kPlotSignal2     , "Signal 2"},
    { kPlotSignal3     , "Signal 3"},
    { kPlotEWKSSWW_dim8, "EWKSSWW_dim8"},
    { kPlotEWKWZ_dim8  , "EWKWZ_dim8"}
};
 
const double mass_el = 0.000510998928;
const double mass_mu = 0.10566;

double mcCorrection(int type, int year, int jetNMBtags, int jetNBtags, int nJot, double dphillmet, int infileCat[2], ULong64_t eventNumber){
  double totalWeight = 1.0;

  if     (type == 0 &&
         (infileCat[0] == kPlotNonPrompt || infileCat[0] == kPlotTVX || infileCat[0] == kPlotWS)){ // SSWW
    if     (year == 2017 && jetNMBtags > 0) totalWeight = totalWeight * 0.95;
    else if(year == 2017 && jetNBtags  > 0) totalWeight = totalWeight * 0.58;

    else if(year == 2018 && jetNMBtags > 0) totalWeight = totalWeight * 0.75;
    else if(year == 2018 && jetNBtags  > 0) totalWeight = totalWeight * 0.96;
  }
  else if(type == 1){ // ZH
    if     (year == 2016 && infileCat[0] == kPlotDY && nJot == 0) totalWeight = totalWeight * 1.40;
    else if(year == 2016 && infileCat[0] == kPlotDY && nJot >= 1) totalWeight = totalWeight * 0.88;

    else if(year == 2017 && infileCat[0] == kPlotDY && nJot == 0) totalWeight = totalWeight * 1.45;
    else if(year == 2017 && infileCat[0] == kPlotDY && nJot >= 1) totalWeight = totalWeight * 1.10;

    else if(year == 2018 && infileCat[0] == kPlotDY && nJot == 0) totalWeight = totalWeight * 2.40;
    else if(year == 2018 && infileCat[0] == kPlotDY && nJot >= 1) totalWeight = totalWeight * 1.70;
  }

  if(type == 1 || type  == 2){ // ZH or Z
    if     (year == 2016 && infileCat[0] == kPlotDY) totalWeight = totalWeight * (0.986772 + 0.00796195 * dphillmet);
 
    else if(year == 2017 && infileCat[0] == kPlotDY) totalWeight = totalWeight * (0.968796 + 0.01901070 * dphillmet);

    else if(year == 2018 && infileCat[0] == kPlotDY) totalWeight = totalWeight * (0.917654 + 0.04973930 * dphillmet);
  }

  if(type == 0 && year != 2016 && infileCat[0] == kPlotNonPrompt && infileCat[1] == 1 && eventNumber%10 < 9) infileCat[0] = kPlotTVX;

  return totalWeight;
}
