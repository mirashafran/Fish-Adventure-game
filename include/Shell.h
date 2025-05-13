#pragma once
#include "StaticObject.h"
#include "ObjectFactory.h"

class Shell : public StaticObject {
public:
	using StaticObject::StaticObject;

private:
	static bool m_registerit;
};