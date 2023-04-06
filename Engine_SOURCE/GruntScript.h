#pragma once
#include "Script.h"

namespace dru
{
    class CGruntScript :
        public CScript
    {
    public:

        CGruntScript();
        virtual ~CGruntScript();

        virtual void Initialize() override;
        virtual void update() override;
        virtual void fixedUpdate() override;
        virtual void render() override;

        virtual void OnCollisionEnter(CCollider2D* _oppo);
        virtual void OnCollision(CCollider2D* _oppo);
        virtual void OnCollisionExit(CCollider2D* _oppo);
    };
}

