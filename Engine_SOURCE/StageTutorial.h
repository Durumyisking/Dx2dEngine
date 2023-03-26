#pragma once
#include "Stage.h"

namespace dru
{
    class CStageTutorial :
        public CStage
    {
    public:
        CStageTutorial();
        virtual ~CStageTutorial();

        virtual void InitStage();
    };


}