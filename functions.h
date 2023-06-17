#include <string>
#include <fstream>
#include <sstream>
using namespace std;


// -------------------------- GLOBAL VARIABLES -----------------------------
	int n = 7;				// no.of layers (input + 5 hidden layers + ouput layer)
	int neurons = 8;		// no.of threads in each hidden layer
	float layer1_weight[2][8] = {0};
	float layer2_weight[8][8] = {0};
	float layer3_weight[8][8] = {0};	
	float layer4_weight[8][8] = {0};	
	float layer5_weight[8][8] = {0}; 
	float output_layer_weight[8] = {0}; 
	
	/*
	float layer1_weight[2][8] = {{0.1,-0.2,0.3,0.1,-0.2,0.3,0.1,-0.2},
								 {0.4,0.5,0.6,-0.4,0.5,0.6,-0.4,0.5}};  // input layer
	
	float layer2_weight[8][8] = {{-0.2,0.3,-0.4,0.5,0.6,-0.7,0.8,-0.9},
								 {0.1,0.9,-0.3,0.2,-0.5,0.4,0.6,-0.8},
								 {-0.7,0.5,0.8,-0.2,-0.3,-0.6,0.1,0.4}, 
								 {-0.2,0.3,-0.4,0.5,0.6,-0.7,0.8,-0.9},
								 {0.1,0.9,-0.3,0.2,-0.5,0.4,0.6,-0.8},
								 {-0.7,0.5,0.8,-0.2,-0.3,-0.6,0.1,0.4},
								 {-0.2,0.3,-0.4,0.5,0.6,-0.7,0.8,-0.9},
								 {0.1,0.9,-0.3,0.2,-0.5,0.4,0.6,-0.8}};
	
	float layer3_weight[8][8] = {{0.3,-0.4,0.5,-0.6,-0.7,0.8,-0.9,0.1},
								 {-0.2,-0.9,0.4,-0.3,0.5,-0.6,-0.8,0.1},
								 {0.6,-0.5,-0.7,0.2,0.4,0.8,-0.1,-0.3},
								 {0.3,-0.4,0.5,-0.6,-0.7,0.8,-0.9,0.1},
								 {-0.2,-0.9,0.4,-0.3,0.5,-0.6,-0.8,0.1},
								 {0.6,-0.5,-0.7,0.2,0.4,0.8,-0.1,-0.3},
								 {0.3,-0.4,0.5,-0.6,-0.7,0.8,-0.9,0.1},
								 {-0.2,-0.9,0.4,-0.3,0.5,-0.6,-0.8,0.1}};
	
	float layer4_weight[8][8] = {{0.4,-0.5,0.6,-0.7,-0.8,0.9,-0.1,0.2},
								 {-0.3,-0.8,0.5,-0.4,0.6,-0.7,-0.9,0.2},
								 {0.5,-0.4,-0.6,0.3,0.2,0.8,-0.2,-0.1},
								 {0.4,-0.5,0.6,-0.7,-0.8,0.9,-0.1,0.2},
								 {-0.3,-0.8,0.5,-0.4,0.6,-0.7,-0.9,0.2},
								 {0.5,-0.4,-0.6,0.3,0.2,0.8,-0.2,-0.1},
								 {0.4,-0.5,0.6,-0.7,-0.8,0.9,-0.1,0.2},
								 {-0.3,-0.8,0.5,-0.4,0.6,-0.7,-0.9,0.2}};
		
	float layer5_weight[8][8] = {{0.5,-0.6,0.7,-0.8,-0.9,0.1,-0.2,0.3},
								 {-0.4,-0.7,0.6,-0.5,0.8,-0.6,-0.2,0.1},
								 {0.4,-0.3,-0.5,0.1,0.6,0.7,-0.3,-0.2},
								 {0.5,-0.6,0.7,-0.8,-0.9,0.1,-0.2,0.3},
								 {-0.4,-0.7,0.6,-0.5,0.8,-0.6,-0.2,0.1},
								 {0.4,-0.3,-0.5,0.1,0.6,0.7,-0.3,-0.2},
								 {0.5,-0.6,0.7,-0.8,-0.9,0.1,-0.2,0.3},
								 {-0.4,-0.7,0.6,-0.5,0.8,-0.6,-0.2,0.1}};
	
	float output_layer_weight[8] = {-0.1,0.2,0.3,0.4,0.5,-0.6,-0.7,0.8};*/


