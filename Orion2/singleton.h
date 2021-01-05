#pragma once

#define SINGLETON(name, type) const auto name = singleton::get<type>()
#define STATIC_SINGLETON(name, type) static SINGLETON(name, type)

#include <memory>

class singleton
{
public:
	template <typename T, typename... Args>
	static auto get(Args... args) -> std::shared_ptr<T>
	{
		const static auto pInstance = std::make_shared<T>(args...);

		return pInstance;
	}
};
