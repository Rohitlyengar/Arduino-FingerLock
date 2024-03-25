//Copyright © 2023 Rohit Iyengar. All rights reserved.
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#define lockOutput 12

LiquidCrystal_I2C lcd(0x27, 20, 4);

#define mySerial Serial1

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
const byte numRows = 4;
const byte numCols = 4;
char keypressed;
char c[4];
char n[4];
char code[] = "1234"; //Change password here 4 Digits Only
int Pass;
int New;
int Unlock = 5000;
char keymap[numRows][numCols] =
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

byte rowPins[numRows] = { 9,8,7,6 };
byte colPins[numCols] = { 5,4,3,2 };
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

uint8_t id;
void setup()
{
    Serial.begin(9600);
    pinMode(lockOutput, OUTPUT);
    finger.begin(57600);
    lcd.backlight();
    lcd.begin(20, 4);
    lcd.print("SMART DOOR LOCK!");
    lcd.blink();
    delay(2000);
    lcd.setCursor(0, 1);
    lcd.print("INITIALIZING");
    delay(2000);
    lcd.setCursor(0, 2);
    lcd.print("INITIALIZED");
    digitalWrite(lockOutput, HIGH);
    delay(2000);
    lcd.clear();
}

void loop()
{
    Pass = 0;
    keypressed = NULL;
    getFingerprintIDez();
    keypressed = myKeypad.getKey();
    Serial.println(keypressed);

    if (keypressed == 'A') 
    {
        Pass = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("NEW USER ENROLLMENT");
        delay(2000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ENTER PASSWORD");
        getPassword();

        if (Pass == 4)
        {
            Enrolling();
            delay(2000);
            lcd.clear();
        }
        else
        {
            lcd.setCursor(0, 0);
            lcd.print("INCORRECT PASSWORD");
            delay(2000);
            lcd.clear();
        }
    }
    if (keypressed == 'B')
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SYSTEM BYPASSED!");
        lcd.blink();
        lcd.setCursor(0, 1);
        lcd.print("UNLOCKING...");
        delay(3500);
        lcd.setCursor(0, 2);
        lcd.print("UNLOCKED");
        digitalWrite(lockOutput, LOW);
        lcd.blink();
        delay(50);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("DOOR UNLOCKED");
        lcd.blink();
        delay(Unlock);
        digitalWrite(lockOutput, HIGH);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.blink();
        lcd.print("DOOR LOCKED");
        delay(2000);
    }

    if (keypressed == 'C') 
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("CHANGE PASSWORD");
        delay(1500);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ENTER CURRENT PASS");

        getPassword();
        if (Pass == 4) 
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("ENTER NEW PASSOWRD");
            lcd.setCursor(0, 1);
            for (int i = 0; i < 4; i++) 
            {
                c[i] = myKeypad.waitForKey();
                lcd.setCursor(i, 1);
                lcd.print("*");
            }
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("CONFIRM PASSWORD");
            lcd.setCursor(0, 1);
            for (int j = 0; j < 4; j++) 
            {
                n[j] = myKeypad.waitForKey();
                lcd.setCursor(j, 1);
                lcd.print("*");
            }
            for (int k = 0; k < 4; k++) 
            {
                if (c[k] == n[k]) 
                {
                    New++;
                }
            }
            if (New == 4) 
            {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("PASSWORD UPDATED!");
                for (int i = 0; i < 4; i++)
                {
                    code[i] = n[i];
                }
                delay(1500);
            }
            else 
            {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("PASSWORD MISSMATCH!");
                delay(1500);
            }
        }
        else
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("INCORRECT PASSWORD");
            delay(1500);
        }
    }

    if (keypressed == 'D')
    {
        lcd.clear();
        lcd.print("DELETE DATABASE?");
        delay(1000);
        lcd.setCursor(0, 1);
        lcd.print("PRESS 1 T0 CONTINUE");
        lcd.setCursor(0, 2);
        lcd.print("PRESS 0 T0 CANCEL");
        keypressed = myKeypad.waitForKey();
        if (keypressed == '1') 
        {
            delay(1500);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("ENTER PASSWORD");
            getPassword();
            if (Pass == 4) 
            {
                finger.emptyDatabase();
                delay(1500);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("DATABASE EMPTY!");
                delay(1500);
            }
            else 
            {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("INCORRECT PASSWORD");
                delay(2500);
                return;
            }
        }
        else 
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("ABROTED");
            delay(2500);
        }
    }

    if (keypressed == '#') 
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("CREDITS:");
        delay(2000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ROHIT IYENGAR");
        delay(500);
        lcd.setCursor(0, 1);
        lcd.print("K A AKIL BARADWAJ");
        delay(500);
        lcd.setCursor(0, 2);
        lcd.print("SURAJ PATIL");
        delay(500);
        lcd.setCursor(0, 3);
        lcd.print("VINAYAK R YADAHALLI");
        delay(2000);
        return;
    }
    if (keypressed == '*')
    {
        Pass = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("CHANGE UNLOCK TIMER");
        delay(1500);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ENTER PASSWORD");
        getPassword();
        if (Pass == 4)
        {
            keypressed = NULL;
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("ENTER LOCK DURATION");
            lcd.setCursor(0, 1);
            keypressed = myKeypad.waitForKey();
            Serial.println(keypressed);

            Unlock = (keypressed - 48) * 1000;

            delay(500);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("LOCK DURATION SET TO");
            lcd.setCursor(0, 2);
            lcd.print(keypressed);
            lcd.setCursor(4, 2);
            lcd.print("SECONDS");
            delay(1500);

        }
        else
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("INCORRECT PASSWORD");
            delay(1500);
            return;
        }
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PLACE FINGER NOW!");
    lcd.setCursor(0, 1);
    lcd.print("WAITING...");
}

