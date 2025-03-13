package com.example.helloandroid;

import android.widget.TextView;

class uas_RunnableThread implements Runnable {

	Thread runner;
	public int id;
	public int seq;
	//arrays
	public int[][][] tm2, u;
	public int [][] wtdr;
	//symbolic
	public int N1, N2, N3, N4;
	
	public TextView tv;
	public uas_RunnableThread() {
	}
	public uas_RunnableThread(String threadName, int z) {
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
			int t1=0,t2=0,t3=0,t4=0,ub,lb;
	
			if(id==0) 
				{
					lb = 1;	ub = N1/2;
				}
				else 
				{
					lb = (N1/2)+1; ub = N1;
				}
			
			if (N3 >= 1 && N2 >= 2 && N4 >= 1) { 
				/*par */ for(t1 = lb; t1 <= ub; t1++) { 
				 /*par */ for(t3 = 1; t3 <= N3; t3++) { 
				 /*par */  for(t4 = 1; t4 <= N4; t4++) { 
				   tm2[t4][t3][t1] = tm2[t4][t3][t1]+ u[t4][1][t3]*wtdr[1][t3]; 
				   if (t1 >= 1 && t4 >= 1 && t4 <= N4 && t3 >= 1 && t3 <= N3 && N1 >= t1) { 
				     for(t2 = 2; t2 <= N2; t2++) { 
				      tm2[t4][t3][t1] = tm2[t4][t3][t1] +u[t4][t2][t3]*wtdr[t2][t3]; 
				     } 
				    } 	
				   } 
				  } 
				 } 
				} 

		}
		
		//tv.setText("Hello Thread" + Integer.toString(id) );
	}
	
	public void sequential_loop()
	{
		int i=0,j=0,k=0,iz=0;
		
		for(iz=1; iz<=N1; iz++) 
			  for(k=1; k<=N2; k++) 
			    for(j=1; j<=N3; j++) 
			      for(i=1; i<=N4; i++)
			         tm2[i][j][iz] = tm2[i][j][iz]+u[i][k][j]*wtdr[k][j]; 
		
	}
	
	public void jomp_loop()
	{
		
		
	}

}


public class UAS_loop
{
	public String output;
	public long time;
	
	int N1, N2, N3, N4, DIM1, DIM2, DIM3, DIM4;
	
	int[][][] tm2;
	int[][][] u;
	int[][] wtdr;
	
	public UAS_loop(int num_proc, int iter)
	{
		   N1 = iter;   // 100
		   N2 = N1;
		   N3 = N1;
		   N4 = N1;
		   
		   DIM1 = N1+2;
		   DIM2 = N2+2;
		   DIM3 = N3+2;
		   DIM4 = N4+2;
		   
		   output = "";
		   
		   tm2 = new int[DIM1][DIM2][DIM3];     
	       u = new int[DIM1][DIM2][DIM3];	   
	       wtdr = new int[DIM1][DIM2];
	       
	       if(num_proc == 1)
	    	   seq();
	       else par();
	       
	       
	       
	}
	
	void seq()
	{
		long start = System.currentTimeMillis();
	       
	       
	       uas_RunnableThread r3 = new uas_RunnableThread();
	       
	       r3.u = u; r3.tm2 = tm2; r3.wtdr = wtdr;
	       r3.N1 = N1; r3.N2 = N2; r3.N3 = N3; r3.N4 = N4;
	       
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
	       
         
	       uas_RunnableThread r1 = new uas_RunnableThread();
	       
	       r1.u = u; r1.tm2 = tm2; r1.wtdr = wtdr;
	       r1.N1 = N1; r1.N2 = N2; r1.N3 = N3; r1.N4 = N4;
	       
	       r1.id = 0; r1.seq = 0;

	       
	       Thread thread1 = new Thread(r1, "thread1");
	       
	       uas_RunnableThread r2 = new uas_RunnableThread();

	       r2.u = u; r2.tm2 = tm2; r2.wtdr = wtdr;
	       r2.N1 = N1; r2.N2 = N2; r2.N3 = N3; r2.N4 = N4;
	       
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