#include <iostream>
#include <vector>
#include <numeric>
#include <emscripten.h>
using namespace std;
 
// Helper function to 3–partition problem.
// It returns true if there exist three subsets with a given sum
bool isSubsetExist(vector<int> const &S, int n, int a, int b, int c, vector<int> &arr)
{
    // return true if the subset is found
    if (a == 0 && b == 0 && c == 0) {
        return true;
    }
 
    // base case: no items left
    if (n < 0) {
        return false;
    }
 
    // Case 1. The current item becomes part of the first subset
    bool A = false;
    if (a - S[n] >= 0)
    {
        arr[n] = 1;        // current element goes to the first subset
        A = isSubsetExist(S, n - 1, a - S[n], b, c, arr);
    }
 
    // Case 2. The current item becomes part of the second subset
    bool B = false;
    if (!A && (b - S[n] >= 0))
    {
        arr[n] = 2;        // current element goes to the second subset
        B = isSubsetExist(S, n - 1, a, b - S[n], c, arr);
    }
 
    // Case 3. The current item becomes part of the third subset
    bool C = false;
    if ((!A && !B) && (c - S[n] >= 0))
    {
        arr[n] = 3;        // current element goes to the third subset
        C = isSubsetExist(S, n - 1, a, b, c - S[n], arr);
    }
 
    // return true if we get a solution
    return A || B || C;
}
 
// Function for solving the 3–partition problem. It prints the subset if
// the given set `S[0…n-1]` can be divided into three subsets with an equal sum
extern "C" {   
    EMSCRIPTEN_KEEPALIVE 
    void partition(vector<int> const &S)
    {
        cout << "ACACAAC ";
        // get the sum of all elements in the set
        int sum = accumulate(S.begin(), S.end(), 0);
    
        // total number of items in `S`
        int n = S.size();
    
        // construct an array to track the subsets
        // `arr[i] = k` represents i'th item of `S` is part of k'th subset
        vector<int> arr(n);
    
        // set result to true if the sum is divisible by 3 and the set `S` can
        // be divided into three subsets with an equal sum
        bool result = (n >= 3) && !(sum % 3) &&
                isSubsetExist(S, n - 1, sum/3, sum/3, sum/3, arr);
    
        if (!result)
        {
            cout << "La partición de S = {"; 
            for (int i = 0; i < n; i++){
                cout << " " << S[i];
            }
            cout << " } no es posible";
            return;
        }
        cout << "La partición de S = {";
        for (int i = 0; i < n; i++)
        {
                cout << " " << S[i];
        }
        cout << " } es posible y estas serían:" << endl;
        // print the partitions
        for (int i = 0; i < 3; i++)
        {
            cout << "S" << i << " = { ";
            for (int j = 0; j < n; j++)
            {
                if (arr[j] == i + 1) {
                    cout << S[j] << " ";
                }
            }
            cout << "}" << endl;
        }
    }
} 
int main()
{
    // Input: a set of integers
    vector<int> S = { 7, 3, 2, 1, 5, 4, 8 };
 
    partition(S);
 
    return 0;
}