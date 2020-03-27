/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzaæ dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundacjê Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŒCI HANDLOWEJ albo PRZYDATNOŒCI DO OKREŚLONYCH
ZASTOSOWAÑ.W celu uzyskania bliŻszych informacji siĘgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymasz też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/





#include "main.h"

using namespace glm;

float aspect=(float)16/9; //Stosunek szerokosci do wysokoœci okna
std::clock_t start;

//Uchwyty na shadery
ShaderProgram *shaderProgram; //Wskaźnik na obiekt reprezentujący program cieniujący.

//Procedura obsługi błędów
void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
void freeOpenGLProgram();
//Procedura obsługi klawiatury
void key_callback(GLFWwindow* window, int key,
                  int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_RIGHT)
        {
            if(modyfikator.get_frd()>=0)
                modyfikator.set_lr(-1);
            else
                modyfikator.set_lr(1);
            if(modyfikator.get_frd()==0)
                modyfikator.set_whl(PI);
        }
        if (key == GLFW_KEY_LEFT)
        {
            if(modyfikator.get_frd()>=0)
                modyfikator.set_lr(1);
            else
                modyfikator.set_lr(-1);
            if(modyfikator.get_frd()==0)
                modyfikator.set_whl(PI);
        }
        if (key == GLFW_KEY_UP)
        {
            modyfikator.set_frd(10);
            modyfikator.set_whl(PI);
        }
        if (key == GLFW_KEY_DOWN)
        {
            modyfikator.set_frd(-10);
            modyfikator.set_whl(-PI);
            if(modyfikator.get_lr()==-1)
                modyfikator.set_lr(1);
            else if(modyfikator.get_lr()==1)
                modyfikator.set_lr(-1);
        }
        if (key == GLFW_KEY_A)
            modyfikator.set_turret_lr(1);
        if (key == GLFW_KEY_D)
            modyfikator.set_turret_lr(-1);
        if (key == GLFW_KEY_W)
            modyfikator.set_up(-0.5);
        if (key == GLFW_KEY_S)
            modyfikator.set_up(0.5);
        if (key == GLFW_KEY_SPACE)
        {
            if(modyfikator.get_fire()==0)
            {
                modyfikator.set_fire(20);
                start=std::clock();
            }
        }
        if (key==GLFW_KEY_ESCAPE)
        {
            freeOpenGLProgram();
            glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
            glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
            exit(EXIT_SUCCESS);
        }
    }

    if (action == GLFW_RELEASE)
    {
        if (key == GLFW_KEY_RIGHT)
        {
            if(modyfikator.get_lr()==-1&&modyfikator.get_frd()>=0)
                modyfikator.set_lr(0);
            if(modyfikator.get_lr()==1&&modyfikator.get_frd()<0)
                modyfikator.set_lr(0);
        }
        if (key == GLFW_KEY_LEFT)
        {
            if(modyfikator.get_lr()==1&&modyfikator.get_frd()>=0)
                modyfikator.set_lr(0);
            if(modyfikator.get_lr()==-1&&modyfikator.get_frd()<0)
                modyfikator.set_lr(0);
        }
        if (key == GLFW_KEY_UP)
        {
            if(modyfikator.get_frd()==10)
                modyfikator.set_frd(0);
        }
        if (key == GLFW_KEY_DOWN)
        {
            if(modyfikator.get_lr()==1)
                modyfikator.set_lr(-1);
            else if(modyfikator.get_lr()==-1)
                modyfikator.set_lr(1);
            if(modyfikator.get_frd()==-10)
                modyfikator.set_frd(0);
        }
        if (key == GLFW_KEY_A)
        {
            if(modyfikator.get_turret_lr()==1)
                modyfikator.set_turret_lr(0);
        }
        if (key == GLFW_KEY_D)
        {
            if(modyfikator.get_turret_lr()==-1)
                modyfikator.set_turret_lr(0);
        }
        if (key == GLFW_KEY_W)
        {
            if(modyfikator.get_up()==-0.5)
                modyfikator.set_up(0);
        }
        if (key == GLFW_KEY_S)
        {
            if(modyfikator.get_up()==0.5)
                modyfikator.set_up(0);
        }
    }
}

