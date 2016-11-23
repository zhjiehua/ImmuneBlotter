/**
  ******************************************************************************
  * @file    WDAGUI_Project.c
  * @author  zhjiehua
  * @version V1.0
  * @date    2016-xx-xx
  * @brief   用户APP文件
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#include "WDAGUI_Purge.h"
#include "WFGUI_Common.h"

WM_HWIN CreateWindow(void);

/**
  * @brief  _cbProject,用户回调函数
  * @param  none
  * @retval none
  */
static void _cbPurge(WM_MESSAGE * pMsg)
{
	
	WM_HWIN hWin;
	int xSize,ySize;
    HANDLE_LIST *appNode;

	
	
	hWin = pMsg->hWin;
	  switch (pMsg->MsgId) {
	  case WM_CREATE:
			
//			CreateWindow();
	  break; 
	  case WM_DELETE:
	     /* 获取app句柄对应的链表结点 */
		appNode = hAPPLinkedList_GetAppNode(pMsg->hWin);
		if(appNode != NULL)
		{
			/* 删除app句柄链表里的记录 */	
			hAPPLinkedList_Del(appNode);
		
			/* 发送消息通知ctrl窗口*/		
			WM_SendMessageNoPara(WinPara.hWinCtrl,MY_MESSAGE_CTRLCHANGE);	
		}
	    
	  break;	
	  case WM_PAINT:
		//
	    // Draw background
	    //
	    xSize = WM_GetWindowSizeX(hWin);
	    ySize = WM_GetWindowSizeY(hWin);
	    GUI_SetColor(GUI_WHITE);
		
		GUI_FillRect(0,0,xSize,ySize);
		
	  break;
	}	
}




/**
  * @brief  WFGUI_Project,用户APP
  * @param  none
  * @retval none
  */
void WDAGUI_Purge(void)
{
	/*提示消息：等待您完善更多的应用 */
	HANDLE_LIST *hProject = hAPPLinkedList_NewNode();
	
	/* 创建电话窗口 */
	hProject->hAPP = WM_CreateWindowAsChild(
		0, 
		0, 
		WinPara.xSizeWin, 
		WinPara.ySizeWin, 
		WinPara.hWinMain, WM_CF_SHOW | WM_CF_STAYONTOP, _cbPurge, 0);	
	
	/* 记录当前窗口 */
	/* 添加结点到链表 */
	hAPPLinkedList_AddTail(hProject);
	/* 向ctrl窗口发送消息 */
	WM_SendMessageNoPara(WinPara.hWinCtrl,MY_MESSAGE_CTRLCHANGE);
	
	/* show sorry */
	MESSAGEBOX_Create("there is no Purge","sorry",GUI_MESSAGEBOX_CF_MODAL);
}
