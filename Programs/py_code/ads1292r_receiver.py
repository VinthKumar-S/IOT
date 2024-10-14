import serial
import time
import matplotlib.pyplot as plt
import numpy as np

arduino = serial.Serial(port='COM4',baudrate=9600,timeout=1)

def plot_init():
    plt.ion()
    fig, ax = plt.subplots(figsize=(16,8))
    ax.set_ylim(400,700)
    ax.set_xlabel("Time (s)")
    ax.set_ylabel("ECG/Respiration Value")
    return fig,ax

def read_and_plot():
    fig,ax = plot_init()
    time_values = []
    ecg_values = []

    start_time = time.time()
    while True:
        try:
            arduino_data = arduino.readline().decode('utf-8').strip()
            if arduino_data:
                print(arduino_data)

                parts = arduino_data.split(":")
                if len(parts) == 2:
                    try:
                        ecg_values = float(parts[1])

                        elaspsed_time = time.time() - start_time
                        time_values.append(elaspsed_time)
                        ecg_values.append(ecg_values)

                        ax.clear()
                        ax.plot(time_value,ecg_value,label='ECG/Respiration')
                        ax.legend()
                        ax.set_ylim(400,700)
                        ax.set_xlabel("Time (s)")
                        ax.set_ylabel("ECG/Respiration Value")
                        plt.pause(0.1)
                    except ValueError:
                        print("Format Error")
        except serial.SerialException:
            print("Device connection lossed")

            try:
                arduino.close()
            except serial.SerialException:
                print("Unnable to connect")
                break
        except KeyboardInterrupt:
            print('Plotting stopped')
            break
    arduino.close()

if __name__ == '__main__':
    read_and_plot()