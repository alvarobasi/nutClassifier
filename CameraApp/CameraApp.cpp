#include "CameraApp.h"

CameraApp::CameraApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//Abrir la cámara y configurarla con algunos parámetros como el enfoque y la anchura y altura de pixeles.
	cap = new cv::VideoCapture(1);
	cap->set(cv::CAP_PROP_FRAME_WIDTH, 1920);
	cap->set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
	cap->set(cv::CAP_PROP_AUTOFOCUS, 0);
	cap->set(cv::CAP_PROP_FOCUS, 25);
	capturing = false;

	connect(ui.video_cap, SIGNAL(toggled(bool)), this, SLOT(startStopCapture(bool)));
	connect(ui.image_cap, SIGNAL(clicked()), this, SLOT(imageCapture()));
	connect(ui.train_but, SIGNAL(clicked()), this, SLOT(neuralNetworkSetting()));

}

CameraApp::~CameraApp() {
	cap->release();
}

void CameraApp::videoCapture() {
	cv::Mat img;
	cap->read(img);

	cv::Mat1f feature_mat;
	std::vector<cv::Rect> rectangles;
	//Introducimos la imagen capturada en la función threshold, la cual devuelve un vector que contiene la información de las ROIs de los diferentes objetos detectados.
	//También nos devuelve la matriz de características obtenidas de cada objeto segmentado, con las muestras (objetos) en cada fila, y sus características extraidas en cada columna.
	rectangles = threshold(img, feature_mat);

	//Obtenemos los datos de máximo y mínimo de cada característica con los que se han normalizado las características utilizadas en el entrenamiento. 
	cv::Mat min_max = FiletoMat("normal_data.txt");

	cv::Rect submat;
	cv::Mat1f auxiliar;

	//´Normalizamos la matriz de características con los valores guardados del último entrenamiento. Modelo de normalización ---> f(x)-min/range
	for (int i = 0; i < feature_mat.cols; i++)
	{
		submat = cv::Rect(i, 0, 1, feature_mat.rows);
		auxiliar = feature_mat(submat);
		cv::subtract(auxiliar, min_max.at<float>(i, 0), auxiliar);
		cv::divide(auxiliar, min_max.at<float>(i, 1) - min_max.at<float>(i, 0), auxiliar);

	}

	//Creamos el clasificador SVM y lo cargamos con la información almacenada del último entrenamiento.
	Ptr<SVM> svm = cv::Algorithm::load<SVM>("svm.yml");

	//Pasamos la información de cada fila al clasificador y mostramos en la imagen el resultado de la predicción realizada + la ROI donde se encuentra cada objeto.
	for (int i = 0; i<feature_mat.rows; i++) {
		std::ostringstream str4;
		int pred = svm->predict(feature_mat.row(i), cv::noArray());
		rectangle(img, rectangles[i].tl(), rectangles[i].br(), CV_RGB(0, 255, 0), 3, 8, 0);
		if (pred == 0)
		{
			str4 << "almendra";
		}
		else if (pred == 1)
		{
			str4 << "avellana";
		}
		else if (pred == 2)
		{
			str4 << "castana";
		}
		else if (pred == 3)
		{
			str4 << "nuez";
		}
		else if (pred == 4)
		{
			str4 << "pistacho";
		}

		putText(img, str4.str(), cv::Point(rectangles[i].tl().x + 5, rectangles[i].tl().y + 30), cv::FONT_HERSHEY_COMPLEX_SMALL, 2.00, CV_RGB(229, 87, 4), 2, CV_AA);
	}

	ui.window3->setVisualicedImage(img);

	if (capturing)
	{
		QTimer::singleShot(10, this, SLOT(videoCapture()));
	}
}

