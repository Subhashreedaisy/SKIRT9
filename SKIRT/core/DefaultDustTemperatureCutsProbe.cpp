/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "DefaultDustTemperatureCutsProbe.hpp"
#include "Array.hpp"
#include "Configuration.hpp"
#include "DisjointWavelengthGrid.hpp"
#include "FITSInOut.hpp"
#include "MediumSystem.hpp"
#include "Parallel.hpp"
#include "ParallelFactory.hpp"
#include "SpatialGrid.hpp"
#include "TextOutFile.hpp"
#include "Units.hpp"

////////////////////////////////////////////////////////////////////

// Private class to output a FITS file with the mean dust temperatures
// in one of the coordinate planes (xy, xz, or yz).
namespace
{
    // The image size in each direction, in pixels
    const int Np = 1024;

    class WriteTemperatureCut
    {
    private:
        // cached values initialized in constructor
        Probe* item;
        MediumSystem* ms;
        WavelengthGrid* wavelengthGrid;
        Units* units;
        double xbase, ybase, zbase, xpsize, ypsize, zpsize, xcenter, ycenter, zcenter;

        // data members initialized in setup()
        bool xd, yd, zd;  // direction of coordinate plane (110, 101, 011)
        string plane;    // name of the coordinate plane (xy, xz, yz)

        // results vector, properly resized in constructor
        Array Tv;

    public:
        // constructor
        WriteTemperatureCut(Probe* item_, MediumSystem* ms_)
            : item(item_), ms(ms_),
              wavelengthGrid(ms_->find<Configuration>()->radiationFieldWLG()), units(ms_->find<Units>())
        {
            double xmin, ymin, zmin, xmax, ymax, zmax;
            ms->grid()->boundingBox().extent(xmin,ymin,zmin,xmax,ymax,zmax);
            xpsize = (xmax-xmin)/Np;
            ypsize = (ymax-ymin)/Np;
            zpsize = (zmax-zmin)/Np;
            xbase = xmin + 0.5*xpsize;
            ybase = ymin + 0.5*ypsize;
            zbase = zmin + 0.5*zpsize;
            xcenter = (xmin+xmax)/2.0;
            ycenter = (ymin+ymax)/2.0;
            zcenter = (zmin+zmax)/2.0;

            Tv.resize(Np*Np);
        }

        // setup for calculating a specific coordinate plane
        void setup(bool xdir, bool ydir, bool zdir)
        {
            xd = xdir;
            yd = ydir;
            zd = zdir;
            plane = "";
            if (xd) plane += "x";
            if (yd) plane += "y";
            if (zd) plane += "z";
        }

        // the parallelized loop body; calculates the results for a set of lines in the images
        void body(size_t firstIndex, size_t numIndices)
        {
            for (size_t j = firstIndex; j != firstIndex+numIndices; ++j)
            {
                double z = zd ? (zbase + j*zpsize) : 0.;
                for (int i=0; i<Np; i++)
                {
                    double x = xd ? (xbase + i*xpsize) : 0.;
                    double y = yd ? (ybase + (zd ? i : j)*ypsize) : 0.;
                    int l = i + Np*j;
                    Tv[l] = units->otemperature(ms->indicativeDustTemperature(Position(x,y,z)));
                }
            }
        }

        // Write the results to a FITS file with an appropriate name
        void write()
        {
            string description = "dust temperatures in the " + plane + " plane";
            string filename = item->itemName() + "_dust_T_" + plane;
            FITSInOut::write(item, description, filename, Tv, units->utemperature(), Np, Np,
                             units->olength(xd?xpsize:ypsize), units->olength(zd?zpsize:ypsize),
                             units->olength(xd?xcenter:ycenter), units->olength(zd?zcenter:ycenter),
                             units->ulength());
        }
    };
}

////////////////////////////////////////////////////////////////////

void DefaultDustTemperatureCutsProbe::probeRun()
{
    if (find<Configuration>()->hasPanRadiationField() && find<MediumSystem>()->hasDust())
    {
        // locate the medium system
        auto ms = find<MediumSystem>();

        // configure parallelization; perform only at the root processs
        Parallel* parallel = find<ParallelFactory>()->parallelRootOnly();

        // construct a private class instance to do the work
        WriteTemperatureCut wtc(this, ms);

        // for the xy plane (always)
        {
            wtc.setup(1,1,0);
            parallel->call(Np, [&wtc](size_t i ,size_t n) { wtc.body(i, n); });
            wtc.write();
        }

        // for the xz plane (only if dimension is at least 2)
        int dimension = ms->dimension();
        if (dimension >= 2)
        {
            wtc.setup(1,0,1);
            parallel->call(Np, [&wtc](size_t i ,size_t n) { wtc.body(i, n); });
            wtc.write();
        }

        // for the yz plane (only if dimension is 3)
        if (dimension == 3)
        {
            wtc.setup(0,1,1);
            parallel->call(Np, [&wtc](size_t i ,size_t n) { wtc.body(i, n); });
            wtc.write();
        }

    }
}

////////////////////////////////////////////////////////////////////
