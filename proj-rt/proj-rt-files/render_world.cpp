#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"

extern bool disable_hierarchy;

Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
Hit Render_World::Closest_Intersection(const Ray& ray)
{
    std::cout << "Entered closest_intersection" << std::endl;
    //;
    int min_t = std::numeric_limits<int>::max();
    Hit closest;
    for(unsigned i = 0; i < this->objects.size(); ++i) {
        Hit temp = this->objects.at(i)->Intersection(ray, objects.at(i)->number_parts);
        if(temp.object != NULL) {
            if(temp.dist < min_t && temp.dist > small_t) {
                min_t = temp.dist;
                closest = temp;
            }
        }
    }
    std::cout << "Exit closest_intersection" << std::endl;
    return closest;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    std::cout << "Entered render pixel" << std::endl;
    //  set up the initial view ray here
    Ray ray;
    vec3 end_point = camera.position;
    vec3 direction = this->camera.World_Position(pixel_index).normalized();
    ray.endpoint = end_point;
    ray.direction = direction;
    vec3 color = Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
    std::cout << "Exit render pixel" << std::endl;
}

void Render_World::Render()
{
    if(!disable_hierarchy)
        Initialize_Hierarchy();

    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    std::cout << "Entered cast ray " << std::endl;
    vec3 color;
    //  determine the color here
    Hit hit;
    hit = this->Closest_Intersection(ray);
    if(hit.object != NULL) {
	std::cout << "entered if" << std::endl;
        vec3 intersection_point = ray.Point(hit.dist);
	std::cout << "out of ray.point" << std::endl;
	std::cout << "entering normal" << std::endl;
        vec3 normal = hit.object->Normal(intersection_point, 0);
	std::cout << "out of normal" << std::endl;
        color = hit.object->material_shader->Shade_Surface(ray, intersection_point, normal, recursion_depth);
	std::cout << "out of shade surface" << std::endl;
    }
    else {
	std::cout << "Entered else" << std::endl;
	vec3 temp;
        color = background_shader->Shade_Surface(ray, temp, temp, recursion_depth);
    }
    std::cout << "Exit cast ray" << std::endl;
    return color;
}

void Render_World::Initialize_Hierarchy()
{
    TODO; // Fill in hierarchy.entries; there should be one entry for
    // each part of each object.

    hierarchy.Reorder_Entries();
    hierarchy.Build_Tree();
}
