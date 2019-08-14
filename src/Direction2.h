#ifndef DIRECTION2_H
#define DIRECTION2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "napi.h"

#include <vector>

class Direction2 : public CGALWrapper<Direction2, Direction_2>
{
public:

    Direction2(Napi::CallbackInfo const& info);

    // The name to be used for our JS class.
    static const char *Name;

    // Add our property descriptors (instance and static methods and values) to the list that will
    // be used to define our JS class.  Called indirectly at module load time via the module
    // init function.
    static void AddProperties(Napi::Env env, std::vector<PropertyDescriptor>& properties);

    // Attempt to parse a JS argument into the CGAL object referred to by receiver. Returns true
    // if parse was successful, false otherwise.
    static bool ParseArg(Napi::Env env, Napi::Value arg, Direction_2& receiver);

    // Convert a CGAL object of the wrapped class to a POD JS object. If precise is set to false,
    // will attempt to render in terms of doubles for coordinates, and may lose precision.
    static Napi::Value ToPOD(Napi::Env env, Direction_2 const& direction, bool precise=true);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of the wrapped CGAL class.
    //

    Napi::Value IsEqual(Napi::CallbackInfo const& info);
    Napi::Value IsLessThan(Napi::CallbackInfo const& info);
    Napi::Value IsGreaterThan(Napi::CallbackInfo const& info);
    Napi::Value IsCCWBetween(Napi::CallbackInfo const& info);
    Napi::Value Opposite(Napi::CallbackInfo const& info);
    Napi::Value ToVector(Napi::CallbackInfo const& info);
    Napi::Value DX(Napi::CallbackInfo const& info);
    Napi::Value DY(Napi::CallbackInfo const& info);

};

#endif // !defined(DIRECTION2_H)
