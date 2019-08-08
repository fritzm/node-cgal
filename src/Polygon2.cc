#include "Polygon2.h"
#include "Point2.h"
// #include "AffTransformation2.h"
#include "cgal_args.h"

using namespace std;


Polygon2::Polygon2(Napi::CallbackInfo const& info)
:   CGALWrapper(info)
{
}


const char *Polygon2::Name = "Polygon2";


void Polygon2::AddProperties(std::vector<PropertyDescriptor>& properties)
{
    properties.insert(properties.end(),{
        InstanceMethod("isEqual", &Polygon2::IsEqual),
        InstanceMethod("isSimple", &Polygon2::IsSimple),
        InstanceMethod("isConvex", &Polygon2::IsConvex),
        InstanceMethod("orientation", &Polygon2::Orientation),
        InstanceMethod("orientedSide", &Polygon2::OrientedSide),
        InstanceMethod("boundedSide", &Polygon2::BoundedSide),
        InstanceMethod("area", &Polygon2::Area),
        InstanceMethod("coords", &Polygon2::Coords)
        // NODE_SET_METHOD(constructorTemplate, "transform", Transform);
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


Napi::Value Polygon2::ToPOD(Napi::Env env, Polygon_2 const& box, bool precise)
{
    return Point2::SeqToPOD(env, box.vertices_begin(), box.vertices_end(), precise);
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
    return Napi::Number::New(info.Env(), mWrapped.area());
}


// void Polygon2::Transform(const FunctionCallbackInfo<Value> &info)
// {
//   Isolate *isolate = info.GetIsolate();
//   HandleScope scope(isolate);
//   try {
//     ARGS_ASSERT(isolate, info.Length() == 2);

//     Aff_transformation_2 afft;
//     if (!AffTransformation2::ParseArg(isolate, info[0], afft)) {
//       ARGS_ASSERT(isolate, false);
//     }

//     Polygon_2 poly;
//     if (!ParseArg(isolate, info[1], poly)) {
//       ARGS_ASSERT(isolate, false);
//     }

//     Polygon_2 xpoly = CGAL::transform(afft, poly);
//     info.GetReturnValue().Set(New(isolate, xpoly));
//   }
//   catch (const exception &e) {
//     isolate->ThrowException(String::NewFromUtf8(isolate, e.what(), NewStringType::kNormal).ToLocalChecked());
//   }
// }


Napi::Value Polygon2::Coords(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    Napi::Array array;
    Vertex_iterator it;
    uint32_t i;
    for(it=mWrapped.vertices_begin(),i=0; it!=mWrapped.vertices_end(); ++it,++i) {
        array[i] = Point2::New(env, *it);
    }
    return array;
}
