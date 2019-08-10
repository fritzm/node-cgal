#include "Arrangement2Vertex.h"
#include "Arrangement2Halfedge.h"
#include "Arrangement2Face.h"
#include "Point2.h"
#include "cgal_args.h"
#include <sstream>

using namespace std;


Arrangement2Vertex::Arrangement2Vertex(Napi::CallbackInfo const& info)
:   CGALWrapper(info)
{
}


char const* Arrangement2Vertex::Name = "Vertex";


void Arrangement2Vertex::AddProperties(Napi::Env env, vector<PropertyDescriptor>& properties)
{
    properties.insert(properties.end(), {
        InstanceMethod("toString", &Arrangement2Vertex::ToString),
        InstanceMethod("isAtOpenBoundary", &Arrangement2Vertex::IsAtOpenBoundary),
        InstanceMethod("isIsolated", &Arrangement2Vertex::IsIsolated),
        InstanceMethod("degree", &Arrangement2Vertex::Degree),
        InstanceMethod("incidentHalfedges", &Arrangement2Vertex::IncidentHalfedges),
        InstanceMethod("face", &Arrangement2Vertex::Face),
        InstanceMethod("point", &Arrangement2Vertex::Point),
        InstanceMethod("parameterSpaceInX", &Arrangement2Vertex::ParameterSpaceInX),
        InstanceMethod("parameterSpaceInY", &Arrangement2Vertex::ParameterSpaceInY)
    });
}


bool Arrangement2Vertex::ParseArg(Napi::Env env, Napi::Value arg, Arrangement_2::Vertex_handle& receiver)
{
    return false;
}


Napi::Value Arrangement2Vertex::ToPOD(Napi::Env env, Arrangement_2::Vertex_handle const& vertex, bool precise)
{
    return Napi::Object::New(env);
}


Napi::Value Arrangement2Vertex::ToString(Napi::CallbackInfo const& info)
{
    ostringstream str;
    str << "[object "  << Name << " " << mWrapped.ptr() <<" ";
    if (mWrapped->is_at_open_boundary()) {
        switch(mWrapped->parameter_space_in_x()) {
        case CGAL::ARR_LEFT_BOUNDARY:
            str << "LEFT";
            break;
        case CGAL::ARR_RIGHT_BOUNDARY:
            str << "RIGHT";
            break;
        default:
            str << "INTERIOR";
            break;
        }
        str << " ";
        switch(mWrapped->parameter_space_in_y()) {
        case CGAL::ARR_TOP_BOUNDARY:
            str << "TOP";
            break;
        case CGAL::ARR_BOTTOM_BOUNDARY:
            str << "BOTTOM";
            break;
        default:
            str << "INTERIOR";
            break;
        }
    } else {
        str << mWrapped->point();
    }
    str << "]";
    return Napi::String::New(info.Env(), str.str());
}


Napi::Value Arrangement2Vertex::IsAtOpenBoundary(Napi::CallbackInfo const& info)
{
    return Napi::Boolean::New(info.Env(), mWrapped->is_at_open_boundary());
}


Napi::Value Arrangement2Vertex::IsIsolated(Napi::CallbackInfo const& info)
{
    return Napi::Boolean::New(info.Env(), mWrapped->is_isolated());
}


Napi::Value Arrangement2Vertex::Degree(Napi::CallbackInfo const& info)
{
    return Napi::Number::New(info.Env(), mWrapped->degree());
}


Napi::Value Arrangement2Vertex::IncidentHalfedges(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    Napi::Array array = Napi::Array::New(env);
    Arrangement_2::Halfedge_around_vertex_circulator first, curr;
    first = curr = mWrapped->incident_halfedges();
    uint32_t i = 0;
    do {
        array.Set(i, Arrangement2Halfedge::New(env, curr));
    } while(++i,++curr != first);
    return array;
}


Napi::Value Arrangement2Vertex::Face(Napi::CallbackInfo const& info)
{
    return Arrangement2Face::New(info.Env(), mWrapped->face());
}


Napi::Value Arrangement2Vertex::Point(Napi::CallbackInfo const& info)
{
    return Point2::New(info.Env(), mWrapped->point());
}


Napi::Value Arrangement2Vertex::ParameterSpaceInX(Napi::CallbackInfo const& info)
{
    return Napi::Number::New(info.Env(), mWrapped->parameter_space_in_x());
}


Napi::Value Arrangement2Vertex::ParameterSpaceInY(Napi::CallbackInfo const& info)
{
    return Napi::Number::New(info.Env(), mWrapped->parameter_space_in_y());
}
