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







//
//
//void Engine::Draw()
//{
//	glClearColor(1.0,0.0,0.0,1.0);
//	glClear(GL_COLOR_BUFFER_BIT);
//}
//
//void Engine::printGLString(const char *name, GLenum s) {
//    const char *v = (const char *) glGetString(s);
//    LOGI("GL %s = %s\n", name, v);
//}
//
//void Engine::checkGlError(const char* op) {
//    for (GLint error = glGetError(); error; error
//            = glGetError()) {
//        LOGI("after %s() glError (0x%x)\n", op, error);
//    }
//}
//
//static const char gVertexShader[] = 
//    "attribute vec4 vPosition;\n"
//    "void main() {\n"
//    "  gl_Position = vPosition;\n"
//    "}\n";
//
//static const char gFragmentShader[] = 
//    "precision mediump float;\n"
//    "void main() {\n"
//    "  gl_FragColor = vec4(1.0, 0.0, 0.0, 0.1);\n"
//    "}\n";

//
//GLuint createProgram(const char* pVertexSource, const char* pFragmentSource) {
//    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
//    if (!vertexShader) {
//        return 0;
//    }
//
//    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
//    if (!pixelShader) {
//        return 0;
//    }
//
//    GLuint program = glCreateProgram();
//    if (program) {
//        glAttachShader(program, vertexShader);
//        checkGlError("glAttachShader");
//        glAttachShader(program, pixelShader);
//        checkGlError("glAttachShader");
//        glLinkProgram(program);
//        GLint linkStatus = GL_FALSE;
//        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
//        if (linkStatus != GL_TRUE) {
//            GLint bufLength = 0;
//            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
//            if (bufLength) {
//                char* buf = (char*) malloc(bufLength);
//                if (buf) {
//                    glGetProgramInfoLog(program, bufLength, NULL, buf);
//                    LOGE("Could not link program:\n%s\n", buf);
//                    free(buf);
//                }
//            }
//            glDeleteProgram(program);
//            program = 0;
//        }
//    }
//    return program;
//}