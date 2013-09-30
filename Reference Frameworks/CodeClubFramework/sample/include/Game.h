/**
 * @file Game.h
 *
 * OpenGL Framework - Sample
 * 2013
 */

#ifndef GAME_H
#define GAME_H

#include <BaseGame.h>
#include <Camera.h>
#include <KeyboardState.h>
#include <Mesh.h>
#include <Shader.h>
#include <Texture.h>

class Game : public glframework::BaseGame
{
public:
	
	Game(glframework::Window* window, glframework::Graphics* graphics);

	~Game();

	void update(const float elapsedTime);

	void render();

private:

	devmath::Quaternion _cameraRotation;
	devmath::Vector3 _cameraPosition;

	static const float SPEED;

	glframework::Camera* _camera;
	glframework::Shader* _shader;

	glframework::Mesh* _mesh;
	glframework::Texture* _texture;

	glframework::KeyboardState _keyboard;

	float _rotationAngle;

	Game(const Game& game);

	void initialize();
	void updateInput();
};

#endif