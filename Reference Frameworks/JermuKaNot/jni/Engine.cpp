#include <Engine.h> 
#include <stdlib.h> 
#include <FileReader.h>
#include <cmath>

#undef isnan
Engine::Engine() 
{ 
  Scale = blackBarH = blackBarV = 0;
} 
  
Engine::~Engine() 
{ 
  
} 
  
void Engine::Update() 
{ 
  
} 
  
GLuint loadShader(GLenum shaderType, const char* pSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    #ifndef WINDOWS_FRAMEWORK
                    LOGE("Could not compile shader %d:\n%s\n",
                            shaderType, buf);
                    #else
 
                    #endif
                     
                         
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
} 

void Engine::fixAspectRatio(float desiredWidth,float desiredHeight,float width,float height)
{
	//Calculate desired Aspect Ratio
	float dAR =  desiredWidth/ desiredHeight;

	//Calculate real Aspect Ratio
	float rAR = width/height;
	float w,h;
	//Check Aspect Ratio's
	if(dAR==rAR)
	{
		//Same aspect, no letterboxing needed!
		Scale = width/desiredWidth;
	}
	else if(dAR<rAR)
	{
		//Horizontal letterboxing needed!
		Scale = height/desiredHeight;
		blackBarH = (width-Scale*desiredWidth)/2;
		
	}
	else
	{
		//Vertical letterboxing needed!
		Scale = width/desiredWidth;
		blackBarV = (height-(Scale*desiredHeight))/2;
	}
	 w = desiredWidth*Scale;
	 h = desiredHeight*Scale;

	glViewport((int)blackBarH, (int)blackBarV,(int)w,(int)h); // Sets up the OpenGL viewport

    //amount of vertices for the object
    num_vertices = 6*5;
     //write a parser for these and store as text files!
    static const char gVertexShader[] = 
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
 
    static const char gFragmentShader[] = 
	"precision mediump float;\n"
	"varying vec2 Uv;\n"
	"uniform sampler2D s_texture;\n"
    "void main() {\n"
    "  gl_FragColor = texture2D(s_texture,Uv);\n"
    "}\n"; 
  
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


  
    //compile shader codes 
    PS = loadShader(GL_FRAGMENT_SHADER,gFragmentShader); 
    VS = loadShader(GL_VERTEX_SHADER,gVertexShader); 
  
    //make the shader program; 
    Program = glCreateProgram(); 
  
    //attach shaders to the program 
    glAttachShader(Program,VS); 
    glAttachShader(Program,PS); 
  
    //bind position string to attrib at loc 0 
    glBindAttribLocation(Program,0,"vPosition"); 
	//bind Color string to attrib at loc 1 
	glBindAttribLocation(Program,1,"vUv"); 
  
    //finalize shader 
    glLinkProgram(Program); 
  
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

	Position = glGetAttribLocation(Program,"vPosition");
	Uv = glGetAttribLocation(Program,"vUv");
	loc = glGetUniformLocation(Program, "s_texture");
	loc2 = glGetUniformLocation(Program, "Projection");
	loc3 = glGetUniformLocation(Program, "Translation");

	GLubyte* pixels;
	
	FileReader *FR = new FileReader("Test.tga");
	
	unsigned char*buffer = (unsigned char*)malloc(sizeof(unsigned char)*4);
	//move to position 12, next 4 bytes are size
	//
	FR->FileSeek(12,0);
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
	delete FR;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1,&Texture);
	glActiveTexture(GL_TEXTURE0);
		
    // Bind the texture object
    glBindTexture(GL_TEXTURE_2D, Texture);

    // Load the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sizex, sizey, 0, GL_RGBA,
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

	//1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16
	position = 0;
	sine = 0;

 }

void Engine::Draw() 
{ 
	position+=0.01f;
	sine+=0.1f;

    //Draw 
    glClearColor(0,0,1,1); 
    #ifndef ANDROID_FRAMEWORK 
    glClearDepth(1); 
    #else 
    glClearDepthf(1); 
    #endif 
  
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 
    
	glEnableVertexAttribArray(Position);    
	glEnableVertexAttribArray(Uv);    
	glUseProgram(Program);

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
}