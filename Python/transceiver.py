from time import clock
import time as tm
import random
import config
import errorHandler


#-----------------------------------------------------------#
# Method : transceiver                                      #
# Controls the Tx and Rx with Arduino                       #
# Sets the globals of control and data                      #
# Mode : Thread                                             #
#-----------------------------------------------------------#
def transceiver ():

    config.logger.info("Thread transceiver Starting")
    
    # Wait till Transformer Max Current is provided
    # Send the Max Current to Arduino
    #-----------------------------------------------
    try:
        for i in range(5):
            while (config.trans[i].maxi == 0):
                pass
            rc = config.comm[0].sendMaxCurrent (i, config.trans[i].maxi)
            if not (rc == "OK"):
                config.logger.info(config.error[6])
                retry = errorHandler(config.error[6])
                if (retry):
                    i = i - 1
                else:
                    break
    except:
        config.logger.info(config.error[6])
        exit()
    #-----------------------------------------------
        
                
    t0 = clock()
    while(config.appStatus):
        
        if ((clock() - t0) >= 0.1):
            
            # Ping Arduino to check OK
            #-----------------------------------------------
            try:
                rc = config.comm[0].pingArduino()
                if not (rc == "OK"):
                    config.logger.info(config.error[2])
                    errorHandler(config.error[2])
                    break
                    
            except:
                config.logger.info(config.error[2])
                exit()                
            #-----------------------------------------------
                
            
            # Get Transformer Status from Arduuino
            #-----------------------------------------------
            try:
                ts = config.comm[0].getTransformerStatus()
                for i in range(5):
                    # If Current State is OFF and new State is ON
                    # Then reset the transformer
                    if (config.trans[i].state == False and ts[i] == True):
                        config.trans[i].resetTransformer()
                    config.trans[i].setTransformerStatus(ts[i])
            except:
                config.logger.info(config.error[3])
                exit()                                
            #-----------------------------------------------

            
            # Get the Transformer Data and Write to File
            #-----------------------------------------------
            try:
                metaData = config.file[0].getFieldLayout()
                data = {}
                
                for i in range(5):
                    # Fetch Data only if Transformer ON
                    if (config.trans[i].state):

                        # Get it from Arduino
                        vi = config.comm[0].getTransformerData(i)

                        # Set it in the object
                        config.trans[i].setVoltagesAndCurrent(vi)
                        
                        # Write them in File
                        config.file[i].openCSVFile()

                        # Format Date & Time
                        d = tm.localtime(tm.time())
                        date = "%d/%d/%d"%(d[2],d[1],d[0])
                        time = "%d:%d:%d"%(d[3],d[4],d[5])
                        data[metaData[0]] = date
                        data[metaData[1]] = time
                        
                        # Write the data
                        for j in range(2,len(metaData)):
                             data[metaData[j]] = vi[j-2]              
                        config.file[i].writeCSVFile(data)
                        config.file[i].closeCSVFile()
                        data.clear()
                        
                t0 = clock()
            except:
                config.logger.info(config.error[4])
                exit()                                
            #-----------------------------------------------
                
            i = random.randint(0,1)
            if (i):
                config.appStatus = False

        #-------End of Transformer Data Read Write --------#
        

        # Check if Transformer Trip point reached
        # Send STOP command and Start Alarm
        #--------------------------------------------------
        try:
            for i in range(5):
                if (config.trans[i].tripped):                    
                    rc = config.comm[0].stopTransformer(i)
                    rc = config.comm[0].startAlarm()
                    if not (rc == "OK"):
                        config.logger.info(config.error[5])
                        errorHandler(config.error[5])
                        break
        except:
            config.logger.info(config.error[5])
            exit()                                
            
        #-------End of Transformer Trip------------------#

    config.logger.info("Transceiver Thread Exited")                
    print("Thread ends here \n")
