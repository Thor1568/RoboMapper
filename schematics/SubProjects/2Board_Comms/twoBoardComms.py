import RPi.GPIO as io

io.setmode(io.BCM)
msgChnl = 4
LEDPIN = 5
io.setup(msgChnl, io.IN)


def sendMsg(binArr, period, msgBreak, channel):
    io.setup(channel, io.OUT)
    for msgBreak in period:
        pass
    #
    for x in range(len(binArr)):
        if binArr[x] == 1:
            io.output(msgChnl, io.HIGH)
        else:
            io.output(msgChnl, io.LOW)

def reciveMsg(period, msgBreak, channel):
    io.setup(channel, io.IN)
    binArr = []
    for msgBreak in period:
        binArr += io.input(channel)
    return binArr


def main():
    io.setup(LEDPIN, io.OUT, initial=io.HIGH)
    for x in range(200):
        pass

    io.cleanup()





if __name__ == '__main__':
    main()
