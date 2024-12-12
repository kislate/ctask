#include <REGX52.H>

// ????
void Delay(unsigned int xms) //@11.0592MHz
{
    unsigned char i, j;
    while (xms)
    {
        i = 2;
        j = 199;
        do
        {
            while (--j);
        } while (--i);
        xms--;
    }
}

// ?????????
unsigned char KeyScan()
{
    if (P3_0 == 0) {  // ??1
        Delay(20);
        if (P3_0 == 0) {
            while (P3_0 == 0);  // ??????
            return 1;
        }
    }
    if (P3_1 == 0) {  // ??2
        Delay(20);
        if (P3_1 == 0) {
            while (P3_1 == 0);  // ??????
            return 2;
        }
    }
    return 0;
}

// ????
unsigned char mode = 0;  // ?????
bit paused = 0;          // ????

void UpdateLights() {
    switch (mode)
    {
        case 0: // ????
            P2 = 0xFE; Delay(500);KeyScan();
            P2 = 0xFD; Delay(500);KeyScan();
            P2 = 0xFB; Delay(500);KeyScan();
            P2 = 0xF7; Delay(500);KeyScan();
            P2 = 0xEF; Delay(500);KeyScan();
            P2 = 0xDF; Delay(500);KeyScan();
            P2 = 0xBF; Delay(500);KeyScan();
            P2 = 0x7F; Delay(500);KeyScan();
            break;

        case 1: // ????
            P2 = 0x7F; Delay(500);KeyScan();
            P2 = 0xBF; Delay(500);KeyScan();
            P2 = 0xDF; Delay(500);KeyScan();
            P2 = 0xEF; Delay(500);KeyScan();
            P2 = 0xF7; Delay(500);KeyScan();
            P2 = 0xFB; Delay(500);KeyScan();
            P2 = 0xFD; Delay(500);KeyScan();
            P2 = 0xFE; Delay(500);KeyScan();
            break;

        case 2: // ?????
            P2 = 0xFE; Delay(500);KeyScan();
            P2 = 0xFD; Delay(500);KeyScan();
            P2 = 0xFB; Delay(500);KeyScan();
            P2 = 0xF7; Delay(500);KeyScan();
            P2 = 0xEF; Delay(500);KeyScan();
            P2 = 0xDF; Delay(500);KeyScan();
            P2 = 0xBF; Delay(500);KeyScan();
            P2 = 0x7F; Delay(500);KeyScan();
            P2 = 0xFF; Delay(500);KeyScan();
            break;
    }
}

void main()
{
    unsigned char key;
    
    while (1)
    {
        key = KeyScan(); // ????

        // ????
        if (key == 1) // ??1:????
        {
            mode++;
            if (mode > 2) mode = 0; // ???3???
        }
        if (key == 2) // ??2:??/??
        {
            paused = !paused;
        }

        // ?????,??????
        if (!paused)
        {
            UpdateLights(); // ???????
        }
        else
        {
            Delay(50); // ??????????
        }
    }
}
