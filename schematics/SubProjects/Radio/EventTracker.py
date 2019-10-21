#This is an event tracker that prepares messages to be pushed over radio

class Event():
    def __init__(self, dType, data):
        self.dType = dType
        self.data = data


class EventController():
    def __init__(self, period, t_break):
        self.period = period
        self.t_break = t_break

    def run(self):
        run = True
        while run:
            break


def main():
    print("Not much here... ideas mostly")


if __name__ == '__main__':
    main()
