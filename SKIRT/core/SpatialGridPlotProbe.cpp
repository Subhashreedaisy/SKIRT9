/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "SpatialGridPlotProbe.hpp"
#include "MediumSystem.hpp"
#include "SpatialGrid.hpp"

////////////////////////////////////////////////////////////////////

void SpatialGridPlotProbe::probeSetup()
{
    // locate the grid (it is OK for the medium system to have no media components)
    auto ms = find<MediumSystem>(false);
    if (ms)
    {
        ms->grid()->writeGridPlotFiles(this);
    }
}

////////////////////////////////////////////////////////////////////
