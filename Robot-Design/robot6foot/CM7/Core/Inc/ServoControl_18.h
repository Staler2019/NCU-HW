void robotInit(UART_HandleTypeDef* huart,uint32_t arrive_time)
{
	uint32_t servo_amount = 18;
	uint32_t servo_list[18] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
	uint32_t servo_pwm_list[18] = {1500,1000,500,1500,1000,500,1500,1000,500,1500,2000,2500,1500,2000,2500,1400,2000,2500};
	robot_control_cmd(huart,servo_amount,arrive_time,servo_list,servo_pwm_list);
}

int robot_control_cmd(UART_HandleTypeDef* huart,uint32_t servo_amount,uint32_t arrive_time,uint32_t* servo_list,uint32_t* servo_pwm_list)
{
	uint32_t length = servo_amount * 3 + 5;
	uint8_t *cmd_data = (uint8_t *)malloc(sizeof(uint8_t)*(length+2));
	cmd_data[0] = 0x55;
	cmd_data[1] = 0x55;
	cmd_data[2] = length;
	cmd_data[3] = 0x03;
	cmd_data[4] = servo_amount;
	cmd_data[5] = (arrive_time<<8 & 0xffff) >>8;
	cmd_data[6] = (arrive_time & 0xffff)>>8;
	uint32_t i=0,k=7;
	while(k < length+2)
	{
		cmd_data[k] = servo_list[i];
		k++;
		cmd_data[k] = (servo_pwm_list[i]<<8 & 0xffff) >>8;
		k++;
		cmd_data[k] = servo_pwm_list[i]>>8;
		k++;
		i++;
	}
	HAL_UART_Transmit(huart, cmd_data, length+2 , HAL_MAX_DELAY);
	HAL_Delay(arrive_time);
	return 1;
}
int robotForward(UART_HandleTypeDef* huart)
{
	uint32_t servo_amount = 18;
	uint32_t servo_list[18] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
	uint32_t servo_pwm_list_1[18] = {1700,1000, 500,1300, 800, 500,1700,1000, 500,1700,2200,2500,1300,2000,2500,1700,2200,2500};
	uint32_t servo_pwm_list_2[18] = {1700,1000, 500,1300,1000, 500,1700,1000, 500,1700,2000,2500,1300,2000,2500,1700,2000,2500};
	uint32_t servo_pwm_list_3[18] = {1300, 800, 500,1700,1000, 500,1300, 800, 500,1300,2000,2500,1700,2200,2500,1300,2000,2500};
	uint32_t servo_pwm_list_4[18] = {1300,1000, 500,1700,1000, 500,1300,1000, 500,1300,2000,2500,1700,2000,2500,1300,2000,2500};
	robot_control_cmd(huart,servo_amount,150,servo_list,servo_pwm_list_1);
	robot_control_cmd(huart,servo_amount,100,servo_list,servo_pwm_list_2);
	robot_control_cmd(huart,servo_amount,150,servo_list,servo_pwm_list_3);
	robot_control_cmd(huart,servo_amount,100,servo_list,servo_pwm_list_4);
	return 1;
}
int robotBackward(UART_HandleTypeDef* huart)
{
	uint32_t servo_amount = 18;
	uint32_t servo_list[18] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
	uint32_t servo_pwm_list_1[18] = {1300,1000, 500,1700, 800, 500,1300,1000, 500,1300,2200,2500,1700,2000,2500,1300,2200,2500};
	uint32_t servo_pwm_list_2[18] = {1300,1000, 500,1700,1000, 500,1300,1000, 500,1300,2000,2500,1700,2000,2500,1300,2000,2500};
	uint32_t servo_pwm_list_3[18] = {1700, 800, 500,1300,1000, 500,1700, 800, 500,1700,2000,2500,1300,2200,2500,1700,2000,2500};
	uint32_t servo_pwm_list_4[18] = {1700,1000, 500,1300,1000, 500,1700,1000, 500,1700,2000,2500,1300,2000,2500,1700,2000,2500};

	robot_control_cmd(huart,servo_amount,200,servo_list,servo_pwm_list_1);
	robot_control_cmd(huart,servo_amount,100,servo_list,servo_pwm_list_2);
	robot_control_cmd(huart,servo_amount,200,servo_list,servo_pwm_list_3);
	robot_control_cmd(huart,servo_amount,100,servo_list,servo_pwm_list_4);
	return 1;
}
int robotTurnLeft(UART_HandleTypeDef* huart)
{
	uint32_t servo_amount = 18;
	uint32_t servo_list[18] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
	uint32_t servo_pwm_list_1[18] = {1500,1000, 500,2000, 800, 500,1500,1000, 500,2000,2200,2500,1500,2000,2500,2000,2200,2500};
	uint32_t servo_pwm_list_2[18] = {1500,1000, 500,2000,1000, 500,1500,1000, 500,2000,2000,2500,1500,2000,2500,2000,2000,2500};
	uint32_t servo_pwm_list_3[18] = {1500, 800, 500,1500,1000, 500,1500, 800, 500,1500,2000,2500,1500,2200,2500,1500,2000,2500};
	uint32_t servo_pwm_list_4[18] = {1500,1000, 500,1500,1000, 500,1500,1000, 500,1500,2000,2500,1500,2000,2500,1500,2000,2500};

	robot_control_cmd(huart,servo_amount,150,servo_list,servo_pwm_list_1);
	robot_control_cmd(huart,servo_amount,150,servo_list,servo_pwm_list_2);
	robot_control_cmd(huart,servo_amount,150,servo_list,servo_pwm_list_3);
	robot_control_cmd(huart,servo_amount,150,servo_list,servo_pwm_list_4);
	return 1;
}
int robotTurnRight(UART_HandleTypeDef* huart)
{
	uint32_t servo_amount = 18;
	uint32_t servo_list[18] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
	uint32_t servo_pwm_list_1[18] = {1500,1000, 500,1000, 800, 500,1500,1000, 500,1000,2200,2500,1500,2000,2500,1000,2200,2500};
	uint32_t servo_pwm_list_2[18] = {1500,1000, 500,1000,1000, 500,1500,1000, 500,1000,2000,2500,1500,2000,2500,1000,2000,2500};
	uint32_t servo_pwm_list_3[18] = {1500, 800, 500,1500,1000, 500,1500, 800, 500,1500,2000,2500,1500,2200,2500,1500,2000,2500};
	uint32_t servo_pwm_list_4[18] = {1500,1000, 500,1500,1000, 500,1500,1000, 500,1500,2000,2500,1500,2000,2500,1500,2000,2500};

	robot_control_cmd(huart,servo_amount,150,servo_list,servo_pwm_list_1);
	robot_control_cmd(huart,servo_amount,150,servo_list,servo_pwm_list_2);
	robot_control_cmd(huart,servo_amount,150,servo_list,servo_pwm_list_3);
	robot_control_cmd(huart,servo_amount,150,servo_list,servo_pwm_list_4);
	return 1;
}

