#pragma once

#include "Singleton.h"

class MasterList : public Singleton<MasterList>
{
	friend class Singleton<MasterList>;

public:
	MasterList() = default;
	~MasterList() = default;
};