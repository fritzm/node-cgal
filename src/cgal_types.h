#ifndef CGAL_TYPES_H
#define CGAL_TYPES_H

#if CGAL_USE_EPECK
#include "CGAL/Exact_predicates_exact_constructions_kernel.h"
#else
#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#endif

#include "CGAL/Arr_linear_traits_2.h"
#include "CGAL/number_utils.h"
#include "CGAL/Extended_cartesian.h"
#include "CGAL/Bbox_2.h"
#include "CGAL/Partition_traits_2.h"
#include "CGAL/partition_2.h"
#include "CGAL/Segment_2.h"
#include "CGAL/Line_2.h"
#include "CGAL/Ray_2.h"
#include "CGAL/Arrangement_2.h"
#include "CGAL/Polygon_with_holes_2.h"
#include "CGAL/Polygon_set_2.h"

#if CGAL_USE_EPECK
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
#else
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
#endif

typedef CGAL::Bbox_2 Bbox_2;
typedef CGAL::Point_2<K> Point_2;
typedef CGAL::Polygon_set_2<K> Polygon_set_2;
typedef CGAL::Direction_2<K> Direction_2;
typedef CGAL::Segment_2<K> Segment_2;
typedef CGAL::Line_2<K> Line_2;
typedef CGAL::Ray_2<K> Ray_2;
typedef CGAL::Vector_2<K> Vector_2;
typedef CGAL::Rotation Rotation;
typedef CGAL::Aff_transformation_2<K> Aff_transformation_2;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef CGAL::Polygon_with_holes_2<K> Polygon_with_holes_2;
typedef CGAL::Partition_traits_2<K> Partition_Traits_2;
typedef CGAL::Arrangement_2<CGAL::Arr_linear_traits_2<K>> Arrangement_2;
typedef Arrangement_2::Geometry_traits_2::Curve_2 Curve_2;

#endif // !defined(CGAL_TYPES_H)
