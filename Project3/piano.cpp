#include<iostream>
#include<string>
#include<cctype>
using namespace std;


bool isTuneWellFormed (string tune);
bool isTunePlayable (string tune);
bool isBeatPlayable (string beat);
int translateTune(string tune, string& instructions, int& badBeat);
char translateNote(int octave, char noteLetter, char accidentalSign);
string translateBeat(string beat);

// To ensure that '/' is not confused with '\'
const char END_OF_BEAT = '/';


// My test int main to test my functions.
int main()
{
    string test, translation;
    int troubleBeat;
    cout << "Enter tune: ";
    getline(cin, test);
    
    cout << "isTuneWellFormed returns ";
    if (isTuneWellFormed(test))
        cout << "true" << endl;
    else
        cout << "false" << endl;
    
    cout << "isTunePlayable returns ";
    if (isTunePlayable(test))
        cout << "true" << endl;
    else
        cout << "false" << endl;
    
    cout << endl;
    
    
    int returnValue = translateTune(test, translation, troubleBeat);
    
    
    // Translation of tune is changed and the return value should be 0.
    if (isTunePlayable(test) == true)
        cout << "The tune is playable and the translation of the tune is " << translation << " and the return value is " << returnValue << endl;
    
    // Bad beat is changed and the return value should be 2.
    else if (isTuneWellFormed(test) == true)
        cout << "The tune is well-formed, but not playable. The bad beat is " << troubleBeat << " and the return value is " << returnValue <<  endl;
    
    // Parameters are unchanged and the return value should be 1.
    else
        cout << "The tune is not playable or well-formed. The return value is " << returnValue << endl;
}

bool isTuneWellFormed (string tune)
{
    // Checks for empty tune, since empty tune is still well-formed
    if (tune.size() == 0)
        return true;
    
    // If tune is not empty, check if tune ends with '/'
    else if (tune[tune.size()-1] != END_OF_BEAT)
        return false;
    
    // Repeatedly go through and check each character in tune
    int k = 0;
    while(k < tune.size())
    {
        // Checks for '/'
        if (tune[k] == END_OF_BEAT)
            k++;
        
        // Verifies that the character between '/'s is a valid note letter
        else if (tune[k] != 'A' && tune[k] != 'B' && tune[k] != 'C' && tune[k] != 'D' && tune[k] != 'E' && tune[k] != 'F' && tune[k] != 'G')
            return false;
        
        else
        {
            k++;
            
            // Checks for possible accidental
            if (tune[k] == '#'|| tune[k] == 'b')
                k++;
            
            // Checks for possible octave identifier
            if (isdigit(tune[k]))
                k++;
        }
    }
    
    // If tune passes through all checks, the tune is well-formed and returns true.
    return true;
}



bool isTunePlayable (string tune)
{
    // Checks for empty tune, since empty tune is also playable
    if (tune.size() == 0)
        return true;
    
    // If tune is not empty, check if tune ends with '/'
    else if (tune[tune.size()-1] != END_OF_BEAT)
        return false;
    
    // Repeatedly go through and check each character in tune
    int k = 0;
    while(k < tune.size())
    {
        // Checks for '/'
        if (tune[k] == END_OF_BEAT)
            k++;
        
        // Verifies that the character between '/'s is a valid note letter
        else if (tune[k] != 'A' && tune[k] != 'B' && tune[k] != 'C' && tune[k] != 'D' && tune[k] != 'E' && tune[k] != 'F' && tune[k] != 'G')
            return false;
        
        // Check individually for 'C' since it has several exceptions
        else if (tune[k] == 'C')
        {
            k++;
            if (tune[k] == '#' || tune[k] == 'b')
                k++;
            
            // Special case for Cb6
            if (tune[k-1] == 'b' && tune[k] == '6')
                k++;
            
            // C has octave ranges from 2 to 6.
            else if (tune[k] == '2' || tune[k] == '3' || tune[k] == '4' || tune[k] == '5' || tune[k] == '6')
                k++;
            
        }
        
        // Special case for B#1
        else if (tune[k] == 'B' && tune[k+1] == '#' && tune[k+2] == '1')
            k++;
        
        else
        {
            k++;
            
            // Checks for possible accidental
            if (tune[k] == '#'|| tune[k] == 'b')
                k++;
            
            // Checks if note is in playable octave range
            if (tune[k] == '2' || tune[k] == '3' || tune[k] == '4' || tune[k] == '5')
                k++;
        }
    }
    
    // If tune passes through all checks, the tune is playable and returns true.
    return true;
    
}


