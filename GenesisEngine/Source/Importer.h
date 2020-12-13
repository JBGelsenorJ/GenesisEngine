#include "Globals.h"
#include "Application.h"
#include "Material.h"
#include "Mesh.h"


struct aiMaterial;
struct aiScene;
struct aiNode;
struct aiMesh;


namespace MeshImporter {
	void Init();
	void CleanUp();

	void Import(const aiMesh* mesh, GnMesh* ourMesh);
	uint64 Save(const GnMesh* ourMesh, char** Buffer);
	void Load(char* Buffer, GnMesh* ourMesh);

};

namespace TextureImporter {

	void Init();

	void Import(const char* path);
	uint64 Save(char** fileBuffer);
	void Load(const char* fileBuffer, Material* ourTexture);
}; 

//namespace ModelImporter {
//
//
//
//};