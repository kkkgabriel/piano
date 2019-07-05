// variables for ports and pins
int piezo = 13;
int water1 = A5;
int water2 = A4;
int water3 = A3;
int light1 = A2;
int light2 = A1;
int light3 = A0;
int crash1 = 0;
int crash2 = 12;

// variables to store sensor values
int lightValue1;
int lightValue2;
int lightValue3;
int waterValue1;
int waterValue2;
int waterValue3;
int crashValue1;
int crashValue2;

//variables to store limit values
int waterCeiling = 700;
int lightFloor = 1504;

// setup code
void setup() {
  // initialize serial monitor
  Serial.begin(9600);

  // set all sensor pins to input
  pinMode(light1, INPUT);
  pinMode(light2, INPUT);
  pinMode(light3, INPUT);
  pinMode(water1, INPUT);
  pinMode(water2, INPUT);
  pinMode(water3, INPUT);
  pinMode(crash1, INPUT_PULLUP);
  pinMode(crash2, INPUT_PULLUP);

  // set piezo pin as output
  pinMode(piezo, OUTPUT);
  
}

// piano function to take in key number and play the respective note
void piano(int key){
  if ( key == 0 ){
    tone(piezo, 261.63 ,500 ); // C4
    Serial.println("C4");
  } else if ( key == 1 ){
    tone(piezo, 293.66 ,500 ); // D4
    Serial.println("D4");
  } else if ( key == 2 ){
    tone(piezo, 329.63 ,500 ); // E4
    Serial.println("E4");
  } else if ( key == 3 ){
    tone(piezo, 349.23 ,500 ); // F4
    Serial.println("F4");
  } else if ( key == 4 ){
    tone(piezo, 392 ,500 ); //G4
    Serial.println("G4");
  } else if ( key == 5 ){
    tone(piezo, 440 ,500 ); // A5
    Serial.println("A5");
  } else if ( key == 6 ){
    tone(piezo, 493.88 ,500 ); // B5
    Serial.println("B5");
  } else if ( key == 7 ){
    tone(piezo, 523.55 ,500 ); // C5
    Serial.println("C5");
  } else {
    Serial.println("Key does not exist");
  }
}

// main code to run repeatedly
void loop() {
//  Serial.println(analogRead(light3));
  // store sensor values in respective variables
  lightValue1 = analogRead(light1);
  lightValue2 = analogRead(light2);
  lightValue3 = analogRead(light3);
  waterValue1 = analogRead(water1);
  waterValue2 = analogRead(water2);
  waterValue3 = analogRead(water3);
  crashValue1 = not digitalRead(crash1); 
  crashValue2 = not digitalRead(crash2);
  // by default, crash sensors output "1" when not triggered, and "0" when triggered. 
  // Thus, these values have to be inverted with the "not" unary operator.

  // if any of the sensors are triggered, the respective notes will play using the piano() function
  if ( crashValue1 ) {
    piano(0);
    Serial.println("crash Sensor 1 activated");
  } else if ( lightValue1 < lightFloor ) {
    piano(4);
    Serial.println( "Light sensor 1 activated" );
  } else if ( lightValue2 < lightFloor ) {
    piano(5);
    Serial.println( "Light sensor 2 activated" );
  } else if ( lightValue3 < lightFloor ) {
    piano(6);
    Serial.println( "Light sensor 3 activated" );
  } else if ( waterValue1 > waterCeiling ) {
    piano(1);
    Serial.println( "Water sensor 1 activated" );
  } else if ( waterValue2 > waterCeiling ) {
    piano(2);
    Serial.println( "Water sensor 2 activated" );
  } else if ( waterValue3 > waterCeiling ) {
    piano(3);
    Serial.println( "Water sensor 3 activated" );
  } else if ( crashValue2 ) {
    piano(7);
    Serial.println( "crash sensor 2 activated"   );
  }
}
