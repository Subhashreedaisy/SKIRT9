/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "ConsoleLog.hpp"
#include "System.hpp"

////////////////////////////////////////////////////////////////////

ConsoleLog::ConsoleLog()
{
}

////////////////////////////////////////////////////////////////////

ConsoleLog::ConsoleLog(SimulationItem* parent)
{
    parent->addChild(this);
}

////////////////////////////////////////////////////////////////////

void ConsoleLog::output(string message, Log::Level level)
{
    // !! This cast assumes that the items in both enums are in the same order !!
    System::log(message, static_cast<System::LogLevel>(level));
}

////////////////////////////////////////////////////////////////////
