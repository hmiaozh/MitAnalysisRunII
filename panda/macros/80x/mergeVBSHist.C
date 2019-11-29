
void mergeVBSHist() {
TString inputFolder = "/data/t3home000/ceballos/panda/v_001_0";

TFile *_fileEWKWW = TFile::Open(Form("%s/WpWp_EWK.root"  , inputFolder.Data()));
const int nFiles = 4+1;
TFile *_fileWZ[nFiles];
_fileWZ[0] = TFile::Open(Form("%s/WZ3l_0Jets_MG_QCD.root",inputFolder.Data()));
_fileWZ[1] = TFile::Open(Form("%s/WZ3l_1Jets_MG_QCD.root",inputFolder.Data()));
_fileWZ[2] = TFile::Open(Form("%s/WZ3l_2Jets_MG_QCD.root",inputFolder.Data()));
_fileWZ[3] = TFile::Open(Form("%s/WZ3l_3Jets_MG_QCD.root",inputFolder.Data()));
_fileWZ[4] = TFile::Open(Form("%s/WZ3l_MG_EWK.root",inputFolder.Data()));

double xsEWKWW = 0.02598;

double xsWZ[nFiles] = {0.5770677*1.109*1.206,
         	       0.3445573*1.109*1.206,
         	       0.0768421*1.109*1.206,
         	       0.1112010*1.109*1.206,
	     	       0.0176340
                         };

TH1D *hDITotalMCWeightEWKWW = (TH1D*)_fileEWKWW->Get("hDTotalMCWeight");;
TH1D *hDITotalMCWeightWZ[nFiles];
for(int i=0; i<nFiles; i++){
  hDITotalMCWeightWZ[i] = (TH1D*)_fileWZ[i]->Get("hDTotalMCWeight");	 
}

TH1D *hDSSWWMJJ     = (TH1D*)_fileEWKWW->Get("hDSSWWMJJ");     hDSSWWMJJ    ->Scale(xsEWKWW/hDITotalMCWeightEWKWW->GetSumOfWeights());
TH1D *hDSSWWMJJ_PDF = (TH1D*)_fileEWKWW->Get("hDSSWWMJJ_PDF"); hDSSWWMJJ_PDF->Scale(xsEWKWW/hDITotalMCWeightEWKWW->GetSumOfWeights());
TH1D *hDSSWWMJJ_QCD = (TH1D*)_fileEWKWW->Get("hDSSWWMJJ_QCD"); hDSSWWMJJ_QCD->Scale(xsEWKWW/hDITotalMCWeightEWKWW->GetSumOfWeights());
TH1D *hDSSWWMLL     = (TH1D*)_fileEWKWW->Get("hDSSWWMLL");     hDSSWWMLL    ->Scale(xsEWKWW/hDITotalMCWeightEWKWW->GetSumOfWeights());
TH1D *hDSSWWMLL_PDF = (TH1D*)_fileEWKWW->Get("hDSSWWMLL_PDF"); hDSSWWMLL_PDF->Scale(xsEWKWW/hDITotalMCWeightEWKWW->GetSumOfWeights());
TH1D *hDSSWWMLL_QCD = (TH1D*)_fileEWKWW->Get("hDSSWWMLL_QCD"); hDSSWWMLL_QCD->Scale(xsEWKWW/hDITotalMCWeightEWKWW->GetSumOfWeights());

double diff[2];

diff[0] = 1000*(hDSSWWMJJ_PDF->GetSumOfWeights()-hDSSWWMJJ->GetSumOfWeights());
diff[1] = 1000*(hDSSWWMJJ_QCD->GetSumOfWeights()-hDSSWWMJJ->GetSumOfWeights());
printf("hDSSWWMJJ: %.2f %.2f %.2f (%.2f)\n",1000*hDSSWWMJJ->GetSumOfWeights(),diff[0],diff[1],TMath::Sqrt(TMath::Power(diff[0],2)+TMath::Power(diff[1],2)));
for(int i=1; i<=hDSSWWMJJ->GetNbinsX();i++){
  diff[0] = 1000*(hDSSWWMJJ_PDF->GetBinContent(i)-hDSSWWMJJ->GetBinContent(i));
  diff[1] = 1000*(hDSSWWMJJ_QCD->GetBinContent(i)-hDSSWWMJJ->GetBinContent(i));
  printf("hDSSWWMJJ(%d): %.2f %.2f %.2f (%.2f)\n",i,1000*hDSSWWMJJ->GetBinContent(i),diff[0],diff[1],TMath::Sqrt(TMath::Power(diff[0],2)+TMath::Power(diff[1],2)));
}

diff[0] = 1000*(hDSSWWMLL_PDF->GetSumOfWeights()-hDSSWWMLL->GetSumOfWeights());
diff[1] = 1000*(hDSSWWMLL_QCD->GetSumOfWeights()-hDSSWWMLL->GetSumOfWeights());
printf("hDSSWWMLL: %.2f %.2f %.2f (%.2f)\n",1000*hDSSWWMLL->GetSumOfWeights(),diff[0],diff[1],TMath::Sqrt(TMath::Power(diff[0],2)+TMath::Power(diff[1],2)));
for(int i=1; i<=hDSSWWMLL->GetNbinsX();i++){
  diff[0] = 1000*(hDSSWWMLL_PDF->GetBinContent(i)-hDSSWWMLL->GetBinContent(i));
  diff[1] = 1000*(hDSSWWMLL_QCD->GetBinContent(i)-hDSSWWMLL->GetBinContent(i));
  printf("hDSSWWMLL(%d): %.2f %.2f %.2f (%.2f)\n",i,1000*hDSSWWMLL->GetBinContent(i),diff[0],diff[1],TMath::Sqrt(TMath::Power(diff[0],2)+TMath::Power(diff[1],2)));
}

TH1D *hDIWZMJJ[nFiles]; TH1D *hDIWZMJJ_PDF[nFiles]; TH1D *hDIWZMJJ_QCD[nFiles];	 

for(int i=0; i<nFiles; i++){
  hDIWZMJJ[i]     = (TH1D*)_fileWZ[i]->Get("hDWZMJJ");     hDIWZMJJ[i]    ->Scale(xsWZ[i]/hDITotalMCWeightWZ[i]->GetSumOfWeights());  
  hDIWZMJJ_PDF[i] = (TH1D*)_fileWZ[i]->Get("hDWZMJJ_PDF"); hDIWZMJJ_PDF[i]->Scale(xsWZ[i]/hDITotalMCWeightWZ[i]->GetSumOfWeights());  
  hDIWZMJJ_QCD[i] = (TH1D*)_fileWZ[i]->Get("hDWZMJJ_QCD"); hDIWZMJJ_QCD[i]->Scale(xsWZ[i]/hDITotalMCWeightWZ[i]->GetSumOfWeights());  
}

TH1D *hDEWKWZMJJ     = (TH1D*)hDIWZMJJ    [nFiles-1]->Clone();
TH1D *hDEWKWZMJJ_PDF = (TH1D*)hDIWZMJJ_PDF[nFiles-1]->Clone();
TH1D *hDEWKWZMJJ_QCD = (TH1D*)hDIWZMJJ_QCD[nFiles-1]->Clone();

for(int i=1; i<=hDEWKWZMJJ->GetNbinsX();i++){
  diff[0] = 1000*(hDEWKWZMJJ_PDF->GetBinContent(i)-hDEWKWZMJJ->GetBinContent(i));
  diff[1] = 1000*(hDEWKWZMJJ_QCD->GetBinContent(i)-hDEWKWZMJJ->GetBinContent(i));
  printf("hDEWKWZMJJ(%d): %.2f %.2f %.2f (%.2f)\n",i,1000*hDEWKWZMJJ->GetBinContent(i),diff[0],diff[1],TMath::Sqrt(TMath::Power(diff[0],2)+TMath::Power(diff[1],2)));
}

TH1D *hDQCDWZMJJ     = (TH1D*)hDIWZMJJ[0]    ->Clone();
TH1D *hDQCDWZMJJ_PDF = (TH1D*)hDIWZMJJ_PDF[0]->Clone();
TH1D *hDQCDWZMJJ_QCD = (TH1D*)hDIWZMJJ_QCD[0]->Clone();

for(int i=1; i<nFiles-1; i++){
  hDQCDWZMJJ    ->Add(hDIWZMJJ    [i]);	
  hDQCDWZMJJ_PDF->Add(hDIWZMJJ_PDF[i]);   
  hDQCDWZMJJ_QCD->Add(hDIWZMJJ_QCD[i]);   
}

for(int i=1; i<=hDQCDWZMJJ->GetNbinsX();i++){
  diff[0] = 1000*(hDQCDWZMJJ_PDF->GetBinContent(i)-hDQCDWZMJJ->GetBinContent(i));
  diff[1] = 1000*(hDQCDWZMJJ_QCD->GetBinContent(i)-hDQCDWZMJJ->GetBinContent(i));
  printf("hDQCDWZMJJ(%d): %.2f %.2f %.2f (%.2f)\n",i,1000*hDQCDWZMJJ->GetBinContent(i),diff[0],diff[1],TMath::Sqrt(TMath::Power(diff[0],2)+TMath::Power(diff[1],2)));
}

TFile myOutputFile("genVBS.root","RECREATE");
  hDSSWWMJJ    ->Write(); 
  hDSSWWMJJ_PDF->Write(); 
  hDSSWWMJJ_QCD->Write(); 
  hDSSWWMLL    ->Write(); 
  hDSSWWMLL_PDF->Write(); 
  hDSSWWMLL_QCD->Write(); 
  hDEWKWZMJJ	->Write(); 
  hDEWKWZMJJ_PDF->Write(); 
  hDEWKWZMJJ_QCD->Write(); 
  hDQCDWZMJJ	->Write(); 
  hDQCDWZMJJ_PDF->Write(); 
  hDQCDWZMJJ_QCD->Write(); 
myOutputFile.Close();

}
