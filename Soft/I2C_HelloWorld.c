#include "mbed.h"
 
// Read temperature from LM75BD

//https://developer.mbed.org/handbook/I2C

// The mbed API uses 8 bit addresses, so make sure to take that 7 bit address and left shift it by 1 before passing it.

 
I2C i2c(p28, p27);
 
const int addr = 0x90;
 
int main() {
    char cmd[2];
    while (1) {
        cmd[0] = 0x01;
        cmd[1] = 0x00;
        i2c.write(addr, cmd, 2);
 
        wait(0.5);
 
        cmd[0] = 0x00;
        i2c.write(addr, cmd, 1);
        i2c.read(addr, cmd, 2);
 
        float tmp = (float((cmd[0]<<8)|cmd[1]) / 256.0);
        printf("Temp = %.2f\n", tmp);
    }
}
