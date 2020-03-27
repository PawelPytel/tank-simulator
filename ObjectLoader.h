#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <fstream>
#include <lodepng.h>

class ObjectLoader
{
    public:
        ObjectLoader();
        virtual ~ObjectLoader();
        static loadOBJ(
            char * path,
            std::vector < glm::vec4 > & out_vertices,
            std::vector < glm::vec2 > & out_uvs,
            std::vector < glm::vec4 > & out_normals

        );
        static GLuint loadTexture( char * filename);
    protected:

    private:
};

#endif // OBJECTLOADER_H
