#include "Importer.h"

#include "Timer.h"
#include "SDL/include/SDL.h"
#include <fstream>
#include <iostream>
#include <Shlwapi.h>

#include "PhysFS/include/physfs.h"
#include "Assimp/Assimp/include/cimport.h"
#include "Assimp/Assimp/include/scene.h"
#include "Assimp/Assimp/include/postprocess.h"

#include "Devil/include/IL/il.h"
#include "Devil/include/IL/ilu.h"
#include "Devil/include/IL/ilut.h"

#pragma comment (lib, "PhysFS/libx86/physfs.lib")
#pragma comment (lib,"shlwapi.lib")
#pragma comment (lib, "Assimp/Assimp/libx86/assimp.lib")

#pragma comment (lib, "Devil/libx86/DevIL.lib")	
#pragma comment (lib, "Devil/libx86/ILU.lib")	
#pragma comment (lib, "Devil/libx86/ILUT.lib")	



void MeshImporter::Init()
{
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);
}

void MeshImporter::CleanUp()
{
	aiDetachAllLogStreams();
}

void MeshImporter::Import(const aiMesh* mesh, GnMesh* ourMesh) {

	Timer timer;
	timer.Start();

	ourMesh->vertices_amount = mesh->mNumVertices;
	ourMesh->vertices = new float (ourMesh->vertices_amount * 3);
	memcpy(ourMesh->vertices, mesh->mVertices, sizeof(float) * ourMesh->vertices_amount * 3);
	 
	if (mesh->HasFaces())
	{
		ourMesh->indices_amount = mesh->mNumFaces * 3;
		ourMesh->indices = new uint(ourMesh->indices_amount * 3);

		for (size_t i = 0; i < mesh->mNumFaces; i++)
		{
			if (mesh->mFaces[i].mNumIndices != 3)
			{
				LOG_WARNING("WARNING, geometry face with != 3 indices!");
			}
			else
			{
				memcpy(&ourMesh->indices[i * 3], mesh->mFaces[i].mIndices, 3 * sizeof(uint));
			}
		}

	}

	if (mesh->HasNormals())
	{
		ourMesh->normals_amount = mesh->mNumVertices;
		ourMesh->normals = new float(mesh->mNumVertices * 3);

		for (size_t i = 0; i < mesh->mNumFaces; i++)
		{
			ourMesh->normals[i] = mesh->mNormals[i].x;
			ourMesh->normals[i + 1] = mesh->mNormals[i].y;
			ourMesh->normals[i + 2] = mesh->mNormals[i].z;
		}

	}

	ourMesh->texcoords = new float(mesh->mNumVertices * 2);
	for (size_t i = 0; i < mesh->mNumVertices; i+=2)
	{
		ourMesh->texcoords[i] = mesh->mTextureCoords[0][i].x;
		ourMesh->texcoords[i + 1] = mesh->mTextureCoords[0][i].y;
	}

	LOG("Mesh imported in %d ms", timer.Read());
}

uint64 MeshImporter::Save(const GnMesh* ourMesh, char** Buffer) {

	uint ranges[4] = { ourMesh->indices_amount, ourMesh->vertices_amount, ourMesh->normals_amount, ourMesh->texcoords_amount };

	uint size = sizeof(ranges) + sizeof(uint) * ourMesh->indices_amount + sizeof(float) * ourMesh->vertices_amount * 3;

	char* fileBuffer = new char[size]; // Allocate
	char* cursor = fileBuffer;
	
	uint bytes = sizeof(ranges); // First store ranges
	memcpy(cursor, ranges, bytes);
	cursor += bytes;

	// Store indices
	bytes = sizeof(uint) * ourMesh->indices_amount;
	memcpy(cursor, ourMesh->indices, bytes);
	cursor += bytes;

	// Store vertex
	bytes = sizeof(float) * ourMesh->vertices_amount * 3;
	memcpy(cursor, ourMesh->vertices, bytes);
	cursor += bytes;

	// Store normals
	bytes = sizeof(float) * ourMesh->normals_amount * 3;
	memcpy(cursor, ourMesh->normals, bytes);
	cursor += bytes;

	// Store textcoords
	bytes = sizeof(float) * ourMesh->texcoords_amount * 2;
	memcpy(cursor, ourMesh->texcoords, bytes);
	cursor += bytes;

	*Buffer = fileBuffer;
	return size;
}

void  MeshImporter::Load(char* Buffer, GnMesh* ourMesh) {

	Timer timer;
	timer.Start();

	char* cursor = Buffer;

	// amount of indices / vertices / colors / normals / texture_coords
	uint ranges[4];
	uint bytes = sizeof(ranges);
	memcpy(ranges, cursor, bytes);
	cursor += bytes;

	ourMesh->indices_amount = ranges[0];
	ourMesh->vertices_amount = ranges[1];
	ourMesh->normals_amount = ranges[2];
	ourMesh->texcoords_amount = ranges[3];

	// Load indices
	bytes = sizeof(uint) * ourMesh->indices_amount;
	ourMesh->indices = new uint[ourMesh->indices_amount];
	memcpy(ourMesh->indices, cursor, bytes);
	cursor += bytes;

	// Load indices
	bytes = sizeof(float) * ourMesh->vertices_amount * 3;
	ourMesh->vertices = new float[ourMesh->vertices_amount * 3];
	memcpy(ourMesh->vertices, cursor, bytes);
	cursor += bytes;

	// Load normals
	bytes = sizeof(float) * ourMesh->normals_amount * 3;
	ourMesh->normals = new float[ourMesh->normals_amount * 3];
	memcpy(ourMesh->normals, cursor, bytes);
	cursor += bytes;

	// Load textcoords
	bytes = sizeof(float) * ourMesh->texcoords_amount * 3;
	ourMesh->texcoords = new float[ourMesh->texcoords_amount * 3];
	memcpy(ourMesh->texcoords, cursor, bytes);
	cursor += bytes;

	ourMesh->GenerateBuffers();

	LOG(" mesh loaded in %d ms", timer.Read());
}


void TextureImporter::Init()
{
	ilInit();
	iluInit();

	if (ilutRenderer(ILUT_OPENGL))
		LOG("DevIL initted correctly");;
}


void TextureImporter::Import(const char* path) {

	Timer timer;
	timer.Start();

	
	
}

//uint64 TextureImporter::Save(char** fileBuffer) {
//
//}

void TextureImporter::Load(const char* fileBuffer, Material* ourTexture) {


}