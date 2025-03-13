package com.example.helloandroid;

import android.widget.TextView;

class c2_RunnableThread implements Runnable {

	Thread runner;
	public int id;
	public int seq;
	
	//arrays
	public int[][] block;
	public int[][] cos2;
	public int[][] temp2d;
	//symbolic
	public int B;
	
	public TextView tv;
	public c2_RunnableThread() {
	}
	public c2_RunnableThread(String threadName, int z) {
		runner = new Thread(this, threadName); // (1) Create a new thread.
		System.out.println(runner.getName());
		runner.start(); // (2) Start the thread.
	}
	public void run() {
		//Display info about this particular thread
		//System.out.println(Thread.currentThread());
		
		if(seq == 1)
			sequential_loop();
		else
		{
			int i, sum, j, k, lb, ub;
	
			if(id==0) 
				{
					lb = 1;	ub = B/2;
				}
				else 
				{
					lb = (B/2)+1; ub = B;
				}
			
				for (i = lb-1; i < ub-1; i++) {
					for (j = 0; j < B; j++) {
					  sum = 0;
					  for (k = 0; k < B; k++) {
					    sum += block[i][k] * cos2[k][j];
					  }
					  temp2d[i][j] = sum;
					}
				}  


		}
		
		//tv.setText("Hello Thread" + Integer.toString(id) );
	}
	
	public void sequential_loop()
	{
		int i, sum, j, k;
		
		for (i = 0; i < B; i++) {
			for (j = 0; j < B; j++) {
			  sum = 0;
			  for (k = 0; k < B; k++) {
			    sum += block[i][k] * cos2[k][j];
			  }
			  temp2d[i][j] = sum;
			}
		}  
		
	}
	
	public void jomp_loop()
	{
		int t1=0,t2=0,t3=0;
		
		//omp parallel shared(y, twiddle, x, N1, N2, N3)
		{
		//omp for private(t1,t2,t3)

		
		
		/*
		//omp parallel shared(y, twiddle, x, N1, N2, N3)
		{
		//omp for private(t1,t2,t3)
		if (N3 >= 1 && N2 >= 1) {
			  for(t1 = 1; t1 <= N1; t1++) {
				for(t2 = 1; t2 <= N2; t2++) {
				  for(t3 = 1; t3 <= N3; t3++) {
					y[t3][t2][t1]=y[t3][t2][t1]*twiddle[t3][t2][t1]; 
					x[t3][t2][t1]=y[t3][t2][t1]; 
				  }
				}
			  }
			}
		}  
		*/
		
		}
	}

}


public class C2_loop
{
	public String output;
	public long time;
	
	int B, N1, N2, N3, DIM1, DIM2, DIM3;
	
	int[][] block;
	int[][] cos2;
	int[][] temp2d;
	
	public C2_loop(int num_proc, int iter)
	{
		   B = iter;   // 100
		   N1 = B;
		   N2 = N1;
		   N3 = N1;
		   
		   DIM1 = N1+2;
		   DIM2 = N2+2;
		   DIM3 = N3+2;
		   
		   output = "";
		   
		   temp2d = new int[DIM1][DIM2];     
		   block = new int[DIM1][DIM2];  
		   cos2 = new int[DIM1][DIM2];  
		   
	       
	       if(num_proc == 1)
	    	   seq();
	       else par();
	       
	       
	       
	}
	
	void seq()
	{
		long start = System.currentTimeMillis();
	       
	       
	       c2_RunnableThread r3 = new c2_RunnableThread();
	       
	       r3.temp2d = temp2d; r3.block = block; r3.cos2 = cos2; 
	       r3.B = B;
	       
	       r3.id = 0;       
	       r3.seq = 1;
	       
	       Thread thread3 = new Thread(r3, "thread2");
	       thread3.start();
	       try {
			thread3.join();
	       } catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
	       }
	              
	       long end = System.currentTimeMillis();
	       output += "Sequential execution time was "+(end-start)+" ms.";
	       time = end-start;
		   
	}
	
	void par()
	{
		   long start = System.currentTimeMillis();
	       
         
	       c2_RunnableThread r1 = new c2_RunnableThread();
	       
	       r1.temp2d = temp2d; r1.block = block; r1.cos2 = cos2;
	       r1.B = B;
	       
	       r1.id = 0; r1.seq = 0;

	       
	       Thread thread1 = new Thread(r1, "thread1");
	       
	       c2_RunnableThread r2 = new c2_RunnableThread();

	       r2.temp2d = temp2d; r2.block = block; r2.cos2 = cos2;
	       r2.B = B;
	       
	       r2.id = 1; r2.seq = 0;
       
	       
	       Thread thread2 = new Thread(r2, "thread2");
	       
	       thread1.start();
	       thread2.start();
	       try {
			thread1.join();
			thread2.join();
	       } catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
	       }
	      // tv.setText(Integer.toString(t.z));
	       
	       long end = System.currentTimeMillis();
	       Runtime runtime = Runtime.getRuntime();
	       int numberOfProcessors = runtime.availableProcessors();
	       
	       output += "Parallel execution time was "+(end-start)+" ms.   " + " Cores:" + numberOfProcessors ;      		
	       time = end-start;
	}
	
}


/*

for (i = 0; i < B; i++) {
for (j = 0; j < B; j++) {
  sum = 0.0;
  for (k = 0; k < B; k++) {
    sum += block[i][k] * cos2[k][j];
  }
  temp2d[i][j] = sum;
}
}  

*/