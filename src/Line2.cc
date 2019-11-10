#include "Line2.h"
#include "NumberTypes.h"
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
        if (FieldNumberType::ParseArg(env, obj["a"], a) &&
            FieldNumberType::ParseArg(env, obj["b"], b) &&
            FieldNumberType::ParseArg(env, obj["c"], c))
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
    obj.Set("a", FieldNumberType::ToPOD(env, line.a(), precise));
    obj.Set("b", FieldNumberType::ToPOD(env, line.b(), precise));
    obj.Set("c", FieldNumberType::ToPOD(env, line.c(), precise));
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
