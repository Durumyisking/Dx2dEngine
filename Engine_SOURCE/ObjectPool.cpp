#include "ObjectPool.h"
#include "Object.h"
#include "Bullet.h"
#include "PlayerAfterImage.h"

namespace dru
{
	std::vector<CBullet*>* CObjectPool::mBulletPool = {};
	std::vector<CAfterImage*>* CObjectPool::mAfterImagePool1 = {};
	std::vector<CAfterImage*>* CObjectPool::mAfterImagePool2 = {};

	void CObjectPool::Initialize()
	{
		mBulletPool = new std::vector<CBullet*>;
		for (size_t i = 0; i < 10000; i++)
		{
			CBullet* bullet = object::Instantiate_pooling<CBullet>(eLayerType::Bullet, L"Bullet");
			mBulletPool->push_back(bullet);
		}

		mAfterImagePool1 = new std::vector<CAfterImage*>;
		mAfterImagePool2 = new std::vector<CAfterImage*>;
	}

	void CObjectPool::InitializeSub1(bool* _flag)
	{
		for (size_t i = 0; i < 250000; i++)
		{
			CAfterImage* afterimage = object::Instantiate_pooling<CAfterImage>(eLayerType::AfterImage, L"AfterImage");
			mAfterImagePool1->push_back(afterimage);
		}
		*_flag = true;
	}

	void CObjectPool::InitializeSub2(bool* _flag)
	{
		for (size_t i = 0; i < 250000; i++)
		{
			CAfterImage* afterimage = object::Instantiate_pooling<CAfterImage>(eLayerType::AfterImage, L"AfterImage");
			mAfterImagePool2->push_back(afterimage);
		}
		*_flag = true;
	}

	void CObjectPool::Release()
	{
		for (CBullet* bullet : *mBulletPool)
		{
			delete bullet;
			bullet = nullptr;

		}
		delete mBulletPool;

		for (CAfterImage* afterimage : *mAfterImagePool1)
		{
			delete afterimage;
			afterimage = nullptr;

		}
		delete mAfterImagePool1;

		for (CAfterImage* afterimage : *mAfterImagePool2)
		{
			delete afterimage;
			afterimage = nullptr;

		}
		delete mAfterImagePool2;
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
		CAfterImage* afterimage = nullptr;
		if (!mAfterImagePool1->empty())
		{
			afterimage = mAfterImagePool1->back();
			mAfterImagePool1->pop_back();
		}
		else
		{
			afterimage = mAfterImagePool2->back();
			mAfterImagePool2->pop_back();
		}

		CScene* scene = CSceneMgr::mActiveScene;
		CLayer& layer = scene->GetLayer(eLayerType::AfterImage);
		layer.AddGameObject(afterimage, eLayerType::AfterImage);

		return afterimage;
	}
}