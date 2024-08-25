import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class Main {
  public static void main(String[] args) {
    InputReader in = new InputReader(System.in);
    PrintWriter out = new PrintWriter(System.out);
    int t = in.nextInt();
    for (int i = 0; i < t; i++) {
      solve(in, out);
    }
    out.close();
  }

  public static void solve(InputReader in, PrintWriter out) {
    Point p1 = new Point(in.nextInt(), in.nextInt());
    Point p2 = new Point(in.nextInt(), in.nextInt());
    Point p3 = new Point(in.nextInt(), in.nextInt());
    double orientation = Geometry.orientation(p1, p2, p3);
    if (orientation < 0) {
      out.println("RIGHT");
    } else if (orientation > 0) {
      out.println("LEFT");
    } else {
      out.println("TOUCH");
    }
  }

  static class Geometry {
    static int signum(final double x) {
      return Double.compare(x, 0);
    }

    // Check the orientation of three points: p1, p2, p3.
    // If > 0: p3 is on the left of the vector p1p2.
    // If < 0: p3 is on the right of the vector p1p2.
    static double orientation(final Point p1, final Point p2, final Point p3) {
      return orientation(p2.sub(p1), p3.sub(p1));
    }

    // Check the orientation of two vectors: v and w;
    // If > 0: v is on the right of w.
    // If < 0: v is on the left of w.
    // Way to remember: Given the two unit vectors i, j in 2D space.
    // We always have: i.cross(j) = 1.
    static double orientation(final Point v1, final Point v2) {
      return v1.cross(v2);
    }
  }

  static class Point {
    public double x;
    public double y;

    public Point(double x, double y) {
      this.x = x;
      this.y = y;
    }

    public Point clone() {
      return new Point(x, y);
    }

    public Point addSelf(final double x, final double y) {
      this.x += x;
      this.y += y;
      return this;
    }

    public Point addSelf(final Point o) {
      return addSelf(o.x, o.y);
    }

    public Point subSelf(final double x, final double y) {
      this.x -= x;
      this.y -= y;
      return this;
    }

    public Point subSelf(final Point o) {
      return subSelf(o.x, o.y);
    }

    public Point add(final Point o) {
      return new Point(x + o.x, y + o.y);
    }

    public Point sub(final Point o) {
      return new Point(x - o.x, y - o.y);
    }

    public double dot(final Point o) {
      return x * o.x + y * o.y;
    }

    public double cross(final Point o) {
      return x * o.y - y * o.x;
    }
  }

  static class InputReader {
    private final BufferedReader reader;
    private StringTokenizer tokenizer;

    public InputReader(InputStream inputStream) {
        reader = new BufferedReader(new InputStreamReader(inputStream), 32768);
        tokenizer = new StringTokenizer("");
    }

    public boolean hasNext() {
        if (!tokenizer.hasMoreTokens()) {
            String line = null;
            try {
                line = reader.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            if (line == null) {
                return false;
            }
            tokenizer = new StringTokenizer(line);
        }
        return true;
    }

    public String next() {
        if (!hasNext()) {
            throw new RuntimeException();
        }
        return tokenizer.nextToken();
    }

    public int nextInt() {
        return Integer.parseInt(next());
    }

    public long nextLong() {
        return Long.parseLong(next());
    }

    public double nextDouble() {
        return Double.parseDouble(next());
    }
  }
}

