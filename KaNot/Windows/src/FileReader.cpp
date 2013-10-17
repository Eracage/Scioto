#include "FileReader.h"

using namespace Scioto;
//Protected
std::string FileReader::loadFile(const std::string& fileLocation)
{
	std::stringstream stream;
#if WIN32
        stream.str("");
        myFile.open("assets/" + fileLocation,std::ios::in);

        if(myFile.is_open())
        {
                stream << myFile.rdbuf();
                myFile.close();
                return stream.str();
        }
        else
        {
                LOGI("File not found from %c", &fileLocation);
                myFile.close();
                return "";
        }
#elif __ANDROID__
        AAsset* asset = AAssetManager_open(LostCause::AssetManager::manager, fileLocation.c_str(), AASSET_MODE_UNKNOWN);
        off_t length = AAsset_getLength(asset);
        char* text = new char[length+1];
        if(AAsset_read(asset, text, length) < 1)
        {
                debug.write("File not loaded or EOF!");
        }
        AAsset_close(asset);
        text[length] = 0;
        std::string r(text);
        debug.write(r.c_str());
        delete text;
        return r;
#endif
}

GLubyte* FileReader::loadTGA(const std::string& fileName, tgaHeader &header)
{
#if __ANDROID__
        AAsset* asset = AAssetManager_open(AssetManager::manager, fileName.c_str(), AASSET_MODE_UNKNOWN);

    AAsset_read(asset, &header.idLength, 1);
    AAsset_read(asset, &header.colorMapType, 1);
    AAsset_read(asset, &header.type, 1);
    AAsset_seek(asset, 9, SEEK_CUR);
    AAsset_read(asset, &header.width, 2);
    AAsset_read(asset, &header.height, 2);
    AAsset_read(asset, &header.depth, 1);
    AAsset_read(asset, &header.descriptor, 1);
    AAsset_seek(asset, header.idLength, SEEK_CUR);
    
    debug.write("ID_LENGTH: %d", header.idLength);
    debug.write("COLOR_MAP_TYPE: %d", header.colorMapType);
    debug.write("TYPE: %d", header.type);
    debug.write("WIDTH: %d", header.width);
    debug.write("HEIGHT: %d", header.height);
    debug.write("DEPTH: %d", header.depth);
    debug.write("DESCCRIPTOR: %d", header.descriptor);
    
    //24bit / 8 = 3 (RGB), 32bit / 8 = 4 (RGBA)
    int componentCount = header.depth/8;
    
    int size = componentCount * header.width * header.height;
    GLubyte* data = new GLubyte[size];
    
    AAsset_read(asset, data, size);
    
    //data is now BGRA so we format it to RGBA
    for(int i = 0; i < size; i += componentCount)
    {
        GLubyte temp = data[i];
        
        //Switch red and blue
        data[i] = data[i+2];
        data[i+2] = temp;
    }
    
    AAsset_close(asset);
#else
        std::ifstream file;
        file.open("assets/" + fileName, std::ios::binary);

        file.read((char*)&header.idLength, 1);
        file.read((char*)&header.colorMapType, 1);
        file.read((char*)&header.type, 1);
        file.seekg(9, std::ios_base::cur);
        file.read((char*)&header.width, 2);
        file.read((char*)&header.height, 2);
        file.read((char*)&header.depth, 1);
        file.read((char*)&header.descriptor, 1);
        file.seekg(header.idLength, std::ios_base::cur);

        LOGI("ID_LENGTH: %d", header.idLength);
		LOGI("COLOR_MAP_TYPE: %d", header.colorMapType);
		LOGI("TYPE: %d", header.type);
		LOGI("WIDTH: %d", header.width);
		LOGI("HEIGHT: %d", header.height);
		LOGI("DEPTH: %d", header.depth);
		LOGI("DESCCRIPTOR: %d", header.descriptor);

    int componentCount = header.depth/8;
    
    int size = componentCount * header.width * header.height;
    GLubyte* data = new GLubyte[size];
    
        file.read((char*)data, size);

    for(int i = 0; i < size; i += componentCount)
    {
        GLubyte temp = data[i];
        
        data[i] = data[i+2];
        data[i+2] = temp;
    }
    
        file.close();
#endif
        return data;
}
//
//bool FileReader::loadOBJ(const std::string& fileName, std::vector<glm::vec4> &vertices, std::vector<glm::vec3> &normals, std::vector<GLushort> &elements)
//{
//#if __ANDROID__
//        AAsset* asset = AAssetManager_open(AssetManager::manager, fileName.c_str(), AASSET_MODE_UNKNOWN);
//    
//        char* temp = new char(1);
//        char* tempFloat = new char(10);
//        char* tempFace = new char(64);
//
//        glm::vec4 v = vec4(0,0,0,1);
//
//        for(int i = 0; i < AAsset_getLength(asset); i++)
//        {
//                AAsset_read(asset, temp, 1);
//
//                if(temp[0] == '#')
//                {
//                        //debug.write("Read comment line!");
//                        AAsset_seek(asset, 1, SEEK_CUR);
//                        while(temp[0] != '\n')
//                        {
//                                AAsset_read(asset, temp, 1);
//                        }
//                }
//                else if(temp[0] == 'o')
//                {
//                        //debug.write("Read object name!");
//                        AAsset_seek(asset, 1, SEEK_CUR);
//                        while(temp[0] != '\n')
//                        {
//                                AAsset_read(asset, temp, 1);
//                        }
//                }
//                else if(temp[0] == 's')
//                {
//                        //debug.write("Read something line!");
//                        AAsset_seek(asset, 1, SEEK_CUR);
//                        while(temp[0] != '\n')
//                        {
//                                AAsset_read(asset, temp, 1);
//                        }
//                }
//                else if(temp[0] == 'v')
//                {
//                        AAsset_read(asset, temp, 1);
//                        if(temp[0] == 'n')
//                        {
//                                while(temp[0] != '\n')
//                                {
//                                        AAsset_read(asset, temp, 1);
//                                }
//                        }
//                        else
//                        {
//                        AAsset_read(asset, temp, 1);
//
//                        if(temp[0] == '-')
//                        {
//                                AAsset_seek(asset, -1, SEEK_CUR);
//                                AAsset_read(asset, tempFloat, 9);
//                        }
//                        else
//                        {
//                                AAsset_seek(asset, -1, SEEK_CUR);
//                                AAsset_read(asset, tempFloat, 8);
//                        }
//
//                        v.x = std::atof(tempFloat);
//
//                        AAsset_seek(asset, 1, SEEK_CUR);
//                        AAsset_read(asset, temp, 1);
//
//                        if(temp[0] == '-')
//                        {
//                                AAsset_seek(asset, -1, SEEK_CUR);
//                                AAsset_read(asset, tempFloat, 9);
//                        }
//                        else
//                        {
//                                AAsset_seek(asset, -1, SEEK_CUR);
//                                AAsset_read(asset, tempFloat, 8);
//                        }
//
//                        v.y = std::atof(tempFloat);
//
//                        AAsset_seek(asset, 1, SEEK_CUR);
//                        AAsset_read(asset, temp, 1);
//
//                        if(temp[0] == '-')
//                        {
//                                AAsset_seek(asset, -1, SEEK_CUR);
//                                AAsset_read(asset, tempFloat, 9);
//                        }
//                        else
//                        {
//                                AAsset_seek(asset, -1, SEEK_CUR);
//                                AAsset_read(asset, tempFloat, 8);
//                        }
//
//                        v.z = std::atof(tempFloat);
//
//                        v.w = 1.0f;
//                        vertices.push_back(v);
//
//                        //debug.write("Vertexdata: %f %f %f", v.x,v.y,v.z);
//                        }
//                }
//                else if(temp[0] == 'f')
//                {
//                        AAsset_seek(asset, 1, SEEK_CUR);
//                        
//                        int k = 0;
//
//                        while(temp[0] != '\n')
//                        {
//                                AAsset_read(asset, temp, 1);
//                                tempFace[k] = temp[0];
//                                k++;
//                        }
//                        
//                        int a,b,c,d,e,f;
//                        sscanf(tempFace,"%d//%d %d//%d %d//%d", &a, &b, &c, &d, &e, &f );
//                        a--; b--; c--; d--; e--; f--;
//
//                        elements.push_back(a); elements.push_back(c); elements.push_back(e);
//
//                        //debug.write("Facedata: %d %d %d", a, c, e);
//                }
//                else
//                {
//
//                }
//                //temp = NULL;
//                temp[0]=' ';
//        }
//
//        std::vector<int> nb_seen;
//        normals.resize( vertices.size(), glm::vec3(0.0, 0.0, 0.0));
//        nb_seen.resize( vertices.size(), 0);
//        for (unsigned int i = 0; i <  elements.size(); i+=3)
//        {
//                GLushort ia =  elements[i];
//                GLushort ib =  elements[i+1];
//                GLushort ic =  elements[i+2];
//                glm::vec3 normal = glm::normalize(glm::cross(
//                        glm::vec3( vertices[ib]) - glm::vec3( vertices[ia]),
//                        glm::vec3( vertices[ic]) - glm::vec3( vertices[ia])));
// 
//                int v[3];  v[0] = ia;  v[1] = ib;  v[2] = ic;
//                for (int j = 0; j < 3; j++)
//                {
//                        GLushort cur_v = v[j];
//                        nb_seen[cur_v]++;
//                        if (nb_seen[cur_v] == 1)
//                        {
//                                normals[cur_v] = normal;
//                        } 
//                        else
//                        {
//                                // average
//                                normals[cur_v].x =  normals[cur_v].x * (1.0 - 1.0/nb_seen[cur_v]) + normal.x * 1.0/nb_seen[cur_v];
//                                normals[cur_v].y =  normals[cur_v].y * (1.0 - 1.0/nb_seen[cur_v]) + normal.y * 1.0/nb_seen[cur_v];
//                                normals[cur_v].z =  normals[cur_v].z * (1.0 - 1.0/nb_seen[cur_v]) + normal.z * 1.0/nb_seen[cur_v];
//                                normals[cur_v] = glm::normalize( normals[cur_v]);
//                        }
//                }
//                //debug.write("\n%f %f %f", normal.x,normal.y,normal.z);
//        }
//
//    AAsset_close(asset);
//#else
//        std::ifstream file;
//        file.open("assets/" + fileName, std::ios::in);
//
//        if( file == NULL )
//        {
//                debug.write("Impossible to open the file %c!\n", fileName.c_str());
//                file.close();
//                return false;
//        }
//
//        std::string line;
//        while (std::getline(file, line))
//        {
//                if (line.substr(0,2) == "v ")
//                {
//                        std::istringstream s(line.substr(2));
//                        vec4 v; s >> v.x; s >> v.y; s >> v.z; v.w = 1.0f;
//                        vertices.push_back(v);
//                        
//                        //debug.write("\nVertexdata: %f %f %f", v.x,v.y,v.z);
//                }
//                else if (line.substr(0,2) == "f ")
//                {
//                        std::string str = line.substr(2);
//                        int a,b,c,d,e,f;
//                        sscanf_s(str.c_str(),"%d//%d %d//%d %d//%d", &a, &b, &c, &d, &e, &f );
//                        a--; b--; c--; d--; e--; f--;
//                        elements.push_back(a); elements.push_back(c); elements.push_back(e);
//                        //debug.write("\nFaces! %d %d %d", a, c, e);
//                }
//                else if (line.substr(0,2) == "vn")
//                {
//                        std::istringstream s(line.substr(2));
//                        vec3 n; s >> n.x; s >> n.y; s >> n.z;
//                        //normals.push_back(n);
//
//                        //debug.write("\nNormals! %f %f %f", n.x, n.y, n.z);
//                }
//                else if (line[0] == '#')
//                { /* ignoring this line */ }
//                else
//                { /* ignoring this line */ }
//        }
//
//        std::vector<int> nb_seen;
//        normals.resize( vertices.size(), glm::vec3(0.0, 0.0, 0.0));
//        nb_seen.resize( vertices.size(), 0);
//        for (unsigned int i = 0; i <  elements.size(); i+=3)
//        {
//                GLushort ia =  elements[i];
//                GLushort ib =  elements[i+1];
//                GLushort ic =  elements[i+2];
//                glm::vec3 normal = glm::normalize(glm::cross(
//                        glm::vec3( vertices[ib]) - glm::vec3( vertices[ia]),
//                        glm::vec3( vertices[ic]) - glm::vec3( vertices[ia])));
// 
//                int v[3];  v[0] = ia;  v[1] = ib;  v[2] = ic;
//                for (int j = 0; j < 3; j++)
//                {
//                        GLushort cur_v = v[j];
//                        nb_seen[cur_v]++;
//                        if (nb_seen[cur_v] == 1)
//                        {
//                                normals[cur_v] = normal;
//                        } 
//                        else
//                        {
//                                // average
//                                normals[cur_v].x =  normals[cur_v].x * (1.0 - 1.0/nb_seen[cur_v]) + normal.x * 1.0/nb_seen[cur_v];
//                                normals[cur_v].y =  normals[cur_v].y * (1.0 - 1.0/nb_seen[cur_v]) + normal.y * 1.0/nb_seen[cur_v];
//                                normals[cur_v].z =  normals[cur_v].z * (1.0 - 1.0/nb_seen[cur_v]) + normal.z * 1.0/nb_seen[cur_v];
//                                normals[cur_v] = glm::normalize( normals[cur_v]);
//                        }
//                }
//                //debug.write("\n%f %f %f", normal.x,normal.y,normal.z);
//        }
//
//        file.close();
//#endif
//        return true;
//}

FileReader::~FileReader()
{
        
}

//Private
FileReader::FileReader()
{

}
FileReader::FileReader(const FileReader &)
{

}
