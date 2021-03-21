import matplotlib.pyplot as plt

x = [7, 11, 13, 19, 23, 31, 37]
y = [5229, 2216969, 14819233, 1360878045, 188898355755, 80554248332774, 2440483984772697]

plt.plot(x, y)

#plt.yscale("log")

plt.ylabel("# of operaions")
plt.xlabel("Size of field")
plt.show()
