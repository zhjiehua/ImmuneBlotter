/**
  ******************************************************************************
  * @file    WFGUI_DeskTop.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �洢wildfire gui������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� ISO STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 

/*********************************************************************
*
*       Includes
*
**********************************************************************
*/
/*********************************************************************
*
*       System
*/
#include <stddef.h>
#include <stdio.h>

/*********************************************************************
*
*       STemwin GUI
*/
#include "ICONVIEW.h"
#include "TEXT.h"
#include "DIALOG.h"
#include "MESSAGEBOX.h"

/* BSP */
//#include "ff.h"
//#include "bsp_rtc.h"

/* WFGUI */
#include "WFGUI_Common.h"
#include "WFGUI_DeskTop.h"
#include "WFGUI_SDView.h"
#include "WFGUI_Time.h"
#include "WFGUI_Message.h"
#include "WFGUI_Phone.h"
#include "WFGUI_Camera.h"
#include "WFGUI_Snapshot.h"
#include "WFGUI_ImageReader.h"
#include "WFGUI_Temperature.h"
#include "WFGUI_TextReader.h"
#include "WFGUI_Keypad.h"
#include "WFGUI_UserAPP.h"

/*JMGUI*/
#include "JMGUI_DMX512_Setting.h" 
#include "JMGUI_DMX512_Test.h"

/*WDAGUI*/
#include "WDAGUI_Project.h"
#include "WDAGUI_ProjectEdit.h"
#include "WDAGUI_Backflow.h"
#include "WDAGUI_Purge.h"
#include "WDAGUI_Calibration.h"
#include "WDAGUI_Information.h"


#include "WDAProEdit.h"

/* �ڵ��Բ��ֹ��ܵ�ʱ��ʹ������꣬���Լ���ICONͼ�꣬��������ʱ�� */
//#define  GUI_DEVELOP


/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define MSG_MOVE (WM_USER + 0)

#ifndef GUI_DEVELOP
/*********************************************************************
*
*       _aBitmapItem
*/
/*��һҳ��ͼ�ꡣ����Ԫ�طֱ��ǣ�ͼ�����飬ͼ����⣬ͼ��˵��(����û����ͼ��˵��)*/
static const BITMAP_ITEM _aBitmapItem[] = {

  {&bmIcon_Project,			"Project",			"Project" ,					WDAGUI_Project},
  {&bmIcon_ProjectEdit,		"ProjectEdit",		"Edit the project" ,		WDAGUI_ProjectEdit},
  {&bmIcon_Backflow,		"Backflow",			"Backflow the liquid" ,		WDAGUI_Backflow},
  {&bmIcon_Purge,			"Purge",			"Purge the machine" ,		WDAGUI_Purge},
  {&bmIcon_Calibration,		"Calibration",		"Calibrate the machine" ,	WDAGUI_Calibration},
  {&bmIcon_Information,		"Information",		"information" ,				WDAGUI_Information},

  {&bmJM_RGB, 				"DMX_Test", 		"Output the DMX512 test signal",	JMGUI_DMX512_Test},
  {&bmJM_DMX_Setting,		"DMX_Set", 			"Setting the DMX512 attribute",		JMGUI_DMX512_Setting},
  {&bmWFGUI_UserApp,		"UserAPP",			"UserAPP",							WFGUI_UserAPP},

//	{&bmWF_Temperature, "TEMP", 			"Temperature sensor"},
//	{&bmWF_Picture,  		"Picture", 		"Picture viewer"},
//	{&bmWF_Note,    		"Note", 			"Write a note"},
//  {&bmWF_Message,			"Message", 		"Read or write message"},
//  {&bmWF_Phone,  			"Phone",      "make a telephone call"},
//  {&bmWF_Camera,			"Camera", 		"Take a phone"},
};


///*�ڶ�ҳ��ͼ�ꡣ����Ԫ�طֱ��ǣ�ͼ�����飬ͼ����⣬ͼ��˵��(����û����ͼ��˵��)*/
//static const BITMAP_ITEM _aBitmapItem2[] = {
//	{&bmWF_Map,         "Map" ,       "Map"},
//  {&bmWF_Calculator,  "Calculator", "Calculator"},
//  {&bmWFGUI_UserApp,  "UserAPP",    "UserAPP"}, 
//
//};

