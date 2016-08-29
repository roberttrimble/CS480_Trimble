//
//  Utils.cpp
//  Sim01
//
//  Created by 348190 on 10/2/15.
//  Copyright (c) 2015. All rights reserved.
//

#include <iostream>
#include <fstream>

#include <string>
#include <sstream>
#include <vector>
#include <queue>

#include <thread>
#include <chrono>

#include "SimpleTimer.h"
#include "Utils.h"
#include "Struct.h"

using namespace std;





/*
 *
 *-------------------------------------------------
 *getConfigInfo
 *Takes the info from the congif file and puts info into appropriate variable
 *-------------------------------------------------
 *
 *
 */
void getConfigInfo(string *configInfo) {
    string subString;
    int lineCount;
    
    //Loop through the config files 12 lines, skipping the first one and last one
    //------NOTE Lines need to be upped for sim02 & sim03-------
    //----------------------------------------------------------
    for(lineCount = 1; lineCount < 11; lineCount++) {
        
        //Substring the appropriate length at the end of each line, then store
        switch (lineCount) {
                //Version line
            case 1:
                version = configInfo[lineCount].substr(configInfo[lineCount].length() - 3, configInfo[lineCount].length());
                //TEST
                //cout << version << endl;
                break;
                
                //Filepath (for the input test file) line
                //must be the length of test_X.mdf
            case 2:
                filePath = configInfo[lineCount].substr(configInfo[lineCount].length() - 10, configInfo[lineCount].length());
                //TEST
                //cout << filePath << endl;
                break;
                
                //Process type line
                //Either FIFO or SJF/SRTF-N
            case 3:
                procType = configInfo[lineCount].substr(21, configInfo[lineCount].length());
                //TEST
                //cout << procType << endl;
                break;
                
                //Speed of PROCESSOR line
                //must be the length of XX
            case 4:
                processorSpeed = configInfo[lineCount].substr(configInfo[lineCount].length() - 2, configInfo[lineCount].length());
                //TEST
                //cout << processorSpeed << endl;
                break;
                
                //Speed of the MONITOR line
                //must be the length of XX
            case 5:
                monitorSpeed = configInfo[lineCount].substr(configInfo[lineCount].length() - 2, configInfo[lineCount].length());
                //TEST
                //cout << monitorSpeed << endl;
                break;
                
                //Speed of the HARD DIRVE line
                //must be the length of XX
            case 6:
                hardDriveSpeed = configInfo[lineCount].substr(configInfo[lineCount].length() - 2, configInfo[lineCount].length());
                //TEST
                //cout << hardDriveSpeed << endl;
                break;
                
                //Speed of the PRINTER line
                //must be the length of XX
            case 7:
                printerSpeed = configInfo[lineCount].substr(configInfo[lineCount].length() - 2, configInfo[lineCount].length());
                //TEST
                //cout << printerSpeed << endl;
                break;
                
                //Speed of the KEYBOARD line
                //must be the length of XX
            case 8:
                keyboardSpeed = configInfo[lineCount].substr(configInfo[lineCount].length() - 2, configInfo[lineCount].length());
                //TEST
                //cout << keyboardSpeed << endl;
                break;
                
                //Type of log line
                //will store the last word (file, monitor or both)
            case 9:
                logTo = configInfo[lineCount].substr(12, 13);
                //TEST
                //cout << logTo << endl;
                break;
                
                //Filepath (for the output) line
                //must be the length of logfile_X.lgf
            case 10:
                logFilePath = configInfo[lineCount].substr(configInfo[lineCount].length() - 13, configInfo[lineCount].length());
                //TEST
                //cout << logFilePath << endl;
                break;
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////















/*
 *
 *-------------------------------------------------
 *getInputInfo
 *Takes the string from input and divides important info into a vector element
 *Return the vector
 *-------------------------------------------------
 *
 *
 */
vector<string> getInputInfo(string input){
    vector<string> processes;
    
    int startCount = 0;
    int processCount = 0;
    
    char testChar;
    //loops through every char in the input string
    //then divides each segment into a vector element
    for(int i = 0; i < input.length(); i++) {
        //grabs the current char
        testChar = input[i];
        
        //if the current char is a ';'
        if(testChar == ';') {
            //add to vector the string from starting point to current char
            processes.push_back(input.substr(startCount, i-startCount));
            //moves the starting point to after the ';'
            startCount = i+2;
            processCount++;
        }
    }
    //add the last process (because file does not end in ';')
    processes.push_back(input.substr(startCount, startCount+7));
    
    //subtract "Start Program Meta-Data Code:" from beginning of first process by discarding the beginning
    processes[0] = processes[0].substr(29,38);
    //subract " ".End Program Meta-Data Code." from end of last process by discarding the end
    processes[processCount] = processes[processCount].substr(0,7);
    
    
    return processes;
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////











/*
 *
 *-------------------------------------------------
 *procToQueue
 *Determines what type of process it is, and how many cycles it has
 *Each vector element is in the form (S(start)0 I(Keyboard)10 etc)
 *Returns a queue with a process in each element
 *-------------------------------------------------
 *
 *
 */
queue<process> procToQueue(vector<string> input){
    queue<process> queue;
    process temp;
    
    //loop through every process from the vector input
    for(int i = 0; i < input.size(); i++){
        //if the Meta-Data is a S (system)
        if(input[i][0] == 'S'){
            //if the S is a start
            if(input[i][2] == 's'){
                temp.type = "S(start)";
                temp.cycles = input[i].substr(8,input[i].size());
                
                queue.push(temp);
            }
            //if the S in an end
            else {
                temp.type = "S(end)";
                temp.cycles = input[i].substr(6, input[i].size());
                
                queue.push(temp);
            }
        }
        // if the Meta-Data is an A (application)
        if(input[i][0] == 'A'){
            //if the A is a start
            if(input[i][2] == 's'){
                temp.type = "A(start)";
                temp.cycles = input[i].substr(8, input[i].size());
                
                queue.push(temp);
            }
            //if the A is an end
            else {
                temp.type = "A(end)";
                temp.cycles = input[i].substr(6, input[i].size());
                
                queue.push(temp);
            }
        }
        //if the Meta-Data is a P (process)
        if(input[i][0] == 'P'){
            temp.type = "P(run)";
            temp.cycles = input[i].substr(6, input[i].size());
            
            queue.push(temp);
        }
        //if the Meta-Data is an I (input)
        if(input[i][0] == 'I'){
            //if the I is a hard drive
            if(input[i][2] == 'h'){
                temp.type = "I(hard drive)";
                temp.cycles = input[i].substr(13, input[i].size());
                
                queue.push(temp);
            }
            //if the I  is a keyboard
            else {
                temp.type = "I(keyboard)";
                temp.cycles = input[i].substr(11, input[i].size());
                
                queue.push(temp);
            }
        }
        //if the Meta-Data is an O (output)
        if(input[i][0] == 'O'){
            //if the O is a hard drive
            if(input[i][2] == 'h'){
                temp.type = "O(hard drive)";
                temp.cycles = input[i].substr(13, input[i].size());
                
                queue.push(temp);
            }
            //if the O is a monitor
            else if(input[i][2] == 'm'){
                temp.type = "O(monitor)";
                temp.cycles = input[i].substr(10, input[i].size());
                
                queue.push(temp);
            }
            //if the O is a printer
            else {
                temp.type = "O(printer)";
                temp.cycles = input[i].substr(10, input[i].size());
                
                queue.push(temp);
            }
        }
    }
    
    return queue;
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////









/*
 *
 *-------------------------------------------------
 *queueToPCB
 *takes each meta data and puts it into appropriate PCB
 *also, keeps track of how long each PCB is
 *-------------------------------------------------
 *
 */
vector<PCB> queueToPCB(queue<process> procQueue) {
    vector<PCB> PCBlock;
    process tempProcess;
    
    queue<process> tempQueue;
    PCB tempBlock;
    
    int processCount = 1;
    int processLength = 0;
    
    //loop through the input queue
    while(!procQueue.empty()) {
	//if the meta data is an S, ignore it
        if(procQueue.front().type[0] == 'S') {
            //Do Nothing
        }
	//if the meta data is an A (and an end),
	//finish the PCB and set up for the next one
        else if(procQueue.front().type[0] == 'A'){
            if(procQueue.front().type[2] == 'e') {
		//update the process count
                tempBlock.procNumber = processCount;
                processCount++;
		//add the process length, then reset it
                tempBlock.procLength = processLength;
                processLength = 0;
                
		//add the queue to the PCB
                tempBlock.procBlock = tempQueue;
                //add the PCB to vector
                PCBlock.push_back(tempBlock);
                
		//clear the temp queue
                while(!tempQueue.empty())
                    tempQueue.pop();
            }
        }
	//if the meta data is NOT an A or S
        else if(procQueue.front().type[0] != 'S' || procQueue.front().type[0] != 'A'){
	    //if the meta data is a P
            if(procQueue.front().type[0] == 'P') {
		//update process length
                processLength += (stoi(procQueue.front().cycles) * stoi(processorSpeed));
		//add to the queue
                tempQueue.push(procQueue.front());
            }
	    //if the meta data is an O
            else if(procQueue.front().type[0] == 'O') {
		//if O is a monitor
                if(procQueue.front().type[2] == 'm') {
		    //update process length
                    processLength += (stoi(procQueue.front().cycles) * stoi(monitorSpeed));
		    //add to the queue
                    tempQueue.push(procQueue.front());
                }
		//if O is a hard drive
                else if(procQueue.front().type[2] == 'h') {
		    //update the process length
                    processLength += (stoi(procQueue.front().cycles) * stoi(hardDriveSpeed));
		    //add to the queue
                    tempQueue.push(procQueue.front());
                }
		//if O is a printer
                else if(procQueue.front().type[2] == 'p') {
		    //update the process length
                    processLength += (stoi(procQueue.front().cycles) * stoi(printerSpeed));
		    //add to the queue
                    tempQueue.push(procQueue.front());
                }
            }
	    //if the meta data is an I
            else if(procQueue.front().type[0] == 'I') {
		//if the I is a keyboard
                if(procQueue.front().type[2] == 'k') {
		    //update the process length
                    processLength += (stoi(procQueue.front().cycles) * stoi(keyboardSpeed));
		    //add to the queue
                    tempQueue.push(procQueue.front());
                }
		//if the I is a hard drive
                else if(procQueue.front().type[2] == 'h') {
		    //update the process length
                    processLength += (stoi(procQueue.front().cycles) * stoi(hardDriveSpeed));
		    //add to the queue
                    tempQueue.push(procQueue.front());
                }
            }
        }
	//move to the next meta data
        procQueue.pop();
    }
    
    return PCBlock;
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////







/*
 *
 *-------------------------------------------------
 *sortPCB
 *puts the shortest PCB to the front of the vector
 *-------------------------------------------------
 *
 */
vector<PCB> sortPCB(vector<PCB> PCBinput) {
    vector<PCB> PCBoutput;
    PCB temp;

    //put the first PCB into the new vector
    temp.procLength = PCBinput[0].procLength;
    temp.procNumber = PCBinput[0].procNumber;
    temp.procBlock = PCBinput[0].procBlock;
    PCBoutput.push_back(temp);
    
    //loop through the remaining PCBs
    for(int i = 1; i < PCBinput.size(); i++){
        temp.procLength = PCBinput[i].procLength;
        temp.procNumber = PCBinput[i].procNumber;
        temp.procBlock = PCBinput[i].procBlock;
        
	//if the next PCB is shorter, put it in front, else put it in the back
        if(temp.procLength < PCBoutput[0].procLength)
            PCBoutput.insert(PCBoutput.begin(), temp);
        else
            PCBoutput.push_back(temp);
    }
    
    return PCBoutput;
}








//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////









/*
 *
 *-------------------------------------------------
 *procWait
 *Makes each process wait the appropriate amount of time
 *Also outputs each process start and stop time
 *-------------------------------------------------
 *
 */
void procWait(PCB input) {
    
    ofstream fout;
    fout.clear();
    //add onto file if it alread exists
    fout.open(logFilePath, ios_base::app);
    
    
    if(logTo == "Both"){
        cout << totalTime << " - OS: starting process " << input.procNumber << endl;
        fout << totalTime << " - OS: starting process " << input.procNumber << endl;
    }else if(logTo == "Monitor")
        cout << totalTime << " - OS: starting process " << input.procNumber << endl;
    else if(logTo == "File")
        fout << totalTime << " - OS: starting process " << input.procNumber << endl;
    
    while(!input.procBlock.empty()){
        SimpleTimer timer;
        char time[15];
        timer.start();
    
        
    ///////////////////////////////////
    //if the Meta-Data is a P (process)
    ///////////////////////////////////
    if(input.procBlock.front().type[0] == 'P'){
        //Output info
	outputInfo(input.procNumber, " start processing action");
        
        
        this_thread::sleep_for(chrono::milliseconds(stoi(processorSpeed) * stoi(input.procBlock.front().cycles)));
        timer.stop();
        timer.getElapsedTime(time);
        totalTime = totalTime + atof(time);
        
        //Output info
	outputInfo(input.procNumber, " end processing action");
        
    }
    //if the Meta-Data is an I (input)
    if(input.procBlock.front().type[0] == 'I'){
        //if the I is a hard drive
        if(input.procBlock.front().type[2] == 'h'){
            //Output info
	    outputInfo(input.procNumber, " start hard drive input");
            
            this_thread::sleep_for(chrono::milliseconds(stoi(hardDriveSpeed) * stoi(input.procBlock.front().cycles)));
            timer.stop();
            timer.getElapsedTime(time);
            totalTime = totalTime + atof(time);
            
            //Output info
	    outputInfo(input.procNumber, " end hard drive input");
            
        }
        //if the I  is a keyboard
        else {
            //Output info
	    outputInfo(input.procNumber, " start keyboard input");
            
            this_thread::sleep_for(chrono::milliseconds(stoi(keyboardSpeed) * stoi(input.procBlock.front().cycles)));
            timer.stop();
            timer.getElapsedTime(time);
            totalTime = totalTime + atof(time);
            
            //Output info
	    outputInfo(input.procNumber, " end keyboard input");
        }
    }
    ////////////////////////////////////
    //if the Meta-Data is an O (output)
    ////////////////////////////////////
    if(input.procBlock.front().type[0] == 'O'){
        //if the O is a hard drive
        if(input.procBlock.front().type[2] == 'h'){
            //Output info
	    outputInfo(input.procNumber, " start hard drive output");
               
            this_thread::sleep_for(chrono::milliseconds(stoi(hardDriveSpeed) * stoi(input.procBlock.front().cycles)));
            timer.stop();
            timer.getElapsedTime(time);
            totalTime = totalTime + atof(time);
            
            //Output info
	    outputInfo(input.procNumber, " end hard drive output");
        }
        //if the O is a monitor
        else if(input.procBlock.front().type[2] == 'm'){
            //Output info
	    outputInfo(input.procNumber, " start monitor output");
            
            this_thread::sleep_for(chrono::milliseconds(stoi(monitorSpeed) * stoi(input.procBlock.front().cycles)));
            timer.stop();
            timer.getElapsedTime(time);
            totalTime = totalTime + atof(time);
            
            //Output info
	    outputInfo(input.procNumber, " end monitor output");
        }
        //if the O is a printer
        else {
            //Output info
	    outputInfo(input.procNumber, " start printer output");
            
            this_thread::sleep_for(chrono::milliseconds(stoi(printerSpeed) * stoi(input.procBlock.front().cycles)));
            timer.stop();
            timer.getElapsedTime(time);
            totalTime = totalTime + atof(time);
            
            //Output info
	    outputInfo(input.procNumber, " end printer output");
        }
    }
    
        
        input.procBlock.pop();
    }
    if(logTo == "Both"){
        cout << totalTime << " - OS: removing process " << input.procNumber << endl;
        fout << totalTime << " - OS: removing process " << input.procNumber << endl;
    }else if(logTo == "Monitor")
        cout << totalTime << " - OS: removing process " << input.procNumber << endl;
    else if(logTo == "File")
        fout << totalTime << " - OS: removing process " << input.procNumber << endl;
    
    fout.close();
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////









/*
 *
 *-------------------------------------------------
 *outputInfo
 *outputs appropriate info to monitor, file or both
 *-------------------------------------------------
 *
 */
void outputInfo(int procNumber, string input) {
    ofstream fout;
    fout.open(logFilePath, ios_base::app);

    //if the output doesnt need the process number
    if(procNumber == -1) {
	if(logTo == "Both"){
            cout << totalTime << input << endl;
            fout << totalTime << input << endl;
        }else if(logTo == "Monitor")
            cout << totalTime << input << endl;
        else if(logTo == "File")
            fout << totalTime << input << endl;
    }
    //if the output does need a process number
    else {
	if(logTo == "Both"){
                cout << totalTime << " - Process " << procNumber << input << endl;
                fout << totalTime << " - Process " << procNumber << input << endl;
            }else if(logTo == "Monitor")
                cout << totalTime << " - Process " << procNumber << input << endl;
            else if(logTo == "File")
                fout << totalTime << " - Process " << procNumber << input << endl;
    }



    fout.close();
}










































