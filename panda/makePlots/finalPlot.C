#include "TROOT.h"
#include "Math/ProbFuncMathCore.h"
#include "TInterpreter.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TStyle.h"
#include "TPad.h"
#include "Math/QuantFuncMathCore.h"
#include "TMath.h"
#include "TGraphAsymmErrors.h"
#include "TSystem.h"
#include "CMS_lumi.C"
#include "TRandom.h"
#include "MitAnalysisRunII/panda/macros/9x/common.h"
#include "StandardPlot.C"
#include "GoodStyle.C"

double scaling[8] = {1,1,1,1,1,1,1,1};
//double scaling[8] = {73.496/69.913,1.2,168.114/157.695,404.402/361.347,2.583/2.537,1,1,1}; // EM/Zjets/WZ/ZZ/VVV
//double scaling[8] = {0.94,1.04,1.04,1.01,1.00,1.02,1.01,1.05}; // EWK/QCD/VV/VVV/WS/WG/DPS/Wjets

bool isLogSpecial = false;
bool isLogX = false;
bool printRatios = false;

void eraselabel(TPad *p,Double_t h){
  p->cd();
  TPad *pe = new TPad("pe","pe",0.02,0,p->GetLeftMargin(),h);	   
  pe->Draw();
  pe->SetFillColor(p->GetFillColor()); 
  pe->SetBorderMode(0);
}

void atributes(TH1D *histo, TString xtitle = "", TString ytitle = "Fraction", TString units = ""){

  histo->SetTitle("");
  //histo->SetMarkerStyle(20);
  //histo->SetMarkerSize(0.8);
  //histo->SetLineWidth(4);
  if(strcmp(units.Data(),"")==0){
    histo->GetXaxis()->SetTitle(xtitle.Data());
  } else {
    histo->GetXaxis()->SetTitle(Form("%s [%s]",xtitle.Data(),units.Data()));
  }
  histo->GetXaxis()->SetLabelFont  (   42);
  histo->GetXaxis()->SetLabelOffset(0.015);
  histo->GetXaxis()->SetLabelSize  (0.140);
  histo->GetXaxis()->SetNdivisions (  505);
  histo->GetXaxis()->SetTitleFont  (   42);
  histo->GetXaxis()->SetTitleOffset( 0.95);
  histo->GetXaxis()->SetTitleSize  (0.140);
  histo->GetXaxis()->SetTickLength (0.07 );

  histo->GetYaxis()->SetTitle(ytitle.Data());
  histo->GetYaxis()->SetLabelFont  (   42);
  histo->GetYaxis()->SetLabelOffset(0.015);
  histo->GetYaxis()->SetLabelSize  (0.120);
  histo->GetYaxis()->SetNdivisions (  505);
  histo->GetYaxis()->SetTitleFont  (   42);
  histo->GetYaxis()->SetTitleOffset(  0.4);
  histo->GetYaxis()->SetTitleSize  (0.120);
  histo->GetYaxis()->SetTickLength (0.03 );

  histo->SetLineColor  (kBlack);
  histo->SetMarkerStyle(kFullCircle);
}

