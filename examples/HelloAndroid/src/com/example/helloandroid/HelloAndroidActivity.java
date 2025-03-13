// FT_aux_2 Android Java

package com.example.helloandroid;
import java.io.File;



import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import android.view.KeyEvent;
import android.view.View;


import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;
import android.widget.*;

import jomp.compiler.*;
import jomp.runtime.*;

import java.io.*;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.BufferedReader;





public class HelloAndroidActivity extends Activity {
   /** Called when the activity is first created. */
   @Override
   public void onCreate(Bundle savedInstanceState) {  
	   super.onCreate(savedInstanceState);	   
	  // TextView tv = new TextView(this);
	   setContentView(R.layout.main);
	   
	   

	   
	   
	   Button button = (Button) findViewById(R.id.button1);
	   
	   final RadioButton radio0 = (RadioButton) findViewById(R.id.radio0);
	   final RadioButton radio1 = (RadioButton) findViewById(R.id.radio1);
	   final RadioButton radio2 = (RadioButton) findViewById(R.id.radio2);
	   final RadioButton radio3 = (RadioButton) findViewById(R.id.radio3);
	   final RadioButton radio4 = (RadioButton) findViewById(R.id.radio4);
	   final RadioButton radio5 = (RadioButton) findViewById(R.id.radio5);
	   final RadioButton radio6 = (RadioButton) findViewById(R.id.radio6);
	   final RadioButton radio7 = (RadioButton) findViewById(R.id.radio7);
	   final EditText edittext2 = (EditText) findViewById(R.id.editText2);
	   
	   final EditText edit_count = (EditText) findViewById(R.id.EditText01);
	   final EditText edit_param = (EditText) findViewById(R.id.editText1);
	   final EditText threads_param = (EditText) findViewById(R.id.editText3);
	   

       button.setOnClickListener(new View.OnClickListener() {
       	@Override
       	public void onClick(View v) {
       	  long av_time = 0;
       	  int iter = Integer.parseInt(edit_count.getText().toString());
       	  int param = Integer.parseInt(edit_param.getText().toString());
       	  int num_threads = Integer.parseInt(threads_param.getText().toString());
       	  
       	  String params[];
          String set_calc = edittext2.getText().toString();
       	  if(set_calc.contains(","))
       	  {
       		  params = set_calc.split(",");
       		  int petla = Integer.parseInt(params[0]);
       		  iter = Integer.parseInt(params[1]);
       		  edit_count.setText(params[1]);
       		  param = Integer.parseInt(params[2]);
       		  edit_param.setText(params[2]);
       		  num_threads = Integer.parseInt(params[3]);
       		  threads_param.setText(params[3]);
       		  if(petla ==0)
       			  radio0.setChecked(true);
       		  if(petla ==1)
       			  radio1.setChecked(true);
       		  if(petla ==2)
       			  radio2.setChecked(true);
       		  if(petla ==3)
       			  radio3.setChecked(true);
       		  if(petla ==4)
       			  radio4.setChecked(true);
       		  if(petla ==5)
       			  radio5.setChecked(true);
       		  if(petla ==6)
       			  radio6.setChecked(true);
       		  if(petla ==7)
       			  radio7.setChecked(true);
       	  }
       		
       	  
       	for(int i = 0; i<iter;i++)
   		{
         	 if(radio0.isChecked()){
         			FX_loop fx = new FX_loop(num_threads, param);
         			av_time += fx.time;

             }
         	 
          	  if(radio1.isChecked()){
                 MG13_loop mg13 = new MG13_loop(num_threads, param);
                 av_time += mg13.time;
             }
          	  
          	 if(radio2.isChecked()){
            	 UAT_loop uat = new UAT_loop(num_threads, param);
            	 av_time += uat.time;
          	 }
       	  
          	 if(radio3.isChecked()){
          		 UAD4_loop uad4 = new UAD4_loop(num_threads, param);
          		av_time += uad4.time;
          	 }      	  
       	  
          	 if(radio4.isChecked()){
          		 UAS_loop uas = new UAS_loop(num_threads, param);
          		 av_time += uas.time;
          	 }
          	 if(radio5.isChecked()){
          		 H3_loop uas = new H3_loop(num_threads, param);
          		 av_time += uas.time;
          	 }
          	 
          	 if(radio6.isChecked()){
          		 E1_loop uas = new E1_loop(num_threads, param);
          		 av_time += uas.time;
          	 }
          	 
          	 if(radio7.isChecked()){
          		 C2_loop uas = new C2_loop(num_threads, param);
          		 av_time += uas.time;
          	 }
   		}
	 
       	  
  		av_time /= iter;      		
       	edittext2.setText(Long.toString(av_time) + " " + Integer.toString(iter));  // fx.output

       	String filename = "filename.txt";
       	File file = new File(Environment.getExternalStorageDirectory(), filename);
       	FileOutputStream fos;
       	byte[] data = new String("data to write to file").getBytes();
       	try {
       	    fos = new FileOutputStream(file);
       	    fos.write(data);
       	    fos.flush();
       	    fos.close();
       	} catch (FileNotFoundException e) {
       	    // handle exception
       	} catch (IOException e) {
       	    // handle exception
       	}
       	
       	}
        });     
	   
	   
	   try
	   {
		   File f = new File("/sdcard/params.txt");
		   FileInputStream instream = new FileInputStream(f);
		   if(instream != null){
			   InputStreamReader inputreader = new InputStreamReader(instream);
			   BufferedReader bufferedreader = new BufferedReader(inputreader);

			   
			   edittext2.setText(bufferedreader.readLine());

			   if(edittext2.getText().toString() != "")
				   button.performClick();
			   
		   }
		   instream.close();
	    } catch(java.io.IOException e){
   	   }
	   
       
       



        
   }
   

  

}