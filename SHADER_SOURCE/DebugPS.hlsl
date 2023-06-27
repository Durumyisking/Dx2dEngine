#include "global.hlsli"

#define COLLISION_NOT   0
#define COLLISION_ENTER 1
#define COLLISION_STAY  2
#define COLLISION_EXIT  3
#define COLLISION_OFF   4

float4 main() : SV_TARGET
{	
 float4 Out = MAGENTA;
    switch (cbiData1)
    {
        case COLLISION_NOT :
            Out = GREEN;
            break;
        case COLLISION_ENTER:
            Out = BLUE;
            break;
        case COLLISION_STAY:
            Out = RED;
            break;
        case COLLISION_OFF:
            Out = ZERO;
            break;
        case COLLISION_EXIT:
            Out = WHITE;
            break;
        default :
            Out = MAGENTA;
            break;
    }

    //discard;
    
    return Out;

}