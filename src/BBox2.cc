#include "BBox2.h"
#include "cgal_args.h"
#include "napi.h"

using namespace std;


BBox2::BBox2(Napi::CallbackInfo const& info)
:   CGALWrapper(info)
{
}


char const* BBox2::Name = "BBox2";


void BBox2::AddProperties(vector<PropertyDescriptor>& properties)
{
    properties.insert(properties.end(), {
        InstanceMethod("overlaps", &BBox2::Overlaps),
        InstanceMethod("add", &BBox2::Add)
    });
}


bool BBox2::ParseArg(Napi::Env env, Napi::Value arg, Bbox_2& receiver)
{
    if (arg.IsObject()) {
        Napi::Object obj = arg.As<Napi::Object>();

        if (obj.InstanceOf(sConstructor.Value())) {
            receiver = Unwrap(obj)->mWrapped;
            return true;
        }

        if (obj.Get("xmin").IsNumber() &&
            obj.Get("ymin").IsNumber() &&
            obj.Get("xmax").IsNumber() &&
            obj.Get("ymax").IsNumber())
        {
            receiver = Bbox_2(
                obj.Get("xmin").As<Napi::Number>(),
                obj.Get("ymin").As<Napi::Number>(),
                obj.Get("xmax").As<Napi::Number>(),
                obj.Get("ymax").As<Napi::Number>()
            );
            return true;
        }
    }

    return false;
}


Napi::Value BBox2::ToPOD(Napi::Env env, bool precise)
{
    Napi::Object obj = Napi::Object::New(env);
    obj.Set("xmin", mWrapped.xmin());
    obj.Set("ymin", mWrapped.ymin());
    obj.Set("xmax", mWrapped.xmax());
    obj.Set("ymax", mWrapped.ymax());
    return obj;
}


Napi::Value BBox2::Overlaps(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);
    ARGS_PARSE_LOCAL(env, BBox2::ParseArg, Bbox_2, otherBox, info[0]);
    return Napi::Boolean::New(env, do_overlap(mWrapped, otherBox));
}


Napi::Value BBox2::Add(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);
    ARGS_PARSE_LOCAL(env, BBox2::ParseArg, Bbox_2, otherBox, info[0]);
    return BBox2::New(env, mWrapped + otherBox);
}
