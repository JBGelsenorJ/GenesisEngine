#include "Camera.h"
#include "Globals.h"
#include "Transform.h"
#include "GameObject.h"
#include "MathGeoLib/include/Geometry/Frustum.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include "ImGui/imgui.h"

#include "glew/include/glew.h"

Camera::Camera() :Component(){

	type = ComponentType::CAMERA;

	frustum.type = PerspectiveFrustum;

	frustum.front = float3::unitZ;
	frustum.up = float3::unitY;

	frustum.pos = float3(0.0f, 0.0f, -5.0f);

	frustum.farPlaneDistance = 50.0f;
	frustum.nearPlaneDistance = 1.0f;

	frustum.verticalFov = DegToRad(90.0f);
	frustum.horizontalFov = DegToRad(90.0f);
}

Camera::~Camera(){

}

void Camera::Update() {

	DrawCameraBox();

}

void Camera::OnEditor() {

	if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
	{
		float position4f[4] = { frustum.pos.x, frustum.pos.y, frustum.pos.z, 1.0f };
		if (ImGui::DragFloat3("Position", position4f, 0.1f, -10000.0f, 10000.0f))
		{
			frustum.pos.x = position4f[0];
			frustum.pos.y = position4f[1];
			frustum.pos.z = position4f[2];
		}

		ImGui::SliderFloat("Near Plane", &frustum.nearPlaneDistance, 0, 50);
		ImGui::SliderFloat("Far Plane", &frustum.farPlaneDistance, 50, 200);

		ImGui::SliderFloat("Vertical FOV", &frustum.verticalFov, 0, 5);
		ImGui::SliderFloat("Horizontal FOV", &frustum.horizontalFov, 0, 5);
	}

}

void Camera::DrawCameraBox()
{
	glBegin(GL_LINES);

	frustum.GetCornerPoints(camera_corners);

	glVertex3fv((GLfloat*)&camera_corners[0]);
	glVertex3fv((GLfloat*)&camera_corners[1]);
	glVertex3fv((GLfloat*)&camera_corners[0]);
	glVertex3fv((GLfloat*)&camera_corners[4]);

	glVertex3fv((GLfloat*)&camera_corners[4]);
	glVertex3fv((GLfloat*)&camera_corners[5]);
	glVertex3fv((GLfloat*)&camera_corners[5]);
	glVertex3fv((GLfloat*)&camera_corners[1]);

	glVertex3fv((GLfloat*)&camera_corners[0]);
	glVertex3fv((GLfloat*)&camera_corners[2]);
	glVertex3fv((GLfloat*)&camera_corners[4]);
	glVertex3fv((GLfloat*)&camera_corners[6]);

	glVertex3fv((GLfloat*)&camera_corners[5]);
	glVertex3fv((GLfloat*)&camera_corners[7]);
	glVertex3fv((GLfloat*)&camera_corners[1]);
	glVertex3fv((GLfloat*)&camera_corners[3]);

	glVertex3fv((GLfloat*)&camera_corners[2]);
	glVertex3fv((GLfloat*)&camera_corners[6]);
	glVertex3fv((GLfloat*)&camera_corners[2]);
	glVertex3fv((GLfloat*)&camera_corners[3]);

	glVertex3fv((GLfloat*)&camera_corners[6]);
	glVertex3fv((GLfloat*)&camera_corners[7]);
	glVertex3fv((GLfloat*)&camera_corners[3]);
	glVertex3fv((GLfloat*)&camera_corners[7]);
	
	glEnd();
}

float* Camera::GetViewMatrix()
{
	float4x4 matrix;
	matrix = frustum.ViewMatrix();
	matrix.Transpose();

	return (float*)matrix.v;
}

float Camera::GetNearPlane()
{
	return frustum.nearPlaneDistance;
}

float Camera::GetFarPlane()
{
	return frustum.farPlaneDistance;
}

//Returns FOV in degrees
float Camera::GetFOV()
{
	return frustum.verticalFov * RADTODEG;
}

float Camera::GetAspectRatio() 
{
	return frustum.AspectRatio();

}

bool Camera::ContainsAaBox(const AABB& refBox) const
{
	float3 vCorner[8];
	int iTotalIn = 0;
	refBox.GetCornerPoints(vCorner);

	Plane* m_plane = new Plane[6]();
	frustum.GetPlanes(m_plane);
	   
	for (int p = 0; p < 6; ++p) {

		int iInCount = 8;
		int iPtIn = 1;

		for (int i = 0; i < 8; ++i) {
			if (m_plane[p].IsOnPositiveSide(vCorner[i]) == true) {
				iPtIn = 0;
				--iInCount;
			}
		}

		if (iInCount == 0)
			return false;

		iTotalIn += iPtIn;
	}

	if (iTotalIn == 6)
		return true;

	return true;
}
