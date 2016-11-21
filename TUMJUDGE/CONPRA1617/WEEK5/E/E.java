import java.math.BigInteger;
import java.util.BitSet;
import java.util.Scanner;
import java.util.BitSet;
import java.math.*;

public class E {

	static int primes[];
	static int nr_generated_primes;
	static boolean debug_print = false;
	
	static void get_primes(int n){
	  int lim = (int)(Math.sqrt(n) / 2);
	  n /= 2;
	  BitSet p = new BitSet(n);
	  primes = new int[1002];
	  int k = 0;
	  primes[k++] = 2;
	  for(int i=1; i<=lim; i++){
	    if(!p.get(i)){
	    	for(int j=((i*i)<<1)+(i<<1); j<n; j += (i<<1)+1)
	    		p.set(j);
	    }
	  }
	  for(int i=1; i<p.length(); ++i)
		  if(!p.get(i))
			  primes[k++] = 2*i+1;
	  nr_generated_primes = k;
	}
	
	static BigInteger get_lcm(BigInteger A, BigInteger B){
		return (A.multiply(B)).divide(A.gcd(B));
	}
	
	private static BigInteger get_lcms(BigInteger B[]){
		BigInteger current_gcd = B[0].gcd(B[1]);
		BigInteger current_lcm = B[0].multiply(B[1]).divide(current_gcd);
		for(int i=2; i<B.length; ++i){
			current_gcd = B[i].gcd(current_gcd);
			current_lcm = get_lcm(current_lcm, B[i]);
		}
		return current_lcm;
	}
	
	
	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);

		/*
		 * Generate primes up to 10^3.
		 */
		get_primes(1002);

		// read several types of input
		Integer T = s.nextInt();
		for(int t=1;t<=T; ++t){
			Integer K = s.nextInt();
			BigInteger N[] = new BigInteger[K];
			BigInteger A[] = new BigInteger[K];
			BigInteger Nprimes[] = new BigInteger[1002];
			BigInteger Aprimes[] = new BigInteger[1002];
			int[] nprimes_pos = new int[1000]; 
			for(int k=0; k<K; ++k)
				N[k] = s.nextBigInteger(); 
			
			/*
			 * Compute lcm here! because you will modify the N[i] later.
			 */
			BigInteger coordB = get_lcms(N);
			for(int i=0; i<N.length; ++i)
				if(N[i].equals(BigInteger.ONE))
					A[i] = BigInteger.ZERO;
				else
					A[i] = N[i].subtract(BigInteger.valueOf(i));
			
			/*
			 * Remove prime factors from N's
			 */
			int nr_prime_moduli=0;
			for(int i=0; i<nr_generated_primes; ++i){
				BigInteger Factor = BigInteger.valueOf(primes[i]);
				int max_power = 0;
				int max_pos = -1;
				for(int j=0; j<N.length; ++j){
					int power = 0;
					while(N[j].compareTo(Factor) >= 0 && N[j].mod(Factor).equals(BigInteger.ZERO)){
						N[j] = N[j].divide(Factor);
						power++;
					}
					if(power > max_power){
						max_power = power;
						max_pos = j;
					}
				}
				/*
				 * Add the p with the largest k, i.e. p^k to the list of A,N for the CRT.
				 * A = A[i] corresponding to the position where you found the maximum.
				 */
				if(max_power > -1 && max_pos > -1){
					Nprimes[nr_prime_moduli] = Factor.pow(max_power);
					nprimes_pos[nr_prime_moduli] = max_pos;
					nr_prime_moduli++;
				}
			}
			
			for(int i=0; i<nr_prime_moduli; ++i)
				Aprimes[i] = A[nprimes_pos[i]];
		
				
			/*
			 * Chinese Remainder Theorem
			 */
			/*
			 * Compute product of all moduli.
			 */
			BigInteger Prod = BigInteger.ONE;
			for(int i=0; i<N.length; ++i)
				Prod = Prod.multiply(N[i]);
			for(int i=0; i<nr_prime_moduli; ++i)
				Prod = Prod.multiply(Nprimes[i]);

			
			/*
			 * Initalize solution.
			 */
			BigInteger coordA = BigInteger.ZERO;
			BigInteger P;
			for(int i=0; i<N.length; ++i){
				P = Prod.divide(N[i]);
				coordA = coordA.add(A[i].multiply(P).multiply(P.modInverse(N[i])));
			}
			for(int i=0; i<nr_prime_moduli; ++i){
				P = Prod.divide(Nprimes[i]);
				coordA = coordA.add(Aprimes[i].multiply(P).multiply(P.modInverse(Nprimes[i])));
			}
			// NEEDED, otherwise it won't result in the correct solution!
			coordA = coordA.mod(Prod);
			
			System.out.println("Case #" + t + ": " + coordA + " " + coordB);
		}
	}
}
