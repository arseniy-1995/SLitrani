{
  char *name    = "SLitBeam01_";
  char *listing = "SLitBeam01_";
  char *upcom   = "Beam of muons, crystal and APD";
  char *downcom = "Simple example with beam issued from an ellipse";
  gROOT->ProcessLine(".x InitSLitrani.C(5,name,listing,upcom,downcom,kTRUE,kTRUE,kFALSE)");
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
  //  Simulation of an isotropic BC-422 crystal having the form of a TGeoBBox, on top of which
  // is an APD without thin slice having the form of a smaller TGeoBBox. Between the APD and the
  // crystal, there is a slice of glue, having the shape of a TGeoBBox.
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
  //  Everything is contained in the TGeoBBox "TOP", defining the WCS, world coordinate system. Notice
  // that the second argument of AddNode(), the copy nb, is always 1 in this example, since it never
  // happens in this example that the same volume is inserted twice inside some mother volume.
  //  To describe the beam of muons, which is intended to be issued from an ellipse, we place inside
  // TOP a TGeoEltu, an elliptical tube, named "BEAMCRADLE" at the left of the crystal. We rotate it
  // by 90° around the Ox axis, so that the elliptical face of the TGeoEltu points towards the crystal.
  // We displace the TGeoEltu from run to run along the Oz direction, to study the dependence of the
  // efficiency versus the z position of the ellipse emitting muons.
  //  Notice that the TGeoEltu "BEAMCRADLE" is displaced AFTER the geometry has been closed by a
  // call to gGeoManager->CloseGeometry()! To understand how it is possible [calling
  // TGeoVolume::RemoveNode() and TGeoVolume::AddNode() after having closed the geometry is
  // forbidden], read § "Representing Misalignments of the Ideal Geometry", p340 of the ROOT
  // user manual. Method TLitBeam::MoveCradle() do the trick.
  //
  const char *comTL = "Beam cradle is a TGeoEltu";
  const Color_t  matVacuumColor =  0;
  const Color_t  matAirColor = 0;
  const Color_t  BC_422Color     =  9;
  const Color_t  AluColor       =  3;
  const Color_t  GlueColor      = 49;
  const Color_t  TotAbsColor    =  1;
  const Color_t  SiliciumColor  =  2;
  const Color_t  CradleColor    =  5;
  const Double_t IrrA           = 0.0; //Value used for A   when irrelevant !
  const Double_t IrrZ           = 0.0; //Value used for Z   when irrelevant !
  const Double_t IrrRho         = 0.0; //Value used for Rho when irrelevant !
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
  TGeoManager *geom = new TGeoManager("setup","SLitBeam01 of new Litrani");
  //____________________________________________________________________________
  //
  // Materials and media
  //____________________________________________________________________________
  //
  // (1) Vacuum for "TOP"
  //
  //  We define here vacuum as a TGeoMedium, not as a TLitMedium, so that photons cannot
  // travel inside it.
  //
  TGeoMaterial *vacuum_mat = new TGeoMaterial("Vacuum",IrrA,IrrZ,IrrRho);
  TGeoMedium *vacuum = new TGeoMedium("Vacuum",mediumindex++,vacuum_mat);
 

  
  

  
  // (1) Air for "TOP"
 //
 //  We define here air as a TLitMedium. Compton effect and photo-electric
 // effect do occur!
 //
  const Double_t Air_RefrIndex = 1.0003;   //Refractive index of air
  TGeoElementTable* table = gGeoManager->GetElementTable();
  TGeoElement* N = table->FindElement("NITROGEN");
  TGeoElement* O = table->FindElement("OXYGEN");
  TGeoMixture* air_mix = new TGeoMixture("Air", 2, 0.00129);
  air_mix->AddElement(N, 0.7);
  air_mix->AddElement(O, 0.3);
  TLitMedium* air = new TLitMedium("Air", mediumindex++, air_mix, kFALSE, 1.0, 10000.0);
  air->IsIsotropic(Air_RefrIndex);
  gROOT->ProcessLine(".L PhotoEl_Air.C"); //Found in directory FitMacros, not in SplineFitDB.rdb
  TSplineFit* fitPEAir = PhotoEl_Air();
  air->SetXSectnPE(fitPEAir);
  
    
  
  
  //
  // (2) Full pedantic definition of BC-422 сцинтиллятор!
  //
  //  By this definition, A,Z and density are defined. They are needed by Litrani ONLY if
  // class TLitGamma is used, which is not the case here. We give them here just
  // as an example. Radiation length, interaction length and Moliere radius are also given
  // here, although not used. They would be used only with class TLitCascade. As BC-422 emits
  // photons when crossed by a particle, we need the emission spectrum of BC-422, which is
  // "Spectrum_PbWO4La", found in database file SpectraDB.rdb. It was inserted into SpectraDB.rdb
  // using CINT macro Spectrum_PbWO4La.C.
  //
 
  
  

 
  const Double_t BC_422_radlen = 0.893;  //radiation length of BC-422
  const Double_t BC_422_intlen = 19.5;   //interaction length of BC-422
  const Double_t BC_422_rMoliere = 2.0;    //Moliere radius of BC-422 in cm
//  const Double_t nPhotMeV = 0.55*38000;     // =55%
  const Double_t nPhotMeV = 0.55*17400;
  TGeoElementTable* table = gGeoManager->GetElementTable();
  TGeoElement* H = table->FindElement("HYDROGEN");
  TGeoElement* C = table->FindElement("CARBON");
  TGeoMixture* BC_422_mix = new TGeoMixture("BC_422", 2, 1.023);
  BC_422_mix->AddElement(H, 1.102);
  BC_422_mix->AddElement(C, 1.0);
  
 // BC_422_mix->AddElement(H, 10);
 // BC_422_mix->AddElement(C, 9);

  const Double_t Light_Attenuation_Length = 8.0; // см

  BC_422_mix->SetRadLen(-BC_422_radlen, BC_422_intlen);
  TLitMedium* BC_422 = new TLitMedium("BC_422", mediumindex++, BC_422_mix, kFALSE, 1.0, Light_Attenuation_Length);
  const Double_t ns0 = 1.58;   //index 0 for the Sellmeier law for BC-422
  const Double_t ns1 = 1.68;   //index 1 for the Sellmeier law for BC-422
  const Double_t ls1 = 270.63;   //1st resonant wavelength for the Sellmeier law for BC-422
  const Double_t n_ref = 1.58;    // константный показатель преломления

 // BC_422->IsIsotropic(1,ns0,ns1,ls1);      // показатель преломления в соответсвии с законом  Зельмейера
 
  
  
  BC_422->SetPhotMev(nPhotMeV);
  BC_422->SetXSectnPE("PhotoEl_Air"); //Found in SplineFitDB.rdb
  BC_422->dEdx("DEdx_MusInPbWO4__000", 100.0, kTRUE);

  const Double_t decay_time_BC_422 = 1.6; // нс
  const Double_t rise_time_BC_422 = 0.35; // нс
  
  sp = new TLitSpectrum("Spectrum_BC_422", "Emission Spectrum | BC-422");
  sp->AddOneComponent(370.0, 30.0, 1.0, decay_time_BC_422, rise_time_BC_422, 1.0);
  sp->Normalize();
  BC_422->SetLitSpectrum(sp);

  cout << "Z/A H  : " << H->Z() << "    " << H->A() << endl;
  cout << "Z/A C  : " << C->Z() << "    " << C->A() << endl;
  cout << "Z tot  : " << TLitPhys::Get()->GetZ(BC_422) << endl;
  cout << "A tot  : " << TLitPhys::Get()->GetA(BC_422) << endl;

 BC_422->IsIsotropic(n_ref);                // показатель преломления константа
  //BC_422->FindSpectrum("Spectrum_PbWO4La");
 BC_422->SetCascades(BC_422_rMoliere); //only useful when TLitCascade used


  
  /*
  
  
    //
  // (2) Full pedantic definition of PbWO4!
  //
  //  By this definition, A,Z and density are defined. They are needed by Litrani ONLY if
  // class TLitGamma is used, which is not the case here. We give them here just
  // as an example. Radiation length, interaction length and Moliere radius are also given
  // here, although not used. They would be used only with class TLitCascade. As PbWO4 emits
  // photons when crossed by a particle, we need the emission spectrum of PbWO4, which is
  // "Spectrum_PbWO4La", found in database file SpectraDB.rdb. It was inserted into SpectraDB.rdb
  // using CINT macro Spectrum_PbWO4La.C.
  //

  
  
  const Double_t PbWO4_radlen   = 0.893;  //radiation length of PbWO4
  const Double_t PbWO4_intlen   = 19.5;   //interaction length of PbWO4
  const Double_t PbWO4_rMoliere = 2.0;    //Moliere radius of PbWO4 in cm
  const Double_t nPhotMeV = 10000;
  
  TGeoElementTable *table = gGeoManager->GetElementTable();
  TGeoElement *Pb = table->FindElement("LEAD");
  TGeoElement *W  = table->FindElement("TUNGSTEN");
  TGeoElement *O  = table->FindElement("OXYGEN");
  TGeoMixture *pbwo4_mix = new TGeoMixture("PbWO4",3,8.28);
  pbwo4_mix->AddElement(Pb,1);
  pbwo4_mix->AddElement(W,1);
  pbwo4_mix->AddElement(O,4);
  pbwo4_mix->SetRadLen(-PbWO4_radlen,PbWO4_intlen);
  TLitMedium *pbwo4 = new TLitMedium("PbWO4",mediumindex++,pbwo4_mix,kFALSE,1.0,"AbsorptionLength_PbWO4");
  const Double_t ns0 = 1.5861;   //index 0 for the Sellmeier law for PbWO4
  const Double_t ns1 = 1.1062;   //index 1 for the Sellmeier law for PbWO4
  const Double_t ls1 = 270.63;   //1st resonant wavelength for the Sellmeier law for PbWO4
  const Double_t n_ref = 2.0;    // константный показатель преломления
  
 // pbwo4->IsIsotropic(1,ns0,ns1,ls1);      // показатель преломления в соответсвии с законом  Зельмейера
  pbwo4->IsIsotropic(n_ref);                // показатель преломления константа
  pbwo4->FindSpectrum("Spectrum_PbWO4La");
  pbwo4->SetCascades(PbWO4_rMoliere); //only useful when TLitCascade used
  pbwo4->SetPhotMev(nPhotMeV);
  pbwo4->SetXSectnPE("PhotoEl_CaWO4"); //Found in SplineFitDB.rdb
  pbwo4->dEdx("DEdx_MusInPbWO4__000",100.0);
  

cout << "Z/A Pb : " << Pb->Z() << "    " << Pb->A() << endl;
cout << "Z/A W  : " <<  W->Z() << "    " <<  W->A() << endl;
cout << "Z/A O  : " <<  O->Z() << "    " <<  O->A() << endl;
cout << "Z tot  : " << TLitPhys::Get()->GetZ(pbwo4) << endl;
cout << "A tot  : " << TLitPhys::Get()->GetA(pbwo4) << endl;

*/

  /*
  
  

  //
  // (2) Full pedantic definition of CaWO4!
  //
  const Double_t nPhotMeV = 10000;
  TLitSpectrum* sp;
  TGeoElement* Ca = table->FindElement("CALCIUM");
  TGeoElement* W = table->FindElement("TUNGSTEN");
  TGeoMixture* cawo4_mix = new TGeoMixture("CaWO4", 3, 6.06);
  cawo4_mix->AddElement(Ca, 1);
  cawo4_mix->AddElement(W, 1);
  cawo4_mix->AddElement(O, 4);
  TLitMedium* cawo4 = new TLitMedium("CaWO4", mediumindex++, cawo4_mix, kFALSE, 1.0, 100.0);
     
    cout << "Z/A Ca : " << Ca->Z() << "    " << Ca->A() << endl;
    cout << "Z/A W  : " <<  W->Z() << "    " <<  W->A() << endl;
    cout << "Z/A O  : " <<  O->Z() << "    " <<  O->A() << endl;
    cout << "Z tot  : " << TLitPhys::Get()->GetZ(cawo4) << endl;
    cout << "A tot  : " << TLitPhys::Get()->GetA(cawo4) << endl;
    
  cawo4->IsIsotropic(2.0);
  sp = new TLitSpectrum("Spectrum_CaWO4", "Emission Spectrum | CaWO4");
  sp->AddOneComponent(447.0, 25.0, 1.0, 2000.0, -1.0, 0.01, 320000.0, -1.0, 0.99);
  sp->Normalize();
  cawo4->SetLitSpectrum(sp);
  cawo4->SetPhotMev(nPhotMeV);
  cawo4->SetXSectnPE("PhotoEl_CaWO4"); //Found in SplineFitDB.rdb

  */

  
  //
  // (3) Full pedantic definition of Silicium
  //
  TGeoElement *Si = table->FindElement("SILICON");
  TGeoMaterial *silicium_mat = new TGeoMaterial("Silicium",Si,2.33);
  TLitMedium *silicium = new TLitMedium("Silicium",mediumindex++,silicium_mat,kTRUE,1.0,"AbsorptionLength_Silicium");
  silicium->IsIsotropic("RefrIndex_Silicium");
  
  
  
  
  //
  //  (4) Definition of medium "glue"    (клей, оптическая смазка)
  //
  TGeoMaterial *glue_mat = new TGeoMaterial("Glue",IrrA,IrrZ,IrrRho);
  switch (ns) {
  case 1:
    TLitMedium *glue = new TLitMedium("Glue",mediumindex++,glue_mat,kFALSE,1.0,10.0);
    break;
  default:
    TLitMedium *glue = new TLitMedium("Glue",mediumindex++,glue_mat,kFALSE,1.0,"AbsorptionLength_Meltmount1704");
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
  TGeoMaterial *totabs_mat = new TGeoMaterial("TotAbsorbing",IrrA,IrrZ,IrrRho);
  TLitMedium *totabsorbing = new TLitMedium("TotAbsorbing",mediumindex++,totabs_mat,-1.0);
  totabsorbing->SetAsWrapping(0.0,0.0,1.0,1.0,1.0);
  totabsorbing->IsIsotropic(1.0);
 
  
  
  //
  //  (7) Definition of wrapping medium aluminium
  //
  const Double_t Air_RefrIndex     = 1.0003;   //Refractive index of air
  const Double_t aluminium_diffus  = 0.01;
  const Double_t AluminiumSupplAbs = 0.1;
  TGeoMaterial *aluminium_mat = new TGeoMaterial("Aluminium",IrrA,IrrZ,IrrRho);
  TLitMedium *aluminium = new TLitMedium("Aluminium",mediumindex++,aluminium_mat,1.0);
  aluminium->SetAsWrapping(aluminium_diffus,"RIndexRev_Aluminium","IIndexRev_Aluminium",1.0,AluminiumSupplAbs);
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
  // Dimensions of beam cradle of type TGeoEltu inside TOP
  //
  const Double_t crad_dx = 0.1;
  const Double_t crad_dy = 0.1;
  const Double_t crad_dz = 0.2;
  
  
  //
  // Start position of beam cradle and step size
  //
  const Double_t frsp   = 0.5; //frsp == free space
  const Double_t stepz  = 0.5;
  const Double_t starty = -2.0;
  Double_t startz = -crys_dz + frsp;
  Double_t arun  = 2*(crys_dz-frsp)/stepz + 1.0;
  Int_t nrun = (Int_t)arun;
  
  
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
  const Double_t glueapd_dz[2] = {0.05,0.5};
  //
  // Width of wrapping is wid
  //
  const Double_t wid[2] = {0.1,0.5};
  Double_t ws2 = 0.5*wid[ns];
  //
  // Dimensions of TGEOBBox of alu around crystal "CRYSTALWS"
  //
  Double_t aluc_dx = crys_dx + wid[ns];
  Double_t aluc_dy = crys_dy + wid[ns];
  Double_t aluc_dz = crys_dz + wid[ns];
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
  const Double_t top_dx    = 3.0;
  const Double_t top_dy    = 3.0;
  Double_t top_dz = wid[ns] + crys_dz + glueapd_dz[ns] + apd_dz + 1.0;
  
  
  
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

 
  
  
  
  //  ph6 is for the start position of the beam cradle inside TOP
  Double_t phi,theta,psi;
  TGeoRotation r6;
  TEuler euler(90.0,0.0,180.0,90.0);
  euler.GetEulerAngles(phi,theta,psi);
  r6.SetAngles(phi,theta,psi);
  TGeoTranslation t6(0.0,starty,startz);
  TGeoCombiTrans *c6 = new TGeoCombiTrans(t6,r6);
  TGeoHMatrix *ph6 = new TGeoHMatrix(*c6);
  
  
  
  
  //____________________________________________________________________________
  //
  // Volumes and nodes
  //____________________________________________________________________________
  //
  //
  // top box containing everything and defining the WCS, world coordinate system
  //
 // TGeoVolume *top = geom->MakeBox("TOP",vacuum,top_dx,top_dy,top_dz);
  TGeoVolume* top = geom->MakeBox("TOP", air, top_dx, top_dy, top_dz);

  geom->SetTopVolume(top);




  //
  // Composite shape aluminium
  //
  TGeoBBox *revcrys_shape = new TGeoBBox("CRYSTALWS",aluc_dx,aluc_dy,aluc_dz);
 
  TGeoBBox* revapd_shape_1 = new TGeoBBox("APDWS_1", alua_dx, alua_dy, alua_dz);
  TGeoBBox* revapd_shape_2 = new TGeoBBox("APDWS_2", alua_dx, alua_dy, alua_dz);
  TGeoBBox* revapd_shape_3 = new TGeoBBox("APDWS_3", alua_dx, alua_dy, alua_dz);
  TGeoBBox* revapd_shape_4 = new TGeoBBox("APDWS_4", alua_dx, alua_dy, alua_dz);
  
  TGeoBBox* revapd_shape_5 = new TGeoBBox("APDWS_5", alua_dx, alua_dy, alua_dz);
  TGeoBBox* revapd_shape_6 = new TGeoBBox("APDWS_6", alua_dx, alua_dy, alua_dz);
  TGeoBBox* revapd_shape_7 = new TGeoBBox("APDWS_7", alua_dx, alua_dy, alua_dz);
  TGeoBBox* revapd_shape_8 = new TGeoBBox("APDWS_8", alua_dx, alua_dy, alua_dz);


  TGeoCompositeShape* rev_shape = new TGeoCompositeShape("REV", "CRYSTALWS+APDWS_1:t1_1+APDWS_2:t1_2+APDWS_3:t1_3+APDWS_4:t1_4+APDWS_5:t1_5+APDWS_6:t1_6+APDWS_7:t1_7+APDWS_8:t1_8");

  
  TGeoVolume *rev = new TGeoVolume("REV",rev_shape,aluminium);
  top->AddNode(rev,1);
  
  
  
  //
  // TGeoBBox of "totabsorbing" around APD and glue of APD
  //

  TGeoVolume* tot_1 = geom->MakeBox("TOT_1", totabsorbing, tot_dx, tot_dy, tot_dz);
  TGeoVolume* tot_2 = geom->MakeBox("TOT_2", totabsorbing, tot_dx, tot_dy, tot_dz);
  TGeoVolume* tot_3 = geom->MakeBox("TOT_3", totabsorbing, tot_dx, tot_dy, tot_dz);
  TGeoVolume* tot_4 = geom->MakeBox("TOT_4", totabsorbing, tot_dx, tot_dy, tot_dz);
  
  TGeoVolume* tot_5 = geom->MakeBox("TOT_5", totabsorbing, tot_dx, tot_dy, tot_dz);
  TGeoVolume* tot_6 = geom->MakeBox("TOT_6", totabsorbing, tot_dx, tot_dy, tot_dz);
  TGeoVolume* tot_7 = geom->MakeBox("TOT_7", totabsorbing, tot_dx, tot_dy, tot_dz);
  TGeoVolume* tot_8 = geom->MakeBox("TOT_8", totabsorbing, tot_dx, tot_dy, tot_dz);
  


  rev->AddNode(tot_1, 1, t3_1);
  rev->AddNode(tot_2, 1, t3_2);
  rev->AddNode(tot_3, 1, t3_3);
  rev->AddNode(tot_4, 1, t3_4);

  rev->AddNode(tot_5, 1, t3_5);
  rev->AddNode(tot_6, 1, t3_6);
  rev->AddNode(tot_7, 1, t3_7);
  rev->AddNode(tot_8, 1, t3_8);
 
  
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
  TGeoVolume* apd_3 = geom->MakeBox("APD_3", silicium, apd_dx, apd_dy, apd_dz);
  TGeoVolume* apd_4 = geom->MakeBox("APD_4", silicium, apd_dx, apd_dy, apd_dz);
  TGeoVolume* apd_5 = geom->MakeBox("APD_5", silicium, apd_dx, apd_dy, apd_dz);
  TGeoVolume* apd_6 = geom->MakeBox("APD_6", silicium, apd_dx, apd_dy, apd_dz);
  TGeoVolume* apd_7 = geom->MakeBox("APD_7", silicium, apd_dx, apd_dy, apd_dz);
  TGeoVolume* apd_8 = geom->MakeBox("APD_8", silicium, apd_dx, apd_dy, apd_dz);

  tot_1->AddNode(apd_1, 1, t4_1);
  tot_2->AddNode(apd_2, 1, t4_2);
  tot_3->AddNode(apd_3, 1, t4_3);
  tot_4->AddNode(apd_4, 1, t4_4);

  tot_5->AddNode(apd_5, 1, t4_5);
  tot_6->AddNode(apd_6, 1, t4_6);
  tot_7->AddNode(apd_7, 1, t4_7);
  tot_8->AddNode(apd_8, 1, t4_8);
  
  
  
  //  apd being a detector, booking of a TLitVolume is necessary. All characteristics of the
  // APD will then be given by a call to TLitVolume::SetAPD().
 
  
  TLitVolume* lit_apd_1 = new TLitVolume(apd_1);
  TLitVolume* lit_apd_2 = new TLitVolume(apd_2);
  TLitVolume* lit_apd_3 = new TLitVolume(apd_3);
  TLitVolume* lit_apd_4 = new TLitVolume(apd_4);
  
  TLitVolume* lit_apd_5 = new TLitVolume(apd_5);
  TLitVolume* lit_apd_6 = new TLitVolume(apd_6);
  TLitVolume* lit_apd_7 = new TLitVolume(apd_7);
  TLitVolume* lit_apd_8 = new TLitVolume(apd_8);

  lit_apd_1->SetAPD("GainProfile_CMSAPD", 3);
  lit_apd_2->SetAPD("GainProfile_CMSAPD", 3);
  lit_apd_3->SetAPD("GainProfile_CMSAPD", 3);
  lit_apd_4->SetAPD("GainProfile_CMSAPD", 3);
  
  lit_apd_5->SetAPD("GainProfile_CMSAPD", 3);
  lit_apd_6->SetAPD("GainProfile_CMSAPD", 3);
  lit_apd_7->SetAPD("GainProfile_CMSAPD", 3);
  lit_apd_8->SetAPD("GainProfile_CMSAPD", 3);

  //
  // TGeoBBox of glue of APD
  //
 
  TGeoVolume* glueapd_1 = geom->MakeBox("GlueAPD_1", glue, glueapd_dx, glueapd_dy, glueapd_dz[ns]);
  TGeoVolume* glueapd_2 = geom->MakeBox("GlueAPD_2", glue, glueapd_dx, glueapd_dy, glueapd_dz[ns]);
  TGeoVolume* glueapd_3 = geom->MakeBox("GlueAPD_3", glue, glueapd_dx, glueapd_dy, glueapd_dz[ns]);
  TGeoVolume* glueapd_4 = geom->MakeBox("GlueAPD_4", glue, glueapd_dx, glueapd_dy, glueapd_dz[ns]);
  
  TGeoVolume* glueapd_5 = geom->MakeBox("GlueAPD_5", glue, glueapd_dx, glueapd_dy, glueapd_dz[ns]);
  TGeoVolume* glueapd_6 = geom->MakeBox("GlueAPD_6", glue, glueapd_dx, glueapd_dy, glueapd_dz[ns]);
  TGeoVolume* glueapd_7 = geom->MakeBox("GlueAPD_7", glue, glueapd_dx, glueapd_dy, glueapd_dz[ns]);
  TGeoVolume* glueapd_8 = geom->MakeBox("GlueAPD_8", glue, glueapd_dx, glueapd_dy, glueapd_dz[ns]);


  tot_1->AddNode(glueapd_1, 1, t5_1);
  tot_2->AddNode(glueapd_2, 1, t5_2);
  tot_3->AddNode(glueapd_3, 1, t5_3);
  tot_4->AddNode(glueapd_4, 1, t5_4);

  tot_5->AddNode(glueapd_5, 1, t5_5);
  tot_6->AddNode(glueapd_6, 1, t5_6);
  tot_7->AddNode(glueapd_7, 1, t5_7);
  tot_8->AddNode(glueapd_8, 1, t5_8);
 
  
  
  //
  // TGeoBBox crystal made of BC-422 is centered inside "rev"
  //
  TGeoVolume *crystal = geom->MakeBox("CRYSTAL",BC_422,crys_dx,crys_dy,crys_dz);
  rev->AddNode(crystal,1);
  //
  // TGeoEltu beam cradle made of vacuum inside TOP.
  //
  //TGeoVolume *cradle = geom->MakeEltu("BEAMCRADLE",vacuum,crad_dx,crad_dy,crad_dz);
  TGeoVolume* cradle = geom->MakeEltu("BEAMCRADLE", air, crad_dx, crad_dy, crad_dz);

  top->AddNode(cradle,1,ph6);
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

  tot_3->SetVisibility(kTRUE);
  tot_3->SetLineColor(TotAbsColor);
  tot_3->SetLineWidth(1);

  tot_4->SetVisibility(kTRUE);
  tot_4->SetLineColor(TotAbsColor);
  tot_4->SetLineWidth(1);

  tot_5->SetVisibility(kTRUE);
  tot_5->SetLineColor(TotAbsColor);
  tot_5->SetLineWidth(1);

  tot_6->SetVisibility(kTRUE);
  tot_6->SetLineColor(TotAbsColor);
  tot_6->SetLineWidth(1);

  tot_7->SetVisibility(kTRUE);
  tot_7->SetLineColor(TotAbsColor);
  tot_7->SetLineWidth(1);

  tot_8->SetVisibility(kTRUE);
  tot_8->SetLineColor(TotAbsColor);
  tot_8->SetLineWidth(1);


  apd_1->SetVisibility(kTRUE);
  apd_1->SetLineColor(SiliciumColor);
  apd_1->SetLineWidth(1);

  apd_2->SetVisibility(kTRUE);
  apd_2->SetLineColor(SiliciumColor);
  apd_2->SetLineWidth(1);

  apd_3->SetVisibility(kTRUE);
  apd_3->SetLineColor(SiliciumColor);
  apd_3->SetLineWidth(1);

  apd_4->SetVisibility(kTRUE);
  apd_4->SetLineColor(SiliciumColor);
  apd_4->SetLineWidth(1);

  apd_5->SetVisibility(kTRUE);
  apd_5->SetLineColor(SiliciumColor);
  apd_5->SetLineWidth(1);

  apd_6->SetVisibility(kTRUE);
  apd_6->SetLineColor(SiliciumColor);
  apd_6->SetLineWidth(1);

  apd_7->SetVisibility(kTRUE);
  apd_7->SetLineColor(SiliciumColor);
  apd_7->SetLineWidth(1);

  apd_8->SetVisibility(kTRUE);
  apd_8->SetLineColor(SiliciumColor);
  apd_8->SetLineWidth(1);

  glueapd_1->SetVisibility(kTRUE);
  glueapd_1->SetLineColor(GlueColor);
  glueapd_1->SetLineWidth(1);

  glueapd_2->SetVisibility(kTRUE);
  glueapd_2->SetLineColor(GlueColor);
  glueapd_2->SetLineWidth(1);

  glueapd_3->SetVisibility(kTRUE);
  glueapd_3->SetLineColor(GlueColor);
  glueapd_3->SetLineWidth(1);
  
  glueapd_4->SetVisibility(kTRUE);
  glueapd_4->SetLineColor(GlueColor);
  glueapd_4->SetLineWidth(1);

  glueapd_5->SetVisibility(kTRUE);
  glueapd_5->SetLineColor(GlueColor);
  glueapd_5->SetLineWidth(1);

  glueapd_6->SetVisibility(kTRUE);
  glueapd_6->SetLineColor(GlueColor);
  glueapd_6->SetLineWidth(1);

  glueapd_7->SetVisibility(kTRUE);
  glueapd_7->SetLineColor(GlueColor);
  glueapd_7->SetLineWidth(1);

  glueapd_8->SetVisibility(kTRUE);
  glueapd_8->SetLineColor(GlueColor);
  glueapd_8->SetLineWidth(1);

  
  crystal->SetVisibility(kTRUE);
  crystal->SetLineColor(BC_422Color);
  crystal->SetLineWidth(1);
  cradle->SetVisibility(kTRUE);
  cradle->SetLineColor(CradleColor);
  cradle->SetLineWidth(1);
  gGeoManager->SetTopVisible(1);
  gGeoManager->SetVisLevel(4);
  TLit::Get()->BookCanvas(5);
  gTwoPad->SetStateOfPads(Pad1Only);
  gTwoPad->SetAllGrey();
  gTwoPad->CommentTL(comTL);
  //  gStyle->SetCanvasPreferGL(kTRUE);
  // top->Draw("ogl");
  top->Draw("");
 
  
  //____________________________________________________________________________
  //____________________________________________________________________________
  //
  // Generation of photons
  //____________________________________________________________________________
  //____________________________________________________________________________
  //
  //  Notice that the TGeoEltu "BEAMCRADLE" is displaced AFTER the geometry has been closed by a
  // call to gGeoManager->CloseGeometry()! To understand how it is possible [calling
  // TGeoVolume::RemoveNode() and TGeoVolume::AddNode() after having closed the geometry is
  // forbidden!], read § "Representing Misalignments of the Ideal Geometry", p340 of the ROOT
  // user manual.  Method TLitBeam::MoveCradle() do the trick.
  //
  
  Int_t krun;
  
  Double_t m_e = 0.5109989500015; // МэВ
  Double_t E_e = 0.545914; // МэВ
  Double_t p_e = pow(E_e * E_e - m_e * m_e, 1.0 / 2.0);
  
  p_e = E_e;

  //TLitParticle *particle = new TLitParticle(13,gaussian,1.0,0.5,1.5,5.0);      // 11/-11 электроны/позитроны, 13/-13 мю-/мю+ , 22 гамма	   // энергия в ГэВ	
  
  // для Sr-90
  TLitParticle* particle = new TLitParticle(-11, gaussian, p_e/1000.0, p_e * 0.8 / 1000.0, p_e * 1.2 / 1000.0, 5.0);      // 11/-11 электроны/позитроны, 13/-13 мю-/мю+ , 22 гамма	   // энергия в ГэВ	


  TVector3 dir(0.0,0.0,1.0);
  TVector3 dirfce(0.0,0.0,1.0);
  TLitBeam *beam = new TLitBeam("muons","beam of muons","/TOP_1/BEAMCRADLE_1",particle,kTRUE,kFALSE);
  beam->SetEmission(sinuscosinus,5.0,dir,"",kFALSE,0.0,kTRUE,dirfce);
  Double_t xyz[3];
  xyz[0] = 0.0;
  xyz[1] = starty;
  for (krun=1;krun<=nrun;krun++) {
    beam->Gen(krun,6,startz);
    startz += stepz;
    if (krun != nrun) {
      xyz[2] = startz;
      ph6->SetTranslation(xyz);
      beam->MoveCradle(ph6,kTRUE);
    }
  }


  gLitGp->SetTitle("position z along crystal axis");
  gLitGp->Summary();
  gTwoPad->SetStateOfPads(Pad1AndPad2);
  gTwoPad->ChangePad();
  gLitGs->DoStat();
  TLit::Get()->CloseFiles();


}