void CameraApp::imageCapture() {

	cv::Mat img;
	//Pausamos el video si es que está activo.
	if (capturing)
	{
		capturing = false;
	}
	//Abrimos un diálogo para elegir una imagen.
	QString file_name = QFileDialog::getOpenFileName(this, tr("Open Image"), "./image_set", tr("Image Files (*.png *.jpg *.bmp)"));
	cv::String path = file_name.toStdString();
	img = cv::imread(path, true);
	try
	{
		//Repetimos exactamente los mismos pasos que con la captura de vídeo explicada anteriormente.
		cv::Mat1f feature_mat;
		std::vector<cv::Rect> rectangles;
		rectangles = threshold(img, feature_mat);

		cv::Mat min_max = FiletoMat("normal_data.txt");

		cv::Rect submat;
		cv::Mat1f auxiliar;

		for (int i = 0; i < feature_mat.cols; i++)
		{
			submat = cv::Rect(i, 0, 1, feature_mat.rows);
			auxiliar = feature_mat(submat);
			cv::subtract(auxiliar, min_max.at<float>(i, 0), auxiliar);
			cv::divide(auxiliar, min_max.at<float>(i, 1) - min_max.at<float>(i, 0), auxiliar);

		}


		Ptr<SVM> svm = cv::Algorithm::load<SVM>("svm.yml");

		for (int i = 0; i<feature_mat.rows; i++) {
			std::ostringstream str4;
			int pred = svm->predict(feature_mat.row(i), cv::noArray());
			rectangle(img, rectangles[i].tl(), rectangles[i].br(), CV_RGB(0, 255, 0), 3, 8, 0);
			if (pred == 0)
			{
				str4 << "almendra";
			}
			else if (pred == 1)
			{
				str4 << "avellana";
			}
			else if (pred == 2)
			{
				str4 << "castana";
			}
			else if (pred == 3)
			{
				str4 << "nuez";
			}
			else if (pred == 4)
			{
				str4 << "pistacho";
			}

			putText(img, str4.str(), cv::Point(rectangles[i].tl().x + 5, rectangles[i].tl().y + 30), cv::FONT_HERSHEY_COMPLEX_SMALL, 2.00, CV_RGB(229, 87, 4), 2, CV_AA);
		}

		ui.window3->setVisualicedImage(img);

	}
	catch (const std::exception&)
	{
		//En el caso en el que haya habido algún error o no se haya escogido una imagen tras abrir y cerrar el explorador de archivos, atendemos la excepción con un mensaje de error.
		QMessageBox::critical(
			this,
			tr("Camera App"),
			tr("Ha habido un error."));
	}
}

//Esta función nos permite pausar y reanudar el vídeo con el botón correspondiente.
void CameraApp::startStopCapture(bool start) {

	if (start)
	{
		capturing = true;
		videoCapture();
	}
	else
	{
		capturing = false;
	}
}

//Función para segmentar y extraer la matriz de características de una imagen.
std::vector<cv::Rect> CameraApp::threshold(cv::Mat img, cv::Mat1f &feature_mat) {
	cv::Mat edge_img, gray_img;
	cv::Mat1f feature_vector;
	std::vector< std::vector<cv::Point> > contours;

	cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);
	//Aplicamos un filtro gaussiano para reducir ruido.
	cv::GaussianBlur(gray_img, gray_img, Size(5, 5), 0, 0);

	//Umbralización adaptativa para mejorar la robustez frente a cambios de iluminación.
	adaptiveThreshold(gray_img, gray_img, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 55, 5);

	//Extraemos los bordes de la umbralización.
	cv::Canny(gray_img, edge_img, 23, 3 * 23, 3);

	//Los dilatamos con el fin de unirlos entre si y cerrar huecos.
	cv::morphologyEx(edge_img, edge_img, cv::MORPH_DILATE, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(14, 14)));

	//Encontramos contornos con el fin de rellenarlos y poder realizar así una erosión y reducir el ruido recogido por Canny en la imagen umbralizada.
	findContours(edge_img, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	drawContours(edge_img, contours, -1, cv::Scalar(255), CV_FILLED);
	cv::morphologyEx(edge_img, edge_img, cv::MORPH_ERODE, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(14, 14)));

	//Una vez hecha la erosión, volvemos a buscar contornos y almacenarlos en un vector.
	findContours(edge_img, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	std::vector<std::vector<cv::Point> > contours_poly(contours.size());
	std::vector<cv::Rect> boundRect(contours.size());

	//Obtenemos y almacenamos la ROI de cada contorno.
	for (int i = 0; i < contours.size(); i++)
	{
		boundRect[i] = cv::boundingRect(cv::Mat(contours[i]));
	}

	cv::Mat img_roi, mask_roi;
	cv::Rect roi;
	double num_hist_elements;
	std::vector<cv::Rect> boundRect_blobs;
	for (int i = 0; i< contours.size(); i++)
	{
		//Aplicamos un filtrado por área y convexidad (desactivado) y obtenemos la roi de cada contorno y el área de ésta (para normalizar el histograma).  
		if (cv::contourArea(contours[i])>3300 /*&& !isContourConvex(contours[i])*/ && cv::contourArea(contours[i])<300000) {

			roi = cv::Rect(boundRect[i].x, boundRect[i].y, boundRect[i].width, boundRect[i].height);
			boundRect_blobs.push_back(roi);
			num_hist_elements = roi.area();
			img_roi = img(roi).clone();

			mask_roi = cv::Mat();

			//Introducimos cada roi en la función de extracción de características de la que obtenemos un vector con las características de cada imagen.
			feature_vector = extractFeatures(img_roi, mask_roi, num_hist_elements);
			//Dichos vectores los almacenamos en la matriz de caracteristicas.
			feature_mat.push_back(feature_vector);

		}
	}

	//Mostramos el resultado de la umbralización.
	ui.window2->setVisualicedImage(edge_img);

	return boundRect_blobs;
}

