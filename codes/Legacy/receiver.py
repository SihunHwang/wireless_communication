import serial
from serial import Serial
import serial.tools.list_ports
import time
import csv
import pandas as pd
import numpy as np



arduino = serial.Serial(port='COM7', baudrate=6e6, timeout=.1)

# Create CSV file
f = open("data.csv","w",newline='')
f.truncate()

# Toggle DTR to reset the Arduino
arduino.setDTR(False)
time.sleep(1)
arduino.flushInput()
arduino.setDTR(True)

for i in range(int(60 * 9600)):
    # Read the line
    bytes = arduino.readline()
    decoded_bytes = bytes.decode("utf-16").strip()
    # print(decoded_bytes)

    values = [float(x) for x in decoded_bytes.split()]
    #print(values)

    # Write to CSV
    writer = csv.writer(f,delimiter=",")
    writer.writerow(values)

f.close()





'''
#decoding
data = np.genfromtxt('data.csv', delimiter=',')
#print(data)

binary = ''
last_row = []
for row in data:

    if last_row == row:
        continue
    if row[0] == row[1]:
        print('errer: signal on both pins')
        continue
    
    if row[0] == 1:
        binary += '0'
    elif row[1] == 1:
        binary += '1'

    last_row = row

# Split the binary string into 8-bit chunks
binary_chunks = [binary[i:i+8] for i in range(0, len(binary), 8)]

# Convert each 8-bit chunk to text character
text = ''.join([chr(int(chunk, 2)) for chunk in binary_chunks])

print(f'text sent: {text}')
'''
        
