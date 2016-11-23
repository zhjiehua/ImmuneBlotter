/**
  ******************************************************************************
  * @file    WFGUI_Phone.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �绰Ӧ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */

#include <string.h>
#include <stdlib.h>

#include "WFGUI_Phone.h"

#include "WFGUI_Message.h"
#include "WFGUI_Keypad.h"


#include "DIALOG.h"

//#include "sim900a.h"
//#include "bsp_usart2.h"


#define PHONEKEY_BORDER 10
#define PHONEKEY_PITCH  2
#define PHONEKEY_WIDTH	70
#define PHONEKEY_HEIGHT 35

#define GUI_KEY_COLOR 	GUI_WHITE


static const BUTTON_DATA _aButtonData[] = {
	
	/*	��һ�Ű��� */
  { PHONEKEY_BORDER	,PHONEKEY_BORDER	,  PHONEKEY_WIDTH		,PHONEKEY_HEIGHT, "1"   ,GUI_KEY_COLOR },
  { PHONEKEY_BORDER +	 PHONEKEY_PITCH + PHONEKEY_WIDTH		,PHONEKEY_BORDER		,  PHONEKEY_WIDTH		, PHONEKEY_HEIGHT, "2",GUI_KEY_COLOR },
  { PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_WIDTH)*2	,PHONEKEY_BORDER		,  PHONEKEY_WIDTH		, PHONEKEY_HEIGHT, "3",GUI_KEY_COLOR },
	
	/*	�ڶ��Ű��� */
  { PHONEKEY_BORDER	,PHONEKEY_BORDER + PHONEKEY_PITCH + PHONEKEY_HEIGHT 	,  PHONEKEY_WIDTH		,PHONEKEY_HEIGHT, "4"   ,GUI_KEY_COLOR },
  { PHONEKEY_BORDER +	 PHONEKEY_PITCH + PHONEKEY_WIDTH		,PHONEKEY_BORDER + PHONEKEY_PITCH + PHONEKEY_HEIGHT 	,  PHONEKEY_WIDTH		, PHONEKEY_HEIGHT, "5",GUI_KEY_COLOR },
  { PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_WIDTH)*2	,PHONEKEY_BORDER + PHONEKEY_PITCH + PHONEKEY_HEIGHT		,  PHONEKEY_WIDTH		, PHONEKEY_HEIGHT, "6",GUI_KEY_COLOR },

	/*	�����Ű��� */
  { PHONEKEY_BORDER	,PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_HEIGHT)*2 	,  PHONEKEY_WIDTH		,PHONEKEY_HEIGHT, "7"   ,GUI_KEY_COLOR },
  { PHONEKEY_BORDER +	 PHONEKEY_PITCH + PHONEKEY_WIDTH		,PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_HEIGHT)*2 	,  PHONEKEY_WIDTH		, PHONEKEY_HEIGHT, "8",GUI_KEY_COLOR },
  { PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_WIDTH)*2	,PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_HEIGHT)*2		,  PHONEKEY_WIDTH		, PHONEKEY_HEIGHT, "9",GUI_KEY_COLOR },

	/*	�����Ű��� */
  { PHONEKEY_BORDER	,PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_HEIGHT)*3 	,  PHONEKEY_WIDTH		,PHONEKEY_HEIGHT, "."   ,GUI_KEY_COLOR },
  { PHONEKEY_BORDER +	 PHONEKEY_PITCH + PHONEKEY_WIDTH		,PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_HEIGHT)*3 	,  PHONEKEY_WIDTH		, PHONEKEY_HEIGHT, "0",GUI_KEY_COLOR },
  { PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_WIDTH)*2	,PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_HEIGHT)*3		,  PHONEKEY_WIDTH		, PHONEKEY_HEIGHT, "<--",GUI_KEY_COLOR },

	/*	�����Ű��� */
  { PHONEKEY_BORDER	,PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_HEIGHT)*4 	,  PHONEKEY_WIDTH*2		,PHONEKEY_HEIGHT, "CANCEL"   ,GUI_KEY_COLOR },
