/**
 * @file Mesh.h
 *
 * OpenGL Framework
 * 2013
 */

#ifndef MESH_H
#define MESH_H

#include <Graphics.h>
#include <IndexBuffer.h>
#include <Node.h>
#include <VertexBuffer.h>

namespace glframework
{
	class Mesh : public Node
	{
	public:

		Mesh(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer);

		~Mesh();

		void render(Graphics* graphics) const;

	private:

		VertexBuffer* _vertexBuffer;
		IndexBuffer* _indexBuffer;

		Mesh(const Mesh& mesh);
	};
}

#endif