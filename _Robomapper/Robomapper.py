#Robomapper python file
import DeejMapper
import serial
import os
ser = serial.Serial('/dev/ttyUSB0', 9600)

def cleanInput(msg):
    return (msg.decode())[0:len(msg.decode())-2]

#Create visual map
wid = 800; height = 600; scale = 50;
gDisp = pygame.display.set_mode((wid,height), 0, 16)
pygame.display.set_caption('mapper yes')
gclock = pygame.time.Clock()
startX = 0; startY = 0;

maxWidth = 15
maxHeight = 11
botMap = LimMap(maxWidth, maxHeight, scale)

temp = VisualMap(wid, height, scale, botMap)
temp.worldMap.map[startY][startX] = 3
temp.genBarriers()
temp.createRobot(startX,startY)

myRobot = Robot(scale)

readData = []
sendData = []
dataFileName = "lastRuntimeSave"
sensorData = "lastRunSensorData"
sensorFile = open(sensorData, "a")
botMap.saveMap(dataFileName)
while True:
    for x in range(8):
        readData.append(cleanInput(ser.readline()))



    for x in range(len(readData)):
        print(readData[x])
        recieved = readData[x]
        if recieved[0] == "0":
            frontDist = recieved[1:]
        elif recieved[1] == "1":
            rearDist = recieved[1:]
        elif recieved[2] == "2":
            leftDist = recieved[1:]
        elif recieved[3] == "3":
            rightDist = recieved[1:]
        elif recieved[4] == "4":
            temp = recieved[1:]
        elif recieved[5] == "5":
            humidity = recieved[1:]
        elif recieved[6] == "6":
            robotAngle = recieved[1:]
        elif recieved[7] == "7":
            wet = recieved[1:]
        elif recieved[8] == "8":
            mode = recieved[1:]

    if wkey:
        newmap = myRobot.move(0, -1, botMap.map)
        #make the robot actually move
        sendData.append()
        botMap.updateMap(newmap)
        botMap.saveMap(dataFileName)
    if skey:
        newmap = myRobot.move(0, 1, botMap.map)
        botMap.updateMap(newmap)
        sendData.append()
        botMap.saveMap(dataFileName)
    if dkey:
        newmap = myRobot.move(1, 0, botMap.map)
        botMap.updateMap(newmap)
        sendData.append()
        botMap.saveMap(dataFileName)
    if akey:
        newmap = myRobot.move(-1, 0, botMap.map)
        botMap.updateMap(newmap)
        sendData.append()
        botMap.saveMap(dataFileName)

    wkey = False;skey =False;dkey= False;akey= False



    #Reset robot position and tiles seen by robot
    #Update the visual map?
    temp.update(botMap)
    #blah blah
    gDisp.fill(BLACK)
    temp.render(gDisp)
    pygame.display.flip()
    gclock.tick(60)

pygame.quit()
print(botMap.map)
