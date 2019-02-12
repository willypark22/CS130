#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
  vec3 color;
  vec3 l, r, position, lightEmitted, ambientValue, diffuseValue, specularValue, lightPosition;

  //calculate ambient
  ambientValue = world.ambient_color * world.ambient_intensity * color_ambient;
  for(unsigned int i = 0; i < world.lights.size(); i++) {
    //set up
    l = world.lights.at(i)->position - intersection_point;
    Ray shadowRay;
    shadowRay.endpoint = intersection_point;
    shadowRay.direction = l;
    Hit hit = world.Closest_Intersection(shadowRay);
    lightEmitted = world.lights.at(i)->Emitted_Light(l);
    vec3 object = shadowRay.Point(hit.dist);

    if(!world.enable_shadows || (!hit.object || object.magnitude() > l.normalized().magnitude())) {
      r = -l + 2 * dot(l, normal) * normal;
      r = r.normalized();

      //calculate diffuse
      diffuseValue += color_diffuse * lightEmitted * std::max(dot(normal, l.normalized()), 0.0);

      //calculate specular
      specularValue += color_specular * lightEmitted * std::pow(std::max(dot(r, -(ray.direction.normalized())), 0.0), specular_power);
    }
  }
  color = ambientValue + diffuseValue + specularValue;
  return color;
}
