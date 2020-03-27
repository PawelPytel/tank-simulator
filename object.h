#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "ObjectLoader.h"

class Object
{
    public:
        Object();
        Object( char* path);
        void loadTexture(char* path);
        virtual ~Object();
        std::vector< glm::vec4 > get_vertices();
        std::vector< glm::vec2 > get_uvs();
        std::vector< glm::vec4 > get_normals();

        GLuint get_texture();
        int get_vericles_count();

    private:
        std::vector< glm::vec4 > vertices;
        std::vector< glm::vec2 > uvs;
        std::vector< glm::vec4 > normals;

        GLuint texture;
};


#endif // OBJECT_H_INCLUDED
