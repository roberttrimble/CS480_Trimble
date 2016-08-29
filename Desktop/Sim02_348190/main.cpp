//
//  main.cpp
//  Sim02
//
//  Created by 348190 on 10/1/15.
//  Copyright (c) 2015. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

#include <thread>

#include <unistd.h>

#include "SimpleTimer.h"
#include "Utils.h"
#include "Struct.h"


using namespace std;

//Global Varibles all from config file
string version;
string filePath;
string procType;
string processorSpeed;
string monitorSpeed;
string hardDriveSpeed;
string printerSpeed;
string keyboardSpeed;
string logTo;
string logFilePath;

float totalTime;




int main(int argc, const char * argv[]) {
    
    ifstream fin;
    
    const char* inFile = argv[1];
    fin.open(inFile);
    
    string configLine[15]; //holds each line to the config file
    
    //Read in config file line by line
    int lineCount = 0;
    if(fin.is_open()){
        //store each line into the line string array
        while(getline(fin,configLine[lineCount])){
            //TEST
            //cout << configLine[lineCount] << endl;
            
            lineCount++;
        }
    }
    else cout << "Couldn't open file" << endl;
    cout << endl;
    fin.close();
    
    //extract info from each line
    //call Utils function
    getConfigInfo(configLine);
    
    
    //Read in input file into a single string
    fin.open(filePath); //file given from config
    string inputString,
	   fileLine;
    
    getline(fin,fileLine);
    while(fin){
        inputString += fileLine;
        getline(fin,fileLine);
    }
    fin.close();
    
    //parse string into a vector
    vector<string> processes; //struct from Struct.h
    //call Utils function
    processes = getInputInfo(inputString);
    
    
    
    //put each vector element into a Queue
    queue<process> processQ;
    //call Utils function
    processQ = procToQueue(processes);
    
    //divide process queue into a PCB vector
    vector<PCB> ProcControlBlock;
    //call Utils function
    ProcControlBlock = queueToPCB(processQ);
    
    
    //TEST
    /*while(!ProcControlBlock.empty()){
        while(!ProcControlBlock[0].procBlock.empty()){
            cout << ProcControlBlock[0].procBlock.front().type << " ";
            cout << ProcControlBlock[0].procNumber << " ";
            cout << ProcControlBlock[0].procLength << endl;
            
            ProcControlBlock[0].procBlock.pop();
        }
        ProcControlBlock.erase(ProcControlBlock.begin());
    }*/
    //END TEST
    
    
    
    
    cout << endl;

    //output info
    outputInfo(-1, " - Simulator program starting");
    
    //loop through the PCBs
    while(!ProcControlBlock.empty()){
        
         
	//output info
	outputInfo(-1, " - OS: selecting next process");  
  
	//Sort the PCBs (if neccessary)
        if(procType == "SJF" || procType == "SRTF-N")
	    //call Utils function
            ProcControlBlock = sortPCB(ProcControlBlock);
        
        //create a thread, and make it wait
        thread t(procWait, ProcControlBlock[0]);
        
        //close the thread
        t.join();
        //remove the process
        ProcControlBlock.erase(ProcControlBlock.begin());
    }
    
    //output info
    outputInfo(-1, " - Simulator program ending \n\n");
  
    //END
    return 0;
}

