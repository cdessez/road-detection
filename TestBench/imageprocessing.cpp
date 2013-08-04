#include "imageprocessing.h"

#define PI 3.14159265358


ImageProcessing::ImageProcessing() :
    QThread(), imgSource(), imgResult(), file(),
    doA(true), doB(true), doC(true), doD(true), doE(true), doF(false), doG(false), doH(false), doI(false),
    doMedianFilterA(true), doLowPassFilterA(false), filterSizeA(3),
    colorSpaceB(3), doBackprojectingB(true), doDistanceFilterB(false), backprojectingTresholdB(50), distanceFilterTresholdB(50),
    samplePosxB(0), samplePosyB(0), sampleSizeB(15),
    doMedianFilterC(true), doClosingC(true), doOpenningC(false), closingPrioritaryC(true),
    filterSizeC(3), closingSizeC(3), openningSizeC(3), closingRepetitionsC(1), openningRepetitionsC(1),
    doFindContoursD(false), doCannyD(true), doMinPerimeterD(true), minPerimeterD(50), thicknessD(2), cannyLowThresholdD(125), cannyHighThresholdD(350),
    stepRadiiE(3), stepAngleE(2), thresholdE(80), miniRoadAngleE(20),
    fourPointsRatioF(4.0), resultSizeRatioF(5.0), resolutionRatioF(4),
    aG(255.0), bG(1.0), avGaussBlurG(true), blurSizeG(3),
    shiftingRigidityH(3), widthRigidityH(5), maxWidthDifferenceH(20), cuttingLimitH(50), transparencyH(30), cutColorH(false)
{
}


ImageProcessing::ImageProcessing(String file, QObject *parent)
{
    ImageProcessing();
    this->setParent(parent);
    setImage(file);
}


void ImageProcessing::setImage(String file){
    this->file = file ;
    imgSource = imread(file) ;
}

void ImageProcessing::setDoA(bool b) { doA = b ; }
void ImageProcessing::setDoB(bool b) { doB = b ; }
void ImageProcessing::setDoC(bool b) { doC = b ; }
void ImageProcessing::setDoD(bool b) { doD = b ; }
void ImageProcessing::setDoE(bool b) { doE = b ; }
void ImageProcessing::setDoF(bool b) { doF = b ; }
void ImageProcessing::setDoG(bool b) { doG = b ; }
void ImageProcessing::setDoH(bool b) { doH = b ; }
void ImageProcessing::setDoI(bool b) { doI = b ; }
void ImageProcessing::setDoMedianFilterA(bool b) { doMedianFilterA = b ; }
void ImageProcessing::setDoLowPassFilterA(bool b) { doLowPassFilterA = b ; }
void ImageProcessing::setFilterSizeA(int i) { filterSizeA = i ; }
void ImageProcessing::setColorSpaceB(int i) { colorSpaceB = i ; }
void ImageProcessing::setDoBackProjectingB(bool b) { doBackprojectingB = b ; }
void ImageProcessing::setBackprojectingTresholdB(int i) { backprojectingTresholdB = i ; }
void ImageProcessing::setDoDistanceFilterB(bool b) { doDistanceFilterB = b ; }
void ImageProcessing::setDistanceFilterTresholdB(int i) { distanceFilterTresholdB = i ; }
void ImageProcessing::setSamplePosxB(int i) { samplePosxB = i ; }
void ImageProcessing::setSamplePosyB(int i) { samplePosyB = i ; }
void ImageProcessing::setSampleSizeB(int i) { sampleSizeB = i ; }
void ImageProcessing::setDoMedianFilterC(bool b) { doMedianFilterC = b ; }
void ImageProcessing::setDoClosing(bool b) { doClosingC = b ; }
void ImageProcessing::setDoOpenning(bool b) { doOpenningC = b ; }
void ImageProcessing::setClosingPrioritaryC(bool b) { closingPrioritaryC = b ; }
void ImageProcessing::setFilterSizeC(int i) { filterSizeC = i ; }
void ImageProcessing::setClosingSizeC(int i) { closingSizeC = i ; }
void ImageProcessing::setOpenningSizeC(int i) { openningSizeC = i ; }
void ImageProcessing::setOpenningRepetitionsC(int i) { openningRepetitionsC = i ; }
void ImageProcessing::setClosingRepetitionsC(int i) { closingRepetitionsC = i ; }
void ImageProcessing::setDoFindContoursD(bool b) { doFindContoursD = b ; }
void ImageProcessing::setDoCannyD(bool b) { doCannyD = b ; }
void ImageProcessing::setDoMinPerimeterD(bool b) { doMinPerimeterD = b ; }
void ImageProcessing::setMinPerimeterD(int i) { minPerimeterD = i ; }
void ImageProcessing::setThicknessD(int i) { thicknessD = i ; }
void ImageProcessing::setCannyLowThresholdD(int i) { cannyLowThresholdD = i ; }
void ImageProcessing::setCannyHighThresholdD(int i) { cannyHighThresholdD = i ; }
void ImageProcessing::setStepRadiiE(int i) { stepRadiiE = i ; }
void ImageProcessing::setStepAngleE(int i) { stepAngleE = i ; }
void ImageProcessing::setThresholdE(int i) { thresholdE = i ; }
void ImageProcessing::setMiniRoadAngleE(int i) { miniRoadAngleE = i ; }
void ImageProcessing::setFourPointsRatioF(double d) { fourPointsRatioF = d ; }
void ImageProcessing::setResultSizeRatioF(double d) { resultSizeRatioF = d ; }
void ImageProcessing::setResolutionRatioF(int i) { resolutionRatioF = i ; }
void ImageProcessing::setAG(double d) { aG = d ; }
void ImageProcessing::setBG(double d) { bG = d ; }
void ImageProcessing::setAvGaussBlurG(bool b) { avGaussBlurG = b ; }
void ImageProcessing::setBlurSizeG(int i) { blurSizeG = i ; }
void ImageProcessing::setShiftingRigidityH(int i) { shiftingRigidityH = i ; }
void ImageProcessing::setWidthRigidityH(int i) { widthRigidityH = i ; }
void ImageProcessing::setMaxWidthDifferenceH(int i) { maxWidthDifferenceH = i ; }
void ImageProcessing::setCutColorH(bool b) { cutColorH = b ; }
void ImageProcessing::setCuttingLimitH(int i) { cuttingLimitH = i ; }
void ImageProcessing::setTransparencyH(int i) { transparencyH = i ; }


