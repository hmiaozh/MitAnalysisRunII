#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TString.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <TLatex.h>
#include <TCanvas.h>
#include "TStyle.h"
#include "TSystem.h"
#include "TLorentzVector.h"

void DrawTLatex(Double_t x, Double_t y, Double_t tsize, const char* text, bool isLeft = true)
{
  TLatex* tl = new TLatex(x, y, text);

  tl->SetNDC();
  if(isLeft) tl->SetTextAlign(   11);
  else       tl->SetTextAlign(   31); 
  tl->SetTextFont (   42);
  tl->SetTextSize (tsize);

  tl->Draw("same");
}

void atributes(TH2D *histo, TString xtitle, TString ytitle, TString title, int option = 0){

  histo->SetTitle(title.Data()); histo->SetTitle("");
  histo->GetXaxis()->SetTitle(xtitle.Data());
  histo->GetXaxis()->SetLabelFont  (   42);
  histo->GetXaxis()->SetLabelOffset(0.015);
  histo->GetXaxis()->SetLabelSize  (0.030);
  histo->GetXaxis()->SetNdivisions (  505);
  histo->GetXaxis()->SetTitleFont  (   42);
  histo->GetXaxis()->SetTitleOffset( 1.20);
  histo->GetXaxis()->SetTitleSize  (0.030);
  histo->GetXaxis()->SetTickLength (0.07 );

  histo->GetYaxis()->SetTitle(ytitle.Data());
  histo->GetYaxis()->SetLabelFont  (   42);
  histo->GetYaxis()->SetLabelOffset(0.015);
  histo->GetYaxis()->SetLabelSize  (0.030);
  histo->GetYaxis()->SetNdivisions (  505);
  histo->GetYaxis()->SetTitleFont  (   42);
  histo->GetYaxis()->SetTitleOffset( 1.50);
  histo->GetYaxis()->SetTitleSize  (0.030);
  histo->GetYaxis()->SetTickLength (0.03 );

  histo->GetZaxis()->SetLabelSize  (0.020);

  if(option == 1){
    histo->GetXaxis()->SetLabelOffset(0.005);
    histo->GetXaxis()->SetLabelSize  (0.015);
    histo->GetYaxis()->SetLabelOffset(0.005);
    histo->GetYaxis()->SetLabelSize  (0.015);
    const Int_t NRGBs = 5;
    const Int_t NCont = 255;
    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);  
    TAxis *xa =histo->GetXaxis();
    xa->SetBinLabel(1 ,"2016 e#mu");
    xa->SetBinLabel(2 ,"2016 SR |#eta^{#gamma}|<1 bin 1");
    xa->SetBinLabel(3 ,"2016 SR |#eta^{#gamma}|<1 bin 2");
    xa->SetBinLabel(4 ,"2016 SR |#eta^{#gamma}|<1 bin 3");
    xa->SetBinLabel(5 ,"2016 SR |#eta^{#gamma}|<1 bin 4");
    xa->SetBinLabel(6 ,"2016 SR |#eta^{#gamma}|<1 bin 5");
    xa->SetBinLabel(7 ,"2016 SR |#eta^{#gamma}|>1 bin 1");
    xa->SetBinLabel(8 ,"2016 SR |#eta^{#gamma}|>1 bin 2");
    xa->SetBinLabel(9 ,"2016 SR |#eta^{#gamma}|>1 bin 3");
    xa->SetBinLabel(10,"2016 SR |#eta^{#gamma}|>1 bin 4");
    xa->SetBinLabel(11,"2016 SR |#eta^{#gamma}|>1 bin 5");
    xa->SetBinLabel(12,"2016 WZ bin 1");
    xa->SetBinLabel(13,"2016 WZ bin 2");
    xa->SetBinLabel(14,"2016 ZZ bin 1");
    xa->SetBinLabel(15,"2016 ZZ bin 2");
    xa->SetBinLabel(16,"2017 e#mu");
    xa->SetBinLabel(17,"2017 SR |#eta^{#gamma}|<1 bin 1");
    xa->SetBinLabel(18,"2017 SR |#eta^{#gamma}|<1 bin 2");
    xa->SetBinLabel(19,"2017 SR |#eta^{#gamma}|<1 bin 3");
    xa->SetBinLabel(20,"2017 SR |#eta^{#gamma}|<1 bin 4");
    xa->SetBinLabel(21,"2017 SR |#eta^{#gamma}|<1 bin 5");
    xa->SetBinLabel(22,"2017 SR |#eta^{#gamma}|>1 bin 1");
    xa->SetBinLabel(23,"2017 SR |#eta^{#gamma}|>1 bin 2");
    xa->SetBinLabel(24,"2017 SR |#eta^{#gamma}|>1 bin 3");
    xa->SetBinLabel(25,"2017 SR |#eta^{#gamma}|>1 bin 4");
    xa->SetBinLabel(26,"2017 SR |#eta^{#gamma}|>1 bin 5");
    xa->SetBinLabel(27,"2017 WZ bin 1");
    xa->SetBinLabel(28,"2017 WZ bin 2");
    xa->SetBinLabel(29,"2017 ZZ bin 1");
    xa->SetBinLabel(30,"2017 ZZ bin 2");
    xa->SetBinLabel(31,"2018 e#mu");
    xa->SetBinLabel(32,"2018 SR |#eta^{#gamma}|<1 bin 1");
    xa->SetBinLabel(33,"2018 SR |#eta^{#gamma}|<1 bin 2");
    xa->SetBinLabel(34,"2018 SR |#eta^{#gamma}|<1 bin 3");
    xa->SetBinLabel(35,"2018 SR |#eta^{#gamma}|<1 bin 4");
    xa->SetBinLabel(36,"2018 SR |#eta^{#gamma}|<1 bin 5");
    xa->SetBinLabel(37,"2018 SR |#eta^{#gamma}|>1 bin 1");
    xa->SetBinLabel(38,"2018 SR |#eta^{#gamma}|>1 bin 2");
    xa->SetBinLabel(39,"2018 SR |#eta^{#gamma}|>1 bin 3");
    xa->SetBinLabel(40,"2018 SR |#eta^{#gamma}|>1 bin 4");
    xa->SetBinLabel(41,"2018 SR |#eta^{#gamma}|>1 bin 5");
    xa->SetBinLabel(42,"2018 WZ bin 1");
    xa->SetBinLabel(43,"2018 WZ bin 2");
    xa->SetBinLabel(44,"2018 ZZ bin 1");
    xa->SetBinLabel(45,"2018 ZZ bin 2");
    xa->SetRangeUser(0,45);
    TAxis *ya =histo->GetYaxis();
    ya->SetBinLabel(1 ,"2016 e#mu");
    ya->SetBinLabel(2 ,"2016 SR |#eta^{#gamma}|<1 bin 1");
    ya->SetBinLabel(3 ,"2016 SR |#eta^{#gamma}|<1 bin 2");
    ya->SetBinLabel(4 ,"2016 SR |#eta^{#gamma}|<1 bin 3");
    ya->SetBinLabel(5 ,"2016 SR |#eta^{#gamma}|<1 bin 4");
    ya->SetBinLabel(6 ,"2016 SR |#eta^{#gamma}|<1 bin 5");
    ya->SetBinLabel(7 ,"2016 SR |#eta^{#gamma}|>1 bin 1");
    ya->SetBinLabel(8 ,"2016 SR |#eta^{#gamma}|>1 bin 2");
    ya->SetBinLabel(9 ,"2016 SR |#eta^{#gamma}|>1 bin 3");
    ya->SetBinLabel(10,"2016 SR |#eta^{#gamma}|>1 bin 4");
    ya->SetBinLabel(11,"2016 SR |#eta^{#gamma}|>1 bin 5");
    ya->SetBinLabel(12,"2016 WZ bin 1");
    ya->SetBinLabel(13,"2016 WZ bin 2");
    ya->SetBinLabel(14,"2016 ZZ bin 1");
    ya->SetBinLabel(15,"2016 ZZ bin 2");
    ya->SetBinLabel(16,"2017 e#mu");
    ya->SetBinLabel(17,"2017 SR |#eta^{#gamma}|<1 bin 1");
    ya->SetBinLabel(18,"2017 SR |#eta^{#gamma}|<1 bin 2");
    ya->SetBinLabel(19,"2017 SR |#eta^{#gamma}|<1 bin 3");
    ya->SetBinLabel(20,"2017 SR |#eta^{#gamma}|<1 bin 4");
    ya->SetBinLabel(21,"2017 SR |#eta^{#gamma}|<1 bin 5");
    ya->SetBinLabel(22,"2017 SR |#eta^{#gamma}|>1 bin 1");
    ya->SetBinLabel(23,"2017 SR |#eta^{#gamma}|>1 bin 2");
    ya->SetBinLabel(24,"2017 SR |#eta^{#gamma}|>1 bin 3");
    ya->SetBinLabel(25,"2017 SR |#eta^{#gamma}|>1 bin 4");
    ya->SetBinLabel(26,"2017 SR |#eta^{#gamma}|>1 bin 5");
    ya->SetBinLabel(27,"2017 WZ bin 1");
    ya->SetBinLabel(28,"2017 WZ bin 2");
    ya->SetBinLabel(29,"2017 ZZ bin 1");
    ya->SetBinLabel(30,"2017 ZZ bin 2");
    ya->SetBinLabel(31,"2018 e#mu");
    ya->SetBinLabel(32,"2018 SR |#eta^{#gamma}|<1 bin 1");
    ya->SetBinLabel(33,"2018 SR |#eta^{#gamma}|<1 bin 2");
    ya->SetBinLabel(34,"2018 SR |#eta^{#gamma}|<1 bin 3");
    ya->SetBinLabel(35,"2018 SR |#eta^{#gamma}|<1 bin 4");
    ya->SetBinLabel(36,"2018 SR |#eta^{#gamma}|<1 bin 5");
    ya->SetBinLabel(37,"2018 SR |#eta^{#gamma}|>1 bin 1");
    ya->SetBinLabel(38,"2018 SR |#eta^{#gamma}|>1 bin 2");
    ya->SetBinLabel(39,"2018 SR |#eta^{#gamma}|>1 bin 3");
    ya->SetBinLabel(40,"2018 SR |#eta^{#gamma}|>1 bin 4");
    ya->SetBinLabel(41,"2018 SR |#eta^{#gamma}|>1 bin 5");
    ya->SetBinLabel(42,"2018 WZ bin 1");
    ya->SetBinLabel(43,"2018 WZ bin 2");
    ya->SetBinLabel(44,"2018 ZZ bin 1");
    ya->SetBinLabel(45,"2018 ZZ bin 2");
    ya->SetRangeUser(0,45);
  }

  histo->SetLineColor  (kBlack);
  histo->SetMarkerStyle(kFullCircle);
}

