#include "mesh.h"
#include <stdio.h>
#include <stdlib.h>

//  Constructor
	Mesh::Mesh()
	{
		this->translate = glm::mat4(0.0f);
		this->rotate = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f));
		this->scale = glm::mat4(1.0f);
		this->calculateModelMatrix();
	}
	void Mesh::create(GLuint program, GLfloat* verticies, int floatCount)
	{
		GLuint vbo;
		glGenVertexArrays(1, &(this->vao));
		glBindVertexArray(this->vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		
		GLfloat *vertexData = (GLfloat*)malloc(sizeof(GLfloat) * floatCount);
		for(int i = 0; i < floatCount; i++)
		{
			vertexData[i] = verticies[i];
		}

		glBufferData(GL_ARRAY_BUFFER, floatCount * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);
	
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);

		this->program = program;
		free(vertexData);
	}
	
	//  Set Translate Matrix 		
	void Mesh::setPosition(float x, float y, float z)
	{
		this->translate = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
		this->calculateModelMatrix();
	}

	//  Set Rotation Matrix
	void Mesh::setRotation(float x, float y, float z, float angle)
	{
		this->rotate = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(x, y, z));
		this->calculateModelMatrix();
	}
	//  Set Scale Matrix
	void Mesh::setScale(float x, float y, float z)
	{
		this->scale = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
		this->calculateModelMatrix();
	}

	void Mesh::calculateModelMatrix()
	{
		this->model = this->translate  * this->scale;
	}
