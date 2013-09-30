/**
 * @file VertexBuffer.cpp
 *
 * OpenGL Framework
 * 2013
 */

#include <VertexBuffer.h>

using namespace glframework;
using namespace std;

VertexBuffer::VertexBuffer() { }

VertexBuffer::VertexBuffer(const VertexBuffer& vertexBuffer)
	: _vertexArrays(vertexBuffer._vertexArrays) { }
		
VertexBuffer::~VertexBuffer()
{
	destroyVertexArrays();
}


// Public

void VertexBuffer::addVertexArray(VertexArray* vertexArray)
{
	_vertexArrays.push_back(vertexArray);
}

void VertexBuffer::clear()
{
	destroyVertexArrays();
	_vertexArrays.clear();
}

void VertexBuffer::setVertexArrays(const Shader* shader)
{
	for(list<VertexArray*>::iterator i = _vertexArrays.begin(); i != _vertexArrays.end(); ++i)
		(*i)->setVertexData(shader);
}


// Private

void VertexBuffer::destroyVertexArrays()
{
	for(list<VertexArray*>::iterator i = _vertexArrays.begin(); i != _vertexArrays.end(); ++i)
		delete (*i);
}