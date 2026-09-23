#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/// This function simulates giving us the number of available servers.
/// Ignore its implementation, all you need to know is that when you call
/// this function it returns an integer greater than 1. And you may assume it
/// does so in O(1) time.
/// No other assumptions can be made about this function.
int available_servers() {
    return 2 + rand() % 100;
}

/// `sublists` is the arrays that need to be merged
/// `sublist_sizes` is the size of each of those arrays (i.e. sublists[i] will have sublist_sizes[i] items)
/// `number_of_sublists` is the number of sublists passed to the function in the previous 2 parameters
int* merge_sorted_lists(int** sublists, int* sublist_sizes, int number_of_sublists) {
    int current_count = number_of_sublists;

    int** current_lists = new int*[current_count];
    int* current_sizes = new int[current_count];

    for (int i = 0; i < current_count; i++) {
        current_sizes[i] = sublist_sizes[i];

        current_lists[i] = new int[current_sizes[i]];

        for (int j = 0; j < current_sizes[i]; j++) {
            current_lists[i][j] = sublists[i][j];
        }
    }

    // 下一步写 pairwise merge
    while (current_count > 1) {

    int next_count = (current_count + 1) / 2;

    int** next_lists = new int*[next_count];
    int* next_sizes = new int[next_count];

    int next_index = 0;

    for (int i = 0; i < current_count; i += 2) {

        if (i + 1 < current_count) 
            {
                int left_size = current_sizes[i];
                int right_size = current_sizes[i + 1];

                int merged_size = left_size + right_size;

                next_sizes[next_index] = merged_size;
                next_lists[next_index] = new int[merged_size];

                int left_index = 0;
                int right_index = 0;
                int result_index = 0;

                // Merge while both lists still have items
                while (left_index < left_size &&
                       right_index < right_size)
                {
                    if (current_lists[i][left_index] <
                        current_lists[i + 1][right_index])
                    {
                        next_lists[next_index][result_index] =
                            current_lists[i][left_index];

                        left_index++;
                    }
                    else
                    {
                        next_lists[next_index][result_index] =
                            current_lists[i + 1][right_index];

                        right_index++;
                    }

                    result_index++;
                }

                // Copy remaining items from the left list
                while (left_index < left_size)
                {
                    next_lists[next_index][result_index] =
                        current_lists[i][left_index];

                    left_index++;
                    result_index++;
                }

                // Copy remaining items from the right list
                while (right_index < right_size)
                {
                    next_lists[next_index][result_index] =
                        current_lists[i + 1][right_index];

                    right_index++;
                    result_index++;
                }
            }
        
        else {
            next_sizes[next_index] = current_sizes[i];

            next_lists[next_index] =
                new int[current_sizes[i]];

            for (int j = 0; j < current_sizes[i]; j++) {
                next_lists[next_index][j] =
                    current_lists[i][j];
            }
        }

        next_index++;
    }

    // 下一步还要释放 current_lists
    // Delete the old round
        for (int i = 0; i < current_count; i++)
        {
            delete[] current_lists[i];
        }

        delete[] current_lists;
        delete[] current_sizes;

        // Move to the next round
        current_lists = next_lists;
        current_sizes = next_sizes;
        current_count = next_count;
    }
    // 然后 current_lists = next_lists
    // Copy the final merged list into the returned array
    int final_size = current_sizes[0];
    int* result = new int[final_size];

    for (int i = 0; i < final_size; i++)
    {
        result[i] = current_lists[0][i];
    }

    delete[] current_lists[0];
    delete[] current_lists;
    delete[] current_sizes;

    return result;
}

int* merge_sort(int* items, int n) {
    // Ask for the next k (the number of servers currently available)
    int k = available_servers();
    if (k > n) k = n;

    if (n <= 1) {
    int* result = new int[n];

    if (n == 1) {
        result[0] = items[0];
    }

    return result;
}
    // Implement the sorting logic, return a pointer to the sorted array on the heap
    int** sublists = new int* [k];
    int* sublist_sizes = new int[k];

    int base_size=n/k;
    int remainder = n%k;

    for (int i=0; i<k; i++) {
        sublist_sizes[i] = base_size;

        if(i< remainder) {
            sublist_sizes[i]++;
        }
        sublists[i] = new int[sublist_sizes[i]];
    }
    int index =0;
    for(int i=0; i<k; i++){
        for(int j=0; j<sublist_sizes[i]; j++){
            sublists[i][j] =items[index];
            index++;
        }
    }
    
    for(int i=0; i<k; i++){
       int* sorted_sublist = merge_sort(sublists[i], sublist_sizes[i]);

       delete[] sublists[i];

        sublists[i] = sorted_sublist;
    }

    
int* result =merge_sorted_lists(sublists, sublist_sizes, k);

for (int i = 0; i < k; i++) {
    delete[] sublists[i];
    }

    delete[] sublists;
    delete[] sublist_sizes;

    return result;
}

int main(int argc, char** argv) {

    bool data_from_console = argc == 1; // run './a.out' and './a.out bottom text' to see the difference

    int* sorted;
    int n;

    if (data_from_console) {

        srand(10001);

        cout << "Enter number of data values:" << endl;
        cin >> n;
        int* data = new int[n];
        cout << "Enter data values:" << endl;
        for (int i = 0; i < n; i++) {
            cin >> data[i];
        }
        sorted = merge_sort(data, n);
        delete[] data;
    } else {
        srand(time(nullptr));
        n = 10;
        int data[] = {9, 4, 7, 2, 1, 6, 8, 3, 5, 0};

        sorted = merge_sort(data, n);
    }

    cout << "Sorted values:" << endl;
    for (int i = 0; i < n; i++) {
        cout << sorted[i] << " ";
        if ((i & 31) == 31) cout << '\n'; // Break up lines so that line by line diff is useful
    }
    cout << endl;

    return 0;
}
