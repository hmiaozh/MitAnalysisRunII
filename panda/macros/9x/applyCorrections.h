double fakeRateFactor(double pt, double eta, int pdgId, bool applyTight, TH2D *histoFakeEffSelMediumEtaPt_m, TH2D *histoFakeEffSelMediumEtaPt_e, TH2D *histoFakeEffSelTightEtaPt_m, TH2D *histoFakeEffSelTightEtaPt_e){
  if(eta >= 2.4) eta = 2.3999; else if(eta <= -2.4) eta = -2.3999;
  if(pt >= 45) pt = 44.999;
  int binXT = histoFakeEffSelMediumEtaPt_m->GetXaxis()->FindFixBin(eta);
  int binYT = histoFakeEffSelMediumEtaPt_m->GetYaxis()->FindFixBin(pt);
  
  double rate = 1.0;
  if     (TMath::Abs(pdgId) == 13 && applyTight == false) rate = TMath::Min(histoFakeEffSelMediumEtaPt_m->GetBinContent(binXT,binYT),0.999999);
  else if(TMath::Abs(pdgId) == 13 && applyTight == true)  rate = TMath::Min(histoFakeEffSelTightEtaPt_m ->GetBinContent(binXT,binYT),0.999999);
  else if(TMath::Abs(pdgId) == 11 && applyTight == false) rate = TMath::Min(histoFakeEffSelMediumEtaPt_e->GetBinContent(binXT,binYT),0.999999);
  else if(TMath::Abs(pdgId) == 11 && applyTight == true)  rate = TMath::Min(histoFakeEffSelTightEtaPt_e ->GetBinContent(binXT,binYT),0.999999);
  else printf("IMPOSSIBLE COMPUTING FAKE RATES\n");

  //if(pt<20 && applyTight == true) rate = 2*rate/(1+rate);

  return rate/(1-rate);
}

double lepScaleFactor(double pt, double eta, int pdgId, bool applyTight, TH2D *histoLepEffSelMediumEtaPt_m, TH2D *histoLepEffSelMediumEtaPt_e, TH2D *histoLepEffSelTightEtaPt_m, TH2D *histoLepEffSelTightEtaPt_e){
  if(eta >= 2.4) eta = 2.3999; else if(eta <= -2.4) eta = -2.3999;
  if(pt >= 100) pt = 99.999; else if(pt <= 20) pt = 20.001;
  int binXT = histoLepEffSelMediumEtaPt_m->GetXaxis()->FindFixBin(eta);
  int binYT = histoLepEffSelMediumEtaPt_m->GetYaxis()->FindFixBin(pt);

  double sf = 1.0;
  if     (TMath::Abs(pdgId) == 13 && applyTight == false) sf = histoLepEffSelMediumEtaPt_m->GetBinContent(binXT,binYT);
  else if(TMath::Abs(pdgId) == 13 && applyTight == true)  sf = histoLepEffSelTightEtaPt_m ->GetBinContent(binXT,binYT);
  else if(TMath::Abs(pdgId) == 11 && applyTight == false) sf = histoLepEffSelMediumEtaPt_e->GetBinContent(binXT,binYT);
  else if(TMath::Abs(pdgId) == 11 && applyTight == true)  sf = histoLepEffSelTightEtaPt_e ->GetBinContent(binXT,binYT);
  else printf("IMPOSSIBLE COMPUTING Lep SF\n");
  
  if(sf == 0){printf("SF == 0!: %f %f %d %d %d\n",pt,eta,pdgId,binXT,binYT);}

  return sf;
}

double nPUScaleFactor(TH1D *fhDPU, float npu){
  double mynpu = TMath::Min(npu,(float)79.999);
  Int_t npuxbin = fhDPU->GetXaxis()->FindBin(mynpu);
  return fhDPU->GetBinContent(npuxbin);
}

double electronToPhotonSF(double pt, int year){
  double effDA = 1.0;
  double effMC = 1.0;
  if	 (year == 2016) {
     effDA = (0.0052 + 1.114 * TMath::Power(pt + 122.84, -0.75));
     effMC = (0.0050 + 2.922 * TMath::Power(pt +  87.23, -1.18));
  }
  else if(year == 2017 || year == 2018) {
     effDA = (0.0256 + 3.000 * TMath::Power(pt + 10.78, -1.43));
     effMC = (0.0068 + 0.029 * TMath::Power(pt - 22.10, -0.45));
  }
  //printf("electronToPhotonSF (pt=%.1f): %f/%f=%f\n",pt,effDA,effMC,effDA/effMC);

  return effDA/effMC;
}

