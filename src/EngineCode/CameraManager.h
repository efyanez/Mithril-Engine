#ifndef _CameraManager
#define _CameraManager

#include "AzulCore.h"
#include "MithrilEngine.h"

class CameraManager
{
public:

	CameraManager() {};
	CameraManager(const CameraManager&) {};
	CameraManager& operator= (const CameraManager) {};
	~CameraManager() {};

	//! Sets and updates the default camera
	void SetDefaultCamera();

	//! Returns the current camera as a Camera* type
	Camera* GetCurrentCamera();

	//! Returns the current camera as a Camera* type
	Camera* GetCurrent2DCamera();
	//! Terminate the Camera Manager and delete the current camera pointer
	void Terminate();

private:
	Camera* currentCamera;
	Camera* current2DCamera;
};

#endif _CameraManager