#include "Ray2.h"
#include "Point2.h"
#include "Line2.h"
#include "Direction2.h"
#include "Vector2.h"
#include "cgal_args.h"

using namespace std;


Ray2::Ray2(Napi::CallbackInfo const& info)
:   CGALWrapper(info)
{
}


const char *Ray2::Name = "Ray2";


void Ray2::AddProperties(Napi::Env env, vector<PropertyDescriptor>& properties)
{
    properties.insert(properties.end(), {
        InstanceMethod("isEqual", &Ray2::IsEqual),
        InstanceMethod("source", &Ray2::Source),
        InstanceMethod("point", &Ray2::Point),
        InstanceMethod("direction", &Ray2::Direction),
        InstanceMethod("toVector", &Ray2::ToVector),
        InstanceMethod("supportingLine", &Ray2::SupportingLine),
        InstanceMethod("opposite", &Ray2::Opposite),
        InstanceMethod("isDegenerate", &Ray2::IsDegenerate),
        InstanceMethod("isHorizontal", &Ray2::IsHorizontal),
        InstanceMethod("isVertical", &Ray2::IsVertical),
        InstanceMethod("hasOn", &Ray2::HasOn),
        InstanceMethod("collinearHasOn", &Ray2::CollinearHasOn)
    });
}


bool Ray2::ParseArg(Napi::Env env, Napi::Value arg, Ray_2& receiver)
{
    if (arg.IsObject()) {
        Napi::Object obj = arg.As<Napi::Object>();

        if (obj.InstanceOf(sConstructor.Value())) {
            receiver = Unwrap(obj)->mWrapped;
            return true;
        }

        Point_2 p;
        Direction_2 d;
        if (Point2::ParseArg(env, obj["p"], p) &&
            Direction2::ParseArg(env, obj["d"], d))
        {
            receiver = Ray_2(p, d);
            return true;
        }

        Point_2 q;
        if (Point2::ParseArg(env, obj["q"], q)) {
            receiver = Ray_2(p, q);
            return true;
        }

        Line_2 l;
        if (Line2::ParseArg(env, obj["l"], l)) {
            receiver = Ray_2(p, l);
            return true;
        }

        Vector_2 v;
        if (Vector2::ParseArg(env, obj["v"], v)) {
            receiver = Ray_2(p, v);
            return true;
        }

    }

    return false;
}


Napi::Value Ray2::ToPOD(Napi::Env env, Ray_2 const& ray, bool precise)
{
    Napi::Object obj = Napi::Object::New(env);
    obj.Set("p", Point2::ToPOD(env, ray.source(), precise));
    obj.Set("d", Direction2::ToPOD(env, ray.direction(), precise));
    return obj;
}


Napi::Value Ray2::IsEqual(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);
    ARGS_PARSE_LOCAL(env, Ray2::ParseArg, Ray_2, otherRay, info[0]);
    return Napi::Boolean::New(env, mWrapped == otherRay);
}


Napi::Value Ray2::Source(Napi::CallbackInfo const& info)
{
    return Point2::New(info.Env(), mWrapped.source());
}


Napi::Value Ray2::Point(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);
    ARGS_ASSERT(env, info[0].IsNumber())
    return Point2::New(env, mWrapped.point(info[0].As<Napi::Number>()));
}


Napi::Value Ray2::Direction(Napi::CallbackInfo const& info)
{
    return Direction2::New(info.Env(), mWrapped.direction());
}


Napi::Value Ray2::ToVector(Napi::CallbackInfo const& info)
{
    return Vector2::New(info.Env(), mWrapped.to_vector());
}


Napi::Value Ray2::SupportingLine(Napi::CallbackInfo const& info)
{
    return Line2::New(info.Env(), mWrapped.supporting_line());
}


Napi::Value Ray2::Opposite(Napi::CallbackInfo const& info)
{
    return Ray2::New(info.Env(), mWrapped.opposite());
}


Napi::Value Ray2::IsDegenerate(Napi::CallbackInfo const& info)
{
    return Napi::Boolean::New(info.Env(), mWrapped.is_degenerate());
}


Napi::Value Ray2::IsHorizontal(Napi::CallbackInfo const& info)
{
    return Napi::Boolean::New(info.Env(), mWrapped.is_horizontal());
}


Napi::Value Ray2::IsVertical(Napi::CallbackInfo const& info)
{
    return Napi::Boolean::New(info.Env(), mWrapped.is_vertical());
}


Napi::Value Ray2::HasOn(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);
    ARGS_PARSE_LOCAL(env, Point2::ParseArg, Point_2, point, info[0]);
    return Napi::Boolean::New(env, mWrapped.has_on(point));
}


Napi::Value Ray2::CollinearHasOn(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);
    ARGS_PARSE_LOCAL(env, Point2::ParseArg, Point_2, point, info[0]);
    return Napi::Boolean::New(env, mWrapped.collinear_has_on(point));
}
