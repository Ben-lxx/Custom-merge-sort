#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Rectangle {
    int width;
    int height;

    bool operator<(const Rectangle right) const
    {
        return width * height < right.width * right.height;
    }
};

template<typename T>
void insertion_sort(T* array, int size) {
   for (int i = 1; i < size; i++)
    {
        T key = array[i];
        int j = i - 1;

        while (j >= 0 && key < array[j])
        {
            array[j + 1] = array[j];
            j--;
        }

        array[j + 1] = key;
    }
}

template<typename T>
void merge_sort(T* arr, int n) {
    if (n <= 1)
        return;

    int left_half_size = n / 2;
    int right_half_size = n - left_half_size;

    T* left_half = new T[left_half_size];
    T* right_half = new T[right_half_size];

    for (int i = 0; i < n; i++)
    {
        if (i < left_half_size)
        {
            left_half[i] = arr[i];
        }
        else
        {
            right_half[i - left_half_size] = arr[i];
        }
    }

    merge_sort(left_half, left_half_size);
    merge_sort(right_half, right_half_size);

    int left_half_index = 0;
    int right_half_index = 0;
    int result_index = 0;

    while (left_half_index < left_half_size &&
           right_half_index < right_half_size)
    {
        if (!(right_half[right_half_index] < left_half[left_half_index]))
        {
            arr[result_index] = left_half[left_half_index];
            left_half_index++;
            result_index++;
        }
        else
        {
            arr[result_index] = right_half[right_half_index];
            right_half_index++;
            result_index++;
        }
    }

    while (left_half_index < left_half_size)
    {
        arr[result_index++] = left_half[left_half_index++];
    }

    while (right_half_index < right_half_size)
    {
        arr[result_index++] = right_half[right_half_index++];
    }

    delete[] left_half;
    delete[] right_half;
}

int main() {
    srand(time(nullptr));

    Rectangle rects_1[10], rects_2[10];  //testing with 10 rectangles
    
    for (int i = 0; i < 10; i++) {
        rects_1[i].width = rand() % 20;
        rects_1[i].height = rand() % 20;
        rects_2[i].width = rects_1[i].width;
        rects_2[i].height = rects_1[i].height;
    }
    
    insertion_sort(rects_1, 10);
    merge_sort(rects_2, 10);
    int last_area = -1;
    
    for (int i = 0; i < 10; i++) {
        int cur_area = rects_1[i].width * rects_1[i].height;
        if (cur_area < last_area) {
            cout << "The sorted arrays don't match!" << endl;
            return 1;
        }
        last_area = cur_area;
    }
    
    for (int i = 0; i < 10; i++) {
        if (rects_1[i].width != rects_2[i].width || rects_1[i].height != rects_2[i].height) {
            cout << "The sorted arrays don't match!" << endl;
            return 1;
        }
    }
    
    cout << "Everything seems fine : )" << endl;


// ===== Extra Tests =====

cout << "\nTest 1 - Already sorted:" << endl;

Rectangle test1[4] = {
    {2, 2},
    {3, 3},
    {4, 4},
    {5, 5}
};

insertion_sort(test1, 4);

for (int i = 0; i < 4; i++)
{
    cout << test1[i].width * test1[i].height << " ";
}
cout << endl;


cout << "Test 2 - Reverse order:" << endl;

Rectangle test2[4] = {
    {5, 5},
    {4, 4},
    {3, 3},
    {2, 2}
};

merge_sort(test2, 4);

for (int i = 0; i < 4; i++)
{
    cout << test2[i].width * test2[i].height << " ";
}
cout << endl;


cout << "Test 3 - Equal areas:" << endl;

Rectangle test3[4] = {
    {2, 6},
    {3, 4},
    {1, 5},
    {2, 3}
};

insertion_sort(test3, 4);

for (int i = 0; i < 4; i++)
{
    cout << test3[i].width * test3[i].height << " ";
}
cout << endl;


cout << "Test 4 - Single item:" << endl;

Rectangle test4[1] = {
    {7, 3}
};

merge_sort(test4, 1);

cout << test4[0].width * test4[0].height << endl;


// 一定仍然在 main() 最后
return 0;
}