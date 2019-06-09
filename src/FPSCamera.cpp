#include "FPSCamera.h"


namespace uGLy
{

	void FPSCamera::calculateVectors()
	{
		float cosPitch = glm::cos(glm::radians(pitch));
		float sinPitch = glm::sin(glm::radians(pitch));
		float cosYaw = glm::cos(glm::radians(yaw));
		float sinYaw = glm::sin(glm::radians(yaw));

		right = glm::vec3(cosYaw, 0.0f, -sinYaw);
		up = glm::vec3(sinYaw * sinPitch, cosPitch, cosYaw * sinPitch);
		forward = glm::vec3(sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw);

		refreshViewMatrix();
	}


	void FPSCamera::processMousePosition(float xpos, float ypos)
	{
		if (firstMovement)
		{
			lastX = xpos;
			lastY = ypos;
			firstMovement = false;
		}

		currentX = xpos;
		currentY = ypos;
		float offsetX = lastX - currentX;
		float offsetY = lastY - currentX;

		yaw += (sensitivity * offsetX);
		pitch += (sensitivity * offsetY);

		if (pitch > 90.0f)
		{
			pitch = 90.0f;
		}
		else if (pitch < -90.0f)
		{
			pitch = -90.0f;
		}

		yaw = fmod(yaw, 360.0f);

		lastX = currentX;
		lastY = currentY;

		calculateVectors();
	}


	void FPSCamera::activate(float xpos, float ypos)
	{
		active = true;
	}

}