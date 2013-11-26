#pragma once
#ifndef FILEREADER_H_SCIOTO
#define FILEREADER_H_SCIOTO

#include <stdio.h>
#include "OpenGL.h"

#include <fstream>
#include <sstream>

#ifdef __ANDROID__
#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>
#endif

#include "Debug.h"

namespace Scioto
{
	struct tgaHeader
	{
		GLubyte idLength;
		GLubyte colorMapType;
		GLubyte type;
		GLushort width;
		GLushort height;
		GLubyte depth;
		GLubyte descriptor;
	};

	class FileReader
	{
	public:

#ifdef __ANDROID__
static AAssetManager* A_Manager;
#endif

		FileReader();
		~FileReader();

		std::string loadFile(const std::string& fileLocation);
		static GLubyte* loadTGA(const std::string& fileName, tgaHeader &header);
		//static bool loadOBJ(const std::string& fileName, std::vector<glm::vec4> &vertices, std::vector<glm::vec3> &normals, std::vector<GLushort> &elements);


		FileReader(const FileReader &);

		std::ifstream myFile;
		std::stringstream stream;
	private:
	};
}

#endif