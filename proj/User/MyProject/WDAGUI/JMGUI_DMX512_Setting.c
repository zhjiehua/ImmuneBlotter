/**
  ******************************************************************************
  * @file    JMGUI_DMX512.c
  * @author  jiehua
  * @version V1.0
  * @date    2014-xx-xx
  * @brief   DMX512�ź����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� ��� ������ 
  * 
  * 
  *
  ******************************************************************************
  */

#include "JMGUI_DMX512_Setting.h"
#include "WFGUI_Phone.h"
//#include "usart.h"

static const Edit_TypeDef _aEditData[] =
{
	{100,0,140,90,"Addr",GUI_ID_EDIT0,GUI_WHITE},
	{100,90,140,90,"LampNum",GUI_ID_EDIT1,GUI_WHITE},
	{100,90,140,100,"ChannelNum",GUI_ID_EDIT2,GUI_WHITE},
};

/*DMX512���Խṹ��*/
DMX512_TypeDef DMX512_Attr = {1, 10, 3};

int edit_id;

  /**
  * @brief  _GetEditLabel,��_aEditData������Ҹ�Id��Label
  * @param  Id
  * @retval Label
  */
static char* _GetEditLabel(int Id)
{
	int i;
	for(i=0;i<GUI_COUNTOF(_aEditData);i++)
	{
		if(_aEditData[i].Id == Id)
		return _aEditData[i].acLabel;
	}
	return NULL;
}


  /**
  * @brief  _cbDMX512,DMX512���ڻص�����
  * @param  none
  * @retval none
  */
