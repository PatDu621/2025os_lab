//�޸ĺ��interrupt.cpp


#include "os_type.h"
#include "os_constant.h"
#include "asm_utils.h"
#include "stdio.h"

extern STDIO stdio;

int times = 0;

InterruptManager::InterruptManager()
{
    initialize();
}

void InterruptManager::initialize()
{
    // ��ʼ���жϼ�������
    times = 0;

    // ��ʼ��IDT
    IDT = (uint32 *)IDT_START_ADDRESS;
    asm_lidt(IDT_START_ADDRESS, 256 * 8 - 1);

    for (uint i = 0; i < 256; ++i)
    {
        setInterruptDescriptor(i, (uint32)asm_unhandled_interrupt, 0);
    }

    // ��ʼ��8259AоƬ
    initialize8259A();
}

void InterruptManager::setInterruptDescriptor(uint32 index, uint32 address, byte DPL)
{
    IDT[index * 2] = (CODE_SELECTOR << 16) | (address & 0xffff);
    IDT[index * 2 + 1] = (address & 0xffff0000) | (0x1 << 15) | (DPL << 13) | (0xe << 8);
}

void InterruptManager::initialize8259A()
{
    // ICW 1
    asm_out_port(0x20, 0x11);
    asm_out_port(0xa0, 0x11);
    // ICW 2
    IRQ0_8259A_MASTER = 0x20;
    IRQ0_8259A_SLAVE = 0x28;
    asm_out_port(0x21, IRQ0_8259A_MASTER);
    asm_out_port(0xa1, IRQ0_8259A_SLAVE);
    // ICW 3
    asm_out_port(0x21, 4);
    asm_out_port(0xa1, 2);
    // ICW 4
    asm_out_port(0x21, 1);
    asm_out_port(0xa1, 1);

    // OCW 1 ������Ƭ�����жϣ�����Ƭ��IRQ2��Ҫ����
    asm_out_port(0x21, 0xfb);
    // OCW 1 ���δ�Ƭ�����ж�
    asm_out_port(0xa1, 0xff);
}

void InterruptManager::enableTimeInterrupt()
{
    uint8 value;
    // ������ƬOCW
    asm_in_port(0x21, &value);
    // ������Ƭʱ���жϣ���0����
    value = value & 0xfe;
    asm_out_port(0x21, value);
}

void InterruptManager::disableTimeInterrupt()
{
    uint8 value;
    asm_in_port(0x21, &value);
    // �ر�ʱ���жϣ���1�ر�
    value = value | 0x01;
    asm_out_port(0x21, value);
}

void InterruptManager::disableTimeInterrupt()
{
    uint8 value;
    asm_in_port(0x21, &value);
    // �ر�ʱ���жϣ���1�ر�
    value = value | 0x01;
    asm_out_port(0x21, value);
}

void InterruptManager::setTimeInterrupt(void *handler)
{
    setInterruptDescriptor(IRQ0_8259A_MASTER, (uint32)handler, 0);
}

// �жϴ�����
int count = 0; //λ��
uint8 color =0; //��ɫ
extern "C" void c_time_interrupt_handler()
{
    // �����Ļ
    for (int i = 0; i < 80; ++i)
    {
        stdio.print(0, i, ' ', 0x07);
    }

    // ����жϷ����Ĵ���
    ++times;
    ++count;
    char str[] = "23336062 Yifei Du and the interrupt happened: ";
    char number[10];
    int temp = times;

    // ������ת��Ϊ�ַ�����ʾ
    for(int i = 0; i < 10; ++i ) {
        if(temp) {
            number[i] = temp % 10 + '0';
        } else {
            number[i] = '0';
        }
        temp /= 10;
    }


    // �ƶ���굽(0,0)����ַ�
    stdio.moveCursor(0);
    for(int i = 0; str[i]; ++i ) {
        //��������
        if (i == count){
            stdio.print(str[i], color); //0x0eΪ��ɫ  //һ����ʾ�����ַ�
            stdio.print(str[i+1], ++color %= 16); //
            stdio.print(str[i+2], ++color %= 16); //colorΪ��������ɫ
            i += 2;
        }
        else{
            stdio.print(str[i]);
        }
    }

    ++count; //�����
    count %= 37;

    // ����жϷ����Ĵ���
    for( int i = 9; i > 0; --i ) {
        stdio.print(number[i]);
    }
}
                                                

