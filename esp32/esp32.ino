#include <WiFi.h>
#include <WiFiUdp.h>

#define CONTROL_PIN 0 

// BOM MUSIC BOX
// 66668888
const char* ssid = "NAVY_FAST_5G"; 
const char* password = "12345678";
// const char* ssid = "FPT Thanh Duyen"; 
// const char* password = "27061994";
String localIp;
const char* name = "Room1";

const int UDP_PORT = 9999;
const int TCP_PORT = 12345;
WiFiServer server;
WiFiClient client;
WiFiUDP udp;

void setup() {
  
  pinMode(CONTROL_PIN, OUTPUT);
  digitalWrite(CONTROL_PIN, LOW);
  Serial.begin(115200);
  delay(1000);

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  localIp = WiFi.localIP().toString();
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(localIp);
  delay(500);


  // Start TCP server
  server.begin(TCP_PORT);
  Serial.println("TCP server started on port 12345" );
  // Initialize UDP
  udp.begin(UDP_PORT);
  Serial.println("Listening for UDP broadcast message...");
}

void controlRoom(String cmd){
  if(cmd == "start"){
    digitalWrite(CONTROL_PIN, HIGH);
    client.print("started");
    Serial.print("Replyed: started\n");
  }
  else if(cmd == "end"){
    digitalWrite(CONTROL_PIN, LOW);
    client.print("ended");
    Serial.print("REPLYED: ended\n");
  }
  else if(cmd == "getRunningStatus"){
    int pinStatus = digitalRead(CONTROL_PIN);
    if (pinStatus == HIGH) {
        client.print("started");
        Serial.print("Replyed: started\n");
    } else {
        client.print("ended");
        Serial.print("Replyed: ended\n");
    }
  }
}

// Function to handle the TCP client interaction
void handleTCPClient() {
  Serial.println("handle TCP Client!");
  while(1){
    client = server.available();
    if (client) {
      Serial.println("PC connected!");
      while (client.connected()) {
          client.setTimeout(10000);
          Serial.println("Listenning message from PC...");
          String data = client.readStringUntil('\n');
          if (!data.length() == 0) {
            Serial.print("Received: ");
            Serial.println(data);
            controlRoom(data);
          }
          else{
            Serial.println("Connection timeout, Client disconnected");
            break;
          }
      }
      client.stop();
      Serial.println("Client disconnected, Listening for UDP broadcast message again...");
      udp.begin(UDP_PORT);
      return;
    }
  }
   Serial.println("While timeout, back to UDP listenning...");
}

void listenForUDP() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    char incomingPacket[255];
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = '\0';  // Null-terminate the received string
    }

    Serial.print("Received UDP packet: ");
    Serial.println(incomingPacket);
    if (String(incomingPacket) == name) {
      String response = name;
      udp.beginPacket(udp.remoteIP(), udp.remotePort()); // Send response to the sender's IP and port
      udp.write((const uint8_t*)response.c_str(), response.length());
      udp.endPacket(); // End the UDP packet
      udp.stop();  // Stop listening for UDP messages
      handleTCPClient();  // Start handling TCP commands
    }
  }
}

void loop() {
  listenForUDP(); 
}