QImage ImageProcessing::getResult() {
    Mat img ;
    imgResult.copyTo(img);
    if (((doB || doC || doD || doE) && !doF) || (doG && !doH))
        cvtColor(imgResult,img,CV_GRAY2RGB);
    else
        cvtColor(imgResult,img,CV_BGR2RGB);
    return QImage((const unsigned char*)(img.data), img.cols,img.rows,QImage::Format_RGB888).copy();
}

QImage ImageProcessing::getSampleQImage() {
    Mat img ;
    getSample(imgSource, samplePosxB, samplePosyB, sampleSizeB).copyTo(img);
    cvtColor(img,img,CV_BGR2RGB);
    return QImage((const unsigned char*)(img.data), img.cols,img.rows,QImage::Format_RGB888).copy();
}


void ImageProcessing::run() {
    Mat image ;
    this->imgSource.copyTo(image);

    if (doA) {
        if (doLowPassFilterA)
            image = lowPassFilter(image, filterSizeA);
        if (doMedianFilterA)
            image = medianFilter(image, filterSizeA);
    }
    if (doB) {
        if (doBackprojectingB) {
            switch (colorSpaceB) {
            case 0 :
                image = backprojectionGray(image, backprojectingTresholdB, samplePosxB, samplePosyB, sampleSizeB);
                break ;
            case 1 :
                image = backprojectionBGR(image, backprojectingTresholdB, samplePosxB, samplePosyB, sampleSizeB);
                break ;
            case 2 :
                image = backprojectionCIE(image, backprojectingTresholdB, samplePosxB, samplePosyB, sampleSizeB);
                break ;
            case 3 :
                image = backprojectionHSV(image, backprojectingTresholdB, samplePosxB, samplePosyB, sampleSizeB);
                break ;
            case 4 :
                image = backprojectionYCRCB(image, backprojectingTresholdB, samplePosxB, samplePosyB, sampleSizeB);
                break ;
            }
        }
        if (doDistanceFilterB){
            switch (colorSpaceB) {
            case 0 :
                image = distanceFilterGray(image, distanceFilterTresholdB, samplePosxB, samplePosyB, sampleSizeB);
                break ;
            case 1 :
                image = distanceFilterBGR(image, distanceFilterTresholdB, samplePosxB, samplePosyB, sampleSizeB);
                break ;
            case 2 :
                image = distanceFilterCIE(image, distanceFilterTresholdB, samplePosxB, samplePosyB, sampleSizeB);
                break ;
            case 3 :
                image = distanceFilterHSV(image, distanceFilterTresholdB, samplePosxB, samplePosyB, sampleSizeB);
                break ;
            case 4 :
                image = distanceFilterYCRCB(image, distanceFilterTresholdB, samplePosxB, samplePosyB, sampleSizeB);
                break ;
            }
        }
        if (!doDistanceFilterB && !doBackprojectingB)
            cvtColor(image,image,CV_BGR2GRAY);
    }
    if (doC) {
        if (doMedianFilterC)
            image = medianFilter(image, filterSizeC);
        if (doOpenningC && doClosingC){
            if (closingPrioritaryC){
                for(int i=0; i<closingRepetitionsC; i++)
                    image = closing(image, closingSizeC);
                for(int i=0; i<openningRepetitionsC; i++)
                    image = openning(image, openningSizeC);
            } else {
                for(int i=0; i<openningRepetitionsC; i++)
                    image = openning(image, openningSizeC);
                for(int i=0; i<closingRepetitionsC; i++)
                    image = closing(image, closingSizeC);
            }
        } else {
            if (doOpenningC)
                for(int i=0; i<openningRepetitionsC; i++)
                    image = openning(image, openningSizeC);
            if (doClosingC)
                for(int i=0; i<closingRepetitionsC; i++)
                    image = closing(image, closingSizeC);
        }
    }
    if (doD) {
        if (doCannyD)
            image = performCanny(image, cannyLowThresholdD, cannyHighThresholdD);
        if (doFindContoursD)
            image = performFindContours(image, thicknessD, doMinPerimeterD, minPerimeterD);
    }
    if (doE) {
        image = extractAndDrawRoadLines(imgSource, image, stepRadiiE, stepAngleE, thresholdE, cannyLowThresholdD, cannyHighThresholdD, miniRoadAngleE);
    }
    if (doF && !doH) {
        image = birdEyeView(imgSource,
                            extractRoadLines(imgSource, image, stepRadiiE, stepAngleE, thresholdE, cannyLowThresholdD, cannyHighThresholdD, miniRoadAngleE),
                            fourPointsRatioF,
                            resultSizeRatioF,
                            resolutionRatioF);
    }
    if (doG && !doH) {
        image = createPotential(image, aG, bG, avGaussBlurG, blurSizeG);
    }
    if (doH) {
        Mat bev = birdEyeView(imgSource,
                              extractRoadLines(imgSource, image, stepRadiiE, stepAngleE, thresholdE, cannyLowThresholdD, cannyHighThresholdD, miniRoadAngleE),
                              fourPointsRatioF,
                              resultSizeRatioF,
                              resolutionRatioF);
        Mat potential = createPotential(bev, aG, bG, avGaussBlurG, blurSizeG) ;
        Mat mask = snakeRoadBorderLine(potential, shiftingRigidityH, widthRigidityH, maxWidthDifferenceH, cutColorH, cuttingLimitH);

        if (!doI){
            addWeighted(bev, 1., mask, transparencyH/100., 0., image);
        } else {
            Mat mask2 ;
            warpPerspective(mask, mask2, homography, Size(imgSource.cols, imgSource.rows), WARP_INVERSE_MAP);
            addWeighted(imgSource, 1., mask2, transparencyH/100., 0., image);
        }
    }

    imgResult = image ;
}



