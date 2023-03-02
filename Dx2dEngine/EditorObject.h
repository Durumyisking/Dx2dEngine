#pragma once
#include "GameObj.h"

namespace dru
{
    class CEditorObject :
        public CGameObj
    {
	public:
		CEditorObject();
		virtual ~CEditorObject();

		virtual void Initialize();
		virtual void update();
		virtual void fixedUpdate();
		virtual void render();

    };

}