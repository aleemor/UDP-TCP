#include <SPI.h>
#include <Ethernet.h>

uint64_t prev_time=0;


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte server_IP[] = {192,168,1,250};

EthernetClient client;

struct dati{
  uint8_t start_pack = 0x00;
  uint8_t one = 0x01;
  uint8_t two = 0x02;
  uint8_t end_pack = 0x03;
}packet;

void setup() {
  Ethernet.init(10);  
  
  Serial.begin(9600);

  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    } else if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    while (true) {
      delay(1);
    }
  }
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());

  if (client.connect(server_IP, 8080)){
    Serial.println("Connected.");
  }
}

void loop() {
  
  connection_debug();

  if (millis()>prev_time+1000){
    send_TCP();
    prev_time = millis();
  }
  
  delay(50);
}

void send_TCP(){
  if (client.connected()){
    Serial.print(millis());
    Serial.print(" sending: ");
    Serial.print(packet.start_pack,HEX);
    Serial.print(" - ");
    Serial.print(packet.one,HEX);
    Serial.print(" - ");   
    Serial.print(packet.two,HEX);
    Serial.print(" - ");    
    Serial.print(packet.end_pack,HEX);
    Serial.print("\n");     
    client.write((byte *)&packet, sizeof(packet));
  }
  else {
    Serial.println("TCP connection failed");
  }
}

void connection_debug(){
    switch (Ethernet.maintain()) {
    case 1:
      Serial.println("Error: renewed fail");
      break;
    case 2:
      Serial.println("Renewed success");
      Serial.print("My IP address: ");
      
      Serial.println(Ethernet.localIP());
      break;
    case 3:
      Serial.println("Error: rebind fail");
      break;

    case 4:
      Serial.println("Rebind success");
      Serial.print("My IP address: ");
      Serial.println(Ethernet.localIP());
      break;

    default:
      break;
  }
}
