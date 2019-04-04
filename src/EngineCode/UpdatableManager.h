#ifndef _UpdatableManager
#define _UpdatableManager

#include <list>

class Updatable;

class UpdatableManager
{
public:
	UpdatableManager() = default;
	~UpdatableManager();
	UpdatableManager(const UpdatableManager&) = delete;
	UpdatableManager& operator=(const UpdatableManager&) = delete;

	using StorageListRef = std::list<Updatable*>::iterator;

	void Register(Updatable* up);
	void Deregister(Updatable* up);

private:
	std::list<Updatable*> StorageList;
	StorageListRef ref;

friend class Scene;

	void ProcessElements();
};

#endif // !_UpdatableManager
