#ifndef __MODEL_H
#define __MODEL_H
#include "GameEntity.h"
#include "GLTexture.h"
#include "Mesh.h"

#include <vector>
#include <string>

#include <glew.h>

namespace SDLFramework {

	class Model
		: public GameEntity {
	private:
		Mesh* mMesh;
		ShaderUtil* mShader;

		GLuint vBufferID;
		GLuint iBufferID;
		uint32_t numIndices;

		glm::mat4 positionMatrix;
		glm::mat4 rotationMatrix;
		glm::mat4 scaleMatrix;

	public:
		Model(std::string filename, ShaderUtil& shader);
		~Model();

		virtual void Update() override;
		virtual void Render() override;

	private:
		void CreateVertexBuffer();
		void CreateIndexBuffer();
	};

}
#endif