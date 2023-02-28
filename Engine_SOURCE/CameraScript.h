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

    private:
        CCamera* mCameraObject;
    };

}