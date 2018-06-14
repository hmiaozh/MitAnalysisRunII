void checkEqualBinning(TString fileName = "", int intervalType = 0, bool debug = false){
  TFile *_file0 = TFile::Open(fileName.Data());
  TH1F* histo0 = (TH1F*)_file0->Get(Form("bdtValue/histo13"));
  TH1F* histo1 = (TH1F*)_file0->Get(Form("bdtValue/histo14"));
  double sum[3]= {0, 0, 0};
  double theInterval[8] = {1/8., 2/8., 3/8., 4/8., 5/8., 6/8., 7/8., 8.001/8.};
  bool theCall[8] = {false, false, false, false, false, false, false, false};
  if(intervalType == 1){
    theInterval[0] = 1/6.;
    theInterval[1] = 2/6.;
    theInterval[2] = 3/6.;
    theInterval[3] = 4/6.;
    theInterval[4] = 5/6.;
    theInterval[5] = 6.001/6.;
    theInterval[6] = 7/6.;
    theInterval[7] = 8/6.;
  }
  for(int nb=1; nb<=histo0->GetNbinsX(); nb++){
    sum[0] = sum[0] +  histo0->GetBinContent(nb) / histo0->GetSumOfWeights();
    sum[1] = sum[1] +  histo1->GetBinContent(nb) / histo1->GetSumOfWeights();
    sum[2] = sum[2] + (histo0->GetBinContent(nb) + histo1->GetBinContent(nb)) / (histo0->GetSumOfWeights() + histo1->GetSumOfWeights());
    if(debug) printf("%5.3f %5.3f %5.3f\n",sum[0],sum[1],sum[2]);
    for(int i=0; i<8; i++) {
      if(theCall[i] == false && sum[2] > theInterval[i]){
        printf("%3d %5.2f %5.3f %5.3f %5.3f %d\n",nb,-1.0+nb/100.,sum[0],sum[1],sum[2],i);
	theCall[i] = true;
        break;
      }
    }
  }

}
