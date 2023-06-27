#pragma once
#include "Engine.h"

namespace dru
{
	class CAsyncLoad
	{

	public:
		static void Initialize(bool* _flag);
		static void LoadAfterImageMaterial1(bool* _flag);
		static void LoadAfterImageMaterial2(bool* _flag);

	};
}
