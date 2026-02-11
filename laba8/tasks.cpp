#include "header.h"

void backrec9(){
  std::fstream input("input1.txt");
  int N,B;
  input >> N >> B;
  std::vector<Item> items(N);
  for(int  i = 0; i < N; ++i){
    items[i].index = i+1;
    input >> items[i].weight;
  }
  for(int  i = 0; i < N; ++i){
    input >> items[i].volume;
  }

  std::vector<int> maxWeight(B+1,-1);
  maxWeight[0]=0;
  std::vector<int> maxCount(B+1,0);
  std::vector<std::vector<bool>> usedItems(B+1,std::vector<bool>(N,false));

  for(int i = 0; i < N; ++i){
    int currentWeight = items[i].weight;
    for(int j = B-currentWeight;j >= 0;--j){
      if(maxWeight[j]<0) continue;
      int newWeight = j + currentWeight;

      bool better = false;
      if(maxWeight[newWeight] < maxWeight[j] + currentWeight){
        better = true;
      }
      else if(maxWeight[newWeight] == maxWeight[j]+currentWeight and maxCount[newWeight] < maxCount[j]+1){
        better = true;
      }

      if(better){
        maxWeight[newWeight] = maxWeight[j]+currentWeight;
        maxCount[newWeight] = maxCount[j]+1;
        usedItems[newWeight] = usedItems[j];
        usedItems[newWeight][i]=true;
      }
    }
  }
  int best = 0;
  for(int i = 1; i <= B; ++i){
    if(maxWeight[i]>maxWeight[best] or (maxWeight[i] == maxWeight[best] and maxCount[i] > maxCount[best])){
      best = i;
    }
  }
  std::vector<int> chosen;
  int totalVolume=0;

  for(int i = 0;i<N; ++i){
    if(usedItems[best][i]){
      chosen.push_back(items[i].index);
      totalVolume+=items[i].volume;
    }
  }
  for (int id : chosen) {
    std::cout << id << " ";
  }
  std::cout << "\nСуммарный вес: " << maxWeight[best] << "\n";
  std::cout << "Суммарный объем: " << totalVolume << "\n";

  input.close();
}

void homedyn3(){
  std::fstream input("input2.txt");
  std::fstream output("output2.txt");
  int N;
  input >> N;
  std::vector<std::vector<int>> board(N, std::vector<int>(N));
  std::vector<std::vector<int>> dp(N, std::vector<int>(N, 0));
  
  for(int i = 0; i < N; ++i){
    for (int j = 0; j < N; ++j){
      input >> board[i][j];
    }
  }

  dp[N-1][N-1] = board[N-1][N-1];
  for(int j = N-2; j >= 0; --j){
      dp[N-1][j] = dp[N-1][j+1] + board[N-1][j];
  }
  
  for(int i = N-2; i >= 0; --i){
    dp[i][N-1] = dp[i+1][N-1] + board[i][N-1];
  }
  for(int i = N-2; i >= 0; --i){
    for(int j = N-2; j >= 0; --j){
      if(dp[i+1][j] >= dp[i][j+1]){
        dp[i][j] = dp[i+1][j] + board[i][j];
      }
      else{
        dp[i][j] = dp[i][j+1] + board[i][j];
      }
    }
  }
  int maxsum = dp[0][0];
  std::cout <<"maxsum = " << maxsum << "\n";

  std::string path;
  int i = 0, j = 0;
    
  while(i!=N-1 || j !=N-1){
    if(i == N-1){
      path+='L';
      j++;
    }
    else if(j==N-1){
      path+='U';
      i++;
    }
    else{
      if(dp[i+1][j] >= dp[i][j+1]){
        path+='U';
        i++;
      }
      else{
        path+='L';
        j++;
      }
    }
  }


  std::cout << "path = " << path;
  output << maxsum << std::endl << path << std::endl;

  output.close();
  input.close();
}

void homedyn15(){
  int K,N;
  std::cout << "Введите основание системы счисления 2<=K<=10:";
  std::cin>> K;
  std::cout << "Введите количество разрядов N 1<=N<=20, N+K < 26:";
  std::cin>> N;
  if(K < 2 or K > 10 or N <= 1 or N >= 20 or N + K >= 26){
    std::cout << "Некорректные входные данные\n";
    return;
  }

  double nz,oz,tz;
  double n_nz,n_oz,n_tz;
  nz=K-1;
  oz=0;
  tz=0;
  for(int i=2;i<=N;++i){
    n_nz=(nz+oz+tz)*(K-1);
    n_oz=nz;
    n_tz=oz;
    nz=n_nz;
    oz=n_oz;
    tz=n_tz;
  }

  double result = nz+oz+tz;
  std::cout << std::fixed << std::setprecision(0);
  std::cout << result;

}