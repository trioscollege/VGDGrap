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

		GLuint vBufferID;
		GLuint iBufferID;
		uint32_t numIndices;

	public:
		Model(std::string filename);
		~Model();

		const GLuint& GetVertexBufferID();
		const GLuint& GetIndexBufferID();
		const uint32_t& GetNumIndices();

		virtual void Render() override;

	private:
		GLuint CreateVertexBuffer();
		GLuint CreateIndexBuffer();
	};

}
#endif