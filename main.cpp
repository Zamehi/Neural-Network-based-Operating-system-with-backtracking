#include <iostream>
#include <unistd.h>
#include <fcntl.h>			// writing & reading modes
#include <sys/stat.h>		// for mkfifo
#include <sys/wait.h>
#include <pthread.h>
#include "argument.h"
#include "functions.h"
using namespace std;




// --------------------------- MAIN FUNCTION -------------------------------
int main()
{
	int input = 2;
	
	float input_val[input] = {0.1, 0.2};
	float input_layer_output[input][neurons] = {0};
	float layer1_input[neurons] = {0};
	float layer1_output[neurons][neurons] = {0};
	float layer2_input[neurons] = {0};
	float layer2_output[neurons][neurons] = {0};
	float layer3_input[neurons] = {0};
	float layer3_output[neurons][neurons] = {0};
	float layer4_input[neurons] = {0};
	float layer4_output[neurons][neurons] = {0};
	float layer5_input[neurons] = {0};
	float layer5_output[neurons][1] = {0};
	float output = 0, output_read = 0;

	mkfifo("pipe1", 0666);  mkfifo("pipe5", 0666);  mkfifo("pipe9", 0666);
	mkfifo("pipe2", 0666);  mkfifo("pipe6", 0666);  mkfifo("pipe10", 0666);
	mkfifo("pipe3", 0666);  mkfifo("pipe7", 0666);  mkfifo("pipe11", 0666);
	mkfifo("pipe4", 0666);  mkfifo("pipe8", 0666);  mkfifo("pipe12", 0666);
	mkfifo("pipe13", 0666); mkfifo("pipe14", 0666); mkfifo("pipe15", 0666);  
	mkfifo("pipe16", 0666); mkfifo("pipe17", 0666); mkfifo("pipe18", 0666);  
	mkfifo("pipe19", 0666); mkfifo("pipe20", 0666); mkfifo("pipe21", 0666);
	mkfifo("pipe22", 0666);	mkfifo("pipe23", 0666);	mkfifo("pipe24", 0666);
	mkfifo("pipe25", 0666);	mkfifo("pipe26", 0666);	mkfifo("pipe27", 0666);
	mkfifo("pipe28", 0666);	mkfifo("pipe29", 0666);	mkfifo("pipe30", 0666);
	mkfifo("pipe31", 0666);	mkfifo("pipe32", 0666);	mkfifo("pipe33", 0666);
	mkfifo("pipe34", 0666);	mkfifo("pipe35", 0666);	mkfifo("pipe36", 0666);
	mkfifo("pipe37", 0666);	mkfifo("pipe38", 0666);	mkfifo("pipe39", 0666);
	mkfifo("pipe40", 0666);	mkfifo("pipe41", 0666);	mkfifo("pipe42", 0666);
	mkfifo("pipe43", 0666);
	
	int var = 0;
	read_file();
	
	//do {
	//jump_point:
	while(var<=1)
	{
		// *******************************************************************************
		// ************************ CREATING LAYERS DYNAMICALLY **************************
		// *******************************************************************************
		// CREATING n ARRAY FOR STORING n PROCESSES IDs 
		pid_t* p = new pid_t[n];		
		for(int i = 0; i < n; i++)
			p[i] = -1;
		
		// 	CREATING n PROCESSES -- 'n' layers <- 'n' child processes
		p[0] = fork();					// input layer
		for(int i = 0; i < n-1; i++)
		{
			if(p[i] > 0)				// if parent process => create another process
			{
				p[i+1] = fork();
			} 
		}	
		
		//jump_point:
		//  ############################### INPUT LAYER ################################
		if(p[0] == 0)	
		{
			pthread_t pid[input];
			pthread_attr_t t[input];
	   		
	   		Argument arg1(input_val[0], "pipe1", 0, layer1_weight);	
			pthread_attr_init(&t[0]);
			pthread_attr_setdetachstate(&t[0], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid[0], &t[0], layer_thread, &arg1);
			
			Argument arg2(input_val[1], "pipe2", 1, layer1_weight);	
			pthread_attr_init(&t[1]);
			pthread_attr_setdetachstate(&t[1], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid[1], &t[1], layer_thread, &arg2);
			//exit(0);
		}
		

		
		
			sleep(2);
		//  ############################# HIDDEN LAYER 1 ###############################
		if(p[1] == 0)	
		{
			cout << "\n\tInput Layer's Output => \n";
			char buff1[100] = {'\0'}, buff2[100] = {'\0'};
			
			int y = open("pipe1", O_RDONLY);
			read(y, buff1, sizeof(buff1));
			cout << buff1;
			close(y);
			
			int z = open("pipe2", O_RDONLY);
			read(z, buff2, sizeof(buff2));
			cout << buff2 << endl;
			close(z);
			
			string s = "", ss = "";
			int i = 0, j = 0, k = 0;
			while(j != neurons || k != neurons)
			{
				s += buff1[i];		ss += buff2[i];
				if(buff1[i] == ',' )
				{
					s.pop_back();
					input_layer_output[0][j] = stof(s);
					j++;
					s = "";
				}
				if(buff2[i] == ',')
				{
					ss.pop_back();
					input_layer_output[1][k] = stof(ss);
					k++;
					ss = "";
				}
				i++;
			}
			
			cout << "Hidden Layer 1 Input :: \n"; 
			for(int i = 0; i < neurons; i++) {
				layer1_input[i] = input_layer_output[0][i] + input_layer_output[1][i];
				cout << layer1_input[i] << " | "; 
			}
			cout << endl << endl;

			
			pthread_t pid1[neurons];
			pthread_attr_t t1[neurons];
	   		
	   		Argument arg3(layer1_input[0], "pipe3", 0, layer2_weight);	
			pthread_attr_init(&t1[0]);
			pthread_attr_setdetachstate(&t1[0], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid1[0], &t1[0], layer_thread, &arg3);
			
			Argument arg4(layer1_input[1], "pipe4", 1, layer2_weight);	
			pthread_attr_init(&t1[1]);
			pthread_attr_setdetachstate(&t1[1], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid1[1], &t1[1], layer_thread, &arg4);
			
			Argument arg5(layer1_input[2], "pipe5", 2, layer2_weight);	
			pthread_attr_init(&t1[2]);
			pthread_attr_setdetachstate(&t1[2], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid1[2], &t1[2], layer_thread, &arg5);
			
			Argument arg6(layer1_input[3], "pipe6", 3, layer2_weight);	
			pthread_attr_init(&t1[3]);
			pthread_attr_setdetachstate(&t1[3], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid1[3], &t1[3], layer_thread, &arg6);
			
			Argument arg7(layer1_input[4], "pipe7", 4, layer2_weight);	
			pthread_attr_init(&t1[4]);
			pthread_attr_setdetachstate(&t1[4], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid1[4], &t1[4], layer_thread, &arg7);
			
			Argument arg8(layer1_input[5], "pipe8", 5, layer2_weight);	
			pthread_attr_init(&t1[5]);
			pthread_attr_setdetachstate(&t1[5], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid1[5], &t1[5], layer_thread, &arg8);
			
			Argument arg9(layer1_input[6], "pipe9", 6, layer2_weight);	
			pthread_attr_init(&t1[6]);
			pthread_attr_setdetachstate(&t1[6], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid1[6], &t1[6], layer_thread, &arg9);
			
			Argument arg10(layer1_input[7], "pipe10", 7, layer2_weight);	
			pthread_attr_init(&t1[7]);
			pthread_attr_setdetachstate(&t1[7], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid1[7], &t1[7], layer_thread, &arg10);
			//exit(0);
		}
			
			
			
			sleep(2);
		//  ############################# HIDDEN LAYER 2 ###############################
		if(p[2] == 0)	
		{
			cout << "\n\tHidden Layer 1 Output =>  \n";
			char b1[100] = {'\0'}, b2[100] = {'\0'}, b3[100] = {'\0'}, b4[100] = {'\0'},
				 b5[100] = {'\0'}, b6[100] = {'\0'}, b7[100] = {'\0'}, b8[100] = {'\0'};
			
			int t = open("pipe3", O_RDONLY);
			read(t, b1, sizeof(b1));
			cout << b1;
			close(t);
			
			int u = open("pipe4", O_RDONLY);
			read(u, b2, sizeof(b2));
			cout << b2;
			close(u);
			
			int v = open("pipe5", O_RDONLY);
			read(v, b3, sizeof(b3));
			cout << b3;
			close(v);
			
			int w = open("pipe6", O_RDONLY);
			read(w, b4, sizeof(b4));
			cout << b4 ;
			close(w);
			
			int x = open("pipe7", O_RDONLY);
			read(x, b5, sizeof(b5));
			cout << b5;
			close(x);
			
			int y = open("pipe8", O_RDONLY);
			read(y, b6, sizeof(b6));
			cout << b6;
			close(y);
			
			int z = open("pipe9", O_RDONLY);
			read(z, b7, sizeof(b7));
			cout << b7;
			close(z);
			
			int h = open("pipe10", O_RDONLY);
			read(h, b8, sizeof(b8));
			cout << b8 << endl;
			close(h);
			
			string s = "", ss = "", sss = "", ssss = "";
			string s1 = "", ss1 = "", sss1 = "", ssss1 = "";
			int i = 0, j = 0, k = 0, l = 0, m = 0, r = 0, o = 0, d = 0, q = 0;
			
			while(j != neurons || k != neurons || l != neurons || m != neurons || 
				  r != neurons || o != neurons || d != neurons || q != neurons )
			{	 
				s += b1[i];		ss += b2[i];	sss += b3[i];	ssss += b4[i];
				s1+= b5[i];		ss1+= b6[i];	sss1+= b7[i];	ssss1+= b8[i];
				if(b1[i] == ',' )
				{
					s.pop_back();
					layer1_output[0][j] = stof(s);
					j++;
					s = "";
				}
				if(b2[i] == ',')
				{
					ss.pop_back();
					layer1_output[1][k] = stof(ss);
					k++;
					ss = "";
				}
				if(b3[i] == ',' )
				{
					sss.pop_back();
					layer1_output[2][l] = stof(sss);
					l++;
					sss = "";
				}
				if(b4[i] == ',')
				{
					ssss.pop_back();
					layer1_output[3][m] = stof(ssss);
					m++;
					ssss = "";
				}
				
				if(b5[i] == ',' )
				{
					s1.pop_back();
					layer1_output[4][r] = stof(s1); 
					r++;
					s1 = "";
				}
				if(b6[i] == ',')
				{
					ss1.pop_back();
					layer1_output[5][o] = stof(ss1);
					o++;
					ss1 = "";
				}
				if(b7[i] == ',' )
				{
					sss1.pop_back();
					layer1_output[6][d] = stof(sss1);
					d++;
					sss1 = "";
				}
				if(b8[i] == ',')
				{
					ssss1.pop_back();
					layer1_output[7][q] = stof(ssss1);
					q++;
					ssss1 = "";
				}
				i++;
			}
			
			cout << "Hidden Layer 2 Input :: \n"; 
			for(int i = 0; i < neurons; i++) {
				for(int j = 0; j < neurons; j++) 
					layer2_input[i] += layer1_output[j][i];
				cout << layer2_input[i] << " | "; 
			}
			cout << endl << endl;
			
			
			pthread_t pid2[neurons];
			pthread_attr_t t2[neurons];
	   		
	   		Argument arg11(layer2_input[0], "pipe11", 0, layer3_weight);	
			pthread_attr_init(&t2[0]);
			pthread_attr_setdetachstate(&t2[0], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid2[0], &t2[0], layer_thread, &arg11);
			
			Argument arg12(layer2_input[1], "pipe12", 1, layer3_weight);	
			pthread_attr_init(&t2[1]);
			pthread_attr_setdetachstate(&t2[1], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid2[1], &t2[1], layer_thread, &arg12);
			
			Argument arg13(layer2_input[2], "pipe13", 2, layer3_weight);	
			pthread_attr_init(&t2[2]);
			pthread_attr_setdetachstate(&t2[2], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid2[2], &t2[2], layer_thread, &arg13);
			
			Argument arg14(layer2_input[3], "pipe14", 3, layer3_weight);	
			pthread_attr_init(&t2[3]);
			pthread_attr_setdetachstate(&t2[3], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid2[3], &t2[3], layer_thread, &arg14);
			
			Argument arg15(layer2_input[4], "pipe15", 4, layer3_weight);	
			pthread_attr_init(&t2[4]);
			pthread_attr_setdetachstate(&t2[4], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid2[4], &t2[4], layer_thread, &arg15);
			
			Argument arg16(layer2_input[5], "pipe16", 5, layer3_weight);	
			pthread_attr_init(&t2[5]);
			pthread_attr_setdetachstate(&t2[5], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid2[5], &t2[5], layer_thread, &arg16);
			
			Argument arg17(layer2_input[6], "pipe17", 6, layer3_weight);	
			pthread_attr_init(&t2[6]);
			pthread_attr_setdetachstate(&t2[6], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid2[6], &t2[6], layer_thread, &arg17);
			
			Argument arg18(layer2_input[7], "pipe18", 7, layer3_weight);	
			pthread_attr_init(&t2[7]);
			pthread_attr_setdetachstate(&t2[7], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid2[7], &t2[7], layer_thread, &arg18);
			//exit(0);
		}
		
		
		
			sleep(2);   
		//  ############################# HIDDEN LAYER 3 ###############################
		if(p[3] == 0)	
		{
			cout << "\n\tHidden Layer 2 Output =>  \n";
			char b1[100] = {'\0'}, b2[100] = {'\0'}, b3[100] = {'\0'}, b4[100] = {'\0'},
				 b5[100] = {'\0'}, b6[100] = {'\0'}, b7[100] = {'\0'}, b8[100] = {'\0'};
			
			int t = open("pipe11", O_RDONLY);
			read(t, b1, sizeof(b1));
			cout << b1;
			close(t);
			
			int u = open("pipe12", O_RDONLY);
			read(u, b2, sizeof(b2));
			cout << b2;
			close(u);
			
			int v = open("pipe13", O_RDONLY);
			read(v, b3, sizeof(b3));
			cout << b3;
			close(v);
			
			int w = open("pipe14", O_RDONLY);
			read(w, b4, sizeof(b4));
			cout << b4 ;
			close(w);
			
			int x = open("pipe15", O_RDONLY);
			read(x, b5, sizeof(b5));
			cout << b5;
			close(x);
			
			int y = open("pipe16", O_RDONLY);
			read(y, b6, sizeof(b6));
			cout << b6;
			close(y);
			
			int z = open("pipe17", O_RDONLY);
			read(z, b7, sizeof(b7));
			cout << b7;
			close(z);
			
			int h = open("pipe18", O_RDONLY);
			read(h, b8, sizeof(b8));
			cout << b8 << endl;
			close(h);
			
			string s = "", ss = "", sss = "", ssss = "";
			string s1 = "", ss1 = "", sss1 = "", ssss1 = "";
			int i = 0, j = 0, k = 0, l = 0, m = 0, r = 0, o = 0, d = 0, q = 0;
			
			while(j != neurons || k != neurons || l != neurons || m != neurons ||
				  r != neurons || o != neurons || d != neurons || q != neurons )
			{	 
				s += b1[i];		ss += b2[i];	sss += b3[i];	ssss += b4[i];
				s1+= b5[i];		ss1+= b6[i];	sss1+= b7[i];	ssss1+= b8[i];
				if(b1[i] == ',' )
				{
					s.pop_back();
					layer2_output[0][j] = stof(s);
					j++;
					s = "";
				}
				if(b2[i] == ',')
				{
					ss.pop_back();
					layer2_output[1][k] = stof(ss);
					k++;
					ss = "";
				}
				if(b3[i] == ',' )
				{
					sss.pop_back();
					layer2_output[2][l] = stof(sss);
					l++;
					sss = "";
				}
				if(b4[i] == ',')
				{
					ssss.pop_back();
					layer2_output[3][m] = stof(ssss);
					m++;
					ssss = "";
				}
				if(b5[i] == ',' )
				{
					s1.pop_back();
					layer2_output[4][r] = stof(s1); 
					r++;
					s1 = "";
				}
				if(b6[i] == ',')
				{
					ss1.pop_back();
					layer2_output[5][o] = stof(ss1);
					o++;
					ss1 = "";
				}
				if(b7[i] == ',' )
				{
					sss1.pop_back();
					layer2_output[6][d] = stof(sss1);
					d++;
					sss1 = "";
				}
				if(b8[i] == ',')
				{
					ssss1.pop_back();
					layer2_output[7][q] = stof(ssss1);
					q++;
					ssss1 = "";
				}
				i++;
			}
			
					
			cout << "Hidden Layer 3 Input :: \n"; 
			for(int i = 0; i < neurons; i++) {
				for(int j = 0; j < neurons; j++) 
					layer3_input[i] += layer2_output[j][i];
				cout << layer3_input[i] << " | "; 
			}
			cout << endl << endl;
			
			pthread_t pid3[neurons];
			pthread_attr_t t3[neurons];
	   		
	   		Argument arg19(layer3_input[0], "pipe19", 0, layer4_weight);	
			pthread_attr_init(&t3[0]);
			pthread_attr_setdetachstate(&t3[0], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid3[0], &t3[0], layer_thread, &arg19);
			
			Argument arg20(layer3_input[1], "pipe20", 1, layer4_weight);	
			pthread_attr_init(&t3[1]);
			pthread_attr_setdetachstate(&t3[1], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid3[1], &t3[1], layer_thread, &arg20);
			
			Argument arg21(layer3_input[2], "pipe21", 2, layer4_weight);	
			pthread_attr_init(&t3[2]);
			pthread_attr_setdetachstate(&t3[2], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid3[2], &t3[2], layer_thread, &arg21);
			
			Argument arg22(layer3_input[3], "pipe22", 3, layer4_weight);	
			pthread_attr_init(&t3[3]);
			pthread_attr_setdetachstate(&t3[3], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid3[3], &t3[3], layer_thread, &arg22);
			
			Argument arg23(layer3_input[4], "pipe23", 4, layer4_weight);	
			pthread_attr_init(&t3[4]);
			pthread_attr_setdetachstate(&t3[4], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid3[4], &t3[4], layer_thread, &arg23);
			
			Argument arg24(layer3_input[5], "pipe24", 5, layer4_weight);	
			pthread_attr_init(&t3[5]);
			pthread_attr_setdetachstate(&t3[5], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid3[5], &t3[5], layer_thread, &arg24);
			
			Argument arg25(layer3_input[6], "pipe25", 6, layer4_weight);	
			pthread_attr_init(&t3[6]);
			pthread_attr_setdetachstate(&t3[6], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid3[6], &t3[6], layer_thread, &arg25);
			
			Argument arg26(layer3_input[7], "pipe26", 7, layer4_weight);	
			pthread_attr_init(&t3[7]);
			pthread_attr_setdetachstate(&t3[7], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid3[7], &t3[7], layer_thread, &arg26);
			//exit(0);
		}
		
		
		
		
			sleep(2);   
		//  ############################# HIDDEN LAYER 4 ###############################
		if(p[4] == 0)	
		{
			cout << "\n\tHidden Layer 3 Output =>  \n";
			char b1[100] = {'\0'}, b2[100] = {'\0'}, b3[100] = {'\0'}, b4[100] = {'\0'},
				 b5[100] = {'\0'}, b6[100] = {'\0'}, b7[100] = {'\0'}, b8[100] = {'\0'};
			
			int t = open("pipe19", O_RDONLY);
			read(t, b1, sizeof(b1));
			cout << b1;
			close(t);
			
			int u = open("pipe20", O_RDONLY);
			read(u, b2, sizeof(b2));
			cout << b2;
			close(u);
			
			int v = open("pipe21", O_RDONLY);
			read(v, b3, sizeof(b3));
			cout << b3;
			close(v);
			
			int w = open("pipe22", O_RDONLY);
			read(w, b4, sizeof(b4));
			cout << b4 ;
			close(w);
			
			int x = open("pipe23", O_RDONLY);
			read(x, b5, sizeof(b5));
			cout << b5;
			close(x);
			
			int y = open("pipe24", O_RDONLY);
			read(y, b6, sizeof(b6));
			cout << b6;
			close(y);
			
			int z = open("pipe25", O_RDONLY);
			read(z, b7, sizeof(b7));
			cout << b7;
			close(z);
			
			int h = open("pipe26", O_RDONLY);
			read(h, b8, sizeof(b8));
			cout << b8 << endl;
			close(h);
			
			string s = "", ss = "", sss = "", ssss = "";
			string s1 = "", ss1 = "", sss1 = "", ssss1 = "";
			int i = 0, j = 0, k = 0, l = 0, m = 0, r = 0, o = 0, d = 0, q = 0;
			
			while(j != neurons || k != neurons || l != neurons || m != neurons ||
				  r != neurons || o != neurons || d != neurons || q != neurons )
			{	 
				s += b1[i];		ss += b2[i];	sss += b3[i];	ssss += b4[i];
				s1+= b5[i];		ss1+= b6[i];	sss1+= b7[i];	ssss1+= b8[i];
				if(b1[i] == ',' )
				{
					s.pop_back();
					layer3_output[0][j] = stof(s);
					j++;
					s = "";
				}
				if(b2[i] == ',')
				{
					ss.pop_back();
					layer3_output[1][k] = stof(ss); 
					k++;
					ss = "";
				}
				if(b3[i] == ',' )
				{
					sss.pop_back();
					layer3_output[2][l] = stof(sss);
					l++;
					sss = "";
				}
				if(b4[i] == ',')
				{
					ssss.pop_back();
					layer3_output[3][m] = stof(ssss);
					m++;
					ssss = "";
				}
				if(b5[i] == ',' )
				{
					s1.pop_back();
					layer3_output[4][r] = stof(s1); 
					r++;
					s1 = "";
				}
				if(b6[i] == ',')
				{
					ss1.pop_back();
					layer3_output[5][o] = stof(ss1);
					o++;
					ss1 = "";
				}
				if(b7[i] == ',' )
				{
					sss1.pop_back();
					layer3_output[6][d] = stof(sss1);
					d++;
					sss1 = "";
				}
				if(b8[i] == ',')
				{
					ssss1.pop_back();
					layer3_output[7][q] = stof(ssss1);
					q++;
					ssss1 = "";
				}
				i++;
			}
			
			
			cout << "Hidden Layer 4 Input :: \n"; 
			for(int i = 0; i < neurons; i++) {
				for(int j = 0; j < neurons; j++) 
					layer4_input[i] += layer3_output[j][i];
				cout << layer4_input[i] << " | "; 
			}
			cout << endl << endl;
			
			pthread_t pid4[neurons];
			pthread_attr_t t4[neurons];
	   		
	   		Argument arg27(layer4_input[0], "pipe27", 0, layer5_weight);	
			pthread_attr_init(&t4[0]);
			pthread_attr_setdetachstate(&t4[0], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid4[0], &t4[0], layer_thread, &arg27);
			
			Argument arg28(layer4_input[1], "pipe28", 1, layer5_weight);	
			pthread_attr_init(&t4[1]);
			pthread_attr_setdetachstate(&t4[1], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid4[1], &t4[1], layer_thread, &arg28);
			
			Argument arg29(layer4_input[2], "pipe29", 2, layer5_weight);	
			pthread_attr_init(&t4[2]);
			pthread_attr_setdetachstate(&t4[2], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid4[2], &t4[2], layer_thread, &arg29);
			
			Argument arg30(layer4_input[3], "pipe30", 3, layer5_weight);	
			pthread_attr_init(&t4[3]);
			pthread_attr_setdetachstate(&t4[3], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid4[3], &t4[3], layer_thread, &arg30);
			
			Argument arg31(layer4_input[4], "pipe31", 4, layer5_weight);	
			pthread_attr_init(&t4[4]);
			pthread_attr_setdetachstate(&t4[4], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid4[4], &t4[4], layer_thread, &arg31);
			
			Argument arg32(layer4_input[5], "pipe32", 5, layer5_weight);	
			pthread_attr_init(&t4[5]);
			pthread_attr_setdetachstate(&t4[5], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid4[5], &t4[5], layer_thread, &arg32);
			
			Argument arg33(layer4_input[6], "pipe33", 6, layer5_weight);	
			pthread_attr_init(&t4[6]);
			pthread_attr_setdetachstate(&t4[6], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid4[6], &t4[6], layer_thread, &arg33);
			
			Argument arg34(layer4_input[7], "pipe34", 7, layer5_weight);	
			pthread_attr_init(&t4[7]);
			pthread_attr_setdetachstate(&t4[7], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid4[7], &t4[7], layer_thread, &arg34);
			//exit(0);		
		}
		
			sleep(2);   
		//  ############################# HIDDEN LAYER 5 ###############################
		if(p[5] == 0)	
		{
			cout << "\n\tHidden Layer 4 Output =>  \n";
			char b1[100] = {'\0'}, b2[100] = {'\0'}, b3[100] = {'\0'}, b4[100] = {'\0'},
				 b5[100] = {'\0'}, b6[100] = {'\0'}, b7[100] = {'\0'}, b8[100] = {'\0'};
			
			int t = open("pipe27", O_RDONLY);
			read(t, b1, sizeof(b1));
			cout << b1;
			close(t);
			
			int u = open("pipe28", O_RDONLY);
			read(u, b2, sizeof(b2));
			cout << b2;
			close(u);
			
			int v = open("pipe29", O_RDONLY);
			read(v, b3, sizeof(b3));
			cout << b3;
			close(v);
			
			int w = open("pipe30", O_RDONLY);
			read(w, b4, sizeof(b4));
			cout << b4 ;
			close(w);
			
			int x = open("pipe31", O_RDONLY);
			read(x, b5, sizeof(b5));
			cout << b5;
			close(x);
			
			int y = open("pipe32", O_RDONLY);
			read(y, b6, sizeof(b6));
			cout << b6;
			close(y);
			
			int z = open("pipe33", O_RDONLY);
			read(z, b7, sizeof(b7));
			cout << b7;
			close(z);
			
			int h = open("pipe34", O_RDONLY);
			read(h, b8, sizeof(b8));
			cout << b8 << endl;
			close(h);
			
			string s = "", ss = "", sss = "", ssss = "";
			string s1 = "", ss1 = "", sss1 = "", ssss1 = "";
			int i = 0, j = 0, k = 0, l = 0, m = 0, r = 0, o = 0, d = 0, q = 0;
			
			while(j != neurons || k != neurons || l != neurons || m != neurons ||
				  r != neurons || o != neurons || d != neurons || q != neurons )
			{	 
				s += b1[i];		ss += b2[i];	sss += b3[i];	ssss += b4[i];
				s1+= b5[i];		ss1+= b6[i];	sss1+= b7[i];	ssss1+= b8[i];
				if(b1[i] == ',' )
				{
					s.pop_back();
					layer4_output[0][j] = stof(s);
					j++;
					s = "";
				}
				if(b2[i] == ',')
				{
					ss.pop_back();
					layer4_output[1][k] = stof(ss);
					k++;
					ss = "";
				}
				if(b3[i] == ',' )
				{
					sss.pop_back();
					layer4_output[2][l] = stof(sss); 
					l++;
					sss = "";
				}
				if(b4[i] == ',')
				{
					ssss.pop_back();
					layer4_output[3][m] = stof(ssss);
					m++;
					ssss = "";
				}
				if(b5[i] == ',' )
				{
					s1.pop_back();
					layer4_output[4][r] = stof(s1); 
					r++;
					s1 = "";
				}
				if(b6[i] == ',')
				{
					ss1.pop_back();
					layer4_output[5][o] = stof(ss1);
					o++;
					ss1 = "";
				}
				if(b7[i] == ',' )
				{
					sss1.pop_back();
					layer4_output[6][d] = stof(sss1);
					d++;
					sss1 = "";
				}
				if(b8[i] == ',')
				{
					ssss1.pop_back();
					layer4_output[7][q] = stof(ssss1);
					q++;
					ssss1 = "";
				}
				i++;
			}
			
			cout << "Hidden Layer 5 Input :: \n"; 
			for(int i = 0; i < neurons; i++) {
				for(int j = 0; j < neurons; j++) 
					layer5_input[i] += layer4_output[j][i];
				cout << layer5_input[i] << " | "; 
			}
			cout << endl << endl;
			
			pthread_t pid5[neurons];
			pthread_attr_t t5[neurons];
	   		
	   		last_arg last_arg1(layer5_input[0], "pipe35", output_layer_weight[0]);	
			pthread_attr_init(&t5[0]);
			pthread_attr_setdetachstate(&t5[0], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid5[0], &t5[0], last_layer_thread, &last_arg1);
			
			last_arg last_arg2(layer5_input[1], "pipe36", output_layer_weight[1]);	
			pthread_attr_init(&t5[1]);
			pthread_attr_setdetachstate(&t5[1], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid5[1], &t5[1], last_layer_thread, &last_arg2);
			
			last_arg last_arg3(layer5_input[2], "pipe37", output_layer_weight[2]);	
			pthread_attr_init(&t5[2]);
			pthread_attr_setdetachstate(&t5[2], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid5[2], &t5[2], last_layer_thread, &last_arg3);
			
			last_arg last_arg4(layer5_input[3], "pipe38", output_layer_weight[3]);	
			pthread_attr_init(&t5[3]);
			pthread_attr_setdetachstate(&t5[3], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid5[3], &t5[3], last_layer_thread, &last_arg4);
			
			last_arg last_arg5(layer5_input[4], "pipe39", output_layer_weight[4]);	
			pthread_attr_init(&t5[4]);
			pthread_attr_setdetachstate(&t5[4], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid5[4], &t5[4], last_layer_thread, &last_arg5);
			
			last_arg last_arg6(layer5_input[5], "pipe40", output_layer_weight[5]);	
			pthread_attr_init(&t5[5]);
			pthread_attr_setdetachstate(&t5[5], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid5[5], &t5[5], last_layer_thread, &last_arg6);
			
			last_arg last_arg7(layer5_input[6], "pipe41", output_layer_weight[6]);	
			pthread_attr_init(&t5[6]);
			pthread_attr_setdetachstate(&t5[6], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid5[6], &t5[6], last_layer_thread, &last_arg7);
			
			last_arg last_arg8(layer5_input[7], "pipe42", output_layer_weight[7]);	
			pthread_attr_init(&t5[7]);
			pthread_attr_setdetachstate(&t5[7], PTHREAD_CREATE_DETACHED);
			pthread_create(&pid5[7], &t5[7], last_layer_thread, &last_arg8);
			//exit(0);	
		}
		
		
			sleep(2);
		//  ############################# OUTPUT LAYER ###############################
		if(p[6] == 0)	
		{
			cout << "\n\tHidden Layer 5 Output =>  \n";
			char b1[100] = {'\0'}, b2[100] = {'\0'}, b3[100] = {'\0'}, b4[100] = {'\0'},
				 b5[100] = {'\0'}, b6[100] = {'\0'}, b7[100] = {'\0'}, b8[100] = {'\0'};
			
			int t = open("pipe35", O_RDONLY);
			read(t, b1, sizeof(b1));
			cout << b1;
			close(t);
			
			int u = open("pipe36", O_RDONLY);
			read(u, b2, sizeof(b2));
			cout << b2;
			close(u);
			
			int v = open("pipe37", O_RDONLY);
			read(v, b3, sizeof(b3));
			cout << b3;
			close(v);
			
			int w = open("pipe38", O_RDONLY);
			read(w, b4, sizeof(b4));
			cout << b4 ;
			close(w);
			
			int x = open("pipe39", O_RDONLY);
			read(x, b5, sizeof(b5));
			cout << b5;
			close(x);
			
			int y = open("pipe40", O_RDONLY);
			read(y, b6, sizeof(b6));
			cout << b6;
			close(y);
			
			int z = open("pipe41", O_RDONLY);
			read(z, b7, sizeof(b7));
			cout << b7;
			close(z);
			
			int h = open("pipe42", O_RDONLY);
			read(h, b8, sizeof(b8));
			cout << b8 << endl;
			close(h);
			
			string s = "", ss = "", sss = "", ssss = "";
			string s1 = "", ss1 = "", sss1 = "", ssss1 = "";
			int i = 0, j = 0, k = 0, l = 0, m = 0, r = 0, o = 0, d = 0, q = 0;
			
			while(j != 1 || k != 1 || l != 1 || m != 1 || r != 1 || o != 1 || d != 1 || q != 1 )
			{	 
				s += b1[i];		ss += b2[i];	sss += b3[i];	ssss += b4[i];
				s1+= b5[i];		ss1+= b6[i];	sss1+= b7[i];	ssss1+= b8[i];
				
				if(b1[i] == ',' )
				{
					s.pop_back();
					layer5_output[0][j] = stof(s);
					j++;
					s = "";
				}
				if(b2[i] == ',')
				{
					ss.pop_back();
					layer5_output[1][k] = stof(ss);
					k++;
					ss = "";
				}
				if(b3[i] == ',' )
				{
					sss.pop_back();
					layer5_output[2][l] = stof(sss);
					l++;
					sss = "";
				}
				if(b4[i] == ',')
				{
					ssss.pop_back();
					layer5_output[3][m] = stof(ssss);
					m++;
					ssss = "";
				}
				if(b5[i] == ',' )
				{
					s1.pop_back();
					layer5_output[4][r] = stof(s1); 
					r++;
					s1 = "";
				}
				if(b6[i] == ',')
				{
					ss1.pop_back();
					layer5_output[5][o] = stof(ss1);
					o++;
					ss1 = "";
				}
				if(b7[i] == ',' )
				{
					sss1.pop_back();
					layer5_output[6][d] = stof(sss1);
					d++;
					sss1 = "";
				}
				if(b8[i] == ',')
				{
					ssss1.pop_back();
					layer5_output[7][q] = stof(ssss1);
					q++;
					ssss1 = "";
				}
				i++;
			}
			
			
			for(int i = 0; i < neurons; i++) 
					output += layer5_output[i][0];
			cout << "Final Output is = " << output << endl;
			
			pthread_t pid6;
			pthread_attr_t t6;
	   		
	   		output_arg arg(output, "pipe43");	
			pthread_attr_init(&t6);
			pthread_attr_setdetachstate(&t6, PTHREAD_CREATE_DETACHED);
			pthread_create(&pid6, &t6, output_layer_thread, &arg);
			//exit(0);
		}
		
		
				sleep(2);
		//  ############################# MAIN LAYER ###############################
		if(p[n-1] > 0)		// parent thread reading output pipe and regenerating input_vals
		{
			cout << "\nOutput Layer pipe read =>  ";
			char b1[100] = {'\0'};
			
			int t = open("pipe43", O_RDONLY);
			read(t, b1, sizeof(b1));
			close(t);
			string s = b1;
			s.pop_back();
			cout << s << endl;
			output_read = stof(s);
			
			input_val[0] = ((output_read * output_read) + output_read + 1) / 2;
			input_val[1] = ((output_read * output_read) - output_read) / 2;
			cout << "Regenerating input values --> " << input_val[0] << "  " << input_val[1];
			cout << endl << endl;
			
		}
		
		for(int i = 0; i < n; i++) 
		{
			if(p[i] == 0)
				exit(0);
		}
		//cout << input;
		var++;
	}
		//goto jump_point;
	//}
	//while(var == 1);
	
	pthread_exit(NULL);
}







