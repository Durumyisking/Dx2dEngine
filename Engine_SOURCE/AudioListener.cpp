#include "AudioListener.h"
#include "Transform.h"
#include "GameObj.h"
#include "Fmod.h"

namespace dru
{
	CAudioListener::CAudioListener()
		: CComponent(eComponentType::AudioListener)
	{
	}

	CAudioListener::~CAudioListener()
	{
	}

	void CAudioListener::Initialize()
	{
	}

	void CAudioListener::update()
	{
	}

	void CAudioListener::fixedUpdate()
	{
		CTransform* tr = GetOwner()->GetComponent<CTransform>();
		Vector3 pos = tr->GetPosition();
		Vector3 foward = tr->Forward();
		Vector3 up = tr->Up();

		Vector3 vel = { 0.0f, 0.0f, 0.0f };
		CFmod::Set3DListenerAttributes(&pos, &vel, &foward, &up);
	}

	void CAudioListener::render()
	{
	}

}