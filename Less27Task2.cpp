#include <iostream>
#include <vector>
#include <string>

class Employee {
    std::string cName;
public:
    Employee(const std::string& inName) : cName(inName) {}

    std::string getName() {
        return cName;
    }
};

class Worker : public Employee {
public:
    Worker(const std::string& inName) : Employee(inName) {}

    void receiveInstruction(int instruction) {
        std::cout << "Worker " << getName() << " received instruction: " << instruction << std::endl;
    }
};

class Manager : public Employee {
    std::vector<Worker> workers; // Работники под командой менеджера
    int nIDManager{ 0 };
public:
    Manager(const std::string& inName) : Employee(inName) {}

    void receiveInstruction(int instruction) {
       
        int hash = instruction + nIDManager;
        std::srand(hash);

        int tasksCount = rand() % (workers.size() + 1);
        std::cout << "Manager " << getName() << " is distributing " << tasksCount << " tasks." << std::endl;

        for (int i = 0; i < tasksCount; ++i) {
            if (!workers.empty()) {
                //int randomWorkerIndex = rand() % workers.size();
                workers[i].receiveInstruction(instruction);
                workers.erase(workers.begin() + i); // Удаляем работника, чтобы не повторять
            }
        }
    }

    void addWorker(Worker& worker) {
        workers.push_back(worker);
    }

};

class Company {
    std::vector<Manager> teams; // Команды с менеджерами
public:
    Company(int numTeams, int numWorkersPerTeam) {
        for (int i = 0; i < numTeams; ++i) {
            std::string managerName = "Manager_" + i;
            Manager manager(managerName);          
            teams.push_back(manager);
            for (int j = 0; j < numWorkersPerTeam; ++j) {
                std::string workerName = "Worker_" + std::to_string(i) + "_" + std::to_string(j);
                Worker worker(workerName);         
                manager.addWorker(worker); // Добавить работника к менеджеру
            }
        }
    }

    void receiveInstructions() {
        int instruction;
        while (true) {
            std::cout << "Enter instruction (any integer), -1 to finish: ";
            std::cin >> instruction;
            if (instruction == -1) break;

            for (int i = 0; i < teams.size(); ++i) {
                teams[i].receiveInstruction(instruction);
            }
        }
    }
};

int main() {
    int numTeams, numWorkersPerTeam;
    std::cout << "Enter number of teams: ";
    std::cin >> numTeams;

    std::cout << "Enter number of workers per team: ";
    std::cin >> numWorkersPerTeam;

    Company company(numTeams, numWorkersPerTeam);
    company.receiveInstructions();

    return 0;
};