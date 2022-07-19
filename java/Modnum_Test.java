import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class Modnum_Test {
//    Functions with s- prefix performs operation on the current object
//    instead of creating a new one (s for 'self')
//    In general, s- functions should be faster than regular functions
//    since they involve less object creation

    public static void main(String[] args) {
        Modnum printValue = new Modnum(100);
        System.out.printf("Test 1: %d (Expected 100)\n", printValue.value());
        System.out.printf("Test 2: %d (Expected 999999907)\n", printValue.opposite().value());

        Modnum a = new Modnum(6);
        System.out.printf("Test 3: %d (Expected 13)\n", a.sAdd(new Modnum(7)).value());

        Modnum b = new Modnum(13);
        System.out.printf("Test 4: %d (Expected 33)\n", b.add(new Modnum(20)).value());

        Modnum c = new Modnum(2);
        System.out.printf("Test 5: %d (Expected 688423210)\n", c.pow(1000).value());
    }

    static class Modnum {
        public static final int mod = 1_000_000_007;
        private int x = 0;
        private int norm_modnum(int n) {
            if (n < 0) n += mod;
            if (n >= mod) n -= mod;
            return n;
        }
        Modnum() {}
        Modnum(int x) { if (x >= 0 && x < mod) this.x = x; else this.x = norm_modnum(x); }
        Modnum(long x) { this.x = norm_modnum((int) x % mod); }
        public int value() { return x; }

        public Modnum sPow(long b) {
            Modnum res = new Modnum(1);
            while (b > 0) {
                if ((b & 1) == 1) res.sMul(this);
                this.sMul(this);
                b >>= 1;
            }
            this.x = res.x;
            return this;
        }
        public Modnum pow(long b) {
            Modnum res = new Modnum(this.x);
            res.sPow(b);
            return res;
        }
        public Modnum inv() { return this.pow(mod - 2); }
        public Modnum opposite() { return new Modnum(norm_modnum(mod - x)); }
        public Modnum sAdd(Modnum o) { x = norm_modnum(x + o.x); return this; }
        public Modnum sSub(Modnum o) { x = norm_modnum(x - o.x); return this; }
        public Modnum sMul(Modnum o) { x = (int) ((long) x * o.x % mod); return this; }
        public Modnum sDiv(Modnum o) { sMul(o.inv()); return this; }

        public Modnum add(Modnum o) { Modnum ans = new Modnum(this.x); ans.sAdd(o); return ans; }
        public Modnum sub(Modnum o) { Modnum ans = new Modnum(this.x); ans.sSub(o); return ans; }
        public Modnum mul(Modnum o) { Modnum ans = new Modnum(this.x); ans.sMul(o); return ans; }
        public Modnum div(Modnum o) { Modnum ans = new Modnum(this.x); ans.sDiv(o); return ans; }
    }
}