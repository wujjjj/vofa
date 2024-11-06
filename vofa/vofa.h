/****************************************************************
������vofa���ڵ�������firewater�Ŀ�
ʹ�÷���:
ʹ��ǰ����vofa_init�󶨴���,�˴�����Ҫ�򿪴����ж�
������ͨ������vofa_get_rx_flag()��ȡ���ڽ���״̬
����ֵΪ0���޽���,����ֵΪ1���н���
�жϽ�����ɺ����parse_command()��ȡ���յİ�
���ṹ��Ϊvofa_data,�ṹ����RX_cmdΪ���յ������,RX_valueΪ���յ�����

����һ�����ݿ���ʹ��vofa_send_data����
���Ͷ�����ݿ���ʹ��vofa_send_buf����
****************************************************************/
#ifndef __VOFA_H
#define __VOFA_H

#include "main.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define max_buf_longth 49

typedef struct{
	UART_HandleTypeDef *huart;
	uint8_t RX_flag;
	uint8_t RX_longth;
	char RX_buf[max_buf_longth];
	char RX_packet[max_buf_longth];
}vofa_struct;

typedef struct{
	int8_t RX_cmd;
	float RX_value;
}vofa_data;

void vofa_init(UART_HandleTypeDef *huart);
void vofa_send_data(float tx_buf);
void vofa_send_buf(float *send_data,uint8_t size);
uint8_t vofa_get_rx_flag(void);
vofa_data parse_command(void);

#endif
