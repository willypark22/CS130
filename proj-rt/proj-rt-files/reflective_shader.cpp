#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    color = (1 - reflectivity) * shader->Shade_Surface(ray, intersection_point, normal, recursion_depth);
    vec3 d = ray.direction;
    vec3 reflection = d - 2 * (dot(d, normal)) * normal;
    Ray reflectionRay(intersection_point, reflection);
    if((recursion_depth < world.recursion_depth_limit) && (recursion_depth >= 1)) {
      color += (reflectivity * world.Cast_Ray(reflectionRay, ++recursion_depth));
    }
    return color;
}
