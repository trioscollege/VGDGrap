#ifndef __MESH_H
#define __MESH_H
#include "MathHelper.h"
#include "tiny_obj_loader.h"

#include <vector>

namespace SDLFramework {
	struct Mesh {
		Mesh(const std::vector<Vertex3D>& vertices, const std::vector<uint32_t>& indices);

		const std::vector<Vertex3D>& getVertices() const;
		const std::vector<uint32_t>& getIndices() const;
	private:
		const std::vector<Vertex3D> vertices;
		const std::vector<uint32_t> indices;

	};
}
#endif