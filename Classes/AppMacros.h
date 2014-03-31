#ifndef __APPMACROS_H__
#define __APPMACROS_H__

#include "cocos2d.h"

#define DESIGN_RESOLUTION_1200X800   0
#define TARGET_DESIGN_RESOLUTION_SIZE  DESIGN_RESOLUTION_1200X800

typedef struct tagResource
{
    cocos2d::CCSize size;
    char directory[100];
}Resource;

//static Resource smallResource  =  { cocos2d::CCSizeMake(480, 320),   "iphone" };
static Resource mediumResource =  { cocos2d::CCSizeMake(1200, 800),  "nexus7" };
//static Resource largeResource  =  { cocos2d::CCSizeMake(2048, 1536), "ipadhd" };

//#if (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_480X320)
//static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(480, 320);

//#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_1024X768)
#if (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_1200X800)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(1200, 800);

//#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_2048X1536)
//static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(2048, 1536);
#else
#error unknown target design resolution!
#endif

#endif /* __APPMACROS_H__ */
