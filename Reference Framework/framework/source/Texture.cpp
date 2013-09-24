/**
 * @file Texture.cpp
 *
 * OpenGL Framework
 * 2013
 */

#include <Texture.h>
#include <cassert>

#include <Debug.h>

using namespace glframework;
using namespace std;

Texture::Texture(const Header& header, BYTE* data)
	: _id(0),
	  _width(header.width),
	  _height(header.height),
	  _depth(header.depth),
	  _data(data)
{
	initialize();
}

Texture::~Texture()
{
	destroy();
}


// Public

int Texture::width() const
{
	return _width;
}

int Texture::height() const
{
	return _height;
}

void Texture::bind(const Shader* shader) const
{
	glActiveTexture(GL_TEXTURE0);
	checkGLErrors();
	
	bindObject(this);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	checkGLErrors();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	checkGLErrors();

	GLint location = glGetUniformLocation(shader->program(), "fwSampler");
	checkGLErrors();
	glUniform1i(location, 0);
	checkGLErrors();
}

// Static

Texture* Texture::load(const std::string& filename)
{
	ifstream stream;
	stream.open(filename, ios::binary);

	assert(stream.is_open());

	Header header = readHeader(stream);
	assert(header.type == 2);
	assert(header.depth == 24 || header.depth == 32);

	BYTE* data = readData(stream, header);
	stream.close();

	return new Texture(header, data);
}


// Private

void Texture::initialize()
{
	createObject();
	initializeObject();
}

void Texture::destroy()
{
	glDeleteTextures(1, &_id);
	checkGLErrors();

	delete[] _data;
}

void Texture::createObject()
{
	glGenTextures(1, &_id);
	checkGLErrors();
}

void Texture::initializeObject()
{
	bindObject(this);

	GLint format = GL_RGB;

	if(_depth == 32)
		format = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, format, _width, _height, 0, format, GL_UNSIGNED_BYTE, _data);
	checkGLErrors();

	bindObject(NULL);
}

// Static

void Texture::bindObject(const Texture* texture)
{
	GLuint id = 0;

	if(texture != 0)
		id = texture->_id;

	glBindTexture(GL_TEXTURE_2D, id);
	checkGLErrors();
}

Texture::Header Texture::readHeader(std::ifstream& stream)
{
	Header header;

	stream.seekg(2);
	stream.read((char*)&header.type, sizeof(header.type));

	stream.seekg(9, ios::cur);
	stream.read((char*)&header.width, sizeof(header.width));
	stream.read((char*)&header.height, sizeof(header.height));
	stream.read((char*)&header.depth, sizeof(header.depth));
	stream.read((char*)&header.descriptor, sizeof(header.descriptor));

	return header;
}

Texture::BYTE* Texture::readData(std::ifstream& stream, const Header& header)
{
	const int componentCount = header.depth / 8;
	const int dataSize = componentCount * header.width * header.height;

	BYTE* buffer = new BYTE[dataSize];
	stream.read((char*)buffer, dataSize);

	BYTE* data = formatData(buffer, dataSize, componentCount, header);
	delete[] buffer;

	return data;
}

Texture::BYTE* Texture::formatData(const BYTE* buffer, const int dataSize, const int componentCount, const Header& header)
{
	BYTE* data = new BYTE[dataSize];
	bool isOriginAtBottom = (header.descriptor & (1 << 5)) == 0;

	const int width = componentCount * header.width;

	int dataIndex;
	int bufferIndex;

	for(int y = 0; y < header.height; ++y)
	{
		for(int x = 0; x < width; x += componentCount)
		{
			dataIndex = (header.height - 1- y) * width + x;

			if(isOriginAtBottom)
				bufferIndex = dataIndex;
			else
				bufferIndex = y * width + x;

			data[dataIndex]		= buffer[bufferIndex + 2];
			data[dataIndex + 1] = buffer[bufferIndex + 1];
			data[dataIndex + 2] = buffer[bufferIndex];

			if(header.depth == 32)
				data[dataIndex + 3] = buffer[bufferIndex + 3];
		}
	}

	return data;
}