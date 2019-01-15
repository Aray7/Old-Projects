#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

//Binary search of the dictionary for a specific word (query)
bool check(string* dictionary, int dictionarySize, int left, int right, string query)
{
    int middle = (left + right) / 2;

    if(dictionary[middle] == query)
        return true;

    else if(left > right)
        return false;

    else
    {
        if(query < dictionary[middle])
            return check(dictionary, dictionarySize, left, middle - 1, query);
        else
            return check(dictionary, dictionarySize, middle + 1, right, query);
    }
}

//Swap two characters in a string
void swap(string& word, int i, int j)
{
    int temp = word[i];
    word[i] = word[j];
    word[j] = temp;
}

//Checks if the permutations vector already contains a certain word
//This handles the case in which words like "apple" and "apple" are
//considered separate cases by the permute function, but really these
//are the same word - the two p's are just switched.
bool contains(vector<string> permutations, string query)
{
    for(int i = 0; i < permutations.size(); i++)
    {
        if(permutations[i] == query)
          return true;
    }
    return false;
}

//Generates all unique permutations of a given string
//and drops them into a vector
//NOTE: For this function to work correctly, the initial function
//call should be permute(permutations, word, 0);
void permute(vector<string>& permutations, string word, int k)
{
    if(k == word.length() && !contains(permutations, word))
        permutations.push_back(word);

    else
        for(int j = k; j < word.length(); j++)
        {
            swap(word, j, k);
            permute(permutations, word, k+1);
            swap(word, j, k);
        }
}

int main()
{
    string* dictionary;
    int dictionarySize;
    vector<string> permutations;
    ifstream dictionary_Txt;
    string dictionaryString;
    ifstream jumble_Txt;
    string jumbleString;
    int t = 0;

    dictionary_Txt.open("dictionary.txt");
    jumble_Txt.open("jumble.txt");

    if(dictionary_Txt.fail())
        cout << "Error: could not open file." << endl;

    else if(jumble_Txt.fail())
        cout << "Error: could not open file." << endl;

    else
    {
        dictionary_Txt >> dictionarySize;
        dictionary = new string[dictionarySize];

        while(dictionary_Txt >> dictionaryString)
            dictionary[t++] = dictionaryString;

        while(jumble_Txt >> jumbleString)
        {
            permutations.clear();
            permute(permutations, jumbleString, 0);

            cout << jumbleString << " could be: ";

            for(int i = 0; i < permutations.size(); i++)
            {
                if(check(dictionary, dictionarySize, 0, dictionarySize - 1, permutations[i]))
                    cout << permutations[i] << endl;
            }
            cout << endl;
        }
    }

    return 0;
}
