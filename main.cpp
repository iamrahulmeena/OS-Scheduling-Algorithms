#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

// Process class with necessary attributes and methods
class Process {
public:
    int id, burstTime, arrivalTime, priority, waitingTime, turnaroundTime, remainingTime;

    Process(int id, int burstTime, int arrivalTime, int priority = 0)
        : id(id), burstTime(burstTime), arrivalTime(arrivalTime), priority(priority), remainingTime(burstTime) {}

    // Calculate Waiting Time and Turnaround Time
    void calculateTimes(int startTime) {
        waitingTime = startTime - arrivalTime;
        turnaroundTime = waitingTime + burstTime;
    }
};

// Base class for scheduling algorithms
class Scheduler {
public:
    virtual void schedule(vector<Process>& processes) = 0; // Abstract method to schedule processes
    virtual void displayResults(const vector<Process>& processes) const = 0; // Display results for each algorithm
    virtual ~Scheduler() {}
};

// FCFS Scheduling - First Come First Serve
class FCFS : public Scheduler {
public:
    void schedule(vector<Process>& processes) override {
        sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
            return a.arrivalTime < b.arrivalTime;
        });

        int totalTime = 0;
        for (auto& p : processes) {
            p.calculateTimes(totalTime);
            totalTime += p.burstTime;
        }
    }

    void displayResults(const vector<Process>& processes) const override {
        cout << "\nFCFS Scheduling Results:\n";
        for (const auto& p : processes) {
            cout << "Process " << p.id << " - Waiting Time: " << p.waitingTime
                 << ", Turnaround Time: " << p.turnaroundTime << "\n";
        }
    }
};

// SJF Scheduling - Shortest Job First (Non-Preemptive)
class SJF : public Scheduler {
public:
    void schedule(vector<Process>& processes) override {
        sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
            return a.burstTime < b.burstTime;
        });

        int totalTime = 0;
        for (auto& p : processes) {
            p.calculateTimes(totalTime);
            totalTime += p.burstTime;
        }
    }

    void displayResults(const vector<Process>& processes) const override {
        cout << "\nSJF Scheduling Results:\n";
        for (const auto& p : processes) {
            cout << "Process " << p.id << " - Waiting Time: " << p.waitingTime
                 << ", Turnaround Time: " << p.turnaroundTime << "\n";
        }
    }
};

// Priority Scheduling
class PriorityScheduling : public Scheduler {
public:
    void schedule(vector<Process>& processes) override {
        sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
            return a.priority < b.priority;
        });

        int totalTime = 0;
        for (auto& p : processes) {
            p.calculateTimes(totalTime);
            totalTime += p.burstTime;
        }
    }

    void displayResults(const vector<Process>& processes) const override {
        cout << "\nPriority Scheduling Results:\n";
        for (const auto& p : processes) {
            cout << "Process " << p.id << " - Waiting Time: " << p.waitingTime
                 << ", Turnaround Time: " << p.turnaroundTime << "\n";
        }
    }
};

// Round Robin Scheduling
class RR : public Scheduler {
    int timeQuantum;
public:
    RR(int tq) : timeQuantum(tq) {}

    void schedule(vector<Process>& processes) override {
        queue<Process*> q;
        int totalTime = 0;

        for (auto& p : processes) {
            q.push(&p);
        }

        while (!q.empty()) {
            Process* p = q.front();
            q.pop();

            if (p->remainingTime > timeQuantum) {
                p->remainingTime -= timeQuantum;
                totalTime += timeQuantum;
                q.push(p);
            } else {
                totalTime += p->remainingTime;
                p->calculateTimes(totalTime);
                p->remainingTime = 0;
            }
        }
    }

    void displayResults(const vector<Process>& processes) const override {
        cout << "\nRound Robin Scheduling Results:\n";
        for (const auto& p : processes) {
            cout << "Process " << p.id << " - Waiting Time: " << p.waitingTime
                 << ", Turnaround Time: " << p.turnaroundTime << "\n";
        }
    }
};

