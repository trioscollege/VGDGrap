#include "Model.h"

#include <glm.hpp>

SDLFramework::Model::Model(std::string filename) {
	mMesh = AssetManager::Instance()->GetMesh(filename);
	vBufferID = CreateVertexBuffer();
	iBufferID = CreateIndexBuffer();
	numIndices = static_cast<uint32_t>(mMesh->getIndices().size());
}

SDLFramework::Model::~Model() {
	AssetManager::Instance()->DestroyMesh(mMesh);
	mMesh = nullptr;

	glDeleteBuffers(1, &vBufferID);
	glDeleteBuffers(1, &iBufferID);
}

const GLuint& SDLFramework::Model::GetVertexBufferID() {
	return vBufferID;
}

const GLuint& SDLFramework::Model::GetIndexBufferID() {
	return iBufferID;
}

const uint32_t& SDLFramework::Model::GetNumIndices() {
	return numIndices;
}

void SDLFramework::Model::Render() {
	std::cout << "The mesh has " << std::to_string(mMesh->getVertices().size()) << " vertices and " << std::to_string(mMesh->getIndices().size()) << " indices." << std::endl;
}

GLuint SDLFramework::Model::CreateVertexBuffer() {
	std::vector<glm::vec3> positions;

	for (const auto& vertex : mMesh->getVertices()) {
		positions.push_back(vertex.position);
	}

	GLuint id;
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return id;
}

GLuint SDLFramework::Model::CreateIndexBuffer() {
	GLuint id;
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mMesh->getIndices().size() * sizeof(uint32_t), mMesh->getIndices().data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return id;
}

