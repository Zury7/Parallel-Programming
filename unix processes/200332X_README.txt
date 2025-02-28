##################
###  OVERVIEW  ###
##################

- Project Name : Programming Lab 1 
- Version : 1.0
- Module Code : CS 3480
- Module Name : Secure App Development 
- Contributor : Kurukulasooriya KVR 200332X
- Finalized on : 23rd August 2023
- Description : This lab is aimed on getting a good experience about processs' behavior 
		using fork, exec, exit and wait system calls. 
- Related files :  lab1p1.c & lab1p2.c
		   a.c, b.c and c.c for Inputs 
		   200332XReport.pdf

###########################
### INITIAL REQUIREMNTS ###
###########################

- All the built files are required to run in a Linux based Environment installed in a VMWare 
  to mitigate the potential harmful impact from exhausting system infrastucture by spawning 
  child processes in an infinite loop.

#################################
### INSTALLATION REQUIREMENTS ###
#################################

- No additional installation is required. 

##############################################
### INSTRUCTIONS ON HOW TO BUILD & EXECUTE ###
##############################################

-To Build the code:
	1. In the terminal, go to the directory where the lab1p1.c & lab1p2.c are saved.
	2. Build those 2 files by running the following commands:
		gcc lab1p1.c -o lab1p1
		gcc lab1p2.c -o lab1p2
-To Run(Execute) the code:
    Lab1p1 :
	1. Run the following command to execute lab1p1
		./lab1p1 /bin/echo Linux is cool + /bin/echo But I am sleepy +/bin/echo Going to sleep now + /bin/sleep 5 + /bin/echo Now I am awake
    Lab1p2 :
      Example 01:
	1. Run the following command to execute lab1p2 for the first example. 
		./lab1p2 gcc -c %
	2. Input the following.
		a.c
		b.c
		c.c
	3. Press CTRL+D to terminate.
	4. Check for the compiled files of a.o,b.o & c.o and Run them using following command.
		./a.o
		./b.o
		./c.o
      Example 02:
	1. Run the following command to execute lab1p2 for the second example. 
		./lab1p2 gcc % % % % % %
	2. Input the following.
		-c a.c
		-c b.c
		-c c.c
		-o test a.o b.o c.o
	   ( The test file is a single file that combines the all a.o,b.o & c.o)
	3. Press CTRL+D to terminate.
	4. Check for the compiled files of a.o,b.o,c.o and test and Run them using following command.
	5. To check the functionality of test file, Run the following command.
		./test
    
		
