#else	//�ڵ���ʱʹ��������飬���ٴ�����
/*********************************************************************
*
*       _aBitmapItem
*/
static const BITMAP_ITEM _aBitmapItem[] = {
//  {&bmWF_Floder, 			"Browser", 		"Use the browser to explore the www"},
//  {&bmWF_Clock,   		"Clock", 			"Adjust current time and date"},
	{&bmWF_Temperature, "TEMP", 			"Temperature sensor"},
	{&bmWF_Picture,  		"Picture", 		"Picture viewer"},
//	{&bmWF_Note,    		"Note", 			"Write a note"},
//  {&bmWF_Message,			"Message", 		"Read or write message"},
//  {&bmWF_Phone,  			"Phone",      "make a telephone call"},
//  {&bmWF_Camera,			"Camera", 		"Take a phone"},
//	{&bmWF_Map,         "Map" ,       "Map"},
//  {&bmWF_Calculator,  "Calculator", "Calculator"},
};

/*�ڶ�ҳ��ͼ�ꡣ����Ԫ�طֱ��ǣ�ͼ�����飬ͼ����⣬ͼ��˵��(����û����ͼ��˵��)*/
//static const BITMAP_ITEM _aBitmapItem2[] = {
////	{&bmWF_Map,         "Map" ,       "Map"},
////  {&bmWF_Calculator,  "Calculator", "Calculator"},
//  {&bmWFGUI_UserApp,  "UserAPP",    "UserAPP"}, 
//
//};
#endif

/* ȫ�ֱ��� */
WIN_PARA WinPara;			//�û�ʹ�õĴ��ڶ�������
//SD_FONT SDFont;				//ʹ���ⲿ����ʱ��Ҫ�õ������ݽṹ			
WM_HWIN hStatusText;
/**
  * @brief  _cbBKWin,���汳���Ļص�����
  * @param  none
  * @retval none
  */
static void _cbBKWin(WM_MESSAGE * pMsg) {  

  switch (pMsg->MsgId) {
  case WM_PAINT:		//�ػ汳��
  	GUI_SetColor(GUI_DARKGRAY);
	GUI_FillRect(0,0,LCD_GetXSize(),LCD_GetYSize());
    break;
	
	default:		
    WM_DefaultProc(pMsg);
	break;
  }
}

/**
  * @brief  _cbStatusWin,״̬���ص�����
  * @param  none
  * @retval none
  */
static void _cbStatusWin(WM_MESSAGE * pMsg)
{
	int        NCode;
	int        Id;
	
	 switch (pMsg->MsgId) {	 
	    case WM_NOTIFY_PARENT:	//֪ͨ������
		 	Id    = WM_GetId(pMsg->hWinSrc);      // �ؼ���ID
			NCode = pMsg->Data.v;                 // ֪ͨ����
			if(NCode == WM_NOTIFICATION_RELEASED)	//�����ͷ���Ϣ	
			{
				if(Id == GUI_ID_BUTTON0)	//Ұ��Logo����	
				{
					/* ��ʾ��Ϣ��ʾ�� */
					MESSAGEBOX_Create("\n\n  WDA GUI 0.1  \n\n","About",0);						 					
				}
			}
	   	break;
		case MY_MESSAGE_STATUSTEXT:
			//TEXT_SetText(hStatusText, pMsg->Data.p);
			break;
		case WM_PAINT:		//�ػ汳��
			GUI_SetColor(GUI_BLACK);
			GUI_FillRect(0,0,WinPara.xSizeLCD ,WinPara.yPosWin);
		break;	 
		default:		
        	WM_DefaultProc(pMsg);
		break;		 
	 }
}

/**
  * @brief  _cbIndexWin,�������ڻص�����
  * @param  none
  * @retval none
  */
static void _cbIndexWin(WM_MESSAGE * pMsg)
{
	 switch (pMsg->MsgId) {
		 case WM_PAINT:										//�ػ汳��				 
		 		GUI_SetColor(GUI_BLACK);			
				GUI_FillRect(0,0,WM_GetWindowSizeX(pMsg->hWin) ,WM_GetWindowSizeY(pMsg->hWin));
			 				
				/* ������������ */
				GUI_SetColor(GUI_LIGHTGRAY);
				GUI_FillCircle(WM_GetWindowSizeX(pMsg->hWin)/2,WM_GetWindowSizeY(pMsg->hWin)/2,5);						
		 break;	

		 default:
			 WM_DefaultProc(pMsg);
		 break;
		}			 
}

