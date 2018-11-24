# creating a web API to Store and View and Delete Time Stamp

from flask import Flask
import pickle
import datetime

app = Flask(__name__)

# The timeStamp is stored in the pickle file
pickleFileName="data.pickle"

def savePickle(timeData):
	# Save Pickle File 
    pickleFile = open(pickleFileName, 'wb') 
    #print(timeData)
    pickle.dump(timeData, pickleFile)                      
    pickleFile.close() 

def loadPickle():
	#Load Pickle File
	pickleFile = open(pickleFileName, 'rb') 
	timeData =[]     
	timeData = pickle.load(pickleFile)
	pickleFile.close() 
	return(timeData)

def saveData():
	#get data, append the timeStamp and save it at the end
	timeData = loadPickle()
	timeData.append(str(datetime.datetime.now()))
	savePickle(timeData)
	return(str(datetime.datetime.now()))

def deleteData():
	#save empty list to clear all data
	timeData = []
	savePickle(timeData)
	return 'data Cleared'	

def printData():
	#get the data and print in HTML format to view
	pageHtml= '<h1>DateTimeStamp</h1>'
	timeData= loadPickle()
	for timeStamp in timeData: 
		pageHtml+= '<h5>'+str(timeStamp)+'</h5>'
	return pageHtml



@app.route('/printData')
def onHttpRequestPrint():
    return printData()

@app.route('/saveData')
def onHttpRequestSave():
    return saveData()

@app.route('/clearData')
def onHttpRequestDelete():
    return deleteData()    

if __name__ == '__main__':
    app.run(host= '192.168.1.15')