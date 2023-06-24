#include <vector>

template<typename T>
bool linearSearch(const std::vector<T>& arr_, const T& v_)
{
    for (unsigned i = 0; i < arr_.size(); i++)
    {
        if (arr_[i] == v_)
        {
            return true;
        }
        // for sequential search if the array is sorted, we can quit earlier
	    if (arr_[i] > v_)
        {
            return false;
        }
    }
    return false;
}