#include "Segment2.h"
#include "Point2.h"
#include "cgal_args.h"


using namespace std;


Segment2::Segment2(Napi::CallbackInfo const& info)
:   CGALWrapper(info)
{
}


const char *Segment2::Name = "Segment2";


void Segment2::AddProperties(vector<PropertyDescriptor>& properties)
{
    properties.insert(properties.end(), {
        InstanceMethod("isHorizontal", &Segment2::IsHorizontal),
        InstanceMethod("isVertical", &Segment2::IsVertical)
    });
}


bool Segment2::ParseArg(Napi::Env env, Napi::Value arg, Segment_2& receiver)
{
    if (arg.IsObject()) {
        Napi::Object obj = arg.As<Napi::Object>();

        if (obj.InstanceOf(sConstructor.Value())) {
            receiver = Unwrap(obj)->mWrapped;
            return true;
        }

        Point_2 source, target;
        if (Point2::ParseArg(env, obj["source"], source) &&
            Point2::ParseArg(env, obj["target"], target))
        {
            receiver = Segment_2(source, target);
            return true;
        }
    }

    return false;
}


Napi::Value Segment2::ToPOD(Napi::Env env, Segment_2 const& segment, bool precise)
{
    Napi::Object obj = Napi::Object::New(env);
    obj.Set("source", Point2::ToPOD(env, segment.source(), precise));
    obj.Set("target", Point2::ToPOD(env, segment.target(), precise));
    return obj;
}


Napi::Value Segment2::IsHorizontal(Napi::CallbackInfo const& info)
{
    return Napi::Value::From(info.Env(), mWrapped.is_horizontal());
}


Napi::Value Segment2::IsVertical(Napi::CallbackInfo const& info)
{
    return Napi::Value::From(info.Env(), mWrapped.is_vertical());
}
