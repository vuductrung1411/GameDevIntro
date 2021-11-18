#include "Camera.h"

void Camera::SetValue(Coords c, int h, int w)
{
	Camera::coords = c;
	Camera::height = h;
	Camera::width = w;
}