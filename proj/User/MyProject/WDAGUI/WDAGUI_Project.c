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

#include "WDAGUI_Project.h"
#include "WFGUI_Common.h"

#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x00)
#define ID_EDIT_0 (GUI_ID_USER + 0x01)
#define ID_LISTVIEW_0 (GUI_ID_USER + 0x02)
#define ID_MULTIPAGE_0 (GUI_ID_USER + 0x03)
#define ID_LISTVIEW_1 (GUI_ID_USER + 0x04)
/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
	{ FRAMEWIN_CreateIndirect, "framewin", ID_FRAMEWIN_0, 0, 20, 480, 270, 0, 0x64, 0 },

	//{ EDIT_CreateIndirect, "Edit", ID_EDIT_0, 74, 203, 80, 20, 0, 0x64, 0 },
	//{ LISTVIEW_CreateIndirect, "Listview", ID_LISTVIEW_0, 249, 42, 168, 129, 0, 0x0, 0 },
	//{ MULTIPAGE_CreateIndirect, "Multipage", ID_MULTIPAGE_0, 20, 8, 173, 153, 0, 0x0, 0 },
	//{ LISTVIEW_CreateIndirect, "Listview", ID_LISTVIEW_1, 29, 46, 137, 94, 0, 0x0, 0 },

	// USER START (Optionally insert additional widgets)
	// USER END
};

/**
  * @brief  _cbProject,用户回调函数
  * @param  none
  * @retval none
  */
