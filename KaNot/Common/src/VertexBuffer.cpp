#include <VertexBuffer.h>

namespace Scioto
{
	
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
		for(size_t i = 0; i < _vertexArrays.size(); ++i)
			_vertexArrays[i]->setVertexData(shader);
	}


	// Private

	void VertexBuffer::destroyVertexArrays()
	{
		for(size_t i = 0; i < _vertexArrays.size(); ++i)
			delete _vertexArrays[i];
	}
}