/**
  * @brief  _cbButtonWin,���ư�ť���ڻص�����
  * @param  none
  * @retval none
  */
static void _cbButtonWin(WM_MESSAGE * pMsg)
{
	int Id,NCode;
	WM_HWIN hItem;			
	
	 switch (pMsg->MsgId) {
		 
		 case WM_PAINT:										  //�ػ洰��	
			GUI_SetColor(GUI_BLACK);			
			GUI_FillRect(0,0,WM_GetWindowSizeX(pMsg->hWin) ,WM_GetWindowSizeY(pMsg->hWin));
		 
		 break;		 
		 case WM_CREATE:										//��������
			
		 	/*���ؼ�*/
			hItem = BUTTON_CreateEx(
				0,
				0,
				WinPara.xSizeLCD/6, 
				WinPara.ySizeWinCtrl, 
				pMsg->hWin, WM_CF_SHOW|WM_CF_MEMDEV , 0, GUI_ID_BUTTON0
				);
			BUTTON_SetText(hItem, "<");
		 
		 break;
		 case WM_NOTIFY_PARENT:		//�����Ӵ�����Ϣ	
			Id = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			
			if(NCode == WM_NOTIFICATION_RELEASED)
			{
				if(Id == GUI_ID_BUTTON0)
				{
					HANDLE_LIST *hAPPOnTop;
    
					/* ��ȡ���ϲ�Ĵ��ھ�� */
					hAPPOnTop =	hAPPLinkedList_GetAppTop();
					if(hAPPOnTop != NULL)
					{
						WM_DeleteWindow(hAPPOnTop->hAPP); //	�رմ���
					}
				}
			}	
		break;
		 
		default:
			WM_DefaultProc(pMsg);
		break;
		}			 
}

/**
  * @brief  _cbCtrlWin,�������ص�����
  * @param  none
  * @retval none
  */
static void _cbCtrlWin(WM_MESSAGE * pMsg)
{
	WM_HWIN hItem;	
	WM_HWIN hItemNext;	
	WM_MESSAGE msg;

	 switch (pMsg->MsgId) {			 	 
		case WM_PAINT:	      //�ػ汳��				
			GUI_SetColor(GUI_BLACK);			
			GUI_FillRect(0,0,WM_GetWindowSizeX(pMsg->hWin) ,WM_GetWindowSizeY(pMsg->hWin));			
		break;
		
		case MY_MESSAGE_CTRLCHANGE:
			if(hAPPLinkedList_GetAppTop()==NULL) //���û��app���ڣ����������ʾ��������
			{
				hItem = WM_GetFirstChild(WinPara.hWinCtrl);
				hItemNext = WM_GetNextSibling(hItem);
				
				/* ���ݻص����������ִ��� */
				if(WM_GetCallback(hItem) == _cbIndexWin && WM_GetCallback(hItemNext) == _cbButtonWin)
				{
					/* ��ʾindex���ڣ�����button���� */
					WM_ShowWindow(hItem);
					WM_HideWindow(hItemNext);
					WM_Paint(hItem);	//Ҫ�ػ��������ڣ���������					 
				}
				else if(WM_GetCallback(hItemNext) == _cbIndexWin  && WM_GetCallback(hItem) == _cbButtonWin)
				{
					/* ��ʾindex���ڣ�����button���� */
					WM_ShowWindow(hItemNext);
					WM_HideWindow(hItem);
					WM_Paint(hItemNext);	//Ҫ�ػ��������ڣ���������	
				}		
			}
			else //�������app���ڣ���ʾ���ư�ť����
			{
				hItem = WM_GetFirstChild(WinPara.hWinCtrl);
				hItemNext = WM_GetNextSibling(hItem);
	
				/* ���ݻص����������ִ��� */
				if(WM_GetCallback(hItem) == _cbIndexWin  && WM_GetCallback(hItemNext) == _cbButtonWin)
			 	{
				 /* ��ʾbutton���ڣ�����index���� */
					WM_ShowWindow(hItemNext);
					WM_HideWindow(hItem);
					WM_Paint(hItemNext);	//Ҫ�ػ��������ڣ���������
				}
				else if(WM_GetCallback(hItemNext) == _cbIndexWin  && WM_GetCallback(hItem) == _cbButtonWin)
				{
					/* ��ʾbutton���ڣ�����index���� */
					WM_ShowWindow(hItem);
					WM_HideWindow(hItemNext);
					WM_Paint(hItem);	//Ҫ�ػ��������ڣ���������	
				}

				//msg.MsgId = MY_MESSAGE_STATUSTEXT;
				//msg.hWin = WinPara.hWinStatus;
				//msg.hWinSrc = pMsg->hWin;
				//(char *)(msg.Data.p) =  HOMETITLE;
				//WM_SendMessage(WinPara.hWinStatus, &msg);
			}
		break;				 
		default:		
			WM_DefaultProc(pMsg);
		break;		 
	 }
}

