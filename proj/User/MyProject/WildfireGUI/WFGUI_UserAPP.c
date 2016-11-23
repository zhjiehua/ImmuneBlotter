/**
  ******************************************************************************
  * @file    WFGUI_UserAPP.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �û�APP�ļ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */

#include "WFGUI_UserAPP.h"
#include "WFGUI_Common.h"

WM_HWIN CreateWindow(void);

/**
  * @brief  _cbUserAPP,�û��ص�����
  * @param  none
  * @retval none
  */
static void _cbUserAPP(WM_MESSAGE * pMsg)
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
  * @brief  WFGUI_UserAPP,�û�APP
  * @param  none
  * @retval none
  */
void WFGUI_UserAPP(void)
{
	/*��ʾ��Ϣ���ȴ������Ƹ����Ӧ�� */
	HANDLE_LIST *hUser = hAPPLinkedList_NewNode();
	
	/* �����绰���� */
	hUser->hAPP = WM_CreateWindowAsChild(0, 0, WinPara.xSizeWin, WinPara.ySizeWin, WinPara.hWinMain, WM_CF_SHOW | WM_CF_STAYONTOP, _cbUserAPP, 0);	
	
	/* ��¼��ǰ���� */
	/* ��ӽ�㵽���� */
	hAPPLinkedList_AddTail(hUser);
	/* ��ctrl���ڷ�����Ϣ */
	WM_SendMessageNoPara(WinPara.hWinCtrl,MY_MESSAGE_CTRLCHANGE);
	
	/* show sorry */
	//GUI_MessageBox("there is no APP","sorry",GUI_MESSAGEBOX_CF_MOVEABLE);
	MESSAGEBOX_Create("there is no APP","sorry",GUI_MESSAGEBOX_CF_MODAL);


}
