//
// Camera Class from the base code of Project 6 of UPenn CIS-565 Fall 2013
// With modification to use the latest version of GLM

#include <glm/gtx/rotate_vector.hpp>
#include <glm/glm.hpp>
#include "camera.h"

using namespace glm;

void Camera::adjust(float dx, // look left right
        float dy, //look up down
        float dz,
        float tx, //strafe left right
        float ty,
        float tz)//go forward) //strafe up down
{

    if (abs(dx) > 0) {
        rx += dx;
        rx = fmod(rx,360.0f);
    }

    if (abs(dy) > 0) {
        ry += dy;
        ry = clamp(ry,-70.0f, 70.0f);
    }

    if (abs(tx) > 0) {
        vec3 dir = glm::rotate(start_dir,rx + 90,up);
 
        vec2 dir2(dir.x,dir.y);
        vec2 mag = dir2 * tx;
        pos += mag;	
    }

    if (abs(ty) > 0) {
        z += ty;
    }

    if (abs(tz) > 0) {
        vec3 dir = glm::rotate(start_dir,rx,up);
        vec2 dir2(dir.x,dir.y);
        vec2 mag = dir2 * tz;
        pos += mag;
    }
}

mat4x4 Camera::get_view() {
    vec3 inclin = glm::rotate(start_dir,ry,start_left);
    vec3 spun = glm::rotate(inclin,rx,up);
    vec3 cent(pos, z);
    return lookAt(cent, cent + spun, up);
}