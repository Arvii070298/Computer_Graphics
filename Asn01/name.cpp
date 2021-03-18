
// Sai Arvind Reddy Desireddy
//sd1253
//-----------------------------------------------------------------------------------
// Splat-based point renderer.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/trigonometric.hpp> // sin, cos

#include "mesh.hpp"
#include "shader.hpp"
#include "window.hpp"
#include "camera.hpp"
#include "grid.hpp"
#include "flat_lighter.hpp"
#include "mesh.hpp"
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

Camera cam;
bool scene_changed = true;
GLFWwindow *window;
Grid grid;
Flat_Lighter lighter;

std::vector<Mesh*> letter_shapes;
float F1(float t) {
    return ((1 - t) * (1 - t) * (1 - t));
}
float F2(float t) {
    return (3 * (1 - t) * (1 - t) * t);
}
////finding f3(t)
float F3(float t) {
    return (3 * (1 - t) * t * t);
}
//finding f4(t)
float F4(float t) {
    return (t * t * t);
}
int add_vertex(float x, float y, float z,
               float *coords, GLuint *indexes, int vert_index) {
    int i = vert_index / 4;
    indexes[i] = i;
    coords[vert_index++] = x;
    coords[vert_index++] = y;
    coords[vert_index++] = z;
    coords[vert_index++] = 1;
    return vert_index;
}

