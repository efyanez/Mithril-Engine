#ifndef _DrawableManager
#define _DrawableManager

#include <list>

class Drawable;

class DrawableManager
{
public:
	DrawableManager() = default;
	~DrawableManager();
	DrawableManager(const DrawableManager&) = delete;
	DrawableManager& operator=(const DrawableManager&) = delete;

	using StorageListRef = std::list<Drawable*>::iterator;

	void Register(Drawable* dr);
	void Deregister(Drawable* dr);

private:
	std::list<Drawable*> StorageList;
	StorageListRef ref;

friend class Scene;

	void ProcessElements();
};

#endif // !_DrawableManager
