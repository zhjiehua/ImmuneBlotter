/**
  ******************************************************************************
  * @file    WFGUI_Phone.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   电话应用
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
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
	
	/*	第一排按键 */
  { PHONEKEY_BORDER	,PHONEKEY_BORDER	,  PHONEKEY_WIDTH		,PHONEKEY_HEIGHT, "1"   ,GUI_KEY_COLOR },
  { PHONEKEY_BORDER +	 PHONEKEY_PITCH + PHONEKEY_WIDTH		,PHONEKEY_BORDER		,  PHONEKEY_WIDTH		, PHONEKEY_HEIGHT, "2",GUI_KEY_COLOR },
  { PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_WIDTH)*2	,PHONEKEY_BORDER		,  PHONEKEY_WIDTH		, PHONEKEY_HEIGHT, "3",GUI_KEY_COLOR },
	
	/*	第二排按键 */
  { PHONEKEY_BORDER	,PHONEKEY_BORDER + PHONEKEY_PITCH + PHONEKEY_HEIGHT 	,  PHONEKEY_WIDTH		,PHONEKEY_HEIGHT, "4"   ,GUI_KEY_COLOR },
  { PHONEKEY_BORDER +	 PHONEKEY_PITCH + PHONEKEY_WIDTH		,PHONEKEY_BORDER + PHONEKEY_PITCH + PHONEKEY_HEIGHT 	,  PHONEKEY_WIDTH		, PHONEKEY_HEIGHT, "5",GUI_KEY_COLOR },
  { PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_WIDTH)*2	,PHONEKEY_BORDER + PHONEKEY_PITCH + PHONEKEY_HEIGHT		,  PHONEKEY_WIDTH		, PHONEKEY_HEIGHT, "6",GUI_KEY_COLOR },

	/*	第三排按键 */
  { PHONEKEY_BORDER	,PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_HEIGHT)*2 	,  PHONEKEY_WIDTH		,PHONEKEY_HEIGHT, "7"   ,GUI_KEY_COLOR },
  { PHONEKEY_BORDER +	 PHONEKEY_PITCH + PHONEKEY_WIDTH		,PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_HEIGHT)*2 	,  PHONEKEY_WIDTH		, PHONEKEY_HEIGHT, "8",GUI_KEY_COLOR },
  { PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_WIDTH)*2	,PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_HEIGHT)*2		,  PHONEKEY_WIDTH		, PHONEKEY_HEIGHT, "9",GUI_KEY_COLOR },

	/*	第四排按键 */
  { PHONEKEY_BORDER	,PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_HEIGHT)*3 	,  PHONEKEY_WIDTH		,PHONEKEY_HEIGHT, "."   ,GUI_KEY_COLOR },
  { PHONEKEY_BORDER +	 PHONEKEY_PITCH + PHONEKEY_WIDTH		,PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_HEIGHT)*3 	,  PHONEKEY_WIDTH		, PHONEKEY_HEIGHT, "0",GUI_KEY_COLOR },
  { PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_WIDTH)*2	,PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_HEIGHT)*3		,  PHONEKEY_WIDTH		, PHONEKEY_HEIGHT, "<--",GUI_KEY_COLOR },

	/*	第五排按键 */
  { PHONEKEY_BORDER	,PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_HEIGHT)*4 	,  PHONEKEY_WIDTH*2		,PHONEKEY_HEIGHT, "CANCEL"   ,GUI_KEY_COLOR },
//  { PHONEKEY_BORDER +	 PHONEKEY_PITCH + PHONEKEY_WIDTH		,PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_HEIGHT)*4 	,  PHONEKEY_WIDTH		, PHONEKEY_HEIGHT, "OK",GUI_KEY_COLOR },
  { PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_WIDTH)*2	,PHONEKEY_BORDER + (PHONEKEY_PITCH + PHONEKEY_HEIGHT)*4		,  PHONEKEY_WIDTH		, PHONEKEY_HEIGHT, "OK",GUI_KEY_COLOR },

};


char s[20];  //Edit Text Buffer
uint8_t ok_flag; //if press the ok button(1: press;0: unpress)

//static void Phone_Calling(WM_HWIN Parent,char *num);




