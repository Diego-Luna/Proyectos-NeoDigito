// -> NeoDigito
#include <NeoDigito.h>

#define PIN 12        // Pin where the display will be attached
#define DIGITS 4      // Number of NeoDigitos connected
#define PIXPERSEG 2   // NeoPixels per segment

// Specified the number of displays and the number of neopixels per segment, some arguments of the neopixel strip used must be added.
NeoDigito display1 = NeoDigito(DIGITS, PIXPERSEG, PIN, NEO_GRB + NEO_KHZ800); // For more info abaut the last argumets check Adafruit_Neopixel documentation.

int R = 0;
int G = 0;
int B = 0;

// -> DHT22
#include "DHT.h"
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

const int DHTPin = 5;     // what digital pin we're connected to

DHT dht(DHTPin, DHTTYPE);

String integerValue = "";
String floatValue = "";

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  dht.begin();

  // -> NeoDigito
  display1.begin();             // This fuction calls Adafruit_NeoPixel.begin() to configure.
}

void loop() {
  // -> DHT22
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // -> NeoDigito
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");

  PreparingValues(t);
  adjustColor(t);

  display1.setPixelColor(R, G, B); // Color specified by a 32bit hex, or 8bit numbers (red, green, blue), Also colors names, red, white, yellow, etc.

  display1.print(integerValue);
  display1.print(floatValue);
  display1.show();
}

void PreparingValues(float t) {


  int val_1 = int(t);
  float val_2 = t - float(val_1);
  float val_2_firts = 0.00;
  String val_2_string = "";

  if ( val_1 >= 10 ) {
    if (val_1 >= 10 && val_1 < 20) val_2_firts = 1.00;
    if (val_1 >= 20 && val_1 < 30) val_2_firts = 2.00;
    if (val_1 >= 30 && val_1 < 40) val_2_firts = 3.00;
    if (val_1 >= 40 && val_1 < 50) val_2_firts = 4.00;
    if (val_1 >= 50 && val_1 < 60) val_2_firts = 5.00;

    integerValue = String(val_1);
    floatValue =  String(val_2 + val_2_firts);

  } else if (val_1 <= -1) {
    int index = 1;
    int index_limite = 1;
    if (val_1 <= -1 && val_1 > -10) val_2_string = "-";
    if (val_1 <= -10 && val_1 > -20) val_2_string = "-1"; index = 2; index_limite = 2;
    if (val_1 <= -20 && val_1 > -30) val_2_string = "-2"; index = 2; index_limite = 2;
    if (val_1 <= -30 && val_1 > -40) val_2_string = "-3"; index = 2; index_limite = 2;

    integerValue = String(val_1);
    //floatValue = "-" + val_2_string;
    floatValue = val_2_string + String(val_2);

    floatValue.remove(index, index_limite);
  } else {
    val_2_firts = .00;
    integerValue = " " + String(val_1);
    floatValue =  String(val_2 + val_2_firts);
  }

}

void adjustColor(float t) {

  if (t > 10.00) {
    int redIntensity = map(t, 10, 50, 10, 255);

    R = redIntensity ;
    B = 0;

  } else {
    int blueIntensity = map(t, -40, 10, 10, 255);

    B = blueIntensity;
    R = 0;
  }

  Serial.print(" ->  Rojo : ");
  Serial.println(R);

  Serial.print(" ->  Blue : ");
  Serial.println(B);

  Serial.print(" ->  Green : ");
  Serial.println(G);

}