double effhDPhotonScaleFactor(double pt, double eta, TString type, TH2D *fhDIdSF, TH2D *fhDVetoSF){

  if(pt>=200) pt = +199.999;

  if     (eta>=+2.4) eta = +2.399;
  else if(eta<=-2.4) eta = -2.399;

  Int_t binXA = 0;
  Int_t binYA = 0;
  Int_t binXB = 0;
  Int_t binYB = 0;

  binXA = fhDIdSF  ->GetXaxis()->FindFixBin(eta);binYA = fhDIdSF  ->GetYaxis()->FindFixBin(pt);
  
  eta = abs(eta); if(eta < 1.5) eta = 1.0; else eta = 2.0;
  binXB = fhDVetoSF->GetXaxis()->FindFixBin(eta);binYB = fhDVetoSF->GetYaxis()->FindFixBin(pt);

  double idSF   = fhDIdSF  ->GetBinContent(binXA, binYA);
  double vetoSF = fhDVetoSF->GetBinContent(binXB, binYB);
  
  if(idSF <= 0 || vetoSF <= 0) printf("photonSF <= 0! %f %f %d %d %d %d - %f %f\n",idSF,vetoSF,binXA,binYA,binXB,binYB,pt,eta);

  return idSF*vetoSF;
}

void trigger_sf(double trgRes[2], int nlep,
	TH2D* trgSFMMBB, TH2D* trgSFMMEB, TH2D* trgSFMMBE, TH2D* trgSFMMEE, TH2D* trgSFEEBB, TH2D* trgSFEEEB, TH2D* trgSFEEBE, TH2D* trgSFEEEE,
        TH2D* trgSFMEBB, TH2D* trgSFMEEB, TH2D* trgSFMEBE, TH2D* trgSFMEEE, TH2D* trgSFEMBB, TH2D* trgSFEMEB, TH2D* trgSFEMBE, TH2D* trgSFEMEE,
        double pt1, double eta1, int pdgid1, 
	double pt2, double eta2, int pdgid2){

  trgRes[0] = 1.0;
  trgRes[1] = 0.0;
  if(nlep == 2){
    if     (pt1 <= 20) pt1 = 20.001;
    else if(pt1 >= 70) pt1 = 69.999;
    if     (pt2 <= 20) pt2 = 20.001;
    else if(pt2 >= 70) pt2 = 69.999;
    double ptaux = pt1;
    double etaaux = eta1;
    double pdgidaux = pdgid1;
    if(pt1 < pt2) {
      pt1 = pt2; pt2 = ptaux; 
      pdgid1 = pdgid2; pdgid2 = pdgidaux;
      eta1 = eta2; eta2 = etaaux;
    }
    int binPt1 = trgSFMMBB->GetXaxis()->FindFixBin(pt1);
    int binPt2 = trgSFMMBB->GetXaxis()->FindFixBin(pt2);
    int lepType = -1;
    if     (abs(pdgid1)==13 && abs(pdgid2)==13) lepType = 0;
    else if(abs(pdgid1)==11 && abs(pdgid2)==11) lepType = 1;
    else if(abs(pdgid1)==13 && abs(pdgid2)==11) lepType = 2;
    else if(abs(pdgid1)==11 && abs(pdgid2)==13) lepType = 3;
    int neta1 = 0; if(TMath::Abs(eta1) > 1.5) neta1 = 1;
    int neta2 = 0; if(TMath::Abs(eta2) > 1.5) neta2 = 1;

    if     (lepType == 0 && neta1 == 0 && neta2 == 0) {trgRes[0] = trgSFMMBB->GetBinContent(binPt1,binPt2); trgRes[1] = trgSFMMBB->GetBinError(binPt1,binPt2);}
    else if(lepType == 0 && neta1 == 1 && neta2 == 0) {trgRes[0] = trgSFMMEB->GetBinContent(binPt1,binPt2); trgRes[1] = trgSFMMEB->GetBinError(binPt1,binPt2);}
    else if(lepType == 0 && neta1 == 0 && neta2 == 1) {trgRes[0] = trgSFMMBE->GetBinContent(binPt1,binPt2); trgRes[1] = trgSFMMBE->GetBinError(binPt1,binPt2);}
    else if(lepType == 0 && neta1 == 1 && neta2 == 1) {trgRes[0] = trgSFMMEE->GetBinContent(binPt1,binPt2); trgRes[1] = trgSFMMEE->GetBinError(binPt1,binPt2);}
    else if(lepType == 1 && neta1 == 0 && neta2 == 0) {trgRes[0] = trgSFEEBB->GetBinContent(binPt1,binPt2); trgRes[1] = trgSFEEBB->GetBinError(binPt1,binPt2);}
    else if(lepType == 1 && neta1 == 1 && neta2 == 0) {trgRes[0] = trgSFEEEB->GetBinContent(binPt1,binPt2); trgRes[1] = trgSFEEEB->GetBinError(binPt1,binPt2);}
    else if(lepType == 1 && neta1 == 0 && neta2 == 1) {trgRes[0] = trgSFEEBE->GetBinContent(binPt1,binPt2); trgRes[1] = trgSFEEBE->GetBinError(binPt1,binPt2);}
    else if(lepType == 1 && neta1 == 1 && neta2 == 1) {trgRes[0] = trgSFEEEE->GetBinContent(binPt1,binPt2); trgRes[1] = trgSFEEEE->GetBinError(binPt1,binPt2);}
    else if(lepType == 2 && neta1 == 0 && neta2 == 0) {trgRes[0] = trgSFMEBB->GetBinContent(binPt1,binPt2); trgRes[1] = trgSFMEBB->GetBinError(binPt1,binPt2);}
    else if(lepType == 2 && neta1 == 1 && neta2 == 0) {trgRes[0] = trgSFMEEB->GetBinContent(binPt1,binPt2); trgRes[1] = trgSFMEEB->GetBinError(binPt1,binPt2);}
    else if(lepType == 2 && neta1 == 0 && neta2 == 1) {trgRes[0] = trgSFMEBE->GetBinContent(binPt1,binPt2); trgRes[1] = trgSFMEBE->GetBinError(binPt1,binPt2);}
    else if(lepType == 2 && neta1 == 1 && neta2 == 1) {trgRes[0] = trgSFMEEE->GetBinContent(binPt1,binPt2); trgRes[1] = trgSFMEEE->GetBinError(binPt1,binPt2);}
    else if(lepType == 3 && neta1 == 0 && neta2 == 0) {trgRes[0] = trgSFEMBB->GetBinContent(binPt1,binPt2); trgRes[1] = trgSFEMBB->GetBinError(binPt1,binPt2);}
    else if(lepType == 3 && neta1 == 1 && neta2 == 0) {trgRes[0] = trgSFEMEB->GetBinContent(binPt1,binPt2); trgRes[1] = trgSFEMEB->GetBinError(binPt1,binPt2);}
    else if(lepType == 3 && neta1 == 0 && neta2 == 1) {trgRes[0] = trgSFEMBE->GetBinContent(binPt1,binPt2); trgRes[1] = trgSFEMBE->GetBinError(binPt1,binPt2);}
    else if(lepType == 3 && neta1 == 1 && neta2 == 1) {trgRes[0] = trgSFEMEE->GetBinContent(binPt1,binPt2); trgRes[1] = trgSFEMEE->GetBinError(binPt1,binPt2);}
    else {printf("Problem trgSF\n"); return;}
  }
}

