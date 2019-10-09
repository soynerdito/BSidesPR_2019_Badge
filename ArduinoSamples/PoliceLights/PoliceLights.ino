// English for which LED to Strobe
#define RED 0x0
#define BLUE 0x1
 
// Variable to track which LED is on
byte whichLED = RED;
 
// Where are the LEDs connected?
int LED_Red = 0;
int LED_Blue = 2;
 
// State variables for the LEDs
byte Red_State = LOW;
byte Blue_State = LOW;
 
// Some delay values to change flashing behavior
unsigned long switchDelay = 250;
unsigned long strobeDelay = 50;
 
// Seed the initial wait for the strobe effect
unsigned long strobeWait = strobeDelay;
 
// Variable to see when we should swtich LEDs
unsigned long waitUntilSwitch = switchDelay;  // seed initial wait

void setup() {
   pinMode(LED_Red, OUTPUT);
   pinMode(LED_Blue, OUTPUT);
   pinMode(LED_Red+1, OUTPUT);
   pinMode(LED_Blue+1, OUTPUT);

}
unsigned count = 0;
void loop() {
    count++;
    if( count > 50000 ){
      if( LED_Red > 0 ){
        LED_Red = 0;
        LED_Blue = 2;
      }else{
        LED_Red = 1;
        LED_Blue = 3;  
      }
      
      count = 0;
      digitalWrite(0, 0);
      digitalWrite(1, 0);
      digitalWrite(2, 0);
      digitalWrite(3, 0);
    }
    digitalWrite(LED_Red, Red_State);     // each iteration of loop() will set the IO pins,
    digitalWrite(LED_Blue, Blue_State);    // even if they don't change, that's okay

    
 
    // Toggle back and forth between the two LEDs
    if ((long)(millis() - waitUntilSwitch)>=0) {
        // time is up!
        Red_State = LOW;
        Blue_State = LOW;
        whichLED = !whichLED;  // toggle LED to strobe
        waitUntilSwitch += switchDelay;
    }
 
    // Create the stobing effect
    if ((long)(millis() - strobeWait)>=0) {
        if (whichLED == RED)
            Red_State = !Red_State;
        if (whichLED == BLUE)
            Blue_State = !Blue_State;
        strobeWait += strobeDelay;
    }
}
