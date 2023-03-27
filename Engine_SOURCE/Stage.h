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

namespace dru
{
    enum class eReadyState
    {
        NotReady,
        Ready,
        ReadyEnd,
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
     
        void LoadUI();
        void SetOwner(CScene* _scene) { mOwner = _scene; }

        eReadyState GetReadyState() { return mReady; }
        void SetReady(eReadyState _State) { mReady = _State; }

    protected:
        CScene* mOwner;

        std::vector<CGameObj*> mHudBatteryParts;
        CGameObj* mHudTimerBar;
        CGameObj* mHudLeftHand;
        CGameObj* mHudRightHand;

        eReadyState mReady;
	};
}

