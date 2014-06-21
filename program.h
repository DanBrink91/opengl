#include <GL/glew.h>
#include <string>

class Program
{
	public:
		Program(std::string debugName);
		//  Attempt to create and attach shader
		bool attachShader(GLenum shaderType, const char* shaderFile);
		//  Attempt to link program
		bool link();

		GLuint program;
		std::string debugName; 	
	private:
		//  Return shader source from file
		const char* getShaderSource(const char* shaderFile);
};
