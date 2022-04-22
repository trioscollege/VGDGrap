#include "Graphics.h"
#include "Camera.h"

#include <gtx/transform.hpp>

namespace SDLFramework {
	Camera::Camera(const float& width, const float& height) 
		: position(0.0f, 0.0f, 1.0f),
			target(0.0f, 0.0f, 0.0f),
			up(0.0f, 1.0f, 0.0f){
		CreateProjectionMatrix(width, height);
		CreateViewMatrix();
	}

	void Camera::Update() {
		CreateViewMatrix();
	}

	const glm::mat4& Camera::GetProjectionMatrix() {
		return projMatrix;
	}

	const glm::mat4& Camera::GetViewMatrix() {
		return viewMatrix;
	}
	
	void SDLFramework::Camera::CreateProjectionMatrix(const float& width, const float& height) {
		projMatrix = glm::perspective(glm::radians(60.0f), width / height, 0.01f, 1000.0f);
	}

	void Camera::CreateViewMatrix() {
		viewMatrix = glm::lookAt(position, target, up);
	}
}