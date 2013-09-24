/**
 * @file Graphics.cpp
 *
 * OpenGL Framework
 * 2013
 */

#include <Graphics.h>
#include <GL/glew.h>

#include <Debug.h>

using namespace devmath;
using namespace glframework;
using namespace std;

Graphics::Graphics(const Window* window)
	: _viewport(0, 0, window->width(), window->height()),
	  _shader(NULL),
	  _vertexBuffer(NULL),
	  _indexBuffer(NULL),
	  _worldTransform(Matrix4::identity()),
	  _viewTransform(Matrix4::identity()),
	  _projectionTransform(Matrix4::identity())
{
	initializeViewport();
}

Graphics::~Graphics() { }


// Public


void Graphics::setIndexBuffer(IndexBuffer* value)
{
	_indexBuffer = value;
}

void Graphics::setProjectionTransform(const devmath::Matrix4& value)
{
	_projectionTransform = value;
}

void Graphics::setShader(Shader* value)
{
	_shader = value;
}

void Graphics::setVertexBuffer(VertexBuffer* value)
{
	_vertexBuffer = value;
}

devmath::Rectangle Graphics::viewport() const
{
	return _viewport;
}

void Graphics::setViewTransform(const devmath::Matrix4& value)
{
	_viewTransform = value;
}

void Graphics::setWorldTransform(const devmath::Matrix4& value)
{
	_worldTransform = value;
}

void Graphics::clear(const float red, const float green, const float blue, const float alpha) const
{
	glClearColor(red, green, blue, alpha);
	checkGLErrors();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	checkGLErrors();
}

void Graphics::enableBlending(const BlendState& blendState)
{
	glEnable(GL_BLEND);
	checkGLErrors();
	glBlendEquationSeparate(blendState.colorEquation(), blendState.alphaEquation());
	checkGLErrors();

	glBlendFuncSeparate(blendState.sourceColorBlend(), blendState.destinationColorBlend(),
		 blendState.sourceAlphaBlend(), blendState.destinationAlphaBlend());
	checkGLErrors();
}

void Graphics::enableCulling() const
{
	glEnable(GL_CULL_FACE);
}

void Graphics::enableDepthTesting() const
{
	glEnable(GL_DEPTH_TEST);
}

void Graphics::render() const
{
	_shader->use();

	_shader->setUniform("fwWorld", _worldTransform);
	_shader->setUniform("fwView", _viewTransform);
	_shader->setUniform("fwProjection", _projectionTransform);

	_vertexBuffer->setVertexArrays(_shader);
	renderIndices();
	
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
}


// Private

void Graphics::initializeViewport() const
{
	glViewport(_viewport.x, _viewport.y, _viewport.width, _viewport.height);
}

void Graphics::renderIndices() const
{
	const vector<INDEX>& indices = _indexBuffer->indices();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices.front());
	checkGLErrors();
}