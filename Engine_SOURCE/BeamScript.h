#pragma once
#include "Script.h"

namespace dru
{
    class CBeamScript :
        public CScript
    {
	public:
		CBeamScript();
		virtual ~CBeamScript();

		virtual void Initialize() override;
		virtual void update() override;
		virtual void fixedUpdate() override;
		virtual void render() override;

		virtual void OnCollisionEnter(CCollider2D* _oppo);
		virtual void OnCollision(CCollider2D* _oppo);
		virtual void OnCollisionExit(CCollider2D* _oppo);

		void SetBeam(CGameObj* _Beam) { mBeam = _Beam; }
		void Reset() { mbLaserShooted = false; }

	private:
		CGameObj* mBeam;
		CAudioSource* mAudioSource;

		bool mbLaserShoot;
		bool mbLaserShooted;

		float mLaserOperateTimer;

    };
}

