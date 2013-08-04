#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv ;

#include <QThread>
#include <QImage>
#include <QMap>


class ImageProcessing : public QThread
{
public:
    explicit ImageProcessing() ;
    ImageProcessing(String file, QObject *parent) ;
    void setImage(String file) ;
    QImage getResult();
    QImage getSampleQImage();
    void setDoA(bool b);
    void setDoB(bool b);
    void setDoC(bool b);
    void setDoD(bool b);
    void setDoE(bool b);
    void setDoF(bool b);
    void setDoG(bool b);
    void setDoH(bool b);
    void setDoI(bool b);
    void setDoMedianFilterA(bool b);
    void setDoLowPassFilterA(bool b);
    void setFilterSizeA(int i);
    void setColorSpaceB(int i);
    void setDoBackProjectingB(bool b);
    void setBackprojectingTresholdB(int i);
    void setDoDistanceFilterB(bool b);
    void setDistanceFilterTresholdB(int i);
    void setSamplePosxB(int i);
    void setSamplePosyB(int i);
    void setSampleSizeB(int i);
    void setDoMedianFilterC(bool b);
    void setDoClosing(bool b);
    void setDoOpenning(bool b);
    void setClosingPrioritaryC(bool b);
    void setFilterSizeC(int i);
    void setOpenningSizeC(int i);
    void setClosingSizeC(int i);
    void setOpenningRepetitionsC(int i);
    void setClosingRepetitionsC(int i);
    void setDoFindContoursD(bool b);
    void setDoMinPerimeterD(bool b);
    void setDoCannyD(bool b);
    void setMinPerimeterD(int i);
    void setThicknessD(int i);
    void setCannyLowThresholdD(int i);
    void setCannyHighThresholdD(int i);
    void setStepRadiiE(int i);
    void setStepAngleE(int i);
    void setThresholdE(int i);
    void setMiniRoadAngleE(int i);
    void setFourPointsRatioF(double d);
    void setResultSizeRatioF(double d);
    void setResolutionRatioF(int i) ;
    void setAG(double d);
    void setBG(double d);
    void setAvGaussBlurG(bool b);
    void setBlurSizeG(int i);
    void setShiftingRigidityH(int i);
    void setWidthRigidityH(int i);
    void setMaxWidthDifferenceH(int i);
    void setCutColorH(bool b);
    void setCuttingLimitH(int i);
    void setTransparencyH(int i);

protected:
    Mat imgSource ;
    Mat imgResult ;
    String file ;
    Mat homography ;
    bool doA, doB, doC, doD, doE, doF, doG, doH, doI ;
    bool doMedianFilterA, doLowPassFilterA ; int filterSizeA ;
    int colorSpaceB, backprojectingTresholdB, distanceFilterTresholdB ; bool doBackprojectingB, doDistanceFilterB ;
    int samplePosxB, samplePosyB, sampleSizeB ;
    bool doMedianFilterC, doClosingC, doOpenningC, closingPrioritaryC ;
    int filterSizeC, openningSizeC, closingSizeC, openningRepetitionsC, closingRepetitionsC ;
    bool doFindContoursD, doMinPerimeterD, doCannyD ; int minPerimeterD, thicknessD, cannyLowThresholdD, cannyHighThresholdD ;
    int stepRadiiE, stepAngleE, thresholdE, miniRoadAngleE ;
    double fourPointsRatioF, resultSizeRatioF ; int resolutionRatioF ;
    double aG, bG ; bool avGaussBlurG ; int blurSizeG ;
    int shiftingRigidityH, widthRigidityH, maxWidthDifferenceH, cuttingLimitH, transparencyH ; bool cutColorH ;

    virtual void run();

    // Fonctions de traitement d'image
    Mat lowPassFilter(const Mat &image, int filterSize);
    Mat medianFilter(const Mat &image, int filterSize);
    Mat getSample(const Mat &image, int samplePosx, int samplePosy, int sampleSize) ;
    Mat backprojectionGray(const Mat &image, int treshold, int samplePosx, int samplePosy, int sampleSize) ;
    Mat backprojectionBGR(const Mat &image, int treshold, int samplePosx, int samplePosy, int sampleSize) ;
    Mat backprojectionCIE(const Mat &image, int treshold, int samplePosx, int samplePosy, int sampleSize) ;
    Mat backprojectionHSV(const Mat &image, int treshold, int samplePosx, int samplePosy, int sampleSize) ;
    Mat backprojectionYCRCB(const Mat &image, int treshold, int samplePosx, int samplePosy, int sampleSize) ;
    uchar getAverageColorGray(const Mat &image, int samplePosx, int samplePosy, int sampleSize) ;
    Mat distanceFilterGray(Mat &image, int treshold, int samplePosx, int samplePosy, int sampleSize) ;
    Vec3b getAverageColor3b(const Mat &image, int samplePosx, int samplePosy, int sampleSize) ;
    Mat distanceFilterBGR(Mat &image, int treshold, int samplePosx, int samplePosy, int sampleSize) ;
    Mat distanceFilterCIE(Mat &image, int treshold, int samplePosx, int samplePosy, int sampleSize) ;
    Vec2b getAverageColorHSV(const Mat &image, int samplePosx, int samplePosy, int sampleSize) ;
    Mat distanceFilterHSV(Mat &image, int treshold, int samplePosx, int samplePosy, int sampleSize) ;
    Vec2b getAverageColorYCRCB(const Mat &image, int samplePosx, int samplePosy, int sampleSize) ;
    Mat distanceFilterYCRCB(Mat &image, int treshold, int samplePosx, int samplePosy, int sampleSize) ;
    Mat openning(const Mat &image, int size) ;
    Mat closing(const Mat &image, int size) ;
    Mat performCanny(const Mat &image, int lowThreshold, int highThreshold) ;
    Mat performFindContours(Mat &image, int thickness, bool doMinPerimeter, int minPerimeter) ;
    vector<Vec2f> extractLines(Mat &image, int stepRadii, int stepAngle, int threshold, int cannyLowThreshold, int cannyHighThreshold) ;
    Mat extractAndDrawRoadLines(Mat &imageOrigin, Mat &mask, int stepRadii, int stepAngle, int threshold, int cannyLowThreshold, int cannyHighThreshold, int miniRoadAngle) ;
    vector<Vec2f> extractRoadLines(Mat &imageOrigin, Mat &mask, int stepRadii, int stepAngle, int threshold, int cannyLowThreshold, int cannyHighThreshold, int miniRoadAngle) ;
    Mat birdEyeView(Mat &imageOrigin, vector<Vec2f> roadLines, double fourPointsRatio, double resultSizeRatio, int resolutionRatio) ;
    Mat createPotential(const Mat& image, double a, double b, bool avGaussBlur, int blurSize);
    Mat snakeRoadBorderLine(Mat& image, int shiftingRigidity, int widthRigidity, int maxWidthDifference, bool cutColor, int cuttingLimit) ;

signals:

};

#endif // IMAGEPROCESSING_H
