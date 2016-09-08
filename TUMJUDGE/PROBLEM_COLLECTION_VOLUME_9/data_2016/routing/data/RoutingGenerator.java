
import java.util.HashSet;
import java.util.Random;

public class RoutingGenerator {

    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("usage: java RoutingGenerator seed n density");
        }
        long seed = Long.parseLong(args[0]);
        int n = Integer.parseInt(args[1]);
        double density = Double.parseDouble(args[2]);

        Random r = new Random(seed);
        StringBuilder sb = new StringBuilder();
        sb.append(n).append("\n");
        for (int i = 1; i <= n; i++) {
            int[] tmp = new int[n-1];
            for (int j = 0; j < tmp.length; j++) {
                tmp[j] = j + (j >= i-1 ? 1 : 0);
            }
            int[] servers = randomSet(tmp, r, density);
            int m = servers.length;
            int t = r.nextInt(1001);
            sb.append(m).append(' ').append(t).append("\n");
            for (int j = 0; j < m; j++) {
                int[] forbidden = randomSet(tmp, r, 1 - density);
                sb.append(forbidden.length).append(' ').append(servers[j]+1);
                for (int k = 0; k < forbidden.length; k++) {
                    sb.append(' ').append(forbidden[k]+1);
                }
                sb.append("\n");
            }
        }
        System.out.print(sb);
    }

    public static int[] randomSet(int[] arr, Random r, double density) {
        HashSet<Integer> set = new HashSet<>();
        for (int i : arr) {
            if (r.nextDouble() < density) {
                set.add(i);
            }
        }
        int[] ret = new int[set.size()];
        int key = 0;
        for (int value : set) {
            ret[key++] = value;
        }
        return ret;
    }
}
