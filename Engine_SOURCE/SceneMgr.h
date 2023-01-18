#pragma once
#include "Engine.h"

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
		CSceneMgr();
		~CSceneMgr();

	public:
		// Ŭ���� ���ο� �ִ°� ó�� �������� �����Լ��� ���� ��������� �� ���� ����
		static void init();
		static void update();
		static void fixedupdate();
		static void render();


	private:
		static CScene* mScenes[(static_cast<UINT>(eSceneType::End))];	// ��� �� ���
		static CScene* mPlayScene;

	};
}

