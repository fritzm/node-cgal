#include "Direction2.h"
#include "Point2.h"
#include "Line2.h"
#include "Vector2.h"
#include "Segment2.h"
#include "Ray2.h"
#include "cgal_args.h"

using namespace std;


Direction2::Direction2(Napi::CallbackInfo const& info)
:   CGALWrapper(info)
{
}


const char *Direction2::Name = "Direction2";


void Direction2::AddProperties(std::vector<PropertyDescriptor>& properties)
{
    properties.insert(properties.end(), {
        InstanceMethod("isEqual", &Direction2::IsEqual),
        InstanceMethod("isLessThan", &Direction2::IsLessThan),
        InstanceMethod("isGreaterThan", &Direction2::IsGreaterThan),
        InstanceMethod("isCCWBetween", &Direction2::IsCCWBetween),
        InstanceMethod("opposite", &Direction2::Opposite),
        InstanceMethod("toVector", &Direction2::ToVector),
        InstanceMethod("dx", &Direction2::DX),
        InstanceMethod("dy", &Direction2::DY)
    });
}


bool Direction2::ParseArg(Napi::Env env, Napi::Value arg, Direction_2& receiver)
{
    if (arg.IsObject() && arg.As<Napi::Object>().InstanceOf(sConstructor.Value())) {
        receiver = Unwrap(arg.As<Napi::Object>())->mWrapped;
        return true;
    }

    Vector_2 vector;
    if (Vector2::ParseArg(env, arg, vector)) {
        receiver = Direction_2(vector);
        return true;
    }

    Line_2 line;
    if (Line2::ParseArg(env, arg, line)) {
        receiver = Direction_2(line);
        return true;
    }

    Ray_2 ray;
    if (Ray2::ParseArg(env, arg, ray)) {
        receiver = Direction_2(ray);
        return true;
    }

    Segment_2 segment;
    if (Segment2::ParseArg(env, arg, segment)) {
        receiver = Direction_2(segment);
        return true;
    }

    if (arg.IsObject()) {
        Napi::Object inits = arg.As<Napi::Object>();
        K::FT dx, dy;
        if (::ParseNumberArg(env, inits["dx"], dx) &&
            ::ParseNumberArg(env, inits["dy"], dy))
        {
            receiver = Direction_2(dx, dy);
            return true;
        }
    }

    return false;
}


Napi::Value Direction2::ToPOD(Napi::Env env, Direction_2 const& direction, bool precise)
{
    Napi::Object obj = Napi::Object::New(env);

    if (precise) {

        ostringstream dxstr;
#if CGAL_USE_EPECK
        dxstr << direction.dx().exact();
#else
        dxstr << setprecision(20) << direction.dx();
#endif
        obj.Set("dx", dxstr.str());
        ostringstream dystr;
#if CGAL_USE_EPECK
        dystr << direction.dy().exact();
#else
        dystr << setprecision(20) << direction.dy();
#endif
        obj.Set("dy", dystr.str());

    } else {

        obj.Set("dx", CGAL::to_double(direction.dx()));
        obj.Set("dy", CGAL::to_double(direction.dy()));

    }

    return obj;
}


Napi::Value Direction2::IsEqual(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);
    ARGS_PARSE_LOCAL(env, Direction2::ParseArg, Direction_2, otherDir, info[0]);
    return Napi::Boolean::New(env, mWrapped == otherDir);
}


Napi::Value Direction2::IsLessThan(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);
    ARGS_PARSE_LOCAL(env, Direction2::ParseArg, Direction_2, otherDir, info[0]);
    return Napi::Boolean::New(env, mWrapped < otherDir);
}


Napi::Value Direction2::IsGreaterThan(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);
    ARGS_PARSE_LOCAL(env, Direction2::ParseArg, Direction_2, otherDir, info[0]);
    return Napi::Boolean::New(env, mWrapped > otherDir);
}


Napi::Value Direction2::IsCCWBetween(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 2);
    ARGS_PARSE_LOCAL(env, Direction2::ParseArg, Direction_2, d1, info[0]);
    ARGS_PARSE_LOCAL(env, Direction2::ParseArg, Direction_2, d2, info[1]);
    return Napi::Boolean::New(env, mWrapped.counterclockwise_in_between(d1, d2));
}


Napi::Value Direction2::Opposite(Napi::CallbackInfo const& info)
{
    return Direction2::New(info.Env(), -mWrapped);
}


Napi::Value Direction2::ToVector(Napi::CallbackInfo const& info)
{
    return Vector2::New(info.Env(), mWrapped.vector());
}


Napi::Value Direction2::DX(Napi::CallbackInfo const& info)
{
    return Napi::Number::New(info.Env(), CGAL::to_double(mWrapped.dx()));
}


Napi::Value Direction2::DY(Napi::CallbackInfo const& info)
{
    return Napi::Number::New(info.Env(), CGAL::to_double(mWrapped.dy()));
}
