#include <iostream>
#include <cstring>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;

const int MAX_WORD_LENGTH = 20;
const int MAX_DOC_LENGTH = 200;
int standardizeRules (int distance[],
                      char word1[][MAX_WORD_LENGTH+1],
                      char word2[][MAX_WORD_LENGTH+1],
                      int nRules);

int determineQuality (const int distance[],
                      const char word1[][MAX_WORD_LENGTH+1],
                      const char word2[][MAX_WORD_LENGTH+1],
                      int nRules,
                      const char document[]);
void ruleRemover (int distance[],
                   char word1[][MAX_WORD_LENGTH+1],
                   char word2[][MAX_WORD_LENGTH+1],
                   int& nRules,
                   int position);

int main()
{
    
    const int TEST1_NCRITERIA = 4;
    int test1dist[TEST1_NCRITERIA] = {
        2,           4,          1,           13,
    };
    char test1w1[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "have",
    };
    char test1w2[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad",
    };
    
    for(int k = 0; k < 4; k++)
    {
        cout << "Rule " << k+1 << ": (" << test1dist[k] << ", " << test1w1[k] << ", " << test1w2[k] << ")" << endl;
    }
    

    // Assert tests to check functions.
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "The mad UCLA scientist unleashed a deranged evil giant robot.") == 2);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "The mad UCLA scientist unleashed    a deranged robot.") == 2);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "**** 2014 ****") == 0);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "  That plot: NEFARIOUS!") == 1);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "deranged deranged robot deranged robot robot") == 1);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "Two mad scientists suffer from deranged-robot fever.") == 0);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "The scientist that was mad was a mad scientist.") == 1);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "The mad mad scientist have mad deranged robot.") == 3);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "ROBOT IS DERANGED AND HAVE MAD SCIENTIST!!!") == 3);
    cout << "All tests succeeded" << endl;
    
}


int standardizeRules(int distance[],
                     char word1[][MAX_WORD_LENGTH+1],
                     char word2[][MAX_WORD_LENGTH+1],
                     int nRules)
{
    // If n is not positive, there are no standardized rules. Return 0.
    if (nRules <= 0)
        return 0;
    
    // Loop to check each element of each array, row by row
    for (int k = 0; k < nRules; k++)
    {
        // Checks if distance is positive, else removes the rule (row).
        if (distance[k] < 0)
        {
            ruleRemover(distance, word1, word2, nRules, k);
            k--;
        }
        else
        {
            // Loop to check each char for alpha char, else removes the rule
            for (int j = 0; word1[k][j] != '\0' || word2[k][j] != '\0'; j++)
            {
                //Checks for empty string
                if (strlen(word1[k]) == 0 || strlen(word2[k]) == 0)
                {
                    ruleRemover(distance, word1, word2, nRules, k);
                    k--;
                }
                
                if ((isalpha(word1[k][j]) == 0 || isalpha(word2[k][j]) == 0) && word1[k][j] != '\0'  && word2[k][j] != '\0')
                {
                    ruleRemover(distance, word1, word2, nRules, k);
                    k--;
                }
                // Changes rules to lowercase
                else
                {
                    word1[k][j] = tolower(word1[k][j]);
                    word2[k][j] = tolower(word2[k][j]);
                }
            }
        }
    }
    
    // Checks for repeat rules and removes repeats
    for(int k = 0; k < nRules; k++)
    {
        for(int j = 0; j < nRules; j++)
        {
            if(((strcmp(word1[k], word2[j]) == 0) && (strcmp(word2[k], word1[j]) == 0))||((strcmp(word1[j], word1[k]) == 0) && (strcmp(word2[j], word2[k]) == 0) && k != j))
            {
                // Removes the repeat rule that has a smaller distance
                if(distance[k] >= distance[j])
                {
                    ruleRemover(distance, word1, word2, nRules, j);
                    k--;

                }
                else
                {
                    ruleRemover(distance, word1, word2, nRules, k);
                    k--;
                }
            }
        }
        
    }
// Returns the amount of standardized rules
return nRules;

}


int determineQuality (const int distance[],
                      const char word1[][MAX_WORD_LENGTH+1],
                      const char word2[][MAX_WORD_LENGTH+1],
                      int nRules,
                      const char document[])
{
    int rulesMatched = 0;
    char tempDoc [MAX_DOC_LENGTH+1] = { };
    char tempDocArray [MAX_DOC_LENGTH+1][MAX_DOC_LENGTH+1];
    int wordNumber = 0;
    int pos = 0;
    
    if (nRules <= 0)
        return 0;
    
    // Copy the document into a local variable, removing non-alpha and non-space characters.
    for(int k = 0; document[k] != '\0'; k++)
    {
        if(isalpha(document[k]) || document[k] == ' ')
        {
            // Makes all letters lowercase in the temporary document.
            tempDoc[pos] = tolower(document[k]);
            pos++;
        }
    }
    
    // Translates the tempDoc into a 2 dimensional array so the individual words can be checked with the
    char tempCString[MAX_DOC_LENGTH+1];
    for(int j = 0; tempDoc[j] != '\0'; j++)
    {
        // Only copies alpha characters into the array
        if(isalpha(tempDoc[j]))
        {
            for(int k = j; isalpha(tempDoc[k]) != 0; k++)
            {
                char tempLetter[2] = {tempDoc[k]};
                strcat(tempCString, tempLetter);
                j++;
            }
            // Copies string into array and reinitializes tempCString to empty.
            strcpy(tempDocArray[wordNumber], tempCString);
            strcpy(tempCString, "");
            wordNumber++;
        }
    }

    // Loop to check each rule individually
    for(int k = 0; k < nRules; k++)
    {
        int repeatRule = 0;
        // Loop to check each word in tempDocArray
        for(int j = 0; j < wordNumber; j++)
        {
            // If there is a word that matches a rule word, check distance.
            if (strcmp(tempDocArray[j], word1[k]) == 0)
            {
                for(int l = 0; l < wordNumber; l++)
                {
                    if((strcmp(tempDocArray[l], word2[k]) == 0) && (abs(j-l) <= distance[k]) && j != l )
                    {
                        repeatRule++;
                    }
                }
            }
        }
        // Checks for repeat rules and adds to number of rules matched
        if (repeatRule > 0)
            rulesMatched++;
    }
    return rulesMatched;
}

// Function to remove a rule.
void ruleRemover (int distance[],
                  char word1[][MAX_WORD_LENGTH+1],
                  char word2[][MAX_WORD_LENGTH+1],
                  int& nRules,
                  int pos)
{
    // Moves each component of the rule to the end of the array (similar to rotate left from project 5)
    int endDistance = distance[pos];
    for (int k = pos; k < nRules-1; k++)
        distance[k] = distance[k+1];
    distance[nRules-1] = endDistance;

    char endWord1[MAX_WORD_LENGTH+1];
    strcpy(endWord1, word1[pos]);
    for (int k = pos; k < nRules-1; k++)
        strcpy(word1[k], word1[k+1]);
    strcpy (word1[nRules-1], endWord1);
    
    char endWord2[MAX_WORD_LENGTH+1];
    strcpy(endWord2, word2[pos]);
    for (int k = pos; k < nRules-1; k++)
        strcpy(word2[k], word2[k+1]);
    strcpy (word2[nRules-1], endWord2);
    
    // Decreases number of components in array
    nRules--;
}



