#ifndef _WDAPROEDIT_H
#define _WDAPROEDIT_H

#include "stdint.h"
#include "WFGUI_LinkedList.h"

#define EEPROM_PROSTART 0xF0
#define EEPROM_PROEND 0xF1
#define EEPROM_ACTSTART 0xF2
#define EEPROM_ACTEND 0xF3
#define EEPROM_NAMESTART 0xF4
#define EEPROM_NAMEEND 0xF5

#define STATE_START 0
#define STATE_PRO 1
#define STATE_PRONAME 2
#define STATE_ACT 3
#define STATE_ACTNAME 4
#define STATE_ACTDATA 5
/*
�洢�ļ��б�
0xF0 0xF4 P r o j e c t 0 0xF5 
0xF2 0xF4 A c t 0 0xF5 0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07 0x08 0x09 0xF3      //һ������������
����
0xF1   //һ����Ŀ����
����

������Ŀͷ->����ͷ->��Ŀ����->����β->����ͷ->����ͷ->��������->����β->��������-> ����ͷ->����->����β-> ���� ->����β 


ע���ڴ洢������Ҫ��¼�ܹ����˶����ֽڣ��ֽ������������ļ��б���ʼ����
�ֽ���->��1����Ŀ����->��2����Ŀ����
*/

typedef struct{
	struct list_head listNode;//��Ŀ�б�

	uint8_t *name;//��Ŀ����
	struct list_head hActHead;//�����б�ͷ

}PROEDIT_MAN;

typedef struct{
	struct list_head listNode;//�����б�

	uint8_t *name;//��������
	uint8_t pump;//����š���8���ã���Χ0~8��0��ʾ��ʹ�ñ�
	uint8_t tips;//�Ƿ��˹���Ԥ���ޡ�������Ĥ��
	uint8_t fillAmount;//��ע������Χ1.0~3.0mL������0.1���������Ϊ0����ÿؼ����ɱ༭
	uint8_t voice;//��ʾ�����ޡ��̡��кͳ�
	uint8_t imbibition;//��Һ����0��1��2��3��4
	uint8_t shakeTimeHour;//ҡ��ʱ�䡣00��00~00��24
	uint8_t shakeTimeMinute;
	uint8_t shakeSpeed;//ҡ�����ʡ������кͿ�
	uint8_t loopTime;//ѭ������

}ACTEDIT_MAN;


extern uint8_t proData[];
extern uint16_t proDataLen;

extern PROEDIT_MAN hProEditMan;//��Ŀ����ͷ

int8_t parseProData(uint8_t *data, uint16_t len);

#endif
