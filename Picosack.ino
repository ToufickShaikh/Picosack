#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <ESP8266HTTPClient.h>
#include "Pico.h"                       //header file containing HTML code
const char* ssid = "Picosack";
const char* password = "12345678";


ESP8266WebServer server(80);

String publicIP;



void handleRoot() {
  server.send(200, "text/html", html);  //send HTML page to web browser of client
 
}


void handleForm() {
  String html = "<html><body>";
  html += "<h1>upload form to picosack</h1>";
  html += "<form method='POST' action='/submit'>";
  html += "<label for='name'>Name:</label>";
  html += "<input type='text' id='name' name='name'><br><br>";
  html += "<label for='email'>Email:</label>";
  html += "<input type='email' id='email' name='email'><br><br>";
  html += "<input type='submit' value='Submit'>";
  html += "<h1>Upload file to picosack(in future)</h1>";
  html += "<form method='POST' action='/upload' enctype='multipart/form-data'>";
  html += "<input type='file' name='file'><br><br>";
  html += "<input type='submit' value='Upload'>";
  html += "</form>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}


void handleSubmit() {
  String name = server.arg("name");
  String email = server.arg("email");

  String message = "Name: " + name + ", Email: " + email;
  message += "<br>Public IP: " + publicIP;

  Serial.println(message);

  // Save the data to a file
  File dataFile = SPIFFS.open("/formdata.txt", "a");
  if (dataFile) {
    dataFile.println(message);
    dataFile.close();
    Serial.println("Data saved to file");
  } else {
    Serial.println("Error opening data file");
  }

  server.send(200, "text/html", "Form submitted successfully!");
}

void handleData() {
  String data;

  // Read the data file
  File dataFile = SPIFFS.open("/formdata.txt", "r");
  if (dataFile) {
    while (dataFile.available()) {
      String line = dataFile.readStringUntil('\n');
      data += line + "<br>";
    }
    dataFile.close();
    Serial.println("Data file read");
  } else {
    Serial.println("Error opening data file");
  }

  String html = "<html><body>";
  html += "<h1>Submitted Form Data</h1>";
  html += data;
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleViewData() {
  String data;

  // Read the data file
  File dataFile = SPIFFS.open("/formdata.txt", "r");
  if (dataFile) {
    while (dataFile.available()) {
      data += dataFile.readStringUntil('\n');
    }
    dataFile.close();
    Serial.println("Data file read");
  } else {
    Serial.println("Error opening data file");
  }

  String html = "<html><body>";
  html += "<h1>Saved Form Data</h1>";
  html += "<pre>" + data + "</pre>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void getPublicIP() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, "http://api.ipify.org");
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
      publicIP = http.getString();
      Serial.print("Public IP: ");
      Serial.println(publicIP);
    }
    http.end();
  }
}

void handleDeleteData() {
  if (SPIFFS.remove("/formdata.txt")) {
    Serial.println("Data file deleted");
    server.send(200, "text/html", "Data deleted successfully!");
  } else {
    Serial.println("Error deleting data file");
    server.send(200, "text/html", "Error deleting data!");
  }
}

void handleStorage() {
  fs::FSInfo fs_info;
  if (SPIFFS.info(fs_info)) {
    String storageStatus = "Total Bytes: " + String(fs_info.totalBytes) + "<br>";
    storageStatus += "Used Bytes: " + String(fs_info.usedBytes) + "<br>";
    storageStatus += "Free Bytes: " + String(fs_info.totalBytes - fs_info.usedBytes) + "<br>";
    server.send(200, "text/html", storageStatus);
  } else {
    server.send(200, "text/html", "Error reading storage information!");
  }
}

// void handleSack() {
//   String html = "<html><body>";
//   html += "<h1>Upload file to sack</h1>";
//   html += "<form method='POST' action='/upload' enctype='multipart/form-data'>";
//   html += "<input type='file' name='file'><br><br>";
//   html += "<input type='submit' value='Upload'>";
//   html += "</form>";
//   html += "</body></html>";
//   server.send(200, "text/html", html);
// }

// void handleUpload() {
//   HTTPUpload& upload = server.upload();
//   if (upload.status == UPLOAD_FILE_START) {
//     String filename = "/uploads/" + upload.filename;
//     fs::FSInfo fs_info;
//     if (SPIFFS.info(fs_info)) {
//       if (fs_info.totalBytes - fs_info.usedBytes < upload.totalSize) {
//         server.send(200, "text/html", "Not enough space available to upload the file!");
//         return;
//       }
//     }
//     fs::File file = SPIFFS.open(filename, "w");
//     if (!file) {
//       server.send(200, "text/html", "Error opening file for writing!");
//       return;
//     }
//     file.close();
//   } else if (upload.status == UPLOAD_FILE_WRITE) {
//     String filename = "/uploads/" + upload.filename;
//     fs::File file = SPIFFS.open(filename, "a");
//     if (file) {
//       file.write(upload.buf, upload.currentSize);
//       file.close();
//     }
//   } else if (upload.status == UPLOAD_FILE_END) {
//     server.send(200, "text/html", "File uploaded successfully!");
//   }
// }

// void handleFileList() {
//   String fileList = "";
//   Dir dir = SPIFFS.openDir("/uploads");
//   while (dir.next()) {
//     fileList += "/" + dir.fileName() + "<br>"; // Include forward slash
//   }
//   server.send(200, "text/html", fileList);
// }
void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("ESP8266 IP Address: ");
  Serial.println(WiFi.localIP());

  if (!SPIFFS.begin()) {
    Serial.println("Error initializing SPIFFS");
    return;
  }
  Serial.println("SPIFFS initialized");

  getPublicIP();  // Get the public IP address

  server.on("/", handleRoot);
  server.on("/form", handleForm);
  server.on("/submit", handleSubmit);
  // server.on("/sack", handleSack);
  server.on("/data", handleData);
  server.on("/viewdata", handleViewData);
  server.on("/delete", handleDeleteData);
  server.on("/storage", handleStorage);
  // server.on("/upload", HTTP_POST, handleUpload);
  // server.on("/list", handleFileList);


  server.begin();
  Serial.println("Server started");
}



void loop() {
  server.handleClient();
}
