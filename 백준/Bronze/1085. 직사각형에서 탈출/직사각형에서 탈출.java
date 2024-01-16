import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
		int[] num = new int[5];
        int calx, caly;

        Scanner scanner = new Scanner (System.in);
        for (int i=0; i<4; i++) {
            num[i] = scanner.nextInt();
        }

        if (num[0] > Math.abs(num[2] - num[0]) ) {
            calx = Math.abs(num[2] - num[0]);
        } else {
            calx = num[0];
        }
        //System.out.println(calx);

        if (num[1] > Math.abs(num[3] - num[1])) {
            caly = Math.abs(num[3] - num[1]);
        } else {
            caly = num[1];
        }

        if (caly > calx) {
            System.out.println(calx);
        } else {
            System.out.println(caly);
        }
 
	}
}