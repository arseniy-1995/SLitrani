#include <iostream.h>
#include "TFile.h"
#include "TTree.h"

Double_t delta_t04 (Double_t b04){
 
return 36000.0/(b04-50.0)+500.0;
  
}

Double_t delta_t05 (Double_t b05){
  
return  36000.0/(b05-50.0)+520.0;
  
}

Double_t delta_t06 (Double_t b06){
  
return  36000.0/(b06-50.0)+520.0;
  
}

Double_t delta_t07 (Double_t b07){
  
return  36000.0/(b07-50.0)+520.0;
  
}




Double_t bt04_left (Double_t *x, Double_t *par){
 
  Double_t xx=x[0];
  
  return 3600.0/(xx-500.0)+50.0;
  
}

Double_t bt04_right (Double_t *x, Double_t *par){
 
  Double_t xx=x[0];
  return 3600.0/(xx-850.0)+300.0;
  
}

Double_t bt05_left (Double_t *x, Double_t *par){
 
  Double_t xx=x[0];
  return 3600.0/(xx-520.0)+50.0;
  
}

Double_t bt05_right (Double_t *x, Double_t *par){
 
  Double_t xx=x[0];
  return 3600.0/(xx-820.0)+300.0;
  
}


Double_t bt06_left (Double_t *x, Double_t *par){
 
  Double_t xx=x[0];
  return 3600.0/(xx-520.0)+50.0;
  
}

Double_t bt06_right (Double_t *x, Double_t *par){
 
  Double_t xx=x[0];
  return 3600.0/(xx-900.0)+350;
  
}


Double_t bt07_left (Double_t *x, Double_t *par){
 
  Double_t xx=x[0];
  return 3600.0/(xx-520.0)+50.0;
  
}

Double_t bt07_right (Double_t *x, Double_t *par){
 
  Double_t xx=x[0];
  return 3600.0/(xx-950.0)+350.0;
  
}


