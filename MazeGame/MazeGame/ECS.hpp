#ifndef ECS_HPP
#define ECS_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>


class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T>
inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr ComponentID MAX_COMPONENTS = 32;

using ComponentBitSet = std::bitset<MAX_COMPONENTS>;
using ComponentArray = std::array<Component *, MAX_COMPONENTS>;

class Component
{
public:
	Entity *mEntity;
	
	virtual ~Component() {};

	virtual void init() {};
	virtual void update() {};
	virtual void draw() {};
};


class Entity
{
private:
	bool mActive;
	std::vector<std::unique_ptr<Component>> mComponents;

	ComponentArray mComponentArray;
	ComponentBitSet mComponentBitSet;
public:
	void update()
	{
		for (auto &c : mComponents) {
			c->update();
		}
	}
	void draw()
	{
		for (auto &c : mComponents) {
			c->draw();
		}
	}
	bool isActive() 
	{
		return mActive;
	}
	void destroy()
	{
		mActive = false;
	}
	
	template <typename T>
	bool hasComponent() const
	{
		return mComponentBitSet[getComponentTypeID<T>()];
	}

	// ??
	template <typename T, typename... TArgs>
	T &addComponent(TArgs&&... mArgs)
	{
		T *c(new T(std::forward<TArgs>(mArgs)...));
		c->mEntity = this;

		std::unique_ptr<Component> uPtr{ c };
		mComponents.emplace_back(std::move(uPtr));
		mComponentArray[getComponentTypeID<T>()] = c;
		mComponentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	// ?
	template <typename T>
	T &getComponent() const
	{
		auto ptr(mComponentArray[getComponentTypeID<T>()]);
		return *static_cast<T *>(ptr);
	}
};


class Manager {
private:
	std::vector<std::unique_ptr<Entity>> mEntities;
public:
	void update()
	{
		for (auto &e : mEntities) {
			e->update();
		}
	}

	void draw()
	{
		for (auto &e : mEntities) {
			e->draw();
		}
	}

	void refresh()
	{
		// Check if any components are inactive, if so remove them
		mEntities.erase(
			std::remove_if(
				std::begin(mEntities),
				std::end(mEntities),
				[](const std::unique_ptr<Entity> &e)
				{
					return !e->isActive();
				}
			),
			std::end(mEntities)
		);
	}

	Entity &addEntity()
	{
		Entity *e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		mEntities.emplace_back(std::move(uPtr));
		return *e;
	}
};

#endif