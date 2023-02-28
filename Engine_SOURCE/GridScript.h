#pragma once
#include "Script.h"
#include "Camera.h"

namespace dru
{
    class CGridScript :
        public CScript
    {
    public:
        CGridScript();
        virtual ~CGridScript();

        virtual void Initialize() override;
        virtual void update() override;
        virtual void fixedUpdate() override;
        virtual void render() override;

        void SetCamera(CCamera* _Camera) { mCamera = _Camera; }

    private:
        CCamera* mCamera;

    };
}

