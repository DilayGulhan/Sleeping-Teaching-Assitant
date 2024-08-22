# Sleeping Teaching Assistant Problem

## Overview
This program simulates a scenario with a Teaching Assistant (TA) and several students in a waiting room. The TA can either be asleep or helping a student. Students arrive at random intervals and either wait for the TA to become available or leave if no seats are available. The TA helps students when they are available.

## Components
### TA Thread (ta function): 
Represents the Teaching Assistant who can either be asleep or assisting students.
### Student Threads (student function): 
Represents individual students who arrive at random intervals to seek help from the TA.
## Synchronization Mechanisms:
### Mutexes: 
Ensure mutual exclusion when accessing shared resources (help and during_help).
### Semaphores: 
Manage the synchronization between the TA and students (ta_ready and student_ready).

## Output
The output consists of messages indicating:

When the TA is helping a student and for how long.
When students are waiting, being helped, or leaving due to full chairs.
When the TA is sleeping.
## Notes
This simulation assumes a fixed number of chairs (NUM_CHAIRS) and students (NUM_STUDENTS).
The random sleep times simulate the variability in student arrival times and TA assistance durations.