/**
  * @brief  _cbMainWin,�����ڻص�����
  * @param  none
  * @retval none
  */
static void _cbMainWin(WM_MESSAGE * pMsg)
{
	switch (pMsg->MsgId) {
			 
	    case WM_NOTIFY_PARENT:

		break;											
		case WM_PAINT:	              //�ػ汳��
			GUI_SetColor(GUI_BLACK);
			GUI_FillRect(0,0,WinPara.xSizeWin ,WinPara.ySizeWin);
		break;				      
		default:		
			WM_DefaultProc(pMsg);
		break; 
	 }
}

/**
  * @brief  ShowTips��ʾ���û��ȴ�����Ϣ���ڽ���App֮ǰʹ��
  * @param  none
  * @retval none
  */
//static void ShowTips(WM_HWIN hWin)
//{
//		/* ����ȴ���Ϣ */
//		WM_SelectWindow(hWin);
//		GUI_SetColor(GUI_BLACK);
//		GUI_FillRect(0,0,WinPara.xSizeWin *VIRTUAL_WIN_NUM  ,WinPara.ySizeWin);
////		GUI_SetFont(&SDFont.XFont);
//		GUI_SetFont(&GUI_Font13B_ASCII);
//		GUI_SetColor(GUI_WHITE);
//		GUI_DispStringHCenterAt("Please wait...", WinPara.xSizeWin >> 1, WinPara.ySizeWin / 3);
//}


/**
  * @brief  Icon���ڻص�����
  * @param  none
  * @retval none
  */
