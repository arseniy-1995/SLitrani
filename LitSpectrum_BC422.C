TLitSpectrum* LitSpectrum_BC422(Bool_t todraw = kFALSE,Bool_t infile = kFALSE,Bool_t firstinfile = kFALSE)
{
//
// This macro has been produced using the file "Spectrum.C" produced by the macro
//"GaussDecomp_PbWO4Nb.C", introducing later on the decay times components
//
  char c;
  Bool_t ok;
  TLitSpectrum *sp;
  sp = new TLitSpectrum("Spectrum_BC422","Emission Spectrum | Lead tungstate PbWO4 doped with niobium");
  sp->AddOneComponent(384.869,22.8501,1000000.0, 1.6,0.35,1.0);
  sp->Normalize();
  sp->SetMacro("LitSpectrum_BC422.C");
  sp->fComment[0] = "Although PbWO4 is said to have 2 emission bands, one at 420 nm";
  sp->fComment[1] = "and the other at 500 nm, we have found that the global emission";
  sp->fComment[2] = "spectrum cannot be fitted well with only 2 gaussians. So we have";
  sp->fComment[3] = "made a fit with 4 gaussians, the 1st 2 peaks with mean values fixed";
  sp->fComment[4] = "at 420 and 500 nm, the other 2 auxiliary peaks having free mean";
  sp->fComment[5] = "values adjusted by the fit";
  if (todraw) {
    if (!gTwoPad) {
      gLit = new TLitGlob(5);
      gLit->BookCanvas();
    }
    sp->DrawDecayTimes();
    sp->DrawSpectrum();
    sp->Print();
  }
  if (infile) {
    if (firstinfile) sp->UpdateFile(kTRUE);
    else             sp->UpdateFile(kFALSE);
  }
  return sp;
}
