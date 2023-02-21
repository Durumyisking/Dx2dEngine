#pragma once
#include "GameObj.h"

namespace dru
{
    class CBackground :public CGameObj
    {
	public:
		CBackground();
		virtual ~CBackground();

		virtual void Initialize();
		virtual void update();
		virtual void fixedupdate();
		virtual void render();


	private:
		CSpriteRenderer*			mSpriteRenderer;

		std::shared_ptr<CMesh>		mMesh;
//		std::shared_ptr<CShader>	mSpriteShader;


    };
}