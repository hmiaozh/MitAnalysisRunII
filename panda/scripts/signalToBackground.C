#include <TCanvas.h>
#include <TFile.h>
#include <TH1F.h>
#include <THStack.h>
#include <TLegend.h>
#include <TMath.h>
#include <TLine.h>
#include <TString.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TTree.h>
#include <TList.h>
#include <TPaveText.h>
#include <TText.h>
#include <TGraphAsymmErrors.h>
#include <cassert>
#include "RooArgSet.h"

#include "MitVHBBAnalysis/macros/vhbbPlot.h"

using namespace vhbbPlot;

vector<TString> regionNames = {
 "ZeeH2TopCR_ZptBin0",
 "ZeeH2TopCR_ZptBin1",
 "ZeeH2TopCR_ZptBin2",
 "ZmmH2TopCR_ZptBin0",
 "ZmmH2TopCR_ZptBin1",
 "ZmmH2TopCR_ZptBin2",
 "ZeeHFJSR",
 "ZeeHHeavyFlavorCR_ZptBin0",
 "ZeeHHeavyFlavorCR_ZptBin1",
 "ZeeHHeavyFlavorCR_ZptBin2",
 "ZeeHHeavyFlavorFJCR",
 "ZeeHLightFlavorCR_ZptBin0",
 "ZeeHLightFlavorCR_ZptBin1",
 "ZeeHLightFlavorCR_ZptBin2",
 "ZeeHLightFlavorFJCR",
 "ZeeHSR_ZptBin0",
 "ZeeHSR_ZptBin1",
 "ZeeHSR_ZptBin2",
 "ZmmHFJSR",
 "ZmmHHeavyFlavorCR_ZptBin0",
 "ZmmHHeavyFlavorCR_ZptBin1",
 "ZmmHHeavyFlavorCR_ZptBin2",
 "ZmmHHeavyFlavorFJCR",
 "ZmmHLightFlavorCR_ZptBin0",
 "ZmmHLightFlavorCR_ZptBin1",
 "ZmmHLightFlavorCR_ZptBin2",
 "ZmmHLightFlavorFJCR",
 "ZmmHSR_ZptBin0",
 "ZmmHSR_ZptBin1",
 "ZmmHSR_ZptBin2",
 "ZeeHVZbbFJCR",
 "ZeeHVZbbCR_ZptBin0",
 "ZeeHVZbbCR_ZptBin1",
 "ZeeHVZbbCR_ZptBin2",
 "ZmmHVZbbFJCR",
 "ZmmHVZbbCR_ZptBin0",
 "ZmmHVZbbCR_ZptBin1",
 "ZmmHVZbbCR_ZptBin2"
};

