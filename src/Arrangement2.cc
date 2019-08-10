#include "Arrangement2.h"
#include "Arrangement2Face.h"
#include "Arrangement2Halfedge.h"
#include "Arrangement2Vertex.h"
#include "Line2.h"
#include "Point2.h"
#include "Polygon2.h"
#include "Curve2.h"
#include "cgal_args.h"

using namespace std;


Arrangement2::Arrangement2(Napi::CallbackInfo const& info)
:   CGALWrapper(info)
{
}


char const* Arrangement2::Name = "Arrangement2";


void Arrangement2::AddProperties(Napi::Env env, vector<PropertyDescriptor>& properties)
{
    properties.insert(properties.end(), {
        InstanceMethod("toString", &Arrangement2::ToString),
        InstanceMethod("clear", &Arrangement2::Clear),
        InstanceMethod("isEmpty", &Arrangement2::IsEmpty),
        InstanceMethod("isValid", &Arrangement2::IsValid),
        InstanceMethod("insert", &Arrangement2::Insert),
        InstanceMethod("insertLines", &Arrangement2::InsertLines), // deprecated
        InstanceMethod("numberOfVertices", &Arrangement2::NumberOfVertices),
        InstanceMethod("numberOfIsolatedVertices", &Arrangement2::NumberOfIsolatedVertices),
        InstanceMethod("vertices", &Arrangement2::Vertices),
        InstanceMethod("numberOfVerticesAtInfinity", &Arrangement2::NumberOfVerticesAtInfinity),
        InstanceMethod("unboundedFace", &Arrangement2::UnboundedFace),
        InstanceMethod("numberOfFaces", &Arrangement2::NumberOfFaces),
        InstanceMethod("faces", &Arrangement2::Faces),
        InstanceMethod("numberOfUnboundedFaces", &Arrangement2::NumberOfUnboundedFaces),
        InstanceMethod("unboundedFaces", &Arrangement2::UnboundedFaces),
        InstanceMethod("fictitiousFace", &Arrangement2::FictitiousFace),
        InstanceMethod("numberOfHalfedges", &Arrangement2::NumberOfHalfedges),
        InstanceMethod("halfedges", &Arrangement2::Halfedges),
        InstanceMethod("numberOfEdges", &Arrangement2::NumberOfEdges),
        InstanceMethod("edges", &Arrangement2::Edges),
        InstanceMethod("insertInFaceInterior", &Arrangement2::InsertInFaceInterior),
        InstanceMethod("insertFromLeftVertex", &Arrangement2::InsertFromLeftVertex),
        InstanceMethod("insertFromRightVertex", &Arrangement2::InsertFromRightVertex),
        InstanceMethod("insertAtVertices", &Arrangement2::InsertAtVertices),
        InstanceMethod("modifyVertex", &Arrangement2::ModifyVertex),
        InstanceMethod("removeIsolatedVertex", &Arrangement2::RemoveIsolatedVertex),
        InstanceMethod("modifyEdge", &Arrangement2::ModifyEdge),
        InstanceMethod("splitEdge", &Arrangement2::SplitEdge),
        InstanceMethod("mergeEdge", &Arrangement2::MergeEdge),
        InstanceMethod("removeEdge", &Arrangement2::RemoveEdge),
        InstanceMethod("removeEdgeAndMerge", &Arrangement2::RemoveEdgeAndMerge)
    });

    // Arrangement2Face::Init(constructorTemplate);
    // Arrangement2Halfedge::Init(constructorTemplate);
    // Arrangement2Vertex::Init(constructorTemplate);
}


bool Arrangement2::ParseArg(Napi::Env env, Napi::Value arg, Arrangement_2& receiver)
{
    return false;
}