// SRTF Scheduling - Shortest Remaining Time First
class SRTF : public Scheduler {
public:
    void schedule(vector<Process>& processes) override {
        sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
            return a.arrivalTime < b.arrivalTime;
        });

        int totalTime = 0, completed = 0;
        while (completed < processes.size()) {
            Process* currentProcess = nullptr;

            for (auto& p : processes) {
                if (p.arrivalTime <= totalTime && p.remainingTime > 0) {
                    if (!currentProcess || p.remainingTime < currentProcess->remainingTime) {
                        currentProcess = &p;
                    }
                }
            }

            if (currentProcess) {
                currentProcess->remainingTime--;
                totalTime++;

                if (currentProcess->remainingTime == 0) {
                    currentProcess->calculateTimes(totalTime);
                    completed++;
                }
            } else {
                totalTime++;
            }
        }
    }

    void displayResults(const vector<Process>& processes) const override {
        cout << "\nSRTF Scheduling Results:\n";
        for (const auto& p : processes) {
            cout << "Process " << p.id << " - Waiting Time: " << p.waitingTime
                 << ", Turnaround Time: " << p.turnaroundTime << "\n";
        }
    }
};

// Multilevel Queue Scheduling
class MultilevelQueueScheduling : public Scheduler {
public:
    void schedule(vector<Process>& processes) override {
        vector<Process> highPriority, lowPriority;

        // Separate processes based on priority
        for (auto& p : processes) {
            if (p.priority == 1) {
                highPriority.push_back(p);
            } else {
                lowPriority.push_back(p);
            }
        }

        // Process high priority first (FCFS)
        int totalTime = 0;
        for (auto& p : highPriority) {
            p.calculateTimes(totalTime);
            totalTime += p.burstTime;
        }

        // Then process low priority (FCFS)
        for (auto& p : lowPriority) {
            p.calculateTimes(totalTime);
            totalTime += p.burstTime;
        }

        processes = highPriority;
        processes.insert(processes.end(), lowPriority.begin(), lowPriority.end());
    }

    void displayResults(const vector<Process>& processes) const override {
        cout << "\nMultilevel Queue Scheduling Results:\n";
        for (const auto& p : processes) {
            cout << "Process " << p.id << " - Waiting Time: " << p.waitingTime
                 << ", Turnaround Time: " << p.turnaroundTime << "\n";
        }
    }
};

// Multilevel Feedback Queue Scheduling
class MultilevelFeedbackQueueScheduling : public Scheduler {
    int timeQuantum;
public:
    MultilevelFeedbackQueueScheduling(int tq) : timeQuantum(tq) {}

    void schedule(vector<Process>& processes) override {
        queue<Process*> highQueue, lowQueue;

        for (auto& p : processes) {
            highQueue.push(&p);
        }

        int totalTime = 0;
        while (!highQueue.empty()) {
            Process* p = highQueue.front();
            highQueue.pop();

            if (p->remainingTime > timeQuantum) {
                p->remainingTime -= timeQuantum;
                totalTime += timeQuantum;
                lowQueue.push(p); // Move to low priority queue
            } else {
                totalTime += p->remainingTime;
                p->calculateTimes(totalTime);
                p->remainingTime = 0;
            }
        }

        while (!lowQueue.empty()) {
            Process* p = lowQueue.front();
            lowQueue.pop();

            totalTime += p->remainingTime;
            p->calculateTimes(totalTime);
            p->remainingTime = 0;
        }
    }

    void displayResults(const vector<Process>& processes) const override {
        cout << "\nMultilevel Feedback Queue Scheduling Results:\n";
        for (const auto& p : processes) {
            cout << "Process " << p.id << " - Waiting Time: " << p.waitingTime
                 << ", Turnaround Time: " << p.turnaroundTime << "\n";
        }
    }
};

// Main function
int main() {
    int n, timeQuantum;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes;
    for (int i = 0; i < n; i++) {
        int id, burstTime, arrivalTime, priority;
        cout << "\nEnter details for Process " << i + 1 << ":\n";
        cout << "Process ID: ";
        cin >> id;
        cout << "Burst Time: ";
        cin >> burstTime;
        cout << "Arrival Time: ";
        cin >> arrivalTime;
        cout << "Priority (0 if not applicable): ";
        cin >> priority;

        processes.push_back(Process(id, burstTime, arrivalTime, priority));
    }

    cout << "Enter Time Quantum for Round Robin and Multilevel Feedback Queue: ";
    cin >> timeQuantum;

    // Initialize all scheduling algorithms
    vector<Scheduler*> schedulers = {
        new FCFS(),
        new SJF(),
        new PriorityScheduling(),
        new RR(timeQuantum),
        new SRTF(),
        new MultilevelQueueScheduling(),
        new MultilevelFeedbackQueueScheduling(timeQuantum)
    };

    // Execute all algorithms and display results
    for (auto scheduler : schedulers) {
        scheduler->schedule(processes);
        scheduler->displayResults(processes);
    }

    // Clean up dynamically allocated memory
    for (auto scheduler : schedulers) {
        delete scheduler;
    }

    return 0;
}