int translateTune(string tune, string& instructions, int& badBeat)
{
    string temp, beat;
    
    // Check if tune is playable
    if (isTunePlayable(tune) == true)
    {
        // Translate the tune beat by beat.
        for(int k = 0; k < tune.size(); beat = "")
        {
            for ( ;tune[k] != END_OF_BEAT; k++)
            {
                temp = beat;
                beat = temp + tune[k];
            }
            
            // Calls function to translate the beat
            string translatedBeat = translateBeat(beat);
            
            // If beat is empty (i.e. //), enters a space.
            if(translatedBeat.size() == 0)
            {
                temp = instructions;
                instructions = temp + " ";
            }
            
            // If there is more than one note in a beat, enters an open bracket
            else if(translatedBeat.size() > 1)
            {
                temp = instructions;
                instructions = temp + "[";
            }
            
            // Enters the translated beat into the instructions
            temp = instructions;
            instructions = temp + translatedBeat;
            
            // As above, if there is more than one note in a beat, enters a close bracket
            if(translatedBeat.size() > 1)
            {
                temp = instructions;
                instructions = temp + "]";
            }
            
            if(tune[k] == END_OF_BEAT)
                k++;
        }
        return 0;
    }
    
    
    // If tune is not playable but is well formed, set badBeat to number of the beat of the first unplayable note and return 2.
    else if (isTuneWellFormed (tune) == 1)
    {
        int numberOfEndBeats = 0;
        int badBeatCounter = 1;
        for(int t = 0; t < tune.size(); t++)
        {
            if(tune[t] == END_OF_BEAT)
                numberOfEndBeats++;
        }
        
        for(int k = 0; k < (tune.size() - numberOfEndBeats); )
        {
            for ( ;tune[k] != END_OF_BEAT; k++)
            {
                temp = beat;
                beat = temp + tune[k];
            }
            
            if (tune[k] == END_OF_BEAT)
                k++;
            
            // Counts the bad beat and returns when it is not playable.
            if(isBeatPlayable(beat) == 1)
            {
                badBeatCounter += 1;
                beat = "";
            }
            else
                break;
        }
    
        badBeat = badBeatCounter;
        return 2;
    }
    
    // If tune is not playable OR well formed, return 1.
    else
        return 1;
}




//*************************************
//  translateNote function given by Professor Smallberg
//*************************************

// Given an octave number, a note letter, and an accidental sign, return
// the character that the indicated note translates to if it is playable.
// Return a space character if it is not playable.
//
// First parameter:   the octave number (the integer 4 is the number of the
//                    octave that starts with middle C, for example).
// Second parameter:  an upper case note letter, 'A' through 'G'
// Third parameter:   '#', 'b', or ' ' (meaning no accidental sign)
//
// Examples:  translateNote(4, 'A', ' ') returns 'Q'
//            translateNote(4, 'A', '#') returns '%'
//            translateNote(4, 'H', ' ') returns ' '


char translateNote(int octave, char noteLetter, char accidentalSign)
{
    // This check is here solely to report a common CS 31 student error.
    if (octave > 9)
    {
        cerr << "********** translateNote was called with first argument = "
        << octave << endl;
    }
    
    // Convert Cb, C, C#/Db, D, D#/Eb, ..., B, B#
    //      to -1, 0,   1,   2,   3, ...,  11, 12
    
    int note;
    switch (noteLetter)
    {
        case 'C':  note =  0; break;
        case 'D':  note =  2; break;
        case 'E':  note =  4; break;
        case 'F':  note =  5; break;
        case 'G':  note =  7; break;
        case 'A':  note =  9; break;
        case 'B':  note = 11; break;
        default:   return ' ';
    }
    switch (accidentalSign)
    {
        case '#':  note++; break;
        case 'b':  note--; break;
        case ' ':  break;
        default:   return ' ';
    }
    
    // Convert ..., A#1, B1, C2, C#2, D2, ... to
    //         ..., -2,  -1, 0,   1,  2, ...
    
    int sequenceNumber = 12 * (octave - 2) + note;
    
    string keymap = "Z1X2CV3B4N5M,6.7/A8S9D0FG!H@JK#L$Q%WE^R&TY*U(I)OP";
    if (sequenceNumber < 0  ||  sequenceNumber >= keymap.size())
        return ' ';
    return keymap[sequenceNumber];
}



