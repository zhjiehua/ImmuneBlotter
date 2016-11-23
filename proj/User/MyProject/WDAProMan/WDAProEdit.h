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
存储文件列表
0xF0 0xF4 P r o j e c t 0 0xF5 
0xF2 0xF4 A c t 0 0xF5 0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07 0x08 0x09 0xF3      //一个动作的数据
……
0xF1   //一个项目结束
……

即，项目头->名称头->项目名称->名称尾->动作头->名称头->动作名称->名称尾->动作数据-> 动作头->……->动作尾-> …… ->动作尾 


注意在存储数据是要记录总共用了多少字节，字节数放在数据文件列表的最开始，即
字节数->第1个项目数据->第2个项目数据
*/

typedef struct{
	struct list_head listNode;//项目列表

	uint8_t *name;//项目名称
	struct list_head hActHead;//动作列表头

}PROEDIT_MAN;

typedef struct{
	struct list_head listNode;//动作列表

	uint8_t *name;//动作名称
	uint8_t pump;//泵序号。共8个泵，范围0~8，0表示不使用泵
	uint8_t tips;//是否人工干预。无、样本和膜条
	uint8_t fillAmount;//加注量。范围1.0~3.0mL，精度0.1，若泵序号为0，则该控件不可编辑
	uint8_t voice;//提示音。无、短、中和长
	uint8_t imbibition;//吸液量。0、1、2、3和4
	uint8_t shakeTimeHour;//摇动时间。00：00~00：24
	uint8_t shakeTimeMinute;
	uint8_t shakeSpeed;//摇动速率。慢、中和快
	uint8_t loopTime;//循环次数

}ACTEDIT_MAN;


extern uint8_t proData[];
extern uint16_t proDataLen;

extern PROEDIT_MAN hProEditMan;//项目管理头

int8_t parseProData(uint8_t *data, uint16_t len);

#endif
