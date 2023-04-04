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


namespace dru
{
    enum class eReadyState
    {
        NotReady,
        Ready,
        ReadyEnd,
        LoadEnd,
        End,
    };

	class CStage
	{
    public:
        CStage();
        virtual ~CStage();

        virtual void InitStage() = 0;
        virtual void LoadAfterReady() = 0;
        virtual void Update();
        virtual void Exit();

        void LoadUI();
        void SetOwner(CScene* _scene) { mScene = _scene; }

        eReadyState GetReadyState() { return mReady; }
        void SetReady(eReadyState _State) { mReady = _State; }

        void Reset();

        void BulletTimeBatteryOperation();

    protected:
        CScene* mScene;

        CPlayer* mPlayer;

        CGameObj* mUICursor;

        std::vector<CGameObj*> mHudBatteryParts;
        CGameObj* mHudTimerBar;
        CGameObj* mHudLeftHand;
        CGameObj* mHudRightHand;

        eReadyState mReady;

        UINT mBulletTimeGaugePrev;
        UINT mBulletTimeGaugeCurrent;

    };
}