//Función para extraer las características de cada imagen.
cv::Mat1f CameraApp::extractFeatures(cv::Mat img_roi, cv::Mat mask_roi, int num_hist_elements) {

	cv::Mat hsv_roi;

	cv::cvtColor(img_roi, hsv_roi, cv::COLOR_BGR2HSV);

	int hbins = 30, sbins = 30;
	int histSize[] = { hbins, sbins };

	float hranges[] = { 0, 180 };
	float sranges[] = { 0, 256 };

	const float* ranges[] = { hranges, sranges };
	cv::Mat1f hs_hist, hs_hist_norm, hs_hist2;

	int channels[] = { 0, 1 };
	//Calculamos el histograma conjunto H-S reducido a 30x30 bins con el fin de extraer características de color de cada imagen.
	cv::calcHist(&hsv_roi, 1, channels, mask_roi, hs_hist, 2, histSize, ranges, true, false);
	//Normalizamos el histograma de tal manera que obtenemos la probablidad de ocurrencia de cada valor H-S.
	hs_hist = hs_hist / num_hist_elements;

	//Posteriormente obtenemos diferentes ROIs de la matriz H-S con el fin de reducir características de color y seleccionar lás más representativas. Dichas matrices han sido obtenidas mediante inspección de la matriz HS de cada imagen correspondiente a cada fruto seco separado.

	//pistacho
	cv::Rect submat = cv::Rect(2, 2, 5, 3);

	//almedra y nuez
	cv::Rect submat2 = cv::Rect(11, 2, 10, 2);

	//castaña y avellana
	cv::Rect submat3 = cv::Rect(7, 0, 14, 1);
	cv::Rect submat4 = cv::Rect(8, 28, 7, 2);

	//avellana
	cv::Rect submat5 = cv::Rect(7, 1, 7, 1);

	//Aplicamos cada roi, vecotrizamos y concatenamos cada vector con el fin de obtener un unico vector con todas las características finalemnte extraidas del color.
	cv::Mat1f hs_hist_red = hs_hist(submat).clone();
	cv::Mat1f hs_hist_red2 = hs_hist(submat2).clone();
	cv::Mat1f hs_hist_red3 = hs_hist(submat3).clone();
	cv::Mat1f hs_hist_red4 = hs_hist(submat4).clone();
	cv::Mat1f hs_hist_red5 = hs_hist(submat5).clone();

	std::vector<float>hist_vec(hs_hist_red.begin(), hs_hist_red.end());
	std::vector<float>hist_vec2(hs_hist_red2.begin(), hs_hist_red2.end());
	std::vector<float>hist_vec3(hs_hist_red3.begin(), hs_hist_red3.end());
	std::vector<float>hist_vec4(hs_hist_red4.begin(), hs_hist_red4.end());
	std::vector<float>hist_vec5(hs_hist_red5.begin(), hs_hist_red5.end());

	std::vector<float>hist_vec_total;

	hist_vec_total.reserve(hist_vec.size() + hist_vec2.size() + hist_vec3.size() + hist_vec4.size() + hist_vec5.size());
	hist_vec_total.insert(hist_vec_total.end(), hist_vec.begin(), hist_vec.end());
	hist_vec_total.insert(hist_vec_total.end(), hist_vec2.begin(), hist_vec2.end());
	hist_vec_total.insert(hist_vec_total.end(), hist_vec3.begin(), hist_vec3.end());
	hist_vec_total.insert(hist_vec_total.end(), hist_vec4.begin(), hist_vec4.end());
	hist_vec_total.insert(hist_vec_total.end(), hist_vec5.begin(), hist_vec5.end());

	//Obtenemos el valor de la entropía de cada imagen y la añadimos al vector de características.
	double entr = entropy(img_roi, mask_roi);

	hist_vec_total.push_back(entr);

	//Añadimos al vector de características el área de la ROI de cada imagen. La agregamos 15 veces seguidas con el fin de darle un mayor peso en la clasificación.
	for (int i = 0; i < 15; i++)
	{
		hist_vec_total.push_back(num_hist_elements);
	}

	//Finalmente devolvemos el vector de características completo.
	cv::Mat1f result = cv::Mat(hist_vec_total).t();
	return result;
}

