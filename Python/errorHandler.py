import config

#-----------------------------------------------------------#
# Method : errorHandler                                     #
#-----------------------------------------------------------#            
def errorHandler(error):
    #Give an alert box for retry or close
    retry = True
    if (retry):
        config.commError = True
    else:
        config.appStatus = False
    return retry
