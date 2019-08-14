#ifndef POLYGONWITHHOLES2_H
#define POLYGONWITHHOLES2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "napi.h"

#include <vector>

class PolygonWithHoles2 : public CGALWrapper<PolygonWithHoles2, Polygon_with_holes_2>
{
public:

    PolygonWithHoles2(Napi::CallbackInfo const& info);

    // The name to be used for our JS class.
    static const char *Name;

    // Add our property descriptors (instance and static methods and values) to the list that will
    // be used to define our JS class. Called indirectly at module load time via the module
    // init function.
    static void AddProperties(Napi::Env env, std::vector<PropertyDescriptor>& properties);

    // Attempt to parse a JS argument into the CGAL object referred to by receiver. Returns true
    // if parse was successful, false otherwise.
    static bool ParseArg(Napi::Env env, Napi::Value arg, Polygon_with_holes_2& receiver);

    // Convert a CGAL object of the wrapped class to a POD JS object. If precise is set to false,
    // will attempt to render in terms of doubles for coordinates, and may lose precision.
    static Napi::Value ToPOD(Napi::Env env, Polygon_with_holes_2 const& poly, bool precise=true);

private:

    //
    //----- The following methods will be callable from JS. These will mostly match
    //      the semantics and names of the wrapped CGAL class.
    //

    Napi::Value IsEqual(Napi::CallbackInfo const& info);
    Napi::Value Outer(Napi::CallbackInfo const& info);
    Napi::Value Holes(Napi::CallbackInfo const& info);
    Napi::Value IsUnbounded(Napi::CallbackInfo const& info);

};

#endif // !defined(POLYGONWITHHOLES2_H)
