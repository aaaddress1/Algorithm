/***
*		巨集組合語言取代 in C++
*
*	Author: aaaddress1@gmail.com
*	Date:	2017/1/7
*
***/
#include <stdio.h>
#include <cstdlib>
#include <regex>
#include <iostream>
#define error(msg) { puts(msg); exit(-1); }

char *data;
int lenData;

void readData(const char *fileName) {
	FILE *fptr = fopen(fileName, "r");
	if (fptr == NULL) 
		error("fail to read data from file.");

	fseek(fptr, 0, SEEK_END);
	lenData = ftell(fptr);
	data = new char[lenData + 1];
	rewind(fptr);
	
	for (int buff(0),p(0);; data[p++]=buff) 
		if ((buff = fgetc(fptr)) == EOF) break;

	fclose(fptr);
}

using namespace std;
using namespace std::regex_constants;

string findNRplcMarc(int times, string funcName, string argList) {
	smatch sm, funcm;

	string fullData = string(data);
	string pattern = funcName + "([^m]*macro)(.*)([^\\x00]*)mend";

	if (!regex_search(fullData, sm, regex(pattern, icase)))
		error("fail to find the correct marco to match function name");

	string marcoDef(sm[1]), marcoArgs(sm[2]), marcoOrgArgs(sm[2]), marcoBody(sm[3]);
	string functArgs(argList);

	/* loop to deal with variable name replace */
	while (regex_search(marcoArgs, sm, regex("(&[^,]+)", icase))) {
		if (!regex_search(functArgs, funcm, regex("[^,\\)]+", icase)))
			error("fail to find the correct args to match new function args");

		marcoBody = regex_replace(marcoBody, regex(string(sm[1]).c_str()), string(funcm[0]).c_str());
		marcoArgs = sm.suffix().str();
		functArgs = funcm.suffix().str();
	}

	/* loop to deal with branch label name replace */
	string tmpBody(marcoBody);
	while (regex_search(tmpBody, sm, regex("\\$(.*):", icase))) {
		char newLabelName[256];
		sprintf(newLabelName, "%s%i", string(sm[1]).c_str(), times); 
		marcoBody = regex_replace(marcoBody, regex(("\\$" + string(sm[1])).c_str()), newLabelName);
		tmpBody = sm.suffix().str();
	}

	return "// " + funcName + marcoDef + marcoOrgArgs + " ---> " + funcName + "(" + argList + ")" + marcoBody;
}

int main() {
	readData("test.txt");

 	smatch sm;
 	if (!regex_search(string(data), sm, regex("mend([^\\x00]*)ret", icase)))
 		error("fail to capture the main code in assembly code.");

 	string mainCode = regex_replace((string)sm[1], regex("[\x20\t\r\n]"), "");
 	string output("");

 	int times(0);
	while (regex_search(mainCode, sm, regex("([^\\(]+)\\(([^\\)]*)\\)"))) {
		output += findNRplcMarc(times++, sm[1], sm[2]) + string("\n");
		mainCode = sm.suffix().str();
	}
	output += "	  RET";
	if (FILE *fp = fopen("output.txt", "w")) {
		fprintf(fp, "%s", output.c_str());
		puts("output has been saved in ./output.txt successfully!");
	}
	else 
		puts("fail to save output file.");
	return 0;
}