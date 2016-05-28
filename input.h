#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include "window.h"
#include "matrix.h"

typedef struct _Input {
	Window *window;
	int stable;
	double lastTime;
	float speed;
	float h_angle;
	float v_angle;
} Input;

void input_init(Input *input, Window *window, float h_angle, float v_angle);
void input_reset(Input *input);
void input_get_direction(Input *input, Vec3 *direction, Vec3 *right);

#endif //INPUT_H
