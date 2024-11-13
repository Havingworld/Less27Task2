#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <cassert>

class Employee {
    std::string cName{""};
public:
    Employee(std::string inName) : cName(inName) {}

    void setName() {
        std::cin >> cName;
    }

    std::string getName() {
        return cName;
    }
    //virtual ~Employee() = default;
    //virtual void receiveInstruction(int instruction) = 0;
};

class Worker : Employee {
public:
    Worker(std::string inName) : Employee(inName) {}

    void receiveInstruction(int instruction) {
        std::cout << "Worker " << getName() << " received instruction: " << instruction << std::endl;
    }
};

class Manager : Employee {

    int nCountWorkers{0};
    //std::vector <Worker> workers{}; // Работники под командой менеджера
    Worker** workers{ nullptr }; //массив работников

public:
    //Manager(std::string inName) : Employee(inName) {}
    Manager(int inCountWorkers) :nCountWorkers(inCountWorkers) {
        assert(inCountWorkers >= 0);
        workers = new Worker*[inCountWorkers];
        for (int = i; i < inCountWorkers; ++i){
            workers[i] = new Worker;
        }
    }

    void receiveInstruction(int instruction) {
        int managerID = rand() % 100; // Пример генерации уникального ID для менеджера
        int hash = instruction + managerID;
        std::srand(hash);

        int tasksCount = rand() % (workers.size() + 1);
        std::cout << "Manager " << getName() << " is distributing " << tasksCount << " tasks." << std::endl;

        for (int i = 0; i < tasksCount; ++i) {
            if (!workers.empty()) {
                int randomWorkerIndex = rand() % workers.size();
                workers[randomWorkerIndex].receiveInstruction(instruction);
                workers.erase(workers.begin() + randomWorkerIndex); // Удаляем работника, чтобы не повторять
            }
        }
    }

    void addWorker(std::vector<Worker> worker) {
        workers.push_back(worker);
    }

};

class Company {
    //std::vector<Manager> teams; // Команды с менеджерами
    int nCountTeams{0};
    int mWorkersPerTeam{0};
    Manager** teams {nullptr};
public:

   /* Company(int numTeams, int numWorkersPerTeam) {
        for (int i = 0; i < numTeams; ++i) {
            std::string managerName = "Manager" + std::to_string(i + 1);
            auto manager = std::make_shared<Manager>(managerName);
            teams.push_back(manager);
            for (int j = 0; j < numWorkersPerTeam; ++j) {
                std::string workerName = "Worker" + std::to_string(i + 1) + "_" + std::to_string(j + 1);
                auto worker = std::make_shared<Worker>(workerName);
                manager->addWorker(worker); // Добавить работника к менеджеру
            }
        }
    }    */

    Company (int inCountTeams, int inWorkersPerTeam):nCountTeams(inCountTeams){
        assert(inCountTeams >=0);
        teams = mew Manager*[inCountTeams];
        for (int = i; i < inCountWorkers; ++i){
            teams[i] = new Manager(inWorkersPerTeam);
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
}
