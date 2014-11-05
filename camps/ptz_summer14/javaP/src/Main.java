import java.io.*;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.StringTokenizer;

public class Main {

    public static void main(String[] args) throws FileNotFoundException {
        new Solution().solve();
    }

}

class Solution {
    public void solve() throws FileNotFoundException
    {
        InputReader in = new InputReader(System.in);
        PrintWriter out = new PrintWriter(System.out);
        int n = in.nextInt();
        BigDecimal cur = BigDecimal.ONE;
        cur.setScale(2 * n);
        for (int i = 0; i < n; ++i) {
            out.print(cur.toPlainString() + " ");
            cur = cur.divide(BigDecimal.valueOf(2));
        }
        out.println();
        out.flush();
        while (true)
        {
            BigDecimal ans = BigDecimal.ZERO;
            cur = BigDecimal.ONE;
            ans.setScale(2 * n);
            cur.setScale(2 * n);
            for (int i = 0; i < n; ++i)
            {
                int s = in.nextInt();
                if (s == 0) {
                    out.flush();
                    return;
                }
                if (s == -1) ans = ans.add(cur);
                cur = cur.multiply(BigDecimal.valueOf(2));
            }
            ans = ans.add(BigDecimal.valueOf(0.5));
            out.println(ans.toPlainString());
        }
    }

}

class InputReader {
    public BufferedReader reader;
    public StringTokenizer tokenizer;

    public InputReader(InputStream stream) {
        reader = new BufferedReader(new InputStreamReader(stream), 32768);
        tokenizer = null;
    }

    public String next() {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            try {
                tokenizer = new StringTokenizer(reader.readLine());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        return tokenizer.nextToken();
    }

    public int nextInt() {
        return Integer.parseInt(next());
    }

    public BigInteger nextBigInteger() {
        return new BigInteger(next());
    }
}