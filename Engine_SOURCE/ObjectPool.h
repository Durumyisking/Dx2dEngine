#pragma once
#include "Engine.h"
#include "Bullet.h"

namespace dru
{
	class CObjectPool
	{

	public:
		static void Initialize();
		static void Release();
		static CBullet* PopBullet();



	private:
		static std::vector<CBullet*>* mBulletPool;

	};
}
