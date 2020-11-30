#include "Camera.h"
#include "Globals.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include "ImGui/imgui.h"

#include "glew/include/glew.h"

Camera::Camera() :Component(){

	type = ComponentType::CAMERA;

	frustum.type = PerspectiveFrustum;

	frustum.front = float3::unitZ;
	frustum.up = float3::unitY;

	frustum.pos = float3(0.0f, 0.0f, 0.0f);

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