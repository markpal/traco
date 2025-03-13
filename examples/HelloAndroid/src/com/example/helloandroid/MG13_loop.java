package com.example.helloandroid;

import android.widget.TextView;

class mg13_RunnableThread implements Runnable {

	Thread runner;
	public int id;
	public int seq;
	//arrays
	public int[][][] u;

	//symbolic
	public int N1, N2, n3;
	
	public TextView tv;
	public mg13_RunnableThread() {
	}
	public mg13_RunnableThread(String threadName, int z) {
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
			int t1=0,t2=0,ub,lb;
	
			if(id==0) 
				{
					lb = 1;	ub = N1/2;
				}
				else 
				{
					lb = (N1/2)+1; ub = N1;
				}
			
			if (n3 == 1 && N2 >= 1) {
				  for(t1 = lb; t1 <= ub; t1++) {
				    for(t2 = 1; t2 <= N2; t2++) {
				      u[t2][t1][1] = u[t2][t1][n3-1];
				      if (n3 == 1 && t2 >= 1 && N2 >= t2 && t1 >= 1 && N1 >= t1) {
				        u[t2][t1][n3] = u[t2][t1][ 2];
				      }
				    }
				  }
				}




				if (n3 >= 2 && N2 >= 2) {
				  for(t1 = lb; t1 <= ub; t1++) {
				    for(t2 = 1; t2 <= N2; t2++) {
				      u[t2][t1][1] = u[t2][t1][n3-1];
				      u[t2][t1][n3] = u[t2][t1][2];

				    }
				  }
				}
				if (n3 <= 0 && N2 >= 2) {
				  for(t1 = lb; t1 <= ub; t1++) {
				    for(t2 = 1; t2 <= N2; t2++) {
				      u[t2][t1][1] = u[t2][t1][n3-1];
				      u[t2][t1][n3] = u[t2][t1][2];
				    }
				  }
				}
				if (N2 == 1 && N1 >= 2 && n3 >= 2) {
					for(t1 = lb; t1 <= ub; t1++) {
				      u[1][t1][1] = u[1][t1][n3-1];
				      u[1][t1][n3] = u[1][t1][2];
				  }
				}
				if (N2 == 1 && N1 >= 2 && n3 <= 0) {
					for(t1 = lb; t1 <= ub; t1++) {
				      u[1][t1][1] = u[1][t1][n3-1];
				      u[1][t1][n3] = u[1][t1][2];
				  }
				}


		}
		
		//tv.setText("Hello Thread" + Integer.toString(id) );
	}
	
	public void sequential_loop()
	{
		int i1=0,i2=0;
		
		for(i2 = 1; i2 <= N1; i2++){
			  for(i1 = 1; i1 <= N2; i1++){
			    u[i1][i2][ 1] = u[i1][i2][n3-1];
			    u[i1][i2][n3] = u[i1][i2][   2];
			  }
		}
		
	}
	
	public void jomp_loop()
	{
		
		
	}

}


public class MG13_loop
{
	public String output;
	public long time;
	
	int N1, N2, DIM1, DIM2, n3;
	
	int[][][] u;

	
	public MG13_loop(int num_proc, int iter)
	{
		   N1 = iter;  //1000  
		   N2 = N1;
		   n3 = 8;

		   
		   DIM1 = N1+2;
		   DIM2 = N2+2;

		   
		   output = "";
		    
	       u = new int[DIM1][DIM2][10];
	       
	       if(num_proc == 1)
	    	   seq();
	       else par();
	       
	       
	       
	}
	
	void seq()
	{
		long start = System.currentTimeMillis();
	       
	       
	       mg13_RunnableThread r3 = new mg13_RunnableThread();
	       
	       r3.u = u;
	       r3.N1 = N1; r3.N2 = N2; r3.n3 = n3; 
	       
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
	       
         
	       mg13_RunnableThread r1 = new mg13_RunnableThread();
	       
	       r1.u = u;
	       r1.N1 = N1; r1.N2 = N2; r1.n3 = n3; 
	       
	       r1.id = 0; r1.seq = 0;

	       
	       Thread thread1 = new Thread(r1, "thread1");
	       
	       mg13_RunnableThread r2 = new mg13_RunnableThread();

	       r2.u = u;
	       r2.N1 = N1; r2.N2 = N2; r2.n3 = n3; 
	       
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