Mat ImageProcessing::lowPassFilter(const Mat &image, int filterSize){
    // Filtre passe-bas
    Mat result ;
    blur(image,result,cv::Size(filterSize, filterSize)) ;
    return result ;
}


Mat ImageProcessing::medianFilter(const Mat &image, int filterSize){
    // Filtre de la médiane
    Mat result ;
    medianBlur(image,result,filterSize) ;
    return result ;
}


Mat ImageProcessing::getSample(const Mat &image, int samplePosx, int samplePosy, int sampleSize) {
    int x, y ;
    x = ((image.cols - sampleSize) * samplePosx) /100 ;
    y = ((image.rows - sampleSize) * samplePosy) /100 ;
    return image(Rect(x, y, sampleSize, sampleSize)) ;
}


Mat ImageProcessing::backprojectionGray(const Mat &image, int treshold, int samplePosx, int samplePosy, int sampleSize){
    // image doit etre une image au format BGR (en couleur)
    // Cette fonction colore en blanc les pixels qui ont une forte proba d'appartenir à la même texture que l'échantillon

    Mat imageGray, sample ;
    cvtColor(image, imageGray, CV_BGR2GRAY) ;
    sample = getSample(imageGray, samplePosx, samplePosy, sampleSize) ;

    // Computing the histogram
    MatND hist ;
    int histSize[1]; histSize[0]=256;
    float hranges[2]; hranges[0]=0.0 ; hranges[1]=255.0 ;
    const float* ranges[1]; ranges[0]=hranges ;
    int channels[1]; channels[0]=0;
    calcHist(&sample, 1, channels, Mat(), hist, 1, histSize, ranges) ;
    normalize(hist, hist, 1.0) ;

    // backprojection
    Mat result ;
    calcBackProject(&imageGray, 1, channels, hist, result, ranges, 255.0);

    // Apply the threshold
    threshold(result, result, treshold, 255, THRESH_BINARY);

    return result ;
}


Mat ImageProcessing::backprojectionBGR(const Mat &image, int treshold, int samplePosx, int samplePosy, int sampleSize){
    // image doit etre une image au format BGR (en couleur)
    // Cette fonction colore en blanc les pixels qui ont une forte proba d'appartenir à la même texture que l'échantillon

    Mat imageBGR, sample ;
    image.copyTo(imageBGR);
    sample = getSample(imageBGR, samplePosx, samplePosy, sampleSize) ;

    // Computing the histogram
    MatND hist ;
    int histSize[3];
    float hranges[2];
    const float* ranges[3];
    int channels[3];
    histSize[0]=histSize[1]=histSize[2]=64;
    hranges[0]= 0.0;
    hranges[1]= 255.0;
    ranges[0] = hranges;
    ranges[1] = hranges;
    ranges[2] = hranges;
    channels[0] = 0;
    channels[1] = 1;
    channels[2] = 2;
    calcHist(&sample, 1, channels, Mat(), hist, 3, histSize, ranges) ;
    normalize(hist, hist, 1.0);

    // backprojection
    Mat result ;
    calcBackProject(&imageBGR, 1, channels, hist, result, ranges, 255) ;

    // Apply the threshold
    threshold(result, result, treshold, 255, THRESH_BINARY);

    return result ;
}


Mat ImageProcessing::backprojectionCIE(const Mat &image, int treshold, int samplePosx, int samplePosy, int sampleSize){
    // image doit etre une image au format BGR (en couleur)
    // Cette fonction colore en blanc les pixels qui ont une forte proba d'appartenir à la même texture que l'échantillon

    Mat imageCIE, sample ;
    cvtColor(image, imageCIE, CV_BGR2Lab);
    sample = getSample(imageCIE, samplePosx, samplePosy, sampleSize) ;

    // Computing the histogram
    MatND hist ;
    int histSize[2];
    float hranges[2];
    const float* ranges[2];
    int channels[2];
    histSize[0]=32;
    histSize[1]=32;
    hranges[0]= 0.0;
    hranges[1]= 255.0;
    ranges[0] = hranges;
    ranges[1] = hranges;
    channels[0] = 1;
    channels[1] = 2;
    calcHist(&sample, 1, channels, Mat(), hist, 2, histSize, ranges);
    normalize(hist,hist, 1.0);

    // backprojection
    Mat result ;
    calcBackProject(&imageCIE, 1, channels, hist, result, ranges, 255.0);

    // Apply the threshold
    threshold(result, result, treshold, 255, THRESH_BINARY);

    return result ;
}


