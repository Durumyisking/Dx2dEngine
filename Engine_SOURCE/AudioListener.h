#pragma once
#include "Component.h"

namespace dru
{
	class CAudioListener : public CComponent
	{
	public:
		CAudioListener();
		~CAudioListener();

		virtual void Initialize() override;
		virtual void update() override;
		virtual void fixedUpdate() override;
		virtual void render() override;

	private:
	};
}
