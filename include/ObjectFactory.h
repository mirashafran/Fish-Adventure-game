#pragma once
#include <map>	
#include "OtherFish.h"
#include "StaticObject.h"
#include <sfml/Graphics.hpp>
#include "ResourceManager.h"
#include <cstdlib>


template <typename T>
class ObjectFactory {

	public:
		static ObjectFactory& getInstance();
		std::unique_ptr<T> create(const std::string& name);
		bool registerit(const std::string& name, std::unique_ptr<T>(*f)());

	private:
		ObjectFactory() = default;
		std::map<std::string, std::unique_ptr<T>(*)()> m_map;
};


template <typename T>
ObjectFactory<T>& ObjectFactory<T>::getInstance()
{
	static ObjectFactory instance;
	return instance;
}

template <typename T>
std::unique_ptr<T> ObjectFactory<T>::create(const std::string& name)
{

	auto it = m_map.find(name);
	if (it == m_map.end())
		return nullptr;
	return it->second();

}

template <typename T>
bool ObjectFactory<T>::registerit(const std::string& name, std::unique_ptr<T>(*f)())
{
	m_map.emplace(name, f);
	return true;
}