Mat ImageProcessing::backprojectionHSV(const Mat &image, int treshold, int samplePosx, int samplePosy, int sampleSize){
    // image doit etre une image au format BGR (en couleur)
    // Cette fonction colore en blanc les pixels qui ont une forte proba d'appartenir à la même texture que l'échantillon

    Mat imageHSV, sample ;
    cvtColor(image, imageHSV, CV_BGR2HSV);
    sample = getSample(imageHSV, samplePosx, samplePosy, sampleSize);

    // Computing the histogram
    MatND hist ;
    int histSize[] = {24, 16} ;
    float hranges[] = {0, 180} ;
    float sranges[] = {0, 256} ;
    const float* ranges[] = {hranges, sranges} ;
    int channels[] = {0, 1};
    calcHist(&sample, 1, channels, Mat(), hist, 2, histSize, ranges);
    normalize(hist, hist, 1.0);

    // backprojection
    Mat result ;
    calcBackProject(&imageHSV, 1, channels, hist, result, ranges, 255);

    // Apply the threshold
    threshold(result, result, treshold, 255, THRESH_BINARY);

    return result ;
}


Mat ImageProcessing::backprojectionYCRCB(const Mat &image, int treshold, int samplePosx, int samplePosy, int sampleSize) {
    // image doit etre une image au format BGR (en couleur)
    // Cette fonction colore en blanc les pixels qui ont une forte proba d'appartenir à la même texture que l'échantillon

    Mat imageYCRCB, sample ;
    cvtColor(image, imageYCRCB, CV_BGR2YCrCb);
    sample = getSample(imageYCRCB, samplePosx, samplePosy, sampleSize);

    // Computing the histogram
    MatND hist ;
    int histSize[] = {32, 32} ;
    float hranges[] = {0, 255} ;
    const float* ranges[] = {hranges, hranges} ;
    int channels[] = {1, 2};
    calcHist(&sample, 1, channels, Mat(), hist, 2, histSize, ranges);
    normalize(hist, hist, 1.0);

    // backprojection
    Mat result ;
    calcBackProject(&imageYCRCB, 1, channels, hist, result, ranges, 255);

    // Apply the threshold
    threshold(result, result, treshold, 255, THRESH_BINARY);

    return result ;
}


uchar ImageProcessing::getAverageColorGray(const Mat &image, int samplePosx, int samplePosy, int sampleSize) {
    // image doit être au format Gray
    Mat sample = getSample(image, samplePosx, samplePosy, sampleSize);
    int nl= sample.rows ;
    int nc= sample.cols ;
    int av=0 ;
    for(int j=0; j<nl; j++){
        uchar* data= sample.ptr<uchar>(j);
        for(int i=0; i<nc; i++){
            av+=*data; data++;
        }
    }
    av /= sampleSize*sampleSize ;
    return av ;
}


Mat ImageProcessing::distanceFilterGray(Mat &image, int treshold, int samplePosx, int samplePosy, int sampleSize) {
    // colore les pixels qui sont à une distance de la moyenne de l'échantillon inférieure à treshold
    Mat imageGray ;
    cvtColor(image, imageGray, CV_BGR2GRAY);
    uchar color = getAverageColorGray(imageGray, samplePosx, samplePosy, sampleSize) ;
    Mat result(imageGray.size(), CV_8U);
    int nl= imageGray.rows ;
    int nc= imageGray.cols ;
    for(int j=0; j<nl; j++){
        uchar* data= imageGray.ptr<uchar>(j);
        uchar* res= result.ptr<uchar>(j);
        for(int i=0; i<nc; i++){
            int dist = abs(color-*data) ;
            if (dist<=treshold)
                *res = 255;
            else
                *res = 0;
            data++; res++;
        }
    }
    return result ;
}


Vec3b ImageProcessing::getAverageColor3b(const Mat &image, int samplePosx, int samplePosy, int sampleSize) {
    // image doit être dans un format à 3 canaux
    Mat sample = getSample(image, samplePosx, samplePosy, sampleSize);
    int nl= sample.rows ;
    int nc= sample.cols ;
    int avB=0, avR=0, avG=0 ;
    for(int j=0; j<nl; j++){
        uchar* data= sample.ptr<uchar>(j);
        for(int i=0; i<nc; i++){
            avB+=*data; data++;
            avG+=*data; data++;
            avR+=*data; data++;
        }
    }
    int nbrPx = sampleSize*sampleSize ;
    return Vec3b(avB/nbrPx, avG/nbrPx, avR/nbrPx);
}


Mat ImageProcessing::distanceFilterBGR(Mat &image, int treshold, int samplePosx, int samplePosy, int sampleSize) {
    // colore les pixels qui sont à une distance de la moyenne de l'échantillon inférieure à treshold
    Vec3b color = getAverageColor3b(image, samplePosx, samplePosy, sampleSize) ;
    Mat result(image.size(), CV_8U);
    int nl= image.rows ;
    int nc= image.cols ;
    for(int j=0; j<nl; j++){
        uchar* data= image.ptr<uchar>(j);
        uchar* res= result.ptr<uchar>(j);
        for(int i=0; i<nc; i++){
            int dist= abs((int)*data-(int)color[0]) ; data++;
            dist+= abs(*data-color[1]) ; data++;
            dist+= abs(*data-color[2]) ; data++;
            if (dist<=treshold)
                *res = 255;
            else
                *res = 0;
            res++;
        }
    }
    return result ;
}


