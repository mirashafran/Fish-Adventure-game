#pragma once
#include "StaticObject.h"
#include "ObjectFactory.h"

class Stone : public StaticObject {
public:
	using StaticObject::StaticObject;

private:
	static bool m_registerit;
};