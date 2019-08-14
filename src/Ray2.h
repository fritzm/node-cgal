#ifndef RAY2_H
#define RAY2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "napi.h"

#include <vector>

class Ray2 : public CGALWrapper<Ray2, Ray_2>
{
public:

    Ray2(Napi::CallbackInfo const& info);

    // The name to be used for our JS class.
    static const char *Name;

    // Add our property descriptors (instance and static methods and values) to the list that will
    // be used to define our JS class.  Called indirectly at module load time via the module
    // init function.
    static void AddProperties(Napi::Env env, std::vector<PropertyDescriptor>& properties);

    // Attempt to parse a JS argument into the CGAL object referred to by receiver. Returns true
    // if parse was successful, false otherwise.
    static bool ParseArg(Napi::Env env, Napi::Value arg, Ray_2& receiver);

    // Convert a CGAL object of the wrapped class to a POD JS object. If precise is set to false,
    // will attempt to render in terms of doubles for coordinates, and may lose precision.
    static Napi::Value ToPOD(Napi::Env env, Ray_2 const& ray, bool precise=true);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of the wrapped CGAL class.
    //

    Napi::Value IsEqual(Napi::CallbackInfo const& info);
    Napi::Value Source(Napi::CallbackInfo const& info);
    Napi::Value Point(Napi::CallbackInfo const& info);
    Napi::Value Direction(Napi::CallbackInfo const& info);
    Napi::Value ToVector(Napi::CallbackInfo const& info);
    Napi::Value SupportingLine(Napi::CallbackInfo const& info);
    Napi::Value Opposite(Napi::CallbackInfo const& info);
    Napi::Value IsDegenerate(Napi::CallbackInfo const& info);
    Napi::Value IsHorizontal(Napi::CallbackInfo const& info);
    Napi::Value IsVertical(Napi::CallbackInfo const& info);
    Napi::Value HasOn(Napi::CallbackInfo const& info);
    Napi::Value CollinearHasOn(Napi::CallbackInfo const& info);

};

#endif // !defined(SEGMENT2_H)
