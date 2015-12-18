#include<iostream>
#include<string>
#include<cassert>
using namespace std;

int appendToAll(string a[], int n, string value)    {
    // If the string is negative, returns -1.
    if (n < 0)
        return -1;
    // Goes through each component in string a and add value.
    for (int k = 0; k < n; k++) {
        a[k] += value;
    }
    // Returns n, the size of the array.
    return n;
}


int lookup(const string a[], int n, string target)  {
    // Only goes through loop if n is 0 or greater, else returns -1.
    if (n >= 0)
    {
        // Goes through each component in string a to check if target appears.
        for (int k = 0; k < n; k++)  {
            if (a[k] == target)
                // Returns the position of the first target.
                return k;
        }
    }
     return -1;
}


int positionOfMax(const string a[], int n)  {
    // Only goes through loop if n is greater than 0, else returns -1.
    if (n > 0)
    {
        string greatestString = a[0];
        int position = 0;
        // Goes through each component in string to
        for (int k = 0; k < n; k++) {
            // If a component is greater than the current greatest string it is stored as greatestString and its position is saved, until a larger string appears.
            if (a[k] > greatestString)  {
                greatestString = a[k];
                position = k;
            }
        }
        // Returns the position of the greatest string.
        return position;
    }
    return -1;
}


int rotateLeft(string a[], int n, int pos)  {
    // If n is greater than 0 AND the position is within the boundaries of the array, run through loops. Else returns -1.
     if (n > 0 && pos + 1 <= n && pos >=0)  {
         // Stores string that is being rotated.
        string endString = a[pos];
         // Goes through loop to move each component after position pos to the left.
        for (int k = pos; k < n-1; k++)
            a[k] = a[k+1];
         // After loop, moves string at position pos to the end.
        a[n-1] = endString;
         // Returns original pos.
        return pos;
    }
    return -1;
}


int rotateRight(string a[], int n, int pos) {
    // If n is greater than 0 AND the position is within the boundaries of the array, runs through loop. Else returns -1.
    if (n > 0 && pos + 1 <= n && pos >=0)  {
        // Stores string that is being rotated.
        string frontString = a[pos];
        // Goes through loop to move each component before position pos to the right.
        for (int k = pos; k > 0; k--)
            a[k] = a[k-1];
        // After loop, moves string at position pos to the front.
        a[0] = frontString;
        // Returns original pos.
        return pos;
    }
    return -1;
}


int flip(string a[], int n) {
    // If n is greater than 0, runs through loop. Else returns -1.
    if(n > 0)   {
        // Goes through loop to switch the front component with its correspnding end component.
        for(int k = 0; k < n/2; k++)    {
            string temp = a[k];
            a[k] = a[n-1-k];
            a[n-1-k] = temp;
        }
        // Returns n, the size of the array.
        return n;
    }
    return -1;
}

int differ(const string a1[], int n1, const string a2[], int n2)    {
    // If n1 AND n2 are greater than or equal to 0, goes through loop. Else returns -1.
    if (n1 >= 0 && n2 >= 0) {
        int sameElements = 0;
        // Goes through loop and counts the amount of same components.
        for (int k = 0; k < n1 && k < n2; k++)  {
            if(a1[k] == a2[k])
                sameElements++;
            // If one component differs from its corresponding component, breaks loop.
            else break;
        }
        // Returns the first position at which the corresponding components are not equal (or if they are equal up to the point when one runs out, returns the smaller of n1 and n2.)
        return sameElements;
    
    }
    return -1;
}

int subsequence(const string a1[], int n1, const string a2[], int n2)   {
    // If n1 AND n2 are greater than or equal to 0, goes through loop. Else returns -1.
    if (n1 >= 0 && n2 >= 0) {
        // Goes through loop to check each component of a1.
        for (int k = 0; k < n1; k++)    {
            // Checks to see if component of a1 matches the first component of a2.
            if (a1[k] == a2[0])  {
                int positionOfSub = k;
                // Goes through loop to check if all components of n2 match subsequentially.
                for (int j = 0; ; j++)    {
                    // Returns the position of the start of the subsequence in a1 if a1 contains a2.
                    if (j == n2)
                        return k;
                    else if (a1[positionOfSub] == a2[j])
                        positionOfSub++;
                    // If it does not match, go through loop again.
                    else break;
                }
            }
        }
    }
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) {
    // If n1 AND n2 are greater than or equal to 0, goes through loop. else returns -1.
    if (n1 >= 0 && n2 >= 0) {
        for(int k = 0; k < n1; k++) {   // Goes through nested loop to compare each component of a1 with each component of a2.
            for(int j = 0; j < n2; j++) {
                if(a1[k] == a2[j])
                    return k;           // Returns the position of the first component in a1 that matches any component in a2.
            }
        }
        return -1;
    }
    return -1;
}

