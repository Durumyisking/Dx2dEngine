#pragma once
#include "Script.h"

namespace dru
{
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

        void CamFollowOn() { mbCamFollowPlayerX = true;  mbCamFollowPlayerY = true; }
        void CamFollowOnX() { mbCamFollowPlayerX = true; }
        void CamFollowOnY() { mbCamFollowPlayerY = true; }
        void CamFollowOff() { mbCamFollowPlayerX = false;  mbCamFollowPlayerY = false; }
        void CamFollowOffX() { mbCamFollowPlayerX = false; }
        void CamFollowOffY() { mbCamFollowPlayerY = false; }

        void SetPlayer(CPlayer* _player) { mPlayer = _player; }

    private:
        CCamera* mCameraObject;
        CPlayer* mPlayer;

        std::bitset<static_cast<UINT>(eDir::END)> mDir;
        std::bitset<static_cast<UINT>(eDir::END)> mDirBlock;

        bool mbCamFollowPlayerX;
        bool mbCamFollowPlayerY;

    };

}