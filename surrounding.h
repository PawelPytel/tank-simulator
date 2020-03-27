#ifndef SURROUNDING_H_INCLUDED
#define SURROUNDING_H_INCLUDED
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
using namespace glm;
class Surr{
private:
    std::vector<mat4> matrices;
    std::vector<vec4> positions;
    std::vector<mat4> holes[4];
    bool outside[4];
    int last;
    int first;
    float wallT;
public:
    friend class Tank;
    Surr();
    void set_first();
    void update_outside(vec4 cam);
    bool check_transparency(int j);
    mat4 get_next_wall(int i, int j, int k);
    mat4 get_plane();
    int get_holes_count(int j);
    mat4 get_next_hole(int i, int j);
    void set_wallT(float val);
    float get_wallT();
};


#endif // SURROUNDING_H_INCLUDED
