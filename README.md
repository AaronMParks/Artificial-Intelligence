# Artificial-Intelligence
Collaboration: Aaron Parks (myself), Kaleb Perez, Victor Ekpenyong
The intelligent expert machine that we have created solves the waiting time it would take to see a doctor.  
To complete this task we used forward and backward chaining to implement the intelligent expert machine. 
Forward chaining much like it sounds, the inference engine goes through the facts and rules to get to an end result. Backward chaining following the notion
of forward chaining does the exact opposite, it has the end result and checks to validate that the facts and rules are correct for the specific result.
This program uses unordered maps paired with vectors. Unordered maps have a time complexity of O(1), and vectors are built on heap memory which allows them to grow and shrink automatically and only use the amount of memory it needs. 

The interface that we have built will ask a series of questions (symptoms) to determine which poison you have come in contact with, as well as how (ingested or inhaled) {this is the backward chaining process}
The forward chaining process does the exact opposite, knowing the end result it checks and makes sure that the rules are correct to get to the poison. Once the checks have been made it will then use the rule numbers to decide which treatment option it should be based on the poison.

Below is the result of one run of the program. We have since then removed the memory function (showing the amount of memory used by the program). The memory usage check we used only works on virtual environments (replit, VM BOX, etc).

Does the patient have a headache?
(Y/N)
y

Is the patient vomiting?
(Y/N)
n

Is the patient nauseous?
(Y/N)
y

Is the patient having seizures?
(Y/N)
n

Is the patient having diarrhea?
(Y/N)
n

CONCLUSION

Patient has been poisoned by -- Lead Poisoning Adult

Suggested Treatment -- EDTA Chelation therapy with high amounts of lead

The time taken for this program to run was: 0.000502 seconds.
Memory usage of the program is 45 KB.