Mat ImageProcessing::distanceFilterCIE(Mat &image, int treshold, int samplePosx, int samplePosy, int sampleSize) {
    // colore les pixels qui sont à une distance de la moyenne de l'échantillon inférieure à treshold
    Mat imageCIE ;
    cvtColor(image,imageCIE,CV_BGR2Lab);
    Vec3b color = getAverageColor3b(imageCIE, samplePosx, samplePosy, sampleSize) ;
    Mat result(imageCIE.size(), CV_8U);
    int nl= imageCIE.rows ;
    int nc= imageCIE.cols ;
    for(int j=0; j<nl; j++){
        uchar* data= imageCIE.ptr<uchar>(j);
        uchar* res= result.ptr<uchar>(j);
        for(int i=0; i<nc; i++){
            int dist= abs((int)*data-(int)color[0]) ; data++;
            dist+= abs(*data-color[1]) ; data++;
            dist+= abs(*data-color[2]) ; data++;
            if (dist<=treshold)
                *res = 255;
            else
                *res = 0;
            res++;
        }
    }
    return result ;
}


Vec2b ImageProcessing::getAverageColorHSV(const Mat &image, int samplePosx, int samplePosy, int sampleSize) {
    // image doit être au format HSV
    Mat sample = getSample(image, samplePosx, samplePosy, sampleSize);
    int nl= sample.rows ;
    int nc= sample.cols ;
    int avH=0, avS=0 ;
    for(int j=0; j<nl; j++){
        uchar* data= sample.ptr<uchar>(j);
        for(int i=0; i<nc; i++){
            avH+=*data; data++;
            avS+=*data; data++;
            data++;
        }
    }
    int nbrPx = sampleSize*sampleSize ;
    return Vec2b(avH/nbrPx, avS/nbrPx);
}


Mat ImageProcessing::distanceFilterHSV(Mat &image, int treshold, int samplePosx, int samplePosy, int sampleSize) {
    // colore les pixels qui sont à une distance de la moyenne de l'échantillon inférieure à treshold
    Mat imageHSV ;
    cvtColor(image,imageHSV,CV_BGR2HSV);
    Vec2b color = getAverageColorHSV(imageHSV, samplePosx, samplePosy, sampleSize) ;
    Mat result(imageHSV.size(), CV_8U);
    int nl= imageHSV.rows ;
    int nc= imageHSV.cols ;
    for(int j=0; j<nl; j++){
        uchar* data= imageHSV.ptr<uchar>(j);
        uchar* res= result.ptr<uchar>(j);
        for(int i=0; i<nc; i++){
            int m= 180-abs((int)*data-(int)color[0]) ;
            int n= abs((int)*data-(int)color[0]) ;
                    int dist= (n<m ? n : m) ; data++;
            dist+= abs(*data-color[1]) ; data++;
            data++;
            if (dist<=treshold)
                *res = 255;
            else
                *res = 0;
            res++;
        }
    }
    return result ;
}


Vec2b ImageProcessing::getAverageColorYCRCB(const Mat &image, int samplePosx, int samplePosy, int sampleSize) {
    // image doit être au format YCrCb
    Mat sample = getSample(image, samplePosx, samplePosy, sampleSize);
    int nl= sample.rows ;
    int nc= sample.cols ;
    int avCR=0, avCB=0 ;
    for(int j=0; j<nl; j++){
        uchar* data= sample.ptr<uchar>(j);
        for(int i=0; i<nc; i++){
            data++;
            avCR+=*data; data++;
            avCB+=*data; data++;
        }
    }
    int nbrPx = sampleSize*sampleSize ;
    return Vec2b(avCR/nbrPx, avCB/nbrPx);
}


Mat ImageProcessing::distanceFilterYCRCB(Mat &image, int treshold, int samplePosx, int samplePosy, int sampleSize) {
    // colore les pixels qui sont à une distance de la moyenne de l'échantillon inférieure à treshold
    Mat imageYCRCB ;
    cvtColor(image,imageYCRCB,CV_BGR2YCrCb);
    Vec2b color = getAverageColorYCRCB(imageYCRCB, samplePosx, samplePosy, sampleSize) ;
    Mat result(imageYCRCB.size(), CV_8U);
    int nl= imageYCRCB.rows ;
    int nc= imageYCRCB.cols ;
    for(int j=0; j<nl; j++){
        uchar* data= imageYCRCB.ptr<uchar>(j);
        uchar* res= result.ptr<uchar>(j);
        for(int i=0; i<nc; i++){
            data++;
            int dist= abs((int)*data-(int)color[0]) ; data++;
            dist+= abs(*data-color[1]) ; data++;
            if (dist<=treshold)
                *res = 255;
            else
                *res = 0;
            res++;
        }
    }
    return result ;
}


Mat ImageProcessing::openning(const Mat &image, int size) {
    // preform the openning
    Mat element(2*size+1,2*size+1,CV_8U,Scalar(0));
    circle(element, Point(size+1, size+1), size, Scalar(1), -1);
    Mat openned;
    morphologyEx(image,openned,cv::MORPH_OPEN,element);
    return openned ;
}


Mat ImageProcessing::closing(const Mat &image, int size) {
    // preform the closing
    Mat element(2*size+1,2*size+1,CV_8U,Scalar(0));
    circle(element, Point(size+1, size+1), size, Scalar(1), -1);
    Mat closed;
    morphologyEx(image,closed,MORPH_CLOSE,element);
    return closed ;
}


Mat ImageProcessing::performCanny(const Mat &image, int lowThreshold, int highThreshold) {
    // l'image doit être en Gray (1 seul canal)
    Mat contours ;
    Canny(image, contours, lowThreshold, highThreshold);
    return contours ;
}


