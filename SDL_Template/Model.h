#ifndef __MODEL_H
#define __MODEL_H
#include "GameEntity.h"
#include "GLTexture.h"
#include "Mesh.h"

#include <vector>
#include <string>

#include <glm.hpp>

namespace SDLFramework {

	class Model
		: public GameEntity {
	public:
		

	private:
		Mesh* mMesh;
		std::vector<GLTexture*> mTextures;

	public:
		Model(std::string filename);
		~Model();

		virtual void Render() override;
	};

}
#endif