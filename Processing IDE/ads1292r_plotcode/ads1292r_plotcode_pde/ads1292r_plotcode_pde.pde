import grafica.*;
import processing.serial.*;

Serial myPort;           // Create a Serial object to communicate with Arduino
float[] ecgData = new float[500];  // Buffer to store ECG values for plotting
int index = 0;

GPlot plot;

void setup() {
  size(800, 400);            // Size of the processing window
  
  // Initialize the Serial object to the port Arduino is connected to
  String portName = Serial.list()[0];   // Get the first available port (change this if needed)
  myPort = new Serial(this, portName, 57600);
  
  // Initialize the plot settings for ECG data
  plot = new GPlot(this);
  plot.setPos(25, 25);                // Set position of the plot on the window
  plot.setDim(750, 350);              // Set the size of the plot
  plot.setTitleText("ECG Signal from ADS1292R");  // Title for the graph
  plot.getXAxis().setAxisLabelText("Samples");
  plot.getYAxis().setAxisLabelText("Amplitude");
  
  plot.getXAxis().setNTicks(10);      // Number of ticks on the x-axis
  plot.getYAxis().setNTicks(10);      // Number of ticks on the y-axis
}

void draw() {
  background(255);    // White background
  plot.beginDraw();
  
  // Check if there's any data available from the serial port
  while (myPort.available() > 0) {
    // Read incoming data from Arduino
    String ecgValue = myPort.readStringUntil('\n');  // Read until new line
    
    if (ecgValue != null) {
      ecgValue = trim(ecgValue);  // Trim any extra whitespace
      float ecgFloat = float(ecgValue);  // Convert the string to a float
      
      // Add the ECG value to the buffer and shift the previous values
      if (index < ecgData.length) {
        ecgData[index] = ecgFloat;  // Store the ECG value
        index++;
      } else {
        // Shift the buffer left to make space for new data (FIFO buffer)
        for (int i = 0; i < ecgData.length - 1; i++) {
          ecgData[i] = ecgData[i + 1];
        }
        ecgData[ecgData.length - 1] = ecgFloat;
      }
    }
  }

  // Plot the ECG data
  plot.setPoints(createGraphPoints(ecgData));  // Update the plot with the latest ECG data
  plot.endDraw();
}

// Convert the ECG data into the format needed by Grafica plot
GPointsArray createGraphPoints(float[] data) {
  GPointsArray points = new GPointsArray(data.length);
  for (int i = 0; i < data.length; i++) {
    points.add(i, data[i]);
  }
  return points;
}