//Procedura obługi zmiany rozmiaru bufora ramki
void windowResize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height); //Obraz ma być generowany w oknie o tej rozdzielczoœci
    if (height!=0)
    {
        aspect=(float)width/(float)height; //Stosunek szerokości do wysokości okna
    }
    else
    {
        aspect=(float)16/9;
    }
}

//Tworzy bufor VBO z tablicy
GLuint makeBuffer(void *data, int vertexCount, int vertexSize)
{
    GLuint handle;

    glGenBuffers(1,&handle);//Wygeneruj uchwyt na Vertex Buffer Object (VBO), który bêdzie zawierał tablicę danych
    glBindBuffer(GL_ARRAY_BUFFER,handle);  //Uaktywnij wygenerowany uchwyt VBO
    glBufferData(GL_ARRAY_BUFFER, vertexCount*vertexSize, data, GL_STATIC_DRAW);//Wgraj tablicę do VBO

    return handle;
}

//Przypisuje bufor VBO do atrybutu
void assignVBOtoAttribute(ShaderProgram *shaderProgram,const char* attributeName, GLuint bufVBO, int vertexSize)
{
    GLuint location=shaderProgram->getAttribLocation(attributeName); //Pobierz numer slotu dla atrybutu
    glBindBuffer(GL_ARRAY_BUFFER,bufVBO);  //Uaktywnij uchwyt VBO
    glEnableVertexAttribArray(location); //Włącz używanie atrybutu o numerze slotu zapisanym w zmiennej location
    glVertexAttribPointer(location,vertexSize,GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu location maj¹ byæ brane z aktywnego VBO
}



void prepareObject(ShaderProgram *shaderProgram, Object & object, char* path,GLuint &vao)
{

    //Zbuduj VBO z danymi obiektu do narysowania
    bufVertices=makeBuffer(object.get_vertices().data(), object.get_vericles_count(), sizeof(float)*4); //VBO ze współrzędnymi wierzchołków
    bufNormals=makeBuffer(object.get_normals().data(), object.get_vericles_count(), sizeof(float)*4);//VBO z wektorami normalnymi wierzchołków
    bufTexCoords=makeBuffer(object.get_uvs().data(),object.get_vericles_count(),sizeof(float)*2);
    object.loadTexture(path);
    //Zbuduj VAO wiążący atrybuty z konkretnymi VBO
    glGenVertexArrays(1,&vao); //Wygeneruj uchwyt na VAO i zapisz go do zmiennej globalnej

    glBindVertexArray(vao); //Uaktywnij nowo utworzony VAO

    assignVBOtoAttribute(shaderProgram,"vertex",bufVertices,4); //"vertex" odnosi się do deklaracji "in vec4 vertex;" w vertex shaderze
    assignVBOtoAttribute(shaderProgram,"normal",bufNormals,4); //"normal" odnosi się do deklaracji "in vec4 normal;" w vertex shaderze
    assignVBOtoAttribute(shaderProgram,"texCoord0", bufTexCoords,2);

    glBindVertexArray(0); //Dezaktywuj VAO
}


//Procedura inicjuj¹ca
void initOpenGLProgram(GLFWwindow* window)
{
    //************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
    glClearColor(0, 0, 0, 1); //Czyści ekran na czarno
    glEnable(GL_DEPTH_TEST); //Włącz używanie Z-Bufora
    glfwSetKeyCallback(window, key_callback); //Zarejestruj procedurę obsługi klawiatury
    glfwSetFramebufferSizeCallback(window,windowResize); //Zarejestruj procedurę obsługi zmiany rozmiaru bufora ramki

    shaderProgram=new ShaderProgram("vs.glsl",NULL,"fs.glsl");
    prepareObject(shaderProgram, bullet,"models/T90/bullet.png",bulletVao);
    prepareObject(shaderProgram, gun,"models/T90/camo.png",gunVao);
    prepareObject(shaderProgram, turret,"models/T90/camo.png",turretVao);
    prepareObject(shaderProgram, track,"models/T90/track_mud.png",trackVao);
    prepareObject(shaderProgram, wheel,"models/T90/wheel_mud.png",wheelVao);
    prepareObject(shaderProgram, small_wheel,"models/T90/wheel_mud.png",small_wheelVao);
    prepareObject(shaderProgram, plane,"models/T90/surface.png",planeVao);
    prepareObject(shaderProgram, body,"models/T90/camo.png",bodyVao);
    prepareObject(shaderProgram,wall,"models/T90/wall.png",wallVao);
    prepareObject(shaderProgram,hole,"models/T90/hole_wall.png",holeVao);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram()
{
    delete shaderProgram; //Usunięcie programu cieniującego
    glDeleteVertexArrays(1,&bodyVao); //Usunięcie vao
    glDeleteVertexArrays(1,&turretVao);
    glDeleteVertexArrays(1,&gunVao);
    glDeleteVertexArrays(1,&wheelVao);
    glDeleteVertexArrays(1,&small_wheelVao);
    glDeleteVertexArrays(1,&trackVao);
    glDeleteVertexArrays(1,&planeVao);
    glDeleteVertexArrays(1,&bulletVao);
    glDeleteVertexArrays(1,&wallVao);
    glDeleteVertexArrays(1,&holeVao);
    glDeleteBuffers(1,&bufVertices);
    glDeleteBuffers(1,&bufColors); //Usunięcie VBO z kolorami
    glDeleteBuffers(1,&bufNormals);
}

void drawObject(GLuint vao, ShaderProgram *shaderProgram, mat4 mP, mat4 mV, mat4 mM,vec4 cam,float wallT, int verticesCount, GLuint texture)
{
    //Włączenie programu cieniującego, który ma zostać u¿yty do rysowania

    shaderProgram->use();

    //Przekaż do shadera macierze P,V i M.
    //W linijkach poniżej, polecenie:
    //  shaderProgram->getUniformLocation("P")
    //pobiera numer slotu odpowiadającego zmiennej jednorodnej o podanej nazwie
    //UWAGA! "P" w powy¿szym poleceniu odpowiada deklaracji "uniform mat4 P;" w vertex shaderze,
    //a mP w glm::value_ptr(mP) odpowiada argumentowi  "mat4 mP;" TYM pliku.


    glUniformMatrix4fv(shaderProgram->getUniformLocation("P"),1, false, glm::value_ptr(mP));
    glUniformMatrix4fv(shaderProgram->getUniformLocation("V"),1, false, glm::value_ptr(mV));
    glUniformMatrix4fv(shaderProgram->getUniformLocation("M"),1, false, glm::value_ptr(mM));
    glUniform4fv(shaderProgram->getUniformLocation("cam"),1,value_ptr(cam) );
    glUniform1f(shaderProgram->getUniformLocation("wallT"),wallT );
    glUniform1i(shaderProgram->getUniformLocation("diffuseMap"),0);
    //Uaktywnienie VAO i tym samym uaktywnienie predefiniowanych w tym VAO powiązań slotów atrybutów z tablicami z danymi

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texture);
    //Narysowanie obiektu
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES,0,verticesCount);

    //Posprzątanie po sobie (niekonieczne w sumie jeżeli korzystamy z VAO dla ka¿dego rysowanego obiektu)
    glBindVertexArray(0);
}

