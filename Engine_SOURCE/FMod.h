#pragma once
#include "Engine.h"
#include "druMath.h"

#include "../External/Fmod/Include/fmod_studio.hpp"
#include "../External/Fmod/Include/fmod.hpp"
#include "../External/Fmod/Include/fmod_common.h"
#include "../External/Fmod/Include/fmod_codec.h"
//#include "..\\External\\Include\\Fmod\\common_platform.h"

#ifdef _DEBUG
#pragma comment(lib, "../External/Fmod/lib/Debug/fmodL_vc.lib")
#pragma comment(lib, "../External/Fmod/lib/Debug/fmodstudioL_vc.lib")
#else
#pragma comment(lib, "../External/Fmod/lib/Release/fmod_vc.lib")
#pragma comment(lib, "../External/Fmod/lib/Release/fmodstudio_vc.lib")
#endif


namespace dru
{
	using namespace math;

	class CFmod
	{
	public:
		static void Initialize();
		static bool CreateSound(const std::string& path, FMOD::Sound** sound);
		static void SoundPlay(FMOD::Sound* sound, FMOD::Channel** channel);
		static void Set3DListenerAttributes(const Vector3* pos, const Vector3* vel, const Vector3* forward, const Vector3* up);
		static void Release();

	private:
		static FMOD::Studio::System* mSystem;
		static FMOD::System* mCoreSystem;
	};
}
