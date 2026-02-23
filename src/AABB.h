#pragma once
#include <glm/glm.hpp>
#include <algorithm>

class AABB {
   public:

   glm::vec3 min;
   glm::vec3 max;


   AABB() { reset();}

   void reset() {
      min = glm::vec3( std::numeric_limits<float>::infinity());
      max = glm::vec3(-std::numeric_limits<float>::infinity());
   }

   void expand(const glm::vec3& p){
        min = glm::min(min, p);
        max = glm::max(max, p);
   }

   bool rayIntersect(const glm::vec3& origin, const glm::vec3& invDir, float& enterT, float& exitT) const
   {
      float tmin = (min.x - origin.x) * invDir.x;
      float tmax = (max.x - origin.x) * invDir.x;
      if (tmin > tmax) std::swap(tmin, tmax);

      float tymin = (min.y - origin.y) * invDir.y;
      float tymax = (max.y - origin.y) * invDir.y;
      if (tymin > tymax) std::swap(tymin, tymax);

      if (tmin > tymax || tymin > tmax)
         return false;

      if (tymin > tmin) tmin = tymin;
      if (tymax < tmax) tmax = tymax;

      float tzmin = (min.z - origin.z) * invDir.z;
      float tzmax = (max.z - origin.z) * invDir.z;
      if (tzmin > tzmax) std::swap(tzmin, tzmax);

      if (tmin > tzmax || tzmin > tmax)
         return false;

      tmin = std::max(tmin, tzmin);
      tmax = std::min(tmax, tzmax);

      enterT = tmin;
      exitT  = tmax;
      return exitT >= 0.0f;
   }

   int longestAxis() const {

      glm::vec3 dif = max - min;

      return (dif.x >= dif.y && dif.x >= dif.z) ? 0 : (dif.y >= dif.z) ? 1 : 2;
   }

};

