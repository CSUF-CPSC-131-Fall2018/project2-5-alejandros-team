#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <stdexcept>
#include <iterator>
#include "Webpage.h"
using namespace std;


class BrowserHistory {
public:
	//def ctor
	BrowserHistory();

	void visitSite(Webpage newSite);
	string back();
	string forward();

	void readHistory(string fileName);

	string getUrl();
	size_t getNavSize();
	list<Webpage> getSitesVisited();
	string ex;//error string
	void chop();
private:
	list<Webpage> navHistory;
	list<Webpage>::iterator navPos;
	list<Webpage> sitesVisited;
	int numSites;

};

void BrowserHistory::readHistory(string fileName) {
	string temp;
	int newTime;
	Webpage newSite;
	ifstream inFile(fileName.c_str());

	while (inFile >> temp) {
		if (temp == "new") {
			inFile >> temp >> newTime;
			newSite = Webpage(temp, time_t(newTime));
			visitSite(newSite);
		}
		else if (temp == "back") {
			back();
		}
		else if (temp == "forward") {
			forward();
		}
		else {
			throw logic_error("invalid command");
		}
	}
}
BrowserHistory::BrowserHistory() {
	//defaulting list navHistory with a node of def of Webpage
	navHistory.push_front(Webpage());
	//defaulting iterator navPos with the begining of the navHistory list
	navPos = navHistory.begin();
	sitesVisited.push_front(Webpage());
	numSites = 0;

}
void BrowserHistory::visitSite(Webpage page) {
	list<Webpage>::iterator temp;
	temp = navHistory.end();
	temp--;
	

	sitesVisited.push_back(page);
	navHistory.push_back(page);
	if (navPos != temp) {
		chop();
	}
	navPos = navHistory.end();
	navPos--;
	numSites++;
}
string BrowserHistory::back() {
	//going back 1 in the browserhistory
	
	if (navPos == navHistory.begin()) {
		ex = "error";
		return ex;
	}
	navPos--;
	return navPos->getUrl();

}
string BrowserHistory::forward() {
	//going forward 1 in the navHistory
	list<Webpage>::iterator temp;
	temp = navHistory.end();
	temp--;//temp is pointing to last webpage
	if (navPos == temp) {
		
		ex = "error";
		return ex;
	}
	return navPos->getUrl();
	navPos++;
	
}
string BrowserHistory::getUrl() {
	//return url from webpage iterator pointer
	if (navPos != navHistory.end()) {
		return navPos->getUrl();
	}
	ex = "error";
	return ex;
}
size_t BrowserHistory::getNavSize() {
	return navHistory.size();
	//return numSites;
}
list<Webpage> BrowserHistory::getSitesVisited() {
	/*list<Webpage>::iterator temp;
	temp = navPos;
	for (temp = sitesVisited.begin(); temp != sitesVisited.end(); temp++) {
		cout << temp->getUrl();
	}*/
	return sitesVisited;
}

void BrowserHistory::chop() {
	list<Webpage>::iterator temp;
	temp = navPos;
	navHistory.erase(++temp, navHistory.end());

}