int separate(string a[], int n, string separator)   {
    // If n is greater than 0, goes through loop. Else returns -1.
    if (n > 0)  {
        // Repeatedly, if component is larger than string, moves component left by calling previous function.
        for(int k = 0; k < n; k++)  {
            if (a[k] > separator)  {
                rotateLeft (a, n, k);
            }
        }
        // Ensures that each component was moved to the left.
        for(int k = 0; k < n; k++)  {
            if (a[k] > separator)  {
                rotateLeft (a, n, k);
            }
        }
        // Returns the position of the component that is greater than or equal to the separator string.
        for (int j = 0; j < n; j++) {
            if (a[j] >= separator)
                return j;
        }
        // Returns the size of the array if none of the components are greater than or equal to the separator string.
        return n;
    }
    return -1;
}

int main()  {
    
    //TEST FOR appendToAll
    /*string testArray[] = { "Regina", "Snow", "Emma", "Prince Charming", "Henry"};
    string appendage;
    
    cout << "What would you like to add?" << endl;
    getline(cin, appendage);
    
    const int arraySize = 5;
    
    cout << "The return value of the function is " << appendToAll(testArray, arraySize, appendage) << endl;
    
    for (int i = 0; i < arraySize; i++) {
        
        cout << testArray[i] << endl;
    }
    */
    
    
    //TEST for positionOfMax
    /*string testArray[] = { "zeta", "alpha", "beta", "theta", "pi", "zombie"};
    const int arraySize = 5;
    
    
    cout << "The position of the max string is at " << positionOfMax(testArray, arraySize) << endl;
    */
    
    
    
    //TEST for rotateLeft
    /*string testArray[] = { "Epsilon", "Alpha", "Beta", "Gamma", "Delta"};
    const int arraySize = 5;
    cout << rotateLeft(testArray, arraySize, 0) << endl;
    
    cout << "{";
    for (int k = 0; k < arraySize; k++) {
        cout << testArray[k];
        if (k < arraySize - 1)
            cout << ", ";
    }
    cout << "}" << endl;
    */
    
    
    //TEST for rotateRight
    /*string testArray[] = { "Beta", "Alpha", "Gamma", "Delta", "Epsilon", };
    const int arraySize = 5;
    cout << rotateRight(testArray, arraySize, 1) << endl;
    
    cout << "{";
    for (int k = 0; k < arraySize; k++) {
        cout << testArray[k];
        if (k < arraySize - 1)
            cout << ", ";
    }
    cout << "}" << endl;
    */
    
    //TEST for flip
    /*string testArray[] = {"Eta", "Zeta", "Epsilon", "Delta", "Gamma", "Beta", "Alpha"};
    const int arraySize = 7;
    cout << flip(testArray, arraySize) << endl;
    
    cout << "{";
    for (int k = 0; k < arraySize; k++) {
        cout << testArray[k];
        if (k < arraySize - 1)
            cout << ", ";
    }
    cout << "}" << endl;
    */
    
    //TEST for differ
    /*string test1[] = {"Alpha", "Beta", "Gamma", "Delta", "Epsilon"};
    string test2[] = {"Alpha", "Beta", "Gamma", "Delta", "Epsilon", "Zeta"};
    int n1 = 5;
    int n2 = 6;
    
    cout << "The return value is " << differ(test1, n1, test2, n2) << endl;
    */
    
    
    //TEST for subsequence
    /*string test1[] = {"Alpha", "Beta", "Gamma", "Delta", "Epsilon", "Zeta" };
    string test2[] = { "Gamma", "Delta", "Epsilon"};
    cout << "The return value is " << subsequence(test1, 6, test2, 3) << endl;
    */
    
    //TEST for lookupAny
    /*string test1[] = {"Alpha", "Beta", "Gamma", "Delta", "Epsilon"};
    string test2[] = {"Arizona", "alpha", "Africa", "google", "Delta"};
    
    cout << lookupAny(test1, 5, test2, 5) << endl;
    */
    
    //TEST for separate
    /*string testArray[] = {"Alpha", "Beta", "Whiskey", "Oscar", "Mike", "Sierra", "Kilo", "November"};    //DEBUG
    const int arraySize = 8;
    string separator = "Crystal";
    cout << separate(testArray, arraySize, separator) << endl;
    
    cout << "{";
    for (int k = 0; k < arraySize; k++) {
        cout << testArray[k];
        if (k < arraySize - 1)
            cout << ", ";
    }
    cout << "}" << endl;
    */
    
    string h[7] = { "glenn", "carl", "carol", "rick", "", "maggie", "daryl" };
    assert(lookup(h, 7, "maggie") == 5);
    assert(lookup(h, 7, "carol") == 2);
    assert(lookup(h, 2, "carol") == -1);
    assert(positionOfMax(h, 7) == 3);
    
    string g[4] = { "glenn", "carl", "rick", "maggie" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "glenn?" && g[3] == "maggie?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "rick?" && g[3] == "carl?");
    
    string e[4] = { "carol", "rick", "", "maggie" };
    assert(subsequence(h, 7, e, 4) == 2);
    assert(rotateRight(e, 4, 1) == 1 && e[0] == "rick" && e[2] == "");
    
    string f[3] = { "rick", "carol", "tara" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "tara" && f[2] == "rick");
    
    assert(separate(h, 7, "daryl") == 3);
    
    cout << "All tests succeeded" << endl;
    
    
}




