#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/ioport.h>
#include <linux/ktime.h>
#include <linux/hrtimer.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/delay.h>

MODULE_LICENSE("Dual BSD/GPL");

/* GPIO base address */
#define GPIO_BASE_ADDR (0x3F200000)

/* Controller register base address */
#define BSC1_BASE_ADDR (0x3F804000)
 
/* BSC1 registers i hit */
#define BSC1_REG_C (BSC1_BASE_ADDR + 0x00000000)
#define BSC1_REG_S (BSC1_BASE_ADDR + 0x00000004)
#define BSC1_REG_DLEN (BSC1_BASE_ADDR + 0x00000008)
#define BSC1_REG_SLAVE_ADDR (BSC1_BASE_ADDR + 0x0000000C)
#define BSC1_REG_FIFO (BSC1_BASE_ADDR + 0x00000010)
#define BSC1_REG_DIV (BSC1_BASE_ADDR + 0x00000014)
#define BSC1_REG_DEL (BSC1_BASE_ADDR + 0x00000018)
#define BSC1_REG_CLKT (BSC1_BASE_ADDR + 0x0000001C)


#define GPFSEL0_BASE_ADDR (GPIO_BASE_ADDR + 0x00000000)
#define GPFSEL1_BASE_ADDR (GPIO_BASE_ADDR + 0x00000004)
#define GPFSEL2_BASE_ADDR (GPIO_BASE_ADDR + 0x00000008)
#define GPFSEL3_BASE_ADDR (GPIO_BASE_ADDR + 0x0000000C)
#define GPFSEL4_BASE_ADDR (GPIO_BASE_ADDR + 0x00000010)
#define GPFSEL5_BASE_ADDR (GPIO_BASE_ADDR + 0x00000014)
#define GPSET0_BASE_ADDR (GPIO_BASE_ADDR + 0x0000001C)
#define GPSET1_BASE_ADDR (GPIO_BASE_ADDR + 0x00000020)
#define GPCLR0_BASE_ADDR (GPIO_BASE_ADDR + 0x00000028)
#define GPCLR1_BASE_ADDR (GPIO_BASE_ADDR + 0x0000002C)
#define GPLEV0_BASE_ADDR (GPIO_BASE_ADDR + 0x00000034)
#define GPLEV1_BASE_ADDR (GPIO_BASE_ADDR + 0x00000038)
#define GPPUD_BASE_ADDR (GPIO_BASE_ADDR + 0x00000094)
#define GPPUDCLK0_BASE_ADDR (GPIO_BASE_ADDR + 0x00000098)
#define GPPUDCLK1_BASE_ADDR (GPIO_BASE_ADDR + 0x0000009C)

/* Using gpio as alternate 0 */
#define GPIO_DIRECTION_ALT0 (4)

#define PULL_NONE (0)
#define PULL_DOWN (1)
#define PULL_UP (2)

//Needed GPIO
#define GPIO_02 (2)
#define GPIO_03 (3)

#define START_TRANSFER_SEND (0x00008080)
#define START_TRANSFER_RECIVE (0x00008081)
#define CLEAR_STATUS (0x00000302)
#define SETUP_CTRL_SEND (0x00008110)
#define SETUP_CTRL_RECIVE (0x00008031)

// Declaration of i2c_driver.c functions
int i2c_driver_init(void);
void i2c_driver_exit(void);
static int i2c_driver_open(struct inode *, struct file *);
static int i2c_driver_release(struct inode *, struct file *);
static ssize_t i2c_driver_read(struct file *, char *buf, size_t , loff_t *);
static ssize_t i2c_driver_write(struct file *, const char *buf, size_t, loff_t *);

/* Buffer to store data */
#define BUFF_LEN 80
static char i2c_driver_buffer[BUFF_LEN];
static char data_for_sending[BUFF_LEN];

/* Structure that declares the usual file access functions. */
struct file_operations i2c_driver_fops =
{
    open    :   i2c_driver_open,
    release :   i2c_driver_release,
    read    :   i2c_driver_read,
    write   :   i2c_driver_write
};

module_init(i2c_driver_init);
module_exit(i2c_driver_exit);

/* Major number */
int i2c_driver_major;

/* Register addresses */
volatile void *reg_c = NULL;
volatile void *reg_dlen = NULL;
volatile void *reg_slave_addr = NULL;
volatile void *reg_fifo = NULL;
volatile void *reg_s = NULL;
volatile void *reg_div = NULL;

