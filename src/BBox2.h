#ifndef BBOX2_H
#define BBOX2_H

#include "CGALWrapper.h"
#include "cgal_types.h"

#include <vector>

class BBox2 : public CGALWrapper<BBox2, Bbox_2>
{
public:

    BBox2(Napi::CallbackInfo const& info);

    static char const* Name;
    static void AddProperties(std::vector<PropertyDescriptor>& properties);

    // Attempt to parse a JS argument into the CGAL object referred to by receiver. Returns true
    // if parse was successful, false otherwise.
    static bool ParseArg(Napi::Env env, Napi::Value arg, Bbox_2& receiver);

    // Convert a CGAL object of the wrapped class to a POD JS object. If precise is set to false,
    // will attempt to render in terms of doubles for coordinates, and may lose precision.
    Napi::Value ToPOD(Napi::Env env, bool precise);

private:

    //
    //----- The following methods will be callable from JS. These will mostly match
    //      the semantics and names of the wrapped CGAL class.
    //

    Napi::Value Overlaps(Napi::CallbackInfo const& info);
    Napi::Value Add(Napi::CallbackInfo const& info);

};

#endif // !defined(BBOX2_H)
