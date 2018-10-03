#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>


struct process  // each process will be a struct
{
	int pid = 0;
	int execuutionTime = 0;
	int processPriority = 0;
	bool flag;
};

using namespace std;
int main()
{
	int fileInd = 1;
	pid_t pid;
	vector<process> file;
	string readFromFile; // will read from the input
	getline(cin, readFromFile);
	int quantum = 0;
	quantum = stoi(readFromFile); // reads the first string character as int stored into quantum
	vector<process> wait;


	// now to read the other processes from the file
	while (getline(cin, readFromFile))
	{
		int counter, endOfFile = 0;
		//read from file and store each struct variable into temp variables
		int spaceIndex = readFromFile.find(" ");
		int parentExecution = stoi(readFromFile.substr(0, spaceIndex));
		int parentPriority = stoi(readFromFile.substr(spaceIndex + 1, readFromFile.size()));


		//this instant of p1 struct stores the file content
		process p1;
		p1.pid = counter;
		p1.execuutionTime = parentExecution;
		p1.processPriority = parentPriority;
		p1.flag = true;

		// need to split if execution > quantum
		if (p1.execuutionTime > quantum)
		{
			parentExecution -= quantum;
			p1.flag = false;
			p1.execuutionTime = quantum;

			process p2;
			p2.execuutionTime = parentExecution;
			p2.pid = counter;
			p2.processPriority = parentPriority;
			p2.flag = true;


			if (wait.size() != 0)
			{
				int counter = 0;
				while (wait[counter].processPriority <= p2.processPriority && counter < wait.size())
				{
					counter++;
				}
				wait.insert(wait.begin() + counter, p2);
			}
			else
			{
				wait.push_back(p2);
			}
		}

		if (file.size() != 0)
		{
			int counter = 0;
			while (file[counter].processPriority <= p1.processPriority && counter < file.size())
			{
				counter++;
			}
			file.insert(file.begin() + counter, p1);

		}
		else
		{
			file.push_back(p1);
		}
		endOfFile = parentPriority;
		counter++;
	}

	while (!wait.empty())
	{
		while (file[fileInd].processPriority <= wait[0].processPriority && fileInd < file.size())
		{
			fileInd++;
		}

		while (file[fileInd].processPriority > wait[0].processPriority)
		{
			if (!wait.empty())
			{
				file.insert(file.begin() + fileInd, wait[0]);
				fileInd++;
				wait.erase(wait.begin());
			}
			else
			{
				break;
			}
		}
	}

	if (!wait.empty())
	{
		int i;
		for (i = 0; i < wait.size(); i++)
		{
			file.push_back(wait[i]);
		}
		wait.clear();
	}

	int j, k, z = 0;
	cout << "Scheduling queue:" << endl;
	cout << "\t";
	for (j = 0; j < file.size(); j++)
	{
		if (z == file.size() - 1) {
			cout << "(" << file[j].pid << "," << file[j].execuutionTime << "," << file[j].processPriority << ")" << endl;
			break;
		}
		cout << "(" << file[j].pid << "," << file[j].execuutionTime << "," << file[j].processPriority << "), ";
		z++;
	}

	process p3;
	for (k = 0; k < file.size(); k++)
	{
		pid = fork();
		p3 = file[k];
		if (pid == 0)
		{
			cout << "Process " << p3.pid << ": " << "exec time = " << p3.execuutionTime << ", " << "priority = " << p3.processPriority << endl;
		}
		sleep(p3.execuutionTime);

		if (pid == 0)
		{
			if (p3.flag)
			{
				cout << "Process " << p3.pid << " ends." << endl;
			}
			break;
		}
	}
	return 0;
}

