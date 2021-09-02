//Senlin Xiao 16522077 Computer Graphics Project
#include "lab06_framework.hpp"
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<vector>
using namespace std;
const GLfloat pi = 3.1415926536f;
int n = 30;
unsigned int texture[2];

#define NUM_PARTICLE 10000 //number of particles
#define TOP 1    //initial position
#define BOTTOM -1.2 //end position
#define EDGE 0.6 //position of the edges
#define DELTA_T 0.02 //time loss
#define g 10 // gravity acceleration velocity
int update_pNum = 8000;
int c_particle = 0;
float particles[NUM_PARTICLE][7];

////waterfall effect implementation refers to the thesis on http://www.wodocx.com/p-7530.html
// time loss function, use to generate ramdon number for particles initialisation
float lossT(int r){

    float res = (float)(rand()%r);
    return res;
}
// draw a water particle
void drawParticle(int i){
    GLUquadric *myQuad;
    float x,y,z;
    float d = 0.01;//radius of waterdrops;
    // set the material to every particle
    float diffuse[] = {0.26,0.56,0.8,1.0};
    glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
    myQuad = gluNewQuadric();
    gluQuadricTexture(myQuad, GL_TRUE);

    x = particles[i][0];
    y = particles[i][1];
    z = particles[i][2];

    glTranslatef(x,y,z);

    glColor3f(0.26,0.56,0.8);
    gluSphere(myQuad,d,3,2);
    //go back to the original position for next waterdrops
    glTranslatef(-x,-y,-z);
}

void pInit(int i){
    particles[i][0] = (lossT(1000)/1000-0.5);               //x-direction initialization
    particles[i][1] = lossT(3000)/1000+1.0;                 //y-direction initialization
    particles[i][2] = lossT(1000)/1000-1.0;                 //z-direction initialization
    particles[i][3] = 0.0;              //x velocity initialization
    particles[i][4] = 0;                 //y velocity update
    particles[i][5] = 0.0;               //z velocity update
    particles[i][6] = -1.0;              //marks for striking the edge
    drawParticle(i);

}

//oversee every particle's state, when it go beyond the expect boundries, reset its position, otherwise, keep it falling, to simulate the waterfall effect
void update(int i){
    if(particles[i][1]< BOTTOM){
        pInit(i);//check if particles move above the bottom position
    }else{
        if(particles[i][1] <= 0.6){
            particles[i][6] = 1;
        }
        particles[i][1] -= 0.005*g;
        drawParticle(i);
    }
}

void waterfall(){
    srand((int)time(NULL));
    for(int i = 0;i<NUM_PARTICLE;i++){
        update(i);
    }
}

//texture load function
void loadTex(unsigned char* data_1){

// set up properties of the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// generate texture;
    if(data_1 != NULL){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data_1);

    }
    else{
        printf(" failed to load texture\n");
    }

}
//load_obj

