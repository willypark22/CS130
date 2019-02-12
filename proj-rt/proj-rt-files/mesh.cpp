#include "mesh.h"
#include <fstream>
#include <string>
#include <limits>
#include "plane.h"

// Consider a triangle to intersect a ray if the ray intersects the plane of the
// triangle with barycentric weights in [-weight_tolerance, 1+weight_tolerance]
static const double weight_tolerance = 1e-4;

// Read in a mesh from an obj file.  Populates the bounding box and registers
// one part per triangle (by setting number_parts).
void Mesh::Read_Obj(const char* file)
{
    std::ifstream fin(file);
    if(!fin)
    {
        exit(EXIT_FAILURE);
    }
    std::string line;
    ivec3 e;
    vec3 v;
    box.Make_Empty();
    while(fin)
    {
        getline(fin,line);

        if(sscanf(line.c_str(), "v %lg %lg %lg", &v[0], &v[1], &v[2]) == 3)
        {
            vertices.push_back(v);
            box.Include_Point(v);
        }

        if(sscanf(line.c_str(), "f %d %d %d", &e[0], &e[1], &e[2]) == 3)
        {
            for(int i=0;i<3;i++) e[i]--;
            triangles.push_back(e);
        }
    }
    number_parts=triangles.size();
}

// Check for an intersection against the ray.  See the base class for details.
Hit Mesh::Intersection(const Ray& ray, int part) const
{
  Hit ret = {0, 0, 0};
  double min_t = std::numeric_limits<double>::max();
  double dist = 0;
  if(part < 0) {
    for(unsigned i = 0; i < triangles.size(); ++i) {
      if(Intersect_Triangle(ray, i, dist)) {
        if(dist < min_t) {
          ret.object = this;
          ret.dist = dist;
          ret.part = i;
          min_t = dist;
        }
      }
    }
    return ret;
  }
  else {
    if(Intersect_Triangle(ray, part, dist)) {
      ret.object = this;
      ret.dist = dist;
      ret.part = part;
    }
    return ret;
  }
}

// Compute the normal direction for the triangle with index part.
vec3 Mesh::Normal(const vec3& point, int part) const
{
  assert(part>=0);
  vec3 a = vertices[triangles[part][0]];
  vec3 b = vertices[triangles[part][1]];
  vec3 c = vertices[triangles[part][2]];
  vec3 line1 = b - a;
  vec3 line2 = c - a;

  vec3 normal = cross(line1, line2);
  normal = normal.normalized();
  return normal;
}

// This is a helper routine whose purpose is to simplify the implementation
// of the Intersection routine.  It should test for an intersection between
// the ray and the triangle with index tri.  If an intersection exists,
// record the distance and return true.  Otherwise, return false.
// This intersection should be computed by determining the intersection of
// the ray and the plane of the triangle.  From this, determine (1) where
// along the ray the intersection point occurs (dist) and (2) the barycentric
// coordinates within the triangle where the intersection occurs.  The
// triangle intersects the ray if dist>small_t and the barycentric weights are
// larger than -weight_tolerance.  The use of small_t avoid the self-shadowing
// bug, and the use of weight_tolerance prevents rays from passing in between
// two triangles.
bool Mesh::Intersect_Triangle(const Ray& ray, int tri, double& dist) const
{
  
  vec3 a = vertices[triangles[tri][0]];
  vec3 b = vertices[triangles[tri][1]];
  vec3 c = vertices[triangles[tri][2]];
  vec3 v = b - a;
  vec3 w = c - a;

  if(dot(ray.direction, cross(v, w)) == 0) { 
    return false;
  }
 

  vec3 min = ray.endpoint - a;

  //gamma
  double gamma, gamma1, gamma2, beta, beta1, beta2, s, s1, s2;
  vec3 uv = cross(ray.direction, v);

  gamma1 = dot(uv, min);
  gamma2 = dot(uv, w);
  gamma = gamma1 / gamma2;

  //Beta
  vec3 wu = cross(w, ray.direction);

  beta1 = dot(wu, min);
  beta2 = dot(wu, v);
  beta = beta1 / beta2;

  //s
  vec3 vw = cross(v, w);

  s1 = dot(vw, min);
  s2 = dot(vw, ray.direction);
  s = s1 / s2;

  s = -1 * s;
  dist = s;

  double alpha = 1 - beta - gamma;

  if((alpha > -weight_tol) && (beta > -weight_tol) && (gamma > -weight_tol)) {
    if(s > small_t) {
      return true;
    }
  }
  return false;
}

// Compute the bounding box.  Return the bounding box of only the triangle whose
// index is part.
Box Mesh::Bounding_Box(int part) const
{
    Box b;
    TODO;
    return b;
}
