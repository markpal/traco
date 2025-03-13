package com.example.helloandroid;

import android.widget.TextView;

class fx_RunnableThread implements Runnable {

	Thread runner;
	public int id;
	public int seq;
	
	//arrays
	public int[][][] x, y, twiddle;
	//symbolic
	public int N1, N2, N3;
	
	public TextView tv;
	public fx_RunnableThread() {
	}
	public fx_RunnableThread(String threadName, int z) {
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
			int t1=0,t2=0,t3=0,ub,lb;
	
			if(id==0) 
				{
					lb = 1;	ub = N1/2;
				}
				else 
				{
					lb = (N1/2)+1; ub = N1;
				}
			
			// UDS loop ---
			if (N3 >= 1 && N2 >= 1) {
			  for(t1 = lb; t1 <= ub; t1++) {
				for(t2 = 1; t2 <= N2; t2++) {
				  for(t3 = 1; t3 <= N3; t3++) {
					y[t3][t2][t1]=y[t3][t2][t1]*twiddle[t3][t2][t1]; 
					x[t3][t2][t1]=y[t3][t2][t1]; 
				  }
				}
			  }
			}

		}
		
		//tv.setText("Hello Thread" + Integer.toString(id) );
	}
	
	public void sequential_loop()
	{
		int i=0,j=0,k=0;
		
		for(i=1; i<=N1; i++)
		      for(k=1; k<=N2; k++) 
		        for(j=1; j<=N3; j++) 
				{
		          y[j][k][i]=y[j][k][i]*twiddle[j][k][i];
		          x[j][k][i]=y[j][k][i];
		          
			    }
		
	}
	
	public void jomp_loop()
	{
		int t1=0,t2=0,t3=0;
		
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


public class FX_loop
{
	public String output;
	public long time;
	
	int N1, N2, N3, DIM1, DIM2, DIM3;
	
	int[][][] x;
	int[][][] y;
	int[][][] twiddle;
	
	public FX_loop(int num_proc, int iter)
	{
		   N1 = iter;   // 100
		   N2 = N1;
		   N3 = N1;
		   
		   DIM1 = N1+2;
		   DIM2 = N2+2;
		   DIM3 = N3+2;
		   
		   output = "";
		   
		   x = new int[DIM1][DIM2][DIM3];     
	       y = new int[DIM1][DIM2][DIM3];	   
	       twiddle = new int[DIM1][DIM2][DIM3];
	       
	       if(num_proc == 1)
	    	   seq();
	       else par();
	       
	       
	       
	}
	
	void seq()
	{
		long start = System.currentTimeMillis();
	       
	       
	       fx_RunnableThread r3 = new fx_RunnableThread();
	       
	       r3.x = x; r3.y = y; r3.twiddle = twiddle;
	       r3.N1 = N1; r3.N2 = N2; r3.N3 = N3;
	       
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
	       
         
	       fx_RunnableThread r1 = new fx_RunnableThread();
	       
	       r1.x = x; r1.y = y; r1.twiddle = twiddle;
	       r1.N1 = N1; r1.N2 = N2; r1.N3 = N3;
	       
	       r1.id = 0; r1.seq = 0;

	       
	       Thread thread1 = new Thread(r1, "thread1");
	       
	       fx_RunnableThread r2 = new fx_RunnableThread();

	       r2.x = x; r2.y = y; r2.twiddle = twiddle;
	       r2.N1 = N1; r2.N2 = N2; r2.N3 = N3;
	       
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