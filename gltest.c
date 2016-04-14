#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLEW_STATIC 1

const GLchar vertexShaderSource[] =
	"#version 330 core\n"
	"layout(location = 0) in vec3 vertexPosition_modelspace;\n"
	"void main() {\n"
	"    gl_Position.xyz = vertexPosition_modelspace;\n"
	"    gl_Position.w = 1.0;\n"
	"}";

const GLchar fragmentShaderSource[] =
	"#version 330 core\n"
	"out vec3 color;\n"
	"void main() {\n"
	"    color = vec3(1,0,0);\n"
	"}";

int printError() 
{
	GLenum error;
	while((error = glGetError()) != GL_NO_ERROR) {
		printf("Error: %i\n", error);
	}
}

int loadShader(GLuint *shader, GLenum type, const GLchar *source)
{
	*shader = glCreateShader(type);
	printf("Shader id: %p\n", shader);
	printError();

	int srclen = strlen(source);
	glShaderSource(*shader, 1, &source, &srclen);
	printf("Load shader: %i\n%s\n", srclen, source);
	printError();

	glCompileShader(*shader);
	printError();

	GLint compiled;
	
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE) {
		printf("Could not compile shader\n");


		GLint blen = 0;	
		GLsizei slen = 0;

		glGetShaderiv(*shader, GL_INFO_LOG_LENGTH , &blen);       

		if (blen > 0)
		{
			GLchar* compiler_log = (GLchar*)malloc(blen);

			glGetShaderInfoLog(*shader, blen, &slen, compiler_log);
			printf("Log:\n %s", compiler_log);
			free (compiler_log);
		} else {
			blen = 10;

			GLchar* compiler_log = (GLchar*)malloc(blen);

			glGetShaderInfoLog(*shader, blen, &slen, compiler_log);
			printf("Empty log:\n %.*s", slen, compiler_log);
			free (compiler_log);
		}


		return -1;
	}  

	printf("Compiled shader\n");
	return 0;
}

int createProgram(GLuint *program, GLuint vertexShader, GLuint fragmentShader)
{
	*program = glCreateProgram();

	glAttachShader(*program, vertexShader);
	glAttachShader(*program, fragmentShader);
	glLinkProgram(*program);  
	
	GLint linked;

	glGetProgramiv(*program, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		printf("Could not link program\n");
		return -1;
	}  

	printf("Linked program\n");
	return 0;
}

int main(void)
{
	GLFWwindow* window;

	if(!glfwInit()) {
		printf("Could not init GLFW");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	//Opengl 2.1
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	//Opengl 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS fix
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow( 1024, 768, "Test", NULL, NULL);
	if(!window) {
		fprintf( stderr, "Failed to open GLFW window.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	//#clear errors GLEW may trigger
	printError();
	

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);


	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);


	//Load vertex buffer
	//------------------
	
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


	//Create shaders
	//--------------
	
	GLuint vertexShader, fragmentShader;

	loadShader(&vertexShader, GL_VERTEX_SHADER, vertexShaderSource);
	loadShader(&fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderSource);


	//Create program
	//--------------

	GLuint program;
	createProgram(&program, vertexShader, fragmentShader);

	do {
		glClear( GL_COLOR_BUFFER_BIT );

		glUseProgram(program);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glDrawArrays(GL_TRIANGLES, 0, 3); 

		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	} while(
		glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0
	);

	// Dispose
	// -------

	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(program);

	glfwTerminate();
	return 0;
}
