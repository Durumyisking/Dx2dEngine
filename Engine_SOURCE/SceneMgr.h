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
			End,
		};


	public:
		// Ŭ���� ���ο� �ִ°� ó�� �������� �����Լ��� ���� ��������� �� ���� ����
		static void Initialize();
		static void update();
		static void fixedUpdate();
		static void render();
		static void destory();
		static void release();
		static void LoadScene(eSceneType _Type);

		static void DontDestroyOnLoad(CGameObj* _GameObj);


	public:
		static CScene* mScenes[(static_cast<UINT>(eSceneType::End))];	// ��� �� ���
		static CScene* mActiveScene;

	};
}

