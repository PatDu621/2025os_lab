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

}

void third_thread(void *arg) {
    printf("pid %d name \"%s\": Hello World!\n", programManager.running->pid, programManager.running->name);
}

void second_thread(void *arg) {
    printf("pid %d name \"%s\": Hello World!\n", programManager.running->pid, programManager.running->name);

}

void first_thread(void *arg)
{
    printf("pid %d name \"%s\": Hello World!\n", programManager.running->pid, programManager.running->name);

}

// �����ȷ�����Ⱥ���
void fcfs_schedule() {
    if (!programManager.readyPrograms.empty()) {
        ListItem *item = programManager.readyPrograms.front();
        PCB *nextThread = ListItem2PCB(item, tagInGeneralList);
        nextThread->status = RUNNING;
        programManager.readyPrograms.pop_front();
        programManager.running = nextThread;
        asm_switch_thread(0, nextThread);
    }
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

    // ���������߳�
    programManager.executeThread(first_thread, nullptr, "first thread", 1);
    programManager.executeThread(second_thread, nullptr, "second thread", 1);
    programManager.executeThread(third_thread, nullptr, "third thread", 1);
    programManager.executeThread(fourth_thread, nullptr, "fourth thread", 1);

    // ��ʼִ�������ȷ������
    fcfs_schedule();

    // ����ϵͳ����ֹͣ
    while (1) {
        asm_halt();
    }
}

