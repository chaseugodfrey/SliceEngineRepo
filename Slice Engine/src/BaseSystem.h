#include "entt/entt.hpp"

template<class Derived, class SystemTag, class... Required>
class BaseSystem {

public:
	void Bind(entt::registry& reg)
	{
		mRegistry = &reg;
		(reg.on_construct<Required>().connect<&BaseSystem::SystemOnEnter>(*this), ...);
		(reg.on_destroy<Required>().connect<&BaseSystem::SystemOnExit>(*this), ...);
	}

	void Unbind()
	{
		if (!mRegistry)
			return;

		(mRegistry->on_construct<Required>().disconnect<&BaseSystem::SystemOnEnter>(*this), ...);
		(mRegistry->on_destroy<Required>().disconnect<&BaseSystem::SystemOnExit>(*this), ...);
		mRegistry = nullptr;
	}

	template<class... Excluded>
	void operator()(float dt)
	{
		auto& reg = *mRegistry;
		auto view = reg.view<SystemTag, Required...>(entt::exclude<Excluded...>);
		for (auto entity : view)
		{
			EntityOnUpdate(reg, entity, dt);
			//static_cast<Derived*>(this)->EntityOnUpdate(reg, entity, dt);
		}
	}

	~BaseSystem()
	{
		Unbind();
	}

protected:
	

	virtual void EntityOnEnter(entt::registry& reg, entt::entity entity)
	{
		//static_cast<Derived*>(this)->EntityOnEnter(*mRegistry, entity);
	}

	virtual void EntityOnExit(entt::registry& reg, entt::entity entity)
	{
		//static_cast<Derived*>(this)->EntityOnExit(*mRegistry, entity);
	}

	virtual void EntityOnUpdate(entt::registry& reg, entt::entity entity, float dt)
	{

	}

private:
	void SystemOnEnter(entt::registry& reg, entt::entity entity)
	{
		if (reg.all_of<Required...>(entity) && !reg.any_of<SystemTag>(entity))
		{
			reg.emplace<SystemTag>(entity);
			EntityOnEnter(reg, entity);
		}
	}

	void SystemOnExit(entt::registry& reg, entt::entity entity)
	{
		if (reg.any_of<SystemTag>(entity))
		{
			EntityOnExit(reg, entity);
			reg.remove<SystemTag>(entity);
		}
	}

	entt::registry* mRegistry{};
};