void make_scene() {
    int max_vertices = 100;
    float *coords = new float[max_vertices * 4];
    GLuint *indexes = new GLuint[max_vertices];
    GLuint program_handle = lighter.get_program_handle();

    int i = 0;




    // letter "s"
    i = 0;
  
    glm::vec3 P1;
  glm::vec3  v0 = glm::vec3(0.3, 0, 0);
  glm::vec3  v1 = glm::vec3(1.1, 0.05, 0);
  glm::vec3  v2 = glm::vec3(1.1, 0.45, 0);
  glm::vec3  v3 = glm::vec3(0.3, 0.5, 0);
  int couter = 0;
    for (float t = 0; t <= 1; t += 0.1) {
        P1 = v0 * F1(t) + v1 * F2(t) + v2* F3(t) + v3 * F4(t);
        cout << couter << endl;
        couter ++ ;
        i = add_vertex(P1.x, P1.y, 0, coords, indexes, i);
    }



     v0 = glm::vec3(0.3, 0.5, 0);
     v1 = glm::vec3(-0.15, 0.55, 0);
    v2 = glm::vec3(-0.15, 0.95, 0);
     v3 = glm::vec3(1, 1, 0);

    for (float t = 0; t <= 1; t += 0.1) {
        P1 = v0 * F1(t) + v1 * F2(t) + v2 * F3(t) + v3 * F4(t);
     
        i = add_vertex(P1.x, P1.y, 0, coords, indexes, i);
    }

    letter_shapes.push_back(new Mesh(coords, 20, 4,
        indexes, 20,
        20,
        GL_LINE_STRIP, program_handle,
        "Letter d1"));
    //--------------------------------------------------------------------------------line
    i = 0;
    P1;
    v3 = glm::vec3(0.3, 0, 0);
    v2 = glm::vec3(1.2, 0, 0);
    v1 = glm::vec3(0.8, 0.6, 0);
    v0 = glm::vec3(1.4, 0.5, 0);

    for (float t = 0; t <= 1; t += 0.1) {
        P1 = v0 * F1(t) + v1 * F2(t) + v2 * F3(t) + v3 * F4(t);

        i = add_vertex(P1.x, P1.y, 0, coords, indexes, i);
    }

    letter_shapes.push_back(new Mesh(coords, 10, 4,
        indexes, 10,
        10,
        GL_LINE_STRIP, program_handle,
        "Letter d1"));

    //------------------------------------------------------------------a

    i = 0;
   
     P1;
    v0= glm::vec3(1.4, 0.5, 0);
     v1 = glm::vec3(1.0, 0.5, 0);
     v2 = glm::vec3(1.0, 0.1, 0);
    v3= glm::vec3(1.45, 0.12, 0);
  
    for (float t = 0; t <= 1; t += 0.1) {
        P1 = v0 * F1(t) + v1 * F2(t) + v2 * F3(t) + v3 * F4(t);
      
        i = add_vertex(P1.x, P1.y, 0, coords, indexes, i);
    }


 
    v0 = glm::vec3(1.4, 0.5, 0);
    v1 = glm::vec3(1.26, 0.228, 0);
    v2 = glm::vec3(1.328, 0.0, 0);
    v3 = glm::vec3(1.73, 0.083, 0);

    for (float t = 0; t <= 1; t += 0.1) {
        P1 = v0 * F1(t) + v1 * F2(t) + v2 * F3(t) + v3 * F4(t);

        i = add_vertex(P1.x, P1.y, 0, coords, indexes, i);
    }

    

    letter_shapes.push_back(new Mesh(coords, 20, 4,
        indexes, 20,
        20,
        GL_LINE_STRIP, program_handle,
        "Letter d1"));
   //----------------------------------------- using cardinal splines

//-----------------------------for letter S

    i = 0;
    P1;
    glm::vec3 Q0 = glm::vec3(4, 1, 0);
    glm::vec3 Q1 = glm::vec3(3.5, 0.5, 0);
   
    glm::vec3 Q2 = glm::vec3(3, 0, 0);  
    glm::vec3 Q3 = glm::vec3(4.5, 0.5, 0);
    glm::vec3 Q4 = glm::vec3(4.5, 0.5, 0);

    //glm::vec3 S1 = Q1 + 0.1f * (Q2 - Q0);
    glm::vec3 R1 = Q1 - 0.45f * (Q3 - Q1);
   /* cout << R2.x <<":"<<R2.y<< endl;
    cout << S1.x << ":" << S1.y << endl;*/

    v3= Q0;
    v2 = R1;
    v1 = R1;
    v0 = Q1;

    for (float t = 0; t <= 1; t += 0.1) {
        P1 = v0 * F1(t) + v1 * F2(t) + v2 * F3(t) + v3 * F4(t);

        i = add_vertex(P1.x, P1.y, 0, coords, indexes, i);
    }


    letter_shapes.push_back(new Mesh(coords, 10, 4,
        indexes, 10,
        10,
        GL_LINE_STRIP, program_handle,
        "Letter d1"));
    i = 0;
    P1;
    Q0 = glm::vec3(4, 1, 0);
     Q1 = glm::vec3(3.5, 0.5, 0);

     Q2 = glm::vec3(3, 0, 0);
    Q3 = glm::vec3(4.5, 0.5, 0);



    glm::vec3 R = Q1 - 0.2f * (Q2 - Q0);
    glm::vec3 S = Q2 + 0.6f * (Q3 - Q1);
    
    v0 = Q1;
    v1 = R;
    v2 = S;
    v3 = Q2;

    for (float t = 0; t <= 1; t += 0.1) {
        P1 = v0 * F1(t) + v1 * F2(t) + v2 * F3(t) + v3 * F4(t);

        i = add_vertex(P1.x, P1.y, 0, coords, indexes, i);
    }


    letter_shapes.push_back(new Mesh(coords, 10, 4,
        indexes, 10,
        10,
        GL_LINE_STRIP, program_handle,
        "Letter d1"));


    //=------------------------------------------for letter a
    i = 0;
    P1;
  Q0 = glm::vec3(4.5, 0.5, 0);
     Q1 = glm::vec3(4.5, 0, 0);

     Q2 = glm::vec3(3, 0, 0);
    Q4 = glm::vec3(4, 0.5, 0);

    //glm::vec3 S1 = Q1 + 0.1f * (Q2 - Q0);
     R1 = Q1 + 0.6f * (Q2 - Q0);
    /* cout << R2.x <<":"<<R2.y<< endl;
     cout << S1.x << ":" << S1.y << endl;*/

    v3 = Q0;
    v2 = Q4;
    v1 = R1;
    v0 = Q1;

    for (float t = 0; t <= 1; t += 0.1) {
        P1 = v0 * F1(t) + v1 * F2(t) + v2 * F3(t) + v3 * F4(t);

        i = add_vertex(P1.x, P1.y, 0, coords, indexes, i);
    }


    letter_shapes.push_back(new Mesh(coords, 10, 4,
        indexes, 10,
        10,
        GL_LINE_STRIP, program_handle,
        "Letter d1"));


    i = 0;
    P1;
    Q0 = glm::vec3(4.3, 0.5, 0);
    Q1 = glm::vec3(4.5, 0, 0);

    Q2 = glm::vec3(4.5, 1, 0);
 

    //glm::vec3 S1 = Q1 + 0.1f * (Q2 - Q0);
    R1 = Q1 - 0.3f * (Q2 - Q0);
    /* cout << R2.x <<":"<<R2.y<< endl;
     cout << S1.x << ":" << S1.y << endl;*/

    v0 = Q0;
    v1 = R1;
    v2 = R1;
    v3 = Q1;

    for (float t = 0; t <= 1; t += 0.1) {
        P1 = v0 * F1(t) + v1 * F2(t) + v2 * F3(t) + v3 * F4(t);

        i = add_vertex(P1.x, P1.y, 0, coords, indexes, i);
    }


    letter_shapes.push_back(new Mesh(coords, 10, 4,
        indexes, 10,
        10,
        GL_LINE_STRIP, program_handle,
        "Letter d1"));

    //---------------------------------------------------------------------boudnicng ball

    i = 0;
    P1;
     Q0 = glm::vec3(5, 0, 0);
    Q1 = glm::vec3(5.5, 1, 0);

     Q2 = glm::vec3(6, 0, 0);
     Q3 = glm::vec3(6.5, .7, 0);
    Q4 = glm::vec3(7, 0, 0);
    glm::vec3 Q5 = glm::vec3(7.5, 0.5, 0);
    glm::vec3 Q6 = glm::vec3(8, 0, 0);
   // glm::vec3 Q7 = glm::vec3(8.5, 1, 0);

    //glm::vec3 S1 = Q1 + 0.1f * (Q2 - Q0);
     glm::vec3 S1 = Q1 + 0.3f * (Q2 - Q0);
     glm::vec3 R2 = Q2 - 0.2f * (Q3 - Q1);
     /* cout << R2.x <<":"<<R2.y<< endl;
     cout << S1.x << ":" << S1.y << endl;*/

    v0 = Q1;
    v1 = S1;
    v2 = R2;
    v3 = Q2;

    for (float t = 0; t <= 1; t += 0.1) {
        P1 = v0 * F1(t) + v1 * F2(t) + v2 * F3(t) + v3 * F4(t);

        i = add_vertex(P1.x, P1.y, 0, coords, indexes, i);
    }

    glm::vec3 S2 = Q2 + 0.3f * (Q3 - Q1);
    glm::vec3 R3 = Q3 - 0.5f * (Q4 - Q2);
    v0 = Q2;
    v1 = S2;
    v2 = R3;
    v3 = Q3;

    for (float t = 0; t <= 1; t += 0.1) {
        P1 = v0 * F1(t) + v1 * F2(t) + v2 * F3(t) + v3 * F4(t);

        i = add_vertex(P1.x, P1.y, 0, coords, indexes, i);
    }


    glm::vec3 S3 = Q3 + 0.3f * (Q4 - Q2);
    glm::vec3 R4 = Q4 - 0.3f * (Q5 - Q3);
    v0 = Q3;
    v1 = S3;
    v2 = R4;
    v3 = Q4;

    for (float t = 0; t <= 1; t += 0.1) {
        P1 = v0 * F1(t) + v1 * F2(t) + v2 * F3(t) + v3 * F4(t);

        i = add_vertex(P1.x, P1.y, 0, coords, indexes, i);
    }
    glm::vec3 S4 = Q4 + 0.3f * (Q5 - Q3);
    glm::vec3 R5 = Q5 - 0.3f * (Q6 - Q4);
    v0 = Q4;
    v1 = S4;
    v2 = R5;
    v3 = Q5;

    for (float t = 0; t <= 1; t += 0.1) {
        P1 = v0 * F1(t) + v1 * F2(t) + v2 * F3(t) + v3 * F4(t);

        i = add_vertex(P1.x, P1.y, 0, coords, indexes, i);
    }
    glm::vec3 S5 = Q5 + 0.3f * (Q6 - Q4);
   // glm::vec3 R5 = Q5 - 0.3f * (Q6 - Q4);
    v0 = Q5;
    v1 = S5;
    v2 = S5;
    v3 = Q6;

    for (float t = 0; t <= 1; t += 0.1) {
        P1 = v0 * F1(t) + v1 * F2(t) + v2 * F3(t) + v3 * F4(t);

        i = add_vertex(P1.x, P1.y, 0, coords, indexes, i);
    }

    
    
    
    
    letter_shapes.push_back(new Mesh(coords, 50, 4,
        indexes, 50,
        50,
        GL_LINE_STRIP, program_handle,
        "Letter d1"));


    
}

