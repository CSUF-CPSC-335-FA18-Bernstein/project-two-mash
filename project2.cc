///////////////////////////////////////////////////////////////////////////////
// project2.hh
//
// The three algorithms specified in the project 1 requirements
// document, plus helper functions.
//
///////////////////////////////////////////////////////////////////////////////

#include "project2.hh"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


//-----------------------------------------------------------------------------
// Randomize the order of all items in the list
//-----------------------------------------------------------------------------
void randomize_list(string_vector & strings)
{
    random_shuffle(strings.begin(), strings.end());
}

//-----------------------------------------------------------------------------
void merge(string_vector & strings, size_t start, size_t mid, size_t end)
{
    size_t i, j, k;
    size_t n1 = mid - start + 1;
    size_t n2 = end - mid;
    
    string L[n1];
    string R[n2];
    
    for (i = 0; i < n1; i++)
    {
        L[i] = strings[start + i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = strings[mid + 1 + j];
    }
    i = 0;
    j = 0;
    k = start;
    
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            strings[k] = L[i];
            j++;
        }
        else
        {
            strings[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        strings[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        strings[k] = R[j];
        j++;
        k++;
    }
}

//-----------------------------------------------------------------------------
// Sort the given list using the merge sort algorithm.
// This is a recursive method which splits the list into two
// parts, recursively calls itself on the two parts and then merges 
// the two parts together using the merge() method.
//-----------------------------------------------------------------------------
void mergesort(string_vector & strings, size_t start, size_t end)
{
    if (strings.size() <= 1)
        return;
    else
    {
        size_t mid = start + (end-1)/2;
        
        merge(strings, start, mid, end);
        merge(strings, start, mid, end);
        mergesort(strings, start, end);
    }
}

//-----------------------------------------------------------------------------
// Implementation of the Hoare Partition.
// This partition uses the first element of the list as a partition
// and divides the list into less than and greater than the pivot value
// It returns the index of the final position of the pivot value.
//-----------------------------------------------------------------------------
int hoare_partition(string_vector & strings, int start, int end)
{
    string pivot = strings[end];
    int i = (start - 1);
    
    for(int j = start; j <= end - 1; j++)
    {
        if(strings[j] <= pivot)
        {
            i++;
            swap(strings[i], strings[j]);
        }
    }
    swap(strings[i+1], strings[end]);
    return (i+1);
}

//-----------------------------------------------------------------------------
// Sort the given list using the quicksort algorithm.
// This is a recursive method which splits the list into two
// parts, recursively calls itself on the two parts and then merges 
// the two parts together using the merge() method.
//-----------------------------------------------------------------------------
void quicksort(string_vector & strings, int start, int end)
{
    if (start < end)
    {
        int pi = hoare_partition(strings, start, end);
        
        quicksort(strings, start, pi - 1);
        quicksort(strings, pi + 1, end);
    }
    return;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// ALREADY IMPLEMENTED 
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Load words from the file at the given path. The words vector is
// cleared, and then each word from the file is added to the
// vector. Returns true on success or fale on I/O error.
//-----------------------------------------------------------------------------
bool load_words(string_vector& words, const std::string& path) 
{
    //std::cout << "Loading words from [" << path << "]" << std::endl;
    words.clear();
    std::ifstream ifs(path.c_str());
    if (!ifs.is_open() || !ifs.good()) {
    //cout << "Failed to open [" << path << "]" << std::endl;
    return false;
    }
    int countWordsLoaded = 0;
    while (!ifs.eof()) {
    std::string lineBuffer;
    std::getline(ifs, lineBuffer);
    if (ifs.eof()) {
      break;
    }
    words.push_back(lineBuffer);
    countWordsLoaded++;
    }
    //std::cout << "Loaded " << countWordsLoaded << " words from [" << path << "]" << std::endl;;
    return true;
}

//-----------------------------------------------------------------------------
// Sort the given list using the merge sort algorithm.
// This method is simply a helper to make the initial 
// call the recursive mergesort() method below that requires
// first and last indexes for sorting range
//-----------------------------------------------------------------------------
void mergesort(string_vector & strings)
{
    if (strings.size() == 0) {
    return;
    }
    mergesort(strings, 0, strings.size() - 1);
    return;
}

//-----------------------------------------------------------------------------
// Sort the given list using the quicksort algorithm.
// This method is simply a helper to make the initial 
// call the recursive mergesort() method below that requires
// first and last indexes for sorting range
//-----------------------------------------------------------------------------
void quicksort(string_vector & strings)
{
    if (strings.size() == 0) {
    return;
    }
    quicksort(strings, 0, strings.size() - 1);
    return;
}

