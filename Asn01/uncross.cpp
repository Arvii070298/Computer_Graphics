// Splat-based point renderer.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream> 
#include <sstream> 
#include <glm/vec3.hpp> // glm::vec3
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, rotate
#include <glm/gtx/string_cast.hpp> // glm::to_string()
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
#include "mesh.hpp"
#include "shader.hpp"
#include "window.hpp"
#include "camera.hpp"
#include "grid.hpp"
#include "flat_lighter.hpp"
#include "mesh.hpp"
#include <iostream>
#include <fstream>
#define EPSILON 0.0001
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

int flag = 0;
int active;
int f = 1;
int ite = 0;
void mouse_motion_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow *window);
double counter_size = 0;
Camera cam;
bool scene_changed = true;
GLFWwindow *window;
Grid grid;
Flat_Lighter lighter;
float vertex_size = 0.1;
double mouse_x, mouse_y;
std::vector<string> arr;
std::vector<float> x_cord;
std::vector<float> y_cord;
std::vector<glm::vec3> vertex_positions;
std::vector<Mesh*> edges;
int file_size=0;
Mesh *vertex_shape;
Mesh* intersection_shape;

std::vector<int> a_cord;            //edges
std::vector<int> b_cord;            //edges
int intersection_counter = 0;
std::vector<glm::vec3> intersections_positions;


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



void graph_plot(char **argv) {



    
    std::ifstream file(argv[1]);
    std::string str;
    std::cout << argv[1];
    
    while (std::getline(file, str))
    {
        stringstream geek(str);
       
       
        int x = 0;
        geek >> x;
        arr.push_back(str);
        file_size++;

    }
    stringstream geek(arr[0]);
    double x = 0.0;
    geek >> x;
    counter_size = x;
    double angle = 360 / x;
    //cout << x <<"ikda"<<endl;
    for (int i = 0; i <= x; i++) {
        double an = i * angle;
        x_cord.push_back(cos(an*3.142/180));
        y_cord.push_back(sin(an*3.142/180));
    //  cout << x_cord[i] << y_cord[i]<<  "angle is"  << (an)<< cos(36)<<endl;
    }

   

    // loop through the elements of the array
    /*cout << "aloo 123\n";
    for (int i = 0; i < counter_size; i++) {
        std::cout << arr[i] << ' ';
    }
    int b[] = {100};*/
}
void def_vertex() {
    for (int i = 0; i < counter_size; i++) {

        glm::vec3 position(x_cord[i], y_cord[i], 0);
        vertex_positions.push_back(position);


    }
}
void intersection() {
   
    for (int i = 0; i < (file_size - 2); i++) {
        for (int j = 0; j < (file_size - 2); j++) {
            if (i == j) {
                continue;
            }

           /* cout << "`````````````````````````````````````````" << endl;
             cout << a_cord[i] << b_cord[i] << endl;

             cout << a_cord[j] << b_cord[j] << endl;
             cout << "`````````````````````````````````````````" << endl;*/
            float Ax = x_cord[a_cord[i]];
            float Ay = y_cord[a_cord[i]];
            float Bx = x_cord[b_cord[i]];
            float By = y_cord[b_cord[i]];


            float Cx = x_cord[a_cord[j]];
            float Cy = y_cord[a_cord[j]];
            float Dx = x_cord[b_cord[j]];
            float Dy = y_cord[b_cord[j]];

            float a = Bx - Ax;
            float b = Cx - Dx;
            float c = Cx - Ax;
            float d = By - Ay;
            float e = Cy - Dy;
            float f = Cy - Ay;
            float delta = (a * e) - (b * d);
         
            if (delta == 0) {
                
                continue;
            }
            else {

                float delta_x = (c * e) - (b * f);

                float delta_y = (a * f) - (c * d);
                
                float t = (delta_x / delta);
                float u = (delta_y / delta); 
                if ((t < (1 - EPSILON) && t>(0 + EPSILON)) && (u > (0 + EPSILON) && u < (1 - EPSILON))) {

                    float intersection_a = Ax + (t*(Bx - Ax));

                    float intersection_b = Ay + (t*(By - Ay));
                   

                    intersection_counter=1;
                    glm::vec3 position(intersection_a, intersection_b, 0);
                   intersections_positions.push_back(position);

                    
                }

                
            }

            


        } 
    }
}
void make_scene() {
    int max_vertices = 100;
    float *coords = new float[max_vertices * 4];
    GLuint *indexes = new GLuint[max_vertices];
    GLuint program_handle = lighter.get_program_handle();

    

    int i = 0;
    float s = vertex_size / 2;
    i = add_vertex(-s, -s, 0, coords, indexes, i);
    i = add_vertex(+s, -s, 0, coords, indexes, i);
    i = add_vertex(+s, +s, 0, coords, indexes, i);
    i = add_vertex(-s, +s, 0, coords, indexes, i);
    vertex_shape = new Mesh(coords, 4, 4,
                            indexes, 4,
                            4,
                            GL_TRIANGLE_FAN, program_handle,
                            "Vertex");

    i = 0;
     s = vertex_size / 4;
    i = add_vertex(-s, -s, 0, coords, indexes, i);
    i = add_vertex(+s, -s, 0, coords, indexes, i);
    i = add_vertex(+s, +s, 0, coords, indexes, i);
    i = add_vertex(-s, +s, 0, coords, indexes, i);
    intersection_shape = new Mesh(coords, 4, 4,
        indexes, 4,
        4,
        GL_TRIANGLE_FAN, program_handle,
        "Vertex");



   



    
}


