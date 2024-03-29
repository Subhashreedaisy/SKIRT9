/*//////////////////////////////////////////////////////////////////
////     The SKIRT project -- advanced radiative transfer       ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "PropertyDef.hpp"
#include "PropertyAccessor.hpp"

////////////////////////////////////////////////////////////////////

PropertyDef::PropertyDef(string type, string name, string title)
    : _type(type), _name(name), _title(title)
{
}

////////////////////////////////////////////////////////////////////

PropertyDef::~PropertyDef()
{
}

////////////////////////////////////////////////////////////////////

void PropertyDef::addEnumeration(string name, string title)
{
    _enumNames.push_back(name);
    _enumTitles.push_back(title);
}

////////////////////////////////////////////////////////////////////

void PropertyDef::setAccessor(const PropertyAccessor* accessor)
{
    _accessor.reset(accessor);
}

////////////////////////////////////////////////////////////////////

string PropertyDef::enumTitle(string enumName) const
{
    auto it = std::find(_enumNames.cbegin(), _enumNames.cend(), enumName);
    if (it != _enumNames.cend()) return _enumTitles[it-_enumNames.cbegin()];
    return string();
}

////////////////////////////////////////////////////////////////////

