# nutClassifier #

A Computer Vision VS2017 project developed in C++, OpenCV and Qt. It consists of a nut classifier based on a SVM (Support Vector Machine) Machine Learning algorithm trained with several nut images.

# Phases #
The phases carried out throughout the project where the following:
- Image processing, thresholding and segmentation of the different nuts.
- Features exctraction process. 3 main features are being obtained: Color (HSV color space), texture (entropy computation) and size (contour area from each nut).
- A feature space reduction process is being held by removing residual data and extracting those features that are more relevant for each type of nut.
- SVM training using the resulting normalized features.

# The GUI #
