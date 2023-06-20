#pragma once
#include "Engine.h"

namespace dru
{
	class CBullet;
	class CAfterImage;

	class CObjectPool
	{

	public:
		static void Initialize();
		static void Release();
		static CBullet* PopBullet();
		static CAfterImage* PopAfterImage();



	private:
		static std::vector<CBullet*>* mBulletPool;
		static std::vector<CAfterImage*>* mAfterImagePool;

	};
}
