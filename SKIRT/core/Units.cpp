/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "Units.hpp"
#include "Constants.hpp"
#include "FatalError.hpp"

////////////////////////////////////////////////////////////////////

bool Units::has(string qty, string unit) const
{
    return _unitDef.has(qty, unit);
}

////////////////////////////////////////////////////////////////////

string Units::unit(string qty) const
{
    return _unitDef.unit(qty, type());
}

////////////////////////////////////////////////////////////////////

double Units::in(std::string qty, std::string unit, double value) const
{
    return _unitDef.in(qty, unit, value);
}

////////////////////////////////////////////////////////////////////

double Units::out(string qty, double value) const
{
    return _unitDef.out(qty, type(), value);
}

////////////////////////////////////////////////////////////////////

string Units::ulength() const
{
    return unit("length");
}

////////////////////////////////////////////////////////////////////

double Units::olength(double x) const
{
    return out("length", x);
}

////////////////////////////////////////////////////////////////////

string Units::udistance() const
{
    return unit("distance");
}

////////////////////////////////////////////////////////////////////

double Units::odistance(double d) const
{
    return out("distance", d);
}

////////////////////////////////////////////////////////////////////

string Units::uwavelength() const
{
    return unit("wavelength");
}

////////////////////////////////////////////////////////////////////

double Units::owavelength(double lambda) const
{
    return out("wavelength", lambda);
}

////////////////////////////////////////////////////////////////////

string Units::ugrainsize() const
{
    return unit("grainsize");
}

////////////////////////////////////////////////////////////////////

double Units::ograinsize(double a) const
{
    return out("grainsize", a);
}

////////////////////////////////////////////////////////////////////

string Units::usection() const
{
    return unit("section");
}

////////////////////////////////////////////////////////////////////

double Units::osection(double C) const
{
    return out("section", C);
}

////////////////////////////////////////////////////////////////////

string Units::uvolume() const
{
    return unit("volume");
}

////////////////////////////////////////////////////////////////////

double Units::ovolume(double V) const
{
    return out("volume", V);
}

////////////////////////////////////////////////////////////////////

string Units::uvelocity() const
{
    return unit("velocity");
}

////////////////////////////////////////////////////////////////////

double Units::ovelocity(double v) const
{
    return out("velocity", v);
}

////////////////////////////////////////////////////////////////////

string Units::umass() const
{
    return unit("mass");
}

////////////////////////////////////////////////////////////////////

double Units::omass(double M) const
{
    return out("mass", M);
}

////////////////////////////////////////////////////////////////////

string Units::ubulkmass() const
{
    return unit("bulkmass");
}

////////////////////////////////////////////////////////////////////

double Units::obulkmass(double mu) const
{
    return out("bulkmass", mu);
}

////////////////////////////////////////////////////////////////////

string Units::ubulkmassdensity() const
{
    return unit("bulkmassdensity");
}

////////////////////////////////////////////////////////////////////

double Units::obulkmassdensity(double rho) const
{
    return out("bulkmassdensity", rho);
}

////////////////////////////////////////////////////////////////////

string Units::umasssurfacedensity() const
{
    return unit("masssurfacedensity");
}

////////////////////////////////////////////////////////////////////

double Units::omasssurfacedensity(double Sigma) const
{
    return out("masssurfacedensity", Sigma);
}

////////////////////////////////////////////////////////////////////

string Units::umassvolumedensity() const
{
    return unit("massvolumedensity");
}

////////////////////////////////////////////////////////////////////

double Units::omassvolumedensity(double rho) const
{
    return out("massvolumedensity", rho);
}

////////////////////////////////////////////////////////////////////

string Units::unumbersurfacedensity() const
{
    return unit("numbersurfacedensity");
}

////////////////////////////////////////////////////////////////////

double Units::onumbersurfacedensity(double N) const
{
    return out("numbersurfacedensity", N);
}

////////////////////////////////////////////////////////////////////

string Units::unumbervolumedensity() const
{
    return unit("numbervolumedensity");
}

////////////////////////////////////////////////////////////////////

double Units::onumbervolumedensity(double n) const
{
    return out("numbervolumedensity", n);
}

////////////////////////////////////////////////////////////////////

string Units::umasscoefficient() const
{
    return unit("masscoefficient");
}

////////////////////////////////////////////////////////////////////

double Units::omasscoefficient(double kappa) const
{
    return out("masscoefficient", kappa);
}

////////////////////////////////////////////////////////////////////

string Units::uenergy() const
{
    return unit("energy");
}

