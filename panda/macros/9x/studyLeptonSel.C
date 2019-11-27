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
void studyLeptonSel(TString fileName = "MitAnalysisRunII/data/90x/histoDY0EffSFStudy_2016.root", int type = 0){

  const int nLepSel = 16; const int nBaseSel[2] {0, 0};
  TFile *_file0 = TFile::Open(fileName.Data());
  if(!_file0) return;

  if     (type == 0){
    TH2D* histoEffStudy[nLepSel][2];
    for(int nsel=0; nsel<nLepSel; nsel++){
      for(int nt=0; nt<2; nt++){
        histoEffStudy[nsel][nt] = (TH2D*)_file0->Get(Form("histoEffStudy_%d_%d_%d",nsel,nt,0)); histoEffStudy[nsel][nt]->SetDirectory(0);
      }
    }
    for(int nsel=0; nsel<nLepSel; nsel++){
      printf("(%2d): %6.3f %6.3f\n",nsel,histoEffStudy[nsel][0]->GetSumOfWeights()/histoEffStudy[nBaseSel[0]][0]->GetSumOfWeights(),
                                         histoEffStudy[nsel][1]->GetSumOfWeights()/histoEffStudy[nBaseSel[1]][1]->GetSumOfWeights());
    }
  }
  else if(type == 1){
    TH2D* histoFakeDenEtaPt[2];
    TH2D* histoFakeNumSelEtaPt[nLepSel][2];
    for(int i=0; i<2; i++){
      histoFakeDenEtaPt[i] = (TH2D*)_file0->Get(Form("histoFakeDenEtaPt_%d_%d",i,0)); histoFakeDenEtaPt[i]->SetDirectory(0);
      for(int nsel=0; nsel<nLepSel; nsel++){
        histoFakeNumSelEtaPt[nsel][i] = (TH2D*)_file0->Get(Form("histoFakeNumSelEtaPt_%d_%d_%d",nsel,i,0)); histoFakeNumSelEtaPt[nsel][i]->SetDirectory(0);
      }
    }
    for(int nsel=0; nsel<nLepSel; nsel++){
      printf("(%2d): %6.3f %6.3f\n",nsel,histoFakeNumSelEtaPt[nsel][0]->GetSumOfWeights()/histoFakeDenEtaPt[0]->GetSumOfWeights(),
                                         histoFakeNumSelEtaPt[nsel][1]->GetSumOfWeights()/histoFakeDenEtaPt[1]->GetSumOfWeights());
    }
  }

}
