#include <Engine.h>
#include <stdlib.h>

using namespace Scioto;

Engine::Engine()
{
	const char gVertexShader[] = 
    "attribute vec3 vPosition;\n"
	"attribute vec2 vUv;\n"
	"uniform mat4 Projection;\n"
	"uniform mat4 Translation;\n"
	"varying vec2 Uv;\n"
    "void main() {\n"
	"  gl_Position = vec4(vPosition,1.0);\n"
	"  gl_Position *= Translation*Projection;\n"	
	"  Uv = vUv;\n"
    "}\n";

	const char gFragmentShader[] = 
	"precision mediump float;\n"
	"varying vec2 Uv;\n"
	"uniform sampler2D s_texture;\n"
    "void main() {\n"
    "  gl_FragColor = texture2D(s_texture,Uv);\n"
    "}\n"; 

	shader = new Shader(gVertexShader,gFragmentShader);




	////////////////////////////////////////////////////TEMP
	
    num_vertices = 6*5;

    Data = (GLfloat*)malloc(sizeof(GLfloat)*num_vertices);

    float v = 128; 

    Data[0] = -v; 
    Data[1] = -v; 
    Data[2] = 0; 

    Data[3] = 0; 
    Data[4] = 0; 


    Data[5] = -v; 
    Data[6] = v; 
    Data[7] = 0;

    Data[8] = 0; 
    Data[9] = 1; 


    Data[10] = v; 
    Data[11] = -v; 
	Data[12] = 0; 

    Data[13] = 1; 
    Data[14] = 0; 
    

    Data[15] = -v; 
    Data[16] = v; 
    Data[17] = 0; 

	Data[18] = 0; 
    Data[19] = 1; 


    Data[20] = v; 
    Data[21] = v; 
	Data[22] = 0; 

    Data[23] = 1; 
    Data[24] = 1; 


    Data[25] = v; 
    Data[26] = -v; 
    Data[27] = 0; 

	Data[28] = 1; 
    Data[29] = 0; 

	
    //create VBO
    glGenBuffers(1,&VBO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glBufferData(GL_ARRAY_BUFFER,sizeof(Data)*num_vertices,Data,GL_DYNAMIC_DRAW);
	
	Data = (GLfloat*)malloc(sizeof(GLfloat)*num_vertices); 

    v =64;
	float s = 0;
    Data[0] = -v+s; 
    Data[1] = -v+s; 
    Data[2] = 0.1f; 

    Data[3] = 0; 
    Data[4] = 0; 


    Data[5] = -v+s; 
    Data[6] = v+s; 
    Data[7] = 0.1f;

    Data[8] = 0; 
    Data[9] = 1; 


    Data[10] = v+s; 
    Data[11] = -v+s; 
	Data[12] = 0.1f; 

    Data[13] = 1; 
    Data[14] = 0; 
    

    Data[15] = -v+s; 
    Data[16] = v+s; 
    Data[17] = 0.1f; 

	Data[18] = 0; 
    Data[19] = 1; 


    Data[20] = v+s; 
    Data[21] = v+s; 
	Data[22] = 0.1f; 

    Data[23] = 1; 
    Data[24] = 1; 


    Data[25] = v+s; 
    Data[26] = -v+s; 
    Data[27] = 0.1f; 

	Data[28] = 1; 
    Data[29] = 0; 

	glGenBuffers(1,&VBO2); 

	glBindBuffer(GL_ARRAY_BUFFER,VBO2); 

    glBufferData(GL_ARRAY_BUFFER,sizeof(Data)*num_vertices,Data,GL_DYNAMIC_DRAW);
	checkGlError("BindBuffer");
	Position = glGetAttribLocation(shader->Program,"vPosition");
	Uv = glGetAttribLocation(shader->Program,"vUv");
	loc = glGetUniformLocation(shader->Program, "s_texture");
	loc2 = glGetUniformLocation(shader->Program, "Projection");
	loc3 = glGetUniformLocation(shader->Program, "Translation");

	GLubyte* pixels = Scioto::FileReader::loadTGA("Test.tga",header);

	//FileReader *FR = new FileReader("Test.tga");
	
	//unsigned char*buffer = (unsigned char*)malloc(sizeof(unsigned char)*4);
	//move to position 12, next 4 bytes are size
	//
	/*FR->FileSeek(12,0);
	FR->ReadBytes(4,buffer);
	int sizex= buffer[0]+buffer[1]*256;
	int sizey= buffer[2]+buffer[3]*256;
	free(buffer);
	
	buffer = (unsigned char*)malloc(sizeof(unsigned char)*1);
	FR->FileSeek(16,0);
	FR->ReadBytes(1,buffer);
	int bpp = buffer[0];
	free(buffer);
	
	int datasize = sizex*sizey*bpp/8;
	pixels = (unsigned char*)malloc(sizeof(unsigned char)*datasize);
	unsigned char *Buffer = (unsigned char*)malloc(sizeof(unsigned char)*datasize);
	
	FR->FileSeek(18,0);
	FR->ReadBytes(datasize,Buffer);	
	for(int i = 0;i<datasize;i+=4)
	{
		pixels[i+0] = Buffer[i+2];
		pixels[i+1] = Buffer[i+1];
		pixels[i+2] = Buffer[i+0];
		pixels[i+3] = Buffer[i+3];
	}
	delete FR;*/

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1,&Texture);
	checkGlError("GenTextures");
		
    // Bind the texture object
    glBindTexture(GL_TEXTURE_2D, Texture);
	checkGlError("BindTexture");
	glActiveTexture(GL_TEXTURE0);
//GLuint*pixels = NULL;
    // Load the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, header.width, header.height, 0, GL_RGBA,
                    GL_UNSIGNED_BYTE, pixels);
 
    // Set the filtering mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

	GLfloat Projection[16] = 
	{
		 1.0f/1024.0f, 0,	0,	-1
		,0,	1.0f/768.0f,	0,1
		,0,	0,	1,	0
		,0,	0,	0,	1};

	GLfloat Translation[16] = 
	{
		 1, 0,	0,	64
		,0,	1,	0,	-384
		,0,	0,	1,	0
		,0,	0,	0,	1
	};

	GlTranslation = (GLfloat*)malloc(4*4*sizeof(float));
	GlTranslation[0] = Translation[0];
	GlTranslation[1] = Translation[1];
	GlTranslation[2] = Translation[2];
	GlTranslation[3] = Translation[3];
	
	GlTranslation[4] = Translation[4];
	GlTranslation[5] = Translation[5];
	GlTranslation[6] = Translation[6];
	GlTranslation[7] = Translation[7];

	GlTranslation[8] = Translation[8];
	GlTranslation[9] = Translation[9];
	GlTranslation[10] = Translation[10];
	GlTranslation[11] = Translation[11];

	GlTranslation[12] = Translation[12];
	GlTranslation[13] = Translation[13];
	GlTranslation[14] = Translation[14];
	GlTranslation[15] = Translation[15];

	GlProjection = (GLfloat*)malloc(4*4*sizeof(float));
	GlProjection[0] = Projection[0];
	GlProjection[1] = Projection[1];
	GlProjection[2] = Projection[2];
	GlProjection[3] = Projection[3];
	
	GlProjection[4] = Projection[4];
	GlProjection[5] = Projection[5];
	GlProjection[6] = Projection[6];
	GlProjection[7] = Projection[7];

	GlProjection[8] = Projection[8];
	GlProjection[9] = Projection[9];
	GlProjection[10] = Projection[10];
	GlProjection[11] = Projection[11];

	GlProjection[12] = Projection[12];
	GlProjection[13] = Projection[13];
	GlProjection[14] = Projection[14];
	GlProjection[15] = Projection[15];
	checkGlError("EndOfInit");

	//1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16
	position = 0;
	sine = 0;

}
Engine::~Engine()
{
}

