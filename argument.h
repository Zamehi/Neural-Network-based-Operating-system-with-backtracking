
int neuron = 8;

struct Argument
{
	float input;
	const char* p;
	int index;
	float *weight;
	
	Argument(float i, const char* p, int index, float w[][8])
	{
		this->input = i;
		this->p = p;
		this->index = index;
		
		weight = new float[neuron];
				
		for(int j = 0; j < neuron; j++)
			weight[j] = w[index][j];
			
	}
	
};

struct last_arg
{
	float input;
	const char* p;
	float weight;
	
	last_arg(float i, const char* p, float w)
	{
		this->input = i;
		this->p = p;
		weight = w;
	}
};



struct output_arg
{
	float input;
	const char* p;
	
	output_arg(float i, const char* p)
	{
		this->input = i;
		this->p = p;
	}
};





