
#include "model.h"

void model_init(Model *model)
{
	model->length = 0;
	model->vertices = NULL;
	model->colors = NULL;
	model->vertexbuffer = 0;
	model->colorbuffer = 0;
}

void model_set_data_length(Model *model, int length)
{
	model->length = length;
}

void model_set_vertices(Model *model, GLfloat *vertices)
{
	model->vertices = vertices;
}

void model_set_colors(Model *model, GLfloat *colors)
{
	model->colors = colors;
}

int model_bind(Model *model)
{
	glGenBuffers(1, &model->vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, model->vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, model->length, model->vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &model->colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, model->colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, model->length, model->colors, GL_STATIC_DRAW);
}

int model_render(Model *model)
{
	// Cube vertex
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, model->vertexbuffer);
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
	glBindBuffer(GL_ARRAY_BUFFER, model->colorbuffer);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glDrawArrays(GL_TRIANGLES, 0, model->length*3); 

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void model_dispose(Model *model)
{
	glDeleteBuffers(1, &model->vertexbuffer);
	glDeleteBuffers(1, &model->colorbuffer);
}
