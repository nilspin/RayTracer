#include<iostream>
#include<limits>
#include<fstream>
#include<glm/glm.hpp>
#include "ray.hpp"
#include "hitable_list.hpp"
#include "sphere.hpp"

using namespace std;
using namespace glm;

vec3 color(const ray& r, hitable *world)
{
    hit_record rec;
    if(world->hit(r, 0.0, numeric_limits<float>::max(), rec))
    {
        return 0.5f*vec3(rec.normal.x + 1.0f, rec.normal.y + 1.0f, rec.normal.z + 1.0f);
    }
    else
    {
        vec3 unit_direction = normalize(r.direction());
        float t = 0.5*(unit_direction.y + 1.0);

        //return blend between blue and white
        return (1.0f-t)*vec3(1.0f) + t*vec3(0.5f, 0.7f, 1.0f);
    }
}
int main()
{
    ofstream fout;
    fout.open("picture.ppm");

    int nx=300;
    int ny=150;
    fout<<"P3\n"<< nx << " " << ny << "\n255\n";
    vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
    vec3 horizontal(4.0f, 0.0f, 0.0f);
    vec3 vertical(0.0f, 2.0f, 0.0f);
    vec3 origin(0.0f);

    hitable *list[2];
    list[0] = new sphere(vec3(0.0f, -100.5f, -1.0f), 100.0);
    list[1] = new sphere(vec3(0.0f, 0.0f, -1.0f), 0.5);

    hitable *world = new hitable_list(list, 2);

    for(int j=ny-1; j>=0; j--)
    {
        for(int i=0;i < nx; ++i)
        {
            float u = float(i)/float(nx);
            float v = float(j)/float(ny);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);

            vec3 p = r.point_at_parameter(1.0); //why 2?
            vec3 col = color(r, world);
            int ir = int(255.99*col.r);
            int ig = int(255.99*col.g);
            int ib = int(255.99*col.b);
            fout<< ir << " " << ig << " " << ib << "\n";
        }
    }
    return 0;
}
