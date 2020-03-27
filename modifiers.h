#ifndef MODIFIERS_H_INCLUDED
#define MODIFIERS_H_INCLUDED
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
class Mods{
    private:
        friend class Tank;
        friend void key_callback(GLFWwindow* window, int key,int scancode, int action, int mods, Mods mod);
        float lr;
        float turret_lr;
        float frd;
        float up;
        float whl;
        float fire;
    public:
        float get_lr();
        float get_turret_lr();
        float get_frd();
        float get_up();
        float get_whl();
        float get_fire();
        float get_fire_cooldown();
        void set_lr(float val);
        void set_turret_lr(float val);
        void set_frd(float val);
        void set_up(float val);
        void set_whl(float val);
        void set_fire(float val);
        Mods();
};


#endif // MODIFIERS_H_INCLUDED
