#include "task2.h"

std::vector <Client> generateClients(){
  int N;
  std::vector <Client> clients;
  srand(time(0));
  std::cout << "Введите кол-во клиентов\n";
  std::cin >> N;
  for(int i = 0; i < N; ++i){
    Client newClient;
    newClient.year = 2000 + rand() % 11;
    newClient.month = 1 + rand() % 12;
    newClient.id = 10 + rand() % 90;
    newClient.duration = 1 + rand() % 30;
    clients.push_back(newClient);
  }
  return clients;
}

bool comparator(Client a, Client b){
  if(a.year != b.year){
    return a.year < b.year;
  }
  if(a.duration != b.duration){
    return a.duration < b.duration;
  }
  return a.month > b.month;
}

std::vector <Client> filterClients(std::vector<Client> clients, int K){
  std::vector <Client> filteredClients;
  std::vector <Client> answer;
  for(Client x : clients){
    if(x.id == K){
      filteredClients.push_back(x);
    }
  }
  if(filteredClients.empty()){
    std::cout << "Нет данных\n";
    return answer;
  }
  std::sort(filteredClients.begin(),filteredClients.end(), comparator);
  int currentYear = 0;
  for(Client x : filteredClients){
    if(x.year != currentYear){
      answer.push_back(x);
      currentYear = x.year;
    }
  }
  return answer;
}

void printInfo(std::vector <Client> clients){
  for(Client x : clients){
    std::cout << x.year << " " << x.month << " " << x.duration << "\n";
  }
}

int inputId(){
  int K;
  std::cout << "Введите K\n";
  std::cin >> K;
  return K;
}

void answer2(){
  int K = inputId();
  std::vector<Client> clients = generateClients();
  std::vector<Client> answer = filterClients(clients, K);
  printInfo(answer);
}