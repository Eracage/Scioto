/**
 * @file Node.cpp
 *
 * OpenGL Framework
 * 2013
 */

#include <Node.h>

using namespace devmath;
using namespace glframework;

Node::Node()
	: _position(0.0f),
	  _rotation(Quaternion::identity()),
	  _transform(Matrix4::identity()) { }

Node::~Node() { }


// Public

const Vector3& Node::position() const
{
	return _position;
}

void Node::setPosition(const Vector3& value)
{
	_position = value;
	updateTransform();
}

const Quaternion& Node::rotation() const
{
	return _rotation;
}

void Node::setRotation(const Quaternion& value)
{
	_rotation = value;
	updateTransform();
}

Matrix4 Node::worldTransform() const
{
	return _transform;
}


// Protected

void Node::updateTransform()
{
	_transform = Matrix4::createTranslation(_position) * Matrix4(_rotation);
}