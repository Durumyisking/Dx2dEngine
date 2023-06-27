#pragma once
#include "LiveGameObj.h"

namespace dru
{
	class CAfterImage;
	class CHorizonGauge;
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
		virtual void fontRender();
		virtual void rewindRender();

		void AddBlockGauge();
		void PlayGauge();

		void Hit(Vector3& _enemyPos, int _Type);

	private:
		bool mbPlayerDead;
		CHorizonGauge* mBlockGauge;

	public:
		bool IsPlayerDead() const { return mbPlayerDead; }
		void SetPlayerDead(bool _Value) { mbPlayerDead = _Value; }
		void SetPlayerStun();

	};
}