#include <iostream>
#include <type_traits>
#include <initializer_list>
#include <stdexcept>
#include <ctime>
using namespace std;

//#include <vector>

template <typename type>
class Line {
private:
    type* array;
    int array_length;

    void range_chack(int index) const {
        if (index < 0 || index >= array_length)
            throw out_of_range("Index out of range");
    }

    bool iscontain(type* arr, int length, type element_to_find) {
        for (int current_index = 0; current_index < length; current_index++)
        {
            if (arr[current_index] == element_to_find)
                return true;
        }
        return false;
    }

public:
    Line() {
        srand(time(0));

        array_length = 0;
        array = nullptr;
    }

    Line(initializer_list<type> list) {
        srand(time(0));

        array_length = list.size();
        array = new type[array_length];
        int current_index = 0;
        for (const type& item : list) {
            array[current_index++] = item;
        }
    }

    ~Line() {
        delete[] array;
    }

    void add(type new_element) {
        type* copy = new type[array_length + 1];
        for (int current_index = 0; current_index < array_length; current_index++) {
            copy[current_index] = array[current_index];
        }
        copy[array_length] = new_element;
        array_length++;
        delete[] array;
        array = copy; 
    }


    void remove(type removable) {
        bool found = false;
        type* copy = new type[array_length - 1];

        for (int current_index = 0, temp_index = 0; current_index < array_length; current_index++)
        {
            if (array[current_index] != removable || found) {
                copy[temp_index++] = array[current_index];
            }
            else { 
                found = true;
            };
        }

        delete[] array;
        array = copy;
        array_length--;
    }

    type pop() {
        if (this->empty())
            throw invalid_argument("you can't pop if the line is empty");

        array_length--;
        type* copy = new type[array_length];
        type removd = array[array_length];
        for (int current_index = 0; current_index < array_length; current_index++)
        {
            copy[current_index] = array[current_index];
        }
        delete[] array;
        array = copy;
        return removd;

        //type removd = array[array_length - 1];
        //this->remove(array[array_length])
        //return removd;
    }

    type popback() {
        if (this->empty())
            throw invalid_argument("you can't pop if the line is empty");

        type* copy = new type[array_length - 1];
        type removd = array[0];
        int current_index = 0;
        for (int loop_index = 1; loop_index < array_length; loop_index++)
        {
            copy[current_index++] = array[loop_index];
        }
        delete[] array;
        array = copy;
        array_length--;
        return removd;

        //type removd = array[0];
        //this->remove(array[0])
        //return removd;
    }

    void revers() {
        if (this->empty())
            return;

        type* copy = new type[array_length];
        for (int current_index = 0; current_index < array_length; current_index++)
        {
            copy[current_index] = array[array_length - current_index - 1];
        }
        delete[] array;
        array = copy;
    }

    Line /* type* */ get_range(int start, int end) const {
        if (this->empty())
            throw invalid_argument("The array is empty.");
        else if (start >= end)
            throw invalid_argument("start must be smaller than end");

        this->range_chack(start);
        this->range_chack(end - 1);

        Line<type> copy;
        for (int current_index = start; current_index < end; current_index++) {
            copy.add(array[current_index]);
        }
        return copy;

        //type* copy = new type[end - start];
        //for (int current_index = start, int index = 0; current_index < end; current_index++) {
        //    copy[index++] = array[current_index];
        //}
        //return copy;
    }

    type at(int index) {
        this->range_chack( index);
        return array[index];
    }

    void at(int index, type new_element) {
        this->range_chack( index);
        array[index] = new_element;
    }

    type& operator[](int index) {//set
        this->range_chack( index);
        return array[index];
    }

    const type& operator[](int index) const {//get
        this->range_chack( index);
        return array[index];
    }

    typename enable_if<
        is_same<type, int>::value ||
        is_same<type, double>::value ||
        is_same<type, char>::value>::type
        creat(int len) {
        this->clear();

        array_length = len;
        array = new type[array_length];

        for (int current_index = 0; current_index < array_length; current_index++)
        {
            if (is_same<type, int>::value) {
                array[current_index] = rand() % 100;
            }
            else if (is_same<type, double>::value) {
                array[current_index] = static_cast<double>(rand()) / RAND_MAX * 100.0;
            }
            else if (is_same<type, char>::value) {
                array[current_index] = rand() % 26 + 97;
            }
            else throw invalid_argument("Type error.");
        }
    }

    //typename enable_if<
    //    is_same<type, int>::value ||
    //    is_same<type, double>::value ||
    //    is_same<type, char>::value>::type
    void sort(bool isrevers = false) {

        for (int current_index = 1; current_index < array_length; current_index++) {
            type now = array[current_index];
            int j = current_index - 1;
            while (j >= 0 && array[j] > now) {
                array[j + 1] = array[j];
                j--;
            }
            array[j + 1] = now;
        }

        if (isrevers) {
            this->revers();
        }
    }

