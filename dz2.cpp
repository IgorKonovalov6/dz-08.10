#include <iostream>
using namespace std;

class DynamicArray {
private:
    int* data;      // указатель на данные
    int size;       // размер массива

public:
    // Конструктор
    DynamicArray(int n) {
        if (n <= 0) n = 1; // защита от некорректного размера
        size = n;
        data = new int[size];
        for (int i = 0; i < size; i++)
            data[i] = 0;
        cout << "sozdan masiv razmerom " << size << endl;
    }

    // Конструктор копирования
    DynamicArray(const DynamicArray& other) {
        size = other.size;
        data = new int[size];
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];
        cout << "vizvan konstruktor kopirovaniy" << endl;
    }

    // Деструктор
    ~DynamicArray() {
        delete[] data;
        cout << "masiv unichtojen" << endl;
    }

    // Функция вывода
    void print() const {
        cout << "{ ";
        for (int i = 0; i < size; i++)
            cout << data[i] << (i < size - 1 ? ", " : "");
        cout << " }" << endl;
    }

    // Геттер
    int get(int index) const {
        if (index < 0 || index >= size) {
            cout << "oshibka: vihod za granici masiva!" << endl;
            return 0;
        }
        return data[index];
    }

    // Сеттер
    void set(int index, int value) {
        if (index < 0 || index >= size) {
            cout << "oshibka: vihod za granici masiva!" << endl;
            return;
        }
        if (value < -100 || value > 100) {
            cout << "oshibka: znachenie vne diapazona [-100, 100]!" << endl;
            return;
        }
        data[index] = value;
    }

    // Добавление элемента в конец
    void push_back(int value) {
        if (value < -100 || value > 100) {
            cout << "oshibka: znachenie vne diapazona [-100, 100]!" << endl;
            return;
        }

        int* newData = new int[size + 1];
        for (int i = 0; i < size; i++)
            newData[i] = data[i];
        newData[size] = value;
        delete[] data;
        data = newData;
        size++;
        cout << "dobavleno znachenie " << value << endl;
    }

    // Операция сложения массивов
    DynamicArray add(const DynamicArray& other) const {
        int maxSize = max(size, other.size);
        DynamicArray result(maxSize);
        for (int i = 0; i < maxSize; i++) {
            int a = (i < size) ? data[i] : 0;
            int b = (i < other.size) ? other.data[i] : 0;
            result.set(i, a + b);
        }
        return result;
    }

    // Операция вычитания массивов
    DynamicArray subtract(const DynamicArray& other) const {
        int maxSize = max(size, other.size);
        DynamicArray result(maxSize);
        for (int i = 0; i < maxSize; i++) {
            int a = (i < size) ? data[i] : 0;
            int b = (i < other.size) ? other.data[i] : 0;
            result.set(i, a - b);
        }
        return result;
    }
};

int main() {
    cout << "zadanie 1" << endl;
    DynamicArray arr1(5);
    arr1.set(0, 10);
    arr1.set(1, -20);
    arr1.set(2, 30);
    arr1.print();

    cout << "\nzadanie 2" << endl;
    DynamicArray arr2 = arr1; // вызов конструктора копирования
    arr2.print();

    cout << "\nzadanie 3" << endl;
    arr1.push_back(40);
    arr1.print();

    cout << "\nzadanie 4" << endl;
    DynamicArray arr3(3);
    arr3.set(0, 5);
    arr3.set(1, 15);
    arr3.set(2, 25);
    cout << "arr3 = ";
    arr3.print();

    DynamicArray sum = arr1.add(arr3);
    DynamicArray diff = arr1.subtract(arr3);

    cout << "arr1 + arr3 = ";
    sum.print();

    cout << "arr1 - arr3 = ";
    diff.print();

    return 0;
}