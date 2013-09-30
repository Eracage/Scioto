/**
 * @file Texture.h
 *
 * OpenGL Framework
 * 2013
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include <fstream>
#include <string>
#include <GL/glew.h>

#include <Shader.h>

namespace glframework
{
	class Texture
	{
	public:

		typedef unsigned char BYTE;
		typedef unsigned short USHORT;

		struct Header
		{
			BYTE type;
			USHORT width;
			USHORT height;
			BYTE depth;
			BYTE descriptor;
		};

		Texture(const Header& header, BYTE* data);

		~Texture();

		int width() const;

		int height() const;

		void bind(const Shader* shader) const;

		static Texture* load(const std::string& filename);

	private:

		GLuint _id;

		int _width;
		int _height;
		int _depth;

		BYTE* _data;

		Texture(const Texture& texture);

		void initialize();
		void destroy();
		void createObject();
		void initializeObject();

		static void bindObject(const Texture* texture);
		static Header readHeader(std::ifstream& stream);
		static BYTE* readData(std::ifstream& stream, const Header& header);
		static BYTE* formatData(const BYTE* buffer, const int dataSize, const int componentCount, const Header& header);
	};
}

#endif