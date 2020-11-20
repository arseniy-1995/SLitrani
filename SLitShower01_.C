{
char* name = "SLitShower01_";
char* listing = "SLitShower01_";
char* upcom = "Electromagnetic shower, 1 crystals with APD";
char* downcom = "Cascade below crystal, starting in TOP";
gROOT->ProcessLine(".x InitSLitrani.C(5,name,listing,upcom,downcom,kFALSE,kTRUE,kFALSE)");
//
// arguments of InitSLitrani:
//
// size     size of main canvas of TwoPadDisplay [ 1 <= size <= 8 ]
// name     name of the produced ROOT file (without ".root")
// listing  name of the listing file (without ".lis")
// upcom    name of the comment appearing on top    left of canvas
// downcom  name of the comment appearing on bottom left of canvas
// otherseq true if one wants an other sequence of random numbers at each new launching
// indebug  true if one wants to run Litrani in debug mode
// WithDate if true, appends date and time to name of root file and name of listing
//
//  Simulation of 2 isotropic PbWO4 crystals having the form of a TGeoBBox, on top of each
// crystal is an APD without thin slice having the form of a smaller TGeoBBox. Between the APD
// and the crystal, there is a slice of glue, having the shape of a TGeoBBox.
//  The whole is surrounded by an aluminium coating. This aluminium wrapping has in consequence
// a shape which is the union of 2 TGeoBBox, slightly bigger than the sum of the crystal and the
// APD. The use of union for defining the aluminium wrapping is necessary in order that no overlap
// occurs and that all 6 faces of the crystal be covered with aluminium, including the part of the
// upper face not covered by the APD. This is by far simpler than painfully defining thin slices
// of aluminium for covering each face of the crystal. A small complication arises because we do
// not want that the wrapping of the APD be made of aluminium, but we require that it be a totally
// absorbing wrapping, named "totabsorbing". For that, we define a TGeoBBox made of "totabsorbing",
// slightly bigger than the APD and containing it and included inside the union shape of aluminium.
// This is a not too complicate way of describing an equipped crystal, using the possibility offered
// by the TGeo geometry of placing shapes inside other shapes, and using union in order to avoid
// extrusion.
//  The 2 crystals with APD and wrapping are contained in the TGeoBBox "TOP", defining the WCS,
// world coordinate system. We generate an electromagnetic shower below the crystal, pointing along
// Oz. We displace the shower from run to run below the 2 crystals, so that it affects first
// mostly crystal 1 and then mostly crystal 2.
//
const char* comTL = "Cascade is an µ+ of 100 Gev";
const Color_t  matVacuumColor = 0;
const Color_t  PbWO4Color = 9;
const Color_t  AluColor = 3;
const Color_t  GlueColor = 49;
const Color_t  TotAbsColor = 1;
const Color_t  SiliciumColor = 2;
const Color_t  CradleColor = 5;
const Double_t IrrA = 0.0; //Value used for A   when irrelevant !
const Double_t IrrZ = 0.0; //Value used for Z   when irrelevant !
const Double_t IrrRho = 0.0; //Value used for Rho when irrelevant !
Int_t mediumindex = 1;
gCleanOut->fMaxInfo = 1000;
Short_t ns = -1;
Bool_t  ok = kFALSE;
/*
while (!ok) {
  cout << "Please choose between:" << endl;
  cout << " - a setup with realistic dimensions [answer 0]" << endl;
  cout << " - a setup easy to see on drawing    [answer 1]" << endl;
  cout << "   your choice: ";
  cin  >> ns;
  ok = (ns==0) || (ns==1);
}
*/
ns = 0;
//____________________________________________________________________________
//____________________________________________________________________________
//
// Building the geometry
//____________________________________________________________________________
//____________________________________________________________________________
//
TGeoManager* geom = new TGeoManager("setup", "SLitShower01_ of new Litrani");
//____________________________________________________________________________
//
// Materials and media
//____________________________________________________________________________
//
// (1) Vacuum for "TOP"
//
//  We define here vacuum as a TGeoMedium, not as a TlitMedium, so that photons cannot
// travel inside it. The cascade can be started in "TOP", but it will not generate
// photons until it reaches the crystals.
//
TGeoMaterial* vacuum_mat = new TGeoMaterial("Vacuum", IrrA, IrrZ, IrrRho);
TGeoMedium* vacuum = new TGeoMedium("Vacuum", mediumindex++, vacuum_mat);
//
// (2) Full pedantic definition of PbWO4!
//
//  By this definition, A,Z and density are defined. They are needed by Litrani ONLY if
// class TLitGamma is used, which is not the case here. We give them here just
// as an example. Radiation length, interaction length and Moliere radius are given
// here, they are needed for generating electromagnetic showers.
//

/*



const Double_t NaI(Tl)_radlen = 0.893;  //radiation length of PbWO4
const Double_t NaI(Tl)_intlen = 19.5;   //interaction length of PbWO4
const Double_t NaI(Tl)_rMoliere = 2.0;    //Moliere radius of PbWO4 in cm
TGeoElementTable* table = gGeoManager->GetElementTable();
TGeoElement* Na = table->FindElement("LEAD");
TGeoElement* I = table->FindElement("IODUM");
TGeoElement* Tl = table->FindElement("THALLIUM");
TGeoMixture* NaI(Tl)_mix = new TGeoMixture("NaI(Tl)", 3, 8.28);
NaI(Tl)_mix->AddElement(Pb, 1);
NaI(Tl)_mix->AddElement(W, 1);
NaI(Tl)_mix->AddElement(O, 1);
NaI(Tl)_mix->SetRadLen(-NaI(Tl)_radlen, NaI(Tl)_intlen);
TLitMedium* NaI(Tl) = new TLitMedium("NaI(Tl)", mediumindex++, NaI(Tl)_mix, kFALSE, 1.0, "AbsorptionLength_PbWO4");
const Double_t ns0 = 1.5861;   //index 0 for the Sellmeier law for PbWO4
const Double_t ns1 = 1.1062;   //index 1 for the Sellmeier law for PbWO4
const Double_t ls1 = 270.63;   //1st resonant wavelength for the Sellmeier law for PbWO4
NaI(Tl)->IsIsotropic(1, ns0, ns1, ls1);
NaI(Tl)->FindSpectrum("Spectrum_PbWO4La");
NaI(Tl)->SetCascades(PbWO4_rMoliere); //only useful when TLitCascade used
NaI(Tl)->SetPhotMev(100.0);


*/

const Double_t PbWO4_radlen = 0.893;  //radiation length of PbWO4
const Double_t PbWO4_intlen = 19.5;   //interaction length of PbWO4
const Double_t PbWO4_rMoliere = 2.0;    //Moliere radius of PbWO4 in cm



TGeoElementTable* table = gGeoManager->GetElementTable();
TGeoElement* Pb = table->FindElement("LEAD");
TGeoElement* W = table->FindElement("TUNGSTEN");
TGeoElement* O = table->FindElement("OXYGEN");
TGeoMixture* pbwo4_mix = new TGeoMixture("PbWO4", 3, 8.28);
pbwo4_mix->AddElement(Pb, 1);
pbwo4_mix->AddElement(W, 1);
pbwo4_mix->AddElement(O, 4);
pbwo4_mix->SetRadLen(-PbWO4_radlen, PbWO4_intlen);
TLitMedium* pbwo4 = new TLitMedium("PbWO4", mediumindex++, pbwo4_mix, kFALSE, 1.0, "AbsorptionLength_PbWO4");
const Double_t ns0 = 1.5861;   //index 0 for the Sellmeier law for PbWO4
const Double_t ns1 = 1.1062;   //index 1 for the Sellmeier law for PbWO4
const Double_t ls1 = 270.63;   //1st resonant wavelength for the Sellmeier law for PbWO4
pbwo4->IsIsotropic(1, ns0, ns1, ls1);
pbwo4->FindSpectrum("Spectrum_PbWO4La");
pbwo4->SetCascades(PbWO4_rMoliere); //only useful when TLitCascade used
pbwo4->SetPhotMev(100.0);
pbwo4->dEdx("DEdx_MusInPbWO4__000", 100.0);


//
// (3) Full pedantic definition of Silicium
//
TGeoElement* Si = table->FindElement("SILICON");
TGeoMaterial* silicium_mat = new TGeoMaterial("Silicium", Si, 2.33);
TLitMedium* silicium = new TLitMedium("Silicium", mediumindex++, silicium_mat, kTRUE, 1.0,
	"AbsorptionLength_Silicium");
silicium->IsIsotropic("RefrIndex_Silicium");




//
//  (4) Definition of medium "glue"    (клей)
//
TGeoMaterial* glue_mat = new TGeoMaterial("Glue", IrrA, IrrZ, IrrRho);
switch (ns) {
case 1:
	TLitMedium * glue = new TLitMedium("Glue", mediumindex++, glue_mat, kFALSE, 1.0, 10.0);
	break;
default:
	TLitMedium* glue = new TLitMedium("Glue", mediumindex++, glue_mat, kFALSE, 1.0,
		"AbsorptionLength_Meltmount1704");
	break;
}
glue->IsIsotropic("RefrIndex_RTV3145");


//____________________________________________________________________________
//
// Wrappings
//____________________________________________________________________________
//
//
//  (6) Definition of "TotAbsorbing": a totally absorbing wrapping
//
TGeoMaterial* totabs_mat = new TGeoMaterial("TotAbsorbing", IrrA, IrrZ, IrrRho);
TLitMedium* totabsorbing = new TLitMedium("TotAbsorbing", mediumindex++, totabs_mat, -1.0);
totabsorbing->SetAsWrapping(0.0, 0.0, 1.0, 1.0, 1.0);
totabsorbing->IsIsotropic(1.0);
//
//  (7) Definition of wrapping medium aluminium
//
const Double_t Air_RefrIndex = 1.0003;   //Refractive index of air
const Double_t aluminium_diffus = 0.01;
const Double_t AluminiumSupplAbs = 0.1;
TGeoMaterial* aluminium_mat = new TGeoMaterial("Aluminium", IrrA, IrrZ, IrrRho);
TLitMedium* aluminium = new TLitMedium("Aluminium", mediumindex++, aluminium_mat, 1.0);
aluminium->SetAsWrapping(aluminium_diffus, "RIndexRev_Aluminium", "IIndexRev_Aluminium", 1.0, AluminiumSupplAbs);
aluminium->IsIsotropic(Air_RefrIndex);
//____________________________________________________________________________
//
// Dimensions
//____________________________________________________________________________
//
//
// Dimensions of crystal
//
const Double_t crys_dx = 4.0 / 2.0;
const Double_t crys_dy = 0.65 / 2.0;
const Double_t crys_dz = 18.0 / 2.0;
//
// Dimensions of APD
//
const Double_t apd_dx = 0.3 / 2.0;
const Double_t apd_dy = 0.3 / 2.0;
const Double_t apd_dz = 0.145 / 2.0;
//
// Dimensions for glue of APD
//
const Double_t glueapd_dx = apd_dx;
const Double_t glueapd_dy = apd_dy;
const Double_t glueapd_dz[2] = { 0.05,0.5 };
//
// Width of wrapping is wid
//
const Double_t wid[2] = { 0.1,0.5 };
Double_t ws2 = 0.5 * wid[ns];
//
// Dimensions of TGEOBBox of alu around crystal "CRYSTALWS"
//
Double_t aluc_dx = crys_dx + wid[ns];
Double_t aluc_dy = crys_dy + wid[ns];
Double_t aluc_dz = crys_dz + wid[ns];
//
// Start position of cascade and step size
//
const Double_t epsz = 0.01;      //To be just inside TOP, not inside alu
const Double_t frspy = 0.4;       //frspy == free space in y between crystals  (рассто€ние между кристаллами)
const Double_t frspz = 1.0;       //frspz == free space in z below crystals


const Double_t stepy = 0.1;       //Cascade is displaced along Oy in steps stepy
const Double_t starty = -0.65 / 2.0;      //Start position of cascade in y
const Double_t endy = 0.65 / 2.0;      //End   position of cascade in y
Double_t startz = -aluc_dz - epsz; //Start position of cascade in z

//startz = 0.0;

Double_t posy = starty;
Double_t arun = (endy - starty) / stepy;
Int_t    nrun = (Int_t)(arun + 0.5);


//
// Dimensions of TGEOBBox of alu around APD and glue of APD [partially] "APDWS"
//
Double_t alua_dx = apd_dx + wid[ns];
Double_t alua_dy = apd_dy + wid[ns];
Double_t alua_dz = apd_dz + glueapd_dz[ns];
//
// Dimensions of TotAbsorbing wrapping around APD and glue of APD
//
Double_t tot_dx = apd_dx + wid[ns];
Double_t tot_dy = apd_dy + wid[ns];
Double_t tot_dz = apd_dz + glueapd_dz[ns] + ws2;
//
// Dimensions of TOP
//
const Double_t top_dx = 2.0;
const Double_t top_dy = 1.0;
Double_t top_dz = wid[ns] + crys_dz + glueapd_dz[ns] + apd_dz + frspz;
//____________________________________________________________________________
//
// Positionning (translations)
//____________________________________________________________________________
//
//  t1 is for positionning the TGeoBBox of aluminium around the TGeoBBox of "totabsorbing" [itself
// around TGeoBBox APD and TGeoBBox of glue of APD] with respect to the TGeoBBox of aluminium around
// crystal [or equivalently, with respect to the composite shape "rev_shape"].
//  t1 is used for the creation of composite shape, so it has to be named and registered by
// a call to RegisterYourself().
//
const Double_t t_alua_crys_z = aluc_dz + alua_dz;
TGeoTranslation* t1_1 = new TGeoTranslation("t1_1", -1.29, 0.0, t_alua_crys_z);
t1_1->RegisterYourself();

TGeoTranslation* t1_2 = new TGeoTranslation("t1_2", -0.43, 0.0, t_alua_crys_z);
t1_2->RegisterYourself();

TGeoTranslation* t1_3 = new TGeoTranslation("t1_3", 0.43, 0.0, t_alua_crys_z);
t1_3->RegisterYourself();

TGeoTranslation* t1_4 = new TGeoTranslation("t1_4", 1.29, 0.0, t_alua_crys_z);
t1_4->RegisterYourself();


TGeoTranslation* t1_5 = new TGeoTranslation("t1_5", -1.29, 0.0, -t_alua_crys_z);
t1_5->RegisterYourself();

TGeoTranslation* t1_6 = new TGeoTranslation("t1_6", -0.43, 0.0, -t_alua_crys_z);
t1_6->RegisterYourself();

TGeoTranslation* t1_7 = new TGeoTranslation("t1_7", 0.43, 0.0, -t_alua_crys_z);
t1_7->RegisterYourself();

TGeoTranslation* t1_8 = new TGeoTranslation("t1_8", 1.29, 0.0, -t_alua_crys_z);
t1_8->RegisterYourself();




//  t3 is for positionning the TGeoBBox of "totabsorbing" around APD and around glue of APD
// with respect to the TGeoBBox of aluminium around crystal [or equivalently, with respect
// to the composite shape "rev_shape"].
//
const Double_t t_tot_crys_z = crys_dz + alua_dz + ws2;
TGeoTranslation* t3_1 = new TGeoTranslation("t3_1", -1.29, 0.0, t_tot_crys_z);
TGeoTranslation* t3_2 = new TGeoTranslation("t3_2", -0.43, 0.0, t_tot_crys_z);
TGeoTranslation* t3_3 = new TGeoTranslation("t3_3", 0.43, 0.0, t_tot_crys_z);
TGeoTranslation* t3_4 = new TGeoTranslation("t3_4", 1.29, 0.0, t_tot_crys_z);

TGeoTranslation* t3_5 = new TGeoTranslation("t3_5", -1.29, 0.0, -t_tot_crys_z);
TGeoTranslation* t3_6 = new TGeoTranslation("t3_6", -0.43, 0.0, -t_tot_crys_z);
TGeoTranslation* t3_7 = new TGeoTranslation("t3_7", 0.43, 0.0, -t_tot_crys_z);
TGeoTranslation* t3_8 = new TGeoTranslation("t3_8", 1.29, 0.0, -t_tot_crys_z);


//  t4 is for positionning the TGeoBBox of APD inside the TGeoBBox of "totabsorbing"
//  around APD and glue of APD "TOT"
//
Double_t t_apd_tot_z = glueapd_dz[ns] - ws2;
TGeoTranslation* t4_1 = new TGeoTranslation("t4_1", 0.0, 0.0, t_apd_tot_z);
TGeoTranslation* t4_2 = new TGeoTranslation("t4_2", 0.0, 0.0, t_apd_tot_z);
TGeoTranslation* t4_3 = new TGeoTranslation("t4_3", 0.0, 0.0, t_apd_tot_z);
TGeoTranslation* t4_4 = new TGeoTranslation("t4_4", 0.0, 0.0, t_apd_tot_z);

TGeoTranslation* t4_5 = new TGeoTranslation("t4_5", 0.0, 0.0, -t_apd_tot_z);
TGeoTranslation* t4_6 = new TGeoTranslation("t4_6", 0.0, 0.0, -t_apd_tot_z);
TGeoTranslation* t4_7 = new TGeoTranslation("t4_7", 0.0, 0.0, -t_apd_tot_z);
TGeoTranslation* t4_8 = new TGeoTranslation("t4_8", 0.0, 0.0, -t_apd_tot_z);


//  t5 is for positionning TGeoBBox of glue of the APD inside the TGeoBBox of "totabsorbing"
//  around APD and glue of APD "TOT"
//

const Double_t t_glueapd_tot_z = -(apd_dz + ws2);
TGeoTranslation* t5_1 = new TGeoTranslation("t5_1", 0.0, 0.0, t_glueapd_tot_z);
TGeoTranslation* t5_2 = new TGeoTranslation("t5_2", 0.0, 0.0, t_glueapd_tot_z);
TGeoTranslation* t5_3 = new TGeoTranslation("t5_3", 0.0, 0.0, t_glueapd_tot_z);
TGeoTranslation* t5_4 = new TGeoTranslation("t5_4", 0.0, 0.0, t_glueapd_tot_z);

TGeoTranslation* t5_5 = new TGeoTranslation("t5_5", 0.0, 0.0, -t_glueapd_tot_z);
TGeoTranslation* t5_6 = new TGeoTranslation("t5_6", 0.0, 0.0, -t_glueapd_tot_z);
TGeoTranslation* t5_7 = new TGeoTranslation("t5_7", 0.0, 0.0, -t_glueapd_tot_z);
TGeoTranslation* t5_8 = new TGeoTranslation("t5_8", 0.0, 0.0, -t_glueapd_tot_z);



//  t6 is for positionning the first instance of the composite shape "REV" at a -y coord.
// inside "TOP"
Double_t t_rev = aluc_dy + 0.5 * frspy;
TGeoTranslation* t6 = new TGeoTranslation("t6", 0.0, -t_rev, 0.0);


//  t7 is for positionning the 2nd instance of the composite shape "REV" at a +y coord.
// inside "TOP"
TGeoTranslation* t7 = new TGeoTranslation("t7", 0.0, t_rev, 0.0);


//____________________________________________________________________________
//
// Volumes and nodes
//____________________________________________________________________________
//
//
// top box containing everything and defining the WCS, world coordinate system
//
TGeoVolume* top = geom->MakeBox("TOP", vacuum, top_dx, top_dy, top_dz);
geom->SetTopVolume(top);


//
// Composite shape aluminium
//
TGeoBBox* revcrys_shape = new TGeoBBox("CRYSTALWS", aluc_dx, aluc_dy, aluc_dz);
TGeoBBox* revapd_shape_1 = new TGeoBBox("APDWS_1", alua_dx, alua_dy, alua_dz);
TGeoBBox* revapd_shape_2 = new TGeoBBox("APDWS_2", alua_dx, alua_dy, alua_dz);

TGeoCompositeShape* rev_shape = new TGeoCompositeShape("REV", "CRYSTALWS+APDWS_1:t1_1+APDWS_1:t1_2+APDWS_1:t1_3+APDWS_1:t1_4+APDWS_2:t1_5+APDWS_2:t1_6+APDWS_2:t1_7+APDWS_2:t1_8");



TGeoVolume* rev = new TGeoVolume("REV", rev_shape, aluminium);



top->AddNode(rev, 1, t6);

//top->AddNode(rev, 2, t7);


//
// TGeoBBox of "totabsorbing" around APD and glue of APD
//
TGeoVolume* tot_1 = geom->MakeBox("TOT_1", totabsorbing, tot_dx, tot_dy, tot_dz);
TGeoVolume* tot_2 = geom->MakeBox("TOT_2", totabsorbing, tot_dx, tot_dy, tot_dz);

rev->AddNode(tot_1, 1, t3_1);
rev->AddNode(tot_1, 1, t3_2);
rev->AddNode(tot_1, 1, t3_3);
rev->AddNode(tot_1, 1, t3_4);

rev->AddNode(tot_2, 1, t3_5);
rev->AddNode(tot_2, 1, t3_6);
rev->AddNode(tot_2, 1, t3_7);
rev->AddNode(tot_2, 1, t3_8);



//
//  TGeoBBox APD of silicium
//
//  Notice that in this example, we have given to 2*apd_dz [which should be the distance from
// cathode to anode of the APD] a totally unrealistic value of 1 cm. Refer to the description of
// method TLitVolume::SetAPD(), where it is explained: 
// - Important notice concerning distance from cathode to anode: the distance
// from cathode to anode for an APD is of the order of 0.01 cm. It does not make sense
// to give for instance to this distance a value of for instance 1 cm. But for
// reasons of appearance of the APD on the drawing of the geometry, the user
// can be tempted to give to the APD a depth much bigger than the true distance
// between cathode and anode. If Litrani finds an unrealistic depth for the APD
// when looking at the geometry of the shape being the APD, then Litrani replaces
// this unrealistic depth by the value of the static variable TLitVolume::fgMaxCatAn
// By default, TLitVolume::fgMaxCatAn is equal to 0.01 cm. The user of Litrani
// can freely change this value from his CINT macro, since TLitVolume::fgMaxCatAn
// is a public variable.


TGeoVolume* apd_1 = geom->MakeBox("APD_1", silicium, apd_dx, apd_dy, apd_dz);
TGeoVolume* apd_2 = geom->MakeBox("APD_2", silicium, apd_dx, apd_dy, apd_dz);

tot_1->AddNode(apd_1, 1, t4_1);
tot_1->AddNode(apd_1, 1, t4_2);
tot_1->AddNode(apd_1, 1, t4_3);
tot_1->AddNode(apd_1, 1, t4_4);

tot_2->AddNode(apd_2, 1, t4_5);
tot_2->AddNode(apd_2, 1, t4_6);
tot_2->AddNode(apd_2, 1, t4_7);
tot_2->AddNode(apd_2, 1, t4_8);


//  apd being a detector, booking of a TLitVolume is necessary. All characteristics of the
// APD will then be given by a call to TLitVolume::SetAPD().
TLitVolume* lit_apd_1 = new TLitVolume(apd_1);
TLitVolume* lit_apd_2 = new TLitVolume(apd_2);
lit_apd_1->SetAPD("GainProfile_CMSAPD", 3);
lit_apd_2->SetAPD("GainProfile_CMSAPD", 3);

//
// TGeoBBox of glue of APD
//

TGeoVolume* glueapd_1 = geom->MakeBox("GlueAPD_1", glue, glueapd_dx, glueapd_dy, glueapd_dz[ns]);
TGeoVolume* glueapd_2 = geom->MakeBox("GlueAPD_2", glue, glueapd_dx, glueapd_dy, glueapd_dz[ns]);

tot_1->AddNode(glueapd_1, 1, t5_1);
tot_1->AddNode(glueapd_1, 1, t5_2);
tot_1->AddNode(glueapd_1, 1, t5_3);
tot_1->AddNode(glueapd_1, 1, t5_4);

tot_2->AddNode(glueapd_2, 1, t5_5);
tot_2->AddNode(glueapd_2, 1, t5_6);
tot_2->AddNode(glueapd_2, 1, t5_7);
tot_2->AddNode(glueapd_2, 1, t5_8);



//
// TGeoBBox crystal made of PbWO4 is centered inside "rev"
//
TGeoVolume* crystal = geom->MakeBox("CRYSTAL", pbwo4, crys_dx, crys_dy, crys_dz);
rev->AddNode(crystal, 1);

//
geom->CloseGeometry();
geom->CheckOverlaps(0.01);
//____________________________________________________________________________
//____________________________________________________________________________
//
// End of Building the geometry
//____________________________________________________________________________
//____________________________________________________________________________
//
//____________________________________________________________________________
//
// Colors and drawing
//____________________________________________________________________________
//


top->SetVisibility(kFALSE);
//top->SetVisibility(kTRUE);
top->SetVisContainers();
top->SetLineColor(1);
top->SetLineWidth(1);


rev->SetLineColor(AluColor);
rev->SetLineWidth(1);


tot_1->SetVisibility(kTRUE);
tot_1->SetLineColor(TotAbsColor);
tot_1->SetLineWidth(1);

tot_2->SetVisibility(kTRUE);
tot_2->SetLineColor(TotAbsColor);
tot_2->SetLineWidth(1);


apd_1->SetVisibility(kTRUE);
apd_1->SetLineColor(SiliciumColor);
apd_1->SetLineWidth(1);

apd_2->SetVisibility(kTRUE);
apd_2->SetLineColor(SiliciumColor);
apd_2->SetLineWidth(1);


glueapd_1->SetVisibility(kTRUE);
glueapd_1->SetLineColor(GlueColor);
glueapd_1->SetLineWidth(1);

glueapd_2->SetVisibility(kTRUE);
glueapd_2->SetLineColor(GlueColor);
glueapd_2->SetLineWidth(1);


crystal->SetVisibility(kTRUE);
crystal->SetLineColor(PbWO4Color);
crystal->SetLineWidth(1);


gGeoManager->SetTopVisible(1);
gGeoManager->SetVisLevel(4);
TLit::Get()->BookCanvas(5);
gTwoPad->SetStateOfPads(Pad1Only);
gTwoPad->SetAllGrey();
gTwoPad->CommentTL(comTL);
// gStyle->SetCanvasPreferGL(kTRUE);
// top->Draw("ogl");
top->Draw("");
//____________________________________________________________________________
//____________________________________________________________________________
//
// Generation of photons
//____________________________________________________________________________
//____________________________________________________________________________
//
//  If inlocal is true, works in LOCAL COORDINATE SYSTEM, using 1st constructor of
// TLitCascade. If false, works in WORLD COORDINATE SYSTEM using the 3rd constructor.
// Both are valid and equivalent. Try both!
//


//Bool_t inlocal = kFALSE;
Bool_t inlocal = kTRUE;
Int_t krun;
TLit::Get()->PrintPeriod(25000);
//TLit::Get()->PrintPeriod(250);

TString path = "/TOP_1";
TVector3 StartCasc(0.0, posy, startz);		// координаты и направление каскада
TVector3 AxisCasc(0.0, 0.0, 1.0);

//TVector3 StartCasc(0.0, 0.0, 0.0);		// координаты и направление каскада
//TVector3 AxisCasc(0.0, 1.0, 0.0);


TLitCascade* casc;
if (inlocal)
casc = new TLitCascade("µ+", "µ+", path.Data(), "PbWO4", -11, 1.0, StartCasc, AxisCasc);		  // 11/-11 электроны/позитроны, 13/-13 мю-/мю+ (не работает), 22 гамма	   // энерги€ в √э¬	   
else
casc = new TLitCascade("µ+", "µ+", "PbWO4", StartCasc, AxisCasc, -11, 1.0);
for (krun=1;krun<=nrun;krun++) {
//for (krun = 1; krun <= 2; krun++) {
	casc->Gen(krun, posy);
	posy += stepy;
	if (krun != nrun) {
		StartCasc.SetXYZ(0.0, posy, startz);
		if (inlocal) casc->NewPosition(path.Data(), StartCasc, AxisCasc);
		else         casc->NewPosition(StartCasc, AxisCasc);
	}
}
gLitGp->SetTitle("position y of cascade");
gLitGp->Summary();
gTwoPad->SetStateOfPads(Pad1AndPad2);
gTwoPad->ChangePad();
gLitGs->DoStat();
TLit::Get()->CloseFiles();
}
