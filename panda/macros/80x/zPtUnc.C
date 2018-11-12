void zPtUnc(TString input = "/data/t3home000/ceballos/panda/v_001_0/genZpt_NLO.root", int ana = 0){

TFile *_file = TFile::Open(input.Data());

if(ana == 0){  // ZLL analysis
  TH1D *hDIDilPtMM;       TH1D *hDIDilPtMM_PDF;       TH1D *hDIDilPtMM_QCD;    
  TH1D *hDIDilPtEE;       TH1D *hDIDilPtEE_PDF;       TH1D *hDIDilPtEE_QCD;    
  TH1D *hDIDilHighPtIncMM;TH1D *hDIDilHighPtIncMM_PDF;TH1D *hDIDilHighPtIncMM_QCD;   
  TH1D *hDIDilHighPtIncEE;TH1D *hDIDilHighPtIncEE_PDF;TH1D *hDIDilHighPtIncEE_QCD;   
  TH1D *hDIDilHighPtMM;   TH1D *hDIDilHighPtMM_PDF;   TH1D *hDIDilHighPtMM_QCD;    
  TH1D *hDIDilHighPtEE;   TH1D *hDIDilHighPtEE_PDF;   TH1D *hDIDilHighPtEE_QCD;    

  hDIDilPtMM       = (TH1D*)_file->Get("hDDilPtMM");     
  hDIDilPtEE       = (TH1D*)_file->Get("hDDilPtEE");     
  hDIDilHighPtIncMM= (TH1D*)_file->Get("hDDilHighPtIncMM");
  hDIDilHighPtIncEE= (TH1D*)_file->Get("hDDilHighPtIncEE");
  hDIDilHighPtMM   = (TH1D*)_file->Get("hDDilHighPtMM");
  hDIDilHighPtEE   = (TH1D*)_file->Get("hDDilHighPtEE");

  hDIDilPtMM_PDF       = (TH1D*)_file->Get("hDDilPtMM_PDF");
  hDIDilPtEE_PDF       = (TH1D*)_file->Get("hDDilPtEE_PDF");
  hDIDilHighPtIncMM_PDF= (TH1D*)_file->Get("hDDilHighPtIncMM_PDF");
  hDIDilHighPtIncEE_PDF= (TH1D*)_file->Get("hDDilHighPtIncEE_PDF");
  hDIDilHighPtMM_PDF   = (TH1D*)_file->Get("hDDilHighPtMM_PDF");
  hDIDilHighPtEE_PDF   = (TH1D*)_file->Get("hDDilHighPtEE_PDF");

  hDIDilPtMM_QCD       = (TH1D*)_file->Get("hDDilPtMM_QCD");
  hDIDilPtEE_QCD       = (TH1D*)_file->Get("hDDilPtEE_QCD");
  hDIDilHighPtIncMM_QCD= (TH1D*)_file->Get("hDDilHighPtIncMM_QCD");
  hDIDilHighPtIncEE_QCD= (TH1D*)_file->Get("hDDilHighPtIncEE_QCD");
  hDIDilHighPtMM_QCD   = (TH1D*)_file->Get("hDDilHighPtMM_QCD");
  hDIDilHighPtEE_QCD   = (TH1D*)_file->Get("hDDilHighPtEE_QCD");

  printf("(%d) MM pdf/qcd = %8.2f / %5.2f / %5.2f ||| EE = %8.2f / %5.2f / %5.2f\n",0,
     1000*hDIDilHighPtIncMM->GetSumOfWeights(),100*abs((hDIDilHighPtIncMM_PDF->GetSumOfWeights()/hDIDilHighPtIncMM->GetSumOfWeights())-1),100*abs((hDIDilHighPtIncMM_QCD->GetSumOfWeights()/hDIDilHighPtIncMM->GetSumOfWeights())-1),
     1000*hDIDilHighPtIncEE->GetSumOfWeights(),100*abs((hDIDilHighPtIncEE_PDF->GetSumOfWeights()/hDIDilHighPtIncEE->GetSumOfWeights())-1),100*abs((hDIDilHighPtIncEE_QCD->GetSumOfWeights()/hDIDilHighPtIncEE->GetSumOfWeights())-1));
  printf("(%d) MM pdf/qcd = %8.2f / %5.2f / %5.2f ||| EE = %8.2f / %5.2f / %5.2f\n",0,
     1000*hDIDilHighPtIncMM->GetSumOfWeights(),100*abs((hDIDilHighPtMM_PDF->GetSumOfWeights()/hDIDilHighPtMM->GetSumOfWeights())/(hDIDilHighPtIncMM_PDF->GetSumOfWeights()/hDIDilHighPtIncMM->GetSumOfWeights())-1),100*abs((hDIDilHighPtMM_QCD->GetSumOfWeights()/hDIDilHighPtMM->GetSumOfWeights())/(hDIDilHighPtIncMM_QCD->GetSumOfWeights()/hDIDilHighPtIncMM->GetSumOfWeights())-1),
     1000*hDIDilHighPtIncEE->GetSumOfWeights(),100*abs((hDIDilHighPtEE_PDF->GetSumOfWeights()/hDIDilHighPtEE->GetSumOfWeights())/(hDIDilHighPtIncEE_PDF->GetSumOfWeights()/hDIDilHighPtIncEE->GetSumOfWeights())-1),100*abs((hDIDilHighPtEE_QCD->GetSumOfWeights()/hDIDilHighPtEE->GetSumOfWeights())/(hDIDilHighPtIncEE_QCD->GetSumOfWeights()/hDIDilHighPtIncEE->GetSumOfWeights())-1));

  // Unc / default
  hDIDilPtMM_PDF       ->Divide(hDIDilPtMM	 );
  hDIDilPtEE_PDF       ->Divide(hDIDilPtEE	 );
  hDIDilHighPtIncMM_PDF->Divide(hDIDilHighPtIncMM);
  hDIDilHighPtIncEE_PDF->Divide(hDIDilHighPtIncEE);
  hDIDilHighPtMM_PDF   ->Divide(hDIDilHighPtMM   );
  hDIDilHighPtEE_PDF   ->Divide(hDIDilHighPtEE   );

  hDIDilPtMM_QCD       ->Divide(hDIDilPtMM	 );
  hDIDilPtEE_QCD       ->Divide(hDIDilPtEE	 );
  hDIDilHighPtIncMM_QCD->Divide(hDIDilHighPtIncMM);
  hDIDilHighPtIncEE_QCD->Divide(hDIDilHighPtIncEE);
  hDIDilHighPtMM_QCD   ->Divide(hDIDilHighPtMM   );
  hDIDilHighPtEE_QCD   ->Divide(hDIDilHighPtEE   );

  printf("---------------------------------------------------------------------\n");
  for(int i=1; i<=hDIDilHighPtIncMM->GetNbinsX(); i++){
    printf("(%d) MM pdf/qcd = %8.2f / %5.2f / %5.2f ||| EE = %8.2f / %5.2f / %5.2f\n",i,
       1000*hDIDilHighPtMM->GetBinContent(i),100*abs(hDIDilHighPtMM_PDF->GetBinContent(i)-1),100*abs(hDIDilHighPtMM_QCD->GetBinContent(i)-1),
       1000*hDIDilHighPtEE->GetBinContent(i),100*abs(hDIDilHighPtEE_PDF->GetBinContent(i)-1),100*abs(hDIDilHighPtEE_QCD->GetBinContent(i)-1)); 
  }

  printf("---------------------------------------------------------------------\n");
  for(int i=1; i<=hDIDilHighPtIncMM->GetNbinsX(); i++){
    printf("(%d) MM pdf/qcd = %8.2f / %5.2f / %5.2f ||| EE = %8.2f / %5.2f / %5.2f\n",i,
       1000*hDIDilHighPtIncMM->GetBinContent(i),100*abs(hDIDilHighPtIncMM_PDF->GetBinContent(i)-1),100*abs(hDIDilHighPtIncMM_QCD->GetBinContent(i)-1),
       1000*hDIDilHighPtIncEE->GetBinContent(i),100*abs(hDIDilHighPtIncEE_PDF->GetBinContent(i)-1),100*abs(hDIDilHighPtIncEE_QCD->GetBinContent(i)-1)); 
  }

  // tight / loose
  hDIDilHighPtMM_PDF->Divide(hDIDilHighPtIncMM_PDF);
  hDIDilHighPtEE_PDF->Divide(hDIDilHighPtIncEE_PDF);
  hDIDilHighPtMM_QCD->Divide(hDIDilHighPtIncMM_QCD);
  hDIDilHighPtEE_QCD->Divide(hDIDilHighPtIncEE_QCD);
  
  printf("---------------------------------------------------------------------\n");
  for(int i=1; i<=hDIDilHighPtIncMM->GetNbinsX(); i++){
    printf("(%d) MM pdf/qcd = %8.2f / %5.2f / %5.2f ||| EE = %8.2f / %5.2f / %5.2f\n",i,
       1000*hDIDilHighPtIncMM->GetBinContent(i),100*abs(hDIDilHighPtMM_PDF->GetBinContent(i)-1),100*abs(hDIDilHighPtMM_QCD->GetBinContent(i)-1),
       1000*hDIDilHighPtIncEE->GetBinContent(i),100*abs(hDIDilHighPtEE_PDF->GetBinContent(i)-1),100*abs(hDIDilHighPtEE_QCD->GetBinContent(i)-1));
  
  }
}
else if(ana == 1){  // Znunu analysis
  TH1D *hDIDilHighPtNN;   TH1D *hDIDilHighPtNN_PDF;   TH1D *hDIDilHighPtNN_QCD;    

  hDIDilHighPtNN      = (TH1D*)_file->Get("hDDilHighPtNN");
  hDIDilHighPtNoEWKNN = (TH1D*)_file->Get("hDDilHighPtNoEWKNN");

  hDIDilHighPtNN_PDF = (TH1D*)_file->Get("hDDilHighPtNN_PDF");

  hDIDilHighPtNN_QCD = (TH1D*)_file->Get("hDDilHighPtNN_QCD");

  printf("(%d) NN pdf/qcd = %8.2f / %5.2f / %5.2f (noewk) %8.2f \n",0,
     1000*hDIDilHighPtNN->GetSumOfWeights()/6.,
     100*abs(hDIDilHighPtNN_PDF->GetSumOfWeights()/hDIDilHighPtNN->GetSumOfWeights()-1),
     100*abs(hDIDilHighPtNN_QCD->GetSumOfWeights()/hDIDilHighPtNN->GetSumOfWeights()-1),
     1000*hDIDilHighPtNoEWKNN->GetSumOfWeights()/6.);

  printf("---------------------------------------------------------------------\n");
  for(int i=1; i<=hDIDilHighPtNN->GetNbinsX(); i++){
    printf("(%d) NN pdf/qcd = %8.2f / %5.2f / %5.2f (noewk) %8.2f\n",i,
       1000*hDIDilHighPtNN->GetBinContent(i)/6.,
       100*abs(hDIDilHighPtNN_PDF->GetBinContent(i)/hDIDilHighPtNN->GetBinContent(i)-1),
       100*abs(hDIDilHighPtNN_QCD->GetBinContent(i)/hDIDilHighPtNN->GetBinContent(i)-1),
       1000*hDIDilHighPtNoEWKNN->GetBinContent(i)/6.); 
  }

}
}