Mat ImageProcessing::performFindContours(Mat &image, int thickness, bool doMinPerimeter, int minPerimeter){
    // cherche les contours fermés, les rejette si trop petites et doMinPerimeter==true, et les trace
    std::vector<std::vector<Point> > contours;
    findContours(image, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE) ;

    if (doMinPerimeter) {
        std::vector<std::vector<cv::Point> >::iterator itc= contours.begin();
        while (itc!=contours.end()) {
            if (itc->size() < minPerimeter)
                itc= contours.erase(itc);
            else
                ++itc;
        }
    }

    Mat result(image.size(),CV_8U,Scalar(0));
    drawContours(result,contours, -1, Scalar(255), thickness);

    return result ;


}


vector<Vec2f> ImageProcessing::extractLines(Mat &image, int stepRadii, int stepAngle, int threshold, int cannyLowThreshold, int cannyHighThreshold){
    // extrait les lignes de l'image par transformée de Hough
    Mat contours = performCanny(image, cannyLowThreshold, cannyHighThreshold) ;
    vector<Vec2f> lines ;
    cv::HoughLines(contours, lines, stepRadii, stepAngle*PI/180, threshold) ;
    return lines ;
}


Mat ImageProcessing::extractAndDrawRoadLines(Mat &imageOrigin, Mat &mask, int stepRadii, int stepAngle, int threshold, int cannyLowThreshold, int cannyHighThreshold, int miniRoadAngle){
    // extrait les lignes de imageOrigin&mask et les trace en blanc sur fond noir
    mask(Rect(0, 0, imageOrigin.cols, imageOrigin.rows/5*3)).setTo(Scalar(0));
    Mat maskedImage ;
    cvtColor(imageOrigin, maskedImage, CV_BGR2GRAY);
    maskedImage = maskedImage & mask ;

    //maskedImage = performCanny(maskedImage, cannyLowThreshold, cannyHighThreshold) ;
    vector<Vec2f> lines = extractLines(maskedImage, stepRadii, stepAngle, threshold, cannyLowThreshold, cannyHighThreshold);

    float angle = ((float) miniRoadAngle)*PI/180.0 ;
    Vec2f leftLine(0., 1.1*PI/2.);
    bool leftLineExists = false ;
    Vec2f rightLine(0., 0.9*PI/2.);
    bool rightLineExists = false ;
    vector<Vec2f>::iterator it= lines.begin();
    //*
    while (it!=lines.end()) {
        float theta= (*it)[1];
        if (theta > angle && theta < rightLine[1]) {
            rightLine[0] = (*it)[0] ;
            rightLine[1] = (*it)[1] ;
            rightLineExists = true ;
        } else if (theta < PI - angle && theta > leftLine[1]) {
            leftLine[0] = (*it)[0] ;
            leftLine[1] = (*it)[1] ;
            leftLineExists = true ;
        }
        ++it;
    }
    //*/

    //* sélection de la droite d'angle médian dans le paquet de droite dont l'angle diffère de moins de 3°
    QMap<float, Vec2f> leftMap, rightMap ;
    vector<Vec2f>::iterator i= lines.begin() ;
    angle = 3.*PI/180. ;
    while (i!=lines.end()) {
        float theta= (*i)[1];
        if (theta - rightLine[1] <= angle) {
            rightMap.insert(theta, *i);
        } else if (leftLine[1] - theta <= angle) {
            leftMap.insert(theta, *i) ;
        }
        ++i;
    }
    int nLeft = (leftMap.size() + 1) / 3 ;
    int nRight = (rightMap.size() + 1) / 3 ;
    int j = 0 ;
    foreach(Vec2f v, leftMap){
        if (j == nLeft)
            leftLine = v ;
        j++ ;
    }
    j = 0 ;
    foreach(Vec2f v, rightMap){
        if (j == nRight)
            rightLine = v ;
        j++ ;
    }//*/

    // Cas pathologiques si aucune ligne correspondant aux critères ne convient
    if (leftLineExists && !rightLineExists){
        rightLine[0]= leftLine[0] - (maskedImage.cols*cos(leftLine[1])) ;
        rightLine[1]= PI - leftLine[1] ;
    }
    if (rightLineExists && !leftLineExists){
        leftLine[0]= rightLine[0] - (maskedImage.cols*cos(rightLine[1])) ;
        leftLine[1]= PI - rightLine[1] ;
    }
    if (!leftLineExists && !rightLineExists) {
        rightLine[0]=0. ;
        rightLine[1]=PI/4. ;
        leftLine[0]= rightLine[0] - maskedImage.cols*cos(rightLine[1]) ;
        leftLine[1]= PI - rightLine[1] ;
    }

    //*  Trace tous les droites détectées
    vector<Vec2f>::iterator ite= lines.begin();
    while (ite!=lines.end()) {
        float rho= (*ite)[0];
        float theta= (*ite)[1];
        if (theta < PI/4. || theta > 3.*PI/4.) {
            Point pt1(rho/cos(theta),0);
            Point pt2((rho-maskedImage.rows*sin(theta))/cos(theta),maskedImage.rows);
            line(maskedImage, pt1, pt2, cv::Scalar(255), 1);
        } else {
            Point pt1(0,rho/sin(theta));
            Point pt2(maskedImage.cols, (rho-maskedImage.cols*cos(theta))/sin(theta));
            line(maskedImage, pt1, pt2, cv::Scalar(255), 1);
        }
        ++ite;
    }
    //*/

    //* Trace les deux droites sélectionnées
    float rho = leftLine[0] ; float theta = leftLine[1] ;
    if (theta < PI/4. || theta > 3.*PI/4.) { // ~vertical line
        Point pt1(rho/cos(theta),0);
        Point pt2((rho-maskedImage.rows*sin(theta))/cos(theta), maskedImage.rows);
        line(maskedImage, pt1, pt2, Scalar(255), 6);
    } else { // ~horizontal line
        Point pt1(0,rho/sin(theta));
        Point pt2(maskedImage.cols, (rho-maskedImage.cols*cos(theta))/sin(theta));
        line(maskedImage, pt1, pt2, Scalar(255), 6);
    }
    rho = rightLine[0] ; theta = rightLine[1] ;
    if (theta < PI/4. || theta > 3.*PI/4.) { // ~vertical line
        Point pt1(rho/cos(theta),0);
        Point pt2((rho-maskedImage.rows*sin(theta))/cos(theta), maskedImage.rows);
        line(maskedImage, pt1, pt2, Scalar(255), 6);
    } else { // ~horizontal line
        Point pt1(0,rho/sin(theta));
        Point pt2(maskedImage.cols, (rho-maskedImage.cols*cos(theta))/sin(theta));
        line(maskedImage, pt1, pt2, Scalar(255), 6);
    }//*/

    return maskedImage ;
}


