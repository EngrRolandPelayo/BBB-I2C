#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <string>
#include <memory>
#include <array>

using namespace std;

int16_t accel_x;
int16_t accel_y;
int16_t accel_z;
int16_t gyro_x;
int16_t gyro_y;
int16_t gyro_z;

const char* deviceADDR = " 0x68";
const char* PWR_MGMT_1 = " 0x6B ";
const char* ACCEL_X_OUT_H = " 0x3B ";
const char* ACCEL_X_OUT_L = " 0x3C ";
const char* ACCEL_Y_OUT_H = " 0x3D ";
const char* ACCEL_Y_OUT_L = " 0x3E ";
const char* ACCEL_Z_OUT_H = " 0x3F ";
const char* ACCEL_Z_OUT_L = " 0x40 ";
const char* GYRO_X_OUT_H = " 0x43 ";
const char* GYRO_X_OUT_L = " 0x44 ";
const char* GYRO_Y_OUT_H = " 0x45 ";
const char* GYRO_Y_OUT_L = " 0x46 ";
const char* GYRO_Z_OUT_H = " 0x47 ";
const char* GYRO_Z_OUT_L = " 0x48 ";

const char* cmdGet = "i2cget -y 2";
const char* cmdSet = "i2cset -y 2";

string exec(char* cmd) {

string data;
FILE * stream;
const int max_buffer = 256;
char buffer[max_buffer];
strcat(cmd," 2>&1");

stream = popen(cmd, "r");

if (stream) {
	while (!feof(stream))
		if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
		pclose(stream);
	}
	return data;

}

int main(){
	
	while(true){
		char str1[100];
		char str2[100];
		strcpy(str1,cmdGet); //str1 = i2cget -y 2
		strcat(str1,deviceADDR); //str1 = i2cget -y 2 0x68 
		strcat(str1,ACCEL_X_OUT_H); //str1 = i2cget -y 2 0x68 0x3B
		strcpy(str2,cmdGet); //str1 = i2cget -y 2
		strcat(str2,deviceADDR); //str1 = i2cget -y 2 0x68 
		strcat(str2,ACCEL_X_OUT_L); //str1 = i2cget -y 2 0x68 0x3B
		accel_x = stoi(exec(str1), nullptr, 16) << 8 + stoi(exec(str2), nullptr, 16);
		cout << accel_x << endl;
	}
	
	return 0;
}
