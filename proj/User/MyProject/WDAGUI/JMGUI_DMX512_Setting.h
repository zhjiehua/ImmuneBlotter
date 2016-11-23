#ifndef __DMX512_H
#define __DMX512_H
	
#include "WFGUI_Common.h"

#include "DIALOG.h"
#include "WM.h"

typedef struct
{
  int          xPos;
  int          yPos;
  int          xSize;
  int          ySize;
  char * 	   acLabel;
  int		   Id;
  GUI_COLOR	   bkColor;
}Edit_TypeDef;


/*DMX512 Ù–‘*/
typedef struct
{
	uint32_t Addr;
	uint32_t LampNum;
	uint32_t ChannelNum;
}DMX512_TypeDef;

extern DMX512_TypeDef DMX512_Attr;

void JMGUI_DMX512_Setting(void);

#endif
