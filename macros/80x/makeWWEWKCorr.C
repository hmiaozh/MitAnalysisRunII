#include <TROOT.h>                  // access to gROOT, entry point to ROOT system
#include <TSystem.h>                // interface to OS
#include <vector>                   // STL vector class
#include <iostream>                 // standard I/O
#include <iomanip>                  // functions to format standard I/O
#include <fstream>                  // functions for file I/O
#include <string>                   // C++ string class
#include <sstream>                  // class for parsing strings
#include <TFile.h>                  // File handle
#include <TH1D.h>                   // 1D histogram class
#include <TMath.h>                  // TMath

void makeWWEWKCorr(int debug = 0) 
{
  const int nPoints = 50;

  // input data
  const TString xs_pt3_qcd_Name("MitAnalysisRunII/data/80x/WWEWKCorr/xs_pt3_qcd.txt");
  const TString xs_pt3_qcd_ewk_Name("MitAnalysisRunII/data/80x/WWEWKCorr/xs_pt3_qcd_ewk.txt");
  const TString xs_m35_qcd_Name("MitAnalysisRunII/data/80x/WWEWKCorr/xs_m35_qcd.txt");
  const TString xs_m35_qcd_ewk_Name("MitAnalysisRunII/data/80x/WWEWKCorr/xs_m35_qcd_ewk.txt");

  vector<Double_t> min_xs_pt3_qcd;
  vector<Double_t> max_xs_pt3_qcd;
  vector<Double_t> xs_xs_pt3_qcd;
  vector<Double_t> xse_up_xs_pt3_qcd;
  vector<Double_t> xse_down_xs_pt3_qcd;
  {
    ifstream ifs;
    ifs.open(xs_pt3_qcd_Name.Data());
    assert(ifs.is_open());
    string line;
    while(getline(ifs,line)) {
      Double_t min,max,xs,xse_up,xse_down;
      stringstream ss(line);
      ss >> min >> max >> xs >> xse_up >> xse_down;
      min_xs_pt3_qcd.push_back(min);
      max_xs_pt3_qcd.push_back(max);
      xs_xs_pt3_qcd.push_back(xs);
      xse_up_xs_pt3_qcd.push_back(xse_up);
      xse_down_xs_pt3_qcd.push_back(xse_down);
    }
    ifs.close();
  }

  vector<Double_t> min_xs_pt3_qcd_ewk;
  vector<Double_t> max_xs_pt3_qcd_ewk;
  vector<Double_t> xs_xs_pt3_qcd_ewk;
  vector<Double_t> xse_up_xs_pt3_qcd_ewk;
  vector<Double_t> xse_down_xs_pt3_qcd_ewk;
  {
    ifstream ifs;
    ifs.open(xs_pt3_qcd_ewk_Name.Data());
    assert(ifs.is_open());
    string line;
    while(getline(ifs,line)) {
      Double_t min,max,xs,xse_up,xse_down;
      stringstream ss(line);
      ss >> min >> max >> xs >> xse_up >> xse_down;
      min_xs_pt3_qcd_ewk.push_back(min);
      max_xs_pt3_qcd_ewk.push_back(max);
      xs_xs_pt3_qcd_ewk.push_back(xs);
      xse_up_xs_pt3_qcd_ewk.push_back(xse_up);
      xse_down_xs_pt3_qcd_ewk.push_back(xse_down);
    }
    ifs.close();
  }

  vector<Double_t> min_xs_mll_qcd;
  vector<Double_t> max_xs_mll_qcd;
  vector<Double_t> xs_xs_mll_qcd;
  vector<Double_t> xse_up_xs_mll_qcd;
  vector<Double_t> xse_down_xs_mll_qcd;
  {
    ifstream ifs;
    ifs.open(xs_m35_qcd_Name.Data());
    assert(ifs.is_open());
    string line;
    while(getline(ifs,line)) {
      Double_t min,max,xs,xse_up,xse_down;
      stringstream ss(line);
      ss >> min >> max >> xs >> xse_up >> xse_down;
      min_xs_mll_qcd.push_back(min);
      max_xs_mll_qcd.push_back(max);
      xs_xs_mll_qcd.push_back(xs);
      xse_up_xs_mll_qcd.push_back(xse_up);
      xse_down_xs_mll_qcd.push_back(xse_down);
    }
    ifs.close();
  }

  vector<Double_t> min_xs_mll_qcd_ewk;
  vector<Double_t> max_xs_mll_qcd_ewk;
  vector<Double_t> xs_xs_mll_qcd_ewk;
  vector<Double_t> xse_up_xs_mll_qcd_ewk;
  vector<Double_t> xse_down_xs_mll_qcd_ewk;
  {
    ifstream ifs;
    ifs.open(xs_m35_qcd_ewk_Name.Data());
    assert(ifs.is_open());
    string line;
    while(getline(ifs,line)) {
      Double_t min,max,xs,xse_up,xse_down;
      stringstream ss(line);
      ss >> min >> max >> xs >> xse_up >> xse_down;
      min_xs_mll_qcd_ewk.push_back(min);
      max_xs_mll_qcd_ewk.push_back(max);
      xs_xs_mll_qcd_ewk.push_back(xs);
      xse_up_xs_mll_qcd_ewk.push_back(xse_up);
      xse_down_xs_mll_qcd_ewk.push_back(xse_down);
    }
    ifs.close();
  }

  if(min_xs_pt3_qcd.size()     != nPoints ||
     min_xs_pt3_qcd_ewk.size() != nPoints ||
     min_xs_mll_qcd.size()     != nPoints ||
     min_xs_mll_qcd_ewk.size() != nPoints) {printf("PROBLEM WITH NPOINTS\n"); return;}

  Float_t xbinsPtlm[nPoints+1];
  Float_t xbinsMll[nPoints+1];
  for(int i=0; i<nPoints; i++){
    xbinsPtlm[i] = min_xs_pt3_qcd[i];
    xbinsMll[i]  = min_xs_mll_qcd[i];
  }
  xbinsPtlm[nPoints] = max_xs_pt3_qcd[nPoints-1];
  xbinsMll[nPoints]  = max_xs_mll_qcd[nPoints-1];

  TH1D *xs_Ptlm_QCD = new TH1D(Form("xs_Ptlm_QCD"), Form("xs_Ptlm_QCD"), nPoints, xbinsPtlm);
  TH1D *xs_Ptlm_QCD_EWK = new TH1D(Form("xs_Ptlm_QCD_EWK"), Form("xs_Ptlm_QCD_EWK"), nPoints, xbinsPtlm);
  TH1D *ratio_Ptlm = new TH1D(Form("ratio_Ptlm"), Form("ratio_Ptlm"), nPoints, xbinsPtlm);
  TH1D *xs_Mll_QCD = new TH1D(Form("xs_Mll_QCD"), Form("xs_Mll_QCD"), nPoints, xbinsMll);
  TH1D *xs_Mll_QCD_EWK = new TH1D(Form("xs_Mll_QCD_EWK"), Form("xs_Mll_QCD_EWK"), nPoints, xbinsMll);
  TH1D *ratio_Mll = new TH1D(Form("ratio_Mll"), Form("ratio_Mll"), nPoints, xbinsMll);

  double ratio, ratioe;
  for(int i=0; i<nPoints; i++){
    xs_Ptlm_QCD    ->SetBinContent(i+1,xs_xs_pt3_qcd[i]);     xs_Ptlm_QCD    ->SetBinError(i+1,xse_up_xs_pt3_qcd[i]);
    xs_Ptlm_QCD_EWK->SetBinContent(i+1,xs_xs_pt3_qcd_ewk[i]); xs_Ptlm_QCD_EWK->SetBinError(i+1,xse_up_xs_pt3_qcd_ewk[i]);
    ratio = 1; ratioe = 0;
    if(xs_xs_pt3_qcd[i] > 0){
      ratio = xs_xs_pt3_qcd_ewk[i]/xs_xs_pt3_qcd[i];
      ratioe = ratio * sqrt(TMath::Power(xse_up_xs_pt3_qcd[i]/xs_xs_pt3_qcd[i],2)+TMath::Power(xse_up_xs_pt3_qcd_ewk[i]/xs_xs_pt3_qcd_ewk[i],2));
    }
    ratio_Ptlm->SetBinContent(i+1,ratio); ratio_Ptlm->SetBinError(i+1,ratioe);

    xs_Mll_QCD    ->SetBinContent(i+1,xs_xs_mll_qcd[i]);      xs_Mll_QCD    ->SetBinError(i+1,xse_up_xs_mll_qcd[i]);
    xs_Mll_QCD_EWK->SetBinContent(i+1,xs_xs_mll_qcd_ewk[i]);  xs_Mll_QCD_EWK->SetBinError(i+1,xse_up_xs_mll_qcd_ewk[i]);
    ratio = 1; ratioe = 0;
    if(xs_xs_mll_qcd[i] > 0){
      ratio = xs_xs_mll_qcd_ewk[i]/xs_xs_mll_qcd[i];
      ratioe = ratio * sqrt(TMath::Power(xse_up_xs_mll_qcd[i]/xs_xs_mll_qcd[i],2)+TMath::Power(xse_up_xs_mll_qcd_ewk[i]/xs_xs_mll_qcd_ewk[i],2));
    }
    ratio_Mll->SetBinContent(i+1,ratio); ratio_Mll->SetBinError(i+1,ratioe);

    if(debug == 1) printf("%d: (%f)%f/%f=%f (%f)%f/%f=%f\n",i,
                          xs_Ptlm_QCD_EWK->GetXaxis()->GetBinLowEdge(i),
                          xs_Ptlm_QCD_EWK->GetBinContent(i+1),xs_Ptlm_QCD->GetBinContent(i+1),xs_Ptlm_QCD_EWK->GetBinContent(i+1)/xs_Ptlm_QCD->GetBinContent(i+1),
                          xs_Mll_QCD_EWK->GetXaxis()->GetBinLowEdge(i),
			  xs_Mll_QCD_EWK->GetBinContent(i+1),xs_Mll_QCD->GetBinContent(i+1),xs_Mll_QCD_EWK->GetBinContent(i+1)/xs_Mll_QCD->GetBinContent(i+1));
  }
  
  TFile* outFileHistos = new TFile("WW_EWK_Corr.root","recreate");
  outFileHistos->cd();
  xs_Ptlm_QCD->Write();
  xs_Ptlm_QCD_EWK->Write();
  ratio_Ptlm->Write();
  xs_Mll_QCD->Write();
  xs_Mll_QCD_EWK->Write();
  ratio_Mll->Write();
  outFileHistos->Close();

}
