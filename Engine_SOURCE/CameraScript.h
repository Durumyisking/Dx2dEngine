#pragma once
#include "Script.h"
#include "Player.h"

namespace dru
{
    // 흔들림 효과를 위한 구조체
    struct ShakeParams {
        float magnitude;  // 흔들림 크기
        float duration;   // 흔들림 지속 시간
    };

    class CCameraScript :
        public CScript
    {
    public:
        CCameraScript();
        virtual ~CCameraScript();

        virtual void Initialize() override;
        virtual void update() override;
        virtual void fixedUpdate() override;
        virtual void render() override;

        virtual void OnCollisionEnter(CCollider2D* _oppo);
        virtual void OnCollision(CCollider2D* _oppo);
        virtual void OnCollisionExit(CCollider2D* _oppo);

        void KeyBoardMove();
        void TargetMove();
        void Shake(const ShakeParams& params);
        void CancelShake();
        void ShakeMove();

        void FreeViewOn() { mbFreeView = true; }
        void FreeViewOff() { mbFreeView = false; }

        void CamFollowOn() { mbCamFollowPlayerX = true;  mbCamFollowPlayerY = true; }
        void CamFollowOnX() { mbCamFollowPlayerX = true; }
        void CamFollowOnY() { mbCamFollowPlayerY = true; }
        void CamFollowOff() { mbCamFollowPlayerX = false;  mbCamFollowPlayerY = false; }
        void CamFollowOffX() { mbCamFollowPlayerX = false; }
        void CamFollowOffY() { mbCamFollowPlayerY = false; }

        void SetPlayer(CPlayer* _player) { mPlayer = _player; }

        void DirBlockOn(eDir _Dir);
        void AllDirBlockOff();


    private:
        CCamera* mCameraObject;
        CTransform* mTransform;
        CPlayer* mPlayer;
        CGameObj* mTarget;
        Vector3 mLookAt;

        float	mSpeed;
        float	mCamStep;

        bool mbShaking;
        ShakeParams mShakeParams;
        float mShakeTimer;

        std::bitset<static_cast<UINT>(eDir::END)> mDir;
        std::bitset<static_cast<UINT>(eDir::END)> mDirBlock;

        bool mbCamFollowPlayerX;
        bool mbCamFollowPlayerY;

        bool mbFreeView;
    };

}