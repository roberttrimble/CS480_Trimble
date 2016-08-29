//
//  Utils.h
//  Sim01
//
//  Created by 348190 on 10/2/15.
//  Copyright (c) 2015. All rights reserved.
//

#ifndef __Sim01__Utils__
#define __Sim01__Utils__


#include "Struct.h"

using namespace std;

//config variables
extern string version;
extern string filePath;
extern string processorSpeed;
extern string monitorSpeed;
extern string hardDriveSpeed;
extern string printerSpeed;
extern string keyboardSpeed;
extern string logTo;
extern string logFilePath;
extern float totalTime;



/*
 * @pre     a config file has been entered
 * @param   string ptr to each line of the config file
 * @post    config info in stored into appropriate global variable
 * @return  NONE
 */
void getConfigInfo(string *configLine);

/*
 * @pre     an input file that has been converted into a single string
 * @param   a single string input
 * @post    NONE
 * @return  a vector with each element being a process (S(start)0, I(Keyboard)15, etc)
 */
vector<string> getInputInfo(string input);

/*
 * @pre     a vector with each element being a string of a single process
 * @param   a vector with all the processes
 * @post    NONE
 * @return  a queue of processes, with each process holding the type and how many cycles to do
 */
queue<process> procToQueue(vector<string>);

/*
 * @pre     a thread is created, and type/cycles are stored in a queue
 * @param   the current threads (front of queue) type and # of cycles to do
 * @post    the current thread has waited the appropriate amount of time, and its start/stop time has been outputted to screen, file, or both
 * @return  NONE
 */
void procWait(string type, string cycles);



#endif /* defined(__Sim01__Utils__) */
