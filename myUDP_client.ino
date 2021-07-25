#include <Ethernet.h>
#include <EthernetUdp.h>

uint64_t prev_time=0;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

EthernetUDP Udp;

IPAddress remote(192,168,1,250);
unsigned int remotePort=8080;

uint8_t buffer_TX[] = {0x00, 0x02, 0x01, 0x03};

void setup() {
  Serial.begin(9600);
  Ethernet.init(10);
  
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

  Udp.begin(8000);
}

void loop() {
  
  if (millis()>prev_time+1000){
    send_UDP();
    prev_time = millis();
  }
  
  delay(50);  
}

void send_UDP(){
  Serial.print(millis());
  Serial.print(" - Sending UDP: ");
  Serial.print(buffer_TX[0]);
  Serial.print(" - ");
  Serial.print(buffer_TX[1]);
  Serial.print(" - ");
  Serial.print(buffer_TX[2]);
  Serial.print(" - ");
  Serial.print(buffer_TX[3]);
  Serial.print("\n");
  Udp.beginPacket(remote,remotePort);
  Udp.write(buffer_TX,sizeof(buffer_TX));
  Udp.endPacket();
}
