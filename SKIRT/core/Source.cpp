/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "Source.hpp"
#include "Random.hpp"

//////////////////////////////////////////////////////////////////////

void Source::setupSelfBefore()
{
    SimulationItem::setupSelfBefore();

    _random = find<Random>();
}

//////////////////////////////////////////////////////////////////////

void Source::prepareForLaunch(double /*sourceBias*/, size_t /*firstIndex*/, size_t /*numIndices*/)
{
}

//////////////////////////////////////////////////////////////////////
