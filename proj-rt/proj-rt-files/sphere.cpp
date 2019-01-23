#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    //TODO;
    //std::cout << "Entered sphere intersection " << std::endl;
    vec3 u = ray.direction;
    vec3 v = ray.endpoint - center;
    
    float a = 1; //u dot u = 1
    float b = 2 * dot(u, v);
    float c = dot(v, v) - (radius * radius);
    double value = b*b - 4*a*c;
    
    float t0 = (-b - sqrt(value)) / (2*a);
    float t1 = (-b + sqrt(value)) / (2*a);
        
    Hit hit0, hit1;
    hit0.object = this;
    hit1.object = this;
    
    if(value > 0) {
	if(t0 > 0) {
		hit0.dist = t0;
	}
	else {
	hit0.dist = 0;
	}
    
        hit1.dist = t1;
        hit1.part = 0;
        hit0.part = 0;
    }
    else if(value == 0) {
	hit0.dist = t0;
	hit0.part = 0;
    }
    /*if(value < 0) {
        hit0.object = NULL;
    }
    else if (value == 0) {
        if(
        hit0.dist = t0;
        
    */
    //std::cout << "Exit sphere intersection" << std::endl;
    return hit0;
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    //std::cout << "Entered sphere normal" << std::endl;
    vec3 normal;
    TODO; compute the normal direction
    //std::cout << "Exit normal" << std::endl;
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
