/**
 * @file IndexBuffer.cpp
 *
 * OpenGL Framework
 * 2013
 */

#include <IndexBuffer.h>
#include <GL/glew.h>

using namespace glframework;
using namespace std;

IndexBuffer::IndexBuffer() { }

IndexBuffer::IndexBuffer(const IndexBuffer& indexBuffer)
	: _indices(indexBuffer._indices) { }

IndexBuffer::~IndexBuffer() { }

const vector<INDEX>& IndexBuffer::indices() const
{
	return _indices;
}

void IndexBuffer::addIndex(const INDEX index)
{
	_indices.push_back(index);
}

void IndexBuffer::addIndices(const vector<INDEX>& indices)
{
	_indices.insert(_indices.end(), indices.begin(), indices.end());
}

void IndexBuffer::clear()
{
	_indices.clear();
}