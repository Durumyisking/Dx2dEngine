#pragma once
#include "Entity.h"
#include "Layer.h"

namespace dru
{
	class CScene : public CEntity // 이름과 고유 id를 가진 class
	{
	public:
		CScene();
		virtual ~CScene();

		virtual void init();
		virtual void update();
		virtual void fixedupdate();
		virtual void render();

	private:
		std::vector<CLayer> mLayers;

	};

}

