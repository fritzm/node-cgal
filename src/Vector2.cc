#include "Vector2.h"
#include "Point2.h"
#include "Line2.h"
#include "NumberTypes.h"
#include "Segment2.h"
#include "Ray2.h"
#include "cgal_args.h"

using namespace std;


Vector2::Vector2(Napi::CallbackInfo const& info)
:   CGALWrapper(info)
{
}


const char *Vector2::Name = "Vector2";


void Vector2::AddProperties(Napi::Env env, vector<PropertyDescriptor>& properties)
{
}


bool Vector2::ParseArg(Napi::Env env, Napi::Value arg, Vector_2& receiver)
{
    if (arg.IsObject() && arg.As<Napi::Object>().InstanceOf(sConstructor.Value())) {
        receiver = Unwrap(arg.As<Napi::Object>())->mWrapped;
        return true;
    }

    Line_2 line;
    if (Line2::ParseArg(env, arg, line)) {
        receiver = Vector_2(line);
        return true;
    }

    Segment_2 segment;
    if (Segment2::ParseArg(env, arg, segment)) {
        receiver = Vector_2(segment);
        return true;
    }

    Ray_2 ray;
    if (Ray2::ParseArg(env, arg, ray)) {
        receiver = Vector_2(ray);
        return true;
    }

    if (arg.IsObject()) {
        Napi::Object inits = arg.As<Napi::Object>();
        K::FT x, y;
        if (FieldNumberType::ParseArg(env, inits["x"], x) &&
            FieldNumberType::ParseArg(env, inits["y"], y))
        {
            receiver = Vector_2(x, y);
            return true;
        }

    }

    return false;
}


Napi::Value Vector2::ToPOD(Napi::Env env, Vector_2 const& vector, bool precise)
{
    Napi::Object obj = Napi::Object::New(env);
    obj.Set("x", FieldNumberType::ToPOD(env, vector.x(), precise));
    obj.Set("y", FieldNumberType::ToPOD(env, vector.y(), precise));
    return obj;
}
