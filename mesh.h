#include <GL/glew.h>

#define GLM_FORCE_RADIANS 1
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Mesh
{
	public:
		//  Constructor
		Mesh();
		
		void create(GLuint program, GLfloat* verticies, int floatCount);

		//  model matrix
		glm::mat4 model;
		
		//  Set Translate Matrix 		
		void setPosition(float x, float y, float z);
		//  Set Rotation Matrix
		void setRotation(float x, float y, float z, float angle);
		//  Set Scale Matrix
		void setScale(float x, float y, float z);
		
		//  Vertex Array Object
		GLuint vao;
	private:
		//  Called everytime transform, rotate, or scale matricies are changed.
		void calculateModelMatrix();
		
		//  Matricies
		glm::mat4 translate, rotate, scale;
		
		//  What program to run to render this mesh
		GLuint program;
};
