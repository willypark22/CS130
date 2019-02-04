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

	for(unsigned i = 0; i < world.lights.size(); ++i) {

		//set up
		lightPosition = world.lights[i]->position;
		l = lightPosition - intersection_point;
		Ray shadowRay;
		shadowRay.endpoint = intersection_point;
		shadowRay.direction = l;
		Hit hit = world.Closest_Intersection(shadowRay);
		lightEmitted = world.lights[i]->Emitted_Light(l);

		if(!world.enable_shadows || !hit.object) {
			r = -l + 2 * dot(l, normal) * normal;
			r = r.normalized();
		
			//calculate diffuse
			diffuseValue += color_diffuse * lightEmitted * std::max(dot(normal, l.normalized()), 0.0);

			//calculate specular
			specularValue += color_specular * lightEmitted * std::pow(std::max(dot(r, -(ray.direction)), 0.0), specular_power);
		}
		
	}
	color = ambientValue + diffuseValue + specularValue;
	return color;
}
