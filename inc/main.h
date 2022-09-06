#ifndef __DEF_EFL_Border_Sample_H__
#define __DEF_EFL_Border_Sample_H__

#include <dlog.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "BorderSample"

#define BODER_EDJ "/usr/apps/EFL-Border-Sample/res/EFL-Border-Sample.edj"

typedef struct _appdata
{
    Evas_Object *win;
    Evas_Object *bx;
    Evas_Object *bx2;
    Evas_Object *border;

} appdata;

#endif