void main() {

// TFile *f=new TFile("4hamama3.root");
  
// TFile *f=new TFile("stend_with_optical_grease.root");
  
TFile *f=new TFile("stend_30.09.root");
  
TCanvas *MyC = new TCanvas("MyC", "MyC", 0, 0, 2000, 1000);

TF1 *f04_left = new TF1 ("f04_left", bt04_left,500, 2000, 1);
TF1 *f04_right = new TF1 ("f04_right",bt04_right,850, 2000, 1);

TF1 *f05_left = new TF1 ("f05_left", bt05_left,520, 2000, 1);
TF1 *f05_right = new TF1 ("f05_right", bt05_right,820, 2000, 1);

TF1 *f06_left = new TF1 ("f06_left", bt06_left,520, 2000, 1);
TF1 *f06_right = new TF1 ("f06_right", bt06_right,900, 2000, 1);

TF1 *f07_left = new TF1 ("f07_left", bt07_left,520, 2000, 1);
TF1 *f07_right = new TF1 ("f07_right", bt07_right,950, 2000, 1);


TH1F *h1_time = new TH1F("h1_time","time resolution",1000,-500,500);

TH1F *h1_time_delta = new TH1F("h1_time_delta","time resolution_delta",500,-500,500);

//TH1F *h1_time_delta_1 = new TH1F("h1_time_delta_1","time resolution_delta",500,-500,500);

//TH1F *h1_time_delta_2 = new TH1F("h1_time_delta_2","time resolution_delta",500,-500,500);

//TH1F *h1_time_delta_3 = new TH1F("h1_time_delta_3","time resolution_delta",500,-500,500);

//TH1F *h1_time_delta_4 = new TH1F("h1_time_delta_4","time resolution_delta",500,-500,500);



TH1F *h1_time_SiPM04_delta_1 = new TH1F("h1_time_SiPM04_delta_1","time resolution_delta",500,-500,500);

TH1F *h1_time_SiPM04_delta_2 = new TH1F("h1_time_SiPM04_delta_2","time resolution_delta",500,-500,500);

TH1F *h1_time_SiPM04_delta_3 = new TH1F("h1_time_SiPM04_delta_3","time resolution_delta",500,-500,500);

TH1F *h1_time_SiPM04_delta_4 = new TH1F("h1_time_SiPM04_delta_4","time resolution_delta",500,-500,500);


TH1F *h1_time_SiPM05_delta_1 = new TH1F("h1_time_SiPM05_delta_1","time resolution_delta",500,-500,500);

TH1F *h1_time_SiPM05_delta_2 = new TH1F("h1_time_SiPM05_delta_2","time resolution_delta",500,-500,500);

TH1F *h1_time_SiPM05_delta_3 = new TH1F("h1_time_SiPM05_delta_3","time resolution_delta",500,-500,500);

TH1F *h1_time_SiPM05_delta_4 = new TH1F("h1_time_SiPM05_delta_4","time resolution_delta",500,-500,500);


TH1F *h1_time_SiPM06_delta_1 = new TH1F("h1_time_SiPM06_delta_1","time resolution_delta",500,-500,500);

TH1F *h1_time_SiPM06_delta_2 = new TH1F("h1_time_SiPM06_delta_2","time resolution_delta",500,-500,500);

TH1F *h1_time_SiPM06_delta_3 = new TH1F("h1_time_SiPM06_delta_3","time resolution_delta",500,-500,500);

TH1F *h1_time_SiPM06_delta_4 = new TH1F("h1_time_SiPM06_delta_4","time resolution_delta",500,-500,500);


TH1F *h1_time_SiPM07_delta_1 = new TH1F("h1_time_SiPM07_delta_1","time resolution_delta",500,-500,500);

TH1F *h1_time_SiPM07_delta_2 = new TH1F("h1_time_SiPM07_delta_2","time resolution_delta",500,-500,500);

TH1F *h1_time_SiPM07_delta_3 = new TH1F("h1_time_SiPM07_delta_3","time resolution_delta",500,-500,500);

TH1F *h1_time_SiPM07_delta_4 = new TH1F("h1_time_SiPM07_delta_4","time resolution_delta",500,-500,500);



//cout<<"!!!"<<endl;

//TH1F *h1_1 = new TH1F("h1_1","t04-delta_t04",500,-500,500);
//TH1F *h1_2 = new TH1F("h1_2","t05-delta_t05",500,-500,500);
//TH1F *h1_3 = new TH1F("h1_3","t06-delta_t06",500,-500,500);
//TH1F *h1_4 = new TH1F("h1_4","t07-delta_t07",500,-500,500);


TH2 *h2_1 = new TH2D("h2_1","b04:t04+cut",500,0,2100,500,0,2100);
TH2 *h3_1 = new TH2D("h3_1","b04:t04+cut",500,0,2100,1000,0,2100);

TH2 *h2_2 = new TH2D("h2_2","b05:t05+cut",500,0,2100,500,0,2100);
TH2 *h3_2 = new TH2D("h3_2","b04:t04+cut",500,0,2100,500,0,2100);

TH2 *h2_3 = new TH2D("h2_3","b06:t06+cut",500,0,2100,500,0,2100);
TH2 *h3_3 = new TH2D("h3_3","b06:t06+cut",500,0,2100,500,0,2100);

TH2 *h2_4 = new TH2D("h2_4","b07:t07+cut",500,0,2100,500,0,2100);
TH2 *h3_4 = new TH2D("h3_4","b07:t07+cut",500,0,2100,500,0,2100);

TH2 *h4 = new TH2D("h4","b04:b05+Cut",500,0,2100,500,0,2100);
TH2 *h5 = new TH2D("h5","b06:b07+Cut",500,0,2100,500,0,2100);
//TH2 *h6 = new TH2D("h6","b04:b06+Cut",500,0,2100,500,0,2100);
//TH2 *h7 = new TH2D("h7","b05:b07+Cut",500,0,2100,500,0,2100);
//TH2 *h8 = new TH2D("h8","b04:b07+Cut",500,0,2100,500,0,2100);
//TH2 *h9 = new TH2D("h9","b05:b06+Cut",500,0,2100,500,0,2100);

TH2 *h4_ = new TH2D("h4_","b04:b05+Cut",500,0,2100,500,0,2100);
TH2 *h5_ = new TH2D("h5_","b06:b07+Cut",1000,0,2100,500,0,2100);
//TH2 *h6_ = new TH2D("h6_","b04:b06+Cut",1000,0,2100,500,0,2100);
//TH2 *h7_ = new TH2D("h7_","b05:b07+Cut",1000,0,2100,500,0,2100);
//TH2 *h8_ = new TH2D("h8_","b04:b07+Cut",1000,0,2100,500,0,2100);
//TH2 *h9_ = new TH2D("h9_","b05:b06+Cut",1000,0,2100,500,0,2100);

TH2 *h4_2 = new TH2D("h4_2","t04:t05+Cut",500,0,2100,500,0,2100);
TH2 *h5_2 = new TH2D("h5_2","t06:t07+Cut",500,0,2100,500,0,2100);
//TH2 *h6_2 = new TH2D("h6_2","t04:t06+Cut",500,0,2100,500,0,2100);
//TH2 *h7_2 = new TH2D("h7_2","t05:t07+Cut",500,0,2100,500,0,2100);
//TH2 *h8_2 = new TH2D("h8_2","t04:t07+Cut",500,0,2100,500,0,2100);
//TH2 *h9_2 = new TH2D("h9_2","t05:t06+Cut",500,0,2100,500,0,2100);


TH2 *h4_3 = new TH2D("h4_3","t04:t05+Cut",500,0,2100,500,0,2100);
TH2 *h5_3 = new TH2D("h5_3","t06:t07+Cut",500,0,2100,500,0,2100);
//TH2 *h6_3 = new TH2D("h6_3","t04:t06+Cut",500,0,2100,500,0,2100);
//TH2 *h7_3 = new TH2D("h7_3","t05:t07+Cut",500,0,2100,500,0,2100);
//TH2 *h8_3 = new TH2D("h8_3","t04:t07+Cut",500,0,2100,500,0,2100);
//TH2 *h9_3 = new TH2D("h9_3","t05:t06+Cut",500,0,2100,500,0,2100);



//h2 = new TProfile2D("h2","h2",40,-4,4,40,-4,4,0,20);


TCut cut_time = "t04>400.0&&t05>400.0&&t06>400.0&&t07>400.0&&t04<1500.0&&t05<1500.0&&t06<1500.0&&t07<1500.0";
TCut cut_aplitude = "b04>50.0&&b05>50.0&&b06>50.0&&b07>50.0&&b04<2100.0&&b05<2100.0&&b06<2100.0&&b07<2100.0&&b08>90.0&&b08<1800.0";
//TCut cut_aplitude = "b04<1980.0&&b05<1980.0&&b06<1980.0&&b07<1980.0&&b08>80.0&&b08<1800.0";
TCut cut_bt04 = "(t04-500.0)*(b04-50.0)>36000.0&&(t04-850.0)*(b04-300.0)<36000.0";
TCut cut_bt05 = "(t05-520.0)*(b05-50.0)>36000.0&&(t05-820.0)*(b05-300.0)<36000.0";
TCut cut_bt06 = "(t06-520.0)*(b06-50.0)>36000.0&&(t06-900.0)*(b06-350.0)<36000.0";
TCut cut_bt07 = "(t07-520.0)*(b07-50.0)>36000.0&&(t07-950.0)*(b07-350.0)<36000.0";


//TCut cut_time = "";
//TCut cut_aplitude = "";
//TCut cut_bt04 = "";
//TCut cut_bt05 = "";
//TCut cut_bt06 = "";
//TCut cut_bt07 = "";


TCut cut_b_interval_1 = "b04<500.0&&b05<500.0&&b06<500.0&&b07<500.0";

TCut cut_b_interval_2 = "b04>500.0&&b05>500.0&&b06>500.0&&b07>500.0&&b04<1000.0&&b05<1000.0&&b06<1000.0&&b07<1000.0";

TCut cut_b_interval_3 = "b04>1000.0&&b05>1000.0&&b06>1000.0&&b07>1000.0&&b04<1500.0&&b05<1500.0&&b06<1500.0&&b07<1500.0";

TCut cut_b_interval_4 = "b04>1500.0&&b05>1500.0&&b06>1500.0&&b07>1500.0&&b04<2000.0&&b05<2000.0&&b06<2000.0&&b07<2000.0";


TCut cut_b_interval_1_SiPM04 = "b04<500.0";

TCut cut_b_interval_2_SiPM04 = "b04>500.0&&b04<1000.0";

TCut cut_b_interval_3_SiPM04 = "b04>1000.0&&b04<1500.0";

TCut cut_b_interval_4_SiPM04 = "b04>1500.0&&b04<2000.0";


TCut cut_b_interval_1_SiPM05 = "b05<500.0";

TCut cut_b_interval_2_SiPM05 = "b05>500.0&&b05<1000.0";

TCut cut_b_interval_3_SiPM05 = "b05>1000.0&&b05<1500.0";

TCut cut_b_interval_4_SiPM05 = "b05>1500.0&&b05<2000.0";


TCut cut_b_interval_1_SiPM06 = "b06<500.0";

TCut cut_b_interval_2_SiPM06 = "b06>500.0&&b06<1000.0";

TCut cut_b_interval_3_SiPM06 = "b06>1000.0&&b06<1500.0";

TCut cut_b_interval_4_SiPM06 = "b06>1500.0&&b06<2000.0";


TCut cut_b_interval_1_SiPM07 = "b07<500.0";

TCut cut_b_interval_2_SiPM07 = "b07>500.0&&b07<1000.0";

TCut cut_b_interval_3_SiPM07 = "b07>1000.0&&b07<1500.0";

TCut cut_b_interval_4_SiPM07 = "b07>1500.0&&b07<2000.0";




ntpl->Draw("t04+t05-(t06+t07)+275.0>>h1_time",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07);

ntpl->Draw("(t04-delta_t04(b04))+(t05-delta_t05(b05))-((t06-delta_t06(b06))+(t07-delta_t07(b07)))+275.0>>h1_time_delta",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07);

//ntpl->Draw("(t04-delta_t04(b04))+(t05-delta_t05(b05))-((t06-delta_t06(b06))+(t07-delta_t07(b07)))+275.0>>h1_time_delta_1",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_b_interval_1);

//ntpl->Draw("(t04-delta_t04(b04))+(t05-delta_t05(b05))-((t06-delta_t06(b06))+(t07-delta_t07(b07)))+275.0>>h1_time_delta_2",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_b_interval_2);

//ntpl->Draw("(t04-delta_t04(b04))+(t05-delta_t05(b05))-((t06-delta_t06(b06))+(t07-delta_t07(b07)))+275.0>>h1_time_delta_3",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_b_interval_3);

//ntpl->Draw("(t04-delta_t04(b04))+(t05-delta_t05(b05))-((t06-delta_t06(b06))+(t07-delta_t07(b07)))+275.0>>h1_time_delta_4",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_b_interval_4);


//ntpl->Draw("t04-delta_t04(b04)>>h1_1",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07);
//ntpl->Draw("t05-delta_t05(b05)>>h1_2",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07);
//ntpl->Draw("t06-delta_t06(b06)>>h1_3",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07);
//ntpl->Draw("t07-delta_t07(b07)>>h1_4",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07);


ntpl->Draw("t04-delta_t04(b04)>>h1_time_SiPM04_delta_1",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_b_interval_1_SiPM04);
ntpl->Draw("t04-delta_t04(b04)>>h1_time_SiPM04_delta_2",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_b_interval_2_SiPM04);
ntpl->Draw("t04-delta_t04(b04)>>h1_time_SiPM04_delta_3",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_b_interval_3_SiPM04);
ntpl->Draw("t04-delta_t04(b04)>>h1_time_SiPM04_delta_4",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_b_interval_4_SiPM04);


ntpl->Draw("t05-delta_t05(b05)>>h1_time_SiPM05_delta_1",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_b_interval_1_SiPM05);
ntpl->Draw("t05-delta_t05(b05)>>h1_time_SiPM05_delta_2",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_b_interval_2_SiPM05);
ntpl->Draw("t05-delta_t05(b05)>>h1_time_SiPM05_delta_3",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_b_interval_3_SiPM05);
ntpl->Draw("t05-delta_t05(b05)>>h1_time_SiPM05_delta_4",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_b_interval_4_SiPM05);


ntpl->Draw("t06-delta_t06(b06)>>h1_time_SiPM06_delta_1",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_b_interval_1_SiPM06);
ntpl->Draw("t06-delta_t06(b06)>>h1_time_SiPM06_delta_2",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_b_interval_2_SiPM06);
ntpl->Draw("t06-delta_t06(b06)>>h1_time_SiPM06_delta_3",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_b_interval_3_SiPM06);
ntpl->Draw("t06-delta_t06(b06)>>h1_time_SiPM06_delta_4",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_b_interval_4_SiPM06);


ntpl->Draw("t07-delta_t07(b07)>>h1_time_SiPM07_delta_1",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_b_interval_1_SiPM07);
ntpl->Draw("t07-delta_t07(b07)>>h1_time_SiPM07_delta_2",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_b_interval_2_SiPM07);
ntpl->Draw("t07-delta_t07(b07)>>h1_time_SiPM07_delta_3",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_b_interval_3_SiPM07);
ntpl->Draw("t07-delta_t07(b07)>>h1_time_SiPM07_delta_4",cut_time&&cut_aplitude&&cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_b_interval_4_SiPM07);



ntpl->Draw("b04:b05>>h4", cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_time&&cut_aplitude);
ntpl->Draw("b06:b07>>h5", cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_time&&cut_aplitude);
//ntpl->Draw("b04:b06>>h6", cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_time&&cut_aplitude);
//ntpl->Draw("b05:b07>>h7", cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_time&&cut_aplitude);
//ntpl->Draw("b04:b07>>h8", cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_time&&cut_aplitude);
//ntpl->Draw("b05:b06>>h9", cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_time&&cut_aplitude);

ntpl->Draw("b04:b05>>h4_");
ntpl->Draw("b06:b07>>h5_");
//ntpl->Draw("b04:b06>>h6_");
//ntpl->Draw("b05:b07>>h7_");
//ntpl->Draw("b04:b07>>h8_");
//ntpl->Draw("b05:b06>>h9_");



ntpl->Draw("t04:t05>>h4_2", cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_time&&cut_aplitude);
ntpl->Draw("t06:t07>>h5_2", cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_time&&cut_aplitude);
//ntpl->Draw("t04:t06>>h6_2", cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_time&&cut_aplitude);
//ntpl->Draw("t05:t07>>h7_2", cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_time&&cut_aplitude);
//ntpl->Draw("t04:t07>>h8_2", cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_time&&cut_aplitude);
//ntpl->Draw("t05:t06>>h9_2", cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_time&&cut_aplitude);



ntpl->Draw("t04:t05>>h4_3");
ntpl->Draw("t06:t07>>h5_3");
//ntpl->Draw("t04:t06>>h6_3");
//ntpl->Draw("t05:t07>>h7_3");
//ntpl->Draw("t04:t07>>h8_3");
//ntpl->Draw("t05:t06>>h9_3");



MyC->Divide(4,4);
MyC->cd(1);

gStyle->SetOptFit(1111);
h1_time->Fit("gaus", "","", -200,200);

h1_time->GetXaxis()->SetTitle("Time, channel number");
h1_time->GetYaxis()->SetTitle("Events number");
h1_time->GetXaxis()->CenterTitle();
h1_time->GetYaxis()->CenterTitle();

h1_time->Draw();


MyC->cd(2);

ntpl->Draw("b04:t04>>h2_1");
ntpl->Draw("b04:t04>>h3_1",cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_time&&cut_aplitude);
//ntpl->Draw("b04:t04>>h3",cut_bt04);

h2_1->GetXaxis()->SetTitle("Time, channel number");
h2_1->GetYaxis()->SetTitle("Amplitude, channel number");
h2_1->GetXaxis()->CenterTitle();
h2_1->GetYaxis()->CenterTitle();

h2_1->Draw();
//h3->SetMarkerStyle(5);
h3_1->SetMarkerColor(kRed);
h3_1->Draw("same");

//f04_left->SetMarkerColor(kGreen);
//f04_right->SetMarkerColor(kGreen);

f04_left->Draw("same");
f04_right->Draw("same");

MyC->cd(3);
ntpl->Draw("b05:t05>>h2_2");
ntpl->Draw("b05:t05>>h3_2",cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_time&&cut_aplitude);
//ntpl->Draw("b04:t04>>h3",cut_bt04);

h2_2->GetXaxis()->SetTitle("Time, channel number");
h2_2->GetYaxis()->SetTitle("Amplitude, channel number");
h2_2->GetXaxis()->CenterTitle();
h2_2->GetYaxis()->CenterTitle();

h2_2->Draw();
//h3->SetMarkerStyle(5);
h3_2->SetMarkerColor(kRed);
h3_2->Draw("same");

f05_left->Draw("same");
f05_right->Draw("same");

MyC->cd(4);
ntpl->Draw("b06:t06>>h2_3");
ntpl->Draw("b06:t06>>h3_3",cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_time&&cut_aplitude);
//ntpl->Draw("b04:t04>>h3",cut_bt04);

h2_3->GetXaxis()->SetTitle("Time, channel number");
h2_3->GetYaxis()->SetTitle("Amplitude, channel number");
h2_3->GetXaxis()->CenterTitle();
h2_3->GetYaxis()->CenterTitle();

h2_3->Draw();
//h3->SetMarkerStyle(5);
h3_3->SetMarkerColor(kRed);
h3_3->Draw("same");

f06_left->Draw("same");
f06_right->Draw("same");

MyC->cd(5);
ntpl->Draw("b07:t07>>h2_4");
ntpl->Draw("b07:t07>>h3_4",cut_bt04&&cut_bt05&&cut_bt06&&cut_bt07&&cut_time&&cut_aplitude);
//ntpl->Draw("b04:t04>>h3",cut_bt04);

h2_4->GetXaxis()->SetTitle("Time, channel number");
h2_4->GetYaxis()->SetTitle("Amplitude, channel number");
h2_4->GetXaxis()->CenterTitle();
h2_4->GetYaxis()->CenterTitle();

h2_4->Draw();
//h3->SetMarkerStyle(5);
h3_4->SetMarkerColor(kRed);
h3_4->Draw("same");

f07_left->Draw("same");
f07_right->Draw("same");


MyC->cd(6);


h1_time_delta->GetXaxis()->SetTitle("Time, channel number");
h1_time_delta->GetYaxis()->SetTitle("Events number");
h1_time_delta->GetXaxis()->CenterTitle();
h1_time_delta->GetYaxis()->CenterTitle();

gStyle->SetOptFit(1111);
h1_time_delta->Fit("gaus", "","", -200,200);
h1_time_delta->Draw();

MyC->cd(7);

h4_3->GetXaxis()->SetTitle("Time, channel number");
h4_3->GetYaxis()->SetTitle("Time, channel number");
h4_3->GetXaxis()->CenterTitle();
h4_3->GetYaxis()->CenterTitle();

h4_3->Draw();
//h3->SetMarkerStyle(5);
h4_2->SetMarkerColor(kRed);
h4_2->Draw("same");

MyC->cd(8);

h5_3->GetXaxis()->SetTitle("Time, channel number");
h5_3->GetYaxis()->SetTitle("Time, channel number");
h5_3->GetXaxis()->CenterTitle();
h5_3->GetYaxis()->CenterTitle();

h5_3->Draw();
//h3->SetMarkerStyle(5);
h5_2->SetMarkerColor(kRed);
h5_2->Draw("same");

MyC->cd(9);

h4_->GetXaxis()->SetTitle("Amplitude, channel number");
h4_->GetYaxis()->SetTitle("Amplitude, channel number");
h4_->GetXaxis()->CenterTitle();
h4_->GetYaxis()->CenterTitle();

h4_->Draw();
//h3->SetMarkerStyle(5);
h4->SetMarkerColor(kRed);
h4->Draw("same");

MyC->cd(10);

h5_->GetXaxis()->SetTitle("Amplitude, channel number");
h5_->GetYaxis()->SetTitle("Amplitude, channel number");
h5_->GetXaxis()->CenterTitle();
h5_->GetYaxis()->CenterTitle();

h5_->Draw();
//h3->SetMarkerStyle(5);
h5->SetMarkerColor(kRed);
h5->Draw("same");

/*

MyC->cd(11);

gStyle->SetOptFit(1111);
h1_time_delta_1->Fit("gaus", "","", -200,200);
h1_time_delta_1->Draw();

MyC->cd(12);

gStyle->SetOptFit(1111);
h1_time_delta_2->Fit("gaus", "","", -200,200);
h1_time_delta_2->Draw();


MyC->cd(13);

gStyle->SetOptFit(1111);
h1_time_delta_3->Fit("gaus", "","", -200,200);
h1_time_delta_3->Draw();

MyC->cd(14);

gStyle->SetOptFit(1111);
h1_time_delta_4->Fit("gaus", "","", -200,200);
h1_time_delta_4->Draw();

*/



MyC->cd(11);

gStyle->SetOptFit(1111);
h1_time_SiPM04_delta_1->Fit("gaus", "","", -200,500);
h1_time_SiPM04_delta_1->Draw();

MyC->cd(12);

gStyle->SetOptFit(1111);
h1_time_SiPM04_delta_2->Fit("gaus", "","", -200,500);
h1_time_SiPM04_delta_2->Draw();


MyC->cd(13);

gStyle->SetOptFit(1111);
h1_time_SiPM04_delta_3->Fit("gaus", "","", -200,500);
h1_time_SiPM04_delta_3->Draw();

MyC->cd(14);

gStyle->SetOptFit(1111);
h1_time_SiPM04_delta_4->Fit("gaus", "","", -200,500);
h1_time_SiPM04_delta_4->Draw();




MyC->Update();
//f.Close();
}
