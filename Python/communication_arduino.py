import PyCmdMessenger
from time import clock
from random import randint

class Communication ():
    def __init__(self):
        self.arduino = PyCmdMessenger.ArduinoBoard("/dev/ttyACM0",baud_rate=9600)

        #Initialize the commands
        self.commands = [['PING', ""],
                        ["SEND_MAX_CURRENT","ii"],
                        ['GET_STATUS',""],
                        ['GET_STATUS_RSP',"?????"], 
                        ["GET_DATA","i"],
                        ["GET_DATA_RSP","ffffff"],
                        ["STOP_TRANS","i"],
                        ["START_ALARM",""],
                        ["RSP_OK","s"],
                        ["RSP_ERR","s"]]


        # Initialize the messenger
        self.serial = PyCmdMessenger.CmdMessenger(self.arduino,self.commands)
        
    def pingArduino(self):
        self.serial.send("PING")
        startTime = clock()
        timeToWait = 0.5
        while(startTime + timeToWait > clock()):
            response = self.receive()
            if (response):
               break;
            
        if (reponse):    
            return (response[1])
        else:    
            return "COMM_ERR"

    def sendMaxCurrent(self, transNum, i):
        self.serial.send("SEND_MAX_CURRENT", transnum, i)
        startTime = clock()
        timeToWait = 0.5
        while(startTime + timeToWait > clock()):
            response = self.receive()
            if (response):
               break;
            
        if (reponse):    
            return (response[1])
        else:    
            return "COMM_ERR"

    def getTransformerData(self,i):
        self.serial.send("GET_DATA",i)
        vi = []
        startTime = clock()
        timeToWait = 0.5
        while(startTime + timeToWait > clock()):
            response = self.receive()
            if (response):
                break
            
        if (response):    
            if (response[0] == "GET_DATA_RSP"):
                vi = reponse[1]
            else:
                return vi
        else:
            return vi

    def stopTransformer(self,i):
        self.serial.send("STOP_TRANS",i)
        startTime = clock()
        timeToWait = 0.5
        while(startTime + timeToWait > clock()):
            response = self.receive()
            if (response):
               break;
            
        if (reponse):    
            return (response[1])
        else:    
            return "COMM_ERR"

    def startAlarm(self):
        self.serial.send("START_ALARM")
        startTime = clock()
        timeToWait = 0.5
        while(startTime + timeToWait > clock()):
            response = self.receive()
            if (response):
               break;
            
        if (reponse):    
            return (response[1])
        else:    
            return "COMM_ERR"

    def getTransformerStatus(self):
        self.serial.send("GET_STATUS")
        status = []
        startTime = clock()
        timeToWait = 0.5
        while(startTime + timeToWait > clock()):
            response = self.receive()
            if (response):
                break
            
        if (response):    
            if (response[0] == "GET_STATUS_RSP"):
                status = reponse[1]
            else:
                return status
        else:
            return status

