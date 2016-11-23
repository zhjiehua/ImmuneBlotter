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

#include "WDAGUI_Action.h"
#include "WFGUI_Common.h"

static ACTEDIT_MAN curActTemp;

void createAction(WM_HWIN hWin)
{
	WM_HWIN hWin_Temp;
	TEXT_Handle hText_Temp;
	DROPDOWN_Handle hDropdown_Temp;
	EDIT_Handle hEdit_Temp;

	int xSizeWin = WM_GetWindowSizeX(hWin);
	int ySizeWin = WM_GetWindowSizeY(hWin);

	char strTemp[10];

	//复制参数到pCurActTemp
	memcpy(&curActTemp, pCurAct, sizeof(ACTEDIT_MAN));

//==============================泵=================================
	hText_Temp = TEXT_CreateEx(
		0,
		0,
		xSizeWin/2,
		ySizeWin/9,
		hWin, WM_CF_SHOW, 0, GUIID_ACT, "Pump");
	//TEXT_SetFont(hText_Temp, &GUI_Font24_ASCII);
	TEXT_SetTextAlign(hText_Temp, TEXT_CF_HCENTER|TEXT_CF_VCENTER);

	hDropdown_Temp = DROPDOWN_CreateEx(
		xSizeWin/2,
		0 + ySizeWin/36,
		xSizeWin/2,
		ySizeWin/9,
		hWin, WM_CF_SHOW, 0, GUIID_ACT_PUMP);
	//DROPDOWN_SetFont(hDropdown_Temp, &GUI_Font24_ASCII);
	DROPDOWN_SetTextAlign(hDropdown_Temp, TEXT_CF_VCENTER);
	DROPDOWN_SetListHeight(hDropdown_Temp, 24*10);
	//DROPDOWN_SetTextHeight(hDropdown_Temp, ySizeWin/9);
	DROPDOWN_InsertString(hDropdown_Temp, "0", 0);
	DROPDOWN_InsertString(hDropdown_Temp, "1", 1);
	DROPDOWN_InsertString(hDropdown_Temp, "2", 2);
	DROPDOWN_InsertString(hDropdown_Temp, "3", 3);
	DROPDOWN_InsertString(hDropdown_Temp, "4", 4);
	DROPDOWN_InsertString(hDropdown_Temp, "5", 5);
	DROPDOWN_InsertString(hDropdown_Temp, "6", 6);
	DROPDOWN_InsertString(hDropdown_Temp, "7", 7);
	DROPDOWN_InsertString(hDropdown_Temp, "8", 8);
	DROPDOWN_SetSel(hDropdown_Temp, pCurAct->pump);

//=======================提示==========================================
	hText_Temp = TEXT_CreateEx(
		0,
		ySizeWin/9,
		xSizeWin/2,
		ySizeWin/9,
		hWin, WM_CF_SHOW, 0, GUIID_ACT_PUMP, "Tips");
	TEXT_SetFont(hText_Temp, &GUI_Font24_ASCII);
	TEXT_SetTextAlign(hText_Temp, TEXT_CF_HCENTER|TEXT_CF_VCENTER);

	hDropdown_Temp = DROPDOWN_CreateEx(
		xSizeWin/2,
		ySizeWin/9 + ySizeWin/36,
		xSizeWin/2,
		ySizeWin/9,
		hWin, WM_CF_SHOW, 0, GUIID_ACT_TIPS);
	DROPDOWN_SetTextAlign(hDropdown_Temp, TEXT_CF_VCENTER);
	DROPDOWN_SetListHeight(hDropdown_Temp, 24*4);
	DROPDOWN_InsertString(hDropdown_Temp, "None", 0);
	DROPDOWN_InsertString(hDropdown_Temp, "Sample", 1);
	DROPDOWN_InsertString(hDropdown_Temp, "Membrane", 2);
	DROPDOWN_SetSel(hDropdown_Temp, pCurAct->tips);

//======================加注量===========================================
	hText_Temp = TEXT_CreateEx(
		0,
		ySizeWin*2/9,
		xSizeWin/2,
		ySizeWin/9,
		hWin, WM_CF_SHOW, 0, GUIID_ACT, "Fill Amount(mL)");
	TEXT_SetFont(hText_Temp, &GUI_Font24_ASCII);
	TEXT_SetTextAlign(hText_Temp, TEXT_CF_HCENTER|TEXT_CF_VCENTER);

	hEdit_Temp = EDIT_CreateEx(
		xSizeWin/2,
		ySizeWin*2/9 + ySizeWin/36,
		xSizeWin/2,
		ySizeWin/9 - ySizeWin/18,
		hWin, WM_CF_SHOW, 0, GUIID_ACT_FILLAMOUNT, 3);
	sprintf(strTemp, "%f", (float)pCurAct->fillAmount/10);
	EDIT_SetText(hEdit_Temp, (char *)strTemp);

//=====================声音===========================================
	hText_Temp = TEXT_CreateEx(
		0,
		ySizeWin*3/9,
		xSizeWin/2,
		ySizeWin/9,
		hWin, WM_CF_SHOW, 0, GUIID_ACT, "Voice");
	TEXT_SetFont(hText_Temp, &GUI_Font24_ASCII);
	TEXT_SetTextAlign(hText_Temp, TEXT_CF_HCENTER|TEXT_CF_VCENTER);

	hDropdown_Temp = DROPDOWN_CreateEx(
		xSizeWin/2,
		ySizeWin*3/9 + ySizeWin/36,
		xSizeWin/2,
		ySizeWin/9,
		hWin, WM_CF_SHOW, 0, GUIID_ACT_VOICE);
	DROPDOWN_SetTextAlign(hDropdown_Temp, TEXT_CF_VCENTER);
	DROPDOWN_SetListHeight(hDropdown_Temp, 24*5);
	DROPDOWN_InsertString(hDropdown_Temp, "None", 0);
	DROPDOWN_InsertString(hDropdown_Temp, "Short", 1);
	DROPDOWN_InsertString(hDropdown_Temp, "Middle", 2);
	DROPDOWN_InsertString(hDropdown_Temp, "Long", 3);
	DROPDOWN_SetSel(hDropdown_Temp, pCurAct->voice);

//===================吸液量==============================================
	hText_Temp = TEXT_CreateEx(
		0,
		ySizeWin*4/9,
		xSizeWin/2,
		ySizeWin/9,
		hWin, WM_CF_SHOW, 0, GUIID_ACT, "Imbibition(mL)");
	TEXT_SetFont(hText_Temp, &GUI_Font24_ASCII);
	TEXT_SetTextAlign(hText_Temp, TEXT_CF_HCENTER|TEXT_CF_VCENTER);

	hDropdown_Temp = DROPDOWN_CreateEx(
		xSizeWin/2,
		ySizeWin*4/9 + ySizeWin/36,
		xSizeWin/2,
		ySizeWin/9,
		hWin, WM_CF_SHOW, 0, GUIID_ACT_IMBIBITION);
	DROPDOWN_SetTextAlign(hDropdown_Temp, TEXT_CF_VCENTER);
	DROPDOWN_SetListHeight(hDropdown_Temp, 24*6);
	DROPDOWN_InsertString(hDropdown_Temp, "0", 0);
	DROPDOWN_InsertString(hDropdown_Temp, "1", 1);
	DROPDOWN_InsertString(hDropdown_Temp, "2", 2);
	DROPDOWN_InsertString(hDropdown_Temp, "3", 3);
	DROPDOWN_InsertString(hDropdown_Temp, "4", 4);
	DROPDOWN_SetSel(hDropdown_Temp, pCurAct->imbibition);

//===================摇动时间==============================================
	hText_Temp = TEXT_CreateEx(
		0,
		ySizeWin*5/9,
		xSizeWin/2,
		ySizeWin/9,
		hWin, WM_CF_SHOW, 0, GUIID_ACT, "Shake Time(h:m)");
	TEXT_SetFont(hText_Temp, &GUI_Font24_ASCII);
	TEXT_SetTextAlign(hText_Temp, TEXT_CF_HCENTER|TEXT_CF_VCENTER);

	hEdit_Temp = EDIT_CreateEx(
		xSizeWin/2,
		ySizeWin*5/9 + ySizeWin/36,
		xSizeWin/5,
		ySizeWin/9 - ySizeWin/18,
		hWin, WM_CF_SHOW, 0, GUIID_ACT_SHAKETIMEHOUR, 2);
	sprintf(strTemp, "%d", pCurAct->shakeTimeHour);
	if(pCurAct->shakeTimeHour < 10)
	{
		strTemp[2] = strTemp[1];
		strTemp[1] = strTemp[0];
		strTemp[0] = '0';
	}
	EDIT_SetText(hEdit_Temp, strTemp);

	hText_Temp = TEXT_CreateEx(
		xSizeWin/2 + xSizeWin/5,
		ySizeWin*5/9,
		xSizeWin/10,
		ySizeWin/9,
		hWin, WM_CF_SHOW, 0, GUIID_ACT, ":");
	TEXT_SetFont(hText_Temp, &GUI_Font24_ASCII);
	TEXT_SetTextAlign(hText_Temp, TEXT_CF_HCENTER|TEXT_CF_VCENTER);

	hEdit_Temp = EDIT_CreateEx(
		xSizeWin/2 + xSizeWin*3/10,
		ySizeWin*5/9 + ySizeWin/36,
		xSizeWin/5,
		ySizeWin/9 - ySizeWin/18,
		hWin, WM_CF_SHOW, 0, GUIID_ACT_SHAKETIMEMINUTE, 2);
	sprintf(strTemp, "%d", pCurAct->shakeTimeMinute);
	if(pCurAct->shakeTimeMinute < 10)
	{
		strTemp[2] = strTemp[1];
		strTemp[1] = strTemp[0];
		strTemp[0] = '0';
	}
	EDIT_SetText(hEdit_Temp, strTemp);

//===================摇动速度==============================================
	hText_Temp = TEXT_CreateEx(
		0,
		ySizeWin*6/9,
		xSizeWin/2,
		ySizeWin/9,
		hWin, WM_CF_SHOW, 0, GUIID_ACT, "Shake Speed");
	TEXT_SetFont(hText_Temp, &GUI_Font24_ASCII);
	TEXT_SetTextAlign(hText_Temp, TEXT_CF_HCENTER|TEXT_CF_VCENTER);	

	hDropdown_Temp = DROPDOWN_CreateEx(
		xSizeWin/2,
		ySizeWin*6/9 + ySizeWin/36,
		xSizeWin/2,
		ySizeWin/9,
		hWin, WM_CF_SHOW, 0, GUIID_ACT_SHAKESPEED);
	DROPDOWN_SetTextAlign(hDropdown_Temp, TEXT_CF_VCENTER);
	DROPDOWN_SetListHeight(hDropdown_Temp, 24*4);
	DROPDOWN_InsertString(hDropdown_Temp, "Slow", 0);
	DROPDOWN_InsertString(hDropdown_Temp, "Middle", 1);
	DROPDOWN_InsertString(hDropdown_Temp, "Fast", 2);
	DROPDOWN_SetSel(hDropdown_Temp, pCurAct->shakeSpeed);

//===================循环次数==============================================
	hText_Temp = TEXT_CreateEx(
		0,
		ySizeWin*7/9,
		xSizeWin/2,
		ySizeWin/9,
		hWin, WM_CF_SHOW, 0, GUIID_ACT, "Loop Time");
	TEXT_SetFont(hText_Temp, &GUI_Font24_ASCII);
	TEXT_SetTextAlign(hText_Temp, TEXT_CF_HCENTER|TEXT_CF_VCENTER);	

	hDropdown_Temp = DROPDOWN_CreateEx(
		xSizeWin/2,
		ySizeWin*7/9 + ySizeWin/36,
		xSizeWin/2,
		ySizeWin/9,
		hWin, WM_CF_SHOW, 0, GUIID_ACT_LOOPTIME);
	DROPDOWN_SetTextAlign(hDropdown_Temp, TEXT_CF_VCENTER);
	DROPDOWN_SetListHeight(hDropdown_Temp, 24*4);
	DROPDOWN_InsertString(hDropdown_Temp, "1", 0);
	DROPDOWN_InsertString(hDropdown_Temp, "2", 1);
	DROPDOWN_InsertString(hDropdown_Temp, "3", 2);
	DROPDOWN_SetUpMode(hDropdown_Temp, 1);
	DROPDOWN_SetSel(hDropdown_Temp, pCurAct->loopTime);

//===================保存 取消==============================================
	hWin_Temp = BUTTON_CreateEx(
		0,
		ySizeWin*8/9,
		xSizeWin/2,
		ySizeWin/9,
		hWin, WM_CF_SHOW, 0, GUIID_ACT_SAVE);
	BUTTON_SetText(hWin_Temp, "Save");

	hWin_Temp = BUTTON_CreateEx(
		xSizeWin/2,
		ySizeWin*8/9,
		xSizeWin/2,
		ySizeWin/9,
		hWin, WM_CF_SHOW, 0, GUIID_ACT_CANCEL);
	BUTTON_SetText(hWin_Temp, "Cancel");
}

