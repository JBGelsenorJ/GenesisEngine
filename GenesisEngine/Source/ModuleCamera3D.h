#pragma once
#include "Module.h"
#include "Globals.h"
#include "Camera.h"

#include "MathGeoLib/include/MathGeoLib.h"

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(bool start_enabled = true);
	~ModuleCamera3D();

	bool Init();
	bool Start();
	bool LoadConfig(JSON_Object* config) override;
	update_status Update(float dt);
	bool CleanUp();

	//void Look(float3& Position);
	void LookAt(const float3& Spot);
	void Move(const float3& Movement);
	float* GetViewMatrix();

	void Reset();
	void SetBackgroundColor(float r, float g, float b, float w);

public:

	Camera* cam;
	float3 Position;
	float3 Reference;
	Color background;

	float move_speed;
	float drag_speed;
	float zoom_speed;
	float sensitivity;
	float movement;

private:

	mat4x4 ViewMatrix, ViewMatrixInverse;
};