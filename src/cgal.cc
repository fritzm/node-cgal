#include "cgal.h"
#include "cgal_types.h"
#include "AffTransformation2.h"
// #include "Arrangement2.h"
#include "BBox2.h"
#include "Curve2.h"
// #include "D2.h"
#include "Direction2.h"
#include "Line2.h"
// #include "NefPolyhedron2.h"
#include "Point2.h"
#include "Polygon2.h"
// #include "PolygonSet2.h"
// #include "PolygonWithHoles2.h"
#include "Ray2.h"
#include "Segment2.h"
#include "Vector2.h"

using namespace std;

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("NEGATIVE", (int)CGAL::NEGATIVE);
    exports.Set("ZERO", (int)CGAL::ZERO);
    exports.Set("POSITIVE", (int)CGAL::POSITIVE);
    exports.Set("RIGHT_TURN", (int)CGAL::RIGHT_TURN);
    exports.Set("LEFT_TURN", (int)CGAL::LEFT_TURN);
    exports.Set("CLOCKWISE", (int)CGAL::CLOCKWISE);
    exports.Set("COUNTERCLOCKWISE", (int)CGAL::COUNTERCLOCKWISE);
    exports.Set("COLLINEAR", (int)CGAL::COLLINEAR);
    exports.Set("COPLANAR", (int)CGAL::COPLANAR);
    exports.Set("DEGENERATE", (int)CGAL::DEGENERATE);
    exports.Set("ON_NEGATIVE_SIDE", (int)CGAL::ON_NEGATIVE_SIDE);
    exports.Set("ON_ORIENTED_BOUNDARY", (int)CGAL::ON_ORIENTED_BOUNDARY);
    exports.Set("ON_POSITIVE_SIDE", (int)CGAL::ON_POSITIVE_SIDE);
    exports.Set("SMALLER", (int)CGAL::SMALLER);
    exports.Set("EQUAL", (int)CGAL::EQUAL);
    exports.Set("LARGER", (int)CGAL::LARGER);
    exports.Set("ON_UNBOUNDED_SIDE", (int)CGAL::ON_UNBOUNDED_SIDE);
    exports.Set("ON_BOUNDARY", (int)CGAL::ON_BOUNDARY);
    exports.Set("ON_BOUNDED_SIDE", (int)CGAL::ON_BOUNDED_SIDE);
    exports.Set("OBTUSE", (int)CGAL::OBTUSE);
    exports.Set("RIGHT", (int)CGAL::RIGHT);
    exports.Set("ACUTE", (int)CGAL::ACUTE);
    exports.Set("ARR_LEFT_BOUNDARY", (int)CGAL::ARR_LEFT_BOUNDARY);
    exports.Set("ARR_RIGHT_BOUNDARY", (int)CGAL::ARR_RIGHT_BOUNDARY);
    exports.Set("ARR_BOTTOM_BOUNDARY", (int)CGAL::ARR_BOTTOM_BOUNDARY);
    exports.Set("ARR_TOP_BOUNDARY", (int)CGAL::ARR_TOP_BOUNDARY);
    exports.Set("ARR_INTERIOR", (int)CGAL::ARR_INTERIOR);

    AffTransformation2::Init(env, exports);
    // Arrangement2::Init(env, exports);
    BBox2::Init(env, exports);
    Curve2::Init(env, exports);
    // D2::Init(env, exports);
    Direction2::Init(env, exports);
    Line2::Init(env, exports);
    // NefPolyhedron2::Init(env, exports);
    Point2::Init(env, exports);
    Polygon2::Init(env, exports);
    // PolygonSet2::Init(env, exports);
    // PolygonWithHoles2::Init(env, exports);
    Ray2::Init(env, exports);
    Segment2::Init(env, exports);
    Vector2::Init(env, exports);

    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init);


