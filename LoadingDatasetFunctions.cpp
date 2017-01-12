//
// Created by Szymek on 11.11.2016.
//
#include <exception>
#include "LoadingDatasetFunctions.h"


Dataset<double, double> LoadingDatasetFromFile(const char *path) {
    streampos size;
    char *memblock;
    int dimensionOfData;
    const int OFFSET = 4;
    const int LABELBYTES = 1;
    const int FEATUREBYTES = 8;
    const int BYTESBEETWENLINES = 25;
    static_assert(sizeof(double) == 8, "bo tak");
    static_assert(sizeof(int) == 4, "bo tak");
    static_assert(sizeof(bool) == 1, "bo tak");

    ifstream file(path, ios::in | ios::binary | ios::ate);
    if (file.is_open()) {
        getDataDimension(dimensionOfData, file, size, memblock);
        vector<vector<double>> features;
        vector<vector<double>> labels;
        for (int loopControl = OFFSET; loopControl < size; loopControl = loopControl + BYTESBEETWENLINES) {
            vector<double> Feature;
            vector<double> label;
            getLabel(memblock, label, loopControl);
            labels.push_back(label);
            char featureBuffer[8];
            double feature;
            getFirstFeature(memblock, FEATUREBYTES, loopControl, Feature, featureBuffer, feature);
            getSecondFeature(memblock, FEATUREBYTES, loopControl, Feature, featureBuffer, feature);
            getThirdFeature(memblock, FEATUREBYTES, loopControl, Feature, featureBuffer, feature);
            features.push_back(Feature);
        }
        file.close();
        delete[] memblock;
        Dataset<double, double> dataset(features, labels);
        cout << "Dataset loaded" << endl;
        return dataset;
    }
}


void getDataDimension(int &dimensionOfData, ifstream &file, streampos &size, char *&memblock) {
    size = file.tellg();
    memblock = new char[size];
    file.seekg(0, ios_base::beg);
    file.read(memblock, size);
    char dimensionBuffer[] = {memblock[0], memblock[1], memblock[2], memblock[3]};
    memcpy(&dimensionOfData, dimensionBuffer, sizeof(dimensionOfData));
}

void getThirdFeature(const char *memblock, const int FEATUREBYTES, int loopControl, vector<double> &Feature,
                     char *featureBuffer, double &feature) {
    for (int loopControl2 = 1; loopControl2 <= FEATUREBYTES; loopControl2++) {
        featureBuffer[loopControl2 - 1] = memblock[loopControl + loopControl2 + 2 * FEATUREBYTES];
    }
    memcpy(&feature, featureBuffer, sizeof(feature));
    Feature.push_back(feature);
}

void getSecondFeature(const char *memblock, const int FEATUREBYTES, int loopControl, vector<double> &Feature,
                      char *featureBuffer, double &feature) {
    for (int loopControl2 = 1; loopControl2 <= FEATUREBYTES; loopControl2++) {
        featureBuffer[loopControl2 - 1] = memblock[loopControl + loopControl2 + FEATUREBYTES];
    }
    memcpy(&feature, featureBuffer, sizeof(feature));
    Feature.push_back(feature);
}

void getFirstFeature(const char *memblock, const int FEATUREBYTES, int loopControl, vector<double> &Feature,
                     char *featureBuffer, double &feature) {
    for (int loopControl2 = 1; loopControl2 <= FEATUREBYTES; loopControl2++) {
        featureBuffer[loopControl2 - 1] = memblock[loopControl + loopControl2];
    }
    memcpy(&feature, featureBuffer, sizeof(feature));
    Feature.push_back(feature);
}

void getLabel(const char *memblock, vector<double> &Labels, int loopControl) {
    char labelBuffer[] = {memblock[loopControl]};
    bool label;
    memcpy(&label, labelBuffer, sizeof(label));
    if (label)
        Labels.push_back(double(1.0));
    else
        Labels.push_back(double(0.0));
}

