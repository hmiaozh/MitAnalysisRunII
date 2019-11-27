#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TString.h>
#include <TH1D.h>
#include <TMath.h>
#include <iostream>
#include <fstream>
#include <TStyle.h>

#include "MitAnalysisRunII/panda/macros/9x/common.h"

void checkEqualBinning(TString fileName = "", int numberOfBins = 8, bool debug = false, int histoNumber = kPlotEWKWZ){
  TFile *the_input_file = TFile::Open(fileName.Data());
  if(!the_input_file) return;
  TH1D* theHisto = (TH1D*)the_input_file->Get(Form("histo%d",histoNumber));
  if(!theHisto) return;

  const int nBinBDT = numberOfBins; Float_t theInterval[nBinBDT];
  for(int i=0; i<=nBinBDT; i++) theInterval[i] = (i+1.)/numberOfBins;
  theInterval[nBinBDT-1] = 1.001;
  double sum = 0;
  double toKeep[nBinBDT];
  bool theCall[nBinBDT];
  for(int i=0; i<nBinBDT; i++) theCall[i] = false;

  for(int nb=1; nb<=theHisto->GetNbinsX(); nb++){
    sum = sum +  theHisto->GetBinContent(nb) / theHisto->GetSumOfWeights();
    if(debug) printf("%5.3f\n",sum);
    for(int i=0; i<nBinBDT; i++) {
      if(theCall[i] == false && sum > theInterval[i]){
        printf("%3d %5.2f %5.3f %d\n",nb,-1.0+nb/100.,sum,i);
	theCall[i] = true;
	toKeep[i] = -1.0+nb/100.;
        break;
      }
    }
  }

  for(int i=0; i<nBinBDT; i++) {
   if(theCall[i] == true) printf(",%5.2f",toKeep[i]);
  }
  printf("\n");
}
