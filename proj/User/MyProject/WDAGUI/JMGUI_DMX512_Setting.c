/**
  ******************************************************************************
  * @file    JMGUI_DMX512.c
  * @author  jiehua
  * @version V1.0
  * @date    2014-xx-xx
  * @brief   DMX512信号输出
  ******************************************************************************
  * @attention
  *
  * 实验平台:神州 Ⅲ号 开发板 
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

/*DMX512属性结构体*/
DMX512_TypeDef DMX512_Attr = {1, 10, 3};

int edit_id;

  /**
  * @brief  _GetEditLabel,从_aEditData数组查找该Id的Label
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
  * @brief  _cbDMX512,DMX512窗口回调函数
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

		case WM_NOTIFY_PARENT:
			
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			
			if(NCode == WM_NOTIFICATION_RELEASED )
			{
				if(Id == GUI_ID_EDIT0)
				{
					char *lb, text[20];
					edit_id = GUI_ID_EDIT0; //记录现在编辑的是那个控件
					lb = _GetEditLabel(GUI_ID_EDIT0);
					sprintf(text, "%d", DMX512_Attr.Addr );
					WFGUI_Phone(lb, text, hWin);  //调用键盘窗口
				}
				else if(Id == GUI_ID_EDIT1)
				{
					char *lb, text[20];
					edit_id = GUI_ID_EDIT1; //记录现在编辑的是那个控件
					lb = _GetEditLabel(GUI_ID_EDIT1);
					sprintf(text, "%d", DMX512_Attr.LampNum );
					WFGUI_Phone(lb, text, hWin);  //调用键盘窗口
				}
				else if(Id == GUI_ID_EDIT2)
				{
					char *lb, text[20];
					edit_id = GUI_ID_EDIT2; //记录现在编辑的是那个控件
					lb = _GetEditLabel(GUI_ID_EDIT2);
					sprintf(text, "%d", DMX512_Attr.ChannelNum );
					WFGUI_Phone(lb, text, hWin);  //调用键盘窗口
				}
			}

			if(NCode == WM_NOTIFICATION_CHILD_DELETED)
			{
				if(ok_flag == 1)//是按下OK键
				{
					uint32_t temp;					
					WM_HWIN hFirstChild;

					ok_flag = 0;

					switch(edit_id)
					{
						case GUI_ID_EDIT0:
							temp = atoi(s); //将字符串转换成整型, 字符串s是来自键盘文件的全局变量
							DMX512_Attr.Addr = temp; //更新DMX512结构数据

							hFirstChild = WM_GetFirstChild(pMsg->hWin);//获取EDIT0窗口(Addr)的句柄
							EDIT_SetText(hFirstChild, s); //向EDIT写入DMX512.Addr数据								
						break;
						case GUI_ID_EDIT1:
							temp = atoi(s); //将字符串转换成整型
							DMX512_Attr.LampNum = temp; //更新DMX512结构数据

							hFirstChild = WM_GetFirstChild(pMsg->hWin);//获取EDIT0窗口(Addr)的句柄
							hFirstChild = WM_GetNextSibling(hFirstChild);
							EDIT_SetText(hFirstChild, s); //向EDIT写入DMX512.Addr数据								
						break;
						case GUI_ID_EDIT2:
							temp = atoi(s); //将字符串转换成整型
							DMX512_Attr.ChannelNum = temp; //更新DMX512结构数据

							hFirstChild = WM_GetFirstChild(pMsg->hWin);//获取EDIT0窗口(Addr)的句柄
							hFirstChild = WM_GetNextSibling(hFirstChild);
							hFirstChild = WM_GetNextSibling(hFirstChild);
							EDIT_SetText(hFirstChild, s); //向EDIT写入DMX512.Addr数据								
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
  * @brief  JMGUI_DMX512,DMX512信号发送
  * @param  none
  * @retval none
  */
  void JMGUI_DMX512_Setting(void)
  {
  	WM_HWIN hEdit, hText;
	char str[20];
	
	HANDLE_LIST *hDMX512 = hAPPLinkedList_NewNode();

	
	/* 创建DMX512属性窗口 */
	hDMX512->hAPP = WM_CreateWindowAsChild(0, 0, WinPara.xSizeWin,WinPara.ySizeWin ,WinPara.hWinMain , WM_CF_SHOW | WM_CF_STAYONTOP, _cbDMX512, 0);	


	/* 创建地址窗口 */	
	hEdit	= EDIT_CreateEx(100,0,140,90,hDMX512->hAPP,WM_CF_SHOW,0,GUI_ID_EDIT0,20);	
	/* 设置文本 */
	sprintf(str, "%d", DMX512_Attr.Addr);
	EDIT_SetText(hEdit, str);
	/* 设置文本框背景 */
	EDIT_SetBkColor(hEdit,EDIT_CI_ENABLED,GUI_DARKGRAY);
	/* 设置文本字体 */
	EDIT_SetFont(hEdit,GUI_FONT_24B_ASCII);	
	/* 设置字体颜色 */
	EDIT_SetTextColor(hEdit,EDIT_CI_ENABLED,GUI_WHITE);	
	/* 设置文本对齐方式 */
	EDIT_SetTextAlign(hEdit,TEXT_CF_HCENTER|TEXT_CF_VCENTER);

	/* 创建灯具数量窗口 */	
	hEdit	= EDIT_CreateEx(100,90,140,90,hDMX512->hAPP,WM_CF_SHOW,0,GUI_ID_EDIT1,20);	
	/* 设置文本 */
	sprintf(str, "%d", DMX512_Attr.LampNum);
	EDIT_SetText(hEdit, str);
	/* 设置文本框背景 */
	EDIT_SetBkColor(hEdit,EDIT_CI_ENABLED,GUI_DARKGRAY);
	/* 设置文本字体 */
	EDIT_SetFont(hEdit,GUI_FONT_24B_ASCII);	
	/* 设置字体颜色 */
	EDIT_SetTextColor(hEdit,EDIT_CI_ENABLED,GUI_WHITE);	
	/* 设置文本对齐方式 */
	EDIT_SetTextAlign(hEdit,TEXT_CF_HCENTER|TEXT_CF_VCENTER);

	/* 创建通道数窗口 */	
	hEdit	= EDIT_CreateEx(100,180,140,100,hDMX512->hAPP,WM_CF_SHOW,0,GUI_ID_EDIT2,20);	
	/* 设置文本 */
	sprintf(str, "%d", DMX512_Attr.ChannelNum);
	EDIT_SetText(hEdit, str);
	/* 设置文本框背景 */
	EDIT_SetBkColor(hEdit,EDIT_CI_ENABLED,GUI_DARKGRAY);
	/* 设置文本字体 */
	EDIT_SetFont(hEdit,GUI_FONT_24B_ASCII);	
	/* 设置字体颜色 */
	EDIT_SetTextColor(hEdit,EDIT_CI_ENABLED,GUI_WHITE);	
	/* 设置文本对齐方式 */
	EDIT_SetTextAlign(hEdit,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
	



	/* 创建地址文本显示窗口 */	
	hText = TEXT_CreateEx(0,0,100,90,hDMX512->hAPP,WM_CF_SHOW,TEXT_CF_HCENTER|TEXT_CF_VCENTER,GUI_ID_TEXT0,_aEditData[0].acLabel);	
	/* 设置文本框背景 */
	TEXT_SetBkColor(hText,GUI_DARKGRAY);	
	/* 设置文本字体 */
	TEXT_SetFont(hText,GUI_FONT_13B_ASCII);	
	/* 设置字体颜色 */
	TEXT_SetTextColor(hText, GUI_BLACK);	
	/* 设置文本对齐方式 */
	TEXT_SetTextAlign(hText,TEXT_CF_HCENTER|TEXT_CF_VCENTER);

	/* 创建灯具数量文本显示窗口 */	
	hText = TEXT_CreateEx(0,90,100,90,hDMX512->hAPP,WM_CF_SHOW,TEXT_CF_HCENTER|TEXT_CF_VCENTER,GUI_ID_TEXT1,_aEditData[1].acLabel);	
	/* 设置文本框背景 */
	TEXT_SetBkColor(hText,GUI_DARKGRAY);	
	/* 设置文本字体 */
	TEXT_SetFont(hText,GUI_FONT_13B_ASCII);	
	/* 设置字体颜色 */
	TEXT_SetTextColor(hText, GUI_BLACK);	
	/* 设置文本对齐方式 */
	TEXT_SetTextAlign(hText,TEXT_CF_HCENTER|TEXT_CF_VCENTER);

	/* 创建通道数文本显示窗口 */	
	hText = TEXT_CreateEx(0,180,100,100,hDMX512->hAPP,WM_CF_SHOW,TEXT_CF_HCENTER|TEXT_CF_VCENTER,GUI_ID_TEXT2,_aEditData[2].acLabel);	
	/* 设置文本框背景 */
	TEXT_SetBkColor(hText,GUI_DARKGRAY);	
	/* 设置文本字体 */
	TEXT_SetFont(hText,GUI_FONT_13B_ASCII);	
	/* 设置字体颜色 */
	TEXT_SetTextColor(hText, GUI_BLACK);	
	/* 设置文本对齐方式 */
	TEXT_SetTextAlign(hText,TEXT_CF_HCENTER|TEXT_CF_VCENTER);



	/* 设置窗口聚焦 */
	WM_SetFocus(hEdit);	 //这句非常重要，因为后面的按键发送的数据都是发送到目前聚焦的控件

	/* 添加结点到链表 */
	hAPPLinkedList_AddTail(hDMX512);
	/* 向ctrl窗口发送消息 */
	WM_SendMessageNoPara(WinPara.hWinCtrl,MY_MESSAGE_CTRLCHANGE);

	WM_SetFocus(hEdit);	//再次聚焦	
  }