static void _cbIconWin(WM_MESSAGE * pMsg)
{
	WM_HWIN hWin;
	WM_HWIN hItem;
	WM_HWIN hParent;

	WM_MESSAGE msg;

	int        NCode;
    int        Id;
    int        Sel;
	
	unsigned char i,j;
	hParent = pMsg->hWin;
	
	switch (pMsg->MsgId) {
	
		case WM_CREATE:			
							
				for(i=0;i<VIRTUAL_WIN_NUM;i++)
				{
					/*
					* ����ͼ��ؼ�
					*/			
					hWin = ICONVIEW_CreateEx(
												i*240, 
												5, 
												WinPara.xSizeWin,  
												WinPara.ySizeWin, 
												hParent, WM_CF_SHOW | WM_CF_HASTRANS, 
												0, //������ICONVIEW_CF_AUTOSCROLLBAR_V��Ĭ��Ϊ0
												GUI_ID_ICONVIEW0+i, //icon��ID
												//55, 70 //icon�Ĵ�С
												90,90
												);
									
					/* ����ѡ��ͼ�����ɫ */
					ICONVIEW_SetBkColor(hWin, ICONVIEW_CI_SEL, GUI_BLUE | 0xC0000000);
					/* ����ͼ������� */
					ICONVIEW_SetFont(hWin, &GUI_Font13B_ASCII);
					
					/* ���ó�ʼѡ���ͼ��Ϊ -1 (��ʾ��δѡ��)*/
					ICONVIEW_SetSel(hWin,-1);
				}
				
				/* ���õ�ǰ���� */	
				WinPara.ctr_index = 0;
				
		        /* ��ʾ��һ��ͼ��ҳ */
		        hWin = WM_GetDialogItem(pMsg->hWin,GUI_ID_ICONVIEW0);
				
				/*
				* ���ͼ�굽ͼ��ؼ�
				*/
				for (j = 0 ; j < ICON_PAGE_NUM  && j < GUI_COUNTOF(_aBitmapItem); j++)
				{    
					ICONVIEW_AddBitmapItem(hWin, _aBitmapItem[j].pBitmap, _aBitmapItem[j].pText);
					//ICONVIEW_AddBitmapItem(hWin, _aBitmapItem[j].pBitmap, _aBitmapItem[j].pText, _aBitmapItem[j].index);
				}		

				break;

		case WM_NOTIFY_PARENT:

				Id    = WM_GetId(pMsg->hWinSrc);      // �ؼ���ID
				NCode = pMsg->Data.v;                 // ֪ͨ����
	 
				switch (Id) {
					
					case GUI_ID_ICONVIEW0:								// ͼ��ؼ�0
					
						switch (NCode) 
						{
							case WM_NOTIFICATION_RELEASED:
							//case WM_NOTIFICATION_SEL_CHANGED:
								/*
								* ��ȡ��ǰѡ�е�ͼ��
								*/
								Sel   = ICONVIEW_GetSel(pMsg->hWinSrc);
								
								if(Sel > sizeof(_aBitmapItem))
									break;
								
								(*_aBitmapItem[Sel].pFun)();

							/*
								switch(Sel)
								{										
								case 0:				                          
									WDAGUI_Project(); 
									break;
								case 1:				                          
									WDAGUI_ProjectEdit(); 
									break;
								case 2:				                          
									WDAGUI_Backflow(); 
									break;
								case 3:				                          
									WDAGUI_Purge(); 
									break;
								case 4:				                          
									WDAGUI_Calibration(); 
									break;
								case 5:				                          
									WDAGUI_Information(); 
									break;
								case 6:
									JMGUI_DMX512_Test();
									break;									
								case 7:
									JMGUI_DMX512_Setting();									
									break;	                      
								case 8:				                          
									WFGUI_UserAPP(); 
									break;
								default:
									break;
								}	
								*/
								//msg.MsgId = MY_MESSAGE_STATUSTEXT;
								//msg.hWin = WinPara.hWinStatus;
								//msg.hWinSrc = hParent;
								//(const char *)(msg.Data.p) =  _aBitmapItem[Sel].pText;
								//WM_SendMessage(WinPara.hWinStatus, &msg);

								/* ��ȡICON�ľ�� */
								hItem = WM_GetDialogItem(hParent, GUI_ID_ICONVIEW0);
							
								/* ���ó�ʼѡ���ͼ��Ϊ -1 (��ʾ��δѡ��)*/
								ICONVIEW_SetSel(hItem,-1);											
							break;//WM_NOTIFICATION_RELEASED
						}//NCODE					
				break;//ICONVIEW0
			   }
			break;
	 case WM_PAINT:	//�ػ汳��
		GUI_SetColor(GUI_BLACK);
		GUI_FillRect(0,0,WinPara.xSizeWin *VIRTUAL_WIN_NUM  ,WinPara.ySizeWin);
	 break;				//WM_PAINT	 
	 default:		
		WM_DefaultProc(pMsg);
	 break;
		}
}

/**
  * @brief  SetDefaultSkin,����gui��Ĭ��Ƥ��
	*					
  * @param  none
  * @retval none
  */
static void SetDefaultSkin(void)
{
	/* ���ø��ֿؼ���Ƥ��Ϊ��win7��Ƥ�� */
	BUTTON_SetDefaultSkin   (BUTTON_SKIN_FLEX);
	CHECKBOX_SetDefaultSkin (CHECKBOX_SKIN_FLEX);
	DROPDOWN_SetDefaultSkin (DROPDOWN_SKIN_FLEX);
	FRAMEWIN_SetDefaultSkin (FRAMEWIN_SKIN_FLEX);
	HEADER_SetDefaultSkin   (HEADER_SKIN_FLEX);
	PROGBAR_SetDefaultSkin  (PROGBAR_SKIN_FLEX);
	RADIO_SetDefaultSkin    (RADIO_SKIN_FLEX);
	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
	SLIDER_SetDefaultSkin   (SLIDER_SKIN_FLEX);
	
	/* ���û����� */
	SCROLLBAR_SetDefaultWidth(15);						//���
	SCROLLBAR_SetThumbSizeMin(10);						//������Сsize	
	
	/* ����Ĭ������ */
	BUTTON_SetDefaultFont(&GUI_Font24_ASCII);
	TEXT_SetDefaultFont(&GUI_Font24_ASCII);
	DROPDOWN_SetDefaultFont(&GUI_Font24_ASCII);
	EDIT_SetDefaultFont(&GUI_Font24_ASCII);

	/* ����framwin  */
	FRAMEWIN_SetDefaultTitleHeight(20);					//�������߶�
	//FRAMEWIN_SetDefaultFont(GUI_FONT_8X16);			//Ĭ������
	FRAMEWIN_SetDefaultFont(&GUI_Font24_ASCII);
	FRAMEWIN_SetDefaultTextColor(1,GUI_BLACK); 	//���ü���״̬ʱ�ı���������ɫ
	WM_SetDesktopColor(GUI_BLACK);
}