int robotTransverseLeft(UART_HandleTypeDef* huart)
{
	uint32_t servo_amount = 18;
	uint32_t servo_list[18] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
	uint32_t servo_pwm_list_1[18] = {1000, 700, 750,1500,1100, 650,2000, 700, 750,2000,1600,1800,1501,2300,2250,1000,1600,1800};
	uint32_t servo_pwm_list_2[18] = {1000,1400,1200,1500,1100, 650,2000,1400,1200,2000,1600,1800,1501,1900,2350,1000,1600,1800};
	uint32_t servo_pwm_list_3[18] = {1000,1400,1200,1500, 800, 650,2000,1400,1200,2000,1900,1800,1501,1900,2350,1000,1900,1800};
	uint32_t servo_pwm_list_4[18] = {1000,1100, 650,1500, 800, 650,2000,1100, 650,2000,1900,1800,1501,1600,1800,1000,1900,1800};
	uint32_t servo_pwm_list_5[18] = {1000,1100, 650,1500,1400,1200,2000,1100, 650,2000,1900,2350,1501,1600,1800,1000,1900,2350};
	uint32_t servo_pwm_list_6[18] = {1000, 800, 650,1500,1400,1200,2000, 800, 650,2000,1900,2350,1501,2200,2350,1000,1900,2350};

	robot_control_cmd(huart,servo_amount,300,servo_list,servo_pwm_list_1);
	robot_control_cmd(huart,servo_amount,300,servo_list,servo_pwm_list_2);
	robot_control_cmd(huart,servo_amount,300,servo_list,servo_pwm_list_3);
	robot_control_cmd(huart,servo_amount,300,servo_list,servo_pwm_list_4);
	robot_control_cmd(huart,servo_amount,300,servo_list,servo_pwm_list_5);
	robot_control_cmd(huart,servo_amount,300,servo_list,servo_pwm_list_6);
	return 1;
}
int robotTransverseRight(UART_HandleTypeDef* huart)
{
	uint32_t servo_amount = 18;
	uint32_t servo_list[18] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};

	uint32_t servo_pwm_list_1[18] = {1000, 800, 650,1500,1400,1200,2000, 800, 650,2000,1900,2350,1501,2200,2350,1000,1900,2350};
	uint32_t servo_pwm_list_2[18] = {1000,1100, 650,1500,1400,1200,2000,1100, 650,2000,1900,2350,1501,1600,1800,1000,1900,2350};
	uint32_t servo_pwm_list_3[18] = {1000,1100, 650,1500, 800, 650,2000,1100, 650,2000,1900,1800,1501,1600,1800,1000,1900,1800};
	uint32_t servo_pwm_list_4[18] = {1000,1400,1200,1500, 800, 650,2000,1400,1200,2000,1900,1800,1501,1900,2350,1000,1900,1800};
	uint32_t servo_pwm_list_5[18] = {1000,1400,1200,1500,1100, 650,2000,1400,1200,2000,1600,1800,1501,1900,2350,1000,1600,1800};
	uint32_t servo_pwm_list_6[18] = {1000, 700, 750,1500,1100, 650,2000, 700, 750,2000,1600,1800,1501,2300,2250,1000,1600,1800};

	robot_control_cmd(huart,servo_amount,300,servo_list,servo_pwm_list_1);
	robot_control_cmd(huart,servo_amount,300,servo_list,servo_pwm_list_2);
	robot_control_cmd(huart,servo_amount,300,servo_list,servo_pwm_list_3);
	robot_control_cmd(huart,servo_amount,300,servo_list,servo_pwm_list_4);
	robot_control_cmd(huart,servo_amount,300,servo_list,servo_pwm_list_5);
	robot_control_cmd(huart,servo_amount,300,servo_list,servo_pwm_list_6);
	return 1;
}
