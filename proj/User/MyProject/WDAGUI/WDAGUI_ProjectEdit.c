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

#include "WDAGUI_ProjectEdit.h"
#include "WFGUI_Common.h"
#include "WDAProEdit.h"
#include "WDAGUI_Action.h"

static uint8_t projSel;
static uint8_t actSel;
static uint8_t flagProjAct;//0表示project;1表示action

PROEDIT_MAN *pCurProj;//当前项目
ACTEDIT_MAN *pCurAct;//当前动作


static void _cbAction(WM_MESSAGE * pMsg)
{
	WM_HWIN hWin;
	int xSize,ySize;
	HANDLE_LIST *appNode;

	hWin = pMsg->hWin;
	switch (pMsg->MsgId) {
	case WM_CREATE:
		createAction(hWin);
		flagProjAct = 2;//标记进入action页面
		break;
	case WM_NOTIFY_PARENT:

		cbActionNotifyParent(pMsg);

		break;
	case WM_DELETE:
		/* 获取app句柄对应的链表结点 */
		appNode = hAPPLinkedList_GetAppNode(pMsg->hWin);
		if(appNode != NULL)
		{
			/* 删除app句柄链表里的记录 */
			hAPPLinkedList_Del(appNode);

			flagProjAct = 1;//标记进入actionshow页面
		}
		break;

	case WM_PAINT:
		//
		// Draw background
		//
		xSize = WM_GetWindowSizeX(hWin);
		ySize = WM_GetWindowSizeY(hWin);
		GUI_SetColor(GUI_GRAY);

		GUI_FillRect(0,0,xSize,ySize);	
		break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}	
}

