#pragma once
#include "../Editor_SOURCE/DebugObject.h"
#include "../Editor_SOURCE/EditorObject.h"
#include "../Editor_SOURCE/Widget.h"

namespace dru
{
	class CEditor
	{
	public:
		void Initialize();
		void Run();

		void update();
		void fixedUpdate();
		void render();
		void destroy();

		void debugRender();

	private:
		std::vector<CWidget> mWidgets;
		std::vector<CEditorObject> mEditorObjects;
		std::vector<CDebugObject> mDebugObjects;
	};

}