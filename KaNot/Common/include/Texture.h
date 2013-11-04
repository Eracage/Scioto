#pragma once
#ifndef TEXTURE_H
#define	TEXTURE_H

#include <Debug.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

namespace Scioto
{
	class Texture2D
	{
	public:
		Texture2D();
		Texture2D(const std::string& FileName);
		~Texture2D();

		void loadTexture(const std::string& FileName);
		GLuint GetGLTextureID();

		unsigned char idLength, colorMapType, type, depth, descriptor;
		unsigned short width, height;

	private:
		Texture2D(Texture2D& Texture);

		GLuint m_texture;
		unsigned char* Pixels;

	};
}

#endif