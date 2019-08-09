#include "PolygonSet2.h"
#include "PolygonWithHoles2.h"
#include "Arrangement2.h"
#include "Polygon2.h"
#include "Point2.h"
#include "cgal_args.h"

using namespace std;


PolygonSet2::PolygonSet2(Napi::CallbackInfo const& info)
:   CGALWrapper(info)
{
}


const char *PolygonSet2::Name = "PolygonSet2";

ostream &operator<<(ostream &str, const Polygon_set_2 &polySet)
{
    return str;
}


void PolygonSet2::AddProperties(std::vector<PropertyDescriptor>& properties)
{
    properties.insert(properties.end(), {
        InstanceMethod("polygonsWithHoles", &PolygonSet2::PolygonsWithHoles),
        InstanceMethod("numPolygonsWithHoles", &PolygonSet2::NumPolygonsWithHoles),
        InstanceMethod("isEmpty", &PolygonSet2::IsEmpty),
        InstanceMethod("isPlane", &PolygonSet2::IsPlane),
        // InstanceMethod("arrangement", &PolygonSet2::Arrangement),
        InstanceMethod("clear", &PolygonSet2::Clear),
        InstanceMethod("complement", &PolygonSet2::Complement),
        InstanceMethod("intersection", &PolygonSet2::Intersection),
        InstanceMethod("join", &PolygonSet2::Join),
        InstanceMethod("difference", &PolygonSet2::Difference),
        InstanceMethod("symmetricDifference", &PolygonSet2::SymmetricDifference),
        InstanceMethod("intersects", &PolygonSet2::Intersects),
        // InstanceMethod("locate", &PolygonSet2::Locate),
        InstanceMethod("insert", &PolygonSet2::Insert),
        InstanceMethod("orientedSide", &PolygonSet2::OrientedSide),
        InstanceMethod("isValid", &PolygonSet2::IsValid)
    });
}


bool PolygonSet2::ParseArg(Napi::Env env, Napi::Value arg, Polygon_set_2& receiver)
{
    if (arg.IsObject() && arg.As<Napi::Object>().InstanceOf(sConstructor.Value())) {
        receiver = Unwrap(arg.As<Napi::Object>())->mWrapped;
        return true;
    }

    Polygon_2 poly;
    if (Polygon2::ParseArg(env, arg, poly)) {
        receiver = Polygon_set_2(poly);
        return true;
    }

    Polygon_with_holes_2 pwh;
    if (PolygonWithHoles2::ParseArg(env, arg, pwh)) {
        receiver = Polygon_set_2(pwh);
        return true;
    }

    return false;
}


Napi::Value PolygonSet2::ToPOD(Napi::Env env, Polygon_set_2 const& polys, bool precise)
{
    vector<Polygon_with_holes_2> pwhs;
    polys.polygons_with_holes(back_inserter(pwhs));
    return PolygonWithHoles2::SeqToPOD(env, pwhs.begin(), pwhs.end(), precise);
}


Napi::Value PolygonSet2::PolygonsWithHoles(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    vector<Polygon_with_holes_2> pwhs;
    mWrapped.polygons_with_holes(back_inserter(pwhs));
    Napi::Array array = Napi::Array::New(env);
    uint32_t i;
    vector<Polygon_with_holes_2>::iterator it;
    for(it=pwhs.begin(),i=0; it!=pwhs.end(); ++it,++i) {
        array.Set(i, PolygonWithHoles2::New(env, *it));
    }
    return array;
}


Napi::Value PolygonSet2::NumPolygonsWithHoles(Napi::CallbackInfo const& info)
{
    return Napi::Number::New(info.Env(), mWrapped.number_of_polygons_with_holes());
}


Napi::Value PolygonSet2::IsEmpty(Napi::CallbackInfo const& info)
{
    return Napi::Boolean::New(info.Env(), mWrapped.is_empty());
}


Napi::Value PolygonSet2::IsPlane(Napi::CallbackInfo const& info)
{
    return Napi::Boolean::New(info.Env(), mWrapped.is_plane());
}


// Napi::Value PolygonSet2::Arrangement(Napi::CallbackInfo const& info)
// {
//     return Arrangement2::New(info.Env(), mWrapped.arrangement());
// }


Napi::Value PolygonSet2::Clear(Napi::CallbackInfo const& info)
{
    mWrapped.clear();
    return info.Env().Undefined();
}


Napi::Value PolygonSet2::Insert(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);

    Polygon_2 poly;
    if (Polygon2::ParseArg(env, info[0], poly)) {
        mWrapped.insert(poly);
        return env.Undefined();
    }

    Polygon_with_holes_2 pwh;
    if (PolygonWithHoles2::ParseArg(env, info[0], pwh)) {
        mWrapped.insert(pwh);
        return env.Undefined();
    }

    ARGS_ASSERT(env, false);
}


Napi::Value PolygonSet2::Complement(Napi::CallbackInfo const& info)
{
    mWrapped.complement();
    return info.Env().Undefined();
}