void objectEfficiency(TString fileName = "/data/t3home000/ceballos/panda/prod/v_001_0/ZH_ZToLL_HToGDarkG_M125.root", 
                      TString format = "pdf",
		      TString fileNameC = "/data/t3home000/ceballos/panda/prod/v_001_0/fitDiagnosticszhg_comb_125.root"){

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

  TFile *fFileC = TFile::Open(fileNameC.Data());
  TH2D *hDCorrelation = (TH2D*)(fFile->Get("shapes_fit_b/overall_total_covar")); assert(hDCorrelation); hDCorrelation->SetDirectory(0);     
  //TH2D *hDCorrelation = (TH2D*)(fFile->Get("covariance_fit_b")); assert(hDCorrelation); hDCorrelation->SetDirectory(0);     
  delete fFileC;

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
  atributes(hDCorrelation,"","","Correlation matrix",1);
  TCanvas* c00 = new TCanvas("c00","c00",5,5,500,500);
  TCanvas* c01 = new TCanvas("c01","c01",5,5,500,500);
  TCanvas* c02 = new TCanvas("c02","c02",5,5,500,500);
  TCanvas* c03 = new TCanvas("c03","c03",5,5,500,500);
  c00->cd(); hDDenMuEtaPt->Draw("colz,text");DrawTLatex(0.10, 0.91, 0.032, "#bf{CMS} Supplementary       arXiv: 1908.02699");
  c01->cd(); hDDenElEtaPt->Draw("colz,text");DrawTLatex(0.10, 0.91, 0.032, "#bf{CMS} Supplementary       arXiv: 1908.02699");
  c02->cd(); hDDenPhEtaPt->Draw("colz,text");DrawTLatex(0.10, 0.91, 0.032, "#bf{CMS} Supplementary       arXiv: 1908.02699");
  c03->cd();
  {
  hDCorrelation->Draw("colz");
  DrawTLatex(0.10, 0.91, 0.032, "#bf{CMS} Supplementary       arXiv: 1908.02699");
  DrawTLatex(0.95, 0.91, 0.032, "137 fb^{-1} (13 TeV)",false);
  }
  TString outputName;
  outputName = Form("hDDenMuEtaPt.%s",format.Data());  c00->SaveAs(outputName.Data());
  outputName = Form("hDDenElEtaPt.%s",format.Data());  c01->SaveAs(outputName.Data());
  outputName = Form("hDDenPhEtaPt.%s",format.Data());  c02->SaveAs(outputName.Data());
  outputName = Form("hDCorrelation.%s",format.Data()); c03->SaveAs(outputName.Data());

  char output[200];
  sprintf(output,"histo_objectEfficiency.root");	
  TFile* outFileEff = new TFile(output,"recreate");
  outFileEff->cd();
  hDDenMuEtaPt ->SetNameTitle(Form("hDEffMuEtaPt"), Form("hDEffMuEtaPt"));  hDDenMuEtaPt ->Write();
  hDDenElEtaPt ->SetNameTitle(Form("hDEffElEtaPt"), Form("hDEffElEtaPt"));  hDDenElEtaPt ->Write();
  hDDenPhEtaPt ->SetNameTitle(Form("hDEffPhEtaPt"), Form("hDEffPhEtaPt"));  hDDenPhEtaPt ->Write();
  hDCorrelation->SetNameTitle(Form("hDCorrelation"),Form("hDCorrelation")); hDCorrelation->Write();
  outFileEff->Close();
}
