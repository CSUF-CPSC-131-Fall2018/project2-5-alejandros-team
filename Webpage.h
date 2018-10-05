#pragma once


#include <string>
using namespace std;

class Webpage {
public:
	//def ctor
	Webpage();
	Webpage(const string& webpageUrl, const time_t& timeVisited);
	string getUrl();
	time_t getTime();

private:
	string url;
	time_t time;
};
//default webpage
Webpage::Webpage() {
	url = "blank";
	time = 0;
}
//setter
Webpage::Webpage(const string& webpageurl, const time_t& timeVisited) {
	url = webpageurl;
	time = timeVisited;
}
//getter functions
string Webpage::getUrl() {
	return url;
}

time_t Webpage::getTime() {
	return time;
}
