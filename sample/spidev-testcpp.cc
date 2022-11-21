#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <spidev_lib++.h>

int  main( void)
{
  uint8_t tx_buffer[32];
  uint8_t rx_buffer[32];
  
  SPI *controller = NULL;
  SPI *driver = NULL;

  spi_config_t controller_spi;
  spi_config_t driver_spi;
  
  controller_spi.mode=3;
  controller_spi.speed=1000000;
  controller_spi.delay=0;
  controller_spi.bits_per_word=8;
  controller = new SPI("/dev/spidev0.0",&controller_spi);
  
  driver_spi.mode=3;
  driver_spi.speed=1000000;
  driver_spi.delay=0;
  driver_spi.bits_per_word=8;
  driver = new SPI("/dev/spidev0.1",&controller_spi);
  

  if (controller->begin())
  {
    memset(tx_buffer,0,32);
    memset(rx_buffer,0,32);
    sprintf((char*)tx_buffer, "\x81\x00\x00\x00\x00");
    //printf("sending %s, to spidev2.0 in full duplex \n ",(char*)tx_buffer);
    printf("sending 0x 81 00 00 00 00 to controller\n");  
    //controller->xfer(tx_buffer,strlen((char*)tx_buffer),rx_buffer,strlen((char*)tx_buffer));
    controller->xfer(tx_buffer, 5, rx_buffer, 5);
    printf("rx_buffer = %s\n", (char *)(rx_buffer+1));
        
    sprintf((char*)tx_buffer,"\x00\x00\x00\x00\x00");
    printf("sending 0x 00 00 00 00 00 to controller\n"); 
    controller->xfer(tx_buffer, 5, rx_buffer, 5);
    printf("rx_buffer = %s\n", (char *)(rx_buffer+1));
    for (int i = 0; i < 5; ++i) 
    {
      printf("rx_buffer[i] = %d\n", rx_buffer[i]);
    }
    //controller->end();    
    delete controller;
  }
  
  if (driver->begin())
  {
    memset(tx_buffer,0,32);
    memset(rx_buffer,0,32);
    sprintf((char*)tx_buffer, "\x00\x00\x00\x00\x00");
    printf("sending 0x 00 00 00 00 00 to driver\n");
    driver->xfer(tx_buffer, 5, rx_buffer, 5);
    for (int i = 0; i < 5; ++i) 
    {
      printf("rx_buffer[i] = %d\n", rx_buffer[i]);
    }
    
    sprintf((char*)tx_buffer, "\x01\x00\x00\x00\x00");
    printf("sending 0x 01 00 00 00 00 to driver\n");
    driver->xfer(tx_buffer, 5, rx_buffer, 5);
    for (int i = 0; i < 5; ++i) 
    {
      printf("rx_buffer[i] = %d\n", rx_buffer[i]);
    }
    
    delete driver;
  }
  
  return 0;
}
