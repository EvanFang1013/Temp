import spidev
from time import sleep
DEBUG = False

#setup and open an SPI channel
spi_max_speed = 32 * 1000000 # 4 MHz
spi = spidev.SpiDev()
spi.open(0,0)
spi.max_speed_hz = spi_max_speed

def setOutput(val):
# lowbyte has 8 data bits D0..D7
    lowByte = val & 0xff; # 0b 1111 1111
# highbyte has control and data bits
# control bits are:
# B7, B6, B5, B4, B3, B2, B1, B0
# W ,BUF, !GA, !SHDN, B11, B10, B9, B8
# B7=0:write to DAC, B6=0:unbuffered, B5=1:Gain=1X, B4=1:Output is active
    highByte = ((val >> 8) & 0xff) | 0b0 << 7 | 0b0 << 6 | 0b1 << 5 | 0b1 << 4;
# by using spi.xfer2(), the CS is released after each block, transferring the
# value to the output pin.
    spi.xfer2([highByte, lowByte])

try:
    print ("Expect 2kHz square wave by MCP4921...")
    print ("Ctrl+C to quit")

    while(True):
        #newbits = int(0) #min. Vout
        #setOutput(newbits)
        #sleep(0.000125)
        for i in range (0,4095,1):
                       
            newbits = int(i) #max. Vout
            setOutput(newbits)
            sleep(0.01)
        for a in range(i,0,-1):
            newbits = int(a) #max. Vout
            setOutput(newbits)
            sleep(0.01)
        
except KeyboardInterrupt:
    print ("\nClosing SPI channel")
    spi.close()

def main():
    pass

if name == 'main':
    main()

