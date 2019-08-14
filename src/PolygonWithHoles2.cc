#include "PolygonWithHoles2.h"
#include "Polygon2.h"
#include "cgal_args.h"

using namespace std;


PolygonWithHoles2::PolygonWithHoles2(Napi::CallbackInfo const& info)
:   CGALWrapper(info)
{
}


const char *PolygonWithHoles2::Name = "PolygonWithHoles2";


void PolygonWithHoles2::AddProperties(Napi::Env env, vector<PropertyDescriptor>& properties)
{
    properties.insert(properties.end(), {
        InstanceMethod("isEqual", &PolygonWithHoles2::IsEqual),
        InstanceMethod("outer", &PolygonWithHoles2::Outer),
        InstanceMethod("holes", &PolygonWithHoles2::Holes),
        InstanceMethod("isUnbounded", &PolygonWithHoles2::IsUnbounded)
    });
}


bool PolygonWithHoles2::ParseArg(Napi::Env env, Napi::Value arg, Polygon_with_holes_2& receiver)
{
    if (arg.IsObject()) {
        Napi::Object obj = arg.As<Napi::Object>();

        if (obj.InstanceOf(sConstructor.Value())) {
            receiver = Unwrap(obj)->mWrapped;
            return true;
        }

        Polygon_2 outer;
        vector<Polygon_2> holes;
        if (Polygon2::ParseArg(env, obj["outer"], outer) &&
            Polygon2::ParseSeqArg(env, obj["holes"], back_inserter(holes)))
        {
            receiver = Polygon_with_holes_2(outer, holes.begin(), holes.end());
            return true;
        }
        if (Polygon2::ParseArg(env, arg, outer)) {
            receiver = Polygon_with_holes_2(outer);
            return true;
        }

    }

    return false;
}


Napi::Value PolygonWithHoles2::ToPOD(Napi::Env env, Polygon_with_holes_2 const& poly, bool precise)
{
    Napi::Object obj = Napi::Object::New(env);
    obj.Set("outer", Polygon2::ToPOD(env, poly.outer_boundary(), precise));
    obj.Set("holes", Polygon2::SeqToPOD(env, poly.holes_begin(), poly.holes_end(), precise));
    return obj;
}


Napi::Value PolygonWithHoles2::IsEqual(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);
    ARGS_PARSE_LOCAL(env, PolygonWithHoles2::ParseArg, Polygon_with_holes_2, otherPoly, info[0]);
    return Napi::Boolean::New(env, mWrapped == otherPoly);
}


Napi::Value PolygonWithHoles2::Outer(Napi::CallbackInfo const& info)
{
    return Polygon2::New(info.Env(), mWrapped.outer_boundary());
}


Napi::Value PolygonWithHoles2::Holes(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    Napi::Array array = Napi::Array::New(env);
    uint32_t i;
    Polygon_with_holes_2::Hole_const_iterator it;
    for(it=mWrapped.holes_begin(),i=0; it!=mWrapped.holes_end(); ++it,++i) {
        array.Set(i, Polygon2::New(env, *it));
    }
    return array;
}


Napi::Value PolygonWithHoles2::IsUnbounded(Napi::CallbackInfo const& info)
{
    return Napi::Boolean::New(info.Env(), mWrapped.is_unbounded());
}
