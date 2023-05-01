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
			Mission,


			Temp,
			End,
		};


	public:
		// 클래스 내부에 있는것 처럼 보이지만 전역함수임 따라서 멤버변수를 알 수가 없음
		static void Initialize();
		static void update();
		static void fixedUpdate();
		static void render();
		static void destory();
		static void release();
		static void LoadScene(eSceneType _Type);

		static void DontDestroyOnLoad(CGameObj* _GameObj);

		template <typename T>
		static T* GetScene (eSceneType _Type)
		{
			return dynamic_cast<T*>(mScenes[(static_cast<UINT>(_Type))]);
		}

	public:
		static CScene* mScenes[(static_cast<UINT>(eSceneType::End))];	// 모든 씬 목록
		static CScene* mActiveScene;

	};
}

