#include "PointLight.h"

namespace uGLy
{

	PointLight::PointLight(glm::vec3 position,
		float kconstant,
		float klinear,
		float kquadratic)
	{
		this->position = position;
		this->kconstant = kconstant;
		this->klinear = klinear;
		this->kquadratic = kquadratic;
	}

}
