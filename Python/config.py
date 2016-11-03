import logging

#-----------------------------------------------------------#
# Config : Configuration File                               #
# Put all the Singleton Objects / Variable that needs       #
# across the module access                                  #
# Mode : Singleton                                          #
#-----------------------------------------------------------#

# Initialize Variables
appStatus = False
commError = False
trans = [] 
file = []
comm = []

# Event Log Initialization

logger = logging.getLogger(__name__)
logger.setLevel(logging.INFO)

handler = logging.FileHandler('events.log', 'w')
handler.setLevel(logging.INFO)

# create a logging format
formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
handler.setFormatter(formatter)

# add the handlers to the logger
logger.addHandler(handler)

error = [ "Communication Initialization Error",
          "File Handler Initialization Error",
          "Unable to connect to Controller",
          "Unable to get Transformer Status from Controller",         
          "Unable to get Transformer Data from Controller",         
          "Unable to send STOP SIGNAL to Controller",
          "Unable to send MAX Current to Controller"
        ]

#------------------------End-------------------------------#
