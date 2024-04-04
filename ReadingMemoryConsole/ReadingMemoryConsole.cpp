// ReadingMemoryConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

using namespace std;

#include <iostream>
#include <Windows.h>

using namespace std;

int main() {
    int intRead = 0;

    DWORD processId = 13556;
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

    if (hProcess == NULL) {
        DWORD errorCode = GetLastError();
        cerr << "Erreur lors de l'ouverture du processus. Code d'erreur : " << errorCode << endl;
        return errorCode;
    }

    // Adresse m�moire de la variable varInt dans le programme
    LPVOID addressVarInt = (LPVOID)0x0000000BA516F3F4;

    // Lecture de la m�moire du processus pour obtenir la valeur de varInt
    if (!ReadProcessMemory(hProcess, addressVarInt, &intRead, sizeof(int), NULL)) {
        DWORD errorCode = GetLastError();
        cerr << "Erreur lors de la lecture de la m�moire du processus. Code d'erreur : " << errorCode << endl;
        CloseHandle(hProcess);
        return errorCode;
    }

    // Affichage de la valeur lue
    cout << "Valeur lue avant : " << intRead << endl;

    // Ajout de 1 � la valeur lue
    intRead += 1;

    // R��criture de la nouvelle valeur dans la m�moire du processus
    if (!WriteProcessMemory(hProcess, addressVarInt, &intRead, sizeof(int), NULL)) {
        DWORD errorCode = GetLastError();
        cerr << "Erreur lors de l'�criture dans la m�moire du processus. Code d'erreur : " << errorCode << endl;
        CloseHandle(hProcess);
        return errorCode;
    }

    // Affichage de la nouvelle valeur apr�s l'avoir �crite
    cout << "Nouvelle valeur �crite : " << intRead << endl;

    // Fermeture du handle du processus
    CloseHandle(hProcess);

    // Attendre que l'utilisateur appuie sur Entr�e pour quitter
    cout << "Appuyez sur ENTREE pour quitter." << endl;
    getchar();

    return 0;
}