#include "plane.h"
#include "ray.h"
#include <cfloat>
#include <limits>

// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
Hit Plane::Intersection(const Ray& ray, int part) const
{
    //TODO;
    std::cout << "Entered plane intersection" << std::endl;
    float t = (dot(normal, (x1 - ray.endpoint))) / dot(normal, ray.direction);
    
    Hit temp;
    
    if(t > 0) {
        temp.object = this;
        temp.dist = t;
        return temp;
    }
    else {
        temp.object = NULL;
    }
    std::cout << "Exit plane intersetion" << std::endl;
    return temp;
}

vec3 Plane::Normal(const vec3& point, int part) const
{
std::cout << "Entred plane normal" << std::endl;
    return normal;
}

// There is not a good answer for the bounding box of an infinite object.
// The safe thing to do is to return a box that contains everything.
Box Plane::Bounding_Box(int part) const
{
    Box b;
    b.hi.fill(std::numeric_limits<double>::max());
    b.lo=-b.hi;
    return b;
}
