#pragma once
#include "Script.h"

namespace dru
{
    class CMaskScript :
        public CScript
    {
        public:
            CMaskScript();
            virtual ~CMaskScript();

            virtual void Initialize() override;
            virtual void update() override;
            virtual void fixedUpdate() override;
            virtual void render() override;

        void GoDown() { mbGoDown = true; }
        bool MoveDone() { return mbMoveDone; }

        void SetTarget(CTransform* _tr) { mTargetTransform = _tr; }

    private:
        bool mbMoveDone;
        bool mbGoDown;
        CTransform* mTargetTransform;

        float mSpeed;
        float mStep;
    };

}