void finalPlot(int nsel = 0, int ReBin = 1, TString XTitle = "N_{jets}", TString units = "", TString plotName = "histoWW_56.root", TString outputName = "njets",
                bool isLogY = false, int year = 2017, TString higgsLabel = "", double lumi = 1.0, bool isBlind = false, TString extraLabel = "",
		bool show2D = true, bool applyScaling = false, TString mlfitResult = "", TString channelName = "") {

  //gInterpreter->ExecuteMacro("GoodStyle.C");
  //gROOT->LoadMacro("StandardPlot.C");
  gStyle->SetOptStat(0);

  TFile* file = new TFile(plotName, "read");  if(!file) {printf("File %s does not exist\n",plotName.Data()); return;}

  StandardPlot myPlot;
  myPlot.setLumi(lumi);
  myPlot.setLabel(XTitle);
  myPlot.addLabel(extraLabel.Data());
  myPlot.setHiggsLabel(higgsLabel.Data());
  myPlot.setUnits(units);

  double SF_yield[nPlotCategories]; 
  double SF_yield_unc[nPlotCategories];
  TFile *mlfit=0;
  if(mlfitResult!="") {
    mlfit=TFile::Open(mlfitResult); assert(mlfit);
  }
  TH1F* _hist[nPlotCategories];
  TH1F* hData = 0;
  TH1F* hBck = 0;
  for(int ic=0; ic<nPlotCategories; ic++){
    _hist[ic] = (TH1F*)file->Get(Form("histo%d",ic));
    if(ic == kPlotData) {
      //for(int i=1; i<=_hist[ic]->GetNbinsX(); i++){
      //  if(i>20)_hist[ic]->SetBinContent(i,0);
      //}
      hData = (TH1F*)_hist[ic]->Clone();
      hBck  = (TH1F*)_hist[ic]->Clone(); hBck->Scale(0);
    }
    if(isBlind == true && ic == kPlotData) continue;

    if(mlfitResult!="" && ic != kPlotData && ic != kPlotBSM) {
      if     ((TH1F*)mlfit->Get(Form("shapes_prefit/%s/%s",channelName.Data(),plotBaseNames[ic].Data()))) {
        double sum[3] = {0, 0, 0};
        for(int i=1; i<=((TH1F*)mlfit->Get(Form("shapes_fit_s/%s/%s",channelName.Data(),plotBaseNames[ic].Data())))->GetNbinsX(); i++){
          //sum[0] = sum[0] + ((TH1F*)mlfit->Get(Form("shapes_fit_s/%s/%s",channelName.Data(),plotBaseNames[ic].Data()))) ->GetBinContent(i);
	  //sum[1] = sum[1] + ((TH1F*)mlfit->Get(Form("shapes_prefit/%s/%s",channelName.Data(),plotBaseNames[ic].Data())))->GetBinContent(i);
	  sum[2] = sum[2] + ((TH1F*)mlfit->Get(Form("shapes_fit_s/%s/%s",channelName.Data(),plotBaseNames[ic].Data())))->GetBinError(i);
        }
        sum[0] = ((TH1F*)mlfit->Get(Form("shapes_fit_s/%s/%s",channelName.Data(),plotBaseNames[ic].Data()))) ->GetSumOfWeights();
	sum[1] = ((TH1F*)mlfit->Get(Form("shapes_prefit/%s/%s",channelName.Data(),plotBaseNames[ic].Data())))->GetSumOfWeights();
        SF_yield[ic]     = sum[0] / sum[1];
        SF_yield_unc[ic] = sum[2] / sum[0];
        printf("POST FIT SFs: SF[%s] = %.3f +/- %.3f | %.3f\n",plotBaseNames[ic].Data(),SF_yield[ic],SF_yield_unc[ic],
	       ((TH1F*)mlfit->Get(Form("shapes_fit_s/%s/%s",channelName.Data(),plotBaseNames[ic].Data()))) ->GetSumOfWeights()/
	       ((TH1F*)mlfit->Get(Form("shapes_prefit/%s/%s",channelName.Data(),plotBaseNames[ic].Data())))->GetSumOfWeights());
      }
      _hist[ic]->Scale(SF_yield[ic]);
      for(int i=1; i<=_hist[ic]->GetNbinsX(); i++){
        //_hist[ic]->SetBinContent(i,_hist[ic]->GetBinContent(i)*SF_yield[ic]);
        _hist[ic]->SetBinError(i,TMath::Sqrt(TMath::Power(_hist[ic]->GetBinError(i)*SF_yield[ic],2)+TMath::Power(_hist[ic]->GetBinContent(i)*SF_yield_unc[ic],2)));
      }
    } // mltFit result

    if(ic == kPlotDY) _hist[ic]->Scale(lumi);
    if(ic != kPlotData && ic != kPlotBSM) hBck->Add(_hist[ic]);

    if(_hist[ic]->GetSumOfWeights() > 0) myPlot.setMCHist(ic, _hist[ic]);
  }
  if(hBck->GetSumOfWeights() == 0) return;
  double scale = hData->GetSumOfWeights()/hBck->GetSumOfWeights();
  printf("data/bck: %f / %f = %f\n",hData->GetSumOfWeights(),hBck->GetSumOfWeights(),scale);
  if(applyScaling == true) hBck->Scale(scale);

  for(int ic=0; ic<nPlotCategories; ic++){
    if(isBlind == true && ic == kPlotData) continue;
    if(applyScaling == true && ic != kPlotData && ic != kPlotBSM) _hist[ic]->Scale(scale);
    if(_hist[ic]->GetSumOfWeights() > 0) myPlot.setMCHist(ic, _hist[ic]);
  }

  myPlot.setOverlaid(false);

  TCanvas* c1 = new TCanvas("c1", "c1",5,5,500,500);

  if(show2D==false){
  if(isLogY == true) c1->SetLogy();
  if(isLogX == true) c1->SetLogx();
  myPlot.Draw(ReBin);  // Can pass a rebin 
  CMS_lumi( c1, year, 12 );
  } else {
  c1->SetBottomMargin(0.1);
  c1->cd();
  TPad *pad1 = new TPad("pad1", "pad1",0.00,0.30,1.00,1.00);
  TPad *pad2 = new TPad("pad2", "pad2",0.00,0.00,1.00,0.29);
  pad1->SetBottomMargin(0);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);
  pad1->Draw();
  pad2->Draw();

  pad1->cd();
  if(isLogY == true) c1->SetLogy();
  if(isLogY == true) pad1->SetLogy();
  if(isLogX == true) c1->SetLogx();
  if(isLogX == true) pad1->SetLogx();
  
  if(isLogSpecial) {c1->SetLogx();pad1->SetLogx();pad2->SetLogx();}

  myPlot.Draw(ReBin);
  CMS_lumi( pad1, year, 12 );

  pad2->cd();
  //pad2->SetGridy();
  hBck ->Rebin(ReBin);
  hData->Rebin(ReBin);
  TH1D* hTotalDivision = (TH1D*) hData->Clone();
  hTotalDivision->Reset();
  TH1D* hDataDivision = (TH1D*) hData->Clone();
  hDataDivision->Reset();
  TH1D* hRatio = (TH1D*) hData->Clone();
  hRatio->Reset();
  TH1D* hBand = (TH1D*) hData->Clone();
  hBand->Reset();

  hDataDivision ->Add(hData );
  hTotalDivision->Add(hBck  );
  //hTotalDivision->Scale(hDataDivision->GetSumOfWeights()/hTotalDivision->GetSumOfWeights());
  TGraphAsymmErrors *g = new TGraphAsymmErrors(hDataDivision);
  bool showPulls = false;
  bool useGarwood = false;
  for(int i=1; i<=hDataDivision->GetNbinsX(); i++){
    if(showPulls){
      double pull = 0.0;
      if(useGarwood == false){
        if((hDataDivision->GetBinError(i) > 0 || hTotalDivision->GetBinError(i) > 0) && hDataDivision->GetBinContent(i) > 0){
          pull = (hDataDivision->GetBinContent(i)-hTotalDivision->GetBinContent(i))/sqrt(hDataDivision->GetBinError(i)*hDataDivision->GetBinError(i)+hTotalDivision->GetBinError(i)*hTotalDivision->GetBinError(i));
        }
      } 
      else {
        pull = TMath::Sqrt(2)*TMath::ErfInverse(-1+2*ROOT::Math::poisson_cdf(hDataDivision->GetBinContent(i),hTotalDivision->GetBinContent(i))); 
      }
      hRatio->SetBinContent(i,pull);
      hRatio->SetBinError(i,1.0);
      if(printRatios) printf("pull(%3d): da: %f pred: %f --> %f\n",i,hDataDivision ->GetBinContent(i),hTotalDivision->GetBinContent(i),pull);
    }
    else {
      double N = g->GetY()[i-1];
      double alpha=(1-0.6827);
      double L = (N==0) ? 0 : (ROOT::Math::gamma_quantile(alpha/2,N,1.));
      double U = ROOT::Math::gamma_quantile_c(alpha/2,N+1,1);
      //double diff = hDataDivision->GetBinError(i);
      double diff = (U-L)/2;
      if( N != hDataDivision ->GetBinContent(i)) cout << "PROBLEM" << endl;
      double pull = 1.0; double pullerr = 0.0;
      if(hDataDivision->GetBinContent(i) > 0 && hTotalDivision->GetBinContent(i) > 0){
        pull = (hDataDivision->GetBinContent(i)/hTotalDivision->GetBinContent(i));
	pullerr = pull*diff/hDataDivision->GetBinContent(i);
      }
      //if(pull<0.97) pull = 0.98+gRandom->Uniform()*0.01;
      //if(pull>1.05) pull = 1.05+gRandom->Uniform()*0.02;
      hRatio->SetBinContent(i,pull);
      hRatio->SetBinError(i,pullerr);
      hBand->SetBinContent(i,1);
      hBand->SetBinError(i,hTotalDivision->GetBinError(i)/hTotalDivision->GetBinContent(i));
      //if(pull<0.97||pull>1.03)
      if(printRatios) printf("ratio(%3d): %f +/- %f --> da: %f +/- %f (%f) pred: %f +/- %f\n",i,pull,pullerr,hDataDivision ->GetBinContent(i),hDataDivision ->GetBinError(i),diff,hTotalDivision->GetBinContent(i),hTotalDivision->GetBinError(i));
    }
  }
  if(showPulls) atributes(hRatio,XTitle.Data(),"Pull",units.Data());
  else          atributes(hRatio,XTitle.Data(),"Data/Bkg.",units.Data());
  hRatio->Draw("e");
  hBand->SetFillColor(12);
  hBand->SetFillStyle(3002);
  hBand->SetMarkerSize(0);
  hBand->SetLineWidth(0);
  hBand->Draw("E2same");

  // Draw a line throgh y=0
  double theLines[2] = {1.0, 0.5};
  if(showPulls) {theLines[0] = 0.0; theLines[1] = 1.5;}
  TLine* baseline = new TLine(hRatio->GetXaxis()->GetXmin(), theLines[0],
                              hRatio->GetXaxis()->GetXmax(), theLines[0]);
  baseline->SetLineStyle(kDashed);
  baseline->Draw();
  // Set the y-axis range symmetric around y=0
  Double_t dy = TMath::Max(TMath::Abs(hRatio->GetMaximum()),
                           TMath::Abs(hRatio->GetMinimum())) + theLines[1];
  if(showPulls) hRatio->GetYaxis()->SetRangeUser(-dy, +dy);
  else          hRatio->GetYaxis()->SetRangeUser(0.301, +1.699);
  hRatio->GetYaxis()->CenterTitle();
  eraselabel(pad1,hData->GetXaxis()->GetLabelSize());
  }

  char CommandToExec[300];
  sprintf(CommandToExec,"mkdir -p plots");
  gSystem->Exec(CommandToExec);  

  if(strcmp(outputName.Data(),"") != 0){
    TString myOutputFile;
    outputName = Form("%s_%d",outputName.Data(),year);
    myOutputFile = Form("plots/%s.eps",outputName.Data());
    //c1->SaveAs(myOutputFile.Data());
    myOutputFile = Form("plots/%s.png",outputName.Data());
    c1->SaveAs(myOutputFile.Data());
    myOutputFile = Form("plots/%s.pdf",outputName.Data());
    c1->SaveAs(myOutputFile.Data());
    myOutputFile = Form("plots/%s.root",outputName.Data());
    //c1->SaveAs(myOutputFile.Data());
  }

  bool computePU = false;
  if(computePU){
    hBck->Scale(hData->GetSumOfWeights()/hBck->GetSumOfWeights());
    TH1D * npvWeights =  (TH1D*)hData->Clone("npvWeights");
    npvWeights->Sumw2();
    npvWeights->Divide(hBck);
    for(int i=1; i<=npvWeights->GetNbinsX(); i++){
      if(npvWeights->GetBinContent(i) > 2) {
        printf("Big number in (%d): %f, set to 2\n",i,npvWeights->GetBinContent(i));npvWeights->SetBinContent(i,2);
      }
    }
    TFile output(Form("npvWeights_%d.root",year),"RECREATE");
    npvWeights->Write();
    output.Close();
  }

}
