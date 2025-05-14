
#include <WiFi.h>
#define CONTROL_PIN 0 

// BOM MUSIC BOX
// 66668888
const char* ssid     = "BOM MUSIC BOX"; 
const char* password = "66668888";
WiFiServer server(3333);
WiFiClient client;
String localIp;
void setup() {
  
  pinMode(CONTROL_PIN, OUTPUT);
  digitalWrite(CONTROL_PIN, LOW);
  Serial.begin(115200);
  delay(1000);


  // IPAddress local_IP(192, 168, 2, 33);       // Choose an unused IP in your network
  // IPAddress gateway(192, 168, 1, 1);          // Your router's IP
  // IPAddress subnet(255, 255, 255, 0);
  // IPAddress primaryDNS(8, 8, 8, 8);           // Optional
  // IPAddress secondaryDNS(8, 8, 4, 4);
  // if (!WiFi.config(local_IP)) {
  //     Serial.println("⚠️  STA Failed to configure");
  // }

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
  server.begin();
  Serial.println("TCP server started on port 3333");
}


void controlRoom(String cmd){
  if(cmd == "start"){
    digitalWrite(CONTROL_PIN, HIGH);
    client.print("started");
    Serial.print("REPLYED: started");
  }
  else if(cmd == "end"){
    digitalWrite(CONTROL_PIN, LOW);
    client.print("ended");
    Serial.print("REPLYED: ended");
  }
  else if(cmd == "getRunningStatus"){
    int pinStatus = digitalRead(CONTROL_PIN);
    if (pinStatus == HIGH) {
        client.print("started");
    } else {
        client.print("ended");
    }
    Serial.print("REPLYED QQQQ");
  }
}

void handleCmdFromPC(){
  client = server.available();
  if (client) {
    Serial.println("PC connected!");
    while (client.connected()) {
      if (client.available()) {
        String data = client.readStringUntil('\n');
        Serial.print("Received: ");
        Serial.println(data);

        controlRoom(data);
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}

void loop() {
  handleCmdFromPC();
}
