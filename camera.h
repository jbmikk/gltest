#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include "matrix.h"


typedef struct _Camera {
	float h_angle;
	float v_angle;
	float fov;
	float aspect;
	Vec3 pos;
	Vec3 center;
	Vec3 up;
} Camera;

void camera_init(Camera *camera);
void camera_get_matrix(Camera *camera, Mat4 *vp);
void camera_set_fov(Camera *camera, float fov);
void camera_set_aspect(Camera *camera, float aspect);
void camera_set_position(Camera *camera, Vec3 *position);
void camera_set_center(Camera *camera, Vec3 *center);
void camera_set_up(Camera *camera, Vec3 *up);


#endif //CAMERA_H
