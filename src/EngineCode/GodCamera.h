#ifndef _GodCamera
#define _GodCamera

#include "Updatable.h"
#include "AzulCore.h"
#include "CameraManager.h" 

class Camera;

class GodCamera : public Updatable
{
public:
	//! GodCamera constructor
	/*!
	\ingroup MithrilEngine
	*/
	GodCamera();

	~GodCamera();

	//! Take user input (Arrow keys and Y,G,H,J keys) to move the God Camera
	void Update() override;

private:

	Camera* currentCamera;
};

#endif // _GodCamera