void Engine::Update()
{
}

void Engine::Draw()
{
	position+=0.01f;
	sine+=0.1f;
	checkGlError("draw");

    //Draw
    glClearColor(0,0,1,1);
    #ifdef _WIN32
    glClearDepth(1);
    #else
    glClearDepthf(1);
    #endif

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	
	glEnableVertexAttribArray(Position);    
	glEnableVertexAttribArray(Uv);    
	glUseProgram(shader->Program);

glEnable (GL_BLEND);
glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//first VBO
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);

	glUniform1i(loc, 0);
    glVertexAttribPointer(Position,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),0); 
	glVertexAttribPointer(Uv,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(sizeof(GL_FLOAT)*3)); 
	GlTranslation[3] += position;
	GlTranslation[7] += std::sin(sine*2)*10;
	glUniformMatrix4fv(loc2,1,GL_FALSE,GlProjection);
	glUniformMatrix4fv(loc3,1,GL_FALSE,GlTranslation);
	glBindBuffer(GL_ARRAY_BUFFER,VBO2); 
    glDrawArrays(GL_TRIANGLES,0,num_vertices); 
	checkGlError("draw");
	//2nd VBO
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	
	glUniform1i(loc, 0); 


	
	glUniformMatrix4fv(loc2,1,GL_FALSE,GlProjection);
	glUniformMatrix4fv(loc3,1,GL_FALSE,GlTranslation);
	glVertexAttribPointer(Position,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),0); 
	glVertexAttribPointer(Uv,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(sizeof(GL_FLOAT)*3)); 

	glBindBuffer(GL_ARRAY_BUFFER,VBO); 
    glDrawArrays(GL_TRIANGLES,0,num_vertices);  


    //glBindBuffer(GL_ARRAY_BUFFER,VBO);
    ////int position = glGetAttribLocation(shader->Program,"position");
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GL_FLOAT),0);
    //glUseProgram(shader->Program);
    //glDrawArrays(GL_TRIANGLES,0,num_vertices);
}