#include "D2.h"
#include "cgal_args.h"
#include "cgal_types.h"
#include "AffTransformation2.h"
#include "Point2.h"
#include "Polygon2.h"
#include "PolygonWithHoles2.h"
#include "CGAL/Boolean_set_operations_2.h"

using namespace std;


Napi::Object D2::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("doIntersect", Napi::Function::New(env, DoIntersect));
    exports.Set("convexPartition2", Napi::Function::New(env, ConvexPartition2));
    exports.Set("convexHull2", Napi::Function::New(env, ConvexHull2));
    exports.Set("collinear", Napi::Function::New(env, Collinear));
    return exports;
}


Napi::Value DoIntersect(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 2);

    Polygon_2 poly0;
    if (Polygon2::ParseArg(env, info[0], poly0)) {
        Polygon_2 poly1;
        if (Polygon2::ParseArg(env, info[1], poly1)) {
            return Napi::Boolean::New(env, CGAL::do_intersect(poly0, poly1));
        }
        Polygon_with_holes_2 pwh1;
        if (PolygonWithHoles2::ParseArg(env, info[1], pwh1)) {
            return Napi::Boolean::New(env, CGAL::do_intersect(poly0, pwh1));
        }
        ARGS_ASSERT(env, false);
    }

    Polygon_with_holes_2 pwh0;
    if (PolygonWithHoles2::ParseArg(env, info[0], pwh0)) {
        Polygon_2 poly1;
        if (Polygon2::ParseArg(env, info[1], poly1)) {
            return Napi::Boolean::New(env, CGAL::do_intersect(pwh0, poly1));
        }
        Polygon_with_holes_2 pwh1;
        if (PolygonWithHoles2::ParseArg(env, info[1], pwh1)) {
            return Napi::Boolean::New(env, CGAL::do_intersect(pwh0, pwh1));
        }
        ARGS_ASSERT(env, false);
    }

    ARGS_ASSERT(env, false);
}


Napi::Value ConvexPartition2(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);
    ARGS_PARSE_LOCAL(env, Polygon2::ParseArg, Polygon_2, inputPoly, info[0]);
    Partition_Traits_2 partition_traits;
    list<Partition_Traits_2::Polygon_2> partition;
    CGAL::approx_convex_partition_2(
        inputPoly.vertices_begin(), inputPoly.vertices_end(),
        back_inserter(partition),
        partition_traits
    );
    Napi::Array array = Napi::Array::New(env);
    uint32_t i;
    list<Partition_Traits_2::Polygon_2>::iterator it;
    for(it=partition.begin(),i=0; it!=partition.end(); ++it,++i) {
        array.Set(i, Polygon2::New(env, Polygon_2(it->vertices_begin(), it->vertices_end())));
    }
    return array;
}


Napi::Value ConvexHull2(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 1);
    ARGS_PARSE_LOCAL_SEQ(env, Point2::ParseSeqArg, list<Point_2>, points, info[0]);
    list<Point_2> hull;
    CGAL::convex_hull_2(points.begin(), points.end(), back_inserter(hull));
    Napi::Array array = Napi::Array::New(env);
    uint32_t i;
    list<Point_2>::iterator it;
    for(it=hull.begin(),i=0; it!=hull.end(); ++it,++i) {
        array.Set(i, Point2::New(env, *it));
    }
    return array;
}


Napi::Value Collinear(Napi::CallbackInfo const& info)
{
    Napi::Env env = info.Env();
    ARGS_ASSERT(env, info.Length() == 3);
    ARGS_PARSE_LOCAL(env, Point2::ParseArg, Point_2, p0, info[0])
    ARGS_PARSE_LOCAL(env, Point2::ParseArg, Point_2, p1, info[1])
    ARGS_PARSE_LOCAL(env, Point2::ParseArg, Point_2, p2, info[2])
    return Napi::Boolean::New(env, CGAL::collinear(p0, p1, p2));
}
