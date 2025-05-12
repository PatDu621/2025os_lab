#include "asm_utils.h"
#include "interrupt.h"
#include "stdio.h"
#include "program.h"
#include "thread.h"

// 屏幕IO处理器
STDIO stdio;
// 中断管理器
InterruptManager interruptManager;
// 程序管理器
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

// 先来先服务调度函数
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
    // 中断管理器
    interruptManager.initialize();
    interruptManager.enableTimeInterrupt();
    interruptManager.setTimeInterrupt((void *)asm_time_interrupt_handler);

    // 输出管理器
    stdio.initialize();

    // 进程/线程管理器
    programManager.initialize();

    // 创建所有线程
    programManager.executeThread(first_thread, nullptr, "first thread", 1);
    programManager.executeThread(second_thread, nullptr, "second thread", 1);
    programManager.executeThread(third_thread, nullptr, "third thread", 1);
    programManager.executeThread(fourth_thread, nullptr, "fourth thread", 1);

    // 开始执行先来先服务调度
    fcfs_schedule();

    // 避免系统过早停止
    while (1) {
        asm_halt();
    }
}

