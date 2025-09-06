import java.io.*;
import java.util.*;

public class Main {
    static class Solver {
        FasterInputReader in;
        PrintWriter out;

        Solver(FasterInputReader in, PrintWriter out) {
            this.in = in;
            this.out = out;
        }

        final int D = 4;
        final int[] dr = {0, 1, 0, -1};
        final int[] dc = {1, 0, -1, 0};

        int[][] g;
        long[][][] w;

        boolean checkCycle(int r, int c) {
            long dis = w[r][c][0];
            dis += w[r][c + 1][1];
            dis += w[r + 1][c + 1][2];
            dis += w[r + 1][c][3];
            return dis == 0;
        }

        void solve() {
            int n = in.nextInt();
            int m = in.nextInt();
            int k = in.nextInt();

            g = new int[n][m];
            for (int i = 0; i < n; i++) {
                String row = in.next();
                for (int j = 0; j < m; j++) {
                    g[i][j] = row.charAt(j) - '0';
                }
            }

            int q = in.nextInt();
            int[][] queries = new int[q][4];

            for (int i = 0; i < q; i++) {
                for (int j = 0; j < 4; j++) {
                    queries[i][j] = in.nextInt() - 1;
                }
            }

            w = new long[n][m][D];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    for (int d = 0; d < D; d++) {
                        int a = i + dr[d];
                        int b = j + dc[d];
                        if (a < 0 || a >= n) continue;
                        if (b < 0 || b >= m) continue;

                        w[i][j][d] = 1;
                        for (int c = 0; c < k; c++) {
                            w[i][j][d] *= (g[a][b] - g[i][j]);
                        }
                    }
                }
            }
            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < m - 1; j++) {
                    if (!checkCycle(i, j)) {
                        for (int qi = 0; qi < q; qi++) {
                            out.println("INVALID");
                        }
                        return;
                    }
                }
            }

            // final long INF = (long) 1e8 + 26;
            long[][] dis = new long[n][m];
            boolean[][] vis = new boolean[n][m];

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    dis[i][j] = Long.MAX_VALUE;
                    vis[i][j] = false;
                }
            }

            // PriorityQueue<Cell> pq = new PriorityQueue<>(Comparator.comparingLong(o -> o.w));
            // pq.add(new Cell(0, 0, 0));
            MinHeap minHeap = new MinHeap();
            minHeap.push(0, 0, 0);
            dis[0][0] = 0;

            // while (!pq.isEmpty()) {
            while (minHeap.size > 0) {
                // Cell u = pq.poll();
                int ur = minHeap.rs[0];
                int uc = minHeap.cs[0];
                long uw = minHeap.ws[0];
                minHeap.pop();

                if(vis[ur][uc]) continue;
                vis[ur][uc] = true;

                for(int i = 0; i < D; i++) {
                    int vr = ur + dr[i];
                    int vc = uc + dc[i];
                    long vw = uw + w[ur][uc][i];
                    if(0 <= vr && vr < n && 0 <= vc && vc < m && dis[vr][vc] > vw) {
                        dis[vr][vc] = vw;
                        // pq.add(new Cell(vr, vc, vw));
                        minHeap.push(vr, vc, vw);
                    }
                }
            }

            for (int i = 0; i < q; i++) {
                int sr = queries[i][0];
                int sc = queries[i][1];
                int tr = queries[i][2];
                int tc = queries[i][3];
                out.println(dis[sr][sc] - dis[tr][tc]);
            }
        }
    }

    static class Cell {
        int r;
        int c;
        long w;

        Cell(int r, int c, long w) {
            this.r = r;
            this.c = c;
            this.w = w;
        }

        @Override
        public String toString() {
            return "Cell{" +
                    "r=" + r +
                    ", c=" + c +
                    ", w=" + w +
                    '}';
        }
    }

    static class MinHeap {
        static final int N = (int) 1e6;
        int size;
        int[] rs;
        int[] cs;
        long[] ws;

        MinHeap() {
            size = 0;
            rs = new int[N];
            cs = new int[N];
            ws = new long[N];
        }

        void push(int r, int c, long w) {
            rs[size] = r;
            cs[size] = c;
            ws[size] = w;
            int i = size;
            int p = (i - 1) / 2;
            size++;
            while (i > 0 && ws[i] < ws[p]) {
                swap(i, p);
                i = p;
                p = (i - 1) / 2;
            }
        }

        void pop() {
            swap(0, size - 1);
            size--;
            heapify(0);
        }

        void swap(int i, int j) {
            int rt = rs[i]; rs[i] = rs[j]; rs[j] = rt;
            int ct = cs[i]; cs[i] = cs[j]; cs[j] = ct;
            long wt = ws[i]; ws[i] = ws[j]; ws[j] = wt;
        }

        void heapify(int i) {
            while (true) {
                int smallest = i;
                int l = i * 2 + 1;
                int r = i * 2 + 2;
                if (l < size && ws[l] < ws[smallest]) {
                    smallest = l;
                }
                if (r < size && ws[r] < ws[smallest]) {
                    smallest = r;
                }
                if (smallest == i) {
                    break;
                }
                swap(i, smallest);
                i = smallest;
            }
        }
    }

    public static void main(String[] args) {
        FasterInputReader in = new FasterInputReader(System.in);
        PrintWriter out = new PrintWriter(System.out);
        Solver solver = new Solver(in, out);
        solver.solve();
        out.close();
    }

    static class FasterInputReader {
        private InputStream stream;
        private byte[] buf = new byte[65536];
        private int curChar;
        private int numChars;
        private FasterInputReader.SpaceCharFilter filter;

        public FasterInputReader(InputStream stream) {
            this.stream = stream;
        }

        public int[] nextIntArray(int size) {
            int[] array = new int[size];
            for (int i = 0; i < size; i++) {
                array[i] = nextInt();
            }
            return array;
        }

        public int get() {
            if (numChars == -1) {
                throw new InputMismatchException();
            }
            if (curChar >= numChars) {
                curChar = 0;
                try {
                    numChars = stream.read(buf);
                } catch (IOException e) {
                    throw new InputMismatchException();
                }
                if (numChars <= 0) {
                    return -1;
                }
            }
            return buf[curChar++];
        }

        public String next() {
            int c = get();
            while (isSpaceChar(c)) {
                c = get();
            }
            StringBuilder res = new StringBuilder();
            do {
                if (Character.isValidCodePoint(c)) {
                    res.appendCodePoint(c);
                }
                c = get();
            } while (!isSpaceChar(c));
            return res.toString();
        }

        public int nextInt() {
            int c = get();
            while (isSpaceChar(c)) {
                c = get();
            }
            int sgn = 1;
            if (c == '-') {
                sgn = -1;
                c = get();
            }
            int res = 0;
            do {
                if (c < '0' || c > '9') {
                    throw new InputMismatchException();
                }
                res *= 10;
                res += c - '0';
                c = get();
            } while (!isSpaceChar(c));
            return res * sgn;
        }

        public boolean isSpaceChar(int c) {
            if (filter != null) {
                return filter.isSpaceChar(c);
            }
            return isWhitespace(c);
        }

        public static boolean isWhitespace(int c) {
            return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
        }

        public interface SpaceCharFilter {
            public boolean isSpaceChar(int ch);

        }

    }

    static class InputReader {
        static final String DEFAULT_DELIM_SET = " \t\n\r\f";
        BufferedReader reader;
        StringTokenizer tokenizer;
        String delimSet;

        InputReader(InputStream inStream) {
            this(inStream, InputReader.DEFAULT_DELIM_SET);
        }

        InputReader(InputStream inStream, String delimSet) {
            this.delimSet = delimSet;
            reader = new BufferedReader(new InputStreamReader(inStream));
            tokenizer = new StringTokenizer("", delimSet);
        }

        String next() {
            while (!tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                    throw new RuntimeException();
                }
            }
            return tokenizer.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        long nextLong() {
            return Long.parseLong(next());
        }

        double nextDouble() {
            return Double.parseDouble(next());
        }

    }
}
