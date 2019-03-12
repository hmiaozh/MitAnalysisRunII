void mergeZptHist(int nsel = 0) {
TString inputFolder = "/data/t3home000/ceballos/panda/v_001_0";

if(nsel == 0){ // NLO
const int nFiles = 6;
TFile *_file[nFiles];
_file[0] = TFile::Open(Form("%s/DYJetsToLL_Pt0To50.root"  , inputFolder.Data()));
_file[1] = TFile::Open(Form("%s/DYJetsToLL_Pt50To100.root", inputFolder.Data()));
_file[2] = TFile::Open(Form("%s/DYJetsToLL_Pt100To250.root",inputFolder.Data()));
_file[3] = TFile::Open(Form("%s/DYJetsToLL_Pt250To400.root",inputFolder.Data()));
_file[4] = TFile::Open(Form("%s/DYJetsToLL_Pt400To650.root",inputFolder.Data()));
_file[5] = TFile::Open(Form("%s/DYJetsToLL_Pt650ToInf.root",inputFolder.Data()));

double xs[6] = {5512.4400*2075.14/2008.4,
                 374.6800*2075.14/2008.4,
		  86.5200*2075.14/2008.4,
		   3.3247*2075.14/2008.4,
		   0.4491*2075.14/2008.4,
		   0.0422*2075.14/2008.4
               };

TH1D *hDITotalMCWeight[nFiles];

TH1D *hDIDilPtMM[nFiles];     TH1D *hDIDilPtMM_PDF[nFiles];	TH1D *hDIDilPtMM_QCD[nFiles];	 
TH1D *hDIDilPtEE[nFiles];     TH1D *hDIDilPtEE_PDF[nFiles];	TH1D *hDIDilPtEE_QCD[nFiles];	 
TH1D *hDIDilHighPtIncMM[nFiles]; TH1D *hDIDilHighPtIncMM_PDF[nFiles];	TH1D *hDIDilHighPtIncMM_QCD[nFiles];	 
TH1D *hDIDilHighPtIncEE[nFiles]; TH1D *hDIDilHighPtIncEE_PDF[nFiles];	TH1D *hDIDilHighPtIncEE_QCD[nFiles];	 
TH1D *hDIDilHighPtMM[nFiles]; TH1D *hDIDilHighPtMM_PDF[nFiles];	TH1D *hDIDilHighPtMM_QCD[nFiles];	 
TH1D *hDIDilHighPtEE[nFiles]; TH1D *hDIDilHighPtEE_PDF[nFiles];	TH1D *hDIDilHighPtEE_QCD[nFiles];	 
TH1D *hDIDilHighPtNoEWKMM[nFiles];	    
TH1D *hDIDilHighPtNoEWKEE[nFiles];	    
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

for(int i=0; i<nFiles; i++){
  hDITotalMCWeight[i] = (TH1D*)_file[i]->Get("hDTotalMCWeight");	 

  hDIDilPtMM[i]       = (TH1D*)_file[i]->Get("hDDilPtMM");     hDIDilPtMM[i]->Sumw2();     hDIDilPtMM[i]     ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilPtEE[i]       = (TH1D*)_file[i]->Get("hDDilPtEE");     hDIDilPtEE[i]->Sumw2();     hDIDilPtEE[i]     ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtIncMM[i]   = (TH1D*)_file[i]->Get("hDDilHighPtIncMM"); hDIDilHighPtIncMM[i]->Sumw2(); hDIDilHighPtIncMM[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtIncEE[i]   = (TH1D*)_file[i]->Get("hDDilHighPtIncEE"); hDIDilHighPtIncEE[i]->Sumw2(); hDIDilHighPtIncEE[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtMM[i]   = (TH1D*)_file[i]->Get("hDDilHighPtMM"); hDIDilHighPtMM[i]->Sumw2(); hDIDilHighPtMM[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtEE[i]   = (TH1D*)_file[i]->Get("hDDilHighPtEE"); hDIDilHighPtEE[i]->Sumw2(); hDIDilHighPtEE[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtNoEWKMM[i]   = (TH1D*)_file[i]->Get("hDDilHighPtNoEWKMM"); hDIDilHighPtNoEWKMM[i]->Sumw2(); hDIDilHighPtNoEWKMM[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtNoEWKEE[i]   = (TH1D*)_file[i]->Get("hDDilHighPtNoEWKEE"); hDIDilHighPtNoEWKEE[i]->Sumw2(); hDIDilHighPtNoEWKEE[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilRapMM[i]      = (TH1D*)_file[i]->Get("hDDilRapMM");    hDIDilRapMM[i]->Sumw2();    hDIDilRapMM[i]    ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIDilRapEE[i]      = (TH1D*)_file[i]->Get("hDDilRapEE");    hDIDilRapEE[i]->Sumw2();    hDIDilRapEE[i]    ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIDilPhiStarMM[i]  = (TH1D*)_file[i]->Get("hDDilPhiStarMM");hDIDilPhiStarMM[i]->Sumw2();hDIDilPhiStarMM[i]->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());	    
  hDIDilPhiStarEE[i]  = (TH1D*)_file[i]->Get("hDDilPhiStarEE");hDIDilPhiStarEE[i]->Sumw2();hDIDilPhiStarEE[i]->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());	    
  hDIDilPtRap0MM[i]   = (TH1D*)_file[i]->Get("hDDilPtRap0MM"); hDIDilPtRap0MM[i]->Sumw2(); hDIDilPtRap0MM[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap0EE[i]   = (TH1D*)_file[i]->Get("hDDilPtRap0EE"); hDIDilPtRap0EE[i]->Sumw2(); hDIDilPtRap0EE[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap1MM[i]   = (TH1D*)_file[i]->Get("hDDilPtRap1MM"); hDIDilPtRap1MM[i]->Sumw2(); hDIDilPtRap1MM[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap1EE[i]   = (TH1D*)_file[i]->Get("hDDilPtRap1EE"); hDIDilPtRap1EE[i]->Sumw2(); hDIDilPtRap1EE[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap2MM[i]   = (TH1D*)_file[i]->Get("hDDilPtRap2MM"); hDIDilPtRap2MM[i]->Sumw2(); hDIDilPtRap2MM[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap2EE[i]   = (TH1D*)_file[i]->Get("hDDilPtRap2EE"); hDIDilPtRap2EE[i]->Sumw2(); hDIDilPtRap2EE[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap3MM[i]   = (TH1D*)_file[i]->Get("hDDilPtRap3MM"); hDIDilPtRap3MM[i]->Sumw2(); hDIDilPtRap3MM[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap3EE[i]   = (TH1D*)_file[i]->Get("hDDilPtRap3EE"); hDIDilPtRap3EE[i]->Sumw2(); hDIDilPtRap3EE[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap4MM[i]   = (TH1D*)_file[i]->Get("hDDilPtRap4MM"); hDIDilPtRap4MM[i]->Sumw2(); hDIDilPtRap4MM[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap4EE[i]   = (TH1D*)_file[i]->Get("hDDilPtRap4EE"); hDIDilPtRap4EE[i]->Sumw2(); hDIDilPtRap4EE[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());

  hDIDilPtMM_PDF[i]       = (TH1D*)_file[i]->Get("hDDilPtMM_PDF");     hDIDilPtMM_PDF[i]     ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilPtEE_PDF[i]       = (TH1D*)_file[i]->Get("hDDilPtEE_PDF");     hDIDilPtEE_PDF[i]     ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtIncMM_PDF[i]   = (TH1D*)_file[i]->Get("hDDilHighPtIncMM_PDF"); hDIDilHighPtIncMM_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtIncEE_PDF[i]   = (TH1D*)_file[i]->Get("hDDilHighPtIncEE_PDF"); hDIDilHighPtIncEE_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtMM_PDF[i]   = (TH1D*)_file[i]->Get("hDDilHighPtMM_PDF"); hDIDilHighPtMM_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtEE_PDF[i]   = (TH1D*)_file[i]->Get("hDDilHighPtEE_PDF"); hDIDilHighPtEE_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilRapMM_PDF[i]      = (TH1D*)_file[i]->Get("hDDilRapMM_PDF");    hDIDilRapMM_PDF[i]    ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIDilRapEE_PDF[i]      = (TH1D*)_file[i]->Get("hDDilRapEE_PDF");    hDIDilRapEE_PDF[i]    ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIDilPhiStarMM_PDF[i]  = (TH1D*)_file[i]->Get("hDDilPhiStarMM_PDF");hDIDilPhiStarMM_PDF[i]->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());       
  hDIDilPhiStarEE_PDF[i]  = (TH1D*)_file[i]->Get("hDDilPhiStarEE_PDF");hDIDilPhiStarEE_PDF[i]->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());       
  hDIDilPtRap0MM_PDF[i]   = (TH1D*)_file[i]->Get("hDDilPtRap0MM_PDF"); hDIDilPtRap0MM_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap0EE_PDF[i]   = (TH1D*)_file[i]->Get("hDDilPtRap0EE_PDF"); hDIDilPtRap0EE_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap1MM_PDF[i]   = (TH1D*)_file[i]->Get("hDDilPtRap1MM_PDF"); hDIDilPtRap1MM_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap1EE_PDF[i]   = (TH1D*)_file[i]->Get("hDDilPtRap1EE_PDF"); hDIDilPtRap1EE_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap2MM_PDF[i]   = (TH1D*)_file[i]->Get("hDDilPtRap2MM_PDF"); hDIDilPtRap2MM_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap2EE_PDF[i]   = (TH1D*)_file[i]->Get("hDDilPtRap2EE_PDF"); hDIDilPtRap2EE_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap3MM_PDF[i]   = (TH1D*)_file[i]->Get("hDDilPtRap3MM_PDF"); hDIDilPtRap3MM_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap3EE_PDF[i]   = (TH1D*)_file[i]->Get("hDDilPtRap3EE_PDF"); hDIDilPtRap3EE_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap4MM_PDF[i]   = (TH1D*)_file[i]->Get("hDDilPtRap4MM_PDF"); hDIDilPtRap4MM_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap4EE_PDF[i]   = (TH1D*)_file[i]->Get("hDDilPtRap4EE_PDF"); hDIDilPtRap4EE_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());

  hDIDilPtMM_QCD[i]       = (TH1D*)_file[i]->Get("hDDilPtMM_QCD");     hDIDilPtMM_QCD[i]     ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilPtEE_QCD[i]       = (TH1D*)_file[i]->Get("hDDilPtEE_QCD");     hDIDilPtEE_QCD[i]     ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtIncMM_QCD[i]   = (TH1D*)_file[i]->Get("hDDilHighPtIncMM_QCD"); hDIDilHighPtIncMM_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtIncEE_QCD[i]   = (TH1D*)_file[i]->Get("hDDilHighPtIncEE_QCD"); hDIDilHighPtIncEE_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtMM_QCD[i]   = (TH1D*)_file[i]->Get("hDDilHighPtMM_QCD"); hDIDilHighPtMM_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtEE_QCD[i]   = (TH1D*)_file[i]->Get("hDDilHighPtEE_QCD"); hDIDilHighPtEE_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilRapMM_QCD[i]      = (TH1D*)_file[i]->Get("hDDilRapMM_QCD");    hDIDilRapMM_QCD[i]    ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIDilRapEE_QCD[i]      = (TH1D*)_file[i]->Get("hDDilRapEE_QCD");    hDIDilRapEE_QCD[i]    ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIDilPhiStarMM_QCD[i]  = (TH1D*)_file[i]->Get("hDDilPhiStarMM_QCD");hDIDilPhiStarMM_QCD[i]->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());       
  hDIDilPhiStarEE_QCD[i]  = (TH1D*)_file[i]->Get("hDDilPhiStarEE_QCD");hDIDilPhiStarEE_QCD[i]->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());       
  hDIDilPtRap0MM_QCD[i]   = (TH1D*)_file[i]->Get("hDDilPtRap0MM_QCD"); hDIDilPtRap0MM_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap0EE_QCD[i]   = (TH1D*)_file[i]->Get("hDDilPtRap0EE_QCD"); hDIDilPtRap0EE_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap1MM_QCD[i]   = (TH1D*)_file[i]->Get("hDDilPtRap1MM_QCD"); hDIDilPtRap1MM_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap1EE_QCD[i]   = (TH1D*)_file[i]->Get("hDDilPtRap1EE_QCD"); hDIDilPtRap1EE_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap2MM_QCD[i]   = (TH1D*)_file[i]->Get("hDDilPtRap2MM_QCD"); hDIDilPtRap2MM_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap2EE_QCD[i]   = (TH1D*)_file[i]->Get("hDDilPtRap2EE_QCD"); hDIDilPtRap2EE_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap3MM_QCD[i]   = (TH1D*)_file[i]->Get("hDDilPtRap3MM_QCD"); hDIDilPtRap3MM_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap3EE_QCD[i]   = (TH1D*)_file[i]->Get("hDDilPtRap3EE_QCD"); hDIDilPtRap3EE_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap4MM_QCD[i]   = (TH1D*)_file[i]->Get("hDDilPtRap4MM_QCD"); hDIDilPtRap4MM_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap4EE_QCD[i]   = (TH1D*)_file[i]->Get("hDDilPtRap4EE_QCD"); hDIDilPtRap4EE_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
}

TH1D *hDDilPtMM      = (TH1D*)hDIDilPtMM     [0]->Clone();
TH1D *hDDilPtEE      = (TH1D*)hDIDilPtEE     [0]->Clone();
TH1D *hDDilHighPtIncMM  = (TH1D*)hDIDilHighPtIncMM [0]->Clone();
TH1D *hDDilHighPtIncEE  = (TH1D*)hDIDilHighPtIncEE [0]->Clone();
TH1D *hDDilHighPtMM  = (TH1D*)hDIDilHighPtMM [0]->Clone();
TH1D *hDDilHighPtEE  = (TH1D*)hDIDilHighPtEE [0]->Clone();
TH1D *hDDilHighPtNoEWKMM  = (TH1D*)hDIDilHighPtNoEWKMM [0]->Clone();
TH1D *hDDilHighPtNoEWKEE  = (TH1D*)hDIDilHighPtNoEWKEE [0]->Clone();
TH1D *hDDilRapMM     = (TH1D*)hDIDilRapMM    [0]->Clone();
TH1D *hDDilRapEE     = (TH1D*)hDIDilRapEE    [0]->Clone();
TH1D *hDDilPhiStarMM = (TH1D*)hDIDilPhiStarMM[0]->Clone();
TH1D *hDDilPhiStarEE = (TH1D*)hDIDilPhiStarEE[0]->Clone();
TH1D *hDDilPtRap0MM  = (TH1D*)hDIDilPtRap0MM [0]->Clone();
TH1D *hDDilPtRap0EE  = (TH1D*)hDIDilPtRap0EE [0]->Clone();
TH1D *hDDilPtRap1MM  = (TH1D*)hDIDilPtRap1MM [0]->Clone();
TH1D *hDDilPtRap1EE  = (TH1D*)hDIDilPtRap1EE [0]->Clone();
TH1D *hDDilPtRap2MM  = (TH1D*)hDIDilPtRap2MM [0]->Clone();
TH1D *hDDilPtRap2EE  = (TH1D*)hDIDilPtRap2EE [0]->Clone();
TH1D *hDDilPtRap3MM  = (TH1D*)hDIDilPtRap3MM [0]->Clone();
TH1D *hDDilPtRap3EE  = (TH1D*)hDIDilPtRap3EE [0]->Clone();
TH1D *hDDilPtRap4MM  = (TH1D*)hDIDilPtRap4MM [0]->Clone();
TH1D *hDDilPtRap4EE  = (TH1D*)hDIDilPtRap4EE [0]->Clone();

TH1D *hDDilPtMM_PDF      = (TH1D*)hDIDilPtMM_PDF     [0]->Clone();
TH1D *hDDilPtEE_PDF      = (TH1D*)hDIDilPtEE_PDF     [0]->Clone();
TH1D *hDDilHighPtIncMM_PDF  = (TH1D*)hDIDilHighPtIncMM_PDF [0]->Clone();
TH1D *hDDilHighPtIncEE_PDF  = (TH1D*)hDIDilHighPtIncEE_PDF [0]->Clone();
TH1D *hDDilHighPtMM_PDF  = (TH1D*)hDIDilHighPtMM_PDF [0]->Clone();
TH1D *hDDilHighPtEE_PDF  = (TH1D*)hDIDilHighPtEE_PDF [0]->Clone();
TH1D *hDDilRapMM_PDF     = (TH1D*)hDIDilRapMM_PDF    [0]->Clone();
TH1D *hDDilRapEE_PDF     = (TH1D*)hDIDilRapEE_PDF    [0]->Clone();
TH1D *hDDilPhiStarMM_PDF = (TH1D*)hDIDilPhiStarMM_PDF[0]->Clone();
TH1D *hDDilPhiStarEE_PDF = (TH1D*)hDIDilPhiStarEE_PDF[0]->Clone();
TH1D *hDDilPtRap0MM_PDF  = (TH1D*)hDIDilPtRap0MM_PDF [0]->Clone();
TH1D *hDDilPtRap0EE_PDF  = (TH1D*)hDIDilPtRap0EE_PDF [0]->Clone();
TH1D *hDDilPtRap1MM_PDF  = (TH1D*)hDIDilPtRap1MM_PDF [0]->Clone();
TH1D *hDDilPtRap1EE_PDF  = (TH1D*)hDIDilPtRap1EE_PDF [0]->Clone();
TH1D *hDDilPtRap2MM_PDF  = (TH1D*)hDIDilPtRap2MM_PDF [0]->Clone();
TH1D *hDDilPtRap2EE_PDF  = (TH1D*)hDIDilPtRap2EE_PDF [0]->Clone();
TH1D *hDDilPtRap3MM_PDF  = (TH1D*)hDIDilPtRap3MM_PDF [0]->Clone();
TH1D *hDDilPtRap3EE_PDF  = (TH1D*)hDIDilPtRap3EE_PDF [0]->Clone();
TH1D *hDDilPtRap4MM_PDF  = (TH1D*)hDIDilPtRap4MM_PDF [0]->Clone();
TH1D *hDDilPtRap4EE_PDF  = (TH1D*)hDIDilPtRap4EE_PDF [0]->Clone();

TH1D *hDDilPtMM_QCD      = (TH1D*)hDIDilPtMM_QCD     [0]->Clone();
TH1D *hDDilPtEE_QCD      = (TH1D*)hDIDilPtEE_QCD     [0]->Clone();
TH1D *hDDilHighPtIncMM_QCD  = (TH1D*)hDIDilHighPtIncMM_QCD [0]->Clone();
TH1D *hDDilHighPtIncEE_QCD  = (TH1D*)hDIDilHighPtIncEE_QCD [0]->Clone();
TH1D *hDDilHighPtMM_QCD  = (TH1D*)hDIDilHighPtMM_QCD [0]->Clone();
TH1D *hDDilHighPtEE_QCD  = (TH1D*)hDIDilHighPtEE_QCD [0]->Clone();
TH1D *hDDilRapMM_QCD     = (TH1D*)hDIDilRapMM_QCD    [0]->Clone();
TH1D *hDDilRapEE_QCD     = (TH1D*)hDIDilRapEE_QCD    [0]->Clone();
TH1D *hDDilPhiStarMM_QCD = (TH1D*)hDIDilPhiStarMM_QCD[0]->Clone();
TH1D *hDDilPhiStarEE_QCD = (TH1D*)hDIDilPhiStarEE_QCD[0]->Clone();
TH1D *hDDilPtRap0MM_QCD  = (TH1D*)hDIDilPtRap0MM_QCD [0]->Clone();
TH1D *hDDilPtRap0EE_QCD  = (TH1D*)hDIDilPtRap0EE_QCD [0]->Clone();
TH1D *hDDilPtRap1MM_QCD  = (TH1D*)hDIDilPtRap1MM_QCD [0]->Clone();
TH1D *hDDilPtRap1EE_QCD  = (TH1D*)hDIDilPtRap1EE_QCD [0]->Clone();
TH1D *hDDilPtRap2MM_QCD  = (TH1D*)hDIDilPtRap2MM_QCD [0]->Clone();
TH1D *hDDilPtRap2EE_QCD  = (TH1D*)hDIDilPtRap2EE_QCD [0]->Clone();
TH1D *hDDilPtRap3MM_QCD  = (TH1D*)hDIDilPtRap3MM_QCD [0]->Clone();
TH1D *hDDilPtRap3EE_QCD  = (TH1D*)hDIDilPtRap3EE_QCD [0]->Clone();
TH1D *hDDilPtRap4MM_QCD  = (TH1D*)hDIDilPtRap4MM_QCD [0]->Clone();
TH1D *hDDilPtRap4EE_QCD  = (TH1D*)hDIDilPtRap4EE_QCD [0]->Clone();

for(int i=1; i<nFiles; i++){
  hDDilPtMM	->Add(hDIDilPtMM     [i]);   
  hDDilPtEE	->Add(hDIDilPtEE     [i]);   
  hDDilHighPtIncMM	->Add(hDIDilHighPtIncMM [i]);   
  hDDilHighPtIncEE	->Add(hDIDilHighPtIncEE [i]);   
  hDDilHighPtMM	->Add(hDIDilHighPtMM [i]);   
  hDDilHighPtEE	->Add(hDIDilHighPtEE [i]);   
  hDDilHighPtNoEWKMM	->Add(hDIDilHighPtNoEWKMM [i]);   
  hDDilHighPtNoEWKEE	->Add(hDIDilHighPtNoEWKEE [i]);   
  hDDilRapMM	->Add(hDIDilRapMM    [i]);  
  hDDilRapEE	->Add(hDIDilRapEE    [i]);  
  hDDilPhiStarMM->Add(hDIDilPhiStarMM[i]);  
  hDDilPhiStarEE->Add(hDIDilPhiStarEE[i]);  
  hDDilPtRap0MM ->Add(hDIDilPtRap0MM [i]);  
  hDDilPtRap0EE ->Add(hDIDilPtRap0EE [i]);  
  hDDilPtRap1MM ->Add(hDIDilPtRap1MM [i]);
  hDDilPtRap1EE ->Add(hDIDilPtRap1EE [i]);
  hDDilPtRap2MM ->Add(hDIDilPtRap2MM [i]);
  hDDilPtRap2EE ->Add(hDIDilPtRap2EE [i]);
  hDDilPtRap3MM ->Add(hDIDilPtRap3MM [i]);
  hDDilPtRap3EE ->Add(hDIDilPtRap3EE [i]);
  hDDilPtRap4MM ->Add(hDIDilPtRap4MM [i]);
  hDDilPtRap4EE ->Add(hDIDilPtRap4EE [i]);

  hDDilPtMM_PDF     ->Add(hDIDilPtMM_PDF     [i]);   
  hDDilPtEE_PDF     ->Add(hDIDilPtEE_PDF     [i]);   
  hDDilHighPtIncMM_PDF ->Add(hDIDilHighPtIncMM_PDF [i]);   
  hDDilHighPtIncEE_PDF ->Add(hDIDilHighPtIncEE_PDF [i]);   
  hDDilHighPtMM_PDF ->Add(hDIDilHighPtMM_PDF [i]);   
  hDDilHighPtEE_PDF ->Add(hDIDilHighPtEE_PDF [i]);   
  hDDilRapMM_PDF    ->Add(hDIDilRapMM_PDF    [i]);  
  hDDilRapEE_PDF    ->Add(hDIDilRapEE_PDF    [i]);  
  hDDilPhiStarMM_PDF->Add(hDIDilPhiStarMM_PDF[i]);  
  hDDilPhiStarEE_PDF->Add(hDIDilPhiStarEE_PDF[i]);  
  hDDilPtRap0MM_PDF ->Add(hDIDilPtRap0MM_PDF [i]);  
  hDDilPtRap0EE_PDF ->Add(hDIDilPtRap0EE_PDF [i]);  
  hDDilPtRap1MM_PDF ->Add(hDIDilPtRap1MM_PDF [i]);
  hDDilPtRap1EE_PDF ->Add(hDIDilPtRap1EE_PDF [i]);
  hDDilPtRap2MM_PDF ->Add(hDIDilPtRap2MM_PDF [i]);
  hDDilPtRap2EE_PDF ->Add(hDIDilPtRap2EE_PDF [i]);
  hDDilPtRap3MM_PDF ->Add(hDIDilPtRap3MM_PDF [i]);
  hDDilPtRap3EE_PDF ->Add(hDIDilPtRap3EE_PDF [i]);
  hDDilPtRap4MM_PDF ->Add(hDIDilPtRap4MM_PDF [i]);
  hDDilPtRap4EE_PDF ->Add(hDIDilPtRap4EE_PDF [i]);

  hDDilPtMM_QCD     ->Add(hDIDilPtMM_QCD     [i]);   
  hDDilPtEE_QCD     ->Add(hDIDilPtEE_QCD     [i]);   
  hDDilHighPtIncMM_QCD ->Add(hDIDilHighPtIncMM_QCD [i]);   
  hDDilHighPtIncEE_QCD ->Add(hDIDilHighPtIncEE_QCD [i]);   
  hDDilHighPtMM_QCD ->Add(hDIDilHighPtMM_QCD [i]);   
  hDDilHighPtEE_QCD ->Add(hDIDilHighPtEE_QCD [i]);   
  hDDilRapMM_QCD    ->Add(hDIDilRapMM_QCD    [i]);  
  hDDilRapEE_QCD    ->Add(hDIDilRapEE_QCD    [i]);  
  hDDilPhiStarMM_QCD->Add(hDIDilPhiStarMM_QCD[i]);  
  hDDilPhiStarEE_QCD->Add(hDIDilPhiStarEE_QCD[i]);  
  hDDilPtRap0MM_QCD ->Add(hDIDilPtRap0MM_QCD [i]);  
  hDDilPtRap0EE_QCD ->Add(hDIDilPtRap0EE_QCD [i]);  
  hDDilPtRap1MM_QCD ->Add(hDIDilPtRap1MM_QCD [i]);
  hDDilPtRap1EE_QCD ->Add(hDIDilPtRap1EE_QCD [i]);
  hDDilPtRap2MM_QCD ->Add(hDIDilPtRap2MM_QCD [i]);
  hDDilPtRap2EE_QCD ->Add(hDIDilPtRap2EE_QCD [i]);
  hDDilPtRap3MM_QCD ->Add(hDIDilPtRap3MM_QCD [i]);
  hDDilPtRap3EE_QCD ->Add(hDIDilPtRap3EE_QCD [i]);
  hDDilPtRap4MM_QCD ->Add(hDIDilPtRap4MM_QCD [i]);
  hDDilPtRap4EE_QCD ->Add(hDIDilPtRap4EE_QCD [i]);
}

TFile myOutputFile("genZpt_NLO.root","RECREATE");
  hDDilPtMM	->Write(); 
  hDDilPtEE	->Write(); 
  hDDilHighPtIncMM	->Write(); 
  hDDilHighPtIncEE	->Write(); 
  hDDilHighPtMM	->Write(); 
  hDDilHighPtEE	->Write(); 
  hDDilHighPtNoEWKMM	->Write(); 
  hDDilHighPtNoEWKEE	->Write(); 
  hDDilRapMM	->Write();
  hDDilRapEE	->Write();
  hDDilPhiStarMM->Write();
  hDDilPhiStarEE->Write();
  hDDilPtRap0MM ->Write();
  hDDilPtRap0EE ->Write();
  hDDilPtRap1MM ->Write();
  hDDilPtRap1EE ->Write();
  hDDilPtRap2MM ->Write();
  hDDilPtRap2EE ->Write();
  hDDilPtRap3MM ->Write();
  hDDilPtRap3EE ->Write();
  hDDilPtRap4MM ->Write();
  hDDilPtRap4EE ->Write();

  hDDilPtMM_PDF     ->Write(); 
  hDDilPtEE_PDF     ->Write(); 
  hDDilHighPtIncMM_PDF ->Write(); 
  hDDilHighPtIncEE_PDF ->Write(); 
  hDDilHighPtMM_PDF ->Write(); 
  hDDilHighPtEE_PDF ->Write(); 
  hDDilRapMM_PDF    ->Write();
  hDDilRapEE_PDF    ->Write();
  hDDilPhiStarMM_PDF->Write();
  hDDilPhiStarEE_PDF->Write();
  hDDilPtRap0MM_PDF ->Write();
  hDDilPtRap0EE_PDF ->Write();
  hDDilPtRap1MM_PDF ->Write();
  hDDilPtRap1EE_PDF ->Write();
  hDDilPtRap2MM_PDF ->Write();
  hDDilPtRap2EE_PDF ->Write();
  hDDilPtRap3MM_PDF ->Write();
  hDDilPtRap3EE_PDF ->Write();
  hDDilPtRap4MM_PDF ->Write();
  hDDilPtRap4EE_PDF ->Write();

  hDDilPtMM_QCD     ->Write(); 
  hDDilPtEE_QCD     ->Write(); 
  hDDilHighPtIncMM_QCD ->Write(); 
  hDDilHighPtIncEE_QCD ->Write(); 
  hDDilHighPtMM_QCD ->Write(); 
  hDDilHighPtEE_QCD ->Write(); 
  hDDilRapMM_QCD    ->Write();
  hDDilRapEE_QCD    ->Write();
  hDDilPhiStarMM_QCD->Write();
  hDDilPhiStarEE_QCD->Write();
  hDDilPtRap0MM_QCD ->Write();
  hDDilPtRap0EE_QCD ->Write();
  hDDilPtRap1MM_QCD ->Write();
  hDDilPtRap1EE_QCD ->Write();
  hDDilPtRap2MM_QCD ->Write();
  hDDilPtRap2EE_QCD ->Write();
  hDDilPtRap3MM_QCD ->Write();
  hDDilPtRap3EE_QCD ->Write();
  hDDilPtRap4MM_QCD ->Write();
  hDDilPtRap4EE_QCD ->Write();
myOutputFile.Close();

} 
else if(nsel == 1){ // LO
const int nFiles = 3;
TFile *_file[nFiles];
_file[0] = TFile::Open(Form("%s/DYJetsToLL_M-50_LO_Pt000To050.root", inputFolder.Data()));
_file[1] = TFile::Open(Form("%s/DYJetsToLL_M-50_LO_Pt100to200.root", inputFolder.Data()));
_file[2] = TFile::Open(Form("%s/DYJetsToLL_M-50_LO_Pt200toInf.root",inputFolder.Data()));

double xs[nFiles] = {2075.14*3,
                       69.586*2075.14/2008.4,
		        8.186*2075.14/2008.4};

TH1D *hDITotalMCWeight[nFiles];

TH1D *hDIDilPtMM[nFiles];     TH1D *hDIDilPtMM_PDF[nFiles];	TH1D *hDIDilPtMM_QCD[nFiles];	 
TH1D *hDIDilPtEE[nFiles];     TH1D *hDIDilPtEE_PDF[nFiles];	TH1D *hDIDilPtEE_QCD[nFiles];	 
TH1D *hDIDilHighPtIncMM[nFiles]; TH1D *hDIDilHighPtIncMM_PDF[nFiles];	TH1D *hDIDilHighPtIncMM_QCD[nFiles];	 
TH1D *hDIDilHighPtIncEE[nFiles]; TH1D *hDIDilHighPtIncEE_PDF[nFiles];	TH1D *hDIDilHighPtIncEE_QCD[nFiles];	 
TH1D *hDIDilHighPtMM[nFiles]; TH1D *hDIDilHighPtMM_PDF[nFiles];	TH1D *hDIDilHighPtMM_QCD[nFiles];	 
TH1D *hDIDilHighPtEE[nFiles]; TH1D *hDIDilHighPtEE_PDF[nFiles];	TH1D *hDIDilHighPtEE_QCD[nFiles];	 
TH1D *hDIDilHighPtNoEWKMM[nFiles];   
TH1D *hDIDilHighPtNoEWKEE[nFiles];   
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

for(int i=0; i<nFiles; i++){
  hDITotalMCWeight[i] = (TH1D*)_file[i]->Get("hDTotalMCWeight");	 

  hDIDilPtMM[i]       = (TH1D*)_file[i]->Get("hDDilPtMM");     hDIDilPtMM[i]->Sumw2();     hDIDilPtMM[i]     ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilPtEE[i]       = (TH1D*)_file[i]->Get("hDDilPtEE");     hDIDilPtEE[i]->Sumw2();     hDIDilPtEE[i]     ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtIncMM[i]   = (TH1D*)_file[i]->Get("hDDilHighPtIncMM"); hDIDilHighPtIncMM[i]->Sumw2(); hDIDilHighPtIncMM[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtIncEE[i]   = (TH1D*)_file[i]->Get("hDDilHighPtIncEE"); hDIDilHighPtIncEE[i]->Sumw2(); hDIDilHighPtIncEE[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtMM[i]   = (TH1D*)_file[i]->Get("hDDilHighPtMM"); hDIDilHighPtMM[i]->Sumw2(); hDIDilHighPtMM[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtEE[i]   = (TH1D*)_file[i]->Get("hDDilHighPtEE"); hDIDilHighPtEE[i]->Sumw2(); hDIDilHighPtEE[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtNoEWKMM[i]   = (TH1D*)_file[i]->Get("hDDilHighPtNoEWKMM"); hDIDilHighPtNoEWKMM[i]->Sumw2(); hDIDilHighPtNoEWKMM[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtNoEWKEE[i]   = (TH1D*)_file[i]->Get("hDDilHighPtNoEWKEE"); hDIDilHighPtNoEWKEE[i]->Sumw2(); hDIDilHighPtNoEWKEE[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilRapMM[i]      = (TH1D*)_file[i]->Get("hDDilRapMM");    hDIDilRapMM[i]->Sumw2();    hDIDilRapMM[i]    ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIDilRapEE[i]      = (TH1D*)_file[i]->Get("hDDilRapEE");    hDIDilRapEE[i]->Sumw2();    hDIDilRapEE[i]    ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIDilPhiStarMM[i]  = (TH1D*)_file[i]->Get("hDDilPhiStarMM");hDIDilPhiStarMM[i]->Sumw2();hDIDilPhiStarMM[i]->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());	  
  hDIDilPhiStarEE[i]  = (TH1D*)_file[i]->Get("hDDilPhiStarEE");hDIDilPhiStarEE[i]->Sumw2();hDIDilPhiStarEE[i]->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());	  
  hDIDilPtRap0MM[i]   = (TH1D*)_file[i]->Get("hDDilPtRap0MM"); hDIDilPtRap0MM[i]->Sumw2(); hDIDilPtRap0MM[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap0EE[i]   = (TH1D*)_file[i]->Get("hDDilPtRap0EE"); hDIDilPtRap0EE[i]->Sumw2(); hDIDilPtRap0EE[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap1MM[i]   = (TH1D*)_file[i]->Get("hDDilPtRap1MM"); hDIDilPtRap1MM[i]->Sumw2(); hDIDilPtRap1MM[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap1EE[i]   = (TH1D*)_file[i]->Get("hDDilPtRap1EE"); hDIDilPtRap1EE[i]->Sumw2(); hDIDilPtRap1EE[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap2MM[i]   = (TH1D*)_file[i]->Get("hDDilPtRap2MM"); hDIDilPtRap2MM[i]->Sumw2(); hDIDilPtRap2MM[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap2EE[i]   = (TH1D*)_file[i]->Get("hDDilPtRap2EE"); hDIDilPtRap2EE[i]->Sumw2(); hDIDilPtRap2EE[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap3MM[i]   = (TH1D*)_file[i]->Get("hDDilPtRap3MM"); hDIDilPtRap3MM[i]->Sumw2(); hDIDilPtRap3MM[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap3EE[i]   = (TH1D*)_file[i]->Get("hDDilPtRap3EE"); hDIDilPtRap3EE[i]->Sumw2(); hDIDilPtRap3EE[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap4MM[i]   = (TH1D*)_file[i]->Get("hDDilPtRap4MM"); hDIDilPtRap4MM[i]->Sumw2(); hDIDilPtRap4MM[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap4EE[i]   = (TH1D*)_file[i]->Get("hDDilPtRap4EE"); hDIDilPtRap4EE[i]->Sumw2(); hDIDilPtRap4EE[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());

  hDIDilPtMM_PDF[i]       = (TH1D*)_file[i]->Get("hDDilPtMM_PDF");     hDIDilPtMM_PDF[i]     ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilPtEE_PDF[i]       = (TH1D*)_file[i]->Get("hDDilPtEE_PDF");     hDIDilPtEE_PDF[i]     ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtIncMM_PDF[i]   = (TH1D*)_file[i]->Get("hDDilHighPtIncMM_PDF"); hDIDilHighPtIncMM_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtIncEE_PDF[i]   = (TH1D*)_file[i]->Get("hDDilHighPtIncEE_PDF"); hDIDilHighPtIncEE_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtMM_PDF[i]   = (TH1D*)_file[i]->Get("hDDilHighPtMM_PDF"); hDIDilHighPtMM_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtEE_PDF[i]   = (TH1D*)_file[i]->Get("hDDilHighPtEE_PDF"); hDIDilHighPtEE_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilRapMM_PDF[i]      = (TH1D*)_file[i]->Get("hDDilRapMM_PDF");    hDIDilRapMM_PDF[i]    ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIDilRapEE_PDF[i]      = (TH1D*)_file[i]->Get("hDDilRapEE_PDF");    hDIDilRapEE_PDF[i]    ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIDilPhiStarMM_PDF[i]  = (TH1D*)_file[i]->Get("hDDilPhiStarMM_PDF");hDIDilPhiStarMM_PDF[i]->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());       
  hDIDilPhiStarEE_PDF[i]  = (TH1D*)_file[i]->Get("hDDilPhiStarEE_PDF");hDIDilPhiStarEE_PDF[i]->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());       
  hDIDilPtRap0MM_PDF[i]   = (TH1D*)_file[i]->Get("hDDilPtRap0MM_PDF"); hDIDilPtRap0MM_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap0EE_PDF[i]   = (TH1D*)_file[i]->Get("hDDilPtRap0EE_PDF"); hDIDilPtRap0EE_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap1MM_PDF[i]   = (TH1D*)_file[i]->Get("hDDilPtRap1MM_PDF"); hDIDilPtRap1MM_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap1EE_PDF[i]   = (TH1D*)_file[i]->Get("hDDilPtRap1EE_PDF"); hDIDilPtRap1EE_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap2MM_PDF[i]   = (TH1D*)_file[i]->Get("hDDilPtRap2MM_PDF"); hDIDilPtRap2MM_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap2EE_PDF[i]   = (TH1D*)_file[i]->Get("hDDilPtRap2EE_PDF"); hDIDilPtRap2EE_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap3MM_PDF[i]   = (TH1D*)_file[i]->Get("hDDilPtRap3MM_PDF"); hDIDilPtRap3MM_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap3EE_PDF[i]   = (TH1D*)_file[i]->Get("hDDilPtRap3EE_PDF"); hDIDilPtRap3EE_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap4MM_PDF[i]   = (TH1D*)_file[i]->Get("hDDilPtRap4MM_PDF"); hDIDilPtRap4MM_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap4EE_PDF[i]   = (TH1D*)_file[i]->Get("hDDilPtRap4EE_PDF"); hDIDilPtRap4EE_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());

  hDIDilPtMM_QCD[i]       = (TH1D*)_file[i]->Get("hDDilPtMM_QCD");     hDIDilPtMM_QCD[i]     ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilPtEE_QCD[i]       = (TH1D*)_file[i]->Get("hDDilPtEE_QCD");     hDIDilPtEE_QCD[i]     ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtIncMM_QCD[i]   = (TH1D*)_file[i]->Get("hDDilHighPtIncMM_QCD"); hDIDilHighPtIncMM_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtIncEE_QCD[i]   = (TH1D*)_file[i]->Get("hDDilHighPtIncEE_QCD"); hDIDilHighPtIncEE_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtMM_QCD[i]   = (TH1D*)_file[i]->Get("hDDilHighPtMM_QCD"); hDIDilHighPtMM_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtEE_QCD[i]   = (TH1D*)_file[i]->Get("hDDilHighPtEE_QCD"); hDIDilHighPtEE_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilRapMM_QCD[i]      = (TH1D*)_file[i]->Get("hDDilRapMM_QCD");    hDIDilRapMM_QCD[i]    ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIDilRapEE_QCD[i]      = (TH1D*)_file[i]->Get("hDDilRapEE_QCD");    hDIDilRapEE_QCD[i]    ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIDilPhiStarMM_QCD[i]  = (TH1D*)_file[i]->Get("hDDilPhiStarMM_QCD");hDIDilPhiStarMM_QCD[i]->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());       
  hDIDilPhiStarEE_QCD[i]  = (TH1D*)_file[i]->Get("hDDilPhiStarEE_QCD");hDIDilPhiStarEE_QCD[i]->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());       
  hDIDilPtRap0MM_QCD[i]   = (TH1D*)_file[i]->Get("hDDilPtRap0MM_QCD"); hDIDilPtRap0MM_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap0EE_QCD[i]   = (TH1D*)_file[i]->Get("hDDilPtRap0EE_QCD"); hDIDilPtRap0EE_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap1MM_QCD[i]   = (TH1D*)_file[i]->Get("hDDilPtRap1MM_QCD"); hDIDilPtRap1MM_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap1EE_QCD[i]   = (TH1D*)_file[i]->Get("hDDilPtRap1EE_QCD"); hDIDilPtRap1EE_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap2MM_QCD[i]   = (TH1D*)_file[i]->Get("hDDilPtRap2MM_QCD"); hDIDilPtRap2MM_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap2EE_QCD[i]   = (TH1D*)_file[i]->Get("hDDilPtRap2EE_QCD"); hDIDilPtRap2EE_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap3MM_QCD[i]   = (TH1D*)_file[i]->Get("hDDilPtRap3MM_QCD"); hDIDilPtRap3MM_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap3EE_QCD[i]   = (TH1D*)_file[i]->Get("hDDilPtRap3EE_QCD"); hDIDilPtRap3EE_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap4MM_QCD[i]   = (TH1D*)_file[i]->Get("hDDilPtRap4MM_QCD"); hDIDilPtRap4MM_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
  hDIDilPtRap4EE_QCD[i]   = (TH1D*)_file[i]->Get("hDDilPtRap4EE_QCD"); hDIDilPtRap4EE_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());
}

TH1D *hDDilPtMM      = (TH1D*)hDIDilPtMM     [0]->Clone();
TH1D *hDDilPtEE      = (TH1D*)hDIDilPtEE     [0]->Clone();
TH1D *hDDilHighPtIncMM  = (TH1D*)hDIDilHighPtIncMM [0]->Clone();
TH1D *hDDilHighPtIncEE  = (TH1D*)hDIDilHighPtIncEE [0]->Clone();
TH1D *hDDilHighPtMM  = (TH1D*)hDIDilHighPtMM [0]->Clone();
TH1D *hDDilHighPtEE  = (TH1D*)hDIDilHighPtEE [0]->Clone();
TH1D *hDDilHighPtNoEWKMM  = (TH1D*)hDIDilHighPtNoEWKMM [0]->Clone();
TH1D *hDDilHighPtNoEWKEE  = (TH1D*)hDIDilHighPtNoEWKEE [0]->Clone();
TH1D *hDDilRapMM     = (TH1D*)hDIDilRapMM    [0]->Clone();
TH1D *hDDilRapEE     = (TH1D*)hDIDilRapEE    [0]->Clone();
TH1D *hDDilPhiStarMM = (TH1D*)hDIDilPhiStarMM[0]->Clone();
TH1D *hDDilPhiStarEE = (TH1D*)hDIDilPhiStarEE[0]->Clone();
TH1D *hDDilPtRap0MM  = (TH1D*)hDIDilPtRap0MM [0]->Clone();
TH1D *hDDilPtRap0EE  = (TH1D*)hDIDilPtRap0EE [0]->Clone();
TH1D *hDDilPtRap1MM  = (TH1D*)hDIDilPtRap1MM [0]->Clone();
TH1D *hDDilPtRap1EE  = (TH1D*)hDIDilPtRap1EE [0]->Clone();
TH1D *hDDilPtRap2MM  = (TH1D*)hDIDilPtRap2MM [0]->Clone();
TH1D *hDDilPtRap2EE  = (TH1D*)hDIDilPtRap2EE [0]->Clone();
TH1D *hDDilPtRap3MM  = (TH1D*)hDIDilPtRap3MM [0]->Clone();
TH1D *hDDilPtRap3EE  = (TH1D*)hDIDilPtRap3EE [0]->Clone();
TH1D *hDDilPtRap4MM  = (TH1D*)hDIDilPtRap4MM [0]->Clone();
TH1D *hDDilPtRap4EE  = (TH1D*)hDIDilPtRap4EE [0]->Clone();

TH1D *hDDilPtMM_PDF      = (TH1D*)hDIDilPtMM_PDF     [0]->Clone();
TH1D *hDDilPtEE_PDF      = (TH1D*)hDIDilPtEE_PDF     [0]->Clone();
TH1D *hDDilHighPtIncMM_PDF  = (TH1D*)hDIDilHighPtIncMM_PDF [0]->Clone();
TH1D *hDDilHighPtIncEE_PDF  = (TH1D*)hDIDilHighPtIncEE_PDF [0]->Clone();
TH1D *hDDilHighPtMM_PDF  = (TH1D*)hDIDilHighPtMM_PDF [0]->Clone();
TH1D *hDDilHighPtEE_PDF  = (TH1D*)hDIDilHighPtEE_PDF [0]->Clone();
TH1D *hDDilRapMM_PDF     = (TH1D*)hDIDilRapMM_PDF    [0]->Clone();
TH1D *hDDilRapEE_PDF     = (TH1D*)hDIDilRapEE_PDF    [0]->Clone();
TH1D *hDDilPhiStarMM_PDF = (TH1D*)hDIDilPhiStarMM_PDF[0]->Clone();
TH1D *hDDilPhiStarEE_PDF = (TH1D*)hDIDilPhiStarEE_PDF[0]->Clone();
TH1D *hDDilPtRap0MM_PDF  = (TH1D*)hDIDilPtRap0MM_PDF [0]->Clone();
TH1D *hDDilPtRap0EE_PDF  = (TH1D*)hDIDilPtRap0EE_PDF [0]->Clone();
TH1D *hDDilPtRap1MM_PDF  = (TH1D*)hDIDilPtRap1MM_PDF [0]->Clone();
TH1D *hDDilPtRap1EE_PDF  = (TH1D*)hDIDilPtRap1EE_PDF [0]->Clone();
TH1D *hDDilPtRap2MM_PDF  = (TH1D*)hDIDilPtRap2MM_PDF [0]->Clone();
TH1D *hDDilPtRap2EE_PDF  = (TH1D*)hDIDilPtRap2EE_PDF [0]->Clone();
TH1D *hDDilPtRap3MM_PDF  = (TH1D*)hDIDilPtRap3MM_PDF [0]->Clone();
TH1D *hDDilPtRap3EE_PDF  = (TH1D*)hDIDilPtRap3EE_PDF [0]->Clone();
TH1D *hDDilPtRap4MM_PDF  = (TH1D*)hDIDilPtRap4MM_PDF [0]->Clone();
TH1D *hDDilPtRap4EE_PDF  = (TH1D*)hDIDilPtRap4EE_PDF [0]->Clone();

TH1D *hDDilPtMM_QCD      = (TH1D*)hDIDilPtMM_QCD     [0]->Clone();
TH1D *hDDilPtEE_QCD      = (TH1D*)hDIDilPtEE_QCD     [0]->Clone();
TH1D *hDDilHighPtIncMM_QCD  = (TH1D*)hDIDilHighPtIncMM_QCD [0]->Clone();
TH1D *hDDilHighPtIncEE_QCD  = (TH1D*)hDIDilHighPtIncEE_QCD [0]->Clone();
TH1D *hDDilHighPtMM_QCD  = (TH1D*)hDIDilHighPtMM_QCD [0]->Clone();
TH1D *hDDilHighPtEE_QCD  = (TH1D*)hDIDilHighPtEE_QCD [0]->Clone();
TH1D *hDDilRapMM_QCD     = (TH1D*)hDIDilRapMM_QCD    [0]->Clone();
TH1D *hDDilRapEE_QCD     = (TH1D*)hDIDilRapEE_QCD    [0]->Clone();
TH1D *hDDilPhiStarMM_QCD = (TH1D*)hDIDilPhiStarMM_QCD[0]->Clone();
TH1D *hDDilPhiStarEE_QCD = (TH1D*)hDIDilPhiStarEE_QCD[0]->Clone();
TH1D *hDDilPtRap0MM_QCD  = (TH1D*)hDIDilPtRap0MM_QCD [0]->Clone();
TH1D *hDDilPtRap0EE_QCD  = (TH1D*)hDIDilPtRap0EE_QCD [0]->Clone();
TH1D *hDDilPtRap1MM_QCD  = (TH1D*)hDIDilPtRap1MM_QCD [0]->Clone();
TH1D *hDDilPtRap1EE_QCD  = (TH1D*)hDIDilPtRap1EE_QCD [0]->Clone();
TH1D *hDDilPtRap2MM_QCD  = (TH1D*)hDIDilPtRap2MM_QCD [0]->Clone();
TH1D *hDDilPtRap2EE_QCD  = (TH1D*)hDIDilPtRap2EE_QCD [0]->Clone();
TH1D *hDDilPtRap3MM_QCD  = (TH1D*)hDIDilPtRap3MM_QCD [0]->Clone();
TH1D *hDDilPtRap3EE_QCD  = (TH1D*)hDIDilPtRap3EE_QCD [0]->Clone();
TH1D *hDDilPtRap4MM_QCD  = (TH1D*)hDIDilPtRap4MM_QCD [0]->Clone();
TH1D *hDDilPtRap4EE_QCD  = (TH1D*)hDIDilPtRap4EE_QCD [0]->Clone();

for(int i=1; i<nFiles; i++){
  hDDilPtMM	->Add(hDIDilPtMM     [i]);   
  hDDilPtEE	->Add(hDIDilPtEE     [i]);   
  hDDilHighPtIncMM	->Add(hDIDilHighPtIncMM [i]);   
  hDDilHighPtIncEE	->Add(hDIDilHighPtIncEE [i]);   
  hDDilHighPtMM	->Add(hDIDilHighPtMM [i]);   
  hDDilHighPtEE	->Add(hDIDilHighPtEE [i]);   
  hDDilHighPtNoEWKMM	->Add(hDIDilHighPtNoEWKMM [i]);   
  hDDilHighPtNoEWKEE	->Add(hDIDilHighPtNoEWKEE [i]);   
  hDDilRapMM	->Add(hDIDilRapMM    [i]);  
  hDDilRapEE	->Add(hDIDilRapEE    [i]);  
  hDDilPhiStarMM->Add(hDIDilPhiStarMM[i]);  
  hDDilPhiStarEE->Add(hDIDilPhiStarEE[i]);  
  hDDilPtRap0MM ->Add(hDIDilPtRap0MM [i]);  
  hDDilPtRap0EE ->Add(hDIDilPtRap0EE [i]);  
  hDDilPtRap1MM ->Add(hDIDilPtRap1MM [i]);
  hDDilPtRap1EE ->Add(hDIDilPtRap1EE [i]);
  hDDilPtRap2MM ->Add(hDIDilPtRap2MM [i]);
  hDDilPtRap2EE ->Add(hDIDilPtRap2EE [i]);
  hDDilPtRap3MM ->Add(hDIDilPtRap3MM [i]);
  hDDilPtRap3EE ->Add(hDIDilPtRap3EE [i]);
  hDDilPtRap4MM ->Add(hDIDilPtRap4MM [i]);
  hDDilPtRap4EE ->Add(hDIDilPtRap4EE [i]);

  hDDilPtMM_PDF     ->Add(hDIDilPtMM_PDF     [i]);   
  hDDilPtEE_PDF     ->Add(hDIDilPtEE_PDF     [i]);   
  hDDilHighPtIncMM_PDF ->Add(hDIDilHighPtIncMM_PDF [i]);   
  hDDilHighPtIncEE_PDF ->Add(hDIDilHighPtIncEE_PDF [i]);   
  hDDilHighPtMM_PDF ->Add(hDIDilHighPtMM_PDF [i]);   
  hDDilHighPtEE_PDF ->Add(hDIDilHighPtEE_PDF [i]);   
  hDDilRapMM_PDF    ->Add(hDIDilRapMM_PDF    [i]);  
  hDDilRapEE_PDF    ->Add(hDIDilRapEE_PDF    [i]);  
  hDDilPhiStarMM_PDF->Add(hDIDilPhiStarMM_PDF[i]);  
  hDDilPhiStarEE_PDF->Add(hDIDilPhiStarEE_PDF[i]);  
  hDDilPtRap0MM_PDF ->Add(hDIDilPtRap0MM_PDF [i]);  
  hDDilPtRap0EE_PDF ->Add(hDIDilPtRap0EE_PDF [i]);  
  hDDilPtRap1MM_PDF ->Add(hDIDilPtRap1MM_PDF [i]);
  hDDilPtRap1EE_PDF ->Add(hDIDilPtRap1EE_PDF [i]);
  hDDilPtRap2MM_PDF ->Add(hDIDilPtRap2MM_PDF [i]);
  hDDilPtRap2EE_PDF ->Add(hDIDilPtRap2EE_PDF [i]);
  hDDilPtRap3MM_PDF ->Add(hDIDilPtRap3MM_PDF [i]);
  hDDilPtRap3EE_PDF ->Add(hDIDilPtRap3EE_PDF [i]);
  hDDilPtRap4MM_PDF ->Add(hDIDilPtRap4MM_PDF [i]);
  hDDilPtRap4EE_PDF ->Add(hDIDilPtRap4EE_PDF [i]);

  hDDilPtMM_QCD     ->Add(hDIDilPtMM_QCD     [i]);   
  hDDilPtEE_QCD     ->Add(hDIDilPtEE_QCD     [i]);   
  hDDilHighPtIncMM_QCD ->Add(hDIDilHighPtIncMM_QCD [i]);   
  hDDilHighPtIncEE_QCD ->Add(hDIDilHighPtIncEE_QCD [i]);   
  hDDilHighPtMM_QCD ->Add(hDIDilHighPtMM_QCD [i]);   
  hDDilHighPtEE_QCD ->Add(hDIDilHighPtEE_QCD [i]);   
  hDDilRapMM_QCD    ->Add(hDIDilRapMM_QCD    [i]);  
  hDDilRapEE_QCD    ->Add(hDIDilRapEE_QCD    [i]);  
  hDDilPhiStarMM_QCD->Add(hDIDilPhiStarMM_QCD[i]);  
  hDDilPhiStarEE_QCD->Add(hDIDilPhiStarEE_QCD[i]);  
  hDDilPtRap0MM_QCD ->Add(hDIDilPtRap0MM_QCD [i]);  
  hDDilPtRap0EE_QCD ->Add(hDIDilPtRap0EE_QCD [i]);  
  hDDilPtRap1MM_QCD ->Add(hDIDilPtRap1MM_QCD [i]);
  hDDilPtRap1EE_QCD ->Add(hDIDilPtRap1EE_QCD [i]);
  hDDilPtRap2MM_QCD ->Add(hDIDilPtRap2MM_QCD [i]);
  hDDilPtRap2EE_QCD ->Add(hDIDilPtRap2EE_QCD [i]);
  hDDilPtRap3MM_QCD ->Add(hDIDilPtRap3MM_QCD [i]);
  hDDilPtRap3EE_QCD ->Add(hDIDilPtRap3EE_QCD [i]);
  hDDilPtRap4MM_QCD ->Add(hDIDilPtRap4MM_QCD [i]);
  hDDilPtRap4EE_QCD ->Add(hDIDilPtRap4EE_QCD [i]);
}

TFile myOutputFile("genZpt_LO.root","RECREATE");
  hDDilPtMM	->Write(); 
  hDDilPtEE	->Write(); 
  hDDilHighPtIncMM	->Write(); 
  hDDilHighPtIncEE	->Write(); 
  hDDilHighPtMM	->Write(); 
  hDDilHighPtEE	->Write(); 
  hDDilHighPtNoEWKMM	->Write(); 
  hDDilHighPtNoEWKEE	->Write(); 
  hDDilRapMM	->Write();
  hDDilRapEE	->Write();
  hDDilPhiStarMM->Write();
  hDDilPhiStarEE->Write();
  hDDilPtRap0MM ->Write();
  hDDilPtRap0EE ->Write();
  hDDilPtRap1MM ->Write();
  hDDilPtRap1EE ->Write();
  hDDilPtRap2MM ->Write();
  hDDilPtRap2EE ->Write();
  hDDilPtRap3MM ->Write();
  hDDilPtRap3EE ->Write();
  hDDilPtRap4MM ->Write();
  hDDilPtRap4EE ->Write();

  hDDilPtMM_PDF     ->Write(); 
  hDDilPtEE_PDF     ->Write(); 
  hDDilHighPtIncMM_PDF ->Write(); 
  hDDilHighPtIncEE_PDF ->Write(); 
  hDDilHighPtMM_PDF ->Write(); 
  hDDilHighPtEE_PDF ->Write(); 
  hDDilRapMM_PDF    ->Write();
  hDDilRapEE_PDF    ->Write();
  hDDilPhiStarMM_PDF->Write();
  hDDilPhiStarEE_PDF->Write();
  hDDilPtRap0MM_PDF ->Write();
  hDDilPtRap0EE_PDF ->Write();
  hDDilPtRap1MM_PDF ->Write();
  hDDilPtRap1EE_PDF ->Write();
  hDDilPtRap2MM_PDF ->Write();
  hDDilPtRap2EE_PDF ->Write();
  hDDilPtRap3MM_PDF ->Write();
  hDDilPtRap3EE_PDF ->Write();
  hDDilPtRap4MM_PDF ->Write();
  hDDilPtRap4EE_PDF ->Write();

  hDDilPtMM_QCD     ->Write(); 
  hDDilPtEE_QCD     ->Write(); 
  hDDilHighPtIncMM_QCD ->Write(); 
  hDDilHighPtIncEE_QCD ->Write(); 
  hDDilHighPtMM_QCD ->Write(); 
  hDDilHighPtEE_QCD ->Write(); 
  hDDilRapMM_QCD    ->Write();
  hDDilRapEE_QCD    ->Write();
  hDDilPhiStarMM_QCD->Write();
  hDDilPhiStarEE_QCD->Write();
  hDDilPtRap0MM_QCD ->Write();
  hDDilPtRap0EE_QCD ->Write();
  hDDilPtRap1MM_QCD ->Write();
  hDDilPtRap1EE_QCD ->Write();
  hDDilPtRap2MM_QCD ->Write();
  hDDilPtRap2EE_QCD ->Write();
  hDDilPtRap3MM_QCD ->Write();
  hDDilPtRap3EE_QCD ->Write();
  hDDilPtRap4MM_QCD ->Write();
  hDDilPtRap4EE_QCD ->Write();
myOutputFile.Close();
}
else if(nsel == 2){ // WW
const int nFiles = 2;
TFile *_file[nFiles];
_file[0] = TFile::Open(Form("%s/qqWW.root", inputFolder.Data()));
_file[1] = TFile::Open(Form("%s/ggWW.root", inputFolder.Data()));

double xs[nFiles] = {(118.7-3.974)*0.1086*0.1086*9*1.035,3.974*0.1086*0.1086*9*1.4};

TH1D *hDITotalMCWeight[nFiles];

TH1D *hDIWWMLL[nFiles];       TH1D *hDIWWMLL_PDF[nFiles];        TH1D *hDIWWMLL_QCD[nFiles];	 
TH1D *hDIWWDPHILL[nFiles];    TH1D *hDIWWDPHILL_PDF[nFiles];     TH1D *hDIWWDPHILL_QCD[nFiles];   
TH1D *hDIWWPTL1[nFiles];      TH1D *hDIWWPTL1_PDF[nFiles];       TH1D *hDIWWPTL1_QCD[nFiles];	 
TH1D *hDIWWPTL2[nFiles];      TH1D *hDIWWPTL2_PDF[nFiles];       TH1D *hDIWWPTL2_QCD[nFiles];   
TH1D *hDIWWPTLL[nFiles];      TH1D *hDIWWPTLL_PDF[nFiles];       TH1D *hDIWWPTLL_QCD[nFiles];   
TH1D *hDIWWMLL0JET[nFiles];   TH1D *hDIWWMLL0JET_PDF[nFiles];	 TH1D *hDIWWMLL0JET_QCD[nFiles];       
TH1D *hDIWWDPHILL0JET[nFiles];TH1D *hDIWWDPHILL0JET_PDF[nFiles]; TH1D *hDIWWDPHILL0JET_QCD[nFiles];   
TH1D *hDIWWPTL10JET[nFiles];  TH1D *hDIWWPTL10JET_PDF[nFiles];   TH1D *hDIWWPTL10JET_QCD[nFiles];      
TH1D *hDIWWPTL20JET[nFiles];  TH1D *hDIWWPTL20JET_PDF[nFiles];   TH1D *hDIWWPTL20JET_QCD[nFiles];   
TH1D *hDIWWPTLL0JET[nFiles];  TH1D *hDIWWPTLL0JET_PDF[nFiles];   TH1D *hDIWWPTLL0JET_QCD[nFiles];   
TH1D *hDIWWN0JET[nFiles];     TH1D *hDIWWN0JET_PDF[nFiles];      TH1D *hDIWWN0JET_QCD[nFiles];   
TH1D *hDIWWNJET[nFiles];      TH1D *hDIWWNJET_PDF[nFiles];       TH1D *hDIWWNJET_QCD[nFiles];   

for(int i=0; i<nFiles; i++){
  hDITotalMCWeight[i] = (TH1D*)_file[i]->Get("hDTotalMCWeight");	 

  hDIWWMLL[i]       = (TH1D*)_file[i]->Get("hDWWMLL");        hDIWWMLL[i]->Sumw2();        hDIWWMLL[i]       ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIWWDPHILL[i]    = (TH1D*)_file[i]->Get("hDWWDPHILL");     hDIWWDPHILL[i]->Sumw2();     hDIWWDPHILL[i]    ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIWWPTL1[i]      = (TH1D*)_file[i]->Get("hDWWPTL1");       hDIWWPTL1[i]->Sumw2();       hDIWWPTL1[i]      ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIWWPTL2[i]      = (TH1D*)_file[i]->Get("hDWWPTL2");       hDIWWPTL2[i]->Sumw2();       hDIWWPTL2[i]      ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIWWPTLL[i]      = (TH1D*)_file[i]->Get("hDWWPTLL");       hDIWWPTLL[i]->Sumw2();       hDIWWPTLL[i]      ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIWWMLL0JET[i]   = (TH1D*)_file[i]->Get("hDWWMLL0JET");    hDIWWMLL0JET[i]->Sumw2();    hDIWWMLL0JET[i]   ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIWWDPHILL0JET[i]= (TH1D*)_file[i]->Get("hDWWDPHILL0JET"); hDIWWDPHILL0JET[i]->Sumw2(); hDIWWDPHILL0JET[i]->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIWWPTL10JET[i]  = (TH1D*)_file[i]->Get("hDWWPTL10JET");   hDIWWPTL10JET[i]->Sumw2();   hDIWWPTL10JET[i]  ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIWWPTL20JET[i]  = (TH1D*)_file[i]->Get("hDWWPTL20JET");   hDIWWPTL20JET[i]->Sumw2();   hDIWWPTL20JET[i]  ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIWWPTLL0JET[i]  = (TH1D*)_file[i]->Get("hDWWPTLL0JET");   hDIWWPTLL0JET[i]->Sumw2();   hDIWWPTLL0JET[i]  ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIWWN0JET[i]     = (TH1D*)_file[i]->Get("hDWWN0JET");      hDIWWN0JET[i]->Sumw2();      hDIWWN0JET[i]     ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIWWNJET[i]      = (TH1D*)_file[i]->Get("hDWWNJET");       hDIWWNJET[i]->Sumw2();       hDIWWNJET[i]      ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 

  hDIWWMLL_PDF[i]       = (TH1D*)_file[i]->Get("hDWWMLL_PDF");        hDIWWMLL_PDF[i]       ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIWWDPHILL_PDF[i]    = (TH1D*)_file[i]->Get("hDWWDPHILL_PDF");     hDIWWDPHILL_PDF[i]    ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIWWPTL1_PDF[i]      = (TH1D*)_file[i]->Get("hDWWPTL1_PDF");       hDIWWPTL1_PDF[i]      ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIWWPTL2_PDF[i]      = (TH1D*)_file[i]->Get("hDWWPTL2_PDF");       hDIWWPTL2_PDF[i]      ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIWWPTLL_PDF[i]      = (TH1D*)_file[i]->Get("hDWWPTLL_PDF");       hDIWWPTLL_PDF[i]      ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIWWMLL0JET_PDF[i]   = (TH1D*)_file[i]->Get("hDWWMLL0JET_PDF");    hDIWWMLL0JET_PDF[i]   ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIWWDPHILL0JET_PDF[i]= (TH1D*)_file[i]->Get("hDWWDPHILL0JET_PDF"); hDIWWDPHILL0JET_PDF[i]->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIWWPTL10JET_PDF[i]  = (TH1D*)_file[i]->Get("hDWWPTL10JET_PDF");   hDIWWPTL10JET_PDF[i]  ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIWWPTL20JET_PDF[i]  = (TH1D*)_file[i]->Get("hDWWPTL20JET_PDF");   hDIWWPTL20JET_PDF[i]  ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIWWPTLL0JET_PDF[i]  = (TH1D*)_file[i]->Get("hDWWPTLL0JET_PDF");   hDIWWPTLL0JET_PDF[i]  ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIWWN0JET_PDF[i]     = (TH1D*)_file[i]->Get("hDWWN0JET_PDF");      hDIWWN0JET_PDF[i]     ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIWWNJET_PDF[i]      = (TH1D*)_file[i]->Get("hDWWNJET_PDF");       hDIWWNJET_PDF[i]      ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 

  hDIWWMLL_QCD[i]       = (TH1D*)_file[i]->Get("hDWWMLL_QCD");        hDIWWMLL_QCD[i]       ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIWWDPHILL_QCD[i]    = (TH1D*)_file[i]->Get("hDWWDPHILL_QCD");     hDIWWDPHILL_QCD[i]    ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIWWPTL1_QCD[i]      = (TH1D*)_file[i]->Get("hDWWPTL1_QCD");       hDIWWPTL1_QCD[i]      ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIWWPTL2_QCD[i]      = (TH1D*)_file[i]->Get("hDWWPTL2_QCD");       hDIWWPTL2_QCD[i]      ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIWWPTLL_QCD[i]      = (TH1D*)_file[i]->Get("hDWWPTLL_QCD");       hDIWWPTLL_QCD[i]      ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIWWMLL0JET_QCD[i]   = (TH1D*)_file[i]->Get("hDWWMLL0JET_QCD");    hDIWWMLL0JET_QCD[i]   ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIWWDPHILL0JET_QCD[i]= (TH1D*)_file[i]->Get("hDWWDPHILL0JET_QCD"); hDIWWDPHILL0JET_QCD[i]->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIWWPTL10JET_QCD[i]  = (TH1D*)_file[i]->Get("hDWWPTL10JET_QCD");   hDIWWPTL10JET_QCD[i]  ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIWWPTL20JET_QCD[i]  = (TH1D*)_file[i]->Get("hDWWPTL20JET_QCD");   hDIWWPTL20JET_QCD[i]  ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIWWPTLL0JET_QCD[i]  = (TH1D*)_file[i]->Get("hDWWPTLL0JET_QCD");   hDIWWPTLL0JET_QCD[i]  ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIWWN0JET_QCD[i]     = (TH1D*)_file[i]->Get("hDWWN0JET_QCD");      hDIWWN0JET_QCD[i]     ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
  hDIWWNJET_QCD[i]      = (TH1D*)_file[i]->Get("hDWWNJET_QCD");       hDIWWNJET_QCD[i]      ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights()); 
}

TH1D *hDWWMLL          = (TH1D*)hDIWWMLL       [0]->Clone();
TH1D *hDWWDPHILL       = (TH1D*)hDIWWDPHILL    [0]->Clone();
TH1D *hDWWPTL1         = (TH1D*)hDIWWPTL1      [0]->Clone();
TH1D *hDWWPTL2         = (TH1D*)hDIWWPTL2      [0]->Clone();
TH1D *hDWWPTLL         = (TH1D*)hDIWWPTLL      [0]->Clone();
TH1D *hDWWMLL0JET      = (TH1D*)hDIWWMLL0JET   [0]->Clone();
TH1D *hDWWDPHILL0JET   = (TH1D*)hDIWWDPHILL0JET[0]->Clone();
TH1D *hDWWPTL10JET     = (TH1D*)hDIWWPTL10JET  [0]->Clone();
TH1D *hDWWPTL20JET     = (TH1D*)hDIWWPTL20JET  [0]->Clone();
TH1D *hDWWPTLL0JET     = (TH1D*)hDIWWPTLL0JET  [0]->Clone();
TH1D *hDWWN0JET        = (TH1D*)hDIWWN0JET     [0]->Clone();
TH1D *hDWWNJET         = (TH1D*)hDIWWNJET      [0]->Clone();

TH1D *hDWWMLL_PDF          = (TH1D*)hDIWWMLL_PDF       [0]->Clone();
TH1D *hDWWDPHILL_PDF       = (TH1D*)hDIWWDPHILL_PDF    [0]->Clone();
TH1D *hDWWPTL1_PDF         = (TH1D*)hDIWWPTL1_PDF      [0]->Clone();
TH1D *hDWWPTL2_PDF         = (TH1D*)hDIWWPTL2_PDF      [0]->Clone();
TH1D *hDWWPTLL_PDF         = (TH1D*)hDIWWPTLL_PDF      [0]->Clone();
TH1D *hDWWMLL0JET_PDF      = (TH1D*)hDIWWMLL0JET_PDF   [0]->Clone();
TH1D *hDWWDPHILL0JET_PDF   = (TH1D*)hDIWWDPHILL0JET_PDF[0]->Clone();
TH1D *hDWWPTL10JET_PDF     = (TH1D*)hDIWWPTL10JET_PDF  [0]->Clone();
TH1D *hDWWPTL20JET_PDF     = (TH1D*)hDIWWPTL20JET_PDF  [0]->Clone();
TH1D *hDWWPTLL0JET_PDF     = (TH1D*)hDIWWPTLL0JET_PDF  [0]->Clone();
TH1D *hDWWN0JET_PDF        = (TH1D*)hDIWWN0JET_PDF     [0]->Clone();
TH1D *hDWWNJET_PDF         = (TH1D*)hDIWWNJET_PDF      [0]->Clone();

TH1D *hDWWMLL_QCD          = (TH1D*)hDIWWMLL_QCD       [0]->Clone();
TH1D *hDWWDPHILL_QCD       = (TH1D*)hDIWWDPHILL_QCD    [0]->Clone();
TH1D *hDWWPTL1_QCD         = (TH1D*)hDIWWPTL1_QCD      [0]->Clone();
TH1D *hDWWPTL2_QCD         = (TH1D*)hDIWWPTL2_QCD      [0]->Clone();
TH1D *hDWWPTLL_QCD         = (TH1D*)hDIWWPTLL_QCD      [0]->Clone();
TH1D *hDWWMLL0JET_QCD      = (TH1D*)hDIWWMLL0JET_QCD   [0]->Clone();
TH1D *hDWWDPHILL0JET_QCD   = (TH1D*)hDIWWDPHILL0JET_QCD[0]->Clone();
TH1D *hDWWPTL10JET_QCD     = (TH1D*)hDIWWPTL10JET_QCD  [0]->Clone();
TH1D *hDWWPTL20JET_QCD     = (TH1D*)hDIWWPTL20JET_QCD  [0]->Clone();
TH1D *hDWWPTLL0JET_QCD     = (TH1D*)hDIWWPTLL0JET_QCD  [0]->Clone();
TH1D *hDWWN0JET_QCD        = (TH1D*)hDIWWN0JET_QCD     [0]->Clone();
TH1D *hDWWNJET_QCD         = (TH1D*)hDIWWNJET_QCD      [0]->Clone();

for(int i=1; i<nFiles; i++){
  hDWWMLL   	->Add(hDIWWMLL	     [i]);   
  hDWWDPHILL	->Add(hDIWWDPHILL    [i]);  
  hDWWPTL1   	->Add(hDIWWPTL1	     [i]);   
  hDWWPTL2  	->Add(hDIWWPTL2      [i]);  
  hDWWPTLL  	->Add(hDIWWPTLL      [i]);  
  hDWWMLL0JET   ->Add(hDIWWMLL0JET   [i]);   
  hDWWDPHILL0JET->Add(hDIWWDPHILL0JET[i]);  
  hDWWPTL10JET  ->Add(hDIWWPTL10JET  [i]);   
  hDWWPTL20JET  ->Add(hDIWWPTL20JET  [i]);  
  hDWWPTLL0JET  ->Add(hDIWWPTLL0JET  [i]);  
  hDWWN0JET	->Add(hDIWWN0JET     [i]);  
  hDWWNJET	->Add(hDIWWNJET      [i]);  

  hDWWMLL_PDF       ->Add(hDIWWMLL_PDF       [i]);   
  hDWWDPHILL_PDF    ->Add(hDIWWDPHILL_PDF    [i]);  
  hDWWPTL1_PDF      ->Add(hDIWWPTL1_PDF      [i]);   
  hDWWPTL2_PDF      ->Add(hDIWWPTL2_PDF      [i]);  
  hDWWPTLL_PDF      ->Add(hDIWWPTLL_PDF      [i]);  
  hDWWMLL0JET_PDF   ->Add(hDIWWMLL0JET_PDF   [i]);   
  hDWWDPHILL0JET_PDF->Add(hDIWWDPHILL0JET_PDF[i]);  
  hDWWPTL10JET_PDF  ->Add(hDIWWPTL10JET_PDF  [i]);   
  hDWWPTL20JET_PDF  ->Add(hDIWWPTL20JET_PDF  [i]);  
  hDWWPTLL0JET_PDF  ->Add(hDIWWPTLL0JET_PDF  [i]);  
  hDWWN0JET_PDF	    ->Add(hDIWWN0JET_PDF     [i]);  
  hDWWNJET_PDF	    ->Add(hDIWWNJET_PDF      [i]);  

  hDWWMLL_QCD       ->Add(hDIWWMLL_QCD       [i]);   
  hDWWDPHILL_QCD    ->Add(hDIWWDPHILL_QCD    [i]);  
  hDWWPTL1_QCD      ->Add(hDIWWPTL1_QCD      [i]);   
  hDWWPTL2_QCD      ->Add(hDIWWPTL2_QCD      [i]);  
  hDWWPTLL_QCD      ->Add(hDIWWPTLL_QCD      [i]);  
  hDWWMLL0JET_QCD   ->Add(hDIWWMLL0JET_QCD   [i]);   
  hDWWDPHILL0JET_QCD->Add(hDIWWDPHILL0JET_QCD[i]);  
  hDWWPTL10JET_QCD  ->Add(hDIWWPTL10JET_QCD  [i]);   
  hDWWPTL20JET_QCD  ->Add(hDIWWPTL20JET_QCD  [i]);  
  hDWWPTLL0JET_QCD  ->Add(hDIWWPTLL0JET_QCD  [i]);  
  hDWWN0JET_QCD	    ->Add(hDIWWN0JET_QCD     [i]);  
  hDWWNJET_QCD	    ->Add(hDIWWNJET_QCD      [i]);  
}

TFile myOutputFile("genWW.root","RECREATE");
  hDWWMLL	->Write(); 
  hDWWDPHILL	->Write(); 
  hDWWPTL1	->Write();
  hDWWPTL2	->Write();
  hDWWPTLL	->Write();
  hDWWMLL0JET	->Write(); 
  hDWWDPHILL0JET->Write(); 
  hDWWPTL10JET  ->Write();
  hDWWPTL20JET  ->Write();
  hDWWPTLL0JET  ->Write();
  hDWWN0JET	->Write(); 
  hDWWNJET	->Write(); 

  hDWWMLL_PDF	    ->Write(); 
  hDWWDPHILL_PDF    ->Write(); 
  hDWWPTL1_PDF      ->Write();
  hDWWPTL2_PDF      ->Write();
  hDWWPTLL_PDF      ->Write();
  hDWWMLL0JET_PDF   ->Write(); 
  hDWWDPHILL0JET_PDF->Write(); 
  hDWWPTL10JET_PDF  ->Write();
  hDWWPTL20JET_PDF  ->Write();
  hDWWPTLL0JET_PDF  ->Write();
  hDWWN0JET_PDF     ->Write(); 
  hDWWNJET_PDF      ->Write(); 

  hDWWMLL_QCD	    ->Write();
  hDWWDPHILL_QCD    ->Write();
  hDWWPTL1_QCD      ->Write(); 
  hDWWPTL2_QCD      ->Write(); 
  hDWWPTLL_QCD      ->Write();
  hDWWMLL0JET_QCD   ->Write();
  hDWWDPHILL0JET_QCD->Write();
  hDWWPTL10JET_QCD  ->Write(); 
  hDWWPTL20JET_QCD  ->Write(); 
  hDWWPTLL0JET_QCD  ->Write();
  hDWWN0JET_QCD     ->Write();
  hDWWNJET_QCD      ->Write();
myOutputFile.Close();
}
else if(nsel == 3){ // Znunu
const int nFiles = 4;
TFile *_file[nFiles];
_file[0] = TFile::Open(Form("%s/ZtoNuNu_pt100to250.root",inputFolder.Data()));
_file[1] = TFile::Open(Form("%s/ZtoNuNu_pt250to400.root",inputFolder.Data()));
_file[2] = TFile::Open(Form("%s/ZtoNuNu_pt400to650.root",inputFolder.Data()));
_file[3] = TFile::Open(Form("%s/ZtoNuNu_pt650toinf.root",inputFolder.Data()));

double xs[nFiles] = {3*54.8229*2075.14/2008.4,
                      3*2.0705*2075.14/2008.4,
		      3*0.2779*2075.14/2008.4,
		      3*0.0261*2075.14/2008.4};

TH1D *hDITotalMCWeight[nFiles];

TH1D *hDIDilHighPtNN[nFiles]; TH1D *hDIDilHighPtNN_PDF[nFiles];	TH1D *hDIDilHighPtNN_QCD[nFiles];	 
TH1D *hDIDilHighPtNoEWKNN[nFiles];	 

for(int i=0; i<nFiles; i++){
  hDITotalMCWeight[i] = (TH1D*)_file[i]->Get("hDTotalMCWeight");	 

  hDIDilHighPtNN[i]   = (TH1D*)_file[i]->Get("hDDilHighPtNN"); hDIDilHighPtNN[i]->Sumw2(); hDIDilHighPtNN[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
  hDIDilHighPtNoEWKNN[i]   = (TH1D*)_file[i]->Get("hDDilHighPtNoEWKNN"); hDIDilHighPtNoEWKNN[i]->Sumw2(); hDIDilHighPtNoEWKNN[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  

  hDIDilHighPtNN_PDF[i]   = (TH1D*)_file[i]->Get("hDDilHighPtNN_PDF"); hDIDilHighPtNN_PDF[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  

  hDIDilHighPtNN_QCD[i]   = (TH1D*)_file[i]->Get("hDDilHighPtNN_QCD"); hDIDilHighPtNN_QCD[i] ->Scale(xs[i]/hDITotalMCWeight[i]->GetSumOfWeights());  
}

TH1D *hDDilHighPtNN  = (TH1D*)hDIDilHighPtNN [0]->Clone();
TH1D *hDDilHighPtNoEWKNN  = (TH1D*)hDIDilHighPtNoEWKNN [0]->Clone();

TH1D *hDDilHighPtNN_PDF  = (TH1D*)hDIDilHighPtNN_PDF [0]->Clone();

TH1D *hDDilHighPtNN_QCD  = (TH1D*)hDIDilHighPtNN_QCD [0]->Clone();

for(int i=1; i<nFiles; i++){
  hDDilHighPtNN	->Add(hDIDilHighPtNN [i]);   
  hDDilHighPtNoEWKNN	->Add(hDIDilHighPtNoEWKNN [i]);   

  hDDilHighPtNN_PDF ->Add(hDIDilHighPtNN_PDF [i]);   

  hDDilHighPtNN_QCD ->Add(hDIDilHighPtNN_QCD [i]);   
}

TFile myOutputFile("genZNuNupt_NLO.root","RECREATE");
  hDDilHighPtNN	->Write(); 
 hDDilHighPtNoEWKNN	->Write(); 

  hDDilHighPtNN_PDF ->Write(); 

  hDDilHighPtNN_QCD ->Write(); 
myOutputFile.Close();

} 
}
