#include "object.h"
Object::Object() {}
Object::Object( char* path)
{
    ObjectLoader::loadOBJ(path, vertices, uvs, normals);
}
void Object::loadTexture(char* path)
{
    texture = ObjectLoader::loadTexture(path);
}


std::vector< glm::vec4 > Object::get_vertices()
{
    return vertices;
}

std::vector< glm::vec2 > Object::get_uvs()
{
    return uvs;
}

std::vector< glm::vec4 > Object::get_normals()
{
    return normals;
}



int Object::get_vericles_count()
{
    return vertices.size();
}

GLuint Object::get_texture()
{
    return texture;
}

Object::~Object()
{
    //dtor
}

