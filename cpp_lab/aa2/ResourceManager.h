#pragma once
#include <string>
#include <unordered_map>
#include <memory>

class ResourceManager
{
public:
	int* load(const std::string& filename)
	{
		auto it = m_cache.find(filename);
		if (it != m_cache.end())
		{
			return it->second.get();
		}

		std::shared_ptr<int> resource = std::make_shared<int>(0);

		m_cache[filename] = resource;

		return resource.get();
	}

private:
	std::unordered_map<std::string, std::shared_ptr<int>> m_cache;
};
