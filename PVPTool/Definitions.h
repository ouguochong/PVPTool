#include <Windows.h>

#define NewThread(Function) CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Function, 0, 0, 0);

// Pointers & Offsets
#define CharAddy 0x0116A8E8
#define TeleOffset 0x4048
#define TeleXOffset 0x4050
#define TeleYOffset 0x4054

#define StatAddy 0x0116ABC4
#define HPOffset 0x1848

#define SettingAddy 0x0116A8DC
#define HPAlertOffset 0x98