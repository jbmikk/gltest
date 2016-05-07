#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "matrix.h"

#define GLEW_STATIC 1

const GLchar basicVertexShaderSource[] =
	"#version 330 core\n"
	"layout(location = 0) in vec3 vertexPosition_modelspace;\n"
	"void main() {\n"
	"    gl_Position.xyz = vertexPosition_modelspace;\n"
	"    gl_Position.w = 1.0;\n"
	"}";

const GLchar mvpVertexShaderSource[] =
	"#version 330 core\n"
	"layout(location = 0) in vec3 vertexPosition_modelspace;\n"
	"layout(location = 1) in vec3 vertexColor;\n"
	"uniform mat4 MVP;\n"
	"out vec3 fragmentColor;\n"
	"void main() {\n"
	"    gl_Position = MVP * vec4(vertexPosition_modelspace,1);\n"
	"    fragmentColor = vertexColor;\n"
	"}";

const GLchar fragmentShaderSource[] =
	"#version 330 core\n"
	"in vec3 fragmentColor;\n"
	"out vec3 color;\n"
	"void main() {\n"
	"    color = fragmentColor;\n"
	"}";

static const GLfloat cube_vertex_data[] = {
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
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

static const GLfloat cube_color_data[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
};

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

	window = glfwCreateWindow( 640, 480, "Test", NULL, NULL);
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
	static const GLfloat *vertex_data = cube_vertex_data;
	static const int vertex_count = sizeof(cube_vertex_data);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_count, vertex_data, GL_STATIC_DRAW);


	//Load color buffer
	//-----------------

	static const GLfloat *color_data = cube_color_data;
	static const int color_count = sizeof(cube_color_data);

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, color_count, color_data, GL_STATIC_DRAW);


	//Create shaders
	//--------------
	
	GLuint vertexShader, fragmentShader;

	loadShader(&vertexShader, GL_VERTEX_SHADER, mvpVertexShaderSource);
	loadShader(&fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderSource);


	//Create program
	//--------------

	GLuint program;
	createProgram(&program, vertexShader, fragmentShader);


	// Get MVP uniform
	// ---------------

	GLuint mvp_ul = glGetUniformLocation(program, "MVP");


	// Model Matrix
	// ------------

	Mat4 s;
	scale_m4(&s, 0.5f, 0.5f, 0.5f);
	printf("Scale:\n");
	print_m4(&s);

	Mat4 r;
	rotate_m4(&r, 1.0f, 1.0f, 1.0f, 0.2f);
	printf("Rotate:\n");
	print_m4(&r);

	Mat4 t;
	translate_m4(&t, 0.1f, 0.1f, -2.0f);
	printf("Translate:\n");
	print_m4(&t);

	Mat4 rs;
	printf("Rotated*Scaled:\n");
	mul_m4(&rs, &r, &s);
	print_m4(&rs);

	Mat4 model;
	printf("Model:\n");
	mul_m4(&model, &t, &rs);
	print_m4(&model);


	// Projection Matrix
	// -----------------

	Mat4 projection;
	perspective_m4(&projection, 1.0f, (640.0f/480.0f), 0.1f, 100.0f);
	printf("Perspective:\n");
	print_m4(&projection);
	

	// Mvp Matrix
	// ----------
	
	Mat4 mvp;
	mul_m4(&mvp, &projection, &model);
	printf("Perspective:\n");
	print_m4(&mvp);
	
	do {
		glClear( GL_COLOR_BUFFER_BIT );

		glUseProgram(program);
		
		// Set MVP transform
		glUniformMatrix4fv(mvp_ul, 1, GL_TRUE, &mvp[0][0]);

		// Cube vertex
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

		// Cube colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glDrawArrays(GL_TRIANGLES, 0, vertex_count*3); 

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
	glDetachShader(program, fragmentShader);
	glDetachShader(program, vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteProgram(program);

	glfwTerminate();
	return 0;
}
