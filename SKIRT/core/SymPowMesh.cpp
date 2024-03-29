/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "SymPowMesh.hpp"
#include "NR.hpp"

////////////////////////////////////////////////////////////////////

Array SymPowMesh::mesh() const
{
    Array tv;
    if (numBins()>2) NR::buildSymmetricPowerLawGrid(tv, 0.0, 1.0, numBins(), _ratio);
    else NR::buildLinearGrid(tv, 0.0, 1.0, numBins());
    return tv;
}

//////////////////////////////////////////////////////////////////////