void signalToBackground(
  TString mlfitResult="",
  TString outputFileName="test",
  bool isVZSignal = false,
  bool doRatioPad = true,
  bool isBlinded = true
) {
  const int nBins = 10;
  double xBins[nBins+1] = {0.00, 0.01, 0.02, 0.03, 0.04, 0.07, 0.10, 0.15, 0.20, 0.30, 0.50};

  if(mlfitResult!="") {  
    TFile *mlfit=TFile::Open(mlfitResult); assert(mlfit);;
    TH1F *histo_logsb_data = new TH1F("histo_logsb_data", "histo_logsb_data", nBins, xBins);
    TH1F *histo_logsb_b    = new TH1F("histo_logsb_b",    "histo_logsb_b",    nBins, xBins);
    TH1F *histo_logsb_sb   = new TH1F("histo_logsb_sb",   "histo_logsb_sb",   nBins, xBins);

    for(unsigned int i=0; i<regionNames.size(); i++){
      TH1F *prefitSignal = (TH1F*)mlfit->Get(Form("shapes_prefit/%s/%s",regionNames[i].Data(), plotBaseNames[kPlotZH].Data()));
      if(isVZSignal == false && prefitSignal) {
        TH1F *prefitSignal2 = (TH1F*)mlfit->Get(Form("shapes_prefit/%s/%s",regionNames[i].Data(), plotBaseNames[kPlotGGZH].Data()));
        if(prefitSignal2) prefitSignal->Add(prefitSignal2);
      }
      else if(isVZSignal == true) {
        prefitSignal = (TH1F*)mlfit->Get(Form("shapes_prefit/%s/%s",regionNames[i].Data(), plotBaseNames[kPlotVZbb].Data()));
      }
      TGraphAsymmErrors *data = (TGraphAsymmErrors*)mlfit->Get(Form("shapes_prefit/%s/%s",regionNames[i].Data(), "data"));
      if(prefitSignal) {
        TH1F *postfitTotal    = (TH1F*)mlfit->Get(Form("shapes_fit_s/%s/total",regionNames[i].Data()));
        TH1F *postfitTotalBck = (TH1F*)mlfit->Get(Form("shapes_fit_s/%s/total_background",regionNames[i].Data()));
        TH1F *postfitSignal   = (TH1F*)mlfit->Get(Form("shapes_fit_s/%s/%s",regionNames[i].Data(), plotBaseNames[kPlotZH].Data()));
        TH1F *postfitSignal2  = (TH1F*)mlfit->Get(Form("shapes_fit_s/%s/%s",regionNames[i].Data(), plotBaseNames[kPlotGGZH].Data()));
        if(isVZSignal == false && postfitSignal2) postfitSignal->Add(postfitSignal2);
        else if(isVZSignal == true) postfitSignal = (TH1F*)mlfit->Get(Form("shapes_fit_s/%s/%s",regionNames[i].Data(), plotBaseNames[kPlotVZbb].Data()));

        double diff_rel = TMath::Abs(postfitTotal->GetSumOfWeights() - postfitTotalBck->GetSumOfWeights() - postfitSignal->GetSumOfWeights())/postfitTotal->GetSumOfWeights();
        if(diff_rel > 0.0001){
	  printf("Total - Bck - Sig != 0!: %f - %f - %f = %f\n",postfitTotal->GetSumOfWeights(),postfitTotalBck->GetSumOfWeights(),postfitSignal->GetSumOfWeights(),postfitTotal->GetSumOfWeights() - postfitTotalBck->GetSumOfWeights() - postfitSignal->GetSumOfWeights());
	}

        for(int nb=1; nb<=postfitTotal->GetNbinsX(); nb++) {
	  if(prefitSignal->GetBinContent(nb) <= 0) continue;
	  double theBck = postfitTotalBck->GetBinContent(nb);
	  double theSig = prefitSignal->GetBinContent(nb);
          double logsb = TMath::Min(log(1.+theSig/theBck), xBins[nBins]-0.001);
	  int theBin = histo_logsb_data->FindBin(logsb);

	  histo_logsb_data->SetBinContent(theBin, histo_logsb_data->GetBinContent(theBin) + data->Eval(nb-0.5));
	  histo_logsb_data->SetBinError  (theBin, sqrt(histo_logsb_data->GetBinError(theBin) * histo_logsb_data->GetBinError(theBin) + data->Eval(nb-0.5)));
	  histo_logsb_b   ->SetBinContent(theBin, histo_logsb_b   ->GetBinContent(theBin) + theBck);
	  histo_logsb_sb  ->SetBinContent(theBin, histo_logsb_sb  ->GetBinContent(theBin) + theBck + theSig);
	  //histo_logsb_b   ->SetBinError  (theBin, sqrt(histo_logsb_b ->GetBinError(theBin) * histo_logsb_b ->GetBinError(theBin) + postfitTotalBck->GetBinError(nb) * postfitTotalBck->GetBinError(nb)));
	  //histo_logsb_sb  ->SetBinError  (theBin, sqrt(histo_logsb_sb->GetBinError(theBin) * histo_logsb_sb->GetBinError(theBin) + postfitTotalBck->GetBinError(nb) * postfitTotalBck->GetBinError(nb)));
	  histo_logsb_b   ->SetBinError  (theBin, histo_logsb_b ->GetBinError(theBin) + postfitTotalBck->GetBinError(nb));
	  histo_logsb_sb  ->SetBinError  (theBin, histo_logsb_sb->GetBinError(theBin) + postfitTotalBck->GetBinError(nb));

          //histo_logsb_data->Fill(logsb, data->Eval(nb-0.5));
          //histo_logsb_b   ->Fill(logsb, theBck);
          //histo_logsb_sb  ->Fill(logsb, theBck + theSig);

          if(logsb > 0.2) printf("%20s %2d %5.0f %6.1f %6.1f %6.3f %6.3f\n",regionNames[i].Data(),nb,data->Eval(nb-0.5),theSig,theBck,theSig/theBck,logsb);
        }
      }
    }

    TFile* outFile = new TFile(Form("%s.root",outputFileName.Data()),"recreate");
    outFile->cd();
    histo_logsb_data->Write();
    histo_logsb_b   ->Write();
    histo_logsb_sb  ->Write();
    outFile->Close();

  } else {
    TFile* inFile = new TFile(Form("%s.root",outputFileName.Data()),"read");
    TH1F *histo_logsb_data = (TH1F*)(inFile->Get("histo_logsb_data")); assert(histo_logsb_data); histo_logsb_data->SetDirectory(0);
    TH1F *histo_logsb_b    = (TH1F*)(inFile->Get("histo_logsb_b"));    assert(histo_logsb_b   ); histo_logsb_b   ->SetDirectory(0);
    TH1F *histo_logsb_sb   = (TH1F*)(inFile->Get("histo_logsb_sb"));   assert(histo_logsb_sb  ); histo_logsb_sb  ->SetDirectory(0);

    histo_logsb_data->SetMarkerColor(plotColors[kPlotData]); 
    histo_logsb_data->SetLineColor(plotColors[kPlotData]); 
    histo_logsb_data->SetMarkerStyle(20);
    histo_logsb_b->SetLineColor(plotColors[kPlotZbb]);
    histo_logsb_b->SetFillColor(plotColors[kPlotZbb]);
    histo_logsb_b->SetMarkerColor(plotColors[kPlotZbb]);
    histo_logsb_b->SetFillStyle(1001);
    histo_logsb_sb->SetMarkerColor(plotColors[kPlotZH]); 
    histo_logsb_sb->SetLineColor(plotColors[kPlotZH]); 
    histo_logsb_sb->SetLineWidth(3);
    histo_logsb_sb->SetFillStyle(0);

    histo_logsb_data->Scale(0.1,"width");
    histo_logsb_b   ->Scale(0.1,"width");
    histo_logsb_sb  ->Scale(0.1,"width");

    if(isBlinded) {
      for(int nb=1; nb<=histo_logsb_data->GetNbinsX(); nb++) {
        histo_logsb_data->SetBinContent(nb,histo_logsb_sb->GetBinContent(nb));
	histo_logsb_data->SetBinError(nb,sqrt(histo_logsb_sb->GetBinContent(nb)));
      }
    } else {
      for(int nb=1; nb<=histo_logsb_data->GetNbinsX(); nb++) {
        histo_logsb_data->SetBinContent(nb,histo_logsb_data->GetBinContent(nb));
	histo_logsb_data->SetBinError(nb,sqrt(histo_logsb_data->GetBinContent(nb)));
      }
    }

    //histo_logsb_data->SetMinimum(1);
    histo_logsb_data->ResetAttLine();
    histo_logsb_data->ResetAttFill();
    histo_logsb_data->ResetAttMarker();
    histo_logsb_data->SetTitle("");
    histo_logsb_data->SetStats(false);

    histo_logsb_data->GetXaxis()->SetTitle("log(1+S/B)");
    histo_logsb_data->GetYaxis()->SetTitle("Events");
    TCanvas *canvas = new TCanvas(Form("canvas"),"canvas",600,480);
    TPad *pad1=0,*pad2=0;
    if(doRatioPad) {
      canvas->SetTopMargin(0.0); 
      canvas->SetRightMargin(0.02);
      canvas->SetBottomMargin(0.1); 
      pad1= new TPad("pad1", "pad1", 0, 0.3, 1.,1);
      pad1->SetTopMargin(0.1);
      pad1->SetLeftMargin(0.15);
      pad1->SetRightMargin(0.04);
      pad1->SetBottomMargin(0.03); 
      pad1->Draw();             
      pad1->cd();              
      pad1->SetLogy();
      histo_logsb_data->GetXaxis()->SetLabelOffset(999);
      histo_logsb_data->GetXaxis()->SetLabelSize(0);
    } else {
      canvas->cd();
      canvas->SetLogy();
    }
    histo_logsb_data->Draw("e");
    histo_logsb_b   ->Draw("same,hist");
    histo_logsb_sb  ->Draw("same,hist");
    TLegend *legend1=new TLegend(0.5,0.85,0.8,0.65);
    legend1->AddEntry(histo_logsb_data, "Data" ,"lp");
    legend1->AddEntry(histo_logsb_b   , "Background"  ,"f");
    legend1->AddEntry(histo_logsb_sb  , "Signal+background"  ,"f");
    legend1->Draw();

    TPaveText *cmsText;
    if(doRatioPad) cmsText=new TPaveText(.19,.65,.39,.85,"nbNDC");
    else           cmsText=new TPaveText(.14,.7,.35,.85,"nbNDC");
    TText *cmsTextL1 = cmsText->AddText("#font[62]{CMS}");
    TText *cmsTextL2 = cmsText->AddText("#font[52]{Preliminary}");
    cmsTextL1->SetTextAlign(11);
    cmsTextL2->SetTextAlign(11);
    cmsText->SetFillColorAlpha(0,0);
    cmsText->Draw("same");

    if(doRatioPad) {
      TH1F *hRatio = (TH1F*) histo_logsb_data->Clone("hRatio");
      hRatio->SetDirectory(0);
      TH1F *hRatioExp = (TH1F*) histo_logsb_sb->Clone("hRatioExp");
      hRatioExp->SetDirectory(0);
      double naiveSignificance = 0;
      for(int nb=1; nb<=hRatio->GetNbinsX(); nb++) {
        if(histo_logsb_b->GetBinContent(nb)>0 && hRatio->GetBinContent(nb)>0) {
	  printf("%6d %10.1f %10.1f %5.3f %10.1f %10.1f %5.3f\n",nb,
	  histo_logsb_data->GetBinContent(nb),histo_logsb_b->GetBinContent(nb),histo_logsb_data->GetBinContent(nb) / histo_logsb_b->GetBinContent(nb)
           ,histo_logsb_data->GetBinError(nb),histo_logsb_b->GetBinContent(nb),histo_logsb_data->GetBinError(nb)   / histo_logsb_b->GetBinContent(nb));

          naiveSignificance = naiveSignificance + 
	       (histo_logsb_data->GetBinContent(nb)-histo_logsb_b->GetBinContent(nb))*(histo_logsb_data->GetBinContent(nb)-histo_logsb_b->GetBinContent(nb))/
	       (histo_logsb_data->GetBinError(nb)*histo_logsb_data->GetBinError(nb)+histo_logsb_b->GetBinError(nb)*histo_logsb_b->GetBinError(nb));

	  hRatio->SetBinContent   ( nb, histo_logsb_data->GetBinContent(nb) / histo_logsb_b->GetBinContent(nb));
          hRatio->SetBinError     ( nb, histo_logsb_data->GetBinError(nb)   / histo_logsb_b->GetBinContent(nb)); 
	  hRatioExp->SetBinContent( nb, histo_logsb_sb  ->GetBinContent(nb) / histo_logsb_b->GetBinContent(nb));
          hRatioExp->SetBinError  ( nb, histo_logsb_sb  ->GetBinError(nb)   / histo_logsb_b->GetBinContent(nb));
        } else {
          hRatio->SetBinContent( nb, 1);
          hRatio->SetBinError(nb, 1);
          hRatioExp->SetBinContent( nb, 1);
          hRatioExp->SetBinError(nb, 1);
        }
      } 
      printf("naiveSignificance: %f\n",sqrt(naiveSignificance));

      TH1F *hErrorBand = (TH1F*)histo_logsb_b->Clone("hErrorBand");
      hErrorBand->SetFillColor(kBlack); hErrorBand->SetFillStyle(3254);
      hErrorBand->SetMarkerColor(kBlack); hErrorBand->SetMarkerSize(0);

      TH1F *hRatioBand = (TH1F*)hErrorBand->Clone("hRatioBand");
      for(int nb=1; nb<=hRatio->GetNbinsX(); nb++) {
        hRatioBand->SetBinContent(nb,1);
        hRatioBand->SetBinError(nb, histo_logsb_b->GetBinError(nb) / histo_logsb_b->GetBinContent(nb));
      }

      canvas->cd();
      pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
      pad2->SetLeftMargin(0.15);
      pad2->SetTopMargin(0);
      pad2->SetBottomMargin(0.4);
      pad2->SetRightMargin(0.04);
      pad2->Draw(); pad2->cd();
      hRatio->SetStats(false);
      hRatioExp->SetStats(false);
      hRatioBand->SetStats(false);
      hRatioBand->SetTitle("");
      hRatioBand->GetXaxis()->SetTitleSize(0.16);
      hRatioBand->GetXaxis()->SetTitleOffset(1.05);
      hRatioBand->GetYaxis()->SetNdivisions(503);
      hRatioBand->GetXaxis()->SetLabelSize(0.2);
      hRatioBand->GetXaxis()->SetTitle("log(1+S/B)");
      hRatioBand->GetYaxis()->SetTitle("Data/B");
      hRatioBand->GetYaxis()->CenterTitle();
      hRatioBand->GetYaxis()->SetTitleOffset(0.37);
      hRatioBand->GetYaxis()->SetTitleSize(0.12);
      hRatioBand->GetYaxis()->SetLabelSize(0.15);
      hRatioBand->SetFillStyle(3254);
      hRatioBand->SetFillColor(kBlack);
      hRatioBand->SetLineColor(kBlack);
      hRatioBand->SetMinimum(.8);
      hRatioBand->SetMaximum(2.35);
      hRatioBand->Draw("E2");
      
      hRatio->SetLineColor(kBlack);
      hRatio->SetMarkerStyle(20);
      hRatio->SetMarkerSize(0.8);
      hRatio->Draw("P E1 x0 SAME");
      hRatioExp->SetLineColor(kRed);
      hRatioExp->Draw("hist SAME");
      TLine *baseline = new TLine(0,1,xBins[nBins],1);
      baseline->SetLineStyle(kSolid); baseline->Draw("SAME");
    }

    TString outPdf = Form("plot_%s.pdf",outputFileName.Data()); 
    TString outPng = Form("plot_%s.png",outputFileName.Data()); 
    canvas->Print(outPdf);
    //system(Form("gs -sDEVICE=png16m -dTextAlphaBits=4 -g1800x1440 -dUseCropBox -dFIXEDMEDIA -dPDFFitPage -o %s %s >/dev/null 2>&1 &",outPng.Data(), outPdf.Data()));
    delete canvas;
  }

}
