#include "ObjectPool.h"
#include "Object.h"
#include "Bullet.h"
#include "PlayerAfterImage.h"

namespace dru
{
	std::vector<CBullet*>* CObjectPool::mBulletPool = {};
	std::vector<CAfterImage*>* CObjectPool::mAfterImagePool = {};

	void CObjectPool::Initialize()
	{
		mBulletPool = new std::vector<CBullet*>;
		for (size_t i = 0; i < 10000; i++)
		{
			CBullet* bullet = object::Instantiate_pooling<CBullet>(eLayerType::Bullet, L"Bullet");
			mBulletPool->push_back(bullet);
		}

		mAfterImagePool = new std::vector<CAfterImage*>;
		for (size_t i = 0; i < 100000; i++)
		{
			CAfterImage* afterimage = object::Instantiate_pooling<CAfterImage>(eLayerType::AfterImage, L"AfterImage");
			mAfterImagePool->push_back(afterimage);
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

		for (CAfterImage* afterimage : *mAfterImagePool)
		{
			delete afterimage;
			afterimage = nullptr;

		}
		delete mAfterImagePool;
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
	CAfterImage* CObjectPool::PopAfterImage()
	{
		CAfterImage* afterimage = mAfterImagePool->back();

		CScene* scene = CSceneMgr::mActiveScene;
		CLayer& layer = scene->GetLayer(eLayerType::AfterImage);
		layer.AddGameObject(afterimage, eLayerType::AfterImage);

		mAfterImagePool->pop_back();

		return afterimage;
	}
}