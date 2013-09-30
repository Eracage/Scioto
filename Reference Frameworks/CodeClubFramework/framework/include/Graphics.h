/**
 * @file Graphics.h
 *
 * OpenGL Framework
 * 2013
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <devmath/Matrix4.h>
#include <devmath/Rectangle.h>

#include <BlendState.h>
#include <IndexBuffer.h>
#include <Shader.h>
#include <VertexBuffer.h>
#include <Window.h>

namespace glframework
{
	class Graphics
	{
	public:

		Graphics(const Window* window);

		~Graphics();

		void setIndexBuffer(IndexBuffer* value);

		void setProjectionTransform(const devmath::Matrix4& value);

		void setShader(Shader* value);

		void setVertexBuffer(VertexBuffer* value);

		devmath::Rectangle viewport() const;

		void setViewTransform(const devmath::Matrix4& value);

		void setWorldTransform(const devmath::Matrix4& value);

		void clear(const float red, const float green, const float blue, const float alpha) const;

		void enableBlending(const BlendState& blendState);

		void enableCulling() const;

		void enableDepthTesting() const;

		void render() const;

	private:

		devmath::Rectangle _viewport;

		Shader* _shader;
		VertexBuffer* _vertexBuffer;
		IndexBuffer* _indexBuffer;

		devmath::Matrix4 _worldTransform;
		devmath::Matrix4 _viewTransform;
		devmath::Matrix4 _projectionTransform;

		Graphics(const Graphics& graphics);

		void initializeViewport() const;
		void renderIndices() const;
	};
}

#endif