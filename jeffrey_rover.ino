#include <WiFiS3.h>

// ===== CREATE YOUR OWN WIFI =====
char ssid[] = "RobotCar";      // WiFi name (you will see this on phone)
char pass[] = "12345678";      // Password (min 8 chars)

WiFiServer server(80);

// ===== MOTOR PINS =====

// Driver 1
int D1_IN1 = 2;
int D1_IN2 = 3;
int D1_IN3 = 4;
int D1_IN4 = 5;

// Driver 2
int D2_IN1 = 6;
int D2_IN2 = 7;
int D2_IN3 = 8;
int D2_IN4 = 9;

// Driver 3
int D3_IN1 = 10;
int D3_IN2 = 11;
int D3_IN3 = 12;
int D3_IN4 = 13;

void setup() {
  Serial.begin(9600);

  // Set pins
  int pins[] = {
    D1_IN1, D1_IN2, D1_IN3, D1_IN4,
    D2_IN1, D2_IN2, D2_IN3, D2_IN4,
    D3_IN1, D3_IN2, D3_IN3, D3_IN4
  };

  for (int i = 0; i < 12; i++) {
    pinMode(pins[i], OUTPUT);
  }

  // ===== START WIFI HOTSPOT =====
  Serial.println("Starting WiFi...");
  WiFi.beginAP(ssid, pass);  // IMPORTANT LINE

  delay(5000);

  Serial.println("WiFi Started!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

// ===== MOTOR FUNCTIONS =====

void forward() {
  digitalWrite(D1_IN1, HIGH); digitalWrite(D1_IN2, LOW);
  digitalWrite(D1_IN3, LOW);  digitalWrite(D1_IN4, HIGH);

  digitalWrite(D2_IN1, HIGH); digitalWrite(D2_IN2, LOW);
  digitalWrite(D2_IN3, LOW);  digitalWrite(D2_IN4, HIGH);

  digitalWrite(D3_IN1, HIGH); digitalWrite(D3_IN2, LOW);
  digitalWrite(D3_IN3, LOW);  digitalWrite(D3_IN4, HIGH);
}

void backward() {
  digitalWrite(D1_IN1, LOW);  digitalWrite(D1_IN2, HIGH);
  digitalWrite(D1_IN3, HIGH); digitalWrite(D1_IN4, LOW);

  digitalWrite(D2_IN1, LOW);  digitalWrite(D2_IN2, HIGH);
  digitalWrite(D2_IN3, HIGH); digitalWrite(D2_IN4, LOW);

  digitalWrite(D3_IN1, LOW);  digitalWrite(D3_IN2, HIGH);
  digitalWrite(D3_IN3, HIGH); digitalWrite(D3_IN4, LOW);
}

void left() {
  digitalWrite(D1_IN1, LOW);  digitalWrite(D1_IN2, HIGH);
  digitalWrite(D1_IN3, HIGH); digitalWrite(D1_IN4, LOW);

  digitalWrite(D2_IN1, LOW);  digitalWrite(D2_IN2, HIGH);
  digitalWrite(D2_IN3, HIGH); digitalWrite(D2_IN4, LOW);

  digitalWrite(D3_IN1, LOW);  digitalWrite(D3_IN2, HIGH);
  digitalWrite(D3_IN3, HIGH); digitalWrite(D3_IN4, LOW);
}

void right() {
  digitalWrite(D1_IN1, HIGH); digitalWrite(D1_IN2, LOW);
  digitalWrite(D1_IN3, LOW);  digitalWrite(D1_IN4, HIGH);

  digitalWrite(D2_IN1, HIGH); digitalWrite(D2_IN2, LOW);
  digitalWrite(D2_IN3, LOW);  digitalWrite(D2_IN4, HIGH);

  digitalWrite(D3_IN1, HIGH); digitalWrite(D3_IN2, LOW);
  digitalWrite(D3_IN3, LOW);  digitalWrite(D3_IN4, HIGH);
}

void stopMotors() {
  int pins[] = {
    D1_IN1, D1_IN2, D1_IN3, D1_IN4,
    D2_IN1, D2_IN2, D2_IN3, D2_IN4,
    D3_IN1, D3_IN2, D3_IN3, D3_IN4
  };

  for (int i = 0; i < 12; i++) {
    digitalWrite(pins[i], LOW);
  }
}

// ===== LOOP =====

void loop() {
  WiFiClient client = server.available();

  if (client) {
    String request = client.readStringUntil('\r');

    if (request.indexOf("/F") != -1) forward();
    else if (request.indexOf("/B") != -1) backward();
    else if (request.indexOf("/L") != -1) left();
    else if (request.indexOf("/R") != -1) right();
    else if (request.indexOf("/S") != -1) stopMotors();

    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html\n");

    client.println("<html><body style='text-align:center;'>");
    client.println("<h1>Robot Control</h1>");

    client.println("<a href='/F'><button style='width:120px;height:60px;'>Forward</button></a><br><br>");
    client.println("<a href='/L'><button style='width:120px;height:60px;'>Left</button></a>");
    client.println("<a href='/R'><button style='width:120px;height:60px;'>Right</button></a><br><br>");
    client.println("<a href='/B'><button style='width:120px;height:60px;'>Backward</button></a><br><br>");
    client.println("<a href='/S'><button style='width:120px;height:60px;background:red;'>STOP</button></a>");

    client.println("</body></html>");

    client.stop();
  }
}
