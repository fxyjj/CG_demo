//Senlin Xiao 16522077 Computer Graphics Project
////this project code borrowed framework from lab6 of CG module, framework code can be found from moodle
#include "lab06_framework.hpp"
#include "loadFunclib.hpp"
double gLastMouseX = 0;
double gLastMouseY = 0;
#define PI 3.1415926

using namespace std;



/*****************************************************************************/
// Scene Objects
/*****************************************************************************/

Object gSceneRoot;
auto *gAxis = gSceneRoot.addChild<Axis>();
auto *gGround = gSceneRoot.addChild<MeshGround>();
auto *gCube = gSceneRoot.addChild<Cube>();

// An observer camera which shows the world and the camera you are tweaking
auto *gLeftCamera = gSceneRoot.addChild<PerspectiveCamera>();

Object *activeObject(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_Z))
        return gCube;
    return gLeftCamera;
}

Texture gCubeTex;

/*****************************************************************************/
// Scene Creation
/*****************************************************************************/

void updateCamera()
{
    const float aspect = 1.f * gFramebufferWidth / gFramebufferHeight;
    gLeftCamera->setAspect(aspect);
}

void initScene()
{
    updateCamera();
    gLeftCamera->position().x = 3;
    gLeftCamera->position().z = 3;
    gLeftCamera->position().y = 3;
    gLeftCamera->setZFar(1000);

    gCubeTex.create();
    gCube->setTexture(&gCubeTex);
}

/*****************************************************************************/
// Scene Update
/*****************************************************************************/

void update(GLFWwindow *window, float dt)
{
    auto multiplier = 1.f;
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
        multiplier *= 10;
    if(glfwGetKey(window, GLFW_KEY_LEFT_ALT))
        multiplier /= 10;
    const auto step = 0.1f * multiplier;

    glm::vec3 move { 0, 0, 0 };

     if(glfwGetKey(window, GLFW_KEY_W)){
        move.z -= step*cos(gLastMouseX*PI/180);
        move.x += step*sin(gLastMouseX*PI/180);
    }

    if(glfwGetKey(window, GLFW_KEY_A)){
        move.z -= step*sin(gLastMouseX*PI/180);
        move.x -= step*cos(gLastMouseX*PI/180);
    }

    if(glfwGetKey(window, GLFW_KEY_S)){
        move.z += step*cos(gLastMouseX*PI/180);
        move.x -= step*sin(gLastMouseX*PI/180);
    }

    if(glfwGetKey(window, GLFW_KEY_D)){
        move.z += step*sin(gLastMouseX*PI/180);
        move.x += step*cos(gLastMouseX*PI/180);
    }
    if(glfwGetKey(window, GLFW_KEY_Q))
        move.y -= step;
    if(glfwGetKey(window, GLFW_KEY_E))
        move.y += step;
    activeObject(window)->position() += move;
}

/*****************************************************************************/
// Scene Rendering
/*****************************************************************************/

void drawViewport(float dt)
{
    glViewport(0, 0, gFramebufferWidth, gFramebufferHeight);

    glMatrixMode(GL_PROJECTION);
    // Reset the matrix
    glLoadIdentity();
    // Apply projection matrix
    gLeftCamera->applyProjectionMatrix();

    glMatrixMode(GL_MODELVIEW);
    // Reset the matrix
    glLoadIdentity();
    // Apply camera world-to-local transformation
    gLeftCamera->applyWorldToLocalMatrix();

    // Draw the scene hierarchy
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    gSceneRoot.drawHierarchyTransformed(dt);
}

int k = 0;

void render(float dt)
{
    // Clear the framebuffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//light effect
    float light_pos[] = {-1.2,-112.0,-0.1,1.0};
    GLfloat light_ambient [] = { 0, 0, 0, 1.0 };
    GLfloat light_diffuse [] = { 1, 1, 1, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT , light_ambient );
    glLightfv(GL_LIGHT0, GL_DIFFUSE , light_diffuse );
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.15);
    glEnable(GL_LIGHTING);
    //control the state of light0, light_0 = true, light_0 is active, otherwise, not;
    if(light_0){
        glEnable(GL_LIGHT0);
    }else{
        glDisable(GL_LIGHT0);
    }

    //light1
    float light1_pos[] = {-13.1,-112.0,-4.4,1.0};
    glLightfv(GL_LIGHT1,GL_POSITION,light1_pos);
    glLightfv(GL_LIGHT1, GL_AMBIENT , light_ambient );
    glLightfv(GL_LIGHT1, GL_DIFFUSE , light_diffuse );
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.15);
    //control the sts\ate of light1, light_0 = true, light_0 is active, otherwise, not;
    if(light_1){
        glEnable(GL_LIGHT1);
    }else{
        glDisable(GL_LIGHT1);
    }


    //light2
    float light2_pos[] = {-10.5,-112.0,5.5,1.0};
