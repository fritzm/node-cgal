#ifndef SEGMENT2_H
#define SEGMENT2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "napi.h"

class Segment2 : public CGALWrapper<Segment2, Segment_2>
{
public:

    Segment2(Napi::CallbackInfo const& info);

    // The name to be used for our JS class.
    static const char *Name;

    // Add our property descriptors (instance and static methods and values) to the list that will
    // be used to define our JS class.  Called indirectly at module load time via the module
    // init function.
    static void AddProperties(std::vector<PropertyDescriptor>& properties);

    // Attempt to parse a JS argument into the CGAL object referred to by receiver. Returns true
    // if parse was successful, false otherwise.
    static bool ParseArg(Napi::Env env, Napi::Value arg, Segment_2& receiver);

    // Convert our wrapped CGAL object to a POD JS object. If precise is set to false,
    // attempt to render in terms of doubles for coordinates, which may lose precision.
    static Napi::Value ToPOD(Napi::Env env, Segment_2 const& segment, bool precise);

private:

    //
    //----- The following methods will be callable from JS. These will mostly match
    //      the semantics and names of the wrapped CGAL class.
    //

    Napi::Value IsHorizontal(Napi::CallbackInfo const& info);
    Napi::Value IsVertical(Napi::CallbackInfo const& info);

};

#endif // !defined(SEGMENT2_H)
