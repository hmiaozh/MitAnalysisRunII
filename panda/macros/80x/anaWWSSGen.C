void anaWWSSGen(int nsel = 0) {
TString inputPandaFolder = "/data/t3home000/ceballos/panda/v_001_0";
TString inputNeroFolder = "/home/ceballos/cms/cmssw/047/CMSSW_8_0_26_patch1/src/inputs_wwssgen";

const int nFiles = 2;
TFile *_fileP[nFiles],*_fileN[nFiles];
_fileP[0] = TFile::Open(Form("%s/WpWp_EWK.root", inputPandaFolder.Data()));
_fileP[1] = TFile::Open(Form("%s/WpWp_QCD.root", inputPandaFolder.Data()));
_fileN[0] = TFile::Open(Form("%s/histoMllGen_EWK.root", inputNeroFolder.Data()));
_fileN[1] = TFile::Open(Form("%s/histoMllGen_QCD.root", inputNeroFolder.Data()));

double xs[nFiles] = {0.0269642, 0.0261515};
double lumi = 35.9*1000;
TString names[nFiles] = {"EWK", "QCD"};

TH1D *hDITotalMCWeight[nFiles];

TH1D *hDWWSSMLL[nFiles];
TH1D *histoMllGen[nFiles];
TH1D *histoRatio[nFiles];

     TH1D *hDIDilPtMM_PDF[nFiles];	TH1D *hDIDilPtMM_QCD[nFiles];	 
TH1D *hDIDilPtEE[nFiles];     TH1D *hDIDilPtEE_PDF[nFiles];	TH1D *hDIDilPtEE_QCD[nFiles];	 
TH1D *hDIDilRapMM[nFiles];    TH1D *hDIDilRapMM_PDF[nFiles];	TH1D *hDIDilRapMM_QCD[nFiles];   
TH1D *hDIDilRapEE[nFiles];    TH1D *hDIDilRapEE_PDF[nFiles];	TH1D *hDIDilRapEE_QCD[nFiles];   
TH1D *hDIDilPhiStarMM[nFiles];TH1D *hDIDilPhiStarMM_PDF[nFiles];TH1D *hDIDilPhiStarMM_QCD[nFiles];    
TH1D *hDIDilPhiStarEE[nFiles];TH1D *hDIDilPhiStarEE_PDF[nFiles];TH1D *hDIDilPhiStarEE_QCD[nFiles];    
TH1D *hDIDilPtRap0MM[nFiles]; TH1D *hDIDilPtRap0MM_PDF[nFiles]; TH1D *hDIDilPtRap0MM_QCD[nFiles];
TH1D *hDIDilPtRap0EE[nFiles]; TH1D *hDIDilPtRap0EE_PDF[nFiles]; TH1D *hDIDilPtRap0EE_QCD[nFiles];
TH1D *hDIDilPtRap1MM[nFiles]; TH1D *hDIDilPtRap1MM_PDF[nFiles]; TH1D *hDIDilPtRap1MM_QCD[nFiles];
TH1D *hDIDilPtRap1EE[nFiles]; TH1D *hDIDilPtRap1EE_PDF[nFiles]; TH1D *hDIDilPtRap1EE_QCD[nFiles];
TH1D *hDIDilPtRap2MM[nFiles]; TH1D *hDIDilPtRap2MM_PDF[nFiles]; TH1D *hDIDilPtRap2MM_QCD[nFiles];
TH1D *hDIDilPtRap2EE[nFiles]; TH1D *hDIDilPtRap2EE_PDF[nFiles]; TH1D *hDIDilPtRap2EE_QCD[nFiles];
TH1D *hDIDilPtRap3MM[nFiles]; TH1D *hDIDilPtRap3MM_PDF[nFiles]; TH1D *hDIDilPtRap3MM_QCD[nFiles];
TH1D *hDIDilPtRap3EE[nFiles]; TH1D *hDIDilPtRap3EE_PDF[nFiles]; TH1D *hDIDilPtRap3EE_QCD[nFiles];
TH1D *hDIDilPtRap4MM[nFiles]; TH1D *hDIDilPtRap4MM_PDF[nFiles]; TH1D *hDIDilPtRap4MM_QCD[nFiles];
TH1D *hDIDilPtRap4EE[nFiles]; TH1D *hDIDilPtRap4EE_PDF[nFiles]; TH1D *hDIDilPtRap4EE_QCD[nFiles];

TFile myOutputFile("genWWSS_Ratio.root","RECREATE");
for(int i=0; i<nFiles; i++){
  hDITotalMCWeight[i] = (TH1D*)_fileP[i]->Get("hDTotalMCWeight");	 

  hDWWSSMLL[i]        = (TH1D*)_fileP[i]->Get("hDWWSSMLL");    hDWWSSMLL[i]->Sumw2();      hDWWSSMLL[i]      ->Scale(lumi*xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  histoMllGen[i]      = (TH1D*)_fileN[i]->Get("histoMllGen");  histoMllGen[i]->Sumw2();

  histoRatio[i]       = (TH1D*)histoMllGen[i]->Clone(Form("eff_%s",names[i].Data()));
  histoRatio[i]->Divide(hDWWSSMLL[i]);
  histoRatio[i]->Write();
}
myOutputFile.Close();

}
