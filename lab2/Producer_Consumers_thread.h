//
// Created by wh1isper on 2019/11/6.
// 参考博客：https://blog.csdn.net/dailongjian2008/article/details/53184706 by Jaylon88
//

#ifndef OS_LAB2_DOC_PRODUCER_CONSUMERS_THREAD_H
#define OS_LAB2_DOC_PRODUCER_CONSUMERS_THREAD_H

#include <deque>
#include <vector>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <iostream>
#include <random>
#include <cstdlib>

class Producer_Consumers_thread {
private:
    std::deque<int> seat;           // buffer队列
    std::mutex m_mtx;               // 互斥锁
    std::condition_variable m_cv;   // 信号量
    int producer_num;               // 患者人数
    int consumer_num;               // 医生人数
    int max_seat;                   // 座位数（buffer区最大值）
private:
    void producer(int id);

    void consumer(int id);

public:
    Producer_Consumers_thread() : consumer_num(1), max_seat(3), producer_num(5) {}

    Producer_Consumers_thread(int _M, int _N, int _P) : consumer_num(_M), max_seat(_N), producer_num(_P) {}

    void start();
};


#endif //OS_LAB2_DOC_PRODUCER_CONSUMERS_THREAD_H
