#include "TROOT.h"
#include "Math/ProbFuncMathCore.h"
#include "TInterpreter.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TStyle.h"
#include "TPad.h"
#include "TMath.h"
#include "TGraphAsymmErrors.h"
#include "TSystem.h"
#include "GoodStyle.C"

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

void make2DPlots(int year, TString format = "png"){
  int nTypeLepSel[2] = {-1, -1};
  if     (year == 2016) {nTypeLepSel[0] =  2; nTypeLepSel[1] = 7;}
  else if(year == 2017) {nTypeLepSel[0] = 13; nTypeLepSel[1] = 7;}
  else if(year == 2018) {nTypeLepSel[0] = 15; nTypeLepSel[1] = 7;}
  else {printf("Wrong year (%d)!\n",year); return;}

  gStyle->SetOptStat(0);
  gStyle->SetPaintTextFormat(".3f");
  gStyle->SetPalette(1);
 
  TString fLepton_FakesName = Form("MitAnalysisRunII/data/90x/fakes/histoFakeEtaPt_%d.root",year);
  TString elephoSFPath = Form("MitAnalysisRunII/data/90x/eff/histoDY0LGSF_%d.root",year);
  TString trgSFPath = Form("MitAnalysisRunII/data/90x/trigger/histo_triggerEff_sel0_%d.root",year);
  TString effSFPath = Form("MitAnalysisRunII/data/90x/eff/histoDY0EffSFStudy_%d.root",year);

  TFile *fLepton_Fakes = TFile::Open(fLepton_FakesName.Data());
  TH2D* histoFakeEffSelTightEtaPt_m  = (TH2D*)fLepton_Fakes->Get(Form("histoFakeEffSelEtaPt_%d_0",nTypeLepSel[0])); histoFakeEffSelTightEtaPt_m ->SetDirectory(0);	
  TH2D* histoFakeEffSelTightEtaPt_e  = (TH2D*)fLepton_Fakes->Get(Form("histoFakeEffSelEtaPt_%d_1",nTypeLepSel[1])); histoFakeEffSelTightEtaPt_e ->SetDirectory(0);

  TFile *fLepton_Eff = TFile::Open(effSFPath.Data());
  TH2D* histoLepEffSelTightEtaPt_m  = (TH2D*)fLepton_Eff->Get(Form("histoEffSFStudy_%d_0",nTypeLepSel[0])); histoLepEffSelTightEtaPt_m ->SetDirectory(0);   
  TH2D* histoLepEffSelTightEtaPt_e  = (TH2D*)fLepton_Eff->Get(Form("histoEffSFStudy_%d_1",nTypeLepSel[1])); histoLepEffSelTightEtaPt_e ->SetDirectory(0);
  fLepton_Eff->Close();

  TFile *fElePhoSF = TFile::Open(elephoSFPath.Data());
  TH2D *fhDElePhoSF = (TH2D*)(fElePhoSF->Get("histoLGSF")); assert(fhDElePhoSF); fhDElePhoSF->SetDirectory(0);
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

  atributes(histoFakeEffSelTightEtaPt_m ,"|#eta|","p_{T} [GeV]","Muon non-prompt rate");
  atributes(histoFakeEffSelTightEtaPt_e ,"|#eta|","p_{T} [GeV]","Electron non-prompt rate");

  atributes(histoLepEffSelTightEtaPt_m ,"#eta","p_{T} [GeV]","Muon efficiency scale factor");   
  atributes(histoLepEffSelTightEtaPt_e ,"#eta","p_{T} [GeV]","Electron efficiency scale factor");

  atributes(fhDElePhoSF,"|#eta|","p_{T} [GeV]","Electron to photon rate");

  atributes(trgSFMMBB,"p_{T}^{leading} [GeV]","p_{T}^{trailing} [GeV]","#mu#mu Barrel-Barrel");
  atributes(trgSFMMEB,"p_{T}^{leading} [GeV]","p_{T}^{trailing} [GeV]","#mu#mu Endcap-Barrel");
  atributes(trgSFMMBE,"p_{T}^{leading} [GeV]","p_{T}^{trailing} [GeV]","#mu#mu Barrel-Endcap");
  atributes(trgSFMMEE,"p_{T}^{leading} [GeV]","p_{T}^{trailing} [GeV]","#mu#mu Endcap-Endcap");
  atributes(trgSFEEBB,"p_{T}^{leading} [GeV]","p_{T}^{trailing} [GeV]","ee Barrel-Barrel");
  atributes(trgSFEEEB,"p_{T}^{leading} [GeV]","p_{T}^{trailing} [GeV]","ee Endcap-Barrel");
  atributes(trgSFEEBE,"p_{T}^{leading} [GeV]","p_{T}^{trailing} [GeV]","ee Barrel-Endcap");
  atributes(trgSFEEEE,"p_{T}^{leading} [GeV]","p_{T}^{trailing} [GeV]","ee Endcap-Endcap");
  atributes(trgSFMEBB,"p_{T}^{leading} [GeV]","p_{T}^{trailing} [GeV]","#mue Barrel-Barrel");
  atributes(trgSFMEEB,"p_{T}^{leading} [GeV]","p_{T}^{trailing} [GeV]","#mue Endcap-Barrel");
  atributes(trgSFMEBE,"p_{T}^{leading} [GeV]","p_{T}^{trailing} [GeV]","#mue Barrel-Endcap");
  atributes(trgSFMEEE,"p_{T}^{leading} [GeV]","p_{T}^{trailing} [GeV]","#mue Endcap-Endcap");
  atributes(trgSFEMBB,"p_{T}^{leading} [GeV]","p_{T}^{trailing} [GeV]","e#mu Barrel-Barrel");
  atributes(trgSFEMEB,"p_{T}^{leading} [GeV]","p_{T}^{trailing} [GeV]","e#mu Endcap-Barrel");
  atributes(trgSFEMBE,"p_{T}^{leading} [GeV]","p_{T}^{trailing} [GeV]","e#mu Barrel-Endcap");
  atributes(trgSFEMEE,"p_{T}^{leading} [GeV]","p_{T}^{trailing} [GeV]","e#mu Endcap-Endcap");
  
  TCanvas* c00 = new TCanvas("c00","c00",5,5,500,500);
  TCanvas* c01 = new TCanvas("c01","c01",5,5,500,500);

  TCanvas* c10 = new TCanvas("c10","c10",5,5,500,500);
  TCanvas* c11 = new TCanvas("c11","c11",5,5,500,500);

  TCanvas* c20 = new TCanvas("c20","c20",5,5,500,500);

  TCanvas* c30 = new TCanvas("c30","c30",5,5,500,500);
  TCanvas* c31 = new TCanvas("c31","c31",5,5,500,500);
  TCanvas* c32 = new TCanvas("c32","c32",5,5,500,500);
  TCanvas* c33 = new TCanvas("c33","c33",5,5,500,500);
  TCanvas* c40 = new TCanvas("c40","c40",5,5,500,500);
  TCanvas* c41 = new TCanvas("c41","c41",5,5,500,500);
  TCanvas* c42 = new TCanvas("c42","c42",5,5,500,500);
  TCanvas* c43 = new TCanvas("c43","c43",5,5,500,500);
  TCanvas* c50 = new TCanvas("c50","c50",5,5,500,500);
  TCanvas* c51 = new TCanvas("c51","c51",5,5,500,500);
  TCanvas* c52 = new TCanvas("c52","c52",5,5,500,500);
  TCanvas* c53 = new TCanvas("c53","c53",5,5,500,500);
  TCanvas* c60 = new TCanvas("c60","c60",5,5,500,500);
  TCanvas* c61 = new TCanvas("c61","c61",5,5,500,500);
  TCanvas* c62 = new TCanvas("c62","c62",5,5,500,500);
  TCanvas* c63 = new TCanvas("c63","c63",5,5,500,500);
  
  c00->cd(); histoFakeEffSelTightEtaPt_m ->Draw("colz,text,e");
  c01->cd(); histoFakeEffSelTightEtaPt_e ->Draw("colz,text,e");
  
  c10->cd(); histoLepEffSelTightEtaPt_m ->Draw("colz,text,e");
  c11->cd(); histoLepEffSelTightEtaPt_e ->Draw("colz,text,e");
  
  c20->cd(); fhDElePhoSF->Draw("colz,text,e");

  c30->cd(); trgSFMMBB->Draw("colz,text,e");
  c31->cd(); trgSFMMEB->Draw("colz,text,e");
  c32->cd(); trgSFMMBE->Draw("colz,text,e");
  c33->cd(); trgSFMMEE->Draw("colz,text,e");
  c40->cd(); trgSFEEBB->Draw("colz,text,e");
  c41->cd(); trgSFEEEB->Draw("colz,text,e");
  c42->cd(); trgSFEEBE->Draw("colz,text,e");
  c43->cd(); trgSFEEEE->Draw("colz,text,e");
  c50->cd(); trgSFMEBB->Draw("colz,text,e");
  c51->cd(); trgSFMEEB->Draw("colz,text,e");
  c52->cd(); trgSFMEBE->Draw("colz,text,e");
  c53->cd(); trgSFMEEE->Draw("colz,text,e");
  c60->cd(); trgSFEMBB->Draw("colz,text,e");
  c61->cd(); trgSFEMEB->Draw("colz,text,e");
  c62->cd(); trgSFEMBE->Draw("colz,text,e");
  c63->cd(); trgSFEMEE->Draw("colz,text,e");

  char CommandToExec[300];
  sprintf(CommandToExec,"mkdir -p plots");
  gSystem->Exec(CommandToExec);  

  TString outputName;
  outputName = Form("plots/histoFakeEffSelTightEtaPt_m_%d.%s",year,format.Data());  c00->SaveAs(outputName.Data());
  outputName = Form("plots/histoFakeEffSelTightEtaPt_e_%d.%s",year,format.Data());  c01->SaveAs(outputName.Data());

  outputName = Form("plots/histoLepEffSelTightEtaPt_m_%d.%s",year,format.Data());  c10->SaveAs(outputName.Data());
  outputName = Form("plots/histoLepEffSelTightEtaPt_e_%d.%s",year,format.Data());  c11->SaveAs(outputName.Data());

  outputName = Form("plots/fhDElePhoSF_%d.%s",year,format.Data()); c20->SaveAs(outputName.Data());

  outputName = Form("plots/trgSFMMBB_%d.%s",year,format.Data()); c30->SaveAs(outputName.Data());
  outputName = Form("plots/trgSFMMEB_%d.%s",year,format.Data()); c31->SaveAs(outputName.Data());
  outputName = Form("plots/trgSFMMBE_%d.%s",year,format.Data()); c32->SaveAs(outputName.Data());
  outputName = Form("plots/trgSFMMEE_%d.%s",year,format.Data()); c33->SaveAs(outputName.Data());
  outputName = Form("plots/trgSFEEBB_%d.%s",year,format.Data()); c40->SaveAs(outputName.Data());
  outputName = Form("plots/trgSFEEEB_%d.%s",year,format.Data()); c41->SaveAs(outputName.Data());
  outputName = Form("plots/trgSFEEBE_%d.%s",year,format.Data()); c42->SaveAs(outputName.Data());
  outputName = Form("plots/trgSFEEEE_%d.%s",year,format.Data()); c43->SaveAs(outputName.Data());
  outputName = Form("plots/trgSFMEBB_%d.%s",year,format.Data()); c50->SaveAs(outputName.Data());
  outputName = Form("plots/trgSFMEEB_%d.%s",year,format.Data()); c51->SaveAs(outputName.Data());
  outputName = Form("plots/trgSFMEBE_%d.%s",year,format.Data()); c52->SaveAs(outputName.Data());
  outputName = Form("plots/trgSFMEEE_%d.%s",year,format.Data()); c53->SaveAs(outputName.Data());
  outputName = Form("plots/trgSFEMBB_%d.%s",year,format.Data()); c60->SaveAs(outputName.Data());
  outputName = Form("plots/trgSFEMEB_%d.%s",year,format.Data()); c61->SaveAs(outputName.Data());
  outputName = Form("plots/trgSFEMBE_%d.%s",year,format.Data()); c62->SaveAs(outputName.Data());
  outputName = Form("plots/trgSFEMEE_%d.%s",year,format.Data()); c63->SaveAs(outputName.Data());
}
