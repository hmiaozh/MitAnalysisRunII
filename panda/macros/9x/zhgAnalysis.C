#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TString.h>
#include <TRandom.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <iostream>
#include <fstream>
#include "TLorentzVector.h"

#include "MitAnalysisRunII/panda/macros/9x/pandaFlat.C"
#include "MitAnalysisRunII/panda/macros/9x/common.h"
#include "MitAnalysisRunII/panda/macros/9x/applyCorrections.h"

const bool isSingleLeptonAna = false;
const bool isDEBUG = false;
const bool showSyst = true;
const unsigned int period = 0;
const double mcPrescale = 1;
const bool usePureMC = true; // if true, passLooseLepId not applied
enum selType                     { ZHGSEL,   BTAGSEL,   ZLGSEL,   WZSEL,   WZGSEL,   ZZSEL,   WWSEL, nSelTypes};
TString selTypeName[nSelTypes]=  {"ZHGSEL", "BTAGSEL", "ZLGSEL", "WZSEL", "WZGSEL", "ZZSEL", "WWSEL"};
enum systType                     {JESUP=0, JESDOWN,  SCALEMUP,  SCALEMDOWN,  SCALEEUP,  SCALEEDOWN,  SCALEGUP,  SCALEGDOWN, nSystTypes};
TString systTypeName[nSystTypes]= {"JESUP","JESDOWN","SCALEMUP","SCALEMDOWN","SCALEEUP","SCALEEDOWN","SCALEGUP","SCALEGDOWN"};

const double pdfUncs[2] = {1.010, 1.016};

const double muScale  = 1.01;
const double elScaleB = 1.01;
const double elScaleE = 1.02;
const double phScaleB = 1.01;
const double phScaleE = 1.02;

