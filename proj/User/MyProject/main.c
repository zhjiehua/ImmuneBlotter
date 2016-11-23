/*
 *	
 */

#include "GUI.h"
#include "DIALOG.h"
#include "stdio.h"
#include "wfgui_common.h"

WM_HWIN CreateFramewin(void);

extern void WFGUI_MainTask(void);

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {

  GUI_Init();

  //GUI_DispString("Hello world!");
  //CreateFramewin();
  WFGUI_MainTask();

  //while(1)
  //{
	 // GUI_Delay(35);
  //}
}

/*************************** End of file ****************************/