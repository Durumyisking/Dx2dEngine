#pragma once

#include "TimeMgr.h"
#include "Object.h"
#include "Camera.h"
#include "Input.h"
#include "Collider2D.h"
#include "CollisionMgr.h"
#include "RigidBody.h"
#include "Light.h"

#include "Background.h"
#include "Player.h"
#include "Monster.h"
#include "Grunt.h"

#include "GridScript.h"
#include "FadeScript.h"
#include "CursorScript.h"
#include "MaskScript.h"

#include "Animator.h"

#include "Floor.h"
#include "Wall.h"
#include "Ceiling.h"
#include "OutWall.h"
#include "OutWallSide.h"

#include "BackgroundColorScript.h"
#include "FadeScript.h"
#include "PlayerScript.h"


namespace dru
{
    enum class eStageState
    {
        NotReady,
        Ready, // 이때 ready 호출
        ReadyEnd,
        LoadUI,
        LoadEnd,
        End,
    };

	class CStage
	{
    public:
        CStage();
        virtual ~CStage();

        virtual void InitStage() = 0;
        virtual void LoadinReady() = 0;
        virtual void Update();
        virtual void Exit();

        void LoadUI();
        void SetOwner(CScene* _scene) { mScene = _scene; }

        eStageState GetReadyState() { return mStageState; }
        void SetReady(eStageState _State) { mStageState = _State; }

        virtual void NotReadyOperate();
        virtual void ReadyOperate();
        virtual void ReadyEndOperate();
        virtual void LoadUIOperate();
        virtual void LoadEndOperate();

        virtual void Reset() = 0;

        void BulletTimeBatteryOperation();

        

    protected:
        CScene* mScene;
        CBackgroundColor* mDeadBg;
        bool mbIsDeadBgOn;

        CPlayer* mPlayer;
        Vector3 mPlayerDefaultPos;


        CGameObj* mUICursor;

        std::vector<CGameObj*> mHudBatteryParts;
        CGameObj* mHudTimerBar;
        CGameObj* mHudLeftHand;
        CGameObj* mHudRightHand;

        eStageState mStageState;

        UINT mBulletTimeGaugePrev;
        UINT mBulletTimeGaugeCurrent;

    private:
        CGameObj* mKeyEnter;

    };
}

