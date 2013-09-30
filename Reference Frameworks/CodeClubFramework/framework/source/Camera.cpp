/**
 * @file Camera.cpp
 *
 * OpenGL Framework
 * 2013
 */

#include <Camera.h>

#include <cmath>
#include <devmath/Utils.h>

using namespace devmath;
using namespace glframework;

Camera::Camera(const Rectangle& viewport)
	: _viewTransform(Matrix4::identity()),
	  _projectionTransform(Matrix4::identity())
{
	createProjectionTransform(viewport);
}

Camera::~Camera() { }


// Public

const Matrix4& Camera::projectionTransform() const
{
	return _projectionTransform;
}

const Matrix4& Camera::viewTransform() const
{
	return _viewTransform;
}


// Private

const float Camera::FIELD_OF_VIEW_Y = toRadians(90.0f);
const float Camera::NEAR_Z = 1.0f;
const float Camera::FAR_Z = 1000.0f;

void Camera::createProjectionTransform(const Rectangle& viewport)
{
	const float aspectRatio = (float)viewport.width / viewport.height;

	const float top = NEAR_Z * tan(FIELD_OF_VIEW_Y / 2.0f);
	const float bottom = -top;
	const float right = top * aspectRatio;
	const float left = -right;

	const float width = right - left;
	const float height = bottom - top;
	const float depth = FAR_Z - NEAR_Z;

	_projectionTransform = Matrix4
	(
		2.0f * NEAR_Z / width,	0.0f,					   0.0f,						   0.0f,
		0.0f,					2.0f * NEAR_Z / -height,   0.0f,						   0.0f,
		(left + right) / width, (top + bottom) / -height, -(NEAR_Z + FAR_Z) / depth,	  -1.0f,
		0.0f,					0.0f,					  -2.0f * NEAR_Z * FAR_Z / depth,  0.0f
	);
}

void Camera::updateTransform()
{
	Node::updateTransform();

	Quaternion inverseRotation = _rotation.inverse();
	_viewTransform = Matrix4::createTranslation(-_position) * Matrix4(inverseRotation);
}