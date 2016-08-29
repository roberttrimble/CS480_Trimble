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
    
    //Loop through the config files 11 lines, skipping the first one and last one
    //------NOTE Lines need to be upped for sim02 & sim03-------
    //----------------------------------------------------------
    for(lineCount = 1; lineCount < 10; lineCount++) {
        
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
                
            //Speed of PROCESSOR line
            //must be the length of XX
            case 3:
                processorSpeed = configInfo[lineCount].substr(configInfo[lineCount].length() - 2, configInfo[lineCount].length());
		//TEST
                //cout << processorSpeed << endl;
                break;
                
            //Speed of the MONITOR line
            //must be the length of XX
            case 4:
                monitorSpeed = configInfo[lineCount].substr(configInfo[lineCount].length() - 2, configInfo[lineCount].length());
		//TEST
                //cout << monitorSpeed << endl;
                break;
                
            //Speed of the HARD DIRVE line
            //must be the length of XX
            case 5:
                hardDriveSpeed = configInfo[lineCount].substr(configInfo[lineCount].length() - 2, configInfo[lineCount].length());
		//TEST
                //cout << hardDriveSpeed << endl;
                break;
                
            //Speed of the PRINTER line
            //must be the length of XXX
            case 6:
                printerSpeed = configInfo[lineCount].substr(configInfo[lineCount].length() - 3, configInfo[lineCount].length());
		//TEST
                //cout << printerSpeed << endl;
                break;
                
            //Speed of the KEYBOARD line
            //must be the length of XXX
            case 7:
                keyboardSpeed = configInfo[lineCount].substr(configInfo[lineCount].length() - 3, configInfo[lineCount].length());
		//TEST
                //cout << keyboardSpeed << endl;
                break;
                
            //Type of log line
            //will store the last word (file, monitor or both)
            case 8:
                logTo = configInfo[lineCount].substr(12, 13);
		//TEST
                //cout << logTo << endl;
                break;
                
            //Filepath (for the output) line
            //must be the length of logfile_X.lgf
            case 9:
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
 *procWait
 *Makes each process wait the appropriate amount of time
 *Also outputs each process start and stop time
 *-------------------------------------------------
 *
 */
void procWait(string type, string cycles) {
    //TEST
    //cout << type << "  " << cycles << endl;
    
    SimpleTimer timer;
    char time[15];

    //start the timer
    timer.start();
    
    ofstream fout;
    fout.clear();
    //add onto file if it alread exists
    fout.open(logFilePath, ios_base::app);
    
    //////////////////////////////////
    //if the Meta-Data is a S (system)
    //////////////////////////////////
    if(type[0] == 'S'){
        //if the S is a start
        if(type[2] == 's'){
            
            this_thread::sleep_for(chrono::milliseconds());
            timer.stop();
            timer.getElapsedTime(time);
            totalTime = totalTime + atof(time);
            
                //Output info
                if(logTo == "Both"){
                    cout << totalTime << " - Simulator program starting" << endl;
                    fout << totalTime << " - Simulator program starting" << endl;
                }else if(logTo == "Monitor")
                    cout << totalTime << " - Simulator program starting" << endl;
                else if(logTo == "File")
                    fout << totalTime << " - Simulator program starting" << endl;

        }
        //if the S in an end
        else {
            
            this_thread::sleep_for(chrono::milliseconds());
            timer.stop();
            timer.getElapsedTime(time);
            totalTime = totalTime + atof(time);
            
                //Output info
                if(logTo == "Both"){
                    cout << totalTime << " - Simulator program ending" << endl << endl;
                    fout << totalTime << " - Simulator program ending" << endl << endl;
                }else if(logTo == "Monitor")
                    cout << totalTime << " - Simulator program ending" << endl << endl;
                else if(logTo == "File")
                    fout << totalTime << " - Simulator program ending" << endl << endl;
            
        }
    }
    /////////////////////////////////////////
    // if the Meta-Data is an A (application)
    /////////////////////////////////////////
    if(type[0] == 'A'){
        //if the A is a start
        if(type[2] == 's'){
            
            this_thread::sleep_for(chrono::milliseconds());
            timer.stop();
            timer.getElapsedTime(time);
            totalTime = totalTime + atof(time);
            
                //Output info
                if(logTo == "Both"){
                    cout << totalTime << " - OS: starting process " << version << endl;
                    fout << totalTime << " - OS: starting process " << version << endl;
                }else if(logTo == "Monitor")
                    cout << totalTime << " - OS: starting process " << version << endl;
                else if(logTo == "File")
                    fout << totalTime << " - OS: starting process " << version << endl;
            
        }
        //if the A is an end
        else {
            
            this_thread::sleep_for(chrono::milliseconds());
            timer.stop();
            timer.getElapsedTime(time);
            totalTime = totalTime + atof(time);
            
                //Output info
                if(logTo == "Both"){
                    cout << totalTime << " - OS: removing process " << version << endl;
                    fout << totalTime << " - OS: removing process " << version << endl;
                }else if(logTo == "Monitor")
                    cout << totalTime << " - OS: removing process " << version << endl;
                else if(logTo == "File")
                    fout << totalTime << " - OS: removing process " << version << endl;
            
        }
    }
    ///////////////////////////////////
    //if the Meta-Data is a P (process)
    ///////////////////////////////////
    if(type[0] == 'P'){
                //Output info
                if(logTo == "Both"){
                    cout << totalTime << " - Process " << version << " start processing action" << endl;
                    fout << totalTime << " - Process " << version << " start processing action" << endl;
                }else if(logTo == "Monitor")
                    cout << totalTime << " - Process " << version << " start processing action" << endl;
                else if(logTo == "File")
                    fout << totalTime << " - Process " << version << " start processing action" << endl;

        
        this_thread::sleep_for(chrono::milliseconds(stoi(processorSpeed) * stoi(cycles)));
        timer.stop();
        timer.getElapsedTime(time);
        totalTime = totalTime + atof(time);
        
                //Output info
                if(logTo == "Both"){
                    cout << totalTime << " - Process " << version << " end processing action" << endl;
                    fout << totalTime << " - Process " << version << " end processing action" << endl;
                }else if(logTo == "Monitor")
                    cout << totalTime << " - Process " << version << " end processing action" << endl;
                else if(logTo == "File")
                    fout << totalTime << " - Process " << version << " end processing action" << endl;
        
    }
    //if the Meta-Data is an I (input)
    if(type[0] == 'I'){
        //if the I is a hard drive
        if(type[2] == 'h'){
                //Output info
                if(logTo == "Both"){
                    cout << totalTime << " - Process " << version << " start hard drive input" << endl;
                    fout << totalTime << " - Process " << version << " start hard drive input" << endl;
                }else if(logTo == "Monitor")
                    cout << totalTime << " - Process " << version << " start hard drive input" << endl;
                else if(logTo == "File")
                    fout << totalTime << " - Process " << version << " start hard drive input" << endl;

            
            this_thread::sleep_for(chrono::milliseconds(stoi(hardDriveSpeed) * stoi(cycles)));
            timer.stop();
            timer.getElapsedTime(time);
            totalTime = totalTime + atof(time);
            
                //Output info
                if(logTo == "Both"){
                    cout << totalTime << " - Process " << version << " end hard drive input" << endl;
                    fout << totalTime << " - Process " << version << " end hard drive input" << endl;
                }else if(logTo == "Monitor")
                    cout << totalTime << " - Process " << version << " end hard drive input" << endl;
                else if(logTo == "File")
                    fout << totalTime << " - Process " << version << " end hard drive input" << endl;
            
        }
        //if the I  is a keyboard
        else {
                //Output info
                if(logTo == "Both"){
                    cout << totalTime << " - Process " << version << " start keyboard input" << endl;
                    fout << totalTime << " - Process " << version << " start keyboard input" << endl;
                }else if(logTo == "Monitor")
                    cout << totalTime << " - Process " << version << " start keyboard input" << endl;
                else if(logTo == "File")
                    fout << totalTime << " - Process " << version << " start keyboard input" << endl;

            
            this_thread::sleep_for(chrono::milliseconds(stoi(keyboardSpeed) * stoi(cycles)));
            timer.stop();
            timer.getElapsedTime(time);
            totalTime = totalTime + atof(time);
            
                //Output info
                if(logTo == "Both"){
                    cout << totalTime << " - Process " << version << " end keyboard input" << endl;
                    fout << totalTime << " - Process " << version << " end keyboard input" << endl;
                }else if(logTo == "Monitor")
                    cout << totalTime << " - Process " << version << " end keyboard input" << endl;
                else if(logTo == "File")
                    fout << totalTime << " - Process " << version << " end keyboard input" << endl;
            
        }
    }
    ////////////////////////////////////
    //if the Meta-Data is an O (output)
    ////////////////////////////////////
    if(type[0] == 'O'){
        //if the O is a hard drive
        if(type[2] == 'h'){
                //Output info
                if(logTo == "Both"){
                    cout << totalTime << " - Process " << version << " start hard drive output" << endl;
                    fout << totalTime << " - Process " << version << " start hard drive output" << endl;
                }else if(logTo == "Monitor")
                    cout << totalTime << " - Process " << version << " start hard drive output" << endl;
                else if(logTo == "File")
                    fout << totalTime << " - Process " << version << " start hard drive output" << endl;
            
            
            this_thread::sleep_for(chrono::milliseconds(stoi(hardDriveSpeed) * stoi(cycles)));
            timer.stop();
            timer.getElapsedTime(time);
            totalTime = totalTime + atof(time);
            
                //Output info
                if(logTo == "Both"){
                    cout << totalTime << " - Process " << version << " end hard drive output" << endl;
                    fout << totalTime << " - Process " << version << " end hard drive output" << endl;
                }else if(logTo == "Monitor")
                    cout << totalTime << " - Process " << version << " end hard drive output" << endl;
                else if(logTo == "File")
                    fout << totalTime << " - Process " << version << " end hard drive output" << endl;
            
        }
        //if the O is a monitor
        else if(type[2] == 'm'){
                //Output info
                if(logTo == "Both"){
                    cout << totalTime << " - Process " << version << " start monitor output" << endl;
                    fout << totalTime << " - Process " << version << " start monitor output" << endl;
                }else if(logTo == "Monitor")
                    cout << totalTime << " - Process " << version << " start monitor output" << endl;
                else if(logTo == "File")
                    fout << totalTime << " - Process " << version << " start monitor output" << endl;
            

            this_thread::sleep_for(chrono::milliseconds(stoi(monitorSpeed) * stoi(cycles)));
            timer.stop();
            timer.getElapsedTime(time);
            totalTime = totalTime + atof(time);
            
                //Output info
                if(logTo == "Both"){
                    cout << totalTime << " - Process " << version << " end monitor output" << endl;
                    fout << totalTime << " - Process " << version << " end monitor output" << endl;
                }else if(logTo == "Monitor")
                    cout << totalTime << " - Process " << version << " end monitor output" << endl;
                else if(logTo == "File")
                    fout << totalTime << " - Process " << version << " end monitor output" << endl;
            
        }
        //if the O is a printer
        else {
                //Output info
                if(logTo == "Both"){
                    cout << totalTime << " - Process " << version << " start printer output" << endl;
                    fout << totalTime << " - Process " << version << " start printer output" << endl;
                }else if(logTo == "Monitor")
                    cout << totalTime << " - Process " << version << " start printer output" << endl;
                else if(logTo == "File")
                    fout << totalTime << " - Process " << version << " start printer output" << endl;
            

            this_thread::sleep_for(chrono::milliseconds(stoi(printerSpeed) * stoi(cycles)));
            timer.stop();
            timer.getElapsedTime(time);
            totalTime = totalTime + atof(time);
            
                //Output info
                if(logTo == "Both"){
                    cout << totalTime << " - Process " << version << " end printer output" << endl;
                    fout << totalTime << " - Process " << version << " end printer output" << endl;
                }else if(logTo == "Monitor")
                    cout << totalTime << " - Process " << version << " end printer output" << endl;
                else if(logTo == "File")
                    fout << totalTime << " - Process " << version << " end printer output" << endl;
            
        }
    }

    fout.close();
}













































