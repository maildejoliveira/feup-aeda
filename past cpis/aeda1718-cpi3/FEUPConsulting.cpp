/*
 * FEUPConsulting.cpp
 *
 *  Created on: 10/12/2017
 *      Author: CS
 */

#include "FEUPConsulting.h"

FEUPConsulting::FEUPConsulting() : expertizes(Expertize("", 0)) {
}

FEUPConsulting::FEUPConsulting(vector<Project*> projects) : expertizes(Expertize("", 0)) {
	this->projects = projects;
}

void FEUPConsulting::addProjects(vector<Project*> projects) {
	this->projects = projects;
}

vector<Project*> FEUPConsulting::getProjects() const {
	return this->projects;
}


// get the expertize objet with the given name, including all students with the corresponding skills
Expertize FEUPConsulting::getExpertize(string name, unsigned cost) {
	Expertize itemNotFound("", 0);
	Expertize expertize(name, cost);
	Expertize search = expertizes.find(expertize);

	return search;
}


void FEUPConsulting::addProject(Project* project) {
	//TODO
	Expertize itemNotFound("", 0);
	Expertize expertize(project->getExpertize(), project->getCost());
	Expertize search = expertizes.find(expertize);

	if (search == itemNotFound) {
		this->expertizes.insert(expertize);
	}

	projects.push_back(project);
}

BST<Expertize> FEUPConsulting::getExpertizes() const {
	return this->expertizes;
}

void FEUPConsulting::addNewExpertize(const Expertize& expertize1) {
	this->expertizes.insert(expertize1);
}

vector<StudentPtr> FEUPConsulting::getStudents() const {
	vector<StudentPtr> ptrs;
	HashTabStudentPtr::const_iterator it1 = this->students.begin();
	HashTabStudentPtr::const_iterator it2 = this->students.end();
	for (; it1 != it2; it1++) {
		ptrs.push_back(*it1); //We can make it a bit more complex by considering only records with a condition!
	}
	return ptrs;
}

void FEUPConsulting::setStudents(vector<StudentPtr>& newStudents) {
	for (int i = 0; i < newStudents.size(); i++) students.insert(newStudents[i]);
}

priority_queue<Student> FEUPConsulting::getActiveStudents() const {
	return activeStudents;
}
void FEUPConsulting::setActiveStudents(priority_queue<Student>& students) {
	activeStudents = students;
}


//
// TODO: Part I   - BST
//

//TODO a) adds student to vector of students available of expertize with name expertize and cost cost
void FEUPConsulting::addAvailability(Student* student, string expertizeAvailable, unsigned cost) {
	BSTItrIn<Expertize> itrIn(expertizes);
	while (!itrIn.isAtEnd()) {
		if (itrIn.retrieve().getName() == expertizeAvailable && itrIn.retrieve().getCost() == cost) {
			itrIn.retrieve().addConsultant(student);
			return;
		}
		itrIn.advance();
	}
	Expertize exp(expertizeAvailable, cost);
	exp.addConsultant(student);
	expertizes.insert(exp);
}

 //TODO b) returns all students availables for the project with expertize and cost if hasn't any currentProject
vector<Student*> FEUPConsulting::getCandidateStudents(Project* project) const {
	vector<Student*> temp;
	BSTItrIn<Expertize> itrIn(expertizes);
	while (!itrIn.isAtEnd()) {
		if (itrIn.retrieve().getName() == project->getExpertize() && itrIn.retrieve().getCost() == project->getCost()) {
			for (int i = 0; i < itrIn.retrieve().getConsultants().size(); i++) {
				if (itrIn.retrieve().getConsultants()[i]->getCurrentProject() == "") {
					temp.push_back(itrIn.retrieve().getConsultants()[i]);
				}
			}
		}
		itrIn.advance();
	}
	return temp;

}

//TODO c) 
bool FEUPConsulting::assignProjectToStudent(Project* project, Student* student) {
	if (project->getConsultant() != NULL) {
		return false;
	}
	vector<Student*> v = getCandidateStudents(project);
	if (find(v.begin(), v.end(), student)!=v.end()) {
		student->addProject(project->getTitle());
		project->setConsultant(student);
		return true;
	}
	return false;

}

//
// TODO: Part II  - Hash Table
//

//TODO d)
void FEUPConsulting::addStudent(Student* student) {
	students.insert(StudentPtr(student));
}

//TODO e)
void FEUPConsulting::changeStudentEMail(Student* student, string newEMail) {
	for (auto it = students.begin(); it != students.end(); it++) {
		if ((*it).getEMail() == student->getEMail()) {
			students.erase(it);
			StudentPtr s(student);
			s.setEMail(newEMail);
			students.insert(s);
			return;
		}
	}
}


//
// TODO: Part III - Priority Queue
//

//TODO f)
void FEUPConsulting::addActiveStudents(const vector<Student>& candidates, int min) {
	for (int i = 0; i < candidates.size(); i++) {
		if (candidates[i].getPastProjects().size() >= min) {
			activeStudents.push(candidates[i]);
		}
	}
}

//TODO g)
int FEUPConsulting::mostActiveStudent(Student& studentMaximus) {
	if (activeStudents.size() == 0) return 0;
	Student s(activeStudents.top());
	priority_queue<Student> help = activeStudents;
	help.pop();
	while (!help.empty()) {
		if (s.getPastProjects().size() == help.top().getPastProjects().size()) {
			return 0;
		}	
		help.pop();
	}
	studentMaximus = s;
	return activeStudents.size();

}
