//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include "CayenneMQTTESP32.h" // ganti tanda " dengan > jika program error
#include "DHT.h"

#define DHTPIN 15     // what digital pin we're connected to
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// WiFi network info.
char ssid[] = "DESKTOP-5N1IDJO3463";
char wifiPassword[] = "12345678";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "f2f2f380-81b7-11ed-8d53-d7cd1025126a";
char password[] = "cc82c4918a6a4cd98073d5272de89f8424e819a6";
char clientID[] = "fdde3570-81b7-11ed-8d53-d7cd1025126a";

unsigned long lastMillis = 0;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  //  pinMode (D4, OUTPUT);
}
float h, t;
void loop() {
  Cayenne.loop();

  h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();
 

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) ) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

}

CAYENNE_OUT(1)
{
  CAYENNE_LOG("Send data for Virtual Channel %d Suhu %f C", 1, t);
  Cayenne.celsiusWrite(1, t);
}

CAYENNE_OUT(2)
{
  CAYENNE_LOG("Send data for Virtual Channel %d Hum %f ", 2, h);
  Cayenne.virtualWrite(2, h);
