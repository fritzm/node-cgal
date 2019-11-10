#include "Polygon2.h"
#include "AffTransformation2.h"
#include "NumberTypes.h"
#include "Point2.h"
#include "cgal_args.h"

using namespace std;


Polygon2::Polygon2(Napi::CallbackInfo const& info)
:   CGALWrapper(info)
{
}


const char *Polygon2::Name = "Polygon2";


void Polygon2::AddProperties(Napi::Env env, vector<PropertyDescriptor>& properties)
{
    properties.insert(properties.end(),{
        InstanceMethod("isEqual", &Polygon2::IsEqual),
        InstanceMethod("isSimple", &Polygon2::IsSimple),
        InstanceMethod("isConvex", &Polygon2::IsConvex),
        InstanceMethod("orientation", &Polygon2::Orientation),
        InstanceMethod("orientedSide", &Polygon2::OrientedSide),
        InstanceMethod("boundedSide", &Polygon2::BoundedSide),
        InstanceMethod("area", &Polygon2::Area),
        InstanceMethod("transform", &Polygon2::Transform),
        InstanceMethod("coords", &Polygon2::Coords)
    });
}


bool Polygon2::ParseArg(Napi::Env env, Napi::Value arg, Polygon_2& receiver)
{
    if (arg.IsObject() && arg.As<Napi::Object>().InstanceOf(sConstructor.Value())) {
        receiver = Unwrap(arg.As<Napi::Object>())->mWrapped;
        return true;
    }

    if (arg.IsArray()) {
        return Point2::ParseSeqArg(env, arg, back_inserter(receiver));
    }

    return false;
}


Napi::Value Polygon2::ToPOD(Napi::Env env, Polygon_2 const& poly, bool precise)
{
    return Point2::SeqToPOD(env, poly.vertices_begin(), poly.vertices_end(), precise);
}


Napi::Value Polygon2::IsEqual(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);
    ARGS_PARSE_LOCAL(env, Polygon2::ParseArg, Polygon_2, otherPoly, info[0]);
    return Napi::Boolean::New(env, mWrapped == otherPoly);
}


Napi::Value Polygon2::IsSimple(Napi::CallbackInfo const& info)
{
    return Napi::Boolean::New(info.Env(), mWrapped.is_simple());
}


Napi::Value Polygon2::IsConvex(Napi::CallbackInfo const& info)
{
    return Napi::Boolean::New(info.Env(), mWrapped.is_convex());
}


Napi::Value Polygon2::Orientation(Napi::CallbackInfo const& info)
{
    return Napi::Number::New(info.Env(), mWrapped.orientation());
}


Napi::Value Polygon2::OrientedSide(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);
    ARGS_PARSE_LOCAL(env, Point2::ParseArg, Point_2, point, info[0]);
    return Napi::Number::New(env, mWrapped.oriented_side(point));
}


Napi::Value Polygon2::BoundedSide(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);
    ARGS_PARSE_LOCAL(env, Point2::ParseArg, Point_2, point, info[0]);
    return Napi::Number::New(env, mWrapped.bounded_side(point));
}


Napi::Value Polygon2::Area(Napi::CallbackInfo const& info)
{
    return FieldNumberType::New(info.Env(), mWrapped.area());
}


Napi::Value Polygon2::Transform(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);
    ARGS_PARSE_LOCAL(env, AffTransformation2::ParseArg, Aff_transformation_2, afft, info[0]);
    return Polygon2::New(env, CGAL::transform(afft, mWrapped));
}


Napi::Value Polygon2::Coords(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    Napi::Array array = Napi::Array::New(env, mWrapped.size());
    Polygon_2::Vertex_iterator it;
    uint32_t i;
    for(it=mWrapped.vertices_begin(),i=0; it!=mWrapped.vertices_end(); ++it,++i) {
        array[i] = Point2::New(env, *it);
    }
    return array;
}