void getPassword() 
{
    Pass = 0;
    New = 0;
    for (int i = 0; i < 4; i++) {
        c[i] = myKeypad.waitForKey();
        lcd.setCursor(i, 1);
        lcd.print("*");
    }
    lcd.clear();
    for (int j = 0; j < 4; j++)
    {
        if (code[j] == c[j])
            Pass++;
    }
}
void Enrolling() 
{
    keypressed = NULL;
    lcd.clear();
    lcd.print("USER ENROLLMENT");
    delay(1500);
    lcd.clear();
    lcd.setCursor(0, 0);

    lcd.print("ENTER UNIQUE USER ID");
    id = readnumber();
    if (id == 0) 
    {
        return;
    }
    while (!getFingerprintEnroll());
}

uint8_t getFingerprintEnroll() 
{

    int p = -1;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PLACE YOUR FINGER");
    delay(750);
    while (p != FINGERPRINT_OK) 
    {
        p = finger.getImage();
        switch (p) 
        {
        case FINGERPRINT_OK:
            Serial.println("Image taken");
            /**
              Success
            */
            break;
        case FINGERPRINT_NOFINGER:
            Serial.println(".");
            /** 
              Wating For Finger
            */
            break;
        case FINGERPRINT_PACKETRECIEVEERR:
            Serial.println("Communication error");
            break;
        case FINGERPRINT_IMAGEFAIL:
            Serial.println("Imaging error");
            break;
        default:
            Serial.println("Unknown error");
            break;
        }
    }

    p = finger.image2Tz(1);
    switch (p) 
    {
    case FINGERPRINT_OK:
        Serial.println("Image converted");
        /**
          Success
        */
        break;
    case FINGERPRINT_IMAGEMESS:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("FEATURES NOT FOUND");
        delay(1500);
        return p;
    case FINGERPRINT_PACKETRECIEVEERR:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("COMMS ERROR");
        delay(1500);
        return p;
    case FINGERPRINT_FEATUREFAIL:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("FEATURES NOT FOUND");
        delay(1500);
        return p;
    case FINGERPRINT_INVALIDIMAGE:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("FEATURES NOT FOUND");
        delay(1500);
        return p;
    default:
        Serial.println("Unknown error");
        return p;
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("REMOVE YOUR FINGER");
    delay(2000);
    p = 0;
    while (p != FINGERPRINT_NOFINGER) 
    {
        p = finger.getImage();
    }
    p = -1;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PLACE YOUR FINGER");
    while (p != FINGERPRINT_OK) 
    {
        p = finger.getImage();
        switch (p) 
        {
        case FINGERPRINT_OK:
            Serial.println("Image taken");
            /**
              Success
            */
            break;
        case FINGERPRINT_NOFINGER:
            Serial.print(".");
            break;
        case FINGERPRINT_PACKETRECIEVEERR:
            Serial.println("Communication error");
            break;
        case FINGERPRINT_IMAGEFAIL:
            Serial.println("Imaging error");
            break;
        default:
            Serial.println("Unknown error");
            break;
        }
    }

    p = finger.image2Tz(2);
    switch (p) 
    {
    case FINGERPRINT_OK:
        Serial.println("Image converted");
        /**
        Success
        */
        break;
    case FINGERPRINT_IMAGEMESS:
        Serial.println("Image too messy");
        return p;
    case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        return p;
    case FINGERPRINT_FEATUREFAIL:
        Serial.println("Could not find fingerprint features");
        return p;
    case FINGERPRINT_INVALIDIMAGE:
        Serial.println("Could not find fingerprint features");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("FEATURES NOT FOUND");
        delay(1500);
        return p;
    default:
        Serial.println("Unknown error");
        return p;
    }

    p = finger.createModel();
    if (p == FINGERPRINT_OK) 
    {
      /**
        Success
      */
        Serial.println("Prints matched!");
    }
    else if (p == FINGERPRINT_PACKETRECIEVEERR) 
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("COMMS ERROR");
        delay(1500);
        return p;
    }
    else if (p == FINGERPRINT_ENROLLMISMATCH) 
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("FINGERS MISMATCHED");
        delay(1500);
        return p;
    }
    else 
    {
        Serial.println("Unknown error");
        return p;
    }

    p = finger.storeModel(id);
    if (p == FINGERPRINT_OK) 
    {
        Serial.println("Stored!");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("PRINT STORED AT");
        lcd.setCursor(0, 1);
        lcd.print("ID: ");
        lcd.setCursor(5, 1);
        lcd.print(id);
        delay(3000);
    }
    else if (p == FINGERPRINT_PACKETRECIEVEERR) 
    {
        Serial.println("Communication error");
        return p;
    }
    else if (p == FINGERPRINT_BADLOCATION) 
    {
        Serial.println("Could not store in that location");
        return p;
    }
    else if (p == FINGERPRINT_FLASHERR) 
    {
        Serial.println("Error writing to flash");
        return p;
    }
    else 
    {
        Serial.println("Unknown error");
        return p;
    }
    return true;
}
uint8_t readnumber(void) 
{
    uint8_t num = 0;
    while (num == 0) 
    {
        char key = myKeypad.waitForKey();
        int num1 = key - 48;
        lcd.setCursor(0, 1);
        lcd.print(num1);
        key = myKeypad.waitForKey();
        int num2 = key - 48;
        lcd.setCursor(1, 1);
        lcd.print(num2);
        key = myKeypad.waitForKey();
        int num3 = key - 48;
        lcd.setCursor(2, 1);
        lcd.print(num3);
        delay(1000);
        num = (num1 * 100) + (num2 * 10) + num3;
        key = NO_KEY;

    }
    return num;
}

