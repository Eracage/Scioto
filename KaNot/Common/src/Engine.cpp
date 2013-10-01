#include <Engine.h>
#include <stdlib.h>

using namespace Scioto;

Engine::Engine()
{
	shader = new Shader();
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

    glBindBuffer(GL_ARRAY_BUFFER,shader->VBO);
    int position = glGetAttribLocation(shader->Program,"position");
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GL_FLOAT),0);
    glUseProgram(shader->Program);
    glDrawArrays(GL_TRIANGLES,0,shader->num_vertices);
}