//load-function
// param attrib, vector data structure, used to store vectices coordinates, refer to tinyobjloader.h,
// param shapes, vector data structure, used to store faces information of the object,
// param materials, vector data structure, used to store materials information of each faces of the object
// tex, true if the object need texture, false otherwise;
//emit, true if the object need emiot light effect, false otherwise
void load_obj(tinyobj::attrib_t attrib, vector<tinyobj::shape_t> shapes,vector<tinyobj::material_t> materials, bool tex,bool emit)
{
    for (int j = 0; j < shapes.size(); j++) {
        int a = 0;
        for (int p = 0; p < shapes[j].mesh.indices.size(); p += 3) {
            int nind1 = shapes[j].mesh.indices[p].normal_index;
            int nind2 = shapes[j].mesh.indices[p + 1].normal_index;
            int nind3 = shapes[j].mesh.indices[p + 2].normal_index;
            //emit indicates whether the loading object has emission attribute, true to set its emission performance, otherwise, not
            if (emit) {
                float s[] = {1, 1, 1, 1.0};
                glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, s);
            } else {
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materials[shapes[j].mesh.material_ids[a]].diffuse);
            }
            a++;
            int ind1 = shapes[j].mesh.indices[p].vertex_index;
            int ind2 = shapes[j].mesh.indices[p + 1].vertex_index;
            int ind3 = shapes[j].mesh.indices[p + 2].vertex_index;
            glBegin(GL_TRIANGLES);
            // tex indicate whether the object has texture, true to set its texture coordinate, otherwise, not
            if (tex)
                glTexCoord2d(attrib.texcoords[shapes[j].mesh.indices[p].texcoord_index],
                             attrib.texcoords[shapes[j].mesh.indices[p].texcoord_index + 1]);
            //normal setting, used to implement the light effect
            glNormal3f(attrib.normals[3 * nind1 + 0], attrib.normals[3 * nind1 + 1], attrib.normals[3 * nind1 + 2]);
            glVertex3f(attrib.vertices[3 * ind1 + 0], attrib.vertices[3 * ind1 + 1], attrib.vertices[3 * ind1 + 2]);
            if (tex)
                glTexCoord2d(attrib.texcoords[shapes[j].mesh.indices[p + 1].texcoord_index],
                             attrib.texcoords[shapes[j].mesh.indices[p + 1].texcoord_index + 1]);
            glNormal3f(attrib.normals[3 * nind2 + 0], attrib.normals[3 * nind2 + 1], attrib.normals[3 * nind2 + 2]);
            glVertex3f(attrib.vertices[3 * ind2 + 0], attrib.vertices[3 * ind2 + 1], attrib.vertices[3 * ind2 + 2]);
            if (tex)
                glTexCoord2d(attrib.texcoords[shapes[j].mesh.indices[p + 2].texcoord_index],
                             attrib.texcoords[shapes[j].mesh.indices[p + 2].texcoord_index + 1]);
            glNormal3f(attrib.normals[3 * nind3 + 0], attrib.normals[3 * nind3 + 1], attrib.normals[3 * nind3 + 2]);
            glVertex3f(attrib.vertices[3 * ind3 + 0], attrib.vertices[3 * ind3 + 1], attrib.vertices[3 * ind3 + 2]);
            glEnd();
        }
    }
}

//waterwheel object
//borrow model from https://sketchfab.com/3d-models/gd51-darren-t4a3-2f1e5edfdd354df7aa2579443d7cd088
std::string inputfile_wheel = "waterwheel.obj";
tinyobj::attrib_t attrib_wheel;
std::vector<tinyobj::shape_t> shapes_wheel;
std::vector<tinyobj::material_t> materials_wheel;

std::string warn_wheel;
std::string err_wheel;

bool ret_wheel = tinyobj::LoadObj(&attrib_wheel, &shapes_wheel, &materials_wheel, &warn_wheel, &err_wheel, inputfile_wheel.c_str());

//scene object, some of the object inside this main scene is referred to sketchFab website,
// temple: https://sketchfab.com/3d-models/day-1-temple-019a4bedbb5243dbbe4d3d425b836a09
// mainland & river & trees & grass & rocks: https://sketchfab.com/3d-models/the-river-2a8453f6f5834671ab82a3afc1d6bd26
// lamps: https://sketchfab.com/3d-models/basic-streetlantern-73f702e0f8a64c30b487a914d80ac32c
// desks: https://sketchfab.com/search?features=downloadable&q=desk&sort_by=-likeCount&type=models
std::string inputfile_scene = "scene.obj";
tinyobj::attrib_t attrib_scene;
std::vector<tinyobj::shape_t> shapes_scene;
std::vector<tinyobj::material_t> materials_scene;

std::string warn_scene;
std::string err_scene;

bool ret_scene = tinyobj::LoadObj(&attrib_scene, &shapes_scene, &materials_scene, &warn_scene, &err_scene, inputfile_scene.c_str());

//sky object refer to sketchFab website: https://sketchfab.com/3d-models/fantasy-sky-background-15c79bb2fc1147128039fe4ff90fd5a0
std::string inputfile_sky = "sky.obj";
tinyobj::attrib_t attrib_sky;
std::vector<tinyobj::shape_t> shapes_sky;
std::vector<tinyobj::material_t> materials_sky;

std::string warn_sky;
std::string err_sky;

bool ret_sky = tinyobj::LoadObj(&attrib_sky, &shapes_sky, &materials_sky, &warn_sky, &err_sky, inputfile_sky.c_str());

//star obj， refer to sketchFab website: https://sketchfab.com/3d-models/star-cluster-15k-stars-model-51148b78a37a4a72b22d8e06f4293e07
std::string inputfile_star = "stars.obj";
tinyobj::attrib_t attrib_star;
std::vector<tinyobj::shape_t> shapes_star;
std::vector<tinyobj::material_t> materials_star;

std::string warn_star;
std::string err_star;

bool ret_star = tinyobj::LoadObj(&attrib_star, &shapes_star, &materials_star, &warn_star, &err_star, inputfile_star.c_str());




