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
#include "MitAnalysisRunII/panda/macros/9x/trigger_auxiliar.h"

const double mcPrescale = 1;
const bool usePureMC = false;
const int debug = 0;
const bool showSyst = true;

enum systType                     {JESUP=0, JESDOWN,  METUP,  METDOWN, nSystTypes};
TString systTypeName[nSystTypes]= {"JESUP","JESDOWN","METUP","METDOWN"};

void sswwAnalysis(
int year, int fidAna = 0, TString WZName = "WZ3l_MG"
){

  TString fidAnaName = "";
  if(fidAna == 1) fidAnaName = "_fiducial";
  // trigger
  double trgEff [3][nTrgBinPt1][nTrgBinPt2][nTrgBinEta1][nTrgBinEta2];
  double trgEffE[3][nTrgBinPt1][nTrgBinPt2][nTrgBinEta1][nTrgBinEta2];
  initialize_trgEff(trgEff, trgEffE, year);

  //*******************************************************
  //Inputs
  //*******************************************************
  double WSSF[5],WSSFE[5];
  if     (year == 2016){
    for(int i=0; i<5; i++) {WSSF[i] = WSSF_2016[i]; WSSFE[i] = WSSFE_2016[i];}
  }
  else if(year == 2017){
    for(int i=0; i<5; i++) {WSSF[i] = WSSF_2017[i]; WSSFE[i] = WSSFE_2017[i];}
  }
  else if(year == 2018){
    for(int i=0; i<5; i++) {WSSF[i] = WSSF_2018[i]; WSSFE[i] = WSSFE_2018[i];}
  }

  vector<TString> infileName_;
  vector<int> infileCat_;

  double lumi;
  TString filesPath;
  TString fLepton_FakesName;
  TString puPath;
  if     (year == 2018) {
    lumi = 56.1;
    filesPath = "/data/t3home000/ceballos/panda/v_006_0/";
    fLepton_FakesName = "MitAnalysisRunII/data/90x/histoFakeEtaPt_2018.root";
    puPath = "MitAnalysisRunII/data/90x/puWeights_90x_2018.root";

    if     (1){
      infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	          infileCat_.push_back(kPlotData);

      infileName_.push_back(Form("%sWpWp_EWK.root" ,filesPath.Data())); 	  infileCat_.push_back(kPlotSSWWEWK);

      infileName_.push_back(Form("%sWpWp_QCD.root" ,filesPath.Data())); 	  infileCat_.push_back(kPlotSSWWQCD);

      infileName_.push_back(Form("%sWZ3l_MG_QCD.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWZ);
      infileName_.push_back(Form("%sWZ3l_MG_EWK.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotEWKWZ);

      infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);
      infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);

      infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotVVV);
      infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotVVV);
      infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotVVV);

      infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sggWW.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sDYNJetsToLL.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotWS);

      infileName_.push_back(Form("%sVG_M120.root" ,filesPath.Data()));            infileCat_.push_back(kPlotVG);

      infileName_.push_back(Form("%sWWdps.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotDPSWW);
    }
  }
  else if(year == 2017) {
    lumi = 41.5;
    filesPath = "/data/t3home000/ceballos/panda/v_004_0/";
    fLepton_FakesName = "MitAnalysisRunII/data/90x/histoFakeEtaPt_2017.root";
    puPath = "MitAnalysisRunII/data/90x/puWeights_90x_2017.root";

    if     (WZName == "WZ3l_MG"){
      infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	          infileCat_.push_back(kPlotData);

      infileName_.push_back(Form("%sWpWp_EWK.root" ,filesPath.Data())); 	  infileCat_.push_back(kPlotSSWWEWK);

      infileName_.push_back(Form("%sWpWp_QCD.root" ,filesPath.Data())); 	  infileCat_.push_back(kPlotSSWWQCD);

      infileName_.push_back(Form("%sWZ3l_MG_QCD.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWZ);
      infileName_.push_back(Form("%sWZ3l_MG_EWK.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotEWKWZ);

      infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);
      infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotZZ);

      infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotVVV);
      infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotVVV);
      infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	          infileCat_.push_back(kPlotVVV);

      infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sggWW.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sDYNJetsToLL.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotWS);

      infileName_.push_back(Form("%sVG_M120.root" ,filesPath.Data()));            infileCat_.push_back(kPlotVG);

      infileName_.push_back(Form("%sWWdps.root" ,filesPath.Data())); 	          infileCat_.push_back(kPlotDPSWW);
    }
    else if(WZName == "WZ3l_powheg"){
      infileName_.push_back(Form("%sWZ3l_powheg.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWZ);
    }
    else if(WZName == "WZ3l_amcnlo"){
      infileName_.push_back(Form("%sWZ3l_amcnlo.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWZ);
    }
    else if(WZName == "WZ3l_powheg_mll1"){
      infileName_.push_back(Form("%sWZ3l_powheg_mll1.root" ,filesPath.Data()));   infileCat_.push_back(kPlotWZ);
    }
    else if(WZName == "WZ3l_MG_only"){
      infileName_.push_back(Form("%sWZ3l_MG_QCD.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWZ);
      infileName_.push_back(Form("%sWZ3l_MG_EWK.root" ,filesPath.Data()));        infileCat_.push_back(kPlotEWKWZ);
    }
    else {
      printf("Wrong WZName (%s), exit\n",WZName.Data());
      return;
    }
  }
  else if(year == 2016) {
    lumi = 35.9;
    filesPath = "/data/t3home000/ceballos/panda/v_002_0/";
    fLepton_FakesName = "MitAnalysisRunII/data/90x/histoFakeEtaPt_2016.root";
    puPath = "MitAnalysisRunII/data/80x/puWeights_80x_37ifb.root";

    if     (WZName == "WZ3l_MG"){
      infileName_.push_back(Form("%sdata.root",filesPath.Data()));		  infileCat_.push_back(kPlotData);

      infileName_.push_back(Form("%sWpWp_EWK.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotSSWWEWK);

      infileName_.push_back(Form("%sWpWp_QCD.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotSSWWQCD);

      infileName_.push_back(Form("%sWZ3l_MG_QCD.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotWZ);
      infileName_.push_back(Form("%sWZ3l_MG_EWK.root" ,filesPath.Data()));	  infileCat_.push_back(kPlotEWKWZ);

      infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotZZ);
      infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotZZ);

      infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotVVV);
      infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotVVV);

      infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sggWW.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sTW.root" ,filesPath.Data())); 		  infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sDYNJetsToLL.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWS);
      infileName_.push_back(Form("%sH125.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotWS);

      infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));                 infileCat_.push_back(kPlotVG);

      infileName_.push_back(Form("%sWWdps.root" ,filesPath.Data()));		  infileCat_.push_back(kPlotDPSWW);
    }
    else if(WZName == "WZ3l_powheg"){
      infileName_.push_back(Form("%sWZ.root" ,filesPath.Data()));                 infileCat_.push_back(kPlotWZ);
      infileName_.push_back(Form("%sWGstar.root" ,filesPath.Data()));             infileCat_.push_back(kPlotWZ);
    }
    else if(WZName == "WZ3l_MG_only"){
      infileName_.push_back(Form("%sWZ3l_MG_QCD.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWZ);
      infileName_.push_back(Form("%sWZ3l_MG_EWK.root" ,filesPath.Data()));        infileCat_.push_back(kPlotWZ);
    }
  }
  else {
    return;
  }

  TFile *fLepton_Fakes = TFile::Open(fLepton_FakesName.Data());
  TH2D* histoFakeEffSelMediumEtaPt_m = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_0_0"); histoFakeEffSelMediumEtaPt_m->SetDirectory(0);
  TH2D* histoFakeEffSelMediumEtaPt_e = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_0_1"); histoFakeEffSelMediumEtaPt_e->SetDirectory(0);

  //TH2D* histoFakeEffSelTightEtaPt_m = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_4_0"); histoFakeEffSelTightEtaPt_m ->SetDirectory(0);
  TH2D* histoFakeEffSelTightEtaPt_m = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_0_0");;
  if	 (year == 2016) {histoFakeEffSelTightEtaPt_m = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_2_0");  printf("2016 tight mu sel\n");}
  else if(year == 2017) {histoFakeEffSelTightEtaPt_m = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_13_0"); printf("2017 tight mu sel\n");}
  else if(year == 2018) {histoFakeEffSelTightEtaPt_m = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_13_0"); printf("2018 tight mu sel\n");}
  histoFakeEffSelTightEtaPt_m ->SetDirectory(0);	

  //TH2D* histoFakeEffSelTightEtaPt_e = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_4_1"); histoFakeEffSelTightEtaPt_e ->SetDirectory(0);
  TH2D* histoFakeEffSelTightEtaPt_e  = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_0_1"); 
  if	 (year == 2016) {histoFakeEffSelTightEtaPt_e = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_7_1"); printf("2016 tight el sel\n");}
  else if(year == 2017) {histoFakeEffSelTightEtaPt_e = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_4_1"); printf("2017 tight el sel\n");}
  else if(year == 2018) {histoFakeEffSelTightEtaPt_e = (TH2D*)fLepton_Fakes->Get("histoFakeEffSelEtaPt_4_1"); printf("2018 tight el sel\n");}
  histoFakeEffSelTightEtaPt_e ->SetDirectory(0);

  fLepton_Fakes->Close();

  TFile *fPUFile = TFile::Open(Form("%s",puPath.Data()));
  TH1D *fhDPU     = (TH1D*)(fPUFile->Get("puWeights"));     assert(fhDPU);     fhDPU    ->SetDirectory(0);
  TH1D *fhDPUUp   = (TH1D*)(fPUFile->Get("puWeightsUp"));   assert(fhDPUUp);   fhDPUUp  ->SetDirectory(0);
  TH1D *fhDPUDown = (TH1D*)(fPUFile->Get("puWeightsDown")); assert(fhDPUDown); fhDPUDown->SetDirectory(0);
  delete fPUFile;

  const int nBinMJJ = 4; Float_t xbinsMJJ[nBinMJJ+1] = {500, 800, 1100, 1500, 2000};
  const int nBinMLL = 4; Float_t xbinsMLL[nBinMLL+1] = {0, 100, 180, 300, 500};
  /*const int nBinMVA = 24; Float_t xbins[nBinMVA+1] = {500, 800, 1100, 1500, 2000,
                                                          2800, 3100, 3500, 4000,
						          4800, 5100, 5500, 6000,
						          6800, 7100, 7500, 8000,
						          8800, 9100, 9500,10000,
						         10800,11100,11500,12000};*/
  const int nBinMVA = 44; Float_t xbins[nBinMVA+1] = {500, 800, 1100, 1500, 2000,
                                                          2800, 3100, 3500, 4000,
						          4800, 5100, 5500, 6000,
						          6800, 7100, 7500, 8000,
						          8800, 9100, 9500,10000,
						         10800,11100,11500,12000,
						         12800,13100,13500,14000,
						         14800,15100,15500,16000,
						         16800,17100,17500,18000,
						         18800,19100,19500,20000,
						         20800,21100,21500,22000};
  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 92;
  TH1D* histo[allPlots][nPlotCategories];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    if     (thePlot >=   0 && thePlot <=   5) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >=   6 && thePlot <=   8) {nBinPlot =   5; xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >=   9 && thePlot <=  11) {nBinPlot =  80; xminPlot =  0.0; xmaxPlot = 8.0;}
    else if(thePlot >=  12 && thePlot <=  14) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot =2000;}
    else if(thePlot >=  15 && thePlot <=  17) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 1.0;}
    else if(thePlot >=  15 && thePlot <=  23) {nBinPlot =   5; xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >=  24 && thePlot <=  29) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >=  46 && thePlot <=  51) {nBinPlot = 100; xminPlot = -5.0; xmaxPlot = 5.0;}
    else if(thePlot >=  52 && thePlot <=  54) {nBinPlot =  80; xminPlot =  0.0; xmaxPlot = 8.0;}
    else if(thePlot >=  55 && thePlot <=  57) {nBinPlot = 200; xminPlot =500.0; xmaxPlot =2500;}
    else if(thePlot >=  58 && thePlot <=  60) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 1.0;}
    else if(thePlot >=  61 && thePlot <=  69) {nBinPlot =   5; xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >=  70 && thePlot <=  72) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >=  73 && thePlot <=  75) {nBinPlot = 100; xminPlot = -5.0; xmaxPlot = 5.0;}
    else if(thePlot >=  76 && thePlot <=  78) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >=  79 && thePlot <=  81) {nBinPlot =  50; xminPlot =  0.0; xmaxPlot = 2.5;}
    else if(thePlot >=  82 && thePlot <=  87) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 1.0;}
    else if(thePlot >=  88 && thePlot <=  90) {nBinPlot = 200; xminPlot = 20.0; xmaxPlot = 220;}
    TH1D* histos;
    if     (thePlot == allPlots-1)            histos = new TH1D("histos", "histos", nBinMVA, xbins);
    else if(thePlot >=  30 && thePlot <=  39) histos = new TH1D("histos", "histos", nBinMJJ, xbinsMJJ);
    else if(thePlot >=  40 && thePlot <=  45) histos = new TH1D("histos", "histos", nBinMLL, xbinsMLL);
    else                                      histos = new TH1D("histos", "histos", nBinPlot, xminPlot, xmaxPlot);
    histos->Sumw2();
    for(int i=0; i<nPlotCategories; i++) histo[thePlot][i] = (TH1D*) histos->Clone(Form("histo%d",i));
    histos->Reset();histos->Clear();
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
  TH1D *histo_PUBoundingUp[nPlotCategories];
  TH1D *histo_PUBoundingDown[nPlotCategories];
  TH1D *histo_BTAGBBoundingUp[nPlotCategories];
  TH1D *histo_BTAGBBoundingDown[nPlotCategories];
  TH1D *histo_BTAGLBoundingUp[nPlotCategories];
  TH1D *histo_BTAGLBoundingDown[nPlotCategories];
  TH1D *histo_WSBoundingUp[nPlotCategories];
  TH1D *histo_WSBoundingDown[nPlotCategories];
  TH1D *histo_EWKCorrWZUp[nPlotCategories];
  TH1D *histo_EWKCorrWZDown[nPlotCategories];
  TH1D *histo_EWKqqZZCorrUp[nPlotCategories];
  TH1D *histo_EWKqqZZCorrDown[nPlotCategories];
  TH1D *histo_ggZZCorrUp[nPlotCategories];
  TH1D *histo_ggZZCorrDown[nPlotCategories];
  TH1D *histo_JESBoundingUp[nPlotCategories];
  TH1D *histo_JESBoundingDown[nPlotCategories];
  TH1D *histo_PreFireBoundingUp[nPlotCategories];
  TH1D *histo_PreFireBoundingDown[nPlotCategories];
  
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
    histo_PUBoundingUp		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_puUp"           , plotBaseNames[ic].Data()));
    histo_PUBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_puDown"         , plotBaseNames[ic].Data()));
    histo_BTAGBBoundingUp	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_btagb_%dUp"     , plotBaseNames[ic].Data(),year));
    histo_BTAGBBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_btagb_%dDown"   , plotBaseNames[ic].Data(),year));
    histo_BTAGLBoundingUp	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_btagl_%dUp"     , plotBaseNames[ic].Data(),year));
    histo_BTAGLBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_btagl_%dDown"   , plotBaseNames[ic].Data(),year));
    histo_WSBoundingUp          [ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_wseffUp"        , plotBaseNames[ic].Data()));
    histo_WSBoundingDown        [ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_wseffDown"      , plotBaseNames[ic].Data()));
    histo_EWKCorrWZUp		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKWZCorrUp"        , plotBaseNames[ic].Data()));
    histo_EWKCorrWZDown 	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKWZCorrDown"      , plotBaseNames[ic].Data()));
    histo_EWKqqZZCorrUp 	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKqqZZCorrUp"      , plotBaseNames[ic].Data()));
    histo_EWKqqZZCorrDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_EWKqqZZCorrDown"    , plotBaseNames[ic].Data()));
    histo_ggZZCorrUp		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_ggZZCorrUp"         , plotBaseNames[ic].Data()));
    histo_ggZZCorrDown		[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_ggZZCorrDown"       , plotBaseNames[ic].Data()));
    histo_JESBoundingUp 	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_jes_%dUp"       , plotBaseNames[ic].Data(),year));
    histo_JESBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_jes_%dDown"     , plotBaseNames[ic].Data(),year));
    histo_PreFireBoundingUp 	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_prefire_%dUp"   , plotBaseNames[ic].Data(),year));
    histo_PreFireBoundingDown	[ic] = (TH1D*)histo_MVA->Clone(Form("histo_%s_CMS_prefire_%dDown" , plotBaseNames[ic].Data(),year));
  }

  //*******************************************************
  // Chain Loop
  //*******************************************************
  for(UInt_t ifile=0; ifile<infileName_.size(); ifile++) {
    printf("sampleNames(%d): %s\n",ifile,infileName_[ifile].Data());
    TFile *the_input_file = TFile::Open(infileName_[ifile].Data());
    TTree *the_input_tree = (TTree*)the_input_file->FindObjectAny("events");

    if(debug != 0 && infileCat_[ifile] != 0) return;
    
    pandaFlat thePandaFlat(the_input_tree);
    double theMCPrescale = 1.0; if(infileCat_[ifile] != kPlotData) theMCPrescale = mcPrescale;
    Long64_t nentries = thePandaFlat.fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = thePandaFlat.LoadTree(jentry);
      if (ientry < 0) break;
      nb = thePandaFlat.fChain->GetEntry(jentry);   nbytes += nb;
      if (jentry%1000000 == 0) printf("--- reading event %8lld (%8lld) of %8lld\n",jentry,ientry,nentries);
      if (infileCat_[ifile] != kPlotData && jentry%(int)theMCPrescale != 0) continue;

      if(debug == 2) printf("STEP1 %llu\n",thePandaFlat.eventNumber);

      bool passTrigger = (thePandaFlat.trigger & (1<<kEMuTrig)) != 0       || (thePandaFlat.trigger & (1<<kDoubleMuTrig)) != 0  ||
                         (thePandaFlat.trigger & (1<<kSingleMuTrig)) != 0  || (thePandaFlat.trigger & (1<<kDoubleEleTrig)) != 0 ||
                         (thePandaFlat.trigger & (1<<kSingleEleTrig)) != 0;
      if(passTrigger == false) continue;
      if(thePandaFlat.metFilter == 0) continue;
      if(debug == 2) printf("STEP2 %llu\n",thePandaFlat.eventNumber);

      if(thePandaFlat.nLooseLep < 2 || thePandaFlat.nLooseLep > 3) continue;
      if(debug == 2) printf("STEP3 %llu\n",thePandaFlat.eventNumber);

      vector<float>  looseLepPt,looseLepEta,looseLepPhi,looseLepSF;
      vector<int> looseLepSelBit,looseLepPdgId,looseLepTripleCharge,looseLepMissingHits;
      int ptSelCuts[3] = {0,0,0};
      for(int i=0; i<thePandaFlat.nLooseMuon; i++){
        looseLepPt.push_back(thePandaFlat.muonPt[i]);
        looseLepEta.push_back(thePandaFlat.muonEta[i]);
        looseLepPhi.push_back(thePandaFlat.muonPhi[i]);
        looseLepSF.push_back(thePandaFlat.muonSfReco[i] * thePandaFlat.muonSfTight[i]);
        looseLepSelBit.push_back(thePandaFlat.muonSelBit[i]);
        looseLepPdgId.push_back(thePandaFlat.muonPdgId[i]);
        looseLepTripleCharge.push_back(1);
        looseLepMissingHits.push_back(0);
	if(thePandaFlat.muonPt[i] > 25) ptSelCuts[0]++;
	if(thePandaFlat.muonPt[i] > 20) ptSelCuts[1]++;
	if(thePandaFlat.muonPt[i] > 10) ptSelCuts[2]++;
      }
      for(int i=0; i<thePandaFlat.nLooseElectron; i++){
        looseLepPt.push_back(thePandaFlat.electronPt[i]);
        looseLepEta.push_back(thePandaFlat.electronEta[i]);
        looseLepPhi.push_back(thePandaFlat.electronPhi[i]);
        looseLepSelBit.push_back(thePandaFlat.electronSelBit[i]);
        looseLepSF.push_back(thePandaFlat.electronSfReco[i] * thePandaFlat.electronSfTight[i]);
        looseLepPdgId.push_back(thePandaFlat.electronPdgId[i]);
        looseLepTripleCharge.push_back(thePandaFlat.electronTripleCharge[i]);
        looseLepMissingHits.push_back(thePandaFlat.electronNMissingHits[i]);
	if(thePandaFlat.electronPt[i] > 25) ptSelCuts[0]++;
	if(thePandaFlat.electronPt[i] > 20) ptSelCuts[1]++;
	if(thePandaFlat.electronPt[i] > 10) ptSelCuts[2]++;
      }

      if((int)looseLepPt.size() != thePandaFlat.nLooseLep) printf("IMPOSSIBLE\n");

      if(!(ptSelCuts[0] >= 1 && ptSelCuts[1] >= 2 && ptSelCuts[2] >= thePandaFlat.nLooseLep)) continue;

      int theCategory = infileCat_[ifile];
      bool isNotMCFake = thePandaFlat.looseGenLep1PdgId != 0 && thePandaFlat.looseGenLep2PdgId != 0;
      if(thePandaFlat.nLooseLep >= 3) isNotMCFake = isNotMCFake && thePandaFlat.looseGenLep3PdgId != 0;
      if(thePandaFlat.nLooseLep >= 4) isNotMCFake = isNotMCFake && thePandaFlat.looseGenLep4PdgId != 0;
      if(theCategory != kPlotData && theCategory != kPlotVG && isNotMCFake == false && usePureMC == false) continue;

      vector<TLorentzVector> vLoose;
      vector<int> idLep;
      bool passLooseLepId = true;
      int qTot = 0;
      unsigned int countLeptonTight = 0;
      for(int i=0; i<thePandaFlat.nLooseLep; i++) {
        idLep.push_back(0);
        //if((looseLepSelBit[i] & kTight) == kTight && (looseLepSelBit[i] & kDxyz) == kDxyz && looseLepTripleCharge[i] == 1 && looseLepMissingHits[i] == 0) idLep[i] = 1;
        if(abs(looseLepPdgId[i])==13) {
	  if	 (year == 2016 && (looseLepSelBit[i] & kTight) == kTight && (looseLepSelBit[i] & kDxyz) == kDxyz) idLep[i] = 1;
	  else if(year == 2017 && (looseLepSelBit[i] & kMvaTight) == kMvaTight && (looseLepSelBit[i] & kMiniIsoTight) == kMiniIsoTight) idLep[i] = 1;
	  else if(year == 2018 && (looseLepSelBit[i] & kMvaTight) == kMvaTight && (looseLepSelBit[i] & kMiniIsoTight) == kMiniIsoTight) idLep[i] = 1;
	}
	else {
          if     (year == 2016 && (looseLepSelBit[i] & kEleMvaWP80) == kEleMvaWP80 && looseLepTripleCharge[i] == 1) idLep[i] = 1;
	  else if(year == 2017 && (looseLepSelBit[i] & kTight) == kTight && (looseLepSelBit[i] & kDxyz) == kDxyz && looseLepMissingHits[i] == 0 && looseLepTripleCharge[i] == 1) idLep[i] = 1;
	  else if(year == 2018 && (looseLepSelBit[i] & kTight) == kTight && (looseLepSelBit[i] & kDxyz) == kDxyz && looseLepMissingHits[i] == 0 && looseLepTripleCharge[i] == 1) idLep[i] = 1;
	}
	countLeptonTight = countLeptonTight + (idLep[i] > 0);
        double thePDGMass = mass_mu;
        if(abs(looseLepPdgId[i])==11) thePDGMass = mass_el;
	TLorentzVector vLepTemp; vLepTemp.SetPtEtaPhiM(looseLepPt[i],looseLepEta[i],looseLepPhi[i],thePDGMass);
        vLoose.push_back(vLepTemp);

	qTot = qTot + abs(looseLepPdgId[i])/looseLepPdgId[i];

        passLooseLepId = passLooseLepId && ((looseLepSelBit[i] & kFake) == kFake);
      }
      if(debug == 2) printf("STEP4 %llu %d %d %d %zu\n",thePandaFlat.eventNumber,passLooseLepId,qTot,countLeptonTight,idLep.size());
      if(passLooseLepId == false) continue;
      if(usePureMC == true && countLeptonTight != idLep.size()) continue;
      if(debug == 2) printf("STEP5 %llu\n",thePandaFlat.eventNumber);

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
      if     (year == 2016 | year == 2018) {
        vMet    .SetPtEtaPhiM(thePandaFlat.pfmet,0.0,thePandaFlat.pfmetphi,0.0);
        vMetUp  .SetPtEtaPhiM(thePandaFlat.pfmet_JESTotalUp  ,0.0,thePandaFlat.pfmetphi_JESTotalUp  ,0.0);
        vMetDown.SetPtEtaPhiM(thePandaFlat.pfmet_JESTotalDown,0.0,thePandaFlat.pfmetphi_JESTotalDown,0.0);
      } 
      else if(year == 2017){
        vMet    .SetPtEtaPhiM(thePandaFlat.puppimet,0.0,thePandaFlat.puppimetphi,0.0);
        vMetUp  .SetPtEtaPhiM(thePandaFlat.puppimet_JESTotalUp  ,0.0,thePandaFlat.puppimetphi_JESTotalUp  ,0.0);
        vMetDown.SetPtEtaPhiM(thePandaFlat.puppimet_JESTotalDown,0.0,thePandaFlat.puppimetphi_JESTotalDown,0.0);
      }

      double mllZ = 10000; double mllmin = 10000;
      TLorentzVector vZ1l1,vZ1l2,vWln;
      int whichWln = -1;
      if     (vLoose.size() == 2){
        vZ1l1  = vLoose[0];
        vZ1l2  = vLoose[1];
	mllZ   = (vLoose[0]+vLoose[1]).M();
	mllmin = (vLoose[0]+vLoose[1]).M();
	whichWln = 9; // random number greater or equal than 0
      }
      else if(vLoose.size() == 3){
        if((vLoose[0]+vLoose[1]).M() < mllmin) mllmin = (vLoose[0]+vLoose[1]).M();
        if((vLoose[0]+vLoose[2]).M() < mllmin) mllmin = (vLoose[0]+vLoose[2]).M();
        if((vLoose[1]+vLoose[2]).M() < mllmin) mllmin = (vLoose[1]+vLoose[2]).M();
	if(abs(looseLepPdgId[0]) == abs(looseLepPdgId[1]) && looseLepPdgId[0] != looseLepPdgId[1]) {
          if(fabs((vLoose[0]+vLoose[1]).M()-91.1876) < fabs(mllZ-91.1876)) {
	    mllZ  = (vLoose[0]+vLoose[1]).M();
	    vZ1l1 = vLoose[0];
	    vZ1l2 = vLoose[1];
	    vWln  = vLoose[2];
	    whichWln = 2;
	  }
	}
	if(abs(looseLepPdgId[0]) == abs(looseLepPdgId[2]) && looseLepPdgId[0] != looseLepPdgId[2]) {
          if(fabs((vLoose[0]+vLoose[2]).M()-91.1876) < fabs(mllZ-91.1876)) {
            mllZ  = (vLoose[0]+vLoose[2]).M();
	    vZ1l1 = vLoose[0];
	    vZ1l2 = vLoose[2];
	    vWln  = vLoose[1];
	    whichWln = 1;
	  }
	}
	if(abs(looseLepPdgId[1]) == abs(looseLepPdgId[2]) && looseLepPdgId[1] != looseLepPdgId[2]) {
          if(fabs((vLoose[1]+vLoose[2]).M()-91.1876) < fabs(mllZ-91.1876)) {
            mllZ  = (vLoose[1]+vLoose[2]).M();
	    vZ1l1 = vLoose[1];
	    vZ1l2 = vLoose[2];
	    vWln  = vLoose[0];
	    whichWln = 0;
	  }
	}
      }

      if(whichWln == -1) continue;

      TLorentzVector vJot1;     vJot1.SetPtEtaPhiM    (thePandaFlat.jotPt[0]             ,thePandaFlat.jotEta[0],thePandaFlat.jotPhi[0],0.0);
      TLorentzVector vJot2;     vJot2.SetPtEtaPhiM    (thePandaFlat.jotPt[1]             ,thePandaFlat.jotEta[1],thePandaFlat.jotPhi[1],0.0);
      TLorentzVector vJot1Up;   vJot1Up.SetPtEtaPhiM  (thePandaFlat.jotPt_JESTotalUp[0]  ,thePandaFlat.jotEta[0],thePandaFlat.jotPhi[0],0.0);
      TLorentzVector vJot2Up;   vJot2Up.SetPtEtaPhiM  (thePandaFlat.jotPt_JESTotalUp[1]  ,thePandaFlat.jotEta[1],thePandaFlat.jotPhi[1],0.0);
      TLorentzVector vJot1Down; vJot1Down.SetPtEtaPhiM(thePandaFlat.jotPt_JESTotalDown[0],thePandaFlat.jotEta[0],thePandaFlat.jotPhi[0],0.0);
      TLorentzVector vJot2Down; vJot2Down.SetPtEtaPhiM(thePandaFlat.jotPt_JESTotalDown[1],thePandaFlat.jotEta[1],thePandaFlat.jotPhi[1],0.0);

      double massJJ         = thePandaFlat.jot12Mass;               //(vJot1+vJot2).M();
      double massJJUp       = thePandaFlat.jot12Mass_JESTotalUp;   //(vJot1Up+vJot2Up).M();
      double massJJDown     = thePandaFlat.jot12Mass_JESTotalDown; //(vJot1Down+vJot2Down).M();
      double deltaEtaJJ     = thePandaFlat.jot12DEta;              //TMath::Abs(vJot1.Eta()    -vJot2.Eta());
      double deltaEtaJJUp   = thePandaFlat.jot12DEta_JESTotalUp;   //TMath::Abs(vJot1Up.Eta()  -vJot2Up.Eta());
      double deltaEtaJJDown = thePandaFlat.jot12DEta_JESTotalDown; //TMath::Abs(vJot1Down.Eta()-vJot2Down.Eta());
      //double deltaPhiJJ     = thePandaFlat.jot12DPhi;              //TMath::Abs(vJot1.Phi()    -vJot2.Phi());
      //double deltaPhiJJUp   = thePandaFlat.jot12DPhi_JESTotalUp;   //TMath::Abs(vJot1Up.Phi()  -vJot2Up.Phi());
      //double deltaPhiJJDown = thePandaFlat.jot12DPhi_JESTotalDown; //TMath::Abs(vJot1Down.Phi()-vJot2Down.Phi());

      bool passMJJ     = thePandaFlat.nJot              >= 2 && massJJ     > 500;
      bool passMJJUp   = thePandaFlat.nJot_JESTotalUp   >= 2 && massJJUp   > 500;
      bool passMJJDown = thePandaFlat.nJot_JESTotalDown >= 2 && massJJDown > 500;
      bool passDEtaJJ     = thePandaFlat.nJot              >= 2 && deltaEtaJJ     > 2.5;
      bool passDEtaJJUp   = thePandaFlat.nJot_JESTotalUp   >= 2 && deltaEtaJJUp   > 2.5;
      bool passDEtaJJDown = thePandaFlat.nJot_JESTotalDown >= 2 && deltaEtaJJDown > 2.5;

      double maxLeptonZ = 0; double maxLeptonZUp = 0; double maxLeptonZDown = 0;
      for(unsigned int i=0; i<vLoose.size(); i++) {
        if(TMath::Abs(vLoose[i].Eta()-(vJot1.Eta()+vJot2.Eta())/2.)/deltaEtaJJ > maxLeptonZ)
          maxLeptonZ     = TMath::Abs(vLoose[i].Eta()-(vJot1.Eta()+vJot2.Eta())/2.)/deltaEtaJJ;
        if(TMath::Abs(vLoose[i].Eta()-(vJot1Up.Eta()+vJot2Up.Eta())/2.)/deltaEtaJJUp > maxLeptonZUp)
	  maxLeptonZUp   = TMath::Abs(vLoose[i].Eta()-(vJot1Up.Eta()+vJot2Up.Eta())/2.)/deltaEtaJJUp;
        if(TMath::Abs(vLoose[i].Eta()-(vJot1Down.Eta()+vJot2Down.Eta())/2.)/deltaEtaJJDown > maxLeptonZDown)
	  maxLeptonZDown = TMath::Abs(vLoose[i].Eta()-(vJot1Down.Eta()+vJot2Down.Eta())/2.)/deltaEtaJJDown;
      }
      bool passZMax     = thePandaFlat.nJot              >= 2 && maxLeptonZ     < 0.75;
      bool passZMaxUp   = thePandaFlat.nJot_JESTotalUp   >= 2 && maxLeptonZUp   < 0.75;
      bool passZMaxDown = thePandaFlat.nJot_JESTotalDown >= 2 && maxLeptonZDown < 0.75;

      bool passMLL   = mllZ > 20 && (fabs(mllZ-91.1876) > 15 || lepType != 1);
      bool passMET = vMet.Pt() > 40; bool passMETUp = vMetUp.Pt() > 40;bool passMETDown = vMetDown.Pt() > 40;
      bool passNjets = thePandaFlat.nJot >= 2; bool passNjetsUp = thePandaFlat.nJot_JESTotalUp >= 2; bool passNjetsDown = thePandaFlat.nJot_JESTotalDown >= 2;
      bool passBtagVeto = thePandaFlat.jetNMBtags == 0; bool passBtagVetoUp = thePandaFlat.jetNMBtags_JESTotalUp == 0; bool passBtagVetoDown = thePandaFlat.jetNMBtags_JESTotalDown == 0;
      bool passTauVeto = thePandaFlat.nTau == 0;
      //                                                            0        1            2              3               4            5             6                 7            8     
      bool passSel[9]     = {qTot != 0 && thePandaFlat.nLooseLep == 2, passMLL, passMET    , passNjets    , passDEtaJJ    , passMJJ    , passZMax    , passBtagVeto    , passTauVeto};
      bool passSelUp[9]   = {qTot != 0 && thePandaFlat.nLooseLep == 2, passMLL, passMETUp  , passNjetsUp  , passDEtaJJUp  , passMJJUp  , passZMaxUp  , passBtagVetoUp  , passTauVeto};
      bool passSelDown[9] = {qTot != 0 && thePandaFlat.nLooseLep == 2, passMLL, passMETDown, passNjetsDown, passDEtaJJDown, passMJJDown, passZMaxDown, passBtagVetoDown, passTauVeto};

      bool passWZPresel = whichWln >= 0 && thePandaFlat.nLooseLep == 3 && 
                          fabs(mllZ-91.1876) < 15 && mllmin > 4 && vWln.Pt() > 20;
      bool passWWSel     = passSel[0]     && passSel[1]     && passSel[2]     && passSel[3]     && passSel[4]     && passSel[5]     && passSel[6]     && passSel[7]     && passSel[8];
      bool passWWSelUp   = passSelUp[0]   && passSelUp[1]   && passSelUp[2]   && passSelUp[3]   && passSelUp[4]   && passSelUp[5]   && passSelUp[6]   && passSelUp[7]   && passSelUp[8];
      bool passWWSelDown = passSelDown[0] && passSelDown[1] && passSelDown[2] && passSelDown[3] && passSelDown[4] && passSelDown[5] && passSelDown[6] && passSelDown[7] && passSelDown[8];
      bool passBtagSel     = passSel[0]     && passSel[1]     && passSel[2]     && passSel[3]     && passSel[4]     && passSel[5]     && passSel[6]     && !passSel[7]     && passSel[8];
      bool passBtagSelUp   = passSelUp[0]   && passSelUp[1]   && passSelUp[2]   && passSelUp[3]   && passSelUp[4]   && passSelUp[5]   && passSelUp[6]   && !passSelUp[7]   && passSelUp[8];
      bool passBtagSelDown = passSelDown[0] && passSelDown[1] && passSelDown[2] && passSelDown[3] && passSelDown[4] && passSelDown[5] && passSelDown[6] && !passSelDown[7] && passSelDown[8];
      bool passWZSel     = passWZPresel && passSel[2]     && passSel[3]     && passSel[4]     && passSel[5]     && passSel[6]     && passSel[7]     && passSel[8];
      bool passWZSelUp   = passWZPresel && passSelUp[2]   && passSelUp[3]   && passSelUp[4]   && passSelUp[5]   && passSelUp[6]   && passSelUp[7]   && passSelUp[8];
      bool passWZSelDown = passWZPresel && passSelDown[2] && passSelDown[3] && passSelDown[4] && passSelDown[5] && passSelDown[6] && passSelDown[7] && passSelDown[8];

      bool passZSel      = passSel[0]     && mllZ > 20      &&!passSel[2]     && passSel[3]     && passSel[4]     && passSel[5]     && passSel[6]     && passSel[7]     && passSel[8];

      bool passPresel    = passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[5];

      bool passAllButOneSel[8] = {
        passSel[0] &&               passSel[2] && passSel[3] && passSel[4] && passSel[5] && passSel[6] && passSel[7] && passSel[8],
        passSel[0] && passSel[1] &&               passSel[3] && passSel[4] && passSel[5] && passSel[6] && passSel[7] && passSel[8],
	passSel[0] && passSel[1] && passSel[2]&&                                                          passSel[7] && passSel[8],
	passSel[0] && passSel[1] && passSel[2] && passSel[3] &&               passSel[5] && passSel[6] && passSel[7] && passSel[8],
	passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[4] &&               passSel[6] && passSel[7] && passSel[8],
	passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[4] && passSel[5] &&               passSel[7] && passSel[8],
	passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[4] && passSel[5] && passSel[6]               && passSel[8],
	passSel[0] && passSel[1] && passSel[2] && passSel[3] && passSel[4] && passSel[5] && passSel[6] && passSel[7]
      };

      int dataCardSel = -1; int dataCardSelUp = -1;int dataCardSelDown = -1;
      if     (passWWSel)   dataCardSel = 0;
      else if(passBtagSel) dataCardSel = 1;
      else if(passWZSel)   dataCardSel = 2;
      if     (passWWSelUp)   dataCardSelUp = 0;
      else if(passBtagSelUp) dataCardSelUp = 1;
      else if(passWZSelUp)   dataCardSelUp = 2;
      if     (passWWSelDown)   dataCardSelDown = 0;
      else if(passBtagSelDown) dataCardSelDown = 1;
      else if(passWZSelDown)   dataCardSelDown = 2;

      bool passSystCuts[nSystTypes] = {dataCardSelUp >= 0, dataCardSelDown >= 0, dataCardSel >= 0, dataCardSel >= 0};

      double totalWeight = 1.0; double puWeight = 1.0; double puWeightUp = 1.0; double puWeightDown = 1.0; double effWSUnc = 1.0; double sf_l1PrefireE = 1.0;
      if(theCategory != kPlotData){
        double triggerWeights[2] = {1.0, 0.0};
	if(thePandaFlat.nLooseLep == 2) {
          trigger_sf(triggerWeights, trgEff, trgEffE, lepType, looseLepPt[0], TMath::Abs(looseLepEta[0]), looseLepPt[1], TMath::Abs(looseLepEta[1]));
        }

	puWeight     = nPUScaleFactor(fhDPU,    thePandaFlat.pu);
        puWeightUp   = nPUScaleFactor(fhDPUUp,  thePandaFlat.pu);
        puWeightDown = nPUScaleFactor(fhDPUDown,thePandaFlat.pu);

        sf_l1PrefireE = 1.0 + TMath::Abs(1.0 - thePandaFlat.sf_l1Prefire) * 0.2;

        totalWeight = thePandaFlat.normalizedWeight * lumi * puWeight * thePandaFlat.sf_l1Prefire * looseLepSF[0] * looseLepSF[1] * triggerWeights[0] * theMCPrescale;

        if(passBtagVeto) totalWeight = totalWeight * thePandaFlat.sf_btag0;
        else             totalWeight = totalWeight * thePandaFlat.sf_btagGT0;

        if     (infileCat_[ifile] == kPlotWZ)                                                totalWeight = totalWeight * thePandaFlat.sf_wz;
	else if(infileCat_[ifile] == kPlotZZ && infileName_[ifile].Contains("qqZZ") == true) totalWeight = totalWeight * thePandaFlat.sf_zz;

        if(infileCat_[ifile] == kPlotSSWWEWK) totalWeight = totalWeight * ewkCorrWpWp(thePandaFlat.genMjj);

        bool isRS = thePandaFlat.looseGenLep1PdgId > 0 && thePandaFlat.looseGenLep2PdgId > 0;
        if(thePandaFlat.nLooseLep >= 3) isRS = isRS && thePandaFlat.looseGenLep3PdgId > 0;
        if(thePandaFlat.nLooseLep >= 4) isRS = isRS && thePandaFlat.looseGenLep4PdgId > 0;
	if(!isRS && theCategory != kPlotVG) {
	  theCategory = kPlotWS;
	  int theWSLepton = -1;
	  if     (thePandaFlat.nLooseLep >= 2 && abs(looseLepPdgId[0]) == 11 && thePandaFlat.looseGenLep1PdgId < 0) theWSLepton = 0;
	  else if(thePandaFlat.nLooseLep >= 2 && abs(looseLepPdgId[1]) == 11 && thePandaFlat.looseGenLep2PdgId < 0) theWSLepton = 1;
	  else if(thePandaFlat.nLooseLep >= 3 && abs(looseLepPdgId[2]) == 11 && thePandaFlat.looseGenLep3PdgId < 0) theWSLepton = 2;
	  else if(thePandaFlat.nLooseLep >= 4 && abs(looseLepPdgId[3]) == 11 && thePandaFlat.looseGenLep4PdgId < 0) theWSLepton = 3;
          if(theWSLepton >= 0){
	    int nEta;
            if     (TMath::Abs(looseLepEta[theWSLepton]) < 0.5) nEta = 0;
            else if(TMath::Abs(looseLepEta[theWSLepton]) < 1.0) nEta = 1;
            else if(TMath::Abs(looseLepEta[theWSLepton]) < 1.5) nEta = 2;
            else if(TMath::Abs(looseLepEta[theWSLepton]) < 2.0) nEta = 3;
            else                                                nEta = 4;
	    totalWeight = totalWeight * WSSF[nEta];
	    effWSUnc = WSSFE[nEta];
	  }
	}
      }

      if(usePureMC == false && countLeptonTight != idLep.size()){
        double fakeSF = 1.0;
        for(unsigned int nl=0; nl<idLep.size(); nl++){
          if(idLep[nl] == 1) continue;
          bool applyTight = true;
          fakeSF = fakeSF * fakeRateFactor(TMath::Min((double)looseLepPt[nl],44.999),TMath::Abs(looseLepEta[nl]),TMath::Abs(looseLepPdgId[nl]),applyTight,histoFakeEffSelMediumEtaPt_m,histoFakeEffSelMediumEtaPt_e,histoFakeEffSelTightEtaPt_m,histoFakeEffSelTightEtaPt_e);
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

      if(theCategory != kPlotData){
        if     (year == 2017 && thePandaFlat.jetNMBtags > 0) totalWeight = totalWeight * 0.60;
        else if(year == 2017 && thePandaFlat.jetNBtags  > 0) totalWeight = totalWeight * 0.85;
      }

      if(theCategory == kPlotSSWWEWK && fidAna == 1 && 
         thePandaFlat.genLep1Pt > 20 and TMath::Abs(thePandaFlat.genLep1Eta) < 2.5 &&
	 thePandaFlat.genLep2Pt > 20 and TMath::Abs(thePandaFlat.genLep2Eta) < 2.5){
        if     (thePandaFlat.genMjj >  500 && thePandaFlat.genMjj <=  800) theCategory = kPlotSignal0;
	else if(thePandaFlat.genMjj >  800 && thePandaFlat.genMjj <= 1100) theCategory = kPlotSignal1;
	else if(thePandaFlat.genMjj > 1100 && thePandaFlat.genMjj <= 1500) theCategory = kPlotSignal2;
	else if(thePandaFlat.genMjj > 1500)                                theCategory = kPlotSignal3;
      }

      if(passAllButOneSel[0])histo[lepType+  0][theCategory]->Fill(TMath::Min(mllZ,199.999),totalWeight);
      if(passAllButOneSel[1])histo[lepType+  3][theCategory]->Fill(TMath::Min(vMet.Pt(),199.999),totalWeight);
      if(passAllButOneSel[2])histo[lepType+  6][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJot,5.499),totalWeight);
      if(passAllButOneSel[3])histo[lepType+  9][theCategory]->Fill(TMath::Min(deltaEtaJJ,7.999),totalWeight);
      if(passAllButOneSel[4])histo[lepType+ 12][theCategory]->Fill(TMath::Min(massJJ,1999.999),totalWeight);
      if(passAllButOneSel[5])histo[lepType+ 15][theCategory]->Fill(TMath::Min(maxLeptonZ,0.999),totalWeight);
      if(passAllButOneSel[6])histo[lepType+ 18][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNMBtags,4.499),totalWeight);
      if(passAllButOneSel[7])histo[lepType+ 21][theCategory]->Fill(TMath::Min((double)thePandaFlat.nTau,4.499),totalWeight);
      if(passWWSel)          histo[lepType+ 24][theCategory]->Fill(TMath::Min(vZ1l1.Pt(),199.999),totalWeight);
      if(passWWSel)          histo[lepType+ 27][theCategory]->Fill(TMath::Min(vZ1l2.Pt(),199.999),totalWeight);
      if(passWWSel)          histo[lepType+ 30][theCategory]->Fill(TMath::Min(massJJ,1999.999),totalWeight);
      if(passWZSel)          histo[lepType+ 33][theCategory]->Fill(TMath::Min(massJJ,1999.999),totalWeight);
      if(passBtagSel)        histo[lepType+ 37][theCategory]->Fill(TMath::Min(massJJ,1999.999),totalWeight);
      if(passWWSel)          histo[lepType+ 40][theCategory]->Fill(TMath::Min(mllZ,xbinsMLL[nBinMLL]-0.0001),totalWeight);
      if(passBtagSel)        histo[lepType+ 43][theCategory]->Fill(TMath::Min(mllZ,xbinsMLL[nBinMLL]-0.0001),totalWeight);
      if(passWWSel)          histo[lepType+ 46][theCategory]->Fill(vJot1.Eta(),totalWeight);
      if(passWWSel)          histo[lepType+ 46][theCategory]->Fill(vJot2.Eta(),totalWeight);
      if(passBtagSel)        histo[lepType+ 49][theCategory]->Fill(vJot1.Eta(),totalWeight);
      if(passBtagSel)        histo[lepType+ 49][theCategory]->Fill(vJot2.Eta(),totalWeight);
      if(passPresel)         histo[lepType+ 52][theCategory]->Fill(TMath::Min(deltaEtaJJ,7.999),totalWeight);
      if(passPresel)         histo[lepType+ 55][theCategory]->Fill(TMath::Min(massJJ,2499.999),totalWeight);
      if(passPresel)         histo[lepType+ 58][theCategory]->Fill(TMath::Min(maxLeptonZ,0.999),totalWeight);
      if(passPresel)         histo[lepType+ 61][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNBtags,4.499),totalWeight);
      if(passPresel)         histo[lepType+ 64][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNMBtags,4.499),totalWeight);
      if(passPresel && thePandaFlat.jetNBtags > 0)
                             histo[lepType+ 67][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNMBtags,4.499),totalWeight);
      if(passPresel)         histo[lepType+ 70][theCategory]->Fill(TMath::Min(vJot1.Pt(),199.999),totalWeight);
      if(passPresel)         histo[lepType+ 70][theCategory]->Fill(TMath::Min(vJot2.Pt(),199.999),totalWeight);
      if(passPresel)         histo[lepType+ 73][theCategory]->Fill(vJot1.Eta(),totalWeight);
      if(passPresel)         histo[lepType+ 73][theCategory]->Fill(vJot2.Eta(),totalWeight);
      if(passPresel)         histo[lepType+ 76][theCategory]->Fill(TMath::Min(vZ1l1.Pt(),199.999),totalWeight);
      if(passPresel)         histo[lepType+ 76][theCategory]->Fill(TMath::Min(vZ1l2.Pt(),199.999),totalWeight);
      if(passPresel)         histo[lepType+ 79][theCategory]->Fill(TMath::Abs(vZ1l1.Eta()),totalWeight);
      if(passPresel)         histo[lepType+ 79][theCategory]->Fill(TMath::Abs(vZ1l2.Eta()),totalWeight);
      if(passPresel)         histo[lepType+ 82][theCategory]->Fill(TMath::Max((double)TMath::Max(thePandaFlat.jotCSV[0],thePandaFlat.jotCSV[1]),0.001),totalWeight);
      if(passPresel)         histo[lepType+ 85][theCategory]->Fill(TMath::Max((double)TMath::Min(thePandaFlat.jotCSV[0],thePandaFlat.jotCSV[1]),0.001),totalWeight);
      if(passZSel)           histo[lepType+ 88][theCategory]->Fill(TMath::Min(mllZ,219.999),totalWeight);

      if((theCategory == kPlotData && passWZSel && debug == 1) || debug == 2){
        printf("DATA %d %d %llu | %d %d | %d -> %d %d %d %d %d %d %d %d %d | %.1f %.1f %.1f %.1f %.2f | %.1f %.1f %.1f %d | %.2f %.2f %.2f %.2f %.2f %.2f / %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",
	thePandaFlat.runNumber,thePandaFlat.lumiNumber,thePandaFlat.eventNumber,theCategory,lepType,
	passWZSel,passSel[0],passSel[1],passSel[2],passSel[3],passSel[4],passSel[5],passSel[6],passSel[7],passSel[8],
	mllZ,vMet.Pt(),deltaEtaJJ,massJJ,maxLeptonZ,
	fabs(mllZ-91.1876),mllmin,vWln.Pt(),whichWln,vJot1.Pt(),vJot1.Eta(),vJot1.Phi(),vJot2.Pt(),vJot2.Eta(),vJot2.Phi(),
	vLoose[0].Pt(),vLoose[0].Eta(),vLoose[0].Phi(),vLoose[1].Pt(),vLoose[1].Eta(),vLoose[1].Phi(),vLoose[2].Pt(),vLoose[2].Eta(),vLoose[2].Phi());
      }

      if(1){
        double typeSelAux0 = 0;
        if     (mllZ < 100) typeSelAux0 = 0;
        else if(mllZ < 180) typeSelAux0 = 1;
        else if(mllZ < 300) typeSelAux0 = 2;
        else                typeSelAux0 = 3;
        double typeSelAux1 = 0;
	if(qTot>0) typeSelAux1 = 1;
        double MVAVar     = TMath::Min(massJJ     ,xbinsMJJ[nBinMJJ]-0.0001);
        double MVAVarUp   = TMath::Min(massJJUp   ,xbinsMJJ[nBinMJJ]-0.0001);
        double MVAVarDown = TMath::Min(massJJDown ,xbinsMJJ[nBinMJJ]-0.0001);
        if     (dataCardSel     == 0) MVAVar     = MVAVar     + 2000 * typeSelAux0 + 8000 * typeSelAux1;
        else if(dataCardSel     == 1) MVAVar     = MVAVar     + 16000 + 2000 * typeSelAux1;
        else if(dataCardSel     == 2) MVAVar     = MVAVar     + 20000;
        if     (dataCardSelUp   == 0) MVAVarUp   = MVAVarUp   + 2000 * typeSelAux0 + 8000 * typeSelAux1;
        else if(dataCardSelUp   == 1) MVAVarUp   = MVAVarUp   + 16000 + 2000 * typeSelAux1;
        else if(dataCardSelUp   == 2) MVAVarUp   = MVAVarUp   + 20000;
        if     (dataCardSelDown == 0) MVAVarDown = MVAVarDown + 2000 * typeSelAux0 + 8000 * typeSelAux1;
        else if(dataCardSelDown == 1) MVAVarDown = MVAVarDown + 16000 + 2000 * typeSelAux1;
        else if(dataCardSelDown == 2) MVAVarDown = MVAVarDown + 20000;

        // Avoid QCD scale weights that are anomalous high
        double maxQCDscale = (TMath::Abs(thePandaFlat.scale[0])+TMath::Abs(thePandaFlat.scale[1])+TMath::Abs(thePandaFlat.scale[2])+
	                      TMath::Abs(thePandaFlat.scale[3])+TMath::Abs(thePandaFlat.scale[4])+TMath::Abs(thePandaFlat.scale[5]))/6.0;
        if(maxQCDscale == 0) maxQCDscale = 1;

        double sf_ewkcorrwz_unc = 1.0; double sf_ewkcorrzz_unc = 1.0; double sf_ggcorrzz_unc = 1.0; double sf_corrwzzz_unc = 1.0;
	if(theCategory == kPlotWZ) sf_ewkcorrwz_unc = 1.02;
	if     (theCategory == kPlotZZ && infileName_[ifile].Contains("qqZZ") == true) sf_ewkcorrzz_unc = thePandaFlat.sf_zzUnc;
	else if(theCategory == kPlotZZ) sf_ggcorrzz_unc = 1.10;

        if     (theCategory == kPlotData && dataCardSel >= 0){
          histo_Baseline[theCategory]->Fill(MVAVar,totalWeight);
        }
        else if(theCategory != kPlotData){
	  if(dataCardSel >= 0) {
	    histo_Baseline[theCategory]->Fill(MVAVar,totalWeight);
	    histo_QCDScaleBounding[theCategory][0]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[0])/maxQCDscale);
	    histo_QCDScaleBounding[theCategory][1]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[1])/maxQCDscale);
	    histo_QCDScaleBounding[theCategory][2]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[2])/maxQCDscale);
	    histo_QCDScaleBounding[theCategory][3]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[3])/maxQCDscale);
	    histo_QCDScaleBounding[theCategory][4]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[4])/maxQCDscale);
	    histo_QCDScaleBounding[theCategory][5]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[5])/maxQCDscale);
	    histo_PDFBoundingUp[theCategory]  ->Fill(MVAVar,totalWeight*TMath::Max((double)thePandaFlat.pdfUp,1.01));
	    histo_PDFBoundingDown[theCategory]->Fill(MVAVar,totalWeight*TMath::Min((double)thePandaFlat.pdfDown,0.99));
            histo_LepEffMBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*muSFUnc); histo_LepEffEBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*elSFUnc);
            histo_LepEffMBoundingDown[theCategory]->Fill(MVAVar,totalWeight/muSFUnc); histo_LepEffEBoundingDown[theCategory]->Fill(MVAVar,totalWeight/elSFUnc);
            histo_PUBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*puWeightUp  /puWeight);
            histo_PUBoundingDown[theCategory]->Fill(MVAVar,totalWeight*puWeightDown/puWeight);
            histo_BTAGBBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0BUp  /thePandaFlat.sf_btag0);
            histo_BTAGBBoundingDown[theCategory]->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0BDown/thePandaFlat.sf_btag0);
            histo_BTAGLBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0MUp  /thePandaFlat.sf_btag0);
            histo_BTAGLBoundingDown[theCategory]->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0MDown/thePandaFlat.sf_btag0);
            histo_WSBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*effWSUnc);
            histo_WSBoundingDown[theCategory]->Fill(MVAVar,totalWeight/effWSUnc);
	    histo_EWKCorrWZUp  [theCategory]->Fill(MVAVar,totalWeight*sf_ewkcorrwz_unc);
	    histo_EWKCorrWZDown[theCategory]->Fill(MVAVar,totalWeight/sf_ewkcorrwz_unc);
	    histo_EWKqqZZCorrUp  [theCategory]->Fill(MVAVar,totalWeight*sf_ewkcorrzz_unc);
	    histo_EWKqqZZCorrDown[theCategory]->Fill(MVAVar,totalWeight/sf_ewkcorrzz_unc);
	    histo_ggZZCorrUp  [theCategory]->Fill(MVAVar,totalWeight*sf_ggcorrzz_unc);
	    histo_ggZZCorrDown[theCategory]->Fill(MVAVar,totalWeight/sf_ggcorrzz_unc);
            histo_PreFireBoundingUp  [theCategory]->Fill(MVAVar,totalWeight*sf_l1PrefireE);
            histo_PreFireBoundingDown[theCategory]->Fill(MVAVar,totalWeight/sf_l1PrefireE);
	  }
          if(passSystCuts[JESUP])  histo_JESBoundingUp  [theCategory]->Fill(MVAVarUp  ,totalWeight);
          if(passSystCuts[JESDOWN])histo_JESBoundingDown[theCategory]->Fill(MVAVarDown,totalWeight);
        }
      }

    } // end events loop
    the_input_file->Close();
  } // end chain loop

  for(int ic=0; ic<nPlotCategories; ic++) histo[allPlots-1][ic]->Add(histo_Baseline[ic]);

  double lumiE = 1.025;
  if     (year == 2017) lumiE = 1.023;
  else if(year == 2018) lumiE = 1.050;
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
      histo_PUBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PUBoundingUp  	[ic]->GetBinContent(nb),1e-7f));
      histo_PUBoundingDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_PUBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      histo_BTAGBBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_BTAGBBoundingUp	[ic]->GetBinContent(nb),1e-7f));
      histo_BTAGBBoundingDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_BTAGBBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      histo_BTAGLBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_BTAGLBoundingUp	[ic]->GetBinContent(nb),1e-7f));
      histo_BTAGBBoundingDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_BTAGBBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      histo_WSBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_WSBoundingUp	        [ic]->GetBinContent(nb),1e-7f));
      histo_WSBoundingDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_WSBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      histo_EWKCorrWZUp 	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKCorrWZUp		[ic]->GetBinContent(nb),1e-7f));
      histo_EWKCorrWZDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKCorrWZDown 	[ic]->GetBinContent(nb),1e-7f));
      histo_EWKqqZZCorrUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKqqZZCorrUp 	[ic]->GetBinContent(nb),1e-7f));
      histo_EWKqqZZCorrDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_EWKqqZZCorrDown	[ic]->GetBinContent(nb),1e-7f));
      histo_ggZZCorrUp  	  [ic]->SetBinContent(nb, TMath::Max((float)histo_ggZZCorrUp		[ic]->GetBinContent(nb),1e-7f));
      histo_ggZZCorrDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_ggZZCorrDown  	[ic]->GetBinContent(nb),1e-7f));
      histo_JESBoundingUp	  [ic]->SetBinContent(nb, TMath::Max((float)histo_JESBoundingUp 	[ic]->GetBinContent(nb),1e-7f));
      histo_JESBoundingDown	  [ic]->SetBinContent(nb, TMath::Max((float)histo_JESBoundingDown	[ic]->GetBinContent(nb),1e-7f));
      histo_PreFireBoundingUp     [ic]->SetBinContent(nb, TMath::Max((float)histo_PreFireBoundingUp  	[ic]->GetBinContent(nb),1e-7f));
      histo_PreFireBoundingDown   [ic]->SetBinContent(nb, TMath::Max((float)histo_PreFireBoundingDown	[ic]->GetBinContent(nb),1e-7f));
    }
    histo_PUBoundingUp	[ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_PUBoundingUp  [ic]->GetSumOfWeights());
    histo_PUBoundingDown[ic]->Scale(histo_Baseline[ic]->GetSumOfWeights()/histo_PUBoundingDown[ic]->GetSumOfWeights());
    if(ic == kPlotWZ) {
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

    printf("uncertainties BTAGBUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_BTAGBBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties BTAGBDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_BTAGBBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties BTAGLUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_BTAGLBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties BTAGLDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_BTAGLBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties WSUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_WSBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties WSDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_WSBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
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

    printf("uncertainties JESUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_JESBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties JESDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_JESBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }

    printf("uncertainties PreFireUp\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_PreFireBoundingUp[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
    printf("uncertainties PreFireDown\n");
    for(unsigned ic=0; ic<nPlotCategories; ic++) {
      if(ic == kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
         printf("%10s: ",plotBaseNames[ic].Data());
        for(int i=1; i<=histo_MVA->GetNbinsX(); i++) {if(histo_Baseline[ic]->GetBinContent(i)>0)printf("%5.1f ",histo_PreFireBoundingDown[ic]->GetBinContent(i)/histo_Baseline[ic]->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    }
  }

  // Filling datacards input root file
  char outputLimits[200];
  sprintf(outputLimits,"ssww_%d%s_input.root",year,fidAnaName.Data());
  TFile* outFileLimits = new TFile(outputLimits,"recreate");
  outFileLimits->cd();

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
    histo_PUBoundingUp  	[ic]->Write();
    histo_PUBoundingDown	[ic]->Write();
    histo_BTAGBBoundingUp	[ic]->Write();
    histo_BTAGBBoundingDown	[ic]->Write();
    histo_BTAGLBoundingUp	[ic]->Write();
    histo_BTAGLBoundingDown	[ic]->Write();
    histo_WSBoundingUp          [ic]->Write();
    histo_WSBoundingDown        [ic]->Write();
    histo_EWKCorrWZUp		[ic]->Write();
    histo_EWKCorrWZDown 	[ic]->Write();
    histo_EWKqqZZCorrUp 	[ic]->Write();
    histo_EWKqqZZCorrDown	[ic]->Write();
    histo_ggZZCorrUp		[ic]->Write();
    histo_ggZZCorrDown  	[ic]->Write();
    histo_JESBoundingUp 	[ic]->Write();
    histo_JESBoundingDown	[ic]->Write();
    histo_PreFireBoundingUp 	[ic]->Write();
    histo_PreFireBoundingDown	[ic]->Write();
  }
  outFileLimits->Close();


  // Filling datacards txt file
  char outputLimitsCard[200];  					  
  sprintf(outputLimitsCard,"datacard_ssww_%d%s.txt",year,fidAnaName.Data());
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
    if     (ic != kPlotSSWWEWK && 
            ic != kPlotSignal0 && ic != kPlotSignal1 && 
            ic != kPlotSignal2 && ic != kPlotSignal2) newcardShape << Form("%d  ", ic);
    else if(ic == kPlotSignal0) newcardShape << Form("%d  ", -1);
    else if(ic == kPlotSignal1) newcardShape << Form("%d  ", -2);
    else if(ic == kPlotSignal2) newcardShape << Form("%d  ", -3);
    else if(ic == kPlotSignal3) newcardShape << Form("%d  ", -4);
    else                        newcardShape << Form("%d  ",  0);
  }
  newcardShape << Form("\n");

  newcardShape << Form("rate  ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("%f  ", histo_Baseline[ic]->GetSumOfWeights());
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_fake_%d    lnN     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("1.2 ");
    else                     newcardShape << Form("- ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("lumi_13TeV_%d    lnN     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("%6.3f ",lumiE);
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_momres_m    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("%6.3f ",1.005);
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_momres_e    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("%6.3f ",1.005);
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_trigger    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("%6.3f ",1.005);
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

  for(unsigned ic=0; ic<nPlotCategories; ic++) {
    if(ic== kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("QCDScale_%s_ACCEPT    shape   ",plotBaseNames[ic].Data());
    for(unsigned ic2=0; ic2<nPlotCategories; ic2++) {
      if(ic2 == kPlotData || histo_Baseline[ic2]->GetSumOfWeights() <= 0) continue;
          if(ic==ic2) newcardShape << Form("1.0  ");
          else       newcardShape << Form("-  ");
      }
      newcardShape << Form("\n");
  }

  newcardShape << Form("PDF    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_eff_m    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_eff_e    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_pu    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_btagb_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_btagl_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_jes_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt || ic == kPlotDY) newcardShape << Form("- ");
    else                                      newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_prefire_%d    shape     ",year);
  for (int ic=0; ic<nPlotCategories; ic++){
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_ssww_wznorm  rateParam * %s 1 [0.1,3]\n",plotBaseNames[kPlotWZ].Data());
  newcardShape << Form("CMS_ssww_wznorm  rateParam * %s 1 [0.1,3]\n",plotBaseNames[kPlotEWKWZ].Data());

  newcardShape << Form("ch1 autoMCStats 0\n");

  newcardShape.close();

  // Writing standard histograms
  char output[200];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    sprintf(output,"histossww_%d_%d%s.root",year,thePlot,fidAnaName.Data());	
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    double totBck = 0;
    for(int i=1; i<nPlotCategories; i++) totBck = totBck + histo[thePlot][i]->GetSumOfWeights();
    printf("(%2d) %7.1f vs. %7.1f ",thePlot,histo[thePlot][0]->GetSumOfWeights(),totBck);
    printf("(");
    for(int i=1; i<nPlotCategories; i++) printf("%7.1f ",histo[thePlot][i]->GetSumOfWeights());
    printf(")\n");
    for(int np=0; np<nPlotCategories; np++) histo[thePlot][np]->Write();
    outFilePlotsNote->Close();
  }

}
