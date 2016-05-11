#ifndef MODEL_H
#define MODEL_H

#include <GLFW/glfw3.h>

typedef struct _Model {
	int length;
	GLfloat *vertices;
	GLfloat *colors;
	GLuint vertexbuffer;
	GLuint colorbuffer;
} Model;

void model_init(Model *model);
void model_set_data_length(Model *model, int length);
void model_set_vertices(Model *model, GLfloat *vertices);
void model_set_colors(Model *model, GLfloat *colors);
int model_bind(Model *model);
void model_dispose(Model *model);

#endif //MODEL_H
