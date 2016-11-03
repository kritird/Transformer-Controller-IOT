# Get system & package imports
import sys
from threading import Thread

# Get local imports
from communication import *
from transformer import *
from fileHandler import *
from uiHandler import *
from transceiver import *
import config
import errorHandler


#-----------------------------------------------------------#
# Method : main                                             #
# This is the main control of the application               #
# Sets the globals of control and data                      #
# Mode : Main                                               #
#-----------------------------------------------------------#
def main():

    # Assign the initial objects
    #-------------------------------------------------------
    try:
        config.comm.append(Communication())
    except:
        config.logger.info(config.error[0])
        sys.exit()
        
    try:        
        for i in range(5):
            tr = Transformer()
            config.trans.append(tr)
            
            f = FileHandler(i)
            config.file.append(f)
    except:
        config.logger.info(config.error[1])
        sys.exit()
    #-------------------------------------------------------

        
            
    #setup ui display
    #-------------------------------------------------------
    config.logger.info("UI Init Starting")



    #-------------------------------------------------------

        
    config.appStatus = True
    for i in range(5):
        config.trans[i].maxi = 200

    
    # Wait till user starts the application
    #-------------------------------------------------------
    while (config.appStatus == False):
        pass
    
    config.logger.info("Main Starting")
    #-------------------------------------------------------

    
    # Check if Arduino is available
    #-------------------------------------------------------
    while (True):
        rc = config.comm[0].pingArduino()
        if not (rc == "OK"):
            #Give Alert Window - Retry / Quit
            config.logger.info(config.error[2])
            retry = errorHandler(config.error[2])
            if not (retry):
                processCompletion()
        config.commError = False
        break            
    #-------------------------------------------------------
        
    # Main thread for Data Read and File Write
    # This thread will read Transformer Data and
    # Write it in the file
    #-------------------------------------------------------
    txRxThread = Thread(target=transceiver, args=())
    txRxThread.start()
    #-------------------------------------------------------
        

    #Main loop to control & keep application running
    #-------------------------------------------------------
    while(True):
        
        #If application Stop requested
        if not (config.appStatus):
            processCompletion()
            break
        
        # If we have a communication error
        # Retry Communication
        if (config.commError):
            while (True):
                if not (txRxThread.is_alive()):
                    config.commError = False
                    config.logger.info("Restarting thread after communication error")
                    txRxThread = Thread(target=transceiver, args=())
                    txRxThread.start()
                    break
                
        #Handle Trip point controls
        for tr in config.trans:
            if (tr.state):
                if (tr.vo and tr.vu):
                    if (tr.v[0] > tr.vo or
                        tr.v[1] > tr.vo or
                        tr.v[2] > tr.vo):
                        tr.setTransformerTripped()
                        config.logger.info("Transformer Tripped due to over voltage")
                        
                    if (tr.v[0] < tr.vu or
                        tr.v[1] < tr.vu or
                        tr.v[2] < tr.vu):
                        tr.setTransformerTripped()
                        config.logger.info("Transformer Tripped due to under voltage")
                    
                if (tr.io):
                    if (tr.i[0] > tr.io or
                        tr.i[1] > tr.io or
                        tr.i[2] > tr.io):
                        tr.setTransformerTripped()
                        config.logger.info("Transformer Tripped due to over current")

        #---------------------------------------------------                
                                                
            
    #---------End of Control Loop---------#
    #-------------------------------------#

    # Wait for threads to join in
    txRxThread.join()
    
#---------------------------------------------------
#                  End of Main
#---------------------------------------------------                


#-----------------------------------------------------------#
# Method : processCompletion                                #
# Graceful completion and exit of application               #
# Mode : Main                                               #
#-----------------------------------------------------------#
def processCompletion():
    print("Main \n")
    for i in range(5):
        print (config.trans[i].vi)
    pass

    config.logger.info("Application Completed")
    print("Completion")
    sys.exit()

#-----------------------------------------------------------#
# Method : Initiate Application                             #
# Mode : Main                                               #
#-----------------------------------------------------------#
if __name__ == "__main__":
    main()
    config.logger.info("Application Exited")
    print("we are done")
    sys.exit()
    
    
    
