#ifndef OBJIMPORT_H
#define OBJIMPORT_H

#include <fstream>
#include <string>
#include <vector>

#include <IndexBuffer.h>
#include <Mesh.h>
#include <VertexBuffer.h>
#include <devmath/Vector2.h>
#include <devmath/Vector3.h>

namespace glframework
{
	class ObjImport
	{
	public:

		ObjImport();

		~ObjImport();

		Mesh* load(const std::string& filename);

	private:

		std::ifstream _file;
		std::vector<std::string> _tokens;
		
		std::vector<devmath::Vector3> _vertexPositions;
		std::vector<devmath::Vector3> _vertexNormals;
		std::vector<devmath::Vector2> _vertexTextureCoords;
		std::vector<INDEX> _indices;

		ObjImport(const ObjImport& objImport);

		void readTokens();
		void parseTokens();
		Mesh* createMesh() const;
		void addVertexPosition(const size_t tokenIndex);
		void addVertexNormal(const size_t tokenIndex);
		void addVertexTextureCoord(const size_t tokenIndex);
		void addIndex(const size_t tokenIndex);
		VertexBuffer* createVertexBuffer() const;
		IndexBuffer* createIndexBuffer() const;
	};
}

#endif