## Creating a pyhton version of the GunAnalysis.cpp

import math
import  matplotlib.pyplot as plt

## Creating a class that takes pressures and lengths ona barrel of a rifle to calculate velocities and 
class RifleAnalysis:

	## List of local variables in the rifleAnalysis clas
	g = 9.8
	lengths = []
	pressures = []
	
	## Creating a constructor that will initialize the data
	def __init__(self, radius, mass, lengths, pressures):
		self.rad = float(radius)
		self.mass = float(mass)
		self.length = lengths
		self.press = pressures 

	## End of constructor



	## Creating a function that will calculate the area of the bullet
	def getArea(self):
		return math.pi * math.pow(self.rad,2)
	## End
	

	
	## Creating a fucntion that will calculate the velocity of the bullet coming out of the barrel of rifle
	def velocityFinal(self):
		totalEven = 0.0
		totalOdd = 0.0
		delta = self.length[0]
		area = math.pi * math.pow(self.rad,2)
		firstLastSum  = self.press[0] + self.press[len(self.press) - 1]
		gamma = 2 * delta * area / 3

		for index in range(1,len(self.press) - 1):
			if index % 2 == 0:
				totalEven += 2 * self.press[index]
			else:
				totalOdd += 4 * self.press[index]
		
		total = gamma * (firstLastSum + totalEven + totalOdd)
	
		## But since this is the velocity ** 2, we need to square root it
		total = math.sqrt(total)
		
		return total
	## End



	## Creating a function that will calculate the velocity between two data points
	## @param: index
	## @return: total velocity at that index
	def getVelocity(self,index):
		totalEven = 0
		totalOdd = 0
		delta = self.length[0]
		firstLastSum = self.press[0] + self.press[index - 1]
		area = math.pi * math.pow(self.rad,2)
		gamma = 2 * delta * area / 3
		
		for i in range(1,index - 1):
			if index % 2 == 0:
				totalEven += 2 * self.press[i]
			else:
				totalOdd += 4 * self.press[i]
		
		total = gamma * (firstLastSum + totalEven + totalOdd)
		
		## But since this is the velocity ** 2, we need to square root it
		total = math.sqrt(total)
		
		return total
	## End
	
	
	
	
	## Creating a function that will calculate the times at each point of the barrel of the rifle
	def getBarrelTimes(self, velocity):
		times = []
		
		for index in range(len(self.press)):
			if index == 0:
				times.append(self.length[0] / velocity[0])
			elif index + 1 > len(velocity) - 1:
				times.append( math.fabs((self.length[index] - self.length[index - 1])) / math.fabs((velocity[index] - velocity[index - 1])) )
			else:
				times.append( ( math.fabs((self.length[index + 1] - self.length[index])) / math.fabs((velocity[index + 1] - velocity[index])) ))
			
		return times
	## End
	
	
	
	
	## Creating a function that will calcualte the acceleration of the bullet in the barrel of the rifle
	def getAccelerations(self,index,velocity):
		if index - 1 < 0:
			return 0.5 * ( math.pow(velocity[index],2) / self.length[index] )
		elif index + 1 > len(self.press) -1 :
			return 0.5 * ( ( math.pow(velocity[index],2) -  math.pow(velocity[index-1],2) ) / (self.length[index] - self.length[index - 1]) )
		else:
			return 0.5 * ( ( math.pow(velocity[index + 1],2) - math.pow(velocity[index - 1],2 ) ) / (self.length[index + 1] - self.length[index - 1]) )
	## End
	
	
## End of rifleAnalysis Class





## Creaitng a class that will calcualte the trajectory of an object
class RifleTrajectory:
	
	## List of global variables 
	g = 9.8
	
	
	## Creating a constructor that will initialize the data
	def __init__(self,velocity,angle):
		self.vel = velocity
		self.angle = (math.pi * angle) / 180
	## End
	
	
	
	## Creating a function that will calculate the time to reach the max height
	def time(self):
		return ( self.vel * math.sin(self.angle) ) / self.g
	## End
	
	
	
	## Creating a fucntion that will calculate the max height of a trajectory
	def maxHeight(self):
		return (0.5 * math.pow(self.vel,2) * math.pow(math.sin(self.angle),2) ) / self.g
	## End
	
	
	
	## Creating a function that will calculate the range of a trajectory
	def rangeTraj(self):
		return math.pow(self.vel,2) * math.sin(2 * self.angle) / self.g
	## End
	
	
	
	## Creating a function that will calculate the coordinates in the x-direction
	def xCoord(self,time):
		return self.vel * math.cos(self.angle) * time
	## End
	
	## Creating a function that will calcaulte the coordinates in the y-direction
	def yCoord(self,time):
		return self.vel * math.sin(self.angle) * time - 0.5 * self.g * math.pow(time,2)
	## End
	
## End of the trajectoryAnalysis Class



##### Main ####
s = "/Users/jasonmora/Programs/C++/Gun-Analysis/GunDataCP.txt"
gunData = open(s,'r')

## Creates an empty list
A = []

## Reads in the data and adds to the list
for index in gunData:
	A.append(index.split())

lengths = []
pressuresOne = []
pressuresTwo = []

for i in range(len(A)):
	for j in range(len(A[i])):
		if j == 0:
			lengths.append(float(A[i][j]))
		elif j == 1:
			pressuresOne.append(float(A[i][j]) * math.pow(10,6))
		elif j == 2:
			pressuresTwo.append(float(A[i][j]) * math.pow(10,6))


## Creating the RifleAnalysis object
rifleOne = RifleAnalysis(1, .1, lengths, pressuresOne)
rifleTwo = RifleAnalysis(1, .1, lengths, pressuresTwo)


velocROne = []
velocRTwo = []

for index in range(len(pressuresOne)):
	velocROne.append(rifleOne.getVelocity(index))

for index in range(len(pressuresTwo)):
	velocRTwo.append(rifleTwo.getVelocity(index))


## Creating the TrajectoryAnalysis objects 
tracjectOne = RifleTrajectory(rifleOne.velocityFinal(), 45)
trajectTwo = RifleTrajectory(rifleTwo.velocityFinal(), 45)


## Generates a list of 10 seconds
times = [i for i in range(101)]

## Creating a loop that will enter the coordinates for the rifles
xCoordOne = []
xCoordTwo = []
yCoordOne = []
yCoordTwo = []

for index in times:
	## Adds the coordinates for the first rifle
	xCoordOne.append(tracjectOne.xCoord(index))
	yCoordOne.append(tracjectOne.yCoord(index))
	
	xCoordTwo.append(trajectTwo.xCoord(index))
	yCoordTwo.append(trajectTwo.yCoord(index))


## Creating a plot that will print the both rifle's trajectory
plt.subplot(4,2,1)
plt.plot(xCoordOne,yCoordOne,"b")
plt.title("Trajectory of Rifle One")
plt.xlabel("x")
plt.ylabel("y")

plt.subplot(4,2,2)
plt.plot(xCoordTwo,yCoordTwo,"r")
plt.title("Trajectory of Rifle Two")
plt.xlabel("x")
plt.ylabel("y")



## Creating graphs for the pressures inside both rifle's barrel 
plt.subplot(4,1,3)
plt.plot(lengths, pressuresOne, "b*")
plt.title("\nPressues vs Lengths")
plt.ylabel("Pressures of Rifle One")

plt.subplot(4,1,4)
plt.plot(lengths,pressuresTwo, "ro")
plt.ylabel("Pressures of Rifle Two")
plt.xlabel("Lengths of Barrel")

## Plots all of the graphs 
plt.show()