Napi::Value Arrangement2::ToPOD(Napi::Env env, Arrangement_2 const& arrange, bool precise)
{
    Napi::Object obj = Napi::Object::New(env);

    obj.Set("numFaces",
        Napi::Number::New(env, arrange.number_of_faces()));
    obj.Set("numUnboundedFaces",
        Napi::Number::New(env, arrange.number_of_unbounded_faces()));
    obj.Set("numBoundedFaces",
        Napi::Number::New(env, arrange.number_of_faces()-arrange.number_of_unbounded_faces()));
    obj.Set("numVertices",
        Napi::Number::New(env, arrange.number_of_vertices()));

    Napi::Array faceArray = Napi::Array::New(env);
    obj.Set("boundedFaces", faceArray);
    Arrangement_2::Face_const_iterator fit;
    uint32_t faceNum = 0;
    for(fit = arrange.faces_begin(); fit != arrange.faces_end(); ++fit) {
        if (!fit->is_unbounded()){
            Polygon_2 poly;
            back_insert_iterator<Polygon_2> bit = back_inserter(poly);
            Arrangement_2::Ccb_halfedge_const_circulator circ = fit->outer_ccb();
            Arrangement_2::Ccb_halfedge_const_circulator curr = circ;
            do { 
                *bit++ = curr->source()->point(); 
            } while (++curr != circ);
            faceArray.Set(faceNum, Polygon2::ToPOD(env, poly, precise));
            faceNum++;
        }
    }

    return obj;
}


Napi::Value Arrangement2::ToString(Napi::CallbackInfo const& info)
{
    ostringstream str;
    str << "[object "  << Name << " " << &mWrapped << " ";
    str << "F:" << mWrapped.number_of_faces() << " ";
    str << "V:" << mWrapped.number_of_vertices() << " ";
    str << "E:" << mWrapped.number_of_edges() << "]";
    return Napi::String::New(info.Env(), str.str());
}


Napi::Value Arrangement2::Clear(Napi::CallbackInfo const& info)
{
    mWrapped.clear();
    return info.Env().Undefined();
}


Napi::Value Arrangement2::IsEmpty(Napi::CallbackInfo const& info)
{
    return Napi::Boolean::New(info.Env(), mWrapped.is_empty());
}


Napi::Value Arrangement2::IsValid(Napi::CallbackInfo const& info)
{
    return Napi::Boolean::New(info.Env(), mWrapped.is_valid());
}


Napi::Value Arrangement2::Insert(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);

    if (info[0].IsArray()) {
        vector<Curve_2> curves;
        Curve2::ParseSeqArg(env, info[0], back_inserter(curves));
        insert(mWrapped, curves.begin(), curves.end());
        return env.Undefined();
    }

    Curve_2 curve;
    if (Curve2::ParseArg(env, info[0], curve)) {
        insert(mWrapped, curve);
        return env.Undefined();
    }

    ARGS_ASSERT(env, false);
}


Napi::Value Arrangement2::InsertLines(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);
    ARGS_ASSERT(env, info[0].IsArray());
    Napi::Array lines = info[0].As<Napi::Array>();
    for(uint32_t i=0; i<lines.Length(); ++i) {
        ARGS_PARSE_LOCAL(env, Line2::ParseArg, Line_2, line, lines[i]);
        insert(mWrapped, line);
    }
    return env.Undefined();
}


Napi::Value Arrangement2::NumberOfVertices(Napi::CallbackInfo const& info)
{
    return Napi::Number::New(info.Env(), mWrapped.number_of_vertices());
}


Napi::Value Arrangement2::NumberOfIsolatedVertices(Napi::CallbackInfo const& info)
{
    return Napi::Number::New(info.Env(), mWrapped.number_of_isolated_vertices());
}


Napi::Value Arrangement2::Vertices(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    Napi::Array array = Napi::Array::New(env);
    Arrangement_2::Vertex_iterator it;
    uint32_t i;
    for(it=mWrapped.vertices_begin(),i=0; it!=mWrapped.vertices_end(); ++it,++i) {
        array.Set(i, Arrangement2Vertex::New(env, it));
    }
    return array;
}