void cbActionNotifyParent(WM_MESSAGE * pMsg)
{
	int Id, NCode;
	WM_HWIN hWin;
	char strTemp[10];
	int intTemp;
	int iTemp;
	int flag = 0;

	hWin = pMsg->hWinSrc;
	Id    = WM_GetId(hWin);
	NCode = pMsg->Data.v;	

	switch(NCode) {
	case WM_NOTIFICATION_RELEASED:
		if(Id == GUIID_ACT_SAVE)//保存数据
		{
			HANDLE_LIST *hAPPOnTop;

			//保存参数
			memcpy(pCurAct, &curActTemp, sizeof(ACTEDIT_MAN));

			/* 获取最上层的窗口句柄 */
			hAPPOnTop =	hAPPLinkedList_GetAppTop();
			if(hAPPOnTop != NULL)
			{
				WM_DeleteWindow(hAPPOnTop->hAPP); //	关闭窗口
			}
		}
		else if(Id == GUIID_ACT_CANCEL)//取消本次参数
		{
			HANDLE_LIST *hAPPOnTop;

			/* 获取最上层的窗口句柄 */
			hAPPOnTop =	hAPPLinkedList_GetAppTop();
			if(hAPPOnTop != NULL)
			{
				WM_DeleteWindow(hAPPOnTop->hAPP);	//关闭窗口
			}
		}
		break;
	case WM_NOTIFICATION_SEL_CHANGED://下拉列表的数据有变化
		if(Id == GUIID_ACT_PUMP)
		{
			curActTemp.pump = DROPDOWN_GetSel(hWin);
		}
		else if(Id == GUIID_ACT_TIPS)
		{
			curActTemp.tips = DROPDOWN_GetSel(hWin);
		}
		else if(Id == GUIID_ACT_VOICE)
		{
			curActTemp.voice = DROPDOWN_GetSel(hWin);
		}
		else if(Id == GUIID_ACT_IMBIBITION)
		{
			curActTemp.imbibition = DROPDOWN_GetSel(hWin);
		}
		else if(Id == GUIID_ACT_SHAKESPEED)
		{
			curActTemp.shakeSpeed = DROPDOWN_GetSel(hWin);
		}
		else if(Id == GUIID_ACT_LOOPTIME)
		{
			curActTemp.loopTime = DROPDOWN_GetSel(hWin);
		}
		break;
	case WM_NOTIFICATION_VALUE_CHANGED:

		if(Id == GUIID_ACT_FILLAMOUNT)
		{
			iTemp = EDIT_GetNumChars(hWin);
			EDIT_GetText(hWin, strTemp, sizeof(strTemp));

			if(iTemp == 3)
			{
				if(strTemp[1] != '.')
					flag = 1;
				else if(strTemp[0] < '1' || strTemp[0] > '3')//1
					flag = 1;
				else if(strTemp[0] == '3' && strTemp[2] != '0')
					flag = 1;
				else if(strTemp[2] < '0' || strTemp[2] > '9')
					flag = 1;

				if(flag)
				{
					sprintf(strTemp, "%f", (float)pCurAct->fillAmount/10);
					EDIT_SetText(hWin, (char *)strTemp);

					MESSAGEBOX_Create("Please input the number from 1.0 to 3.0","Warning",GUI_MESSAGEBOX_CF_MODAL);
				}
				else
				{
					strTemp[1] = strTemp[2];
					strTemp[2] = strTemp[3];
					intTemp = atoi(strTemp);
					curActTemp.fillAmount = intTemp;
				}
			}
		}
		else if(Id == GUIID_ACT_SHAKETIMEHOUR)
		{
			iTemp = EDIT_GetNumChars(hWin);
			EDIT_GetText(hWin, strTemp, sizeof(strTemp));

			if(iTemp == 2)
			{
				intTemp = atoi(strTemp);
				if(intTemp > 24)
					flag = 1;

				if(flag)
				{
					sprintf(strTemp, "%d", pCurAct->shakeTimeHour);
					EDIT_SetText(hWin, (char *)strTemp);

					MESSAGEBOX_Create("Please input the number from 0 to 24","Warning",GUI_MESSAGEBOX_CF_MODAL);
				}
				else
				{
					curActTemp.shakeTimeHour = intTemp;
				}
			}
		}
		else if(Id == GUIID_ACT_SHAKETIMEMINUTE)
		{
			iTemp = EDIT_GetNumChars(hWin);
			EDIT_GetText(hWin, strTemp, sizeof(strTemp));

			if(iTemp == 2)
			{
				intTemp = atoi(strTemp);
				if(intTemp > 29)
					flag = 1;

				if(flag)
				{
					sprintf(strTemp, "%d", pCurAct->shakeTimeMinute);
					EDIT_SetText(hWin, (char *)strTemp);

					MESSAGEBOX_Create("Please input the number from 0 to 59","Warning",GUI_MESSAGEBOX_CF_MODAL);
				}
				else
				{
					curActTemp.shakeTimeMinute = intTemp;
				}
			}
		}
		break;

	case WM_NOTIFICATION_LOST_FOCUS:
		if(Id == GUIID_ACT_FILLAMOUNT)
		{
			iTemp = EDIT_GetNumChars(hWin);
			EDIT_GetText(hWin, strTemp, sizeof(strTemp));

			if(iTemp == 0)
			{
				sprintf(strTemp, "%f", (float)pCurAct->fillAmount/10);
			}
			else if(iTemp == 1)
			{
				if(strTemp[0] < '1' || strTemp[0] > '3')
					sprintf(strTemp, "%f", (float)pCurAct->fillAmount/10);
				else
				{
					strTemp[1] = '.';
					strTemp[2] = '0';
					strTemp[3] = '\0';
				}
			}
			else if(iTemp == 2)
			{
				if(strTemp[1] != '.' || strTemp[0] < '1' || strTemp[0] > '3')//1
					sprintf(strTemp, "%f", (float)pCurAct->fillAmount/10);
				else
				{
					strTemp[2] = '0';
					strTemp[3] = '\0';
				}
			}

			EDIT_SetText(hWin, (char *)strTemp);
			strTemp[1] = strTemp[2];
			strTemp[2] = strTemp[3];
			intTemp = atoi(strTemp);
			curActTemp.fillAmount = intTemp;
			
		}
		else if(Id == GUIID_ACT_SHAKETIMEHOUR)
		{
			iTemp = EDIT_GetNumChars(hWin);
			EDIT_GetText(hWin, strTemp, sizeof(strTemp));

			if(iTemp == 0)
				sprintf(strTemp, "%d", pCurAct->shakeTimeHour);
			if(iTemp == 1)
			{
				strTemp[1] = strTemp[0];
				strTemp[0] = '0';
				strTemp[2] = '\0';
			}

			EDIT_SetText(hWin, (char *)strTemp);
			intTemp = atoi(strTemp);
			curActTemp.shakeTimeHour = intTemp;
		}
		else if(Id == GUIID_ACT_SHAKETIMEMINUTE)
		{
			iTemp = EDIT_GetNumChars(hWin);
			EDIT_GetText(hWin, strTemp, sizeof(strTemp));

			if(iTemp == 0)
				sprintf(strTemp, "%d", pCurAct->shakeTimeMinute);
			if(iTemp == 1)
			{
				strTemp[1] = strTemp[0];
				strTemp[0] = '0';
				strTemp[2] = '\0';
			}

			EDIT_SetText(hWin, (char *)strTemp);
			intTemp = atoi(strTemp);
			curActTemp.shakeTimeMinute = intTemp;
		}
		break;

	case WM_NOTIFICATION_GOT_FOCUS:
		if(Id == GUIID_ACT_FILLAMOUNT || Id == GUIID_ACT_SHAKETIMEHOUR || Id == GUIID_ACT_SHAKETIMEMINUTE)
		{
			/*int i;
			for(i=0;i<EDIT_GetNumChars(hWin);i++)
			{
				EDIT_SetTextColor(hWin, i, GUI_BLUE);
			}*/
			//EDIT_SetSel(hWin, 0, EDIT_GetNumChars(hWin));
		}
		break;

	}//switch(NCode)
}