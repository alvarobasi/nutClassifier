# nutClassifier #

A Computer Vision VS2017 project developed in C++, OpenCV and Qt. It consists of a nut classifier based on a SVM (Support Vector Machine) Machine Learning algorithm trained with several nut images.

# Phases #
The phases carried out throughout the project where the following:
- Image processing, thresholding and segmentation of the different nuts.
- Features exctraction process. 3 main features are being obtained: Color (HSV color space), texture (entropy computation) and size (contour area from each nut).
- A feature space reduction process is being held by removing residual data and extracting those features that are more relevant for each type of nut.
- SVM training using the resulting normalized features.

# The GUI #
![alt text](https://github.com/alvarobasi/nutClassifier/blob/master/classifier_image.png)

The program consists of a main window in which we find two widgets where we can see the result of the thresholding process in the left side, and the result of the classification in the right side, so that it is possible to check the quality of the segmentation with certain light and classification conditions. Three buttons have been placed under these views: the first one to classify the nuts located within a selected image stored in the local computer, the second one to start a video capture to test the classification performance in real-time, and the last one to perform a training of the SVM classifier using the set of images located in the program's main directory. This folder can be filled with more nut images in order to improve the classification performance. Once the training process is finished, a new window will prompted giving information about the success percentage during the test process and the confusion matrix corresponding to this process.

# Demo #
In this section a video demo of the project can be found.
[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/LyU9x2qVVVE/599.jpg)](https://youtu.be/LyU9x2qVVVE)