//        float light2_pos[] = {kx,-112.0,ki,1.0};
    glLightfv(GL_LIGHT2,GL_POSITION,light2_pos);
    glLightfv(GL_LIGHT2, GL_AMBIENT , light_ambient );
    glLightfv(GL_LIGHT2, GL_DIFFUSE , light_diffuse );
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.15);
    //control the sts]ate of light2, light_2 = true, light_0 is active, otherwise, not;
    if(light_2){
        glEnable(GL_LIGHT2);
    }else{
        glDisable(GL_LIGHT2);
    }

    //light3
    float light3_pos[] = {-6.1,-112.0,9.0,1.0};

    glLightfv(GL_LIGHT3,GL_POSITION,light3_pos);
    glLightfv(GL_LIGHT3, GL_AMBIENT , light_ambient );
    glLightfv(GL_LIGHT3, GL_DIFFUSE , light_diffuse );
    glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.15);
    //control the state of light3, light_3 = true, light_0 is active, otherwise, not;
    if(light_3){
        glEnable(GL_LIGHT3);
    }else{
        glDisable(GL_LIGHT3);
    }
    //light4
    float light4_pos[] = {0.0,-8.0,3.0,1.0};
    glLightfv(GL_LIGHT4,GL_POSITION,light4_pos);
    glLightfv(GL_LIGHT4, GL_AMBIENT , light_ambient );
    glLightfv(GL_LIGHT4, GL_DIFFUSE , light_diffuse );
    glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 0.05);
    //this light source is used to light the moon, so it is always active
    glEnable(GL_LIGHT4);


    glEnable(GL_DEPTH_TEST);// deep test
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    drawViewport(dt);
    glPopAttrib();
    glPushMatrix();
    //draw water wheel and let it rotate constantly in the scene.
    glTranslatef(-4.6,0.8,3.0);
    glRotatef(-day, 1,0,0);
    //set wood texture on waterwheel
    glGenTextures(2, texture);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    loadTex(data_1);
    load_obj(attrib_wheel,shapes_wheel,materials_wheel,true,false);
    glPopMatrix();
    //load the main land of the scene
    load_obj(attrib_scene,shapes_scene,materials_scene,false,false);
    //waterfall animation implemented here.
    //there are four places in the scene have the water falling effect.
    glTranslatef(-4.7,-2.5,1.6);
    waterfall();

    glTranslatef(-0.4,0,-0.3);
    glRotatef(-50,0,1,0);
    waterfall();

    glPopMatrix();
    glTranslatef(-2.8,0.0,0.0);
    glRotatef(50,0,1,0);
    waterfall();

    glTranslatef(15.5,0.0,-0.8);
    waterfall();
    //stars object in the scene
    glTranslatef(0,120,0);
    load_obj(attrib_star,shapes_star,materials_star,false,false);
    //set texture to the moon in the scene
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    loadTex(data_2);
    GLUquadric *mQuadric = gluNewQuadric();
    gluQuadricTexture(mQuadric, GL_TRUE);
    gluSphere(mQuadric,2,20,20);
    gluDeleteQuadric(mQuadric);
}

/*****************************************************************************/
// Window Management
/*****************************************************************************/

int gFramebufferWidth = 1280;
int gFramebufferHeight = 720;
int gHalfWidth = gFramebufferWidth / 2;
const char *gWindowTitle = "CG_project";

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // Record the correct size of the viewport
    gFramebufferWidth = width;
    gFramebufferHeight = height;
    gHalfWidth = gFramebufferWidth / 2;
    updateCamera();
}

/*****************************************************************************/
// Input Handling
/*****************************************************************************/



void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    // record the relative movement of the mouse
    auto dx = xpos - gLastMouseX;
    auto dy = ypos - gLastMouseY;
    gLastMouseX = xpos;
    gLastMouseY = ypos;
    activeObject(window)->orientation().y -= (float)dx;
    activeObject(window)->orientation().x -= (float)dy;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(!action) return;

    switch(key)
    {
        case GLFW_KEY_H:
            gSceneRoot.printObjectHierarchy();
            break;
            //used to debugs and set objects' position properly
//        case 61:
//            ki+=0.1;
//            printf("ki%f\n",ki);
//            break;
//        case 45:
//            ki-=0.1;
//            printf("ki%f\n",ki);
//            break;
//        case 48:
//            kp+=0.1;
//            printf("kp%f\n",kp);
//            break;
//        case 57:
//            kp-=0.1;
//            printf("kp%f\n",kp);
//            break;
//        case 56:
//            kx+=0.1;
//            printf("kx%f\n",kx);
//            break;
//        case 55:
//            kx-=0.1;
//            printf("kx%f\n",kx);
//            break;
        case 49:
            light_0 = !light_0;
            break;
        case 50:
            light_1 = !light_1;
            break;
        case 51:
            light_2 = !light_2;
            break;
        case 52:
            light_3 = !light_3;
            break;
        default: ;
    }
}

/*****************************************************************************/
// File Drop Handler
/*****************************************************************************/

void drop_callback(GLFWwindow* window, int count, const char** paths)
{
    gCubeTex.loadFromFile(paths[0]);
}

/*****************************************************************************/
// Install Callbacks
/*****************************************************************************/

void installCallbacks(GLFWwindow *window)
{
    // Register our callbacks so we can know when the events occur.
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetDropCallback(window, drop_callback);
}


