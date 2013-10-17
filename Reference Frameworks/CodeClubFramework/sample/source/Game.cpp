/**
 * @file Game.cpp
 *
 * OpenGL Framework - Sample
 * 2013
 */

#include <Game.h>

#include <string>

#include <Input.h>
#include <ObjImport.h>
#include <devmath/Quaternion.h>
#include <devmath/Utils.h>
#include <devmath/Vector3.h>

using namespace devmath;
using namespace glframework;
using namespace std;

Game::Game(Window* window, Graphics* graphics)
	: BaseGame(window, graphics),
	  _camera(NULL),
	  _shader(NULL),
	  _mesh(NULL),
	  _rotationAngle(0.0f),
	  _texture(NULL)
{
	initialize();
}

Game::~Game()
{
	delete _mesh;
	delete _shader;
	delete _camera;
}


// Public

void Game::update(const float elapsedTime)
{
	updateInput();


	_rotationAngle += elapsedTime;
	const Quaternion rotation =		Quaternion::createRotationX(-PI / 2.0f) *
									Quaternion::createRotationZ(_rotationAngle) *
									Quaternion::createRotationZ(0);
	_mesh->setRotation(rotation);
}

void Game::render()
{
	_graphics->clear(0.0f, 0.0f, 0.0f, 1.0f);

	_graphics->setShader(_shader);
	_graphics->setViewTransform(_camera->viewTransform());
	_graphics->setProjectionTransform(_camera->projectionTransform());

	_graphics->enableCulling();
	_graphics->enableDepthTesting();

	_mesh->render(_graphics);
	BaseGame::render();
}


// Private

const float Game::SPEED = 10.0f;

void Game::initialize()
{
	_camera = new Camera(_graphics->viewport());
	
	string vertexCode =
		"attribute vec3 fwPosition;														\n"
		"attribute vec2 fwTextureCoord;													\n"

		"uniform mat4 fwWorld;															\n"
		"uniform mat4 fwView;															\n"
		"uniform mat4 fwProjection;														\n"

		"varying vec2 textureCoord;														\n"

		"void main()																	\n"
		"{																				\n"
		"	textureCoord = fwTextureCoord;												\n"
		"	gl_Position = fwProjection * fwView * fwWorld * vec4(fwPosition, 1.0);		\n"
		"}																				\n";

	string fragmentCode =
		"uniform sampler2D fwSampler;													\n"
		"varying vec2 textureCoord;														\n"

		"void main()																	\n"
		"{																				\n"
		"    gl_FragColor = texture2D(fwSampler,textureCoord);							\n"
		"}																				\n";

	_shader = new Shader(vertexCode, fragmentCode);

	ObjImport objImport;
	_mesh = objImport.load("assets/model.obj");
	_mesh->setPosition(Vector3(0.0f, -75.0f, -125.0f));

	_texture = Texture::load("assets/diffuse.tga");
	_texture->bind(_shader);

	//glEnable(GL_CULL_FACE);
}

void Game::updateInput() {}