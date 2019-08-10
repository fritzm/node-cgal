#include "Line2.h"
#include "Point2.h"

using namespace std;


Line2::Line2(Napi::CallbackInfo const& info)
:   CGALWrapper(info)
{
}


const char *Line2::Name = "Line2";


void Line2::AddProperties(Napi::Env env, vector<PropertyDescriptor>& properties)
{
    properties.insert(properties.end(), {
        InstanceMethod("isEqual", &Line2::IsEqual),
        InstanceMethod("isDegenerate", &Line2::IsDegenerate),
        InstanceMethod("isHorizontal", &Line2::IsHorizontal),
        InstanceMethod("isVertical", &Line2::IsVertical),
        InstanceMethod("opposite", &Line2::Opposite)
    });
}


bool Line2::ParseArg(Napi::Env env, Napi::Value arg, Line_2& receiver)
{
    if (arg.IsObject()) {
        Napi::Object obj = arg.As<Napi::Object>();

        if (obj.InstanceOf(sConstructor.Value())) {
            receiver = Unwrap(obj)->mWrapped;
            return true;
        }

        K::FT a, b, c;
        if (::ParseNumberArg(env, obj["a"], a) &&
            ::ParseNumberArg(env, obj["b"], b) &&
            ::ParseNumberArg(env, obj["c"], c))
        {
            receiver = Line_2(a, b, c);
            return true;
        }

        Point_2 p, q;
        if (Point2::ParseArg(env, obj["p"], p) &&
            Point2::ParseArg(env, obj["q"], q))
        {
            receiver = Line_2(p, q);
            return true;
        }
    }

    return false;
}


Napi::Value Line2::ToPOD(Napi::Env env, Line_2 const& line, bool precise)
{
    Napi::Object obj = Napi::Object::New(env);

    if (precise) {

        ostringstream astr;
#if CGAL_USE_EPECK
        astr << line.a().exact();
#else
        astr << setprecision(20) << line.a();
#endif
        obj.Set("a", astr.str());
        ostringstream bstr;
#if CGAL_USE_EPECK
        bstr << line.b().exact();
#else
        bstr << setprecision(20) << line.b();
#endif
        obj.Set("b", bstr.str());
        ostringstream cstr;
#if CGAL_USE_EPECK
        cstr << line.c().exact();
#else
        cstr << setprecision(20) << line.c();
#endif
        obj.Set("c", cstr.str());

    } else {

        obj.Set("a", CGAL::to_double(line.a()));
        obj.Set("b", CGAL::to_double(line.b()));
        obj.Set("c", CGAL::to_double(line.c()));

    }

    return obj;
}


Napi::Value Line2::IsEqual(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);
    ARGS_PARSE_LOCAL(env, Line2::ParseArg, Line_2, otherLine, info[0]);
    return Napi::Boolean::New(env, mWrapped == otherLine);
}


Napi::Value Line2::IsDegenerate(Napi::CallbackInfo const& info)
{
    return Napi::Boolean::New(info.Env(), mWrapped.is_degenerate());
}


Napi::Value Line2::IsHorizontal(Napi::CallbackInfo const& info)
{
    return Napi::Boolean::New(info.Env(), mWrapped.is_horizontal());
}


Napi::Value Line2::IsVertical(Napi::CallbackInfo const& info)
{
    return Napi::Boolean::New(info.Env(), mWrapped.is_vertical());
}


Napi::Value Line2::Opposite(Napi::CallbackInfo const& info)
{
    return Line2::New(info.Env(), mWrapped.opposite());
}
