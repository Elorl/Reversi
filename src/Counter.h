
#ifndef EX1_COUNTER_H
#define EX1_COUNTER_H

/**
 *  Counter.
 */
class Counter {
public:
    Counter();
    void increase(int number);
    void decrease(int number);
    int get();
private:
    int count;
public:
    void setCount(int count);
};


#endif //EX1_COUNTER_H
