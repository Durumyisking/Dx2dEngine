#pragma once
#include "LiveGameObj.h"

namespace dru
{
	class CPlayer :
		public CLiveGameObj
	{

	public:
		CPlayer();
		virtual ~CPlayer();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

		virtual void PushFrameCpaturedData();
		virtual void RewindOperate(float _ElapsedTime);
	};
}