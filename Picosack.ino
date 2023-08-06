#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include "Pico.h"  //header file containing HTML code
const char* ssid = "Picosack";
const char* password = "12345678";


ESP8266WebServer server(80);


String getPublicIP() {
  WiFiClient client;
  HTTPClient http;

  if (!client.connect("api64.ipify.org", 80)) {
    Serial.println("Connection failed");
    return "";
  }

  http.begin(client, "http://api64.ipify.org");
  int httpCode = http.GET();

  String publicIP = "";

  if (httpCode == HTTP_CODE_OK) {
    publicIP = http.getString();
  } else {
    Serial.printf("Failed to get public IP, error code: %d\n", httpCode);
  }

  http.end();
  return publicIP;
}


void handleRoot() {
  server.send(200, "text/html", html);  //send HTML page to web browser of client
}

String uploadedName;
String uploadedEmail;
String uploadedFilename;

void handleForm() {
  String html = "<html><head>";
  // Include Tailwind CSS from CDN
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<link href='https://cdn.jsdelivr.net/npm/tailwindcss@2.2.19/dist/tailwind.min.css' rel='stylesheet'>";
  html += "</head><body class='bg-gray-100 flex flex-col items-center justify-center min-h-screen'>";
  html += "<div class='container mx-auto bg-white rounded-lg shadow-lg p-8 sm:w-96'>";
  html += "<h1 class='text-3xl font-bold mb-4 text-center'>PicoSack - A Portable Web Server</h1>";
  html += "<p class='mb-4'>Welcome to PicoSack, a lightweight web server running on an ESP8266 microcontroller. You can upload files and access them using the links below.</p>";
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


void handleUpload() {
  if (server.uri() != "/upload")
    return;

  HTTPUpload& upload = server.upload();
  uploadedName = "";
  uploadedEmail = "";
  uploadedFilename = "";

  // Get the name and email from the form fields
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i) == "name") {
      uploadedName = server.arg(i);
    } else if (server.argName(i) == "email") {
      uploadedEmail = server.arg(i);
    }
  }

  // Handle the file upload
  if (upload.status == UPLOAD_FILE_START) {
    uploadedFilename = upload.filename;
    String filename = "/uploads/" + uploadedFilename;
    fs::File file = SPIFFS.open(filename, "w");
    if (!file) {
      Serial.println("Error opening file for writing");
      return;
    }
    Serial.print("Uploading file: ");
    Serial.println(filename);
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    String filename = "/uploads/" + uploadedFilename;
    fs::File file = SPIFFS.open(filename, "a");
    if (file) {
      file.write(upload.buf, upload.currentSize);
      file.close();
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    Serial.println("File upload finished successfully!");

    // Save the data to the CSV file
    String dataLine = uploadedName + "," + uploadedEmail + "," + uploadedFilename + "," + getPublicIP() + "\n";
    fs::File dataFile = SPIFFS.open("/data.csv", "a");
    if (dataFile) {
      dataFile.print(dataLine);
      dataFile.close();
    }
    // Send a success message to the client
    String html = "<html><head>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    html += "<link href='https://cdn.jsdelivr.net/npm/tailwindcss@2.2.19/dist/tailwind.min.css' rel='stylesheet'>";
    html += "</head><body class='bg-gray-100 flex flex-col items-center justify-center min-h-screen'>";
    html += "<div class='container mx-auto bg-white rounded-lg shadow-lg p-8 sm:w-96'>";
    html += "<h1 class='text-3xl font-bold mb-4 text-center'>PicoSack - Upload File</h1>";
    html += "<p class='mb-4'>Form submitted successfully!</p>";
    html += "<a href='/'>Back to Home</a>";
    html += "</div>";
    html += "</body></html>";
    server.send(200, "text/html", html);
  }
}


