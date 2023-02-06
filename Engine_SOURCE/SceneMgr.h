#pragma once
#include "Engine.h"
#include "GameObj.h"
namespace dru
{
	class CScene;
	class CSceneMgr
	{
	public:
		enum class eSceneType
		{
			Title,
			Main,

			End,
		};


	public:
		// 클래스 내부에 있는것 처럼 보이지만 전역함수임 따라서 멤버변수를 알 수가 없음
		static void Initialize();
		static void update();
		static void fixedupdate();
		static void render();


	public:
//		static CScene* mScenes[(static_cast<UINT>(eSceneType::End))];	// 모든 씬 목록
		static CScene* mPlayScene;

	};
}

