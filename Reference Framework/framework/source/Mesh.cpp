/**
 * @file Mesh.cpp
 *
 * OpenGL Framework
 * 2013
 */

#include <Mesh.h>

using namespace glframework;

Mesh::Mesh(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer)
	: _vertexBuffer(vertexBuffer),
	  _indexBuffer(indexBuffer) { }

Mesh::~Mesh()
{
	delete _indexBuffer;
	delete _vertexBuffer;
}


// Public

void Mesh::render(Graphics* graphics) const
{
	graphics->setVertexBuffer(_vertexBuffer);
	graphics->setIndexBuffer(_indexBuffer);
	graphics->setWorldTransform(worldTransform());
	graphics->render();
}