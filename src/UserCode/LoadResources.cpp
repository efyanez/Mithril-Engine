#include "../EngineCode/MithrilEngine.h"

void MithrilEngine::LoadResources()
{

	ModelManager::LoadDefaultModels();
	TextureManager::LoadDefaultTextures();
	ShaderManager::LoadDefaultShaders();

	TextureManager::LoadTexture("SpaceFrigateTex", "../Assets/ModelsAndTextures/space_frigate.tga");
	TextureManager::LoadTexture("EnemyTankTex", "../Assets/ModelsAndTextures/enemytanktexture.tga");
	TextureManager::LoadTexture("PlaneTex", "../Assets/ModelsAndTextures/newterrain.tga");
	TextureManager::LoadTexture("WeedTex", "../Assets/ModelsAndTextures/Duckweed.tga");

	TextureManager::LoadTexture("BrickWall", "../Assets/ModelsAndTextures/brick-wall.tga");
	TextureManager::LoadTexture("RoofTexture", "../Assets/ModelsAndTextures/Rooftexture.tga");
	TextureManager::LoadTexture("RedBrick", "../Assets/ModelsAndTextures/RedBrick.tga");
	TextureManager::LoadTexture("ChimneyTexture", "../Assets/ModelsAndTextures/Chimneytexture.tga");
	TextureManager::LoadTexture("StartUI", "../Assets/ModelsAndTextures/StartUI.tga");
	TextureManager::LoadTexture("UITex", "../Assets/ModelsAndTextures/tankgameUI.tga");
	TextureManager::LoadTexture("Hearts3", "../Assets/ModelsAndTextures/hearts3.tga");
	TextureManager::LoadTexture("Hearts2", "../Assets/ModelsAndTextures/hearts2.tga");
	TextureManager::LoadTexture("Hearts1", "../Assets/ModelsAndTextures/hearts1.tga");
	TextureManager::LoadTexture("Sunset", "../Assets/ModelsAndTextures/sunset.tga");
	TextureManager::LoadTexture("StitchTex", "../Assets/ModelsAndTextures/stitch.tga");

	// Particle Effect Textures
	TextureManager::LoadTexture("Fire", "../Assets/ModelsAndTextures/fireparticle.tga");
	TextureManager::LoadTexture("Smoke", "../Assets/ModelsAndTextures/smokeparticle.tga");
	TextureManager::LoadTexture("Magic", "../Assets/ModelsAndTextures/magicparticle.tga");
	TextureManager::LoadTexture("Water1", "../Assets/ModelsAndTextures/wateroutsideparticle.tga");
	TextureManager::LoadTexture("Water2", "../Assets/ModelsAndTextures/waterinsideparticle.tga");

	TextureManager::LoadTexture("TimesNewRoman", "../Assets/ModelsAndTextures/TimesNewRoman.tga");
	TextureManager::LoadTexture("BerlinSans", "../Assets/ModelsAndTextures/BerlinSans.tga");

	SpriteFontManager::LoadSpriteFont("TimesNewRoman", "../Assets/Fonts/TimesNewRoman.xml");
	SpriteFontManager::LoadSpriteFont("BerlinSans", "../Assets/Fonts/BerlinSans.xml");

	ModelManager::LoadModel("Axis", "../Assets/ModelsAndTextures/Axis.azul");
	ModelManager::LoadModel("Plane", "../Assets/ModelsAndTextures/Plane.azul");
	ModelManager::LoadModel("Frigate", "../Assets/ModelsAndTextures/space_frigate.azul");
	ModelManager::LoadModel("TankBottom", "../Assets/ModelsAndTextures/tank_bottom.azul");
	ModelManager::LoadModel("TankTop", "../Assets/ModelsAndTextures/tank_top.azul");
	ModelManager::LoadModel("EnemyTank", "../Assets/ModelsAndTextures/enemytank.azul");
	ModelManager::LoadModel("Terrain", "../Assets/ModelsAndTextures/terrain.azul");
	ModelManager::LoadModel("Grass", "../Assets/ModelsAndTextures/grass.azul");
	ModelManager::LoadModel("Sky", "../Assets/ModelsAndTextures/sky.azul");
	ModelManager::LoadModel("Square", "../Assets/ModelsAndTextures/Square.azul");

	ModelManager::LoadModel("Pyramid", "../Assets/ModelsAndTextures/Cottage.azul");

	ImageManager::CreateImage("StartUI", TextureManager::GetTexture("StartUI"), new Rect(0.0f, 0.0f, (float)TextureManager::GetTexture("StartUI")->getWidth(), (float)TextureManager::GetTexture("StartUI")->getHeight()));
	ImageManager::CreateImage("UI", TextureManager::GetTexture("UITex"), new Rect(0.0f, 0.0f, (float)TextureManager::GetTexture("UITex")->getWidth(), (float)TextureManager::GetTexture("UITex")->getHeight()));
	ImageManager::CreateImage("Hearts3", TextureManager::GetTexture("Hearts3"), new Rect(0.0f, 0.0f, (float)TextureManager::GetTexture("Hearts3")->getWidth(), (float)TextureManager::GetTexture("Hearts3")->getHeight()));
	ImageManager::CreateImage("Hearts2", TextureManager::GetTexture("Hearts2"), new Rect(0.0f, 0.0f, (float)TextureManager::GetTexture("Hearts2")->getWidth(), (float)TextureManager::GetTexture("Hearts2")->getHeight()));
	ImageManager::CreateImage("Hearts1", TextureManager::GetTexture("Hearts1"), new Rect(0.0f, 0.0f, (float)TextureManager::GetTexture("Hearts1")->getWidth(), (float)TextureManager::GetTexture("Hearts1")->getHeight()));
	ImageManager::CreateImage("Stitch", TextureManager::GetTexture("StitchTex"), new Rect(0.0f, 0.0f, (float)TextureManager::GetTexture("StitchTex")->getWidth(), (float)TextureManager::GetTexture("StitchTex")->getHeight()));

	SoundManager::LoadSound("TankShot", "../Assets/Sounds/tankshot.ogg");
	SoundManager::LoadSound("TankMove", "../Assets/Sounds/tankmove.ogg");
	SoundManager::LoadSound("StartMusic", "../Assets/Sounds/startmusic.ogg");

	TerrainObjectManager::LoadTerrainObject("MainTerrain", "../Assets/ModelsAndTextures/finalHM.tga", "PlaneTex", 6, 6, 597, 225, 5, 2.0f, -10.0f, 2.0f);
	TerrainObjectManager::LoadTerrainObject("StartTerrain", "../Assets/ModelsAndTextures/startterrain.tga", "PlaneTex", 8, 8, 1024, 150, 3, 1.5f, 0.0f, 2.0f, 3);
	TerrainObjectManager::LoadTerrainObject("FinalTerrain", "../Assets/ModelsAndTextures/finallevelHM.tga", "PlaneTex", 8, 8, 800, 650, 3, 1.5f, 0.0f, 2.0f, 3);

	ParticleEffectStream* pe = new ParticleEffectStream();
	pe->SetBurstCount(300);
	pe->SetBurstIntervalAndLife(0.5f, 3.0f);
	pe->SetGraphicObject("Square", "Water1");
	pe->SetSpeed(1.0f);
	pe->SetScale(3.0f);
	pe->SetTightness(0.8f);

	ParticleEffectManager::LoadParticleEffect("Water1", pe);

	ParticleEffectStream* pe2 = new ParticleEffectStream();
	pe2->SetBurstCount(30);
	pe2->SetBurstIntervalAndLife(0.5f, 3.0f);
	pe2->SetGraphicObject("Square", "Water2");
	pe2->SetSpeed(1.0f);
	pe2->SetScale(2.0f);
	pe2->SetTightness(0.8f);

	ParticleEffectManager::LoadParticleEffect("Water2", pe2);

	ParticleEffectSphericalBurst* pe3 = new ParticleEffectSphericalBurst();
	pe3->SetBurstCount(300);
	pe3->SetBurstIntervalAndLife(1.1f, 1.0f);
	pe3->SetGraphicObject("Square", "Fire");
	pe3->SetSpeed(6.0f);
	pe3->SetScale(2.0f);
	ParticleEffectManager::LoadParticleEffect("Explosion", pe3);

	Scene* firstScene = new StartScene();
	//Scene* firstScene = new FirstScene();
	//Scene* firstScene = new SecondScene();
	//Scene* firstScene = new FinalScene();
	SceneManager::SetCurrentScene(firstScene);
	SceneManager::InitializeCurrentScene();
}