Napi::Value Arrangement2::NumberOfVerticesAtInfinity(Napi::CallbackInfo const& info)
{
    return Napi::Number::New(info.Env(), mWrapped.number_of_vertices_at_infinity());
}


Napi::Value Arrangement2::UnboundedFace(Napi::CallbackInfo const& info)
{
    return Arrangement2Face::New(info.Env(), mWrapped.unbounded_face());
}


Napi::Value Arrangement2::NumberOfFaces(Napi::CallbackInfo const& info)
{
    return Napi::Number::New(info.Env(), mWrapped.number_of_faces());
}


Napi::Value Arrangement2::Faces(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    Napi::Array array = Napi::Array::New(env);
    Arrangement_2::Face_iterator it;
    uint32_t i;
    for(it=mWrapped.faces_begin(),i=0; it!=mWrapped.faces_end(); ++it,++i) {
        array.Set(i, Arrangement2Face::New(env, it));
    }
    return array;
}


Napi::Value Arrangement2::NumberOfUnboundedFaces(Napi::CallbackInfo const& info)
{
    return Napi::Number::New(info.Env(), mWrapped.number_of_unbounded_faces());
}


Napi::Value Arrangement2::UnboundedFaces(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    Napi::Array array = Napi::Array::New(env);
    Arrangement_2::Face_iterator it;
    uint32_t i;
    for(it=mWrapped.unbounded_faces_begin(),i=0; it!=mWrapped.unbounded_faces_end(); ++it,++i) {
        array.Set(i, Arrangement2Face::New(env, it));
    }
    return array;
}


Napi::Value Arrangement2::FictitiousFace(Napi::CallbackInfo const& info)
{
    return Arrangement2Face::New(info.Env(), mWrapped.fictitious_face());
}


Napi::Value Arrangement2::NumberOfHalfedges(Napi::CallbackInfo const& info)
{
    return Napi::Number::New(info.Env(), mWrapped.number_of_halfedges());
}


Napi::Value Arrangement2::Halfedges(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    Napi::Array array = Napi::Array::New(env);
    Arrangement_2::Halfedge_iterator it;
    uint32_t i;
    for(it=mWrapped.halfedges_begin(),i=0; it!=mWrapped.halfedges_end(); ++it,++i) {
        array.Set(i, Arrangement2Halfedge::New(env, it));
    }
    return array;
}


Napi::Value Arrangement2::NumberOfEdges(Napi::CallbackInfo const& info)
{
    return Napi::Number::New(info.Env(), mWrapped.number_of_edges());
}


Napi::Value Arrangement2::Edges(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    Napi::Array array = Napi::Array::New(env);
    Arrangement_2::Halfedge_iterator it;
    uint32_t i;
    for(it=mWrapped.edges_begin(),i=0; it!=mWrapped.edges_end(); ++it,++i) {
        array.Set(i, Arrangement2Halfedge::New(env, it));
    }
    return array;
}


Napi::Value Arrangement2::InsertInFaceInterior(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();

    Point_2 point;
    Arrangement_2::Face_handle face;
    Curve_2 curve;

    if ((info.Length() == 2)
        && Point2::ParseArg(env, info[0], point)
        && Arrangement2Face::ParseArg(env, info[1], face))
    {
        return Arrangement2Vertex::New(env, mWrapped.insert_in_face_interior(point, face));
    }

    if ((info.Length() == 2)
        && Curve2::ParseArg(env, info[0], curve)
        && Arrangement2Face::ParseArg(env, info[1], face))
    {
        return Arrangement2Halfedge::New(env, mWrapped.insert_in_face_interior(curve, face));
    }

    ARGS_ASSERT(env, false);
}


