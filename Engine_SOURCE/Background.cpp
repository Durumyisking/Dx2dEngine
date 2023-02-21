#include "Background.h"

namespace dru
{
	CBackground::CBackground()
	{
		mSpriteRenderer = new CSpriteRenderer();
		this->AddComponent(mSpriteRenderer);

		mMesh = CResources::Find<CMesh>(L"RectMesh");
		mSpriteRenderer->SetMesh(mMesh);

//		mSpriteShader = CResources::Find<CShader>(L"SpriteShader");

	}

	CBackground::~CBackground()
	{
	}

	void CBackground::Initialize()
	{

		CGameObj::Initialize();
	}

	void CBackground::update()
	{
		CGameObj::update();
	}

	void CBackground::fixedupdate()
	{
		CGameObj::fixedupdate();
	}

	void CBackground::render()
	{
		CGameObj::render();
	}

}