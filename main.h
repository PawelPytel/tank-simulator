#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <cstdio>
#include <ctime>
#include <vector>
#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include <windows.h>
#include <mmsystem.h>
#include "bullet.h"
#include <time.h>
#include <math.h>
#include "object.h"
#include "modifiers.h"
#include "surrounding.h"
#include "tank.h"
// obiekty
Object body("models/T90/T 90_test.obj");
Object gun("models/T90/T 90_gun2.obj");
Object turret("models/T90/T 90_turret2.obj");
Object wheel("models/T90/T 90_wheel2.obj");
Object small_wheel("models/T90/T 90_small_wheel2.obj");
Object track("models/T90/T 90_track.obj");
Object plane("models/T90/T 90_plane.obj");
Object bullet("models/T90/bullet.obj");
Object wall("models/T90/wall2.obj");
Object hole("models/T90/hole.obj");
Mods modyfikator;
Tank tank;
Surr surr;
//Uchwyty na VAO i bufory wierzchołków
GLuint holeVao;
GLuint bulletVao;
GLuint bodyVao;
GLuint turretVao;
GLuint gunVao;
GLuint wheelVao;
GLuint small_wheelVao;
GLuint trackVao;
GLuint planeVao;
GLuint wallVao;
GLuint bufVertices; //Uchwyt na bufor VBO przechowujący tablicę współrzędnych wierzchołków
GLuint bufColors;
GLuint bufNormals;
GLuint bufTexCoords;




