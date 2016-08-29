//
//  Struct.h
//  Sim02
//
//  Created by 348190 on 10/2/15.
//  Copyright (c) 2015. All rights reserved.
//

#ifndef __Sim02__Struct__
#define __Sim02__Struct__

#include <stdio.h>
#include <string>
#include <queue>

using namespace std;

/*
 *-------------------------------------------------
 *Struct process
 *type holds the type of process (S(start), I(keyboard), etc)
 *cycles holds the amount of cylces to do
 *-------------------------------------------------
 */
struct process {
    string type;
    string cycles;
};

/*
 *-------------------------------------------------
 *Struct PCB
 *procNumber holds the PCB number (1, 2 etc)
 *procLength holds the amount of time it would take to complete the PCB
 *procBlock holds each process for the PCB
 *-------------------------------------------------
 */
struct PCB {
    int procNumber;
    int procLength;
    
    queue<process> procBlock;
};

#endif /* defined(__Sim02__Struct__) */
