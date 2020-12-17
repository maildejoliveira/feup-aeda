/*
 * ReadingClub.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "ReadingClub.h"

ReadingClub::ReadingClub() : catalogItems(BookCatalogItem("", "", 0)) {
	//do nothing!
}

ReadingClub::ReadingClub(vector<Book*> books) : catalogItems(BookCatalogItem("", "", 0)) {
	this->books = books;
}

void ReadingClub::addBook(Book* book) {
	this->books.push_back(book);
}

void ReadingClub::addBooks(vector<Book*> books) {
	this->books = books;
}

vector<Book*> ReadingClub::getBooks() const {
	return this->books;
}

BookCatalogItem ReadingClub::getCatalogItem(string title, string author) {
	BookCatalogItem itemNotFound("", "", 0);
	BSTItrIn<BookCatalogItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if (it.retrieve().getTitle() == title && it.retrieve().getAuthor() == author) {
			BookCatalogItem bci(it.retrieve().getTitle(), it.retrieve().getAuthor(), 0);
			bci.setItems(it.retrieve().getItems());
			return bci;
		}
		it.advance();
	}
	return itemNotFound;
}

void ReadingClub::addCatalogItem(Book* book) {
	BookCatalogItem itemNotFound("", "", 0);
	BookCatalogItem bci(book->getTitle(), book->getAuthor(), book->getYear());
	BookCatalogItem bciX = catalogItems.find(bci);
	if (bciX == itemNotFound) {
		bci.addItems(book);
		this->catalogItems.insert(bci);
	}
	else {
		this->catalogItems.remove(bciX);
		bciX.addItems(book);
		this->catalogItems.insert(bciX);
	}
	books.push_back(book);
}

BST<BookCatalogItem> ReadingClub::getCatalogItems() const {
	return this->catalogItems;
}

vector<UserRecord> ReadingClub::getUserRecords() const {
	vector<UserRecord> records;
	HashTabUserRecord::const_iterator it1 = this->userRecords.begin();
	HashTabUserRecord::const_iterator it2 = this->userRecords.end();
	for (; it1 != it2; it1++) {
		records.push_back(*it1);
	}
	return records;
}

void ReadingClub::setUserRecords(vector<UserRecord>& urs) {
	for (int i = 0; i < urs.size(); i++) userRecords.insert(urs[i]);
}

priority_queue<User> ReadingClub::getBestReaderCandidates() const {
	return readerCandidates;
}

void ReadingClub::setBestReaderCandidates(priority_queue<User>& candidates) {
	readerCandidates = candidates;
}



//
// TODO: Part I   - BST
//

//TODO a)
//mesmo titulo e diferente autor implica diferente item de catalogo
void ReadingClub::generateCatalog() {
	for (int i = 0; i < books.size(); i++) {
		BookCatalogItem bci(books[i]->getTitle(), books[i]->getAuthor(), books[i]->getYear());
		if (catalogItems.find(bci).getTitle() == "") {
			bci.addItems(books[i]);
			catalogItems.insert(bci);
		}
		else {
			BookCatalogItem b = catalogItems.find(bci);
			BookCatalogItem bci(b.getTitle(),b.getAuthor(), books[i]->getYear());
			bci.setItems(b.getItems());
			bci.addItems(books[i]);
			catalogItems.remove(b);
			catalogItems.insert(bci);
		}
	}


}

//TODO b)
vector<Book*> ReadingClub::getAvailableItems(Book* book) const {
	vector<Book*> temp;
	BSTItrIn<BookCatalogItem> itrIn(catalogItems);
	while (!itrIn.isAtEnd()) {
		if (itrIn.retrieve().getTitle() == book->getTitle() && itrIn.retrieve().getAuthor() == book->getAuthor()) {
			for (int i = 0; i < itrIn.retrieve().getItems().size(); i++) {
				if (itrIn.retrieve().getItems()[i]->getReader()==NULL) {
					temp.push_back(itrIn.retrieve().getItems()[i]);
				}
			}
			return temp;
		}
		itrIn.advance();
	}
	return temp;
}

//TODO c)
bool ReadingClub::borrowBookFromCatalog(Book* book, User* reader) {
	BSTItrIn<BookCatalogItem> itrIn(catalogItems);
	while (!itrIn.isAtEnd()) {
		if (itrIn.retrieve().getTitle() == book->getTitle() && itrIn.retrieve().getAuthor() == book->getAuthor()) {
			for (int i = 0; i < itrIn.retrieve().getItems().size(); i++) {
				if (itrIn.retrieve().getItems()[i]->getReader() == NULL) {
					reader->addReading(itrIn.retrieve().getItems()[i]->getTitle(), itrIn.retrieve().getItems()[i]->getAuthor());
					itrIn.retrieve().getItems()[i]->setReader(reader);
					return true;
				}
			}
		}
		itrIn.advance();
	}
	return false;
}


//
// TODO: Part II  - Hash Table
//

//TODO d)
void ReadingClub::addUserRecord(User* user) {
	userRecords.insert(UserRecord(user));
}

//TODO e)
void ReadingClub::changeUserEMail(User* user, string newEMail) {
	for (auto it = userRecords.begin(); it != userRecords.end(); it++) {
		if ((*it).getEMail() == user->getEMail()) {
			userRecords.erase(it);
			user->setEMail(newEMail);
			userRecords.insert(UserRecord(user));
			return;
		}
	}
}


//
// TODO: Part III - Priority Queue
//

//TODO f)
void ReadingClub::addBestReaderCandidates(const vector<User>& candidates, int min) {
	for (int i = 0; i < candidates.size(); i++) {
		int n = candidates[i].getReadings().size();
		if (candidates[i].getReading().first != "") n++;
		if (n >= min) {
			readerCandidates.push(candidates[i]);
		}
	}
}

//TODO g)
int ReadingClub::awardReaderChampion(User& champion) {
	if (readerCandidates.empty()) return 0;
	priority_queue<User> help = readerCandidates;
	int max = readerCandidates.top().getReadings().size();
	if (readerCandidates.top().getReading().first != "") max++;
	help.pop();
	while (!help.empty()) {
		int n = help.top().getReadings().size();
		if (help.top().getReading().first != "") n++;
		if (n == max) return 0;
		else {
			champion = readerCandidates.top();
			return readerCandidates.size();
		}
		help.pop();
	}
	return readerCandidates.size();
}