int getFingerprintIDez() 
{
    uint8_t p = finger.getImage();
    if (p != FINGERPRINT_OK) return -1;
    p = finger.image2Tz();
    if (p != FINGERPRINT_OK) return -1;
    p = finger.fingerFastSearch();
    if (p != FINGERPRINT_OK) 
    {
        lcd.clear();
        lcd.print("ACCES DENIED");
        delay(2000);
        lcd.clear();
        lcd.print("PLACE FINGER");
        return -1;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("FINGERPRINT MATCHED");
    lcd.setCursor(0, 1);
    lcd.print("ID:");
    lcd.setCursor(4, 1);
    lcd.print(finger.fingerID, DEC);
    delay(2500);

    Pass = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ENTER PASSWORD");
    getPassword();
    if (Pass == 4) 
    {
        digitalWrite(lockOutput, LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("WELCOME");
        lcd.setCursor(0, 1);
        lcd.print("USER :");

        lcd.setCursor(6, 1);
        lcd.print(finger.fingerID, DEC);
        Serial.print(Unlock);
        delay(Unlock);
        digitalWrite(lockOutput, HIGH);
    }
    else 
    {
        lcd.setCursor(0, 0);
        lcd.print("INCORRECT PASSWORD");
        delay(2000);
        lcd.clear();
        lcd.clear();
    }
    lcd.print("PLACE FINGER");
    return finger.fingerID;
}