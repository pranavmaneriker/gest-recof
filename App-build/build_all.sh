#!/bin/bash
echo "Compiling training programs\n"
g++ svm_train.cpp `pkg-config opencv --cflags --libs` -o train
g++ 2_col_train.cpp `pkg-config opencv --cflags --libs` -o train2
echo "Done compiling. Now training the SVM\n"
./train
./train2
echo "Training complete. Now compiling the classifier\n"
g++ svm_class.cpp `pkg-config opencv --cflags --libs` -o class
g++ 2_col_class.cpp `pkg-config opencv --cflags --libs` -o class2
echo "Clasifiers compiled. Now the main program will be compiled\n"
g++ Main.cpp `pkg-config opencv --cflags --libs` -o main
g++ Main2.cpp `pkg-config opencv --cflags --libs` -o main2
g++ Run.cpp `pkg-config opencv --cflags --libs` -o run
echo "Completed. To run, type ./run and end with ctrl+c\n"
