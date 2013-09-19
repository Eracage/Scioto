//#include <Engine.h>
//
//Engine::Engine()
//{
//	testiluku = 5;
//}
//Engine::~Engine()
//{
//
//}
//void Engine::Update()
//{
//
//}
//void Engine::Draw()
//{
//	glClearColor(1.0,0.0,0.0,1.0);
//	glClear(GL_COLOR_BUFFER_BIT);
//}

#include <Engine.h>
#include <stdlib.h>
 
Engine::Engine()
{
 
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
                    //LOGE("Could not compile shader %d:\n%s\n",
                            //shaderType, buf);
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
 
void Engine::Draw()
{
    //Declare gl object "handles"
    GLuint VBO;
    GLuint PS,VS;
    GLuint Program;
     
    //amount of vertices for the object
    unsigned int num_vertices = 6*3;
     
    //The shader code, bad placement, no can do!
    static const char gVertexShader[] = 
    "attribute vec4 vPosition;\n"
    "void main() {\n"
    "  gl_Position = vPosition;\n"
    "}\n";
 
    static const char gFragmentShader[] = 
    "precision mediump float;\n"
    "void main() {\n"
    "  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
    "}\n";
 
    GLfloat* Data = (GLfloat*)malloc(sizeof(GLfloat)*num_vertices);
 
    float v =0.5f;
 
    Data[0] = -v;
    Data[1] = -v;
    Data[2] = 0;
 
    Data[3] = -v;
    Data[4] = v;
    Data[5] = 0;
 
    Data[6] = v;
    Data[7] = -v;
    Data[8] = 0;
 
    Data[9] = -v;
    Data[10] = v;
    Data[11] = 0;
 
    Data[12] = v;
    Data[13] = v;
    Data[14] = 0;
 
    Data[15] = v;
    Data[16] = -v;
    Data[17] = 0;
 
    //compile shader codes
    PS = loadShader(GL_FRAGMENT_SHADER,gFragmentShader);
    VS = loadShader(GL_VERTEX_SHADER,gVertexShader);
 
    //make the shader program;
    Program = glCreateProgram();
 
    //attach shaders to the program
    glAttachShader(Program,VS);
    glAttachShader(Program,PS);
 
    //bind position string to attrib at loc 0
    glBindAttribLocation(Program,0,"position");
 
    //finalize shader
    glLinkProgram(Program);
 
    //create VBO
    glGenBuffers(1,&VBO);
 
 
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
 
    glBufferData(GL_ARRAY_BUFFER,sizeof(Data)*num_vertices,Data,GL_DYNAMIC_DRAW);
 
    //Draw
    glClearColor(0,0,1,1);
    #ifndef ANDROID_FRAMEWORK
    glClearDepth(1);
    #else
    glClearDepthf(1);
    #endif
 
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
     
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    int position = glGetAttribLocation(Program,"position");
    glEnableVertexAttribArray(0);   
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GL_FLOAT),0);
    glUseProgram(Program);
    glDrawArrays(GL_TRIANGLES,0,num_vertices);
     
     
}

