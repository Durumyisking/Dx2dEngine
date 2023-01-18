#include "Scene.h"
#include "Input.h"

namespace dru
{
	CScene::CScene()
	{
	}
	CScene::~CScene()
	{
	}
	void CScene::init()
	{
	}

	void CScene::update()
	{
		if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
		{
			return;
		}
	}

	void CScene::fixedupdate()
	{
	}

	void CScene::render()
	{
	}

}