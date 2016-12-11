//
// Created by Szymek on 11.11.2016.
//

#ifndef GENETICALGORITHM_LOADINGDATASETFUNCTIONS_H
#define GENETICALGORITHM_LOADINGDATASETFUNCTIONS_H

#include "Dataset.h"
#include <fstream>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

//Dataset<double, bool> LoadingDatasetFromFile(char *path);

void getLabel(const char *memblock, std::vector<bool> &Labels, int loopControl);

void getFirstFeature(const char *memblock, const int FEATUREBYTES, int loopControl, std::vector<double> &Feature,
                     char *featureBuffer, double &feature);

void getSecondFeature(const char *memblock, const int FEATUREBYTES, int loopControl, std::vector<double> &Feature,
                      char *featureBuffer, double &feature);

void getThirdFeature(const char *memblock, const int FEATUREBYTES, int loopControl, std::vector<double> &Feature,
                     char *featureBuffer, double &feature);

void getDataDimension(int &dimensionOfData, ifstream &file, streampos &size, char *&memblock);

void LoadDataset(const char *path, vector<vector<double>> &features, vector<vector<double>> &labels, int n_inputs, int n_outputs);

#endif //GENETICALGORITHM_LOADINGDATASETFUNCTIONS_H
