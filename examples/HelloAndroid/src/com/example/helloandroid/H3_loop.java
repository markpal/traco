package com.example.helloandroid;

import android.widget.TextView;

class h3_RunnableThread implements Runnable {

	Thread runner;
	public int id;
	public int seq;
	
	//arrays
	public int[][] image;
	public int[] gray_level_mapping;
	//symbolic
	public int N;
	
	public TextView tv;
	public h3_RunnableThread() {
	}
	public h3_RunnableThread(String threadName, int z) {
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
			int i, ii, j, lb, ub;
	
			if(id==0) 
				{
					lb = 1;	ub = N/2;
				}
				else 
				{
					lb = (N/2)+1; ub = N;
				}
			
			  for (i = lb-1; i < ub-1; i++) {
				    ii = image[i][0];
				    for (j = 1; j < N; ++j) {
				        image[i][j-1] = gray_level_mapping[ii];
					ii = image[i][j];
				    }
				    image[i][N-1] = gray_level_mapping[ii];
			  }

		}
		
		//tv.setText("Hello Thread" + Integer.toString(id) );
	}
	
	public void sequential_loop()
	{
		int i, ii, j;
		
		for (i = 0; i < N; i++) {
		    ii = image[i][0];
		    for (j = 1; j < N; ++j) {
		        image[i][j-1] = gray_level_mapping[ii];
			ii = image[i][j];
		    }
		    image[i][N-1] = gray_level_mapping[ii];
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


public class H3_loop
{
	public String output;
	public long time;
	
	int N, N1, N2, N3, DIM1, DIM2, DIM3;
	
	int[][] image;
	int[] gray_level_mapping;
	
	public H3_loop(int num_proc, int iter)
	{
		   N = iter;   // 100
		   N1 = N;
		   N2 = N1;
		   N3 = N1;
		   
		   DIM1 = N1+2;
		   DIM2 = N2+2;
		   DIM3 = N3+2;
		   
		   output = "";
		   
		   image = new int[DIM1][DIM2];     
		   gray_level_mapping = new int[DIM1];	
		   
		   for(int z1=0; z1<iter; z1++)
			   for(int z2=0; z2<iter; z2++)
				   image[z1][z2] = z1;
	       
	       if(num_proc == 1)
	    	   seq();
	       else par();
	       
	       
	       
	}
	
	void seq()
	{
		long start = System.currentTimeMillis();
	       
	       
	       h3_RunnableThread r3 = new h3_RunnableThread();
	       
	       r3.image = image; r3.gray_level_mapping = gray_level_mapping; 
	       r3.N = N;
	       
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
	       
         
	       h3_RunnableThread r1 = new h3_RunnableThread();
	       
	       r1.image = image; r1.gray_level_mapping = gray_level_mapping; 
	       r1.N = N;
	       
	       r1.id = 0; r1.seq = 0;

	       
	       Thread thread1 = new Thread(r1, "thread1");
	       
	       h3_RunnableThread r2 = new h3_RunnableThread();

	       r2.image = image; r2.gray_level_mapping = gray_level_mapping; 
	       r2.N = N;
	       
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
