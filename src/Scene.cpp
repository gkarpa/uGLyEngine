#include "Scene.h"

namespace uGLy
{

	Scene::Scene(int width, int height, float fovy, float zNear, float zFar)
	{
		windowWidth = width;
		windowHeight = height;
		defaultFovy = fovy;
		this->fovy = fovy;
		this->zNear = zNear;
		this->zFar = zFar;
		updateProjectionMatrix();
	}

	Scene::~Scene()
	{
	}

	void Scene::addCamera(Camera *camera)
	{
		this->camera = camera;
		this->camera->windowWidth = this->windowWidth;
		this->camera->windowHeight = this->windowHeight;
	}

	
	const glm::mat4 & Scene::getProjectionMatrix()
	{
		return this->projectionMatrix;
	}

	void Scene::updateProjectionMatrix()
	{
		projectionMatrix = glm::perspective(glm::radians(fovy), static_cast<float>(windowWidth) / windowHeight, zNear, zFar);
	}

	void Scene::updateFovY(float fovy)
	{
		if (fovy > 100.0f)
		{
			fovy = 100.0f;
		}
		else if (fovy < 10.0f)
		{
			fovy = 10.0f;
		}

		this->fovy = fovy;
		updateProjectionMatrix();
	}

	
	void Scene::resize(int newWidth, int newHeight)
	{
		windowWidth = newWidth;
		windowHeight = newHeight;
		camera->windowWidth = windowWidth;
		camera->windowHeight = windowHeight;
		glViewport(0, 0, windowWidth, windowHeight);
		updateProjectionMatrix();
	}

	void Scene::reset()
	{
		this->camera->reset();
		fovy = defaultFovy;
		this->updateProjectionMatrix();
	}

	void Scene::clear()
	{
		this->reset();
		this->textureManager.Clear();
		this->meshes.clear();
	}

}