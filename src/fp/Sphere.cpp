#include "Sphere.h"
#include "math/Epsilon.h"

using fp::Sphere;

std::optional<Hit> Sphere::intersect(const Ray &ray) const noexcept {
  // Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
  auto op = centre_ - ray.origin();
  auto radiusSquared = radius_ * radius_;
  auto b = op.dot(ray.direction());
  auto determinant = b * b - op.lengthSquared() + radiusSquared;
  if (determinant < 0)
    return {};

  determinant = sqrt(determinant);
  auto minusT = b - determinant;
  auto plusT = b + determinant;
  if (minusT < Epsilon && plusT < Epsilon)
    return {};

  auto t = minusT > Epsilon ? minusT : plusT;
  auto hitPosition = ray.positionAlong(t);
  auto normal = (hitPosition - centre_).normalised();
  if (normal.dot(ray.direction()) > 0)
    normal = -normal;
  return Hit{t, hitPosition, normal};
}
