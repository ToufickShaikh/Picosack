# Installing and Using Picosack in Arduino IDE

Picosack is a portable web server designed for IoT devices using the ESP8266 microcontroller. This guide will walk you through the installation process and show you how to use Picosack in the Arduino IDE.

## Prerequisites

Before you begin, ensure you have the following prerequisites:

1. **Arduino IDE:** Make sure you have the latest version of the Arduino IDE installed on your computer. You can download it from the official Arduino website: https://www.arduino.cc/en/software

2. **ESP8266 Board Package:** To program the ESP8266 microcontroller, you need to install the ESP8266 board package in Arduino IDE. Follow these steps to install it:

   - Open Arduino IDE and go to **File** > **Preferences**.
   - In the Additional Boards Manager URLs field, enter the following URL and click **OK**:
     ```
     http://arduino.esp8266.com/stable/package_esp8266com_index.json
     ```
   - Go to **Tools** > **Board** > **Boards Manager**.
   - Search for "esp8266" and install the board package by **ESP8266 Community**.

## Installation

To install Picosack, follow these steps:

1. Clone the Picosack repository to your computer:

   ```
   git clone https://github.com/Toufick190/picosack.git
   ```

2. Open the Arduino IDE.

3. Go to **Sketch** > **Include Library** > **Add .ZIP Library**.

4. Navigate to the location where you cloned the Picosack repository and select the `picosack.zip` file. Click **Open**.

5. Picosack is now installed in your Arduino IDE.

## Usage

Now that you have installed Picosack, you can use it in your Arduino projects. Follow these steps to get started:

1. Open the Arduino IDE.

2. Go to **File** > **Examples** > **Picosack**.

3. Choose one of the examples provided to get started. These examples demonstrate various functionalities of Picosack, such as serving static files, handling HTTP requests, and more.

4. Connect your ESP8266 board to your computer via USB.

5. Go to **Tools** > **Board** and select the appropriate ESP8266 board variant you are using.

6. Go to **Tools** > **Port** and select the port where your ESP8266 board is connected.

7. Compile and upload the selected example to your ESP8266 board by clicking the right-arrow icon (or **Sketch** > **Upload**).

8. Once the upload is successful, open the Serial Monitor (Tools > Serial Monitor) to view the IP address assigned to your ESP8266 board.

9. Open a web browser and enter the IP address. You should see the web page served by Picosack.

10. Congratulations! You have successfully installed and used Picosack in your Arduino IDE.

## Troubleshooting

- If you encounter any issues during installation or usage, please refer to the [Picosack documentation](docs/) for troubleshooting tips and FAQs.

## Support

If you have any questions or need assistance, feel free to [create an issue](https://github.com/Toufick190/picosack/issues) on GitHub.

## Contributing

We welcome contributions to improve Picosack and make it even better. Please follow the guidelines in the [contribution guidelines](CONTRIBUTING.md) if you wish to contribute.

---
# Flashing Picosack Directly to ESP8266

In addition to using the Arduino IDE, you can also flash Picosack directly to the ESP8266 microcontroller using the ESP8266 Flash Download Tool (ESPFlashDownloadTool).

## Prerequisites

Before you begin, ensure you have the following prerequisites:

1. **ESP8266 Flash Download Tool:** Download the ESP8266 Flash Download Tool from the official Espressif website: https://www.espressif.com/en/support/download/other-tools

2. **Picosack Binary:** Obtain the compiled binary of Picosack specific to your ESP8266 board variant. This binary is typically provided in the `bin` directory of the Picosack repository or downloadable from the project's release section.

## Flashing Picosack

Follow these steps to flash Picosack directly to your ESP8266:

1. Connect your ESP8266 board to your computer via USB.

2. Open the ESP8266 Flash Download Tool (ESPFlashDownloadTool).

3. Configure the Flash Download Tool settings as follows:

   - **SPI Speed:** Typically, you can use the default SPI speed for most ESP8266 boards.
   - **SPI Mode:** Choose the appropriate SPI mode supported by your ESP8266 board (usually Mode QIO).
   - **Flash Size:** Select the flash size of your ESP8266 board (e.g., 4MB).
   - **COM Port:** Select the COM port to which your ESP8266 board is connected.

4. Click the "ESP8266 DownloadTool" button in the tool.

5. In the "Config" tab, select the appropriate addresses for the following sections:

   - **Boot Mode:** Choose the boot mode appropriate for your board (e.g., QIO, DIO).
   - **User1:** Set this address to the location of the Picosack binary.

6. In the "Download Path" section, browse and select the Picosack binary file.

7. Power on your ESP8266 board while holding down the appropriate boot button (e.g., GPIO0). This puts the board into programming mode.

8. Click the "Start" button in the Flash Download Tool to begin flashing the binary to your ESP8266.

9. The Flash Download Tool will display progress as it flashes the binary to your ESP8266.

10. Once the flashing process is complete, power off the ESP8266 board, remove it from programming mode, and power it back on.

11. Picosack is now flashed directly to your ESP8266, and your board is ready to serve web pages.

## Troubleshooting

- If you encounter any issues during the flashing process, double-check the Flash Download Tool settings and the connection between your ESP8266 board and computer.

- Ensure that you have selected the correct binary file specific to your ESP8266 board variant.

## Support

If you have any questions or need assistance, feel free to [create an issue](https://github.com/Toufick190/picosack/issues) on GitHub.

## Contributing

We welcome contributions to improve Picosack and make it even better. Please follow the guidelines in the [contribution guidelines](CONTRIBUTING.md) if you wish to contribute.

---
