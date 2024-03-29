/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "LaserAngularDistribution.hpp"

//////////////////////////////////////////////////////////////////////

double LaserAngularDistribution::probabilityForInclinationCosine(double costheta) const
{
    return costheta>0.99999 ? std::numeric_limits<double>::infinity() : 0.;
}

//////////////////////////////////////////////////////////////////////

double LaserAngularDistribution::generateInclinationCosine() const
{
    return 1.;
}

//////////////////////////////////////////////////////////////////////
