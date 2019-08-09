#ifndef POLYGONSET2_H
#define POLYGONSET2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "napi.h"

#include <vector>


class PolygonSet2 : public CGALWrapper<PolygonSet2, Polygon_set_2>
{
public:

    PolygonSet2(Napi::CallbackInfo const& info);

    // The name to be used for our JS class.
    static const char *Name;

    // Add our property descriptors (instance and static methods and values) to the list that will
    // be used to define our JS class. Called indirectly at module load time via the module
    // init function.
    static void AddProperties(std::vector<PropertyDescriptor>& properties);

    // Attempt to parse a JS argument into the CGAL object referred to by receiver. Returns true
    // if parse was successful, false otherwise.
    static bool ParseArg(Napi::Env env, Napi::Value arg, Polygon_set_2& receiver);

    // Convert a CGAL object of the wrapped class to a POD JS object. If precise is set to false,
    // will attempt to render in terms of doubles for coordinates, and may lose precision.
    static Napi::Value ToPOD(Napi::Env env, Polygon_set_2 const& polys, bool precise=true);

private:

    //
    //----- The following methods will be callable from JS. These will mostly match
    //      the semantics and names of the wrapped CGAL class.
    //

    Napi::Value PolygonsWithHoles(Napi::CallbackInfo const& info);
    Napi::Value NumPolygonsWithHoles(Napi::CallbackInfo const& info);
    Napi::Value IsEmpty(Napi::CallbackInfo const& info);
    Napi::Value IsPlane(Napi::CallbackInfo const& info);
    // Napi::Value Arrangement(Napi::CallbackInfo const& info);
    Napi::Value Clear(Napi::CallbackInfo const& info);
    Napi::Value Insert(Napi::CallbackInfo const& info);
    Napi::Value Complement(Napi::CallbackInfo const& info);
    Napi::Value Intersection(Napi::CallbackInfo const& info);
    Napi::Value Join(Napi::CallbackInfo const& info);
    Napi::Value Difference(Napi::CallbackInfo const& info);
    Napi::Value SymmetricDifference(Napi::CallbackInfo const& info);
    Napi::Value Intersects(Napi::CallbackInfo const& info);
    // Napi::Value Locate(Napi::CallbackInfo const& info);
    Napi::Value OrientedSide(Napi::CallbackInfo const& info);
    Napi::Value IsValid(Napi::CallbackInfo const& info);

};

namespace std {
    ostream &operator<<(ostream &str, const Polygon_set_2 &pset);
}

#endif // !defined(POLYGONSET2_H)
