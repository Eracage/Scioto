
#include <ObjImport.h>

#include <assert.h>
#include <VertexArray.h>

using namespace devmath;
using namespace glframework;
using namespace std;

ObjImport::ObjImport() {}

ObjImport::~ObjImport() {}

// Public

Mesh* ObjImport::load(const string& filename)
{
	_file.open(filename, ios::in);
	assert(!_file.fail());
	readTokens();
	_file.close();

	parseTokens();
	return createMesh();
}

// Private

void ObjImport::readTokens()
{
	char character;
	string token;

	while(!_file.eof())
	{
		character = (char)_file.get();

		switch(character)
		{
			case '\t':	// tabulator
			case '\n':	// new line
			case '\r':	// to start of new row
			case ' ':	// space
			case '/':
				if(!token.empty())
				{
					_tokens.push_back(token);
					token = string();
				}

				break;

			case '#':
				while(!_file.eof() && character != '\n')
					character = (char)_file.get();

				break;

			default:
				token.push_back(character);
				break;
		}
	}

	if(!token.empty())
	{
		_tokens.push_back(token);
	}
}

void ObjImport::parseTokens()
{
	const size_t tokenCount = _tokens.size();

	for(size_t i = 0; i < tokenCount; ++i)
	{
		if(_tokens[i] == "v")
		{
			addVertexPosition(i + 1);
			i += 3;
		}
		else if (_tokens[i] == "vn")
		{
			addVertexNormal(i + 1);
			i += 3;
		}
		else if (_tokens[i] == "vt")
		{
			addVertexTextureCoord(i + 1);
			i += 3;
		}
		else if (_tokens[i] == "f")
		{
			addIndex(i + 1);
			i += 9;
		}

	}
}

Mesh* ObjImport::createMesh() const
{
	VertexBuffer* vertexBuffer = createVertexBuffer();
	IndexBuffer* indexBuffer = createIndexBuffer();

	return new Mesh(vertexBuffer, indexBuffer);
}

void ObjImport::addVertexPosition(const size_t tokenIndex)
{
	Vector3 vertex;
	vertex.x = (float)atof(_tokens[tokenIndex].c_str());
	vertex.y = (float)atof(_tokens[tokenIndex + 1].c_str());
	vertex.z = (float)atof(_tokens[tokenIndex + 2].c_str());

	_vertexPositions.push_back(vertex);
}

void ObjImport::addVertexNormal(const size_t tokenIndex)
{
	Vector3 vertex;
	vertex.x = (float)atof(_tokens[tokenIndex].c_str());
	vertex.y = (float)atof(_tokens[tokenIndex + 1].c_str());
	vertex.z = (float)atof(_tokens[tokenIndex + 2].c_str());

	_vertexNormals.push_back(vertex);
}

void ObjImport::addVertexTextureCoord(const size_t tokenIndex)
{
	Vector2 vertex;
	vertex.x = (float)atof(_tokens[tokenIndex].c_str());
	vertex.y = (float)atof(_tokens[tokenIndex + 1].c_str());

	_vertexTextureCoords.push_back(vertex);
}

void ObjImport::addIndex(const size_t tokenIndex)
{
	INDEX index;

	for(int i = 0; i < 9; ++i)
	{
		index = atoi(_tokens[tokenIndex + i].c_str()) - 1;
		_indices.push_back(index);
	}
}

VertexBuffer* ObjImport::createVertexBuffer() const
{
	vector<devmath::Vector3> vertexPositions;
	vector<devmath::Vector3> vertexNormals;
	vector<devmath::Vector2> vertexTextureCoords;

	const size_t indexCount = _indices.size();

	for(size_t i = 0; i < indexCount; i += 3)
	{
		vertexPositions.push_back(_vertexPositions[_indices[i]]);
		vertexNormals.push_back(_vertexNormals[_indices[i + 2]]);
		vertexTextureCoords.push_back(_vertexTextureCoords[_indices[i + 1]]);
	}
	
	VertexArray* positionArray = new VertexArray("fwPosition", vertexPositions);
	VertexArray* normalArray = new VertexArray("fwNormal", vertexNormals);
	VertexArray* textureCoordArray = new VertexArray("fwTextureCoord", vertexTextureCoords);

	VertexBuffer* vertexBuffer = new VertexBuffer();
	vertexBuffer->addVertexArray(positionArray);
	vertexBuffer->addVertexArray(normalArray);
	vertexBuffer->addVertexArray(textureCoordArray);

	return vertexBuffer;
}

IndexBuffer* ObjImport::createIndexBuffer() const
{
	const size_t indexCount = _indices.size() / 3;
	IndexBuffer* indexBuffer = new IndexBuffer();

	for(size_t i = 0; i < indexCount; ++i)
		indexBuffer->addIndex(i);

	return indexBuffer;
}