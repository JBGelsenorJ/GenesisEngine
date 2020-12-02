#pragma once
#include "Component.h"
#include "Globals.h"
#include "MathGeoLib/include/Geometry/Frustum.h"

#include <string>

class GameObject;

class Camera : public Component {
public:
	Camera();
	~Camera();

	virtual void Update() override;
	virtual void OnEditor() override;

	void DrawCameraBox();

	float GetAspectRatio();
	float* GetViewMatrix();
	
public:

	Frustum frustum;
	float3 reference;
	float3 camera_corners[8];

};
