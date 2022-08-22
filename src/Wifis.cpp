#include "Wifis.h"

WiFiClient client;

void Wifi_Init()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("WiFi Connected");
  Serial.println(WiFi.localIP());
}

void send_event(const char *event)
{
  Serial.print("Connecting to ");
  Serial.println(IFTTT_HOST);

  const uint8_t httpPort = 80;
  if (!client.connect(IFTTT_HOST, httpPort))
  {
    Serial.println("Connection failed");
    return;
  }

  String url = "/trigger/";
  url += event;
  url += "/with/key/";
  url += IFTTT_KEY;

  String mJson = String("{\"value1\":\"") + "센서가 감지되어 전원 종료 후 제어를 보류합니다.\"}";

  Serial.print("Requesting URL: ");
  Serial.println(url);

  client.println(String("POST ") + url + " HTTP/1.1");
  client.println(String("Host: ") + IFTTT_HOST);
  client.println("Content-Type: application/json");
  client.print("Content-Length: ");
  client.println(mJson.length());
  client.println();
  client.println(mJson);

  while (client.connected())
  {
    if (client.available())
    {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    else
    {
      delay(50);
    };
  }
  Serial.println();
  Serial.println("closing connection");
  client.stop();
}