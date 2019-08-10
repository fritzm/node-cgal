#ifndef ARRANGEMENT2HALFEDGE_H
#define ARRANGEMENT2HALFEDGE_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "napi.h"

#include <vector>

class Arrangement2Halfedge : public CGALWrapper<Arrangement2Halfedge, Arrangement_2::Halfedge_handle>
{
public:

    Arrangement2Halfedge(Napi::CallbackInfo const& info);

    // The name to be used for our JS class.
    static const char *Name;

    // Add our property descriptors (instance and static methods and values) to the list that will
    // be used to define our JS class. Called indirectly at module load time via the module
    // init function.
    static void AddProperties(Napi::Env env, std::vector<PropertyDescriptor>& properties);

    // Attempt to parse a JS argument into the CGAL object referred to by receiver. Returns true
    // if parse was successful, false otherwise.
    static bool ParseArg(Napi::Env env, Napi::Value arg, Arrangement_2::Halfedge_handle& receiver);

    // Convert a CGAL object of the wrapped class to a POD JS object. If precise is set to false,
    // will attempt to render in terms of doubles for coordinates, and may lose precision.
    static Napi::Value ToPOD(Napi::Env env, Arrangement_2::Halfedge_handle const& hedge, bool precise=true);

private:

    //
    //----- The following methods will be callable from JS. These will mostly match
    //      the semantics and names of the wrapped CGAL class.
    //

    Napi::Value ToString(Napi::CallbackInfo const& info);
    Napi::Value IsFictitious(Napi::CallbackInfo const& info);
    Napi::Value Source(Napi::CallbackInfo const& info);
    Napi::Value Target(Napi::CallbackInfo const& info);
    Napi::Value Face(Napi::CallbackInfo const& info);
    Napi::Value Twin(Napi::CallbackInfo const& info);
    Napi::Value Prev(Napi::CallbackInfo const& info);
    Napi::Value Next(Napi::CallbackInfo const& info);
    Napi::Value CCB(Napi::CallbackInfo const& info);
    Napi::Value Curve(Napi::CallbackInfo const& info);

};

// Declare missing output stream operator so compiler can expand default ToString template method.
// We won't actually link against this since the method is shadowed above, but it needs to be
// declared to satisfy the compiler.

namespace std {
    ostream &operator<<(ostream &str, const Arrangement_2::Halfedge_handle &halfedge);
}

#endif // !defined(ARRANGEMENT2HALFEDGE_H)