void drawScene2(GLFWwindow *window, Tank & tank, Surr & surr)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //Wykonaj czyszczenie bufora kolorów
    mat4 tmp,tmp2,tmp3,tmp4,V;
    float wallT=surr.get_wallT();
    glm::mat4 P = glm::perspective(50 * PI / 180, aspect, 2.0f, 200.0f); //Wylicz macierz rzutowania
    tank.move_body(surr);
    vec4 cam=tank.get_cam_and_count_V();
    V=tank.get_V();
    drawObject(bodyVao,shaderProgram,P,V,tank.get_M(),cam,wallT, body.get_vericles_count(), body.get_texture());
    tmp=tank.from_body_to_turret();
    drawObject(turretVao,shaderProgram,P,V,tmp,cam,wallT, turret.get_vericles_count(), turret.get_texture());
    tmp=tank.from_turret_to_gun(tmp);
    drawObject(gunVao,shaderProgram,P,V,tmp,cam,wallT, gun.get_vericles_count(), gun.get_texture());
    tank.fire(surr,modyfikator,tmp);
    if(modyfikator.get_fire()==20 ||modyfikator.get_fire()==BULLET_SPEED)
        drawObject(bulletVao,shaderProgram,P,V,tank.get_BM(),cam,wallT, bullet.get_vericles_count(), bullet.get_texture());



    for(int j=0; j<2; j++)
    {
        tmp=tank.get_left_small_wheels(j);
        tmp2=tmp;
        tmp=tank.rotate_left_wheels(tmp);
        drawObject(small_wheelVao,shaderProgram,P,V,tmp,cam,wallT, small_wheel.get_vericles_count(), small_wheel.get_texture());
        tmp=tank.get_right_small_wheels(j);
        tmp4=tmp;
        tmp=tank.rotate_right_wheels(tmp);
        drawObject(small_wheelVao,shaderProgram,P,V,tmp,cam,wallT, small_wheel.get_vericles_count(), small_wheel.get_texture());
        tmp=tank.get_track(j);
        drawObject(trackVao,shaderProgram,P,V,tmp,cam,wallT, track.get_vericles_count(), track.get_texture());
    }
    for(int i=1; i<7; i++)
    {
        tmp3=tank.get_left_wheels(tmp2,i);
        drawObject(wheelVao,shaderProgram,P,V,tmp3,cam,wallT, wheel.get_vericles_count(), wheel.get_texture());
        tmp3=tank.get_right_wheels(tmp4,i);
        drawObject(wheelVao,shaderProgram,P,V,tmp3,cam,wallT, wheel.get_vericles_count(), wheel.get_texture());
    }
    tmp=surr.get_plane();
    drawObject(planeVao,shaderProgram,P,V,tmp,cam,wallT, plane.get_vericles_count(), plane.get_texture());
    surr.update_outside(cam);
    for(int k=0; k<2; k++)
    {
        surr.set_first();
        for(int j=0; j<4; j++)
        {
            if(surr.check_transparency(j))
                wallT=0.1;
            else
                wallT=1;
            for(int i=0; i<surr.get_holes_count(j); i++)
            {
                drawObject(holeVao,shaderProgram,P,V,surr.get_next_hole(i,j),cam,wallT,hole.get_vericles_count(),hole.get_texture());
            }
            for(int i=0; i<7; i++)
            {
                //tmp=surr.matrices[k*4*7+(first+j)%4*7+i];

                //if(j==2&&outside[last]==1&&outside[(last-1)%4])
                drawObject(wallVao,shaderProgram,P,V,surr.get_next_wall(i,j,k),cam,wallT,wall.get_vericles_count(),wall.get_texture());
            }
        }
    }


    surr.set_wallT(1);







    glfwSwapBuffers(window);
}




