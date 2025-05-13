#pragma once
#include "StaticObject.h"
#include "ObjectFactory.h"

class Bubble : public StaticObject {
public:
	using StaticObject::StaticObject;

private:
	static bool m_registerit;
};