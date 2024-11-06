#include "vofa.h"

vofa_struct vofa;
uint8_t RX_data;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart == vofa.huart) {
		if(RX_data == '\n' || RX_data == '\r'){
			memcpy(vofa.RX_packet, vofa.RX_buf, vofa.RX_longth);
			memset(vofa.RX_buf, '\0', vofa.RX_longth);
			vofa.RX_flag = 1;
			vofa.RX_longth = 0;
		}else{
			vofa.RX_buf[vofa.RX_longth] = RX_data;
			vofa.RX_longth++;
		}
		HAL_UART_Receive_IT(vofa.huart,&RX_data, 1);
    }
}

void vofa_init(UART_HandleTypeDef *huart){
	vofa.huart = huart;
	vofa.RX_longth = 0;
	vofa.RX_flag = 0;
	HAL_UART_Receive_IT(vofa.huart,&RX_data, 1);
}

void vofa_send_buf(float *send_data,uint8_t size){
	uint8_t i;
	static char send_buffer[max_buf_longth];
	static char float_buf[10];
	
	memset(send_buffer,'\0',max_buf_longth);
	memset(float_buf,'\0',10);
	
	for(i=0;i<size;i++){
		sprintf(float_buf,"%.2f",send_data[i]);
		strcat(send_buffer, float_buf);
		if(i == size-1){
			strcat(send_buffer, "\r\n");
		}else{
			strcat(send_buffer, ",");
		}
	}
	HAL_UART_Transmit_IT(vofa.huart,(uint8_t*)send_buffer,strlen(send_buffer));
}

void vofa_send_data(float tx_buf){
	char *send_buffer;
	sprintf(send_buffer,"%.2f\r\n",tx_buf);
	HAL_UART_Transmit_IT(vofa.huart,(uint8_t*)send_buffer,strlen(send_buffer));
}

uint8_t vofa_get_rx_flag(void){
	return vofa.RX_flag;
}

vofa_data parse_command(void){
	vofa_data vdata;
	uint8_t input_longth = strlen(vofa.RX_packet);
    if (input_longth < 3) {
        vdata.RX_cmd = -1;
        vdata.RX_value = -1;
        return vdata;
    }

    char op_str[3] = {vofa.RX_packet[0], vofa.RX_packet[1], '\0'};
    vdata.RX_cmd = atoi(op_str);

    char value_str[input_longth-2];
    strcpy(value_str, vofa.RX_packet + 2);
    vdata.RX_value = atof(value_str);
	
	vofa.RX_flag = 0;
	memset(vofa.RX_packet, '\0', input_longth);
	
	return vdata;
}

