#pragma once
#include "Component.h"
#include "Globals.h"

#include <string>

class Camera : public Component {
public:
	Camera();
	~Camera();

	void Update() override;
	void OnEditor() override;

private:

};
