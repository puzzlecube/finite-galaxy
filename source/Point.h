// Point.h

#ifndef POINT_H_
#define POINT_H_

#ifdef __SSE3__
#include <pmmintrin.h>
#endif



// Class representing a 2D point with functions for a variety of vector operations.
// A Point can represent either a location or a vector (e.g. a velocity, or a
// distance between two points, or a unit vector representing a direction). All
// basic mathematical operations that make sense for vectors are supported.
// Internally the coordinates are stored in a SSE vector and the processor's vector
// extensions are used to optimize all operations.
class Point {
public:
  Point();
  Point(double x, double y);
  Point(const Point &point);
  
  Point &operator=(const Point &point);
  
  // Check if the point is anything but (0, 0).
  explicit operator bool() const;
  bool operator!() const;
  
  // No comparison operators are provided because I never expect to use them
  // and because comparisons with doubles are inherently unsafe due to the
  // possibility of rounding errors and imprecision.
  
  Point operator+(const Point &point) const;
  Point &operator+=(const Point &point);
  Point operator-(const Point &point) const;
  Point &operator-=(const Point &point);
  Point operator-() const;
  
  Point operator*(double scalar) const;
  friend Point operator*(double scalar, const Point &point);
  Point &operator*=(double scalar);
  Point operator/(double scalar) const;
  Point &operator/=(double scalar);
  
  Point operator*(const Point &other) const;
  Point &operator*=(const Point &other);
  
  double &X();
  const double &X() const;
  double &Y();
  const double &Y() const;
  
  void Set(double x, double y);
  
  // Operations that treat this point as a vector from (0, 0):
  double Dot(const Point &point) const;
  double Cross(const Point &point) const;
  
  double Length() const;
  double LengthSquared() const;
  Point Unit() const;
  
  double Distance(const Point &point) const;
  double DistanceSquared(const Point &point) const;
  
  friend Point abs(const Point &p);
  friend Point min(const Point &p, const Point &q);
  friend Point max(const Point &p, const Point &q);
  
  
private:
#ifdef __SSE3__
  // Private constructor, using a vector.
  explicit Point(const __m128d &v);
  
  
private:
  union {
    __m128d v;
    struct {
      double x;
      double y;
    };
  };
#else
  double x;
  double y;
#endif
};



// Inline accessor functions, for speed:
inline double &Point::X()
{
  return x;
}



inline const double &Point::X() const
{
  return x;
}



inline double &Point::Y()
{
  return y;
}



inline const double &Point::Y() const
{
  return y;
}



#endif
