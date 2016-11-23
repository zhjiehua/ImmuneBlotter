/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.16                          *
*        Compiled Jun  4 2012, 15:48:59                              *
*        (c) 2011 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"
#include "JMGUI_DMX512_Test.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#define ID_WINDOW_0  (GUI_ID_USER + 0x00)
#define ID_RADIO_0  (GUI_ID_USER + 0x01)
#define ID_BUTTON_0  (GUI_ID_USER + 0x02)
#define ID_BUTTON_1  (GUI_ID_USER + 0x03)

// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

int radio_id; //��¼��ѡ��ѡ��������ʲô
uint8_t ok_test_flag; //ok��������

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 240, 280, 0, 0, 0 },
  { RADIO_CreateIndirect, "Radio", ID_RADIO_0, 9, 15, 80, 249, 0, 6410, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 112, 81, 100, 40, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 112, 154, 100, 40, 0, 0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int Id, NCode;
  // USER START (Optionally insert additional variables)
    HANDLE_LIST *appNode;
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Window'
    //
    hItem = pMsg->hWin;
    WINDOW_SetBkColor(hItem, 0x00C0C0C0);
    //
    // Initialization of 'Radio'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_RADIO_0);
    RADIO_SetText(hItem, "Red", 0);
    RADIO_SetText(hItem, "Green", 1);
    RADIO_SetText(hItem, "Blue", 2);
    RADIO_SetText(hItem, "White", 3);
    RADIO_SetText(hItem, "Flow1", 4);
    RADIO_SetText(hItem, "Flow2", 5);
    RADIO_SetText(hItem, "Color", 6);
    RADIO_SetText(hItem, "None", 7);
    RADIO_SetText(hItem, "Star", 8);
    RADIO_SetText(hItem, "Flip", 9);
    RADIO_SetFont(hItem, GUI_FONT_16B_ASCII);
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetText(hItem, "OK");
    BUTTON_SetFont(hItem, GUI_FONT_24B_ASCII);
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetText(hItem, "CANCEL");
    BUTTON_SetFont(hItem, GUI_FONT_24B_ASCII);
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;

	  case WM_DELETE:
	     /* ��ȡapp�����Ӧ��������� */
		appNode = hAPPLinkedList_GetAppNode(pMsg->hWin);
		if(appNode != NULL)
		{
			/* ɾ��app���������ļ�¼ */	
			hAPPLinkedList_Del(appNode);
		
			/* ������Ϣ֪ͨctrl����*/		
			WM_SendMessageNoPara(WinPara.hWinCtrl,MY_MESSAGE_CTRLCHANGE);	
		}
	    
	  break;


  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_RADIO_0: // Notifications sent by 'Radio'
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
    case ID_BUTTON_0: // Notifications sent by 'ok'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
		{
			WM_HWIN hItem;
			hItem = WM_GetDialogItem(pMsg->hWin, ID_RADIO_0);

			ok_test_flag = 1;
			radio_id = RADIO_GetValue(hItem);
//			printf("radio_id = %d\r\n",radio_id);
		}
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'cancel'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
		ok_test_flag = 0;
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

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateWindow
*/

void JMGUI_DMX512_Test(void) {

  HANDLE_LIST *hDMX512_Test = hAPPLinkedList_NewNode(); //������β�˷���һ���ڵ�

  hDMX512_Test->hAPP = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbDialog, WinPara.hWinMain, 0, 0);
   printf("hDMX512_Test->hAPP = %d\r\n",hDMX512_Test->hAPP);
  	/* ���ӽ�㵽���� */
	hAPPLinkedList_AddTail(hDMX512_Test);
	/* ��ctrl���ڷ�����Ϣ */
	WM_SendMessageNoPara(WinPara.hWinCtrl,MY_MESSAGE_CTRLCHANGE);

	WM_SetFocus(hDMX512_Test->hAPP);	//�ٴξ۽�
  //return hDMX512_Test->hAPP;
}

// USER START (Optionally insert additional public code)

/*���DMX512�ź�*/
void DMX512_Test(void)
{
	//int* pdata = 0;
	if(ok_test_flag)//ok������
	{
		switch(radio_id)//�жϵ�ѡ��ѡ����ʲô����
		{				
			case 0:
				//RTest(pdata);
				DEBUG("RTest\n");
			break;
			case 1:
				//GTest(pdata);
				DEBUG("GTest\n");
			break;
			case 2:
				//BTest(pdata);
				DEBUG("BTest\n");
			break;
			case 3:
				//WTest(pdata);
				DEBUG("WTest\n");
			break;
			case 4:
				//Flow1Test(pdata);
				DEBUG("Flow1Test\n");
			break;
			case 5:
				//Flow2Test(pdata);
				DEBUG("Flow2Test\n");
			break;
			case 6:
				//ColorTest(pdata);
				DEBUG("ColorTest\n");
			break;
			case 7:
				//NoneTest(pdata);
				DEBUG("NoneTest\n");
			break;
			case 8:
				
			break;
			case 9:

			break;
			default:
			break;
		}
	}
}

// USER END

/*************************** End of file ****************************/