#include <algorithm>
#include <vector>
#include <iostream>
namespace ybt {
template <typename T>
void shell_sort(std::vector<T>& arr)
{
    int j;
    auto gap = arr.size() / 2;
    while (gap)
    {
        for (auto i = gap; i < arr.size(); ++i)
        {
            T temp = arr[i];
            for (j = i - gap; j >= 0 && arr[j] > temp; j -= gap)
                std::swap(arr[j], arr[j + gap]);
            // arr[j] = temp;
        }
        gap /= 2;
    }
}
} // namespace ybt