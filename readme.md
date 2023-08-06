# PicoSack - A Portable Web Server for ESP8266

PicoSack is a lightweight and versatile web server solution designed for ESP8266-based IoT devices. With PicoSack, you can easily create a web interface to interact with your ESP8266 microcontroller and manage files, data, and more.

## Features

- **Web Interface:** PicoSack provides a user-friendly web interface that allows you to upload and manage files, view data, and monitor storage.

- **File Upload:** Upload files to your ESP8266 device using the web interface. PicoSack organizes and stores these files securely.

- **Data Handling:** Collect and handle data submitted through web forms, enabling efficient data management for your IoT projects.

- **Storage Monitoring:** Monitor the usage of your ESP8266's storage, providing insights into available space and usage.

## Getting Started

To use PicoSack, follow these steps:

1. Connect your ESP8266 to your Wi-Fi network using the provided `ssid` and `password` in the code.

2. Upload the code to your ESP8266 using the Arduino IDE or your preferred development environment.

3. Access the PicoSack web interface by navigating to the IP address of your ESP8266 in a web browser.

4. Use the web interface to upload files, handle data, and monitor storage.

## Examples

- Uploading a File: Easily upload files to your ESP8266 and access them via the provided links.

- Handling Data: Collect user data through web forms and process it for your IoT applications.

- Storage Monitoring: Get insights into your ESP8266's storage usage to ensure efficient data management.

## Dependencies

PicoSack utilizes the following libraries:

- ESP8266WiFi: Establish Wi-Fi connectivity.
- ESP8266WebServer: Handle web server functionality.
- FS: Manage the file system on your ESP8266.
- ESP8266HTTPClient: Perform HTTP requests.
- WiFiClientSecure: Enable secure connections.
- Pico: Included header file containing HTML code for the web interface.

## Contributing

PicoSack welcomes contributions from the community. Feel free to submit pull requests, report issues, or provide feedback. Please refer to our [Contributing Guidelines](CONTRIBUTING.md) for more information.

## License

PicoSack is released under the [MIT License](LICENSE).

---

For more information and detailed usage instructions, please refer to the [documentation](docs/README.md).

Follow [@digital_hokage](https://www.instagram.com/digital_hokage/) on Instagram for updates and insights.
