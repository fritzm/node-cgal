#include "Curve2.h"
#include "Line2.h"
#include "Point2.h"
#include "Segment2.h"
#include "Ray2.h"
#include "cgal_args.h"

using namespace std;


Curve2::Curve2(Napi::CallbackInfo const& info)
:   CGALWrapper(info)
{
}


const char *Curve2::Name = "Curve2";


void Curve2::AddProperties(std::vector<PropertyDescriptor>& properties)
{
    properties.insert(properties.end(), {
        InstanceMethod("isSegment", &Curve2::IsSegment),
        InstanceMethod("segment", &Curve2::Segment),
        InstanceMethod("isRay", &Curve2::IsRay),
        InstanceMethod("ray", &Curve2::Ray),
        InstanceMethod("isLine", &Curve2::IsLine),
        InstanceMethod("line", &Curve2::Line),
        InstanceMethod("supportingLine", &Curve2::SupportingLine),
        InstanceMethod("source", &Curve2::Source),
        InstanceMethod("target", &Curve2::Target)
    });
}


bool Curve2::ParseArg(Napi::Env env, Napi::Value arg, Curve_2& receiver)
{
    if (arg.IsObject() && arg.As<Napi::Object>().InstanceOf(sConstructor.Value())) {
        receiver = Unwrap(arg.As<Napi::Object>())->mWrapped;
        return true;
    }

    Segment_2 segment;
    if (Segment2::ParseArg(env, arg, segment)) {
        receiver = Curve_2(segment);
        return true;
    }

    Line_2 line;
    if (Line2::ParseArg(env, arg, line)) {
        receiver = Curve_2(line);
        return true;
    }

    Ray_2 ray;
    if (Ray2::ParseArg(env, arg, ray)) {
        receiver = Curve_2(ray);
        return true;
    }

    return false;
}


Napi::Value Curve2::ToPOD(Napi::Env env, Curve_2 const& curve, bool precise)
{
    Napi::Object obj = Napi::Object::New(env);
    return obj;
}


Napi::Value Curve2::IsSegment(Napi::CallbackInfo const& info)
{
    return Napi::Boolean::New(info.Env(), mWrapped.is_segment());
}


Napi::Value Curve2::Segment(Napi::CallbackInfo const& info)
{
    return Segment2::New(info.Env(), mWrapped.segment());
}


Napi::Value Curve2::IsRay(Napi::CallbackInfo const& info)
{
    return Napi::Boolean::New(info.Env(), mWrapped.is_ray());
}


Napi::Value Curve2::Ray(Napi::CallbackInfo const& info)
{
    return Ray2::New(info.Env(), mWrapped.ray());
}


Napi::Value Curve2::IsLine(Napi::CallbackInfo const& info)
{
    return Napi::Boolean::New(info.Env(), mWrapped.is_line());
}


Napi::Value Curve2::Line(Napi::CallbackInfo const& info)
{
    return Line2::New(info.Env(), mWrapped.line());
}


Napi::Value Curve2::SupportingLine(Napi::CallbackInfo const& info)
{
    return Line2::New(info.Env(), mWrapped.supporting_line());
}


Napi::Value Curve2::Source(Napi::CallbackInfo const& info)
{
    return Point2::New(info.Env(), mWrapped.source());
}


Napi::Value Curve2::Target(Napi::CallbackInfo const& info)
{
    return Point2::New(info.Env(), mWrapped.target());
}
