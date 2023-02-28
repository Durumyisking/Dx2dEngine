#pragma once
#include "Component.h"

namespace dru
{
	class CScript : public CComponent
	{
	public:
		CScript();
		virtual ~CScript();

		virtual void Initialize() override;
		virtual void update() override;
		virtual void fixedUpdate() override;
		virtual void render() override;


	private:


	};
}


