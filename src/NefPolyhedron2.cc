#include "NefPolyhedron2.h"
#include "cgal_args.h"

using namespace std;


NefPolyhedron2::NefPolyhedron2(Napi::CallbackInfo const& info)
:   CGALWrapper(info)
{
}


const char *NefPolyhedron2::Name = "NefPolyhedron2";


void NefPolyhedron2::AddProperties(Napi::Env env, vector<PropertyDescriptor>& properties)
{
    properties.insert(properties.end(), {
        StaticValue("EXCLUDED", Napi::Number::New(env, Nef_polyhedron_2::EXCLUDED), napi_enumerable),
        StaticValue("INCLUDED", Napi::Number::New(env, Nef_polyhedron_2::INCLUDED), napi_enumerable),
        StaticValue("EMPTY", Napi::Number::New(env, Nef_polyhedron_2::EMPTY), napi_enumerable),
        StaticValue("COMPLETE", Napi::Number::New(env, Nef_polyhedron_2::COMPLETE), napi_enumerable)
    });
}


bool NefPolyhedron2::ParseArg(Napi::Env env, Napi::Value arg, Nef_polyhedron_2& receiver)
{
    return false;
}


Napi::Value NefPolyhedron2::ToPOD(Napi::Env env, Nef_polyhedron_2 const& npoly, bool precise)
{
    return Napi::Object::New(env);
}
