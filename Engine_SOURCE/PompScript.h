#pragma once
#include "MonsterScript.h"

namespace dru
{
    class CPompScript :
        public CMonsterScript
    {
    public:

        CPompScript();
        virtual ~CPompScript();

        virtual void Initialize() override;
        virtual void update() override;
        virtual void fixedUpdate() override;
        virtual void render() override;

        virtual void attack();

        virtual void OnCollisionEnter(CCollider2D* _oppo);
        virtual void OnCollision(CCollider2D* _oppo);
        virtual void OnCollisionExit(CCollider2D* _oppo);

        virtual void SetMonsterAttack();

        void PushPlayer();


    private:
        CAnimator* mAnimator;

        float mBlockTimer;
        bool mbCanBlock;
    };

}
