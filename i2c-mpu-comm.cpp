#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int addr = 0x40; /* The I2C address */
char buf[10];
int main(){

 int file;
 int adapter_nr = 2; /* probably dynamically determined */
 char filename[20];
 buf[0] = 0x43;
 snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
 file = open(filename, O_RDWR);
 if (file < 0) {
    /* ERROR HANDLING; you can check errno to see what went wrong */
    exit(1);
 }
 if (ioctl(file, I2C_SLAVE, addr) < 0) {
   /* ERROR HANDLING; you can check errno to see what went wrong */
   exit(1);
 }

 if (read(file, buf, 1) != 1) {
    /* ERROR HANDLING: i2c transaction failed */
  } else {
    printf("%d",buf[0]);
  }


}
