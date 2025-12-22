#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include "Component.h"

class Entity
{
public:
	template<typename T, typename... Args>
	void addComponent(Args&&... args)
	{
		m_components[typeid(T)] = std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	T* getComponent()
	{
		auto it = m_components.find(typeid(T));
		if (it != m_components.end())
			return static_cast<T*>(it->second.get());

		return nullptr;
	}

private:
	std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;
};