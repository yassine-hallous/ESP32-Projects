#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Galaxy A14 2869";
const char* password = "kzt9qeau6yxtbnx";

WebServer server(80);

// HTML for the web page
String htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32 Calculator</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body { font-family: Arial, sans-serif; text-align: center; padding: 20px; background-color: #f0f0f0; }
        .container { max-width: 400px; margin: auto; background: #fff; padding: 30px; border-radius: 10px; box-shadow: 0 0 10px rgba(0,0,0,0.1); }
        h1 { color: #333; }
        input[type='text'], select, button { width: 100%; padding: 10px; margin: 10px 0; border: 1px solid #ccc; border-radius: 5px; box-sizing: border-box; }
        select { margin-top: 5px; }
        button { background-color: #4CAF50; color: white; border: none; cursor: pointer; }
        button:hover { background-color: #45a049; }
        .result { margin-top: 20px; padding: 20px; border: 1px solid #4CAF50; background-color: #d4edda; border-radius: 5px; text-align: center; }
    </style>
</head>
<body>
    <div class="container">
        <h1>ESP32 Calculator</h1>
        <form action="/calculate" method="POST">
            <input type="text" name="num1" placeholder="Number 1" required><br>
            <select name="operation">
                <option value="add">+</option>
                <option value="subtract">-</option>
                <option value="multiply">*</option>
                <option value="divide">/</option>
            </select><br>
            <input type="text" name="num2" placeholder="Number 2" required><br>
            <button type="submit">Calculate</button>
        </form>
        <div class="result" id="resultLabel"></div>
    </div>
</body>
</html>
)rawliteral";

void handleRoot() {
    server.send(200, "text/html", htmlPage);
}

void handleCalculate() {
    if (server.hasArg("num1") && server.hasArg("num2") && server.hasArg("operation")) {
        float num1 = server.arg("num1").toFloat();
        float num2 = server.arg("num2").toFloat();
        String operation = server.arg("operation");
        float result;
        bool validInput = true;
        String resultMessage;

        if (isnan(num1) || isnan(num2)) {
            validInput = false;
        } else {
            if (operation == "add") {
                result = num1 + num2;
            } else if (operation == "subtract") {
                result = num1 - num2;
            } else if (operation == "multiply") {
                result = num1 * num2;
            } else if (operation == "divide") {
                if (num2 != 0) {
                    result = num1 / num2;
                } else {
                    validInput = false;
                    resultMessage = "Error: Division by zero";
                }
            } else {
                validInput = false;
                resultMessage = "Invalid Operation";
            }
        }

        if (validInput) {
            resultMessage = "Result: " + String(result);
        } else if (resultMessage == "") {
            resultMessage = "Invalid Input";
        }

        String response = htmlPage;
        response.replace("<div class=\"result\" id=\"resultLabel\"></div>", "<div class=\"result\" id=\"resultLabel\">" + resultMessage + "</div>");
        server.send(200, "text/html", response);
    } else {
        server.send(400, "text/plain", "Invalid Input");
    }
}

void setup() {
    Serial.begin(115200);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // Set up web server routes
    server.on("/", handleRoot);
    server.on("/calculate", HTTP_POST, handleCalculate);

    // Start the server
    server.begin();
}

void loop() {
    server.handleClient();
}
