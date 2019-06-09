#include "Light.h"


namespace uGLy
{

	Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, bool isOn)
	{
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->isOn = isOn;
	}

	void Light::turnOn()
	{
		isOn = true;
	}

	void Light::turnOff()
	{
		isOn = false;
	}

}