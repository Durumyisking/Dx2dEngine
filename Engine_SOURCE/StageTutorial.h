#pragma once
#include "Stage.h"

namespace dru
{
    enum class TutorialStage
    {
        Move,
        Jump_Crouch,
        Roll,
        Attack,
        Wall,
        BulletTime,

        End,
    };

    class CStageTutorial :
        public CStage
    {
    public:
        CStageTutorial();
        virtual ~CStageTutorial();

        virtual void InitStage();
        virtual void LoadAfterReady();
        virtual void Update();

        void TutorialOperation(TutorialStage _Stage);
        void TutorMove();
        void TutorJumpAndCrouch();
        void TutorRoll();
        void TutorAttack();
        void TutorWall();
        void TutorBulletTime();

        void TutorMoveCheck();
        void TutorJumpAndCrouchCheck();
        void TutorRollCheck();
        void TutorAttackCheck();
        void TutorWallCheck();
        void TutorBulletTimeCheck();

        void TutorSuccess(TutorialStage _Stage);
        void TutorReset(TutorialStage _Stage);

    private:
        void LComplete();
        void RComplete();
        void UComplete();
        void DComplete();


    private:
        CGameObj*    mMaskTarget;
        CGameObj*    mCamTarget;

        CBackground* mStageBackground;
        CBackground* mScreenMask;

        CBackgroundColor* mUIBg;
        CGameObj*         mTutorialtxt;

        CGameObj* mTutorBg;
        CGameObj* mTutorBgTarget;

        // keys
        CGameObj* mKeyLeft;
        CGameObj* mKeyRight;
        CGameObj* mKeyUp;
        CGameObj* mKeyDown;
        CGameObj* mKeyShift;
        CGameObj* mKeyEnter;
        CGameObj* mKeyLClick;


        float   mFadeTimer;
        float   mTutorGapTimer;
        bool    mbFadeDone;
        bool    mbZoomDone;
        bool    mbMaskMove;

        bool    mbTutorBgMoveDone;


        UINT    mCount1;
        UINT    mCount2;
        UINT    mCount3;


        TutorialStage mTutorStage;

    };    
}