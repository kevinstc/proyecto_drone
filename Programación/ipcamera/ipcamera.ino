#include "esp32cam.h"
#include <WebServer.h>
#include <WiFI.h>
static const char* WIFI_SSID = "FreeCP";
static const char* WIFI_PASS = "#samplepassword#";

esp32cam::Resolution initialResolution;

WebServer server(80);

static auto loRes = esp32cam::Resolution::find(320,240);
static auto hiRes = esp32cam::Resolution::find(800,600);

void serveJpg()
{
  auto frame = esp32cam::capture();
  if (frame ==nullptr)
  {
    Serial.println("failCapture");
    server.send(503, "", "");
    return;
  }
  Serial.printf("Capture OK %dx%d %db\n", frame->getWidth(), frame->getHeight(), static_cast<int>(frame->size()));

  server.setContentLength(frame->size());
  server.send(200,"image/jpeg");
  WiFiClient client = server.client();
  frame->writeTo(client);
}

void handleJpgLo()
{
  if(!esp32cam::Camera.changeResolution(loRes)) 
  {
  Serial.println("setLR fail"); 
  }
  serveJpg();
}

void handleJpgHi()
{
  if(!esp32cam::Camera.changeResolution(hiRes)) 
  {
  Serial.println("setHR fail");
  }
  serveJpg();
}



void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("waiting for connection");
  delay(100);
 
  {
    using namespace esp32cam;

    initialResolution = Resolution::find(1024, 768);

    Config cfg;
    cfg.setPins(pins::AiThinker);
    cfg.setResolution(hiRes);
    cfg.setBufferCount(2);
    cfg.setJpeg(80);

    bool ok = Camera.begin(cfg);
    Serial.println(ok ? "Camera ok" : "camera fail");
  }
  /////
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("still not connection");
  while (WiFi.status() != WL_CONNECTED) 
  { 
    delay(500);
    Serial.println("connection failed");
  }
 
  Serial.print("http://");
  Serial.println(WiFi.localIP());
  Serial.println("/cam-lo.jpg");

  Serial.print("http://");
  Serial.println(WiFi.localIP());
  Serial.println("/cam-hi.jpg");
  
  server.on("/cam-lo.jpg", handleJpgLo);
  server.on("/cam-hi.jpg", handleJpgHi);
  server.begin();
}

void loop()
{
  server.handleClient();
}