void zhgAnalysis(
int year, bool isDesk014 = false, int mH = 125
){
  int whichYear = -1;
  if     (year == 2016) whichYear = Y2016;
  else if(year == 2017) whichYear = Y2017;
  else if(year == 2018) whichYear = Y2018;
  else {printf("Wrong year (%d)!\n",year); return;}

  TString inputFolder = "/data/t3home000";
  if(isDesk014 == true) inputFolder = "/local";

  //*******************************************************
  //Inputs
  //*******************************************************
  double WSSF[nBinEtaCorr],WSSFE[nBinEtaCorr];
  double muScaleCorr[nBinEtaCorr],elScaleCorr[nBinEtaCorr];
  if     (year == 2016){
    for(int i=0; i<nBinEtaCorr; i++) {WSSF[i] = WSSF_2016[i]; WSSFE[i] = WSSFE_2016[i]; muScaleCorr[i] = muScaleCorr_2016[i]; elScaleCorr[i] = elScaleCorr_2016[i];}
  }
  else if(year == 2017){
    for(int i=0; i<nBinEtaCorr; i++) {WSSF[i] = WSSF_2017[i]; WSSFE[i] = WSSFE_2017[i]; muScaleCorr[i] = muScaleCorr_2017[i]; elScaleCorr[i] = elScaleCorr_2017[i];}
  }
  else if(year == 2018){
    for(int i=0; i<nBinEtaCorr; i++) {WSSF[i] = WSSF_2018[i]; WSSFE[i] = WSSFE_2018[i]; muScaleCorr[i] = muScaleCorr_2018[i]; elScaleCorr[i] = elScaleCorr_2018[i];}
  }

  printf("muScale:\n");for(int i=0; i<nBinEtaCorr; i++) printf("%f,",muScaleCorr[i]); printf("\n");
  printf("elScale:\n");for(int i=0; i<nBinEtaCorr; i++) printf("%f,",elScaleCorr[i]); printf("\n");

  vector<TString> infileName_;
  vector<int> infileCat_;

  TString filesPath;
  TString fLepton_FakesName = Form("MitAnalysisRunII/data/90x/histoFakeEtaPt_%d.root",year);
  TString puPath;
  TString photonSFPath;
  TString elephoSFPath = Form("MitAnalysisRunII/data/90x/histoDY0LGSF_%d.root",year);
  TString trgSFPath = Form("MitAnalysisRunII/data/90x/histo_triggerEff_sel0_%d.root",year);
  TString effSFPath = Form("MitAnalysisRunII/data/90x/histoDY0EffSFStudy_%d.root",year);
  //TString npvPath = Form("MitAnalysisRunII/data/90x/npvWeights_%d.root",year);
  if(year == 2018) {
    filesPath = Form("%s/ceballos/panda/v_006_3/",inputFolder.Data());
    puPath = "MitAnalysisRunII/data/90x/puWeights_90x_2018.root";
    photonSFPath = "MitAnalysisRunII/data/90x/2018_PhotonsMedium.root";

    infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	         infileCat_.push_back(kPlotData);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		 infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		         infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data())); infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sDYNJetsToLL_NLO.root",filesPath.Data()));      infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));		         infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sWZ3l_amcnlo.root" ,filesPath.Data()));         infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTVV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sZH_ZToLL_HToGDarkG_M%d.root" ,filesPath.Data(),mH)); infileCat_.push_back(kPlotBSM);
  }
  else if(year == 2017) {
    filesPath = Form("%s/ceballos/panda/v_004_3/",inputFolder.Data());
    puPath = "MitAnalysisRunII/data/90x/puWeights_90x_2017.root";
    photonSFPath = "MitAnalysisRunII/data/90x/egammaEffi.txt_EGM2D_runBCDEF_passingMedium94X.root";

    infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	         infileCat_.push_back(kPlotData);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		 infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		         infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data())); infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sDYNJetsToLL_NLO.root",filesPath.Data()));      infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));		         infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sWZ3l_powheg_mll1.root" ,filesPath.Data()));    infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	         infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTVV.root" ,filesPath.Data()));  	         infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sZH_ZToLL_HToGDarkG_M%d.root" ,filesPath.Data(),mH)); infileCat_.push_back(kPlotBSM);
  }
  else if(year == 2016) {
    filesPath = Form("%s/ceballos/panda/v_002_3/",inputFolder.Data());
    puPath = "MitAnalysisRunII/data/80x/puWeights_80x_37ifb.root";
    photonSFPath = "MitAnalysisRunII/data/80x/photon_scalefactors_37ifb.root";

    infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	          infileCat_.push_back(kPlotData);
    infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		          infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotEM);
    infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data()));  infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sDYJetsToLL_Pt0To50.root",filesPath.Data()));    infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sDYJetsToLL_Pt50To100.root",filesPath.Data()));  infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sDYJetsToLL_Pt100To250.root",filesPath.Data())); infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sDYJetsToLL_Pt250To400.root",filesPath.Data())); infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sDYJetsToLL_Pt400To650.root",filesPath.Data())); infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sDYJetsToLL_Pt650ToInf.root",filesPath.Data())); infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));		          infileCat_.push_back(kPlotVG);
    infileName_.push_back(Form("%sWZ.root" ,filesPath.Data()));	                  infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sWGstar.root" ,filesPath.Data()));               infileCat_.push_back(kPlotWZ);
    infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);
    infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotVVV);
    infileName_.push_back(Form("%sZH_ZToLL_HToGDarkG_M%d.root" ,filesPath.Data(),mH)); infileCat_.push_back(kPlotBSM);
  }
  else {
    return;
  }

  //infileName_.clear();infileCat_.clear();
  //infileName_.push_back(Form("%sZH_ZToLL_HToGDarkG_M%d.root" ,filesPath.Data(),mH)); infileCat_.push_back(kPlotBSM);
  //infileName_.push_back(Form("%sVG.root" ,filesPath.Data())); infileCat_.push_back(kPlotVG);

  TFile *fLepton_Fakes = TFile::Open(fLepton_FakesName.Data());
  TH2D* histoFakeEffSelMediumEtaPt_m = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_2_0"); histoFakeEffSelMediumEtaPt_m->SetDirectory(0);
  TH2D* histoFakeEffSelMediumEtaPt_e = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_0_1"); histoFakeEffSelMediumEtaPt_e->SetDirectory(0);
  TH2D* histoFakeEffSelTightEtaPt_m  = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_2_0"); histoFakeEffSelTightEtaPt_m ->SetDirectory(0);
  TH2D* histoFakeEffSelTightEtaPt_e  = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_0_1"); histoFakeEffSelTightEtaPt_e ->SetDirectory(0);

  TFile *fLepton_Eff = TFile::Open(effSFPath.Data());
  TH2D* histoLepEffSelMediumEtaPt_m = (TH2D*)fLepton_Eff->Get("histoEffSFStudy_2_0"); histoLepEffSelMediumEtaPt_m->SetDirectory(0);
  TH2D* histoLepEffSelMediumEtaPt_e = (TH2D*)fLepton_Eff->Get("histoEffSFStudy_0_1"); histoLepEffSelMediumEtaPt_e->SetDirectory(0);
  TH2D* histoLepEffSelTightEtaPt_m  = (TH2D*)fLepton_Eff->Get("histoEffSFStudy_2_0"); histoLepEffSelTightEtaPt_m ->SetDirectory(0);   
  TH2D* histoLepEffSelTightEtaPt_e  = (TH2D*)fLepton_Eff->Get("histoEffSFStudy_0_1"); histoLepEffSelTightEtaPt_e ->SetDirectory(0);
  fLepton_Eff->Close();

  TFile *fPUFile = TFile::Open(Form("%s",puPath.Data()));
  TH1D *fhDPU     = (TH1D*)(fPUFile->Get("puWeights"));     assert(fhDPU);     fhDPU    ->SetDirectory(0);
  TH1D *fhDPUUp   = (TH1D*)(fPUFile->Get("puWeightsUp"));   assert(fhDPUUp);   fhDPUUp  ->SetDirectory(0);
  TH1D *fhDPUDown = (TH1D*)(fPUFile->Get("puWeightsDown")); assert(fhDPUDown); fhDPUDown->SetDirectory(0);
  delete fPUFile;

  TFile *fPhotonSF = TFile::Open(photonSFPath.Data());
  TH2D *fhDPhotonSF       = (TH2D*)(fPhotonSF->Get("EGamma_SF2D")); assert(fhDPhotonSF); fhDPhotonSF->SetDirectory(0);
  TH2D *fhDElectronVetoSF = (TH2D*)(fPhotonSF->Get("Scaling_Factors_HasPix_R9 Inclusive")); assert(fhDElectronVetoSF); fhDElectronVetoSF->SetDirectory(0);
  delete fPhotonSF;

  TFile *fElePhoSF = TFile::Open(elephoSFPath.Data());
  TH2D *fhDElePhoSF    = (TH2D*)(fElePhoSF->Get("histoLGSF"));    assert(fhDElePhoSF);    fhDElePhoSF  ->SetDirectory(0);
  TH2D *fhDElePhoEffda = (TH2D*)(fElePhoSF->Get("histoLGEffda")); assert(fhDElePhoEffda); fhDElePhoEffda->SetDirectory(0);
  delete fElePhoSF;

  TFile *ftrgSF = TFile::Open(trgSFPath.Data());
  TH2D *trgSFMMBB = (TH2D*)(ftrgSF->Get("trgSFMMBB")); assert(trgSFMMBB); trgSFMMBB->SetDirectory(0);
  TH2D *trgSFMMEB = (TH2D*)(ftrgSF->Get("trgSFMMEB")); assert(trgSFMMEB); trgSFMMEB->SetDirectory(0);
  TH2D *trgSFMMBE = (TH2D*)(ftrgSF->Get("trgSFMMBE")); assert(trgSFMMBE); trgSFMMBE->SetDirectory(0);
  TH2D *trgSFMMEE = (TH2D*)(ftrgSF->Get("trgSFMMEE")); assert(trgSFMMEE); trgSFMMEE->SetDirectory(0);
  TH2D *trgSFEEBB = (TH2D*)(ftrgSF->Get("trgSFEEBB")); assert(trgSFEEBB); trgSFEEBB->SetDirectory(0);
  TH2D *trgSFEEEB = (TH2D*)(ftrgSF->Get("trgSFEEEB")); assert(trgSFEEEB); trgSFEEEB->SetDirectory(0);
  TH2D *trgSFEEBE = (TH2D*)(ftrgSF->Get("trgSFEEBE")); assert(trgSFEEBE); trgSFEEBE->SetDirectory(0);
  TH2D *trgSFEEEE = (TH2D*)(ftrgSF->Get("trgSFEEEE")); assert(trgSFEEEE); trgSFEEEE->SetDirectory(0);
  TH2D *trgSFMEBB = (TH2D*)(ftrgSF->Get("trgSFMEBB")); assert(trgSFMEBB); trgSFMEBB->SetDirectory(0);
  TH2D *trgSFMEEB = (TH2D*)(ftrgSF->Get("trgSFMEEB")); assert(trgSFMEEB); trgSFMEEB->SetDirectory(0);
  TH2D *trgSFMEBE = (TH2D*)(ftrgSF->Get("trgSFMEBE")); assert(trgSFMEBE); trgSFMEBE->SetDirectory(0);
  TH2D *trgSFMEEE = (TH2D*)(ftrgSF->Get("trgSFMEEE")); assert(trgSFMEEE); trgSFMEEE->SetDirectory(0);
  TH2D *trgSFEMBB = (TH2D*)(ftrgSF->Get("trgSFEMBB")); assert(trgSFEMBB); trgSFEMBB->SetDirectory(0);
  TH2D *trgSFEMEB = (TH2D*)(ftrgSF->Get("trgSFEMEB")); assert(trgSFEMEB); trgSFEMEB->SetDirectory(0);
  TH2D *trgSFEMBE = (TH2D*)(ftrgSF->Get("trgSFEMBE")); assert(trgSFEMBE); trgSFEMBE->SetDirectory(0);
  TH2D *trgSFEMEE = (TH2D*)(ftrgSF->Get("trgSFEMEE")); assert(trgSFEMEE); trgSFEMEE->SetDirectory(0);
  delete ftrgSF;

  TFile *fSingleTrgSF = TFile::Open(Form("MitAnalysisRunII/data/90x/histoDY0TriggerSFStudy_%d.root",year));
  TH2D *histoMuTrgEffSF = (TH2D*)(fSingleTrgSF->Get("histoTrgEffStudy_1_0")); assert(histoMuTrgEffSF); histoMuTrgEffSF->SetDirectory(0);
  TH2D *histoElTrgEffSF = (TH2D*)(fSingleTrgSF->Get("histoTrgEffStudy_3_0")); assert(histoElTrgEffSF); histoElTrgEffSF->SetDirectory(0);
  delete fSingleTrgSF;

  //TFile *fNPVFile = TFile::Open(Form("%s",npvPath.Data()));
  //TH1D *fhDNPV    = (TH1D*)(fNPVFile->Get("npvWeights"));   assert(fhDNPV);    fhDNPV	->SetDirectory(0);
  //delete fNPVFile;

  printf("running ZHG %d analysis\n",year);

  double normForABCD[4] = {0,0,0,0};

  const int nBinMVA = 15; Double_t xbins[nBinMVA+1] = {-50,   0,  75, 115, 150, 200, 400,
  							         475, 515, 550, 600, 800,
							        1200,
								1600,
								2000,
								2400};
  //const int nBinMVA1D = 7; Double_t xbins1D[nBinMVA1D+1] = {0,  50, 75, 100, 125, 150, 175, 200};
  const int nBinMVA1D = 5; Double_t xbins1D[nBinMVA1D+1] = {0, 75, 115, 150, 200, 350};

  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 56;
  TH1D* histo[allPlots][nPlotCategories];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    bool is1DMT = false;
    if     (thePlot >=   0 && thePlot <=  23) {is1DMT = true;}
    else if(thePlot >=  24 && thePlot <=  24) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 100;}
    else if(thePlot >=  25 && thePlot <=  25) {nBinPlot = 5;   xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >=  26 && thePlot <=  26) {nBinPlot = 160; xminPlot = 70.0; xmaxPlot = 230;}
    else if(thePlot >=  27 && thePlot <=  27) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 1;}
    else if(thePlot >=  28 && thePlot <=  28) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = TMath::Pi();}
    else if(thePlot >=  29 && thePlot <=  29) {nBinPlot = 4;   xminPlot = -0.5; xmaxPlot = 3.5;}
    else if(thePlot >=  30 && thePlot <=  30) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >=  31 && thePlot <=  31) {nBinPlot = 12;  xminPlot =  0.0; xmaxPlot = 3.0;}
    else if(thePlot >=  32 && thePlot <=  32) {nBinPlot = 4;   xminPlot = -0.5; xmaxPlot = 3.5;}
    else if(thePlot >=  33 && thePlot <=  33) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 400;}
    else if(thePlot >=  34 && thePlot <=  34) {nBinPlot = 30;  xminPlot = 70.0; xmaxPlot = 370;}
    else if(thePlot >=  35 && thePlot <=  35) {nBinPlot = 50;  xminPlot =  0.0; xmaxPlot = 2.5;}
    else if(thePlot >=  36 && thePlot <=  36) {nBinPlot = 2;   xminPlot = -0.5; xmaxPlot = 1.5;}
    else if(thePlot >=  37 && thePlot <=  39) {nBinPlot = 11;  xminPlot = -0.5; xmaxPlot =10.5;}
    else if(thePlot >=  40 && thePlot <=  40) {nBinPlot = 100; xminPlot = -5.0; xmaxPlot = 5.0;}
    else if(thePlot >=  41 && thePlot <=  41) {nBinPlot = 160; xminPlot = 70.0; xmaxPlot = 230;}
    else if(thePlot >=  42 && thePlot <=  43) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 1;}
    else if(thePlot >=  44 && thePlot <=  45) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = TMath::Pi();}
    else if(thePlot >=  46 && thePlot <=  46) {is1DMT = true;}
    else if(thePlot >=  47 && thePlot <=  47) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = TMath::Pi();}
    else if(thePlot >=  48 && thePlot <=  48) {nBinPlot = 12;  xminPlot =  0.0; xmaxPlot = 3.0;}
    else if(thePlot >=  49 && thePlot <=  49) {is1DMT = true;}
    else if(thePlot >=  50 && thePlot <=  50) {nBinPlot =  50; xminPlot = 25.0; xmaxPlot = 425.0;}
    else if(thePlot >=  51 && thePlot <=  51) {nBinPlot =  50; xminPlot = 20.0; xmaxPlot = 220.0;}
    else if(thePlot >=  52 && thePlot <=  54) {is1DMT = true;}
    if     (thePlot == allPlots-1) for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinMVA, xbins);
    else if(is1DMT == true)        for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinMVA1D, xbins1D);
    else                           for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = new TH1D(Form("histo_%d_%d",thePlot,i), Form("histo_%d_%d",thePlot,i), nBinPlot, xminPlot, xmaxPlot);
  }

  TH1D* histo_MVA = new TH1D("histo_MVA", "histo_MVA", nBinMVA, xbins); histo_MVA->Sumw2();

  TH1D *histo_Baseline[nPlotCategories];
  TH1D *histo_QCDScaleBounding[nPlotCategories][6];
  TH1D *histo_QCDScaleUp[nPlotCategories];
  TH1D *histo_QCDScaleDown[nPlotCategories];
  TH1D *histo_PDFBoundingUp[nPlotCategories];
  TH1D *histo_PDFBoundingDown[nPlotCategories];
  TH1D *histo_LepEffMBoundingUp[nPlotCategories];
  TH1D *histo_LepEffMBoundingDown[nPlotCategories];
  TH1D *histo_LepEffEBoundingUp[nPlotCategories];
  TH1D *histo_LepEffEBoundingDown[nPlotCategories];
  TH1D *histo_ScaleMBoundingUp[nPlotCategories];
  TH1D *histo_ScaleMBoundingDown[nPlotCategories];
  TH1D *histo_ScaleEBoundingUp[nPlotCategories];
  TH1D *histo_ScaleEBoundingDown[nPlotCategories];
  TH1D *histo_ScaleGBoundingUp[nPlotCategories];
  TH1D *histo_ScaleGBoundingDown[nPlotCategories];
  TH1D *histo_PUBoundingUp[nPlotCategories];
  TH1D *histo_PUBoundingDown[nPlotCategories];
  TH1D *histo_BTAGBBoundingUp[nYears][nPlotCategories];
  TH1D *histo_BTAGBBoundingDown[nYears][nPlotCategories];
  TH1D *histo_BTAGLBoundingUp[nYears][nPlotCategories];
  TH1D *histo_BTAGLBoundingDown[nYears][nPlotCategories];
  TH1D *histo_JESBoundingUp[nYears][nPlotCategories];
  TH1D *histo_JESBoundingDown[nYears][nPlotCategories];
  TH1D *histo_PreFireBoundingUp[nYears][nPlotCategories];
  TH1D *histo_PreFireBoundingDown[nYears][nPlotCategories];
  TH1D *histo_TriggerBoundingUp[nYears][nPlotCategories];
  TH1D *histo_TriggerBoundingDown[nYears][nPlotCategories];
  TH1D *histo_PhoEffBoundingUp[nPlotCategories];
  TH1D *histo_PhoEffBoundingDown[nPlotCategories];
  TH1D *histo_PhoFakeBoundingUp[nPlotCategories];
  TH1D *histo_PhoFakeBoundingDown[nPlotCategories];
  TH1D *histo_ElToPhRateBoundingUp[nPlotCategories];
  TH1D *histo_ElToPhRateBoundingDown[nPlotCategories];
  TH1D *histo_EWKCorrWZUp[nPlotCategories];
  TH1D *histo_EWKCorrWZDown[nPlotCategories];
  TH1D *histo_EWKqqZZCorrUp[nPlotCategories];
  TH1D *histo_EWKqqZZCorrDown[nPlotCategories];
  TH1D *histo_ggZZCorrUp[nPlotCategories];
  TH1D *histo_ggZZCorrDown[nPlotCategories];
  
  for(unsigned ic=kPlotData; ic!=nPlotCategories; ic++) {
    for(int i=0; i<6; i++)  histo_QCDScaleBounding[ic][i] = (TH1D*)histo_MVA->Clone(Form("histo_%s_%d_QCDScaleBounding",plotBaseNames[ic].Data(),i));
    histo_Baseline              [ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s"                    , plotBaseNames[ic].Data()));
    histo_QCDScaleUp            [ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_QCDScale_%s_ACCEPTUp"         , plotBaseNames[ic].Data(), plotBaseNames[ic].Data()));
    histo_QCDScaleDown          [ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_QCDScale_%s_ACCEPTDown"       , plotBaseNames[ic].Data(), plotBaseNames[ic].Data()));
    histo_PDFBoundingUp 	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_PDFUp"              , plotBaseNames[ic].Data()));
    histo_PDFBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_PDFDown"            , plotBaseNames[ic].Data()));
    histo_LepEffMBoundingUp	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_eff_mUp"        , plotBaseNames[ic].Data()));
    histo_LepEffMBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_eff_mDown"      , plotBaseNames[ic].Data()));
    histo_LepEffEBoundingUp	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_eff_eUp"        , plotBaseNames[ic].Data()));
    histo_LepEffEBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_eff_eDown"      , plotBaseNames[ic].Data()));
    histo_ScaleMBoundingUp	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_scale_mUp"      , plotBaseNames[ic].Data()));
    histo_ScaleMBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_scale_mDown"    , plotBaseNames[ic].Data()));
    histo_ScaleEBoundingUp	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_scale_eUp"      , plotBaseNames[ic].Data()));
    histo_ScaleEBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_scale_eDown"    , plotBaseNames[ic].Data()));
    histo_ScaleGBoundingUp	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_scale_pUp"      , plotBaseNames[ic].Data()));
    histo_ScaleGBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_scale_pDown"    , plotBaseNames[ic].Data()));
    histo_PUBoundingUp		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_puUp"           , plotBaseNames[ic].Data()));
    histo_PUBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_puDown"         , plotBaseNames[ic].Data()));
    for(int ny=0; ny<nYears; ny++){
    histo_BTAGBBoundingUp    [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_btagb_%dUp"     , plotBaseNames[ic].Data(),2016+ny));
    histo_BTAGBBoundingDown  [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_btagb_%dDown"   , plotBaseNames[ic].Data(),2016+ny));
    histo_BTAGLBoundingUp    [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_btagl_%dUp"     , plotBaseNames[ic].Data(),2016+ny));
    histo_BTAGLBoundingDown  [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_btagl_%dDown"   , plotBaseNames[ic].Data(),2016+ny));
    histo_JESBoundingUp      [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_jes_%dUp"	   , plotBaseNames[ic].Data(),2016+ny));
    histo_JESBoundingDown    [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_jes_%dDown"	   , plotBaseNames[ic].Data(),2016+ny));
    histo_PreFireBoundingUp  [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_prefire_%dUp"   , plotBaseNames[ic].Data(),2016+ny));
    histo_PreFireBoundingDown[ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_prefire_%dDown" , plotBaseNames[ic].Data(),2016+ny));
    histo_TriggerBoundingUp  [ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_trigger_%dUp"   , plotBaseNames[ic].Data(),2016+ny));
    histo_TriggerBoundingDown[ny][ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_trigger_%dDown" , plotBaseNames[ic].Data(),2016+ny));
    }
    histo_PhoEffBoundingUp	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_eff_photonUp"   , plotBaseNames[ic].Data()));
    histo_PhoEffBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_eff_photonDown" , plotBaseNames[ic].Data()));
    histo_PhoFakeBoundingUp	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fake_photonUp"  , plotBaseNames[ic].Data()));
    histo_PhoFakeBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fake_photonDown", plotBaseNames[ic].Data()));
    histo_ElToPhRateBoundingUp	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fake_elUp"      , plotBaseNames[ic].Data()));
    histo_ElToPhRateBoundingDown[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_fake_elDown"    , plotBaseNames[ic].Data()));
    histo_EWKCorrWZUp		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKWZCorrUp"        , plotBaseNames[ic].Data()));
    histo_EWKCorrWZDown 	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKWZCorrDown"      , plotBaseNames[ic].Data()));
    histo_EWKqqZZCorrUp 	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKqqZZCorrUp"      , plotBaseNames[ic].Data()));
    histo_EWKqqZZCorrDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKqqZZCorrDown"    , plotBaseNames[ic].Data()));
    histo_ggZZCorrUp		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_ggZZCorrUp"         , plotBaseNames[ic].Data()));
    histo_ggZZCorrDown		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_ggZZCorrDown"       , plotBaseNames[ic].Data()));
  }

  //*******************************************************
  // Chain Loop
  //*******************************************************
  for(UInt_t ifile=0; ifile<infileName_.size(); ifile++) {
    printf("sampleNames(%d): %s\n",ifile,infileName_[ifile].Data());
    TFile *the_input_file = TFile::Open(infileName_[ifile].Data());
    TTree *the_input_tree = (TTree*)the_input_file->FindObjectAny("events");

    double srYields[4]  = {0., 0., 0., 0.};
    double srYieldsE[4] = {0., 0., 0., 0.};
    pandaFlat thePandaFlat(the_input_tree);
    double theMCPrescale = 1.0; if(infileCat_[ifile] != kPlotData) theMCPrescale = mcPrescale;
    Long64_t nentries = thePandaFlat.fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = thePandaFlat.LoadTree(jentry);
      if (ientry < 0) break;
      nb = thePandaFlat.fChain->GetEntry(jentry);   nbytes += nb;
      if (jentry%1000000 == 0) printf("--- reading event %8lld (%8lld) of %8lld\n",jentry,ientry,nentries);
      if (infileCat_[ifile] != 0 && jentry%(int)theMCPrescale != 0) continue;

      bool passTrigger = (thePandaFlat.trigger & (1<<kEMuTrig)) != 0       || (thePandaFlat.trigger & (1<<kDoubleMuTrig)) != 0  ||
                         (thePandaFlat.trigger & (1<<kSingleMuTrig)) != 0  || (thePandaFlat.trigger & (1<<kDoubleEleTrig)) != 0 ||
                         (thePandaFlat.trigger & (1<<kSingleEleTrig)) != 0;
      if(isSingleLeptonAna == true) passTrigger = (thePandaFlat.trigger & (1<<kSingleMuTrig))  != 0 || 
                                                  (thePandaFlat.trigger & (1<<kSingleEleTrig)) != 0;
      if((isSingleLeptonAna == false && passTrigger == false) || 
         (isSingleLeptonAna == true  && passTrigger == false && infileCat_[ifile] == kPlotData)) continue;
      if(thePandaFlat.metFilter == 0) continue;

      // Remove bad quality 2017 events right away
      bool passJetEtaCut = true;
      if(year == 2017 && thePandaFlat.nJot >= 1){
        passJetEtaCut = TMath::Abs(thePandaFlat.jotEta[0]) < 2.5 || TMath::Abs(thePandaFlat.jotEta[0]) > 3.0;
      }
      if(passJetEtaCut == false) continue;

      if(thePandaFlat.nLooseLep < 2 || thePandaFlat.nLooseLep > 4) continue;

      vector<float>  looseLepPt,looseLepEta,looseLepPhi,looseLepSF,looseLepIso;
      vector<int> looseLepSelBit,looseLepPdgId,looseLepTripleCharge,looseLepMissingHits;
      int ptSelCuts[3] = {0,0,0};
      for(int i=0; i<thePandaFlat.nLooseMuon; i++){
        int nBinEtaCorr = histoEtaCorr->GetXaxis()->FindBin(TMath::Min((double)TMath::Abs(thePandaFlat.muonEta[i]),2.4999))-1;
        if(infileCat_[ifile]==kPlotData)
        looseLepPt.push_back(thePandaFlat.muonPt[i]);
        else
        looseLepPt.push_back(thePandaFlat.muonPt[i] * muScaleCorr[nBinEtaCorr]);
        looseLepEta.push_back(thePandaFlat.muonEta[i]);
        looseLepPhi.push_back(thePandaFlat.muonPhi[i]);
        looseLepSF.push_back(thePandaFlat.muonSfReco[i] * thePandaFlat.muonSfTight[i]);
        looseLepSelBit.push_back(thePandaFlat.muonSelBit[i]);
        looseLepPdgId.push_back(thePandaFlat.muonPdgId[i]);
        looseLepTripleCharge.push_back(1);
        looseLepMissingHits.push_back(0);
        looseLepIso.push_back(thePandaFlat.muonCombIso[i]);
	if(looseLepPt[looseLepPt.size()-1] > 25) ptSelCuts[0]++;
	if(looseLepPt[looseLepPt.size()-1] > 20) ptSelCuts[1]++;
	if(looseLepPt[looseLepPt.size()-1] > 10) ptSelCuts[2]++;
      }
      for(int i=0; i<thePandaFlat.nLooseElectron; i++){
        int nBinEtaCorr = histoEtaCorr->GetXaxis()->FindBin(TMath::Min((double)TMath::Abs(thePandaFlat.electronEta[i]),2.4999))-1;
        if(infileCat_[ifile]==kPlotData)
        looseLepPt.push_back(thePandaFlat.electronPt[i]);
        else
        looseLepPt.push_back(thePandaFlat.electronPt[i] * elScaleCorr[nBinEtaCorr]);
        looseLepEta.push_back(thePandaFlat.electronEta[i]);
        looseLepPhi.push_back(thePandaFlat.electronPhi[i]);
        looseLepSelBit.push_back(thePandaFlat.electronSelBit[i]);
        looseLepSF.push_back(thePandaFlat.electronSfReco[i] * thePandaFlat.electronSfMedium[i]);
        looseLepPdgId.push_back(thePandaFlat.electronPdgId[i]);
        looseLepTripleCharge.push_back(thePandaFlat.electronTripleCharge[i]);
        looseLepMissingHits.push_back(thePandaFlat.electronNMissingHits[i]);
        looseLepIso.push_back(thePandaFlat.electronCombIso[i]);
	if(looseLepPt[looseLepPt.size()-1] > 25) ptSelCuts[0]++;
	if(looseLepPt[looseLepPt.size()-1] > 20) ptSelCuts[1]++;
	if(looseLepPt[looseLepPt.size()-1] > 10) ptSelCuts[2]++;
      }

      if((int)looseLepPt.size() != thePandaFlat.nLooseLep) printf("IMPOSSIBLE\n");

      if(!(ptSelCuts[0] >= 1 && ptSelCuts[1] >= 2 && ptSelCuts[2] >= thePandaFlat.nLooseLep)) continue;

      int theCategory = infileCat_[ifile];
      bool isNotMCFake = thePandaFlat.looseGenLep1PdgId != 0 && thePandaFlat.looseGenLep2PdgId != 0;
      if(thePandaFlat.nLooseLep >= 3) isNotMCFake = isNotMCFake && thePandaFlat.looseGenLep3PdgId != 0;
      if(thePandaFlat.nLooseLep >= 4) isNotMCFake = isNotMCFake && thePandaFlat.looseGenLep4PdgId != 0;
      if(theCategory != kPlotData && theCategory != kPlotVG && isNotMCFake == false && usePureMC == false) continue;

      vector<TLorentzVector> vLoose,vLooseMUp,vLooseMDown,vLooseEUp,vLooseEDown;
      vector<int> idLep;
      bool passLooseLepId = true;
      int qTot = 0;
      unsigned int countLeptonTight = 0;
      for(int i=0; i<thePandaFlat.nLooseLep; i++) {
        idLep.push_back(0);
        if     (abs(looseLepPdgId[i])==13 && (looseLepSelBit[i] & kTight)  == kTight  && (looseLepSelBit[i] & kDxyz)  == kDxyz) idLep[i] = 1;
        else if(abs(looseLepPdgId[i])==11 && (looseLepSelBit[i] & kMedium) == kMedium) idLep[i] = 1;
	countLeptonTight = countLeptonTight + (idLep[i] > 0);

        double thePDGMass = mass_mu;
        if(abs(looseLepPdgId[i])==11) thePDGMass = mass_el;
	TLorentzVector vLepTemp; vLepTemp.SetPtEtaPhiM(looseLepPt[i],looseLepEta[i],looseLepPhi[i],thePDGMass);
        vLoose.push_back(vLepTemp);

	if(abs(looseLepPdgId[i])==13) vLepTemp.SetPtEtaPhiM(vLoose[i].Pt()*muScale,vLoose[i].Eta(),looseLepPhi[i],thePDGMass);
        else                          vLepTemp.SetPtEtaPhiM(vLoose[i].Pt()*1.00000,vLoose[i].Eta(),looseLepPhi[i],thePDGMass);
        vLooseMUp.push_back(vLepTemp);

	if(abs(looseLepPdgId[i])==13) vLepTemp.SetPtEtaPhiM(vLoose[i].Pt()/muScale,vLoose[i].Eta(),looseLepPhi[i],thePDGMass);
        else                          vLepTemp.SetPtEtaPhiM(vLoose[i].Pt()/1.00000,vLoose[i].Eta(),looseLepPhi[i],thePDGMass);
        vLooseMDown.push_back(vLepTemp);

	if     (abs(looseLepPdgId[i])==13)  vLepTemp.SetPtEtaPhiM(vLoose[i].Pt()*1.000000,vLoose[i].Eta(),looseLepPhi[i],thePDGMass);
	else if(abs(vLoose[i].Eta()) < 1.5) vLepTemp.SetPtEtaPhiM(vLoose[i].Pt()*elScaleB,vLoose[i].Eta(),looseLepPhi[i],thePDGMass);
        else                                vLepTemp.SetPtEtaPhiM(vLoose[i].Pt()*elScaleE,vLoose[i].Eta(),looseLepPhi[i],thePDGMass);
        vLooseEUp.push_back(vLepTemp);

	if     (abs(looseLepPdgId[i])==13)  vLepTemp.SetPtEtaPhiM(vLoose[i].Pt()*1.000000,vLoose[i].Eta(),looseLepPhi[i],thePDGMass);
	else if(abs(vLoose[i].Eta()) < 1.5) vLepTemp.SetPtEtaPhiM(vLoose[i].Pt()/elScaleB,vLoose[i].Eta(),looseLepPhi[i],thePDGMass);
        else                                vLepTemp.SetPtEtaPhiM(vLoose[i].Pt()/elScaleE,vLoose[i].Eta(),looseLepPhi[i],thePDGMass);
        vLooseEDown.push_back(vLepTemp);

	qTot = qTot + abs(looseLepPdgId[i])/looseLepPdgId[i];

        passLooseLepId = passLooseLepId && ((looseLepSelBit[i] & kFake) == kFake);
      }
      if(passLooseLepId == false && usePureMC == false) continue;
      if(usePureMC == true && countLeptonTight != idLep.size()) continue;

      int lepType = -1; double muSFUnc = 1.0; double elSFUnc = 1.0;
      if     (thePandaFlat.nLooseLep == 2){
        if     (abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13) {lepType = 0; muSFUnc = 1.015*1.015;}
        else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11) {lepType = 1; elSFUnc = 1.015*1.015;}
        else  {lepType = 2; muSFUnc = 1.015; elSFUnc = 1.015;}
      }
      else if(thePandaFlat.nLooseLep == 3){
        if     (abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13 && abs(looseLepPdgId[2])==13) {lepType = 0; muSFUnc = 1.015*1.015*1.015;}
        else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11 && abs(looseLepPdgId[2])==11) {lepType = 3; elSFUnc = 1.015*1.015*1.015;}
        else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11) {lepType = 1; muSFUnc = 1.015; elSFUnc = 1.015*1.015;}
        else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[2])==11) {lepType = 1; muSFUnc = 1.015; elSFUnc = 1.015*1.015;}
        else if(abs(looseLepPdgId[1])==11 && abs(looseLepPdgId[2])==11) {lepType = 1; muSFUnc = 1.015; elSFUnc = 1.015*1.015;}
        else if(abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13) {lepType = 2; muSFUnc = 1.015*1.015; elSFUnc = 1.015;}
        else if(abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[2])==13) {lepType = 2; muSFUnc = 1.015*1.015; elSFUnc = 1.015;}
        else if(abs(looseLepPdgId[1])==13 && abs(looseLepPdgId[2])==13) {lepType = 2; muSFUnc = 1.015*1.015; elSFUnc = 1.015;}
        else {printf("Impossible dilepton combination: %d %d %d\n",looseLepPdgId[0],looseLepPdgId[1],looseLepPdgId[2]); continue;}
      }
      else if(thePandaFlat.nLooseLep == 4){
        int nmu = (abs(looseLepPdgId[0])==13) + (abs(looseLepPdgId[1])==13) + (abs(looseLepPdgId[2])==13) + (abs(looseLepPdgId[3])==13);
        int nel = (abs(looseLepPdgId[0])==11) + (abs(looseLepPdgId[1])==11) + (abs(looseLepPdgId[2])==11) + (abs(looseLepPdgId[3])==11);
        if     (nmu == 4 && nel == 0) {lepType = 0; muSFUnc = 1.015*1.015*1.015*1.015;}
        else if(nmu == 0 && nel == 4) {lepType = 1; elSFUnc = 1.015*1.015*1.015*1.015;}
        else if(nmu == 2 && nel == 2) {lepType = 2; muSFUnc = 1.015*1.015; elSFUnc = 1.015*1.015;}
        else if(nmu == 3 && nel == 1) {lepType = 3; muSFUnc = 1.015*1.015*1.015; elSFUnc = 1.015;}
        else if(nmu == 1 && nel == 3) {lepType = 3; muSFUnc = 1.015; elSFUnc = 1.015*1.015*1.015;}
        else {printf("Impossible dilepton combination: %d %d %d %d\n",looseLepPdgId[0],looseLepPdgId[1],looseLepPdgId[2],looseLepPdgId[3]); continue;}
      }

      TLorentzVector vMet,vTrkMet,vMetUp,vMetDown;
      vTrkMet.SetPtEtaPhiM(thePandaFlat.trkmet,0.0,thePandaFlat.trkmetphi,0.0);
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
      //vMet    .SetPx(vMet    .Px()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 0));
      //vMet    .SetPy(vMet    .Py()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 1));
      //vMetUp  .SetPx(vMetUp  .Px()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 0));
      //vMetUp  .SetPy(vMetUp  .Py()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 1));
      //vMetDown.SetPx(vMetDown.Px()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 0));
      //vMetDown.SetPy(vMetDown.Py()-metPhiCorr(year, thePandaFlat.npv, (infileCat_[ifile]==kPlotData), 1));

      double dPhiLepMETMin = 999; double dPhiLepTrackMETMin = 999;
      for(unsigned int i=0; i<vLoose.size(); i++){
        if(dPhiLepMETMin      > TMath::Abs(vLoose[i].DeltaPhi(vMet))   ) dPhiLepMETMin      = TMath::Abs(vLoose[i].DeltaPhi(vMet));
	if(dPhiLepTrackMETMin > TMath::Abs(vLoose[i].DeltaPhi(vTrkMet))) dPhiLepTrackMETMin = TMath::Abs(vLoose[i].DeltaPhi(vTrkMet));
      }

      double PMET[1] = {vMet.Pt()};
      double PTrackMET[1] = {vTrkMet.Pt()};
      if(dPhiLepMETMin < TMath::Pi()/2) {PMET[0] = PMET[0] * sin(dPhiLepMETMin);}
      if(dPhiLepTrackMETMin < TMath::Pi()/2) {PTrackMET[0] = PTrackMET[0] * sin(dPhiLepTrackMETMin);}
      double minPMET[1] = {TMath::Min(PMET[0],PTrackMET[0])};

      TLorentzVector vPhoton,vPhotonUp,vPhotonDown;
      bool passPhoSel = TMath::Abs(thePandaFlat.loosePho1Eta) < 2.5
             && (thePandaFlat.loosePho1SelBit & pMedium) == pMedium 
	     && (thePandaFlat.loosePho1SelBit & pCsafeVeto) == pCsafeVeto 
	     && (thePandaFlat.loosePho1SelBit & pPixelVeto) == pPixelVeto;
      if(passPhoSel == true) {
        vPhoton.SetPtEtaPhiM(thePandaFlat.loosePho1Pt, thePandaFlat.loosePho1Eta, thePandaFlat.loosePho1Phi, 0);
	if(vPhoton.Pt() <= 25) passPhoSel = false;
      }
      bool passPhoSelUp = TMath::Abs(thePandaFlat.loosePho1Eta) < 2.5
             && (thePandaFlat.loosePho1SelBit & pMedium) == pMedium 
	     && (thePandaFlat.loosePho1SelBit & pCsafeVeto) == pCsafeVeto 
	     && (thePandaFlat.loosePho1SelBit & pPixelVeto) == pPixelVeto;
      if(passPhoSelUp == true) {
        if(abs(thePandaFlat.loosePho1Eta) < 1.50) vPhotonUp.SetPtEtaPhiM(thePandaFlat.loosePho1Pt*phScaleB, thePandaFlat.loosePho1Eta, thePandaFlat.loosePho1Phi, 0);
        else                                      vPhotonUp.SetPtEtaPhiM(thePandaFlat.loosePho1Pt*phScaleE, thePandaFlat.loosePho1Eta, thePandaFlat.loosePho1Phi, 0);
	if(vPhotonUp.Pt() <= 25) passPhoSelUp = false;
      }
      bool passPhoSelDown = TMath::Abs(thePandaFlat.loosePho1Eta) < 2.5
             && (thePandaFlat.loosePho1SelBit & pMedium) == pMedium 
	     && (thePandaFlat.loosePho1SelBit & pCsafeVeto) == pCsafeVeto 
	     && (thePandaFlat.loosePho1SelBit & pPixelVeto) == pPixelVeto;
      if(passPhoSelDown == true) {
        if(abs(thePandaFlat.loosePho1Eta) < 1.50) vPhotonDown.SetPtEtaPhiM(thePandaFlat.loosePho1Pt/phScaleB, thePandaFlat.loosePho1Eta, thePandaFlat.loosePho1Phi, 0);
        else                                      vPhotonDown.SetPtEtaPhiM(thePandaFlat.loosePho1Pt/phScaleE, thePandaFlat.loosePho1Eta, thePandaFlat.loosePho1Phi, 0);
	if(vPhotonDown.Pt() <= 25) passPhoSelDown = false;
      }

      double mllZ = 10000; double mllmin = 10000;
      TLorentzVector vZ1l1,vZ1l2,vZ2l1,vZ2l2,vWln;
      bool tightWlnId = false; int whichWln = -1;
      if     (vLoose.size() == 2){
        vZ1l1  = vLoose[0];
        vZ1l2  = vLoose[1];
	mllZ   = (vLoose[0]+vLoose[1]).M();
	mllmin = (vLoose[0]+vLoose[1]).M();
      }
      else if(vLoose.size() == 3){
	if(abs(looseLepPdgId[0]) == abs(looseLepPdgId[1]) && looseLepPdgId[0] != looseLepPdgId[1]) {
          if((vLoose[0]+vLoose[1]).M() < mllmin) mllmin = (vLoose[0]+vLoose[1]).M();
          if(fabs((vLoose[0]+vLoose[1]).M()-91.1876) < fabs(mllZ-91.1876)) {
	    mllZ  = (vLoose[0]+vLoose[1]).M();
	    vZ1l1 = vLoose[0];
	    vZ1l2 = vLoose[1];
	    vWln  = vLoose[2];
            if     (abs(looseLepPdgId[2])==13) tightWlnId = (looseLepSelBit[2] & kTight)  == kTight  && (looseLepSelBit[2] & kDxyz)  == kDxyz;
            else if(abs(looseLepPdgId[2])==11) tightWlnId = (looseLepSelBit[2] & kMedium) == kMedium;
	    whichWln = 2;
	  }
	}
	if(abs(looseLepPdgId[0]) == abs(looseLepPdgId[2]) && looseLepPdgId[0] != looseLepPdgId[2]) {
          if((vLoose[0]+vLoose[2]).M() < mllmin) mllmin = (vLoose[0]+vLoose[2]).M();
          if(fabs((vLoose[0]+vLoose[2]).M()-91.1876) < fabs(mllZ-91.1876)) {
            mllZ  = (vLoose[0]+vLoose[2]).M();
	    vZ1l1 = vLoose[0];
	    vZ1l2 = vLoose[2];
	    vWln  = vLoose[1];
            if     (abs(looseLepPdgId[1])==13) tightWlnId = (looseLepSelBit[1] & kTight)  == kTight  && (looseLepSelBit[1] & kDxyz)  == kDxyz;
            else if(abs(looseLepPdgId[1])==11) tightWlnId = (looseLepSelBit[1] & kMedium) == kMedium;
	    whichWln = 1;
	  }
	}
	if(abs(looseLepPdgId[1]) == abs(looseLepPdgId[2]) && looseLepPdgId[1] != looseLepPdgId[2]) {
          if((vLoose[1]+vLoose[2]).M() < mllmin) mllmin = (vLoose[1]+vLoose[2]).M();
          if(fabs((vLoose[1]+vLoose[2]).M()-91.1876) < fabs(mllZ-91.1876)) {
            mllZ  = (vLoose[1]+vLoose[2]).M();
	    vZ1l1 = vLoose[1];
	    vZ1l2 = vLoose[2];
	    vWln  = vLoose[0];
            if     (abs(looseLepPdgId[0])==13) tightWlnId = (looseLepSelBit[0] & kTight)  == kTight  && (looseLepSelBit[0] & kDxyz)  == kDxyz;
            else if(abs(looseLepPdgId[0])==11) tightWlnId = (looseLepSelBit[0] & kMedium) == kMedium;
	    whichWln = 0;
	  }
	}
        if(whichWln >= 0 && tightWlnId == false && idLep[whichWln] == 1) {countLeptonTight = countLeptonTight - 1; idLep[whichWln] = 0;};
      }
      else if(vLoose.size() == 4){
	if(abs(looseLepPdgId[0]) == abs(looseLepPdgId[1]) && looseLepPdgId[0] != looseLepPdgId[1]) {
          if((vLoose[0]+vLoose[1]).M() < mllmin) mllmin = (vLoose[0]+vLoose[1]).M();
          if(fabs((vLoose[0]+vLoose[1]).M()-91.1876) < fabs(mllZ-91.1876)) {
	    mllZ = (vLoose[0]+vLoose[1]).M();
	    vZ1l1 = vLoose[0];
	    vZ1l2 = vLoose[1];
	    vZ2l1 = vLoose[2];
	    vZ2l2 = vLoose[3];
	  }
	}
	if(abs(looseLepPdgId[0]) == abs(looseLepPdgId[2]) && looseLepPdgId[0] != looseLepPdgId[2]) {
          if((vLoose[0]+vLoose[2]).M() < mllmin) mllmin = (vLoose[0]+vLoose[2]).M();
          if(fabs((vLoose[0]+vLoose[2]).M()-91.1876) < fabs(mllZ-91.1876)) {
            mllZ = (vLoose[0]+vLoose[2]).M();
	    vZ1l1 = vLoose[0];
	    vZ1l2 = vLoose[2];
	    vZ2l1 = vLoose[1];
	    vZ2l2 = vLoose[3];
	  }
	}
	if(abs(looseLepPdgId[0]) == abs(looseLepPdgId[3]) && looseLepPdgId[0] != looseLepPdgId[3]) {
          if((vLoose[0]+vLoose[3]).M() < mllmin) mllmin = (vLoose[0]+vLoose[3]).M();
          if(fabs((vLoose[0]+vLoose[3]).M()-91.1876) < fabs(mllZ-91.1876)) {
            mllZ = (vLoose[0]+vLoose[3]).M();
	    vZ1l1 = vLoose[0];
	    vZ1l2 = vLoose[3];
	    vZ2l1 = vLoose[1];
	    vZ2l2 = vLoose[2];
	  }
	}
	if(abs(looseLepPdgId[1]) == abs(looseLepPdgId[2]) && looseLepPdgId[1] != looseLepPdgId[2]) {
          if((vLoose[1]+vLoose[2]).M() < mllmin) mllmin = (vLoose[1]+vLoose[2]).M();
          if(fabs((vLoose[1]+vLoose[2]).M()-91.1876) < fabs(mllZ-91.1876)) {
            mllZ = (vLoose[1]+vLoose[2]).M();
	    vZ1l1 = vLoose[1];
	    vZ1l2 = vLoose[2];
	    vZ2l1 = vLoose[0];
	    vZ2l2 = vLoose[3];
	  }
	}
	if(abs(looseLepPdgId[1]) == abs(looseLepPdgId[3]) && looseLepPdgId[1] != looseLepPdgId[3]) {
          if((vLoose[1]+vLoose[3]).M() < mllmin) mllmin = (vLoose[1]+vLoose[3]).M();
          if(fabs((vLoose[1]+vLoose[3]).M()-91.1876) < fabs(mllZ-91.1876)) {
            mllZ = (vLoose[1]+vLoose[3]).M();
	    vZ1l1 = vLoose[1];
	    vZ1l2 = vLoose[3];
	    vZ2l1 = vLoose[0];
	    vZ2l2 = vLoose[2];
	  }
	}
	if(abs(looseLepPdgId[2]) == abs(looseLepPdgId[3]) && looseLepPdgId[2] != looseLepPdgId[3]) {
          if((vLoose[2]+vLoose[3]).M() < mllmin) mllmin = (vLoose[2]+vLoose[3]).M();
          if(fabs((vLoose[2]+vLoose[3]).M()-91.1876) < fabs(mllZ-91.1876)) {
            mllZ = (vLoose[2]+vLoose[3]).M();
	    vZ1l1 = vLoose[2];
	    vZ1l2 = vLoose[3];
	    vZ2l1 = vLoose[0];
	    vZ2l2 = vLoose[1];
	  }
	}
      }

      if(usePureMC == true && countLeptonTight != idLep.size()) continue; // It needs to be applied again

      int theMinSelType = -1;
      TLorentzVector theG;
      if     (passPhoSel == true  && vLoose.size() == 2 && TMath::Abs(qTot) == 0){
        theMinSelType = 0;
        theG = vPhoton;
      }
      else if(passPhoSel == false && vLoose.size() == 3 && whichWln >= 0 && tightWlnId == true && TMath::Abs(qTot) == 1){
        theMinSelType = 1;
        theG = vLoose[whichWln]; 
	if(vWln.Pt() != vLoose[whichWln].Pt()) printf("PROBLEM WZ %f %f\n",vWln.Pt(),vLoose[whichWln].Pt());
      }
      else if(passPhoSel == true  && vLoose.size() == 3 && whichWln >= 0 && tightWlnId == true && TMath::Abs(qTot) == 1){       
        theMinSelType = 2;
        vMet.SetPx(vMet.Px()+vLoose[whichWln].Px());
        vMet.SetPy(vMet.Py()+vLoose[whichWln].Px());
        theG = vPhoton;
      }
      else if(passPhoSel == false && vLoose.size() == 4 && vZ2l1.Pt() > 0 && vZ2l2.Pt() > 0 && TMath::Abs((vZ2l1 + vZ2l2).M()-91.1876) < 15.0 && TMath::Abs(qTot) == 0){     
        theMinSelType = 3;
        theG = vZ2l1 + vZ2l2;
      }

      TLorentzVector dilepG = vZ1l1+vZ1l2+theG;
      TLorentzVector dilepGMUp,dilepGMDown,dilepGEUp,dilepGEDown,dilepGGUp,dilepGGDown;

      int theMinSelTypeMUp = -1;TLorentzVector theGMUp;
      if(passPhoSel == true  && vLooseMUp.size() == 2 && TMath::Abs(qTot) == 0 &&
        ((vLooseMUp[0].Pt() > 25 && vLooseMUp[1].Pt() > 20) || (vLooseMUp[1].Pt() > 25 && vLooseMUp[0].Pt() > 20))){
        theMinSelTypeMUp = 0;
        theGMUp = vPhoton;
	dilepGMUp = vLooseMUp[0] + vLooseMUp[1] + theGMUp;
      }
      int theMinSelTypeMDown = -1;TLorentzVector theGMDown;
      if(passPhoSel == true  && vLooseMDown.size() == 2 && TMath::Abs(qTot) == 0 &&
        ((vLooseMDown[0].Pt() > 25 && vLooseMDown[1].Pt() > 20) || (vLooseMDown[1].Pt() > 25 && vLooseMDown[0].Pt() > 20))){
        theMinSelTypeMDown = 0;
        theGMDown = vPhoton;
	dilepGMDown = vLooseMDown[0] + vLooseMDown[1] + theGMDown;
      }
      int theMinSelTypeEUp = -1;TLorentzVector theGEUp;
      if(passPhoSel == true  && vLooseEUp.size() == 2 && TMath::Abs(qTot) == 0 &&
        ((vLooseEUp[0].Pt() > 25 && vLooseEUp[1].Pt() > 20) || (vLooseEUp[1].Pt() > 25 && vLooseEUp[0].Pt() > 20))){
        theMinSelTypeEUp = 0;
        theGEUp = vPhoton;
	dilepGEUp = vLooseEUp[0] + vLooseEUp[1] + theGEUp;
      }
      int theMinSelTypeEDown = -1;TLorentzVector theGEDown;
      if(passPhoSel == true  && vLooseEDown.size() == 2 && TMath::Abs(qTot) == 0 &&
        ((vLooseEDown[0].Pt() > 25 && vLooseEDown[1].Pt() > 20) || (vLooseEDown[1].Pt() > 25 && vLooseEDown[0].Pt() > 20))){
        theMinSelTypeEDown = 0;
        theGEDown = vPhoton;
	dilepGEDown = vLooseEDown[0] + vLooseEDown[1] + theGEDown;
      }
      int theMinSelTypeGUp = -1;TLorentzVector theGGUp;
      if(passPhoSelUp == true  && vLoose.size() == 2 && TMath::Abs(qTot) == 0){
        theMinSelTypeGUp = 0;
        theGGUp = vPhotonUp;
	dilepGGUp = vLoose[0] + vLoose[1] + theGGUp;
      }
      int theMinSelTypeGDown = -1;TLorentzVector theGGDown;
      if(passPhoSelDown == true  && vLooseEDown.size() == 2 && TMath::Abs(qTot) == 0){
        theMinSelTypeGDown = 0;
        theGGDown = vPhotonDown;
	dilepGGDown = vLoose[0] + vLoose[1] + theGGDown;
      }
      //if(theMinSelType == -1) continue;

      double dPhiJetMET = -1.0; double dPhiJetMETUp = -1.0; double dPhiJetMETDown = -1.0;
      if(thePandaFlat.nJot > 0 && thePandaFlat.jotPt[0] > 30) {
        TLorentzVector vJetTemp;
        vJetTemp.SetPtEtaPhiM(thePandaFlat.jotPt[0],thePandaFlat.jotEta[0],thePandaFlat.jotPhi[0],0.0);
        dPhiJetMET = TMath::Abs(vJetTemp.DeltaPhi(vMet));
      }
      if(thePandaFlat.nJot_JESTotalUp > 0 && thePandaFlat.jotPt_JESTotalUp[0] > 30) {
        TLorentzVector vJetTemp;
        vJetTemp.SetPtEtaPhiM(thePandaFlat.jotPt_JESTotalUp[0],thePandaFlat.jotEta[0],thePandaFlat.jotPhi[0],0.0);
        dPhiJetMETUp = TMath::Abs(vJetTemp.DeltaPhi(vMetUp));
      }
      if(thePandaFlat.nJot_JESTotalDown > 0 && thePandaFlat.jotPt_JESTotalDown[0] > 30) {
        TLorentzVector vJetTemp;
        vJetTemp.SetPtEtaPhiM(thePandaFlat.jotPt_JESTotalDown[0],thePandaFlat.jotEta[0],thePandaFlat.jotPhi[0],0.0);
        dPhiJetMETDown = TMath::Abs(vJetTemp.DeltaPhi(vMetDown));
      }

      double massEGZDiff = 100;
      if(passPhoSel == true){
        for(unsigned int i=0; i<vLoose.size(); i++){
	  if(TMath::Abs(looseLepPdgId[i]) == 11 &&
	     TMath::Abs((vLoose[i]+theG).M()-91.1876) < massEGZDiff) massEGZDiff = TMath::Abs((vLoose[i]+theG).M()-91.1876);
        }
      }
      bool passMassEGZDiff = massEGZDiff > 15;

      double dPhiGMET = 0; double dPhiGMETUp = 0;double dPhiGMETDown = 0;
      double mTGMET = 0;   double mTGMETUp = 0;  double mTGMETDown = 0;
      TLorentzVector dilep = vZ1l1+vZ1l2;
      TLorentzVector dilepMUp   = vLooseMUp  [0] +  vLooseMUp  [1];
      TLorentzVector dilepMDown = vLooseMDown[0] +  vLooseMDown[1];
      TLorentzVector dilepEUp   = vLooseEUp  [0] +  vLooseEUp  [1];
      TLorentzVector dilepEDown = vLooseEDown[0] +  vLooseEDown[1];
      if(theMinSelType >= 0){
	dPhiGMET = TMath::Abs(theG.DeltaPhi(vMet));
	dPhiGMETUp = TMath::Abs(theG.DeltaPhi(vMetUp));
	dPhiGMETDown = TMath::Abs(theG.DeltaPhi(vMetDown));
        mTGMET = TMath::Sqrt(2.0*theG.Pt()*vMet.Pt()*(1.0 - cos(dPhiGMET)));
	dPhiGMETUp = TMath::Abs(theG.DeltaPhi(vMetUp));
        mTGMETUp = TMath::Sqrt(2.0*theG.Pt()*vMetUp.Pt()*(1.0 - cos(dPhiGMETUp)));
	dPhiGMETDown = TMath::Abs(theG.DeltaPhi(vMetDown));
        mTGMETDown = TMath::Sqrt(2.0*theG.Pt()*vMetDown.Pt()*(1.0 - cos(dPhiGMETDown)));
      }
      double mTGMETMUp   = mTGMET;
      double mTGMETMDown = mTGMET;
      double mTGMETEUp   = mTGMET;
      double mTGMETEDown = mTGMET;
      double mTGMETGUp   = 0; if(theMinSelTypeGUp   == 0){mTGMETGUp   = TMath::Sqrt(2.0*theGGUp  .Pt()*vMet.Pt()*(1.0 - cos(TMath::Abs(theGGUp  .DeltaPhi(vMet)))));}
      double mTGMETGDown = 0; if(theMinSelTypeGDown == 0){mTGMETGDown = TMath::Sqrt(2.0*theGGDown.Pt()*vMet.Pt()*(1.0 - cos(TMath::Abs(theGGDown.DeltaPhi(vMet)))));}

      double dPhiTriLepMET = TMath::Abs(dilepG.DeltaPhi(vMet));
      double dPhiDiLepGMET     = TMath::Abs(dilep.DeltaPhi(vMet    +theG));
      double dPhiDiLepGMETUp   = TMath::Abs(dilep.DeltaPhi(vMetUp  +theG));
      double dPhiDiLepGMETDown = TMath::Abs(dilep.DeltaPhi(vMetDown+theG));
      bool passZMass = mllmin > 4.0 && TMath::Abs(mllZ-91.1876) < 15.0;
      bool passZMassSB = mllZ > 110 && mllZ < 200;
      bool passMET    = vMet.Pt() > 110; bool passMETUp    = vMetUp.Pt() > 110; bool passMETDown    = vMetDown.Pt() > 110;
      bool passMETMin = vMet.Pt() > 70;  bool passMETMinUp = vMetUp.Pt() > 70;  bool passMETMinDown = vMetDown.Pt() > 70;
      bool passPTLL   = dilep.Pt() > 60;

      bool passZMassMUp   = theMinSelTypeMUp   == 0 && TMath::Abs(dilepMUp  .M()-91.1876) < 15.0;
      bool passZMassMDown = theMinSelTypeMDown == 0 && TMath::Abs(dilepMDown.M()-91.1876) < 15.0;
      bool passZMassEUp   = theMinSelTypeEUp   == 0 && TMath::Abs(dilepEUp  .M()-91.1876) < 15.0;
      bool passZMassEDown = theMinSelTypeEDown == 0 && TMath::Abs(dilepEDown.M()-91.1876) < 15.0;
      bool passZMassGUp   = passZMass;
      bool passZMassGDown = passZMass;

      bool pass3lMass      = dilepG.M() > 100;
      bool pass3lMassMUp   = theMinSelTypeMUp   == 0 && dilepGMUp.M()   > 100;
      bool pass3lMassMDown = theMinSelTypeMDown == 0 && dilepGMDown.M() > 100;
      bool pass3lMassEUp   = theMinSelTypeEUp   == 0 && dilepGEUp.M()   > 100;
      bool pass3lMassEDown = theMinSelTypeEDown == 0 && dilepGEDown.M() > 100;
      bool pass3lMassGUp   = theMinSelTypeGUp   == 0 && dilepGGUp.M()   > 100;
      bool pass3lMassGDown = theMinSelTypeGDown == 0 && dilepGGDown.M() > 100;

      bool passPTLLMUp   = theMinSelTypeMUp   == 0 && dilepMUp  .Pt() > 60;
      bool passPTLLMDown = theMinSelTypeMDown == 0 && dilepMDown.Pt() > 60;
      bool passPTLLEUp   = theMinSelTypeEUp   == 0 && dilepEUp  .Pt() > 60;
      bool passPTLLEDown = theMinSelTypeEDown == 0 && dilepEDown.Pt() > 60;
      bool passPTLLGUp   = passPTLL;
      bool passPTLLGDown = passPTLL;

      if(!(dilep.Pt() > 60 && (vMet.Pt() > 70 || vMetUp.Pt() > 70 ||vMetDown.Pt() > 70) && (thePandaFlat.nLooseLep != 2 || TMath::Abs(dilep.M()-125) < 75))) continue;

      double ptFrac = TMath::Abs(dilepG.Pt()-(vMet).Pt())/dilepG.Pt();
      double ptFracG     = TMath::Abs(dilep.Pt()-(vMet    +theG).Pt())/dilep.Pt();
      double ptFracGUp   = TMath::Abs(dilep.Pt()-(vMetUp  +theG).Pt())/dilep.Pt();
      double ptFracGDown = TMath::Abs(dilep.Pt()-(vMetDown+theG).Pt())/dilep.Pt();
      bool passPTFracG = ptFracG < 0.4; bool passPTFracGUp = ptFracGUp < 0.4; bool passPTFracGDown = ptFracGDown < 0.4;

      bool passPTFracGMUp   = theMinSelTypeMUp   == 0 &&  TMath::Abs(dilepMUp  .Pt()-(vMet+theGMUp  ).Pt())/dilepMUp  .Pt() < 0.4;
      bool passPTFracGMDown = theMinSelTypeMDown == 0 &&  TMath::Abs(dilepMDown.Pt()-(vMet+theGMDown).Pt())/dilepMDown.Pt() < 0.4;
      bool passPTFracGEUp   = theMinSelTypeEUp   == 0 &&  TMath::Abs(dilepEUp  .Pt()-(vMet+theGEUp  ).Pt())/dilepEUp  .Pt() < 0.4;
      bool passPTFracGEDown = theMinSelTypeEDown == 0 &&  TMath::Abs(dilepEDown.Pt()-(vMet+theGEDown).Pt())/dilepEDown.Pt() < 0.4;
      bool passPTFracGGUp   = theMinSelTypeGUp   == 0 &&  TMath::Abs(dilep     .Pt()-(vMet+theGGUp  ).Pt())/dilep     .Pt() < 0.4;
      bool passPTFracGGDown = theMinSelTypeGDown == 0 &&  TMath::Abs(dilep     .Pt()-(vMet+theGGDown).Pt())/dilep     .Pt() < 0.4;

      bool passDPhiZGMET = dPhiDiLepGMET > 2.5; bool passDPhiZGMETUp = dPhiDiLepGMETUp > 2.5; bool passDPhiZGMETDown = dPhiDiLepGMETDown > 2.5;
      bool passNjets     = thePandaFlat.nJot              <= 2;
      bool passNjetsUp   = thePandaFlat.nJot_JESTotalUp   <= 2;
      bool passNjetsDown = thePandaFlat.nJot_JESTotalDown <= 2;

      bool passBtagVeto = thePandaFlat.jetNMBtags == 0; bool passBtagVetoUp = thePandaFlat.jetNMBtags_JESTotalUp == 0; bool passBtagVetoDown = thePandaFlat.jetNMBtags_JESTotalDown == 0;
      double dphill = TMath::Abs(vZ1l1.DeltaPhi(vZ1l2));
      double detall = TMath::Abs(vZ1l1.Eta()-vZ1l2.Eta());
      double drll = sqrt(dphill*dphill+detall*detall);

      bool passDPhiJetMET     = dPhiJetMET     == -1 || dPhiJetMET     >= 0.5;
      bool passDPhiJetMETUp   = dPhiJetMETUp   == -1 || dPhiJetMETUp   >= 0.5;
      bool passDPhiJetMETDown = dPhiJetMETDown == -1 || dPhiJetMETDown >= 0.5;
      bool passTauVeto      = thePandaFlat.nTau == 0;
      const int mtMax = 340;
      bool passMT = mTGMET < mtMax; bool passMTUp = mTGMETUp < mtMax; bool passMTDown = mTGMETDown < mtMax;
      bool passMTMUp   = mTGMETMUp   < mtMax; 
      bool passMTMDown = mTGMETMDown < mtMax; 
      bool passMTEUp   = mTGMETEUp   < mtMax; 
      bool passMTEDown = mTGMETEDown < mtMax; 
      bool passMTGUp   = mTGMETGUp   < mtMax; 
      bool passMTGDown = mTGMETGDown < mtMax; 

      //                                                   0       1         2            3           4      5          6           7             8         9             10
      bool passCutEvol[11] = {theMinSelType == 0 && passPTLL,passMET,passZMass,passBtagVeto,passTauVeto,passMT,pass3lMass,passPTFracG,passDPhiZGMET,passNjets,passDPhiJetMET};
      bool passCutEvolAll = true;

      if(isDEBUG && vLoose.size() == 4) printf("DEBUG %d %d %d %d %d %d %d %d %d %d %d | %f %f\n",theMinSelType,passZMass,passNjets,passMET,passPTFracG,passDPhiZGMET,passBtagVeto,passPTLL,passDPhiJetMET,passTauVeto,passMT,mllmin,TMath::Abs(mllZ-91.1876));

      bool passAllCuts[nSelTypes] = {                   
     theMinSelType == 0 && pass3lMass && passZMass   && passNjets && passMET	&& passPTFracG && passDPhiZGMET &&  passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT,   // ZHGSEL
     theMinSelType == 0 && pass3lMass && passZMass   && passNjets && passMET	&& passPTFracG && passDPhiZGMET && !passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT,   // BTAGSEL
     theMinSelType == 0 && pass3lMass && passZMass   && passNjets &&!passMET	&& passPTFracG && passDPhiZGMET &&  passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT,   // ZLGSEL
     theMinSelType == 1 && pass3lMass && passZMass   && passNjets && passMET	&& passPTFracG && passDPhiZGMET &&  passBtagVeto && passPTLL && passDPhiJetMET &&		 passMT,   // WZSEL
     theMinSelType == 2 && pass3lMass && passZMass   && passNjets && passMET	&& passPTFracG && passDPhiZGMET &&  passBtagVeto && passPTLL && passDPhiJetMET &&		 passMT,   // WZGSEL
     theMinSelType == 3 && pass3lMass && passZMass   && passNjets && passMETMin && passPTFracG && passDPhiZGMET &&  passBtagVeto && passPTLL && passDPhiJetMET &&		 passMT,   // ZZSEL
     theMinSelType == 0 && pass3lMass && passZMassSB && passNjets && passMET	&& passPTFracG && passDPhiZGMET &&  passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT && passMassEGZDiff // WWSEL
                                    };

      bool passNMinusOne[11] = {
     theMinSelType >= 0 && 		passNjets && passMET && passPTFracG && passDPhiZGMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT && pass3lMass,
     theMinSelType >= 0 && passZMass &&	             passMET && passPTFracG && passDPhiZGMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT && pass3lMass,
     theMinSelType >= 0 && passZMass && passNjets &&  	        passPTFracG && passDPhiZGMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT && pass3lMass,
     theMinSelType >= 0 && passZMass && passNjets && passMET &&		       passDPhiZGMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT && pass3lMass,
     theMinSelType >= 0 && passZMass && passNjets && passMET && passPTFracG &&		        passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT && pass3lMass,
     theMinSelType >= 0 && passZMass && passNjets && passMET && passPTFracG && passDPhiZGMET &&		        passPTLL && passDPhiJetMET && passTauVeto && passMT && pass3lMass,
     theMinSelType >= 0 && passZMass && passNjets && passMET && passPTFracG && passDPhiZGMET && passBtagVeto &&	            passDPhiJetMET && passTauVeto && passMT && pass3lMass,
     theMinSelType >= 0 && passZMass && passNjets && passMET && passPTFracG && passDPhiZGMET && passBtagVeto && passPTLL &&	              passTauVeto && passMT && pass3lMass,
     theMinSelType >= 0 && passZMass && passNjets && passMET && passPTFracG && passDPhiZGMET && passBtagVeto && passPTLL && passDPhiJetMET && 	             passMT && pass3lMass,
     theMinSelType >= 0 && passZMass && passNjets && passMET && passPTFracG && passDPhiZGMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto           && pass3lMass,
     theMinSelType >= 0 && passZMass && passNjets && passMET && passPTFracG && passDPhiZGMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT
                                    };

      for(int i=0; i<11; i++) passNMinusOne[i] = mllmin > 4.0 && theMinSelType == 0 && passNMinusOne[i];

      bool passNMinusFour  = theMinSelType == 0 && pass3lMass && passZMass && passNjets && passBtagVeto && passPTLL && passTauVeto && passMT && ptFracG < 1.0;
      bool passNMinusThree = theMinSelType == 0 && pass3lMass && passZMass && passNjets && passBtagVeto && passPTLL && passTauVeto && passMT && passPTFracG && !passMET;

      bool passNMinusA = theMinSelType == 0 && pass3lMass && passZMass && passNjets && passMET &&  passPTFracG &&  passDPhiZGMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT;
      bool passNMinusB = theMinSelType == 0 && pass3lMass && passZMass && passNjets && passMET && !passPTFracG &&  passDPhiZGMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT;
      bool passNMinusC = theMinSelType == 0 && pass3lMass && passZMass && passNjets && passMET &&  passPTFracG && !passDPhiZGMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT;
      bool passNMinusD = theMinSelType == 0 && pass3lMass && passZMass && passNjets && passMET && !passPTFracG && !passDPhiZGMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT;

      passAllCuts[ZLGSEL] = passAllCuts[ZLGSEL] && passMETMin;
      passNMinusOne[2] = passNMinusOne[2] && passMETMin;
      passNMinusFour = passNMinusFour && passMETMin;
      passNMinusThree = passNMinusThree && passMETMin;

      bool passZHGSel     = theMinSelType == 0 && pass3lMass && passZMass && passNjets     && passMET	     && passPTFracG	&& passDPhiZGMET     && passBtagVeto	 && passPTLL && passDPhiJetMET     && passTauVeto && passMT;
      bool passZHGSelUp   = theMinSelType == 0 && pass3lMass && passZMass && passNjetsUp   && passMETUp      && passPTFracGUp	&& passDPhiZGMETUp   && passBtagVetoUp   && passPTLL && passDPhiJetMETUp   && passTauVeto && passMTUp;
      bool passZHGSelDown = theMinSelType == 0 && pass3lMass && passZMass && passNjetsDown && passMETDown    && passPTFracGDown && passDPhiZGMETDown && passBtagVetoDown && passPTLL && passDPhiJetMETDown && passTauVeto && passMTDown;
      bool passWZSel      = theMinSelType == 1 && pass3lMass && passZMass && passNjets     && passMET	     && passPTFracG	&& passDPhiZGMET     && passBtagVeto	 && passPTLL && passDPhiJetMET     &&		     passMT;
      bool passWZSelUp    = theMinSelType == 1 && pass3lMass && passZMass && passNjetsUp   && passMETUp      && passPTFracGUp	&& passDPhiZGMETUp   && passBtagVetoUp   && passPTLL && passDPhiJetMETUp   &&	  	     passMTUp;
      bool passWZSelDown  = theMinSelType == 1 && pass3lMass && passZMass && passNjetsDown && passMETDown    && passPTFracGDown && passDPhiZGMETDown && passBtagVetoDown && passPTLL && passDPhiJetMETDown &&	    	     passMTDown;
      bool passZZSel      = theMinSelType == 3 && pass3lMass && passZMass && passNjets     && passMETMin     && passPTFracG	&& passDPhiZGMET     && passBtagVeto	 && passPTLL && passDPhiJetMET     && lepType!=3  && passMT;
      bool passZZSelUp    = theMinSelType == 3 && pass3lMass && passZMass && passNjetsUp   && passMETMinUp   && passPTFracGUp	&& passDPhiZGMETUp   && passBtagVetoUp   && passPTLL && passDPhiJetMETUp   && lepType!=3  && passMTUp;
      bool passZZSelDown  = theMinSelType == 3 && pass3lMass && passZMass && passNjetsDown && passMETMinDown && passPTFracGDown && passDPhiZGMETDown && passBtagVetoDown && passPTLL && passDPhiJetMETDown && lepType!=3  && passMTDown; 

      bool passZHGSelMUp     = theMinSelTypeMUp   == 0 && pass3lMassMUp   && passZMassMUp   && passNjets && passMET && passPTFracGMUp	&& passDPhiZGMET && passBtagVeto  && passPTLLMUp   && passDPhiJetMET && passTauVeto && passMTMUp  ;
      bool passZHGSelMDown   = theMinSelTypeMDown == 0 && pass3lMassMDown && passZMassMDown && passNjets && passMET && passPTFracGMDown && passDPhiZGMET && passBtagVeto  && passPTLLMDown && passDPhiJetMET && passTauVeto && passMTMDown;
      bool passZHGSelEUp     = theMinSelTypeEUp   == 0 && pass3lMassEUp   && passZMassEUp   && passNjets && passMET && passPTFracGEUp	&& passDPhiZGMET && passBtagVeto  && passPTLLEUp   && passDPhiJetMET && passTauVeto && passMTEUp  ;
      bool passZHGSelEDown   = theMinSelTypeEDown == 0 && pass3lMassEDown && passZMassEDown && passNjets && passMET && passPTFracGEDown && passDPhiZGMET && passBtagVeto  && passPTLLEDown && passDPhiJetMET && passTauVeto && passMTEDown;
      bool passZHGSelGUp     = theMinSelTypeGUp   == 0 && pass3lMassGUp   && passZMassGUp   && passNjets && passMET && passPTFracGGUp	&& passDPhiZGMET && passBtagVeto  && passPTLLGUp   && passDPhiJetMET && passTauVeto && passMTGUp  ;
      bool passZHGSelGDown   = theMinSelTypeGDown == 0 && pass3lMassGDown && passZMassGDown && passNjets && passMET && passPTFracGGDown && passDPhiZGMET && passBtagVeto  && passPTLLGDown && passDPhiJetMET && passTauVeto && passMTGDown;

      if(!(passWZSel     &&
           (vZ1l1.Pt() > 25 || vZ1l2.Pt() > 25) && abs(looseLepPdgId[whichWln]) == 11 &&
	    vZ1l1.Pt() > 20 && vZ1l2.Pt() > 20  && vWln.Pt() > 25)) {passWZSel     = false; passAllCuts[WZSEL] = false;}

      if(!(passWZSelUp   &&
           (vZ1l1.Pt() > 25 || vZ1l2.Pt() > 25) && abs(looseLepPdgId[whichWln]) == 11 &&
	    vZ1l1.Pt() > 20 && vZ1l2.Pt() > 20  && vWln.Pt() > 25)) passWZSelUp   = false;

      if(!(passWZSelDown &&
           (vZ1l1.Pt() > 25 || vZ1l2.Pt() > 25) && abs(looseLepPdgId[whichWln]) == 11 &&
	    vZ1l1.Pt() > 20 && vZ1l2.Pt() > 20  && vWln.Pt() > 25)) passWZSelDown = false;

      int dataCardSel = -1; int dataCardSelUp = -1;int dataCardSelDown = -1;
      if     (passZHGSel)     dataCardSel     = 0;
      else if(passWZSel)      dataCardSel     = 1;
      else if(passZZSel)      dataCardSel     = 2;
      if     (passZHGSelUp)   dataCardSelUp   = 0;
      else if(passWZSelUp)    dataCardSelUp   = 1;
      else if(passZZSelUp)    dataCardSelUp   = 2;
      if     (passZHGSelDown) dataCardSelDown = 0;
      else if(passWZSelDown)  dataCardSelDown = 1;
      else if(passZZSelDown)  dataCardSelDown = 2;
      int dataCardSelMUp = -1;
      if     (passZHGSelMUp)  dataCardSelMUp  = 0;
      else if(passWZSel)      dataCardSelMUp  = 1;
      else if(passZZSel)      dataCardSelMUp  = 2;
      int dataCardSelMDown = -1;
      if     (passZHGSelMDown)dataCardSelMDown= 0;
      else if(passWZSel)      dataCardSelMDown= 1;
      else if(passZZSel)      dataCardSelMDown= 2;
      int dataCardSelEUp = -1;
      if     (passZHGSelEUp)  dataCardSelEUp  = 0;
      else if(passWZSel)      dataCardSelEUp  = 1;
      else if(passZZSel)      dataCardSelEUp  = 2;
      int dataCardSelEDown = -1;
      if     (passZHGSelEDown)dataCardSelEDown= 0;
      else if(passWZSel)      dataCardSelEDown= 1;
      else if(passZZSel)      dataCardSelEDown= 2;
      int dataCardSelGUp = -1;
      if     (passZHGSelGUp)  dataCardSelGUp  = 0;
      else if(passWZSel)      dataCardSelGUp  = 1;
      else if(passZZSel)      dataCardSelGUp  = 2;
      int dataCardSelGDown = -1;
      if     (passZHGSelGDown)dataCardSelGDown= 0;
      else if(passWZSel)      dataCardSelGDown= 1;
      else if(passZZSel)      dataCardSelGDown= 2;

      bool passSystCuts[nSystTypes] = {dataCardSelUp  >= 0, dataCardSelDown  >= 0, 
                                       dataCardSelMUp >= 0, dataCardSelMDown >= 0, 
                                       dataCardSelEUp >= 0, dataCardSelEDown >= 0, 
                                       dataCardSelGUp >= 0, dataCardSelGDown >= 0 
                                       };
 
      double photonSFUnc[3] = {1.0, 1.0, 1.0};
      double totalWeight = 1.0; double puWeight = 1.0; double puWeightUp = 1.0; double puWeightDown = 1.0; double sf_l1PrefireE = 1.0;
      double triggerWeights[2] = {1.0, 0.0};
      if(theCategory != kPlotData){
        if(isSingleLeptonAna == false){
	  trigger_sf(triggerWeights,thePandaFlat.nLooseLep,
	  trgSFMMBB,trgSFMMEB,trgSFMMBE,trgSFMMEE,trgSFEEBB,trgSFEEEB,trgSFEEBE,trgSFEEEE,
	  trgSFMEBB,trgSFMEEB,trgSFMEBE,trgSFMEEE,trgSFEMBB,trgSFEMEB,trgSFEMBE,trgSFEMEE,
	  vLoose[0].Pt(), TMath::Abs(vLoose[0].Eta()), abs(looseLepPdgId[0]),
	  vLoose[1].Pt(), TMath::Abs(vLoose[1].Eta()), abs(looseLepPdgId[1]));
        }
	else  {
	  double totalInEff = 1.0; double totalInEffE = 1.0;
	  for(unsigned int nl=0; nl<vLoose.size(); nl++) {
	    double eff,effE;
	    if(abs(looseLepPdgId[nl])==13){
              eff  = histoMuTrgEffSF->GetBinContent(
	             histoMuTrgEffSF->GetXaxis()->FindFixBin(vLoose[nl].Eta()),
	             histoMuTrgEffSF->GetYaxis()->FindFixBin(TMath::Min(vLoose[nl].Pt(),119.99)));
              effE = histoMuTrgEffSF->GetBinError(
	             histoMuTrgEffSF->GetXaxis()->FindFixBin(vLoose[nl].Eta()),
	             histoMuTrgEffSF->GetYaxis()->FindFixBin(TMath::Min(vLoose[nl].Pt(),119.99)));
            }
	    else {
              eff  = histoElTrgEffSF->GetBinContent(
	             histoElTrgEffSF->GetXaxis()->FindFixBin(vLoose[nl].Eta()),
	             histoElTrgEffSF->GetYaxis()->FindFixBin(TMath::Min(vLoose[nl].Pt(),119.99)));
              effE = histoElTrgEffSF->GetBinError(
	             histoElTrgEffSF->GetXaxis()->FindFixBin(vLoose[nl].Eta()),
	             histoElTrgEffSF->GetYaxis()->FindFixBin(TMath::Min(vLoose[nl].Pt(),119.99)));
	    }
	    totalInEff  = totalInEff  * (1.0 - TMath::Min(eff, 1.0));
	    totalInEffE = totalInEffE * (1.0 - TMath::Min(eff, 1.0) + effE);
          }
	  triggerWeights[0] = 1 - TMath::Max(totalInEff,0.0);
	  triggerWeights[1] = TMath::Abs(totalInEffE - totalInEff);
        }
	puWeight     = nPUScaleFactor(fhDPU,    thePandaFlat.pu);
        puWeightUp   = nPUScaleFactor(fhDPUUp,  thePandaFlat.pu);
        puWeightDown = nPUScaleFactor(fhDPUDown,thePandaFlat.pu);

        sf_l1PrefireE = 1.0 + TMath::Abs(1.0 - thePandaFlat.sf_l1Prefire) * 0.2;

	//double npvWeight = nPUScaleFactor(fhDNPV, thePandaFlat.npv);

        if(passBtagVeto) totalWeight = thePandaFlat.normalizedWeight * lumiV[whichYear] * puWeight * thePandaFlat.sf_l1Prefire * looseLepSF[0] * looseLepSF[1] * triggerWeights[0] * thePandaFlat.sf_btag0   * theMCPrescale;
        else             totalWeight = thePandaFlat.normalizedWeight * lumiV[whichYear] * puWeight * thePandaFlat.sf_l1Prefire * looseLepSF[0] * looseLepSF[1] * triggerWeights[0] * thePandaFlat.sf_btagGT0 * theMCPrescale;

        if     (infileCat_[ifile] == kPlotWZ)                                                totalWeight = totalWeight * thePandaFlat.sf_wz;
	else if(infileCat_[ifile] == kPlotZZ && infileName_[ifile].Contains("qqZZ") == true) totalWeight = totalWeight * thePandaFlat.sf_zz;

        if     (infileCat_[ifile] == kPlotVG && year == 2016) totalWeight = totalWeight * 1.55;
        else if(infileCat_[ifile] == kPlotVG && year == 2017) totalWeight = totalWeight * 1.00;
        else if(infileCat_[ifile] == kPlotVG && year == 2018) totalWeight = totalWeight * 1.45;

	if(passPhoSel == true || passPhoSelUp == true || passPhoSelDown == true) {
          double photonSF = 1.0;
          if     (thePandaFlat.looseGenPho1PdgId == 1) {
	    int nxbin = fhDElePhoSF->GetXaxis()->FindBin(TMath::Abs(vPhoton.Eta()));
	    int nybin = fhDElePhoSF->GetYaxis()->FindBin(TMath::Min((double)vPhoton.Pt(), 124.999));
            photonSF = fhDElePhoSF->GetBinContent(nxbin, nybin);
	    photonSFUnc[2] = (photonSF+fhDElePhoSF->GetBinError(nxbin, nybin))/photonSF;
	  }
          else if(thePandaFlat.looseGenPho1PdgId == 3) {
            photonSF = effhDPhotonScaleFactor(vPhoton.Pt(), vPhoton.Eta(), "medium", fhDPhotonSF, fhDElectronVetoSF); photonSFUnc[0] = 1.02;
	  }
          else {
            photonSF = 1.0; photonSFUnc[1] = 1.10;
	  }
	  totalWeight = totalWeight * photonSF;
	}

        double effSF = 1.0;
        for(unsigned int nl=0; nl<idLep.size(); nl++){
          if(idLep[nl] == 0) continue;
          bool applyTight = false;
          effSF = effSF * lepScaleFactor(vLoose[nl].Pt(),vLoose[nl].Eta(),TMath::Abs(looseLepPdgId[nl]),applyTight,histoLepEffSelMediumEtaPt_m,histoLepEffSelMediumEtaPt_e,histoLepEffSelTightEtaPt_m,histoLepEffSelTightEtaPt_e);
          if(effSF == 0){printf("effSF == 0!: %f %f %d \n",vLoose[nl].Pt(),vLoose[nl].Eta(),TMath::Abs(looseLepPdgId[nl])); return;}
        }
        totalWeight = totalWeight * effSF;
      }

      if(usePureMC == false && countLeptonTight != idLep.size()){
        double fakeSF = 1.0;
        for(unsigned int nl=0; nl<idLep.size(); nl++){
          if(idLep[nl] == 1) continue;
          bool applyTight = false;
          if(whichWln == (int)nl) applyTight = true;
          fakeSF = fakeSF * fakeRateFactor(TMath::Min((double)vLoose[nl].Pt(),44.999),TMath::Abs(vLoose[nl].Eta()),TMath::Abs(looseLepPdgId[nl]),applyTight,histoFakeEffSelMediumEtaPt_m,histoFakeEffSelMediumEtaPt_e,histoFakeEffSelTightEtaPt_m,histoFakeEffSelTightEtaPt_e);
          theCategory = kPlotNonPrompt;
        }
        if     (infileCat_[ifile] != kPlotData && countLeptonTight == idLep.size()-4) fakeSF = +1.0 * fakeSF; // fourth fake, MC
        else if(infileCat_[ifile] != kPlotData && countLeptonTight == idLep.size()-3) fakeSF = -1.0 * fakeSF; // triple fake, MC
        else if(infileCat_[ifile] != kPlotData && countLeptonTight == idLep.size()-2) fakeSF = +1.0 * fakeSF; // double fake, MC
        else if(infileCat_[ifile] != kPlotData && countLeptonTight == idLep.size()-1) fakeSF = -1.0 * fakeSF; // single fake, MC
        else if(infileCat_[ifile] == kPlotData && countLeptonTight == idLep.size()-4) fakeSF = -1.0 * fakeSF; // fourth fake, data
        else if(infileCat_[ifile] == kPlotData && countLeptonTight == idLep.size()-3) fakeSF = +1.0 * fakeSF; // triple fake, data
        else if(infileCat_[ifile] == kPlotData && countLeptonTight == idLep.size()-2) fakeSF = -1.0 * fakeSF; // double fake, data
        else if(infileCat_[ifile] == kPlotData && countLeptonTight == idLep.size()-1) fakeSF = +1.0 * fakeSF; // single fake, data
        else printf("IMPOSSIBLE FAKE OPTION\n");
        totalWeight = totalWeight * fakeSF;
      }

      double elePhoEffda = 0.0;
      if(passAllCuts[WZSEL] && abs(looseLepPdgId[whichWln]) == 11){
        if((vZ1l1.Pt() > 25 || vZ1l2.Pt() > 25) &&
	    vZ1l1.Pt() > 20 && vZ1l2.Pt() > 20  && vWln.Pt() > 25){ // Requirements to emulate signal selection
          int nxbin = fhDElePhoEffda->GetXaxis()->FindBin(TMath::Abs(theG.Eta()));
          int nybin = fhDElePhoEffda->GetYaxis()->FindBin(TMath::Min((double)theG.Pt(), 124.999));
          elePhoEffda = fhDElePhoEffda->GetBinContent(nxbin, nybin);
        }
      }

      if(passAllCuts[ZHGSEL]) {
        srYields [thePandaFlat.looseGenPho1PdgId] = srYields [thePandaFlat.looseGenPho1PdgId] + totalWeight;
        srYieldsE[thePandaFlat.looseGenPho1PdgId] = srYieldsE[thePandaFlat.looseGenPho1PdgId] + totalWeight * totalWeight;
      }

      if(infileCat_[ifile] == kPlotVG && lepType != 2){
        if(passNMinusA) normForABCD[0] = normForABCD[0] + totalWeight;
        if(passNMinusB) normForABCD[1] = normForABCD[1] + totalWeight;
        if(passNMinusC) normForABCD[2] = normForABCD[2] + totalWeight;
        if(passNMinusD) normForABCD[3] = normForABCD[3] + totalWeight;
      }

      if(passAllCuts[ZHGSEL])histo[lepType+  0][theCategory]->Fill(TMath::Min(mTGMET,349.999),totalWeight);
      if(passAllCuts[BTAGSEL])histo[lepType+ 3][theCategory]->Fill(TMath::Min(mTGMET,349.999),totalWeight);
      if(passAllCuts[ZLGSEL])histo[lepType+  6][theCategory]->Fill(TMath::Min(mTGMET,349.999),totalWeight);
      if(passAllCuts[WZSEL])histo[lepType+   9][theCategory]->Fill(TMath::Min(mTGMET,349.999),totalWeight);
      if(passAllCuts[WZGSEL])histo[lepType+ 13][theCategory]->Fill(TMath::Min(mTGMET,349.999),totalWeight);
      if(passAllCuts[ZZSEL])histo[lepType+  17][theCategory]->Fill(TMath::Min(mTGMET,349.999),totalWeight);
      if(passAllCuts[WWSEL])histo[lepType+  21][theCategory]->Fill(TMath::Min(mTGMET,349.999),totalWeight);
      if(passNMinusOne[ 0] && lepType != 2)  histo[24][theCategory]->Fill(TMath::Min(TMath::Abs(mllZ-91.1876),99.999),totalWeight);
      if(passNMinusOne[ 1] && lepType != 2)  histo[25][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJot,4.4999),totalWeight);
      if(passNMinusOne[ 2] && lepType != 2)  histo[26][theCategory]->Fill(TMath::Min(vMet.Pt(),229.999),totalWeight);
      if(passNMinusOne[ 3] && lepType != 2)  histo[27][theCategory]->Fill(TMath::Min(ptFracG,0.999),totalWeight);
      if(passNMinusOne[ 4] && lepType != 2)  histo[28][theCategory]->Fill(dPhiDiLepGMET,totalWeight);
      if(passNMinusOne[ 5] && lepType != 2)  histo[29][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNMBtags,3.499),totalWeight);
      if(passNMinusOne[ 6] && lepType != 2)  histo[30][theCategory]->Fill(TMath::Min(dilep.Pt(),199.999),totalWeight);
      if(passNMinusOne[ 7] && lepType != 2)  histo[31][theCategory]->Fill(TMath::Min(dPhiJetMET,2.999),totalWeight);
      if(passNMinusOne[ 8] && lepType != 2)  histo[32][theCategory]->Fill(TMath::Min((double)thePandaFlat.nTau,3.499),totalWeight);
      if(passNMinusOne[ 9] && lepType != 2)  histo[33][theCategory]->Fill(TMath::Min(mTGMET,399.999),totalWeight);
      if(passNMinusOne[10] && lepType != 2)  histo[34][theCategory]->Fill(TMath::Min(TMath::Max(dilepG.M(),70.001),369.999),totalWeight);
      if(passAllCuts[ZHGSEL] && lepType != 2)histo[35][theCategory]->Fill(TMath::Abs(theG.Eta()),totalWeight);
      if(passAllCuts[ZHGSEL] && lepType != 2)histo[36][theCategory]->Fill((double)((thePandaFlat.loosePho1SelBit & pTrkVeto) == pTrkVeto),totalWeight);
      for(int i=0; i<11; i++) {passCutEvolAll = passCutEvolAll && passCutEvol[i]; if(passCutEvolAll) histo[lepType+37][theCategory]->Fill((double)i,totalWeight);}
      if(passAllCuts[ZHGSEL] && lepType != 2)histo[40][theCategory]->Fill(thePandaFlat.jotEta[0],totalWeight);
      if(passNMinusFour && lepType != 2) {
        histo[41][theCategory]->Fill(TMath::Min(vMet.Pt(),229.999),totalWeight);
        histo[42][theCategory]->Fill(TMath::Min(ptFracG,0.999),totalWeight);
        histo[43][theCategory]->Fill(TMath::Min(ptFrac,0.999),totalWeight);
        histo[44][theCategory]->Fill(dPhiDiLepGMET,totalWeight);
        histo[45][theCategory]->Fill(dPhiTriLepMET,totalWeight);
	histo[46][theCategory]->Fill(TMath::Min(mTGMET,399.999),totalWeight);
      }
      if(passNMinusThree && lepType != 2) {
        histo[47][theCategory]->Fill(dPhiDiLepGMET,totalWeight);
	histo[48][theCategory]->Fill(TMath::Min(dPhiJetMET,2.999),totalWeight);
	histo[49][theCategory]->Fill(TMath::Min(mTGMET,399.999),totalWeight);
      }
      if(passAllCuts[ZHGSEL] && lepType != 2) histo[50][theCategory]->Fill(TMath::Min(TMath::Max(vLoose[0].Pt(),vLoose[1].Pt()),424.999),totalWeight);
      if(passAllCuts[ZHGSEL] && lepType != 2) histo[51][theCategory]->Fill(TMath::Min(TMath::Min(vLoose[0].Pt(),vLoose[1].Pt()),219.999),totalWeight);
      if(passAllCuts[WZSEL]) histo[52][theCategory]->Fill(TMath::Min(mTGMET,349.999),totalWeight*elePhoEffda);
      if(passAllCuts[ZHGSEL] && lepType != 2){
        if(TMath::Abs(theG.Eta()) <= 1.0) histo[53][theCategory]->Fill(TMath::Min(mTGMET,349.999),totalWeight);
        else                              histo[54][theCategory]->Fill(TMath::Min(mTGMET,349.999),totalWeight);
      }

      if(1){ // Begin datacard making
        double MVAVar     = mTGMET;
        double MVAVarUp   = mTGMETUp;
        double MVAVarDown = mTGMETDown;
        double MVAVarMUp  = mTGMETMUp;  
        double MVAVarMDown= mTGMETMDown;
        double MVAVarEUp  = mTGMETEUp;  
        double MVAVarEDown= mTGMETEDown;
        double MVAVarGUp  = mTGMETGUp;
        double MVAVarGDown= mTGMETGDown;
        if     (lepType == 2 && theMinSelType == 0) {MVAVar = -0.5; MVAVarUp = -0.5; MVAVarDown = -0.5;
	}
        else {
          if(TMath::Abs(theG.Eta()) > 1.0){
            MVAVar     = MVAVar     + 400.0;
            MVAVarUp   = MVAVarUp   + 400.0;
            MVAVarDown = MVAVarDown + 400.0;
	  }
          if(dataCardSel     == 1) {MVAVar     = MVAVar	    +  800.0;}
          if(dataCardSelUp   == 1) {MVAVarUp   = MVAVarUp   +  800.0;}
          if(dataCardSelDown == 1) {MVAVarDown = MVAVarDown +  800.0;}
          if(dataCardSel     == 2) {MVAVar     = MVAVar	    + 1600.0;}
          if(dataCardSelUp   == 2) {MVAVarUp   = MVAVarUp   + 1600.0;}
          if(dataCardSelDown == 2) {MVAVarDown = MVAVarDown + 1600.0;}
        }

        if      (lepType == 2 && theMinSelTypeMUp == 0)                   MVAVarMUp = -0.5;
        else if(theMinSelTypeMUp == 0 && TMath::Abs(theGMUp.Eta()) > 1.0) MVAVarMUp = MVAVarMUp + 400.0;

        if      (lepType == 2 && theMinSelTypeMDown == 0)                     MVAVarMDown = -0.5;
        else if(theMinSelTypeMDown == 0 && TMath::Abs(theGMDown.Eta()) > 1.0) MVAVarMDown = MVAVarMDown + 400.0;

        if      (lepType == 2 && theMinSelTypeEUp == 0)                   MVAVarEUp = -0.5;
        else if(theMinSelTypeEUp == 0 && TMath::Abs(theGEUp.Eta()) > 1.0) MVAVarEUp = MVAVarEUp + 400.0;

        if      (lepType == 2 && theMinSelTypeEDown == 0)                     MVAVarEDown = -0.5;
        else if(theMinSelTypeEDown == 0 && TMath::Abs(theGEDown.Eta()) > 1.0) MVAVarEDown = MVAVarEDown + 400.0;

        if      (lepType == 2 && theMinSelTypeGUp == 0)                   MVAVarGUp = -0.5;
        else if(theMinSelTypeGUp == 0 && TMath::Abs(theGGUp.Eta()) > 1.0) MVAVarGUp = MVAVarGUp + 400.0;

        if      (lepType == 2 && theMinSelTypeGDown == 0)                     MVAVarGDown = -0.5;
        else if(theMinSelTypeGDown == 0 && TMath::Abs(theGGDown.Eta()) > 1.0) MVAVarGDown = MVAVarGDown + 400.0;

        if     (dataCardSelMUp     == 1) MVAVarMUp   = MVAVar;
        else if(dataCardSelMUp     == 2) MVAVarMUp   = MVAVar;
        if     (dataCardSelMDown   == 1) MVAVarMDown = MVAVar;
        else if(dataCardSelMDown   == 2) MVAVarMDown = MVAVar;
        if     (dataCardSelEUp     == 1) MVAVarEUp   = MVAVar;
        else if(dataCardSelEUp     == 2) MVAVarEUp   = MVAVar;
        if     (dataCardSelEDown   == 1) MVAVarEDown = MVAVar;
        else if(dataCardSelEDown   == 2) MVAVarEDown = MVAVar;
        if     (dataCardSelGUp     == 1) MVAVarGUp   = MVAVar;
        else if(dataCardSelGUp     == 2) MVAVarGUp   = MVAVar;
        if     (dataCardSelGDown   == 1) MVAVarGDown = MVAVar;
        else if(dataCardSelGDown   == 2) MVAVarGDown = MVAVar;

        double rndWeights[4] = {1,1,1,1};
	if(dataCardSelMUp   >= 1) rndWeights[0] = 1+gRandom->Uniform()*0.01;
	if(dataCardSelMDown >= 1) rndWeights[1] = 1-gRandom->Uniform()*0.01;
	if(dataCardSelEUp   >= 1) rndWeights[2] = 1+gRandom->Uniform()*0.01;
	if(dataCardSelEDown >= 1) rndWeights[3] = 1-gRandom->Uniform()*0.01;

        // Avoid QCD scale weights that are anomalous high
        double maxQCDscale = (TMath::Abs(thePandaFlat.scale[0])+TMath::Abs(thePandaFlat.scale[1])+TMath::Abs(thePandaFlat.scale[2])+
	                      TMath::Abs(thePandaFlat.scale[3])+TMath::Abs(thePandaFlat.scale[4])+TMath::Abs(thePandaFlat.scale[5]))/6.0;
        if(maxQCDscale == 0) maxQCDscale = 1;

        double sf_ewkcorrwz_unc = 1.0; double sf_ewkcorrzz_unc = 1.0; double sf_ggcorrzz_unc = 1.0;
	if(theCategory == kPlotWZ) sf_ewkcorrwz_unc = 1.02;
	if     (theCategory == kPlotZZ && infileName_[ifile].Contains("qqZZ") == true) sf_ewkcorrzz_unc = thePandaFlat.sf_zzUnc;
	else if(theCategory == kPlotZZ) sf_ggcorrzz_unc = 1.10;

        if     (theCategory == kPlotData && dataCardSel >= 0){
          histo_Baseline[theCategory]->Fill(MVAVar,totalWeight);
        }
        else if(theCategory != kPlotData){
	  if(dataCardSel >= 0) {
	    double pdf_error = pdfUncs[0]; if(theCategory == kPlotBSM) pdf_error = pdfUncs[1];
	    histo_Baseline[theCategory]->Fill(MVAVar,totalWeight);
	    histo_QCDScaleBounding[theCategory][0]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[0])/maxQCDscale);
	    histo_QCDScaleBounding[theCategory][1]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[1])/maxQCDscale);
	    histo_QCDScaleBounding[theCategory][2]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[2])/maxQCDscale);
	    histo_QCDScaleBounding[theCategory][3]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[3])/maxQCDscale);
	    histo_QCDScaleBounding[theCategory][4]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[4])/maxQCDscale);
	    histo_QCDScaleBounding[theCategory][5]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[5])/maxQCDscale);
	    histo_PDFBoundingUp[theCategory]  ->Fill(MVAVar,totalWeight*TMath::Max((double)thePandaFlat.pdfUp,pdf_error));
	    histo_PDFBoundingDown[theCategory]->Fill(MVAVar,totalWeight*TMath::Min((double)thePandaFlat.pdfDown,1.0/pdf_error));
            histo_LepEffMBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*muSFUnc); histo_LepEffEBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*elSFUnc);
            histo_LepEffMBoundingDown[theCategory]->Fill(MVAVar,totalWeight/muSFUnc); histo_LepEffEBoundingDown[theCategory]->Fill(MVAVar,totalWeight/elSFUnc);
            histo_PUBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*puWeightUp  /puWeight);
            histo_PUBoundingDown[theCategory]->Fill(MVAVar,totalWeight*puWeightDown/puWeight);
	    for(int ny=0; ny<nYears; ny++){
	      if(ny == whichYear) {
                histo_BTAGBBoundingUp  [ny][theCategory]->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0BUp  /thePandaFlat.sf_btag0);
                histo_BTAGBBoundingDown[ny][theCategory]->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0BDown/thePandaFlat.sf_btag0);
                histo_BTAGLBoundingUp  [ny][theCategory]->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0MUp  /thePandaFlat.sf_btag0);
                histo_BTAGLBoundingDown[ny][theCategory]->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0MDown/thePandaFlat.sf_btag0);
                histo_PreFireBoundingUp  [ny][theCategory]->Fill(MVAVar,totalWeight*sf_l1PrefireE);
                histo_PreFireBoundingDown[ny][theCategory]->Fill(MVAVar,totalWeight/sf_l1PrefireE);
                histo_TriggerBoundingUp  [ny][theCategory]->Fill(MVAVar,totalWeight*(1+triggerWeights[1]));
                histo_TriggerBoundingDown[ny][theCategory]->Fill(MVAVar,totalWeight/(1+triggerWeights[1]));
              } else {
                histo_BTAGBBoundingUp  [ny][theCategory]->Fill(MVAVar,totalWeight);
                histo_BTAGBBoundingDown[ny][theCategory]->Fill(MVAVar,totalWeight);
                histo_BTAGLBoundingUp  [ny][theCategory]->Fill(MVAVar,totalWeight);
                histo_BTAGLBoundingDown[ny][theCategory]->Fill(MVAVar,totalWeight);
                histo_PreFireBoundingUp  [ny][theCategory]->Fill(MVAVar,totalWeight);
                histo_PreFireBoundingDown[ny][theCategory]->Fill(MVAVar,totalWeight);		
                histo_TriggerBoundingUp  [ny][theCategory]->Fill(MVAVar,totalWeight);
                histo_TriggerBoundingDown[ny][theCategory]->Fill(MVAVar,totalWeight);
	      }
	    }
	    histo_PhoEffBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*photonSFUnc[0]);
	    histo_PhoEffBoundingDown[theCategory]->Fill(MVAVar,totalWeight/photonSFUnc[0]);
	    histo_PhoFakeBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*photonSFUnc[1]);
	    histo_PhoFakeBoundingDown[theCategory]->Fill(MVAVar,totalWeight/photonSFUnc[1]);
	    histo_ElToPhRateBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*photonSFUnc[2]);
	    histo_ElToPhRateBoundingDown[theCategory]->Fill(MVAVar,totalWeight/photonSFUnc[2]);
	    histo_EWKCorrWZUp  [theCategory]->Fill(MVAVar,totalWeight*sf_ewkcorrwz_unc);
	    histo_EWKCorrWZDown[theCategory]->Fill(MVAVar,totalWeight/sf_ewkcorrwz_unc);
	    histo_EWKqqZZCorrUp  [theCategory]->Fill(MVAVar,totalWeight*sf_ewkcorrzz_unc);
	    histo_EWKqqZZCorrDown[theCategory]->Fill(MVAVar,totalWeight/sf_ewkcorrzz_unc);
	    histo_ggZZCorrUp  [theCategory]->Fill(MVAVar,totalWeight*sf_ggcorrzz_unc);
	    histo_ggZZCorrDown[theCategory]->Fill(MVAVar,totalWeight/sf_ggcorrzz_unc);
	  }
	  for(int ny=0; ny<nYears; ny++){
	    if(ny == whichYear) {
              if(passSystCuts[JESUP])   histo_JESBoundingUp  [ny][theCategory]->Fill(MVAVarUp  ,totalWeight);
              if(passSystCuts[JESDOWN]) histo_JESBoundingDown[ny][theCategory]->Fill(MVAVarDown,totalWeight);
            } else {
              if(dataCardSel >= 0) histo_JESBoundingUp  [ny][theCategory]->Fill(MVAVar,totalWeight);
              if(dataCardSel >= 0) histo_JESBoundingDown[ny][theCategory]->Fill(MVAVar,totalWeight);
	    }
	  }
          if(passSystCuts[SCALEMUP])   histo_ScaleMBoundingUp  [theCategory]->Fill(MVAVarMUp  ,totalWeight*rndWeights[0]);
          if(passSystCuts[SCALEMDOWN]) histo_ScaleMBoundingDown[theCategory]->Fill(MVAVarMDown,totalWeight*rndWeights[1]);
          if(passSystCuts[SCALEEUP])   histo_ScaleEBoundingUp  [theCategory]->Fill(MVAVarEUp  ,totalWeight*rndWeights[2]);
          if(passSystCuts[SCALEEDOWN]) histo_ScaleEBoundingDown[theCategory]->Fill(MVAVarEDown,totalWeight*rndWeights[3]);
          if(passSystCuts[SCALEGUP])   histo_ScaleGBoundingUp  [theCategory]->Fill(MVAVarGUp  ,totalWeight);
          if(passSystCuts[SCALEGDOWN]) histo_ScaleGBoundingDown[theCategory]->Fill(MVAVarGDown,totalWeight);
        }
      } // End datacard making
    } // end events loop
    printf("srYields: %.2f +/- %.2f / %.2f +/- %.2f / %.2f +/- %.2f / %.2f +/- %.2f\n",
            srYields[0],sqrt(srYieldsE[0]),srYields[1],sqrt(srYieldsE[1]),
            srYields[2],sqrt(srYieldsE[2]),srYields[3],sqrt(srYieldsE[3]));
    the_input_file->Close();
  } // end chain loop

  for(int ic=1; ic<nPlotCategories; ic++) if(histo_Baseline[ic]->GetSumOfWeights() < 0) histo_Baseline[ic]->Scale(0.0);
  for(int ic=0; ic<nPlotCategories; ic++) histo[allPlots-1][ic]->Add(histo_Baseline[ic]);

  double qcdScaleTotal[2] = {0.0345, 0.2200}; // use sigma(ZH) (0.0345) instead of sigma(qq->ZZ) (0.0055) and sigma(gg->ZH) (0.2200)
  double pdfTotal[2] = {0.016, 0.051};
  double syst_WZl[2] = {1.010, 1.012};

  for(unsigned ic=0; ic<nPlotCategories; ic++) {
    if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    for(int nb=1; nb<=histo_Baseline[ic]->GetNbinsX(); nb++){
      // compute QCD scale uncertainties bin-by-bin
      double diffQCDScale[6] = {
       TMath::Abs(histo_QCDScaleBounding[ic][0]->GetBinContent(nb)-histo_Baseline[ic]->GetBinContent(nb)),
       TMath::Abs(histo_QCDScaleBounding[ic][1]->GetBinContent(nb)-histo_Baseline[ic]->GetBinContent(nb)),
       TMath::Abs(histo_QCDScaleBounding[ic][2]->GetBinContent(nb)-histo_Baseline[ic]->GetBinContent(nb)),
       TMath::Abs(histo_QCDScaleBounding[ic][3]->GetBinContent(nb)-histo_Baseline[ic]->GetBinContent(nb)),
       TMath::Abs(histo_QCDScaleBounding[ic][4]->GetBinContent(nb)-histo_Baseline[ic]->GetBinContent(nb)),
       TMath::Abs(histo_QCDScaleBounding[ic][5]->GetBinContent(nb)-histo_Baseline[ic]->GetBinContent(nb))};

      double systQCDScale = diffQCDScale[0];
      for(int nqcd=1; nqcd<6; nqcd++) {
        if(diffQCDScale[nqcd] > systQCDScale) systQCDScale = diffQCDScale[nqcd];
      }

      if(histo_Baseline[ic]->GetBinContent(nb) > 0) 
        systQCDScale = 1.0+systQCDScale/histo_Baseline[ic]->GetBinContent(nb);
      else systQCDScale = 1;

      histo_QCDScaleUp  [ic]->SetBinContent(nb, histo_Baseline[ic]->GetBinContent(nb)*systQCDScale);
      histo_QCDScaleDown[ic]->SetBinContent(nb, histo_Baseline[ic]->GetBinContent(nb)/systQCDScale);

      histo_Baseline              [ic]->SetBinContent(nb, TMath::Max((float)histo_Baseline		[ic]->GetBinContent(nb),1e-7f));
      histo_QCDScaleUp  	  [ic]->SetBinContent(nb, TMath::Max((float)histo_QCDScaleUp		[ic]->GetBinContent(nb),1e-7f));
      histo_QCDScaleDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_QCDScaleDown  	[ic]->GetBinContent(nb),1e-7f));
      histo_PDFBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PDFBoundingUp 	[ic]->GetBinContent(nb),1e-7f));
      histo_PDFBoundingDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PDFBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      histo_LepEffMBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_LepEffMBoundingUp	[ic]->GetBinContent(nb),1e-7f));
      histo_LepEffMBoundingDown   [ic]->SetBinContent(nb, TMath::Max((float)histo_LepEffMBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      histo_LepEffEBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_LepEffEBoundingUp	[ic]->GetBinContent(nb),1e-7f));
      histo_LepEffEBoundingDown   [ic]->SetBinContent(nb, TMath::Max((float)histo_LepEffEBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      histo_ScaleMBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_ScaleMBoundingUp      [ic]->GetBinContent(nb),1e-7f));
      histo_ScaleMBoundingDown    [ic]->SetBinContent(nb, TMath::Max((float)histo_ScaleMBoundingDown    [ic]->GetBinContent(nb),1e-7f));
      histo_ScaleEBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_ScaleEBoundingUp      [ic]->GetBinContent(nb),1e-7f));
      histo_ScaleEBoundingDown    [ic]->SetBinContent(nb, TMath::Max((float)histo_ScaleEBoundingDown    [ic]->GetBinContent(nb),1e-7f));
      histo_ScaleGBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_ScaleGBoundingUp      [ic]->GetBinContent(nb),1e-7f));
      histo_ScaleGBoundingDown    [ic]->SetBinContent(nb, TMath::Max((float)histo_ScaleGBoundingDown    [ic]->GetBinContent(nb),1e-7f));
      histo_PUBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PUBoundingUp  	[ic]->GetBinContent(nb),1e-7f));
      histo_PUBoundingDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PUBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      for(int ny=0; ny<nYears; ny++){
      histo_BTAGBBoundingUp    [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_BTAGBBoundingUp    [ny][ic]->GetBinContent(nb),1e-7f));
      histo_BTAGBBoundingDown  [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_BTAGBBoundingDown  [ny][ic]->GetBinContent(nb),1e-7f));
      histo_BTAGLBoundingUp    [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_BTAGLBoundingUp    [ny][ic]->GetBinContent(nb),1e-7f));
      histo_BTAGLBoundingDown  [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_BTAGLBoundingDown  [ny][ic]->GetBinContent(nb),1e-7f));
      histo_JESBoundingUp      [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_JESBoundingUp      [ny][ic]->GetBinContent(nb),1e-7f));
      histo_JESBoundingDown    [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_JESBoundingDown    [ny][ic]->GetBinContent(nb),1e-7f));
      histo_PreFireBoundingUp  [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_PreFireBoundingUp  [ny][ic]->GetBinContent(nb),1e-7f));
      histo_PreFireBoundingDown[ny][ic]->SetBinContent(nb, TMath::Max((float)histo_PreFireBoundingDown[ny][ic]->GetBinContent(nb),1e-7f));
      histo_TriggerBoundingUp  [ny][ic]->SetBinContent(nb, TMath::Max((float)histo_TriggerBoundingUp  [ny][ic]->GetBinContent(nb),1e-7f));
      histo_TriggerBoundingDown[ny][ic]->SetBinContent(nb, TMath::Max((float)histo_TriggerBoundingDown[ny][ic]->GetBinContent(nb),1e-7f));
      }
      histo_PhoEffBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PhoEffBoundingUp	[ic]->GetBinContent(nb),1e-7f));
      histo_PhoEffBoundingDown    [ic]->SetBinContent(nb, TMath::Max((float)histo_PhoEffBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      histo_PhoFakeBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PhoFakeBoundingUp	[ic]->GetBinContent(nb),1e-7f));
      histo_PhoFakeBoundingDown   [ic]->SetBinContent(nb, TMath::Max((float)histo_PhoFakeBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      histo_ElToPhRateBoundingUp  [ic]->SetBinContent(nb, TMath::Max((float)histo_ElToPhRateBoundingUp  [ic]->GetBinContent(nb),1e-7f));
      histo_ElToPhRateBoundingDown[ic]->SetBinContent(nb, TMath::Max((float)histo_ElToPhRateBoundingDown[ic]->GetBinContent(nb),1e-7f));
      histo_EWKCorrWZUp 	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKCorrWZUp		[ic]->GetBinContent(nb),1e-7f));
      histo_EWKCorrWZDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKCorrWZDown 	[ic]->GetBinContent(nb),1e-7f));
      histo_EWKqqZZCorrUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKqqZZCorrUp 	[ic]->GetBinContent(nb),1e-7f));
      histo_EWKqqZZCorrDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKqqZZCorrDown	[ic]->GetBinContent(nb),1e-7f));
      histo_ggZZCorrUp  	  [ic]->SetBinContent(nb, TMath::Max((float)histo_ggZZCorrUp		[ic]->GetBinContent(nb),1e-7f));
      histo_ggZZCorrDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_ggZZCorrDown  	[ic]->GetBinContent(nb),1e-7f));
    }
    histo_PUBoundingUp	[ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_PUBoundingUp  [ic]->GetSumOfWeights());
    histo_PUBoundingDown[ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_PUBoundingDown[ic]->GetSumOfWeights());
    if(ic == kPlotBSM || ic == kPlotZZ) {
      histo_QCDScaleUp  [ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_QCDScaleUp  [ic]->GetSumOfWeights());
      histo_QCDScaleDown[ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_QCDScaleDown[ic]->GetSumOfWeights());
    }
  }

  if(showSyst == true){
    printf("Yields\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) printf("%6.2f ",histo_Baseline[ic]->GetBinContent(i)); printf("\n");
    }
    printf("uncertainties Statistical\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_Baseline[ic]->GetBinError(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties QCDSCALEUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_QCDScaleUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties QCDSCALEDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_QCDScaleDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties PDFUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_PDFBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties PDFDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_PDFBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties LEPEFFMUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_LepEffMBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties LEPEFFMDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_LepEffMBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties LEPEFFEUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_LepEffEBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties LEPEFFEDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_LepEffEBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties ScaleMUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_ScaleMBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties ScaleMDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_ScaleMBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties ScaleEUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_ScaleEBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties ScaleEDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_ScaleEBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties ScaleGUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_ScaleGBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties ScaleGDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_ScaleGBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties PUUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_PUBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties PUDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_PUBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    for(int ny=0; ny<nYears; ny++){
      printf("uncertainties year (%d)\n",ny);
      printf("uncertainties BTAGBUp\n");
      for(unsigned ic=0; ic<nPlotCategories; ic++) {
	if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
           printf("%10s: ",plotBaseNames[ic].Data());
          for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_BTAGBBoundingUp[ny][ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      }
      printf("uncertainties BTAGBDown\n");
      for(unsigned ic=0; ic<nPlotCategories; ic++) {
	if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
           printf("%10s: ",plotBaseNames[ic].Data());
          for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_BTAGBBoundingDown[ny][ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      }

      printf("uncertainties BTAGLUp\n");
      for(unsigned ic=0; ic<nPlotCategories; ic++) {
	if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
           printf("%10s: ",plotBaseNames[ic].Data());
          for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_BTAGLBoundingUp[ny][ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      }
      printf("uncertainties BTAGLDown\n");
      for(unsigned ic=0; ic<nPlotCategories; ic++) {
	if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
           printf("%10s: ",plotBaseNames[ic].Data());
          for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_BTAGLBoundingDown[ny][ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      }

      printf("uncertainties JESUp\n");
      for(unsigned ic=0; ic<nPlotCategories; ic++) {
	if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
           printf("%10s: ",plotBaseNames[ic].Data());
          for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_JESBoundingUp[ny][ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      }
      printf("uncertainties JESDown\n");
      for(unsigned ic=0; ic<nPlotCategories; ic++) {
	if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
           printf("%10s: ",plotBaseNames[ic].Data());
          for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_JESBoundingDown[ny][ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      }

      printf("uncertainties PreFireUp\n");
      for(unsigned ic=0; ic<nPlotCategories; ic++) {
	if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
           printf("%10s: ",plotBaseNames[ic].Data());
          for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_PreFireBoundingUp[ny][ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      }
      printf("uncertainties PreFireDown\n");
      for(unsigned ic=0; ic<nPlotCategories; ic++) {
	if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
           printf("%10s: ",plotBaseNames[ic].Data());
          for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_PreFireBoundingDown[ny][ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      }

      printf("uncertainties TriggerUp\n");
      for(unsigned ic=0; ic<nPlotCategories; ic++) {
	if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
           printf("%10s: ",plotBaseNames[ic].Data());
          for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_TriggerBoundingUp[ny][ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      }
      printf("uncertainties TriggerDown\n");
      for(unsigned ic=0; ic<nPlotCategories; ic++) {
	if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
           printf("%10s: ",plotBaseNames[ic].Data());
          for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_TriggerBoundingDown[ny][ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
      }
      printf("---------\n");
    }

    printf("uncertainties PHOEFFUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_PhoEffBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties PHOEFFDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_PhoEffBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties PHOFakeUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_PhoFakeBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties PHOFakeDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_PhoFakeBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties ElToPhRateUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_ElToPhRateBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties ElToPhRateDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_ElToPhRateBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties EWKCorrWZUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_EWKCorrWZUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties EWKCorrWZDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_EWKCorrWZDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties EWKqqCorrZZUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_EWKqqZZCorrUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties EWKqqCorrZZDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_EWKqqZZCorrDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties ggCorrZZUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_ggZZCorrUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties ggCorrZZDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_ggZZCorrDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
  }

  // Filling datacards input root file
  char outputLimits[200];
  sprintf(outputLimits,"zhg_%d_mH%d_input.root",year,mH);
  TFile* outFileLimits = new TFile(outputLimits,"recreate");
  outFileLimits->cd();

  double theScale;
  for(unsigned ic=0; ic<nPlotCategories; ic++) {
    if(ic != kPlotData && histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    histo_Baseline		[ic]->Write();
    if(ic == kPlotData) continue;
    histo_QCDScaleUp		[ic]->Write();
    histo_QCDScaleDown  	[ic]->Write();
    histo_PDFBoundingUp 	[ic]->Write();
    histo_PDFBoundingDown	[ic]->Write();
    histo_LepEffMBoundingUp	[ic]->Write();
    histo_LepEffMBoundingDown	[ic]->Write();
    histo_LepEffEBoundingUp	[ic]->Write();
    histo_LepEffEBoundingDown	[ic]->Write();
    histo_ScaleMBoundingUp      [ic]->Write();
    histo_ScaleMBoundingDown    [ic]->Write();
    histo_ScaleEBoundingUp      [ic]->Write();
    histo_ScaleEBoundingDown    [ic]->Write();
    histo_ScaleGBoundingUp      [ic]->Write();
    histo_ScaleGBoundingDown    [ic]->Write();
    histo_PUBoundingUp  	[ic]->Write();
    histo_PUBoundingDown	[ic]->Write();
    for(int ny=0; ny<nYears; ny++){
    histo_BTAGBBoundingUp	[ny][ic]->Write();
    histo_BTAGBBoundingDown	[ny][ic]->Write();
    histo_BTAGLBoundingUp	[ny][ic]->Write();
    histo_BTAGLBoundingDown	[ny][ic]->Write();
    histo_JESBoundingUp 	[ny][ic]->Write();
    histo_JESBoundingDown	[ny][ic]->Write();
    histo_PreFireBoundingUp 	[ny][ic]->Write();
    histo_PreFireBoundingDown	[ny][ic]->Write();
    histo_TriggerBoundingUp 	[ny][ic]->Write();
    histo_TriggerBoundingDown	[ny][ic]->Write();
    }
    histo_PhoEffBoundingUp	[ic]->Write();
    histo_PhoEffBoundingDown	[ic]->Write();
    histo_PhoFakeBoundingUp	[ic]->Write();
    histo_PhoFakeBoundingDown	[ic]->Write();
    histo_ElToPhRateBoundingUp  [ic]->Write();
    histo_ElToPhRateBoundingDown[ic]->Write();
    histo_EWKCorrWZUp		[ic]->Write();
    histo_EWKCorrWZDown 	[ic]->Write();
    histo_EWKqqZZCorrUp 	[ic]->Write();
    histo_EWKqqZZCorrDown	[ic]->Write();
    histo_ggZZCorrUp		[ic]->Write();
    histo_ggZZCorrDown  	[ic]->Write();
  }
  outFileLimits->Close();


  // Filling datacards txt file
  char outputLimitsCard[200];  					  
  sprintf(outputLimitsCard,"datacard_zhg_mH%d_%d.txt",mH,year);
  ofstream newcardShape;
  newcardShape.open(outputLimitsCard);
  newcardShape << Form("imax * number of channels\n");
  newcardShape << Form("jmax * number of background minus 1\n");
  newcardShape << Form("kmax * number of nuisance parameters\n");

  newcardShape << Form("shapes    *   *   %s  histo_$PROCESS histo_$PROCESS_$SYSTEMATIC\n",outputLimits);
  newcardShape << Form("shapes data_obs * %s  histo_Data\n",outputLimits);

  newcardShape << Form("Observation %f\n",histo_Baseline[kPlotData]->GetSumOfWeights());

  newcardShape << Form("bin   ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("ch1  ");
  }
  newcardShape << Form("\n");
 
  newcardShape << Form("process  ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("%s  ", plotBaseNames[ic].Data());
  }
  newcardShape << Form("\n");


  newcardShape << Form("process  ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotBSM) newcardShape << Form("%d  ", ic);
    else               newcardShape << Form("%d  ", 0);
  }
  newcardShape << Form("\n");

  newcardShape << Form("rate  ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("%f  ", histo_Baseline[ic]->GetSumOfWeights());
  }
  newcardShape << Form("\n");

  newcardShape << Form("lumi_13TeV_%d    lnN     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("%6.3f ",lumiE[whichYear]);
  }
  newcardShape << Form("\n");

  newcardShape << Form("UEPS    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotBSM) newcardShape << Form(" - ");
    else               newcardShape << Form("%f  ", 1.02);
  }
  newcardShape << Form("\n");

  newcardShape << Form("EWKWZCorr    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotWZ) newcardShape << Form("- ");
    else              newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("EWKqqZZCorr    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotZZ) newcardShape << Form("- ");
    else              newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("ggZZCorr    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotZZ) newcardShape << Form("- ");
    else              newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("WZ_lep    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotWZ) newcardShape << Form("- ");
    else              newcardShape << Form("%f ",syst_WZl[0]);
  }
  newcardShape << Form("\n");

  newcardShape << Form("WZ_tau    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotWZ) newcardShape << Form("- ");
    else              newcardShape << Form("%f ",syst_WZl[1]);
  }
  newcardShape << Form("\n");

  newcardShape << Form("QCDscaleTotal_ZH    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotBSM) newcardShape << Form("- ");
    else               newcardShape << Form("%f ",1.0+qcdScaleTotal[0]);
  }
  newcardShape << Form("\n");

  for(unsigned ic=0; ic<nPlotCategories; ic++) {
    if(ic== kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("QCDScale_%s_ACCEPT    shape   ",plotBaseNames[ic].Data());
    for(unsigned ic2=0; ic2<nPlotCategories; ic2++) {
      if(ic2 == kPlotData || histo_Baseline[ic2]->GetSumOfWeights() <= 0) continue;
          if(ic==ic2) newcardShape << Form("1.0  ");
          else        newcardShape << Form("-  ");
      }
      newcardShape << Form("\n");
  }

  newcardShape << Form("PDF    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_eff_m    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_eff_e    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_scale_m    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_scale_e    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_scale_p    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_pu    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_btagb_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_btagl_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_jes_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_prefire_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_trigger_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_eff_photon    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_fake_photon    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_fake_el    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("ch1 autoMCStats 0\n");

  //newcardShape << Form("CMS_hzg_emnorm  rateParam * %s 1 [0,10]\n",plotBaseNames[kPlotEM].Data());
  //newcardShape << Form("CMS_hzg_wznorm  rateParam * %s 1 [0,10]\n",plotBaseNames[kPlotWZ].Data());
  //newcardShape << Form("CMS_hzg_zznorm  rateParam * %s 1 [0,10]\n",plotBaseNames[kPlotZZ].Data());

  newcardShape.close();

  // Writing standard histograms
  const int ZLLGHisto1 = 6; const int ZLLGHisto2 = 7;
  double normZLLG[3] = {histo[ZLLGHisto1][kPlotData]->GetSumOfWeights()+histo[ZLLGHisto2][kPlotData]->GetSumOfWeights(),
                        histo[ZLLGHisto1][kPlotVG  ]->GetSumOfWeights()+histo[ZLLGHisto2][kPlotVG  ]->GetSumOfWeights(),
			0};
  char output[200];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    sprintf(output,"histoZHG_mH%d_%d_%d.root",mH,year,thePlot);	
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    double totBck = 0;
    for(int i=1; i<nPlotCategories; i++) if(histo[thePlot][i]->GetSumOfWeights() < 0) histo[thePlot][i]->Scale(0.0);
    for(int i=1; i<nPlotCategories; i++) if(i != kPlotBSM) totBck = totBck + histo[thePlot][i]->GetSumOfWeights();
    printf("(%2d) %7.1f vs. %7.1f ",thePlot,histo[thePlot][0]->GetSumOfWeights(),totBck);
    printf("(");
    for(int i=1; i<nPlotCategories; i++) printf("%7.1f ",histo[thePlot][i]->GetSumOfWeights());
    printf(")\n");
    for(int np=0; np<nPlotCategories; np++) {histo[thePlot][np]->SetNameTitle(Form("histo%d",np),Form("histo%d",np));histo[thePlot][np]->Write();}
    outFilePlotsNote->Close();
    if(thePlot == ZLLGHisto1 || thePlot == ZLLGHisto2){
      for(int i=1; i<nPlotCategories; i++) if(i != kPlotBSM && i != kPlotVG) normZLLG[2] = normZLLG[2] + histo[thePlot][i]->GetSumOfWeights();
    }
  }
  printf("ZLLGSF (%f-%f)/%f = %f\n",normZLLG[0],normZLLG[2],normZLLG[1],(normZLLG[0]-normZLLG[2])/normZLLG[1]);
  printf("normVG: %f X %f / %f = %f vs. %f\n",normForABCD[1],normForABCD[2],normForABCD[3],normForABCD[1]*normForABCD[2]/normForABCD[3],normForABCD[0]);

  {
    for(int i=1; i<=histo[37][kPlotBSM]->GetNbinsX(); i++){
      printf("(%2d): (%6.2f+%6.2f=%6.2f) / (%6.2f+%6.2f=%6.2f)\n",i-1,
        histo[37][kPlotWZ ]->GetBinContent(i),histo[38][kPlotWZ ]->GetBinContent(i),histo[37][kPlotWZ ]->GetBinContent(i)+histo[38][kPlotWZ ]->GetBinContent(i),
	histo[37][kPlotBSM]->GetBinContent(i),histo[38][kPlotBSM]->GetBinContent(i),histo[37][kPlotBSM]->GetBinContent(i)+histo[38][kPlotBSM]->GetBinContent(i));
    }
  }

}
