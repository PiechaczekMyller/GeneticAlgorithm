//
// Created by Szymek on 11.11.2016.
//
#include <exception>
#include "LoadingDatasetFunctions.h"


//Dataset<double, bool> LoadingDatasetFromFile(char *path){
//	streampos size;
//	char *memblock;
//	int dimensionOfData;
//	const int OFFSET = 4;
//	const int LABELBYTES = 1;
//	const int FEATUREBYTES = 8;
//	const int BYTESBEETWENLINES = 25;
//	static_assert(sizeof(double) == 8,"bo tak");
//	static_assert(sizeof(int) == 4,"bo tak");
//	static_assert(sizeof(bool) == 1,"bo tak");
//
//	ifstream file(path, ios::in | ios::binary | ios::ate);
//	if(file.is_open()){
//		getDataDimension(dimensionOfData, file, size, memblock);
//		vector<bool> labels;
//		vector<vector<double>> features;
//		for(int loopControl = OFFSET; loopControl < size; loopControl = loopControl + BYTESBEETWENLINES){
//			vector<double> Feature;
//			getLabel(memblock, labels, loopControl);
//			char featureBuffer[8];
//			double feature;
//			getFirstFeature(memblock, FEATUREBYTES, loopControl, Feature, featureBuffer, feature);
//			getSecondFeature(memblock, FEATUREBYTES, loopControl, Feature, featureBuffer, feature);
//			getThirdFeature(memblock, FEATUREBYTES, loopControl, Feature, featureBuffer, feature);
//			features.push_back(Feature);
//		}
//		file.close();
//		delete[] memblock;
//		Dataset<double, bool> dataset(features, labels);
//		cout << "Dataset loaded" << endl;
//		return dataset;
//	}
//}

void getDataDimension(int &dimensionOfData, ifstream &file, streampos &size, char *&memblock){
	size = file.tellg();
	memblock = new char[size];
	file.seekg(0, ios_base::beg);
	file.read(memblock, size);
	char dimensionBuffer[] = { memblock[0], memblock[1], memblock[2], memblock[3] };
	memcpy(&dimensionOfData, dimensionBuffer, sizeof(dimensionOfData));
}

void getThirdFeature(const char *memblock, const int FEATUREBYTES, int loopControl, vector<double> &Feature,
                     char *featureBuffer, double &feature){
	for(int loopControl2 = 1; loopControl2 <= FEATUREBYTES; loopControl2++){
		featureBuffer[loopControl2 - 1] = memblock[loopControl + loopControl2 + 2 * FEATUREBYTES];
	}
	memcpy(&feature, featureBuffer, sizeof(feature));
	Feature.push_back(feature);
}

void getSecondFeature(const char *memblock, const int FEATUREBYTES, int loopControl, vector<double> &Feature,
                      char *featureBuffer, double &feature){
	for(int loopControl2 = 1; loopControl2 <= FEATUREBYTES; loopControl2++){
		featureBuffer[loopControl2 - 1] = memblock[loopControl + loopControl2 + FEATUREBYTES];
	}
	memcpy(&feature, featureBuffer, sizeof(feature));
	Feature.push_back(feature);
}

void getFirstFeature(const char *memblock, const int FEATUREBYTES, int loopControl, vector<double> &Feature,
                     char *featureBuffer, double &feature){
	for(int loopControl2 = 1; loopControl2 <= FEATUREBYTES; loopControl2++){
		featureBuffer[loopControl2 - 1] = memblock[loopControl + loopControl2];
	}
	memcpy(&feature, featureBuffer, sizeof(feature));
	Feature.push_back(feature);
}

void getLabel(const char *memblock, vector<bool, allocator<bool>> &Labels, int loopControl){
	char labelBuffer[] = { memblock[loopControl] };
	bool label;
	memcpy(&label, labelBuffer, sizeof(label));
	Labels.push_back(label);
}

void LoadDataset(const char *path,vector<vector<double>> &features, vector<vector<double>> &labels, int n_inputs, int n_outputs)
{
	ifstream file;
	string line;
	file.open(path, ios::in);
	int position = 0;
	if (file.is_open())
	{
        cout << "Loading set..." << endl;
		while(!file.eof())
		{
			getline(file, line);
			if (line != "")
			{
				vector<double> feature;
				for (position  = 0; position < n_inputs; position++)
				{
					if (line[position] == '1')
						feature.push_back(1.0);
					else if (line[position] == '0')
						feature.push_back(0.0);
				}
				features.push_back(feature);
				vector<double> label;
				for (position; position < n_outputs + n_inputs; position++)
				{
					if (line[position] == '1')
						label.push_back(1.0);
					else if (line[position] == '0')
						label.push_back(0.0);
				}
				labels.push_back(label);
			}
			else
				break;
		}
	}
    cout << "Set loaded!" << endl;
	file.close();
}