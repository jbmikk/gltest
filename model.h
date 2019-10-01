#ifndef MODEL_H
#define MODEL_H

#include <GLFW/glfw3.h>

typedef struct Model {
	int length;
	GLfloat *vertices;
	GLfloat *colors;
	GLfloat *uv_map;
	GLuint vertexbuffer;
	GLuint colorbuffer;
	GLuint uvbuffer;
	char const *texture_path;
	GLuint texture_id;
} Model;

void model_init(Model *model);
void model_set_data_length(Model *model, int length);
void model_set_vertices(Model *model, GLfloat *vertices);
void model_set_colors(Model *model, GLfloat *colors);
void model_set_uv_map(Model *model, GLfloat *uv_map);
void model_set_texture(Model *model, char const *path);
int model_bind(Model *model);
void model_dispose(Model *model);

#endif //MODEL_H
