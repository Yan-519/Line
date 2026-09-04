#ifndef LINE_H
#define LINE_H


#include <iostream>
#include <string>;

template <typename T>
class Line {
private:
    T* array;
    size_t length;
    size_t current;

    void range_chack(int index) const {
        if (index < 0 || length <= index)
            throw std::out_of_range("Index out of range");
    }

    bool isFull() {
        return current == length;
    }

    bool isShrinkable() {
        return current <= length / 4;
    }

    class Iterator {
    private:
        T* m_ptr;

    public:
        Iterator(T* ptr) : m_ptr(ptr) {}

        // Dereference operator: returns the value
        T& operator*() const { return *m_ptr; }

        // Prefix increment operator: moves to next element
        Iterator& operator++() {
            m_ptr++;
            return *this;
        }

        // Inequality operator: checks loop termination
        bool operator!=(const Iterator& other) const {
            return m_ptr != other.m_ptr;
        }
    };

public:

    Line() {
        srand(time(0));
        this->clear();
    }

    Line(size_t size) {
        length = size;
        array = new T[length];
        current = 0;
    }

    //~Line() {
    //    delete[] array;
    //}

    void trim() {
        if (isFull()) {

            if (length == 0)
                length = 1;
            else 
                length *= 2;

            T* tmp = new T[length];
            for (size_t i = 0; i < current; i++)
                tmp[i] = array[i];

            delete[] array;
            array = tmp;
        }
        else if (isShrinkable()) {
            T* tmp = new T[length / 2];
            for (size_t i = 0; i < current; i++)
                tmp[i] = array[i];

            length /= 2;
            delete[] array;
            array = tmp;
        }
    }

    bool iscontain(T element_to_find) {
        for (int idx = 0; idx < current; idx++)
            if (array[idx] == element_to_find)
                return true;
        return false;
    }

	static bool iscontain(T* array, int length, T element_to_find) {
		for (int idx = 0; idx < length; idx++)
			if (array[idx] == element_to_find)
				return true;
		return false;
	}

    void add(T new_element) {
        trim();
        array[current++] = new_element;
    }


    //void remove(T removable) {
    //    bool found = false;
    //    T* copy = new T[current - 1];

    //    for (int idx = 0, temp_index = 0; idx < current; idx++)
    //    {
    //        if (array[idx] != removable || found) {
    //            copy[temp_index++] = array[idx];
    //        }
    //        else { 
    //            found = true;
    //        };
    //    }

    //    delete[] array;
    //    array = copy;
    //    current--;
    //}

    T pop() {
        if (isEmpty())
            throw std::invalid_argument("you can't pop if the line is empty");

        trim();
        T top = array[current];
        array[current--] = nullptr;
        return top;
    }

    void revers() {
        if (isEmpty())
            return;

        for (size_t idx = 0; idx < current / 2; idx++)
            std::swap(array[idx], array[current - idx]);
    }

    Line /* type* */ get_range(int start, int end) const {
        if (this->isEmpty())
            throw std::invalid_argument("The array is empty.");
        else if (start >= end)
            throw std::invalid_argument("start must be smaller than end");

        this->range_chack(start);
        this->range_chack(end - 1);

        Line<T> copy = new Line(end - start);
        for (int idx = start, index = 0; idx < end; idx++, index++)
            copy[index] = array[idx];

        return copy;
    }

    T at(int index) {
        this->range_chack(index);
        return array[index];
    }

    void at(int index, T new_element) {
        this->range_chack(index);
        array[index] = new_element;
    }

    T& operator[](int index) {//set
        this->range_chack(index);
        return array[index];
    }

    const T& operator[](int index) const {//get
        this->range_chack(index);
        return array[index];
    }

    void sort(bool isrevers = false) {
        for (int idex = 1; idex < current; idex++) {
            T now = array[idex];
            int j = idex - 1;
            while (j >= 0 && array[j] > now) {
                array[j + 1] = array[j];
                j--;
            }
            array[j + 1] = now;
        }

        if (isrevers)
            this->revers();
    }

    void max() {
        if (this->isEmpty())
            throw std::invalid_argument("The array is empty.");

        T max_value = array[0];
        for (int i = 1; i < current; ++i)
            if (array[i] > max_value)
                max_value = array[i];

        return max_value;
    }

    void min() {
        if (this->isEmpty())
            throw std::invalid_argument("The array is empty.");

        T min_value = array[0];
        for (int i = 1; i < current; ++i)
            if (array[i] < min_value)
                min_value = array[i];

        return min_value;
    }

    int size() {
        return length;
    }


    bool isEmpty() const {
        return current == 0;
    }

    void clear() {
        delete[] array;
        array = nullptr;
        length = 0;
        current = 0;
    }

    std::string toString() {
        std::string str = "[";
        for (int idx = 0; idx < current; idx++) {
            str += std::to_string(array[idx]);
            if (idx < current - 1) str += ", ";
        }
        return str + "]";
    }

    const T* get_array() {
        return array;
    }

    int find(T object) {
        for (int current_index = 0; current_index < current; current_index++)
            if (array[current_index] == object)
                return current_index;
        return -1;
    }

    int refind(T object) {
        for (int current_index = current - 1; current_index > -1; current_index--)
            if (array[current_index] == object)
                return current_index;
        return -1;
    }

    void to_set() {
        T* new_array = new T[current];
        int length = 0;
        for (int current_index = 0; current_index < current; current_index++)
            if (!this->iscontain(new_array, length, array[current_index])) 
                new_array[length++] = array[current_index];
            
        

        this->clear();
        current = length;
        array = new T[current];

        for (size_t current_index = 0; current_index < length; current_index++)
            array[current_index] = new_array[current_index];
        
		this->trim();
    }

    Iterator begin() { return Iterator(&array[0]); }
    Iterator end() { return Iterator(&array[current]); }

};

#endif //LINE_H