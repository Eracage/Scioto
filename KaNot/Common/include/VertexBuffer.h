#pragma once
#ifndef VERTEX_BUFFER_H_SCIOTO
#define	VERTEX_BUFFER_H_SCIOTO

#include <VertexArray.h>
#include <vector>

namespace Scioto
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

		std::vector<VertexArray*> _vertexArrays;

		void destroyVertexArrays();
	};
}

#endif