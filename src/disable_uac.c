#include <windows.h>
#include <stdio.h>

int main() {
    HKEY hKey;
    LONG lResult;
    DWORD dwValue = 0;
    const char* regPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";

    // Check if the program has permission to edit the registry
    lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
                           regPath, 
                           0, 
                           KEY_WRITE, 
                           &hKey);

    if (lResult == ERROR_ACCESS_DENIED) {
        printf("Permission denied. Please run the program as an administrator.\n");
        return 1;
    } else if (lResult != ERROR_SUCCESS) {
        printf("Error opening registry key: %ld\n", lResult);
        return 1;
    }

    // Set the value to disable UAC
    lResult = RegSetValueEx(hKey, 
                            "EnableLUA", 
                            0, 
                            REG_DWORD, 
                            (const BYTE*)&dwValue, 
                            sizeof(dwValue));

    if (lResult != ERROR_SUCCESS) {
        printf("Error setting registry value: %ld\n", lResult);
        RegCloseKey(hKey);
        return 1;
    }

    // Close the registry key
    RegCloseKey(hKey);

    printf("UAC has been disabled. Please restart your computer for the changes to take effect.\n");

    return 0;
}