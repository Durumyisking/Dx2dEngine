#pragma once
#include "GameObj.h"

namespace dru
{
    class CHorizonGauge :
        public CGameObj
    {
	public:
		CHorizonGauge();
		virtual ~CHorizonGauge();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

		void Play();
		void SetTimer(float _Timer);

    };
}


