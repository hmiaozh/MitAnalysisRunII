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

void makeSSWWDataCards(TString outputLimits = "ssww_comb_input.root", int fidAna = 0){

  TString fidAnaName = "";
  if(fidAna == 1) fidAnaName = "_fiducial";

  double qcdScaleTotal[2] = {0.035, 0.231};
  double pdfTotal[2] = {0.016, 0.051};
  double syst_WZl[2] = {1.010, 1.012};

  TFile* infile = new TFile(outputLimits,"read");

  TH1D *histo_Baseline[nPlotCategories];
  for(unsigned ic=kPlotData; ic!=nPlotCategories; ic++) {
      histo_Baseline[ic] = (TH1D*)infile->Get(Form("histo_%s", plotBaseNames[ic].Data()));
      if(!histo_Baseline[ic]) continue;
      histo_Baseline[ic]->SetDirectory(0);
  }

  // Filling datacards txt file
  char outputLimitsCard[200];  					  
  sprintf(outputLimitsCard,"datacard_ssww_comb%s.txt",fidAnaName.Data());
  ofstream newcardShape;
  newcardShape.open(outputLimitsCard);
  newcardShape << Form("imax * number of channels\n");
  newcardShape << Form("jmax * number of background minus 1\n");
  newcardShape << Form("kmax * number of nuisance parameters\n");

  newcardShape << Form("shapes    *   *   %s  histo_$PROCESS histo_$PROCESS_$SYSTEMATIC\n",outputLimits.Data());
  newcardShape << Form("shapes data_obs * %s  histo_Data\n",outputLimits.Data());

  newcardShape << Form("Observation %f\n",histo_Baseline[kPlotData]->GetSumOfWeights());

  newcardShape << Form("bin   ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(!histo_Baseline[ic]) continue;
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("ch1  ");
  }
  newcardShape << Form("\n");
 
  newcardShape << Form("process  ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(!histo_Baseline[ic]) continue;
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("%s  ", plotBaseNames[ic].Data());
  }
  newcardShape << Form("\n");

  newcardShape << Form("process  ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(!histo_Baseline[ic]) continue;
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if     (ic != kPlotSSWWEWK && 
            ic != kPlotSignal0 && ic != kPlotSignal1 && 
            ic != kPlotSignal2 && ic != kPlotSignal2) newcardShape << Form("%d  ", ic);
    else if(ic == kPlotSignal0) newcardShape << Form("%d  ", -1);
    else if(ic == kPlotSignal1) newcardShape << Form("%d  ", -2);
    else if(ic == kPlotSignal2) newcardShape << Form("%d  ", -3);
    else if(ic == kPlotSignal3) newcardShape << Form("%d  ", -4);
    else                        newcardShape << Form("%d  ",  0);
  }
  newcardShape << Form("\n");

  newcardShape << Form("rate  ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(!histo_Baseline[ic]) continue;
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("%f  ", histo_Baseline[ic]->GetSumOfWeights());
  }
  newcardShape << Form("\n");

  for(int ny=2016; ny<2016+nYears; ny++){
    newcardShape << Form("CMS_fake_%d    lnN     ",ny);
    for (int ic=0; ic<nPlotCategories; ic++){
      if(!histo_Baseline[ic]) continue;
      if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
      if(ic == kPlotNonPrompt) newcardShape << Form("%.3f ",TMath::Sqrt(lumiV[ny-2016]/totalLumiV) * (1.2-1.0)+1.0);
      else                     newcardShape << Form("- ");
    }
    newcardShape << Form("\n");
  }

  for(int ny=2016; ny<2016+nYears; ny++){
    newcardShape << Form("lumi_13TeV_%d    lnN     ",ny);
    for (int ic=0; ic<nPlotCategories; ic++){
      if(!histo_Baseline[ic]) continue;
      if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
      if(ic == kPlotNonPrompt) newcardShape << Form("- ");
      else                     newcardShape << Form("%6.3f ",TMath::Sqrt(lumiV[ny-2016]/totalLumiV) * (lumiE[ny-2016]-1.0)+1.0);
    }
    newcardShape << Form("\n");
  }

  newcardShape << Form("CMS_momres_m    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(!histo_Baseline[ic]) continue;
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("%6.3f ",1.005);
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_momres_e    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(!histo_Baseline[ic]) continue;
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("%6.3f ",1.005);
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_trigger    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(!histo_Baseline[ic]) continue;
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("%6.3f ",1.005);
  }
  newcardShape << Form("\n");

  newcardShape << Form("EWKWZCorr    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(!histo_Baseline[ic]) continue;
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotWZ) newcardShape << Form("- ");
    else              newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("EWKqqZZCorr    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(!histo_Baseline[ic]) continue;
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotZZ) newcardShape << Form("- ");
    else              newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("ggZZCorr    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(!histo_Baseline[ic]) continue;
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotZZ) newcardShape << Form("- ");
    else              newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("WZ_lep    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(!histo_Baseline[ic]) continue;
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotWZ && ic != kPlotEWKWZ) newcardShape << Form("- ");
    else                                  newcardShape << Form("%f ",syst_WZl[0]);
  }
  newcardShape << Form("\n");

  newcardShape << Form("WZ_tau    lnN     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(!histo_Baseline[ic]) continue;
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic != kPlotWZ && ic != kPlotEWKWZ) newcardShape << Form("- ");
    else                                  newcardShape << Form("%f ",syst_WZl[1]);
  }
  newcardShape << Form("\n");

  for(unsigned ic=0; ic<nPlotCategories; ic++) {
    if(!histo_Baseline[ic]) continue;
    if(ic== kPlotData || ic == kPlotNonPrompt || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    newcardShape << Form("QCDScale_%s_ACCEPT    shape   ",plotBaseNames[ic].Data());
    for(unsigned ic2=0; ic2<nPlotCategories; ic2++) {
      if(!histo_Baseline[ic2]) continue;
      if(ic2 == kPlotData || histo_Baseline[ic2]->GetSumOfWeights() <= 0) continue;
          if(ic==ic2) newcardShape << Form("1.0  ");
          else       newcardShape << Form("-  ");
      }
      newcardShape << Form("\n");
  }

  newcardShape << Form("PDF    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(!histo_Baseline[ic]) continue;
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_eff_m    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(!histo_Baseline[ic]) continue;
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_eff_e    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(!histo_Baseline[ic]) continue;
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  newcardShape << Form("CMS_pu    shape     ");
  for (int ic=0; ic<nPlotCategories; ic++){
    if(!histo_Baseline[ic]) continue;
    if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
    if(ic == kPlotNonPrompt) newcardShape << Form("- ");
    else                     newcardShape << Form("1.0 ");
  }
  newcardShape << Form("\n");

  for(int ny=2016; ny<2016+nYears; ny++){
     newcardShape << Form("CMS_btagb_%d    shape     ",ny);
     for (int ic=0; ic<nPlotCategories; ic++){
       if(!histo_Baseline[ic]) continue;
       if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
       if(ic == kPlotNonPrompt) newcardShape << Form("- ");
       else                     newcardShape << Form("1.0 ");
     }
     newcardShape << Form("\n");

     newcardShape << Form("CMS_btagl_%d    shape     ",ny);
     for (int ic=0; ic<nPlotCategories; ic++){
       if(!histo_Baseline[ic]) continue;
       if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
       if(ic == kPlotNonPrompt) newcardShape << Form("- ");
       else                     newcardShape << Form("1.0 ");
     }
     newcardShape << Form("\n");

     newcardShape << Form("CMS_jes_%d    shape     ",ny);
     for (int ic=0; ic<nPlotCategories; ic++){
       if(!histo_Baseline[ic]) continue;
       if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
       if(ic == kPlotNonPrompt || ic == kPlotDY) newcardShape << Form("- ");
       else                                      newcardShape << Form("1.0 ");
     }
     newcardShape << Form("\n");

     newcardShape << Form("CMS_prefire_%d    shape     ",ny);
     for (int ic=0; ic<nPlotCategories; ic++){
       if(!histo_Baseline[ic]) continue;
       if(ic == kPlotData || histo_Baseline[ic]->GetSumOfWeights() <= 0) continue;
       if(ic == kPlotNonPrompt) newcardShape << Form("- ");
       else                     newcardShape << Form("1.0 ");
     }
     newcardShape << Form("\n");
  }

  newcardShape << Form("CMS_ssww_wznorm  rateParam * %s 1 [0.1,3]\n",plotBaseNames[kPlotWZ].Data());
  newcardShape << Form("CMS_ssww_wznorm  rateParam * %s 1 [0.1,3]\n",plotBaseNames[kPlotEWKWZ].Data());

  newcardShape << Form("ch1 autoMCStats 0\n");

  newcardShape.close();
}
