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


	private:
		CTransform* mTrans;
		Vector3 mPos;
		Vector3 mRot;

	};


}