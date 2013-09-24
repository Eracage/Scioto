/**
 * @file BlendState.h
 *
 * OpenGL Framework
 * 2013
 */

#ifndef BLENDSTATE
#define BLENDSTATE

#include <GL/glew.h>

namespace glframework
{
	enum Blend
	{
		BLEND_ZERO					 = GL_ZERO,
		BLEND_ONE					 = GL_ONE,
		BLEND_SRC_COLOR				 = GL_SRC_COLOR,
		BLEND_INVERSE_SRC_COLOR		 = GL_ONE_MINUS_SRC_COLOR,
		BLEND_SRC_ALPHA				 = GL_SRC_ALPHA,
		BLEND_INVERSE_SRC_ALPHA		 = GL_ONE_MINUS_SRC_ALPHA,
		BLEND_DEST_COLOR			 = GL_DST_COLOR,
		BLEND_INVERSE_DEST_COLOR	 = GL_ONE_MINUS_DST_COLOR,
		BLEND_DEST_ALPHA			 = GL_DST_ALPHA,
		BLEND_INVERSE_DEST_ALPHA	 = GL_ONE_MINUS_DST_ALPHA,
		BLEND_CONSTANT_COLOR		 = GL_CONSTANT_COLOR,
		BLEND_INVERSE_CONSTANT_COLOR = GL_ONE_MINUS_CONSTANT_COLOR,
		BLEND_CONSTANT_ALPHA		 = GL_CONSTANT_ALPHA,
		BLEND_INVERSE_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA,
		BLEND_SRC_ALPHA_SATURATE	 = GL_SRC_ALPHA_SATURATE
	};

	enum BlendEquation
	{
		BLEND_ADD			   = GL_FUNC_ADD,
		BLEND_SUBTRACT		   = GL_FUNC_SUBTRACT,
		BLEND_REVERSE_SUBTRACT = GL_FUNC_REVERSE_SUBTRACT
	};

	class BlendState
	{
	public:
			
			static const BlendState ALPHA_BLEND;
			
			BlendState();

			BlendState(const BlendState& blendState);

			~BlendState();

			BlendEquation alphaEquation() const;

			void setAlphaEquation(const BlendEquation value);

			BlendEquation colorEquation() const;

			void setColorEquation(const BlendEquation value);

			Blend destinationAlphaBlend() const;

			void setDestinationAlphaBlend(const Blend value);

			Blend destinationColorBlend() const;

			void setDestinationColorBlend(const Blend value);

			Blend sourceAlphaBlend() const;

			void setSourceAlphaBlend(const Blend value);

			Blend sourceColorBlend() const;

			void setSourceColorBlend(const Blend value);

			BlendState& operator =(const BlendState& blendState);

	private:

		Blend _sourceColorBlend;
		Blend _sourceAlphaBlend;
		Blend _destinationColorBlend;
		Blend _destinationAlphaBlend;

		BlendEquation _colorEquation;
		BlendEquation _alphaEquation;
	};
}

#endif