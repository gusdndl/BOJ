#include <string>
#include <vector>
#include <queue>
using namespace std;

int solution(vector<int> players, int m, int k) {
    int answer = 0;    // 총 서버 증설 횟수
    int server = 0;    // 현재 유지 중인 서버 수
    queue<pair<int, int>> time;  // (반납 시간, 서버 수) 정보를 저장하는 큐
    
    for(int i = 0; i < players.size(); ++i) {
        // 1. 서비스 기간이 끝난 서버 반납
        if(!time.empty() && time.front().first == i) {
            server -= time.front().second;  // 서버 수 감소
            time.pop();  // 큐에서 제거
        }
        
        // 2. 현재 접속자를 처리하기 위해 서버가 필요한 경우
        if(m <= players[i]) {
            int required = players[i] / m;  // 필요한 서버 수 계산
            
            // 3. 현재 서버로 감당할 수 없다면 증설
            if (required > server) {
                int newServer = required - server;  // 추가로 필요한 서버 수
                server += newServer;  // 현재 서버 수 증가
                answer += newServer;  // 총 증설 횟수에 추가
                time.push({i + k, newServer});  // k시간 후 반납할 서버 정보 기록
            }
        }
    }
    
    return answer;  // 총 증설 횟수 반환
}