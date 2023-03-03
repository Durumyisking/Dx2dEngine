#pragma once
#include "Script.h"

namespace dru
{
	class CCursorScript :
		public CScript
	{

	public:
		CCursorScript();
		virtual ~CCursorScript();

		virtual void Initialize() override;
		virtual void update() override;
		virtual void fixedUpdate() override;
		virtual void render() override;

		Vector3 mMousePos;
		Vector3 mPos;
		Vector3 mRot;
	};


}