import csv
import time as tm
import os.path


class FileHandler:

    def __init__(self, transformer):
        self.path = (os.path.dirname(os.path.realpath(__file__)))
        self.path += "/results/"
        date = tm.localtime(tm.time())
        self.fileName = "%d_%d_%d" %(date[2],date[1],date[0])
        self.path += self.fileName + "/"
        self.fields = ['Date','Time','Voltage1','Voltage2','Voltage3','Current1','Current2','Current3']
        self.transformer = transformer
    
    def openCSVFile(self):
 
        if not os.path.exists(self.path):
            os.makedirs(self.path)
        if not os.path.isfile(self.path+self.fileName+'_Transformer%01d.csv' %self.transformer):            
            self.file = open(self.path+self.fileName+'_Transformer%01d.csv' %self.transformer, 'w')
            writer = csv.DictWriter(self.file, fieldnames=self.fields)
            writer.writeheader()
        else:
            self.file = open(self.path+self.fileName+'_Transformer%01d.csv' %self.transformer, 'a')

    
    def writeCSVFile(self,data):
            self.file = open(self.path+self.fileName+'_Transformer%01d.csv' %self.transformer, 'a')
            writer = csv.DictWriter(self.file, fieldnames=self.fields)
            writer.writerow(data)

    def readCSVFile(self):
            self.file = open(self.path+self.fileName+'_Transformer%01d.csv' %self.transformer, 'r')
            return (csv.DictReader(self.file))
                
    def getFieldLayout(self):
        return self.fields

    def closeCSVFile(self):
        self.file.close()
