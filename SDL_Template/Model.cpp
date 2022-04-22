#include "Model.h"

SDLFramework::Model::Model(std::string filename) {
	mMesh = AssetManager::Instance()->GetMesh(filename);
}

SDLFramework::Model::~Model()
{
}

void SDLFramework::Model::Render() {
	std::cout << "The mesh has " << std::to_string(mMesh->getVertices().size()) << " vertices and " << std::to_string(mMesh->getIndices().size()) << " indices." << std::endl;
}