static void _cbProject(WM_MESSAGE * pMsg)
{
	  HANDLE_LIST *appNode;

	  WM_HWIN hItem;
	  int     NCode;
	  int     Id;
	  // USER START (Optionally insert additional variables)
	  // USER END

	  switch (pMsg->MsgId) {
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
	  case WM_INIT_DIALOG:
		  //
		  // Initialization of 'framewin'
		  //
		  hItem = pMsg->hWin;
		  FRAMEWIN_SetTitleHeight(hItem, 40);
		  FRAMEWIN_SetFont(hItem, GUI_FONT_32B_ASCII);
		  FRAMEWIN_SetText(hItem, "WDA_Builder");
		  FRAMEWIN_SetTextColor(hItem, 0x000000FF);
		  FRAMEWIN_SetTitleVis(hItem, 0);
		  //
		  // Initialization of 'Edit'
		  //
		  hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
		  EDIT_SetText(hItem, "123");
		  //
		  // Initialization of 'Listview'
		  //
		  hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
		  LISTVIEW_AddColumn(hItem, 30, "Col 0", GUI_TA_HCENTER | GUI_TA_VCENTER);
		  LISTVIEW_AddColumn(hItem, 30, "Col 1", GUI_TA_HCENTER | GUI_TA_VCENTER);
		  LISTVIEW_AddColumn(hItem, 30, "Col 2", GUI_TA_HCENTER | GUI_TA_VCENTER);
		  LISTVIEW_AddRow(hItem, NULL);
		  LISTVIEW_SetGridVis(hItem, 1);
		  LISTVIEW_AddColumn(hItem, 30, "Col", GUI_TA_HCENTER | GUI_TA_VCENTER);
		  //
		  // Initialization of 'Multipage'
		  //
		  hItem = WM_GetDialogItem(pMsg->hWin, ID_MULTIPAGE_0);
		  MULTIPAGE_AddEmptyPage(hItem, 0, "Page0");
		  MULTIPAGE_AddEmptyPage(hItem, 0, "Page1");
		  MULTIPAGE_AddEmptyPage(hItem, 0, "Page");
		  //
		  // Initialization of 'Listview'
		  //
		  hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_1);
		  LISTVIEW_AddColumn(hItem, 30, "Col 0", GUI_TA_HCENTER | GUI_TA_VCENTER);
		  LISTVIEW_AddColumn(hItem, 30, "Col 1", GUI_TA_HCENTER | GUI_TA_VCENTER);
		  LISTVIEW_AddColumn(hItem, 30, "Col 3", GUI_TA_HCENTER | GUI_TA_VCENTER);
		  LISTVIEW_AddRow(hItem, NULL);
		  LISTVIEW_SetGridVis(hItem, 1);
		  // USER START (Optionally insert additional code for further widget initialization)
		  // USER END
		  break;
	  case WM_NOTIFY_PARENT:
		  Id    = WM_GetId(pMsg->hWinSrc);
		  NCode = pMsg->Data.v;
		  switch(Id) {
		  case ID_EDIT_0: // Notifications sent by 'Edit'
			  switch(NCode) {
			  case WM_NOTIFICATION_CLICKED:
				  // USER START (Optionally insert code for reacting on notification message)
				  // USER END
				  break;
			  case WM_NOTIFICATION_RELEASED:
				  // USER START (Optionally insert code for reacting on notification message)
				  // USER END
				  break;
			  case WM_NOTIFICATION_VALUE_CHANGED:
				  // USER START (Optionally insert code for reacting on notification message)
				  // USER END
				  break;
				  // USER START (Optionally insert additional code for further notification handling)
				  // USER END
			  }
			  break;
		  case ID_LISTVIEW_0: // Notifications sent by 'Listview'
			  switch(NCode) {
			  case WM_NOTIFICATION_CLICKED:
				  // USER START (Optionally insert code for reacting on notification message)
				  // USER END
				  break;
			  case WM_NOTIFICATION_RELEASED:
				  // USER START (Optionally insert code for reacting on notification message)
				  // USER END
				  break;
			  case WM_NOTIFICATION_SEL_CHANGED:
				  // USER START (Optionally insert code for reacting on notification message)
				  // USER END
				  break;
				  // USER START (Optionally insert additional code for further notification handling)
				  // USER END
			  }
			  break;
		  case ID_MULTIPAGE_0: // Notifications sent by 'Multipage'
			  switch(NCode) {
			  case WM_NOTIFICATION_CLICKED:
				  // USER START (Optionally insert code for reacting on notification message)
				  // USER END
				  break;
			  case WM_NOTIFICATION_RELEASED:
				  // USER START (Optionally insert code for reacting on notification message)
				  // USER END
				  break;
			  case WM_NOTIFICATION_MOVED_OUT:
				  // USER START (Optionally insert code for reacting on notification message)
				  // USER END
				  break;
			  case WM_NOTIFICATION_VALUE_CHANGED:
				  // USER START (Optionally insert code for reacting on notification message)
				  // USER END
				  break;
				  // USER START (Optionally insert additional code for further notification handling)
				  // USER END
			  }
			  break;
		  case ID_LISTVIEW_1: // Notifications sent by 'Listview'
			  switch(NCode) {
			  case WM_NOTIFICATION_CLICKED:
				  // USER START (Optionally insert code for reacting on notification message)
				  // USER END
				  break;
			  case WM_NOTIFICATION_RELEASED:
				  // USER START (Optionally insert code for reacting on notification message)
				  // USER END
				  break;
			  case WM_NOTIFICATION_SEL_CHANGED:
				  // USER START (Optionally insert code for reacting on notification message)
				  // USER END
				  break;
				  // USER START (Optionally insert additional code for further notification handling)
				  // USER END
			  }
			  break;
			  // USER START (Optionally insert additional code for further Ids)
			  // USER END
		  }
		  break;
		  // USER START (Optionally insert additional message handling)
		  // USER END
	  default:
		  WM_DefaultProc(pMsg);
		  break;
	  }
}




/**
  * @brief  WFGUI_Project,用户APP
  * @param  none
  * @retval none
  */
void WDAGUI_Project(void)
{
	/*提示消息：等待您完善更多的应用 */
	HANDLE_LIST *hProject = hAPPLinkedList_NewNode();

	///* 创建电话窗口 */
	//hProject->hAPP = WM_CreateWindowAsChild(
	//	0, 
	//	0, 
	//	WinPara.xSizeWin, 
	//	WinPara.ySizeWin, 
	//	WinPara.hWinMain, WM_CF_SHOW | WM_CF_STAYONTOP, _cbProject, 0
	//	);
	hProject->hAPP = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbProject, WinPara.hWinMain, 0, 0);

	/* 记录当前窗口 */
	/* 添加结点到链表 */
	hAPPLinkedList_AddTail(hProject);

	/* 向ctrl窗口发送消息 */
	WM_SendMessageNoPara(WinPara.hWinCtrl,MY_MESSAGE_CTRLCHANGE);
}
