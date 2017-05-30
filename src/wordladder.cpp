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
#include "vector.h"
#include "set.h"
#include <set>

using namespace std;


void Welcome() {
    cout << "Welcome to CS 106B Word Ladder." <<endl;
    cout << "Please give me two English words, and I will change the " << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

}

string FindNextWord(string currWord, Set<string> &dictWords, Set<string> &alreadyUsed)
{
    string newWord;
    cout << "Current word: " << currWord << endl;
    for (int i = 0; i < currWord.size(); i++) {
        newWord = currWord;
        for (char ch = 'a'; ch <= 'z'; ch++)
        {
            newWord = newWord.replace(i,1,1,ch);
            cout << newWord << endl;
            if (dictWords.contains(newWord))
                if (!alreadyUsed.contains(newWord))
                    return newWord;
        }
    }
    return "";
}



void GenerateLadder(string word1, string word2, Set<string> &dictWords) {
//    Create an empty queue of stacks.
//  	Create/add a stack containing {w1} to the queue.
//  	While the queue is not empty:
//		Dequeue the partial-ladder stack from the front of the queue.
//		For each valid English word that is a "neighbor" (differs by 1 letter)
//		of the word on top of the stack:
//			If that neighbor word has not already been used in a ladder before:
//				If the neighbor word is w2:
//					Hooray! we have found a solution.
//				Otherwise:
//					Create a copy of the current partial-ladder stack.
//					Put the neighbor word on top of the copy stack.
//					Add the copy stack to the end of the queue.

    // Create empty queue of stacks and add a stack with word1
    Queue<Stack<string> > wordLadder;
    Stack<string> baseStack;
    baseStack.add(word1);
    wordLadder.enqueue(baseStack);

    Set<string> alreadyUsed;
    string nextStr;

    while (true)
    {
        // build up a new list of items to search, or stop if empty
        if (wordLadder.size() == 0)
        {
            cout << "Nope nothing found! no ladder. fuk u "<< endl;
            break;
        }
        Stack<string> newString = wordLadder.dequeue();
        while (true)
        {
            // find the next word to use
            nextStr = FindNextWord(newString.peek(), dictWords, alreadyUsed);
            cout << endl;
            // the end of the search
            if (nextStr == word2) {
                // Ladder was found
                cout << "A ladder from " << word2 << " back to " << word1 << ": " << endl;
                cout << word2 << " ";
                while (!newString.isEmpty()) {
                    cout << newString.pop() << " ";
                }
                cout << endl << endl;
                return;
            } else if (nextStr != "") {
                // if there is another word to search with add to the end of the list
                Stack<string> addtlStack = newString;
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
    // TODO: Finish the program!
    Welcome();

    ifstream dictStream;
    string dictName = promptUserForFile(dictStream, "Dictionary file name? ", "Unable to open that file. Try again. ");

    Set<string> dictWords;
    string currWord;
    getline(dictStream, currWord);
    while (currWord != "") {
        dictWords.add(currWord);
        getline(dictStream, currWord);
    }

    while (true) {
        cout << "Word #1 (or Enter to quit): ";
        string word1;
        getline(cin,word1);

        if (word1.empty()) {
            break;
        }

        cout << "Word #2 (or Enter to quit): ";
        string word2;
        getline(cin,word2);
        if (word2.empty()) {
            break;
        } else {

            if (word1.length() != word2.length()) {
                cout << "The two words must be the same length." << endl;
                cout << endl;
                continue;
            }
            if (word1 == word2) {
                cout << "The two words must be different." << endl;
                cout << endl;
                continue;
            }

            // Check they're found in dictionary
            // DO THE PROGRAM!
            GenerateLadder(word1, word2, dictWords);
        }
    }
    cout << "Have a nice day." << endl;
    return 0;
}