    //typename enable_if<
    //    is_same<type, int>::value ||
    //    is_same<type, double>::value ||
    //    is_same<type, char>::value, type>::type
    void max() {
        if (this->empty())
            throw invalid_argument("The array is empty.");

        type max_value = array[0];
        for (int i = 1; i < array_length; ++i) {
            if (array[i] > max_value) {
                max_value = array[i];
            }
        }
        return max_value;
    }

    //typename enable_if<
    //    is_same<type, int>::value ||
    //    is_same<type, double>::value ||
    //    is_same<type, char>::value, type>::type
    void min() {
        if (this->empty())
            throw invalid_argument("The array is empty.");

        type min_value = array[0];
        for (int i = 1; i < array_length; ++i) {
            if (array[i] < min_value) {
                min_value = array[i];
            }
        }
        return min_value;
    }

    //typename enable_if<
    //    is_same<type, int>::value ||
    //    is_same<type, double>::value ||
    //    is_same<type, char>::value>::type
    void shuffle(int times = 1) {

        for (int j = 0; j < times; j++) {
            for (int i = 0; i < array_length; i++) {
                swap(array[i], array[rand() % array_length]);
            }
        }
    }

    //typename enable_if<
    //    is_same<type, int>::value ||
    //    is_same<type, double>::value ||
    //    is_same<type, char>::value>::type
    void sum() {
        if (this->empty())
            throw invalid_argument("The array is empty.");

        type sum = array[0];
        for (size_t current_index = 1; current_index < array_length; current_index++)
        {
            sum += array[current_index];
        }

        return sum;
    }

    int size() {
        return array_length;
    }

    const char* type_name() {
        return typeid(type).name();
    }

    bool empty() const {
        return array_length == 0;
    }

    void clear() {
        delete[] array;
        array = nullptr;
        array_length = 0;
    }

    void clone(type* list, int length) {
        this->clear();

        array_length = length;
        array = new type[array_length];
        for (int current_index = 0; current_index < array_length; current_index++) {
            array[current_index] = list[current_index];
        }
    }

    void creat(int len, type value) {
        this->clear();

        array_length = len;
        array = new type[array_length];

        for (int current_index = 0; current_index < array_length; current_index++)
        {
            array[current_index] = value;
        }
    }

    typename enable_if< is_same<type, int>::value ||
                        is_same<type, char>::value>::type
        creat_range(int start, int end, int diferent) {
        this->clear();
        //if (start == end)
        //    throw invalid_argument("indexes must be different");

        int comtroe_num = ((start <= end - 1) ? 1 : -1) * diferent;
        for (int current_number = start; current_number < end; current_number += comtroe_num)
        {
            this->add(current_number);
        }
    }

    typename enable_if< is_same<type, int>::value ||
        is_same<type, char>::value>::type
        creat_range(int start, int end) {
        this->clear();
        //if (start == end)
        //    throw invalid_argument("indexes must be different");

        int comtroe_num = (start <= end - 1) ? 1 : -1;
        for (int current_number = start; current_number < end; current_number += comtroe_num)
        {
            this->add(current_number);
        }
    }

    typename enable_if< is_same<type, int>::value ||
        is_same<type, char>::value>::type
        creat_range(int end) {
        this->clear();
        //if (end <= 0)  // Ensure that `end` is a positive number
        //    throw invalid_argument("End value must be greater than 0.");

        for (int current_number = 0; current_number < end; current_number++) {
            this->add(current_number);
        }
    }

    void display() {
        for (int current_index = 0; current_index < array_length; current_index++)
        {
            cout << array[current_index] << " ";
        }
        cout << endl;
    }

    const type* get_array() {
        return array;
    }

    int find(type object) {
        for (int current_index = 0; current_index < array_length; current_index++)
        {
            if (array[current_index] == object)
                return current_index;
        }
        return -1;
    }

    int refind(type object) {
        for (int current_index = array_length - 1; current_index > -1; current_index--)
        {
            if (array[current_index] == object)
                return current_index;
        }
        return -1;
    }

    void to_set() {
        type* new_array = new type[array_length];
        int length = 0;
        for (int current_index = 0; current_index < array_length; current_index++)
        {
            if (!this->iscontain(new_array, length, array[current_index])) {
                new_array[length++] = array[current_index];
            }
        }

        this->clear();
        array_length = length;
        array = new type[array_length];

        for (size_t current_index = 0; current_index < length; current_index++)
        {
            array[current_index] = new_array[current_index];
        }
    }
};

int main() {
    Line<int> line;
}
