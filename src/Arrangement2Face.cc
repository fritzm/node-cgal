#include "Arrangement2Face.h"
#include "Arrangement2Halfedge.h"
#include "Arrangement2Vertex.h"
#include "cgal_args.h"

using namespace std;


Arrangement2Face::Arrangement2Face(Napi::CallbackInfo const& info)
:   CGALWrapper(info)
{
}


char const* Arrangement2Face::Name = "Face";


void Arrangement2Face::AddProperties(Napi::Env env, vector<PropertyDescriptor>& properties)
{
    properties.insert(properties.end(), {
        InstanceMethod("toString", &Arrangement2Face::ToString),
        InstanceMethod("isFictitious", &Arrangement2Face::IsFictitious),
        InstanceMethod("isUnbounded", &Arrangement2Face::IsUnbounded),
        InstanceMethod("outerCCB", &Arrangement2Face::OuterCCB),
        InstanceMethod("holes", &Arrangement2Face::Holes),
        InstanceMethod("isolatedVertices", &Arrangement2Face::IsolatedVertices)
    });
}


bool Arrangement2Face::ParseArg(Napi::Env env, Napi::Value arg, Arrangement_2::Face_handle& receiver)
{
    return false;
}


Napi::Value Arrangement2Face::ToPOD(Napi::Env env, Arrangement_2::Face_handle const& face, bool precise)
{
    return Napi::Object::New(env);
}


Napi::Value Arrangement2Face::ToString(Napi::CallbackInfo const& info)
{
    ostringstream str;
    str << "[object "  << Name << " " << mWrapped.ptr() << " ";
    if (mWrapped->is_fictitious()) {
        str << "FIC ";
    } else if (mWrapped->is_unbounded()) {
        str << "UNB ";
    }
    int numedges = 0;
    if (mWrapped->has_outer_ccb()) {
        Arrangement_2::Ccb_halfedge_circulator e, e0;
        e = e0 = mWrapped->outer_ccb();
        do { ++numedges; } while(++e != e0);
    }
    str << "E:" << numedges << " ";
    int numholes = 0;
    Arrangement_2::Hole_iterator h;
    for(h=mWrapped->holes_begin(); h!=mWrapped->holes_end(); ++h,++numholes) {}
    str << "H:" << numholes << " ";
    int numisolated = 0;
    Arrangement_2::Isolated_vertex_iterator i;
    for(i=mWrapped->isolated_vertices_begin(); i!=mWrapped->isolated_vertices_end(); ++i,++numisolated) {}
    str << "I:" << numisolated << "]";
    return Napi::String::New(info.Env(), str.str());
}


Napi::Value Arrangement2Face::IsFictitious(Napi::CallbackInfo const& info)
{
    return Napi::Boolean::New(info.Env(), mWrapped->is_fictitious());
}


Napi::Value Arrangement2Face::IsUnbounded(Napi::CallbackInfo const& info)
{
    return Napi::Boolean::New(info.Env(), mWrapped->is_unbounded());
}


Napi::Value Arrangement2Face::OuterCCB(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    Napi::Array array = Napi::Array::New(env);
    if (mWrapped->has_outer_ccb()) {
        Arrangement_2::Ccb_halfedge_circulator first, curr;
        first = curr = mWrapped->outer_ccb();
        uint32_t i = 0;
        do {
            array.Set(i, Arrangement2Halfedge::New(env, curr));
        } while(++i,++curr != first);
    }
    return array;
}


Napi::Value Arrangement2Face::Holes(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    Napi::Array array = Napi::Array::New(env);
    Arrangement_2::Hole_iterator it;
    uint32_t i;
    for(it=mWrapped->holes_begin(),i=0; it!=mWrapped->holes_end(); ++it,++i) {
        Napi::Array hole = Napi::Array::New(env);
        array.Set(i, hole);
        Arrangement_2::Ccb_halfedge_circulator first, curr;
        first = curr = *it;
        uint32_t j = 0;
        do {
            hole.Set(j, Arrangement2Halfedge::New(env, curr));
        } while(++j,++curr != first);
    }
    return array;
}


Napi::Value Arrangement2Face::IsolatedVertices(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    Napi::Array array = Napi::Array::New(env);
    Arrangement_2::Isolated_vertex_iterator it;
    uint32_t i;
    for(it=mWrapped->isolated_vertices_begin(),i=0; it!=mWrapped->isolated_vertices_end(); ++it,++i) {
        array.Set(i, Arrangement2Vertex::New(env, it));
    }
    return array;
}
