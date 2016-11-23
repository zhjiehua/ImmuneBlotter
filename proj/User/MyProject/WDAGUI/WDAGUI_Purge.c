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

#include "WDAGUI_Purge.h"
#include "WFGUI_Common.h"

WM_HWIN CreateWindow(void);

/**
  * @brief  _cbProject,�û��ص�����
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
	    GUI_SetColor(GUI_WHITE);
		
		GUI_FillRect(0,0,xSize,ySize);
		
	  break;
	}	
}




/**
  * @brief  WFGUI_Project,�û�APP
  * @param  none
  * @retval none
  */
void WDAGUI_Purge(void)
{
	/*��ʾ��Ϣ���ȴ������Ƹ����Ӧ�� */
	HANDLE_LIST *hProject = hAPPLinkedList_NewNode();
	
	/* �����绰���� */
	hProject->hAPP = WM_CreateWindowAsChild(
		0, 
		0, 
		WinPara.xSizeWin, 
		WinPara.ySizeWin, 
		WinPara.hWinMain, WM_CF_SHOW | WM_CF_STAYONTOP, _cbPurge, 0);	
	
	/* ��¼��ǰ���� */
	/* ��ӽ�㵽���� */
	hAPPLinkedList_AddTail(hProject);
	/* ��ctrl���ڷ�����Ϣ */
	WM_SendMessageNoPara(WinPara.hWinCtrl,MY_MESSAGE_CTRLCHANGE);
	
	/* show sorry */
	MESSAGEBOX_Create("there is no Purge","sorry",GUI_MESSAGEBOX_CF_MODAL);
}
