import PyCmdMessenger
from time import clock
import random

class Communication ():
    def __init__(self):

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


        
    def pingArduino(self):
        return "OK"

    def sendMaxCurrent(self, transNum, i):
        return "OK"

    def getTransformerData(self,i):
        vi = []
        for count in range(6):
            vi.append(random.randint(0,10))        
        return vi

    def stopTransformer(self,i):
        return "OK"

    def startAlarm(self):
        return "OK"

    def getTransformerStatus(self):
        status = [True,True,True,True,True]
        return status

