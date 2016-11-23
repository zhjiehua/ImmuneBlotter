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

#include "WDAProEdit.h"
#include "WFGUI_Common.h"


//uint8_t *proData;
//uint8_t proData[] = { 
//	0xF0,0xF4,0x50,0x72,0x6F,0x6A,0x65,0x63,0x74,0x30,0xF5,0xF2,0xF4,0x41,0x63,0x74,0x69,0x6F,0x6E,0x30,0xF5,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0xF3,0xF1,
//};
//uint16_t proDataLen = sizeof(proData);

PROEDIT_MAN hProEditMan;//��Ŀ����ͷ

int8_t parseProData(uint8_t *data, uint16_t len)
{
	uint8_t *p = data;
	uint8_t *pTemp;
	uint16_t i;
	uint8_t j;
	uint8_t state = STATE_START;
	PROEDIT_MAN *pPro;
	ACTEDIT_MAN *pAct;
	uint8_t name[10];
	
	INIT_LIST_HEAD(&hProEditMan.listNode );//��ʼ����Ŀͷ
	INIT_LIST_HEAD(&hProEditMan.hActHead );

	if(len < 2)
		return -1;

	for(i=0;i<len;i++)
	{
		if(state == STATE_START && *p == EEPROM_PROSTART)//��Ŀͷ
		{
			//����һ���ڵ�
			pPro = (PROEDIT_MAN *)malloc(sizeof(PROEDIT_MAN));
			if (pPro == NULL)
			{
				state = STATE_START;

				DEBUG("\r\n pPro malloc error\r\n ");
				return -2;
			}
			list_add_tail(&pPro->listNode,&hProEditMan.listNode);
			INIT_LIST_HEAD(&pPro->hActHead );

			state = STATE_PRO;
			p++;
		}
		else if(state == STATE_PRO && *p == EEPROM_NAMESTART)
		{
			state = STATE_PRONAME;
			p++;
			j = 0;
		}
		else if(state == STATE_PRONAME)
		{
			if(*p == EEPROM_NAMEEND)
			{
				name[j] = '\0';

				pPro->name = (uint8_t *)malloc(j+1);
				
				if (pPro->name == NULL)
				{
					state = STATE_START;

					DEBUG("\r\n pPro->name malloc error\r\n ");
					return -2;
				}

				strcpy(pPro->name, name);

				state = STATE_PRO;
			}
			else
			{
				name[j] = *p;
				j++;
			}

			p++;
		}
		else if(state == STATE_PRO && *p == EEPROM_ACTSTART)
		{
			//����һ���ڵ�
			pAct = (ACTEDIT_MAN *)malloc(sizeof(ACTEDIT_MAN));
			if (pAct == NULL)
			{
				state = STATE_START;

				DEBUG("\r\n pAct malloc error\r\n ");
				return -2;
			}
			list_add_tail(&pAct->listNode,&pPro->hActHead);

			state = STATE_ACT;
			p++;
		}
		else if(state == STATE_ACT && *p == EEPROM_NAMESTART)
		{
			state = STATE_ACTNAME;
			p++;
			j = 0;
		}
		else if(state == STATE_ACTNAME)
		{
			if(*p == EEPROM_NAMEEND)
			{
				name[j] = '\0';

				pAct->name = (uint8_t *)malloc(j+1);
				if (pAct->name == NULL)
				{
					state = STATE_START;

					DEBUG("\r\n pAct->name malloc error\r\n ");
					return -2;
				}

				strcpy(pAct->name, name);

				state = STATE_ACTDATA;
			}
			else
			{
				name[j] = *p;
				j++;
			}

			p++;
			pTemp = &(pAct->pump);
		}
		else if(state == STATE_ACTDATA)
		{
			if(*p == EEPROM_ACTEND)
			{
				state = STATE_ACT;
			}
			else
			{
				*pTemp = *p;
				pTemp++;
			}

			p++;
		}
		else if(state == STATE_ACT && *p == EEPROM_PROEND)//1����Ŀ����
		{
			state = STATE_START;
			p++;
		}
	}
	state = STATE_START;

	//������Ϣ
	{
		struct list_head *pos;	
		PROEDIT_MAN *node;

		list_for_each(pos,&hProEditMan.listNode)
		{
			/* TBD �����и�warning����֪��Ӱ��󲻴�*/
			node = list_entry(pos,PROEDIT_MAN,listNode);

			DEBUG("\r\n node->name =%s \r\n ",node->name);
		}
	}

	return 0;
}