/**
  * @brief  _cbPhone,电话窗口回调函数
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
  * @brief  _cbCalling,电话窗口回调函数
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
//			if(Id == GUI_ID_BUTTON0)				       //挂电话按钮
//			{
//				/* 挂电话 */
////				SIM900A_HANGOFF();				
//						
//				/* 删除窗口 */
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
//			/* 获取app句柄对应的链表结点 */
//		appNode = hAPPLinkedList_GetAppNode(pMsg->hWin);
//		if(appNode != NULL)
//		{
//			/* 删除app句柄链表里的记录 */	
//			hAPPLinkedList_Del(appNode);
//		
//			/* 发送消息通知ctrl窗口*/		
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
  * @brief  _cbPhoneKey,电话窗口回调函数
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
		
			/* 创建电话按键 */
			for (i = 0; i < GUI_COUNTOF(_aButtonData); i++) {
      		hButton = BUTTON_CreateEx(_aButtonData[i].xPos, _aButtonData[i].yPos, _aButtonData[i].xSize, _aButtonData[i].ySize, 
                                hWin, WM_CF_SHOW | WM_CF_HASTRANS, 0, ID_BUTTON + i);
      
			BUTTON_SetText(hButton, _aButtonData[i].acLabel);
			BUTTON_SetFont(hButton,GUI_FONT_20B_ASCII);	
			BUTTON_SetBkColor(hButton,BUTTON_CI_UNPRESSED,_aButtonData[i].bkColor);
      		BUTTON_SetFocussable(hButton, 0); //除能按键的聚焦功能，要不按键按下时就会聚焦在按键，EDIT控件就不能聚焦了，按键的数据就发送不到EDIT控件了
				
    }
	
		break;
		
		case WM_NOTIFY_PARENT:
			
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			
			if(NCode == WM_NOTIFICATION_RELEASED )
			{			
				/* 普通按键 */				
				if (Id - ID_BUTTON < 11) 
				{					
					char c = _aButtonData[Id - ID_BUTTON].acLabel[0];
					
					/* 输入按键数字 */
					GUI_StoreKeyMsg(c, 1);
					GUI_StoreKeyMsg(c, 0);
				
				}
				/* 删除 */
				else if(Id - ID_BUTTON == 11)
				{
					/* 退格 */
					GUI_StoreKeyMsg(GUI_KEY_BACKSPACE, 1);
					GUI_StoreKeyMsg(GUI_KEY_BACKSPACE, 0);
				}
				/* CANCEL*/
				else if(Id - ID_BUTTON == 12)
				{
					/* 删除窗口 */
					WM_DeleteWindow(WM_GetParent(pMsg->hWin));
				}
				/* 确认拨打电话   OK */
				else if(Id - ID_BUTTON == 13)
				{					
					WM_HWIN hPreWin;

					ok_flag = 1; //标记ok按键按下，给调用键盘窗口的窗口判断，因为cancel按键也是有删除本窗口的函数

					hPreWin = WM_GetPrevSibling(pMsg->hWin); //这时，上一同属窗口是hText
					hPreWin = WM_GetPrevSibling(hPreWin);  //这时，上一同属窗口才是hEdit
					EDIT_GetText(hPreWin, s, 20);  //获取hEdit的Text
//
//					hPreWin = WM_GetParent(pMsg->hWin); //该窗口的父窗口是hPhone->hAPP
//

					/* 删除窗口 */
					WM_DeleteWindow(WM_GetParent(pMsg->hWin)); //先获取父窗口的hWin，再删除父窗口（子窗口也会自动删除）
																//这时父窗口会向它的父窗口发送WM_NOTIFICATION_CHILD_DELETED
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
  * @brief  Phone_Calling,正在拨打电话
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
//	/* 创建电话窗口 */
//	hPhone->hAPP = WM_CreateWindowAsChild(0, 0, WinPara.xSizeWin,WinPara.ySizeWin ,WinPara.hWinMain , WM_CF_SHOW | WM_CF_STAYONTOP, _cbPhone, 0);	
//
//	sprintf(DispText,"Calling %s",num);
//	/* 创建号码窗口 */	
//	hText	= TEXT_CreateEx(0,0,240,80,hPhone->hAPP,WM_CF_SHOW,TEXT_CF_HCENTER|TEXT_CF_VCENTER,GUI_ID_TEXT0,DispText);		
//	/* 设置文本框背景 */
//	TEXT_SetBkColor(hText,GUI_DARKGRAY);	
//	/* 设置文本字体 */
//	TEXT_SetFont(hText,GUI_FONT_24B_ASCII);	
//	/* 设置字体颜色 */
//	TEXT_SetTextColor(hText,GUI_WHITE);	
//	/* 设置文本对齐方式 */
//	TEXT_SetTextAlign(hText,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
//		
//
//	/* 创建按键窗口 */
//	WM_CreateWindowAsChild(0, 80, WinPara.xSizeWin,WinPara.ySizeWin-80 ,hPhone->hAPP , WM_CF_SHOW | WM_CF_STAYONTOP, _cbCalling, 0);		
//	
//	/* 添加结点到链表 */
//	hAPPLinkedList_AddTail(hPhone);
//	/* 向ctrl窗口发送消息 */
//	WM_SendMessageNoPara(WinPara.hWinCtrl,MY_MESSAGE_CTRLCHANGE);
//}

	
/**
  * @brief  WFGUI_Phone,电话窗口
  * @param  none
  * @retval none
  */	
void WFGUI_Phone(char* label, char* edittext, WM_HWIN hWin)
{
	WM_HWIN hEdit, hText;
	char str[20];
	
	HANDLE_LIST *hPhone = hAPPLinkedList_NewNode();
	
	/* 创建电话窗口 */
	hPhone->hAPP = WM_CreateWindowAsChild(0, 0, WinPara.xSizeWin,WinPara.ySizeWin , hWin , WM_CF_SHOW | WM_CF_STAYONTOP, _cbPhone, 0);	

	/* 创建号码窗口 */	
	hEdit	= EDIT_CreateEx(0,20,240,60,hPhone->hAPP,WM_CF_SHOW,0,GUI_ID_EDIT0,50);
	/* 设置文本 */
	EDIT_SetText(hEdit, edittext);
	EDIT_GetText(hEdit, str, 20);		
	/* 设置文本框背景 */
	EDIT_SetBkColor(hEdit,EDIT_CI_ENABLED,GUI_DARKGRAY);	
	/* 设置文本字体 */
	EDIT_SetFont(hEdit,GUI_FONT_24B_ASCII);	
	/* 设置字体颜色 */
	EDIT_SetTextColor(hEdit,EDIT_CI_ENABLED,GUI_WHITE);	
	/* 设置文本对齐方式 */
	EDIT_SetTextAlign(hEdit,TEXT_CF_HCENTER|TEXT_CF_VCENTER);	
	/* 设置窗口聚焦 */
	WM_SetFocus(hEdit);	 //这句非常重要，因为后面的按键发送的数据都是发送到目前聚焦的控件



	/* 创建文本显示窗口 */	
	hText = TEXT_CreateEx(0,0,240,20,hPhone->hAPP,WM_CF_SHOW,TEXT_CF_HCENTER|TEXT_CF_VCENTER,GUI_ID_TEXT0,label);	
	/* 设置文本框背景 */
	TEXT_SetBkColor(hText,GUI_DARKGRAY);	
	/* 设置文本字体 */
	TEXT_SetFont(hText,GUI_FONT_24B_ASCII);	
	/* 设置字体颜色 */
	TEXT_SetTextColor(hText, GUI_BLACK);	
	/* 设置文本对齐方式 */
	TEXT_SetTextAlign(hText,TEXT_CF_HCENTER|TEXT_CF_VCENTER);


	/* 创建按键窗口 */
	hText = WM_CreateWindowAsChild(0, 80, WinPara.xSizeWin,WinPara.ySizeWin-80 ,hPhone->hAPP , WM_CF_SHOW | WM_CF_STAYONTOP, _cbPhoneKey, 0);	

	/* 添加结点到链表 */
	hAPPLinkedList_AddTail(hPhone);
	/* 向ctrl窗口发送消息 */
	WM_SendMessageNoPara(WinPara.hWinCtrl,MY_MESSAGE_CTRLCHANGE);

	WM_SetFocus(hEdit);	//再次聚焦	
		
	
}
