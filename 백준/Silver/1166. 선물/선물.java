import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		long N = Long.parseLong(st.nextToken());
		long L = Long.parseLong(st.nextToken());
		long W = Long.parseLong(st.nextToken());
		long H = Long.parseLong(st.nextToken());
		double min = L;
		min = Math.min(min, W);
		min = Math.min(min, H);

		double left = 0;
		double right = min;
		double mid;
		
		for(int i=0; i<10000; i++) {
			mid = (left + right) / 2;
			if ((long)(L/mid) * (long)(W/mid) * (long)(H/mid) < N) {
				right = mid;
			} else {
				left = mid;
			}
		}
		System.out.println(left);
	}
}