Napi::Value PolygonSet2::Intersection(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);

    Polygon_2 poly;
    if (Polygon2::ParseArg(env, info[0], poly)) {
        mWrapped.intersection(poly);
        return env.Undefined();
    }

    Polygon_with_holes_2 pwh;
    if (PolygonWithHoles2::ParseArg(env, info[0], pwh)) {
        mWrapped.intersection(pwh);
        return env.Undefined();
    }

    Polygon_set_2 polySet2;
    if (PolygonSet2::ParseArg(env, info[0], polySet2)) {
        mWrapped.intersection(polySet2);
        return env.Undefined();
    }

    ARGS_ASSERT(env, false);
}


Napi::Value PolygonSet2::Join(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);

    Polygon_2 poly;
    if (Polygon2::ParseArg(env, info[0], poly)) {
        mWrapped.join(poly);
        return env.Undefined();
    }

    Polygon_with_holes_2 pwh;
    if (PolygonWithHoles2::ParseArg(env, info[0], pwh)) {
        mWrapped.join(pwh);
        return env.Undefined();
    }

    Polygon_set_2 polySet2;
    if (PolygonSet2::ParseArg(env, info[0], polySet2)) {
        mWrapped.join(polySet2);
        return env.Undefined();
    }

    ARGS_ASSERT(env, false);
}


Napi::Value PolygonSet2::Difference(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);

    Polygon_2 poly;
    if (Polygon2::ParseArg(env, info[0], poly)) {
        mWrapped.difference(poly);
        return env.Undefined();
    }

    Polygon_with_holes_2 pwh;
    if (PolygonWithHoles2::ParseArg(env, info[0], pwh)) {
        mWrapped.difference(pwh);
        return env.Undefined();
    }

    Polygon_set_2 polySet2;
    if (PolygonSet2::ParseArg(env, info[0], polySet2)) {
        mWrapped.difference(polySet2);
        return env.Undefined();
    }

    ARGS_ASSERT(env, false);
}


Napi::Value PolygonSet2::SymmetricDifference(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);

    Polygon_2 poly;
    if (Polygon2::ParseArg(env, info[0], poly)) {
        mWrapped.symmetric_difference(poly);
        return env.Undefined();
    }

    Polygon_with_holes_2 pwh;
    if (PolygonWithHoles2::ParseArg(env, info[0], pwh)) {
        mWrapped.symmetric_difference(pwh);
        return env.Undefined();
    }

    Polygon_set_2 polySet2;
    if (PolygonSet2::ParseArg(env, info[0], polySet2)) {
        mWrapped.symmetric_difference(polySet2);
        return env.Undefined();
    }

    ARGS_ASSERT(env, false);
}


Napi::Value PolygonSet2::Intersects(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);

    Polygon_2 poly;
    if (Polygon2::ParseArg(env, info[0], poly)) {
        return Napi::Boolean::New(env, mWrapped.do_intersect(poly));
    }

    Polygon_with_holes_2 pwh;
    if (PolygonWithHoles2::ParseArg(env, info[0], pwh)) {
        return Napi::Boolean::New(env, mWrapped.do_intersect(pwh));
    }

    Polygon_set_2 polySet2;
    if (PolygonSet2::ParseArg(env, info[0], polySet2)) {
        return Napi::Boolean::New(env, mWrapped.do_intersect(polySet2));
    }

    ARGS_ASSERT(env, false);
}


// Napi::Value PolygonSet2::Locate(Napi::CallbackInfo const& info)
// {
//         Polygon_set_2 &polySet = ExtractWrapped(info.This());
//         ARGS_ASSERT(env, info.Length() == 2);
//         ARGS_PARSE_LOCAL(env, Point2::ParseArg, Point_2, point, info[0]);
//         ARGS_PARSE_LOCAL(env, PolygonWithHoles2::ParseArg, Polygon_with_holes_2, pwh, info[1]);
//         info.GetReturnValue().Set(Boolean::New(env, mWrapped.locate(point, pwh)));
// }


Napi::Value PolygonSet2::OrientedSide(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);

    Point_2 point;
    if (Point2::ParseArg(env, info[0], point)) {
        return Napi::Number::New(env, mWrapped.oriented_side(point));
    }

    Polygon_2 poly;
    if (Polygon2::ParseArg(env, info[0], poly)) {
        return Napi::Number::New(env, mWrapped.oriented_side(poly));
    }

    Polygon_with_holes_2 pwh;
    if (PolygonWithHoles2::ParseArg(env, info[0], pwh)) {
        return Napi::Number::New(env, mWrapped.oriented_side(pwh));
    }

    Polygon_set_2 polySet2;
    if (PolygonSet2::ParseArg(env, info[0], polySet2)) {
        return Napi::Number::New(env, mWrapped.oriented_side(polySet2));
    }

    ARGS_ASSERT(env, false);
}


Napi::Value PolygonSet2::IsValid(Napi::CallbackInfo const& info)
{
    return Napi::Boolean::New(info.Env(), mWrapped.is_valid());
}
