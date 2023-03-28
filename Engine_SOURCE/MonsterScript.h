#pragma once
#include "Script.h"

namespace dru
{
    enum class eMonsterState
    {
        Idle, //0
        Run,// 2
        Attack,// 5 
        Fall,// 11
        Die,

        End,
    };

    class CMonsterScript :
        public CScript
    {
    public:
        CMonsterScript();
        virtual ~CMonsterScript();

        virtual void Initialize() override;
        virtual void update() override;
        virtual void fixedUpdate() override;
        virtual void render() override;

        virtual void OnCollisionEnter(CCollider2D* _oppo);
        virtual void OnCollision(CCollider2D* _oppo);
        virtual void OnCollisionExit(CCollider2D* _oppo);

        virtual void OnTriggerEnter(CCollider2D* _oppo);
        virtual void OnTrigger(CCollider2D* _oppo);
        virtual void OnTriggerExit(CCollider2D* _oppo);


        CAnimator* mAnimator;
        CRigidBody* mRigidbody;
        CTransform* mTransform;
        Vector3 mPos;


        bool mbOnWall;


        std::bitset<static_cast<UINT>(eMonsterState::End)> mState;

    };

}
