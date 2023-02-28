#pragma once
#include "../Engine_SOURCE/GameObj.h"

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