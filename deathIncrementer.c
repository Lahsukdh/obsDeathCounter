#include <windows.h>
#include <stdio.h>
#define HOTKEY_ID 1

void incDeaths(){
    FILE* fp = fopen("deaths.txt", "r+");
    if(fp == NULL){
        fp = fopen("deaths.txt", "w+");
        if(fp == NULL){
            printf("File failed to open\n");
            return;
        }
        fprintf(fp, "0");
        rewind(fp);
    }
    
    int deaths = 0;
    fscanf(fp, "%d", &deaths);
    deaths++;
    rewind(fp);
    fprintf(fp, "%d", deaths);
    fclose(fp);
}

int main() {
    //hotkey registry
    if(!RegisterHotKey(NULL, HOTKEY_ID, 0, VK_F1)){
        printf("%s", "Registry failed");
        return 1;
    }

    MSG msg;
    while(1){
        if(GetMessage(&msg, NULL, 0, 0)){
            if(msg.message == WM_HOTKEY && msg.wParam == HOTKEY_ID){
                incDeaths();
            }
        }

        //ESC to exit
        if(GetAsyncKeyState(VK_ESCAPE)){
            printf("%s", "exiting program");
            break;
        }
    }

    //unregister hotkey before ending
    UnregisterHotKey(NULL, HOTKEY_ID);
    return 0;

}
