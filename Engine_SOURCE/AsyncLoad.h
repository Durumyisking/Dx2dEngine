#pragma once
#include "Engine.h"

namespace dru
{
	class CAsyncLoad
	{

	public:
		static void Initialize(std::promise<bool>& promiseObj);

	};
}