//Función para calcular el valor de la entropía de una imagen.
double CameraApp::entropy(cv::Mat img_roi, cv::Mat mask_roi)
{
	cv::Mat gray_roi;

	cv::cvtColor(img_roi, gray_roi, cv::COLOR_BGR2GRAY);

	int histSize = 256;
	float range[] = { 0, 256 };
	const float* histRange = { range };
	bool uniform = true;
	bool accumulate = false;

	cv::Mat hist;

	cv::calcHist(&gray_roi, 1, 0, mask_roi, hist, 1, &histSize, &histRange, uniform, accumulate);

	//frequency
	float f = 0;
	for (int i = 0; i<histSize; i++)
	{
		f += hist.at<float>(i);
	}

	//entropy
	double e;
	e = 0;

	float p;

	for (int i = 0; i<histSize; i++)
	{
		p = abs(hist.at<float>(i)) / f;

		if (p != 0)
			e += -p * log10(p);
	}

	return e;
}

//Función para extraer una matriz con las etiquetas de todas las imagenes leidas de la carpeta de entrenamiento y su matriz de características completo de cada muestra.
void CameraApp::extractLables(cv::Mat1f &feature_mat, cv::Mat *p) {

	cv::Mat1f feature_vector;

	QString rutaImagenes = "./train_samples";
	QDir directorio(rutaImagenes);
	QStringList imagenes = directorio.entryList(QStringList() << "*.jpg");
	int size = imagenes.count();

	*p = cv::Mat::zeros(size, 1, CV_32S);

	cv::Mat img;
	for (int i = 0; i < size; i++)
	{
		if (imagenes[i].contains("almendra"))
		{
			(*p).at<int>(i) = 0;

		}
		else if (imagenes[i].contains("avellana"))
		{
			(*p).at<int>(i) = 1;

		}
		else if (imagenes[i].contains("castana"))
		{
			(*p).at<int>(i) = 2;

		}
		else if (imagenes[i].contains("nuez"))
		{
			(*p).at<int>(i) = 3;

		}
		else if (imagenes[i].contains("pistacho"))
		{
			(*p).at<int>(i) = 4;

		}

	}

	//Extraemos las características de cada imagen y lo vectorizamos.
	for (int i = 0; i < size; i++)
	{
		cv::Mat1f feature_vector;
		cv::Mat img_roi, mask_roi;
		double num_hist_elements;

		img = cv::imread(QString("%1/%2").arg(rutaImagenes).arg(imagenes[i]).toStdString());

		num_hist_elements = img.rows*img.cols;
		img_roi = img.clone();

		mask_roi = cv::Mat();

		feature_vector = extractFeatures(img_roi, mask_roi, num_hist_elements);
		feature_mat.push_back(feature_vector);
	}
}

