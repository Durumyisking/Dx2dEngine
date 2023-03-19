#pragma once
#include "Component.h"
#include "Collider2D.h"

namespace dru
{
	class CScript : public CComponent
	{
	public:
		CScript();
		virtual ~CScript();

		virtual void Initialize() override;
		virtual void update() override;
		virtual void fixedUpdate() override;
		virtual void render() override;

		virtual void OnCollisionEnter(CCollider2D* _oppo) {};
		virtual void OnCollision(CCollider2D* _oppo) {};
		virtual void OnCollisionExit(CCollider2D* _oppo) {};

		virtual void OnTriggerEnter(CCollider2D* _oppo) {};
		virtual void OnTrigger(CCollider2D* _oppo) {};
		virtual void OnTriggerExit(CCollider2D* _oppo) {};

		void MakeSlash(const std::wstring& _TextureName, UINT _AnimSize, Vector2 _Ratio);

	};
}


