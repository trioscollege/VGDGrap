#ifndef __CAMERA_H
#define __CAMERA_H

#include <glm.hpp>

namespace SDLFramework {

	class Camera {
	public:
		glm::vec3 position;
		glm::vec3 target;
		glm::vec3 up;
	
	private:
		glm::mat4 projMatrix;
		glm::mat4 viewMatrix;

	public:
		Camera(const float& width, const float& height);

		void Update();

		const glm::mat4& GetProjectionMatrix();
		const glm::mat4& GetViewMatrix();

	private:
		void CreateProjectionMatrix(const float& width, const float& height);
		void CreateViewMatrix();
	};
}
#endif