//void LoadDataset(const char *path,vector<vector<double>> &features, vector<vector<double>> &labels, int n_inputs, int n_outputs)
//{
//	ifstream file;
//	string line;
//	file.open(path, ios::in);
//	int position = 0;
//	if (file.is_open())
//	{
//        cout << "Loading set..." << endl;
//		while(!file.eof())
//		{
//			getline(file, line);
//			if (line != "")
//			{
//				vector<double> feature;
//				for (position  = 0; position < n_inputs; position++)
//				{
//					if (line[position] == '1')
//						feature.push_back(1.0);
//					else if (line[position] == '0')
//						feature.push_back(0.0);
//				}
//				features.push_back(feature);
//				vector<double> label;
//				for (position; position < n_outputs + n_inputs; position++)
//				{
//					if (line[position] == '1')
//						label.push_back(1.0);
//					else if (line[position] == '0')
//						label.push_back(0.0);
//				}
//				labels.push_back(label);
//			}
//			else
//				break;
//		}
//	}
//    cout << "Set loaded!" << endl;
//	file.close();
//}

void JoinDatasets(Dataset<double, double> &trainingSet, Dataset<double, double> &testSet, int test_set_index) {
    const int NO_OF_FEATURES = 3;
    const int NO_OF_LABELS = 1;
    vector<vector<double>> trainingSet_features;
    vector<vector<double>> trainingSet_labels;
    vector<vector<double>> testSet_features;
    vector<vector<double>> testSet_labels;
    string training_sets_path;
    string test_set_path;
    test_set_path = "Datasets/subset" + to_string(test_set_index) + ".txt";
    string line;
    ifstream file;
    for (int index = 1; index <= 10; index++) {
        training_sets_path = "Datasets/subset" + to_string(index) + ".txt";
        if (training_sets_path != test_set_path) {
            file.open(training_sets_path);
            if (file.is_open()) {
                while (!file.eof()) {
                    vector<double> features;
                    for (int feature = 0; feature < NO_OF_FEATURES; feature++) {
                        getline(file, line);
                        features.push_back(stod(line));
                    }
                    trainingSet_features.push_back(features);
                    vector<double> labels;
                    for (int label = 0; label < NO_OF_LABELS; label++) {
                        getline(file, line);
                        labels.push_back(stod(line));
                    }
                    trainingSet_labels.push_back(labels);
                }
            } else {
                cout << "could not open file" << endl;
            }
            file.close();
        } else {
            file.open(test_set_path);
            if (file.is_open()) {
                while (!file.eof()) {
                    vector<double> features;
                    for (int feature = 0; feature < NO_OF_FEATURES; feature++) {
                        getline(file, line);
                        features.push_back(stod(line));
                    }
                    testSet_features.push_back(features);
                    vector<double> labels;
                    for (int label = 0; label < NO_OF_LABELS; label++) {
                        getline(file, line);
                        labels.push_back(stod(line));
                    }
                    testSet_labels.push_back(labels);
                }
            } else {
                cout << "could not open file" << endl;
            }
            file.close();
        }
    }
    trainingSet.setVectorOfFeatures(trainingSet_features);
    trainingSet.setVectorOfLabels(trainingSet_labels);
    trainingSet.setVectorOfIndexes();
    testSet.setVectorOfFeatures(testSet_features);
    testSet.setVectorOfLabels(testSet_labels);
    testSet.setVectorOfIndexes();
}

Dataset<double, double> LoadSingleDataset(const char *path) {
    const int NO_OF_FEATURES = 3;
    const int NO_OF_LABELS = 1;
    vector<vector<double>> set_features;
    vector<vector<double>> set_labels;
    string line;
    ifstream file;

    file.open(path);
    if (file.is_open()) {
        while (!file.eof()) {
            vector<double> features;
            for (int feature = 0; feature < NO_OF_FEATURES; feature++) {
                getline(file, line);
                features.push_back(stod(line));
            }
            set_features.push_back(features);
            vector<double> labels;
            for (int label = 0; label < NO_OF_LABELS; label++) {
                getline(file, line);
                labels.push_back(stod(line));
            }
            set_labels.push_back(labels);
        }
    } else {
        cout << "could not open file" << endl;
    }
    file.close();
    Dataset<double,double> set(set_features, set_labels);
    return set;
};








