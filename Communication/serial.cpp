#include "serial.h"

int k=0;
/****************************************
* @funcName SerialInit
* @brief    打开串口权限
* @para     无
* @return   无
* @date     2021.4.27
* @author   wjl
*****************************************/

bool UsbSerial::SerialInit()
{
       cout<<"+--------------------------------------"<<endl;
       cout<<"|            Usb Serial Send Data     |"<<endl;
       cout<<"+--------------------------------------"<<endl;
       //fd = open("/dev/ttyUSB0",O_RDWR | O_NOCTTY | O_NDELAY);
       fd = open("/dev/ttyUSB0",O_RDWR);
       if(-1 == fd)
       {
           cout<<"Error open Serial"<<endl;
           return false;
       }
       else
       {
           cout<<"Open Serial Successfully"<<endl;
       }
       /*---------- Setting the Attributes of --------- */

       struct termios SerialPortSettings;	/* Create the structure                          */

       tcgetattr(fd, &SerialPortSettings);	/* Get the current attributes of the Serial port */

       cfsetispeed(&SerialPortSettings,B115200); /* Set Read  Speed as 9600                       */
       cfsetospeed(&SerialPortSettings,B115200); /* Set Write Speed as 9600                       */

       SerialPortSettings.c_cflag &= ~PARENB;   /* Disables the Parity Enable bit(PARENB),So No Parity   */
       SerialPortSettings.c_cflag &= ~CSTOPB;   /* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
       SerialPortSettings.c_cflag &= ~CSIZE;	 /* Clears the mask for setting the data size             */
       SerialPortSettings.c_cflag |= CS8;       /* Set the data bits = 8                                 */

       SerialPortSettings.c_cflag &= ~CRTSCTS;       /* No Hardware flow Control                         */
       SerialPortSettings.c_cflag |= CREAD | CLOCAL; /* Enable receiver,Ignore Modem Control lines       */

       SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);          /* Disable XON/XOFF flow control both i/p and o/p */
       SerialPortSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);  /* Non Cannonical mode                            */

       SerialPortSettings.c_oflag &= ~OPOST;/*No Output Processing*/

       SerialPortSettings.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
       if((tcsetattr(fd,TCSANOW,&SerialPortSettings)) != 0) /* Set the attributes to the termios structure*/
       {
           cout<<"\n  ERROR ! in Setting attributes"<<endl;
       }
       else
       {
           cout<<"\n  BaudRate = 115200 \n  StopBits = 1 \n  Parity = none"<<endl;
           cout<<"Serial Start Work "<<endl;
       }
       tcflush(fd,TCIFLUSH);
       cout<<"+--------------------------------------"<<endl;
       /*------------------------------- Write data to serial port -----------------------------*/
       return true;
}

/****************************************
* @funcName TransformData
* @brief    发送内容
* @para     无
* @return   无
* @date     2022.4.2
* @author   cjh
*****************************************/
void UsbSerial::TransformData(const VisionData &data)
{
    Tdata[0] = 0xA5;
    Tdata[1] = CmdID1
//    Append_CRC8_Check_Sum(Tdata, 3);
    Tdata[3] =  data.yaw_angle.c[0];
    Tdata[4] =  data.yaw_angle.c[1];
    Tdata[5] =  data.yaw_angle.c[2];
    Tdata[6] =  data.yaw_angle.c[3];
    Tdata[7] =  data.pitch_angle.c[0];
    Tdata[8] =  data.pitch_angle.c[1];
    Tdata[9] =  data.pitch_angle.c[2];
    Tdata[10] = data.pitch_angle.c[3];
    Tdata[11] = data.dis.c[0];
    Tdata[12] = data.dis.c[1];
    Tdata[13] = data.dis.c[2];
    Tdata[14] = data.dis.c[3];
    Tdata[15] = data.TuoLuo;
    Tdata[16] = data.isshoot;
    Tdata[17] = 0x0D;
//    Append_CRC16_Check_Sum(Tdata, 20);
}

/****************************************
* @funcName send
* @brief    发送函数
* @para     无
* @return   无
* @date     2022.4.2
* @author   cjh
*****************************************/
void UsbSerial::send()
{

    write(fd, Tdata, 18);

//    for(int i = 0; i < 18; i++)
//    {
//       printf("%x  ",Tdata[i]);
//    }
//    cout << endl;

}

/****************************************
* @funcName closePort
* @brief    关闭通讯协议接口
* @para     无
* @return   无
* @date     2022.4.2
* @author   cjh
*****************************************/
void UsbSerial::closePort()
{
    close(fd);
}

/****************************************
* @funcName SerialRecData
* @brief    接受函数
* @para     无
* @return   无
* @date     2022.4.2
* @author   cjh
*****************************************/
void UsbSerial::SerialRecData(double *serial_data)
{
    int bytes_read = 0;
    //bytes_read = read(fd, &read_buffer, 3);


    size_t bytes;
        char *name = ttyname(fd);
        if ((name = nullptr))printf("tty is null\n");
        if (name != nullptr)printf("device:%s\n",name);
        ioctl(fd, FIONREAD, &bytes);

     uint many = 16;
     bytes = read(fd,rdata,many);
//——————————————————————————————————————————————————————————————————
     for(uint i = 0;i < many;i++){//强制拉回
         uint j = i+1;
         if(j == many){j=j-many;}
         if(rdata[i]==0xA5 && rdata[j]==9){
             uint l = i;
             for(uint k = 0;k<many;k++){
                 if(l == many){l=l-many;}
                 data[k]=rdata[l];
                 l++;
             }
         }
     }
//——————————————————————————————————————————————————————————————————
    float tuoluoyiP = 0,tuoluoyiY = 0;
    serial_data[0] = (int)data[3];//颜色
    serial_data[1] = (int)data[4];//装甲板1符2

    tuoluoyiY =((double)(data[5]<<8 | data[6]))*0.005494;
    serial_data[2]  = tuoluoyiY;
//              cout<<"tuoluoyiY"<< tuoluoyiY<<endl;

    tuoluoyiP =((double)(data[7]<<8 | data[8]))*0.005494;
    serial_data[3]  = tuoluoyiP;
//            cout<<"tuoluoyiP"<<tuoluoyiP<<endl;

    serial_data[4] = (int)data[9];//弹速




//         for(int i = 0; i < 16; i++)
//         {
//            printf("%d  ",data[i]);
//         }
//         printf(" \n");

}









