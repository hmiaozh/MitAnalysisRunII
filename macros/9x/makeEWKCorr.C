#include "Riostream.h"
void makeEWKCorr() {
   Float_t x,y,z,t;
   TH1D* hWZ_NLO_CMS     = new TH1D("hWZ_NLO_CMS",    "hWZ_NLO_CMS",    312,500,12980);
   TH1D* hWZ_NLO_CMSUp   = new TH1D("hWZ_NLO_CMSUp",  "hWZ_NLO_CMSUp",  312,500,12980);
   TH1D* hWZ_NLO_CMSDown = new TH1D("hWZ_NLO_CMSDown","hWZ_NLO_CMSDown",312,500,12980);
   TH1D* hWZ_LO_CMS      = new TH1D("hWZ_LO_CMS",     "hWZ_LO_CMS",     312,500,12980);
   TH1D* hWZ_LO_CMSUp    = new TH1D("hWZ_LO_CMSUp",   "hWZ_LO_CMSUp",   312,500,12980);
   TH1D* hWZ_LO_CMSDown  = new TH1D("hWZ_LO_CMSDown", "hWZ_LO_CMSDown", 312,500,12980);
   TH1D* hWZ_KF_CMS      = new TH1D("hWZ_KF_CMS",     "hWZ_KF_CMS",     312,500,12980);
   TH1D* hWZ_KF_CMSUp    = new TH1D("hWZ_KF_CMSUp",   "hWZ_KF_CMSUp",   312,500,12980);
   TH1D* hWZ_KF_CMSDown  = new TH1D("hWZ_KF_CMSDown", "hWZ_KF_CMSDown", 312,500,12980);
   TH1D* hWW_KF_CMS      = new TH1D("hWW_KF_CMS",     "hWW_KF_CMS",      30,500, 2000);
   TH1D* hWW_KF_CMSUp    = new TH1D("hWW_KF_CMSUp",   "hWW_KF_CMSUp",    30,500, 2000);
   TH1D* hWW_KF_CMSDown  = new TH1D("hWW_KF_CMSDown", "hWW_KF_CMSDown",  30,500, 2000);

   ifstream in;
   in.open(Form("MitAnalysisRunII/macros/9x/WZ_NLO_CMS_mjj.dat"));
   Int_t nlines = 0;
   while (1) {
      in >> x >> y >> z >> t;
      if (!in.good()) break;
      if (nlines < 5) printf("x=%8f, y=%8f, z=%8f, t=%8f\n",x,y,z,t);
      hWZ_NLO_CMS   ->Fill(x,y);
      hWZ_NLO_CMSDown->Fill(x,z);
      hWZ_NLO_CMSUp  ->Fill(x,t);
      nlines++;
   }
   printf(" found %d points\n",nlines);
   in.close();

   in.open(Form("MitAnalysisRunII/macros/9x/WZ_LO_CMS_mjj.dat"));
   nlines = 0;
   while (1) {
      in >> x >> y >> z >> t;
      if (!in.good()) break;
      if (nlines < 5) printf("x=%8f, y=%8f, z=%8f, t=%8f\n",x,y,z,t);
      hWZ_LO_CMS    ->Fill(x,y);
      hWZ_LO_CMSDown->Fill(x,z);
      hWZ_LO_CMSUp  ->Fill(x,t);
      nlines++;
   }
   printf(" found %d points\n",nlines);
   in.close();

   hWZ_KF_CMS    ->Add(hWZ_NLO_CMS    ); hWZ_KF_CMS    ->Divide(hWZ_LO_CMS);
   hWZ_KF_CMSUp  ->Add(hWZ_NLO_CMSUp  ); hWZ_KF_CMSUp  ->Divide(hWZ_LO_CMS);
   hWZ_KF_CMSDown->Add(hWZ_NLO_CMSDown); hWZ_KF_CMSDown->Divide(hWZ_LO_CMS);

   hWZ_NLO_CMS    ->Rebin(2); hWZ_NLO_CMS    ->Scale(0.5);
   hWZ_NLO_CMSUp  ->Rebin(2); hWZ_NLO_CMSUp  ->Scale(0.5);
   hWZ_NLO_CMSDown->Rebin(2); hWZ_NLO_CMSDown->Scale(0.5);
   hWZ_LO_CMS     ->Rebin(2); hWZ_LO_CMS     ->Scale(0.5);
   hWZ_LO_CMSUp   ->Rebin(2); hWZ_LO_CMSUp   ->Scale(0.5);
   hWZ_LO_CMSDown ->Rebin(2); hWZ_LO_CMSDown ->Scale(0.5); 
   hWZ_KF_CMS     ->Rebin(2); hWZ_KF_CMS     ->Scale(0.5);
   hWZ_KF_CMSUp   ->Rebin(2); hWZ_KF_CMSUp   ->Scale(0.5);
   hWZ_KF_CMSDown ->Rebin(2); hWZ_KF_CMSDown ->Scale(0.5); 

   hWW_KF_CMS->SetBinContent( 1,0.97);
   hWW_KF_CMS->SetBinContent( 2,0.95);
   hWW_KF_CMS->SetBinContent( 3,0.92);
   hWW_KF_CMS->SetBinContent( 4,0.90);
   hWW_KF_CMS->SetBinContent( 5,0.89);
   hWW_KF_CMS->SetBinContent( 6,0.88);
   hWW_KF_CMS->SetBinContent( 7,0.87);
   hWW_KF_CMS->SetBinContent( 8,0.86);
   hWW_KF_CMS->SetBinContent( 9,0.86);
   hWW_KF_CMS->SetBinContent(10,0.85);
   hWW_KF_CMS->SetBinContent(11,0.84);
   hWW_KF_CMS->SetBinContent(12,0.84);
   hWW_KF_CMS->SetBinContent(13,0.83);
   hWW_KF_CMS->SetBinContent(14,0.83);
   hWW_KF_CMS->SetBinContent(15,0.82);
   hWW_KF_CMS->SetBinContent(16,0.82);
   hWW_KF_CMS->SetBinContent(17,0.81);
   hWW_KF_CMS->SetBinContent(18,0.81);
   hWW_KF_CMS->SetBinContent(19,0.80);
   hWW_KF_CMS->SetBinContent(20,0.79);
   hWW_KF_CMS->SetBinContent(21,0.79);
   hWW_KF_CMS->SetBinContent(22,0.78);
   hWW_KF_CMS->SetBinContent(23,0.78);
   hWW_KF_CMS->SetBinContent(24,0.78);
   hWW_KF_CMS->SetBinContent(25,0.78);
   hWW_KF_CMS->SetBinContent(26,0.78);
   hWW_KF_CMS->SetBinContent(27,0.78);
   hWW_KF_CMS->SetBinContent(28,0.77);
   hWW_KF_CMS->SetBinContent(29,0.77);
   hWW_KF_CMS->SetBinContent(30,0.77);

   hWW_KF_CMSUp  ->Add(hWW_KF_CMS, 1.00*1.027);
   hWW_KF_CMSDown->Add(hWW_KF_CMS, 1.00/1.027);

   auto f = TFile::Open("VV_NLO_LO_CMS_mjj.root","RECREATE");
   f->cd();
   hWZ_NLO_CMS    ->Write(); 
   hWZ_NLO_CMSUp  ->Write(); 
   hWZ_NLO_CMSDown->Write(); 
   hWZ_LO_CMS     ->Write(); 
   hWZ_LO_CMSUp   ->Write(); 
   hWZ_LO_CMSDown ->Write();   
   hWZ_KF_CMS     ->Write(); 
   hWZ_KF_CMSUp   ->Write(); 
   hWZ_KF_CMSDown ->Write();   
   hWW_KF_CMS     ->Write(); 
   hWW_KF_CMSUp   ->Write(); 
   hWW_KF_CMSDown ->Write();   
   f->Close();
}
