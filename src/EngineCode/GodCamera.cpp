#include "GodCamera.h"
#include "SceneManager.h"
#include "Scene.h"

// Camera vars
Vect CamPos(50, 250, 450.0f);
Matrix CamRot(IDENTITY);        // No rotation initially
Vect CamUp(0, 1, 0);            // Using local Y axis as 'Up'
Vect CamDir(0, 0, 1);           // Using the local Z axis as 'forward'
float CamTranSpeed = 1.5f;
float CamRotSpeed = .02f;

GodCamera::GodCamera()
{
	Vect Target(0, 0, 0);
	CamRot.set(ROT_ORIENT, Target - CamPos, CamUp);
	SubmitUpdateRegistration();
	currentCamera = SceneManager::GetCurrentScene()->GetCamManager()->GetCurrentCamera();

	currentCamera->setOrientAndPosition(CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
	currentCamera->updateCamera();
}

GodCamera::~GodCamera()
{

}

void GodCamera::Update()
{

	if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
	{
		//Updatable::SubmitUpdateRegistration();
		//Updatable::SubmitUpdateDeregistration();
	}

	// Camera translation movement (NOTE: This time, I'm NOT using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_Y))
	{
		CamPos += Vect(0, 0, 1) * CamRot * CamTranSpeed;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_H))
	{
		CamPos += Vect(0, 0, 1) * CamRot * -CamTranSpeed;
	}

	if (Keyboard::GetKeyState(AZUL_KEY::KEY_G))
	{
		CamPos += Vect(1, 0, 0) * CamRot * CamTranSpeed;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_J))
	{
		CamPos += Vect(1, 0, 0) * CamRot * -CamTranSpeed;
	}

	// Camera Rotation movement (NOTE: This time, I'm NOT using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_LEFT))
	{
		CamRot *= Matrix(ROT_Y, CamRotSpeed);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_RIGHT))
	{
		CamRot *= Matrix(ROT_Y, -CamRotSpeed);
	}

	if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_UP))
	{
		CamRot *= Matrix(ROT_AXIS_ANGLE, Vect(1, 0, 0) * CamRot, -CamRotSpeed);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_DOWN))
	{
		CamRot *= Matrix(ROT_AXIS_ANGLE, Vect(1, 0, 0) * CamRot, CamRotSpeed);
	}
	currentCamera->setOrientAndPosition(CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
	currentCamera->updateCamera();
}