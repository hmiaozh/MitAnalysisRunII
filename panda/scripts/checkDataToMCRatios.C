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
#include <cassert>
#include "RooArgSet.h"

#include "MitVHBBAnalysis/macros/vhbbPlot.h"

using namespace vhbbPlot;

void theCheckDataToMCRatio(TString fileName = "datacards/zhbb/testcondor_WlnH2TopCR.root", TString histName = "WBosonPt", int type = 0, int year = 2016){
  TFile *_file0 = TFile::Open(fileName.Data());
  TH1F* histo[nPlotCategories];
  TH1F* histoBck;

  for(int iCat=kPlotData; iCat!=nPlotCategories; iCat++) {
    double scale = 1.0;
    if(year == 2016){
      if     (iCat == kPlotTop || iCat == kPlotTT) scale = 1.00;
      else if(iCat == kPlotWbb || iCat == kPlotWb) scale = 1.00;
    }
    histo[iCat] = (TH1F*)_file0->Get(Form("%s/histo%d",histName.Data(),iCat));
    if(iCat == kPlotData) {
      histoBck = (TH1F*)_file0->Get(Form("%s/histo%d",histName.Data(),iCat));
      histoBck->Scale(0.0);
    }
    else if(iCat == kPlotVZbb || iCat == kPlotVVLF || (iCat == kPlotTT&&type!=0)   || (iCat == kPlotTop&&type!=0) || 
            iCat == kPlotWH   || iCat == kPlotZH   || iCat == kPlotGGZH ||  iCat == kPlotQCD ||
	   (iCat == kPlotZbb&&type!=12)  || (iCat == kPlotZb&&type!=12)	|| (iCat == kPlotZLF&&type!=11)  ||
	   (iCat == kPlotWbb&&type!= 2)  || (iCat == kPlotWb&&type!= 2)	|| (iCat == kPlotWLF&&type!= 1)) {
      histo[kPlotData]->Add(histo[iCat],-1.0*scale);
    }
    else {
      printf("The prediction: %s\n",vhbbPlot::plotNames[static_cast<plotCategory>(iCat)].Data());
      histoBck->Add(histo[iCat],scale);
    }
  }
  histo[kPlotData]->Divide(histoBck);
  histo[kPlotData]-> Draw();

}

void checkDataToMCRatios(int type = 0, int year = 2016, bool isBoosted = false){
  if     (type == 0 && year == 2016 && isBoosted == false) theCheckDataToMCRatio("MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_WlnH2TopCR.root", 	"WBosonPt",type,year);
  else if(type == 0 && year == 2017 && isBoosted == false) theCheckDataToMCRatio("MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_WlnH2TopCR.root", 	"WBosonPt",type,year);
  else if(type == 0 && year == 2016 && isBoosted == true)  theCheckDataToMCRatio("MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_WlnHTT2bFJCR.root",	"WBosonPt",type,year);
  else if(type == 0 && year == 2017 && isBoosted == true)  theCheckDataToMCRatio("MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_WlnHTT2bFJCR.root",	"WBosonPt",type,year);
  else if(type ==10 && year == 2016 && isBoosted == false) theCheckDataToMCRatio("MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZllH2TopCR_ZptBin0.root", "ZBosonPt",0,year);
  else if(type ==10 && year == 2017 && isBoosted == false) theCheckDataToMCRatio("MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZllH2TopCR_ZptBin0.root", "ZBosonPt",0,year);

  else if(type == 1 && year == 2016 && isBoosted == false) theCheckDataToMCRatio("MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_WlnHLightFlavorCR.root",         "WBosonPt",type,year);
  else if(type == 1 && year == 2017 && isBoosted == false) theCheckDataToMCRatio("MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_WlnHLightFlavorCR.root",         "WBosonPt",type,year);
  else if(type == 1 && year == 2016 && isBoosted == true)  theCheckDataToMCRatio("MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_WlnHLightFlavorFJCR.root",       "WBosonPt",type,year);
  else if(type == 1 && year == 2017 && isBoosted == true)  theCheckDataToMCRatio("MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_WlnHLightFlavorFJCR.root",       "WBosonPt",type,year);
  else if(type ==11 && year == 2016 && isBoosted == false) theCheckDataToMCRatio("MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZllHLightFlavorCR_ZptBin0.root", "ZBosonPt",type,year);
  else if(type ==11 && year == 2017 && isBoosted == false) theCheckDataToMCRatio("MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZllHLightFlavorCR_ZptBin0.root", "ZBosonPt",type,year);
  else if(type ==11 && year == 2016 && isBoosted == true)  theCheckDataToMCRatio("MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZllHLightFlavorFJCR.root",       "ZBosonPt",type,year);
  else if(type ==11 && year == 2017 && isBoosted == true)  theCheckDataToMCRatio("MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZllHLightFlavorFJCR.root",       "ZBosonPt",type,year);

  else if(type == 2 && year == 2016 && isBoosted == false) theCheckDataToMCRatio("MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_WlnHHeavyFlavorCR.root",         "WBosonPt",type,year);
  else if(type == 2 && year == 2017 && isBoosted == false) theCheckDataToMCRatio("MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_WlnHHeavyFlavorCR.root",         "WBosonPt",type,year);
  else if(type == 2 && year == 2016 && isBoosted == true)  theCheckDataToMCRatio("MitVHBBAnalysis/datacards/whbb/testcondor2016/plots_WlnHHeavyFlavorFJCR.root",       "WBosonPt",type,year);
  else if(type == 2 && year == 2017 && isBoosted == true)  theCheckDataToMCRatio("MitVHBBAnalysis/datacards/whbb/testcondor2017/plots_WlnHHeavyFlavorFJCR.root",       "WBosonPt",type,year);
  else if(type ==12 && year == 2016 && isBoosted == false) theCheckDataToMCRatio("MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZllHHeavyFlavorCR_ZptBin0.root", "ZBosonPt",type,year);
  else if(type ==12 && year == 2017 && isBoosted == false) theCheckDataToMCRatio("MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZllHHeavyFlavorCR_ZptBin0.root", "ZBosonPt",type,year);
  else if(type ==12 && year == 2016 && isBoosted == true)  theCheckDataToMCRatio("MitVHBBAnalysis/datacards/zhbb/testcondor2016/plots_ZllHHeavyFlavorFJCR.root",       "ZBosonPt",type,year);
  else if(type ==12 && year == 2017 && isBoosted == true)  theCheckDataToMCRatio("MitVHBBAnalysis/datacards/zhbb/testcondor2017/plots_ZllHHeavyFlavorFJCR.root",       "ZBosonPt",type,year);
}
