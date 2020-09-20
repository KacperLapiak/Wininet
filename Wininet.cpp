#pragma comment ( lib, "Wininet.lib" )
#include <iostream>
#include <fstream>
#include <windows.h>
#include <wininet.h>

using namespace std;

int main()
{
    fstream hFile("file.txt", ios_base::out | ios_base::in | ios_base::trunc);

    HINTERNET hInternet = InternetOpenA("InetURL/1.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    HINTERNET hConnection = InternetConnectA(hInternet, "reddit.com", 80, " ", " ", INTERNET_SERVICE_HTTP, 0, 0);
    HINTERNET hData = HttpOpenRequestA(hConnection, "GET", "/", NULL, NULL, NULL, INTERNET_FLAG_KEEP_CONNECTION, 0);

    char buf[1024];
    HttpSendRequestA(hData, NULL, 0, NULL, 0);

    while (1)
    {
        DWORD bytesRead = 0;
        while (InternetReadFile(hData, buf, 1023, &bytesRead) && bytesRead != 0)
        {
            buf[bytesRead] = 0; // insert the null terminator.
            hFile << noskipws << buf;
            cout << "Bytes read: " << bytesRead << endl;
        }

        Sleep(60000);
    }

    InternetCloseHandle(hData);
    InternetCloseHandle(hConnection);
    InternetCloseHandle(hInternet);
}