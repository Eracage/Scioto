/**
 * @file Node.h
 *
 * OpenGL Framework
 * 2013
 */

#ifndef NODE_H
#define NODE_H

#include <devmath/Matrix4.h>
#include <devmath/Quaternion.h>
#include <devmath/Vector3.h>

namespace glframework
{
	class Node
	{
	public:

		Node();

		virtual ~Node();

		const devmath::Vector3& position() const;

		void setPosition(const devmath::Vector3& value);

		const devmath::Quaternion& rotation() const;

		void setRotation(const devmath::Quaternion& value);

		devmath::Matrix4 worldTransform() const;

	protected:

		devmath::Vector3 _position;
		devmath::Quaternion _rotation;
		devmath::Matrix4 _transform;

		virtual void updateTransform();

	private:

		Node(const Node& node);
	};
}

#endif