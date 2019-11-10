#include "Point2.h"
#include "AffTransformation2.h"
#include "NumberTypes.h"
#include "cgal_args.h"

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
        Napi::Array array = arg.As<Napi::Array>();
        if (array.Length() == 2) {
            K::FT x, y;
            if (FieldNumberType::ParseArg(env, array[0u], x)
                && FieldNumberType::ParseArg(env, array[1], y))
            {
                receiver = Point_2(x, y);
                return true;
            }
        }
    }

    return false;
}


Napi::Value Point2::ToPOD(Napi::Env env, Point_2 const& point, bool precise)
{
    return FieldNumberType::SeqToPOD(env, point.cartesian_begin(), point.cartesian_end(), precise);
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
    return FieldNumberType::New(info.Env(), mWrapped.x());
}


Napi::Value Point2::Y(Napi::CallbackInfo const& info)
{
    return FieldNumberType::New(info.Env(), mWrapped.y());
}


Napi::Value Point2::Transform(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(isolate, info.Length() == 1);
    ARGS_PARSE_LOCAL(env, AffTransformation2::ParseArg, Aff_transformation_2, aff, info[0]);
    return Point2::New(env, mWrapped.transform(aff));
}
