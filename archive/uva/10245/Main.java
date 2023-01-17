import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.Writer;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.InputMismatchException;

public class Main {
  public static void main(String[] args) {
    InputStream inputStream = System.in;
    OutputStream outputStream = System.out;
    InputReader in = new InputReader(inputStream);
    OutputWriter out = new OutputWriter(outputStream);
    UVa_10245 solver = new UVa_10245();
    solver.solve(1, in, out);
    out.close();
  }

  static class UVa_10245 {
    InputReader in;
    OutputWriter out;
    int n;

    public void solve(int testNumber, InputReader in_, OutputWriter out_) {
      in = in_;
      out = out_;

      while (true) {
        n = in.nextInt();
        if (n == 0)
          break;
        solveCase();
      }
    }

    private void solveCase() {
      Point[] points = new Point[n];
      for (int i = 0; i < n; i++) {
        double x = in.nextDouble();
        double y = in.nextDouble();
        points[i] = new Point(x, y);
      }

      Arrays.sort(points, new Comparator<Point>() {
        public int compare(Point p1, Point p2) {
          return Double.compare(p1.x, p2.x);
        }
      });

      double minDist = findMinDist(points, 0, n - 1);

      if (minDist > 10000) {
        out.println("INFINITY");
      } else {
        out.printf("%.4f\n", minDist);
      }
    }

    private double findMinDist(Point[] points, int start, int end) {
      if (start == end) {
        return (long)1e18;
      }

      int mid = (start + end) / 2;

      // Case 1 and 2: the pair is located on the left or on the right
      double minDistLeft = findMinDist(points, start, mid);
      double minDistRight = findMinDist(points, mid + 1, end);
      double minDist = Math.min(minDistLeft, minDistRight);

      // Case 3: one point is on the left and the other is on the right
      double xDivide = points[mid].x;

      ArrayList<Point> consider = new ArrayList<>();

      for (int i = start; i <= end; i++) {
        if (Math.abs(points[i].x - xDivide) < minDist) {
          consider.add(points[i]);
        }
      }

      Collections.sort(consider, new Comparator<Point>() {
        public int compare(Point p1, Point p2) {
          return Double.compare(p1.y, p2.y);
        }
      });

      for (int i = 0; i < consider.size(); i++) {
        for (int j = i + 1; j < Math.min(i + 15, consider.size()); j++) {
          // 15 = magic number; according to the book "Algorithm Design"
          minDist =
              Math.min(minDist, distance(consider.get(i), consider.get(j)));
        }
      }

      return minDist;
    }

    private double distance(Point p1, Point p2) {
      return Math.sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                       (p1.y - p2.y) * (p1.y - p2.y));
    }

    class Point {
      double x;
      double y;

      public Point(double x, double y) {
        this.x = x;
        this.y = y;
      }
    }
  }

  static class InputReader {
    private final int BUFFER_SIZE = 32768;
    private InputStream stream;
    private byte[] buffer = new byte[BUFFER_SIZE + 1];
    private int pointer = 1;
    private int readLength = 0;
    private int lastWhiteSpace = '\n';

    public InputReader(InputStream stream) { this.stream = stream; }

    private void fillBuffer() {
      try {
        readLength = stream.read(buffer, 1, BUFFER_SIZE);
      } catch (IOException e) {
        throw new RuntimeException(e);
      }
    }

    private byte get() {
      if (pointer > readLength) {
        pointer = 1;
        fillBuffer();
        if (readLength <= 0)
          return -1;
      }
      return buffer[pointer++];
    }

    public char nextChar() {
      int c = get();

      while (isWhiteSpace(c)) {
        c = get();
      }

      return (char)c;
    }

    public int nextInt() {
      int c = nextChar();
      int sign = 1;

      if (c == '-') {
        sign = -1;
        c = get();
      }

      int abs = 0;

      do {
        if (c < '0' || c > '9')
          throw new InputMismatchException();
        abs *= 10;
        abs += c - '0';
        c = get();
      } while (!isWhiteSpace(c));

      lastWhiteSpace = c;

      return abs * sign;
    }

    public double nextDouble() {
      int c = nextChar();
      int sign = 1;

      if (c == '-') {
        sign = -1;
        c = get();
      }

      double abs = 0;

      do {
        if (c < '0' || c > '9')
          throw new InputMismatchException();
        abs *= 10;
        abs += (c - '0');
        c = get();
      } while (!isWhiteSpace(c) && c != '.');

      if (c == '.') {
        c = get();
        double m = 1.0;

        do {
          if (c < '0' || c > '9')
            throw new InputMismatchException();
          m /= 10;
          abs += (c - '0') * m;
          c = get();
        } while (!isWhiteSpace(c));
      }

      return abs * sign;
    }

    public boolean isWhiteSpace(int c) {
      return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
    }
  }

  static class OutputWriter {
    private PrintWriter writer;

    public OutputWriter(OutputStream outputStream) {
      writer = new PrintWriter(
          new BufferedWriter(new OutputStreamWriter(outputStream)));
    }

    public OutputWriter(Writer writer) {
      this.writer = new PrintWriter(writer);
    }

    public void print(Object... objects) {
      for (Object object : objects) {
        writer.print(object);
      }
    }

    public void println(Object... objects) {
      print(objects);
      writer.println();
    }

    public void printf(String format, Object... objects) {
      writer.printf(format, objects);
    }

    public void close() { writer.close(); }
  }
}
