#include "Camera.h"


namespace uGLy
{

	Camera::Camera()
	{
		glm::vec3 position(0.0f, 0.0f, 1.0f);

		initialize(position);
	}


	Camera::Camera(glm::vec3 & _position, glm::vec3 & _forward)
	{
		initialize(_position, _forward);
	}


	Camera::Camera(glm::vec3 & _position, glm::vec3 & _forward, glm::vec3 & _up, glm::vec3 & _right)
	{
		initialize(_position, _forward, _up, _right);
	}


	void Camera::initialize(glm::vec3 & _position)
	{
		glm::vec3 forward = glm::normalize(position);
		initialize(_position, forward);
	}

	void Camera::initialize(glm::vec3 & _position, glm::vec3 & _forward)
	{
		glm::vec3 right = glm::normalize(glm::cross(globalUp, _forward));
		glm::vec3 up = glm::normalize(glm::cross(_forward, right));
		initialize(_position, _forward, up, right);
	}


	void Camera::initialize(glm::vec3 & _position, glm::vec3 & _forward, glm::vec3 & _up, glm::vec3 & _right)
	{
		position = _position;
		defaultPosition = position;

		forward = glm::normalize(_forward);
		defaultForward = forward;

		up = glm::normalize(_up);
		defaultUp = up;

		right = glm::normalize(_right);
		defaultRight = right;

		refreshViewMatrix();
	}


	Camera::~Camera()
	{
	}


	void Camera::refreshViewMatrix()
	{
		viewMatrix = glm::mat4(
			glm::vec4(right.x, up.x, forward.x, 0.0f),
			glm::vec4(right.y, up.y, forward.y, 0.0f),
			glm::vec4(right.z, up.z, forward.z, 0.0f),
			glm::vec4(-glm::dot(right, position), -glm::dot(up, position), -glm::dot(forward, position), 1.0f));
	}

	void Camera::reset()
	{
		position = defaultPosition;
		forward = defaultForward;
		up = defaultUp;
		right = defaultRight;

		pitch = 0.0f;
		yaw = 0.0f;
		calculateVectors();
	}


	const glm::vec3& Camera::getGlobalUp()
	{
		return globalUp;
	}


	const glm::mat4& Camera::getViewMatrix()
	{
		return viewMatrix;
	}


	void Camera::setViewMatrix(const glm::mat4& matrix)
	{
		viewMatrix = matrix;
	}


	void Camera::deactivate()
	{
		active = false;
	}

}