////////////////////////////////////////////////////////////////////

double Units::oenergy(double E) const
{
    return out("energy", E);
}

////////////////////////////////////////////////////////////////////

string Units::ubolluminosity() const
{
    return unit("bolluminosity");
}

////////////////////////////////////////////////////////////////////

double Units::obolluminosity(double L) const
{
    return out("bolluminosity", L);
}

////////////////////////////////////////////////////////////////////

string Units::smonluminosity() const
{
    switch (_fluxOutputStyle)
    {
    case FluxOutputStyle::Wavelength: return "L_lambda";
    case FluxOutputStyle::Frequency:  return "L_nu";
    case FluxOutputStyle::Neutral:    return "lambda*L_lambda";
    }
    return string();
}

////////////////////////////////////////////////////////////////////

string Units::umonluminosity() const
{
    switch (_fluxOutputStyle)
    {
    case FluxOutputStyle::Wavelength: return unit("wavelengthmonluminosity");
    case FluxOutputStyle::Frequency:  return unit("frequencymonluminosity");
    case FluxOutputStyle::Neutral:    return unit("neutralmonluminosity");
    }
    return string();
}

////////////////////////////////////////////////////////////////////

double Units::omonluminosityWavelength(double lambda, double Llambda) const
{
    switch (_fluxOutputStyle)
    {
    case FluxOutputStyle::Wavelength: return out("wavelengthmonluminosity", Llambda);
    case FluxOutputStyle::Frequency:  return out("frequencymonluminosity", lambda*lambda*Llambda/Constants::c());
    case FluxOutputStyle::Neutral:    return out("neutralmonluminosity", lambda*Llambda);
    }
    return 0.;
}

////////////////////////////////////////////////////////////////////

double Units::omonluminosityFrequency(double lambda, double Lnu) const
{
    switch (_fluxOutputStyle)
    {
    case FluxOutputStyle::Wavelength: return out("wavelengthmonluminosity", Lnu*Constants::c()/lambda/lambda);
    case FluxOutputStyle::Frequency:  return out("frequencymonluminosity", Lnu);
    case FluxOutputStyle::Neutral:    return out("neutralmonluminosity", Lnu*Constants::c()/lambda);
    }
    return 0.;
}

////////////////////////////////////////////////////////////////////

string Units::sfluxdensity() const
{
    switch (_fluxOutputStyle)
    {
    case FluxOutputStyle::Wavelength: return "F_lambda";
    case FluxOutputStyle::Frequency:  return "F_nu";
    case FluxOutputStyle::Neutral:    return "lambda*F_lambda";
    }
    return string();
}

////////////////////////////////////////////////////////////////////

string Units::ufluxdensity() const
{
    switch (_fluxOutputStyle)
    {
    case FluxOutputStyle::Wavelength: return unit("wavelengthfluxdensity");
    case FluxOutputStyle::Frequency:  return unit("frequencyfluxdensity");
    case FluxOutputStyle::Neutral:    return unit("neutralfluxdensity");
    }
    return string();
}

////////////////////////////////////////////////////////////////////

double Units::ofluxdensityWavelength(double lambda, double Flambda) const
{
    switch (_fluxOutputStyle)
    {
    case FluxOutputStyle::Wavelength: return out("wavelengthfluxdensity", Flambda);
    case FluxOutputStyle::Frequency:  return out("frequencyfluxdensity", lambda*lambda*Flambda/Constants::c());
    case FluxOutputStyle::Neutral:    return out("neutralfluxdensity", lambda*Flambda);
    }
    return 0.;
}

////////////////////////////////////////////////////////////////////

double Units::ofluxdensityFrequency(double lambda, double Fnu) const
{
    switch (_fluxOutputStyle)
    {
    case FluxOutputStyle::Wavelength: return out("wavelengthfluxdensity", Fnu*Constants::c()/lambda/lambda);
    case FluxOutputStyle::Frequency:  return out("frequencyfluxdensity", Fnu);
    case FluxOutputStyle::Neutral:    return out("neutralfluxdensity", Fnu*Constants::c()/lambda);
    }
    return 0.;
}

////////////////////////////////////////////////////////////////////

string Units::ssurfacebrightness() const
{
    switch (_fluxOutputStyle)
    {
    case FluxOutputStyle::Wavelength: return "f_lambda";
    case FluxOutputStyle::Frequency:  return "f_nu";
    case FluxOutputStyle::Neutral:    return "lambda*f_lambda";
    }
    return string();
}

////////////////////////////////////////////////////////////////////

