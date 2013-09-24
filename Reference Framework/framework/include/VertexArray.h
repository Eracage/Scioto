/**
 * @file VertexArray.h
 *
 * OpenGL Framework
 * 2013
 */

#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <string>
#include <vector>
#include <devmath/Vector2.h>
#include <devmath/Vector3.h>
#include <GL/glew.h>

#include <Shader.h>

namespace glframework
{
	class VertexArray
	{
	public:
		
		VertexArray(const std::string& name, const int componentCount, const int vertexCount);

		VertexArray(const std::string& name, const std::vector<devmath::Vector2>& vertices);

		VertexArray(const std::string& name, const std::vector<devmath::Vector3>& vertices);

		~VertexArray();

		void addVertices(const std::vector<devmath::Vector2>& vertices, const int vertexOffset);

		void addVertices(const std::vector<devmath::Vector3>& vertices, const int vertexOffset);

		void setVertexData(const Shader* shader);

	private:

		std::string _name;
		int _componentCount;

		std::vector<float> _vertices;
		GLuint _buffer;

		VertexArray(const VertexArray& vertexArray);

		void initializeVertices(const std::vector<devmath::Vector2>& vertices);
		void initializeVertices(const std::vector<devmath::Vector3>& vertices);
		void initializeBuffer(const GLvoid* data, const int vertexCount, const GLenum usage);
	};
}

#endif