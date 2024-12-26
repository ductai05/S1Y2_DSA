#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

struct WORD{
    string word;
    string meaning;
};

string findWord(vector<WORD> dictionary, string word, int left, int right){
    // return the meaning of the word if found, otherwise return "Word not found!"
    if (left > right) return "Word not found!";

    int mid = (left + right) / 2;
    if (dictionary[mid].word == word) return dictionary[mid].meaning;
    if (dictionary[mid].word < word) {
        return findWord(dictionary, word, mid + 1, right);
    }
    return findWord(dictionary, word, left, mid - 1);
}

int main(int argc, char* argv[]){
    // get:: wordToFind, outputFile
    vector<string> wordToFind;
    for (int i = 1; i < argc - 1; i++) wordToFind.push_back(argv[i]);
    string outputFile = (argc > 2) ? argv[argc - 1] : "output.txt";

    // get:: dictionary
    vector<WORD> dictionary;
    ifstream fin("English-Vietnamese Dictionary.txt");
    string line;
    WORD word; vector<string> wordAndMeaning; int pos;
    while(!fin.eof()){
        getline(fin, line);
        if (line == "") continue;
        pos = line.find(':');
        word.word = line.substr(0, pos);
        word.meaning = line.substr(pos + 1);
        dictionary.push_back(word);
    }

    // find word and write to output file
    freopen(outputFile.c_str(), "w", stdout);
    // cout << "Dictionary size: " << dictionary.size() << endl;
    if (wordToFind.size() == 0) wordToFind = {"sali-", "Stock appreciation", "pathfinders", "goodmorning"};
    for (const auto& word : wordToFind) {
        cout << word << ": " << findWord(dictionary, word, 0, dictionary.size() - 1) << endl;
    }
}