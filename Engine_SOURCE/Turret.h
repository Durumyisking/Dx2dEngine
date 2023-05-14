#pragma once
#include "LiveGameObj.h"


namespace dru
{
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

	private:
		void MakeBeam();

		CGameObj* mBeam;

	};
}

