#pragma once
#include "Monster.h"

namespace dru
{
	class CHorizonGauge;
	class CPlayer;
    class CPomp :
        public CMonster
    {
	public:
		CPomp();
		virtual ~CPomp();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();
		virtual void rewindRender();
	
		void AddBlockGauge();
		void PlayGauge();

		void SetPlayer(CPlayer* _Player) { mPlayer = _Player; }
		CPlayer* GetPlayer() const { return mPlayer;  }

	private:
		Vector2 mAnimOffset;
		CHorizonGauge* mBlockGauge;
		CPlayer* mPlayer;
	};
}
