/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "ShellGeometry.hpp"
#include "FatalError.hpp"
#include "Random.hpp"
#include "SpecialFunctions.hpp"

////////////////////////////////////////////////////////////////////

void ShellGeometry::setupSelfBefore()
{
    SpheGeometry::setupSelfBefore();

    // verify property values
    if (_rmax <= _rmin) throw FATALERROR("the outer radius of the shell should be larger than the inner radius");

    // calculate cached values
    _smin = SpecialFunctions::gln(_p-2.0,_rmin);
    _sdiff = SpecialFunctions::gln2(_p-2.0,_rmax,_rmin);
    _A = 0.25/M_PI / _sdiff;
}

//////////////////////////////////////////////////////////////////////

double ShellGeometry::density(double r) const
{
    if (r<_rmin || r>_rmax)
        return 0.0;
    else
        return _A * pow(r,-_p);
}

//////////////////////////////////////////////////////////////////////

double ShellGeometry::randomRadius() const
{
    double X = random()->uniform();
    double s = _smin + X*_sdiff;
    return SpecialFunctions::gexp(_p-2.0,s);
}

//////////////////////////////////////////////////////////////////////

double ShellGeometry::Sigmar() const
{
    return _A * SpecialFunctions::gln2(_p,_rmax,_rmin);
}

//////////////////////////////////////////////////////////////////////
