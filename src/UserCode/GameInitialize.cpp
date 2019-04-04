#include "../EngineCode/MithrilEngine.h"

void MithrilEngine::GameInitialize()
{
	// Game Window Device setup
	this->setWindowName("Mithril Engine");
	this->setWidthHeight(800, 600);
	this->SetClearColor(0.4f, 0.4f, 0.8f, 1.0f);
}