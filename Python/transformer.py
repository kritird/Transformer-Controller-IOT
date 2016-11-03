class Transformer:

      def __init__(self):
            self.initialize()
  
      def initialize (self):
            self.v  = self.i  = self.vi = []
            self.vo = self.vu = self.io = 0.0
            self.state = False
            self.tripped = False
            self.maxi = 0.0
            
      def setMaxCurrent (self, i):
            self.maxi = i
               
      def setVoltagesAndCurrent (self,vi):
            self.vi = vi
            self.v = [vi[0],vi[1],vi[2]]
            self.i = [vi[3],vi[4],vi[5]]
                      
      def setOverloadVoltage (self, vo):
            self.vo = vo
      
      def setUnderloadVoltage (self, vu):
            self.vu = vu
              
      def setOverloadCurrent (self, io):
            self.io = io
      
      def setTransformerStatus (self, state):
            self.state = state
                  
      def setTransformerTripped (self):
            self.tripped = True
            self.state = False
            
      def resetTransformer (self):
            self.tripped = False
            self.state = True
            
