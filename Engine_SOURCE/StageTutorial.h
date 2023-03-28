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

        void TutorMove();

    private:
        void LComplete();
        void RComplete();


    private:
        CGameObj*    mMaskTarget;
        CGameObj*    mCamTarget;

        CBackground* mStageBackground;
        CBackground* mScreenMask;

        CBackgroundColor* mUIBg;
        CGameObj*         mTutorialtxt;

        CGameObj* mTutorBg;
        CGameObj* mTutorBg1Target;

        // keys
        CGameObj* mKeyLeft;
        CGameObj* mKeyRight;
        CGameObj* mKeyUp;
        CGameObj* mKeyDown;
        CGameObj* mKeyShift;
        CGameObj* mKeyLClick;


        float   mFadeTimer;
        bool    mbFadeDone;
        bool    mbZoomDone;
        bool    mbMaskMove;

        bool    mbTutorBgMoveDone;


        UINT    mT1LCount;
        UINT    mT1RCount;

        TutorialStage mTutorStage;

    };    
}