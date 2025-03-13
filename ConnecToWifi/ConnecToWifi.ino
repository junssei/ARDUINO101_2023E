#include <ESP8266WiFi.h>

const char* ssid = "PLDTHOMEFIBRbfbf0"; // Your WiFi SSID
const char* password = "PLDTWIFIcnxd6"; // Your WiFi password

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  
  Serial.println("\nWiFi Connected.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
    WiFiClient client = server.available();
    if (client) {
      Serial.println("New Client Connected.");
      String header = "";
      String currentLine = "";
      
      while (client.connected()) {
        if (client.available()) {
          char c = client.read();
          header += c;
          
          if (c == '\n') {
            if (currentLine.length() == 0) {
              if (header.indexOf("GET /water-level") >= 0) {
                  // Serve sensor data in plain text
                  int waterLevel = analogRead(A0);
                  client.println("HTTP/1.1 200 OK");
                  client.println("Content-Type: text/plain");
                  client.println("Connection: close");
                  client.println();
                  client.println(waterLevel);
              } else {
                  // Serve HTML page
                  client.println("HTTP/1.1 200 OK");
                  client.println("Content-type:text/html");
                  client.println("Connection: close");
                  client.println();
                  client.println("<!DOCTYPE html><html>");
                  client.println("<head><meta name='viewport' content='width=device-width, initial-scale=1'>");
                  client.println("<style>");
                  client.println("body { font-family: Arial, sans-serif; text-align: center; background-color: #f4f4f4; }");
                  client.println(".container { width: 90%; max-width: 400px; margin: auto; padding: 20px; background: white; border-radius: 10px; box-shadow: 0px 4px 6px rgba(0,0,0,0.1); }");
                  client.println("h1 { color: #333; }");
                  client.println(".level-box { font-size: 24px; font-weight: bold; padding: 20px; border-radius: 8px; color: white; }");
                  client.println(".low { background: #f44336; }");
                  client.println(".medium { background: #ff9800; }");
                  client.println(".high { background: #4CAF50; }");
                  client.println("</style>");
                  client.println("<script>");
                  client.println("function updateLevel() {");
                  client.println("  fetch('/water-level').then(response => response.text()).then(data => {");
                  client.println("    document.getElementById('level').innerText = data;");
                  client.println("    let levelBox = document.getElementById('level-box');");
                  client.println("    let levelValue = parseInt(data);");
                  client.println("    if (levelValue < 100) { levelBox.className = 'level-box low'; }");
                  client.println("    else if (levelValue < 250) { levelBox.className = 'level-box medium'; }");
                  client.println("    else { levelBox.className = 'level-box high'; }");
                  client.println("  });");
                  client.println("}");
                  client.println("setInterval(updateLevel, 1000);"); // Update every 1 sec
                  client.println("</script>");
                  client.println("</head>");
                  client.println("<body>");
                  client.println("<div class='container'>");
                  client.println("<h1>Water Level Monitor</h1>");
                  client.println("<p>Current Water Level:</p>");
                  client.println("<div id='level-box' class='level-box'>--</div>");
                  client.println("<p id='level' style='font-size: 30px; font-weight: bold;'>--</p>");
                  client.println("</div>");
                  client.println("</body></html>");
              }
              break;
            } else {
                currentLine = "";
            }
          } else if (c != '\r') {
              currentLine += c;
          }
        }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}