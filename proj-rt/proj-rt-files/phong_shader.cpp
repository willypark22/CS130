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
	//TODO; determine the color
	vec3 l, r, lightSource, intersected;
	color = world.ambient_color * world.ambient_intensity * color_ambient;
	/*for(unsigned i = 0; i < world.lights.size(); ++i) {
		l = world.lights[i]->position - intersection_point;
		color += color_diffuse * world.lights[i]->Emitted_Light(l) * std::max(dot(normal, l.normalized()), 0.0);
		r = -l + 2 * (dot(l, normal)) * normal;
		color += color_specular * world.lights[i]->Emitted_Light(l) * std::pow(std::max(dot(ray.direction, r.normalized()), 0.0), specular_power);
		
		l = world.lights[i]->Emitted_Light(ray);
		lightSource = world.lights[i]->position;
		intersected = intersection_point - lightSource;
		r = -l + 2 * (dot(l, normal) * normal;
		r = r.normalized();
	}*/
	return color;
}
