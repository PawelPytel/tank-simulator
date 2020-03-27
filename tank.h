#ifndef TANK_H_INCLUDED
#define TANK_H_INCLUDED
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "modifiers.h"
#include "surrounding.h"
#define BULLET_SPEED 300
using namespace glm;
class Tank{
private:
    mat4 M;
    mat4 BM;
    mat4 V;
    float angle;
    float speed;
    float body_angle;
    float total_angle;
    float turret_angle;
    float gun_angle;
    float wheels_angle;
    float rs;
    float ls;
    float fire_speed;
public:
    Tank();
    mat4 get_M();
    mat4 get_BM();
    mat4 get_V();
    vec4 get_cam_and_count_V();
    void reset();
    void set_angle(Mods mods);
    void set_turret_angle(Mods mods);
    void set_gun_angle(Mods mods);
    void set_ls(Mods mods);
    void set_rs(Mods mods);
    void set_wheels_angle(Mods mods);
    void set_fire_speed(Mods mods);
    void set_speed(Mods mods);
    void move_body(Surr surr);
    mat4 from_body_to_turret();
    mat4 from_turret_to_gun(mat4 tmp);
    void fire(Surr &surr,Mods &mods, mat4 tmp);
    mat4 get_left_small_wheels(int j);
    mat4 get_right_small_wheels(int j);
    mat4 get_track(int j);
    mat4 get_left_wheels(mat4 tmp, int i);
    mat4 get_right_wheels(mat4 tmp, int i);
    mat4 rotate_left_wheels(mat4 tmp );
    mat4 rotate_right_wheels(mat4 tmp );
    };


#endif // TANK_H_INCLUDED
