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
   String html = "<html><head>";
  // Include Tailwind CSS from CDN
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<link href='https://cdn.jsdelivr.net/npm/tailwindcss@2.2.19/dist/tailwind.min.css' rel='stylesheet'>";
  html += "</head><body class='bg-gray-100 flex flex-col items-center justify-center min-h-screen'>";
  html += "<div class='container mx-auto bg-white rounded-lg shadow-lg p-8 sm:w-96'>";
  html += "<h1 class='text-3xl font-bold mb-4 text-center'>PicoSack - A Portable Server</h1>";
  html += "<p class='mb-4'>Welcome to PicoSack, a lightweight server running on an ESP8266 microcontroller. You can upload files and access them using the links below.</p>";
  html += "<form method='POST' action='/upload' enctype='multipart/form-data'>";
  html += "<input type='file' name='file' class='mb-4 w-full'><br>";
  html += "<label class='block mb-2 font-bold' for='name'>Name:</label>";
  html += "<input type='text' name='name' id='name' class='mb-4 w-full p-2 border rounded'>";
  html += "<label class='block mb-2 font-bold' for='email'>Email:</label>";
  html += "<input type='email' name='email' id='email' class='mb-4 w-full p-2 border rounded'>";
  html += "<button type='submit' class='bg-green-500 text-white px-4 py-2 rounded w-full'>Upload</button>";
  html += "</form>";
  html += "<h2 class='text-2xl font-bold mt-8 mb-4'>Uploaded Files</h2>";
  html += "<ul>";
  Dir dir = SPIFFS.openDir("/uploads");
  while (dir.next()) {
    html += "<li class='mb-2'><a href='/uploads/" + dir.fileName() + "' class='text-blue-500 hover:underline'>" + dir.fileName() + "</a></li>";
  }
  html += "</ul>";
  html += "</div>";
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
  String html = "<html><head>";
  // Include Tailwind CSS from CDN
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<link href='https://cdn.jsdelivr.net/npm/tailwindcss@2.2.19/dist/tailwind.min.css' rel='stylesheet'>";
  html += "</head><body class='bg-gray-100 flex flex-col items-center justify-center min-h-screen'>";
  html += "<div class='container mx-auto bg-white rounded-lg shadow-lg p-8 sm:w-96'>";
  html += "<h2 class='text-2xl font-bold mt-8 mb-4'>Storage Information</h2>";
  fs::FSInfo fs_info;
  if (SPIFFS.info(fs_info)) {
    float totalMB = fs_info.totalBytes / (1024.0 * 1024.0);
    float usedMB = fs_info.usedBytes / (1024.0 * 1024.0);
    float freeMB = (fs_info.totalBytes - fs_info.usedBytes) / (1024.0 * 1024.0);

    html += "<p class='mb-4'>Total Storage: <span class='font-bold'>" + String(totalMB, 3) + " MB</span></p>";
    html += "<p class='mb-4'>Used Storage: <span class='font-bold'>" + String(usedMB, 3) + " MB</span></p>";
    html += "<p class='mb-4'>Free Storage: <span class='font-bold'>" + String(freeMB, 3) + " MB</span></p>";
  } else {
    html += "<p class='text-red-500'>Error reading storage information!</p>";
  }
  html += "</div>";
  html += "</body></html>";
  server.send(200, "text/html", html);
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

void handleUpload() {
  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    String filename = "/uploads/" + upload.filename;
    fs::FSInfo fs_info;
    if (SPIFFS.info(fs_info)) {
      if (fs_info.totalBytes - fs_info.usedBytes < upload.totalSize) {
        server.send(200, "text/html", "Not enough space available to upload the file!");
        return;
      }
    }
    fs::File file = SPIFFS.open(filename, "w");
    if (!file) {
      server.send(200, "text/html", "Error opening file for writing!");
      return;
    }
    file.close();
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    String filename = "/uploads/" + upload.filename;
    fs::File file = SPIFFS.open(filename, "a");
    if (file) {
      file.write(upload.buf, upload.currentSize);
      file.close();
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    server.send(200, "text/html", "File uploaded successfully!");
  }
}

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
  server.on("/upload", HTTP_POST, handleUpload);
  // server.on("/list", handleFileList);


  server.begin();
  Serial.println("Server started");
}



void loop() {
  server.handleClient();
}
