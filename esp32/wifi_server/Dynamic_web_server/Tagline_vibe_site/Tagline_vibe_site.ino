#include <WiFi.h>
#include <WebServer.h>

// Create a web server on port 80
WebServer server(80);

// Define Wi-Fi credentials for connecting to an existing network (STA mode)
const char* ssid = "Rocket 2.4";
const char* password = "Roki@2025";

// Store the current tagline (initially set to a default value)
String currentTagline = "Welcome to ESP32 Web!";

// HTML template for the webpage
const char* htmlPageTemplate = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Today's Vibe</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <style>
    @keyframes gradient {
      0% { background-position: 0% 50%; }
      50% { background-position: 100% 50%; }
      100% { background-position: 0% 50%; }
    }
    
    @keyframes float {
      0% { transform: translateY(0px); }
      50% { transform: translateY(-10px); }
      100% { transform: translateY(0px); }
    }
    
    @keyframes glow {
      0% { text-shadow: 0 0 10px rgba(255, 0, 128, 0.7); }
      25% { text-shadow: 0 0 15px rgba(255, 102, 0, 0.7); }
      50% { text-shadow: 0 0 20px rgba(255, 230, 0, 0.7); }
      75% { text-shadow: 0 0 15px rgba(0, 255, 128, 0.7); }
      100% { text-shadow: 0 0 10px rgba(0, 128, 255, 0.7); }
    }
    
    @keyframes rgb-border {
      0% { border-color: #ff0080; }
      20% { border-color: #ff6600; }
      40% { border-color: #ffe600; }
      60% { border-color: #00ff80; }
      80% { border-color: #0080ff; }
      100% { border-color: #8000ff; }
    }
    
    @keyframes pulse {
      0% { transform: scale(1); }
      50% { transform: scale(1.05); }
      100% { transform: scale(1); }
    }
    
    * {
      margin: 0;
      padding: 0;
      box-sizing: border-box;
      font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
    }
    
    html {
      font-size: 16px;
    }
    
    body {
      background: linear-gradient(-45deg, #ee7752, #e73c7e, #23a6d5, #23d5ab);
      background-size: 400% 400%;
      animation: gradient 15s ease infinite;
      color: white;
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: center;
      min-height: 100vh;
      padding: 1rem;
      overflow-x: hidden;
    }
    
    .container {
      background: rgba(15, 14, 22, 0.8);
      backdrop-filter: blur(10px);
      -webkit-backdrop-filter: blur(10px); /* For Safari */
      border: 2px solid;
      border-radius: 16px;
      box-shadow: 0 0 25px rgba(255, 255, 255, 0.2);
      padding: 2rem;
      width: 100%;
      max-width: 500px;
      text-align: center;
      position: relative;
      animation: rgb-border 5s linear infinite, float 6s ease-in-out infinite;
      z-index: 1;
    }
    
    .container::before {
      content: "";
      position: absolute;
      top: -5px;
      left: -5px;
      right: -5px;
      bottom: -5px;
      background: linear-gradient(45deg, #ff0080, #ff6600, #ffe600, #00ff80, #0080ff, #8000ff);
      background-size: 400% 400%;
      z-index: -1;
      filter: blur(15px);
      opacity: 0.7;
      animation: gradient 10s ease infinite;
      border-radius: 20px;
    }
    
    h1 {
      font-size: 1.8rem;
      margin-bottom: 1.5rem;
      color: white;
      font-weight: 700;
      animation: glow 5s ease-in-out infinite;
      text-transform: uppercase;
      letter-spacing: 1px;
      word-wrap: break-word;
      overflow-wrap: break-word;
    }
    
    form {
      display: flex;
      flex-direction: column;
      gap: 1.2rem;
      width: 100%;
    }
    
    input {
      padding: 0.8rem 1rem;
      border: 3px solid #e0e0e0;
      border-radius: 12px;
      font-size: 1rem;
      background: rgba(255, 255, 255, 0.1);
      color: white;
      transition: all 0.3s;
      animation: rgb-border 5s linear infinite;
      width: 100%;
    }
    
    input::placeholder {
      color: rgba(255, 255, 255, 0.7);
      font-size: 0.9rem;
    }
    
    input:focus {
      outline: none;
      background: rgba(255, 255, 255, 0.2);
      box-shadow: 0 0 15px rgba(255, 255, 255, 0.3);
    }
    
    button {
      background: linear-gradient(45deg, #ff0080, #ff6600, #ffe600, #00ff80, #0080ff, #8000ff);
      background-size: 400% 400%;
      animation: gradient 5s ease infinite, pulse 2s infinite;
      color: white;
      border: none;
      border-radius: 12px;
      padding: 0.8rem 1rem;
      font-size: 1rem;
      font-weight: 600;
      cursor: pointer;
      transition: transform 0.3s, box-shadow 0.3s;
      text-transform: uppercase;
      letter-spacing: 1px;
      box-shadow: 0 0 15px rgba(255, 0, 128, 0.5);
      width: 100%;
      -webkit-tap-highlight-color: transparent; /* Remove tap highlight on mobile */
    }
    
    button:hover, button:active {
      transform: translateY(-3px) scale(1.03);
      box-shadow: 0 0 25px rgba(255, 0, 128, 0.8);
    }
    
    .tagline {
      padding: 1.2rem;
      background: rgba(255, 255, 255, 0.1);
      border-radius: 12px;
      margin-bottom: 1.5rem;
      position: relative;
      overflow: hidden;
    }
    
    .tagline::before {
      content: "";
      position: absolute;
      top: -50%;
      left: -50%;
      width: 200%;
      height: 200%;
      background: linear-gradient(45deg, transparent, rgba(255, 255, 255, 0.1), transparent);
      transform: rotate(45deg);
      animation: shine 3s infinite;
    }
    
    @keyframes shine {
      0% { transform: translateX(-100%) rotate(45deg); }
      100% { transform: translateX(100%) rotate(45deg); }
    }
    
    .blob {
      position: absolute;
      width: 150px;
      height: 150px;
      background: linear-gradient(45deg, #ff0080, #ff6600);
      border-radius: 50%;
      filter: blur(40px);
      opacity: 0.4;
      z-index: -1;
    }
    
    .blob1 {
      top: -50px;
      left: -50px;
      animation: float 8s ease-in-out infinite;
    }
    
    .blob2 {
      bottom: -50px;
      right: -50px;
      background: linear-gradient(45deg, #00ff80, #0080ff);
      animation: float 7s ease-in-out infinite reverse;
    }
    
    /* Media Queries for Responsiveness */
    @media (max-width: 768px) {
      html {
        font-size: 14px;
      }
      
      .container {
        padding: 1.5rem;
        max-width: 90%;
      }
      
      .blob {
        width: 100px;
        height: 100px;
      }
    }
    
    @media (max-width: 480px) {
      html {
        font-size: 12px;
      }
      
      body {
        padding: 0.8rem;
      }
      
      .container {
        padding: 1.2rem;
        animation: rgb-border 5s linear infinite, float 4s ease-in-out infinite;
      }
      
      h1 {
        font-size: 1.5rem;
      }
      
      input::placeholder {
        font-size: 0.85rem;
      }
      
      .blob {
        opacity: 0.3; /* Reduce opacity on small screens for better readability */
      }
      
      /* Reduce animation intensity on mobile for better performance */
      @keyframes float {
        0% { transform: translateY(0px); }
        50% { transform: translateY(-5px); }
        100% { transform: translateY(0px); }
      }
    }
    
    /* Ensure animations don't cause motion sickness */
    @media (prefers-reduced-motion: reduce) {
      * {
        animation-duration: 0.01ms !important;
        animation-iteration-count: 1 !important;
        transition-duration: 0.01ms !important;
        scroll-behavior: auto !important;
      }
    }
  </style>
</head>
<body>
  <div class="blob blob1"></div>
  <div class="blob blob2"></div>
  <div class="container">
    <div class="tagline">
      <h1>%TAGLINE%</h1>
    </div>
    <form action="/update" method="POST">
      <input type="text" name="tagline" placeholder="< Drop your ultra fresh vibe here />" required>
      <button type="submit">Level Up The Vibe</button>
    </form>
  </div>
</body>
</html>
)rawliteral";

// Function to replace the placeholder in the HTML with the current tagline
String buildPage() {
  String page = htmlPageTemplate;
  page.replace("%TAGLINE%", currentTagline);
  return page;
}

// Function to handle the root page request (displays the webpage)
void handleRoot() {
  server.send(200, "text/html", buildPage());
}

// Function to handle the update request (changes the tagline based on user input)
void handleUpdate() {
  if (server.method() == HTTP_POST) {
    if (server.hasArg("tagline")) {
      currentTagline = server.arg("tagline");  // Update the tagline
      Serial.println("Updated tagline: " + currentTagline);  // Log the new tagline
    }
  }
  server.sendHeader("Location", "/");  // Redirect back to the root page after update
  server.send(303);  // HTTP status code for redirection
}

void setup() {
  // Start the Serial Monitor for debugging
  Serial.begin(115200);

  // Set ESP32 to Dual Mode (STA + AP)
  WiFi.mode(WIFI_AP_STA);

  // Connect to the existing Wi-Fi network (STA mode)
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {  // Wait until connected to the Wi-Fi network
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to Wi-Fi network");

  // Print the IP address assigned by the router (STA IP)
  Serial.print("STA IP Address: ");
  Serial.println(WiFi.localIP());

  // Create the Access Point (AP mode) with no password
  WiFi.softAP("ESP32-Tagline");
  Serial.print("AP IP Address: ");
  Serial.println(WiFi.softAPIP());  // Print the IP address of the AP

  // Set up the server routes for handling requests
  server.on("/", handleRoot);
  server.on("/update", HTTP_POST, handleUpdate);

  // Start the web server
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
}
