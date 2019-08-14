#ifndef ARRANGEMENT2FACE_H
#define ARRANGEMENT2FACE_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "napi.h"

#include <vector>

class Arrangement2Face : public CGALWrapper<Arrangement2Face, Arrangement_2::Face_handle>
{
public:

    Arrangement2Face(Napi::CallbackInfo const& info);

    // The name to be used for our JS class.
    static const char *Name;

    // Add our property descriptors (instance and static methods and values) to the list that will
    // be used to define our JS class.  Called indirectly at module load time via the module
    // init function.
    static void AddProperties(Napi::Env env, std::vector<PropertyDescriptor>& properties);

    // Attempt to parse a JS argument into the CGAL object referred to by receiver. Returns true
    // if parse was successful, false otherwise.
    static bool ParseArg(Napi::Env env, Napi::Value arg, Arrangement_2::Face_handle& receiver);

    // Convert a CGAL object of the wrapped class to a POD JS object. If precise is set to false,
    // will attempt to render in terms of doubles for coordinates, and may lose precision.
    static Napi::Value ToPOD(Napi::Env env, Arrangement_2::Face_handle const& face, bool precise=true);

private:

    //
    //----- The following methods will be callable from JS.  These will mostly match
    //      the semantics and names of the wrapped CGAL class.
    //

    Napi::Value ToString(Napi::CallbackInfo const& info);
    Napi::Value IsFictitious(Napi::CallbackInfo const& info);
    Napi::Value IsUnbounded(Napi::CallbackInfo const& info);
    Napi::Value OuterCCB(Napi::CallbackInfo const& info);
    Napi::Value Holes(Napi::CallbackInfo const& info);
    Napi::Value IsolatedVertices(Napi::CallbackInfo const& info);

};

// Declare missing output stream operator so compiler can expand default ToString template method.
// We won't actually link against this since the method is shadowed above, but it needs to be
// declared to satisfy the compiler.

namespace std {
    ostream &operator<<(ostream &str, const Arrangement_2::Face_handle &face);
}

#endif // !defined(ARRANGEMENT2FACE_H)
