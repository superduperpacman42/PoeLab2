#!/usr/local/bin/python

from serial import Serial, SerialException
import csv
cxn = Serial('COM5', baudrate=9600)

begin = False
data = []
while(True):
    try:
        while cxn.inWaiting() < 1:
            pass
        result = cxn.readline();
        result = str(result)[2:-5]
        point = result.split(",")
        point = list(map(lambda x:float(x), point))
        if point[0] == -85:
            begin = True
        if begin:
            datapoint = str(point).replace("[","").replace("]","")
            print(datapoint)
            data = data + [datapoint]
            if point[0] == 84:
                break
    except ValueError:
        print ("You are a failure")
print(data)
with open("POE Lab 2 Data.csv", "w") as file:
    writer = csv.writer(file, quoting = csv.QUOTE_NONE,escapechar=' ')
    writer.writerow(data)
print("You are a success")
