#include "ArcballCamera.h"


namespace uGLy
{

	void ArcballCamera::calculateVectors()
	{
		position = glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(pitch), right)
			* glm::rotate(glm::mat4(1.0f), glm::radians(yaw), up)
			* glm::vec4(position, 1.0f));
		forward = glm::normalize(position);
		right = glm::normalize(glm::cross(getGlobalUp(), forward));
		up = glm::cross(forward, right);
		refreshViewMatrix();
	}


	void ArcballCamera::processMousePosition(float xpos, float ypos)
	{
		currentX = xpos;
		currentY = ypos;
		if (currentX != lastX || currentY != lastY) {
			glm::vec3 va = getArcballVector(lastX, lastY);
			glm::vec3 vb = getArcballVector(currentX, currentY);

			glm::quat q = glm::quat(vb, va);
			yaw = glm::degrees(glm::yaw(q));
			pitch = glm::degrees(glm::pitch(q));

			if (pitch > 89.0f)
			{
				pitch = 89.0f;
			}
			else if (pitch < -89.0f)
			{
				pitch = -89.0f;
			}

			yaw = fmod(yaw, 360.0f);
			lastX = currentX;
			lastY = currentY;
			calculateVectors();
		}
	}

	void ArcballCamera::activate(float xpos, float ypos)
	{
		currentX = xpos;
		lastX = xpos;
		currentY = ypos;
		lastY = ypos;
		active = true;
	}


	const glm::vec3 ArcballCamera::getArcballVector(float x, float y)
	{
		glm::vec3 P = glm::vec3((x / windowWidth) * 2 - 1.0,
			(y / windowHeight) * 2 - 1.0,
			0);

		P.y = -P.y;
		float OP_squared = P.x * P.x + P.y * P.y;
		if (OP_squared <= 1.0f)
			P.z = glm::sqrt(1.0f - OP_squared);
		else
			P = glm::normalize(P);
		return P;
	}

}