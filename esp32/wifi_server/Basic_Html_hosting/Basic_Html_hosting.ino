#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Rocket 2.4";
const char* password = "Roki@2025";

WebServer server(80); // HTTP server on port 80

const char* html = R"rawliteral(
<!DOCTYPE html>
<html>
<head><title>ESP32 Web Server</title></head>
<body>
  <h1>Hello from ESP32!</h1>
  <p>This page is hosted on Rokis ESP32 😎</p>
</body>
</html>
)rawliteral";

void handleRoot() {
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi!");
  Serial.println(WiFi.localIP()); // IP to open in browser

  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
