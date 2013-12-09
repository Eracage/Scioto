#pragma once
#ifndef VERTEX_ARRAY_H_SCIOTO
#define	VERTEX_ARRAY_H_SCIOTO

#include <vector>
#include <Sciotomath\Vector.h>
#include <Shader.h>

namespace Scioto
{
	class VertexArray
	{
	public:
		VertexArray(const std::string& name, const int componentCount, const int vertexCount);

		VertexArray(const std::string& name, const std::vector<Vector2>& vertices);

		VertexArray(const std::string& name, const std::vector<Vector3>& vertices);

		VertexArray(const std::string& name, const std::vector<Vector4>& vertices);

		~VertexArray();

		void AddVertices(const std::vector<Vector2>& vertices, const int vertexOffset);

		void AddVertices(const std::vector<Vector3>& vertices, const int vertexOffset);

		void AddVertices(const std::vector<Vector4>& vertices, const int vertexOffset);

		void setVertexData(const Shader* shader);

	private:

		std::string _name;
		int _componentCount;

		std::vector<float> _vertices;
		GLuint _buffer;

		VertexArray(const VertexArray& vertexArray);

		void initializeVertices(const std::vector<Vector2>& vertices);
		void initializeVertices(const std::vector<Vector3>& vertices);
		void initializeVertices(const std::vector<Vector4>& vertices);
		void initializeBuffer(const GLvoid* data, const int vertexCount, const GLenum usage);
	};
}

#endif