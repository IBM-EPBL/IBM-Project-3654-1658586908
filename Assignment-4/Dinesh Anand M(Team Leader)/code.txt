#include<WiFi.h>
#include<PubSubClient.h>

void callback(char* subscribetopic,byte* payload,unsigned int payloadLength);

#define ORG "9y2uod"
#define DEVICE_TYPE "Microcontroller"
#define DEVICE_ID "1407"
#define TOKEN "9585786415"
const int trigger = 21;
const int echo = 4;
const int led = 14;
int res;

char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char publishTopic[] = "iot-2/evt/Data/fmt/json";
char subscribetopic[] = "iot-2/cmd/command/fmt/String";
char authMethod[] = "use-token-auth";
char token[]  = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

WiFiClient wifiClient;
PubSubClient client(server,1883,NULL,wifiClient);

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(led, OUTPUT);
  wificonnect();
  mqttconnect();
}

void loop() {
    digitalWrite(trigger, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH); 
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);

    double duration = pulseIn(4,HIGH);
    duration = duration/100;
    float distance = ceil(((0.034 * (duration))/2)*100);
    res = int(distance);
  
    PublishData(res);

    if(!client.loop()){
         mqttconnect();
  }
    delay(1000);
}

void wificonnect(){
  Serial.println();
  Serial.print("Connecting to ");
  WiFi.begin("Wokwi-GUEST","",6);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void mqttconnect(){
  if(!client.connected()){
    Serial.println("Reconnecting client to ");
    Serial.println(server);
    while (!client.connect(clientId,authMethod,token)){
      Serial.print(".");
      delay(500);
    }
    initManagedDevice();
    Serial.println();
  }
}

void initManagedDevice(){
  if(client.subscribe(subscribetopic)){
    Serial.println(subscribetopic);
    Serial.println("Subscribe to cmd OK");
  }
  else{
    Serial.println("Subscribe to cmd FAILED");
  }
}

void PublishData(int dis){
  mqttconnect();
  if(dis < 100){
  digitalWrite(led,HIGH);
  String payload = "{\"Alert Distance\":";
  payload += dis;
  payload += "}";

  Serial.print("Sending payload: ");
  Serial.println(payload);

  if(client.publish(publishTopic,(char*) payload.c_str())){
    Serial.println("Publish OK");
  }
  else{
    Serial.println("Publish Failed");
  }
  }
  else{
  digitalWrite(led,LOW);
  String payload = "{\"Distance\":";
  payload += dis;
  payload += "}";

  Serial.print("Sending payload: ");
  Serial.println(payload);

  if(client.publish(publishTopic,(char*) payload.c_str())){
    Serial.println("Publish OK");
  }
  else{
    Serial.println("Publish Failed");
  }
  }
  }


void callback(char* subscribetopic,byte* payload, unsigned int payloadLength){
  Serial.print("Callback invoked for topic: ");
  Serial.println(subscribetopic);
}