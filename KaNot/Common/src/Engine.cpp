#include <Engine.h>
#include <stdlib.h>

using namespace Scioto;

Engine::Engine(float ContextWidht, float ContextHeight)
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
	viewport = new Viewport(800,800,ContextWidht, ContextHeight);
	




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



	////////////////////////texturestuff




	GLubyte* pixels = Scioto::FileReader::loadTGA("Test.tga",header);

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



	////////////////////matrixes

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
	checkGlError("EndOfInit");

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

	
	glEnableVertexAttribArray(shader->Position);    
	glEnableVertexAttribArray(shader->Uv);    
	glUseProgram(shader->Program);

glEnable (GL_BLEND);
glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//first VBO
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);

	glUniform1i(shader->loc, 0);
    glVertexAttribPointer(shader->Position,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),0); 
	glVertexAttribPointer(shader->Uv,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(sizeof(GL_FLOAT)*3)); 
	GlTranslation[3] += position;
	GlTranslation[7] += std::sin(sine*2)*10;
	glUniformMatrix4fv(shader->loc2,1,GL_FALSE,viewport->m_projection);
	glUniformMatrix4fv(shader->loc3,1,GL_FALSE,GlTranslation);
	glBindBuffer(GL_ARRAY_BUFFER,VBO2); 
    glDrawArrays(GL_TRIANGLES,0,num_vertices); 
	checkGlError("draw");
	//2nd VBO
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	
	glUniform1i(shader->loc, 0); 


	
	glUniformMatrix4fv(shader->loc2,1,GL_FALSE,viewport->m_projection);
	glUniformMatrix4fv(shader->loc3,1,GL_FALSE,GlTranslation);
	glVertexAttribPointer(shader->Position,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),0); 
	glVertexAttribPointer(shader->Uv,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(sizeof(GL_FLOAT)*3)); 

	glBindBuffer(GL_ARRAY_BUFFER,VBO); 
    glDrawArrays(GL_TRIANGLES,0,num_vertices);  
}