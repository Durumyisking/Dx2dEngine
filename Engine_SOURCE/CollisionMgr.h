#pragma once
#include "CommonInclude.h"
#include "Collider2D.h"

namespace dru
{
	union ColliderID
	{
		struct
		{
			UINT32 left;
			UINT32 right;
		};
		UINT64 id;
	};

	class CCollisionMgr
	{
	public:
		static void Initialize();
		static void update();
		static void fixedUpdate();
		static void render();

		static void CollisionLayerCheck(eLayerType _left, eLayerType _right, bool _benable = true);
		static void LayerCollision(class CScene* _scene, eLayerType _left, eLayerType _right);
		static void ColliderCollision(CCollider2D* _left, CCollider2D* _right);
		static bool Intersect(CCollider2D* _left, CCollider2D* _right);

		static bool lineLine(Vector2 _lineA_p1, Vector2 _lineA_p2, Vector2 _lineB_p1, Vector2 _lineB_p2);
		static bool lineRect(CCollider2D* _left, CCollider2D* _right);

	private:
		static std::bitset<static_cast<UINT>(eLayerType::End)> mLayerCollisionMatrix[static_cast<UINT>(eLayerType::End)];
		static std::map<UINT64, bool> mCollisionMap;

	};
}
