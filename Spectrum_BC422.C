TSplineFit* Spectrum_BC422(Bool_t todraw = kFALSE,Bool_t infile = kFALSE,Bool_t firstinfile = kFALSE)
//
// Arguments:
//
//  todraw       : true if the fit is to be drawn
//  infile       : true if the fit is to be put in file SplineFitDB.rdb
//  firstinfile  : if true, [BE CAREFUL: RISK OF LOOSING FILE SplineFitDB.rdb ]
//                 delete all fits present in file SplineFitDB.rdb and place
//                 this fit as the first fit in a new file SplineFitDB.rdb
//                 default false !!!
// All defaults for arguments correspond to the case where one calls this CINT
//macro from within a Litrani CINT macro to define a needed fit, instead of trying
//to find it in the database file SplineFitDB.rdb using TSplineFit::FindFit()
//
//  Spectrum_BC422.C
//
//  Description :
//
//  spectrum of BC422 doped with Niobium
//
//  Source : CMS ECAL Calorimeter TDR
//
{
Int_t k1;
Int_t k2 = -100;
k1 = TClassTable::GetID("TSplineFit");
if (k1<0) k2 = gSystem.Load("libSplineFit");
const Int_t M = 87;
const Int_t m = 8;
const Double_t zero  = 0.0;
const Double_t z05   = 0.5;
const Double_t Nphot = 1.0e+6;
Int_t i;
Double_t x[M]= { 346.5000458,  347.7567078,  348.856287,  350.2700318,  351.5266938,  352.7833558,  353.7258523,  354.6683488,  355.9250108,  356.5533418,
                 357.4958383,  358.1241693,  358.752500,  360.0091623,  360.7945760,  361.5799898,  362.3654035,  363.3079000,  363.7791483,  364.8787275,
                 365.3499758,  366.2924723,  367.077886,  368.1774653,  369.1199618,  369.7482928,  370.6907893,  371.6332858,  372.5757823,  373.9895270,
                 375.5603545,  376.8170165,  378.230761,  379.6445060,  381.0582508,  382.3149128,  383.5715748,  384.9853195,  386.2419815,  387.8128090,
                 389.2265538,  390.4832158,  391.896960,  393.1536225,  394.4102845,  395.6669465,  397.2377740,  398.9656843,  400.3794290,  401.9502565,
                 403.2069185,  404.7777460,  406.191490,  407.4481528,  408.5477320,  409.9614768,  411.2181388,  412.6318835,  414.3597938,  416.4018695,
                 418.2868625,  420.4860210,  421.899765,  423.4705933,  424.8843380,  426.1410000,  427.3976620,  428.6543240,  429.7539033,  431.3247308,
                 433.5238893,  434.9376340,  436.194296,  437.6080408,  439.3359510,  440.9067785,  442.4776060,  444.2055163,  445.7763438,  447.5042540,
                 448.7609160,  450.1746608,  452.059653,  453.7875640,  455.5154743,  457.0863018,  458.5000465 };
Double_t y[M]= { 0.801282051,  3.525641026,  6.41025641,  10.41666667,  14.58333333,  19.23076923,  23.07692308,  27.88461538,  31.41025641,  34.61538462,
                 37.82051282,  40.86538462,  44.2307692,  47.91666667,  51.12179487,  54.16666667,  57.69230769,  61.21794872,  64.26282051,  67.14743590,
                 69.87179487,  73.23717949,  76.6025641,  80.28846154,  83.81410256,  87.82051282,  91.34615385,  93.91025641,  96.31410256,  98.55769231,
                 100.0000000,  100.0000000,  98.2371794,  96.63461538,  94.07051282,  91.50641026,  88.94230769,  86.53846154,  84.45512821,  82.53205128,
                 80.12820513,  77.88461538,  75.4807692,  73.55769231,  71.95512821,  70.03205128,  67.46794872,  64.90384615,  62.82051282,  60.73717949,
                 58.65384615,  56.73076923,  55.1282051,  52.72435897,  51.12179487,  49.51923077,  47.27564103,  45.67307692,  43.10897436,  40.54487179,
                 37.66025641,  35.41666667,  33.3333333,  31.57051282,  29.96794872,  27.88461538,  26.28205128,  25.16025641,  23.55769231,  22.11538462,
                 20.03205128,  17.94871795,  16.5064102,  15.22435897,  13.94230769,  12.50000000,  11.05769231,  9.615384615,  8.012820513,  7.051282051,
                 6.250000000,  4.807692308,  3.68589743,  2.083333333,  1.121794872,  0.160256410,  0.000000000 };
Double_t s[M];
for (i=0;i<M;i++) s[i] = 0.01;
//
//     Normalization of the spectrum
//
// We normalize y[i] and s[i] in such a way that the surface under the curve be equal to Nphot,
//i.e coresponds to Nphot photons. This is not necessary, but it is a nice feature when we will
//be at the stage of representing the curve as a sum of gaussians.
//
Double_t S = zero;
for (i=0;i<M-1;i++) {
  S += z05*(x[i+1] - x[i])*(y[i] + y[i+1]);
}
cout << "Old Surface: " << S << endl;
for (i=0;i<M;i++) {
  y[i] *= Nphot/S;
  s[i] *= Nphot/S;
}
S = zero;
for (i=0;i<M-1;i++) {
  S += z05*(x[i+1] - x[i])*(y[i] + y[i+1]);
}
cout << "New Surface: " << S    << endl;
cout << "New error  : " << s[0] << endl;
SpecBC422 = new TSplineFit("Spectrum_BC422","Emission Spectrum | Lead tungstate BC422 doped with niobium",16,M,m,x,y,s,kTRUE,0.0,kFALSE,0.0,346.5,458.5,kFALSE);
SpecBC422->SetSource("CMS ECAL Calorimeter TDR");
SpecBC422->SetMacro("Spectrum_BC422.C");
SpecBC422->SetXLabel("wavelength [nm]");
SpecBC422->SetVLabel("Intensity");
  if (todraw) {
    SpecBC422->SetDefaultLabels();
    SpecBC422->DrawFit();
    SpecBC422->Print();
  }
  if (infile) {
    if (firstinfile) SpecBC422->UpdateFile(kTRUE);
    else             SpecBC422->UpdateFile(kFALSE);
  }
  return SpecBC422;
}
