#include "CameraManager.h"


void CameraManager::SetDefaultCamera()
{
	Camera* defaultCam = new Camera(Camera::Type::PERSPECTIVE_3D);
	defaultCam->setViewport(0, 0, MithrilEngine::GetWidth(), MithrilEngine::GetHeight());
	defaultCam->setPerspective(35.0f, float(MithrilEngine::GetWidth()) / float(MithrilEngine::GetHeight()), 1.0f, 5000.0f);

	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(50.0f, 50.0f, 150.0f);
	Vect lookAt3DCam(0.0f, 0.0f, 0.0f);
	defaultCam->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
	defaultCam->updateCamera();

	currentCamera = defaultCam;
	currentCamera->updateCamera();

	Camera* default2DCam = new Camera(Camera::Type::ORTHOGRAPHIC_2D);
	default2DCam->setViewport(0, 0, MithrilEngine::GetWidth(), MithrilEngine::GetHeight());
	default2DCam->setOrthographic(-0.5f*MithrilEngine::GetWidth(), 0.5f*MithrilEngine::GetWidth(), -0.5f*MithrilEngine::GetHeight(), 0.5f*MithrilEngine::GetHeight(), 1.0f, 1000.0f);

	// Orient Camera
	Vect up2DCam(0.0f, 1.0f, 0.0f);
	Vect pos2DCam(0.0f, 0.0f, 0.0f);
	Vect lookAt2DCam(0.0f, 0.0f, -1.0f);
	default2DCam->setOrientAndPosition(up2DCam, lookAt2DCam, pos2DCam);

	default2DCam->updateCamera();

	current2DCamera = default2DCam;
	current2DCamera->updateCamera();

}

Camera * CameraManager::GetCurrentCamera()
{
	return currentCamera;
}

Camera * CameraManager::GetCurrent2DCamera()
{
	return current2DCamera;
}

void CameraManager::Terminate()
{
	delete currentCamera;
	delete current2DCamera;
}
