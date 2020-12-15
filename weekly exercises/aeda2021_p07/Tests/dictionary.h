#ifndef _DIC
#define _DIC
#include <string>
#include <fstream>
#include "bst.h"


class WordMeaning {
        string word;
        string meaning;
        public:
        WordMeaning(string w, string m): word(w), meaning(m) {}
        string getWord() const { return word; }
        string getMeaning() const { return meaning; }
        void setWord(string w) {word=w; }
        void setMeaning(string m) { meaning=m; }
        bool operator < (const WordMeaning &wm1) const;
};


class Dictionary
{
    BST<WordMeaning> words;
public:
    Dictionary(): words(WordMeaning("","")){};
    BST<WordMeaning> getWords() const;
    void readDictionary(ifstream &f);
    string searchFor(string word) const;
    bool correct(string word, string newMeaning);
    void print() const;
};


//TODO
class WordInexistent
{
    string word;
    BST<WordMeaning> wordsCopy;
public:
    WordInexistent(BST<WordMeaning> words, string w): wordsCopy(words), word(w) {};
    string getWordBefore() const {
        BSTItrIn<WordMeaning> it(wordsCopy);
        string wordBef, wordAft;
        while(!it.isAtEnd()){
            wordBef = it.retrieve().getWord();
            if(wordBef<word){
                it.advance();
                wordAft = it.retrieve().getWord();
                if(word<wordAft){
                    return wordBef;
                }
            }
        }
    }
    string getMeaningBefore() const {
        BSTItrIn<WordMeaning> it(wordsCopy);
        string wordBef, wordAft, wordBefMean;
        while(!it.isAtEnd()){
            wordBef = it.retrieve().getWord();
            wordBefMean = it.retrieve().getMeaning();
            if(wordBef<word){
                it.advance();
                wordAft = it.retrieve().getWord();
                if(word<wordAft){
                    return wordBefMean;
                }
            }
        }
    }
    string getWordAfter() const {
        BSTItrIn<WordMeaning> it(wordsCopy);
        string wordBef, wordAft;
        while(!it.isAtEnd()){
            wordBef = it.retrieve().getWord();
            if(wordBef<word){
                it.advance();
                wordAft = it.retrieve().getWord();
                if(word<wordAft){
                    return wordAft;
                }
            }
        }
    }
    string getMeaningAfter() const {
        BSTItrIn<WordMeaning> it(wordsCopy);
        string wordBef, wordAft, wordAftMean;
        while(!it.isAtEnd()){
            wordBef = it.retrieve().getWord();
            if(wordBef<word){
                it.advance();
                wordAft = it.retrieve().getWord();
                wordAftMean = it.retrieve().getMeaning();
                if(word<wordAft){
                    return wordAftMean;
                }
            }
        }
    }
};

#endif