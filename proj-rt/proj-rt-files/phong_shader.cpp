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
	vec3 l, r, position, lightEmitted, ambientValue, diffuseValue, specularValue;
	
	//calculate ambient
	ambientValue = world.ambient_color * world.ambient_intensity * color_ambient;
	for(unsigned i = 0; i < world.lights.size(); ++i) {
		//set up
		position = world.lights[i]->position;
		l = position - intersection_point;
		r = -l + 2 * dot(l, normal) * normal;
		r = r.normalized();
		lightEmitted = world.lights[i]->Emitted_Light(l);
		
		//calculate diffuse
		diffuseValue += color_diffuse * lightEmitted * std::max(dot(normal, l.normalized()), 0.0);

		//calculate specular
		//specularValue += color_specular * lightEmitted * std::pow(std::max(dot(r, -(ray.direction)), 0.0), specular_power);

	}
	color = ambientValue + diffuseValue + specularValue;
	return color;
}
