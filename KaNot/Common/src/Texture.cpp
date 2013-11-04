#include <Texture.h>
#include <FileReader.h>

namespace Scioto
{
	Texture2D::Texture2D()
	{}

	Texture2D::Texture2D(const std::string& FileName)
	{
		loadTexture(FileName);
	}

	Texture2D::~Texture2D()
	{}

	void Texture2D::loadTexture(const std::string& FileName)
	{
		tgaHeader header;
		Pixels = FileReader::loadTGA(FileName,header);

		idLength = header.idLength;
		colorMapType = header.colorMapType;
		type = header.type;
		depth = header.depth;
		descriptor = header.descriptor;
		width = header.width;
		height = header.height;
		
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenTextures(1,&m_texture);
		checkGlError("GenTextures");

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		checkGlError("BindTexture");
		// Load the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, header.width, header.height, 0, GL_RGBA,
						GL_UNSIGNED_BYTE, Pixels);
 
		// Set the filtering mode
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

	}

	GLuint Texture2D::GetGLTextureID()
	{
		return m_texture;
	}

}