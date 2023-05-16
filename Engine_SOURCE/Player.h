#pragma once
#include "LiveGameObj.h"

namespace dru
{
	class CAfterImage;
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

	private:
		bool mbPlayerDead;
		CGameObj* mParticle;

	public:
		bool IsPlayerDead() const { return mbPlayerDead; }
		void SetPlayerDead(bool _Value) { mbPlayerDead = _Value; }
	};
}