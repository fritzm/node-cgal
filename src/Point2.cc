#include "Point2.h"
#include "AffTransformation2.h"
#include "cgal_args.h"
#include "iomanip"

using namespace std;


Point2::Point2(Napi::CallbackInfo const& info)
:   CGALWrapper(info)
{
}


const char *Point2::Name = "Point2";


void Point2::AddProperties(Napi::Env env, vector<PropertyDescriptor>& properties)
{
    properties.insert(properties.end(), {
        InstanceMethod("isEqual", &Point2::IsEqual),
        InstanceMethod("x", &Point2::X),
        InstanceMethod("y", &Point2::Y),
        InstanceMethod("transform", &Point2::Transform)
    });
}


bool Point2::ParseArg(Napi::Env env, Napi::Value arg, Point_2& receiver)
{
    if (arg.IsObject() && arg.As<Napi::Object>().InstanceOf(sConstructor.Value())) {
        receiver = Unwrap(arg.As<Napi::Object>())->mWrapped;
        return true;
    }

    if (arg.IsArray()) {
        Napi::Array coords = arg.As<Napi::Array>();
        K::FT x, y;
        if (::ParseNumberArg(env, coords[0u], x) &&
            ::ParseNumberArg(env, coords[1], y))
        {
            receiver = Point_2(x, y);
            return true;
        }
    }

    return false;
}


Napi::Value Point2::ToPOD(Napi::Env env, Point_2 const& point, bool precise)
{
    Napi::Array array = Napi::Array::New(env, 2);
    if (precise) {
        ostringstream x_str;
#if CGAL_USE_EPECK
        x_str << point.x().exact();
#else
        x_str << setprecision(20) << point.x();
#endif
        array.Set(0u, x_str.str());
        ostringstream y_str;
#if CGAL_USE_EPECK
        y_str << point.y().exact();
#else
        y_str << setprecision(20) << point.y();
#endif
        array.Set(1, y_str.str());
    } else {
        array.Set(0u, CGAL::to_double(point.x()));
        array.Set(1, CGAL::to_double(point.y())); 
    }

    return array;
}


Napi::Value Point2::IsEqual(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);
    ARGS_PARSE_LOCAL(env, Point2::ParseArg, Point_2, otherPoint, info[0]);
    return Napi::Value::From(env, mWrapped == otherPoint);
}


Napi::Value Point2::X(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    return Napi::Value::From(env, CGAL::to_double(mWrapped.x()));
}


Napi::Value Point2::Y(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    return Napi::Value::From(env, CGAL::to_double(mWrapped.y()));
}


Napi::Value Point2::Transform(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(isolate, info.Length() == 1);
    Aff_transformation_2 aff;
    if (AffTransformation2::ParseArg(env, info[0], aff)) {
        return Point2::New(env, mWrapped.transform(aff));
    }
    ARGS_ASSERT(env, false);
}
