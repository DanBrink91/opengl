#include "program.h"
#include <fstream>
#include <string>

//  only for debug
#include <stdio.h>

Program::Program(std::string debugName)
{
	this->program = glCreateProgram();
	this->debugName = debugName;
}

bool Program::attachShader(GLenum shaderType, const char* shaderFile)
{
	GLuint shader;
	const char* fileContents = this->getShaderSource(shaderFile);
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &fileContents, NULL);

	glCompileShader(shader);
	
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength+1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Compile failure:\n%s\n", strInfoLog);
		delete[] strInfoLog;
		return false;
	}
	glAttachShader(this->program, shader);
	return true;
}

bool Program::link()
{
	GLint status;
	glLinkProgram(this->program);
	
	glGetProgramiv(this->program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		printf("No link\n");
		return false;
	}
	
	glValidateProgram(this->program);
	
	glGetProgramiv(this->program, GL_VALIDATE_STATUS, &status);
	if (status == GL_FALSE)
	{
		printf("No validate\n");
		return false;
	}

	return true;	
}
const char* Program::getShaderSource(const char* shaderFile)
{
	std::ifstream in(shaderFile, std::ios::in);
	if(in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		
		return (char*)contents.c_str();
	}
	//  something bad happened :(
	printf("File Read did not work!\n");
	return "";
}
