// ������������ ����   def_Board.h

#define   def_Board

//  ���������� - �������� / ���������
//#define   def_Shifr

#define Ethernet_HALFDUPLEX     0
#define Ethernet_FULLDUPLEX     1

//* * * * * * * *  BOARD DEFINITIONS * * * * * * * * * * * * * * * * * * * * * * * *
// ����������
#define Led_G      PORTC.F2     // �������
#define Led_R      PORTC.F0     // �������
#define Led_Y      PORTC.F1     // ������
//  ���������� ���������� CMOS-������
#define SOUT       PORTB.F0
#define SIN        PORTB.F1
#define SRCLK      PORTB.F2

#define RS485_DE   PORTB.F6
#define RS485_nRE  PORTB.F7

#define SET_RS485_OUT RS485_DE=1; RS485_nRE=1;
#define SET_RS485_IN RS485_DE=0; RS485_nRE=0;

#define RCLK       PORTB.F3
#define REN_       PORTG.F6
#define SRCLR_     PORTG.F5
//  ����� ������ �� ���������� �� ����  � ���������� ����������� ����������
#define CP_RST_    PORTD.F0
#define CP_CTL0    PORTD.F1
#define CP_CTL1    PORTD.F2
#define CP_CTL2    PORTD.F3
#define VSW_CTL    PORTD.F4
#define CP_OUT     PORTD.F5
#define VLO_CTL    PORTD.F6    // �������� �������� �������: =1  �� 12�����, =0  �� 7�����
// ������� �������� ����� ��� �������� �������
#define FB_A       PORTA.F4
#define FB_B       PORTA.F5
#define FB_AMP     PORTA.F3
#define GND_SW     PORTA.F2
// ������� ���������� ���������� �������
#define VLO_OK     PORTG.F7
#define VHI_OK     PORTJ.F7
// ������������������ �� �����
#define SW0        PORTJ.F1     // =0 - ON, =1 - OFF
#define SW1        PORTJ.F0
#define SW2        PORTJ.F5
#define SW3        PORTJ.F4

//  ���� ������� � �������
#define   POWER     1
#define   COMMAND   2
#define   CMD       3
#define   PORT___   4
#define   IP        5
#define   TIME      6