vector<Vec2f> ImageProcessing::extractRoadLines(Mat &imageOrigin, Mat &mask, int stepRadii, int stepAngle, int threshold, int cannyLowThreshold, int cannyHighThreshold, int miniRoadAngle){
    mask(Rect(0, 0, imageOrigin.cols, imageOrigin.rows/5*3)).setTo(Scalar(0));
    Mat maskedImage ;
    cvtColor(imageOrigin, maskedImage, CV_BGR2GRAY);
    maskedImage = maskedImage & mask ;

    vector<Vec2f> lines = extractLines(maskedImage, stepRadii, stepAngle, threshold, cannyLowThreshold, cannyHighThreshold);

    float angle = ((float) miniRoadAngle)*PI/180.0 ;
    Vec2f leftLine(0., 1.1*PI/2.);
    bool leftLineExists = false ;
    Vec2f rightLine(0., 0.9*PI/2.);
    bool rightLineExists = false ;
    vector<Vec2f>::iterator it= lines.begin();
    //*
    while (it!=lines.end()) {
        float theta= (*it)[1];
        if (theta > angle && theta < rightLine[1]) {
            rightLine[0] = (*it)[0] ;
            rightLine[1] = (*it)[1] ;
            rightLineExists = true ;
        } else if (theta < PI - angle && theta > leftLine[1]) {
            leftLine[0] = (*it)[0] ;
            leftLine[1] = (*it)[1] ;
            leftLineExists = true ;
        }
        ++it;
    }
    //*/

    //* sélection de la droite d'angle médian dans le paquet de droite dont l'angle diffère de moins de 3°
    QMap<float, Vec2f> leftMap, rightMap ;
    vector<Vec2f>::iterator i= lines.begin() ;
    angle = 3.*PI/180. ;
    while (i!=lines.end()) {
        float theta= (*i)[1];
        if (theta - rightLine[1] <= angle) {
            rightMap.insert(theta, *i);
        } else if (leftLine[1] - theta <= angle) {
            leftMap.insert(theta, *i) ;
        }
        ++i;
    }
    int nLeft = (leftMap.size() + 1) / 3 ;
    int nRight = (rightMap.size() + 1) / 3 ;
    int j = 0 ;
    foreach(Vec2f v, leftMap){
        if (j == nLeft)
            leftLine = v ;
        j++ ;
    }
    j = 0 ;
    foreach(Vec2f v, rightMap){
        if (j == nRight)
            rightLine = v ;
        j++ ;
    }//*/

    // Cas pathologiques si aucune ligne correspondant aux critères ne convient
    if (leftLineExists && !rightLineExists){
        rightLine[0]= leftLine[0] - (maskedImage.cols*cos(leftLine[1])) ;
        rightLine[1]= PI - leftLine[1] ;
    }
    if (rightLineExists && !leftLineExists){
        leftLine[0]= rightLine[0] - (maskedImage.cols*cos(rightLine[1])) ;
        leftLine[1]= PI - rightLine[1] ;
    }
    if (!leftLineExists && !rightLineExists) {
        rightLine[0]=0. ;
        rightLine[1]=PI/4. ;
        leftLine[0]= rightLine[0] - maskedImage.cols*cos(rightLine[1]) ;
        leftLine[1]= PI - rightLine[1] ;
    }

    vector<Vec2f> res ;
    res.push_back(rightLine) ;
    res.push_back(leftLine) ;
    return res ;
}



