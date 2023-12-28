//code made and tested by sempiternalsykes

#include <Servo.h>

//declaring all variables

int posS1 = 90; //variable to store the servo position
int posS1i = 90; //servo initial position
int incomingByte = 0; //for incoming serial data
int currentPosS1; //current position of servo

int buttonPin = 5; //button pin is attached to pin 5
int servoPin = 9; //servo motor attached to pin 9
int ledPin = 10; //output for results
int lightPin = 0; //raw input data

float raw = 0;
float avg = 0;
float sum = 0;
float absorbance;

int buttonState = 0;
int blank = 0;
int sample = 0;

Servo servol; //to create servo object to control the servo (max: 8 servo objects)

void setup (){

    Serial.begin(9600);
    Serial.println("Spectrophotometer starting");

    servol.attach(servoPin); //attaches the servo on pin 9 to the corresponding servo objects
    servol.write(posS1i); //set the servo position to 0 degrees

    pinMode(buttonPin, INPUT_PULLUP); //controls the reading
    pinMode(ledPin, OUTPUT);

    /* codes on the keyboard that controls the prism (servo)
    == servo ==
    r = 114 (RED)
    o = 111 (ORANGE)
    y = 121 (YELLOW)
    g = 103 (GREEN)
    b = 98 (BLUE)
    p = 112 (PURPLE)
    s = 115 (RESET SERVO)*/
}

void loop (){

    if(Serial.available() > 0){
        incomingByte = Serial.read();
        //switch case to control the servo
        switch(incomingByte){

            case 114:
            if(posS1 > 180){
                posS1 = 172;
            }
            posS1 -= 37;
            servol.write(posS1);
            currentPosS1 = servol.read();
            Serial.println("Wavelength color: RED ");
            break;

            case 111:
            if(posS1 > 180){
                posS1 = 174;
            }
            posS1 -= 35;
            servol.write(posS1);
            currentPosS1 = servol.read();
            Serial.println("Wavelength color: ORANGE ");
            break;

            case 121:
            if(posS1 > 180){
                posS1 = 172;
            }
            posS1 -= 32;
            servol.write(posS1);
            currentPosS1 = servol.read();
            Serial.println("Wavelength color: YELLOW ");
            break;

            case 103:
            if(posS1 > 180){
                posS1 = 175;
            }
            posS1 -= 31;
            servol.write(posS1);
            currentPosS1 = servol.read();
            Serial.println("Wavelength color: GREEN ");
            break;

            case 98:
            if(posS1 > 180){
                posS1 = 170;
            }
            posS1 -= 29;
            servol.write(posS1);
            currentPosS1 = servol.read();
            Serial.println("Wavelength color: BLUE ");
            break;

            case 112:
            if(posS1 > 180){
                posS1 = 182;
            }
            posS1 -= 26;
            servol.write(posS1);
            currentPosS1 = servol.read();
            Serial.println("Wavelength color: PURPLE ");
            break;

            case 114:
            Serial.println("Reset prism to default position");
            servol.write(posS1i);
            posS1 = 90;
            break;

            default:
            incomingByte = 0;
        }
        incomingByte = 0;

        //to get transmittance of blank
        Serial.println("Press button to get transmittance of BLANK");
        while(digitalRead(buttonPin) == HIGH) {
            //wait until button is pressed
            delay(50);
        }
        digitalWrite(ledPin, HIGH);
        //get 5 readings
        sum = 0;
        for(int i = 0; i <= 4; i++){
            raw = analogRead(lightPin);
            sum = sum + raw:
            delay(250);
        }
        //get avg of 5 readings
        blank = sum/5;
        Serial.print("Transmittance of blank: ");
        Serial.println(blank);
        digitalWrite(ledPin, LOW);

        //to get transmittance of sample
        Serial.println("Press button to get transmittance of SAMPLE");
        while(digitalRead(buttonPin) == HIGH) {
            //wait until button is pressed
            delay(50);
        }
        digitalWrite(ledPin, HIGH);
        //get 5 readings
        sum = 0;
        for(int i = 0; i <= 4; i++){
            raw = analogRead(lightPin);
            sum = sum + raw:
            delay(250);
        }
        //get avg of 5 readings
        sample = sum/5;
        Serial.print("Transmittance of sample: ");
        Serial.println(sample);
        digitalWrite(ledPin, LOW);
    }
}

void findAbsorbance(float x, float y){
    absorbance = 2-(log10(x/y*100));
    //print the result
    Serial.print("Absorbance = ");
    Serial.println(absorbance, 4);
}