string Units::usurfacebrightness() const
{
    switch (_fluxOutputStyle)
    {
    case FluxOutputStyle::Wavelength: return unit("wavelengthsurfacebrightness");
    case FluxOutputStyle::Frequency:  return unit("frequencysurfacebrightness");
    case FluxOutputStyle::Neutral:    return unit("neutralsurfacebrightness");
    }
    return string();
}

////////////////////////////////////////////////////////////////////

double Units::osurfacebrightnessWavelength(double lambda, double flambda) const
{
    switch (_fluxOutputStyle)
    {
    case FluxOutputStyle::Wavelength: return out("wavelengthsurfacebrightness", flambda);
    case FluxOutputStyle::Frequency:  return out("frequencysurfacebrightness", lambda*lambda*flambda/Constants::c());
    case FluxOutputStyle::Neutral:    return out("neutralsurfacebrightness", lambda*flambda);
    }
    return 0.;
}

////////////////////////////////////////////////////////////////////

double Units::osurfacebrightnessFrequency(double lambda, double fnu) const
{
    switch (_fluxOutputStyle)
    {
    case FluxOutputStyle::Wavelength: return out("wavelengthsurfacebrightness", fnu*Constants::c()/lambda/lambda);
    case FluxOutputStyle::Frequency:  return out("frequencysurfacebrightness", fnu);
    case FluxOutputStyle::Neutral:    return out("neutralsurfacebrightness", fnu*Constants::c()/lambda);
    }
    return 0.;
}

////////////////////////////////////////////////////////////////////

std::string Units::smeanintensity() const
{
    switch (_fluxOutputStyle)
    {
    case FluxOutputStyle::Wavelength: return "J_lambda";
    case FluxOutputStyle::Frequency:  return "J_nu";
    case FluxOutputStyle::Neutral:    return "lambda*J_lambda";
    }
    return string();
}

////////////////////////////////////////////////////////////////////

std::string Units::umeanintensity() const
{
    switch (_fluxOutputStyle)
    {
    case FluxOutputStyle::Wavelength: return unit("wavelengthmeanintensity");
    case FluxOutputStyle::Frequency:  return unit("frequencymeanintensity");
    case FluxOutputStyle::Neutral:    return unit("neutralmeanintensity");
    }
    return string();
}

////////////////////////////////////////////////////////////////////

double Units::omeanintensityWavelength(double lambda, double Jlambda) const
{
    switch (_fluxOutputStyle)
    {
    case FluxOutputStyle::Wavelength: return out("wavelengthmeanintensity", Jlambda);
    case FluxOutputStyle::Frequency:  return out("frequencymeanintensity", lambda*lambda*Jlambda/Constants::c());
    case FluxOutputStyle::Neutral:    return out("neutralmeanintensity", lambda*Jlambda);
    }
    return 0.;
}

////////////////////////////////////////////////////////////////////

double Units::omeanintensityFrequency(double lambda, double Jnu) const
{
    switch (_fluxOutputStyle)
    {
    case FluxOutputStyle::Wavelength: return out("wavelengthmeanintensity", Jnu*Constants::c()/lambda/lambda);
    case FluxOutputStyle::Frequency:  return out("frequencymeanintensity", Jnu);
    case FluxOutputStyle::Neutral:    return out("neutralmeanintensity", Jnu*Constants::c()/lambda);
    }
    return 0.;
}

////////////////////////////////////////////////////////////////////

string Units::utemperature() const
{
    return unit("temperature");
}

////////////////////////////////////////////////////////////////////

double Units::otemperature(double T) const
{
    return out("temperature", T);
}

////////////////////////////////////////////////////////////////////

string Units::uangle() const
{
    return unit("angle");
}

////////////////////////////////////////////////////////////////////

double Units::oangle(double theta) const
{
    return out("angle", theta);
}

////////////////////////////////////////////////////////////////////

string Units::uposangle() const
{
    return unit("posangle");
}

////////////////////////////////////////////////////////////////////

double Units::oposangle(double theta) const
{
    return out("posangle", theta);
}

////////////////////////////////////////////////////////////////////

string Units::usolidangle() const
{
    return unit("solidangle");
}

////////////////////////////////////////////////////////////////////

double Units::osolidangle(double Omega) const
{
    return out("solidangle", Omega);
}

////////////////////////////////////////////////////////////////////

string Units::upressure() const
{
    return unit("pressure");
}

////////////////////////////////////////////////////////////////////

double Units::opressure(double p) const
{
    return out("pressure", p);
}

////////////////////////////////////////////////////////////////////
