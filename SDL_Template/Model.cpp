#include "Model.h"
#include "GLGraphics.h"

#include <glew.h>
#include <glm.hpp>
#include <gtx/transform.hpp>

namespace SDLFramework {

	Model::Model(std::string filename, ShaderUtil& shader)
		: mShader(&shader) {
		mMesh = AssetManager::Instance()->GetMesh(filename);
		CreateVertexBuffer();
		CreateIndexBuffer();
		numIndices = static_cast<uint32_t>(mMesh->getIndices().size());

		Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);
		Rotate(90.0f);
	}

	Model::~Model() {
		AssetManager::Instance()->DestroyMesh(mMesh);
		mMesh = nullptr;

		glDeleteBuffers(1, &vBufferID);
		glDeleteBuffers(1, &iBufferID);
	}

	void Model::Update() {
		Vector2 pos = Position(World);
		float rad = Rotation(World) * DEG_TO_RAD;
		Vector2 scale = Scale(World);

		positionMatrix = glm::translate(glm::vec3(pos.x, pos.y, -790.0f));
		rotationMatrix = glm::rotate(rad, glm::vec3(1.0f, 0.0f, 0.0f));
		scaleMatrix = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));
	}

	void Model::Render() {
		mShader->Use();

		glm::mat4 transform = positionMatrix * rotationMatrix * scaleMatrix;
		glm::mat4 mvp = GLGraphics::sMainCamera->GetProjectionMatrix() * GLGraphics::sMainCamera->GetViewMatrix() * transform;

		mShader->SetMatrix4f("mvp", mvp);

		glBindBuffer(GL_ARRAY_BUFFER, vBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBufferID);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);

		glDisableVertexAttribArray(0);
	}

	void Model::CreateVertexBuffer() {
		std::vector<glm::vec3> positions;

		for (const auto& vertex : mMesh->getVertices()) {
			positions.push_back(vertex.position);
		}

		glGenBuffers(1, &vBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, vBufferID);
		glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_STATIC_DRAW);
	}

	void Model::CreateIndexBuffer() {
		glGenBuffers(1, &iBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mMesh->getIndices().size() * sizeof(uint32_t), mMesh->getIndices().data(), GL_STATIC_DRAW);
	}
}