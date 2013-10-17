/**
 * @file BlendState.cpp
 *
 * OpenGL Framework
 * 2013
 */

#include <BlendState.h>

using namespace glframework;

const BlendState BlendState::ALPHA_BLEND = BlendState();

BlendState::BlendState()
	: _sourceColorBlend(BLEND_SRC_ALPHA),
	  _sourceAlphaBlend(BLEND_SRC_ALPHA),
	  _destinationColorBlend(BLEND_INVERSE_SRC_ALPHA),
	  _destinationAlphaBlend(BLEND_INVERSE_SRC_ALPHA),
	  _colorEquation(BLEND_ADD),
	  _alphaEquation(BLEND_ADD) { }

BlendState::BlendState(const BlendState& blendState)
	: _sourceColorBlend(blendState._sourceColorBlend),
	  _sourceAlphaBlend(blendState._sourceAlphaBlend),
	  _destinationColorBlend(blendState._destinationColorBlend),
	  _destinationAlphaBlend(blendState._destinationAlphaBlend),
	  _colorEquation(blendState._colorEquation),
	  _alphaEquation(blendState._alphaEquation) { }

BlendState::~BlendState() { }


// Public

BlendEquation BlendState::alphaEquation() const
{
	return _alphaEquation;
}

void BlendState::setAlphaEquation(const BlendEquation value)
{
	_alphaEquation = value;
}

BlendEquation BlendState::colorEquation() const
{
	return _colorEquation;
}

void BlendState::setColorEquation(const BlendEquation value)
{
	_colorEquation = value;
}

Blend BlendState::destinationAlphaBlend() const
{
	return _destinationAlphaBlend;
}

void BlendState::setDestinationAlphaBlend(const Blend value)
{
	_destinationAlphaBlend = value;
}

Blend BlendState::destinationColorBlend() const
{
	return _destinationColorBlend;
}

void BlendState::setDestinationColorBlend(const Blend value)
{
	_destinationColorBlend = value;
}

Blend BlendState::sourceAlphaBlend() const
{
	return _sourceAlphaBlend;
}

void BlendState::setSourceAlphaBlend(const Blend value)
{
	_sourceAlphaBlend = value;
}

Blend BlendState::sourceColorBlend() const
{
	return _sourceColorBlend;
}

void BlendState::setSourceColorBlend(const Blend value)
{
	_sourceColorBlend = value;
}

// Operators

BlendState& BlendState::operator =(const BlendState& blendState)
{
	if(this != &blendState)
	{
		_sourceColorBlend = blendState._sourceColorBlend;
		_sourceAlphaBlend = blendState._sourceAlphaBlend;
		_destinationColorBlend = blendState._destinationColorBlend;
		_destinationAlphaBlend = blendState._destinationAlphaBlend;
		_colorEquation = blendState._colorEquation;
		_alphaEquation = blendState._alphaEquation;
	}

	return *this;
}