void handleData() {
  String html = "<html><head>";
  // Include Tailwind CSS from CDN
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<link href='https://cdn.jsdelivr.net/npm/tailwindcss@2.2.19/dist/tailwind.min.css' rel='stylesheet'>";
  html += "</head><body class='bg-gray-100 flex flex-col items-center justify-center min-h-screen'>";
  html += "<div class='container mx-auto bg-white rounded-lg shadow-lg p-8 sm:w-96'>";
  html += "<h1 class='text-3xl font-bold mb-4 text-center'>PicoSack - Handle Data</h1>";
  html += "<p class='mb-4'>Name: " + uploadedName + "</p>";
  html += "<p class='mb-4'>Email: " + uploadedEmail + "</p>";
  html += "<p class='mb-4'>Uploaded File: " + uploadedFilename + "</p>";
  html += "<a href='/'>Back to Home</a>";
  html += "</div>";
  html += "</body></html>";
  server.send(200, "text/html", html);
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



void handleViewData() {
  String html = "<!DOCTYPE html><html><head><title>PicoSack - Uploaded Data</title>";
  html += "<link rel='stylesheet' href='https://cdn.jsdelivr.net/npm/tailwindcss@2.2.19/dist/tailwind.min.css'>";
  html += "</head><body class='bg-gray-100'>";

  // Navigation bar
  html += "<nav class='bg-blue-600 py-3 text-white'><div class='container mx-auto px-4'>";
  html += "<span class='text-xl font-bold'>PicoSack</span>";
  html += "<a href='/' class='float-right'>Home</a>";
  html += "</div></nav>";

  // Data table
  html += "<div class='container mx-auto mt-6 px-4'>";
  html += "<h2 class='text-2xl font-bold mb-4'>Uploaded Data</h2>";
  html += "<div class='overflow-x-auto'>";
  html += "<table class='table-auto border-collapse border w-full'>";
  html += "<thead><tr><th class='border px-4 py-2 bg-blue-100'>Name</th>";
  html += "<th class='border px-4 py-2 bg-blue-100'>Email</th>";
  html += "<th class='border px-4 py-2 bg-blue-100'>Filename</th>";
  html += "<th class='border px-4 py-2 bg-blue-100'>Public IP</th></tr></thead><tbody>";

  fs::File dataFile = SPIFFS.open("/data.csv", "r");
  if (dataFile) {
    while (dataFile.available()) {
      String line = dataFile.readStringUntil('\n');
      html += "<tr>";
      int index = 0;
      while (index < line.length()) {
        int nextIndex = line.indexOf(",", index);
        if (nextIndex == -1)
          nextIndex = line.length();
        String cellValue = line.substring(index, nextIndex);
        html += "<td class='border px-4 py-2'>" + cellValue + "</td>";
        index = nextIndex + 1;
      }
      html += "</tr>";
    }
    dataFile.close();
  } else {
    html += "<tr><td class='border px-4 py-2' colspan='4'>Data file not found or unable to open.</td></tr>";
  }

  html += "</tbody></table></div></div></body></html>";
  server.send(200, "text/html", html);
}


void handleDeleteData() {
  if (server.method() == HTTP_POST) {
    // Delete data.csv
    if (SPIFFS.exists("/data.csv")) {
      SPIFFS.remove("/data.csv");
      Serial.println("data.csv deleted");
    }

    // Delete uploaded files
    Dir dir = SPIFFS.openDir("/uploads");
    while (dir.next()) {
      SPIFFS.remove(dir.fileName());
      Serial.println("Deleted: " + dir.fileName());
    }

    // Re-create the data.csv file
    fs::File dataFile = SPIFFS.open("/data.csv", "w");
    if (dataFile) {
      dataFile.println("Name,Email,Filename,Public IP");
      dataFile.close();
    }

    server.send(200, "text/html", "Data deleted successfully.<br><a href='/'>Back to Home</a>");
  } else {
    String html = "<html><head>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    html += "<link href='https://cdn.jsdelivr.net/npm/tailwindcss@2.2.19/dist/tailwind.min.css' rel='stylesheet'>";
    html += "</head><body class='bg-gray-100 flex flex-col items-center justify-center min-h-screen'>";
    html += "<div class='container mx-auto bg-white rounded-lg shadow-lg p-8 sm:w-96'>";
    html += "<h2 class='text-2xl font-bold mt-8 mb-4'>Delete Data</h2>";
    html += "<p class='mb-4'>Are you sure you want to delete all stored data?</p>";
    html += "<form method='POST' action='/deletedata'>";
    html += "<button type='submit' class='bg-red-500 text-white px-4 py-2 rounded'>Delete Data</button>";
    html += "</form>";
    html += "<a href='/'>Back to Home</a>";
    html += "</div>";
    html += "</body></html>";
    server.send(200, "text/html", html);
  }
}






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

  // Create the "uploads" directory if it doesn't exist
  if (!SPIFFS.exists("/uploads")) {
    SPIFFS.mkdir("/uploads");
  }

  // Create the "data.csv" file if it doesn't exist
  if (!SPIFFS.exists("/data.csv")) {
    fs::File dataFile = SPIFFS.open("/data.csv", "w");
    if (dataFile) {
      dataFile.println("Name,Email,Filename,Public IP");
      dataFile.close();
    }
  }

  server.on("/", handleRoot);
  server.on("/form", handleForm);
  server.on("/data", handleData);
  server.on("/viewdata", handleViewData);
  server.on("/storage", handleStorage);
  server.on("/upload", HTTP_POST, handleUpload);
  server.on("/deletedata", HTTP_GET, handleDeleteData);
  server.on("/deletedata", HTTP_POST, handleDeleteData);


  server.begin();
  Serial.println("Server started");
}




void loop() {
  server.handleClient();
}