static void _cbActionShow(WM_MESSAGE * pMsg)
{
	uint8_t i, j;
	WM_HWIN hWin, hWin_Temp;
	int xSize,ySize;
	HANDLE_LIST *appNode;
	int Id, NCode;

	hWin = pMsg->hWin;
	switch (pMsg->MsgId) {
	case WM_CREATE:
		//往project窗口添加button控件
		{
			struct list_head *pos;
			PROEDIT_MAN *node;

			i = 0;
			j = 0;

			list_for_each(pos,&pCurProj->hActHead)
			{
				/* TBD 这里有个warning，不知道影响大不大*/
				node = list_entry(pos,PROEDIT_MAN,listNode);

				hWin_Temp = BUTTON_CreateEx(
					WinPara.xSizeWin*i/3,
					WinPara.ySizeWin*j/10,
					WinPara.xSizeWin/3,
					WinPara.ySizeWin/10,
					hWin,
					WM_CF_SHOW,
					0,
					GUIID_ACTION+3*j+i
					);
				BUTTON_SetText(hWin_Temp, node->name);
				DEBUG("\r\n node->name =%s \r\n ",node->name);

				i++;
				if(i >= 3 )
				{
					i = 0;
					j++;
				}
			}
		}
		flagProjAct = 1;//标记进入actionshow页面
		break;
	case WM_NOTIFY_PARENT:
		Id    = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;

		switch(NCode) {
		case WM_NOTIFICATION_RELEASED:
			actSel = Id - GUIID_ACTION;
			break;
		}
		break;
	case WM_DELETE:
		/* 获取app句柄对应的链表结点 */
		appNode = hAPPLinkedList_GetAppNode(pMsg->hWin);
		if(appNode != NULL)
		{
			/* 删除app句柄链表里的记录 */	
			hAPPLinkedList_Del(appNode);

			flagProjAct = 0;//标记退回projectshow页面
		}	    
		break;

	case WM_PAINT:
		//
		// Draw background
		//
		xSize = WM_GetWindowSizeX(hWin);
		ySize = WM_GetWindowSizeY(hWin);
		GUI_SetColor(GUI_GRAY);

		GUI_FillRect(0,0,xSize,ySize);	
		break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}

/**
  * @brief  _cbProject,用户回调函数
  * @param  none
  * @retval none
  */
static void _cbProjectShow(WM_MESSAGE * pMsg)
{
	uint8_t i, j;
	WM_HWIN hWin, hWin_Temp;
	int xSize,ySize;
	int Id, NCode;

	hWin = pMsg->hWin;
	  switch (pMsg->MsgId) {
	  case WM_CREATE:
		//往project窗口添加button控件
		{
			struct list_head *pos;
			PROEDIT_MAN *node;

			i = 0;
			j = 0;

			list_for_each(pos,&hProEditMan.listNode)
			{
				/* TBD 这里有个warning，不知道影响大不大*/
				node = list_entry(pos,PROEDIT_MAN,listNode);

				hWin_Temp = BUTTON_CreateEx(
					WinPara.xSizeWin*i/3,
					WinPara.ySizeWin*j/10,
					WinPara.xSizeWin/3,
					WinPara.ySizeWin/10,
					hWin,
					WM_CF_SHOW,
					0,
					GUIID_PROJECT+3*j+i
					);
				BUTTON_SetText(hWin_Temp, node->name);
				//DEBUG("\r\n node->name =%s \r\n ",node->name);

				i++;
				if(i >= 3 )
				{
					i = 0;
					j++;
				}
			}
		}
		flagProjAct = 0;//标记进入projectshow页面  
		break;
	  case WM_NOTIFY_PARENT:
		  Id    = WM_GetId(pMsg->hWinSrc);
		  NCode = pMsg->Data.v;

		  switch(NCode) 
		  {
			case WM_NOTIFICATION_RELEASED:
				projSel = Id - GUIID_PROJECT;
				break;
			default:
				break;
		  }
		  break;
	  case WM_PAINT:
		//
	    // Draw background
	    //
	    xSize = WM_GetWindowSizeX(hWin);
	    ySize = WM_GetWindowSizeY(hWin);
	    GUI_SetColor(GUI_GRAY);
		
		GUI_FillRect(0,0,xSize,ySize);	
		break;
	  default:
		WM_DefaultProc(pMsg);
		break;
	}	
}

static void _ProjectShow(WM_HWIN hWin)
{
	WM_HWIN hWin_Temp;

	//EDIT按钮
	hWin_Temp = BUTTON_CreateEx(
		0,
		WinPara.ySizeWin*9/10,
		WinPara.xSizeWin/3,
		WinPara.ySizeWin/10,
		hWin,
		WM_CF_SHOW,
		0,
		GUIID_PROJECTEDIT_BUTTON_EDIT
		);
	BUTTON_SetText(hWin_Temp, "EDIT");

	//ADD按钮
	hWin_Temp = BUTTON_CreateEx(
		WinPara.xSizeWin/3,
		WinPara.ySizeWin*9/10,
		WinPara.xSizeWin/3,
		WinPara.ySizeWin/10,
		hWin,
		WM_CF_SHOW,
		0,
		GUIID_PROJECTEDIT_BUTTON_ADD
		);
	BUTTON_SetText(hWin_Temp, "ADD");

	//EDLETE按钮
	hWin_Temp = BUTTON_CreateEx(
		WinPara.xSizeWin*2/3,
		WinPara.ySizeWin*9/10,
		WinPara.xSizeWin/3,
		WinPara.ySizeWin/10,
		hWin,
		WM_CF_SHOW,
		0,
		GUIID_PROJECTEDIT_BUTTON_DELETE
		);
	BUTTON_SetText(hWin_Temp, "DELETE");

	//project窗口
	WM_CreateWindowAsChild(
		0, 
		WinPara.ySizeWin*1/20,
		WinPara.xSizeWin, 
		WinPara.ySizeWin*8/10,
		hWin, WM_CF_SHOW | WM_CF_STAYONTOP, _cbProjectShow, 0);
}

/**
  * @brief  _cbProject,用户回调函数
  * @param  none
  * @retval none
  */
static void _cbProjectEdit(WM_MESSAGE * pMsg)
{
	WM_HWIN hWin;
	int xSize,ySize;
    HANDLE_LIST *appNode;
	int Id, NCode;

	hWin = pMsg->hWin;
	switch (pMsg->MsgId)
	{
		case WM_CREATE:
			_ProjectShow(hWin);
			break;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;

			switch(Id) 
			{
				case GUIID_PROJECTEDIT_BUTTON_EDIT: // EDIT按钮
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED:
							if(flagProjAct == 0)//如果是project页面，则跳到对应的actionshow
							{
								struct list_head *pos;

								uint8_t k = 0;
								HANDLE_LIST *hAction;

								list_for_each(pos,&hProEditMan.listNode)
								{
									if(k == projSel)
									{
										/* TBD 这里有个warning，不知道影响大不大*/
										pCurProj = list_entry(pos,PROEDIT_MAN,listNode);
										break;
									}
									k++;
								}
								if(projSel > k)
								{
									//报错
									break;
								}

								//actionshow窗口
								hAction = hAPPLinkedList_NewNode();

								hAction->hAPP = WM_CreateWindowAsChild(
									0, 
									WinPara.ySizeWin*1/20,
									WinPara.xSizeWin, 
									WinPara.ySizeWin*8/10,
									hWin, WM_CF_SHOW | WM_CF_STAYONTOP, _cbActionShow, 0);
								/* 记录当前窗口 */
								/* 添加结点到链表 */
								hAPPLinkedList_AddTail(hAction);
							}
							else if(flagProjAct == 1)//如果是actionshow页面，则跳到对应的action页面
							{
								struct list_head *pos;

								uint8_t k = 0;
								HANDLE_LIST *hAction;

								list_for_each(pos,&pCurProj->hActHead)
								{
									if(k == actSel)
									{
										/* TBD 这里有个warning，不知道影响大不大*/
										pCurAct = list_entry(pos,ACTEDIT_MAN,listNode);
										break;
									}
									k++;
								}
								if(actSel > k)
								{
									//报错
									break;
								}

								//action窗口
								hAction = hAPPLinkedList_NewNode();

								hAction->hAPP = WM_CreateWindowAsChild(
									0, 
									WinPara.ySizeWin*1/20,
									WinPara.xSizeWin, 
									WinPara.ySizeWin*8/10,
									hWin,
									WM_CF_SHOW | WM_CF_STAYONTOP, _cbAction, 0);
								
								WM_MakeModal(hAction->hAPP);//设置成模态窗口

								/* 记录当前窗口 */
								/* 添加结点到链表 */
								hAPPLinkedList_AddTail(hAction);
							}//else if(flagProjAct == 1)
						break;
					}//switch(NCode) 
				break;

				case GUIID_PROJECTEDIT_BUTTON_ADD: // ADD按钮
					switch(NCode) 
					case WM_NOTIFICATION_RELEASED:

						break;
				break;
			}//switch(Id)
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
			GUI_SetColor(GUI_DARKGRAY);
		
			GUI_FillRect(0,0,xSize,ySize);	
			break;
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
void WDAGUI_ProjectEdit(void)
{
	/*提示消息：等待您完善更多的应用 */
	HANDLE_LIST *hProject = hAPPLinkedList_NewNode();

	/* 创建电话窗口 */
	hProject->hAPP = WM_CreateWindowAsChild(
		0, 
		0, 
		WinPara.xSizeWin, 
		WinPara.ySizeWin, 
		WinPara.hWinMain, WM_CF_SHOW | WM_CF_STAYONTOP, _cbProjectEdit, 0);	
	
	/* 记录当前窗口 */
	/* 添加结点到链表 */
	hAPPLinkedList_AddTail(hProject);
	/* 向ctrl窗口发送消息 */
	WM_SendMessageNoPara(WinPara.hWinCtrl,MY_MESSAGE_CTRLCHANGE);
}
