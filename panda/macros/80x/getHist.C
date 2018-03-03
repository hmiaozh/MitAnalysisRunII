void getHist(int nsel = 0) {
TString inputFolder = "/data/t3home000/ceballos/panda/v_001_0";

const int nFiles = 1;
TFile *_file[nFiles]; TString outputName;
if     (nsel == 0){ // Data
  _file[0] = TFile::Open(Form("%s/SingleMuon.root"  , inputFolder.Data()));
  outputName = "recoeff_data.root";
}
else if(nsel == 1){ // MC
  _file[0] = TFile::Open(Form("%s/DYJetsToLL_M-50_NLO_recoeff.root"  , inputFolder.Data()));
  outputName = "recoeff_mc.root";
}
else {
return;
}

TH1D *hDIRecoMuon_P[28];
TH1D *hDIRecoMuon_F[28];
TH1D *hDIRecoTrack_P[28];
TH1D *hDIRecoTrack_F[28];
TH1D *hDIRecoMuonIso_P[28];
TH1D *hDIRecoMuonIso_F[28];
TH1D *hDIRecoTrackIso_P[28];
TH1D *hDIRecoTrackIso_F[28];

for(int i=0; i<28; i++){
  hDIRecoMuon_P[i]       = (TH1D*)_file[0]->Get(Form("hDRecoMuon_P_%d",i));     hDIRecoMuon_P[i] ->Sumw2();
  hDIRecoMuon_F[i]       = (TH1D*)_file[0]->Get(Form("hDRecoMuon_F_%d",i));     hDIRecoMuon_F[i] ->Sumw2();
  hDIRecoTrack_P[i]      = (TH1D*)_file[0]->Get(Form("hDRecoTrack_P_%d",i));    hDIRecoTrack_P[i]->Sumw2();
  hDIRecoTrack_F[i]      = (TH1D*)_file[0]->Get(Form("hDRecoTrack_F_%d",i));    hDIRecoTrack_F[i]->Sumw2();
  hDIRecoMuonIso_P[i]    = (TH1D*)_file[0]->Get(Form("hDRecoMuonIso_P_%d",i));  hDIRecoMuonIso_P[i] ->Sumw2();
  hDIRecoMuonIso_F[i]    = (TH1D*)_file[0]->Get(Form("hDRecoMuonIso_F_%d",i));  hDIRecoMuonIso_F[i] ->Sumw2();
  hDIRecoTrackIso_P[i]   = (TH1D*)_file[0]->Get(Form("hDRecoTrackIso_P_%d",i)); hDIRecoTrackIso_P[i]->Sumw2();
  hDIRecoTrackIso_F[i]   = (TH1D*)_file[0]->Get(Form("hDRecoTrackIso_F_%d",i)); hDIRecoTrackIso_F[i]->Sumw2();
}

TFile myOutputFile(outputName.Data(),"RECREATE");
for(int i=0; i<28; i++){
  hDIRecoMuon_P[i]    ->Write(); 
  hDIRecoMuon_F[i]    ->Write(); 
  hDIRecoTrack_P[i]   ->Write();
  hDIRecoTrack_F[i]   ->Write();
  hDIRecoMuonIso_P[i] ->Write();
  hDIRecoMuonIso_F[i] ->Write();
  hDIRecoTrackIso_P[i]->Write();
  hDIRecoTrackIso_F[i]->Write();
}
myOutputFile.Close();
}