/**
  * @brief  CreatStatusWin������������״̬��
  * @param  none
  * @retval none
  */
static void CreatStatusWin(void)
{
	//WM_HWIN hText;
	WM_HWIN hButton;

	WinPara.hWinStatus = WM_CreateWindowAsChild(
													0,				//����λ�á���С
													0,
													WinPara.xSizeLCD,
													WinPara.yPosWin,	
													WM_HBKWIN, WM_CF_SHOW | WM_CF_MEMDEV, _cbStatusWin, sizeof(WIN_PARA *)
												);
	
	/* ������ ���� �ı� */
	hStatusText = TEXT_CreateEx(
		0,
		0,
		WinPara.xSizeWin, 
		WinPara.ySizeWinStatus, 
		WinPara.hWinStatus, WM_CF_SHOW, GUI_TA_HCENTER|TEXT_CF_VCENTER, GUI_ID_TEXT1, HOMETITLE);
    TEXT_SetFont(hStatusText, &GUI_Font24_ASCII);
    TEXT_SetTextColor(hStatusText, 0xFF4040);
	
	/* ����Logo ��ť */
	hButton = BUTTON_CreateEx(2,0,40,20,WinPara.hWinStatus,WM_CF_SHOW,0,GUI_ID_BUTTON0);
	BUTTON_SetBitmap(hButton,BUTTON_BI_UNPRESSED,&bmJoinmax_Logo);
	//BUTTON_SetBitmap(hButton,BUTTON_BI_PRESSED,&bmJoinmax_Logo);
	BUTTON_SetBitmap(hButton,BUTTON_BI_PRESSED,&bmWF_Logo);	
}



/**
  * @brief  CreatCtrlWin�������ײ��Ŀ�����
  * @param  none
  * @retval none
  */
static void CreatCtrlWin(void)
{
	WM_HWIN hButtonWin;
	
	WinPara.hWinCtrl = WM_CreateWindowAsChild(
												0,											
												WinPara.yPosWin + WinPara.ySizeWin ,	//�ײ�λ��
												WinPara.xSizeLCD,
												WinPara.ySizeLCD - (WinPara.yPosWin + WinPara.ySizeWin),	//�ײ�ʣ����
												WM_HBKWIN, WM_CF_SHOW | WM_CF_MEMDEV, _cbCtrlWin, sizeof(WIN_PARA *)
											);
	
	/* ������������ (��СԲ���ʾ��ǰ��ͼ��ҳ��)*/
	WM_CreateWindowAsChild(
							0,
							0,
							WM_GetWindowSizeX(WinPara.hWinCtrl),
							WM_GetWindowSizeY(WinPara.hWinCtrl),
							WinPara.hWinCtrl,
							WM_CF_SHOW, _cbIndexWin, 0);
													
	/* ��������button����(��button��Ӧ�ó���״̬�� ����ʾ���ذ�ť) */
	hButtonWin = WM_CreateWindowAsChild(
							0,
							0,
							WM_GetWindowSizeX(WinPara.hWinCtrl),
							WM_GetWindowSizeY(WinPara.hWinCtrl),
							WinPara.hWinCtrl,WM_CF_SHOW,_cbButtonWin,0);

	/* Ĭ������button���� */	
	GUI_Delay(10);	
	WM_HideWindow(hButtonWin);
	GUI_Delay(10);													
}


/**
  * @brief  CreatMainWin����������ʾ����
  * @param  none
  * @retval none
  */
static void CreatMainWin(void)
{
	WinPara.hWinMain = WM_CreateWindowAsChild(
												WinPara.xPosWin ,											
												WinPara.yPosWin ,	//λ��
												WinPara.xSizeWin,
												WinPara.ySizeWin,	//�ײ�ʣ����
												WM_HBKWIN, 
												WM_CF_SHOW | WM_CF_MEMDEV, _cbMainWin, sizeof(WIN_PARA *)
												);	
		/* ����iconͼ�괰�� */
	 WM_CreateWindowAsChild(	0 ,											
								0 ,	//λ��
								WinPara.xSizeWin * VIRTUAL_WIN_NUM,
								WinPara.ySizeWin,	//��
								WinPara.hWinMain,
								//WM_CF_SHOW | WM_CF_MEMDEV|WM_CF_MOTION_X,
								WM_CF_SHOW | WM_CF_MEMDEV|ICONVIEW_CF_AUTOSCROLLBAR_V,
								_cbIconWin,
								0
							);
}

