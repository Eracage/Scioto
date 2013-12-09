#include <VertexArray.h>

namespace Scioto
{
	VertexArray::VertexArray(const std::string& name, const int componentCount, const int vertexCount)
		: _name(name),
		  _componentCount(componentCount),
		  _buffer(0)
	{
		initializeBuffer(NULL, vertexCount, GL_DYNAMIC_DRAW);
	}

	VertexArray::VertexArray(const std::string& name, const std::vector<Vector2>& vertices)
		: _name(name),
		  _componentCount(2),
		  _buffer(0)
	{
		initializeVertices(vertices);
		initializeBuffer(&vertices.front(), vertices.size(), GL_STATIC_DRAW);
	}

	VertexArray::VertexArray(const std::string& name, const std::vector<Vector3>& vertices)
		: _name(name),
		  _componentCount(3),
		  _buffer(0)
	{
		initializeVertices(vertices);
		initializeBuffer(&vertices.front(), vertices.size(), GL_STATIC_DRAW);
	}

	VertexArray::VertexArray(const std::string& name, const std::vector<Vector4>& vertices)
		: _name(name),
		  _componentCount(4),
		  _buffer(0)
	{
		initializeVertices(vertices);
		initializeBuffer(&vertices.front(), vertices.size(), GL_STATIC_DRAW);
	}

	VertexArray::~VertexArray()
	{
		glDeleteBuffers(1, &_buffer);
	}


	// Public

	void VertexArray::AddVertices(const std::vector<Vector2>& vertices, const int vertexOffset)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _buffer);

		const int componentSize = sizeof(float) * 2;
		const GLintptr offset = componentSize * vertexOffset;
		const GLsizeiptr size = componentSize * vertices.size();

		glBufferSubData(GL_ARRAY_BUFFER, offset, size, &vertices.front());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexArray::AddVertices(const std::vector<Vector3>& vertices, const int vertexOffset)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _buffer);

		const int componentSize = sizeof(float) * 3;
		const GLintptr offset = componentSize * vertexOffset;
		const GLsizeiptr size = componentSize * vertices.size();

		glBufferSubData(GL_ARRAY_BUFFER, offset, size, &vertices.front());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexArray::AddVertices(const std::vector<Vector4>& vertices, const int vertexOffset)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _buffer);

		const int componentSize = sizeof(float) * 4;
		const GLintptr offset = componentSize * vertexOffset;
		const GLsizeiptr size = componentSize * vertices.size();

		glBufferSubData(GL_ARRAY_BUFFER, offset, size, &vertices.front());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexArray::setVertexData(const Shader* shader)
	{
		const GLint location = glGetAttribLocation(shader->Program, _name.c_str());
		glEnableVertexAttribArray(location);

		glBindBuffer(GL_ARRAY_BUFFER, _buffer);
		glVertexAttribPointer(location, _componentCount, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	// Private

	void VertexArray::initializeVertices(const std::vector<Vector2>& vertices)
	{
		const size_t vertexCount = vertices.size();
		_vertices.resize(_componentCount * vertexCount);

		size_t index;

		for(size_t i = 0; i < vertexCount; ++i)
		{
			index = _componentCount * i;

			_vertices[index]	 = vertices[i].x;
			_vertices[index + 1] = vertices[i].y;
		}
	}

	void VertexArray::initializeVertices(const std::vector<Vector3>& vertices)
	{
		const size_t vertexCount = vertices.size();
		_vertices.resize(_componentCount * vertexCount);

		size_t index;

		for(size_t i = 0; i < vertexCount; ++i)
		{
			index = _componentCount * i;

			_vertices[index]	 = vertices[i].x;
			_vertices[index + 1] = vertices[i].y;
			_vertices[index + 2] = vertices[i].z;
		}
	}

	void VertexArray::initializeVertices(const std::vector<Vector4>& vertices)
	{
		const size_t vertexCount = vertices.size();
		_vertices.resize(_componentCount * vertexCount);

		size_t index;

		for(size_t i = 0; i < vertexCount; ++i)
		{
			index = _componentCount * i;

			_vertices[index]	 = vertices[i].x;
			_vertices[index + 1] = vertices[i].y;
			_vertices[index + 2] = vertices[i].z;
			_vertices[index + 3] = vertices[i].w;
		}
	}

	void VertexArray::initializeBuffer(const GLvoid* data, const int vertexCount, const GLenum usage)
	{
		glGenBuffers(1, &_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, _buffer);

		const GLsizeiptr size = sizeof(float) * _componentCount * vertexCount;

		glBufferData(GL_ARRAY_BUFFER, size, data, usage);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}