unsigned int GetGPFSELReg(char pin){
    	unsigned int addr;
     if(pin >= 0 && pin <10)
        addr = GPFSEL0_BASE_ADDR;
    else if(pin >= 10 && pin <20)
        addr = GPFSEL1_BASE_ADDR;
    else if(pin >= 20 && pin <30)
        addr = GPFSEL2_BASE_ADDR;
    else if(pin >= 30 && pin <40)
        addr = GPFSEL3_BASE_ADDR;
    else if(pin >= 40 && pin <50)
        addr = GPFSEL4_BASE_ADDR;
    else /*if(pin >= 50 && pin <53) */
        addr = GPFSEL5_BASE_ADDR;
  
  return addr;
}

char GetGPIOPinOffset(char pin){
    
	if(pin >= 0 && pin <10)
        pin = pin;
    else if(pin >= 10 && pin <20)
        pin -= 10;
    else if(pin >= 20 && pin <30)
        pin -= 20;
    else if(pin >= 30 && pin <40)
        pin -= 30;
    else if(pin >= 40 && pin <50)
        pin -= 40;
    else /*if(pin >= 50 && pin <53) */
        pin -= 50;
    return pin;
}

void SetInternalPullUpDown(char pin, char value){
    
	unsigned int base_addr_gppud; 
    unsigned int base_addr_gppudclk; 
    void *addr = NULL;
    unsigned int tmp;
    unsigned int mask;
    
    /* Get base address of GPIO Pull-up/down Register (GPPUD). */
    base_addr_gppud = GPPUD_BASE_ADDR;
    
    /* Get base address of GPIO Pull-up/down Clock Register (GPPUDCLK). */
    base_addr_gppudclk = (pin < 32) ? GPPUDCLK0_BASE_ADDR : GPPUDCLK1_BASE_ADDR;

    /* Get pin offset in register . */
    pin = (pin < 32) ? pin : pin - 32;
    
    /* Write to GPPUD to set the required control signal (i.e. Pull-up or Pull-Down or neither
       to remove the current Pull-up/down). */
    addr = ioremap(base_addr_gppud, 4);
    iowrite32(value, addr);

    /* Wait 150 cycles ^  this provides the required set-up time for the control signal */
    
    /* Write to GPPUDCLK0/1 to clock the control signal into the GPIO pads you wish to
       modify ^  NOTE only the pads which receive a clock will be modified, all others will
       retain their previous state. */
    addr = ioremap(base_addr_gppudclk, 4);
    tmp = ioread32(addr);    
    mask = 0x1 << pin;
    tmp |= mask;        
    iowrite32(tmp, addr);

    /* Wait 150 cycles ^  this provides the required hold time for the control signal */
	
	/* Write to GPPUD to remove the control signal. */
    addr = ioremap(base_addr_gppud, 4);
    iowrite32(PULL_NONE, addr);

    /* Write to GPPUDCLK0/1 to remove the clock. */
    addr = ioremap(base_addr_gppudclk, 4);
    tmp = ioread32(addr);    
    mask = 0x1 << pin;
    tmp &= (~mask);        
    iowrite32(tmp, addr);
}

void SetGpioPinDirection(char pin, char direction){

    unsigned int base_addr; 
    void *addr = NULL;
    unsigned int tmp;
    unsigned int mask;
    
    /* Get base address of function selection register. */
    base_addr = GetGPFSELReg(pin);

    /* Calculate gpio pin offset. */
    pin = GetGPIOPinOffset(pin);    
    
    /* Set gpio pin direction. */
    addr = ioremap(base_addr, 4);
    tmp = ioread32(addr);

    mask = ~(0b111 << (pin*3));
    tmp &= mask;

    mask = (direction & 0b111) << (pin*3);
    tmp |= mask;

    iowrite32(tmp, addr);
}

int SendData(int n){

	unsigned int temp;
	short int i;

	/* Clear S reg */
	iowrite32(CLEAR_STATUS, reg_s);

	/* Setup C reg */
	iowrite32(SETUP_CTRL_SEND, reg_c);

	/* Write to FIFO reg */
	for(i = 0; i < n; i++){
		iowrite32((unsigned int)data_for_sending[i], reg_fifo);
	}

	/* Setup DLEN reg */
	iowrite32((unsigned int)n, reg_dlen);
	
	/* Starting transfer */
	iowrite32(START_TRANSFER_SEND, reg_c);

	/* Polling */
	do {
		temp = ioread32(reg_s);
	} while(!(temp & (1 << 1))); // While !DONE

	temp = ioread32(reg_s);
	temp &= 1 << 8;
	
	/* If there is error transfer */
	if(temp)
		return -1;
	else
		return 0;

}

