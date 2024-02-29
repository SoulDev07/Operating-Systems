#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <algorithm>

using namespace std;

struct Process
{
    int id, at, bt, rt, wt, tat, ldp;

    bool operator==(const Process &other)
    {
        return id == other.id && at == other.at && bt == other.bt &&
               wt == other.wt && tat == other.tat;
    }
};

bool sortProcess(Process &p1, Process &p2)
{
    return tie(p1.at, p1.id) < tie(p2.at, p2.id);
}

int main()
{
    int len, at, bt, tq;
    vector<Process> processes, remainingProcesses, completedProcesses;
    queue<Process> availableProcesses;

    // Take user input
    cout << "Enter no of Processes: ";
    cin >> len;
    cout << "Enter Time Slice: ";
    cin >> tq;

    for (int i = 0; i < len; i++)
    {
        cout << "\nFor Process " << i + 1 << ":\n";
        cout << "Enter Arrival time: ";
        cin >> at;
        cout << "Enter Burst time: ";
        cin >> bt;
        processes.push_back({i + 1, at, bt, bt, 0, 0, at});
    }

    sort(processes.begin(), processes.end(), sortProcess);

    int time = processes[0].at;
    remainingProcesses.clear();
    for (Process &p : processes)
    {
        if (p.at > time)
            remainingProcesses.push_back(p);
        else
            availableProcesses.push(p);
    }
    processes.swap(remainingProcesses);

    while (completedProcesses.size() < len)
    {
        Process &currentProcess = availableProcesses.front();
        availableProcesses.pop();
        currentProcess.wt += time - currentProcess.ldp;
        if (currentProcess.rt < tq)
        {
            time += currentProcess.rt;
            currentProcess.rt = 0;
        }
        else
        {
            time += tq;
            currentProcess.rt -= tq;
        }
        currentProcess.ldp = time;

        // Update available processes list
        remainingProcesses.clear();
        for (Process &p : processes)
        {
            if (p.at > time)
                remainingProcesses.push_back(p);
            else
                availableProcesses.push(p);
        }
        processes.swap(remainingProcesses);

        // Update completed processes list
        if (currentProcess.rt == 0)
        {
            currentProcess.tat = currentProcess.wt + currentProcess.bt;
            completedProcesses.push_back(currentProcess);
        }
        else
        {
            availableProcesses.push(currentProcess);
        }
    }

    // Calculate average waiting time and turn around time
    double avgWT, TTAT = 0;
    for (Process &process : completedProcesses)
    {
        avgWT += process.wt;
        TTAT += process.tat;
    }
    avgWT /= len;

    // Output results
    sort(completedProcesses.begin(), completedProcesses.end(), sortProcess);
    cout << "\nProcess ID\tArrival Time\tBurst Time\t Waiting Time\tTurnaround Time\n";
    for (Process &process : completedProcesses)
    {
        cout << "     " << process.id << "\t\t     " << process.at << "\t\t     " << process.bt;
        cout << "\t\t       " << process.wt << "\t     " << process.tat << "\n";
    }
    cout << "\nAverage Waiting Time: " << avgWT << endl;
    cout << "Total Turn Around Time: " << TTAT << endl;
    return 0;
}