#ifndef CURVE2_H
#define CURVE2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "napi.h"

#include <vector>

class Curve2 : public CGALWrapper<Curve2, Curve_2>
{
public:

    Curve2(Napi::CallbackInfo const& info);

    // The name to be used for our JS class.
    static const char *Name;

    // Add our property descriptors (instance and static methods and values) to the list that will
    // be used to define our JS class.  Called indirectly at module load time via the module
    // init function.
    static void AddProperties(std::vector<PropertyDescriptor>& properties);

    // Attempt to parse a JS argument into the CGAL object referred to by receiver. Returns true
    // if parse was successful, false otherwise.
    static bool ParseArg(Napi::Env env, Napi::Value arg, Curve_2& receiver);

    // Convert a CGAL object of the wrapped class to a POD JS object. If precise is set to false,
    // will attempt to render in terms of doubles for coordinates, and may lose precision.
    static Napi::Value ToPOD(Napi::Env env, Curve_2 const& curve, bool precise=true);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of the wrapped CGAL class.
    //

    Napi::Value IsSegment(Napi::CallbackInfo const& info);
    Napi::Value Segment(Napi::CallbackInfo const& info);
    Napi::Value IsRay(Napi::CallbackInfo const& info);
    Napi::Value Ray(Napi::CallbackInfo const& info);
    Napi::Value IsLine(Napi::CallbackInfo const& info);
    Napi::Value Line(Napi::CallbackInfo const& info);
    Napi::Value SupportingLine(Napi::CallbackInfo const& info);
    Napi::Value Source(Napi::CallbackInfo const& info);
    Napi::Value Target(Napi::CallbackInfo const& info);

};

#endif // !defined(CURVE2_H)
