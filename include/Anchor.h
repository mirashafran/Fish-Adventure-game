#pragma once
#include "StaticObject.h"
#include "ObjectFactory.h"

class Anchor : public StaticObject {
public:
	using StaticObject::StaticObject;

private:
	static bool m_registerit;
};