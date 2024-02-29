#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

struct Process
{
    int id, at, bt, wt, tat;

    bool operator==(const Process &other)
    {
        return id == other.id && at == other.at && bt == other.bt &&
               wt == other.wt && tat == other.tat;
    }
};

bool sortProcess(Process &p1, Process &p2)
{
    return tie(p1.bt, p1.at, p1.id) < tie(p2.bt, p2.at, p2.id);
}

int main()
{
    int len, at, bt;
    vector<Process> processes, availableProcesses, completedProcesses;

    // Take user input
    cout << "Enter no of Processes: ";
    cin >> len;

    for (int i = 0; i < len; i++)
    {
        cout << "\nFor Process " << i + 1 << ":\n";
        cout << "Enter Arrival time: ";
        cin >> at;
        cout << "Enter Burst time: ";
        cin >> bt;
        processes.push_back({i + 1, at, bt, 0, 0});
    }

    int time = 0;
    while (completedProcesses.size() < len)
    {
        // Update available processes list
        for (Process &p : processes)
        {
            if (p.at <= time)
            {
                availableProcesses.push_back(p);
                processes.erase(find(processes.begin(), processes.end(), p));
            }
        }

        // Sort processes by bust time and then arrival time
        sort(availableProcesses.begin(), availableProcesses.end(), sortProcess);

        Process &currentProcess = availableProcesses[0];
        currentProcess.wt = time - currentProcess.at;
        currentProcess.tat = currentProcess.wt + currentProcess.bt;

        // Update current time
        time += currentProcess.bt;

        // Update completed processes list
        completedProcesses.push_back(currentProcess);
        availableProcesses.erase(find(availableProcesses.begin(), availableProcesses.end(), currentProcess));
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