#include "input.h"
#include "math.h"

void input_init(Input *input, Window *window, float x, float y, float z, float h_angle, float v_angle)
{
	input->window = window;
	input->stable = 0;
	input->lastTime = 0;
	input->speed = 0.1f;
	input->x = x;
	input->y = y;
	input->z = z;
	input->h_angle = h_angle;
	input->v_angle = v_angle;

	input_reset(input);
}

void input_reset(Input *input)
{
	Window *window = input->window;
	glfwSetCursorPos(window->handle, window->width/2, window->height/2);
}

void input_get_data(Input *input, Vec3 *position, Vec3 *direction, Vec3 *right)
{
	Window *window = input->window;
	double xpos, ypos;
	double currentTime = glfwGetTime();
	double delta = (float)currentTime - input->lastTime;
	input->lastTime = currentTime;

	glfwGetCursorPos(window->handle, &xpos, &ypos);
	input_reset(input);

	int h_diff = window->width/2 - (int)xpos;
	int v_diff = window->height/2 - (int)ypos;

	if(!input->stable) {
		if(
			h_diff < 0.001 && h_diff > -0.001 &&
			v_diff < 0.001 && v_diff > -0.001
		) {
			input->stable = 1;
		} else {
			h_diff = 0;
			v_diff = 0;
		}
	}

	float dh_angle = input->speed * delta * (float)h_diff;
	float dv_angle = -input->speed * delta * (float)v_diff;
	
	input->h_angle += dh_angle;
	input->v_angle += dv_angle;

	(*direction)[0] = cos(input->v_angle) * sin(input->h_angle);
	(*direction)[1] = sin(input->v_angle);
	(*direction)[2] = cos(input->v_angle) * cos(input->h_angle);

	(*right)[0] = sin(input->h_angle - 3.14f/2.0f);
	(*right)[1] = 0;
	(*right)[2] = cos(input->h_angle - 3.14f/2.0f);

	float speed = input->speed*10;

	if (glfwGetKey(window->handle, GLFW_KEY_UP) == GLFW_PRESS){
		input->x += (*direction)[0] * delta * speed;
		input->y += (*direction)[1] * delta * speed;
		input->z += (*direction)[2] * delta * speed;
	}
	if (glfwGetKey(window->handle, GLFW_KEY_DOWN) == GLFW_PRESS){
		input->x -= (*direction)[0] * delta * speed;
		input->y -= (*direction)[1] * delta * speed;
		input->z -= (*direction)[2] * delta * speed;
	}
	if (glfwGetKey(window->handle, GLFW_KEY_RIGHT) == GLFW_PRESS){
		input->x -= (*right)[0] * delta * speed;
		input->y -= (*right)[1] * delta * speed;
		input->z -= (*right)[2] * delta * speed;
	}
	if (glfwGetKey(window->handle, GLFW_KEY_LEFT) == GLFW_PRESS){
		input->x += (*right)[0] * delta * speed;
		input->y += (*right)[1] * delta * speed;
		input->z += (*right)[2] * delta * speed;
	}

	(*position)[0] = input->x;
	(*position)[1] = input->y;
	(*position)[2] = input->z;

}