// Translates the beat note by note
string translateBeat(string beat)
{
    string temp, translatedBeat;
    int octave = 0;
    char noteLetter, accidentalSign;
    
    // Repeatedly, goes through and translates each note of the beat.
    for(int j = 0; j < beat.size(); )
        
    {
        // Counts first note
        if(isupper(beat[j]))
        {
            noteLetter = beat[j];
            j++;
        }
        
        // Checks for possible accidental
        if(beat[j] == '#' || beat[j] == 'b')
        {
            accidentalSign = beat[j];
            j++;
        }
        
        // If no accidental present, a space is entered in for the accidental sign.
        else
            accidentalSign = ' ';
        
        
        // Translates octave number character to an int value
        if(isdigit(beat[j]))
        {
            char a[5] = {'2', '3', '4', '5', '6'};
            int b[5] = {2, 3, 4, 5, 6};
            
            for(int d = 0; d != 5 ; d++)
            {
                if(beat[j] == a[d])
                {
                    octave = b[d];
                    j++;
                    break;
                }
            }
        }
        
        // If no given octave value, octave will be set to the default octave, 4.
        else octave = 4;
        
        char newNote = translateNote(octave, noteLetter, accidentalSign);
        
        const string stringkeymap[55] {"Z", "1", "X", "2", "C", "V", "3", "B", "4", "N", "5", "M", ",", "6", ".", "7", "/", "A", "8", "S", "9", "D", "0", "F", "G", "!", "H", "@", "J", "K", "#", "L", "$", "Q", "%", "W", "E", "^", "R", "&", "T", "Y", "*", "U", "(", "I", ")", "O", "P", "\"", " "};
        
        const char charkeymap[55] {'Z','1', 'X', '2', 'C', 'V', '3', 'B', '4', 'N', '5', 'M', ',', '6', '.', '7', '/', 'A', '8', 'S', '9', 'D', '0', 'F', 'G', '!', 'H', '@', 'J', 'K', '#', 'L', '$', 'Q', '%', 'W', 'E', '^', 'R', '&', 'T', 'Y', '*', 'U', '(', 'I', ')', 'O', 'P', '"', ' '};
        
        
        // Just in case adding char to strings wouldn't work, I constructed an array to translate char to string so that they can be added.
        for(int z = 0;z < 55; z++)
        {
            if(newNote == charkeymap[z])
            {
                temp = translatedBeat;
                translatedBeat = temp + stringkeymap[z];
                break;
            }
        }
    }
    // Returns the new translated beat
    return translatedBeat;
}


// Test function to check if a beat is playable ~ similar to isTunePlayable, but specific to beats.
bool isBeatPlayable(string beat)
{
    int k = 0;
    while(k < beat.size())
    {
        if (beat[k] != 'A' && beat[k] != 'B' && beat[k] != 'C' && beat[k] != 'D' && beat[k] != 'E' && beat[k] != 'F' && beat[k] != 'G')
            return false;
    
    // Check individually for 'C' since it has several exceptions
        else if (beat[k] == 'C')
        {
            k++;
            if (beat[k] == '#' || beat[k] == 'b')
                k++;
            
            // Special case for Cb6
            if (beat[k-1] == 'b' && beat[k] == '6')
                k++;
            
            // C has octave ranges from 2 to 6.
            else if (beat[k] == '2' || beat[k] == '3' || beat[k] == '4' || beat[k] == '5' || beat[k] == '6')
                k++;
            
        }
    
    // Special case for B#1
        else if (beat[k] == 'B' && beat[k+1] == '#' && beat[k+2] == '1')
            k++;
    
        else
        {
            k++;
            
            // Checks for possible accidental
            if (beat[k] == '#'|| beat[k] == 'b')
                k++;
            
            // Checks if note is in playable octave range
            if (beat[k] == '2' || beat[k] == '3' || beat[k] == '4' || beat[k] == '5')
                k++;
        }
}

// If tune passes through all checks, the tune is playable and returns true.
return true;
}




