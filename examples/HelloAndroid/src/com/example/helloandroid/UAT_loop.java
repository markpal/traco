package com.example.helloandroid;

import android.widget.TextView;

class uat_RunnableThread implements Runnable {

	Thread runner;
	public int id;
	public int seq;
	//arrays
	public int[][][] tx, qbnew;
	public int [] temp;
	//symbolic
	public int N1, N2;
	
	public TextView tv;
	public uat_RunnableThread() {
	}
	public uat_RunnableThread(String threadName, int z) {
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
			
				if (N2 >= 2) { 
					 /* par */ for(t1 = lb; t1 <= ub; t1++) { 
					    temp[t1]=tx[t1][1][1]; 
					    if (t1 <= N1 && t1 >= 1) { 
					      for(t2 = 2; t2 <= N2; t2++) { 
					        temp[t1] = temp[t1] + qbnew[t2-1][1][1]*tx[t1][1][t2];
					      } 
					    }     
					 } 
					}

		}
		
		//tv.setText("Hello Thread" + Integer.toString(id) );
	}
	
	public void sequential_loop()
	{
		int col=0,i=0;
		
		for(col=1; col <= N1; col++)	
		{
		  temp[col]=tx[col][1][1]; 
		  for(i=2; i<= N2; i++)
		  {
		    temp[col] = temp[col] + qbnew[i-1][1][1]*tx[col][1][i];
		  }
		}
		
	}
	
	public void jomp_loop()
	{
		
		
	}

}


public class UAT_loop
{
	public String output;
	public long time;
	
	int N1, N2, DIM1, DIM2;
	
	int[][][] tx;
	int[][][] qbnew;
	int[] temp;
	
	public UAT_loop(int num_proc, int iter)
	{
		   N1 = iter;   //1000
		   N2 = N1;

		   
		   DIM1 = N1+2;
		   DIM2 = N2+2;

		   
		   output = "";
		   
		   temp = new int[DIM1];     
	       tx = new int[DIM1][2][DIM2];	   
	       qbnew = new int[DIM1][2][DIM2];
	       
	       if(num_proc == 1)
	    	   seq();
	       else par();
	       
	       
	       
	}
	
	void seq()
	{
		long start = System.currentTimeMillis();
	       
	       
	       uat_RunnableThread r3 = new uat_RunnableThread();
	       
	       r3.temp = temp; r3.tx = tx; r3.qbnew = qbnew;
	       r3.N1 = N1; r3.N2 = N2; 
	       
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
	       
         
	       uat_RunnableThread r1 = new uat_RunnableThread();
	       
	       r1.temp = temp; r1.tx = tx; r1.qbnew = qbnew;
	       r1.N1 = N1; r1.N2 = N2; 
	       
	       r1.id = 0; r1.seq = 0;

	       
	       Thread thread1 = new Thread(r1, "thread1");
	       
	       uat_RunnableThread r2 = new uat_RunnableThread();

	       r2.temp = temp; r2.tx = tx; r2.qbnew = qbnew;
	       r2.N1 = N1; r2.N2 = N2;
	       
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