void draw_scene() {
    // render
    // ------
    glClearColor(0.4f, 0.2f, 0.1f, 1.0f); // dark red/brown
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    grid.draw();

    lighter.set_camera(cam);
    lighter.set_color(glm::vec4(1, 0, 0, 1));

    letter_shapes[0]->draw();
    letter_shapes[1]->draw();
  
    letter_shapes[2]->draw();
   letter_shapes[3]->draw();
   letter_shapes[4]->draw();
   letter_shapes[5]->draw();
   letter_shapes[6]->draw();

   letter_shapes[7]->draw();




    glfwSwapBuffers(window);
    scene_changed = false;
}

int main(int argc, char **argv)
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();

    int display_width = 1000;
    int display_height = 200;

    GLFW_OpenGL_Window glfw_window(3, 3,
                                   display_width,
                                   display_height,
                                   "My Name",
                                   &framebuffer_size_callback);
    window = glfw_window.get_window();

    lighter.init();

    grid = Grid(0, 0,12, 1,
                1, 0.1, lighter);

    cam = Camera(display_width, display_height);
    cam.init_2D(-0.5, -0.5, 12, 2);

    glfwGetFramebufferSize(glfw_window.get_window(),
                           &display_width,
                           &display_height);
    cam.resize_display(display_width, display_height);

    lighter.set_camera(cam);

    make_scene();

    // render loop
    // -----------
    scene_changed = true;
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);
        if (scene_changed) {

            draw_scene();

        }
        glfwWaitEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

bool key_pressed(unsigned int key_ID, GLFWwindow *window) {
    return glfwGetKey(window, key_ID) == GLFW_PRESS;
}

// process all input: query GLFW whether relevant keys are pressed/released
// this frame, and react accordingly
// --------------------------------------------------------------
void processInput(GLFWwindow *w)
{
    if (key_pressed(GLFW_KEY_ESCAPE, w) ||
        key_pressed(GLFW_KEY_Q, w))
        glfwSetWindowShouldClose(w, true);
}

// glfw: whenever the window size changed (by OS or user resize)
// this callback function executes
// ------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions;
    // note that width and height will be significantly larger
    // than specified on retina displays.
    cam.resize_display(width, height);
    lighter.set_camera(cam);
}
