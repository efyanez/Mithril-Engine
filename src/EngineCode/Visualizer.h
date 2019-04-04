#ifndef _Visualizer
#define _Visualizer

#include <map>
#include "AzulCore.h"
#include "Align16.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
#include <list>

class Collidable;

class Visualizer : public Align16
{

	friend class CollisionVolumeAABB;
	friend class CollisionVolumeOBB;
	friend class CollisionVolumeBSphere;

private:
	static Visualizer* self;
	Visualizer() {};
	Visualizer(const Visualizer&) {};
	Visualizer& operator= (const Visualizer) {};
	~Visualizer();

	static Visualizer& Instance()
	{
		if (!self)
		{
			self = new Visualizer();
		}
		return *self;
	};

	static Vect DEFAULT_COLOR;
	GraphicsObject_WireframeConstantColor* WFUnitSphere;
	GraphicsObject_WireframeConstantColor* WFUnitBox;

	struct VisualizerData
	{
		Vect myColor;
		CollisionVolume* myVolume;
	};

	struct VisualizerTerrainCell
	{
		Vect myColor;
		Matrix myWorld;
	};

	std::list<VisualizerData> visualizerList;
	std::list<VisualizerTerrainCell> visualizerTerrainList;
	

	//! Private non-static function to render BSphere wireframe object.
	/*!
	\param S a Matrix reference.
	\param color a const Vect reference.
	*/
	void privRenderBSphere(Matrix& S, const Vect& color);
	void privRenderAABB(Matrix& S, const Vect& color);
	void privRenderOBB(Matrix& S, const Vect& color);
	void privRenderAll();

	void privSubmitVisualize(CollisionVolume * vol, const Vect & col);
	void privSubmitVisualize(Collidable * vol, const Vect & col);
	void privSubmitVisualize(Vect & min, Vect & max, const Vect & col);

	void privRenderCollisionVolume(Collidable * C, const Vect & color);
	void privRenderCollisionVolume(CollisionVolume * C, const Vect & color);

	void privCreateBSphere();
	void privTerminate();

public:

	//! Public static function to render BSphere wireframe object.
	/*!
	\param S a Matrix reference.
	\param col a const Vect reference.
	*/
	static void ShowAll() { Instance().privRenderAll(); }

	//! Public static function to render a collision volume from a Collidable pointer.
	/*!
	\param C a Collidable pointer.
	\param col a const Vect reference.
	*/
	static void VisualizeMe(Collidable* C, const Vect & col = DEFAULT_COLOR) { Instance().privSubmitVisualize(C, col); }

	//! Public static function to render a collision volume from a CollisionVolume pointer.
	/*!
	\param C a CollisionVolume pointer.
	\param col a const Vect reference.
	*/
	static void VisualizeMe(CollisionVolume * C, const Vect & col = DEFAULT_COLOR) { Instance().privSubmitVisualize(C, col); }

	//! Public static function to render a collision volume from a Vect min and Vect max.
	/*!
	\param min a const Vect reference.
	\param max a const Vect reference.
	\param col a const Vect reference.
	*/
	static void VisualizeMe(Vect & min, Vect & max, const Vect & col = DEFAULT_COLOR) { Instance().privSubmitVisualize(min, max, col); }

	//! Public static function to render a collision volume from a Collidable pointer.
	/*!
	\param C a Collidable pointer.
	\param col a const Vect reference.
	*/
	static void ShowCollisionVolume(Collidable* C, const Vect& col = DEFAULT_COLOR) { Instance().privRenderCollisionVolume(C, col); }

	//! Create initial visualizer shapes
	static void CreateSphere() { Instance().privCreateBSphere(); }
	//! Terminates the Visualizer
	static void Terminate() { Instance().privTerminate(); }

protected:
	static void ShowSphere(CollisionVolumeBSphere& S, const Vect& col = DEFAULT_COLOR) { Instance().privRenderBSphere(S.GetWorld(), col); }
	static void ShowBox(CollisionVolumeAABB& A, const Vect& col = DEFAULT_COLOR) { Instance().privRenderAABB(A.GetWorld(), col); }
	static void ShowBox(CollisionVolumeOBB& A, const Vect& col = DEFAULT_COLOR) { Instance().privRenderOBB(A.GetWorld(), col); }

};

#endif _Visualizer