#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include "window.h"
#include "matrix.h"

typedef struct Input {
	Window *window;
	int stable;
	double lastTime;
	float speed;
	float x;
	float y;
	float z;
	float h_angle;
	float v_angle;
} Input;

void input_init(Input *input, Window *window, float x, float y, float z, float h_angle, float v_angle);
void input_reset(Input *input);
void input_get_data(Input *input, Vec3 *position, Vec3 *direction, Vec3 *right);

#endif //INPUT_H
