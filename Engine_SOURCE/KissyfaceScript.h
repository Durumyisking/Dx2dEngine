#pragma once
#include "BossScript.h"

namespace dru
{
    class CKissyfaceScript :
        public CBossScript
    {
    public:
        CKissyfaceScript();
        virtual ~CKissyfaceScript();

        virtual void Initialize() override;
        virtual void update() override;
        virtual void fixedUpdate() override;
        virtual void render() override;

        virtual void attack();

        virtual void OnCollisionEnter(CCollider2D* _oppo);
        virtual void OnCollision(CCollider2D* _oppo);
        virtual void OnCollisionExit(CCollider2D* _oppo);


        void ChoosePattern();

        // animation Callback
        void waitingEndComplete();


    };
}
