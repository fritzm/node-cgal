#ifndef ARRANGEMENT2VERTEX_H
#define ARRANGEMENT2VERTEX_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "napi.h"

#include <vector>

class Arrangement2Vertex : public CGALWrapper<Arrangement2Vertex, Arrangement_2::Vertex_handle>
{
public:

    Arrangement2Vertex(Napi::CallbackInfo const& info);

    // The name to be used for our JS class.
    static const char *Name;

    // Add our property descriptors (instance and static methods and values) to the list that will
    // be used to define our JS class. Called indirectly at module load time via the module
    // init function.
    static void AddProperties(Napi::Env env, std::vector<PropertyDescriptor>& properties);

    // Attempt to parse a JS argument into the CGAL object referred to by receiver. Returns true
    // if parse was successful, false otherwise.
    static bool ParseArg(Napi::Env env, Napi::Value arg, Arrangement_2::Vertex_handle& receiver);

    // Convert a CGAL object of the wrapped class to a POD JS object. If precise is set to false,
    // will attempt to render in terms of doubles for coordinates, and may lose precision.
    static Napi::Value ToPOD(Napi::Env env, Arrangement_2::Vertex_handle const& vertex, bool precise=true);

private:

    //
    //----- The following methods will be callable from JS. These will mostly match
    //      the semantics and names of the wrapped CGAL class.
    //

    Napi::Value ToString(Napi::CallbackInfo const& info);
    Napi::Value IsAtOpenBoundary(Napi::CallbackInfo const& info);
    Napi::Value IsIsolated(Napi::CallbackInfo const& info);
    Napi::Value Degree(Napi::CallbackInfo const& info);
    Napi::Value IncidentHalfedges(Napi::CallbackInfo const& info);
    Napi::Value Face(Napi::CallbackInfo const& info);
    Napi::Value Point(Napi::CallbackInfo const& info);
    Napi::Value ParameterSpaceInX(Napi::CallbackInfo const& info);
    Napi::Value ParameterSpaceInY(Napi::CallbackInfo const& info);

};

// Declare missing output stream operator so compiler can expand default ToString template method.
// We won't actually link against this since the method is shadowed above, but it needs to be
// declared to satisfy the compiler.

namespace std {
    ostream &operator<<(ostream &str, const Arrangement_2::Vertex_handle &vertex);
}

#endif // !defined(ARRANGEMENT2VERTEX_H)
