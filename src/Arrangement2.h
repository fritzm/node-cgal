#ifndef ARRANGEMENT2_H
#define ARRANGEMENT2_H

#include "CGALWrapper.h"
#include "cgal_types.h"
#include "napi.h"

#include <vector>

class Arrangement2 : public CGALWrapper<Arrangement2, Arrangement_2>
{
public:

    Arrangement2(Napi::CallbackInfo const& info);

    // The name to be used for our JS class.
    static const char *Name;

    // Add our property descriptors (instance and static methods and values) to the list that will
    // be used to define our JS class.  Called indirectly at module load time via the module
    // init function.
    static void AddProperties(Napi::Env env, std::vector<PropertyDescriptor>& properties);

    // Attempt to parse a JS argument into the CGAL object referred to by receiver. Returns true
    // if parse was successful, false otherwise.
    static bool ParseArg(Napi::Env env, Napi::Value arg, Arrangement_2& receiver);

    // Convert a CGAL object of the wrapped class to a POD JS object. If precise is set to false,
    // will attempt to render in terms of doubles for coordinates, and may lose precision.
    static Napi::Value ToPOD(Napi::Env env, Arrangement_2 const& arrange, bool precise=true);

private:

    //
    //----- The following methods will be callable from JS. These will mostly match
    //      the semantics and names of the wrapped CGAL class.
    //

    Napi::Value ToString(Napi::CallbackInfo const& info);
    Napi::Value Clear(Napi::CallbackInfo const& info);
    Napi::Value IsEmpty(Napi::CallbackInfo const& info);
    Napi::Value IsValid(Napi::CallbackInfo const& info);
    Napi::Value InsertLines(Napi::CallbackInfo const& info); // deprecated
    Napi::Value Insert(Napi::CallbackInfo const& info);
    Napi::Value NumberOfVertices(Napi::CallbackInfo const& info);
    Napi::Value NumberOfIsolatedVertices(Napi::CallbackInfo const& info);
    Napi::Value Vertices(Napi::CallbackInfo const& info);
    Napi::Value NumberOfVerticesAtInfinity(Napi::CallbackInfo const& info);
    Napi::Value UnboundedFace(Napi::CallbackInfo const& info);
    Napi::Value NumberOfFaces(Napi::CallbackInfo const& info);
    Napi::Value Faces(Napi::CallbackInfo const& info);
    Napi::Value NumberOfUnboundedFaces(Napi::CallbackInfo const& info);
    Napi::Value UnboundedFaces(Napi::CallbackInfo const& info);
    Napi::Value FictitiousFace(Napi::CallbackInfo const& info);
    Napi::Value NumberOfHalfedges(Napi::CallbackInfo const& info);
    Napi::Value Halfedges(Napi::CallbackInfo const& info);
    Napi::Value NumberOfEdges(Napi::CallbackInfo const& info);
    Napi::Value Edges(Napi::CallbackInfo const& info);
    Napi::Value InsertInFaceInterior(Napi::CallbackInfo const& info);
    Napi::Value InsertFromLeftVertex(Napi::CallbackInfo const& info);
    Napi::Value InsertFromRightVertex(Napi::CallbackInfo const& info);
    Napi::Value InsertAtVertices(Napi::CallbackInfo const& info);
    Napi::Value ModifyVertex(Napi::CallbackInfo const& info);
    Napi::Value RemoveIsolatedVertex(Napi::CallbackInfo const& info);
    Napi::Value ModifyEdge(Napi::CallbackInfo const& info);
    Napi::Value SplitEdge(Napi::CallbackInfo const& info);
    Napi::Value MergeEdge(Napi::CallbackInfo const& info);
    Napi::Value RemoveEdge(Napi::CallbackInfo const& info);
    Napi::Value RemoveEdgeAndMerge(Napi::CallbackInfo const& info);

};

#endif // !defined(ARRANGEMENT2_H)