void draw_edges() {

    for (int i = 2; i < (file_size ); i++) {

        string word = "";
        string first = "";
        for (auto x : arr[i])
        {
            if (x == ' ')
            {

                first = word;
                word = "";
            }
            else
            {
                word = word + x;
            }
        }

        stringstream geek(first);


        int vertex_a = 0;
        geek >> vertex_a;


        stringstream xyz(word);
        int vertex_b = 0;
        xyz >> vertex_b;

      
       a_cord.push_back(vertex_a);
       b_cord.push_back(vertex_b);

    }


    int max_vertices = 100;
    float* coords = new float[max_vertices * 4];
    GLuint* indexes = new GLuint[max_vertices];
    GLuint program_handle = lighter.get_program_handle();

    for (int j = 0; j < (file_size - 2); j++) {
        int i = 0;
        int x = a_cord[j];
        int y = b_cord[j];

        i = 0;

        i = add_vertex(x_cord[x], y_cord[x], 0, coords, indexes, i);
        i = add_vertex(x_cord[y], y_cord[y], 0, coords, indexes, i);

        edges.push_back(new Mesh(coords, 2, 4,
            indexes, 2,
            2,
            GL_LINE_LOOP, program_handle,
            "L"));

    }
       


}


void draw_scene() {
    // render
    // ------
   

    ite++;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (f==1) {
        glClearColor(0.4f, 0.2f, 0.1f, 1.0f); // dark red/brown
       
    }
    
    grid.draw();
 def_vertex();
   
    for (int i = 0; i < (vertex_positions.size()); i++) {
       
        glm::mat4 move = glm::translate(glm::mat4(1.0f), vertex_positions[i]);
        lighter.set_model_transform(move);
        int a[10], n, j;
        n = i;
        for (j = 0; n > 0; j++) {
            a[j] = n % 2;
            n = n / 2;
        }

       

        lighter.set_color(glm::vec4(a[0],a[1],a[2],1));
        vertex_shape->draw();   

    }      

    
       draw_edges();

       
      
       for (int i = 0; i < (file_size-2); i++) {
           glm::vec3 position(0, 0, 0);
           glm::mat4 move = glm::translate(glm::mat4(1.0f),position);
           lighter.set_model_transform(move);
           lighter.set_color(glm::vec4(1, 1, 0, 0));
           edges[i]->draw();

       }
    
       
       intersection();
       for (int i = 0; i < (intersections_positions.size()); i++) {

           glm::mat4 move = glm::translate(glm::mat4(1.0f), intersections_positions[i]);
           lighter.set_model_transform(move);
           lighter.set_color(glm::vec4(1,1,1,0));
           intersection_shape->draw();
       }
      
      
       for (int k = 0; k < edges.size(); k++) {
           delete edges[k];
       }
       if (intersections_positions.size() == 0) {

               glClearColor(0, 0.5, 0, 0);


       }

       if(intersections_positions.size()==0){


        glClearColor(0, 0.4, 0, 0);
        f = 0;

       }
       else {
           f = 1;
       }
       intersections_positions.clear();
      edges.clear();
       vertex_positions.clear();
    glfwSwapBuffers(window);
    if (flag == 0) {
        scene_changed = false;

    }
    
    scene_changed = true;
    
}

