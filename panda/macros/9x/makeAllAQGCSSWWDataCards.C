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

#include "MitAnalysisRunII/panda/macros/9x/makeAQGCSSWWDataCards.C"

void makeAllAQGCSSWWDataCards(TString baseFolder = "/home/ceballos/ana_area/ana_ssww"){
  TString fidAnaName = "_fiducial4";
  int nscanTot = nscan_ft0 + nscan_ft1 + nscan_ft2 + nscan_fm0 + nscan_fm1 + nscan_fm6 + nscan_fm7 + nscan_fs0 + nscan_fs1;
  for(int year=2016; year<=2018; year++){
    for(int iscan=0; iscan<nscanTot; iscan++){
      int theScan = iscan;
      TString AQGC_range = "dummy";
      if     (iscan < nscan_ft0) {theScan = theScan - (0); AQGC_range = AQGCParaName[0] + "_" + AQGC_ft0_range[theScan];}
      else if(iscan < nscan_ft0+nscan_ft1) {theScan = theScan - (nscan_ft0); AQGC_range = AQGCParaName[1] + "_" + AQGC_ft1_range[theScan];}
      else if(iscan < nscan_ft0+nscan_ft1+nscan_ft2) {theScan = theScan - (nscan_ft0+nscan_ft1); AQGC_range = AQGCParaName[2] + "_" + AQGC_ft2_range[theScan];}
      else if(iscan < nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0) {theScan = theScan - (nscan_ft0+nscan_ft1+nscan_ft2); AQGC_range = AQGCParaName[3] + "_" + AQGC_fm0_range[theScan];}
      else if(iscan < nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0+nscan_fm1) {theScan = theScan - (nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0); AQGC_range = AQGCParaName[4] + "_" + AQGC_fm1_range[theScan];}
      else if(iscan < nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0+nscan_fm1+nscan_fm6) {theScan = theScan - (nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0+nscan_fm1); AQGC_range = AQGCParaName[5] + "_" + AQGC_fm6_range[theScan];}
      else if(iscan < nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0+nscan_fm1+nscan_fm6+nscan_fm7) {theScan = theScan - (nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0+nscan_fm1+nscan_fm6); AQGC_range = AQGCParaName[6] + "_" + AQGC_fm7_range[theScan];}
      else if(iscan < nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0+nscan_fm1+nscan_fm6+nscan_fm7+nscan_fs0) {theScan = theScan - (nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0+nscan_fm1+nscan_fm6+nscan_fm7); AQGC_range = AQGCParaName[7] + "_" + AQGC_fs0_range[theScan];}
      else if(iscan < nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0+nscan_fm1+nscan_fm6+nscan_fm7+nscan_fs0+nscan_fs1) {theScan = theScan - (nscan_ft0+nscan_ft1+nscan_ft2+nscan_fm0+nscan_fm1+nscan_fm6+nscan_fm7+nscan_fs0); AQGC_range = AQGCParaName[8] + "_" + AQGC_fs1_range[theScan];}
      TString outputLimits = Form("ssww_aqgc_%s_%d%s_input.root",AQGC_range.Data(),year,fidAnaName.Data());
      printf("%s\n",outputLimits.Data());
      makeAQGCSSWWDataCards(baseFolder.Data(), outputLimits.Data());
    }
  }
}
