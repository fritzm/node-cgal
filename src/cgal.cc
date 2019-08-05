#include "cgal.h"
#include "cgal_types.h"
// #include "AffTransformation2.h"
// #include "Arrangement2.h"
#include "BBox2.h"
// #include "Curve2.h"
// #include "D2.h"
// #include "Direction2.h"
// #include "Line2.h"
// #include "NefPolyhedron2.h"
#include "Point2.h"
// #include "Polygon2.h"
// #include "PolygonSet2.h"
// #include "PolygonWithHoles2.h"
// #include "Ray2.h"
// #include "Segment2.h"
// #include "Vector2.h"

using namespace std;

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    // exports.Set("NEGATIVE", CGAL::NEGATIVE);
    // exports.Set("ZERO", CGAL::ZERO);
    // exports.Set("POSITIVE", CGAL::POSITIVE);
    // exports.Set("RIGHT_TURN", CGAL::RIGHT_TURN);
    // exports.Set("LEFT_TURN", CGAL::LEFT_TURN);
    // exports.Set("CLOCKWISE", CGAL::CLOCKWISE);
    // exports.Set("COUNTERCLOCKWISE", CGAL::COUNTERCLOCKWISE);
    // exports.Set("COLLINEAR", CGAL::COLLINEAR);
    // exports.Set("COPLANAR", CGAL::COPLANAR);
    // exports.Set("DEGENERATE", CGAL::DEGENERATE);
    // exports.Set("ON_NEGATIVE_SIDE", CGAL::ON_NEGATIVE_SIDE);
    // exports.Set("ON_ORIENTED_BOUNDARY", CGAL::ON_ORIENTED_BOUNDARY);
    // exports.Set("ON_POSITIVE_SIDE", CGAL::ON_POSITIVE_SIDE);
    // exports.Set("SMALLER", CGAL::SMALLER);
    // exports.Set("EQUAL", CGAL::EQUAL);
    // exports.Set("LARGER", CGAL::LARGER);
    // exports.Set("ON_UNBOUNDED_SIDE", CGAL::ON_UNBOUNDED_SIDE);
    // exports.Set("ON_BOUNDARY", CGAL::ON_BOUNDARY);
    // exports.Set("ON_BOUNDED_SIDE", CGAL::ON_BOUNDED_SIDE);
    // exports.Set("OBTUSE", CGAL::OBTUSE);
    // exports.Set("RIGHT", CGAL::RIGHT);
    // exports.Set("ACUTE", CGAL::ACUTE);
    // exports.Set("ARR_LEFT_BOUNDARY", CGAL::ARR_LEFT_BOUNDARY);
    // exports.Set("ARR_RIGHT_BOUNDARY", CGAL::ARR_RIGHT_BOUNDARY);
    // exports.Set("ARR_BOTTOM_BOUNDARY", CGAL::ARR_BOTTOM_BOUNDARY);
    // exports.Set("ARR_TOP_BOUNDARY", CGAL::ARR_TOP_BOUNDARY);
    // exports.Set("ARR_INTERIOR", CGAL::ARR_INTERIOR);

    // AffTransformation2::Init(env, exports);
    // Arrangement2::Init(env, exports);
    BBox2::Init(env, exports);
    // Curve2::Init(env, exports);
    // D2::Init(env, exports);
    // Direction2::Init(env, exports);
    // Line2::Init(env, exports);
    // NefPolyhedron2::Init(env, exports);
    Point2::Init(env, exports);
    // Polygon2::Init(env, exports);
    // PolygonSet2::Init(env, exports);
    // PolygonWithHoles2::Init(env, exports);
    // Ray2::Init(env, exports);
    // Segment2::Init(env, exports);
    // Vector2::Init(env, exports);

    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init);


