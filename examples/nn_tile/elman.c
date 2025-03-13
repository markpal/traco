// Author:		John McCullock
// Date:		10-15-05
// Description:	Elman Network Example 1.

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <ctime>
#include <cstdlib>
#include <omp.h>
#include<sys/time.h>

using namespace std;

const int maxTests = 1;
const int maxSamples = 4;

const int inputNeurons = 2000;
const int hiddenNeurons = 2000;
const int outputNeurons = 2000;
const int contextNeurons = 2000;

const double learnRate = 0.2;    //Rho.
const int trainingReps = 2;

//beVector is the symbol used to start or end a sequence.
double beVector[inputNeurons] = {1.0, 0.0, 0.0, 0.0, 0.0, 0.0};

                                     //  0    1    2    3    4    5
double sampleInput[3][inputNeurons] = {{0.0, 0.0, 0.0, 1.0, 0.0, 0.0},
                                       {0.0, 0.0, 0.0, 0.0, 0.0, 1.0},
                                       {0.0, 0.0, 1.0, 0.0, 0.0, 0.0}};

//Input to Hidden weights (with biases).
double wih[inputNeurons + 1][hiddenNeurons];

//Context to Hidden weights (with biases).
double wch[contextNeurons + 1][hiddenNeurons];

//Hidden to Output weights (with biases).
double who[hiddenNeurons + 1][outputNeurons];

//Hidden to Context weights (no biases).
double whc[outputNeurons + 1][contextNeurons];

//Activations.
double inputs[inputNeurons];
double hidden[hiddenNeurons];
double target[outputNeurons];
double actual[outputNeurons];
double context[contextNeurons];

//Unit errors.
double erro[outputNeurons];
double errh[hiddenNeurons];


void ElmanNetwork();
void testNetwork();
void feedForward();
void backPropagate();
void assignRandomWeights();
int getRandomNumber();
double sigmoid(double val);
double sigmoidDerivative(double val);

int main(int argc, char *argv[]){
  // variables to meassure time
  struct timeval s1, f1;
  double  duration, duration1;
int num_proc=1;
  num_proc = atoi(argv[1]);
omp_set_num_threads(num_proc);
 //   cout << fixed << setprecision(3) << endl;           //Format all the output.
  gettimeofday(&s1, NULL);
    srand((unsigned)time(0));   //Seed random number generator with system time.
    ElmanNetwork();
    testNetwork();
  gettimeofday(&f1, NULL);
  duration = (double)f1.tv_sec + ((double)f1.tv_usec/1000000) - ((double)s1.tv_sec + ((double)s1.tv_usec/1000000));
  cout << duration;
    return 0;
}

void ElmanNetwork(){
    double err;
    int sample = 0;
    int iterations = 0;
    bool stopLoop = false;
int i;
    
    assignRandomWeights();
omp_set_num_threads(2);

    //Train the network.
    do {

        if(sample == 0){
          
	for(i = 0; i <= (inputNeurons - 1); i++){
                inputs[i] = beVector[i];
            } // i
        } else {

            for(i = 0; i <= (inputNeurons - 1); i++){
                inputs[i] = sampleInput[sample - 1][i];
            } // i
        }

        //After the samples are entered into the input units, the sample are
        //then offset by one and entered into target-output units for
        //later comparison.
        if(sample == maxSamples - 1){

            for(i = 0; i <= (inputNeurons - 1); i++){
                target[i] = beVector[i];
            } // i
        } else {

            for(i = 0; i <= (inputNeurons - 1); i++){
                target[i] = sampleInput[sample][i];
            } // i
        }

        feedForward();

        err = 0.0;
 #pragma omp parallel for reduction(+:err)
        for(i = 0; i <= (outputNeurons - 1); i++){ 
            err += sqrt(target[i] - actual[i]);
        } // i
        err = 0.5 * err;

        if(iterations > trainingReps){
            stopLoop = true;
        }
        iterations += 1;

        backPropagate();

        sample += 1;
        if(sample == maxSamples){
            sample = 0;
        }
    } while(stopLoop == false);

  //  cout << "Iterations = " << iterations << endl;
}

void testNetwork(){
    int index;
    int randomNumber, predicted;
    bool stopTest, stopSample, successful;

    //Test the network with random input patterns.
    stopTest = false;
    for(int test = 0; test <= maxTests; test++){
        
        //Enter Beginning string.
        inputs[0] = 1.0;
        inputs[1] = 0.0;
        inputs[2] = 0.0;
        inputs[3] = 0.0;
        inputs[4] = 0.0;
        inputs[5] = 0.0;
    //    cout << "(0) ";

        feedForward();

        stopSample = false;
        successful = false;
        index = 0;
        randomNumber = 0;
        predicted = 0;
        
        do {

            for(int i = 0; i <= 5; i++){
              //  cout << actual[i] << " ";
                if(actual[i] >= 0.3){
                    //The output unit with the highest value (usually over 3.0)
                    //is the network's predicted unit that it expects to appear
                    //in the next input vector.
                    //For example, if the 3rd output unit has the highest value,
                    //the network expects the 3rd unit in the next input to
                    //be 1.0
                    //If the actual value isn't what it expected, the random
                    //sequence has failed, and a new test sequence begins.
                    predicted = i;
                }
            } // i
           // cout << "\n";

            randomNumber = getRandomNumber(); //Enter a random letter.
            
            index += 1;              //Increment to the next position.
            if(index == 5){
                stopSample = true;
            } else {
           //     cout << "(" << randomNumber << ") ";
            }

            for(int i = 0; i <= 5; i++){
                if(i == randomNumber){
                    inputs[i] = 1.0;
                    if(i == predicted){
                        successful = true;
                    } else {
                        //Failure. Stop this sample and try a new sample.
                        stopSample = true;
                    }
                } else {
                    inputs[i] = 0.0;
                }
            } // i

            feedForward();

        } while(stopSample == false); //Enter another letter into this sample sequence.

        if((index > 4) && (successful == true)){
            //If the random sequence happens to be in the correct order,
            //the network reports success.
         //   cout << "Success." << endl;
          //  cout << "Completed " << test << " tests." << endl;
            stopTest = true;
            break;
        } else {
         //   cout << "Failed." << endl;
            if(test > maxTests){
                stopTest = true;
             //   cout << "Completed " << test << " tests with no success." << endl;
                break;
            }
        }
    } // Test
}

