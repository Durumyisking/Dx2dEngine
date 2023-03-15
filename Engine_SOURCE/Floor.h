#pragma once
#include "GameObj.h"


namespace dru
{
	class CFloor :
		public CGameObj
	{
	public:
		CFloor();
		virtual ~CFloor();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();


		void SetColliderScale(Vector2 _Scale);
	};


}

