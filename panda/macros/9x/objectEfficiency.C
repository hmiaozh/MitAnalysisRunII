#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TString.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <TCanvas.h>
#include "TStyle.h"
#include "TSystem.h"
#include "TLorentzVector.h"

void atributes(TH2D *histo, TString xtitle, TString ytitle, TString title){

  histo->SetTitle(title.Data());
  histo->GetXaxis()->SetLabelFont  (   42);
  histo->GetXaxis()->SetLabelOffset(0.015);
  histo->GetXaxis()->SetLabelSize  (0.030);
  histo->GetXaxis()->SetNdivisions (  505);
  histo->GetXaxis()->SetTitleFont  (   42);
  histo->GetXaxis()->SetTitleOffset( 1.20);
  histo->GetXaxis()->SetTitleSize  (0.035);
  histo->GetXaxis()->SetTickLength (0.07 );

  histo->GetYaxis()->SetTitle(ytitle.Data());
  histo->GetYaxis()->SetLabelFont  (   42);
  histo->GetYaxis()->SetLabelOffset(0.015);
  histo->GetYaxis()->SetLabelSize  (0.040);
  histo->GetYaxis()->SetNdivisions (  505);
  histo->GetYaxis()->SetTitleFont  (   42);
  histo->GetYaxis()->SetTitleOffset( 1.40);
  histo->GetYaxis()->SetTitleSize  (0.030);
  histo->GetYaxis()->SetTickLength (0.03 );

  histo->GetZaxis()->SetLabelSize  (0.020);

  histo->SetLineColor  (kBlack);
  histo->SetMarkerStyle(kFullCircle);
}

void objectEfficiency(TString fileName, TString format = "png"){

  gStyle->SetOptStat(0);
  gStyle->SetPaintTextFormat(".3f");
  gStyle->SetPalette(1);

  TFile *fFile = TFile::Open(fileName.Data());
  TH2D *hDNumMuEtaPt = (TH2D*)(fFile->Get("hDNumMuEtaPt")); assert(hDNumMuEtaPt); hDNumMuEtaPt->SetDirectory(0);     
  TH2D *hDNumElEtaPt = (TH2D*)(fFile->Get("hDNumElEtaPt")); assert(hDNumElEtaPt); hDNumElEtaPt->SetDirectory(0);	 
  TH2D *hDNumPhEtaPt = (TH2D*)(fFile->Get("hDNumPhEtaPt")); assert(hDNumPhEtaPt); hDNumPhEtaPt->SetDirectory(0); 
  TH2D *hDDenMuEtaPt = (TH2D*)(fFile->Get("hDDenMuEtaPt")); assert(hDDenMuEtaPt); hDDenMuEtaPt->SetDirectory(0);	   
  TH2D *hDDenElEtaPt = (TH2D*)(fFile->Get("hDDenElEtaPt")); assert(hDDenElEtaPt); hDDenElEtaPt->SetDirectory(0);	 
  TH2D *hDDenPhEtaPt = (TH2D*)(fFile->Get("hDDenPhEtaPt")); assert(hDDenPhEtaPt); hDDenPhEtaPt->SetDirectory(0); 
  delete fFile;

  for(int i=1; i<=hDDenMuEtaPt->GetNbinsX(); i++){
    for(int j=1; j<=hDDenMuEtaPt->GetNbinsY(); j++){
      double eff = 1; double unc = 0;
      if(hDDenMuEtaPt->GetBinContent(i,j) > 0){
  	eff = hDNumMuEtaPt->GetBinContent(i,j)/hDDenMuEtaPt->GetBinContent(i,j);
  	unc =sqrt(eff*(1-eff)/hDDenMuEtaPt->GetBinContent(i,j));
      }
      hDDenMuEtaPt->SetBinContent(i,j,eff);
      hDDenMuEtaPt->SetBinError  (i,j,unc);
    }
  }

  for(int i=1; i<=hDDenElEtaPt->GetNbinsX(); i++){
    for(int j=1; j<=hDDenElEtaPt->GetNbinsY(); j++){
      double eff = 1; double unc = 0;
      if(hDDenElEtaPt->GetBinContent(i,j) > 0){
  	eff = hDNumElEtaPt->GetBinContent(i,j)/hDDenElEtaPt->GetBinContent(i,j);
  	unc =sqrt(eff*(1-eff)/hDDenElEtaPt->GetBinContent(i,j));
      }
      hDDenElEtaPt->SetBinContent(i,j,eff);
      hDDenElEtaPt->SetBinError  (i,j,unc);
    }
  }

  for(int i=1; i<=hDDenPhEtaPt->GetNbinsX(); i++){
    for(int j=1; j<=hDDenPhEtaPt->GetNbinsY(); j++){
      double eff = 1; double unc = 0;
      if(hDDenPhEtaPt->GetBinContent(i,j) > 0){
  	eff = hDNumPhEtaPt->GetBinContent(i,j)/hDDenPhEtaPt->GetBinContent(i,j);
  	unc =sqrt(eff*(1-eff)/hDDenPhEtaPt->GetBinContent(i,j));
      }
      hDDenPhEtaPt->SetBinContent(i,j,eff);
      hDDenPhEtaPt->SetBinError  (i,j,unc);
    }
  }

  atributes(hDDenMuEtaPt,"|#eta|","p_{T} [GeV]","Muon efficiency");
  atributes(hDDenElEtaPt,"|#eta|","p_{T} [GeV]","Electron efficiency");
  atributes(hDDenPhEtaPt,"|#eta|","p_{T} [GeV]","Photon efficiency");
  TCanvas* c00 = new TCanvas("c00","c00",5,5,500,500);
  TCanvas* c01 = new TCanvas("c01","c01",5,5,500,500);
  TCanvas* c02 = new TCanvas("c02","c02",5,5,500,500);
  c00->cd(); hDDenMuEtaPt->Draw("colz,text,e");
  c01->cd(); hDDenElEtaPt->Draw("colz,text,e");
  c02->cd(); hDDenPhEtaPt->Draw("colz,text,e");
  TString outputName;
  outputName = Form("hDDenMuEtaPt.%s",format.Data());  c00->SaveAs(outputName.Data());
  outputName = Form("hDDenElEtaPt.%s",format.Data());  c01->SaveAs(outputName.Data());
  outputName = Form("hDDenPhEtaPt.%s",format.Data());  c02->SaveAs(outputName.Data());

  char output[200];
  sprintf(output,"histo_objectEfficiency.root");	
  TFile* outFileEff = new TFile(output,"recreate");
  outFileEff->cd();
  hDDenMuEtaPt->SetNameTitle(Form("hDEffMuEtaPt"),Form("hDEffMuEtaPt")); hDDenMuEtaPt->Write();
  hDDenElEtaPt->SetNameTitle(Form("hDEffElEtaPt"),Form("hDEffElEtaPt")); hDDenElEtaPt->Write();
  hDDenPhEtaPt->SetNameTitle(Form("hDEffPhEtaPt"),Form("hDEffPhEtaPt")); hDDenPhEtaPt->Write();
  outFileEff->Close();
}
