#include "ObjectPool.h"
#include "Object.h"
#include "Engine.h"

namespace dru
{
	std::vector<CBullet*>* CObjectPool::mBulletPool = {};

	void CObjectPool::Initialize()
	{
		mBulletPool = new std::vector<CBullet*>;
		for (size_t i = 0; i < 10000; i++)
		{
			CBullet* bullet = object::Instantiate_pooling<CBullet>(eLayerType::Bullet, L"Bullet");
			mBulletPool->push_back(bullet);
		}

	}

	void CObjectPool::Release()
	{
		for (CBullet* bullet : *mBulletPool)
		{
			delete bullet;
			bullet = nullptr;

		}
		delete mBulletPool;
	}


	CBullet* CObjectPool::PopBullet()
	{
		CBullet* bullet = mBulletPool->back();

		CScene* scene = CSceneMgr::mActiveScene;
		CLayer& layer = scene->GetLayer(eLayerType::Bullet);
		layer.AddGameObject(bullet, eLayerType::Bullet);

		mBulletPool->pop_back();

		return bullet;

	}
}