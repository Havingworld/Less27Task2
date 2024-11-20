#include <iostream>
#include <vector>
#include <string>
#include <cassert>

class Employee {
    std::string cName;
public:
    Employee(const std::string& inName) : cName(inName) {}

    std::string getName() {
        return cName;
    }
};

class Worker : public Employee {
    char cInstr{ NULL };
public:
    Worker(const std::string& inName) : Employee(inName) {}

    void receiveInstruction() { // set instruktion to worker
        char cTaskType = { 65 + rand() % 3 };
        cInstr = { cTaskType };
        std::cout << "Worker " << getName() << " received instruction: " << getInstr() << std::endl;

    }

    char getInstr() {
        return cInstr;
    }

};

class Manager : public Employee {
    Worker** workers{ nullptr };
    int nIDManager{ 0 };
    int nWorkersPerTeam{ 0 };
    int nSetTasks{ 0 };

public:
    Manager(const std::string& inName, int inWorkersPerTeam ) : Employee(inName), nWorkersPerTeam(inWorkersPerTeam) {
        assert(inWorkersPerTeam >= 0);
        workers = new Worker * [inWorkersPerTeam];
        for (int i{ 0 }; i < nWorkersPerTeam; ++i) {
            std::string cName = {"Worker_" + this->getName().back() + std::to_string(i)};
            workers[i] = new Worker(cName);
        }
    }


    void InstructionsToWorker(int instruction) { // set instruktions to workers in team

        int temp = instruction + this->nIDManager;
        std::srand(temp);

        int tasksCount = rand() % this->nWorkersPerTeam + 1;
        std::cout << "Manager " << getName() << " is distributing " << tasksCount << " tasks." << std::endl;

        for (int i{ 0 }; i < this->nWorkersPerTeam; ++i) {
            if (workers != nullptr && this->nSetTasks < this->nWorkersPerTeam && tasksCount > 0) {
                Worker* refWorker{ getWorkerAt(i) };
                if (refWorker->getInstr() == NULL) {
                    refWorker->receiveInstruction();
                    ++this->nSetTasks;
                    --tasksCount;
                }
                
            }
        }
    }

    Worker* getWorkerAt(int index) {
        if (this == nullptr) return nullptr;
        if (index < 0) return nullptr;
        if (index >= nWorkersPerTeam) return nullptr;
        return workers[index];
    }

    int getWorkersPerTeam() {
        return nWorkersPerTeam;
    }
};

class Company {
    Manager** teams{ nullptr };
    int nNumTeams{ 0 };
public:
    Company(int inNumTeams, int inNumWorkersPerTeam) : nNumTeams(inNumTeams) {

        teams = new Manager * [inNumTeams];
        for (int i{ 0 }; i < inNumTeams; ++i) {
            std::string cName = { "Manager_" + std::to_string(i) };
            teams[i] = new Manager(cName, inNumWorkersPerTeam);
        }
      
    }

    void InstructionsToManager() {  //get instructions to managers
        int instruction{ 0 };
        while (instruction != -1) {  
            std::cout << "Enter instruction (any integer), -1 to finish: ";
            std::cin >> instruction;
            if (instruction == -1) break;
            
            for (int i{ 0 }; i < this->nNumTeams; ++i) {
                teams[i]->InstructionsToWorker(instruction);
            }
            if (checkTask()) {
                std::cout << "All workers buised.";
                break;
            }
        }
    }

    Manager* getManagerAt(int index) {
        if (this == nullptr) return nullptr;
        if (index < 0) return nullptr;
        if (index >= nNumTeams) return nullptr;
        return teams[index];
    }

    bool checkTask() {  // Checks if all workers have been assigned a task.
        bool bSetAllTask{ false };
        for (int i{ 0 }; i < this->nNumTeams; ++i) {
            Manager* manager{ getManagerAt(i) };
            for (int j{ 0 }; j < manager->getWorkersPerTeam(); j++) {
                manager->getWorkerAt(j)->getInstr() ? bSetAllTask = { true }: bSetAllTask = { false };
            }
        }
        return bSetAllTask;
    }

    int getNumTeams() {
        return nNumTeams;
    }
};

int main() {
    int numTeams{ 0 }, numWorkersPerTeam{ 0 };
    std::cout << "Enter number of teams: ";
    std::cin >> numTeams;

    std::cout << "Enter number of workers per team: ";
    std::cin >> numWorkersPerTeam;

    Company* company = new Company(numTeams, numWorkersPerTeam);
    company->InstructionsToManager();

    //for (int i{ 0 }; i < company->getNumTeams(); ++i) {
    //    delete company->getManagerAt(i);
    //}
    delete company;

    return 0;
};