//Función en la que se entrena un clasificador SVM.
void CameraApp::neuralNetworkSetting() {
	cv::Mat1f feature_mat;
	cv::Mat *p;
	cv::Mat etiquetas;
	p = &etiquetas;
	//Extraemos la matriz de etiquetas y la de características.
	extractLables(feature_mat, p);

	cv::Mat auxiliar;
	cv::Rect submat;
	cv::Mat min_max(feature_mat.cols, 2, CV_32F), mat_junta;
	double min, max;
	//Creamos una matriz donde almacenamos el valor minimo y maximo de cada característica con el fin de guardarla para posteriormente normalizar las características de evaluación con los mismos valores.
	//Al mismo tiempo normalizamos los valores de la matriz de características que vamos a usar para entranar al clasificador.
	for (int i = 0; i < feature_mat.cols; i++)
	{
		submat = cv::Rect(i, 0, 1, feature_mat.rows);
		auxiliar = feature_mat(submat);
		cv::minMaxLoc(auxiliar, &min, &max);
		cv::subtract(auxiliar, min, auxiliar);
		cv::divide(auxiliar, max - min, auxiliar);
		min_max.at<float>(i, 0) = min;
		min_max.at<float>(i, 1) = max;

	}

	const char* filename = "normal_data.txt";

	writeMatToFile(min_max, filename, false);

	int nfeatures = feature_mat.cols;

	cv::Mat confusion(5, 5, CV_32S, cv::Scalar(0));

	//Creamos un objeto de tipo traindata con el fin de poder dividir las muestras en train y test de forma cómoda y organizada.
	cv::Ptr<cv::ml::TrainData> td = cv::ml::TrainData::create(feature_mat, cv::ml::ROW_SAMPLE, etiquetas);
	//Set de entrenamiento del 80% y 20% de test.
	td->setTrainTestSplitRatio(0.80, true);

	cv::Mat train_mat = td->getTrainSamples();
	cv::Mat label_train_mat = td->getTrainResponses();

	// Creamos y entrenamos el SVM y guardamos los vectores de dicho resultado.
	Ptr<SVM> svm = SVM::create();
	svm->setType(SVM::C_SVC);
	svm->setKernel(SVM::LINEAR);
	svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
	svm->train(train_mat, ROW_SAMPLE, label_train_mat);
	svm->save("svm.yml");

	cv::Mat test_mat = td->getTestSamples();
	cv::Mat test_label_mat = td->getTestResponses();

	//Realizamos un test del clasificador con las muestras de Test.
	for (int i = 0; i<td->getTestSamples().rows; i++) {
		int pred = svm->predict(td->getTestSamples().row(i));
		int truth = test_label_mat.at<int>(i);
		confusion.at<int>(pred, truth)++;
	}
	//El resultado lo mostramos en un diálogo de información (Porcentaje de acierto y matriz de confusión.)
	cv::Mat correct = confusion.diag();
	QString string = "";
	float accuracy = sum(correct)[0] / sum(confusion)[0];
	string = string + "Training and testing completed!\n";
	string = string + "Testing accuracy: " + QString("%1").arg(accuracy * 100) + "%.\n";
	string = string + "Confusion matrix (p-> Predicted; t-> True):\n";
	string = string + "\n";
	int val;
	for (int i = 0; i <= confusion.rows; i++)
	{
		for (int j = 0; j <= confusion.cols; j++)
		{
			if (i == 0 && j == 0) {
				string = string + "		";
			}

			else if (i == 0 && j == 1) {
				string = string + "t_al	";
			}

			else if (i == 0 && j == 2) {
				string = string + "t_av	";
			}

			else if (i == 0 && j == 3) {
				string = string + "t_ct	";
			}

			else if (i == 0 && j == 4) {
				string = string + "t_nz	";
			}

			else if (i == 0 && j == 5) {
				string = string + "t_ps	";
			}

			else if (i == 1 && j == 0) {
				string = string + "p_al	";
			}

			else if (i == 2 && j == 0) {
				string = string + "p_av	";
			}

			else if (i == 3 && j == 0) {
				string = string + "p_ct	";
			}

			else if (i == 4 && j == 0) {
				string = string + "p_nz	";
			}

			else if (i == 5 && j == 0) {
				string = string + "p_ps	";
			}
			else {
				val = confusion.at<int>(i - 1, j - 1);

				if (j == 1)
				{
					string = string + QString("	%1	").arg(val);
				}
				else {
					string = string + QString("%1	").arg(val);
				}

			}
		}
		string = string + "\n\n\n";
	}
	string = string + "\n";

	QMessageBox::information(
		this,
		tr("Camera App"),
		string);
}

//Funcion para pasar una matriz a archivo de texto con el fin de guardar valores.
void CameraApp::writeMatToFile(cv::Mat& m, const char* filename, bool cond)
{
	FILE *file;
	file = fopen(filename, "w");

	for (int i = 0; i<m.rows; i++)
	{
		for (int j = 0; j<m.cols; j++)
		{
			if (cond) {
				fprintf(file, "%d ", m.at<int>(i, j));
			}
			else {
				fprintf(file, "%f ", m.at<float>(i, j));
			}
		}
		fprintf(file, "\n");
	}
	fclose(file);
}

//Funcion que convierte una tabla de txt a Mat.
cv::Mat CameraApp::FiletoMat(const char* filename)
{
	FILE *file;
	file = fopen(filename, "r");

	int N = 0;
	char c;
	while (!feof(file)) {
		c = fgetc(file);

		if (c == '\n')
		{
			N++;
		}
	}
	fclose(file);

	cv::Mat m(N, 2, CV_32F, cv::Scalar(0));
	file = fopen(filename, "r");

	for (int i = 0; i < N; i++)
	{
		fscanf(file, "%f %f", &(m.at<float>(i, 0)), &(m.at<float>(i, 1)));
	}
	fclose(file);

	return m;
}
