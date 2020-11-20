//﻿#include <iostream.h>
//#include "TFile.h"
//#include "TTree.h"

void main() {

const Int_t M = 45;
const Int_t m = 8;
const Double_t zero = 0.0;
const Double_t z05 = 0.5;
const Double_t Nphot = 1.0e+6;
Int_t i;

Double_t x[M] = { 320.6880,  325.7757,  330.8634,  335.9511,  339.3429,  344.4306,  349.5183,  357.9978,  364.7814,  374.9568,
	          385.1322,  397.0035,  412.2666,  429.2256,  442.7928,  458.0559,  473.3190,  488.5821,  502.1493,  515.7165,
	          529.2837,  546.2427,  559.8099,  571.6812,  586.9443,  602.2074,  615.7746,  632.7336,  653.0844,  670.0434,
                  688.6983,  705.6573,  722.6163,  741.2712,  758.2302,  776.8851,  793.8441,  807.4113,  822.6744,  839.6334,
	          851.5047,  866.7678,  882.0309,  895.5981,  900.6858 };
Double_t y[M] = { 4.448,  8.896,  14.178,  17.792,  22.518,  25.576,  30.302,  34.194,  37.252,  40.866,  43.368,  46.148,
		  48.094,  49.484,  50.596,  50.596, 49.484,  48.372,  46.426,  45.036,  42.812,  40.588,  38.642,  35.862,
	          33.638,  31.970,  29.746,  26.688, 24.464,  22.518,  20.294,  18.626,  16.402,  14.734,  13.344,  11.954,
		  10.564,  10.008,  8.618,  7.506,  6.950,  6.116,  5.282,  4.726,  4.726 };



//TH1F* sp = new TH1F("sp", "lambda", 200, 350, 470);

TGraph *sp = new TGraph(M, x, y);

Double_t par[12];

g1 = new TF1("m1","gaus",320,500);
g2 = new TF1("m2","gaus",400,600);
//g3 = new TF1("m3","gaus",400,430);
//g4 = new TF1("m4","gaus",430,460);
//g5 = new TF1("m5","gaus",420,440);
//g6 = new TF1("m6","gaus",400,460);

// The total is the sum of the three, each has 3 parameters
total = new TF1("mstotal","gaus(0)+gaus(3)",330,850);

 // Fit each function and add it to the list of functions
sp->Fit(g1,"R+");
sp->Fit(g2,"R+");
//sp->Fit(g3,"R+");
//sp->Fit(g4,"R+");
//sp->Fit(g5,"R+");
//sp->Fit(g6,"R+");


// Get the parameters from the fit
g1->GetParameters(&par[0]);
g2->GetParameters(&par[3]);
//g3->GetParameters(&par[6]);
//g4->GetParameters(&par[9]);
//g5->GetParameters(&par[12]);
//g6->GetParameters(&par[15]);


// Use the parameters on the sum
total->SetParameters(par);

gStyle->SetOptFit(1111);
TCanvas *E = new TCanvas("E");
E->cd();
sp->Draw();
sp->Fit(total,"R+");



}
