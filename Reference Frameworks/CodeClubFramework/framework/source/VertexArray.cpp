/**
 * @file VertexArray.h
 *
 * OpenGL Framework
 * 2013
 */

#include <VertexArray.h>
#include <Debug.h>

using namespace devmath;
using namespace glframework;
using namespace std;

VertexArray::VertexArray(const string& name, const int componentCount, const int vertexCount)
	: _name(name),
	  _componentCount(componentCount),
	  _buffer(0)
{
	initializeBuffer(NULL, vertexCount, GL_DYNAMIC_DRAW);
}

VertexArray::VertexArray(const string& name, const vector<Vector2>& vertices)
	: _name(name),
	  _componentCount(Vector2::COMPONENTS),
	  _buffer(0)
{
	initializeVertices(vertices);
	initializeBuffer(&vertices.front(), vertices.size(), GL_STATIC_DRAW);
}

VertexArray::VertexArray(const string& name, const vector<Vector3>& vertices)
	: _name(name),
	  _componentCount(Vector3::COMPONENTS),
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

void VertexArray::addVertices(const vector<Vector2>& vertices, const int vertexOffset)
{
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	checkGLErrors();

	const int componentSize = sizeof(float) * Vector2::COMPONENTS;
	const GLintptr offset = componentSize * vertexOffset;
	const GLsizeiptr size = componentSize * vertices.size();

	glBufferSubData(GL_ARRAY_BUFFER, offset, size, &vertices.front());
	checkGLErrors();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	checkGLErrors();
}

void VertexArray::addVertices(const vector<Vector3>& vertices, const int vertexOffset)
{
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	checkGLErrors();

	const int componentSize = sizeof(float) * Vector3::COMPONENTS;
	const GLintptr offset = componentSize * vertexOffset;
	const GLsizeiptr size = componentSize * vertices.size();

	glBufferSubData(GL_ARRAY_BUFFER, offset, size, &vertices.front());
	checkGLErrors();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	checkGLErrors();
}

void VertexArray::setVertexData(const Shader* shader)
{
	GLint location = glGetAttribLocation(shader->program(), _name.c_str());
	checkGLErrors();
	glEnableVertexAttribArray(location);
	checkGLErrors();

	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	checkGLErrors();
	glVertexAttribPointer(location, _componentCount, GL_FLOAT, GL_FALSE, 0, 0);
	checkGLErrors();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	checkGLErrors();
}


// Private

void VertexArray::initializeVertices(const vector<Vector2>& vertices)
{
	size_t vertexCount = vertices.size();
	_vertices.resize(_componentCount * vertexCount);

	size_t index;

	for(size_t i = 0; i < vertexCount; ++i)
	{
		index = _componentCount * i;

		_vertices[index]	 = vertices[i].x;
		_vertices[index + 1] = vertices[i].y;
	}
}

void VertexArray::initializeVertices(const vector<Vector3>& vertices)
{
	size_t vertexCount = vertices.size();
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

void VertexArray::initializeBuffer(const GLvoid* data, const int vertexCount, const GLenum usage)
{
	glGenBuffers(1, &_buffer);
	checkGLErrors();
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	checkGLErrors();

	GLsizeiptr size = sizeof(float) * _componentCount * vertexCount;

	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	checkGLErrors();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	checkGLErrors();
}