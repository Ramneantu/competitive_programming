import java.util.Scanner;
import java.math.BigInteger;
import java.util.ArrayList;

class BigRational {
    private BigInteger num;   // the numerator
    private BigInteger den;   // the denominator

    // create and initialize a new Rational object
    public BigRational(int numerator, int denominator) {
        // BigInteger constructor takes a string, not an int
        num = new BigInteger(numerator + "");
        den = new BigInteger(denominator + "");
        BigInteger g = num.gcd(den);
        num = num.divide(g);
        den = den.divide(g);
    }

    // create and initialize a new Rational object
    public BigRational(BigInteger numerator, BigInteger denominator) {
        BigInteger g = numerator.gcd(denominator);
        num = numerator.divide(g);
        den = denominator.divide(g);
    }

    // return string representation of (this)
    public String toString() {
        return num + "/" + den;
    }

    // return a * b
    public BigRational times(BigRational b) {
        BigRational a = this;
        BigInteger numerator   = a.num.multiply(b.num);
        BigInteger denominator = a.den.multiply(b.den);
        return new BigRational(numerator, denominator);
    }


    // return a + b
    public BigRational plus(BigRational b) {
        BigRational a = this;
        BigInteger numerator   = a.num.multiply(b.den).add(a.den.multiply(b.num));
        BigInteger denominator = a.den.multiply(b.den);
        return new BigRational(numerator, denominator);
    }

    // return 1 / a
    public BigRational reciprocal() { return new BigRational(den, num);  }

    // return a / b
    public BigRational divides(BigRational b) {
        BigRational a = this;
        return a.times(b.reciprocal());
    }
}

public class D {

  public static void main(String[] args){

    Scanner sc = new Scanner(System.in);
    int t = sc.nextInt();
    for(int _t=1; _t<=t; ++_t){
      int n = sc.nextInt();
      String[] dices = sc.next().split("\\+");
      ArrayList<Integer> ds = new ArrayList<Integer>();
      int maxi = 0;
      for(int i=0; i<dices.length; ++i){
        String[] vs = dices[i].split("d");
        int a = Integer.parseInt(vs[0]);
        int b = Integer.parseInt(vs[1]);
        for(int k=0; k<a; ++k){
          ds.add(b);
        }
        maxi += (a*b);
      }

      BigRational[][] dp = new BigRational[ds.size()][maxi+1];
      for(int i=0; i<dp.length; ++i)
        for(int j=0; j<dp[i].length; ++j)
          dp[i][j] = new BigRational(0,1);
      for(int j=1; j<=ds.get(0); ++j)
        dp[0][j] = new BigRational(1,ds.get(0));
      for(int i=1; i<ds.size(); ++i){
        BigRational cnst = new BigRational(1,ds.get(i));
        for(int j=1; j<=maxi; ++j){
          for(int k=1; k<=ds.get(i) && k <= j; ++k)
            dp[i][j] = dp[i][j].plus(cnst.times(dp[i-1][j-k]));
        }
      }

      BigRational res = new BigRational(0,1);
      for(int j=n; j<=maxi; ++j)
        res = res.plus(dp[dp.length-1][j]);
      System.out.println("Case #" + _t + ": " + res.toString());
    }

  }

}
