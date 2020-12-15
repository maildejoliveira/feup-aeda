#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"
#include "bst.h"
#include <algorithm>

using namespace std;

BST<WordMeaning> Dictionary::getWords() const {
    return words;
}

//TODO a)
bool WordMeaning::operator < (const WordMeaning &wm1) const {
    return this->word<wm1.word;
}

//TODO a)
void Dictionary::readDictionary(ifstream &f)
{
    string word;
    string meaning;
    vector <WordMeaning> wor;
    while(!f.eof()){
        getline(f,word);
        getline(f,meaning);
        WordMeaning w(word,meaning);
        words.insert(w);
    }
}

//TODO
string Dictionary::searchFor(string word) const
{
    BSTItrIn<WordMeaning> it(words);
    while(!it.isAtEnd()){
        if(it.retrieve().getWord()==word){
            return it.retrieve().getMeaning();
        }
        it.advance();
    }
    throw(WordInexistent(words, word));
}

//TODO
bool Dictionary::correct(string word, string newMeaning)
{
    try{
        searchFor(word);
    }
    catch (WordInexistent &e) {
       WordMeaning w(word,newMeaning);
       words.insert(w);
       return false;
    }
    string meaning;
    BSTItrIn<WordMeaning> it(words);
    while(!it.isAtEnd()){
        if(it.retrieve().getWord()==word){
            meaning =  it.retrieve().getMeaning();
        }
        it.advance();
    }
    WordMeaning wToRem(word,meaning);
    words.remove(wToRem);
    WordMeaning w(word,newMeaning);
    words.insert(w);
    return true;
}

//TODO b)
void Dictionary::print() const
{
    BSTItrIn<WordMeaning> it(words);
    while(!it.isAtEnd()){
        cout << it.retrieve().getWord() << '\n';
        cout << it.retrieve().getMeaning() << '\n';
        it.advance();
    }
}

