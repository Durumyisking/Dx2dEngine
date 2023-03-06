#include "CollisionMgr.h"
#include "Scene.h"
#include "SceneMgr.h"

namespace dru
{
	std::bitset<static_cast<UINT>(eLayerType::End)> CCollisionMgr::mLayerCollisionMatrix[static_cast<UINT>(eLayerType::End)] = {};
	std::map<UINT64, bool> CCollisionMgr::mCollisionMap;


	void CCollisionMgr::Initialize()
	{

	}

	void CCollisionMgr::update()
	{
		CScene* scene = CSceneMgr::mActiveScene;

		for (UINT row = 0; row < static_cast<UINT>(eLayerType::End); row++)
		{
			for (UINT col = 0; col < static_cast<UINT>(eLayerType::End); col++)
			{
				if (mLayerCollisionMatrix[row][col])
				{
					LayerCollision(scene, static_cast<eLayerType>(col), static_cast<eLayerType>(row));
				}
			}
		}
	}

	void CCollisionMgr::fixedUpdate()
	{
	}

	void CCollisionMgr::render()
	{
	}

	void CCollisionMgr::CollisionLayerCheck(eLayerType _left, eLayerType _right, bool _benable)
	{
		int row = 0;
		int col = 0;

		// Matrix 절반만 사용
		if ((UINT)_left > (UINT)_right)
		{
			row = (UINT)_right;
			col = (UINT)_left;
		}
		else
		{
			row = (UINT)_left;
			col = (UINT)_right;
		}

		mLayerCollisionMatrix[row][col] = _benable;

	}

	void CCollisionMgr::LayerCollision(CScene* _scene, eLayerType _left, eLayerType _right)
	{
		const std::vector<CGameObj*> lefts = _scene->GetGameObj(_left);
		const std::vector<CGameObj*> rights = _scene->GetGameObj(_right);

		for (CGameObj* left : lefts)
		{

			if (left->GetState() != CGameObj::eState::Active)
				continue;

			if (!left->GetComponent<CCollider2D>())
				continue;

			for (CGameObj* right : rights)
			{
				if (right->GetState() != CGameObj::eState::Active)
					continue;

				if (!right->GetComponent<CCollider2D>())
					continue;

				if (left == right)
					continue;

				ColliderCollision(left->GetComponent<CCollider2D>(), right->GetComponent<CCollider2D>());

			}
		}
	}

	void CCollisionMgr::ColliderCollision(CCollider2D* _left, CCollider2D* _right)
	{
		ColliderID colliderID;
		colliderID.left = (UINT)_left;
		colliderID.right = (UINT)_right;

		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(colliderID.id);

		if (mCollisionMap.end() == iter) // 순회했는데 해당 id의 true인애가 없었다. 충돌중이지 않았다.
		{
			mCollisionMap.insert(std::make_pair(colliderID.id, false));
			iter = mCollisionMap.find(colliderID.id);
		}

		// 충돌체크
		if (Intersect(_left, _right)) // 충돌을 한 상태
		{
			// 충돌 중
			if (iter->second)
			{
				if (_left->IsTrigger())
					_left->OnTrigger(_right);
				else
					_left->OnCollision(_right);

				if (_right->IsTrigger())
					_right->OnTrigger(_left);
				else
					_right->OnCollision(_left);

				iter->second = true;
			}
			else // 첫 충돌
			{
				if (_left->IsTrigger())
					_left->OnTriggerEnter(_right);
				else
					_left->OnCollisionEnter(_right);

				if (_right->IsTrigger())
					_right->OnTriggerEnter(_left);
				else
					_right->OnCollisionEnter(_left);

				iter->second = true;
			}
		}
		else // 충돌 X
		{
			if (iter->second) // 충돌 빠져나감
			{
				if (_left->IsTrigger())
					_left->OnTriggerExit(_right);
				else
					_left->OnCollisionExit(_right);

				if (_right->IsTrigger())
					_right->OnTriggerExit(_left);
				else
					_right->OnCollisionExit(_left);

				iter->second = false;
			}
		}
	}

	bool CCollisionMgr::Intersect(CCollider2D* _left, CCollider2D* _right)
	{


		return true;
	}

}