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

void studyFitResults(int nsel = 0,  TString plotName = "done_ana/histoZHG_2019_0001.root", TString mlfitResult = "comb/fitDiagnosticszhg_comb.root", TString channelName = "ch1") {

  TFile* file = new TFile(plotName, "read");  if(!file) {printf("File %s does not exist\n",plotName.Data()); return;}

  TH1F* _hist[nPlotCategories];
  TFile *mlfit=0;
  if(mlfitResult!="") {
    mlfit=TFile::Open(mlfitResult); assert(mlfit);
  }
  double SF_yield[nPlotCategories]; 
  double SF_yield_unc[nPlotCategories];

  const int allExcludeBins = 5;
  int excludeBins[allExcludeBins] = {1, 10, 11, 12, 13};
  double totalSum[2]    = {0.0, 0.0};
  double totalSysUnc[2] = {0.0, 0.0};
  double totalStaUnc[2] = {0.0, 0.0};

  for(int ic=0; ic<nPlotCategories; ic++){
    _hist[ic] = (TH1F*)file->Get(Form("histo%d",ic));
    if(ic == kPlotData || _hist[ic]->GetSumOfWeights() <= 0) continue;
    if(mlfitResult!="" && ic != kPlotData) {
      if     ((TH1F*)mlfit->Get(Form("shapes_prefit/%s/%s",channelName.Data(),plotBaseNames[ic].Data()))) {
        double sum[4] = {0, 0, 0, 0};
        for(int i=1; i<=((TH1F*)mlfit->Get(Form("shapes_fit_s/%s/%s",channelName.Data(),plotBaseNames[ic].Data())))->GetNbinsX(); i++){
	  bool binToExclude = false;
	  for(int nb=0; nb<allExcludeBins; nb++) if(i == excludeBins[nb]) binToExclude = true;
	  if(binToExclude == true) continue;
	  sum[0] = sum[0] + ((TH1F*)mlfit->Get(Form("shapes_prefit/%s/%s",channelName.Data(),plotBaseNames[ic].Data())))->GetBinContent(i);
	  sum[1] = sum[1] + ((TH1F*)mlfit->Get(Form("shapes_prefit/%s/%s",channelName.Data(),plotBaseNames[ic].Data())))->GetBinError (i);
          sum[2] = sum[2] + ((TH1F*)mlfit->Get(Form("shapes_fit_s/%s/%s", channelName.Data(),plotBaseNames[ic].Data())))->GetBinContent(i);
	  sum[3] = sum[3] + ((TH1F*)mlfit->Get(Form("shapes_fit_s/%s/%s", channelName.Data(),plotBaseNames[ic].Data())))->GetBinError (i);
	  if(ic != kPlotBSM) continue; //Trick to go through just once
	  totalSum[0]    = totalSum[0]    + ((TH1F*)mlfit->Get(Form("shapes_prefit/%s/total_background",channelName.Data())))->GetBinContent(i);
	  totalSysUnc[0] = totalSysUnc[0] + ((TH1F*)mlfit->Get(Form("shapes_prefit/%s/total_background",channelName.Data())))->GetBinError  (i);
          totalSum[1]    = totalSum[1]    + ((TH1F*)mlfit->Get(Form("shapes_fit_s/%s/total_background" ,channelName.Data())))->GetBinContent(i);
	  totalSysUnc[1] = totalSysUnc[1] + ((TH1F*)mlfit->Get(Form("shapes_fit_s/%s/total_background" ,channelName.Data())))->GetBinError  (i);
        }
        SF_yield[ic]     = sum[2] / sum[0];
        SF_yield_unc[ic] = sum[3] / sum[2];
        printf("POST FIT SFs: SF[%s] = %.3f +/- %.3f | %.3f +/- %.3f | %.3f +/- %.3f\n",plotBaseNames[ic].Data(),SF_yield[ic],SF_yield_unc[ic],sum[0],sum[1],sum[2],sum[3]);
      }
    } // mltFit result
    double sum[4] = {0, 0, 0, 0};
    for(int i=1; i<=_hist[ic]->GetNbinsX(); i++){
      sum[0] = sum[0] + _hist[ic]->GetBinContent(i);
      sum[1] = sum[1] + TMath::Power(_hist[ic]->GetBinError(i),2);
      sum[2] = sum[2] +  _hist[ic]->GetBinContent(i)*SF_yield[ic];
      sum[3] = sum[3] + TMath::Power(_hist[ic]->GetBinError(i)*SF_yield[ic],2);
    }
    if(ic != kPlotBSM) {
      totalStaUnc[0] = totalStaUnc[0] + sum[1];
      totalStaUnc[1] = totalStaUnc[1] + sum[3];
    }
    printf("Statistical[%s] = %.3f +/- %.3f | %.3f +/- %.3f\n",plotBaseNames[ic].Data(),sum[0],sqrt(sum[1]),sum[2],sqrt(sum[3]));
  }
  printf("Total background = %.3f +/- %.3f (%.3f) | %.3f +/- %.3f (%.3f)\n",totalSum[0],totalSysUnc[0],sqrt(totalStaUnc[0]),totalSum[1],totalSysUnc[1],sqrt(totalStaUnc[1]));
}
