import serial
from matplotlib.animation import FuncAnimation
import matplotlib.pyplot as plt
import numpy as np
from scipy.signal import butter ,filtfilt

arduino = serial.Serial(port='COM4',baudrate=9600,timeout=1)


y_values =[]

def apply_ecg_filter(data,lowcut=0.5,highcut=50.0,fs=250.0,order=2):
    nyquist = 0.5 * fs
    low = lowcut/nyquist
    high= highcut/nyquist
    b,a = butter (order,[low,high] ,btype='band')
    return filtfilt(b,a,data)

def update(frame):
    arduino_data = arduino.readline().decode('utf-8').strip()

    try:
        
        value = float(arduino_data)
        y_values.append(value)

        if len(y_values)>500:
            y_values.pop(0)
        
        if len(y_values) > 50:
            ecg_signal = apply_ecg_filter(np.array(y_values),lowcut=0.5,highcut=50.0,fs=250.0)
        else:
            ecg_signal = np.array(y_values)
        
        plt.clf()
        x_values = list(range(len(ecg_signal)))
        plt.plot(x_values,ecg_signal,color='blue')
        plt.ylim([-2,2])
        plt.grid()

    except ValueError:
        print(f"Invalid data:{arduino_data}")

ani = FuncAnimation(plt.gcf(),update,interval=10)

plt.show()