int main(void)
{

    GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno
    GLFWmonitor* monitor;

    glfwSetErrorCallback(error_callback);//Zarejestruj procedurê obsługi błędów

    if (!glfwInit())   //Zainicjuj bibliotekê GLFW
    {
        fprintf(stderr, "Nie mo¿na zainicjowaæ GLFW.\n");
        exit(EXIT_FAILURE);
    }
    monitor = glfwGetPrimaryMonitor();
    window = glfwCreateWindow(1920, 1080, "Tank", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

    if (!window) //Je¿eli okna nie uda³o siê utworzyæ, to zamknij program
    {
        fprintf(stderr, "Nie mo¿na utworzyæ okna.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
    glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

    if (glewInit() != GLEW_OK)   //Zainicjuj bibliotekę GLEW
    {
        fprintf(stderr, "Nie mo¿na zainicjowaæ GLEW.\n");
        exit(EXIT_FAILURE);
    }
    printf("1\n");
    initOpenGLProgram(window); //Operacje inicjuj¹ce
    printf("1\n");

    Tank tank;
    Surr surr;
    glfwSetTime(0);

    while (!glfwWindowShouldClose(window)){
        tank.reset();
        glfwPollEvents();
        tank.set_angle(modyfikator);
        tank.set_turret_angle(modyfikator);
        tank.set_gun_angle(modyfikator);
        tank.set_ls(modyfikator);
        tank.set_rs(modyfikator);
        tank.set_wheels_angle(modyfikator);
        if ((std::clock()-start)/float CLOCKS_PER_SEC>1)
            modyfikator.set_fire(0);
        tank.set_fire_speed(modyfikator);
        tank.set_speed(modyfikator);
        glfwSetTime(0);
        drawScene2(window,tank,surr);

    }

    freeOpenGLProgram();

    glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
    glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
    exit(EXIT_SUCCESS);
}
