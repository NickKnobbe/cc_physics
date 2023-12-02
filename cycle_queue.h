#ifndef CC_CYCLE_QUEUE
#define CC_CYCLE_QUEUE

template<class T>
class CycleQueue {
private:
    const int MAX_CAPACITY = 100000;
    int capacity = 0;
    int next_waiting_index = 0;
    int next_new_element_index = 0;
    int count = 0;
    T* inner_data;

public:
    CycleQueue() {
        next_waiting_index = 0;
        next_new_element_index = 0;
        capacity = 1000;
        inner_data = new T[capacity];
    }

    CycleQueue(int _capacity) {
        next_waiting_index = 0;
        next_new_element_index = 0;
        capacity = _capacity;
        inner_data = new T[capacity];
    }

    void enqueue(T element) {
        inner_data[next_new_element_index] = element;
        next_new_element_index = (next_new_element_index + 1) % capacity;
        ++count;
        if (count > capacity) {
            count = capacity;
        }
    }

    T* dequeue() {
        if (count < 1) {
            return nullptr;
        }
        ++next_waiting_index;
        T* element = &inner_data[next_waiting_index - 1];
        if (next_waiting_index >= capacity) {
            next_waiting_index = 0;
        }
        --count;
        return element;
    }

    bool is_empty() {
        return count < 1;
    }
};


#endif