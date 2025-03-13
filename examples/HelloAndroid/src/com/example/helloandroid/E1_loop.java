package com.example.helloandroid;

import android.widget.TextView;

class e1_RunnableThread implements Runnable {

	Thread runner;
	public int id;
	public int seq;
	
	//arrays
	public int[][] image_buffer1;
	public int[][] image_buffer2;
	public int[][] image_buffer3;

	//symbolic
	public int N;
	
	public TextView tv;
	public e1_RunnableThread() {
	}
	public e1_RunnableThread(String threadName, int z) {
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
			int i, j, lb, ub, temp1, temp2, temp3,T=1;
	
			if(id==0) 
				{
					lb = 1;	ub = N/2;
				}
				else 
				{
					lb = (N/2)+1; ub = N;
				}
			
			for (i = lb-1; i < ub-1; i++) {
				for (j = 0; j < N; ++j) {
				   temp1 = Math.abs(image_buffer1[i][j]);
				   temp2 = Math.abs(image_buffer2[i][j]);
				   temp3 = (temp1 > temp2) ? temp1 : temp2;
				   image_buffer3[i][j] = (temp3 > T) ? 255 : 0;
				 }
				}

		}
		
		//tv.setText("Hello Thread" + Integer.toString(id) );
	}
	
	public void sequential_loop()
	{
		int i, j, temp1, temp2, temp3,T=1;
		
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; ++j) {
			   temp1 = Math.abs(image_buffer1[i][j]);
			   temp2 = Math.abs(image_buffer2[i][j]);
			   temp3 = (temp1 > temp2) ? temp1 : temp2;
			   image_buffer3[i][j] = (temp3 > T) ? 255 : 0;
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


public class E1_loop
{
	public String output;
	public long time;
	
	int N, N1, N2, N3, DIM1, DIM2, DIM3;
	
	int[][] image_buffer1;
	int[][] image_buffer2;
	int[][] image_buffer3;
	
	public E1_loop(int num_proc, int iter)
	{
		   N = iter;   // 100
		   N1 = N;
		   N2 = N1;
		   N3 = N1;
		   
		   DIM1 = N1+2;
		   DIM2 = N2+2;
		   DIM3 = N3+2;
		   
		   output = "";
		   
		   image_buffer1 = new int[DIM1][DIM2];     
		   image_buffer2 = new int[DIM1][DIM2];  
		   image_buffer3 = new int[DIM1][DIM2];  
	
		          
	       if(num_proc == 1)
	    	   seq();
	       else par();
	       
	       
	       
	}
	
	void seq()
	{
		long start = System.currentTimeMillis();
	       
	       
	       e1_RunnableThread r3 = new e1_RunnableThread();
	       
	       r3.image_buffer1 = image_buffer1;
	       r3.image_buffer2 = image_buffer2; 
	       r3.image_buffer3 = image_buffer3; 
	       
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
	       
         
	       e1_RunnableThread r1 = new e1_RunnableThread();
	       
	       r1.image_buffer1 = image_buffer1;
	       r1.image_buffer2 = image_buffer2; 
	       r1.image_buffer3 = image_buffer3; 
	       
	       r1.N = N;
	       
	       r1.id = 0; r1.seq = 0;

	       
	       Thread thread1 = new Thread(r1, "thread1");
	       
	       e1_RunnableThread r2 = new e1_RunnableThread();

	       r2.image_buffer1 = image_buffer1;
	       r2.image_buffer2 = image_buffer2; 
	       r2.image_buffer3 = image_buffer3;
	       
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


/*

for (i = 0; i < N; i++) {
for (j = 0; j < N; ++j) {
   temp1 = abs(image_buffer1[i][j]);
   temp2 = abs(image_buffer2[i][j]);
   temp3 = (temp1 > temp2) ? temp1 : temp2;
   image_buffer3[i][j] = (temp3 > T) ? 255 : 0;
 }
}

*/