//Avner Merhavi 203090436

// 21/01/18.
//

#include"ThreadPool.h"
#include "Command.h"
#include<unistd.h>
#include <pthread.h>

/**
 * constructor. creates an array of threads, which will be available for re-use.
 * @param threadsNum
 */
ThreadPool::ThreadPool(int threadsNum) : stopped(false) {
    threads = new pthread_t[threadsNum];
    for (int i = 0; i < threadsNum; i++) {
        pthread_create(threads + i, NULL, execute, this);
    }
    pthread_mutex_init(&qLock, NULL);
}
/**
 * calling execute tasks.
 * @param arg  thread pool
 * @return
 */
void *ThreadPool::execute(void *arg) {
    ThreadPool *pool = (ThreadPool *) arg;
    pool->executeTasks();
}

/**
 * addigna task to queue.
 * @param task
 */
void ThreadPool::addTask(Task *task) {
    tasksQueue.push(task);
}

/**
 *  infinite loop. Executes tasks by order of insertions.
 */
void ThreadPool::executeTasks() {
    while (!stopped) {
        pthread_mutex_lock(&qLock);
        if (!tasksQueue.empty()) {
            Task* task = tasksQueue.front();
            tasksQueue.pop();
            pthread_mutex_unlock(&qLock);
            task->execute();
        } else {
            pthread_mutex_unlock(&qLock);
            sleep(1);
        }
    }
}
/**
 * terminates threads.
 */
void ThreadPool::terminate() {
    pthread_mutex_destroy(&qLock);
    stopped = true;
    pthread_cancel(*threads);
}

ThreadPool:: ~ThreadPool() {
    delete[] threads;
}
