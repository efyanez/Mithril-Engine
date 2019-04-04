#ifndef _ShaderManager
#define _ShaderManager

#include <map>
#include "AzulCore.h"

class ShaderManager
{

public:
	enum DefaultShader
	{
		FlatRender,
		LightRender,
		ColorVaryRender,
		ColorConstantRender,
		ColorNoTextureRender,
		SpriteRender,
		SpriteLineRender
	};

private:
	static ShaderManager* self;
	ShaderManager() {};
	ShaderManager(const ShaderManager&) {};
	ShaderManager& operator= (const ShaderManager) {};
	~ShaderManager() {};

	static ShaderManager& Instance()
	{
		if (!self)
		{
			self = new ShaderManager();
		}
		return *self;
	};

	std::map<std::string, ShaderObject*> ShaderList;

	void privLoadShader(std::string key, std::string filepath);
	ShaderObject* privGetShader(std::string key);
	ShaderObject* privGetShader(DefaultShader key);

	void privLoadDefaultShaders();
	void privUnloadShaders();



public:
	//! Public static function. Loads a shader from a filepath into the map of Shader pointers.
	/*!
	\param key A string name for the Shader.
	\param filepath A string filepath for the shader location.
	*/
	static void LoadShader(std::string key, std::string filepath) { Instance().privLoadShader(key, filepath); };

	//! Returns a shader pointer by taking a key and searching the key in the map.
	/*!
	\param key A string name for the Shader.
	\return Returns a Shader pointer.
	*/
	static ShaderObject* GetShader(std::string key) { return Instance().privGetShader(key); };

	//! Returns a Shader pointer by taking a DefaultShader enum.
	/*!
	\param key A DefaultShader enum for the Shader.
	\return Returns a Shader pointer.
	*/
	static ShaderObject* GetShader(DefaultShader key) { return Instance().privGetShader(key); };

	//! Loads the default shaders.
	static void LoadDefaultShaders() { Instance().privLoadDefaultShaders(); };

	//! Unloads the shaders from the map and deletes their associated pointers.
	static void UnloadShaders() { Instance().privUnloadShaders(); };
};

#endif _ShaderManager