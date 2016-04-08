#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shaders.h"
#include <GL/glu.h>
//#define DEBUG

GLFWwindow* window;

// Box stuff
/*
    3-------7   Unit Box
    |\      |\
    | 2-------6    y
    0-|-----4 | -z |
     \|      \|   \|
      1-------5    '-----x
*/
GLfloat boxVerticies[8][3] =
{
  {-1,-1,-1},{-1,-1,1},
  {-1,1,1},{-1,1,-1},
  {1,-1,-1},{1,-1,1},
  {1,1,1},{1,1,-1},
};
GLuint boxElements[12][2]={{0,1},{1,2},{2,3},{3,0},{4,5},{5,6},{6,7},{7,4},{0,4},{1,5},{2,6},{3,7}};
GLuint boxVBO;
GLuint boxEBO;
GLuint boxVAO;
GLuint boxShaderProgram;
void setupCube() {
  // vertex shader
  GLuint boxVertShader = glCreateShader(GL_VERTEX_SHADER);
  const GLchar *vertexShader = _binary_vertex_glsl_start;
  const GLint vertexShaderSize = (int)(long)&_binary_vertex_glsl_size;
  printf("vertex shader %i characters\n",vertexShaderSize);
  printf("%.*s",vertexShaderSize,vertexShader);
  glShaderSource(boxVertShader, 1, &vertexShader, &vertexShaderSize);
  glCompileShader(boxVertShader);
  #ifdef DEBUG
  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("%s\n",infoLog);
  } else {
    printf("success\n");
  }
  #endif

  // fragment shader
  GLuint boxFragShader = glCreateShader(GL_FRAGMENT_SHADER);
  const GLchar *fragmentShader = _binary_fragment_glsl_start;
  const GLint fragmentShaderSize = (int)(long)&_binary_fragment_glsl_size;
  printf("fragment shader %i characters\n",fragmentShaderSize);
  printf("%.*s\n",fragmentShaderSize,fragmentShader);
  glShaderSource(boxFragShader, 1, &fragmentShader, &fragmentShaderSize);
  glCompileShader(boxFragShader);
  #ifdef DEBUG
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("%s\n",infoLog);
  } else {
    printf("success\n");
  }
  #endif

  // program
  boxShaderProgram = glCreateProgram();
  glAttachShader(boxShaderProgram, boxVertShader);
  glAttachShader(boxShaderProgram, boxFragShader);
  glLinkProgram(boxShaderProgram);
  glDeleteShader(boxVertShader);
  glDeleteShader(boxFragShader);
  #ifdef DEBUG
  glGetProgramiv(boxShaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(boxShaderProgram, 512, NULL, infoLog);
    printf("Failure\n%s\n",infoLog);
  }else {
   printf("success\n");
 }
 #endif

  // data
  glGenVertexArrays(1, &boxVAO);
  glBindVertexArray(boxVAO);

  glGenBuffers(1,&boxVBO);
  glBindBuffer(GL_ARRAY_BUFFER, boxVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(boxVerticies), boxVerticies, GL_STATIC_DRAW);

  glGenBuffers(1,&boxEBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,boxEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boxElements), boxElements, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

  glBindVertexArray(0);
}
void drawCube() {
  glUseProgram(boxShaderProgram);
  glBindVertexArray(boxVAO);
  glLineWidth(4);
  glDrawElements(GL_LINES,24,GL_UNSIGNED_INT,0);
}


// GLFW Callbacks

void error_callback(int error, const char* description)
{
    printf("Error: %s\n",description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  glfwSetWindowShouldClose(window, GL_TRUE);
}

// Create and destroy

void createWindow() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  window = glfwCreateWindow(640, 480, "Off-Axis Perspective Box", NULL, NULL);
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);
}

void setup() {
  if (!glfwInit()) {
    exit(1);
  }
  glfwSetErrorCallback(error_callback);
  createWindow();
  glewExperimental = GL_TRUE;
  glewInit(); // HAS TO BE CALLED AFTER THE WINDOW IS CREATED! WHY DID NO ONE TELL ME THIS!!!
  setupCube();
  glClearColor(0.5,0.5,0.5,1.0);
}

void destroyWindow() {
  glfwDestroyWindow(window);
}

void destroy() {
  destroyWindow();
  glfwTerminate();
}

// Main loops

void render(GLFWwindow *window) {
  glClear(GL_COLOR_BUFFER_BIT);
  drawCube();
}

void displayLoop() {
  while (!glfwWindowShouldClose(window)) {
    render(window);
    glfwPollEvents(); // Required for glfwWindowShouldClose() to function.
    glfwSwapBuffers(window);
  }
}

// Good ol' main

int main(int argc, const char **argv) {
  setup();
  displayLoop();
  destroy();
  return 0;
}
