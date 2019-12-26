#ifndef D2_H
#define D2_H

#include "cgal_types.h"
#include "CGAL/convex_hull_2.h"
#include "napi.h"

namespace D2
{
    // Add function templates for CGAL global 2d functions to the package exports.  Called at module
    // load time via the module init function.
    Napi::Object Init(Napi::Env env, Napi::Object exports);
}

// Takes a Polygon2 constructable and returns an array of Polygon2 objects that are an approximately
// optimal (within 4x) partition of the origin polygon into convex sub-polygons.
Napi::Value ConvexPartition2(Napi::CallbackInfo const& info);

// Takes an array of Point2 constructables and returns the convex hull of those points as an array
// of Point2 objects.
Napi::Value ConvexHull2(Napi::CallbackInfo const& info);

// Takes two Polygon2 or PolygonWithHoles2 constructables (or a mix) and returns true if they
// intersect.
Napi::Value DoIntersect(Napi::CallbackInfo const& info);

Napi::Value Collinear(Napi::CallbackInfo const& info);

Napi::Value Midpoint(Napi::CallbackInfo const& info);

#endif // !defined(D2_H)
