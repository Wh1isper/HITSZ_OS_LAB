//
// Created by wh1isper on 2019/11/6.
//

#include "Producer_Consumers_thread.h"

void Producer_Consumers_thread::start() {
    std::vector<std::thread> consumer;
    std::vector<std::thread> producer;
    consumer.clear();
    producer.clear();
    // 启动线程
    for (int i = 0; i < producer_num; i++) {
        producer.emplace_back(std::thread(&Producer_Consumers_thread::producer, this, i));
    }
    for (int i = 0; i < consumer_num; i++) {
        consumer.emplace_back(std::thread(&Producer_Consumers_thread::consumer, this, i));
    }
    // 等待生产者结束
    for (auto &p : producer) {
        p.join();
    }
    // 毒害消费者
    std::unique_lock<std::mutex> lck(m_mtx);
    seat.push_back(-1); // poison
    lck.unlock();
    // 等待消费者结束
    for (auto &c:consumer) {
        c.join();
    }
}

void Producer_Consumers_thread::producer(int id) {
    srand(id);
    while (true) {
        // 随机时间启动
        int milscd = ((rand() % (10-2+1))+ 2)*1000;
        std::chrono::milliseconds dura(milscd);
        std::this_thread::sleep_for(dura);
        std::unique_lock<std::mutex> lck(m_mtx);
        if (seat.size() == max_seat) {
            // 座位满，进入下一个随机时间启动
            printf("病人%d来了\n无空余座位，病人%d暂时回去了\n", id, id);
            lck.unlock();
            continue;
        } else {
            seat.push_back(id);
            printf("病人%d来了\n病人%d坐在了座位上，当前座位剩余%lu\n", id, id, max_seat - seat.size());
            lck.unlock();
            m_cv.notify_all();
            return;
        }
    }
}

void Producer_Consumers_thread::consumer(int id) {
    srand(id);
    while (true) {
        std::unique_lock<std::mutex> lck(m_mtx);
        while (seat.empty()) {
            // 队列空，等待唤醒
            printf("医生%d正在等待病人（Zzzzzzz）\n", id);
            m_cv.wait(lck);
            // 被唤醒啦
            printf("病人来了，医生%d被叫醒了\n",id);
        }
        int patient_id = seat.front();
        if (patient_id == -1) {
            // 所有患者均看病完成，毒害线程
            printf("没有剩余病人，医生%d下班了\n", id);
            lck.unlock();
            m_cv.notify_all();
            return;
        }
        // 病人进房间，医生开始诊疗
        printf("  医生%d正在治病  病人%d正在看病\n", id, patient_id);
        seat.pop_front();
        lck.unlock();
        // 治人也要时间
        int milscd = ((rand() % (5-3+1))+ 3)*1000;
        std::chrono::milliseconds dura(milscd);
        std::this_thread::sleep_for(dura);
        printf("  病人%d离开了医生%d的办公室\n", patient_id, id);
    }
}
