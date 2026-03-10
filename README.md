[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/LzV4HtNX)
# Round Robin (RR) CPU Scheduling — C Implementation

## 🎯 Objective

To implement the **Round Robin CPU Scheduling Algorithm** using the C programming language.

Round Robin is a **preemptive scheduling algorithm** where each process gets a fixed
amount of CPU time called the **Time Quantum** in cyclic order.

---

## 🧠 Algorithm Overview

1. Read number of processes `n`
2. For each process, read:

   * Process ID (PID)
   * Arrival Time (AT)
   * Burst Time (BT)
3. Read Time Quantum `q`
4. Set Remaining Time = Burst Time
5. Start system clock at time = 0
6. Repeat until all processes complete:

   * Traverse process list in order
   * If process has arrived and remaining time > 0:

     * Execute for:

       * `q` units if remaining time > q
       * Remaining time otherwise
     * Update time
     * Reduce remaining time
     * If process finishes:

       * Record completion time
7. Compute:

   * Turnaround Time
   * Waiting Time
   * Averages
8. Print results

---

## 📥 Input Format

```text
n
PID AT BT
PID AT BT
...
q
```

### Where

| Symbol | Meaning             |
| ------ | ------------------- |
| n      | Number of processes |
| PID    | Process ID          |
| AT     | Arrival Time        |
| BT     | Burst Time          |
| q      | Time Quantum        |

---

## 📤 Output Format

```text
Waiting Time:
PID WT
...

Turnaround Time:
PID TAT
...

Average Waiting Time: X.XX
Average Turnaround Time: X.XX
```

---

## 🧮 Formulas Used

### Completion Time

Time at which process finishes execution.

### Turnaround Time

TAT = Completion Time − Arrival Time

### Waiting Time

WT = Turnaround Time − Burst Time

### Averages

Average WT  = Sum of WT / n
Average TAT = Sum of TAT / n

---

## ▶️ Compilation & Execution

### Compile

gcc rr.c -o rr

### Run

./rr

---

## 📁 Files in Repository

rr.c              → C program implementation
run.sh            → Compile & run script
autograding.json  → GitHub Classroom test configuration
README.md         → Assignment instructions
tests/            → Input and expected outputs

---

## ⚠️ Important Notes

* Round Robin is **preemptive**
* Each process gets equal CPU share
* Small quantum → more context switching
* Large quantum → behaves like FCFS
* CPU may be idle if no process has arrived
* Output must match format exactly
* Print averages to **two decimal places**

---

## 📊 Learning Outcomes

Students will learn:

* Preemptive scheduling concepts
* Time-sharing systems
* Process queue simulation
* Waiting & turnaround time calculation

---

## 🧪 Test Cases

This assignment includes **5 test cases** to verify:

* Scheduling correctness
* Time quantum handling
* CPU idle handling
* Output format accuracy

---

## 🧑‍🏫 Evaluation Scheme

| Component          | Marks   |
| ------------------ | ------- |
| Scheduling Logic   | 40      |
| Time Calculations  | 30      |
| Output Format      | 20      |
| Passing Test Cases | 10      |
| **Total**          | **100** |

---

## 🧑‍⚖️ Academic Integrity

* Submit your own work
* Do not copy code
* Plagiarism checks may be used
