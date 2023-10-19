from collections import defaultdict
import sys

sys.setrecursionlimit(100000000)

def solution(edges, target):
    edge_dict = defaultdict(list)
    tree_dict = defaultdict(list)
    visited = [False]*len(target)
    visited[0] = True
    
    for a, b in edges :
        edge_dict[a-1].append(b-1)
        edge_dict[b-1].append(a-1)
        
    def dfs(node) :
        child_list = list()
        for child in edge_dict[node] :
            if visited[child] :
                continue
            visited[child] = True
            child_list.append(child)
        
        if not child_list :
            return [node]
        
        tree_dict[node].extend([0, sorted(child_list)])
        leaf_list = list()
        for child in child_list :
            leaf_list.extend(dfs(child))
        return leaf_list
    
    def search(node) :
        if len(tree_dict[node]) == 0 :
            return node
        
        idx = tree_dict[node][0]
        tree_dict[node][0] = (tree_dict[node][0] + 1) % len(tree_dict[node][1])
        return search(tree_dict[node][1][idx])
            
    leaf_list = dfs(0)
    leaf_cap_dict = { key : 0 for key in leaf_list }
    is_leaf_succeeded = { key : False if target[key] > 0 else True for key in leaf_list }
    order_list = list()
    
    while False in is_leaf_succeeded.values() :
        cur_node = search(0)
        leaf_cap_dict[cur_node] += 1
        
        if leaf_cap_dict[cur_node] > target[cur_node] :
            return [-1]
        if not is_leaf_succeeded[cur_node] and leaf_cap_dict[cur_node]*3 >= target[cur_node] :
            is_leaf_succeeded[cur_node] = True
        
        order_list.append(cur_node)    
      
    answer = [0]*len(order_list)
    for leaf in leaf_list :
        leaf_result = list()
        sur_cap = target[leaf] - leaf_cap_dict[leaf]
        leaf_result = [1]*(leaf_cap_dict[leaf] - sur_cap % 2 - sur_cap // 2) + [2]*(sur_cap % 2) + [3]*(sur_cap // 2)

        for idx, node in enumerate(order_list) :
            if node == leaf :
                answer[idx] = leaf_result.pop(0)
    
    return answer