double metPhiCorr(int year, int npv, bool isData, int metCoord){
  double corr = 1.0;
  if     (year == 2016 && isData == true && metCoord == 0){
    corr = 1.003056+0.143124*npv;
  }
  else if(year == 2016 && isData == true && metCoord == 1){
    corr = 0.289329+0.046554*npv;
  }
  else if(year == 2016 && isData == false && metCoord == 0){
    corr = -0.111478-0.219850*npv;
  }
  else if(year == 2016 && isData == false && metCoord == 1){
    corr = 0.803057-0.038977*npv;
  }
  else if(year == 2017 && isData == true && metCoord == 0){
    corr = 0.315233-0.177541*npv;
  }
  else if(year == 2017 && isData == true && metCoord == 1){
    corr = 0.449429+0.235785*npv;
  }
  else if(year == 2017 && isData == false && metCoord == 0){
    corr = 0.368400-0.230686*npv;
  }
  else if(year == 2017 && isData == false && metCoord == 1){
    corr = -0.210643+0.182399*npv;
  }
  else if(year == 2018 && isData == true && metCoord == 0){
    corr = 1.230829+0.417271*npv;
  }
  else if(year == 2018 && isData == true && metCoord == 1){
    corr = -1.114256+0.103044*npv;
  }
  else if(year == 2018 && isData == false && metCoord == 0){
    corr = -0.117858+0.339384*npv;
  }
  else if(year == 2018 && isData == false && metCoord == 1){
    corr = 0.235414+0.135433*npv;
  }
  else {
    printf("WRONG CHOICE!\n");
  }

  return corr;
}
