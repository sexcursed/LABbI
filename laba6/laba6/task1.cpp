#include "task1.h"

std::vector <client> generate(int N){
    std::vector <client> clients;
    srand(time(0));
    for(int i = 0; i < N; ++i){
        client newClient;
        newClient.duration = 1 + rand() % 30;
        newClient.id = 10 + rand() % 90;
        newClient.year = 2000 + rand() % 11;
        newClient.month = 1 + rand() % 12;
        clients.push_back(newClient);
    }
    return clients;
}

void outClient(client x){
    std::cout << x.duration << " " << x.id << " " << x.year << " " << x.month << "\n";
}

void outClients(std::vector <client> clients){
    int i = 1;
    for(auto x : clients){
        std::cout << i << ". ";
        outClient(x);
        i++;
    }
}

bool comparator(client& a, client& b){
    if(a.duration != b.duration){
        return a.duration < b.duration;
    }
    else if(a.year != b.year){
        return a.year < b.year;
    }
    return a.month < b.month;
}

void answer1(int N){
    std::vector <client> clients = generate(N);
    std::sort(clients.begin(),clients.end(),comparator);
    outClients(clients);
    std::cout << "Строка данных с мин. длительностью занятий и самой ранней датой:\n";
    outClient(clients[0]);
}