int main(int argc, char** argv)
{
    std::cout << argv[0]<<":::::::::::::::::" << argv[1]  << std::endl;

   

    if (argc != 2) {
        std::cout << argc << argv[0] << argv[1] << argv[2] <<  std::endl;
        std::cerr << "Usage:\n";
        std::cerr << "  uncross <graph-file.txt>\n";
        std::cerr << "Press ENTER to exit program:";
        
        char reply[10];
        std::cin.getline(reply, 9);
        exit(1);
    }
    graph_plot(argv);
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    int display_width = 800;
    int display_height = 800;

    GLFW_OpenGL_Window glfw_window(3, 3,
                                   display_width,
                                   display_height,
                                   "Uncross",
                                   &framebuffer_size_callback);
    window = glfw_window.get_window();

    lighter.init();

    grid = Grid(-1, -1, 4, 4,
                1, 0.1, lighter);

    cam = Camera(display_width, display_height);
    cam.init_2D(-1.5, -1.5, 3, 3);

    glfwGetFramebufferSize(glfw_window.get_window(),
                           &display_width,
                           &display_height);
    cam.resize_display(display_width, display_height);

    lighter.set_camera(cam);

    make_scene();

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_motion_callback);
    

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

// glfw calls this every time the mouse moves
void mouse_motion_callback(GLFWwindow* window, double xpos, double ypos) {
    // Save the mouse position.
    // If a vertex is active, change its position.
    mouse_x = ((xpos -400)/260);
    mouse_y = -((ypos -400)/260);
    auto coord = cam.mouse_to_world(xpos, ypos);
  //  cout << coord[0]<<"+++ "<< endl;
    if (flag == 1) {
        x_cord[active] = coord[0];
        y_cord[active] = coord[1];
      //  cout << flag << endl;
        

    }
   /* x_cord[0] = mouse_x;
    y_cord[0] = mouse_y;*/

    
   
    

    



}void check_vertex() {
    if (flag == 1) {
        flag = 0;
       // cout << "reset" << endl;

    }
    else {

        for (int i = 0; i < counter_size; i++) {
            if ((mouse_x < (x_cord[i] + 0.075) && (mouse_x > (x_cord[i] - 0.075))) && (mouse_y<(y_cord[i] + 0.075) && mouse_y>(y_cord[i] - 0.075)))
            {
                //cout << "selected" << x_cord[i] <<"  : "<<y_cord[i]<<endl;
                flag = 1;
                active = i;

                break;
            }
        }
    }

}

// glfw calls this every time the user presses/releases a mouse button
void mouse_button_callback( GLFWwindow* window, int button,
                            int action, int mods ) {
    if (button != GLFW_MOUSE_BUTTON_LEFT)
        return;

    if (action == GLFW_PRESS)
    {
       
      //  cout << mouse_x << mouse_y <<endl;

        
        check_vertex();

        // Left button was pressed:
        // 1. convert mouse coords to world.
        // 2. check each vertex, to see if the mouse
        //    is inside its square.
        // 3. if so, make the vertex active.
    }
}

