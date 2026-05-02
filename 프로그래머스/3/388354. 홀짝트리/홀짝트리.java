import java.util.*;

class Solution {
    static Map<Integer,List<Integer>> graph;
    static int holzzak;
    static int yeokhholzzak;
    static Set<Integer> visited;
    static int[] result;
    
    public int[] solution(int[] nodes, int[][] edges) {
        init(nodes,edges);
        sol(nodes);
        return result;
    }
    
    private static void init(int[] nodes, int[][] edges) {
        graph = new HashMap<>();
        visited = new HashSet<>();
        result = new int[2];

        for(int node : nodes) {
            graph.put(node,new ArrayList<>());
        }
        
        for(int[] edge : edges) {
            int from = edge[0];
            int to = edge[1];
            
            graph.get(from).add(to);
            graph.get(to).add(from);
        }
    }
    
    private static void sol(int[] nodes) {
        
        for(int node : nodes) {
            if(visited.contains(node)) continue;
            
            holzzak = 0;
            yeokhholzzak = 0;
        
            bfs(node);
            
            if(holzzak ==1) {
                result[1]++;
            }
            if(yeokhholzzak==1) {
                result[0]++;
            }
            
            
        }
    }
    
    private static void bfs(int node) {
        Queue<Integer> q = new LinkedList<>();
        q.add(node);
        visited.add(node);
        
        while(!q.isEmpty()) {
            int now = q.poll();
            
            int cnt = graph.get(now).size()-1;
            
            //현재 노드가 짝수
            if(now % 2 ==0) {
                if(cnt % 2 ==0) {
                    holzzak++;
                }else {
                    yeokhholzzak++;
                }
            }else {
                if(cnt % 2 ==1) {
                    holzzak++;
                }else {
                    yeokhholzzak++;
                }
            }
            
            for(int next : graph.get(now)) {
                if(visited.contains(next)) continue;
                
                q.add(next);
                visited.add(next);
            }
        }
    }
}