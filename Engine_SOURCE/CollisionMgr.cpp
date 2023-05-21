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
				if (!_left->IsOn() || !_right->IsOn())
				{
					return;
				}

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
				if (!_left->IsOn() || !_right->IsOn())
				{
					_left->OnCollisionExit(_right);				
					_right->OnCollisionExit(_left);
					_left->SetState(eCollisionState::CollisionExit);
					_right->SetState(eCollisionState::CollisionExit);

					return;
				}

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
		
			Vector3 leftScale = Vector3(_left->GetScale().x, _left->GetScale().y, 1.0f);
			Matrix finalLeft = Matrix::CreateScale(leftScale);
			finalLeft *= leftMatrix;

			Vector3 rightScale = Vector3(_right->GetScale().x, _right->GetScale().y, 1.0f);
			Matrix finalRight = Matrix::CreateScale(rightScale);
			finalRight *= rightMatrix;

			Axis[0] = (Vector3::Transform(arrLocalPos[1], finalLeft));
			Axis[1] = (Vector3::Transform(arrLocalPos[3], finalLeft));
			Axis[2] = (Vector3::Transform(arrLocalPos[1], finalRight));
			Axis[3] = (Vector3::Transform(arrLocalPos[3], finalRight));

			Axis[0] -= Vector3::Transform(arrLocalPos[0], finalLeft);
			Axis[1] -= Vector3::Transform(arrLocalPos[0], finalLeft);
			Axis[2] -= Vector3::Transform(arrLocalPos[0], finalRight);
			Axis[3] -= Vector3::Transform(arrLocalPos[0], finalRight);
			

			for (size_t i = 0; i < 4; ++i)
				Axis[i].z = 0.f;

			Vector3 vc = leftTr->GetWorldPosition() - rightTr->GetWorldPosition();
			vc.z = 0.f;

			Vector3 centerDir = vc;
			for (size_t i = 0; i < 4; i++)
			{
				Vector3 vObjectAxis = Axis[i];
				//vA.Normalize();

				float projDist = 0.f;
				for (size_t j = 0; j < 4; j++)
				{
					projDist += fabsf(Axis[j].Dot(vObjectAxis) / 2.f);
				}

				if (projDist < fabsf(centerDir.Dot(vObjectAxis)))
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


	#pragma region RectVsLine
		else if (eColliderType::Line == _left->GetType() && eColliderType::Rect == _right->GetType())
		{
			return lineRect(_left, _right);
		}

	#pragma endregion


		return true;
	}
	bool CCollisionMgr::lineLine(Vector2 _lineA_p1, Vector2 _lineA_p2, Vector2 _lineB_p1, Vector2 _lineB_p2)
	{
		// calculate the distance to intersection point
		  // uA의 분모는 직선의 기울기
		  // uA는 선분 A위에 있는 B 즉 A와 B의 교차점이 A선 위의 어느정도 비율인가
		  // (uA가 0.5면 선분 B는 A의 중간지점에서 겹치고 0이면 A의 시작지점에서 겹친다)

		float uA =
			((_lineB_p2.x - _lineB_p1.x) 
				* (_lineA_p1.y - _lineB_p1.y)
				- (_lineB_p2.y - _lineB_p1.y)
				* (_lineA_p1.x - _lineB_p1.x))
				/ ((_lineB_p2.y - _lineB_p1.y)
				* (_lineA_p2.x - _lineA_p1.x)
				- (_lineB_p2.x - _lineB_p1.x) 
				* (_lineA_p2.y - _lineA_p1.y));

		float uB =
			((_lineA_p2.x - _lineA_p1.x)
				* (_lineA_p1.y - _lineB_p1.y)
				- (_lineA_p2.y - _lineA_p1.y) 
				* (_lineA_p1.x - _lineB_p1.x))
				/ ((_lineB_p2.y - _lineB_p1.y) 
				* (_lineA_p2.x - _lineA_p1.x)
				- (_lineB_p2.x - _lineB_p1.x)
				* (_lineA_p2.y - _lineA_p1.y));

		// uA와 uB가 둘 다 0~1사이면 충돌중이다! 
		if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
		{
			return true;
		}
		return false;

	}

	bool CCollisionMgr::lineRect(CCollider2D* _left, CCollider2D* _right)
	{
		Vector3 leftPos = _left->GetColliderPos();
		Vector2 leftScale = _left->GetScale() / 2.f;

		Vector2 lineP1 = {};
		Vector2 lineP2 = {};

		lineP1.x = leftPos.x - leftScale.x;
		lineP2.x = leftPos.x + leftScale.x;
		lineP1.y = leftPos.y;
		lineP2.y = leftPos.y;

		//// 회전
		//float rot = _left->GetOwner()->GetRotation().z;
		//lineP1.


		Vector3 rightPos = _right->GetColliderPos();
		Vector2 rightScale = _right->GetScale() / 2.f;

		Vector2 rectlineP1 = {};
		Vector2 rectlineP2 = {};

		rectlineP1.x = rightPos.x - rightScale.x;
		rectlineP2.x = rightPos.x + rightScale.x;
		rectlineP1.y = rightPos.y + rightScale.y;
		rectlineP2.y = rightPos.y + rightScale.y;

		bool bTop = lineLine(lineP1, lineP2, rectlineP1, rectlineP2);

		rectlineP1.x = rightPos.x - rightScale.x;
		rectlineP2.x = rightPos.x + rightScale.x;
		rectlineP1.y = rightPos.y - rightScale.y;
		rectlineP2.y = rightPos.y - rightScale.y;

		bool bBottom = lineLine(lineP1, lineP2, rectlineP1, rectlineP2);

		rectlineP1.x = rightPos.x - rightScale.x;
		rectlineP2.x = rightPos.x - rightScale.x;
		rectlineP1.y = rightPos.y - rightScale.y;
		rectlineP2.y = rightPos.y + rightScale.y;
		
		bool bLeft = lineLine(lineP1, lineP2, rectlineP1, rectlineP2);
		
		rectlineP1.x = rightPos.x + rightScale.x;
		rectlineP2.x = rightPos.x + rightScale.x;
		rectlineP1.y = rightPos.y - rightScale.y;
		rectlineP2.y = rightPos.y + rightScale.y;
		
		bool bRight = lineLine(lineP1, lineP2, rectlineP1, rectlineP2);


		if (bTop || bBottom || bLeft || bRight)
		{
			return true;
		}

		return false;
	}
}