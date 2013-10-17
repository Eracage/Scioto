/**
 * @file VertexBuffer.h
 *
 * OpenGL Framework
 * 2013
 */

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <list>
#include <GL/glew.h>

#include <Shader.h>
#include <VertexArray.h>

namespace glframework
{
	class VertexBuffer
	{
	public:

		VertexBuffer();

		VertexBuffer(const VertexBuffer& vertexBuffer);
		
		~VertexBuffer();

		void addVertexArray(VertexArray* vertexArray);

		void clear();

		void setVertexArrays(const Shader* shader);

	private:

		std::list<VertexArray*> _vertexArrays;

		void destroyVertexArrays();
	};
}

#endif