Mat ImageProcessing::birdEyeView(Mat &imageOrigin, vector<Vec2f> roadLines, double fourPointsRatio, double resultSizeRatio, int resolutionRatio){
    // effectue la transformation (perspective transform) pour un passage en bird-eye view
    Vec2f leftLine = roadLines[0] ;
    Vec2f rightLine = roadLines[1] ;
    Point2f ptsOrg[4], ptsDst[4] ;

    ptsOrg[0] = Point2f((leftLine[0]-imageOrigin.rows*sin(leftLine[1]))/cos(leftLine[1]), imageOrigin.rows) ;
    ptsOrg[1] = Point2f((leftLine[0]-imageOrigin.rows*(fourPointsRatio-1)/fourPointsRatio*sin(leftLine[1]))/cos(leftLine[1]), (fourPointsRatio-1)/fourPointsRatio*imageOrigin.rows) ;
    ptsOrg[2] = Point2f((rightLine[0]-imageOrigin.rows*sin(rightLine[1]))/cos(rightLine[1]), imageOrigin.rows) ;
    ptsOrg[3] = Point2f((rightLine[0]-imageOrigin.rows*(fourPointsRatio-1)/fourPointsRatio*sin(rightLine[1]))/cos(rightLine[1]), (fourPointsRatio-1)/fourPointsRatio*imageOrigin.rows) ;

    int dstX, dstY ;
    dstX = imageOrigin.cols/resolutionRatio ;
    dstY = dstX*resultSizeRatio ;
    ptsDst[0] = Point2f(2*dstX/5., dstY);
    ptsDst[1] = Point2f(2*dstX/5., dstY-dstX/5.) ;
    ptsDst[2] = Point2f(3.*dstX/5., dstY);
    ptsDst[3] = Point2f(3.*dstX/5, dstY-dstX/5.) ;

    homography = getPerspectiveTransform(ptsOrg, ptsDst) ;
    Mat result ;
    warpPerspective(imageOrigin, result, homography, Size(dstX, dstY));

    return result ;
}



Mat ImageProcessing::createPotential(const Mat& image, double a, double b, bool avGaussBlur, int blurSize){
    // crée une image dont les pixels représente le potentiel du point nécessaire à la détection future de la rout
    Mat sobelX, sobelY, image2 ;
    cvtColor(image, image2, CV_BGR2GRAY) ;
    Sobel(image2,sobelX,CV_32F,1,0);
    Sobel(image2,sobelY,CV_32F,0,1);
    int nl= image2.rows ;
    int nc= image2.cols ;
    Mat result(nl,nc, CV_8U) ;
    for(int j=0; j<nl; j++){
        float* dataX= sobelX.ptr<float>(j);
        float* dataY= sobelY.ptr<float>(j);
        uchar* res= result.ptr<uchar>(j);
        for(int i=0; i<nc; i++){
            *res = uchar(floor(a / (1. + b*((*dataX)*(*dataX)+(*dataY)*(*dataY))))) ;
            dataX++; dataY++; res++;
        }
    }
    Mat result2 ;
    if (blurSize!=1){
        if (avGaussBlur)
            blur(result, result2, Size(blurSize,blurSize));
        else
            GaussianBlur(result,result2,cv::Size(blurSize,blurSize),1.5*blurSize);
        return result2 ;
    }
    return result ;
}



Mat ImageProcessing::snakeRoadBorderLine(Mat &image, int shiftingRigidity, int widthRigidity, int maxWidthDifference, bool cutColor, int cuttingLimit){
    // essaye de suivre les bords de la route dans le potentiel calculé par la fonction createPotential
    int nx = image.cols ;
    int ny = image.rows ;
    int dst = nx/5. ;
    int dstMin = dst - dst*maxWidthDifference/100. ;
    int dstMax = dst + dst*maxWidthDifference/100. ;
    int yLimit = (cutColor ? cuttingLimit*ny/100 : 0) ;
    int xl = 2*dst ;
    int xr = 3*dst ;
    int y = ny-1 ;
    char s = 1, w = 1 ;

    Mat result(ny, nx, CV_8UC3);
    //cvtColor(image, result, CV_GRAY2BGR);
    while (xl!=0 && xr!=nx-1 && y!=yLimit){
        y-- ;
        int xlm = xl ;
        int xrm = xr ;
        bool shifts = false ;
        int potm = image.at<uchar>(y, xl) + image.at<uchar>(y, xr) ;
        if (s >= shiftingRigidity){
            int pot = image.at<uchar>(y, xl-1) + image.at<uchar>(y, xr-1) ;
            if (pot<potm){
                xlm=xl-1; xrm=xr-1; potm=pot;
                shifts = true ;
            }
            pot = image.at<uchar>(y, xl+1) + image.at<uchar>(y, xr+1) ;
            if (pot<potm){
                xlm=xl+1; xrm=xr+1; potm=pot;
                shifts = true ;
            }
        } else
            s++ ;
        if (w >= widthRigidity){
            int pot ;
            if (dst<dstMin){
                pot = image.at<uchar>(y, xl+1) + image.at<uchar>(y, xr) ;
                if (pot<potm){
                    xlm=xl+1; xrm=xr; potm=pot;
                    shifts = false ;
                    w = 1 ;
                }
                pot = image.at<uchar>(y, xl) + image.at<uchar>(y, xr-1) ;
                if (pot<potm){
                    xlm=xl; xrm=xr-1; potm=pot;
                    shifts = false ;
                    w = 1 ;
                }
            }
            if (dst<dstMax){
                pot = image.at<uchar>(y, xl) + image.at<uchar>(y, xr+1) ;
                if (pot<potm){
                    xlm=xl; xrm=xr+1; potm=pot;
                    shifts = false ;
                    w = 1 ;
                }
                pot = image.at<uchar>(y, xl-1) + image.at<uchar>(y, xr) ;
                if (pot<potm){
                    xlm=xl-1; xrm=xr; potm=pot;
                    shifts = false ;
                    w = 1 ;
                }
            }
        } else
            w++ ;
        if (shifts) s=1 ;
        xl = xlm ; xr = xrm ; dst = xr - xl ;
        for(int x = xl ; x<=xr ; x++){
            //result.at<Vec3b>(y,x)[0] = 0 ;
            //result.at<Vec3b>(y,x)[1] = 0 ;
            result.at<Vec3b>(y,x)[2] = 255 ;
        }
    }

    return result ;
}





