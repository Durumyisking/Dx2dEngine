#include "LiveGameObj.h"

namespace dru
{
	CLiveGameObj::CLiveGameObj()
		: mFrameCaptureData{}
		, mbRewind(false)
		, mOnStair(false)
		, mMoveDegree(0.f)
	{
	}

	CLiveGameObj::~CLiveGameObj()
	{
		while (!mFrameCaptureData.empty())
		{
			mFrameCaptureData.pop();
		}
	}

	void CLiveGameObj::Initialize()
	{
		for (CComponent* comp : mComponents)
		{
			if (nullptr == comp)
				continue;
			comp->Initialize();
		}

		for (CComponent* script : mScripts)
		{
			if (nullptr == script)
				continue;
			script->Initialize();
		}
	}

	void CLiveGameObj::update()
	{
		if (mbRewind)
		{
			CSceneMain* scene =  dynamic_cast<CSceneMain*>(CSceneMgr::mActiveScene);
			CStage* stage =  scene->GetCurrentStage();	
			RewindOperate(stage->GetElapsedTime());
		}

		for (CComponent* comp : mComponents)
		{
			if (nullptr == comp)
				continue;
			comp->update();
		}
		for (CComponent* script : mScripts)
		{
			if (nullptr == script)
				continue;
			script->update();
		}
	}

	void CLiveGameObj::fixedUpdate()
	{
		for (CComponent* comp : mComponents)
		{
			if (nullptr == comp)
				continue;
			comp->fixedUpdate();
		}

		for (CComponent* script : mScripts)
		{
			if (nullptr == script)
				continue;
			script->fixedUpdate();
		}
	}

	void CLiveGameObj::render()
	{
		for (CComponent* comp : mComponents)
		{
			if (nullptr == comp)
				continue;
			comp->render();
		}

		for (CComponent* script : mScripts)
		{
			if (nullptr == script)
				continue;
			script->render();
		}
	}


}