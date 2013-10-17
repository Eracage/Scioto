/**
 * @file Camera.h
 *
 * OpenGL Framework
 * 2013
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <devmath/Matrix4.h>
#include <devmath/Rectangle.h>

#include <Node.h>

namespace glframework
{
	class Camera : public Node
	{
	public:

		Camera(const devmath::Rectangle& viewport);

		~Camera();

		const devmath::Matrix4& projectionTransform() const;

		const devmath::Matrix4& viewTransform() const;

	private:

		static const float FIELD_OF_VIEW_Y;
		static const float NEAR_Z;
		static const float FAR_Z;

		devmath::Matrix4 _viewTransform;
		devmath::Matrix4 _projectionTransform;

		Camera(const Camera& camera);

		void createProjectionTransform(const devmath::Rectangle& viewport);
		void updateTransform();
	};
}

#endif