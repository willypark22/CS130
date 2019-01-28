#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    //TODO;
    //std::cout << "Entered sphere intersection " << std::endl;
    Hit hit;
    vec3 u = ray.direction;
    vec3 v = ray.endpoint - center;
    
    //double a = 1; //u dot u = 1
    double a = u.magnitude_squared();
    double b = 2 * dot(u, v);
    double c = v.magnitude_squared() - (radius * radius);
    double value = (b*b) - (4*a*c);
    double t0, t1;
    if(value < 0) {
	hit = {0, 0, 0};
    }

    else {
	t0 = ((-1)*b + sqrt(value)) / (2*a);
	t1 = ((-1)*b - sqrt(value)) / (2*a);

	if(t0 < t1 && t0 >= small_t) {
		hit = {this, t0, 1};
	}
	else if(t1 <= t0 && t1 >= small_t) {
		hit = {this, t1, 1};
	}
	else {
		hit = {0, 0, 0};
	}
    }
    return hit;
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal = point - center;
    normal = normal.normalized();
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
