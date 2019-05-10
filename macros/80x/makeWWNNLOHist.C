#include <TROOT.h>
#include <TFile.h>
#include <TSystem.h>
#include <TString.h>
#include <TH1D.h>
#include <TMath.h>
#include <iostream>
#include <fstream>

#include "WWAnalysis/resummation/WWpTreweight.h"

void makeWWNNLOHist(bool changeValues = false){
  WWpTreweight theWWpTreweight(
              "WWAnalysis/resummation/central.dat",
              "WWAnalysis/resummation/resum_up.dat",
              "WWAnalysis/resummation/resum_down.dat",
              "WWAnalysis/resummation/scale_up.dat",
              "WWAnalysis/resummation/scale_down.dat",
              "WWAnalysis/resummation/nnlo_central.dat",
              "WWAnalysis/resummation/powheg_2l2nu_nlo.dat",
              "WWAnalysis/resummation/powheg_2l2nu_qup_nlo.dat",
              "WWAnalysis/resummation/powheg_2l2nu_qdown_nlo.dat",
              "WWAnalysis/resummation/powheg_2l2nu_sup_nlo.dat",
              "WWAnalysis/resummation/powheg_2l2nu_sdown_nlo.dat",
              "WWAnalysis/resummation/powheg_2l2nu_nnlo.dat");

  TFile *fWWPtRatio = TFile::Open(Form("MitAnalysisRunII/data/74x/MyRatioWWpTHistogramAll.root"));
  TH1D *fhDWWPtRatio_NLO       = (TH1D*)(fWWPtRatio->Get("wwpt"));             fhDWWPtRatio_NLO      ->SetDirectory(0);
  TH1D *fhDWWPtRatio_scaleup   = (TH1D*)(fWWPtRatio->Get("wwpt_scaleup"));     fhDWWPtRatio_scaleup  ->SetDirectory(0);
  TH1D *fhDWWPtRatio_scaledown = (TH1D*)(fWWPtRatio->Get("wwpt_scaledown"));   fhDWWPtRatio_scaledown->SetDirectory(0);
  TH1D *fhDWWPtRatio_resumup   = (TH1D*)(fWWPtRatio->Get("wwpt_resumup"));     fhDWWPtRatio_resumup  ->SetDirectory(0);
  TH1D *fhDWWPtRatio_resumdown = (TH1D*)(fWWPtRatio->Get("wwpt_resumdown"));   fhDWWPtRatio_resumdown->SetDirectory(0);
  TH1D *fhDWWPtRatio_NNLO      = (TH1D*)(fhDWWPtRatio_NLO->Clone("wwpt_NNLO"));fhDWWPtRatio_NNLO     ->SetDirectory(0);
  fWWPtRatio->Close();

  for(int i=1; i<=fhDWWPtRatio_NLO->GetNbinsX(); i++) {
    if(changeValues){
      fhDWWPtRatio_NLO->SetBinContent(i,theWWpTreweight.reweight(fhDWWPtRatio_NLO->GetBinCenter(i),0));
    }
    else {
      printf("Type0(%3d) %f %f %f %f\n",i,fhDWWPtRatio_NLO->GetBinCenter(i),fhDWWPtRatio_NLO->GetBinContent(i),theWWpTreweight.reweight(fhDWWPtRatio_NLO->GetBinCenter(i),0),fhDWWPtRatio_NLO->GetBinContent(i)-theWWpTreweight.reweight(fhDWWPtRatio_NLO->GetBinCenter(i),0));
    }
  }

  for(int i=1; i<=fhDWWPtRatio_resumup->GetNbinsX(); i++) {
    if(changeValues){
      fhDWWPtRatio_resumup->SetBinContent(i,theWWpTreweight.reweight(fhDWWPtRatio_resumup->GetBinCenter(i),1));
    }
    else {
      printf("Type1(%3d) %f\n",i,fhDWWPtRatio_resumup->GetBinContent(i)-theWWpTreweight.reweight(fhDWWPtRatio_resumup->GetBinCenter(i),1));
    }
  }

  for(int i=1; i<=fhDWWPtRatio_resumdown->GetNbinsX(); i++) {
    if(changeValues){
      fhDWWPtRatio_resumdown->SetBinContent(i,theWWpTreweight.reweight(fhDWWPtRatio_resumdown->GetBinCenter(i),2));
    }
    else {
      printf("Type2(%3d) %f\n",i,fhDWWPtRatio_resumdown->GetBinContent(i)-theWWpTreweight.reweight(fhDWWPtRatio_resumdown->GetBinCenter(i),2));
    }
  }

  for(int i=1; i<=fhDWWPtRatio_scaleup->GetNbinsX(); i++) {
    if(changeValues){
      fhDWWPtRatio_scaleup->SetBinContent(i,theWWpTreweight.reweight(fhDWWPtRatio_scaleup->GetBinCenter(i),3));
    }
    else {
      printf("Type3(%3d) %f\n",i,fhDWWPtRatio_scaleup->GetBinContent(i)-theWWpTreweight.reweight(fhDWWPtRatio_scaleup->GetBinCenter(i),3));
    }
  }

  for(int i=1; i<=fhDWWPtRatio_scaledown->GetNbinsX(); i++) {
    if(changeValues){
      fhDWWPtRatio_scaledown->SetBinContent(i,theWWpTreweight.reweight(fhDWWPtRatio_scaledown->GetBinCenter(i),4));
    }
    else {
      printf("Type4(%3d) %f\n",i,fhDWWPtRatio_scaledown->GetBinContent(i)-theWWpTreweight.reweight(fhDWWPtRatio_scaledown->GetBinCenter(i),4));
    }
  }

  for(int i=1; i<=fhDWWPtRatio_NNLO->GetNbinsX(); i++) {
    if(changeValues){
      fhDWWPtRatio_NNLO->SetBinContent(i,theWWpTreweight.reweight(fhDWWPtRatio_NNLO->GetBinCenter(i),5));
    }
    else {
      printf("Type5(%3d) %f\n",i,fhDWWPtRatio_NNLO->GetBinContent(i)-theWWpTreweight.reweight(fhDWWPtRatio_NNLO->GetBinCenter(i),5));
    }
  }

  if(changeValues){
    TFile* outFile = new TFile("MyRatioWWpTHistogramAll.root","recreate");
    outFile->cd();
    fhDWWPtRatio_NLO	  ->Write();
    fhDWWPtRatio_scaleup  ->Write();
    fhDWWPtRatio_scaledown->Write();
    fhDWWPtRatio_resumup  ->Write();
    fhDWWPtRatio_resumdown->Write();
    fhDWWPtRatio_NNLO	   ->Write();
    outFile->Close();
  }
}
