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
		// Ŭ���� ���ο� �ִ°� ó�� �������� �����Լ��� ���� ��������� �� ���� ����
		static void Initialize();
		static void update();
		static void fixedupdate();
		static void render();
		static void release();

//		CScene* GetActiveScene() const { return mActiveScene; }


	public:
		static CScene* mScenes[(static_cast<UINT>(eSceneType::End))];	// ��� �� ���
		static CScene* mActiveScene;

	};
}

