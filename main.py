import csv
import random
import numpy
import matplotlib.pyplot as plt

x1 = []
y1 = []

x2 = []
y2 = []

x3 = []
y3 = []


with open('/Users/darina/CLionProjects/untitled/tabu.csv','rt') as file_tabu:
    plots = csv.reader(file_tabu, delimiter=' ')
    for row in plots:
        x1.append(int(row[0]))
        y1.append(int(row[1]) - int(row[2]) - int(row[3]))
with open('/Users/darina/CLionProjects/untitled/goal.csv','rt') as file_goal:
    plots = csv.reader(file_goal, delimiter=' ')
    for row in plots:
        x2.append(int(row[0]))
        y2.append(int(row[1]) - int(row[2]) - int(row[3]))
with open('/Users/darina/CLionProjects/untitled/hill.csv','rt') as file_hill:
    plots = csv.reader(file_hill, delimiter=' ')
    for row in plots:
        x3.append(int(row[0]))
        y3.append(int(row[1]) - int(row[2]) - int(row[3]))

plt.plot(x1, y1, ':r', color='green', label="tabu")
plt.plot(x2, y2, ':r', color='crimson', label="goal")
plt.plot(x3, y3, ':r', color='aqua', label="hill")
plt.xlabel('i')
plt.ylabel('val')
plt.legend()
plt.show()
