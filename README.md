# Computer_Networks
This project is divided into 2 phases. It is not possible to proceed to phase 2 without completing phase 1. In each phase you will have multiple concurrent processes that will communicate over either TCP or UDP sockets.  


## Phase 1:

In this phase, each hospitals opens its input file (HosptialA.txt, HosptialB.txt or HosptialC.txt) and opens a TCP connection with the USC health center to send departments' names and the required range of severity of sympyoms of each department. It sends one packet per department that it has. This means that the hospital should know the static TCP port number of the USC health center in advance. In other words you must hardcode the TCP port number of the the USC health center in the hospital code. Table 1 shows how static UDP and TCP port numbers should be defined for each entity in this project. Each hospital then uses one dynamically-assigned TCP port number (different for each hospital) and establishes one TCP connection to the USC health center (see Requirement 1 of the project description). Thus, there are three different TCP connections to the USC health center (one from each hosptial). 

As soon as the USC health center receives the packets with departments' names and the range of severity of sympyoms requirements of the departments from all the hospitals, it stores locally the available departments in the system along with the hospitals names who offer the departments. It is up to you to decide how you are going to store this information. It may be stored in a file or in the memory (e.g. through an array or a linked list of structs that you can define). Before you make this decision, you have to think of how a student sends their application later to the USC health center. We expect that the USC health center knows which departments are available, which hospitals offer them and their range of severity of sympyoms requirements. 

## Phase 2:

We have two parts for phase 2. The first part uses TCP connections and the second part uses UDP connections. 

In phase 2 of this project, each student sends his/her application to the USC health center through TCP connections. More specifically, each student opens a TCP connection to the USC health center to send the packets with the details of his/her application (the severity of symptoms, department interest1, department interest2 and department interest3). This means that each student should know in advance the static TCP port of the USC health center. You can hardcode this static TCP port and set the value according to Table 1. Then, it opens a TCP connection to this static TCP port of the USC health center. The TCP port number on the student side of the TCP connection is dynamically assigned (from the operating system). Thus there are five TCP connections to the USC health center, one for each student in the system. Each student sends one packet to the USC health center for each line in the application file (at most 4 packets in total).

When the USC health center receives all the packets from a student, it searches his/her interested department in the file or the array/linked list that stored the information of departments. If both of his/her applied departments are not in the system, the USC health center replies with number 0 to the student. The student realizes that his application is invalid and no further waits for the information. 

If the program exists, then the USC health center replies a valid to the student and does the following, 

A) Check the student’s symptom number and compare it with the range of severity of symptoms requirement of the departments that he/she applies to make the decision based on the priority of the program. 

B) Send a packet with rejection to each student who is not admitted to any departments and send a packet with accept information (including accept, department name, hospital name) to each student who is admitted. 

C) For each admitted student, send a packet with the student’s information (including student name, symptom number , admitted department) to the corresponding hospital. 

the USC health center uses UDP connections to communicate with the hospitals and the students. For part B), the USC health center should know the static UDP port of each student in advance. You can hardcode these static UDP ports and set the value according to Table 1. The UDP port number on the USC health center side of the UDP connection is dynamic for this part. There is one UDP connection from the USC health center to each student (except whose application is invalid). For part C), the USC health center should know in advance the static UDP port of the hospitals. You can hardcode these static UDP ports and set the value according to Table 1. Then it opens a UDP connection to this static UDP port of the hospital. The UDP port number on the USC health center side of the UDP connection is dynamic for this part. There is one UDP connection from the USC health center to each hospitals.
