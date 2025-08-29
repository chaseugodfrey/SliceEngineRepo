#include "entt/entt.hpp"

template<class Derived, class ActiveTag, class... Required>
class BaseSystem {

public:
	void Bind(entt::registry& reg)
	{

	}

	void Unbind()
	{
		if (!mRegistry)
			return;

	}

	template<class... Excluded>
	void operator()(float dt)
	{
		auto& reg = *mRegistry;
		auto view = reg.view<activeTag, Required...>(entt::exclude<Excluded...>);
		for (auto entity : view)
		{
			static_cast<Derived*>(this)->EntityOnUpdate(
				reg, entity, view.template get<Required>(entity)..., dt
			);
		}
	}

	~BaseSystem()
	{
		Unbind();
	}

protected:
	void EntityOnEnter(entt::entity entity)
	{
		static_cast<Derived*>(this)->OnEnter(*mRegistry, entity);
	}

	void EntityOnExit(entt::entity entity)
	{
		static_cast<Derived*>(this)->EntityOnExit(*mRegistry, entity);
	}

private:
	void SystemOnEnter(entt::registry& reg, entt::entity entity)
	{
		if (reg.all_of<Required...>(entity) && !reg.any_of<ActiveTag>(entity))
		{
			reg.emplace<ActiveTag>(entity);
			EntityOnEnter(entity);
		}
	}

	void SystemOnExit(entt::registry& reg, entt::entity entity)
	{
		if (reg.any_of<ActiveTag>(entity))
		{
			//EntityOnExit(entity);
			reg.remove<ActiveTag>(entity);
		}
	}

	entt::registry* mRegistry{};
};