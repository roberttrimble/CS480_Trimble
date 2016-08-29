//
//  Struct.h
//  Sim01
//
//  Created by 348190 on 10/2/15.
//  Copyright (c) 2015. All rights reserved.
//

#ifndef __Sim01__Struct__
#define __Sim01__Struct__

#include <stdio.h>
#include <string>

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

#endif /* defined(__Sim01__Struct__) */
