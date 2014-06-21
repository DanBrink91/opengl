#include <GL/glew.h>

class Shader
{
	public:
		Shader(GLenum shaderType, const char* shaderFile);
		const char* getShaderSource(const char* shaderFile);
		
		GLuint shader; 	
};