//  { PHONEKEY_BORDER +	 PHONEKEY_PITCH + PHONEKEY_WIDTH		,PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_HEIGHT)*4 	,  PHONEKEY_WIDTH		, PHONEKEY_HEIGHT, "OK",GUI_KEY_COLOR },
  { PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_WIDTH)*2	,PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_HEIGHT)*4		,  PHONEKEY_WIDTH		, PHONEKEY_HEIGHT, "OK",GUI_KEY_COLOR },

};


char s[20];  //Edit Text Buffer
uint8_t ok_flag; //if press the ok button(1: press;0: unpress)

//static void Phone_Calling(WM_HWIN Parent,char *num);




/**
  * @brief  _cbPhone,�绰���ڻص�����
  * @param  none
  * @retval none
  */
static void _cbPhone(WM_MESSAGE * pMsg)
{
	
	WM_HWIN hWin;
	int xSize,ySize;
	
	HANDLE_LIST *appNode;
	
	
	hWin = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_CREATE:
		
	
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
  * @brief  _cbCalling,�绰���ڻص�����
  * @param  none
  * @retval none
  */
//static void _cbCalling(WM_MESSAGE * pMsg)
//{
//	WM_HWIN hWin;
//	WM_HWIN hButton;
//	
//	HANDLE_LIST *appNode;
//	
//	int xSize,ySize;
//	
//	int Id,NCode;
//	
//	
//	hWin = pMsg->hWin;
//	switch (pMsg->MsgId) {
//  
//		case WM_CREATE:
//			
//		 hButton = BUTTON_CreateEx(70,WM_GetWindowSizeY(hWin)-50,100, 40, 
//                                hWin, WM_CF_SHOW | WM_CF_HASTRANS, 0, GUI_ID_BUTTON0);
//      
//			BUTTON_SetText(hButton, "Hang off");
//			BUTTON_SetFont(hButton,GUI_FONT_20B_ASCII);	
//			BUTTON_SetBkColor(hButton,BUTTON_CI_UNPRESSED,GUI_WHITE);
//			BUTTON_SetBkColor(hButton,BUTTON_CI_PRESSED,GUI_BLUE);    		
//	
//		break;
//		
//	case WM_NOTIFY_PARENT:
//		Id    = WM_GetId(pMsg->hWinSrc);
//		NCode = pMsg->Data.v;
//		
//		if(NCode == WM_NOTIFICATION_RELEASED )
//		{		
//			if(Id == GUI_ID_BUTTON0)				       //�ҵ绰��ť
//			{
//				/* �ҵ绰 */
////				SIM900A_HANGOFF();				
//						
//				/* ɾ������ */
//				WM_DeleteWindow(WM_GetParent(pMsg->hWin));			
//			}
//			
//		}			
//	
//	
//		break;
//		
//    
//  case WM_DELETE:		
//
//			/* ��ȡapp�����Ӧ�������� */
//		appNode = hAPPLinkedList_GetAppNode(pMsg->hWin);
//		if(appNode != NULL)
//		{
//			/* ɾ��app���������ļ�¼ */	
//			hAPPLinkedList_Del(appNode);
//		
//			/* ������Ϣ֪ͨctrl����*/		
//			WM_SendMessageNoPara(WinPara.hWinCtrl,MY_MESSAGE_CTRLCHANGE);	
//		}
//	
//		break;  
//	
//	case WM_PAINT:
//	//
//    // Draw background
//    //
//    xSize = WM_GetWindowSizeX(hWin);
//    ySize = WM_GetWindowSizeY(hWin);
//    GUI_SetColor(GUI_DARKGRAY);
//	
//		GUI_FillRect(0,0,xSize,ySize);
//	
//		break;	
//	}	
//}

/**
  * @brief  _cbPhoneKey,�绰���ڻص�����
  * @param  none
  * @retval none
  */
static void _cbPhoneKey(WM_MESSAGE * pMsg)
{
	
	WM_HWIN hWin;
	WM_HWIN hButton; 
//	WM_HWIN hPhone;
//	WM_HWIN hEdit;
	
	int xSize,ySize;
	
	int Id ;
	int NCode;	
	
	uint8_t i;
	
	
	hWin = pMsg->hWin;
	
  switch (pMsg->MsgId) {
		case WM_CREATE:
		
			/* �����绰���� */
			for (i = 0; i < GUI_COUNTOF(_aButtonData); i++) {
      		hButton = BUTTON_CreateEx(_aButtonData[i].xPos, _aButtonData[i].yPos, _aButtonData[i].xSize, _aButtonData[i].ySize, 
                                hWin, WM_CF_SHOW | WM_CF_HASTRANS, 0, ID_BUTTON + i);
      
			BUTTON_SetText(hButton, _aButtonData[i].acLabel);
			BUTTON_SetFont(hButton,GUI_FONT_20B_ASCII);	
			BUTTON_SetBkColor(hButton,BUTTON_CI_UNPRESSED,_aButtonData[i].bkColor);
      		BUTTON_SetFocussable(hButton, 0); //���ܰ����ľ۽����ܣ�Ҫ����������ʱ�ͻ�۽��ڰ�����EDIT�ؼ��Ͳ��ܾ۽��ˣ����������ݾͷ��Ͳ���EDIT�ؼ���
				
    }
	
		break;
		
		case WM_NOTIFY_PARENT:
			
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			
			if(NCode == WM_NOTIFICATION_RELEASED )
			{			
				/* ��ͨ���� */				
				if (Id - ID_BUTTON < 11) 
				{					
					char c = _aButtonData[Id - ID_BUTTON].acLabel[0];
					
					/* ���밴������ */
					GUI_StoreKeyMsg(c, 1);
					GUI_StoreKeyMsg(c, 0);
				
				}
				/* ɾ�� */
				else if(Id - ID_BUTTON == 11)
				{
					/* �˸� */
					GUI_StoreKeyMsg(GUI_KEY_BACKSPACE, 1);
					GUI_StoreKeyMsg(GUI_KEY_BACKSPACE, 0);
				}
				/* CANCEL*/
				else if(Id - ID_BUTTON == 12)
				{
					/* ɾ������ */
					WM_DeleteWindow(WM_GetParent(pMsg->hWin));
				}
				/* ȷ�ϲ���绰   OK */
				else if(Id - ID_BUTTON == 13)
				{					
					WM_HWIN hPreWin;

					ok_flag = 1; //���ok�������£������ü��̴��ڵĴ����жϣ���Ϊcancel����Ҳ����ɾ�������ڵĺ���

					hPreWin = WM_GetPrevSibling(pMsg->hWin); //��ʱ����һͬ��������hText
					hPreWin = WM_GetPrevSibling(hPreWin);  //��ʱ����һͬ�����ڲ���hEdit
					EDIT_GetText(hPreWin, s, 20);  //��ȡhEdit��Text
//
//					hPreWin = WM_GetParent(pMsg->hWin); //�ô��ڵĸ�������hPhone->hAPP
//

					/* ɾ������ */
					WM_DeleteWindow(WM_GetParent(pMsg->hWin)); //�Ȼ�ȡ�����ڵ�hWin����ɾ�������ڣ��Ӵ���Ҳ���Զ�ɾ����
																//��ʱ�����ڻ������ĸ����ڷ���WM_NOTIFICATION_CHILD_DELETED
				}
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
  * @brief  Phone_Calling,���ڲ���绰
  * @param  none
  * @retval none
  */
//static void Phone_Calling(WM_HWIN Parent,char *num)
//{
//	WM_HWIN hText;
//	
//	HANDLE_LIST *hPhone = hAPPLinkedList_NewNode();
//	
//	char DispText[60];
//	
//	/* �����绰���� */
//	hPhone->hAPP = WM_CreateWindowAsChild(0, 0, WinPara.xSizeWin,WinPara.ySizeWin ,WinPara.hWinMain , WM_CF_SHOW | WM_CF_STAYONTOP, _cbPhone, 0);	
//
//	sprintf(DispText,"Calling %s",num);
//	/* �������봰�� */	
//	hText	= TEXT_CreateEx(0,0,240,80,hPhone->hAPP,WM_CF_SHOW,TEXT_CF_HCENTER|TEXT_CF_VCENTER,GUI_ID_TEXT0,DispText);		
//	/* �����ı��򱳾� */
//	TEXT_SetBkColor(hText,GUI_DARKGRAY);	
//	/* �����ı����� */
//	TEXT_SetFont(hText,GUI_FONT_24B_ASCII);	
//	/* ����������ɫ */
//	TEXT_SetTextColor(hText,GUI_WHITE);	
//	/* �����ı����뷽ʽ */
//	TEXT_SetTextAlign(hText,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
//		
//
//	/* ������������ */
//	WM_CreateWindowAsChild(0, 80, WinPara.xSizeWin,WinPara.ySizeWin-80 ,hPhone->hAPP , WM_CF_SHOW | WM_CF_STAYONTOP, _cbCalling, 0);		
//	
//	/* ��ӽ�㵽���� */
//	hAPPLinkedList_AddTail(hPhone);
//	/* ��ctrl���ڷ�����Ϣ */
//	WM_SendMessageNoPara(WinPara.hWinCtrl,MY_MESSAGE_CTRLCHANGE);
//}

	
/**
  * @brief  WFGUI_Phone,�绰����
  * @param  none
  * @retval none
  */	
void WFGUI_Phone(char* label, char* edittext, WM_HWIN hWin)
{
	WM_HWIN hEdit, hText;
	char str[20];
	
	HANDLE_LIST *hPhone = hAPPLinkedList_NewNode();
	
	/* �����绰���� */
	hPhone->hAPP = WM_CreateWindowAsChild(0, 0, WinPara.xSizeWin,WinPara.ySizeWin , hWin , WM_CF_SHOW | WM_CF_STAYONTOP, _cbPhone, 0);	

	/* �������봰�� */	
	hEdit	= EDIT_CreateEx(0,20,240,60,hPhone->hAPP,WM_CF_SHOW,0,GUI_ID_EDIT0,50);
	/* �����ı� */
	EDIT_SetText(hEdit, edittext);
	EDIT_GetText(hEdit, str, 20);		
	/* �����ı��򱳾� */
	EDIT_SetBkColor(hEdit,EDIT_CI_ENABLED,GUI_DARKGRAY);	
	/* �����ı����� */
	EDIT_SetFont(hEdit,GUI_FONT_24B_ASCII);	
	/* ����������ɫ */
	EDIT_SetTextColor(hEdit,EDIT_CI_ENABLED,GUI_WHITE);	
	/* �����ı����뷽ʽ */
	EDIT_SetTextAlign(hEdit,TEXT_CF_HCENTER|TEXT_CF_VCENTER);	
	/* ���ô��ھ۽� */
	WM_SetFocus(hEdit);	 //���ǳ���Ҫ����Ϊ����İ������͵����ݶ��Ƿ��͵�Ŀǰ�۽��Ŀؼ�



	/* �����ı���ʾ���� */	
	hText = TEXT_CreateEx(0,0,240,20,hPhone->hAPP,WM_CF_SHOW,TEXT_CF_HCENTER|TEXT_CF_VCENTER,GUI_ID_TEXT0,label);	
	/* �����ı��򱳾� */
	TEXT_SetBkColor(hText,GUI_DARKGRAY);	
	/* �����ı����� */
	TEXT_SetFont(hText,GUI_FONT_24B_ASCII);	
	/* ����������ɫ */
	TEXT_SetTextColor(hText, GUI_BLACK);	
	/* �����ı����뷽ʽ */
	TEXT_SetTextAlign(hText,TEXT_CF_HCENTER|TEXT_CF_VCENTER);


	/* ������������ */
	hText = WM_CreateWindowAsChild(0, 80, WinPara.xSizeWin,WinPara.ySizeWin-80 ,hPhone->hAPP , WM_CF_SHOW | WM_CF_STAYONTOP, _cbPhoneKey, 0);	

	/* ��ӽ�㵽���� */
	hAPPLinkedList_AddTail(hPhone);
	/* ��ctrl���ڷ�����Ϣ */
	WM_SendMessageNoPara(WinPara.hWinCtrl,MY_MESSAGE_CTRLCHANGE);

	WM_SetFocus(hEdit);	//�ٴξ۽�	
		
	
}
