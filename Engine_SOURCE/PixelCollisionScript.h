#pragma once
#include "Script.h"
#include "../External/DirectXTex/include/DirectXTex.h"
#include "GraphicDevice.h"
#include "Texture.h"

namespace dru
{
    class CPlayer;

    class CPixelCollisionScript :
        public CScript
    {
    public:
        CPixelCollisionScript();
        virtual ~CPixelCollisionScript();

        virtual void Initialize() override;
        virtual void update() override;
        virtual void fixedUpdate() override;
        virtual void render() override;

        void SetImage(const std::wstring& key);

        CPlayer* mPlayer;

    private:
        ScratchImage* mImage;

    };

}