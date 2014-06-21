#include "shader.h"
#include <fstream>
#include <string>
//  only for debug
#include <stdio.h>

Shader::Shader(GLenum shaderType, const char* shaderFile)
{
	const char* fileContents = this->getShaderSource(shaderFile);
	this->shader = glCreateShader(shaderType);
	glShaderSource(this->shader, 1, &fileContents, NULL);

	glCompileShader(this->shader);
	
	GLint status;
	glGetShaderiv(this->shader, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(this->shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength+1];
		glGetShaderInfoLog(this->shader, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Compile failure:\n%s\n", strInfoLog);
		delete[] strInfoLog;
	}
}

const char* Shader::getShaderSource(const char* shaderFile)
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
