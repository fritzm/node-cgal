#ifndef POLYGON2_H
#define POLYGON2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "napi.h"

#include <vector>

class Polygon2 : public CGALWrapper<Polygon2, Polygon_2>
{
public:

    Polygon2(Napi::CallbackInfo const& info);

    // The name to be used for our JS class.
    static const char *Name;

    // Add our property descriptors (instance and static methods and values) to the list that will
    // be used to define our JS class.  Called indirectly at module load time via the module
    // init function.
    static void AddProperties(Napi::Env env, std::vector<PropertyDescriptor>& properties);

    // Attempt to parse a JS argument into the CGAL object referred to by receiver. Returns true
    // if parse was successful, false otherwise.
    static bool ParseArg(Napi::Env env, Napi::Value arg, Polygon_2& receiver);

    // Convert a CGAL object of the wrapped class to a POD JS object. If precise is set to false,
    // will attempt to render in terms of doubles for coordinates, and may lose precision.
    static Napi::Value ToPOD(Napi::Env env, Polygon_2 const& box, bool precise);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of CGAL::Point_2 methods.
    //

    Napi::Value IsEqual(Napi::CallbackInfo const& info);
    Napi::Value IsSimple(Napi::CallbackInfo const& info);
    Napi::Value IsConvex(Napi::CallbackInfo const& info);
    Napi::Value Orientation(Napi::CallbackInfo const& info);
    Napi::Value OrientedSide(Napi::CallbackInfo const& info);
    Napi::Value BoundedSide(Napi::CallbackInfo const& info);
    Napi::Value Area(Napi::CallbackInfo const& info);
    static Napi::Value Transform(Napi::CallbackInfo const& info);
    Napi::Value Coords(Napi::CallbackInfo const& info);

};

#endif // !defined(POLYGON2_H)