Napi::Value Arrangement2::InsertFromLeftVertex(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();

    Curve_2 curve;
    Arrangement_2::Vertex_handle vertex;
    Arrangement_2::Face_handle face;
    Arrangement_2::Halfedge_handle edge;

    if ((info.Length() == 2)
        && Curve2::ParseArg(env, info[0], curve)
        && Arrangement2Vertex::ParseArg(env, info[1], vertex))
    {
        return Arrangement2Halfedge::New(env, mWrapped.insert_from_left_vertex(curve, vertex));
    }

    if ((info.Length() == 3)
        && Curve2::ParseArg(env, info[0], curve)
        && Arrangement2Vertex::ParseArg(env, info[1], vertex)
        && Arrangement2Face::ParseArg(env, info[2], face))
    {
        return Arrangement2Halfedge::New(env, mWrapped.insert_from_left_vertex(curve, vertex, face));
    }

    if ((info.Length() == 2)
        && Curve2::ParseArg(env, info[0], curve)
        && Arrangement2Halfedge::ParseArg(env, info[1], edge))
    {
        return Arrangement2Halfedge::New(env, mWrapped.insert_from_left_vertex(curve, edge));
    }

    ARGS_ASSERT(env, false);
}


Napi::Value Arrangement2::InsertFromRightVertex(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();

    Curve_2 curve;
    Arrangement_2::Vertex_handle vertex;
    Arrangement_2::Face_handle face;
    Arrangement_2::Halfedge_handle edge;

    if ((info.Length() == 2)
        && Curve2::ParseArg(env, info[0], curve)
        && Arrangement2Vertex::ParseArg(env, info[1], vertex))
    {
        return Arrangement2Halfedge::New(env, mWrapped.insert_from_right_vertex(curve, vertex));
    }

    if ((info.Length() == 3)
        && Curve2::ParseArg(env, info[0], curve)
        && Arrangement2Vertex::ParseArg(env, info[1], vertex)
        && Arrangement2Face::ParseArg(env, info[2], face))
    {
        return Arrangement2Halfedge::New(env, mWrapped.insert_from_right_vertex(curve, vertex, face));
    }

    if ((info.Length() == 2)
        && Curve2::ParseArg(env, info[0], curve)
        && Arrangement2Halfedge::ParseArg(env, info[1], edge))
    {
        return Arrangement2Halfedge::New(env, mWrapped.insert_from_right_vertex(curve, edge));
    }

    ARGS_ASSERT(env, false);
}


Napi::Value Arrangement2::InsertAtVertices(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();

    Curve_2 curve;
    Arrangement_2::Vertex_handle vertex1, vertex2;
    Arrangement_2::Face_handle face;
    Arrangement_2::Halfedge_handle edge1, edge2;

    if ((info.Length() == 3)
        && Curve2::ParseArg(env, info[0], curve)
        && Arrangement2Vertex::ParseArg(env, info[1], vertex1)
        && Arrangement2Vertex::ParseArg(env, info[2], vertex2))
    {
        return Arrangement2Halfedge::New(env, mWrapped.insert_at_vertices(curve, vertex1, vertex2));
    }

    if ((info.Length() == 4)
        && Curve2::ParseArg(env, info[0], curve)
        && Arrangement2Vertex::ParseArg(env, info[1], vertex1)
        && Arrangement2Vertex::ParseArg(env, info[2], vertex2)
        && Arrangement2Face::ParseArg(env, info[3], face))
    {
        return Arrangement2Halfedge::New(env, mWrapped.insert_at_vertices(curve, vertex1, vertex2, face));
    }

    if ((info.Length() == 3)
        && Curve2::ParseArg(env, info[0], curve)
        && Arrangement2Halfedge::ParseArg(env, info[1], edge1)
        && Arrangement2Vertex::ParseArg(env, info[2], vertex1))
    {
        return Arrangement2Halfedge::New(env, mWrapped.insert_at_vertices(curve, edge1, vertex1));
    }

    if ((info.Length() == 3)
        && Curve2::ParseArg(env, info[0], curve)
        && Arrangement2Halfedge::ParseArg(env, info[1], edge1)
        && Arrangement2Halfedge::ParseArg(env, info[2], edge1))
    {
        return Arrangement2Halfedge::New(env, mWrapped.insert_at_vertices(curve, edge1, edge2));
    }

    ARGS_ASSERT(env, false);
}


