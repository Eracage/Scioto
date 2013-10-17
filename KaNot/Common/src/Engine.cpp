#include <Engine.h>
#include <stdlib.h>

using namespace Scioto;

Engine::Engine()
{
	const char gVertexShader[] = 
    "attribute vec4 vPosition;\n"
    "void main() {\n"
    "  gl_Position = vPosition;\n"
    "}\n";

	const char gFragmentShader[] = 
    "precision mediump float;\n"
    "void main() {\n"
    "  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
    "}\n";

	shader = new Shader(gVertexShader,gFragmentShader);




	////////////////////////////////////////////////////TEMP
	
    num_vertices = 6*3;

    Data = (GLfloat*)malloc(sizeof(GLfloat)*num_vertices);

	float v = 0.5f;

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

	
    //create VBO
    glGenBuffers(1,&VBO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glBufferData(GL_ARRAY_BUFFER,sizeof(Data)*num_vertices,Data,GL_DYNAMIC_DRAW);

}
Engine::~Engine()
{
}
void Engine::Update()
{
}

void Engine::Draw()
{
    //Draw
    glClearColor(0,0,1,1);
    #ifdef _WIN32
    glClearDepth(1);
    #else
    glClearDepthf(1);
    #endif

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    //int position = glGetAttribLocation(shader->Program,"position");
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GL_FLOAT),0);
    glUseProgram(shader->Program);
    glDrawArrays(GL_TRIANGLES,0,num_vertices);
}