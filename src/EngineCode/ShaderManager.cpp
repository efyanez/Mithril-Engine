#include "ShaderManager.h"
#include <iostream>

ShaderManager* ShaderManager::self = NULL;

void ShaderManager::privLoadShader(std::string key, std::string filepath)
{
	assert((key != "" || filepath != "") && "Key or filepath invalid");
	assert(Instance().ShaderList[key] == NULL && "Duplicate key found!");

	Instance().ShaderList[key] = new ShaderObject(filepath.c_str());
	assert(Instance().ShaderList[key] != nullptr);
	DebugMsg::out("Successfully loaded: %s\n", key.c_str());
}

ShaderObject * ShaderManager::privGetShader(std::string key)
{

	assert(Instance().ShaderList[key] != NULL && "Shader not found!");
	return Instance().ShaderList[key];
}

ShaderObject * ShaderManager::privGetShader(DefaultShader key)
{
	switch (key)
	{
	case(FlatRender):
		return Instance().ShaderList["FlatRender"];
		break;
	case(LightRender):
		return Instance().ShaderList["LightRender"];
		break;
	case(ColorVaryRender):
		return Instance().ShaderList["ColorVaryRender"];
		break;
	case(ColorConstantRender):
		return Instance().ShaderList["ColorConstantRender"];
		break;
	case(ColorNoTextureRender):
		return Instance().ShaderList["ColorNoTextureRender"];
		break;
	case(SpriteRender):
		return Instance().ShaderList["SpriteRender"];
		break;
	case(SpriteLineRender):
		return Instance().ShaderList["SpriteLineRender"];
		break;
	default:
		return nullptr;
		break;
	}
}

void ShaderManager::privLoadDefaultShaders()
{

	Instance().LoadShader("FlatRender", "../Assets/Shaders/textureFlatRender");

	Instance().LoadShader("LightRender", "../Assets/Shaders/textureLightRender");

	Instance().LoadShader("ColorVaryRender", "../Assets/Shaders/colorVaryRender");

	Instance().LoadShader("ColorConstantRender", "../Assets/Shaders/colorConstantRender");

	Instance().LoadShader("ColorNoTextureRender", "../Assets/Shaders/colorNoTextureRender");

	Instance().LoadShader("SpriteRender", "../Assets/Shaders/spriteRender");

	Instance().LoadShader("SpriteLineRender", "../Assets/Shaders/spriteLineRender");

}

void ShaderManager::privUnloadShaders()
{
	std::map<std::string, ShaderObject*>::iterator shaderIt = Instance().ShaderList.begin();
	while (shaderIt != Instance().ShaderList.end())
	{
		delete shaderIt->second;
		shaderIt->second = nullptr;
		shaderIt++;
	}
	DebugMsg::out("SHADERS UNLOADED\n");
	delete self;
}
