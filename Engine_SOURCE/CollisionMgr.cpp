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
		if ((UINT)_left <= (UINT)_right)
		{
			row = (UINT)_left;
			col = (UINT)_right;
		}
		else
		{
			row = (UINT)_right;
			col = (UINT)_left;
		}

		mLayerCollisionMatrix[row][col] = _benable;
	}

	void CCollisionMgr::LayerCollision(CScene* _scene, eLayerType _left, eLayerType _right)
	{
		const std::vector<CGameObj*>& lefts = _scene->GetGameObj(_left);
		const std::vector<CGameObj*>& rights = _scene->GetGameObj(_right);

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
		colliderID.left = (UINT)_left->GetColliderID();
		colliderID.right = (UINT)_right->GetColliderID();

		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(colliderID.id);

		if (mCollisionMap.end() == iter) // 순회했는데 해당 id의 true인애가 없었다. 충돌중이지 않았다.
		{
			mCollisionMap.insert(std::make_pair(colliderID.id, false));
			iter = mCollisionMap.find(colliderID.id);
		}

		// 충돌체크
		if (Intersect(_left, _right)) // 충돌을 한 상태
		{
			// 첫 충돌
			if (iter->second == false)
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
				_left->SetState(eCollisionState::CollisionEnter);
				_right->SetState(eCollisionState::CollisionEnter);

			}
			else // 충돌 중
			{
				if (_left->IsTrigger())
					_left->OnTrigger(_right);
				else
					_left->OnCollision(_right);

				if (_right->IsTrigger())
					_right->OnTrigger(_left);
				else
					_right->OnCollision(_left);

				_left->SetState(eCollisionState::CollisionStay);
				_right->SetState(eCollisionState::CollisionStay);

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

				_left->SetState(eCollisionState::CollisionExit);
				_right->SetState(eCollisionState::CollisionExit);

			}
			else
			{
				_left->SetState(eCollisionState::CollisionNot);
				_right->SetState(eCollisionState::CollisionNot);

				mCollisionMap.erase(iter);
			}
		}
	}

	bool CCollisionMgr::Intersect(CCollider2D* _left, CCollider2D* _right)
	{

	#pragma region RectVsRect

		if (eColliderType::Rect == _left->GetType() && eColliderType::Rect == _right->GetType())
		{
			Vector3 arrLocalPos[4] =
			{
				Vector3{-0.5f, 0.5f, 0.0f},
				Vector3{0.5f, 0.5f, 0.0f},
				Vector3{0.5f, -0.5f, 0.0f},
				Vector3{-0.5f, -0.5f, 0.0f}
			};

			CTransform* leftTr = _left->GetOwner()->GetComponent<CTransform>();
			CTransform* rightTr = _right->GetOwner()->GetComponent<CTransform>();

			Matrix leftMatrix = leftTr->GetWorldMatrix();
			Matrix rightMatrix = rightTr->GetWorldMatrix();

			// 분리축 벡터 (투영벡터)
			Vector3 Axis[4] = {};
			Axis[0] = (Vector3::Transform(arrLocalPos[1], leftMatrix));
			Axis[1] = (Vector3::Transform(arrLocalPos[3], leftMatrix));
			Axis[2] = (Vector3::Transform(arrLocalPos[1], rightMatrix));
			Axis[3] = (Vector3::Transform(arrLocalPos[3], rightMatrix));

			Axis[0] -= Vector3::Transform(arrLocalPos[0], leftMatrix);
			Axis[1] -= Vector3::Transform(arrLocalPos[0], leftMatrix);
			Axis[2] -= Vector3::Transform(arrLocalPos[0], rightMatrix);
			Axis[3] -= Vector3::Transform(arrLocalPos[0], rightMatrix);

			Vector3 leftScale = Vector3(_left->GetScale().x, _left->GetScale().y, 1.0f);
			Axis[0] = Axis[0] * leftScale;
			Axis[1] = Axis[1] * leftScale;

			Vector3 rightScale = Vector3(_right->GetScale().x, _right->GetScale().y, 1.0f);
			Axis[2] = Axis[2] * rightScale;
			Axis[3] = Axis[3] * rightScale;

			for (size_t i = 0; i < 4; ++i)
				Axis[i].z = 0.f;

			Vector3 vc = leftTr->GetPosition() - rightTr->GetPosition();
			vc.z = 0.f;

			Vector3 centerDir = vc;
			for (size_t i = 0; i < 4; i++)
			{
				Vector3 vA = Axis[i];
				//vA.Normalize();

				float projDist = 0.f;
				for (size_t j = 0; j < 4; j++)
				{
					projDist += fabsf(Axis[j].Dot(vA) / 2.f);
				}

				if (projDist < fabsf(centerDir.Dot(vA)))
				{
					return false;
				}
			}
		}

	#pragma endregion

	#pragma region CircleVsCircle
		
		else if (eColliderType::Circle == _left->GetType() && eColliderType::Circle == _right->GetType())
		{
			Vector2 leftPos = { _left->GetColliderPos().x, _left->GetColliderPos().y };
			Vector2 rightPos = { _right->GetColliderPos().x, _right->GetColliderPos().y };

			float Gap = (leftPos - rightPos).Length();

			float leftScale = _left->GetRadius() * 0.5f;
			float rightScale = _right->GetRadius() * 0.5f;

			if ((leftScale + rightScale) < Gap)
			{
				return false;
			}
		}



	#pragma endregion


	#pragma region RectVsCircle

	#pragma endregion


		return true;
	}
}