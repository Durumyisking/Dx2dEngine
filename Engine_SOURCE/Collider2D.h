#pragma once
#include "Component.h"
#include "Transform.h"

namespace dru
{
    class CCollider2D :
        public CComponent
    {
    public:
        CCollider2D();
        ~CCollider2D();

        virtual void Initialize();
        virtual void update();
        virtual void fixedUpdate();
        virtual void render();

        virtual void OnCollisionEnter(CCollider2D* _oppo);
        virtual void OnCollision(CCollider2D* _oppo);
        virtual void OnCollisionExit(CCollider2D* _oppo);


        // ���� �ʿ� ���¾� (�浹�� ������ ���� �̺�Ʈ�� �ߵ���ų��)
        virtual void OnTriggerEnter(CCollider2D* _oppo);
        virtual void OnTrigger(CCollider2D* _oppo);
        virtual void OnTriggerExit(CCollider2D* _oppo);

        void SetType(eColliderType _Type) { mType = _Type; }
        eColliderType GetType() const { return mType; }
        void SetCenter(Vector2 _Center) { mCenter = _Center; }
        void SetScale(Vector2 _Scale) { mScale = _Scale; }


        bool IsTrigger() const { return mbTrigger; }
        

    private:
        eColliderType mType;
        CTransform* mTransform;

        Vector2 mScale;
        Vector2 mCenter;
        bool    mbTrigger;

    };
}
