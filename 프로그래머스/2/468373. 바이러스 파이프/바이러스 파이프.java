import java.util.*;

class Node {
    int x;
    int y;
    
    Node(int x, int y) {
        this.x = x;
        this.y = y;
    }
}

class Edge {
    int vertex;
    int type;
    
    Edge(int vertex, int type) {
        this.vertex = vertex;
        this.type = type;
    }
}

class Solution {
    
    List<List<Node>> map = new ArrayList<>();
    List<List<Edge>> edgeMap = new ArrayList<>();
    int[] vis;
    int K;
    int answer = 0;
    
    public int solution(int n, int infection, int[][] edges, int k) {
        
        K = k;
        vis = new int[n+1];
        
        for (int i=0; i<=3; i++) {
            map.add(new ArrayList<>());
        }
        
        for (int i=0; i<=n; i++) {
            edgeMap.add(new ArrayList<>());
        }
        
        
        for (int i=0; i<edges.length; i++) {
            int x = edges[i][0];
            int y = edges[i][1];
            int type = edges[i][2];
            
            
            map.get(type).add(new Node(x,y));
            edgeMap.get(x).add(new Edge(y, type));
            edgeMap.get(y).add(new Edge(x, type));
        }
        
        Arrays.fill(vis, -1);
        
        vis[infection] = 0;
        
        dfs(0);
        
        
        return answer;
    }
    
    void dfs(int cur) {
        if (cur >= K) {
            
            int cnt = 0;
            
            for (int i=1; i<vis.length; i++) {
                if (vis[i] != -1) cnt++;
            }
            
            answer = Math.max(answer, cnt);
            
   
            return;
        }
        
        for (Node node : map.get(1)) {
            markInfection(node, cur+1, 1);
        }
        
        dfs(cur+1);
        
        for (Node node : map.get(1)) {
            clearInfection(node, cur+1);
        }
        
        dfs(cur+1);
        
        for (Node node : map.get(2)) {
            markInfection(node, cur+1, 2);
        }
        
        dfs(cur+1);
        
        for (Node node : map.get(2)) {
            clearInfection(node, cur+1);
        }
        
        
        for (Node node : map.get(3)) {
            markInfection(node, cur+1, 3);
        }
        
        dfs(cur+1);
        
        for (Node node : map.get(3)) {
            clearInfection(node, cur+1);
        }
    }
    
    void markInfection(Node node, int time, int num) {
        
        if (vis[node.x] == -1 && vis[node.y] != -1) {
            bfs(node.y, num, time);
        }
        
        if (vis[node.y] == -1 && vis[node.x] != -1) {
            bfs(node.x, num, time);
        }
    }
    
    void clearInfection(Node node, int time) {
        if (vis[node.x] == time) {
            vis[node.x] = -1;
        }
        if (vis[node.y] == time) {
            vis[node.y] = -1;
        }
    }
    
    void bfs(int start, int num, int time) {
        
        Queue<Edge> q = new ArrayDeque<>();
        
        q.add(new Edge(start, num));
        
        while (!q.isEmpty()) {
            
            Edge cur = q.poll();
            
            for (Edge next : edgeMap.get(cur.vertex)) {
                
                if (vis[next.vertex] != -1 || next.type != num) continue;
                
                vis[next.vertex] = time;
                q.add(next);
            }
        }

    }
}