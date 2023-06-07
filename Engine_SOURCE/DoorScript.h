#pragma once
#include "Script.h"

namespace dru
{
    class CAnimator;
    class CDoorScript :
        public CScript
    {
    public:
        CDoorScript();
        virtual ~CDoorScript();

        virtual void Initialize() override;
        virtual void update() override;
        virtual void fixedUpdate() override;
        virtual void render() override;

        virtual void OnCollisionEnter(CCollider2D* _oppo);
        virtual void OnCollision(CCollider2D* _oppo);
        virtual void OnCollisionExit(CCollider2D* _oppo);

        void Reset();

    private:
        CAnimator* mAnimator;
        CCollider2D* mCollider;

        bool mbOpen;

    };
}
