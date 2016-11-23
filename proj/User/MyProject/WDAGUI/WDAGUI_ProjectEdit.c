/**
  ******************************************************************************
  * @file    WDAGUI_Project.c
  * @author  zhjiehua
  * @version V1.0
  * @date    2016-xx-xx
  * @brief   �û�APP�ļ�
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
static uint8_t flagProjAct;//0��ʾproject;1��ʾaction

PROEDIT_MAN *pCurProj;//��ǰ��Ŀ
ACTEDIT_MAN *pCurAct;//��ǰ����


static void _cbAction(WM_MESSAGE * pMsg)
{
	WM_HWIN hWin;
	int xSize,ySize;
	HANDLE_LIST *appNode;

	hWin = pMsg->hWin;
	switch (pMsg->MsgId) {
	case WM_CREATE:
		createAction(hWin);
		flagProjAct = 2;//��ǽ���actionҳ��
		break;
	case WM_NOTIFY_PARENT:

		cbActionNotifyParent(pMsg);

		break;
	case WM_DELETE:
		/* ��ȡapp�����Ӧ�������� */
		appNode = hAPPLinkedList_GetAppNode(pMsg->hWin);
		if(appNode != NULL)
		{
			/* ɾ��app���������ļ�¼ */
			hAPPLinkedList_Del(appNode);

			flagProjAct = 1;//��ǽ���actionshowҳ��
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
		//��project�������button�ؼ�
		{
			struct list_head *pos;
			PROEDIT_MAN *node;

			i = 0;
			j = 0;

			list_for_each(pos,&pCurProj->hActHead)
			{
				/* TBD �����и�warning����֪��Ӱ��󲻴�*/
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
		flagProjAct = 1;//��ǽ���actionshowҳ��
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
		/* ��ȡapp�����Ӧ�������� */
		appNode = hAPPLinkedList_GetAppNode(pMsg->hWin);
		if(appNode != NULL)
		{
			/* ɾ��app���������ļ�¼ */	
			hAPPLinkedList_Del(appNode);

			flagProjAct = 0;//����˻�projectshowҳ��
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
  * @brief  _cbProject,�û��ص�����
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
		//��project�������button�ؼ�
		{
			struct list_head *pos;
			PROEDIT_MAN *node;

			i = 0;
			j = 0;

			list_for_each(pos,&hProEditMan.listNode)
			{
				/* TBD �����и�warning����֪��Ӱ��󲻴�*/
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
		flagProjAct = 0;//��ǽ���projectshowҳ��  
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

	//EDIT��ť
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

	//ADD��ť
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

	//EDLETE��ť
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

	//project����
	WM_CreateWindowAsChild(
		0, 
		WinPara.ySizeWin*1/20,
		WinPara.xSizeWin, 
		WinPara.ySizeWin*8/10,
		hWin, WM_CF_SHOW | WM_CF_STAYONTOP, _cbProjectShow, 0);
}

/**
  * @brief  _cbProject,�û��ص�����
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
				case GUIID_PROJECTEDIT_BUTTON_EDIT: // EDIT��ť
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED:
							if(flagProjAct == 0)//�����projectҳ�棬��������Ӧ��actionshow
							{
								struct list_head *pos;

								uint8_t k = 0;
								HANDLE_LIST *hAction;

								list_for_each(pos,&hProEditMan.listNode)
								{
									if(k == projSel)
									{
										/* TBD �����и�warning����֪��Ӱ��󲻴�*/
										pCurProj = list_entry(pos,PROEDIT_MAN,listNode);
										break;
									}
									k++;
								}
								if(projSel > k)
								{
									//����
									break;
								}

								//actionshow����
								hAction = hAPPLinkedList_NewNode();

								hAction->hAPP = WM_CreateWindowAsChild(
									0, 
									WinPara.ySizeWin*1/20,
									WinPara.xSizeWin, 
									WinPara.ySizeWin*8/10,
									hWin, WM_CF_SHOW | WM_CF_STAYONTOP, _cbActionShow, 0);
								/* ��¼��ǰ���� */
								/* ��ӽ�㵽���� */
								hAPPLinkedList_AddTail(hAction);
							}
							else if(flagProjAct == 1)//�����actionshowҳ�棬��������Ӧ��actionҳ��
							{
								struct list_head *pos;

								uint8_t k = 0;
								HANDLE_LIST *hAction;

								list_for_each(pos,&pCurProj->hActHead)
								{
									if(k == actSel)
									{
										/* TBD �����и�warning����֪��Ӱ��󲻴�*/
										pCurAct = list_entry(pos,ACTEDIT_MAN,listNode);
										break;
									}
									k++;
								}
								if(actSel > k)
								{
									//����
									break;
								}

								//action����
								hAction = hAPPLinkedList_NewNode();

								hAction->hAPP = WM_CreateWindowAsChild(
									0, 
									WinPara.ySizeWin*1/20,
									WinPara.xSizeWin, 
									WinPara.ySizeWin*8/10,
									hWin,
									WM_CF_SHOW | WM_CF_STAYONTOP, _cbAction, 0);
								
								WM_MakeModal(hAction->hAPP);//���ó�ģ̬����

								/* ��¼��ǰ���� */
								/* ��ӽ�㵽���� */
								hAPPLinkedList_AddTail(hAction);
							}//else if(flagProjAct == 1)
						break;
					}//switch(NCode) 
				break;

				case GUIID_PROJECTEDIT_BUTTON_ADD: // ADD��ť
					switch(NCode) 
					case WM_NOTIFICATION_RELEASED:

						break;
				break;
			}//switch(Id)
			break;
		case WM_DELETE:
			/* ��ȡapp�����Ӧ�������� */
			appNode = hAPPLinkedList_GetAppNode(pMsg->hWin);
			if(appNode != NULL)
			{
				/* ɾ��app���������ļ�¼ */	
				hAPPLinkedList_Del(appNode);

				/* ������Ϣ֪ͨctrl����*/		
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
  * @brief  WFGUI_Project,�û�APP
  * @param  none
  * @retval none
  */
void WDAGUI_ProjectEdit(void)
{
	/*��ʾ��Ϣ���ȴ������Ƹ����Ӧ�� */
	HANDLE_LIST *hProject = hAPPLinkedList_NewNode();

	/* �����绰���� */
	hProject->hAPP = WM_CreateWindowAsChild(
		0, 
		0, 
		WinPara.xSizeWin, 
		WinPara.ySizeWin, 
		WinPara.hWinMain, WM_CF_SHOW | WM_CF_STAYONTOP, _cbProjectEdit, 0);	
	
	/* ��¼��ǰ���� */
	/* ��ӽ�㵽���� */
	hAPPLinkedList_AddTail(hProject);
	/* ��ctrl���ڷ�����Ϣ */
	WM_SendMessageNoPara(WinPara.hWinCtrl,MY_MESSAGE_CTRLCHANGE);
}
