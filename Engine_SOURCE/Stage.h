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
#include "Boss.h"
#include "Grunt.h"
#include "Cop.h"
#include "Kissyface.h"

#include "Turret.h"

#include "GridScript.h"
#include "FadeScript.h"
#include "CursorScript.h"
#include "MaskScript.h"

#include "Animator.h"

#include "Floor.h"
#include "Floor2.h"
#include "Wall.h"
#include "Ceiling.h"
#include "OutWall.h"
#include "OutWallSide.h"
#include "Stair.h"

#include "LightObject.h" 

#include "BackgroundColorScript.h"
#include "FadeScript.h"
#include "PlayerScript.h"
#include "BossScript.h"

#include "PostProcess.h"
#include "PostProcessWave.h"


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

     
        virtual void NotReadyOperate();
        virtual void ReadyOperate();
        virtual void ReadyEndOperate();
        virtual void LoadUIOperate();
        virtual void LoadEndOperate();
        void         ClearOperate();

        virtual void Reset();
        virtual void AddStartingLiveObjects();

        void LoadUI();
        void LoadKeyUI();

        void SetOwner(CScene* _scene)
        {
            mScene = _scene;
        }

        eStageState GetReadyState() { return mStageState; }
        void SetReady(eStageState _State) { mStageState = _State; }


        void BulletTimeBatteryOperation();

        void CreateDeadUI();

        void TimerBarOperate();
        void TimerBarScaling(float _Ratio);

        bool GetPlayerState(ePlayerState _State);
        
        void CreatePostProcess_Rewind();
        void CreatePostProcess_Replay();
        void CreatePostProcess_Snow();

        void RewindStart();
        void Rewinding();
        bool RewindEndCheck();
        void RewindEnd();

        void ReplayStart();
        void Replaying();
        bool ReplayEndCheck();
        void ReplayEnd();


        void DeadReset();

        float GetElapsedTime() const { return mElapsedTime; };

        void SetClearCollider(Vector3 _Pos);

        void SetClearOn() 
        {
            if (0 == mEnemyCount)
            {
                mbClear = true;
            }
        }
        void SetClearOff() { mbClear = false; }

        void MonsterDead()
        {
            --mEnemyCount; 
        }
        UINT GetEnemyCount() const { return mEnemyCount; }

        void CamReset();

        static void KeyUI_LeftOn(Vector3 _Pos);
        static void KeyUI_RightOn(Vector3 _Pos);
        static void KeyUI_UpOn(Vector3 _Pos);
        static void KeyUI_DownOn(Vector3 _Pos);
        static void KeyUI_ShiftOn(Vector3 _Pos);
        static void KeyUI_LClickOn(Vector3 _Pos);

        static void KeyUI_LeftOff();
        static void KeyUI_RightOff();
        static void KeyUI_UpOff();
        static void KeyUI_DownOff();
        static void KeyUI_ShiftOff();
        static void KeyUI_LClickOff();

        // keys
        static CGameObj* mKeyLeft;
        static CGameObj* mKeyRight;
        static CGameObj* mKeyUp;
        static CGameObj* mKeyDown;
        static CGameObj* mKeyShift;
        static CGameObj* mKeyLClick;


    protected:
        CBackground* mStageBackground;


        CScene* mScene;
        bool mbClear;
        CGameObj* mClearCollider;

        CPostProcess* mPostProcess_Rewind;
        CPostProcess* mPostProcess_Replay;
        CPostProcess* mPostProcess_Snow;

        CBackgroundColor* mDeadBg;
        bool mbIsDeadBgOn;

        CPlayer* mPlayer;
        Vector3 mPlayerDefaultPos;


        CGameObj* mUICursor;


        std::vector<CGameObj*> mHudBatteryParts;
        CGameObj* mHudTimerBar;
        CGameObj* mHudLeftHand;
        CGameObj* mHudRightHand;

        CBackgroundColor* mBulletTimeMask;

        eStageState mStageState;

        UINT mBulletTimeGaugePrev;
        UINT mBulletTimeGaugeCurrent;

        Vector3 mDefaultTimerBarPos;
        Vector3 mDefaultTimerBarScale;
        float mTimer;
        float mElapsedTime;

        bool mbRewinding;
        bool mbReplaying;
        float mRewindTimer;

        UINT mEnemyCount;

        std::vector<CLiveGameObj*> mRewindObjects;


    private:
        CGameObj* mKeyEnter;

    };
}

