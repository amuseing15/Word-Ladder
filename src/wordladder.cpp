// Word Ladder
// Code written by Jake Magid

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "queue.h"
#include "stack.h"
#include "lexicon.h"
using namespace std;


void Welcome() {
    cout << "Welcome to CS 106B Word Ladder." <<endl;
    cout << "Please give me two English words, and I will change the " << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

}

string FindNextWord(string currWord, Lexicon &dictLex, Lexicon &alreadyUsed)
{
    string newWord;
    //cout << "Current word: " << currWord << endl;
    for (string::size_type i = 0; i < currWord.size(); i++) {
        newWord = currWord;
        for (char ch = 'a'; ch <= 'z'; ch++) {
            newWord = newWord.replace(i,1,1,ch);
            //cout << newWord << endl;
            if (dictLex.contains(newWord))
                if (!alreadyUsed.contains(newWord))
                    return newWord;
        }
    }
    return "";
}



void GenerateLadder(string word1, string word2, Lexicon &dictLex) {

    // Create empty queue of stacks and add a stack with word1
    Queue<Stack<string> > wordLadder;
    Stack<string> baseStack;
    baseStack.add(word1);
    wordLadder.enqueue(baseStack);

    Lexicon alreadyUsed;
    string nextStr;

    while (true)
    {
        // Build up a new list of items to search or stop if empty
        if (wordLadder.size() == 0)
        {
            cout << "No word ladder found from " << word2 << " back to " << word1 << "." << endl;
            cout << endl;
            break;
        }
        Stack<string> newStack = wordLadder.dequeue();
        while (true)
        {
            // find the next word to use
            nextStr = FindNextWord(newStack.peek(), dictLex, alreadyUsed);
            // the end of the search
            if (nextStr == word2) {
                // Ladder was found
                cout << "A ladder from " << word2 << " back to " << word1 << ": " << endl;
                cout << word2 << " ";
                while (!newStack.isEmpty()) {
                    cout << newStack.pop() << " ";
                }
                cout << endl << endl;
                return;
            } else if (nextStr != "") {
                // if there is another word to search with add to the end of the list
                Stack<string> addtlStack = newStack;
                addtlStack.push(nextStr);
                wordLadder.enqueue(addtlStack);
            }
            // else if nothing left to search for stop!!
            else if (nextStr == "")
                break;
            alreadyUsed.add(nextStr);
        }
    }
}


int main() {
    Welcome();

    ifstream dictStream;
    promptUserForFile(dictStream, "Dictionary file name? ", "Unable to open that file. Try again. ");

    Lexicon dictLex(dictStream);
    cout << endl;

    while (true) {
        cout << "Word #1 (or Enter to quit): ";
        string word1;
        getline(cin,word1);
        word1 = toLowerCase(word1);

        if (word1.empty()) {
            break;
        }

        cout << "Word #2 (or Enter to quit): ";
        string word2;
        getline(cin,word2);
        word2 = toLowerCase(word2);

        if (word2.empty()) {
            break;
        } else {

            // Check they're the same length
            if (word1.length() != word2.length()) {
                cout << "The two words must be the same length." << endl;
                cout << endl;
                continue;
            }

            // Check if they're different
            if (word1 == word2) {
                cout << "The two words must be different." << endl;
                cout << endl;
                continue;
            }

            // Check they're found in dictionary
            if (!dictLex.contains(word1) || !dictLex.contains(word2)) {
                cout << "The two words must be found in the dictionary." << endl;
                cout << endl;
                continue;
            }
            // DO THE PROGRAM!
            GenerateLadder(word1, word2, dictLex);
        }
    }
    cout << "Have a nice day." << endl;
    return 0;
}
