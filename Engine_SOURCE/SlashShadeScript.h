#pragma once
#include "Script.h"

namespace dru
{
    class CSlashShadeScript :
        public CScript
    {
    public:
        CSlashShadeScript();
        virtual ~CSlashShadeScript();

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

    private:
        CTransform* mTrans;
        Vector3 mPos;
        Vector3 mRot;
        Vector3 mDir;
        bool mbStart;

    };
}