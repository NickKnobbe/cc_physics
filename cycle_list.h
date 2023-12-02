#ifndef CC_CYCLE_LIST
#define CC_CYCLE_LIST

template<class T>
class CycleList {
private:
    T* inner_data;
    bool actives[10000];
    int index_eval_next = 0;
    int max_capacity = 0;
    int size_present = 0;
public:
    CycleList() {
        max_capacity = 10000;
        for (int i = 0; i < max_capacity; ++i) {
            actives[i] = false;
        }
        inner_data = new T[max_capacity];
        index_eval_next = 0;
        size_present = 0;
    }
    CycleList(int _capacity) {
        max_capacity = _capacity;
        for (int i = 0; i < max_capacity; ++i) {
            actives[i] = false;
        }
        inner_data = new T[_capacity];
        index_eval_next = 0;
        size_present = 0;
    }
    ~CycleList() {
        delete[] inner_data;
    }

    T* peek_next() {
        while (!actives[index_eval_next]) {
            index_eval_next = ++index_eval_next % max_capacity;
        }
        return &inner_data[index_eval_next];
    }

    T* peek_advance_next() {
        while (!actives[index_eval_next]) {
            index_eval_next = ++index_eval_next % max_capacity;
        }
        T* result = &inner_data[index_eval_next];
        index_eval_next = ++index_eval_next % max_capacity;
        return result;
    }

    T* pop_next() {
        while (!actives[index_eval_next]) {
            index_eval_next = ++index_eval_next % max_capacity;
        }
        T result = inner_data[index_eval_next];
        actives[index_eval_next] = false;
        index_eval_next = ++index_eval_next % max_capacity;
        --size_present;
        return &result;
    }

    /// @brief Fill the next null spot 
    /// in the list.
    void fill_next(T element) {
        int safeguard = 0;
        while (actives[index_eval_next]) {
            index_eval_next = ++index_eval_next % max_capacity;
            ++safeguard;
            if (safeguard > size_present) {
                inner_data[index_eval_next] = element;
                actives[index_eval_next] = true;
                return;
            }
        }
        inner_data[index_eval_next] = element;
        actives[index_eval_next] = true;
        ++size_present;
    }

    int size_filled() {
        return size_present;
    }

    int capacity() {
        return max_capacity;
    }

    void verbose_print() {
        for (int i = 0; i < size_present; ++i) {
            if (actives[i]) {
                std::cout << inner_data[i] << std::endl;
            }
            else {
                std::cout << "nullptr" << std::endl;
            }
        }
    }
};

#endif