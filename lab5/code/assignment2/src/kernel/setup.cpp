#include "asm_utils.h"
#include "interrupt.h"
#include "stdio.h"
#include "program.h"
#include "thread.h"

// ��ĻIO������
STDIO stdio;
// �жϹ�����
InterruptManager interruptManager;
// ���������
ProgramManager programManager;

void fourth_thread(void *arg) {
    printf("pid %d name \"%s\": Hello World!\n", programManager.running->pid, programManager.running->name);
    asm_halt();
}

void third_thread(void *arg) {
    printf("pid %d name \"%s\": Hello World!\n", programManager.running->pid, programManager.running->name);
    asm_halt();
}

void second_thread(void *arg) {
    printf("pid %d name \"%s\": Hello World!\n", programManager.running->pid, programManager.running->name);
    asm_halt();
}

void first_thread(void *arg)
{               // �����Ϣ�������߳��Ѿ���ʼ����
    printf("pid %d name \"%s\": Hello World!\n", programManager.running->pid, programManager.running->name);
    asm_halt();
}

extern "C" void setup_kernel()
{

    // �жϹ�����
    interruptManager.initialize();
    interruptManager.enableTimeInterrupt();
    interruptManager.setTimeInterrupt((void *)asm_time_interrupt_handler);

    // ���������
    stdio.initialize();

    // ����/�̹߳�����
    programManager.initialize();

        int pid0 = programManager.executeThread(first_thread, nullptr, "first thread", 1);
    int pid1 = programManager.executeThread(second_thread, nullptr, "second thread", 1);
    int pid2 = programManager.executeThread(third_thread, nullptr, "third thread", 1);
        int pid3 = programManager.executeThread(fourth_thread, nullptr, "fourth thread", 1);
    //�ֶ��л�����һ���߳�
    ListItem *item = programManager.readyPrograms.front();
    PCB *firstThread = ListItem2PCB(item, tagInGeneralList);
    firstThread->status = RUNNING;
    programManager.readyPrograms.pop_front();
    programManager.running = firstThread;
    asm_switch_thread(0, firstThread); //���ں�̬�л����û�̬

    asm_halt();
}
