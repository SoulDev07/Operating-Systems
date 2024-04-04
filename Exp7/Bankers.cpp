#include <iostream>
#include <vector>

using namespace std;

bool isSafe(int proc, int res, vector<vector<int>> &alloc, vector<vector<int>> &max_need, vector<int> &avail)
{
    vector<int> work = avail;
    vector<bool> finish(proc, false);
    vector<int> safeSeq;

    vector<vector<int>> need(proc, vector<int>(res));
    for (int i = 0; i < proc; i++)
        for (int j = 0; j < res; j++)
            need[i][j] = max_need[i][j] - alloc[i][j];

    int numFinished = 0;
    bool progressMade;
    do
    {
        progressMade = false;

        // Check for processes that can be executed
        for (int i = 0; i < proc; i++)
        {
            if (!finish[i])
            {
                bool canBeDone = true;
                for (int j = 0; j < res; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canBeDone = false;
                        break;
                    }
                }
                if (canBeDone)
                {
                    // Execute process
                    for (int j = 0; j < res; j++)
                        work[j] += alloc[i][j];
                    finish[i] = true;
                    safeSeq.push_back(i);
                    numFinished++;
                    progressMade = true;
                }
            }
        }
    } while (progressMade && numFinished < proc);

    if (numFinished == proc)

    {
        cout << "\nSafe sequence: ";
        for (int i = 0; i < proc; i++)
        {
            cout << "P" << safeSeq[i];
            if (i != proc - 1)
                cout << " -> ";
        }
        cout << endl;
        return true;
    }

    cout << "\nDeadlock detected!";
    return false;
}

void requestResource(int proc, int res, vector<vector<int>> &alloc, vector<vector<int>> &max_need, vector<int> &avail)
{
    int process;
    vector<int> request(res);

    cout << "Enter process number (0 to " << proc - 1 << "): ";
    cin >> process;

    cout << "Enter resource request for process P" << process << ": ";
    for (int i = 0; i < res; i++)
        cin >> request[i];

    // Check if the request can be granted
    bool safeToAllocate = true;
    for (int i = 0; i < res; i++)
    {
        if (request[i] > avail[i] || request[i] > (max_need[process][i] - alloc[process][i]))
        {
            safeToAllocate = false;
            break;
        }
    }

    if (!safeToAllocate)
    {
        cout << "Resource request exceeds available resources or maximum need.\n";
        return;
    }

    // Temporarily allocate resources to check for safety
    vector<vector<int>> tempAlloc = alloc;
    vector<int> tempAvail = avail;

    for (int i = 0; i < res; i++)
    {
        tempAlloc[process][i] += request[i];
        tempAvail[i] -= request[i];
    }

    if (isSafe(proc, res, tempAlloc, max_need, tempAvail))
    {
        for (int i = 0; i < res; ++i)
        {
            alloc[process][i] += request[i];
            avail[i] -= request[i];
        }
    }
}

int main()
{
    int proc, res;

    // Number of processes and resources
    cout << "Enter the number of processes: ";
    cin >> proc;
    cout << "Enter the number of resources: ";
    cin >> res;

    vector<vector<int>> max_need(proc, vector<int>(res));
    vector<vector<int>> alloc(proc, vector<int>(res));
    vector<int> avail(res);

    // Input maximum need matrix
    cout << "\nEnter the maximum need matrix:\n";
    for (int i = 0; i < proc; i++)
    {
        cout << "For process P" << i << ": ";
        for (int j = 0; j < res; ++j)
            cin >> max_need[i][j];
    }

    // Input allocated resources matrix
    cout << "\nEnter the allocated resources matrix:\n";
    for (int i = 0; i < proc; i++)
    {
        cout << "For process P" << i << ": ";
        for (int j = 0; j < res; ++j)
            cin >> alloc[i][j];
    }

    // Input available resources
    cout << "\nEnter the available resources: ";
    for (int j = 0; j < res; ++j)
        cin >> avail[j];

    int choice;
    do
    {
        cout << "\nMenu:\n1. Check Safe State\n2. Request Resources\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            isSafe(proc, res, alloc, max_need, avail);
            break;
        case 2:
            requestResource(proc, res, alloc, max_need, avail);
            break;
        case 3:
            break;
        default:
            cout << "Invalid choice! Try again.";
        }
    } while (choice != 3);

    return 0;
}