// ------------------------------ HIDDEN LAYERS' NEURONS ----------------------------------
void *layer_thread(void* arg)
{
	Argument* a = (Argument *)arg;
	float temp;
	string s = "";
	for(int i = 0; i < neurons; i++)
	{
    	temp = a->input * a->weight[i];
    	s += to_string(temp);
    	s += ",";
   	}
   	s += "\n";
   	
   	char const *buffer = s.c_str();
   	int x = open(a->p, O_WRONLY);
   	write (x, buffer, 200);
   	close(x);
	
	pthread_exit(NULL);
}




// ---------------------------- LAST HIDDEN lAYER'S NEURON -------------------------------
void *last_layer_thread(void* arg)
{
	last_arg* a = (last_arg*)arg;
	float temp;
	string s = "";
	temp = a->input * a->weight;
	s += to_string(temp);
	s += ",";
   	s += "\n";
   	
   	char const *buffer = s.c_str();
   	int x = open(a->p, O_WRONLY);
   	write (x, buffer, 200);
   	close(x);
	pthread_exit(NULL);
}



// ------------------------------- OUTPUT LAYERS' NEURON ---------------------------------
void *output_layer_thread(void* arg)
{
	output_arg* a = (output_arg*)arg;
	float temp;
	string s = "";
	temp = a->input;
	s += to_string(temp);
	s += ",";
   	s += "\n";
   	
   	char const *buffer = s.c_str();
   	int x = open(a->p, O_WRONLY);
   	write (x, buffer, 200);
   	close(x);
   	
	pthread_exit(NULL);
}



// ------------------------------- READING FILES FOR WEIGHTS ---------------------------------
void read_file()
{
	int i=0, j=0;
	string value;
	string line;
	
    ifstream file("layer1_weights.txt");
	while (getline(file, line))
	{
		stringstream ss(line);
		while (getline(ss, value, ',')) 
		{
		  layer1_weight[i][j] = stof(value);
		  j++;
		}
		i++; j=0;
	}
	file.close();
	
	
	
	i=0, j=0;
    ifstream file1("layer2_weights.txt");
	while (getline(file1, line))
	{
		stringstream ss1(line);
		while (getline(ss1, value, ',')) 
		{
		  layer2_weight[i][j] = stof(value);
		  j++;
		}
		i++; j=0;
	}
	file1.close();
	
	
	
	i=0, j=0;
    ifstream file2("layer3_weights.txt");
	while (getline(file2, line))
	{
		stringstream ss2(line);
		while (getline(ss2, value, ',')) 
		{
		  layer3_weight[i][j] = stof(value);
		  j++;
		}
		i++; j=0;
	}
	file2.close();
	
	
	
	i=0, j=0;
    ifstream file3("layer4_weights.txt");
	while (getline(file3, line))
	{
		stringstream ss3(line);
		while (getline(ss3, value, ',')) 
		{
		  layer4_weight[i][j] = stof(value);
		  j++;
		}
		i++; j=0;
	}
	file3.close();
	
	
	i=0, j=0;
    ifstream file4("layer5_weights.txt");
	while (getline(file4, line))
	{
		stringstream ss4(line);
		while (getline(ss4, value, ',')) 
		{
		  layer5_weight[i][j] = stof(value);
		  j++;
		}
		i++; j=0;
	}
	file4.close();
	
	
	j=0;
    ifstream file5("output_weight.txt");
	while (getline(file5, line))
	{
		stringstream ss5(line);
		while (getline(ss5, value, ',')) 
		{
		  output_layer_weight[j] = stof(value);
		  j++;
		}
	}
	file5.close();
}