int ReceiveData(int n){

	unsigned int temp;
	unsigned int temp_d;
	unsigned short i;

	i = 0;

	memset(i2c_driver_buffer, '\0', BUFF_LEN);
	
	/* Clear status register before new transmision */
	iowrite32(CLEAR_STATUS, reg_s);

	/* Ready C reg for read, clear fifo */
	iowrite32(SETUP_CTRL_RECIVE, reg_c);

	/* Set expected data length */
	iowrite32((unsigned int)n, reg_dlen);
	
	/* Start transfer */
	iowrite32(START_TRANSFER_RECIVE, reg_c);

	/* Waiting for DONE = 1 */
	do{
		temp = ioread32(reg_s);
	}while(!(temp & (1 << 1)));

	/* Reading data from fifo while there is some */
	do{
		temp = ioread32(reg_s);
		temp &= 1<<5;
		temp_d = ioread32(reg_fifo);
		i2c_driver_buffer[i] = temp_d;
		i++;
		if(i == n)
			break;					
	}while(temp);

	temp = ioread32(reg_s);
	temp &= 1 << 8;
	
	if(temp)
		return -1;
	else
		return 0;

}

int i2c_driver_init(void) {

	int result;	

	result = register_chrdev(0, "i2c_driver", &i2c_driver_fops);
	if(result < 0){

		printk(KERN_ALERT "i2c_driver cannot obtain major number %d\n", i2c_driver_major);
		return result;	

	}

	i2c_driver_major = result;
	printk(KERN_INFO "Inserting i2c_driver module...\n");
	printk(KERN_ALERT "i2c_driver major number is %d\n", i2c_driver_major);

	/* Allocating memory */
	if (request_mem_region(BSC1_BASE_ADDR, 0x20, "i2c_driver") == NULL) {
	
		printk(KERN_INFO "Data memory not available\n");
		return -1;

	}

	/* Setting pull up, and pin alt functions */
	SetGpioPinDirection(GPIO_02, GPIO_DIRECTION_ALT0);
	SetGpioPinDirection(GPIO_03, GPIO_DIRECTION_ALT0);
	SetInternalPullUpDown(GPIO_02, PULL_UP);
	SetInternalPullUpDown(GPIO_03, PULL_UP);

	/* Remaping registers virtual addreses to physical */
	reg_c = ioremap(BSC1_REG_C, 4);
	reg_dlen = ioremap(BSC1_REG_DLEN, 4);
	reg_slave_addr = ioremap(BSC1_REG_SLAVE_ADDR, 4);
	reg_fifo = ioremap(BSC1_REG_FIFO, 4);
	reg_s = ioremap(BSC1_REG_S, 4);
	reg_div = ioremap(BSC1_REG_DIV, 4);

	/* Set Frequency Divider */
	iowrite32(0x000009C4, reg_div);

	return 0;

}

void i2c_driver_exit(void){

	/* Free memory */
	release_mem_region(BSC1_BASE_ADDR, 0x20);

	/* Free major number */
	unregister_chrdev(i2c_driver_major, "i2c_driver");
	SetInternalPullUpDown(GPIO_02, PULL_NONE);
	SetInternalPullUpDown(GPIO_03, PULL_NONE);
	
	printk(KERN_INFO "Removing i2c_driver module\n");

}

static int i2c_driver_open(struct inode *inode, struct file *flip){

	return 0;

}

static int i2c_driver_release(struct inode *inode, struct file *flip){

	return 0;	

}


static ssize_t i2c_driver_read(struct file *filp, char *buf, size_t len, loff_t *f_pos) {

	int data_size = 0;

	if(*f_pos == 0) {

		data_size = strlen(i2c_driver_buffer);
	
		if(copy_to_user(buf, i2c_driver_buffer, data_size) != 0) {

			return -EFAULT;
		
		} else {

			(*f_pos) += data_size;
			return data_size;	
	
		}
		
	} else {

		return 0;

	}

}

static ssize_t i2c_driver_write(struct file *filp, const char *buf, size_t len, loff_t *f_pos){

	unsigned int temp;
	int n, i;
	
	
	if(copy_from_user(i2c_driver_buffer, buf, len) != 0) {

		return -EFAULT;

	} else {

		if(i2c_driver_buffer[0] == 'A'){

			temp = i2c_driver_buffer[1];
			iowrite32(temp, reg_slave_addr);
			temp = ioread32(reg_slave_addr);
			printk(KERN_ALERT "Slave Address is set to: %x\n", temp);		
	
		} else if (i2c_driver_buffer[0] == 'S'){

			n = (int)i2c_driver_buffer[1];

			for(i = 2; i < 2+n; i++)
				data_for_sending[i - 2] = i2c_driver_buffer[i];

			if(SendData(n) < 0)
				printk(KERN_ALERT "Sending data failed, device not responding!\n");
		
		} else if (i2c_driver_buffer[0] == 'R'){

			n = (int)i2c_driver_buffer[1];
			
			if(ReceiveData(n) < 0){
				printk(KERN_ALERT "Reading data failed, device not responding!\n");	
				i2c_driver_buffer[0] = 'E';
			}
		}

		return len;

	}

}
