/****************************************************************
适用于vofa串口调试助手firewater的库
使用方法:
使用前调用vofa_init绑定串口,此串口需要打开串口中断
主函数通过调用vofa_get_rx_flag()获取串口接收状态
返回值为0则无接收,返回值为1则有接收
判断接收完成后调用parse_command()获取接收的包
包结构体为vofa_data,结构体中RX_cmd为接收的命令号,RX_value为接收的数据

发送一个数据可以使用vofa_send_data发送
发送多个数据可以使用vofa_send_buf发送
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
