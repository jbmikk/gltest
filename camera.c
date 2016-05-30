#include "camera.h"

void camera_init(Camera *camera)
{
	camera->h_angle = 0;
	camera->v_angle = 0;
}

void camera_set_fov(Camera *camera, float fov)
{
	camera->fov = fov;
}

void camera_set_aspect(Camera *camera, float aspect)
{
	camera->aspect = aspect;
}

void camera_set_position(Camera *camera, Vec3 *position)
{
	camera->pos[0] = (*position)[0];
	camera->pos[1] = (*position)[1];
	camera->pos[2] = (*position)[2];
}

void camera_set_center(Camera *camera, Vec3 *center)
{
	camera->center[0] = (*center)[0];
	camera->center[1] = (*center)[1];
	camera->center[2] = (*center)[2];
}

void camera_set_up(Camera *camera, Vec3 *up)
{
	camera->up[0] = (*up)[0];
	camera->up[1] = (*up)[1];
	camera->up[2] = (*up)[2];
}

void camera_get_matrix(Camera *camera, Mat4 *vp)
{
	Mat4 view;
	look_at_m4(&view, &camera->pos, &camera->center, &camera->up);

	Mat4 proj;
	perspective_m4(&proj, camera->fov, camera->aspect, 0.01f, 100.0f);

	mul_m4(vp, &proj, &view);
}