void feedForward(){
    double sum;
int out, hid, inp, con;
    //Calculate input and context connections to hidden layer.
    #pragma omp parallel for private(hid, inp, con, sum) default(shared)
    for(hid = 0; hid <= (hiddenNeurons - 1); hid++){
        sum = 0.0;
        //from input to hidden...
        for(inp = 0; inp <= (inputNeurons - 1); inp++){
            sum += inputs[inp] * wih[inp][hid];
        } // inp
        //from context to hidden...
        for(int con = 0; con <= (contextNeurons - 1); con++){
            sum += context[con] * wch[con][hid];
        } // con
        //Add in bias.
        sum += wih[inputNeurons][hid];
        sum += wch[contextNeurons][hid];
        hidden[hid] = sigmoid(sum);
    } // hid

    //Calculate the hidden to output layer.
   #pragma omp parallel for private(hid, out, con, sum) default(shared)
    for(out = 0; out <= (outputNeurons - 1); out++){
        sum = 0.0;
        for(hid = 0; hid <= (hiddenNeurons - 1); hid++){
            sum += hidden[hid] * who[hid][out];
        } // hid

        //Add in bias.
        sum += who[hiddenNeurons][out];
        actual[out] = sigmoid(sum);
    } // out

    //Copy outputs of the hidden to context layer.
    for(int con = 0; con <= (contextNeurons - 1); con++){
        context[con] = hidden[con];
    } // con

}

void backPropagate(){
    int out, hid, inp, con;
    //Calculate the output layer error (step 3 for output cell).
    for(out = 0; out <= (outputNeurons - 1); out++){
        erro[out] = (target[out] - actual[out]) * sigmoidDerivative(actual[out]);
    } // out

    //Calculate the hidden layer error (step 3 for hidden cell).
   #pragma omp parallel for private(hid, out, con) default(shared)
    for(hid = 0; hid <= (hiddenNeurons - 1); hid++){
        errh[hid] = 0.0;
        for(out = 0; out <= (outputNeurons - 1); out++){
            errh[hid] += erro[out] * who[hid][out];
        } // out
        errh[hid] *= sigmoidDerivative(hidden[hid]);
    } // hid

 #pragma omp parallel for private(hid, out, con) default(shared)
    //Update the weights for the output layer (step 4).
    for(int out = 0; out <= (outputNeurons - 1); out++){
        for(int hid = 0; hid <= (hiddenNeurons - 1); hid++){
            who[hid][out] += (learnRate * erro[out] * hidden[hid]);
        } // hid
        //Update the bias.
        who[hiddenNeurons][out] += (learnRate * erro[out]);
    } // out

 #pragma omp parallel for private(hid, inp, con) default(shared)
    //Update the weights for the hidden layer (step 4).
    for(hid = 0; hid <= (hiddenNeurons - 1); hid++){
        for(inp = 0; inp <= (inputNeurons - 1); inp++){
            wih[inp][hid] += (learnRate * errh[hid] * inputs[inp]);
        } // inp
        //Update the bias.
        wih[inputNeurons][hid] += (learnRate * errh[hid]);
    } // hid

}

void assignRandomWeights(){
    int out, hid, inp, con;
#pragma omp parallel for private(hid, inp, con) default(shared)    
for(int inp = 0; inp <= inputNeurons; inp++){
        for(int hid = 0; hid <= (hiddenNeurons - 1); hid++){
            //Assign a random weight value between -0.5 and 0.5
            wih[inp][hid] = -0.5 + double(rand()/(RAND_MAX + 1.0));
        } // hid
    } // inp

#pragma omp parallel for private(hid, inp, con) default(shared)
    for(con = 0; con <= contextNeurons; con++){
        for(hid = 0; hid <= (hiddenNeurons - 1); hid++){
            //Assign a random weight value between -0.5 and 0.5
            wch[con][hid] = -0.5 + double(rand()/(RAND_MAX + 1.0));
        } // hid
    } // con

#pragma omp parallel for private(hid, inp, con, out) default(shared)
    for(hid = 0; hid <= hiddenNeurons; hid++){
        for(out = 0; out <= (outputNeurons - 1); out++){
            //Assign a random weight value between -0.5 and 0.5
            who[hid][out] = -0.5 + double(rand()/(RAND_MAX + 1.0));
        } // out
    } // hid


#pragma omp parallel for private(hid, inp, con) default(shared)
    for(out = 0; out <= outputNeurons; out++){
        for(con = 0; con <= (contextNeurons - 1); con++){
            //These are all fixed weights set to 0.5
            whc[out][con] = 0.5;
        } // con
    } // out

}

int getRandomNumber(){
    //Generate random value between 0 and 6.
    return int(6*rand()/(RAND_MAX + 1.0));
}

double sigmoid(double val){
    return (1.0 / (1.0 + exp(-val)));
}

double sigmoidDerivative(double val){
    return (val * (1.0 - val));
}
