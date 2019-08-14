#include "Arrangement2Halfedge.h"
#include "Arrangement2Vertex.h"
#include "Arrangement2Face.h"
#include "Curve2.h"
#include "cgal_args.h"

using namespace std;


Arrangement2Halfedge::Arrangement2Halfedge(Napi::CallbackInfo const& info)
:   CGALWrapper(info)
{
}


char const* Arrangement2Halfedge::Name = "Halfedge";


void Arrangement2Halfedge::AddProperties(Napi::Env env, vector<PropertyDescriptor>& properties)
{
    properties.insert(properties.end(), {
        InstanceMethod("toString", &Arrangement2Halfedge::ToString),
        InstanceMethod("isFictitious", &Arrangement2Halfedge::IsFictitious),
        InstanceMethod("source", &Arrangement2Halfedge::Source),
        InstanceMethod("target", &Arrangement2Halfedge::Target),
        InstanceMethod("face", &Arrangement2Halfedge::Face),
        InstanceMethod("twin", &Arrangement2Halfedge::Twin),
        InstanceMethod("prev", &Arrangement2Halfedge::Prev),
        InstanceMethod("next", &Arrangement2Halfedge::Next),
        InstanceMethod("ccb", &Arrangement2Halfedge::CCB),
        InstanceMethod("curve", &Arrangement2Halfedge::Curve)
    });
}


bool Arrangement2Halfedge::ParseArg(Napi::Env env, Napi::Value arg, Arrangement_2::Halfedge_handle& receiver)
{
    return false;
}


Napi::Value Arrangement2Halfedge::ToPOD(Napi::Env env, Arrangement_2::Halfedge_handle const& hedge, bool precise)
{
    return Napi::Object::New(env);
}


Napi::Value Arrangement2Halfedge::ToString(Napi::CallbackInfo const& info)
{
    ostringstream str;
    str << "[object "  << Name << " " << mWrapped.ptr() << " ";
    if (mWrapped->is_fictitious()) {
        str << "FIC ";
    }
    str << "]";
    return Napi::String::New(info.Env(), str.str());
}


Napi::Value Arrangement2Halfedge::IsFictitious(Napi::CallbackInfo const& info)
{
    return Napi::Boolean::New(info.Env(), mWrapped->is_fictitious());
}


Napi::Value Arrangement2Halfedge::Source(Napi::CallbackInfo const& info)
{
    return Arrangement2Vertex::New(info.Env(), mWrapped->source());
}


Napi::Value Arrangement2Halfedge::Target(Napi::CallbackInfo const& info)
{
    return Arrangement2Vertex::New(info.Env(), mWrapped->target());
}


Napi::Value Arrangement2Halfedge::Face(Napi::CallbackInfo const& info)
{
    return Arrangement2Face::New(info.Env(), mWrapped->face());
}


Napi::Value Arrangement2Halfedge::Twin(Napi::CallbackInfo const& info)
{
    return Arrangement2Halfedge::New(info.Env(), mWrapped->twin());
}


Napi::Value Arrangement2Halfedge::Prev(Napi::CallbackInfo const& info)
{
    return Arrangement2Halfedge::New(info.Env(), mWrapped->prev());
}


Napi::Value Arrangement2Halfedge::Next(Napi::CallbackInfo const& info)
{
    return Arrangement2Halfedge::New(info.Env(), mWrapped->next());
}


Napi::Value Arrangement2Halfedge::CCB(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    Napi::Array array = Napi::Array::New(env);
    Arrangement_2::Ccb_halfedge_circulator first, curr;
    first = curr = mWrapped->ccb();
    uint32_t i = 0;
    do {
        array.Set(i, Arrangement2Halfedge::New(env, curr));
    } while(++i,++curr != first);
    return array;
}


Napi::Value Arrangement2Halfedge::Curve(Napi::CallbackInfo const& info)
{
    return Curve2::New(info.Env(), mWrapped->curve());
}