static void _cbDMX512(WM_MESSAGE * pMsg)
{
	
	WM_HWIN hWin;
//	WM_HWIN hButton; 
//	WM_HWIN hPhone;
//	WM_HWIN hEdit;
	
	int xSize,ySize;
	
	int Id ;
	int NCode;	
	
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

		case WM_NOTIFY_PARENT:
			
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			
			if(NCode == WM_NOTIFICATION_RELEASED )
			{
				if(Id == GUI_ID_EDIT0)
				{
					char *lb, text[20];
					edit_id = GUI_ID_EDIT0; //��¼���ڱ༭�����Ǹ��ؼ�
					lb = _GetEditLabel(GUI_ID_EDIT0);
					sprintf(text, "%d", DMX512_Attr.Addr );
					WFGUI_Phone(lb, text, hWin);  //���ü��̴���
				}
				else if(Id == GUI_ID_EDIT1)
				{
					char *lb, text[20];
					edit_id = GUI_ID_EDIT1; //��¼���ڱ༭�����Ǹ��ؼ�
					lb = _GetEditLabel(GUI_ID_EDIT1);
					sprintf(text, "%d", DMX512_Attr.LampNum );
					WFGUI_Phone(lb, text, hWin);  //���ü��̴���
				}
				else if(Id == GUI_ID_EDIT2)
				{
					char *lb, text[20];
					edit_id = GUI_ID_EDIT2; //��¼���ڱ༭�����Ǹ��ؼ�
					lb = _GetEditLabel(GUI_ID_EDIT2);
					sprintf(text, "%d", DMX512_Attr.ChannelNum );
					WFGUI_Phone(lb, text, hWin);  //���ü��̴���
				}
			}

			if(NCode == WM_NOTIFICATION_CHILD_DELETED)
			{
				if(ok_flag == 1)//�ǰ���OK��
				{
					uint32_t temp;					
					WM_HWIN hFirstChild;

					ok_flag = 0;

					switch(edit_id)
					{
						case GUI_ID_EDIT0:
							temp = atoi(s); //���ַ���ת��������, �ַ���s�����Լ����ļ���ȫ�ֱ���
							DMX512_Attr.Addr = temp; //����DMX512�ṹ����

							hFirstChild = WM_GetFirstChild(pMsg->hWin);//��ȡEDIT0����(Addr)�ľ��
							EDIT_SetText(hFirstChild, s); //��EDITд��DMX512.Addr����								
						break;
						case GUI_ID_EDIT1:
							temp = atoi(s); //���ַ���ת��������
							DMX512_Attr.LampNum = temp; //����DMX512�ṹ����

							hFirstChild = WM_GetFirstChild(pMsg->hWin);//��ȡEDIT0����(Addr)�ľ��
							hFirstChild = WM_GetNextSibling(hFirstChild);
							EDIT_SetText(hFirstChild, s); //��EDITд��DMX512.Addr����								
						break;
						case GUI_ID_EDIT2:
							temp = atoi(s); //���ַ���ת��������
							DMX512_Attr.ChannelNum = temp; //����DMX512�ṹ����

							hFirstChild = WM_GetFirstChild(pMsg->hWin);//��ȡEDIT0����(Addr)�ľ��
							hFirstChild = WM_GetNextSibling(hFirstChild);
							hFirstChild = WM_GetNextSibling(hFirstChild);
							EDIT_SetText(hFirstChild, s); //��EDITд��DMX512.Addr����								
						break;
					}
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
  * @brief  JMGUI_DMX512,DMX512�źŷ���
  * @param  none
  * @retval none
  */
  void JMGUI_DMX512_Setting(void)
  {
  	WM_HWIN hEdit, hText;
	char str[20];
	
	HANDLE_LIST *hDMX512 = hAPPLinkedList_NewNode();

	
	/* ����DMX512���Դ��� */
	hDMX512->hAPP = WM_CreateWindowAsChild(0, 0, WinPara.xSizeWin,WinPara.ySizeWin ,WinPara.hWinMain , WM_CF_SHOW | WM_CF_STAYONTOP, _cbDMX512, 0);	


	/* ������ַ���� */	
	hEdit	= EDIT_CreateEx(100,0,140,90,hDMX512->hAPP,WM_CF_SHOW,0,GUI_ID_EDIT0,20);	
	/* �����ı� */
	sprintf(str, "%d", DMX512_Attr.Addr);
	EDIT_SetText(hEdit, str);
	/* �����ı��򱳾� */
	EDIT_SetBkColor(hEdit,EDIT_CI_ENABLED,GUI_DARKGRAY);
	/* �����ı����� */
	EDIT_SetFont(hEdit,GUI_FONT_24B_ASCII);	
	/* ����������ɫ */
	EDIT_SetTextColor(hEdit,EDIT_CI_ENABLED,GUI_WHITE);	
	/* �����ı����뷽ʽ */
	EDIT_SetTextAlign(hEdit,TEXT_CF_HCENTER|TEXT_CF_VCENTER);

	/* �����ƾ��������� */	
	hEdit	= EDIT_CreateEx(100,90,140,90,hDMX512->hAPP,WM_CF_SHOW,0,GUI_ID_EDIT1,20);	
	/* �����ı� */
	sprintf(str, "%d", DMX512_Attr.LampNum);
	EDIT_SetText(hEdit, str);
	/* �����ı��򱳾� */
	EDIT_SetBkColor(hEdit,EDIT_CI_ENABLED,GUI_DARKGRAY);
	/* �����ı����� */
	EDIT_SetFont(hEdit,GUI_FONT_24B_ASCII);	
	/* ����������ɫ */
	EDIT_SetTextColor(hEdit,EDIT_CI_ENABLED,GUI_WHITE);	
	/* �����ı����뷽ʽ */
	EDIT_SetTextAlign(hEdit,TEXT_CF_HCENTER|TEXT_CF_VCENTER);

	/* ����ͨ�������� */	
	hEdit	= EDIT_CreateEx(100,180,140,100,hDMX512->hAPP,WM_CF_SHOW,0,GUI_ID_EDIT2,20);	
	/* �����ı� */
	sprintf(str, "%d", DMX512_Attr.ChannelNum);
	EDIT_SetText(hEdit, str);
	/* �����ı��򱳾� */
	EDIT_SetBkColor(hEdit,EDIT_CI_ENABLED,GUI_DARKGRAY);
	/* �����ı����� */
	EDIT_SetFont(hEdit,GUI_FONT_24B_ASCII);	
	/* ����������ɫ */
	EDIT_SetTextColor(hEdit,EDIT_CI_ENABLED,GUI_WHITE);	
	/* �����ı����뷽ʽ */
	EDIT_SetTextAlign(hEdit,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
	



	/* ������ַ�ı���ʾ���� */	
	hText = TEXT_CreateEx(0,0,100,90,hDMX512->hAPP,WM_CF_SHOW,TEXT_CF_HCENTER|TEXT_CF_VCENTER,GUI_ID_TEXT0,_aEditData[0].acLabel);	
	/* �����ı��򱳾� */
	TEXT_SetBkColor(hText,GUI_DARKGRAY);	
	/* �����ı����� */
	TEXT_SetFont(hText,GUI_FONT_13B_ASCII);	
	/* ����������ɫ */
	TEXT_SetTextColor(hText, GUI_BLACK);	
	/* �����ı����뷽ʽ */
	TEXT_SetTextAlign(hText,TEXT_CF_HCENTER|TEXT_CF_VCENTER);

	/* �����ƾ������ı���ʾ���� */	
	hText = TEXT_CreateEx(0,90,100,90,hDMX512->hAPP,WM_CF_SHOW,TEXT_CF_HCENTER|TEXT_CF_VCENTER,GUI_ID_TEXT1,_aEditData[1].acLabel);	
	/* �����ı��򱳾� */
	TEXT_SetBkColor(hText,GUI_DARKGRAY);	
	/* �����ı����� */
	TEXT_SetFont(hText,GUI_FONT_13B_ASCII);	
	/* ����������ɫ */
	TEXT_SetTextColor(hText, GUI_BLACK);	
	/* �����ı����뷽ʽ */
	TEXT_SetTextAlign(hText,TEXT_CF_HCENTER|TEXT_CF_VCENTER);

	/* ����ͨ�����ı���ʾ���� */	
	hText = TEXT_CreateEx(0,180,100,100,hDMX512->hAPP,WM_CF_SHOW,TEXT_CF_HCENTER|TEXT_CF_VCENTER,GUI_ID_TEXT2,_aEditData[2].acLabel);	
	/* �����ı��򱳾� */
	TEXT_SetBkColor(hText,GUI_DARKGRAY);	
	/* �����ı����� */
	TEXT_SetFont(hText,GUI_FONT_13B_ASCII);	
	/* ����������ɫ */
	TEXT_SetTextColor(hText, GUI_BLACK);	
	/* �����ı����뷽ʽ */
	TEXT_SetTextAlign(hText,TEXT_CF_HCENTER|TEXT_CF_VCENTER);



	/* ���ô��ھ۽� */
	WM_SetFocus(hEdit);	 //���ǳ���Ҫ����Ϊ����İ������͵����ݶ��Ƿ��͵�Ŀǰ�۽��Ŀؼ�

	/* ��ӽ�㵽���� */
	hAPPLinkedList_AddTail(hDMX512);
	/* ��ctrl���ڷ�����Ϣ */
	WM_SendMessageNoPara(WinPara.hWinCtrl,MY_MESSAGE_CTRLCHANGE);

	WM_SetFocus(hEdit);	//�ٴξ۽�	
  }