Napi::Value Arrangement2::ModifyVertex(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 2);
    ARGS_PARSE_LOCAL(env, Arrangement2Vertex::ParseArg, Arrangement_2::Vertex_handle, vertex, info[0]);
    ARGS_PARSE_LOCAL(env, Point2::ParseArg, Point_2, point, info[1]);
    return Arrangement2Vertex::New(env, mWrapped.modify_vertex(vertex, point));
}


Napi::Value Arrangement2::RemoveIsolatedVertex(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);
    ARGS_PARSE_LOCAL(env, Arrangement2Vertex::ParseArg, Arrangement_2::Vertex_handle, vertex, info[0]);
    return Arrangement2Face::New(env, mWrapped.remove_isolated_vertex(vertex));
}


Napi::Value Arrangement2::ModifyEdge(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 2);
    ARGS_PARSE_LOCAL(env, Arrangement2Halfedge::ParseArg, Arrangement_2::Halfedge_handle, halfedge, info[0]);
    ARGS_PARSE_LOCAL(env, Curve2::ParseArg, Curve_2, curve, info[1]);
    return Arrangement2Halfedge::New(env, mWrapped.modify_edge(halfedge, curve));
}


Napi::Value Arrangement2::SplitEdge(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 3);
    ARGS_PARSE_LOCAL(env, Arrangement2Halfedge::ParseArg, Arrangement_2::Halfedge_handle, halfedge, info[0]);
    ARGS_PARSE_LOCAL(env, Curve2::ParseArg, Curve_2, curve1, info[1]);
    ARGS_PARSE_LOCAL(env, Curve2::ParseArg, Curve_2, curve2, info[2]);
    return Arrangement2Halfedge::New(env, mWrapped.split_edge(halfedge, curve1, curve2));
}


Napi::Value Arrangement2::MergeEdge(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 3);
    ARGS_PARSE_LOCAL(env, Arrangement2Halfedge::ParseArg, Arrangement_2::Halfedge_handle, halfedge1, info[0]);
    ARGS_PARSE_LOCAL(env, Arrangement2Halfedge::ParseArg, Arrangement_2::Halfedge_handle, halfedge2, info[1]);
    ARGS_PARSE_LOCAL(env, Curve2::ParseArg, Curve_2, curve, info[2]);
    return Arrangement2Halfedge::New(env, mWrapped.merge_edge(halfedge1, halfedge2, curve));
}


Napi::Value Arrangement2::RemoveEdge(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    Arrangement_2::Halfedge_handle edge;

    if ((info.Length() == 1)
        && Arrangement2Halfedge::ParseArg(env, info[0], edge))
    {
        return Arrangement2Face::New(env, mWrapped.remove_edge(edge));
    }

    if ((info.Length() == 2)
        && Arrangement2Halfedge::ParseArg(env, info[0], edge)
        && info[1].IsBoolean())
    {
        return Arrangement2Face::New(env, mWrapped.remove_edge(edge, info[1].As<Napi::Boolean>()));
    }

    if ((info.Length() == 3)
        && Arrangement2Halfedge::ParseArg(env, info[0], edge)
        && info[1].IsBoolean()
        && info[2].IsBoolean())
    {
        return Arrangement2Face::New(env,
            mWrapped.remove_edge(edge, info[1].As<Napi::Boolean>(), info[2].As<Napi::Boolean>())
        );
    }

    ARGS_ASSERT(env, false);
}


Napi::Value Arrangement2::RemoveEdgeAndMerge(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);
    ARGS_PARSE_LOCAL(env, Arrangement2Halfedge::ParseArg, Arrangement_2::Halfedge_handle, hedge, info[0]);
    return Arrangement2Face::New(env, remove_edge(mWrapped, hedge));
}

