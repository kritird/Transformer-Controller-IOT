import csv
import time as tm
import os.path


class TripFileHandler:

    def __init__(self):
        self.path = (os.path.dirname(os.path.realpath(__file__)))
        self.path += "/results/"
        date = tm.localtime(tm.time())
        self.fileName = "%d_%d_%d" %(date[2],date[1],date[0])
        self.path += self.fileName + "/"
        self.fields = ['Transformer','Date','Time','Voltage1','Voltage2','Voltage3','Current1','Current2','Current3','Over Voltage','Under Voltage','Overload']
    
    def openCSVFile(self):
 
        if not os.path.exists(self.path):
            os.makedirs(self.path)
        if not os.path.isfile(self.path+self.fileName+'_Trip_Report.csv'):            
            self.file = open(self.path+self.fileName+'_Trip_Report.csv', 'w')
            writer = csv.DictWriter(self.file, fieldnames=self.fields)
            writer.writeheader()
        else:
            self.file = open(self.path+self.fileName+'_Trip_Report.csv', 'a')

    
    def writeCSVFile(self,data):
            self.file = open(self.path+self.fileName+'_Trip_Report.csv', 'a')
            writer = csv.DictWriter(self.file, fieldnames=self.fields)
            writer.writerow(data)

    def readCSVFile(self):
            self.file = open(self.path+self.fileName+'_Trip_Report.csv', 'r')
            return (csv.DictReader(self.file))
                
    def getFieldLayout(self):
        return self.fields

    def closeCSVFile(self):
        self.file.close()
