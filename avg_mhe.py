import csv
import random
import numpy
import matplotlib.pyplot as plt

x1 = []
y1 = []
x2 = []
y2 = []

with open('f.txt') as file_tabu:
    plots = csv.reader(file_tabu, delimiter='\t')
    for row in plots:
        x1.append(float(row[0].replace(',', '.')))
with open('f.txt') as file_hill:
    plots = csv.reader(file_hill, delimiter='\t')
    for row in plots:
        x2.append(float(row[1].replace(',', '.')))


fig, (ax1, ax2) = plt.subplots(1, 2)
ax1.plot(x1, ':r', color='green', label="tabu")
ax2.plot(x2, ':r', color='red', label="hill")

ax1.legend()
ax2.legend()
plt.show()