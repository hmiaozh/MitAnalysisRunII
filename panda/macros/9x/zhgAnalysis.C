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

const bool isDEBUG = false;
const bool showSyst = true;
const unsigned int period = 0;
const double mcPrescale = 1;
const bool usePureMC = true;
enum selType                     { ZHGSEL,   BTAGSEL,   ZLGSEL,   WZSEL,   WZGSEL,   ZZSEL,   WWSEL, nSelTypes};
TString selTypeName[nSelTypes]=  {"ZHGSEL", "BTAGSEL", "ZLGSEL", "WZSEL", "WZGSEL", "ZZSEL", "WWSEL"};
enum systType                     {JESUP=0, JESDOWN,  METUP,  METDOWN, nSystTypes};
TString systTypeName[nSystTypes]= {"JESUP","JESDOWN","METUP","METDOWN"};

void zhgAnalysis(
){

  double lumi = 35.9;
  if     (period == 1) lumi = 19.3;
  else if(period == 2) lumi = 16.6;
  //*******************************************************
  //Input Files
  //*******************************************************
  TString filesPath    = "/data/t3home000/ceballos/panda/v_002_0/";
  vector<TString> infileName_;
  vector<int> infileCat_;

  infileName_.push_back(Form("%sdata.root",filesPath.Data()));  	       infileCat_.push_back(0);

  if(usePureMC == true){
  infileName_.push_back(Form("%sqqWW.root" ,filesPath.Data())); 	       infileCat_.push_back(1);
  infileName_.push_back(Form("%sggWW.root" ,filesPath.Data())); 	       infileCat_.push_back(1);
  infileName_.push_back(Form("%sTT2L.root" ,filesPath.Data()));		       infileCat_.push_back(1);
  infileName_.push_back(Form("%sTW.root" ,filesPath.Data()));		       infileCat_.push_back(1);
  }
  infileName_.push_back(Form("%sDYJetsToLL_M-10to50.root" ,filesPath.Data())); infileCat_.push_back(2);
  infileName_.push_back(Form("%sDYJetsToLL_Pt0To50.root",filesPath.Data()));   infileCat_.push_back(2);
  infileName_.push_back(Form("%sDYJetsToLL_Pt50To100.root",filesPath.Data())); infileCat_.push_back(2);
  infileName_.push_back(Form("%sDYJetsToLL_Pt100To250.root",filesPath.Data()));infileCat_.push_back(2);
  infileName_.push_back(Form("%sDYJetsToLL_Pt250To400.root",filesPath.Data()));infileCat_.push_back(2);
  infileName_.push_back(Form("%sDYJetsToLL_Pt400To650.root",filesPath.Data()));infileCat_.push_back(2);
  infileName_.push_back(Form("%sDYJetsToLL_Pt650ToInf.root",filesPath.Data()));infileCat_.push_back(2);
  infileName_.push_back(Form("%sVG.root" ,filesPath.Data()));		       infileCat_.push_back(2);
  infileName_.push_back(Form("%sWGstar.root" ,filesPath.Data()));	       infileCat_.push_back(2);

  infileName_.push_back(Form("%sWZ.root" ,filesPath.Data()));		       infileCat_.push_back(3);

  infileName_.push_back(Form("%sqqZZ.root" ,filesPath.Data())); 	       infileCat_.push_back(4);
  infileName_.push_back(Form("%sggZZ.root" ,filesPath.Data())); 	       infileCat_.push_back(4);

  infileName_.push_back(Form("%sVVV.root" ,filesPath.Data()));  	       infileCat_.push_back(5);
  infileName_.push_back(Form("%sTTV.root" ,filesPath.Data()));  	       infileCat_.push_back(5);

  infileName_.push_back(Form("%sH125.root" ,filesPath.Data())); 	       infileCat_.push_back(6);

  infileName_.push_back(Form("%sDarkPhoton_ZH_powheg_M-125.root" ,filesPath.Data())); infileCat_.push_back(7);

  TString puPath = "MitAnalysisRunII/data/80x/puWeights_80x_37ifb.root";
  TFile *fPUFile = TFile::Open(Form("%s",puPath.Data()));
  TH1D *fhDPU     = (TH1D*)(fPUFile->Get("puWeights"));     assert(fhDPU);     fhDPU    ->SetDirectory(0);
  TH1D *fhDPUUp   = (TH1D*)(fPUFile->Get("puWeightsUp"));   assert(fhDPUUp);   fhDPUUp  ->SetDirectory(0);
  TH1D *fhDPUDown = (TH1D*)(fPUFile->Get("puWeightsDown")); assert(fhDPUDown); fhDPUDown->SetDirectory(0);
  delete fPUFile;

  TFile *fLepton_Fakes = TFile::Open(Form("MitAnalysisRunII/data/80x/histoFakeEtaPt_80x_37ifb.root"));
  TH2D* histoFakeEffSelMediumEtaPt_m = (TH2D*)fLepton_Fakes->Get("histoFakeEffSel0EtaPt_0"); histoFakeEffSelMediumEtaPt_m->SetDirectory(0);
  TH2D* histoFakeEffSelMediumEtaPt_e = (TH2D*)fLepton_Fakes->Get("histoFakeEffSel0EtaPt_1"); histoFakeEffSelMediumEtaPt_e->SetDirectory(0);
  TH2D* histoFakeEffSelTightEtaPt_m  = (TH2D*)fLepton_Fakes->Get("histoFakeEffSel2EtaPt_0"); histoFakeEffSelTightEtaPt_m ->SetDirectory(0);
  TH2D* histoFakeEffSelTightEtaPt_e  = (TH2D*)fLepton_Fakes->Get("histoFakeEffSel2EtaPt_1"); histoFakeEffSelTightEtaPt_e ->SetDirectory(0);
  fLepton_Fakes->Close();

  TFile *fLepton_Eta_SF = TFile::Open(Form("MitAnalysisRunII/data/80x/scalefactors_80x_eta_sf_37ifb_period%d.root",period));
  TH1D* scalefactors_Muon_Eta = (TH1D*)fLepton_Eta_SF->Get("scalefactors_Muon_Eta"); scalefactors_Muon_Eta->SetDirectory(0);
  TH1D* scalefactors_Electron_Eta = (TH1D*)fLepton_Eta_SF->Get("scalefactors_Electron_Eta"); scalefactors_Electron_Eta->SetDirectory(0);
  fLepton_Eta_SF->Close();

  TFile *fLepton_SF_mu_central = TFile::Open(Form("MitAnalysisRunII/data/80x/scalefactors_80x_dylan_MediumIdOnly_period%d.root",period));
  TH2D* scalefactors_Medium_Muon = (TH2D*)fLepton_SF_mu_central->Get("scalefactors_Medium_Muon"); scalefactors_Medium_Muon->SetDirectory(0);
  fLepton_SF_mu_central->Close();

  TFile *fLepton_SF_el_central = TFile::Open(Form("MitAnalysisRunII/data/80x/scalefactors_80x_dylan_MediumIdOnly_period%d.root",period));
  TH2D* scalefactors_Medium_Electron = (TH2D*)fLepton_SF_el_central->Get("scalefactors_Medium_Electron"); scalefactors_Medium_Electron->SetDirectory(0);
  fLepton_SF_el_central->Close();

  TFile *fPhotonSF = TFile::Open(Form("MitAnalysisRunII/data/80x/photon_scalefactors_37ifb.root"));
  TH2D *fhDPhotonSF       = (TH2D*)(fPhotonSF->Get("EGamma_SF2D")); assert(fhDPhotonSF); fhDPhotonSF->SetDirectory(0);
  TH2D *fhDElectronVetoSF = (TH2D*)(fPhotonSF->Get("Scaling_Factors_HasPix_R9 Inclusive")); assert(fhDElectronVetoSF); fhDElectronVetoSF->SetDirectory(0);
  delete fPhotonSF;

  double getMaxPtForSFs[2] = {scalefactors_Medium_Muon                  ->GetYaxis()->GetBinCenter(scalefactors_Medium_Muon		     ->GetNbinsY()),
                              scalefactors_Medium_Electron              ->GetYaxis()->GetBinCenter(scalefactors_Medium_Electron		     ->GetNbinsY())
		              };

  const int MVAVarType = 0; const int nBinMVA = 5; Double_t xbins[nBinMVA+1] = {0, 75, 100, 125, 150, 175}; TString addChan = "";

  int nBinPlot      = 200;
  double xminPlot   = 0.0;
  double xmaxPlot   = 200.0;
  const int allPlots = 36;
  const int histBins = 8;
  TH1D* histo[allPlots][histBins];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    if     (thePlot >=   0 && thePlot <=  23) {nBinPlot = 175; xminPlot =  0.0; xmaxPlot = 175;}
    else if(thePlot >=  24 && thePlot <=  24) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = 100;}
    else if(thePlot >=  25 && thePlot <=  25) {nBinPlot = 5;   xminPlot = -0.5; xmaxPlot = 4.5;}
    else if(thePlot >=  26 && thePlot <=  26) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >=  27 && thePlot <=  27) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 2;}
    else if(thePlot >=  28 && thePlot <=  28) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = TMath::Pi();}
    else if(thePlot >=  29 && thePlot <=  29) {nBinPlot = 4;   xminPlot = -0.5; xmaxPlot = 3.5;}
    else if(thePlot >=  30 && thePlot <=  30) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 200;}
    else if(thePlot >=  31 && thePlot <=  31) {nBinPlot = 100; xminPlot =  0.0; xmaxPlot = TMath::Pi();}
    else if(thePlot >=  32 && thePlot <=  32) {nBinPlot = 4;   xminPlot = -0.5; xmaxPlot = 3.5;}
    else if(thePlot >=  33 && thePlot <=  33) {nBinPlot = 200; xminPlot =  0.0; xmaxPlot = 400;}
    else if(thePlot >=  34 && thePlot <=  34) {nBinPlot = 2;   xminPlot = -0.5; xmaxPlot = 1.5;}
    TH1D* histos;
    if(thePlot == allPlots-1) histos = new TH1D("histos", "histos", nBinMVA, xbins);
    else                      histos = new TH1D("histos", "histos", nBinPlot, xminPlot, xmaxPlot);
    histos->Sumw2();
    for(int i=0; i<histBins; i++) histo[thePlot][i] = (TH1D*) histos->Clone(Form("histo%d",i));
    histos->Reset();histos->Clear();
  }

  TH1D* histoMVA = new TH1D("histoMVA", "histoMVA", nBinMVA, xbins); histoMVA->Sumw2();

  TH1D *histo_Data     = (TH1D*) histoMVA->Clone("histo_Data");
  TH1D *histo_EM       = (TH1D*) histoMVA->Clone("histo_EM");	 
  TH1D *histo_VG       = (TH1D*) histoMVA->Clone("histo_VG");	 
  TH1D *histo_WZ       = (TH1D*) histoMVA->Clone("histo_WZ");	 
  TH1D *histo_ZZ       = (TH1D*) histoMVA->Clone("histo_ZZ");
  TH1D *histo_VVV      = (TH1D*) histoMVA->Clone("histo_VVV");	 
  TH1D *histo_Higgs    = (TH1D*) histoMVA->Clone("histo_Higgs"); 
  TH1D *histo_ZH       = (TH1D*) histoMVA->Clone("histo_ZH"); 

  char QCDScaleName[20]; sprintf(QCDScaleName,"QCDScale");
  char PDFName[20]; sprintf(PDFName,"pdf");
  char effMName[20]; sprintf(effMName,"CMS_eff_m");
  char effEName[20]; sprintf(effEName,"CMS_eff_e");
  char METName[20]; sprintf(METName,"CMS_met");
  char JESName[20]; sprintf(JESName,"CMS_jes");
  char PUName[20]; sprintf(PUName,"CMS_pu");
  char BTAGBName[20]; sprintf(BTAGBName,"CMS_btagb");
  char BTAGLName[20]; sprintf(BTAGLName,"CMS_btagl");

  TH1D* histo_EM_CMS_QCDScaleBounding[6];
  TH1D* histo_VG_CMS_QCDScaleBounding[6];
  TH1D* histo_WZ_CMS_QCDScaleBounding[6];
  TH1D* histo_ZZ_CMS_QCDScaleBounding[6];
  TH1D* histo_VVV_CMS_QCDScaleBounding[6];
  TH1D* histo_Higgs_CMS_QCDScaleBounding[6];
  TH1D* histo_ZH_CMS_QCDScaleBounding[6];
  for(int nb=0; nb<6; nb++){
    histo_EM_CMS_QCDScaleBounding[nb]       = new TH1D(Form("histo_EM_QCDScaleEM_f%d",nb),      Form("histo_EM_QCDScaleEM_f%d",nb),nBinMVA, xbins);       histo_EM_CMS_QCDScaleBounding[nb]->Sumw2();
    histo_VG_CMS_QCDScaleBounding[nb]       = new TH1D(Form("histo_VG_QCDScaleVG_f%d",nb),      Form("histo_VG_QCDScaleVG_f%d",nb),nBinMVA, xbins);       histo_VG_CMS_QCDScaleBounding[nb]->Sumw2();
    histo_WZ_CMS_QCDScaleBounding[nb]       = new TH1D(Form("histo_WZ_QCDScaleWZ_f%d",nb),      Form("histo_WZ_QCDScaleWZ_f%d",nb),nBinMVA, xbins);       histo_WZ_CMS_QCDScaleBounding[nb]->Sumw2();
    histo_ZZ_CMS_QCDScaleBounding[nb]       = new TH1D(Form("histo_ZZ_QCDScaleZZ_f%d",nb),      Form("histo_ZZ_QCDScaleZZ_f%d",nb),nBinMVA, xbins);       histo_ZZ_CMS_QCDScaleBounding[nb]->Sumw2();
    histo_VVV_CMS_QCDScaleBounding[nb]      = new TH1D(Form("histo_VVV_QCDScaleVVV_f%d",nb),    Form("histo_VVV_QCDScaleVVV_f%d",nb),nBinMVA, xbins);     histo_VVV_CMS_QCDScaleBounding[nb]->Sumw2();
    histo_Higgs_CMS_QCDScaleBounding[nb]    = new TH1D(Form("histo_Higgs_QCDScaleHiggs_f%d",nb),Form("histo_Higgs_QCDScaleHiggs_f%d",nb),nBinMVA, xbins); histo_Higgs_CMS_QCDScaleBounding[nb]->Sumw2();
    histo_ZH_CMS_QCDScaleBounding[nb]       = new TH1D(Form("histo_ZH_QCDScaleZH_f%d",nb),      Form("histo_ZH_QCDScaleZH_f%d",nb),nBinMVA, xbins);       histo_ZH_CMS_QCDScaleBounding[nb]->Sumw2();
  }

  TH1D* histo_EM_CMS_MVAQCDScaleBoundingUp   = new TH1D( Form("histo_EM_%sEMUp",QCDScaleName)  , Form("histo_EM_%sEMUp",QCDScaleName)  , nBinMVA, xbins); histo_EM_CMS_MVAQCDScaleBoundingUp  ->Sumw2();
  TH1D* histo_VG_CMS_MVAQCDScaleBoundingUp   = new TH1D( Form("histo_VG_%sVGUp",QCDScaleName)  , Form("histo_VG_%sVGUp",QCDScaleName)  , nBinMVA, xbins); histo_VG_CMS_MVAQCDScaleBoundingUp  ->Sumw2();
  TH1D* histo_WZ_CMS_MVAQCDScaleBoundingUp   = new TH1D( Form("histo_WZ_%sWZUp",QCDScaleName)  , Form("histo_WZ_%sWZUp",QCDScaleName)  , nBinMVA, xbins); histo_WZ_CMS_MVAQCDScaleBoundingUp  ->Sumw2();
  TH1D* histo_ZZ_CMS_MVAQCDScaleBoundingUp   = new TH1D( Form("histo_ZZ_%sZZUp",QCDScaleName)  , Form("histo_ZZ_%sZZUp",QCDScaleName)  , nBinMVA, xbins); histo_ZZ_CMS_MVAQCDScaleBoundingUp  ->Sumw2();
  TH1D* histo_VVV_CMS_MVAQCDScaleBoundingUp  = new TH1D( Form("histo_VVV_%sVVVUp",QCDScaleName)  , Form("histo_VVV_%sVVVUp",QCDScaleName)  , nBinMVA, xbins); histo_VVV_CMS_MVAQCDScaleBoundingUp  ->Sumw2();
  TH1D* histo_Higgs_CMS_MVAQCDScaleBoundingUp= new TH1D( Form("histo_Higgs_%sHiggsUp",QCDScaleName)  , Form("histo_Higgs_%sHiggsUp",QCDScaleName)  , nBinMVA, xbins); histo_Higgs_CMS_MVAQCDScaleBoundingUp  ->Sumw2();
  TH1D* histo_ZH_CMS_MVAQCDScaleBoundingUp   = new TH1D( Form("histo_ZH_%sZHUp",QCDScaleName)  , Form("histo_ZH_%sZHUp",QCDScaleName)  , nBinMVA, xbins); histo_ZH_CMS_MVAQCDScaleBoundingUp  ->Sumw2();
  TH1D* histo_EM_CMS_MVAQCDScaleBoundingDown   = new TH1D( Form("histo_EM_%sEMDown",QCDScaleName)  , Form("histo_EM_%sEMDown",QCDScaleName)  , nBinMVA, xbins); histo_EM_CMS_MVAQCDScaleBoundingDown  ->Sumw2();
  TH1D* histo_VG_CMS_MVAQCDScaleBoundingDown   = new TH1D( Form("histo_VG_%sVGDown",QCDScaleName)  , Form("histo_VG_%sVGDown",QCDScaleName)  , nBinMVA, xbins); histo_VG_CMS_MVAQCDScaleBoundingDown  ->Sumw2();
  TH1D* histo_WZ_CMS_MVAQCDScaleBoundingDown   = new TH1D( Form("histo_WZ_%sWZDown",QCDScaleName)  , Form("histo_WZ_%sWZDown",QCDScaleName)  , nBinMVA, xbins); histo_WZ_CMS_MVAQCDScaleBoundingDown  ->Sumw2();
  TH1D* histo_ZZ_CMS_MVAQCDScaleBoundingDown   = new TH1D( Form("histo_ZZ_%sZZDown",QCDScaleName)  , Form("histo_ZZ_%sZZDown",QCDScaleName)  , nBinMVA, xbins); histo_ZZ_CMS_MVAQCDScaleBoundingDown  ->Sumw2();
  TH1D* histo_VVV_CMS_MVAQCDScaleBoundingDown  = new TH1D( Form("histo_VVV_%sVVVDown",QCDScaleName)  , Form("histo_VVV_%sVVVDown",QCDScaleName)  , nBinMVA, xbins); histo_VVV_CMS_MVAQCDScaleBoundingDown  ->Sumw2();
  TH1D* histo_Higgs_CMS_MVAQCDScaleBoundingDown= new TH1D( Form("histo_Higgs_%sHiggsDown",QCDScaleName)  , Form("histo_Higgs_%sHiggsDown",QCDScaleName)  , nBinMVA, xbins); histo_Higgs_CMS_MVAQCDScaleBoundingDown  ->Sumw2();
  TH1D* histo_ZH_CMS_MVAQCDScaleBoundingDown   = new TH1D( Form("histo_ZH_%sZHDown",QCDScaleName)  , Form("histo_ZH_%sZHDown",QCDScaleName)  , nBinMVA, xbins); histo_ZH_CMS_MVAQCDScaleBoundingDown  ->Sumw2();

  TH1D* histo_EM_CMS_MVAPDFBoundingUp   = new TH1D( Form("histo_EM_%sUp",PDFName)  , Form("histo_EM_%sUp",PDFName)  , nBinMVA, xbins); histo_EM_CMS_MVAPDFBoundingUp  ->Sumw2();
  TH1D* histo_VG_CMS_MVAPDFBoundingUp   = new TH1D( Form("histo_VG_%sUp",PDFName)  , Form("histo_VG_%sUp",PDFName)  , nBinMVA, xbins); histo_VG_CMS_MVAPDFBoundingUp  ->Sumw2();
  TH1D* histo_WZ_CMS_MVAPDFBoundingUp   = new TH1D( Form("histo_WZ_%sUp",PDFName)  , Form("histo_WZ_%sUp",PDFName)  , nBinMVA, xbins); histo_WZ_CMS_MVAPDFBoundingUp  ->Sumw2();
  TH1D* histo_ZZ_CMS_MVAPDFBoundingUp   = new TH1D( Form("histo_ZZ_%sUp",PDFName)  , Form("histo_ZZ_%sUp",PDFName)  , nBinMVA, xbins); histo_ZZ_CMS_MVAPDFBoundingUp  ->Sumw2();
  TH1D* histo_VVV_CMS_MVAPDFBoundingUp  = new TH1D( Form("histo_VVV_%sUp",PDFName)  , Form("histo_VVV_%sUp",PDFName)  , nBinMVA, xbins); histo_VVV_CMS_MVAPDFBoundingUp  ->Sumw2();
  TH1D* histo_Higgs_CMS_MVAPDFBoundingUp= new TH1D( Form("histo_Higgs_%sUp",PDFName)  , Form("histo_Higgs_%sUp",PDFName)  , nBinMVA, xbins); histo_Higgs_CMS_MVAPDFBoundingUp  ->Sumw2();
  TH1D* histo_ZH_CMS_MVAPDFBoundingUp   = new TH1D( Form("histo_ZH_%sUp",PDFName)  , Form("histo_ZH_%sUp",PDFName)  , nBinMVA, xbins); histo_ZH_CMS_MVAPDFBoundingUp  ->Sumw2();
  TH1D* histo_EM_CMS_MVAPDFBoundingDown   = new TH1D( Form("histo_EM_%sDown",PDFName)  , Form("histo_EM_%sDown",PDFName)  , nBinMVA, xbins); histo_EM_CMS_MVAPDFBoundingDown  ->Sumw2();
  TH1D* histo_VG_CMS_MVAPDFBoundingDown   = new TH1D( Form("histo_VG_%sDown",PDFName)  , Form("histo_VG_%sDown",PDFName)  , nBinMVA, xbins); histo_VG_CMS_MVAPDFBoundingDown  ->Sumw2();
  TH1D* histo_WZ_CMS_MVAPDFBoundingDown   = new TH1D( Form("histo_WZ_%sDown",PDFName)  , Form("histo_WZ_%sDown",PDFName)  , nBinMVA, xbins); histo_WZ_CMS_MVAPDFBoundingDown  ->Sumw2();
  TH1D* histo_ZZ_CMS_MVAPDFBoundingDown   = new TH1D( Form("histo_ZZ_%sDown",PDFName)  , Form("histo_ZZ_%sDown",PDFName)  , nBinMVA, xbins); histo_ZZ_CMS_MVAPDFBoundingDown  ->Sumw2();
  TH1D* histo_VVV_CMS_MVAPDFBoundingDown  = new TH1D( Form("histo_VVV_%sDown",PDFName)  , Form("histo_VVV_%sDown",PDFName)  , nBinMVA, xbins); histo_VVV_CMS_MVAPDFBoundingDown  ->Sumw2();
  TH1D* histo_Higgs_CMS_MVAPDFBoundingDown= new TH1D( Form("histo_Higgs_%sDown",PDFName)  , Form("histo_Higgs_%sDown",PDFName)  , nBinMVA, xbins); histo_Higgs_CMS_MVAPDFBoundingDown  ->Sumw2();
  TH1D* histo_ZH_CMS_MVAPDFBoundingDown   = new TH1D( Form("histo_ZH_%sDown",PDFName)  , Form("histo_ZH_%sDown",PDFName)  , nBinMVA, xbins); histo_ZH_CMS_MVAPDFBoundingDown  ->Sumw2();

  TH1D* histo_EM_CMS_MVALepEffEBoundingUp   = new TH1D( Form("histo_EM_%sUp",effEName)  , Form("histo_EM_%sUp",effEName)  , nBinMVA, xbins); histo_EM_CMS_MVALepEffEBoundingUp  ->Sumw2();
  TH1D* histo_VG_CMS_MVALepEffEBoundingUp   = new TH1D( Form("histo_VG_%sUp",effEName)  , Form("histo_VG_%sUp",effEName)  , nBinMVA, xbins); histo_VG_CMS_MVALepEffEBoundingUp  ->Sumw2();
  TH1D* histo_WZ_CMS_MVALepEffEBoundingUp   = new TH1D( Form("histo_WZ_%sUp",effEName)  , Form("histo_WZ_%sUp",effEName)  , nBinMVA, xbins); histo_WZ_CMS_MVALepEffEBoundingUp  ->Sumw2();
  TH1D* histo_ZZ_CMS_MVALepEffEBoundingUp   = new TH1D( Form("histo_ZZ_%sUp",effEName)  , Form("histo_ZZ_%sUp",effEName)  , nBinMVA, xbins); histo_ZZ_CMS_MVALepEffEBoundingUp  ->Sumw2();
  TH1D* histo_VVV_CMS_MVALepEffEBoundingUp  = new TH1D( Form("histo_VVV_%sUp",effEName)  , Form("histo_VVV_%sUp",effEName)  , nBinMVA, xbins); histo_VVV_CMS_MVALepEffEBoundingUp  ->Sumw2();
  TH1D* histo_Higgs_CMS_MVALepEffEBoundingUp= new TH1D( Form("histo_Higgs_%sUp",effEName)  , Form("histo_Higgs_%sUp",effEName)  , nBinMVA, xbins); histo_Higgs_CMS_MVALepEffEBoundingUp  ->Sumw2();
  TH1D* histo_ZH_CMS_MVALepEffEBoundingUp   = new TH1D( Form("histo_ZH_%sUp",effEName)  , Form("histo_ZH_%sUp",effEName)  , nBinMVA, xbins); histo_ZH_CMS_MVALepEffEBoundingUp  ->Sumw2();
  TH1D* histo_EM_CMS_MVALepEffEBoundingDown   = new TH1D( Form("histo_EM_%sDown",effEName)  , Form("histo_EM_%sDown",effEName)  , nBinMVA, xbins); histo_EM_CMS_MVALepEffEBoundingDown  ->Sumw2();
  TH1D* histo_VG_CMS_MVALepEffEBoundingDown   = new TH1D( Form("histo_VG_%sDown",effEName)  , Form("histo_VG_%sDown",effEName)  , nBinMVA, xbins); histo_VG_CMS_MVALepEffEBoundingDown  ->Sumw2();
  TH1D* histo_WZ_CMS_MVALepEffEBoundingDown   = new TH1D( Form("histo_WZ_%sDown",effEName)  , Form("histo_WZ_%sDown",effEName)  , nBinMVA, xbins); histo_WZ_CMS_MVALepEffEBoundingDown  ->Sumw2();
  TH1D* histo_ZZ_CMS_MVALepEffEBoundingDown   = new TH1D( Form("histo_ZZ_%sDown",effEName)  , Form("histo_ZZ_%sDown",effEName)  , nBinMVA, xbins); histo_ZZ_CMS_MVALepEffEBoundingDown  ->Sumw2();
  TH1D* histo_VVV_CMS_MVALepEffEBoundingDown  = new TH1D( Form("histo_VVV_%sDown",effEName)  , Form("histo_VVV_%sDown",effEName)  , nBinMVA, xbins); histo_VVV_CMS_MVALepEffEBoundingDown  ->Sumw2();
  TH1D* histo_Higgs_CMS_MVALepEffEBoundingDown= new TH1D( Form("histo_Higgs_%sDown",effEName)  , Form("histo_Higgs_%sDown",effEName)  , nBinMVA, xbins); histo_Higgs_CMS_MVALepEffEBoundingDown  ->Sumw2();
  TH1D* histo_ZH_CMS_MVALepEffEBoundingDown   = new TH1D( Form("histo_ZH_%sDown",effEName)  , Form("histo_ZH_%sDown",effEName)  , nBinMVA, xbins); histo_ZH_CMS_MVALepEffEBoundingDown  ->Sumw2();

  TH1D* histo_EM_CMS_MVALepEffMBoundingUp   = new TH1D( Form("histo_EM_%sUp",effMName)  , Form("histo_EM_%sUp",effMName)  , nBinMVA, xbins); histo_EM_CMS_MVALepEffMBoundingUp  ->Sumw2();
  TH1D* histo_VG_CMS_MVALepEffMBoundingUp   = new TH1D( Form("histo_VG_%sUp",effMName)  , Form("histo_VG_%sUp",effMName)  , nBinMVA, xbins); histo_VG_CMS_MVALepEffMBoundingUp  ->Sumw2();
  TH1D* histo_WZ_CMS_MVALepEffMBoundingUp   = new TH1D( Form("histo_WZ_%sUp",effMName)  , Form("histo_WZ_%sUp",effMName)  , nBinMVA, xbins); histo_WZ_CMS_MVALepEffMBoundingUp  ->Sumw2();
  TH1D* histo_ZZ_CMS_MVALepEffMBoundingUp   = new TH1D( Form("histo_ZZ_%sUp",effMName)  , Form("histo_ZZ_%sUp",effMName)  , nBinMVA, xbins); histo_ZZ_CMS_MVALepEffMBoundingUp  ->Sumw2();
  TH1D* histo_VVV_CMS_MVALepEffMBoundingUp  = new TH1D( Form("histo_VVV_%sUp",effMName)  , Form("histo_VVV_%sUp",effMName)  , nBinMVA, xbins); histo_VVV_CMS_MVALepEffMBoundingUp  ->Sumw2();
  TH1D* histo_Higgs_CMS_MVALepEffMBoundingUp= new TH1D( Form("histo_Higgs_%sUp",effMName)  , Form("histo_Higgs_%sUp",effMName)  , nBinMVA, xbins); histo_Higgs_CMS_MVALepEffMBoundingUp  ->Sumw2();
  TH1D* histo_ZH_CMS_MVALepEffMBoundingUp   = new TH1D( Form("histo_ZH_%sUp",effMName)  , Form("histo_ZH_%sUp",effMName)  , nBinMVA, xbins); histo_ZH_CMS_MVALepEffMBoundingUp  ->Sumw2();
  TH1D* histo_EM_CMS_MVALepEffMBoundingDown   = new TH1D( Form("histo_EM_%sDown",effMName)  , Form("histo_EM_%sDown",effMName)  , nBinMVA, xbins); histo_EM_CMS_MVALepEffMBoundingDown  ->Sumw2();
  TH1D* histo_VG_CMS_MVALepEffMBoundingDown   = new TH1D( Form("histo_VG_%sDown",effMName)  , Form("histo_VG_%sDown",effMName)  , nBinMVA, xbins); histo_VG_CMS_MVALepEffMBoundingDown  ->Sumw2();
  TH1D* histo_WZ_CMS_MVALepEffMBoundingDown   = new TH1D( Form("histo_WZ_%sDown",effMName)  , Form("histo_WZ_%sDown",effMName)  , nBinMVA, xbins); histo_WZ_CMS_MVALepEffMBoundingDown  ->Sumw2();
  TH1D* histo_ZZ_CMS_MVALepEffMBoundingDown   = new TH1D( Form("histo_ZZ_%sDown",effMName)  , Form("histo_ZZ_%sDown",effMName)  , nBinMVA, xbins); histo_ZZ_CMS_MVALepEffMBoundingDown  ->Sumw2();
  TH1D* histo_VVV_CMS_MVALepEffMBoundingDown  = new TH1D( Form("histo_VVV_%sDown",effMName)  , Form("histo_VVV_%sDown",effMName)  , nBinMVA, xbins); histo_VVV_CMS_MVALepEffMBoundingDown  ->Sumw2();
  TH1D* histo_Higgs_CMS_MVALepEffMBoundingDown= new TH1D( Form("histo_Higgs_%sDown",effMName)  , Form("histo_Higgs_%sDown",effMName)  , nBinMVA, xbins); histo_Higgs_CMS_MVALepEffMBoundingDown  ->Sumw2();
  TH1D* histo_ZH_CMS_MVALepEffMBoundingDown   = new TH1D( Form("histo_ZH_%sDown",effMName)  , Form("histo_ZH_%sDown",effMName)  , nBinMVA, xbins); histo_ZH_CMS_MVALepEffMBoundingDown  ->Sumw2();

  TH1D* histo_EM_CMS_MVAMETBoundingUp   = new TH1D( Form("histo_EM_%sUp",METName)  , Form("histo_EM_%sUp",METName)  , nBinMVA, xbins); histo_EM_CMS_MVAMETBoundingUp  ->Sumw2();
  TH1D* histo_VG_CMS_MVAMETBoundingUp   = new TH1D( Form("histo_VG_%sUp",METName)  , Form("histo_VG_%sUp",METName)  , nBinMVA, xbins); histo_VG_CMS_MVAMETBoundingUp  ->Sumw2();
  TH1D* histo_WZ_CMS_MVAMETBoundingUp   = new TH1D( Form("histo_WZ_%sUp",METName)  , Form("histo_WZ_%sUp",METName)  , nBinMVA, xbins); histo_WZ_CMS_MVAMETBoundingUp  ->Sumw2();
  TH1D* histo_ZZ_CMS_MVAMETBoundingUp   = new TH1D( Form("histo_ZZ_%sUp",METName)  , Form("histo_ZZ_%sUp",METName)  , nBinMVA, xbins); histo_ZZ_CMS_MVAMETBoundingUp  ->Sumw2();
  TH1D* histo_VVV_CMS_MVAMETBoundingUp  = new TH1D( Form("histo_VVV_%sUp",METName)  , Form("histo_VVV_%sUp",METName)  , nBinMVA, xbins); histo_VVV_CMS_MVAMETBoundingUp  ->Sumw2();
  TH1D* histo_Higgs_CMS_MVAMETBoundingUp= new TH1D( Form("histo_Higgs_%sUp",METName)  , Form("histo_Higgs_%sUp",METName)  , nBinMVA, xbins); histo_Higgs_CMS_MVAMETBoundingUp  ->Sumw2();
  TH1D* histo_ZH_CMS_MVAMETBoundingUp   = new TH1D( Form("histo_ZH_%sUp",METName)  , Form("histo_ZH_%sUp",METName)  , nBinMVA, xbins); histo_ZH_CMS_MVAMETBoundingUp  ->Sumw2();
  TH1D* histo_EM_CMS_MVAMETBoundingDown   = new TH1D( Form("histo_EM_%sDown",METName)  , Form("histo_EM_%sDown",METName)  , nBinMVA, xbins); histo_EM_CMS_MVAMETBoundingDown  ->Sumw2();
  TH1D* histo_VG_CMS_MVAMETBoundingDown   = new TH1D( Form("histo_VG_%sDown",METName)  , Form("histo_VG_%sDown",METName)  , nBinMVA, xbins); histo_VG_CMS_MVAMETBoundingDown  ->Sumw2();
  TH1D* histo_WZ_CMS_MVAMETBoundingDown   = new TH1D( Form("histo_WZ_%sDown",METName)  , Form("histo_WZ_%sDown",METName)  , nBinMVA, xbins); histo_WZ_CMS_MVAMETBoundingDown  ->Sumw2();
  TH1D* histo_ZZ_CMS_MVAMETBoundingDown   = new TH1D( Form("histo_ZZ_%sDown",METName)  , Form("histo_ZZ_%sDown",METName)  , nBinMVA, xbins); histo_ZZ_CMS_MVAMETBoundingDown  ->Sumw2();
  TH1D* histo_VVV_CMS_MVAMETBoundingDown  = new TH1D( Form("histo_VVV_%sDown",METName)  , Form("histo_VVV_%sDown",METName)  , nBinMVA, xbins); histo_VVV_CMS_MVAMETBoundingDown  ->Sumw2();
  TH1D* histo_Higgs_CMS_MVAMETBoundingDown= new TH1D( Form("histo_Higgs_%sDown",METName)  , Form("histo_Higgs_%sDown",METName)  , nBinMVA, xbins); histo_Higgs_CMS_MVAMETBoundingDown  ->Sumw2();
  TH1D* histo_ZH_CMS_MVAMETBoundingDown   = new TH1D( Form("histo_ZH_%sDown",METName)  , Form("histo_ZH_%sDown",METName)  , nBinMVA, xbins); histo_ZH_CMS_MVAMETBoundingDown  ->Sumw2();

  TH1D* histo_EM_CMS_MVAJESBoundingUp   = new TH1D( Form("histo_EM_%sUp",JESName)  , Form("histo_EM_%sUp",JESName)  , nBinMVA, xbins); histo_EM_CMS_MVAJESBoundingUp  ->Sumw2();
  TH1D* histo_VG_CMS_MVAJESBoundingUp   = new TH1D( Form("histo_VG_%sUp",JESName)  , Form("histo_VG_%sUp",JESName)  , nBinMVA, xbins); histo_VG_CMS_MVAJESBoundingUp  ->Sumw2();
  TH1D* histo_WZ_CMS_MVAJESBoundingUp   = new TH1D( Form("histo_WZ_%sUp",JESName)  , Form("histo_WZ_%sUp",JESName)  , nBinMVA, xbins); histo_WZ_CMS_MVAJESBoundingUp  ->Sumw2();
  TH1D* histo_ZZ_CMS_MVAJESBoundingUp   = new TH1D( Form("histo_ZZ_%sUp",JESName)  , Form("histo_ZZ_%sUp",JESName)  , nBinMVA, xbins); histo_ZZ_CMS_MVAJESBoundingUp  ->Sumw2();
  TH1D* histo_VVV_CMS_MVAJESBoundingUp  = new TH1D( Form("histo_VVV_%sUp",JESName)  , Form("histo_VVV_%sUp",JESName)  , nBinMVA, xbins); histo_VVV_CMS_MVAJESBoundingUp  ->Sumw2();
  TH1D* histo_Higgs_CMS_MVAJESBoundingUp= new TH1D( Form("histo_Higgs_%sUp",JESName)  , Form("histo_Higgs_%sUp",JESName)  , nBinMVA, xbins); histo_Higgs_CMS_MVAJESBoundingUp  ->Sumw2();
  TH1D* histo_ZH_CMS_MVAJESBoundingUp   = new TH1D( Form("histo_ZH_%sUp",JESName)  , Form("histo_ZH_%sUp",JESName)  , nBinMVA, xbins); histo_ZH_CMS_MVAJESBoundingUp  ->Sumw2();
  TH1D* histo_EM_CMS_MVAJESBoundingDown   = new TH1D( Form("histo_EM_%sDown",JESName)  , Form("histo_EM_%sDown",JESName)  , nBinMVA, xbins); histo_EM_CMS_MVAJESBoundingDown  ->Sumw2();
  TH1D* histo_VG_CMS_MVAJESBoundingDown   = new TH1D( Form("histo_VG_%sDown",JESName)  , Form("histo_VG_%sDown",JESName)  , nBinMVA, xbins); histo_VG_CMS_MVAJESBoundingDown  ->Sumw2();
  TH1D* histo_WZ_CMS_MVAJESBoundingDown   = new TH1D( Form("histo_WZ_%sDown",JESName)  , Form("histo_WZ_%sDown",JESName)  , nBinMVA, xbins); histo_WZ_CMS_MVAJESBoundingDown  ->Sumw2();
  TH1D* histo_ZZ_CMS_MVAJESBoundingDown   = new TH1D( Form("histo_ZZ_%sDown",JESName)  , Form("histo_ZZ_%sDown",JESName)  , nBinMVA, xbins); histo_ZZ_CMS_MVAJESBoundingDown  ->Sumw2();
  TH1D* histo_VVV_CMS_MVAJESBoundingDown  = new TH1D( Form("histo_VVV_%sDown",JESName)  , Form("histo_VVV_%sDown",JESName)  , nBinMVA, xbins); histo_VVV_CMS_MVAJESBoundingDown  ->Sumw2();
  TH1D* histo_Higgs_CMS_MVAJESBoundingDown= new TH1D( Form("histo_Higgs_%sDown",JESName)  , Form("histo_Higgs_%sDown",JESName)  , nBinMVA, xbins); histo_Higgs_CMS_MVAJESBoundingDown  ->Sumw2();
  TH1D* histo_ZH_CMS_MVAJESBoundingDown   = new TH1D( Form("histo_ZH_%sDown",JESName)  , Form("histo_ZH_%sDown",JESName)  , nBinMVA, xbins); histo_ZH_CMS_MVAJESBoundingDown  ->Sumw2();

  TH1D* histo_EM_CMS_MVAPUBoundingUp   = new TH1D( Form("histo_EM_%sUp",PUName)  , Form("histo_EM_%sUp",PUName)  , nBinMVA, xbins); histo_EM_CMS_MVAPUBoundingUp  ->Sumw2();
  TH1D* histo_VG_CMS_MVAPUBoundingUp   = new TH1D( Form("histo_VG_%sUp",PUName)  , Form("histo_VG_%sUp",PUName)  , nBinMVA, xbins); histo_VG_CMS_MVAPUBoundingUp  ->Sumw2();
  TH1D* histo_WZ_CMS_MVAPUBoundingUp   = new TH1D( Form("histo_WZ_%sUp",PUName)  , Form("histo_WZ_%sUp",PUName)  , nBinMVA, xbins); histo_WZ_CMS_MVAPUBoundingUp  ->Sumw2();
  TH1D* histo_ZZ_CMS_MVAPUBoundingUp   = new TH1D( Form("histo_ZZ_%sUp",PUName)  , Form("histo_ZZ_%sUp",PUName)  , nBinMVA, xbins); histo_ZZ_CMS_MVAPUBoundingUp  ->Sumw2();
  TH1D* histo_VVV_CMS_MVAPUBoundingUp  = new TH1D( Form("histo_VVV_%sUp",PUName)  , Form("histo_VVV_%sUp",PUName)  , nBinMVA, xbins); histo_VVV_CMS_MVAPUBoundingUp  ->Sumw2();
  TH1D* histo_Higgs_CMS_MVAPUBoundingUp= new TH1D( Form("histo_Higgs_%sUp",PUName)  , Form("histo_Higgs_%sUp",PUName)  , nBinMVA, xbins); histo_Higgs_CMS_MVAPUBoundingUp  ->Sumw2();
  TH1D* histo_ZH_CMS_MVAPUBoundingUp   = new TH1D( Form("histo_ZH_%sUp",PUName)  , Form("histo_ZH_%sUp",PUName)  , nBinMVA, xbins); histo_ZH_CMS_MVAPUBoundingUp  ->Sumw2();
  TH1D* histo_EM_CMS_MVAPUBoundingDown   = new TH1D( Form("histo_EM_%sDown",PUName)  , Form("histo_EM_%sDown",PUName)  , nBinMVA, xbins); histo_EM_CMS_MVAPUBoundingDown  ->Sumw2();
  TH1D* histo_VG_CMS_MVAPUBoundingDown   = new TH1D( Form("histo_VG_%sDown",PUName)  , Form("histo_VG_%sDown",PUName)  , nBinMVA, xbins); histo_VG_CMS_MVAPUBoundingDown  ->Sumw2();
  TH1D* histo_WZ_CMS_MVAPUBoundingDown   = new TH1D( Form("histo_WZ_%sDown",PUName)  , Form("histo_WZ_%sDown",PUName)  , nBinMVA, xbins); histo_WZ_CMS_MVAPUBoundingDown  ->Sumw2();
  TH1D* histo_ZZ_CMS_MVAPUBoundingDown   = new TH1D( Form("histo_ZZ_%sDown",PUName)  , Form("histo_ZZ_%sDown",PUName)  , nBinMVA, xbins); histo_ZZ_CMS_MVAPUBoundingDown  ->Sumw2();
  TH1D* histo_VVV_CMS_MVAPUBoundingDown  = new TH1D( Form("histo_VVV_%sDown",PUName)  , Form("histo_VVV_%sDown",PUName)  , nBinMVA, xbins); histo_VVV_CMS_MVAPUBoundingDown  ->Sumw2();
  TH1D* histo_Higgs_CMS_MVAPUBoundingDown= new TH1D( Form("histo_Higgs_%sDown",PUName)  , Form("histo_Higgs_%sDown",PUName)  , nBinMVA, xbins); histo_Higgs_CMS_MVAPUBoundingDown  ->Sumw2();
  TH1D* histo_ZH_CMS_MVAPUBoundingDown   = new TH1D( Form("histo_ZH_%sDown",PUName)  , Form("histo_ZH_%sDown",PUName)  , nBinMVA, xbins); histo_ZH_CMS_MVAPUBoundingDown  ->Sumw2();

  TH1D* histo_EM_CMS_MVABTAGBBoundingUp   = new TH1D( Form("histo_EM_%sUp",BTAGBName)  , Form("histo_EM_%sUp",BTAGBName)  , nBinMVA, xbins); histo_EM_CMS_MVABTAGBBoundingUp  ->Sumw2();
  TH1D* histo_VG_CMS_MVABTAGBBoundingUp   = new TH1D( Form("histo_VG_%sUp",BTAGBName)  , Form("histo_VG_%sUp",BTAGBName)  , nBinMVA, xbins); histo_VG_CMS_MVABTAGBBoundingUp  ->Sumw2();
  TH1D* histo_WZ_CMS_MVABTAGBBoundingUp   = new TH1D( Form("histo_WZ_%sUp",BTAGBName)  , Form("histo_WZ_%sUp",BTAGBName)  , nBinMVA, xbins); histo_WZ_CMS_MVABTAGBBoundingUp  ->Sumw2();
  TH1D* histo_ZZ_CMS_MVABTAGBBoundingUp   = new TH1D( Form("histo_ZZ_%sUp",BTAGBName)  , Form("histo_ZZ_%sUp",BTAGBName)  , nBinMVA, xbins); histo_ZZ_CMS_MVABTAGBBoundingUp  ->Sumw2();
  TH1D* histo_VVV_CMS_MVABTAGBBoundingUp  = new TH1D( Form("histo_VVV_%sUp",BTAGBName)  , Form("histo_VVV_%sUp",BTAGBName)  , nBinMVA, xbins); histo_VVV_CMS_MVABTAGBBoundingUp  ->Sumw2();
  TH1D* histo_Higgs_CMS_MVABTAGBBoundingUp= new TH1D( Form("histo_Higgs_%sUp",BTAGBName)  , Form("histo_Higgs_%sUp",BTAGBName)  , nBinMVA, xbins); histo_Higgs_CMS_MVABTAGBBoundingUp  ->Sumw2();
  TH1D* histo_ZH_CMS_MVABTAGBBoundingUp   = new TH1D( Form("histo_ZH_%sUp",BTAGBName)  , Form("histo_ZH_%sUp",BTAGBName)  , nBinMVA, xbins); histo_ZH_CMS_MVABTAGBBoundingUp  ->Sumw2();
  TH1D* histo_EM_CMS_MVABTAGBBoundingDown   = new TH1D( Form("histo_EM_%sDown",BTAGBName)  , Form("histo_EM_%sDown",BTAGBName)  , nBinMVA, xbins); histo_EM_CMS_MVABTAGBBoundingDown  ->Sumw2();
  TH1D* histo_VG_CMS_MVABTAGBBoundingDown   = new TH1D( Form("histo_VG_%sDown",BTAGBName)  , Form("histo_VG_%sDown",BTAGBName)  , nBinMVA, xbins); histo_VG_CMS_MVABTAGBBoundingDown  ->Sumw2();
  TH1D* histo_WZ_CMS_MVABTAGBBoundingDown   = new TH1D( Form("histo_WZ_%sDown",BTAGBName)  , Form("histo_WZ_%sDown",BTAGBName)  , nBinMVA, xbins); histo_WZ_CMS_MVABTAGBBoundingDown  ->Sumw2();
  TH1D* histo_ZZ_CMS_MVABTAGBBoundingDown   = new TH1D( Form("histo_ZZ_%sDown",BTAGBName)  , Form("histo_ZZ_%sDown",BTAGBName)  , nBinMVA, xbins); histo_ZZ_CMS_MVABTAGBBoundingDown  ->Sumw2();
  TH1D* histo_VVV_CMS_MVABTAGBBoundingDown  = new TH1D( Form("histo_VVV_%sDown",BTAGBName)  , Form("histo_VVV_%sDown",BTAGBName)  , nBinMVA, xbins); histo_VVV_CMS_MVABTAGBBoundingDown  ->Sumw2();
  TH1D* histo_Higgs_CMS_MVABTAGBBoundingDown= new TH1D( Form("histo_Higgs_%sDown",BTAGBName)  , Form("histo_Higgs_%sDown",BTAGBName)  , nBinMVA, xbins); histo_Higgs_CMS_MVABTAGBBoundingDown  ->Sumw2();
  TH1D* histo_ZH_CMS_MVABTAGBBoundingDown   = new TH1D( Form("histo_ZH_%sDown",BTAGBName)  , Form("histo_ZH_%sDown",BTAGBName)  , nBinMVA, xbins); histo_ZH_CMS_MVABTAGBBoundingDown  ->Sumw2();

  TH1D* histo_EM_CMS_MVABTAGLBoundingUp   = new TH1D( Form("histo_EM_%sUp",BTAGLName)  , Form("histo_EM_%sUp",BTAGLName)  , nBinMVA, xbins); histo_EM_CMS_MVABTAGLBoundingUp  ->Sumw2();
  TH1D* histo_VG_CMS_MVABTAGLBoundingUp   = new TH1D( Form("histo_VG_%sUp",BTAGLName)  , Form("histo_VG_%sUp",BTAGLName)  , nBinMVA, xbins); histo_VG_CMS_MVABTAGLBoundingUp  ->Sumw2();
  TH1D* histo_WZ_CMS_MVABTAGLBoundingUp   = new TH1D( Form("histo_WZ_%sUp",BTAGLName)  , Form("histo_WZ_%sUp",BTAGLName)  , nBinMVA, xbins); histo_WZ_CMS_MVABTAGLBoundingUp  ->Sumw2();
  TH1D* histo_ZZ_CMS_MVABTAGLBoundingUp   = new TH1D( Form("histo_ZZ_%sUp",BTAGLName)  , Form("histo_ZZ_%sUp",BTAGLName)  , nBinMVA, xbins); histo_ZZ_CMS_MVABTAGLBoundingUp  ->Sumw2();
  TH1D* histo_VVV_CMS_MVABTAGLBoundingUp  = new TH1D( Form("histo_VVV_%sUp",BTAGLName)  , Form("histo_VVV_%sUp",BTAGLName)  , nBinMVA, xbins); histo_VVV_CMS_MVABTAGLBoundingUp  ->Sumw2();
  TH1D* histo_Higgs_CMS_MVABTAGLBoundingUp= new TH1D( Form("histo_Higgs_%sUp",BTAGLName)  , Form("histo_Higgs_%sUp",BTAGLName)  , nBinMVA, xbins); histo_Higgs_CMS_MVABTAGLBoundingUp  ->Sumw2();
  TH1D* histo_ZH_CMS_MVABTAGLBoundingUp   = new TH1D( Form("histo_ZH_%sUp",BTAGLName)  , Form("histo_ZH_%sUp",BTAGLName)  , nBinMVA, xbins); histo_ZH_CMS_MVABTAGLBoundingUp  ->Sumw2();
  TH1D* histo_EM_CMS_MVABTAGLBoundingDown   = new TH1D( Form("histo_EM_%sDown",BTAGLName)  , Form("histo_EM_%sDown",BTAGLName)  , nBinMVA, xbins); histo_EM_CMS_MVABTAGLBoundingDown  ->Sumw2();
  TH1D* histo_VG_CMS_MVABTAGLBoundingDown   = new TH1D( Form("histo_VG_%sDown",BTAGLName)  , Form("histo_VG_%sDown",BTAGLName)  , nBinMVA, xbins); histo_VG_CMS_MVABTAGLBoundingDown  ->Sumw2();
  TH1D* histo_WZ_CMS_MVABTAGLBoundingDown   = new TH1D( Form("histo_WZ_%sDown",BTAGLName)  , Form("histo_WZ_%sDown",BTAGLName)  , nBinMVA, xbins); histo_WZ_CMS_MVABTAGLBoundingDown  ->Sumw2();
  TH1D* histo_ZZ_CMS_MVABTAGLBoundingDown   = new TH1D( Form("histo_ZZ_%sDown",BTAGLName)  , Form("histo_ZZ_%sDown",BTAGLName)  , nBinMVA, xbins); histo_ZZ_CMS_MVABTAGLBoundingDown  ->Sumw2();
  TH1D* histo_VVV_CMS_MVABTAGLBoundingDown  = new TH1D( Form("histo_VVV_%sDown",BTAGLName)  , Form("histo_VVV_%sDown",BTAGLName)  , nBinMVA, xbins); histo_VVV_CMS_MVABTAGLBoundingDown  ->Sumw2();
  TH1D* histo_Higgs_CMS_MVABTAGLBoundingDown= new TH1D( Form("histo_Higgs_%sDown",BTAGLName)  , Form("histo_Higgs_%sDown",BTAGLName)  , nBinMVA, xbins); histo_Higgs_CMS_MVABTAGLBoundingDown  ->Sumw2();
  TH1D* histo_ZH_CMS_MVABTAGLBoundingDown   = new TH1D( Form("histo_ZH_%sDown",BTAGLName)  , Form("histo_ZH_%sDown",BTAGLName)  , nBinMVA, xbins); histo_ZH_CMS_MVABTAGLBoundingDown  ->Sumw2();

  TH1D* histo_WZ_CMS_EWKWZCorrUp    	    = new TH1D( Form("histo_WZ_EWKWZCorrUp")  , Form("histo_WZ_EWKWZCorrUp")  , nBinMVA, xbins); histo_WZ_CMS_EWKWZCorrUp  ->Sumw2();
  TH1D* histo_WZ_CMS_EWKWZCorrDown          = new TH1D( Form("histo_WZ_EWKWZCorrDown"), Form("histo_WZ_EWKWZCorrDown"), nBinMVA, xbins); histo_WZ_CMS_EWKWZCorrDown->Sumw2();
  TH1D* histo_ZZ_CMS_EWKqqZZCorrUp          = new TH1D( Form("histo_ZZ_EWKqqZZCorrUp")  , Form("histo_ZZ_EWKqqZZCorrUp")  , nBinMVA, xbins); histo_ZZ_CMS_EWKqqZZCorrUp  ->Sumw2();
  TH1D* histo_ZZ_CMS_EWKqqZZCorrDown        = new TH1D( Form("histo_ZZ_EWKqqZZCorrDown"), Form("histo_ZZ_EWKqqZZCorrDown"), nBinMVA, xbins); histo_ZZ_CMS_EWKqqZZCorrDown->Sumw2();
  TH1D* histo_ZZ_CMS_ggZZCorrUp             = new TH1D( Form("histo_ZZ_ggZZCorrUp")  , Form("histo_ZZ_ggZZCorrUp")  , nBinMVA, xbins); histo_ZZ_CMS_ggZZCorrUp  ->Sumw2();
  TH1D* histo_ZZ_CMS_ggZZCorrDown           = new TH1D( Form("histo_ZZ_ggZZCorrDown"), Form("histo_ZZ_ggZZCorrDown"), nBinMVA, xbins); histo_ZZ_CMS_ggZZCorrDown->Sumw2();

  //*******************************************************
  // Chain Loop
  //*******************************************************
  for(UInt_t ifile=0; ifile<infileName_.size(); ifile++) {
    printf("sampleNames(%d): %s\n",ifile,infileName_[ifile].Data());
    TFile *the_input_file = TFile::Open(infileName_[ifile].Data());
    TTree *the_input_tree = (TTree*)the_input_file->FindObjectAny("events");
    
    pandaFlat thePandaFlat(the_input_tree);
    double theMCPrescale = 1.0; if(infileCat_[ifile] != 0) theMCPrescale = mcPrescale;
    Long64_t nentries = thePandaFlat.fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = thePandaFlat.LoadTree(jentry);
      if (ientry < 0) break;
      nb = thePandaFlat.fChain->GetEntry(jentry);   nbytes += nb;
      if (jentry%1000000 == 0) printf("--- reading event %8lld (%8lld) of %8lld\n",jentry,ientry,nentries);
      if (infileCat_[ifile] != 0 && jentry%(int)theMCPrescale != 0) continue;

      if(infileCat_[ifile] == 0 && ((period == 1 && thePandaFlat.runNumber > 278802) || (period == 2 && thePandaFlat.runNumber <= 278802))) continue;

      bool passTrigger = (thePandaFlat.trigger & (1<<kEMuTrig)) != 0       || (thePandaFlat.trigger & (1<<kDoubleMuTrig)) != 0  ||
                         (thePandaFlat.trigger & (1<<kSingleMuTrig)) != 0  || (thePandaFlat.trigger & (1<<kDoubleEleTrig)) != 0 ||
                         (thePandaFlat.trigger & (1<<kSingleEleTrig)) != 0;
      if(passTrigger == false) continue;

      if(thePandaFlat.nLooseLep < 2 || thePandaFlat.nLooseLep > 4) continue;

      vector<float>  looseLepPt,looseLepEta,looseLepPhi;
      vector<int> looseLepSelBit,looseLepPdgId;
      int ptSelCuts[3] = {0,0,0};
      for(int i=0; i<thePandaFlat.nLooseMuon; i++){
        looseLepPt.push_back(thePandaFlat.muonPt[i]);
        looseLepEta.push_back(thePandaFlat.muonEta[i]);
        looseLepPhi.push_back(thePandaFlat.muonPhi[i]);
        looseLepSelBit.push_back(thePandaFlat.muonSelBit[i]);
        looseLepPdgId.push_back(thePandaFlat.muonPdgId[i]);
	if(thePandaFlat.muonPt[i] > 25) ptSelCuts[0]++;
	if(thePandaFlat.muonPt[i] > 20) ptSelCuts[1]++;
	if(thePandaFlat.muonPt[i] > 10) ptSelCuts[2]++;
      }
      for(int i=0; i<thePandaFlat.nLooseElectron; i++){
        looseLepPt.push_back(thePandaFlat.electronPt[i]);
        looseLepEta.push_back(thePandaFlat.electronEta[i]);
        looseLepPhi.push_back(thePandaFlat.electronPhi[i]);
        looseLepSelBit.push_back(thePandaFlat.electronSelBit[i]);
        looseLepPdgId.push_back(thePandaFlat.electronPdgId[i]);
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
      if(theCategory != 0 && theCategory != 2 && isNotMCFake == false && usePureMC == false) continue;

      vector<TLorentzVector> vLoose;
      vector<int> idLep;
      bool passLooseLepId = true;
      int qTot = 0;
      unsigned int countLeptonTight = 0;
      for(int i=0; i<thePandaFlat.nLooseLep; i++) {
        idLep.push_back(0);
        if((looseLepSelBit[i] & kMedium) == kMedium) idLep[i] = 1;
	countLeptonTight = countLeptonTight + (idLep[i] > 0);

        double thePDGMass = mass_mu;
        if(abs(looseLepPdgId[i])==11) thePDGMass = mass_el;
	TLorentzVector vLepTemp; vLepTemp.SetPtEtaPhiM(looseLepPt[i],looseLepEta[i],looseLepPhi[i],thePDGMass);
        vLoose.push_back(vLepTemp);

	qTot = qTot + abs(looseLepPdgId[i])/looseLepPdgId[i];

        passLooseLepId = passLooseLepId && ((looseLepSelBit[i] & kFake) == kFake);
      }
      if(passLooseLepId == false) continue;
      if(usePureMC == true && countLeptonTight != idLep.size()) continue;

      int lepType = -1;
      if     (thePandaFlat.nLooseLep == 2){
        if     (abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13) lepType = 0;
        else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11) lepType = 1;
        else  lepType = 2;
      }
      else if(thePandaFlat.nLooseLep == 3){
        if     (abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13 && abs(looseLepPdgId[2])==13) lepType = 0;
        else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11 && abs(looseLepPdgId[2])==11) lepType = 3;
        else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[1])==11) lepType = 1;
        else if(abs(looseLepPdgId[0])==11 && abs(looseLepPdgId[2])==11) lepType = 1;
        else if(abs(looseLepPdgId[1])==11 && abs(looseLepPdgId[2])==11) lepType = 1;
        else if(abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[1])==13) lepType = 2;
        else if(abs(looseLepPdgId[0])==13 && abs(looseLepPdgId[2])==13) lepType = 2;
        else if(abs(looseLepPdgId[1])==13 && abs(looseLepPdgId[2])==13) lepType = 2;
        else {printf("Impossible dilepton combination: %d %d %d\n",looseLepPdgId[0],looseLepPdgId[1],looseLepPdgId[2]); continue;}
      }
      else if(thePandaFlat.nLooseLep == 4){
        int nmu = (abs(looseLepPdgId[0])==13) + (abs(looseLepPdgId[1])==13) + (abs(looseLepPdgId[2])==13) + (abs(looseLepPdgId[3])==13);
        int nel = (abs(looseLepPdgId[0])==11) + (abs(looseLepPdgId[1])==11) + (abs(looseLepPdgId[2])==11) + (abs(looseLepPdgId[3])==11);
        if     (nmu == 4 && nel == 0) lepType = 0;
        else if(nmu == 0 && nel == 4) lepType = 1;
        else if(nmu == 2 && nel == 2) lepType = 2;
        else if(nmu == 3 && nel == 1) lepType = 3;
        else if(nmu == 1 && nel == 3) lepType = 3;
        else {printf("Impossible dilepton combination: %d %d %d %d\n",looseLepPdgId[0],looseLepPdgId[1],looseLepPdgId[2],looseLepPdgId[3]); continue;}
      }

      TLorentzVector vMET,vTrkMet;
      vMET.SetPtEtaPhiM(thePandaFlat.pfmet,0.0,thePandaFlat.pfmetphi,0.0);
      vTrkMet.SetPtEtaPhiM(thePandaFlat.trkmet,0.0,thePandaFlat.trkmetphi,0.0);

      double dPhiLepMETMin = 999; double dPhiLepTrackMETMin = 999;
      for(unsigned int i=0; i<vLoose.size(); i++){
        if(dPhiLepMETMin      > TMath::Abs(vLoose[i].DeltaPhi(vMET))   ) dPhiLepMETMin      = TMath::Abs(vLoose[i].DeltaPhi(vMET));
	if(dPhiLepTrackMETMin > TMath::Abs(vLoose[i].DeltaPhi(vTrkMet))) dPhiLepTrackMETMin = TMath::Abs(vLoose[i].DeltaPhi(vTrkMet));
      }

      double PMET[1] = {vMET.Pt()};
      double PTrackMET[1] = {vTrkMet.Pt()};
      if(dPhiLepMETMin < TMath::Pi()/2) {PMET[0] = PMET[0] * sin(dPhiLepMETMin);}
      if(dPhiLepTrackMETMin < TMath::Pi()/2) {PTrackMET[0] = PTrackMET[0] * sin(dPhiLepTrackMETMin);}
      double minPMET[1] = {TMath::Min(PMET[0],PTrackMET[0])};

      bool passPhoSel = thePandaFlat.loosePho1Pt > 25 && TMath::Abs(thePandaFlat.loosePho1Eta) < 2.5
             && (thePandaFlat.loosePho1SelBit & pMedium) == pMedium 
	     && (thePandaFlat.loosePho1SelBit & pCsafeVeto) == pCsafeVeto 
	     && (thePandaFlat.loosePho1SelBit & pPixelVeto) == pPixelVeto;
      TLorentzVector vPhoton;
      vPhoton.SetPtEtaPhiM(thePandaFlat.loosePho1Pt, thePandaFlat.loosePho1Eta, thePandaFlat.loosePho1Phi, 0);

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
	    tightWlnId = (looseLepSelBit[2] & kTight) == kTight && (looseLepSelBit[2] & kDxyz) == kDxyz;
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
	    tightWlnId = (looseLepSelBit[1] & kTight) == kTight && (looseLepSelBit[1] & kDxyz) == kDxyz;
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
	    tightWlnId = (looseLepSelBit[0] & kTight) == kTight && (looseLepSelBit[0] & kDxyz) == kDxyz;
	    whichWln = 0;
	  }
	}
	if(whichWln >= 0 && tightWlnId == true) idLep[whichWln] = 2;
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

      int theMinSelType = -1;
      TLorentzVector theG;
      if     (passPhoSel == true  && vLoose.size() == 2 && TMath::Abs(qTot) == 0){
        theMinSelType = 0;
        theG = vPhoton;
      }
      else if(passPhoSel == false && vLoose.size() == 3 && whichWln >= 0 && tightWlnId == true && TMath::Abs(qTot) == 1){       
        theMinSelType = 1;
        theG = vLoose[whichWln]; 
      }
      else if(passPhoSel == true  && vLoose.size() == 3 && whichWln >= 0 && tightWlnId == true && TMath::Abs(qTot) == 1){       
        theMinSelType = 2;
        vMET.SetPx(vMET.Px()+vLoose[whichWln].Px());
        vMET.SetPy(vMET.Py()+vLoose[whichWln].Px());
        theG = vPhoton;
      }
      else if(passPhoSel == false && vLoose.size() == 4 && vZ2l1.Pt() > 0 && vZ2l2.Pt() > 0 && TMath::Abs((vZ2l1 + vZ2l2).M()-91.1876) < 15.0 && TMath::Abs(qTot) == 0){     
        theMinSelType = 3;
        theG = vZ2l1 + vZ2l2;
      }

      if(theMinSelType == -1) continue;

      double dPhiJetMET = -1.0;
      if(thePandaFlat.jot1Pt > 30) {
        TLorentzVector vJetTemp;
        vJetTemp.SetPtEtaPhiM(thePandaFlat.jot1Pt,thePandaFlat.jot1Eta,thePandaFlat.jot1Phi,0.0);
        dPhiJetMET = TMath::Abs(vJetTemp.DeltaPhi(vMET));
      }

      double dPhiGMET = 0;
      double mTGMET = 0;
      TLorentzVector dilep = vZ1l1+vZ1l2;
      TLorentzVector dilepG = vZ1l1+vZ1l2;
      if(theMinSelType >= 0){
        dilepG = dilepG + theG;
	dPhiGMET = TMath::Abs(theG.DeltaPhi(vMET));
        mTGMET = TMath::Sqrt(2.0*theG.Pt()*vMET.Pt()*(1.0 - cos(dPhiGMET)));
      }

      double dPhiDiLepGMET = TMath::Abs(dilepG.DeltaPhi(vMET));
      bool passZMass = mllmin > 4.0 && TMath::Abs(mllZ-91.1876) < 15.0;
      bool passZMassSB = mllZ > 110 && mllZ < 200;
      bool passMET    = vMET.Pt() > 100;
      bool passMETMin = vMET.Pt() > 60;
      bool passPTLL   = dilep.Pt() > 60;

      double ptFracG = TMath::Abs(dilepG.Pt()-vMET.Pt())/dilep.Pt();
      bool passPTFracG   = ptFracG < 0.4;
      bool passDPhiZGMET = dPhiDiLepGMET > 2.5;
      bool passNjets = thePandaFlat.nJot <= 2;
      bool passNjetsUp = thePandaFlat.nJot_jesUp <= 2;
      bool passNjetsDown = thePandaFlat.nJot_jesDown <= 2;

      bool passBtagVeto = thePandaFlat.jetNMBtags == 0;
      double dphill = TMath::Abs(vZ1l1.DeltaPhi(vZ1l2));
      double detall = TMath::Abs(vZ1l1.Eta()-vZ1l2.Eta());
      double drll = sqrt(dphill*dphill+detall*detall);

      bool passDPhiJetMET   = dPhiJetMET == -1 || dPhiJetMET >= 0.5;
      bool passTauVeto      = thePandaFlat.nTau == 0;
      bool passMT           = mTGMET < 175.0;

      if(isDEBUG && vLoose.size() == 4) printf("DEBUG %d %d %d %d %d %d %d %d %d %d %d | %f %f\n",theMinSelType,passZMass,passNjets,passMET,passPTFracG,passDPhiZGMET,passBtagVeto,passPTLL,passDPhiJetMET,passTauVeto,passMT,mllmin,TMath::Abs(mllZ-91.1876));

      bool passAllCuts[nSelTypes] = {                   
     theMinSelType == 0 && passZMass   && passNjets && passMET    && passPTFracG && passDPhiZGMET &&  passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT,   // ZHGSEL
     theMinSelType == 0 && passZMass   && passNjets && passMET    && passPTFracG && passDPhiZGMET && !passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT,   // BTAGSEL
     theMinSelType == 0 && passZMass   &&              passMET    &&                                                  passPTLL &&                   passTauVeto && passMT,   // ZLGSEL
     theMinSelType == 1 && passZMass   && passNjets && passMET    && passPTFracG && passDPhiZGMET &&  passBtagVeto && passPTLL && passDPhiJetMET &&                passMT,   // WZSEL
     theMinSelType == 2 && passZMass   && passNjets && passMET    && passPTFracG && passDPhiZGMET &&  passBtagVeto && passPTLL && passDPhiJetMET &&	           passMT,   // WZGSEL
     theMinSelType == 3 && passZMass   && passNjets && passMETMin && passPTFracG && passDPhiZGMET &&  passBtagVeto && passPTLL && passDPhiJetMET &&  	           passMT,   // ZZSEL
     theMinSelType == 0 && passZMassSB && passNjets && passMET    && passPTFracG && passDPhiZGMET &&  passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT    // WWSEL
                                    };

      bool passNMinusOne[10] = {
     		  passNjets && passMET && passPTFracG && passDPhiZGMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT,
     passZMass &&	       passMET && passPTFracG && passDPhiZGMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT,
     passZMass && passNjets &&  	  passPTFracG && passDPhiZGMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT,
     passZMass && passNjets && passMET &&		 passDPhiZGMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT,
     passZMass && passNjets && passMET && passPTFracG &&		  passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT,
     passZMass && passNjets && passMET && passPTFracG && passDPhiZGMET &&		  passPTLL && passDPhiJetMET && passTauVeto && passMT,
     passZMass && passNjets && passMET && passPTFracG && passDPhiZGMET && passBtagVeto &&	      passDPhiJetMET && passTauVeto && passMT,
     passZMass && passNjets && passMET && passPTFracG && passDPhiZGMET && passBtagVeto && passPTLL &&			passTauVeto && passMT,
     passZMass && passNjets && passMET && passPTFracG && passDPhiZGMET && passBtagVeto && passPTLL && passDPhiJetMET && 	       passMT,
     passZMass && passNjets && passMET && passPTFracG && passDPhiZGMET && passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto
                                    };

      bool passSystCuts[nSystTypes] = {                   
     theMinSelType == 0 && passZMass   && passNjetsUp   && passMET    && passPTFracG && passDPhiZGMET &&  passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT,
     theMinSelType == 0 && passZMass   && passNjetsDown && passMET    && passPTFracG && passDPhiZGMET &&  passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT,
     theMinSelType == 0 && passZMass   && passNjets     && passMET    && passPTFracG && passDPhiZGMET &&  passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT,
     theMinSelType == 0 && passZMass   && passNjets     && passMET    && passPTFracG && passDPhiZGMET &&  passBtagVeto && passPTLL && passDPhiJetMET && passTauVeto && passMT
                                    };
     for(int i=0; i<10; i++) passNMinusOne[i] = mllmin > 4.0 && theMinSelType == 0 && lepType != 2 && passNMinusOne[i];

      double totalWeight = 1.0; double puWeight = 1.0; double puWeightUp = 1.0; double puWeightDown = 1.0;
      if(theCategory != 0){
        puWeight     = nPUScaleFactor(fhDPU,    thePandaFlat.pu);
        puWeightUp   = nPUScaleFactor(fhDPUUp,  thePandaFlat.pu);
        puWeightDown = nPUScaleFactor(fhDPUDown,thePandaFlat.pu);
        double the_eta_sf[4] = {1.0, 1.0, 1.0, 1.0};
        double sfWeightLepEff[4] = {1.0, 1.0, 1.0, 1.0};
	for(unsigned int i=0; i<vLoose.size(); i++){
          if(abs(looseLepPdgId[i])==13){
            double etal = looseLepEta[i]; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
            int binEta = scalefactors_Muon_Eta->GetXaxis()->FindFixBin(etal);
            the_eta_sf[i] = scalefactors_Muon_Eta->GetBinContent(binEta);
          } else {
            double etal = looseLepEta[i]; if(etal >= 2.5) etal = 2.4999; else if(etal <= -2.5) etal = -2.4999;
            int binEta = scalefactors_Electron_Eta->GetXaxis()->FindFixBin(etal);
            the_eta_sf[i] = scalefactors_Electron_Eta->GetBinContent(binEta);
          }        
          if(abs(looseLepPdgId[i])==13){
            double etal = looseLepEta[i]; if(etal >= 2.4) etal = 2.3999; else if(etal <= -2.4) etal = -2.3999;
            int binXT   = scalefactors_Medium_Muon->GetXaxis()->FindFixBin(etal);
            int binYT_c = scalefactors_Medium_Muon->GetYaxis()->FindFixBin(TMath::Min((double)looseLepPt[i],getMaxPtForSFs[0]));
	    sfWeightLepEff[i] = scalefactors_Medium_Muon->GetBinContent(binXT,binYT_c);
          } else {
            double etal = looseLepEta[i]; if(etal >= 2.5) etal = 2.4999; else if(etal <= -2.5) etal = -2.4999;
            int binXT   = scalefactors_Medium_Electron->GetXaxis()->FindFixBin(etal);
            int binYT_c = scalefactors_Medium_Electron->GetYaxis()->FindFixBin(TMath::Min((double)looseLepPt[i],getMaxPtForSFs[1]));
	    sfWeightLepEff[i] = scalefactors_Medium_Electron->GetBinContent(binXT,binYT_c);
          }
        }

        totalWeight = thePandaFlat.normalizedWeight * lumi * puWeight * 
	  the_eta_sf[0] * the_eta_sf[1] * the_eta_sf[2] * the_eta_sf[3] * 
	  sfWeightLepEff[0] * sfWeightLepEff[1] * sfWeightLepEff[2] * sfWeightLepEff[3] * 
	  thePandaFlat.sf_btag0 * theMCPrescale;

        if     (infileCat_[ifile] == 3)                                                totalWeight = totalWeight * thePandaFlat.sf_wz;
	else if(infileCat_[ifile] == 4 && infileName_[ifile].Contains("qqZZ") == true) totalWeight = totalWeight * thePandaFlat.sf_zz;

	if(passPhoSel == true) {
          double photonSF = 1.0;
          if     (thePandaFlat.looseGenPho1PdgId == 1) {
            photonSF = electronToPhotonSF(vPhoton.Pt());
	  }
          else if(thePandaFlat.looseGenPho1PdgId == 3) {
            photonSF = effhDPhotonScaleFactor(vPhoton.Pt(), vPhoton.Eta(), "medium", fhDPhotonSF, fhDElectronVetoSF);
	  }
	  totalWeight = totalWeight * photonSF;
	}

      }

      if(usePureMC == false && countLeptonTight != idLep.size()){
        double fakeSF = 1.0;
        for(unsigned int nl=0; nl<idLep.size(); nl++){
          if(idLep[nl] != 0) continue;
          bool applyTight = false;
          if(whichWln == (int)nl) applyTight = true;
          if(nl == 0) fakeSF = fakeSF * fakeRateFactor(TMath::Min((double)looseLepPt[0],44.999),TMath::Abs(looseLepEta[0]),TMath::Abs(looseLepPdgId[0]),applyTight,histoFakeEffSelMediumEtaPt_m,histoFakeEffSelMediumEtaPt_e,histoFakeEffSelTightEtaPt_m,histoFakeEffSelTightEtaPt_e);
          if(nl == 1) fakeSF = fakeSF * fakeRateFactor(TMath::Min((double)looseLepPt[1],44.999),TMath::Abs(looseLepEta[1]),TMath::Abs(looseLepPdgId[1]),applyTight,histoFakeEffSelMediumEtaPt_m,histoFakeEffSelMediumEtaPt_e,histoFakeEffSelTightEtaPt_m,histoFakeEffSelTightEtaPt_e);
          if(nl == 2) fakeSF = fakeSF * fakeRateFactor(TMath::Min((double)looseLepPt[2],44.999),TMath::Abs(looseLepEta[2]),TMath::Abs(looseLepPdgId[2]),applyTight,histoFakeEffSelMediumEtaPt_m,histoFakeEffSelMediumEtaPt_e,histoFakeEffSelTightEtaPt_m,histoFakeEffSelTightEtaPt_e);
          if(nl == 3) fakeSF = fakeSF * fakeRateFactor(TMath::Min((double)looseLepPt[3],44.999),TMath::Abs(looseLepEta[3]),TMath::Abs(looseLepPdgId[3]),applyTight,histoFakeEffSelMediumEtaPt_m,histoFakeEffSelMediumEtaPt_e,histoFakeEffSelTightEtaPt_m,histoFakeEffSelTightEtaPt_e);
          theCategory = 1;
        }
        if     (infileCat_[ifile] != 0 && countLeptonTight == idLep.size()-4) fakeSF = +1.0 * fakeSF; // fourth fake, MC
        else if(infileCat_[ifile] != 0 && countLeptonTight == idLep.size()-3) fakeSF = -1.0 * fakeSF; // triple fake, MC
        else if(infileCat_[ifile] != 0 && countLeptonTight == idLep.size()-2) fakeSF = +1.0 * fakeSF; // double fake, MC
        else if(infileCat_[ifile] != 0 && countLeptonTight == idLep.size()-1) fakeSF = -1.0 * fakeSF; // single fake, MC
        else if(infileCat_[ifile] == 0 && countLeptonTight == idLep.size()-4) fakeSF = -1.0 * fakeSF; // fourth fake, data
        else if(infileCat_[ifile] == 0 && countLeptonTight == idLep.size()-3) fakeSF = +1.0 * fakeSF; // triple fake, data
        else if(infileCat_[ifile] == 0 && countLeptonTight == idLep.size()-2) fakeSF = -1.0 * fakeSF; // double fake, data
        else if(infileCat_[ifile] == 0 && countLeptonTight == idLep.size()-1) fakeSF = +1.0 * fakeSF; // single fake, data
        else printf("IMPOSSIBLE FAKE OPTION\n");
        totalWeight = totalWeight * fakeSF;
      }

      if(passAllCuts[ZHGSEL])histo[lepType+  0][theCategory]->Fill(TMath::Min(mTGMET,199.999),totalWeight);
      if(passAllCuts[BTAGSEL])histo[lepType+ 3][theCategory]->Fill(TMath::Min(mTGMET,199.999),totalWeight);
      if(passAllCuts[ZLGSEL])histo[lepType+  6][theCategory]->Fill(TMath::Min(mTGMET,199.999),totalWeight);
      if(passAllCuts[WZSEL])histo[lepType+   9][theCategory]->Fill(TMath::Min(mTGMET,199.999),totalWeight);
      if(passAllCuts[WZGSEL])histo[lepType+ 13][theCategory]->Fill(TMath::Min(mTGMET,199.999),totalWeight);
      if(passAllCuts[ZZSEL])histo[lepType+  17][theCategory]->Fill(TMath::Min(mTGMET,199.999),totalWeight);
      if(passAllCuts[WWSEL])histo[lepType+  21][theCategory]->Fill(TMath::Min(mTGMET,199.999),totalWeight);
      if(passNMinusOne[ 0])  histo[24][theCategory]->Fill(TMath::Min(TMath::Abs(mllZ-91.1876),99.999),totalWeight);
      if(passNMinusOne[ 1])  histo[25][theCategory]->Fill(TMath::Min((double)thePandaFlat.nJot,4.4999),totalWeight);
      if(passNMinusOne[ 2])  histo[26][theCategory]->Fill(TMath::Min(vMET.Pt(),199.999),totalWeight);
      if(passNMinusOne[ 3])  histo[27][theCategory]->Fill(TMath::Min(ptFracG,1.999),totalWeight);
      if(passNMinusOne[ 4])  histo[28][theCategory]->Fill(dPhiDiLepGMET,totalWeight);
      if(passNMinusOne[ 5])  histo[29][theCategory]->Fill(TMath::Min((double)thePandaFlat.jetNMBtags,3.499),totalWeight);
      if(passNMinusOne[ 6])  histo[30][theCategory]->Fill(TMath::Min(dilep.Pt(),199.999),totalWeight);
      if(passNMinusOne[ 7])  histo[31][theCategory]->Fill(dPhiJetMET,totalWeight);
      if(passNMinusOne[ 8])  histo[32][theCategory]->Fill(TMath::Min((double)thePandaFlat.nTau,3.499),totalWeight);
      if(passNMinusOne[ 9])  histo[33][theCategory]->Fill(TMath::Min(mTGMET,399.999),totalWeight);
      if(passAllCuts[ZHGSEL] && lepType != 2) histo[34][theCategory]->Fill((double)((thePandaFlat.loosePho1SelBit & pTrkVeto) == pTrkVeto),totalWeight);

      if(lepType != 2){
        double MVAVar = TMath::Min(mTGMET,xbins[nBinMVA]-0.0001);

        // Avoid QCD scale weights that are anomalous high
        double maxQCDscale = (TMath::Abs(thePandaFlat.scale[0])+TMath::Abs(thePandaFlat.scale[1])+TMath::Abs(thePandaFlat.scale[2])+
	                      TMath::Abs(thePandaFlat.scale[3])+TMath::Abs(thePandaFlat.scale[4])+TMath::Abs(thePandaFlat.scale[5]))/6.0;
        if(maxQCDscale == 0) maxQCDscale = 1;

        if     (theCategory == 0){
          if(passAllCuts[ZHGSEL] && lepType != 2) histo_Data->Fill(MVAVar,totalWeight);
        }
        else if(theCategory == 1){
	  if(passAllCuts[ZHGSEL]) {
	    histo_EM->Fill(MVAVar,totalWeight);
	    histo_EM_CMS_QCDScaleBounding[0]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[0])/maxQCDscale);
	    histo_EM_CMS_QCDScaleBounding[1]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[1])/maxQCDscale);
	    histo_EM_CMS_QCDScaleBounding[2]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[2])/maxQCDscale);
	    histo_EM_CMS_QCDScaleBounding[3]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[3])/maxQCDscale);
	    histo_EM_CMS_QCDScaleBounding[4]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[4])/maxQCDscale);
	    histo_EM_CMS_QCDScaleBounding[5]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[5])/maxQCDscale);
	    histo_EM_CMS_MVAPDFBoundingUp  ->Fill(MVAVar,totalWeight*thePandaFlat.pdfUp);
	    histo_EM_CMS_MVAPDFBoundingDown->Fill(MVAVar,totalWeight*thePandaFlat.pdfDown);
            if     (lepType == 0) {histo_EM_CMS_MVALepEffMBoundingUp  ->Fill(MVAVar,totalWeight*1.020);histo_EM_CMS_MVALepEffEBoundingUp  ->Fill(MVAVar,totalWeight);}
            else if(lepType == 1) {histo_EM_CMS_MVALepEffEBoundingUp  ->Fill(MVAVar,totalWeight*1.020);histo_EM_CMS_MVALepEffMBoundingUp  ->Fill(MVAVar,totalWeight);}
            if     (lepType == 0) {histo_EM_CMS_MVALepEffMBoundingDown->Fill(MVAVar,totalWeight/1.020);histo_EM_CMS_MVALepEffEBoundingDown->Fill(MVAVar,totalWeight);}
            else if(lepType == 1) {histo_EM_CMS_MVALepEffEBoundingDown->Fill(MVAVar,totalWeight/1.020);histo_EM_CMS_MVALepEffMBoundingDown->Fill(MVAVar,totalWeight);}
            histo_EM_CMS_MVAPUBoundingUp  ->Fill(MVAVar,totalWeight*puWeightUp  /puWeight);
            histo_EM_CMS_MVAPUBoundingDown->Fill(MVAVar,totalWeight*puWeightDown/puWeight);
            histo_EM_CMS_MVABTAGBBoundingUp  ->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0BUp  /thePandaFlat.sf_btag0);
            histo_EM_CMS_MVABTAGBBoundingDown->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0BDown/thePandaFlat.sf_btag0);
            histo_EM_CMS_MVABTAGLBoundingUp  ->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0MUp  /thePandaFlat.sf_btag0);
            histo_EM_CMS_MVABTAGLBoundingDown->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0MDown/thePandaFlat.sf_btag0);
	  }
          if(passSystCuts[JESUP])  histo_EM_CMS_MVAJESBoundingUp  ->Fill(MVAVar,totalWeight);
          if(passSystCuts[JESDOWN])histo_EM_CMS_MVAJESBoundingDown->Fill(MVAVar,totalWeight);
          if(passSystCuts[METUP])  histo_EM_CMS_MVAMETBoundingUp  ->Fill(MVAVar,totalWeight);
          if(passSystCuts[METDOWN])histo_EM_CMS_MVAMETBoundingDown->Fill(MVAVar,totalWeight);
        }
        else if(theCategory == 2){
	  if(passAllCuts[ZHGSEL]) {
	    histo_VG->Fill(MVAVar,totalWeight);
	    histo_VG_CMS_QCDScaleBounding[0]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[0])/maxQCDscale);
	    histo_VG_CMS_QCDScaleBounding[1]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[1])/maxQCDscale);
	    histo_VG_CMS_QCDScaleBounding[2]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[2])/maxQCDscale);
	    histo_VG_CMS_QCDScaleBounding[3]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[3])/maxQCDscale);
	    histo_VG_CMS_QCDScaleBounding[4]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[4])/maxQCDscale);
	    histo_VG_CMS_QCDScaleBounding[5]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[5])/maxQCDscale);
	    histo_VG_CMS_MVAPDFBoundingUp  ->Fill(MVAVar,totalWeight*thePandaFlat.pdfUp);
	    histo_VG_CMS_MVAPDFBoundingDown->Fill(MVAVar,totalWeight*thePandaFlat.pdfDown);
            if     (lepType == 0) {histo_VG_CMS_MVALepEffMBoundingUp  ->Fill(MVAVar,totalWeight*1.020);histo_VG_CMS_MVALepEffEBoundingUp  ->Fill(MVAVar,totalWeight);}
            else if(lepType == 1) {histo_VG_CMS_MVALepEffEBoundingUp  ->Fill(MVAVar,totalWeight*1.020);histo_VG_CMS_MVALepEffMBoundingUp  ->Fill(MVAVar,totalWeight);}
            if     (lepType == 0) {histo_VG_CMS_MVALepEffMBoundingDown->Fill(MVAVar,totalWeight/1.020);histo_VG_CMS_MVALepEffEBoundingDown->Fill(MVAVar,totalWeight);}
            else if(lepType == 1) {histo_VG_CMS_MVALepEffEBoundingDown->Fill(MVAVar,totalWeight/1.020);histo_VG_CMS_MVALepEffMBoundingDown->Fill(MVAVar,totalWeight);}
            histo_VG_CMS_MVAPUBoundingUp  ->Fill(MVAVar,totalWeight*puWeightUp  /puWeight);
            histo_VG_CMS_MVAPUBoundingDown->Fill(MVAVar,totalWeight*puWeightDown/puWeight);
            histo_VG_CMS_MVABTAGBBoundingUp  ->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0BUp  /thePandaFlat.sf_btag0);
            histo_VG_CMS_MVABTAGBBoundingDown->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0BDown/thePandaFlat.sf_btag0);
            histo_VG_CMS_MVABTAGLBoundingUp  ->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0MUp  /thePandaFlat.sf_btag0);
            histo_VG_CMS_MVABTAGLBoundingDown->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0MDown/thePandaFlat.sf_btag0);
	  }
          if(passSystCuts[JESUP])  histo_VG_CMS_MVAJESBoundingUp  ->Fill(MVAVar,totalWeight);
          if(passSystCuts[JESDOWN])histo_VG_CMS_MVAJESBoundingDown->Fill(MVAVar,totalWeight);
          if(passSystCuts[METUP])  histo_VG_CMS_MVAMETBoundingUp  ->Fill(MVAVar,totalWeight);
          if(passSystCuts[METDOWN])histo_VG_CMS_MVAMETBoundingDown->Fill(MVAVar,totalWeight);
        }
        else if(theCategory == 3){
	  if(passAllCuts[ZHGSEL]) {
	    histo_WZ->Fill(MVAVar,totalWeight);
	    histo_WZ_CMS_EWKWZCorrUp  ->Fill(MVAVar,totalWeight*1.02);
	    histo_WZ_CMS_EWKWZCorrDown->Fill(MVAVar,totalWeight/1.02);
	    histo_WZ_CMS_QCDScaleBounding[0]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[0])/maxQCDscale);
	    histo_WZ_CMS_QCDScaleBounding[1]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[1])/maxQCDscale);
	    histo_WZ_CMS_QCDScaleBounding[2]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[2])/maxQCDscale);
	    histo_WZ_CMS_QCDScaleBounding[3]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[3])/maxQCDscale);
	    histo_WZ_CMS_QCDScaleBounding[4]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[4])/maxQCDscale);
	    histo_WZ_CMS_QCDScaleBounding[5]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[5])/maxQCDscale);
	    histo_WZ_CMS_MVAPDFBoundingUp  ->Fill(MVAVar,totalWeight*thePandaFlat.pdfUp);
	    histo_WZ_CMS_MVAPDFBoundingDown->Fill(MVAVar,totalWeight*thePandaFlat.pdfDown);
            if     (lepType == 0) {histo_WZ_CMS_MVALepEffMBoundingUp  ->Fill(MVAVar,totalWeight*1.020);histo_WZ_CMS_MVALepEffEBoundingUp  ->Fill(MVAVar,totalWeight);}
            else if(lepType == 1) {histo_WZ_CMS_MVALepEffEBoundingUp  ->Fill(MVAVar,totalWeight*1.020);histo_WZ_CMS_MVALepEffMBoundingUp  ->Fill(MVAVar,totalWeight);}
            if     (lepType == 0) {histo_WZ_CMS_MVALepEffMBoundingDown->Fill(MVAVar,totalWeight/1.020);histo_WZ_CMS_MVALepEffEBoundingDown->Fill(MVAVar,totalWeight);}
            else if(lepType == 1) {histo_WZ_CMS_MVALepEffEBoundingDown->Fill(MVAVar,totalWeight/1.020);histo_WZ_CMS_MVALepEffMBoundingDown->Fill(MVAVar,totalWeight);}
            histo_WZ_CMS_MVAPUBoundingUp  ->Fill(MVAVar,totalWeight*puWeightUp  /puWeight);
            histo_WZ_CMS_MVAPUBoundingDown->Fill(MVAVar,totalWeight*puWeightDown/puWeight);
            histo_WZ_CMS_MVABTAGBBoundingUp  ->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0BUp  /thePandaFlat.sf_btag0);
            histo_WZ_CMS_MVABTAGBBoundingDown->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0BDown/thePandaFlat.sf_btag0);
            histo_WZ_CMS_MVABTAGLBoundingUp  ->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0MUp  /thePandaFlat.sf_btag0);
            histo_WZ_CMS_MVABTAGLBoundingDown->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0MDown/thePandaFlat.sf_btag0);
	  }
          if(passSystCuts[JESUP])  histo_WZ_CMS_MVAJESBoundingUp  ->Fill(MVAVar,totalWeight);
          if(passSystCuts[JESDOWN])histo_WZ_CMS_MVAJESBoundingDown->Fill(MVAVar,totalWeight);
          if(passSystCuts[METUP])  histo_WZ_CMS_MVAMETBoundingUp  ->Fill(MVAVar,totalWeight);
          if(passSystCuts[METDOWN])histo_WZ_CMS_MVAMETBoundingDown->Fill(MVAVar,totalWeight);
        }
        else if(theCategory == 4){
	  if(passAllCuts[ZHGSEL]) {
	    histo_ZZ->Fill(MVAVar,totalWeight);
	    if(infileName_[ifile].Contains("qqZZ") == true) {
	      histo_ZZ_CMS_EWKqqZZCorrUp  ->Fill(MVAVar,totalWeight*thePandaFlat.sf_zzUnc);
	      histo_ZZ_CMS_EWKqqZZCorrDown->Fill(MVAVar,totalWeight/thePandaFlat.sf_zzUnc);
	      histo_ZZ_CMS_ggZZCorrUp  ->Fill(MVAVar,totalWeight);
	      histo_ZZ_CMS_ggZZCorrDown->Fill(MVAVar,totalWeight);
	    } else {
	      histo_ZZ_CMS_EWKqqZZCorrUp  ->Fill(MVAVar,totalWeight);
	      histo_ZZ_CMS_EWKqqZZCorrDown->Fill(MVAVar,totalWeight);
	      histo_ZZ_CMS_ggZZCorrUp  ->Fill(MVAVar,totalWeight*1.30);
	      histo_ZZ_CMS_ggZZCorrDown->Fill(MVAVar,totalWeight/1.30);
	    }
	    histo_ZZ_CMS_QCDScaleBounding[0]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[0])/maxQCDscale);
	    histo_ZZ_CMS_QCDScaleBounding[1]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[1])/maxQCDscale);
	    histo_ZZ_CMS_QCDScaleBounding[2]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[2])/maxQCDscale);
	    histo_ZZ_CMS_QCDScaleBounding[3]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[3])/maxQCDscale);
	    histo_ZZ_CMS_QCDScaleBounding[4]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[4])/maxQCDscale);
	    histo_ZZ_CMS_QCDScaleBounding[5]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[5])/maxQCDscale);
	    histo_ZZ_CMS_MVAPDFBoundingUp  ->Fill(MVAVar,totalWeight*thePandaFlat.pdfUp);
	    histo_ZZ_CMS_MVAPDFBoundingDown->Fill(MVAVar,totalWeight*thePandaFlat.pdfDown);
            if     (lepType == 0) {histo_ZZ_CMS_MVALepEffMBoundingUp  ->Fill(MVAVar,totalWeight*1.020);histo_ZZ_CMS_MVALepEffEBoundingUp  ->Fill(MVAVar,totalWeight);}
            else if(lepType == 1) {histo_ZZ_CMS_MVALepEffEBoundingUp  ->Fill(MVAVar,totalWeight*1.020);histo_ZZ_CMS_MVALepEffMBoundingUp  ->Fill(MVAVar,totalWeight);}
            if     (lepType == 0) {histo_ZZ_CMS_MVALepEffMBoundingDown->Fill(MVAVar,totalWeight/1.020);histo_ZZ_CMS_MVALepEffEBoundingDown->Fill(MVAVar,totalWeight);}
            else if(lepType == 1) {histo_ZZ_CMS_MVALepEffEBoundingDown->Fill(MVAVar,totalWeight/1.020);histo_ZZ_CMS_MVALepEffMBoundingDown->Fill(MVAVar,totalWeight);}
            histo_ZZ_CMS_MVAPUBoundingUp  ->Fill(MVAVar,totalWeight*puWeightUp  /puWeight);
            histo_ZZ_CMS_MVAPUBoundingDown->Fill(MVAVar,totalWeight*puWeightDown/puWeight);
            histo_ZZ_CMS_MVABTAGBBoundingUp  ->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0BUp  /thePandaFlat.sf_btag0);
            histo_ZZ_CMS_MVABTAGBBoundingDown->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0BDown/thePandaFlat.sf_btag0);
            histo_ZZ_CMS_MVABTAGLBoundingUp  ->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0MUp  /thePandaFlat.sf_btag0);
            histo_ZZ_CMS_MVABTAGLBoundingDown->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0MDown/thePandaFlat.sf_btag0);
	  }
          if(passSystCuts[JESUP])  histo_ZZ_CMS_MVAJESBoundingUp  ->Fill(MVAVar,totalWeight);
          if(passSystCuts[JESDOWN])histo_ZZ_CMS_MVAJESBoundingDown->Fill(MVAVar,totalWeight);
          if(passSystCuts[METUP])  histo_ZZ_CMS_MVAMETBoundingUp  ->Fill(MVAVar,totalWeight);
          if(passSystCuts[METDOWN])histo_ZZ_CMS_MVAMETBoundingDown->Fill(MVAVar,totalWeight);
        }
        else if(theCategory == 5){
	  if(passAllCuts[ZHGSEL]) {
	    histo_VVV->Fill(MVAVar,totalWeight);
	    histo_VVV_CMS_QCDScaleBounding[0]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[0])/maxQCDscale);
	    histo_VVV_CMS_QCDScaleBounding[1]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[1])/maxQCDscale);
	    histo_VVV_CMS_QCDScaleBounding[2]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[2])/maxQCDscale);
	    histo_VVV_CMS_QCDScaleBounding[3]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[3])/maxQCDscale);
	    histo_VVV_CMS_QCDScaleBounding[4]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[4])/maxQCDscale);
	    histo_VVV_CMS_QCDScaleBounding[5]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[5])/maxQCDscale);
	    histo_VVV_CMS_MVAPDFBoundingUp  ->Fill(MVAVar,totalWeight*thePandaFlat.pdfUp);
	    histo_VVV_CMS_MVAPDFBoundingDown->Fill(MVAVar,totalWeight*thePandaFlat.pdfDown);
            if     (lepType == 0) {histo_VVV_CMS_MVALepEffMBoundingUp  ->Fill(MVAVar,totalWeight*1.020);histo_VVV_CMS_MVALepEffEBoundingUp  ->Fill(MVAVar,totalWeight);}
            else if(lepType == 1) {histo_VVV_CMS_MVALepEffEBoundingUp  ->Fill(MVAVar,totalWeight*1.020);histo_VVV_CMS_MVALepEffMBoundingUp  ->Fill(MVAVar,totalWeight);}
            if     (lepType == 0) {histo_VVV_CMS_MVALepEffMBoundingDown->Fill(MVAVar,totalWeight/1.020);histo_VVV_CMS_MVALepEffEBoundingDown->Fill(MVAVar,totalWeight);}
            else if(lepType == 1) {histo_VVV_CMS_MVALepEffEBoundingDown->Fill(MVAVar,totalWeight/1.020);histo_VVV_CMS_MVALepEffMBoundingDown->Fill(MVAVar,totalWeight);}
            histo_VVV_CMS_MVAPUBoundingUp  ->Fill(MVAVar,totalWeight*puWeightUp  /puWeight);
            histo_VVV_CMS_MVAPUBoundingDown->Fill(MVAVar,totalWeight*puWeightDown/puWeight);
            histo_VVV_CMS_MVABTAGBBoundingUp  ->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0BUp  /thePandaFlat.sf_btag0);
            histo_VVV_CMS_MVABTAGBBoundingDown->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0BDown/thePandaFlat.sf_btag0);
            histo_VVV_CMS_MVABTAGLBoundingUp  ->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0MUp  /thePandaFlat.sf_btag0);
            histo_VVV_CMS_MVABTAGLBoundingDown->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0MDown/thePandaFlat.sf_btag0);
	  }
          if(passSystCuts[JESUP])  histo_VVV_CMS_MVAJESBoundingUp  ->Fill(MVAVar,totalWeight);
          if(passSystCuts[JESDOWN])histo_VVV_CMS_MVAJESBoundingDown->Fill(MVAVar,totalWeight);
          if(passSystCuts[METUP])  histo_VVV_CMS_MVAMETBoundingUp  ->Fill(MVAVar,totalWeight);
          if(passSystCuts[METDOWN])histo_VVV_CMS_MVAMETBoundingDown->Fill(MVAVar,totalWeight);
        }
        else if(theCategory == 6){
	  if(passAllCuts[ZHGSEL]) {
	    histo_Higgs->Fill(MVAVar,totalWeight);
	    histo_Higgs_CMS_QCDScaleBounding[0]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[0])/maxQCDscale);
	    histo_Higgs_CMS_QCDScaleBounding[1]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[1])/maxQCDscale);
	    histo_Higgs_CMS_QCDScaleBounding[2]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[2])/maxQCDscale);
	    histo_Higgs_CMS_QCDScaleBounding[3]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[3])/maxQCDscale);
	    histo_Higgs_CMS_QCDScaleBounding[4]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[4])/maxQCDscale);
	    histo_Higgs_CMS_QCDScaleBounding[5]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[5])/maxQCDscale);
	    histo_Higgs_CMS_MVAPDFBoundingUp  ->Fill(MVAVar,totalWeight*thePandaFlat.pdfUp);
	    histo_Higgs_CMS_MVAPDFBoundingDown->Fill(MVAVar,totalWeight*thePandaFlat.pdfDown);
            if     (lepType == 0) {histo_Higgs_CMS_MVALepEffMBoundingUp  ->Fill(MVAVar,totalWeight*1.020);histo_Higgs_CMS_MVALepEffEBoundingUp  ->Fill(MVAVar,totalWeight);}
            else if(lepType == 1) {histo_Higgs_CMS_MVALepEffEBoundingUp  ->Fill(MVAVar,totalWeight*1.020);histo_Higgs_CMS_MVALepEffMBoundingUp  ->Fill(MVAVar,totalWeight);}
            if     (lepType == 0) {histo_Higgs_CMS_MVALepEffMBoundingDown->Fill(MVAVar,totalWeight/1.020);histo_Higgs_CMS_MVALepEffEBoundingDown->Fill(MVAVar,totalWeight);}
            else if(lepType == 1) {histo_Higgs_CMS_MVALepEffEBoundingDown->Fill(MVAVar,totalWeight/1.020);histo_Higgs_CMS_MVALepEffMBoundingDown->Fill(MVAVar,totalWeight);}
            histo_Higgs_CMS_MVAPUBoundingUp  ->Fill(MVAVar,totalWeight*puWeightUp  /puWeight);
            histo_Higgs_CMS_MVAPUBoundingDown->Fill(MVAVar,totalWeight*puWeightDown/puWeight);
            histo_Higgs_CMS_MVABTAGBBoundingUp  ->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0BUp  /thePandaFlat.sf_btag0);
            histo_Higgs_CMS_MVABTAGBBoundingDown->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0BDown/thePandaFlat.sf_btag0);
            histo_Higgs_CMS_MVABTAGLBoundingUp  ->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0MUp  /thePandaFlat.sf_btag0);
            histo_Higgs_CMS_MVABTAGLBoundingDown->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0MDown/thePandaFlat.sf_btag0);
	  }
          if(passSystCuts[JESUP])  histo_Higgs_CMS_MVAJESBoundingUp  ->Fill(MVAVar,totalWeight);
          if(passSystCuts[JESDOWN])histo_Higgs_CMS_MVAJESBoundingDown->Fill(MVAVar,totalWeight);
          if(passSystCuts[METUP])  histo_Higgs_CMS_MVAMETBoundingUp  ->Fill(MVAVar,totalWeight);
          if(passSystCuts[METDOWN])histo_Higgs_CMS_MVAMETBoundingDown->Fill(MVAVar,totalWeight);
        }
        else if(theCategory == 7){
	  if(passAllCuts[ZHGSEL]) {
	    histo_ZH->Fill(MVAVar,totalWeight);
	    histo_ZH_CMS_QCDScaleBounding[0]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[0])/maxQCDscale);
	    histo_ZH_CMS_QCDScaleBounding[1]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[1])/maxQCDscale);
	    histo_ZH_CMS_QCDScaleBounding[2]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[2])/maxQCDscale);
	    histo_ZH_CMS_QCDScaleBounding[3]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[3])/maxQCDscale);
	    histo_ZH_CMS_QCDScaleBounding[4]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[4])/maxQCDscale);
	    histo_ZH_CMS_QCDScaleBounding[5]->Fill(MVAVar,totalWeight*TMath::Abs(thePandaFlat.scale[5])/maxQCDscale);
	    histo_ZH_CMS_MVAPDFBoundingUp  ->Fill(MVAVar,totalWeight*thePandaFlat.pdfUp);
	    histo_ZH_CMS_MVAPDFBoundingDown->Fill(MVAVar,totalWeight*thePandaFlat.pdfDown);
            if     (lepType == 0) {histo_ZH_CMS_MVALepEffMBoundingUp  ->Fill(MVAVar,totalWeight*1.020);histo_ZH_CMS_MVALepEffEBoundingUp  ->Fill(MVAVar,totalWeight);}
            else if(lepType == 1) {histo_ZH_CMS_MVALepEffEBoundingUp  ->Fill(MVAVar,totalWeight*1.020);histo_ZH_CMS_MVALepEffMBoundingUp  ->Fill(MVAVar,totalWeight);}
            if     (lepType == 0) {histo_ZH_CMS_MVALepEffMBoundingDown->Fill(MVAVar,totalWeight/1.020);histo_ZH_CMS_MVALepEffEBoundingDown->Fill(MVAVar,totalWeight);}
            else if(lepType == 1) {histo_ZH_CMS_MVALepEffEBoundingDown->Fill(MVAVar,totalWeight/1.020);histo_ZH_CMS_MVALepEffMBoundingDown->Fill(MVAVar,totalWeight);}
            histo_ZH_CMS_MVAPUBoundingUp  ->Fill(MVAVar,totalWeight*puWeightUp  /puWeight);
            histo_ZH_CMS_MVAPUBoundingDown->Fill(MVAVar,totalWeight*puWeightDown/puWeight);
            histo_ZH_CMS_MVABTAGBBoundingUp  ->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0BUp  /thePandaFlat.sf_btag0);
            histo_ZH_CMS_MVABTAGBBoundingDown->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0BDown/thePandaFlat.sf_btag0);
            histo_ZH_CMS_MVABTAGLBoundingUp  ->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0MUp  /thePandaFlat.sf_btag0);
            histo_ZH_CMS_MVABTAGLBoundingDown->Fill(MVAVar,totalWeight*thePandaFlat.sf_btag0MDown/thePandaFlat.sf_btag0);
	  }
          if(passSystCuts[JESUP])  histo_ZH_CMS_MVAJESBoundingUp  ->Fill(MVAVar,totalWeight);
          if(passSystCuts[JESDOWN])histo_ZH_CMS_MVAJESBoundingDown->Fill(MVAVar,totalWeight);
          if(passSystCuts[METUP])  histo_ZH_CMS_MVAMETBoundingUp  ->Fill(MVAVar,totalWeight);
          if(passSystCuts[METDOWN])histo_ZH_CMS_MVAMETBoundingDown->Fill(MVAVar,totalWeight);
        }
      }

    } // end events loop
    the_input_file->Close();
  } // end chain loop

  histo[allPlots-1][0]->Add(histo_Data);
  histo[allPlots-1][1]->Add(histo_EM);
  histo[allPlots-1][2]->Add(histo_VG);
  histo[allPlots-1][3]->Add(histo_WZ);
  histo[allPlots-1][4]->Add(histo_ZZ);
  histo[allPlots-1][5]->Add(histo_VVV);
  histo[allPlots-1][6]->Add(histo_Higgs);
  histo[allPlots-1][7]->Add(histo_ZH);

  double qcdScaleTotal[2] = {0.035, 0.231};
  double pdfTotal[2] = {0.016, 0.051};
  double lumiE = 1.025;
  double syst_WZl[2] = {1.010, 1.012};

  printf("EWK Corr: WZ(%f/%f/%f) ZZ(%f/%f/%f) ggZZ(%f/%f/%f)\n",
                     histo_WZ_CMS_EWKWZCorrUp->GetSumOfWeights(),histo_WZ->GetSumOfWeights(),histo_WZ_CMS_EWKWZCorrDown->GetSumOfWeights(),
                     histo_ZZ_CMS_EWKqqZZCorrUp->GetSumOfWeights(),histo_ZZ->GetSumOfWeights(),histo_ZZ_CMS_EWKqqZZCorrDown->GetSumOfWeights(),
		     histo_ZZ_CMS_ggZZCorrUp ->GetSumOfWeights(),histo_ZZ->GetSumOfWeights(),histo_ZZ_CMS_ggZZCorrDown ->GetSumOfWeights());

  printf("QCD Corr: EM(%f:%f/%f/%f/%f/%f/%f) VG(%f:%f/%f/%f/%f/%f/%f) WZ(%f:%f/%f/%f/%f/%f/%f) ZZ(%f:%f/%f/%f/%f/%f/%f) VV(%f:%f/%f/%f/%f/%f/%f) Higgs(%f:%f/%f/%f/%f/%f/%f) ZH(%f:%f/%f/%f/%f/%f/%f)\n",
    histo_EM->GetSumOfWeights(),histo_EM_CMS_QCDScaleBounding[0]->GetSumOfWeights(),histo_EM_CMS_QCDScaleBounding[1]->GetSumOfWeights(),histo_EM_CMS_QCDScaleBounding[2]->GetSumOfWeights(),histo_EM_CMS_QCDScaleBounding[3]->GetSumOfWeights(),histo_EM_CMS_QCDScaleBounding[4]->GetSumOfWeights(),histo_EM_CMS_QCDScaleBounding[5]->GetSumOfWeights(),
    histo_VG->GetSumOfWeights(),histo_VG_CMS_QCDScaleBounding[0]->GetSumOfWeights(),histo_VG_CMS_QCDScaleBounding[1]->GetSumOfWeights(),histo_VG_CMS_QCDScaleBounding[2]->GetSumOfWeights(),histo_VG_CMS_QCDScaleBounding[3]->GetSumOfWeights(),histo_VG_CMS_QCDScaleBounding[4]->GetSumOfWeights(),histo_VG_CMS_QCDScaleBounding[5]->GetSumOfWeights(),
    histo_WZ->GetSumOfWeights(),histo_WZ_CMS_QCDScaleBounding[0]->GetSumOfWeights(),histo_WZ_CMS_QCDScaleBounding[1]->GetSumOfWeights(),histo_WZ_CMS_QCDScaleBounding[2]->GetSumOfWeights(),histo_WZ_CMS_QCDScaleBounding[3]->GetSumOfWeights(),histo_WZ_CMS_QCDScaleBounding[4]->GetSumOfWeights(),histo_WZ_CMS_QCDScaleBounding[5]->GetSumOfWeights(),
    histo_ZZ->GetSumOfWeights(),histo_ZZ_CMS_QCDScaleBounding[0]->GetSumOfWeights(),histo_ZZ_CMS_QCDScaleBounding[1]->GetSumOfWeights(),histo_ZZ_CMS_QCDScaleBounding[2]->GetSumOfWeights(),histo_ZZ_CMS_QCDScaleBounding[3]->GetSumOfWeights(),histo_ZZ_CMS_QCDScaleBounding[4]->GetSumOfWeights(),histo_ZZ_CMS_QCDScaleBounding[5]->GetSumOfWeights(),
    histo_VVV->GetSumOfWeights(),histo_VVV_CMS_QCDScaleBounding[0]->GetSumOfWeights(),histo_VVV_CMS_QCDScaleBounding[1]->GetSumOfWeights(),histo_VVV_CMS_QCDScaleBounding[2]->GetSumOfWeights(),histo_VVV_CMS_QCDScaleBounding[3]->GetSumOfWeights(),histo_VVV_CMS_QCDScaleBounding[4]->GetSumOfWeights(),histo_VVV_CMS_QCDScaleBounding[5]->GetSumOfWeights(),
    histo_Higgs->GetSumOfWeights(),histo_Higgs_CMS_QCDScaleBounding[0]->GetSumOfWeights(),histo_Higgs_CMS_QCDScaleBounding[1]->GetSumOfWeights(),histo_Higgs_CMS_QCDScaleBounding[2]->GetSumOfWeights(),histo_Higgs_CMS_QCDScaleBounding[3]->GetSumOfWeights(),histo_Higgs_CMS_QCDScaleBounding[4]->GetSumOfWeights(),histo_Higgs_CMS_QCDScaleBounding[5]->GetSumOfWeights(),
    histo_ZH->GetSumOfWeights(),histo_ZH_CMS_QCDScaleBounding[0]->GetSumOfWeights(),histo_ZH_CMS_QCDScaleBounding[1]->GetSumOfWeights(),histo_ZH_CMS_QCDScaleBounding[2]->GetSumOfWeights(),histo_ZH_CMS_QCDScaleBounding[3]->GetSumOfWeights(),histo_ZH_CMS_QCDScaleBounding[4]->GetSumOfWeights(),histo_ZH_CMS_QCDScaleBounding[5]->GetSumOfWeights());

  for(int nb=1; nb<=nBinMVA; nb++){
    double systQCDScale[7] = {TMath::Abs(histo_EM_CMS_QCDScaleBounding[0]   ->GetBinContent(nb)-histo_EM   ->GetBinContent(nb)),
  			      TMath::Abs(histo_VG_CMS_QCDScaleBounding[0]   ->GetBinContent(nb)-histo_VG   ->GetBinContent(nb)),
  			      TMath::Abs(histo_WZ_CMS_QCDScaleBounding[0]   ->GetBinContent(nb)-histo_WZ   ->GetBinContent(nb)),
  			      TMath::Abs(histo_ZZ_CMS_QCDScaleBounding[0]   ->GetBinContent(nb)-histo_ZZ   ->GetBinContent(nb)),
  			      TMath::Abs(histo_VVV_CMS_QCDScaleBounding[0]  ->GetBinContent(nb)-histo_VVV  ->GetBinContent(nb)),
  			      TMath::Abs(histo_Higgs_CMS_QCDScaleBounding[0]->GetBinContent(nb)-histo_Higgs->GetBinContent(nb)),
  			      TMath::Abs(histo_ZH_CMS_QCDScaleBounding[0]   ->GetBinContent(nb)-histo_ZH   ->GetBinContent(nb))};
    for(int nqcd=1; nqcd<6; nqcd++) {
      if(TMath::Abs(histo_EM_CMS_QCDScaleBounding[nqcd]   ->GetBinContent(nb)-histo_EM   ->GetBinContent(nb)) > systQCDScale[0]) systQCDScale[0] = TMath::Abs(histo_EM_CMS_QCDScaleBounding[nqcd]   ->GetBinContent(nb)-histo_EM   ->GetBinContent(nb));
      if(TMath::Abs(histo_VG_CMS_QCDScaleBounding[nqcd]   ->GetBinContent(nb)-histo_VG   ->GetBinContent(nb)) > systQCDScale[1]) systQCDScale[1] = TMath::Abs(histo_VG_CMS_QCDScaleBounding[nqcd]   ->GetBinContent(nb)-histo_VG   ->GetBinContent(nb));
      if(TMath::Abs(histo_WZ_CMS_QCDScaleBounding[nqcd]   ->GetBinContent(nb)-histo_WZ   ->GetBinContent(nb)) > systQCDScale[2]) systQCDScale[2] = TMath::Abs(histo_WZ_CMS_QCDScaleBounding[nqcd]   ->GetBinContent(nb)-histo_WZ   ->GetBinContent(nb));
      if(TMath::Abs(histo_ZZ_CMS_QCDScaleBounding[nqcd]   ->GetBinContent(nb)-histo_ZZ   ->GetBinContent(nb)) > systQCDScale[3]) systQCDScale[3] = TMath::Abs(histo_ZZ_CMS_QCDScaleBounding[nqcd]   ->GetBinContent(nb)-histo_ZZ   ->GetBinContent(nb));
      if(TMath::Abs(histo_VVV_CMS_QCDScaleBounding[nqcd]  ->GetBinContent(nb)-histo_VVV  ->GetBinContent(nb)) > systQCDScale[4]) systQCDScale[4] = TMath::Abs(histo_VVV_CMS_QCDScaleBounding[nqcd]  ->GetBinContent(nb)-histo_VVV  ->GetBinContent(nb));
      if(TMath::Abs(histo_Higgs_CMS_QCDScaleBounding[nqcd]->GetBinContent(nb)-histo_Higgs->GetBinContent(nb)) > systQCDScale[5]) systQCDScale[5] = TMath::Abs(histo_Higgs_CMS_QCDScaleBounding[nqcd]->GetBinContent(nb)-histo_Higgs->GetBinContent(nb));
      if(TMath::Abs(histo_ZH_CMS_QCDScaleBounding[nqcd]   ->GetBinContent(nb)-histo_ZH   ->GetBinContent(nb)) > systQCDScale[6]) systQCDScale[6] = TMath::Abs(histo_ZH_CMS_QCDScaleBounding[nqcd]   ->GetBinContent(nb)-histo_ZH   ->GetBinContent(nb));
    }		      
    if(histo_EM   ->GetBinContent(nb) > 0) systQCDScale[0] = 1 + systQCDScale[0]/histo_EM   ->GetBinContent(nb); else systQCDScale[0] = 1;
    if(histo_VG   ->GetBinContent(nb) > 0) systQCDScale[1] = 1 + systQCDScale[1]/histo_VG   ->GetBinContent(nb); else systQCDScale[1] = 1;
    if(histo_WZ   ->GetBinContent(nb) > 0) systQCDScale[2] = 1 + systQCDScale[2]/histo_WZ   ->GetBinContent(nb); else systQCDScale[2] = 1;
    if(histo_ZZ   ->GetBinContent(nb) > 0) systQCDScale[3] = 1 + systQCDScale[3]/histo_ZZ   ->GetBinContent(nb); else systQCDScale[3] = 1;
    if(histo_VVV  ->GetBinContent(nb) > 0) systQCDScale[4] = 1 + systQCDScale[4]/histo_VVV  ->GetBinContent(nb); else systQCDScale[4] = 1;
    if(histo_Higgs->GetBinContent(nb) > 0) systQCDScale[5] = 1 + systQCDScale[5]/histo_Higgs->GetBinContent(nb); else systQCDScale[5] = 1;
    if(histo_ZH   ->GetBinContent(nb) > 0) systQCDScale[6] = 1 + systQCDScale[6]/histo_ZH   ->GetBinContent(nb); else systQCDScale[6] = 1;

    for(int ntype=0; ntype<7; ntype++) if(systQCDScale[ntype] < 0) systQCDScale[ntype] = 1.0;

    if(systQCDScale[6]-1 > qcdScaleTotal[0]) systQCDScale[6] = 1 + sqrt((systQCDScale[6]-1.0)*(systQCDScale[6]-1.0)-qcdScaleTotal[0]*qcdScaleTotal[0]); else systQCDScale[6] = 1.0;
    histo_EM_CMS_MVAQCDScaleBoundingUp     ->SetBinContent(nb,histo_EM->GetBinContent(nb)    *systQCDScale[0]);
    histo_VG_CMS_MVAQCDScaleBoundingUp     ->SetBinContent(nb,histo_VG->GetBinContent(nb)    *systQCDScale[1]);
    histo_WZ_CMS_MVAQCDScaleBoundingUp     ->SetBinContent(nb,histo_WZ->GetBinContent(nb)    *systQCDScale[2]);
    histo_ZZ_CMS_MVAQCDScaleBoundingUp     ->SetBinContent(nb,histo_ZZ->GetBinContent(nb)    *systQCDScale[3]);
    histo_VVV_CMS_MVAQCDScaleBoundingUp    ->SetBinContent(nb,histo_VVV->GetBinContent(nb)   *systQCDScale[4]);
    histo_Higgs_CMS_MVAQCDScaleBoundingUp  ->SetBinContent(nb,histo_Higgs->GetBinContent(nb) *systQCDScale[5]);
    histo_ZH_CMS_MVAQCDScaleBoundingUp     ->SetBinContent(nb,histo_ZH->GetBinContent(nb)    *systQCDScale[6]);
    histo_EM_CMS_MVAQCDScaleBoundingDown   ->SetBinContent(nb,histo_EM->GetBinContent(nb)    /systQCDScale[0]);
    histo_VG_CMS_MVAQCDScaleBoundingDown   ->SetBinContent(nb,histo_VG->GetBinContent(nb)    /systQCDScale[1]);
    histo_WZ_CMS_MVAQCDScaleBoundingDown   ->SetBinContent(nb,histo_WZ->GetBinContent(nb)    /systQCDScale[2]);
    histo_ZZ_CMS_MVAQCDScaleBoundingDown   ->SetBinContent(nb,histo_ZZ->GetBinContent(nb)    /systQCDScale[3]);
    histo_VVV_CMS_MVAQCDScaleBoundingDown  ->SetBinContent(nb,histo_VVV->GetBinContent(nb)   /systQCDScale[4]);
    histo_Higgs_CMS_MVAQCDScaleBoundingDown->SetBinContent(nb,histo_Higgs->GetBinContent(nb) /systQCDScale[5]);
    histo_ZH_CMS_MVAQCDScaleBoundingDown   ->SetBinContent(nb,histo_ZH->GetBinContent(nb)    /systQCDScale[6]);
  }

  if(showSyst == true){
    printf("uncertainties QCDSCALEUp\n");
    for(int i=1; i<=histo_EM   ->GetNbinsX(); i++) {if(histo_EM   ->GetBinContent(i)>0)printf("%5.1f ",histo_EM_CMS_MVAQCDScaleBoundingUp   ->GetBinContent(i)/histo_EM   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VG   ->GetNbinsX(); i++) {if(histo_VG   ->GetBinContent(i)>0)printf("%5.1f ",histo_VG_CMS_MVAQCDScaleBoundingUp   ->GetBinContent(i)/histo_VG   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_WZ   ->GetNbinsX(); i++) {if(histo_WZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_WZ_CMS_MVAQCDScaleBoundingUp   ->GetBinContent(i)/histo_WZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZZ   ->GetNbinsX(); i++) {if(histo_ZZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZZ_CMS_MVAQCDScaleBoundingUp   ->GetBinContent(i)/histo_ZZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VVV  ->GetNbinsX(); i++) {if(histo_VVV  ->GetBinContent(i)>0)printf("%5.1f ",histo_VVV_CMS_MVAQCDScaleBoundingUp  ->GetBinContent(i)/histo_VVV  ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Higgs->GetNbinsX(); i++) {if(histo_Higgs->GetBinContent(i)>0)printf("%5.1f ",histo_Higgs_CMS_MVAQCDScaleBoundingUp->GetBinContent(i)/histo_Higgs->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZH   ->GetNbinsX(); i++) {if(histo_ZH   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZH_CMS_MVAQCDScaleBoundingUp   ->GetBinContent(i)/histo_ZH   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    printf("uncertainties QCDSCALEDown\n");
    for(int i=1; i<=histo_EM   ->GetNbinsX(); i++) {if(histo_EM   ->GetBinContent(i)>0)printf("%5.1f ",histo_EM_CMS_MVAQCDScaleBoundingDown   ->GetBinContent(i)/histo_EM   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VG   ->GetNbinsX(); i++) {if(histo_VG   ->GetBinContent(i)>0)printf("%5.1f ",histo_VG_CMS_MVAQCDScaleBoundingDown   ->GetBinContent(i)/histo_VG   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_WZ   ->GetNbinsX(); i++) {if(histo_WZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_WZ_CMS_MVAQCDScaleBoundingDown   ->GetBinContent(i)/histo_WZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZZ   ->GetNbinsX(); i++) {if(histo_ZZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZZ_CMS_MVAQCDScaleBoundingDown   ->GetBinContent(i)/histo_ZZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VVV  ->GetNbinsX(); i++) {if(histo_VVV  ->GetBinContent(i)>0)printf("%5.1f ",histo_VVV_CMS_MVAQCDScaleBoundingDown  ->GetBinContent(i)/histo_VVV  ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Higgs->GetNbinsX(); i++) {if(histo_Higgs->GetBinContent(i)>0)printf("%5.1f ",histo_Higgs_CMS_MVAQCDScaleBoundingDown->GetBinContent(i)/histo_Higgs->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZH   ->GetNbinsX(); i++) {if(histo_ZH   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZH_CMS_MVAQCDScaleBoundingDown   ->GetBinContent(i)/histo_ZH   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");

    printf("uncertainties PDFUp\n");
    for(int i=1; i<=histo_EM   ->GetNbinsX(); i++) {if(histo_EM   ->GetBinContent(i)>0)printf("%5.1f ",histo_EM_CMS_MVAPDFBoundingUp   ->GetBinContent(i)/histo_EM   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VG   ->GetNbinsX(); i++) {if(histo_VG   ->GetBinContent(i)>0)printf("%5.1f ",histo_VG_CMS_MVAPDFBoundingUp   ->GetBinContent(i)/histo_VG   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_WZ   ->GetNbinsX(); i++) {if(histo_WZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_WZ_CMS_MVAPDFBoundingUp   ->GetBinContent(i)/histo_WZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZZ   ->GetNbinsX(); i++) {if(histo_ZZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZZ_CMS_MVAPDFBoundingUp   ->GetBinContent(i)/histo_ZZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VVV  ->GetNbinsX(); i++) {if(histo_VVV  ->GetBinContent(i)>0)printf("%5.1f ",histo_VVV_CMS_MVAPDFBoundingUp  ->GetBinContent(i)/histo_VVV  ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Higgs->GetNbinsX(); i++) {if(histo_Higgs->GetBinContent(i)>0)printf("%5.1f ",histo_Higgs_CMS_MVAPDFBoundingUp->GetBinContent(i)/histo_Higgs->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZH   ->GetNbinsX(); i++) {if(histo_ZH   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZH_CMS_MVAPDFBoundingUp   ->GetBinContent(i)/histo_ZH   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    printf("uncertainties PDFDown\n");
    for(int i=1; i<=histo_EM   ->GetNbinsX(); i++) {if(histo_EM   ->GetBinContent(i)>0)printf("%5.1f ",histo_EM_CMS_MVAPDFBoundingDown   ->GetBinContent(i)/histo_EM   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VG   ->GetNbinsX(); i++) {if(histo_VG   ->GetBinContent(i)>0)printf("%5.1f ",histo_VG_CMS_MVAPDFBoundingDown   ->GetBinContent(i)/histo_VG   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_WZ   ->GetNbinsX(); i++) {if(histo_WZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_WZ_CMS_MVAPDFBoundingDown   ->GetBinContent(i)/histo_WZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZZ   ->GetNbinsX(); i++) {if(histo_ZZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZZ_CMS_MVAPDFBoundingDown   ->GetBinContent(i)/histo_ZZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VVV  ->GetNbinsX(); i++) {if(histo_VVV  ->GetBinContent(i)>0)printf("%5.1f ",histo_VVV_CMS_MVAPDFBoundingDown  ->GetBinContent(i)/histo_VVV  ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Higgs->GetNbinsX(); i++) {if(histo_Higgs->GetBinContent(i)>0)printf("%5.1f ",histo_Higgs_CMS_MVAPDFBoundingDown->GetBinContent(i)/histo_Higgs->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZH   ->GetNbinsX(); i++) {if(histo_ZH   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZH_CMS_MVAPDFBoundingDown   ->GetBinContent(i)/histo_ZH   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");

    printf("uncertainties LEPEFFEUp\n");
    for(int i=1; i<=histo_EM   ->GetNbinsX(); i++) {if(histo_EM   ->GetBinContent(i)>0)printf("%5.1f ",histo_EM_CMS_MVALepEffEBoundingUp   ->GetBinContent(i)/histo_EM   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VG   ->GetNbinsX(); i++) {if(histo_VG   ->GetBinContent(i)>0)printf("%5.1f ",histo_VG_CMS_MVALepEffEBoundingUp   ->GetBinContent(i)/histo_VG   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_WZ   ->GetNbinsX(); i++) {if(histo_WZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_WZ_CMS_MVALepEffEBoundingUp   ->GetBinContent(i)/histo_WZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZZ   ->GetNbinsX(); i++) {if(histo_ZZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZZ_CMS_MVALepEffEBoundingUp   ->GetBinContent(i)/histo_ZZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VVV  ->GetNbinsX(); i++) {if(histo_VVV  ->GetBinContent(i)>0)printf("%5.1f ",histo_VVV_CMS_MVALepEffEBoundingUp  ->GetBinContent(i)/histo_VVV  ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Higgs->GetNbinsX(); i++) {if(histo_Higgs->GetBinContent(i)>0)printf("%5.1f ",histo_Higgs_CMS_MVALepEffEBoundingUp->GetBinContent(i)/histo_Higgs->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZH   ->GetNbinsX(); i++) {if(histo_ZH   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZH_CMS_MVALepEffEBoundingUp   ->GetBinContent(i)/histo_ZH   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    printf("uncertainties LEPEFFEDown\n");
    for(int i=1; i<=histo_EM   ->GetNbinsX(); i++) {if(histo_EM   ->GetBinContent(i)>0)printf("%5.1f ",histo_EM_CMS_MVALepEffEBoundingDown   ->GetBinContent(i)/histo_EM   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VG   ->GetNbinsX(); i++) {if(histo_VG   ->GetBinContent(i)>0)printf("%5.1f ",histo_VG_CMS_MVALepEffEBoundingDown   ->GetBinContent(i)/histo_VG   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_WZ   ->GetNbinsX(); i++) {if(histo_WZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_WZ_CMS_MVALepEffEBoundingDown   ->GetBinContent(i)/histo_WZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZZ   ->GetNbinsX(); i++) {if(histo_ZZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZZ_CMS_MVALepEffEBoundingDown   ->GetBinContent(i)/histo_ZZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VVV  ->GetNbinsX(); i++) {if(histo_VVV  ->GetBinContent(i)>0)printf("%5.1f ",histo_VVV_CMS_MVALepEffEBoundingDown  ->GetBinContent(i)/histo_VVV  ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Higgs->GetNbinsX(); i++) {if(histo_Higgs->GetBinContent(i)>0)printf("%5.1f ",histo_Higgs_CMS_MVALepEffEBoundingDown->GetBinContent(i)/histo_Higgs->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZH   ->GetNbinsX(); i++) {if(histo_ZH   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZH_CMS_MVALepEffEBoundingDown   ->GetBinContent(i)/histo_ZH   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");

    printf("uncertainties LEPEFFMUp\n");
    for(int i=1; i<=histo_EM   ->GetNbinsX(); i++) {if(histo_EM   ->GetBinContent(i)>0)printf("%5.1f ",histo_EM_CMS_MVALepEffMBoundingUp   ->GetBinContent(i)/histo_EM   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VG   ->GetNbinsX(); i++) {if(histo_VG   ->GetBinContent(i)>0)printf("%5.1f ",histo_VG_CMS_MVALepEffMBoundingUp   ->GetBinContent(i)/histo_VG   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_WZ   ->GetNbinsX(); i++) {if(histo_WZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_WZ_CMS_MVALepEffMBoundingUp   ->GetBinContent(i)/histo_WZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZZ   ->GetNbinsX(); i++) {if(histo_ZZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZZ_CMS_MVALepEffMBoundingUp   ->GetBinContent(i)/histo_ZZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VVV  ->GetNbinsX(); i++) {if(histo_VVV  ->GetBinContent(i)>0)printf("%5.1f ",histo_VVV_CMS_MVALepEffMBoundingUp  ->GetBinContent(i)/histo_VVV  ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Higgs->GetNbinsX(); i++) {if(histo_Higgs->GetBinContent(i)>0)printf("%5.1f ",histo_Higgs_CMS_MVALepEffMBoundingUp->GetBinContent(i)/histo_Higgs->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZH   ->GetNbinsX(); i++) {if(histo_ZH   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZH_CMS_MVALepEffMBoundingUp   ->GetBinContent(i)/histo_ZH   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    printf("uncertainties LEPEFFMDown\n");
    for(int i=1; i<=histo_EM   ->GetNbinsX(); i++) {if(histo_EM   ->GetBinContent(i)>0)printf("%5.1f ",histo_EM_CMS_MVALepEffMBoundingDown   ->GetBinContent(i)/histo_EM   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VG   ->GetNbinsX(); i++) {if(histo_VG   ->GetBinContent(i)>0)printf("%5.1f ",histo_VG_CMS_MVALepEffMBoundingDown   ->GetBinContent(i)/histo_VG   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_WZ   ->GetNbinsX(); i++) {if(histo_WZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_WZ_CMS_MVALepEffMBoundingDown   ->GetBinContent(i)/histo_WZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZZ   ->GetNbinsX(); i++) {if(histo_ZZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZZ_CMS_MVALepEffMBoundingDown   ->GetBinContent(i)/histo_ZZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VVV  ->GetNbinsX(); i++) {if(histo_VVV  ->GetBinContent(i)>0)printf("%5.1f ",histo_VVV_CMS_MVALepEffMBoundingDown  ->GetBinContent(i)/histo_VVV  ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Higgs->GetNbinsX(); i++) {if(histo_Higgs->GetBinContent(i)>0)printf("%5.1f ",histo_Higgs_CMS_MVALepEffMBoundingDown->GetBinContent(i)/histo_Higgs->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZH   ->GetNbinsX(); i++) {if(histo_ZH   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZH_CMS_MVALepEffMBoundingDown   ->GetBinContent(i)/histo_ZH   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");

    printf("uncertainties METUp\n");
    for(int i=1; i<=histo_EM   ->GetNbinsX(); i++) {if(histo_EM   ->GetBinContent(i)>0)printf("%5.1f ",histo_EM_CMS_MVAMETBoundingUp   ->GetBinContent(i)/histo_EM   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VG   ->GetNbinsX(); i++) {if(histo_VG   ->GetBinContent(i)>0)printf("%5.1f ",histo_VG_CMS_MVAMETBoundingUp   ->GetBinContent(i)/histo_VG   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_WZ   ->GetNbinsX(); i++) {if(histo_WZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_WZ_CMS_MVAMETBoundingUp   ->GetBinContent(i)/histo_WZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZZ   ->GetNbinsX(); i++) {if(histo_ZZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZZ_CMS_MVAMETBoundingUp   ->GetBinContent(i)/histo_ZZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VVV  ->GetNbinsX(); i++) {if(histo_VVV  ->GetBinContent(i)>0)printf("%5.1f ",histo_VVV_CMS_MVAMETBoundingUp  ->GetBinContent(i)/histo_VVV  ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Higgs->GetNbinsX(); i++) {if(histo_Higgs->GetBinContent(i)>0)printf("%5.1f ",histo_Higgs_CMS_MVAMETBoundingUp->GetBinContent(i)/histo_Higgs->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZH   ->GetNbinsX(); i++) {if(histo_ZH   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZH_CMS_MVAMETBoundingUp   ->GetBinContent(i)/histo_ZH   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    printf("uncertainties METDown\n");
    for(int i=1; i<=histo_EM   ->GetNbinsX(); i++) {if(histo_EM   ->GetBinContent(i)>0)printf("%5.1f ",histo_EM_CMS_MVAMETBoundingDown   ->GetBinContent(i)/histo_EM   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VG   ->GetNbinsX(); i++) {if(histo_VG   ->GetBinContent(i)>0)printf("%5.1f ",histo_VG_CMS_MVAMETBoundingDown   ->GetBinContent(i)/histo_VG   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_WZ   ->GetNbinsX(); i++) {if(histo_WZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_WZ_CMS_MVAMETBoundingDown   ->GetBinContent(i)/histo_WZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZZ   ->GetNbinsX(); i++) {if(histo_ZZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZZ_CMS_MVAMETBoundingDown   ->GetBinContent(i)/histo_ZZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VVV  ->GetNbinsX(); i++) {if(histo_VVV  ->GetBinContent(i)>0)printf("%5.1f ",histo_VVV_CMS_MVAMETBoundingDown  ->GetBinContent(i)/histo_VVV  ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Higgs->GetNbinsX(); i++) {if(histo_Higgs->GetBinContent(i)>0)printf("%5.1f ",histo_Higgs_CMS_MVAMETBoundingDown->GetBinContent(i)/histo_Higgs->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZH   ->GetNbinsX(); i++) {if(histo_ZH   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZH_CMS_MVAMETBoundingDown   ->GetBinContent(i)/histo_ZH   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");

    printf("uncertainties JESUp\n");
    for(int i=1; i<=histo_EM   ->GetNbinsX(); i++) {if(histo_EM   ->GetBinContent(i)>0)printf("%5.1f ",histo_EM_CMS_MVAJESBoundingUp   ->GetBinContent(i)/histo_EM   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VG   ->GetNbinsX(); i++) {if(histo_VG   ->GetBinContent(i)>0)printf("%5.1f ",histo_VG_CMS_MVAJESBoundingUp   ->GetBinContent(i)/histo_VG   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_WZ   ->GetNbinsX(); i++) {if(histo_WZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_WZ_CMS_MVAJESBoundingUp   ->GetBinContent(i)/histo_WZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZZ   ->GetNbinsX(); i++) {if(histo_ZZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZZ_CMS_MVAJESBoundingUp   ->GetBinContent(i)/histo_ZZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VVV  ->GetNbinsX(); i++) {if(histo_VVV  ->GetBinContent(i)>0)printf("%5.1f ",histo_VVV_CMS_MVAJESBoundingUp  ->GetBinContent(i)/histo_VVV  ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Higgs->GetNbinsX(); i++) {if(histo_Higgs->GetBinContent(i)>0)printf("%5.1f ",histo_Higgs_CMS_MVAJESBoundingUp->GetBinContent(i)/histo_Higgs->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZH   ->GetNbinsX(); i++) {if(histo_ZH   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZH_CMS_MVAJESBoundingUp   ->GetBinContent(i)/histo_ZH   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    printf("uncertainties JESDown\n");
    for(int i=1; i<=histo_EM   ->GetNbinsX(); i++) {if(histo_EM   ->GetBinContent(i)>0)printf("%5.1f ",histo_EM_CMS_MVAJESBoundingDown   ->GetBinContent(i)/histo_EM   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VG   ->GetNbinsX(); i++) {if(histo_VG   ->GetBinContent(i)>0)printf("%5.1f ",histo_VG_CMS_MVAJESBoundingDown   ->GetBinContent(i)/histo_VG   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_WZ   ->GetNbinsX(); i++) {if(histo_WZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_WZ_CMS_MVAJESBoundingDown   ->GetBinContent(i)/histo_WZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZZ   ->GetNbinsX(); i++) {if(histo_ZZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZZ_CMS_MVAJESBoundingDown   ->GetBinContent(i)/histo_ZZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VVV  ->GetNbinsX(); i++) {if(histo_VVV  ->GetBinContent(i)>0)printf("%5.1f ",histo_VVV_CMS_MVAJESBoundingDown  ->GetBinContent(i)/histo_VVV  ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Higgs->GetNbinsX(); i++) {if(histo_Higgs->GetBinContent(i)>0)printf("%5.1f ",histo_Higgs_CMS_MVAJESBoundingDown->GetBinContent(i)/histo_Higgs->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZH   ->GetNbinsX(); i++) {if(histo_ZH   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZH_CMS_MVAJESBoundingDown   ->GetBinContent(i)/histo_ZH   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");

    printf("uncertainties PUUp\n");
    for(int i=1; i<=histo_EM   ->GetNbinsX(); i++) {if(histo_EM   ->GetBinContent(i)>0)printf("%5.1f ",histo_EM_CMS_MVAPUBoundingUp   ->GetBinContent(i)/histo_EM   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VG   ->GetNbinsX(); i++) {if(histo_VG   ->GetBinContent(i)>0)printf("%5.1f ",histo_VG_CMS_MVAPUBoundingUp   ->GetBinContent(i)/histo_VG   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_WZ   ->GetNbinsX(); i++) {if(histo_WZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_WZ_CMS_MVAPUBoundingUp   ->GetBinContent(i)/histo_WZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZZ   ->GetNbinsX(); i++) {if(histo_ZZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZZ_CMS_MVAPUBoundingUp   ->GetBinContent(i)/histo_ZZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VVV  ->GetNbinsX(); i++) {if(histo_VVV  ->GetBinContent(i)>0)printf("%5.1f ",histo_VVV_CMS_MVAPUBoundingUp  ->GetBinContent(i)/histo_VVV  ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Higgs->GetNbinsX(); i++) {if(histo_Higgs->GetBinContent(i)>0)printf("%5.1f ",histo_Higgs_CMS_MVAPUBoundingUp->GetBinContent(i)/histo_Higgs->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZH   ->GetNbinsX(); i++) {if(histo_ZH   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZH_CMS_MVAPUBoundingUp   ->GetBinContent(i)/histo_ZH   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    printf("uncertainties PUDown\n");
    for(int i=1; i<=histo_EM   ->GetNbinsX(); i++) {if(histo_EM   ->GetBinContent(i)>0)printf("%5.1f ",histo_EM_CMS_MVAPUBoundingDown   ->GetBinContent(i)/histo_EM   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VG   ->GetNbinsX(); i++) {if(histo_VG   ->GetBinContent(i)>0)printf("%5.1f ",histo_VG_CMS_MVAPUBoundingDown   ->GetBinContent(i)/histo_VG   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_WZ   ->GetNbinsX(); i++) {if(histo_WZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_WZ_CMS_MVAPUBoundingDown   ->GetBinContent(i)/histo_WZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZZ   ->GetNbinsX(); i++) {if(histo_ZZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZZ_CMS_MVAPUBoundingDown   ->GetBinContent(i)/histo_ZZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VVV  ->GetNbinsX(); i++) {if(histo_VVV  ->GetBinContent(i)>0)printf("%5.1f ",histo_VVV_CMS_MVAPUBoundingDown  ->GetBinContent(i)/histo_VVV  ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Higgs->GetNbinsX(); i++) {if(histo_Higgs->GetBinContent(i)>0)printf("%5.1f ",histo_Higgs_CMS_MVAPUBoundingDown->GetBinContent(i)/histo_Higgs->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZH   ->GetNbinsX(); i++) {if(histo_ZH   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZH_CMS_MVAPUBoundingDown   ->GetBinContent(i)/histo_ZH   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");

    printf("uncertainties BTAGBUp\n");
    for(int i=1; i<=histo_EM   ->GetNbinsX(); i++) {if(histo_EM   ->GetBinContent(i)>0)printf("%5.1f ",histo_EM_CMS_MVABTAGBBoundingUp   ->GetBinContent(i)/histo_EM   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VG   ->GetNbinsX(); i++) {if(histo_VG   ->GetBinContent(i)>0)printf("%5.1f ",histo_VG_CMS_MVABTAGBBoundingUp   ->GetBinContent(i)/histo_VG   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_WZ   ->GetNbinsX(); i++) {if(histo_WZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_WZ_CMS_MVABTAGBBoundingUp   ->GetBinContent(i)/histo_WZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZZ   ->GetNbinsX(); i++) {if(histo_ZZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZZ_CMS_MVABTAGBBoundingUp   ->GetBinContent(i)/histo_ZZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VVV  ->GetNbinsX(); i++) {if(histo_VVV  ->GetBinContent(i)>0)printf("%5.1f ",histo_VVV_CMS_MVABTAGBBoundingUp  ->GetBinContent(i)/histo_VVV  ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Higgs->GetNbinsX(); i++) {if(histo_Higgs->GetBinContent(i)>0)printf("%5.1f ",histo_Higgs_CMS_MVABTAGBBoundingUp->GetBinContent(i)/histo_Higgs->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZH   ->GetNbinsX(); i++) {if(histo_ZH   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZH_CMS_MVABTAGBBoundingUp   ->GetBinContent(i)/histo_ZH   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    printf("uncertainties BTAGBDown\n");
    for(int i=1; i<=histo_EM   ->GetNbinsX(); i++) {if(histo_EM   ->GetBinContent(i)>0)printf("%5.1f ",histo_EM_CMS_MVABTAGBBoundingDown   ->GetBinContent(i)/histo_EM   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VG   ->GetNbinsX(); i++) {if(histo_VG   ->GetBinContent(i)>0)printf("%5.1f ",histo_VG_CMS_MVABTAGBBoundingDown   ->GetBinContent(i)/histo_VG   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_WZ   ->GetNbinsX(); i++) {if(histo_WZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_WZ_CMS_MVABTAGBBoundingDown   ->GetBinContent(i)/histo_WZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZZ   ->GetNbinsX(); i++) {if(histo_ZZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZZ_CMS_MVABTAGBBoundingDown   ->GetBinContent(i)/histo_ZZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VVV  ->GetNbinsX(); i++) {if(histo_VVV  ->GetBinContent(i)>0)printf("%5.1f ",histo_VVV_CMS_MVABTAGBBoundingDown  ->GetBinContent(i)/histo_VVV  ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Higgs->GetNbinsX(); i++) {if(histo_Higgs->GetBinContent(i)>0)printf("%5.1f ",histo_Higgs_CMS_MVABTAGBBoundingDown->GetBinContent(i)/histo_Higgs->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZH   ->GetNbinsX(); i++) {if(histo_ZH   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZH_CMS_MVABTAGBBoundingDown   ->GetBinContent(i)/histo_ZH   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");

    printf("uncertainties BTAGLUp\n");
    for(int i=1; i<=histo_EM   ->GetNbinsX(); i++) {if(histo_EM   ->GetBinContent(i)>0)printf("%5.1f ",histo_EM_CMS_MVABTAGLBoundingUp   ->GetBinContent(i)/histo_EM   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VG   ->GetNbinsX(); i++) {if(histo_VG   ->GetBinContent(i)>0)printf("%5.1f ",histo_VG_CMS_MVABTAGLBoundingUp   ->GetBinContent(i)/histo_VG   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_WZ   ->GetNbinsX(); i++) {if(histo_WZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_WZ_CMS_MVABTAGLBoundingUp   ->GetBinContent(i)/histo_WZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZZ   ->GetNbinsX(); i++) {if(histo_ZZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZZ_CMS_MVABTAGLBoundingUp   ->GetBinContent(i)/histo_ZZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VVV  ->GetNbinsX(); i++) {if(histo_VVV  ->GetBinContent(i)>0)printf("%5.1f ",histo_VVV_CMS_MVABTAGLBoundingUp  ->GetBinContent(i)/histo_VVV  ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Higgs->GetNbinsX(); i++) {if(histo_Higgs->GetBinContent(i)>0)printf("%5.1f ",histo_Higgs_CMS_MVABTAGLBoundingUp->GetBinContent(i)/histo_Higgs->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZH   ->GetNbinsX(); i++) {if(histo_ZH   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZH_CMS_MVABTAGLBoundingUp   ->GetBinContent(i)/histo_ZH   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    printf("uncertainties BTAGLDown\n");
    for(int i=1; i<=histo_EM   ->GetNbinsX(); i++) {if(histo_EM   ->GetBinContent(i)>0)printf("%5.1f ",histo_EM_CMS_MVABTAGLBoundingDown   ->GetBinContent(i)/histo_EM   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VG   ->GetNbinsX(); i++) {if(histo_VG   ->GetBinContent(i)>0)printf("%5.1f ",histo_VG_CMS_MVABTAGLBoundingDown   ->GetBinContent(i)/histo_VG   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_WZ   ->GetNbinsX(); i++) {if(histo_WZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_WZ_CMS_MVABTAGLBoundingDown   ->GetBinContent(i)/histo_WZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZZ   ->GetNbinsX(); i++) {if(histo_ZZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZZ_CMS_MVABTAGLBoundingDown   ->GetBinContent(i)/histo_ZZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_VVV  ->GetNbinsX(); i++) {if(histo_VVV  ->GetBinContent(i)>0)printf("%5.1f ",histo_VVV_CMS_MVABTAGLBoundingDown  ->GetBinContent(i)/histo_VVV  ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_Higgs->GetNbinsX(); i++) {if(histo_Higgs->GetBinContent(i)>0)printf("%5.1f ",histo_Higgs_CMS_MVABTAGLBoundingDown->GetBinContent(i)/histo_Higgs->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZH   ->GetNbinsX(); i++) {if(histo_ZH   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZH_CMS_MVABTAGLBoundingDown   ->GetBinContent(i)/histo_ZH   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");

    printf("uncertainties THEORYUp\n");
    for(int i=1; i<=histo_WZ   ->GetNbinsX(); i++) {if(histo_WZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_WZ_CMS_EWKWZCorrUp     ->GetBinContent(i)/histo_WZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZZ   ->GetNbinsX(); i++) {if(histo_ZZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZZ_CMS_EWKqqZZCorrUp   ->GetBinContent(i)/histo_ZZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZZ   ->GetNbinsX(); i++) {if(histo_ZZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZZ_CMS_ggZZCorrUp      ->GetBinContent(i)/histo_ZZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    printf("uncertainties THEORYDown\n");
    for(int i=1; i<=histo_WZ   ->GetNbinsX(); i++) {if(histo_WZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_WZ_CMS_EWKWZCorrDown     ->GetBinContent(i)/histo_WZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZZ   ->GetNbinsX(); i++) {if(histo_ZZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZZ_CMS_EWKqqZZCorrDown   ->GetBinContent(i)/histo_ZZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
    for(int i=1; i<=histo_ZZ   ->GetNbinsX(); i++) {if(histo_ZZ   ->GetBinContent(i)>0)printf("%5.1f ",histo_ZZ_CMS_ggZZCorrDown      ->GetBinContent(i)/histo_ZZ   ->GetBinContent(i)*100);else printf("100.0 ");} printf("\n");
  }

  // Filling datacards input root file
  char outputLimits[200];
  sprintf(outputLimits,"zhg_2016_input.root");
  TFile* outFileLimits = new TFile(outputLimits,"recreate");
  outFileLimits->cd();

  histo_Data ->Write();
  histo_EM   ->Write();
  histo_VG   ->Write();
  histo_WZ   ->Write();
  histo_ZZ   ->Write();
  histo_VVV  ->Write();
  histo_Higgs->Write();
  histo_ZH   ->Write();

  histo_EM_CMS_MVAQCDScaleBoundingUp   ->Write();
  histo_VG_CMS_MVAQCDScaleBoundingUp   ->Write();
  histo_WZ_CMS_MVAQCDScaleBoundingUp   ->Write();
  histo_ZZ_CMS_MVAQCDScaleBoundingUp   ->Write();
  histo_VVV_CMS_MVAQCDScaleBoundingUp  ->Write();
  histo_Higgs_CMS_MVAQCDScaleBoundingUp->Write();
  histo_ZH_CMS_MVAQCDScaleBoundingUp   ->Write();

  histo_EM_CMS_MVAQCDScaleBoundingDown	 ->Write();
  histo_VG_CMS_MVAQCDScaleBoundingDown	 ->Write();
  histo_WZ_CMS_MVAQCDScaleBoundingDown	 ->Write();
  histo_ZZ_CMS_MVAQCDScaleBoundingDown	 ->Write();
  histo_VVV_CMS_MVAQCDScaleBoundingDown  ->Write();
  histo_Higgs_CMS_MVAQCDScaleBoundingDown->Write();
  histo_ZH_CMS_MVAQCDScaleBoundingDown	 ->Write();

  histo_EM_CMS_MVAPDFBoundingUp   ->Write();
  histo_VG_CMS_MVAPDFBoundingUp   ->Write();
  histo_WZ_CMS_MVAPDFBoundingUp   ->Write();
  histo_ZZ_CMS_MVAPDFBoundingUp   ->Write();
  histo_VVV_CMS_MVAPDFBoundingUp  ->Write();
  histo_Higgs_CMS_MVAPDFBoundingUp->Write();
  histo_ZH_CMS_MVAPDFBoundingUp   ->Write();

  histo_EM_CMS_MVAPDFBoundingDown   ->Write();
  histo_VG_CMS_MVAPDFBoundingDown   ->Write();
  histo_WZ_CMS_MVAPDFBoundingDown   ->Write();
  histo_ZZ_CMS_MVAPDFBoundingDown   ->Write();
  histo_VVV_CMS_MVAPDFBoundingDown  ->Write();
  histo_Higgs_CMS_MVAPDFBoundingDown->Write();
  histo_ZH_CMS_MVAPDFBoundingDown   ->Write();

  histo_EM_CMS_MVALepEffEBoundingUp   ->Write();
  histo_VG_CMS_MVALepEffEBoundingUp   ->Write();
  histo_WZ_CMS_MVALepEffEBoundingUp   ->Write();
  histo_ZZ_CMS_MVALepEffEBoundingUp   ->Write();
  histo_VVV_CMS_MVALepEffEBoundingUp  ->Write();
  histo_Higgs_CMS_MVALepEffEBoundingUp->Write();
  histo_ZH_CMS_MVALepEffEBoundingUp   ->Write();

  histo_EM_CMS_MVALepEffEBoundingDown   ->Write();
  histo_VG_CMS_MVALepEffEBoundingDown   ->Write();
  histo_WZ_CMS_MVALepEffEBoundingDown   ->Write();
  histo_ZZ_CMS_MVALepEffEBoundingDown   ->Write();
  histo_VVV_CMS_MVALepEffEBoundingDown  ->Write();
  histo_Higgs_CMS_MVALepEffEBoundingDown->Write();
  histo_ZH_CMS_MVALepEffEBoundingDown   ->Write();

  histo_EM_CMS_MVALepEffMBoundingUp   ->Write();
  histo_VG_CMS_MVALepEffMBoundingUp   ->Write();
  histo_WZ_CMS_MVALepEffMBoundingUp   ->Write();
  histo_ZZ_CMS_MVALepEffMBoundingUp   ->Write();
  histo_VVV_CMS_MVALepEffMBoundingUp  ->Write();
  histo_Higgs_CMS_MVALepEffMBoundingUp->Write();
  histo_ZH_CMS_MVALepEffMBoundingUp   ->Write();

  histo_EM_CMS_MVALepEffMBoundingDown   ->Write();
  histo_VG_CMS_MVALepEffMBoundingDown   ->Write();
  histo_WZ_CMS_MVALepEffMBoundingDown   ->Write();
  histo_ZZ_CMS_MVALepEffMBoundingDown   ->Write();
  histo_VVV_CMS_MVALepEffMBoundingDown  ->Write();
  histo_Higgs_CMS_MVALepEffMBoundingDown->Write();
  histo_ZH_CMS_MVALepEffMBoundingDown   ->Write();

  histo_EM_CMS_MVAMETBoundingDown   ->Write();
  histo_VG_CMS_MVAMETBoundingDown   ->Write();
  histo_WZ_CMS_MVAMETBoundingDown   ->Write();
  histo_ZZ_CMS_MVAMETBoundingDown   ->Write();
  histo_VVV_CMS_MVAMETBoundingDown  ->Write();
  histo_Higgs_CMS_MVAMETBoundingDown->Write();
  histo_ZH_CMS_MVAMETBoundingDown   ->Write();

  histo_EM_CMS_MVAJESBoundingUp   ->Write();
  histo_VG_CMS_MVAJESBoundingUp   ->Write();
  histo_WZ_CMS_MVAJESBoundingUp   ->Write();
  histo_ZZ_CMS_MVAJESBoundingUp   ->Write();
  histo_VVV_CMS_MVAJESBoundingUp  ->Write();
  histo_Higgs_CMS_MVAJESBoundingUp->Write();
  histo_ZH_CMS_MVAJESBoundingUp   ->Write();

  histo_EM_CMS_MVAJESBoundingDown   ->Write();
  histo_VG_CMS_MVAJESBoundingDown   ->Write();
  histo_WZ_CMS_MVAJESBoundingDown   ->Write();
  histo_ZZ_CMS_MVAJESBoundingDown   ->Write();
  histo_VVV_CMS_MVAJESBoundingDown  ->Write();
  histo_Higgs_CMS_MVAJESBoundingDown->Write();
  histo_ZH_CMS_MVAJESBoundingDown   ->Write();

  histo_EM_CMS_MVAPUBoundingUp	 ->Write();
  histo_VG_CMS_MVAPUBoundingUp 	 ->Write();
  histo_WZ_CMS_MVAPUBoundingUp	 ->Write();
  histo_ZZ_CMS_MVAPUBoundingUp	 ->Write();
  histo_VVV_CMS_MVAPUBoundingUp  ->Write();
  histo_Higgs_CMS_MVAPUBoundingUp->Write();
  histo_ZH_CMS_MVAPUBoundingUp	 ->Write();

  histo_EM_CMS_MVAPUBoundingDown   ->Write();
  histo_VG_CMS_MVAPUBoundingDown   ->Write();
  histo_WZ_CMS_MVAPUBoundingDown   ->Write();
  histo_ZZ_CMS_MVAPUBoundingDown   ->Write();
  histo_VVV_CMS_MVAPUBoundingDown  ->Write();
  histo_Higgs_CMS_MVAPUBoundingDown->Write();
  histo_ZH_CMS_MVAPUBoundingDown   ->Write();

  histo_EM_CMS_MVABTAGBBoundingUp   ->Write();
  histo_VG_CMS_MVABTAGBBoundingUp   ->Write();
  histo_WZ_CMS_MVABTAGBBoundingUp   ->Write();
  histo_ZZ_CMS_MVABTAGBBoundingUp   ->Write();
  histo_VVV_CMS_MVABTAGBBoundingUp  ->Write();
  histo_Higgs_CMS_MVABTAGBBoundingUp->Write();
  histo_ZH_CMS_MVABTAGBBoundingUp   ->Write();

  histo_EM_CMS_MVABTAGBBoundingDown   ->Write();
  histo_VG_CMS_MVABTAGBBoundingDown   ->Write();
  histo_WZ_CMS_MVABTAGBBoundingDown   ->Write();
  histo_ZZ_CMS_MVABTAGBBoundingDown   ->Write();
  histo_VVV_CMS_MVABTAGBBoundingDown  ->Write();
  histo_Higgs_CMS_MVABTAGBBoundingDown->Write();
  histo_ZH_CMS_MVABTAGBBoundingDown   ->Write();

  histo_EM_CMS_MVABTAGLBoundingUp   ->Write();
  histo_VG_CMS_MVABTAGLBoundingUp   ->Write();
  histo_WZ_CMS_MVABTAGLBoundingUp   ->Write();
  histo_ZZ_CMS_MVABTAGLBoundingUp   ->Write();
  histo_VVV_CMS_MVABTAGLBoundingUp  ->Write();
  histo_Higgs_CMS_MVABTAGLBoundingUp->Write();
  histo_ZH_CMS_MVABTAGLBoundingUp   ->Write();

  histo_EM_CMS_MVABTAGLBoundingDown   ->Write();
  histo_VG_CMS_MVABTAGLBoundingDown   ->Write();
  histo_WZ_CMS_MVABTAGLBoundingDown   ->Write();
  histo_ZZ_CMS_MVABTAGLBoundingDown   ->Write();
  histo_VVV_CMS_MVABTAGLBoundingDown  ->Write();
  histo_Higgs_CMS_MVABTAGLBoundingDown->Write();
  histo_ZH_CMS_MVABTAGLBoundingDown   ->Write();

  histo_WZ_CMS_EWKWZCorrUp    ->Write();
  histo_WZ_CMS_EWKWZCorrDown  ->Write();
  histo_ZZ_CMS_EWKqqZZCorrUp  ->Write();
  histo_ZZ_CMS_EWKqqZZCorrDown->Write();
  histo_ZZ_CMS_ggZZCorrUp     ->Write();
  histo_ZZ_CMS_ggZZCorrDown   ->Write();

  outFileLimits->Close();

  // Filling datacards txt file
  char outputLimitsCard[200];  					  
  sprintf(outputLimitsCard,"datacard_zhg_2016.txt");
  ofstream newcardShape;
  newcardShape.open(outputLimitsCard);
  newcardShape << Form("imax * number of channels\n");
  newcardShape << Form("jmax * number of background minus 1\n");
  newcardShape << Form("kmax * number of nuisance parameters\n");

  newcardShape << Form("shapes    *   *   %s  histo_$PROCESS histo_$PROCESS_$SYSTEMATIC\n",outputLimits);
  newcardShape << Form("shapes data_obs * %s  histo_Data\n",outputLimits);

  newcardShape << Form("Observation %f\n",histo_Data->GetSumOfWeights());

  newcardShape << Form("bin   ");
  for (int i=0; i<histBins-1; i++){
    newcardShape << Form("ch1  ");
  }
  newcardShape << Form("\n");
 
  newcardShape << Form("process  ");
  newcardShape << Form("EM VG WZ ZZ VVV Higgs ZH\n");

  newcardShape << Form("process  ");
  for (int i=0; i<histBins-2; i++){
    newcardShape << Form("%d ",i+1);
  }
  newcardShape << Form("0\n");

  newcardShape << Form("rate  ");
  newcardShape << Form("%f %f %f %f %f %f %f\n",histo_EM->GetSumOfWeights(),histo_VG->GetSumOfWeights(),histo_WZ->GetSumOfWeights(),histo_ZZ->GetSumOfWeights(),histo_VVV->GetSumOfWeights(),histo_Higgs->GetSumOfWeights(),histo_ZH->GetSumOfWeights());

  newcardShape << Form("lumi_13TeV    lnN     ");
  for (int i=0; i<histBins-1; i++){
    newcardShape << Form("%6.3f ",lumiE);
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_momres_m    lnN     ");
  for (int i=0; i<histBins-1; i++){
    newcardShape << Form("%6.3f ",1.005);
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_momres_e    lnN     ");
  for (int i=0; i<histBins-1; i++){
    newcardShape << Form("%6.3f ",1.005);
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_trigger    lnN     ");
  for (int i=0; i<histBins-1; i++){
    newcardShape << Form("%6.3f ",1.010);
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_eff_photon   lnN   -  1.02 -    -     -   -   1.02\n");
  newcardShape << Form("CMS_fake_el      lnN   -   -  1.10 1.10 1.10 1.10  -  \n");
  newcardShape << Form("UEPS             lnN   -   -   -    -     -   -   1.02\n");
  newcardShape << Form("QCDscaleTotal_ZH lnN   -   -   -    -     -   -   %7.5f\n",1.0+qcdScaleTotal[0]);  
  newcardShape << Form("EWKWZCorr    shape     -   -  1.0   -     -   -    -  \n");
  newcardShape << Form("EWKqqZZCorr  shape     -   -   -   1.0    -   -    -  \n");
  newcardShape << Form("ggZZCorr     shape     -   -   -   1.0    -   -    -  \n");
  newcardShape << Form("WZ_lep           lnN   -   - %6.3f  -     -   -    -  \n",syst_WZl[0]);
  newcardShape << Form("WZ_tau           lnN   -   - %6.3f  -     -   -    -  \n",syst_WZl[1]);

  newcardShape << Form("%sEM    shape     1.0  -  -  -  -  -  - \n",QCDScaleName);
  newcardShape << Form("%sVG    shape      -  1.0 -  -  -  -  - \n",QCDScaleName);
  newcardShape << Form("%sWZ    shape      -   - 1.0 -  -  -  - \n",QCDScaleName);
  newcardShape << Form("%sZZ    shape      -   -  - 1.0 -  -  - \n",QCDScaleName);
  newcardShape << Form("%sVVV   shape      -   -  -  - 1.0 -  - \n",QCDScaleName);
  newcardShape << Form("%sHiggs shape      -   -  -  -  - 1.0 - \n",QCDScaleName);
  newcardShape << Form("%sZH    shape      -   -  -  -  -  - 1.0\n",QCDScaleName);

  newcardShape << Form("%s    shape     ",PDFName);
  for (int i=0; i<histBins-1; i++){
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("%s    shape     ",effMName);
  for (int i=0; i<histBins-1; i++){
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("%s    shape     ",effEName);
  for (int i=0; i<histBins-1; i++){
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("%s    shape     ",JESName);
  for (int i=0; i<histBins-1; i++){
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("%s    shape     ",PUName);
  for (int i=0; i<histBins-1; i++){
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("%s    shape     ",BTAGBName);
  for (int i=0; i<histBins-1; i++){
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("%s    shape     ",BTAGLName);
  for (int i=0; i<histBins-1; i++){
    newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("ch1 autoMCStats 0 0 1\n");

  newcardShape.close();

  // Writing standard histograms
  char output[200];
  for(int thePlot=0; thePlot<allPlots; thePlot++){
    sprintf(output,"histoZHG_%d.root",thePlot);	
    TFile* outFilePlotsNote = new TFile(output,"recreate");
    outFilePlotsNote->cd();
    double totBck = 0;
    for(int i=1; i<histBins-1; i++) totBck = totBck + histo[thePlot][i]->GetSumOfWeights();
    printf("(%2d) %7.1f vs. %7.1f ",thePlot,histo[thePlot][0]->GetSumOfWeights(),totBck);
    printf("(");
    for(int i=1; i<histBins; i++) printf("%7.1f ",histo[thePlot][i]->GetSumOfWeights());
    printf(")\n");
    for(int np=0; np<histBins; np++) histo[thePlot][np]->Write();
    outFilePlotsNote->Close();
  }

}
