#pragma once
#include "LiveGameObj.h"

#define SINGLE_LASER_GAP 0.2833f
#define SINGLE_LASER_LIFETIME_GAP 0.755f

namespace dru
{
	class CFloor;
	class CTurret :
		public CLiveGameObj
	{
	public:
		CTurret();
		virtual ~CTurret();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

		void ChangeBeamPos(Vector3 _Pos);
		void ChangeBeamSize(float _ScaleY);
		Vector3 GetBeamWorldPos() const { return mBeam->GetWorldPos(); }

		void SetDestinationFloor(CFloor* _Floor) { mDestinationFloor = _Floor; }
		void AdjustLaserTransform();
		void AdjustAimParticle();

		float GapBetweenFloorAndTurret();

	private:
		void MakeBeam();
		void InitializeParticleSystem();

		CGameObj* mBeam;
		CGameObj* mParticle;

		CFloor* mDestinationFloor;
	};
}

