import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import sys

def main():
    
    # loading data
    time, value = load_data()

    # filtering data below the threshold
    time, value = preprocess(time, value, threshold = 20)

    # plot the data
    plt.scatter(time, value)
    plt.show()

    # splitting data into packets/bins    
    #T = 175.2 # T caculated from data7.csv using: 
    T = 170
    n = round((time[-1] - time[0]) / T) # number of bins
    print(T)
    print(n)

    bits = split_into_bins(time, value, n, T = T)
    
    # print sums of bit
    for bit in bits:
        print(sum(bit))

    
    # decoding bins
    binary = decode_bins_to_binary(bits, threshold = 1000)
    print(f'binary received: {binary}')

    binary = binary[1:-1] # excluding the first and the last bits

    # convert binary to text
    text = binary_to_text(binary)
    print(f'text received: {text}')
    

                


def decode_bins_to_binary(bits, threshold = 1000):
    binary = ''
    for bit in bits:
        if sum(bit) > threshold:
            binary += '1'
        else:
            binary += '0'
    return binary


def split_into_bins(time, value, n, T = 175.2):
    i = 0
    bits = []
    thresholds = [time[0] + (i+1) * T for i in range(n-1)] # list of upper limit of bins except the last bin
    print(thresholds)
    for threshold in thresholds:
        bit = []
        while True:
            if time[i] < threshold:
                bit.append(value[i])
                i += 1
            else:
                break
        bits.append(bit)
    bits.append(time[i:]) 
    return bits
    
def preprocess(time, value, threshold = 4):
    value = [i if i > threshold else 0 for i in value]

    # seaching for first non-zero
    for i in range(len(value)):
        if value[i] != 0:
            starting_index = i
            break
    # slicing the data 
    time = time[starting_index:]
    value = value[starting_index:]

    # searching for fisrt non-zero backwards
    for i in range(len(value)):
        if value[len(value) - 1 -i] != 0:
            ending_index = len(value) - 1 -i
            break
    # slicing the data
    time = time[:ending_index]
    value = value[:ending_index]
    return time, value

def load_data():
    dataframe = pd.read_csv('data/' + sys.argv[1])
    time = [float(i) for i in dataframe['time']]
    value = [float(i) for i in dataframe['value']]
    return time, value
    
def binary_to_text(binary):
    binary_list = [binary[i:i+8] for i in range(0, len(binary), 8)]
    text = ""
    for binary in binary_list:
        decimal = int(binary, 2)
        character = chr(decimal)
        text += character
    return text

def time_plot(data):
    plt.scatter(np.linspace(0, len(data), len(data)), data)   
    plt.ylabel('data')
    plt.show()

def filter_signal(signal, fs, f0, f1):
    n = len(signal)
    frequencies = np.fft.fftfreq(n, 1/fs)
    spectrum = np.fft.fft(signal)
    plt.plot(frequencies, np.abs(spectrum))
    plt.show()
    #spectrum[(frequencies < 100)] = 0
    spectrum[(frequencies < f0 ) | (frequencies > f1 )] = 0
    plt.plot(frequencies, np.abs(spectrum))
    plt.axis([5e5, 4e8, 0,2000000])
    plt.show()
    filtered_signal = np.real(np.fft.ifft(spectrum))
    return filtered_signal

if __name__ == '__main__':
    if len(sys.argv) > 2:
        sys.exit("Usage: python decode.py [data file name]")
    main()