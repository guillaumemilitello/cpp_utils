#include <vector>

template<typename T>
bool linearSearch(const std::vector<T>& arr_, const T& v_)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i].equals(v))
        {
            return true;
        }
        // for sequential search if the array is sorted, we can quit earlier
	    if (arr[i] > v_)
        {
            return false;
        }
    }
    return false;
}