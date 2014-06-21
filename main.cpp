#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

#define GLM_FORCE_RADIANS 1
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "program.h"

//  Global
int winID;
GLint projectionLocation, viewLocation, modelLocation;
GLuint VBO, IBO;
float gChanger = 100.0f; 
glm::vec3 gCameraPos = glm::vec3(0, 0, 2);

static void RenderSceneCB()
{
	gChanger += 0.1f;	
	float sinChange = glutGet(GLUT_ELAPSED_TIME) / 1000.0; //sinf(gChanger);

	//  fov, aspect ratio, near, far
	glm::mat4 Projection = glm::perspective<float>(90.0, 4.0 / 3.0, 0.1, 100.0);
	
	glm::mat4 View = glm::lookAt(
		glm::vec3(0, 0, 1), // Camera position 
		glm::vec3(0, 0, 0), //  Camera looking at
		glm::vec3(0, 1, 0) //  up position, usually 0, 1, 0
		);
	
	//  Model specific stuff here
	glm::mat4 Translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 RotateX = glm::rotate(glm::mat4(1.0f), sinChange, glm::vec3(1.0f, 0.0f, 0.0f));	
	glm::mat4 RotateY = glm::rotate(glm::mat4(1.0f), sinChange, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));
	
	//  Combine all of the model stuff here
	glm::mat4 Model = RotateX * RotateY * Scale;

	//  Multiplied in "Reverse" so it is in the correct order. 
	//glm::mat4 MVP = /*Projection * View */ Model;

	
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(Projection));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(View));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Model));

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//  Grab size of buffer
	int size; glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, size/3/sizeof(GLfloat));
	
	glDisableVertexAttribArray(0);

	glutSwapBuffers();
	glutPostRedisplay();
}

static void keyboardCB(unsigned char key, int x, int y)
{
	float speed = 0.1f;
	switch(key)
	{
		case 119:
			gCameraPos.z -= speed;
		break;
		case 115:
			gCameraPos.z += speed;
		break;
		case 97:
			gCameraPos.x -= speed;
		break;
		case 100:
			gCameraPos.x += speed;
		break;
		case 27: //  Escape key
			glutDestroyWindow(winID);
			exit(0);
		break;
	}
	glutPostRedisplay();
}

static void CreateVertexBuffer()
{
	GLfloat Verticies[] = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
    	-1.0f,-1.0f, 1.0f,
    	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
    	-1.0f,-1.0f,-1.0f,
    	-1.0f, 1.0f,-1.0f, // triangle 2 : end
    	1.0f,-1.0f, 1.0f,
    	-1.0f,-1.0f,-1.0f,
    	1.0f,-1.0f,-1.0f,
    	1.0f, 1.0f,-1.0f,
    	1.0f,-1.0f,-1.0f,
    	-1.0f,-1.0f,-1.0f,
    	-1.0f,-1.0f,-1.0f,
    	-1.0f, 1.0f, 1.0f,
    	-1.0f, 1.0f,-1.0f,
    	1.0f,-1.0f, 1.0f,
    	-1.0f,-1.0f, 1.0f,
    	-1.0f,-1.0f,-1.0f,
    	-1.0f, 1.0f, 1.0f,
    	-1.0f,-1.0f, 1.0f,
    	1.0f,-1.0f, 1.0f,
   	1.0f, 1.0f, 1.0f,
    	1.0f,-1.0f,-1.0f,
    	1.0f, 1.0f,-1.0f,
    	1.0f,-1.0f,-1.0f,
    	1.0f, 1.0f, 1.0f,
    	1.0f,-1.0f, 1.0f,
    	1.0f, 1.0f, 1.0f,
    	1.0f, 1.0f,-1.0f,
    	-1.0f, 1.0f,-1.0f,
    	1.0f, 1.0f, 1.0f,
    	-1.0f, 1.0f,-1.0f,
    	-1.0f, 1.0f, 1.0f,
    	1.0f, 1.0f, 1.0f,
    	-1.0f, 1.0f, 1.0f,
    	1.0f,-1.0f, 1.0f
	};

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Verticies), Verticies, GL_STATIC_DRAW);
}


int main(int argc, char** argv)
{
	const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;		
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(100, 100);
	winID = glutCreateWindow("Test Window");
		
	glutDisplayFunc(RenderSceneCB);
	glutKeyboardFunc(keyboardCB);
	
	GLenum res = glewInit();
	if(res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}	
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	printf("Renderer: %s\n", renderer);
	printf("Version: %s\n", version);	
	Program program("test");

	if(!program.attachShader(GL_VERTEX_SHADER, "shader.vs"))
	{
		printf("vertex shader failed\n");		
	}

	if(!program.attachShader(GL_FRAGMENT_SHADER, "shader.fs"))
	{
		printf("Fragment shader failed\n");
	}
	
	program.link();
	glUseProgram(program.program);
	
	//  Set uniform variables
	GLint location = glGetUniformLocation(program.program, "screenWidth");
	glUniform1i(location, 800);

	GLint location2 = glGetUniformLocation(program.program, "screenHeight");
	glUniform1i(location2, 600);
	
	//  Grab locations for uniforms used in rendering
	projectionLocation = glGetUniformLocation(program.program, "projection");
	viewLocation = glGetUniformLocation(program.program, "view");
	modelLocation = glGetUniformLocation(program.program, "model");
	
	glDepthFunc(GL_LEQUAL);

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);


	CreateVertexBuffer();
	
	glutMainLoop();
	
	return 0;
}
