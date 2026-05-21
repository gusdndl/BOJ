import java.util.*;
class Solution {
    public String solution(int[] numbers) {
        String answer = "";
        String[] str= new String[numbers.length];
        
        int j=0;
        for(int i: numbers){
            str[j++]= String.valueOf(i);
        }
        
        Arrays.sort(str, new Comparator<String>(){
            public int compare(String o1, String o2){
                return -(o1+o2).compareTo(o2+o1);
            }
        });
        
        for(String i: str){
            answer+=i;
        }
        
        for(int i=0; i<answer.length(); i++){
            if(answer.charAt(i)!='0'||i==answer.length()-1){
                answer= answer.substring(i);
                break;
            }
        }
        
        return answer;
    }
}