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
			RewindOperate();
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