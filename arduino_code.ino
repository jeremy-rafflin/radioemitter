/*
 * Configuration des pin actuel : 
 * Pin 2 => interruption 0 => radio receptor
 * Pin 7 => capteur de temperature
 * Pin 10 => Emetteur radio
 * 
 */
#include <ArduinoJson.h>

/* Code exemple : (the % is for the end of the commande). Put thats code into the serial to test
 * {"fonction_name":"SendRadioCode","code":"16129807"}%
 * {"fonction_name":"GetHumidityAndTeperature"}%
 */


//////////////////////////////////////// Partie pour le capteur de température ///////////////////////////////////////
#include <DHT.h>

#define DHTPIN 7     // what pin we're connected to
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

// Fonction permettant de récupérer la temmperature et l'humidité 
void GetHumidityAndTeperature() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& humidity_and_temp = jsonBuffer.createObject();
  
  humidity_and_temp["action"] = "received";
  humidity_and_temp["temperature"] = temperature;
  humidity_and_temp["humidity"] = humidity;
  humidity_and_temp.printTo(Serial);
}

//////////////////////////////////////// Partie pour le capteur radio ///////////////////////////////////////
#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

//////////////////////////////////////// Partie pour le l'émetteur radio /////////////////////////////////////
void SendRadioCode(long code) {
   mySwitch.send(code, 24);
}

//////////////////////////////////////// Partie permettant de récupérer les commandes envoyé a l'arduino via le port série ///////////////////////////////////////
// permet stocker les caractères transmis par la liaison serie
String commande = "";
// caractère indiquant la fin d'une commande
char endMarker = '%';

/*
 * Switch permettant d'exécuter les commandes envoyé par la voie serie par exemple
 */
void executeFunction(String json_data) {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& v = jsonBuffer.parseObject(json_data);
  //on décompose la chaine de cartère
  if ( v["fonction_name"] == String("GetHumidityAndTeperature") ) {
    GetHumidityAndTeperature();
  } else if ( v["fonction_name"] == String("SendRadioCode") ) {
    SendRadioCode(v["code"]);
  }
}

/**
 * Fonction appelé automatiqueemnt dans la boucle principal lorsqu'il y a des données dans le buffer serial
 */
void serialEvent() {
    //lit toutes les données (vide le buffer de réception)
    char last_readed_char = Serial.read();
    if ( last_readed_char == endMarker ) {
      executeFunction(commande);
      commande = "";
    } else {
      commande += last_readed_char;
    }
}


//////////////////////////////////////// initialisation des divers choses ///////////////////////////////////////
void setup() {
   // Open serial communications and wait for port to open: 
   // port usb sur le rp : /dev/ttyUSB0
  Serial.begin(9600);
  dht.begin();
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2 (pour les signaux radio)

// Configuration de l'emition radio
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);
  // Optional set pulse length.
  mySwitch.setPulseLength(310);
  // Optional set protocol (default is 1, will work for most outlets)
  mySwitch.setProtocol(1);
  // Optional set number of transmission repetitions.
  mySwitch.setRepeatTransmit(15);
// fin Configuration de l'emition radio

  delay(1000);
}


// Boucle principal ou l'on execute les actions
void loop() {
  //////////////////////////////////////// Partie pour le capteur radio ///////////////////////////////////////
  if (mySwitch.available()) {
    int value = mySwitch.getReceivedValue();
    
    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {
      // One nvoie le code recu a gladys avec l'action recived
      Serial.print("{\"action\":\"received\",\"value\":");
      Serial.print( mySwitch.getReceivedValue() );
      Serial.println("}");
    }
    delay(200); 
    mySwitch.resetAvailable();
  }
  //////////////////////////////////////// Fin Partie pour le capteur radio ///////////////////////////////////////
}