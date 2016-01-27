// Controle du MCP9804

/* 8 bits d'adresse : 
0011 A2 A1 A0 R/W
A2, A1, A0 : set externally
R/W to 1 for read operation and 0 to write */

// TODO : set des limites


// Registres
#define I2C_REG_CONFIG 		0b00000001
#define I2C_REG_TUPPER 		0b00000010
#define I2C_REG_TLOWER 		0b00000011
#define I2C_REG_TCRIT 		0b00000100
#define I2C_REG_TA	 		0b00000101
#define I2C_REG_RES 		0b00001000

// Paramétrage des pins.
#define I2C_SDA pin0_port0
#define I2C_SCL pin1_port0


I2C i2c(I2C_SDA, I2C_SCL);
const int mpc9804_addr = 0b0011000;

int I2C_init()
{
	int addr_i2c;
	char cmd[4];
	
	addr_i2c = mpc9804_addr << 1;	// Write operation
	cmd[0] = I2C_REG_TUPPER
 	cmd[1] = 0b0000xxxx;	// Limite max +X°C
	cmd[2] = 0bxxxxxx00;	// Limite max +X°C
	i2c.write(addr_i2c, cmd, 3);
	
	addr_i2c = mpc9804_addr << 1;	// Write operation
	cmd[0] = I2C_REG_TLOWER
 	cmd[1] = 0b0001xxxx;	// Limite max -X°C
	cmd[2] = 0bxxxxxx00;	// Limite max -X°C
	i2c.write(addr_i2c, cmd, 3);
	
	addr_i2c = mpc9804_addr << 1;	// Write operation
	cmd[0] = I2C_REG_TCRIT
 	cmd[1] = 0b0000xxxx;	// Limite critique max +X°C
	cmd[2] = 0bxxxxxx00;	// Limite critique max +X°C	
	i2c.write(addr_i2c, cmd, 3);
	
	addr_i2c = mpc9804_addr << 1;	// Write operation
	cmd[0] = I2C_REG_RES
 	cmd[1] = 0b00000000;	// Resolution : 0.5°C
 	i2c.write(addr_i2c, cmd, 2);
	
	addr_i2c = mpc9804_addr << 1;	// Write operation
	cmd[0] = I2C_REG_CONFIG
 	cmd[1] = 0b00000010;	// Hysteresis : 1.5°C
	cmd[2] = 0b11001000;	// Alert output enable, Tcrit, tupper and tlower locked
	i2c.write(addr_i2c, cmd, 3);
}

int I2C_getTA()
{
	addr_i2c = mpc9804_addr << 1;	// Write operation
	cmd[0] = I2C_REG_TA;
	i2c.write(addr_i2c, cmd, 1);
	
	addr_i2c = (mpc9804_addr << 1) + 1;	// Read operation
	i2c.read(addr_i2c, cmd, 2);
	
	if((cmd[0] & 0x10) == 0x10) // Si Ta < 0°C
	{
		return cmd[0] * 16 + cmd[1] * 0.0625;
	}
	else
	{
		return 256 - (cmd[0] * 16 + cmd[1] * 0.0625);
	}
}




