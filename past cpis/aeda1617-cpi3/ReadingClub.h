/*
 * ReadingClub.h
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#ifndef SRC_READINGCLUB_H_
#define SRC_READINGCLUB_H_

#include "Book.h"
#include "User.h"
#include "BST.h"
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

struct userRecordHash
{
	int operator() (const UserRecord& ur) const
	{
		int v = 0;
		for (int i = 0; i < ur.getName().size(); i++) {
			v = 37 * v + ur.getName()[i];
		}
		return v;
	}

	bool operator() (const UserRecord& ur1, const UserRecord& ur2) const
	{
		return ur1.getEMail()==ur2.getEMail();
	}
};

typedef tr1::unordered_set<UserRecord, userRecordHash, userRecordHash> HashTabUserRecord;

class ReadingClub {
	vector<Book*> books; //todos os livros existentes msm q sejam o msm livro mas de diferentes pessoas/edi�oes
	BST<BookCatalogItem> catalogItems; //todos os livros msm q existem embora possam haver mais exemplares deles
	HashTabUserRecord userRecords; //todos os users da plataforma
	priority_queue<User> readerCandidates; //classifica leitores e da premios mediante posi��o
public:
	ReadingClub();
	ReadingClub(vector<Book*> books);
	void addBook(Book* book);
	void addBooks(vector<Book*> books);
	vector<Book*> getBooks() const;

	// Part I   - BST
	BookCatalogItem getCatalogItem(string title, string author);
	void addCatalogItem(Book* book);
	BST<BookCatalogItem> getCatalogItems() const;
	// Part II  - Hash Table
	vector<UserRecord> getUserRecords() const;
	void setUserRecords(vector<UserRecord>& urs);
	// Part III - Piority Queue
	priority_queue<User> getBestReaderCandidates() const;
	void setBestReaderCandidates(priority_queue<User>& candidates);

	// TODO: Implement methods below...
	// Part I   - BST
	/* A */ void generateCatalog();
	/* B */ vector<Book*> getAvailableItems(Book* book) const;
	/* C */ bool borrowBookFromCatalog(Book* book, User* reader);

	// Part II  - Hash Table
	/* D */ void addUserRecord(User* user);
	/* E */ void changeUserEMail(User* user, string newEMail);

	// Part III - Piority Queue
	/* F */ void addBestReaderCandidates(const vector<User>& candidates, int min);
	/* G */ int awardReaderChampion(User& champion);
};




#endif /* SRC_READINGCLUB_H_ */