uint8_t proData[] = { 
	0xF0,0xF4,0x50,0x72,0x6F,0x6A,0x65,0x63,0x74,0x30,0xF5,0xF2,0xF4,0x41,0x63,0x74,0x69,0x6F,0x6E,0x30,0xF5,0x01,0x01,0x0A,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0xF3,0xF1,
	0xF0,0xF4,0x50,0x72,0x6F,0x6A,0x65,0x63,0x74,0x31,0xF5,0xF2,0xF4,0x41,0x63,0x74,0x69,0x6F,0x6E,0x30,0xF5,0x01,0x01,0x0A,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0xF3,0xF1,
	0xF0,0xF4,0x50,0x72,0x6F,0x6A,0x65,0x63,0x74,0x32,0xF5,0xF2,0xF4,0x41,0x63,0x74,0x69,0x6F,0x6E,0x30,0xF5,0x01,0x01,0x0A,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0xF3,0xF1,
	0xF0,0xF4,0x50,0x72,0x6F,0x6A,0x65,0x63,0x74,0x33,0xF5,0xF2,0xF4,0x41,0x63,0x74,0x69,0x6F,0x6E,0x30,0xF5,0x01,0x01,0x0A,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0xF3,0xF1,
	0xF0,0xF4,0x50,0x72,0x6F,0x6A,0x65,0x63,0x74,0x34,0xF5,0xF2,0xF4,0x41,0x63,0x74,0x69,0x6F,0x6E,0x30,0xF5,0x01,0x01,0x0A,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0xF3,0xF1,
	0xF0,0xF4,0x50,0x72,0x6F,0x6A,0x65,0x63,0x74,0x35,0xF5,0xF2,0xF4,0x41,0x63,0x74,0x69,0x6F,0x6E,0x30,0xF5,0x01,0x01,0x0A,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0xF3,0xF1,
};
uint16_t proDataLen = sizeof(proData);

/**
  * @brief  CreatDeskTop������gui����
  * @param  none
  * @retval none
  */
static void CreatDeskTop(void)
{
	//׼������3�����ڣ�������ʹ�õ����û���������������ڻص�������ʹ��
	WinPara.xSizeLCD = LCD_GetXSize();						//LCD��Ļ�ߴ�
	WinPara.ySizeLCD = LCD_GetYSize();						//LCD��Ļ�ߴ�
	WinPara.ySizeWinStatus = 20;
	WinPara.ySizeWinCtrl = 30;
	WinPara.xSizeWin = WinPara.xSizeLCD;					//���ڳߴ�
	WinPara.ySizeWin = WinPara.ySizeLCD - WinPara.ySizeWinStatus - WinPara.ySizeWinCtrl;//���ڳߴ� ��Ļ��С��ȥ״̬���Ϳ�����
	WinPara.xPosWin	 = 0;													//���ڵ���ʼλ��
	WinPara.yPosWin  = WinPara.ySizeWinStatus;								//���ڵ���ʼλ��
	WinPara.xSizeWinVirtual = WinPara.xSizeWin * VIRTUAL_WIN_NUM;	//���ⴰ�ڳߴ磬��������

	/* ����Ĭ��Ƥ�� */
	SetDefaultSkin();
	
	WM_EnableMemdev(WM_HBKWIN);
	
	/* ���ñ�������Ļص����� */
	WM_SetCallback(WM_HBKWIN, _cbBKWin);//ֻ�����ػ汳��
	
	/* ������������ ״̬������������������*/
	CreatStatusWin();
	CreatCtrlWin();
	CreatMainWin();
	
	/* ��ʼ��app���� */													
	hAPPLinkedList_Init();
	parseProData(proData, sizeof(proData));
}


/*********************************************************************
*
*       Public routines
*				���к���
*
**********************************************************************
*/

/**
  * @brief  WFGUI_MainTask,WFGUI������
  * @param  none
  * @retval none
  */
void WFGUI_MainTask(void) {
  
	//WM_MOTION_Enable(1);
	//WM_MOTION_SetDefaultPeriod(1000);
	
	CreatDeskTop();			//����gui����

	while (1) {

		GUI_Delay(50);

	}
}

/*************************** End of file ****************************/

