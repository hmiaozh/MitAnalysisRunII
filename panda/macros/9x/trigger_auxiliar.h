#include "MitAnalysisRunII/panda/macros/9x/trigger_auxiliar_data.h"

void trigger_sf(double trgRes[2], double theTrgEff [3][nTrgBinPt1][nTrgBinPt2][nTrgBinEta1][nTrgBinEta2], 
                                  double theTrgEffE[3][nTrgBinPt1][nTrgBinPt2][nTrgBinEta1][nTrgBinEta2], 
				  int ltype, double pt1, double eta1, double pt2, double eta2){
  if(pt2 <= 15) pt2 = 15;
  double ptaux = pt1;
  double etaaux = eta1;
  if(pt1 < pt2) {pt1 = pt2; pt2 = ptaux; eta1 = eta2; eta2 = etaaux;}

  int npt1  = hDTrgBinPt1 ->GetXaxis()->FindFixBin(pt1)-1;
  int npt2  = hDTrgBinPt2 ->GetXaxis()->FindFixBin(pt2)-1;
  int neta1 = hDTrgBinEta1->GetXaxis()->FindFixBin(eta1)-1;
  int neta2 = hDTrgBinEta2->GetXaxis()->FindFixBin(eta2)-1;

  if(npt1 == -1 || npt2 == -1 || neta1 == -1 || neta2 == -1) printf("PROBLEM %d %d %d %d / %f %f %f %f\n",npt1,npt2,neta1,neta2,pt1,pt2,eta1,eta2);

  trgRes[0] = theTrgEff [ltype][npt1][npt2][neta1][neta2];
  trgRes[1] = theTrgEffE[ltype][npt1][npt2][neta1][neta2];
}
