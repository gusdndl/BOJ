import java.util.*;

class Solution {
    public int[] solution(int[] fees, String[] records) {
        Map<String, Integer> parking = new HashMap<>();
        Map<String, Integer> totalFee = new TreeMap<>();
        
        for (String record : records) {
            String[] temp = record.split(" ");
            int time = getTime(temp[0]);
            String car = temp[1];
            String inOut = temp[2];
            
            if (inOut.equals("IN")) {
                parking.put(car, time);
            } else {
                if (!totalFee.containsKey(car)) {
                    totalFee.put(car, time - parking.get(car));
                } else {
                    totalFee.put(car, totalFee.get(car) + time - parking.get(car));
                }
                parking.remove(car);
            }
        }
        
        if (!parking.isEmpty()) {
            for (String car : parking.keySet()) {
                Integer fee = totalFee.get(car);
                fee = (fee == null) ? 0 : fee;
                totalFee.put(car, fee + (23 * 60 + 59) - parking.get(car));
            }
        }
        
        List<Integer> list = new ArrayList<>();
        for (Integer t : totalFee.values()) {
            int baseTime = fees[0];
            int baseFee = fees[1];
            int partTime = fees[2];
            int partFee = fees[3];
            
            if (t <= baseTime) {
                list.add(baseFee);
            } else {
                list.add((int) (baseFee + Math.ceil((double)(t - baseTime) / partTime) * partFee));
            }
        }
        
        return list.stream().mapToInt(Integer::intValue).toArray();
    }
    
    public int getTime(String s) {
        String[] temp = s.split(":");
        return Integer.parseInt(temp[0]) * 60 + Integer.parseInt(temp[1]);
    }
}
