#include "Vector2.h"
#include "Point2.h"
#include "Line2.h"
#include "Segment2.h"
#include "Ray2.h"
#include "cgal_args.h"

using namespace std;


Vector2::Vector2(Napi::CallbackInfo const& info)
:   CGALWrapper(info)
{
}


const char *Vector2::Name = "Vector2";


void Vector2::AddProperties(std::vector<PropertyDescriptor>& properties)
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
        if (::ParseNumberArg(env, inits["x"], x) &&
            ::ParseNumberArg(env, inits["y"], y))
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
    if (precise) {

        ostringstream xstr;
#if CGAL_USE_EPECK
        xstr << vector.x().exact();
#else
        xstr << setprecision(20) << vector.x();
#endif
        obj.Set("x", xstr.str());
        ostringstream ystr;
#if CGAL_USE_EPECK
        ystr << vector.y().exact();
#else
        ystr << setprecision(20) << vector.y();
#endif
        obj.Set("y", ystr.str());

    } else {

        obj.Set("x", CGAL::to_double(vector.x()));
        obj.Set("y", CGAL::to_double(vector.y()));

    }

    return obj;
}
